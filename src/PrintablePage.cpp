/* 
 * File:   PrintablePage.cpp
 * Author: max
 * 
 * Created on 16. Dezember 2013, 15:21
 */

#include "PrintablePage.h"
#include "RechnungPosGroupPrint.h"
#include "Rechnung.h"
#include "../images/Kendel.xpm"

#include <flx/Flx_Output.h>
#include <flx/Flx_MultiLineOutput.h>
#include <flx/Flx_Box.h>

#include <my/CharBuffer.h>

#include <FL/fl_draw.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_PNG_Image.H>

using namespace flx;
using namespace my;


PrintablePage::PrintablePage( int x, int y ) 
: Flx_Group( x, y, 600, 828 ) 
, _leftMargin( 50 )
, _footerY( 0 )
, _distV( 10 )
, _summenblockH( 60 )
, _bottomMargin( 40 )
, _footerH( 30 )
{
     _footerY = this->y() + h() - _footerH - _bottomMargin;
    createFooter();
    //no end() here!
}

void PrintablePage::createFooter() {
    createFooterAnschrift();
    createFooterTkv();
    createFooterMail();
    createFooterKonto();
    createFooterStNr();
}

void PrintablePage::createFooterAnschrift() {
    _pFooterAnschrift = new Flx_MultiLineOutput( x() + _leftMargin, _footerY, 90, _footerH );
    _pFooterAnschrift->clear_visible_focus();
    _pFooterAnschrift->box( FL_NO_BOX );
    _pFooterAnschrift->textsize( 6 );
    _pFooterAnschrift->value( "Birnenweg 2\n91077 Kleinsendelbach" );
}

void PrintablePage::createFooterTkv() {
    int X = _pFooterAnschrift->x() + _pFooterAnschrift->w() /*+ 10*/;
    _pFooterTkv = new Flx_MultiLineOutput( X, _footerY, 80, _footerH );
    _pFooterTkv->clear_visible_focus();
    _pFooterTkv->box( FL_NO_BOX );
    _pFooterTkv->textsize( 6 );
    _pFooterTkv->value( "Tel: 09126/29 08 60\nFax: 09126/29 08 80" );
}

void PrintablePage::createFooterMail() {
    int X = _pFooterTkv->x() + _pFooterTkv->w() /*+ 10*/;
    _pFooterMail = new Flx_MultiLineOutput( X, _footerY, 112, _footerH );
    _pFooterMail->clear_visible_focus();
    _pFooterMail->box( FL_NO_BOX );
    _pFooterMail->textsize( 6 );
    _pFooterMail->value( "mail: info@kendel-bueroservice.de\nwww.kendel-bueroservice.de" );
}

void PrintablePage::createFooterKonto() {
    int X = _pFooterMail->x() + _pFooterMail->w() + 10;
    _pFooterKonto = new Flx_MultiLineOutput( X, _footerY, 120 /*80*/, _footerH );
    _pFooterKonto->clear_visible_focus();
    _pFooterKonto->box( FL_NO_BOX );
    _pFooterKonto->textsize( 6 );
    //_pFooterKonto->value( "Sparkasse Erlangen\nKto.Nr. 30 001 093\nBLZ 763 500 00" );
    _pFooterKonto->value( "Sparkasse Erlangen\nIBAN DE72 7635 0000 0030 0010 93\nBIC BYLADEM1ERH" );
}

void PrintablePage::createFooterStNr() {
    int X = _pFooterKonto->x() + _pFooterKonto->w() + 10;
    _pFooterStNr = new Flx_MultiLineOutput( X, _footerY, 80, _footerH );
    _pFooterStNr->clear_visible_focus();
    _pFooterStNr->box( FL_NO_BOX );
    _pFooterStNr->textsize( 6 );
    _pFooterStNr->value( "St.Nr. 217/235/50499" );
}

