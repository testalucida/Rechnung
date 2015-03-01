/* 
 * File:   RechnungGroup.cpp
 * Author: max
 * 
 * Created on 21. Dezember 2013, 12:56
 */

#include "RechnungGroup.h"
#include "../images/plus_36x36.xpm"
#include "../images/cancel_36x36.xpm"
#include "../images/save_36x36.xpm"
#include "../images/save_deact_36x36.xpm"
#include "../images/print_36x36.xpm"
#include "../images/equal_36x36.xpm"  
#include "../images/close_36x36.xpm"
#include "Rechnung.h"

#include <my/convert.h>
#include <my/datetime.h>
#include <my/CharBuffer.h>

#include <flx/Flx_Box.h>
#include <flx/flx_boxtypes.h>
#include <flx/flx_colors.h>
#include <flx/Flx_DateChooser.h>
#include <flx/Flx_Button.h>
#include <flx/Flx_FloatInput.h>
#include <flx/Flx_Message.h>

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Pixmap.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Text_Editor.H>

#include <typeinfo>

using namespace my;
using namespace flx;

RechnungGroup::RechnungGroup( int x, int y, int w, int h, const char *pLabel ) 
: Fl_Group( x, y, w, h, pLabel )
{
    //box( FL_DOWN_BOX );
    labelfont( fl_font() );
    labelsize( fl_size() );
    color( FLX_COLOR_GREEN );
    //color( FL_WHITE );
    
    int headerH = 80;
    int summeH = 30;
    int m = 5;
    int detailsH = h - headerH - summeH - m;
    int marginH = 30;
    int marginV = 10;
    int widgH = 23;
    
    
    Fl_Group *pHeader = new Fl_Group( x, y+m, w, headerH );
    {
        //pHeader->box( FLX_GRADIENT_BOX );
        pHeader->box( FL_FLAT_BOX );
        pHeader->color( fl_lighter( FL_GRAY ) );
        _pRenr = new Flx_Box( x+marginH, y+marginV, 80, widgH, "Nr.14 000" );
        _pRenr->align( FL_ALIGN_CENTER | FL_ALIGN_INSIDE );
        _pRenr->box( FLX_GRADIENT_BOX );
        
        int W=0, H=0, vmargin = 3;
        static const char label[] = "Rechnungsdatum: ";
        fl_measure( label, W, H, 0);
        _pRedatum = new Flx_DateChooser( _pRenr->x() + _pRenr->w() + W + marginH,
                                         _pRenr->y(), widgH, label );
        _pRedatum->signalDateSelected.
                connect< RechnungGroup, &RechnungGroup::onRedatumChanged >( this );
        _pKundeName = new Flx_Box( _pRenr->x(), 
                                    _pRenr->y() + _pRenr->h() + marginV, 
                                    310, widgH );
        _pKundeName->box( FLX_GRADIENT_BOX );
        
        int sl = 38; // _pKundeName->y() - this->y() + _pKundeName->h() - marginV;
//        _pNewPartBtn = new Flx_Button( _pRedatum->x() + _pRedatum->w() + 20,
//                                       _pRedatum->y(), sl, sl );
//        _pNewPartBtn = new Flx_Button( x + w - 4*sl - 4*vmargin, /*4==Anzahl Buttons*/
//                                       _pRedatum->y(), sl, sl );
//        _pNewIcon = new Fl_Pixmap( plus_xpm );
//        _pNewPartBtn->image( _pNewIcon );
//        _pNewPartBtn->tooltip( "Leistungsposition hinzufügen" );
//        
//        _pDeleteBtn = new Flx_Button( _pNewPartBtn->x() + _pNewPartBtn->w() + vmargin,
//                _pNewPartBtn->y(), sl, sl );
//        _pDeleteIcon = new Fl_Pixmap( cancel_xpm );
//        _pDeleteBtn->image( _pDeleteIcon );
//        _pDeleteBtn->tooltip( "Rechnung löschen" );
//        _pDeleteBtn->signalSelected.
//            connect< RechnungGroup, &RechnungGroup::onDeleteRechnung >( this );
        
//         _pSumBtn = new Flx_Button( _pDeleteBtn->x() + _pDeleteBtn->w() + vmargin,
//                _pDeleteBtn->y(), sl, sl );
//        _pSumIcon = new Fl_Pixmap( equal_xpm );
//        _pSumBtn->image( _pSumIcon );
//        _pSumBtn->tooltip( "Abschließenden Summenblock einfügen" );
//        _pSumBtn->signalSelected.
//            connect< RechnungGroup, &RechnungGroup::onAddSum >( this );
//        _pSumBtn->clear_visible();
        
//        _pCloseBtn = new Flx_Button( _pDeleteBtn->x() + _pDeleteBtn->w() + vmargin,
//        _pDeleteBtn->y(), sl, sl );
//        _pCloseIcon = new Fl_Pixmap( close_xpm );
//        _pCloseBtn->image( _pCloseIcon );
//        _pCloseBtn->tooltip( "Rechnung schließen" );
//        _pCloseBtn->signalSelected.
//            connect< RechnungGroup, &RechnungGroup::onCloseRechnung >( this );
//       
        
//        _pSaveBtn = new Flx_Button( _pSumBtn->x() + _pSumBtn->w() + vmargin,
//                _pNewPartBtn->y(), sl, sl );
//        _pSaveIcon = new Fl_Pixmap( save_deact_xpm );
//        _pSaveBtn->image( _pSaveIcon );
//        _pSaveBtn->tooltip( "Rechnung speichern" );
//        _pSaveBtn->signalSelected.
//            connect< RechnungGroup, &RechnungGroup::onSave >( this );
        
//        _pPrintBtn = new Flx_Button( _pCloseBtn->x() + _pCloseBtn->w() + vmargin,
//                _pNewPartBtn->y(), sl, sl );
//        _pPrintIcon = new Fl_Pixmap( print_xpm );
//        _pPrintBtn->image( _pPrintIcon );
//        _pPrintBtn->tooltip( "Rechnung drucken" );
//        _pPrintBtn->signalSelected.
//            connect< RechnungGroup, &RechnungGroup::onPrint >( this );
//        
    }
    pHeader->end();
    
    _pDetails = new Fl_Group( x, pHeader->y() + pHeader->h(), w, detailsH );
    {
        _pDetails->box( FL_FLAT_BOX );
        _pEdi = new Fl_Text_Editor( _pDetails->x()+2, _pDetails->y()+2,
                                    _pDetails->w()-4, _pDetails->h()-4 );
        _pEdi->buffer( new Fl_Text_Buffer() );
    }
    _pDetails->end();
    
    _pSummeGrp = new Fl_Group(  pHeader->x(), 
                                _pDetails->y() + _pDetails->h(),
                                pHeader->w(), summeH );
    {
        _pSummeGrp->box( FL_DOWN_BOX );
        _pSummeGrp->color( FL_YELLOW );
        //_pSummeGrp->color( pHeader->color() );
//        _pSummeStd = new Flx_FloatInput( _pSummeGrp->x() + 60,
//                                        _pSummeGrp->y() + 3, 
//                                        60, 26, "Stunden: " );
//        _pSummeStd->textsize( 16 );
//        _pSummeStd->textcolor( FL_RED );
//        _pSummeStd->signalChanged.
//                connect< RechnungGroup, &RechnungGroup::onSummeChanged >( this );
        
        _pSummeNet = new Flx_FloatInput( 
                _pSummeGrp->x() + 80, _pSummeGrp->y() + 2,
                75, 26, "Summe: " );
        _pSummeNet->textsize( 16 );
        _pSummeNet->textcolor( FL_RED );
        
    }
    _pSummeGrp->end();
    
    end();
//    printf( "RechnungGroup y: %d, h: %d ==> ymax = %d\n", 
//            this->y(), this->h(), this->y()+this->h() );
//    printf( "HeaderGroup y: %d, h: %d ==> ymax = %d\n", 
//            pHeader->y(), pHeader->h(), pHeader->y()+pHeader->h() );
//    printf( "DetailsGroup y: %d, h: %d ==> ymax = %d\n", 
//            _pDetails->y(), _pDetails->h(), _pDetails->y()+_pDetails->h() );
//    printf( "SummeGrp y: %d, h: %d ==> ymax = %d\n", 
//            pSummeGrp->y(), pSummeGrp->h(), pSummeGrp->y()+pSummeGrp->h() );
}

