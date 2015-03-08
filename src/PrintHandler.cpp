/* 
 * File:   PrintHandler.cpp
 * Author: max
 * 
 * Created on 17. Dezember 2013, 20:05
 */

#include "PrintHandler.h"
#include "PrintablePage.h"
#include "Rechnung.h"
#include "PrintView.h"
#include "RechnungIO.h"
#include "adresse.h"

#include <flx/Flx_Dialog.h>

#include <FL/Fl_Scroll.H>

using namespace flx;

PrintHandler::PrintHandler( ) {
}

void PrintHandler::onPrint( PrintView &, FirstPrintablePage &page ) {
    Fl_Printer printer;
    printer.start_job( 1 );
    printer.start_page();
//    int w=0, h=0;
//    printer.printable_rect( &w, &h );
    printer.origin( 0, 0 );
//    printer.margins()
    printer.print_widget( &page, 0, 0 );
    printer.end_page();
    printer.end_job();
    
}

void PrintHandler::print( const Rechnung &rechng, bool preview ) {
    createPrintablePages( rechng );
    bool print = true;
    if( preview ) {
        print = showPreview();
    }
 
    if( print ) {
        int nPages = 1;
        if( _printer.start_job( nPages ) == 0 ) {
            int rc = _printer.start_page();
            //    int w=0, h=0;
            //    printer.printable_rect( &w, &h );
            _printer.origin( 0, 0 );
            _printer.print_widget( _pages[0], 0, 0 );
            stopPrinter();
        }
    }
}


void PrintHandler::stopPrinter() {
    _printer.end_page();
    _printer.end_job();
}

void PrintHandler::createPrintablePages( const Rechnung &rechng ) {
    FirstPrintablePage *pFirst = new FirstPrintablePage( 0, 0 );
    _pages.push_back( pFirst );
    FirstPrintablePage &first = *pFirst;
    Adresse adr;
    RechnungIO::instance().getAdresse( rechng.getKdnr(), adr );
    first.setAdresse( adr.toString() );
    first.setDatumAndRenr( rechng.getRedatum().ToEurString().c_str(), 
                           rechng.getRejahr(),rechng.getRenr() );
    
    int cntLeistg = 0;
    
    first.addLeistung( rechng.getText() );
//    for( int maxLeistg = first.getMaxLeistungen(); 
//            cntLeistg < maxLeistg && cntLeistg < rechng.getPosCount(); 
//            cntLeistg++ )
//    {
//        RechnungPos &pos = rechng.getPos( cntLeistg );
//        first.addLeistung( 
//                pos.getPosText().get(),
//                pos.getAnzahlStunden(),
//                pos.getPreisProStd(),
//                pos.getPosBetrag(),
//                0 );
//    }
 
    float ust = rechng.getRechngSummeNetto() * 0.19;
    float bruttoGesamt = rechng.getRechngSummeNetto() + ust;
    first.addGesamtSumme( rechng.getGesamtStunden(), 
            rechng.getPreisProStd(), 
            19.0, 
            ust, 
            rechng.getRechngSummeNetto(), 
            bruttoGesamt );
}

#include<flx/Flx_Button.h>
bool PrintHandler::showPreview() const {
    Flx_Dialog *pDlg = new Flx_Dialog
            ( 100, 100, 800, 700, "Rechnungsverwaltung Kendel Büroservice" );
    int x, y, w, h;
    pDlg->getClientArea( x, y, w, h );
    Fl_Scroll *pScroll = new Fl_Scroll( x, y, w, h );
//    FirstPrintablePage *pPage = new FirstPrintablePage( 0, 0 );
//    pPage->addLeistung( "TestLeistung 1", 3, 32, 96 );
//    pPage->addLeistung( "TestLeistung 2", 3, 32, 96 );
//    pPage->addLeistung( "TestLeistung 3", 3, 32, 96 );
    pScroll->end();

    pDlg->add( pScroll );
    pScroll->add( _pages[0] );
    pDlg->parent( NULL );
    
    return pDlg->show( true );
}

PrintHandler::~PrintHandler( ) {
    vector< PrintablePage* >::iterator itr = _pages.begin();
    for( ; itr != _pages.end(); itr++ ) {
        delete *itr;
    }
}