bool PrintablePage::addLeistung( const char *pLeist, float nStunden,
                                 float nettoPreisProStd, float nettoPreis,
                                 int nUnderlinesNettoPreis ) 
{
    CharBuffer text( pLeist );
    //wenn Stunden angegeben sind, wird eine zusätzliche Zeile unter der 
    //eigentlichen Leistungsbeschreibung ausgegeben:
    if( nStunden > 0 ) {
        CharBuffer aufwand;
        aufwand.addFloat( nStunden );
        aufwand.add( " Stunden" );
        if( nettoPreisProStd > 0 ) {
            aufwand.add( " à € " );
            aufwand.addFloat( nettoPreisProStd );
        }
        if( text.getLength() > 0 ) {
            text.add( '\n' );
        }
        text.add( aufwand.get() );
    }
    
    int y = getNextY();
    //wieviel Platz braucht die neue Position...
    int h = getHeightNeeded( text.get() );
    h += 5; //top & bottom margins
    if( (y + h + _summenblockH ) > _footerY ) {
        //...zu viel
        return false;
    }
    int w = this->w() - _leftMargin - 110;
    RechnungPosGroupPrint *pLeistGrp = 
            new RechnungPosGroupPrint( _leftMargin, y, w, h /*50*/ );
    
    pLeistGrp->setLeistung( text.get() );
    
    //wenn der Netto-Preis angegeben ist, wird er ausgegeben:
    if( nettoPreis > 0 ) {
        pLeistGrp->setNettoPreis( nettoPreis, nUnderlinesNettoPreis );
        pLeistGrp->showEuroLabel( true );
    } else {
        pLeistGrp->showEuroLabel( false );
    }
    
    add( pLeistGrp );
    _leistungen.push_back( pLeistGrp );
    
    return true;
}

void PrintablePage::addGesamtSumme( float nStunden, float nettoPreisProStd, 
                                    float ustProz, float ust, 
                                    float nettoGesamt, float bruttoGesamt )
{
    _distV *= 2;
    addLeistung( "", nStunden, nettoPreisProStd, nettoGesamt );
    
    //die nächsten Zeilen mit geringerem Abstand:
    _distV = 7;
    
    //USt-Zeile
    CharBuffer ustZeile( "+ " );
    ustZeile.addFloat( ustProz );
    ustZeile.add( "% MWSt.");
    addLeistung( ustZeile.get(), 0, 0, ust, 1 );
    
    //Brutto-Summen-Zeile
    addLeistung( "", 0, 0, bruttoGesamt, 2 );
}

int PrintablePage::getHeightNeeded( const char *pText ) const {
    CharBuffer text( pText );
    int nlines = text.getNumberOf( '\n' ) + 1;
    return nlines * fl_size();
}

PrintablePage::~PrintablePage() {
    
}

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////

FirstPrintablePage::FirstPrintablePage( int x, int y ) : PrintablePage( x, y ) {
    createLogo( 300, 30/*50*/ );
    createAbsender( x+_leftMargin, y+100 );
    createAdresse();
    createDatumReNr();
    //createMeineBemuehungen();  
    createEinschraenkung();
 
    end();  
}

void FirstPrintablePage::createLogo( int x, int y ) {
    _pLogo = new Fl_PNG_Image( "/home/max/cpp/fltk/Rechnung/images/Kendel.png" );
    _pLogoBox = new Fl_Box( x, y, 200, 150 );
    _pLogoBox->image( _pLogo );
}

void FirstPrintablePage::createAbsender( int x, int y ) {
    _pAbsender = new Flx_Output( x, y, 380, 22 );
    _pAbsender->box( FL_NO_BOX );
    _pAbsender->textsize( 7 );
    _pAbsender->align( FL_ALIGN_INSIDE );
    _pAbsender->clear_visible_focus();
    _pAbsender->value( "KENDEL Büroservice . Birnenweg 2 . 91077 Kleinsendelbach" );
}

void FirstPrintablePage::createAdresse() {
    int y = _pAbsender->y() + _pAbsender->h() + 35;
    _pAdresse = new Flx_MultiLineOutput( _pAbsender->x(), y, 280, 100 );
    _pAdresse->box( FL_NO_BOX );
    _pAdresse->textsize( 9 );
    _pAdresse->clear_visible_focus();
    //TEST_pAdresse->value( "HONDA-Autohaus Am Eichberg GmbH\n\nAn der Müß 27\n\n96515 Sonneberg" );
}