void RechnungGroup::setRechnung( Rechnung &rechng ) {
    _pRechng = &rechng;
    setKopfdaten();

    _pEdi->buffer()->text( rechng.getText() );
    _pEdi->callback( staticOnTextChanged, this );
    _pEdi->when( FL_WHEN_CHANGED | FL_WHEN_NOT_CHANGED );
//    _pSummeStd->value( rechng.getGesamtStunden() );
    
    _pSummeNet->value( rechng.getRechngSummeNetto() );
    _pSummeNet->signalChanged.
                connect< RechnungGroup, &RechnungGroup::onSummeChanged >( this );
    
    _pRechng->signalRechnungNummerSet.
        connect< RechnungGroup, &RechnungGroup::onRechnungNummerSet >( this );
}

Rechnung &RechnungGroup::getRechnung() { 
    _pRechng->setText( _pEdi->buffer()->text() );
    return *_pRechng; 
}

void RechnungGroup::setKopfdaten() {
    setRechnungsnummer();
    _pKundeName->copy_label( _pRechng->getName().get() );
    _pRedatum->setDate( _pRechng->getRedatum() );
}

void RechnungGroup::setRechnungsnummer() {
    //Rechnungsnummer setzt sich zusammen aus Rechng.jahr + Rechnungsnummer:
    CharBuffer cbRenr;
    cbRenr.addInt( _pRechng->getRejahr() );
    int renr = _pRechng->getRenr();
    if( renr == 0 ) {
        cbRenr.add( "<neu>" );
    } else {
        cbRenr.addInt( _pRechng->getRenr() );
    }
    _pRenr->copy_label( cbRenr.get() );
}