void FirstPrintablePage::setAdresse( const char *pAdresse ) {
    _pAdresse->value( pAdresse );
}

void FirstPrintablePage::setDatumAndRenr( const char *pDatum, int rejahr, int renr ) {
    CharBuffer cb( pDatum );
    cb.add( "\n\nRechng.Nr.: " );
    cb.addInt( rejahr );
    cb.addInt( renr, "%03d" );
    //_pDatum_ReNr->value( cb.get() );  
    _pDatum_ReNr->copy_label( cb.get() );  
}  

void FirstPrintablePage::createDatumReNr() {
    int W = 110;
    int H = 50;
    int X = x() + w() - W - 75;
    int Y = _pAdresse->y() + _pAdresse->h() - H;
    //_pDatum_ReNr = new Flx_MultiLineOutput( X, Y, W, 50 );
    _pDatum_ReNr = new Flx_Box( X, Y, W, 50 );
    _pDatum_ReNr->box( FL_NO_BOX );
//    _pDatum_ReNr->textsize( 9 );
    _pDatum_ReNr->labelsize( 9 );
    _pDatum_ReNr->align( FL_ALIGN_RIGHT | FL_ALIGN_INSIDE );
    _pDatum_ReNr->clear_visible_focus();
    //_pDatum_ReNr->value( "10.11.2013\n\nNr. 13166" );
}

void FirstPrintablePage::createMeineBemuehungen() {
    int Y = _pAdresse->y() + _pAdresse->h() + 80;
    int H = 25;
    _pMeineBemuehungen = new Flx_MultiLineOutput( _pAdresse->x(), Y, 390, H );
    _pMeineBemuehungen->clear_visible_focus();
    _pMeineBemuehungen->box( FL_NO_BOX );
    _pMeineBemuehungen->textsize( 9 );
    _pMeineBemuehungen->value( "Für meine Bemühungen erlauben wir uns in Rechnung zu stellen:" );
}

void FirstPrintablePage::createEinschraenkung() {
    //int Y = _pAdresse->y() + _pAdresse->h() + 20 /*80*/;
    int H = 40 /*25*/;
    int Y = getFooterY() - H - 5;
    
    _pEinschraenkung = new Flx_MultiLineOutput( _pAdresse->x(), Y, 490, H );
    _pEinschraenkung->clear_visible_focus();
    _pEinschraenkung->box( FL_BORDER_BOX );
    _pEinschraenkung->textsize( 7 );
    CharBuffer txt;
    txt.add( "Hinweis auf die eingeschränkte Befugnis zur Hilfeleistung in Steuersachen gemäß §8 Abs. 4 i.V. §6 Nr. 3 und 4 StBergG:\n" );
    txt.add( "> Kontierung und Verbuchung der laufenden Geschäftsvorfälle innerhalb der Finanzbuchhaltung\n" );
    txt.add( "> Erstellung der laufenden Lohnabrechnungen, der Sozialversicherungsmeldungen und der Lohnsteueranmeldungen\n" );
    txt.add( "> Durchführung mechanischer Arbeitsgänge bei der Führung von Büchern und Aufzeichnungen, die für die Besteuerung von Bedeutung sind" );
    _pEinschraenkung->value( txt.get() );
}

int FirstPrintablePage::getVerticalSpace() const {
    return _footerY - ( getNextY() );
}

int FirstPrintablePage::getNextY() const {
    if( _leistungen.empty() ) {
        //return _pMeineBemuehungen->y() + _pMeineBemuehungen->h() + _distV;
        return _pDatum_ReNr->y() + _pDatum_ReNr->h() +  50;
    } else {
        std::vector< RechnungPosGroupPrint* >::const_iterator itr = 
                _leistungen.begin() + _leistungen.size() - 1;
       
        return (*itr)->y() + (*itr)->h() + _distV;
    }
}

FirstPrintablePage::~FirstPrintablePage( ) {
}