void RechnungGroup::setSummen( float gesamtstunden, float resumme ) {
//    _pSummeStd->value( gesamtstunden );
    _pSummeNet->value( resumme );
}

void RechnungGroup::getSummen( float &gesamtstunden, float &resumme ) const {
//    gesamtstunden = _pSummeStd->floatValue();
    resumme = _pSummeNet->floatValue();
}


//void RechnungGroup::onDeleteRechnung( flx::Flx_Button &, flx::ActionParm& ) {
//    RechnungGroupParm parm;
//    parm.action = RECHGRP_ACTION_DELETE_RECHNG;
//    signalRechnungGroupAction.send( this, &parm );
//}

//void RechnungGroup::onAddSum( flx::Flx_Button &, flx::ActionParm& ) {
//    RechnungGroupParm parm;
//    parm.action = RECHGRP_ACTION_ADD_SUM;
//    signalRechnungGroupAction.send( this, &parm );
//}

//void RechnungGroup::onSave( flx::Flx_Button &, flx::ActionParm& ) {
//    RechnungGroupParm parm;
//    parm.action = RECHGRP_ACTION_SAVE;
//    signalRechnungGroupAction.send( this, &parm );
//}

//void RechnungGroup::onPrint( flx::Flx_Button &, flx::ActionParm& ) {
//    RechnungGroupParm parm;
//    parm.action = RECHGRP_ACTION_PRINT;
//    signalRechnungGroupAction.send( this, &parm );
//}

void RechnungGroup::onRechnungNummerSet( Rechnung &, int & ) {
    setRechnungsnummer();
}

void RechnungGroup::onSummeChanged( flx::Flx_NumericInput &, flx::ActionParm & ) {
//    _pRechng->setGesamtStunden( _pSummeStd->floatValue() );
    _pRechng->setRechngSummeNetto( _pSummeNet->floatValue() );
    RechnungGroupParm parm;
    parm.action = RECHGRP_ACTION_CHANGE_SUM;
    signalRechnungGroupAction.send( this, &parm );
}

void RechnungGroup::onRedatumChanged( flx::Flx_DateChooser &, my::MyDate &redatum ) {
    _pRechng->setRedatum( redatum );
    RechnungGroupParm parm;
    parm.action = RECHGRP_ACTION_CHANGE_DATE;
    signalRechnungGroupAction.send( this, &parm );
}

void RechnungGroup::staticOnTextChanged(Fl_Widget*, void *pUserdata ) {
    ((RechnungGroup*)pUserdata)->onTextChanged();
}

void RechnungGroup::onTextChanged() {
    RechnungGroupParm parm;
    parm.action = RECHGRP_ACTION_CHANGE_TEXT;
    signalRechnungGroupAction.send( this, &parm );
}

//void RechnungGroup::onCloseRechnung( flx::Flx_Button &, flx::ActionParm& ) {
//    RechnungGroupParm parm;
//    parm.action = RECHGRP_ACTION_CLOSE_RECHNG;
//    signalRechnungGroupAction.send( this, &parm );
//}

void RechnungGroup::computeSummen() {
//    float summe = 0;
//    float stunden = 0;
//    for( int i = 0, imax = _pDetails->children(); i < imax; i++ ) {
//        Fl_Widget *pW = _pDetails->child( i );
//        if( typeid( *pW ).name() == typeid( RechnungPosGroup ).name() ) {
//            RechnungPosGroup *pPosGrp = (RechnungPosGroup*)pW;
//            RechnungPosAttr info = pPosGrp->getPreisInfo();
//            summe += info.preis;
//            stunden += info.stunden;
//        }
//    }
//    _pSummeStd->value( stunden );
//    _pSummeNet->value( summe );
}

int RechnungGroup::getVertSpace() const {
    int n = _pDetails->children();
    if( n > 0 ) {
        Fl_Widget *pLastChild = _pDetails->child( n - 1 );
        int y = pLastChild->y() + pLastChild->h() + 4;
        return this->h() - _pSummeGrp->h() - (y - this->y());
    }
    return _pDetails->h();
}

RechnungGroup::~RechnungGroup( ) {
}

