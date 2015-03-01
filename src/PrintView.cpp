/* 
 * File:   PrintView.cpp
 * Author: max
 * 
 * Created on 16. Dezember 2013, 15:10
 */

#include "PrintView.h"

#include "PrintablePage.h"

#include <flx/Flx_Group.h>
#include <flx/Flx_Button.h>

#include <FL/Fl_Scroll.H>

using namespace flx;
using namespace my;

PrintView::PrintView(  int x, int y, int w, int h ) 
: Flx_Group( x, y, w, h )
{
    int btnH = 27;
    _pPrintScroll = new Fl_Scroll( x, y, w, h - btnH );
    //_pPage = new FirstPrintablePage( x, y );
    _pPrintScroll->end();
    
    Flx_Group *pBtnGroup = new Flx_Group( x, y + h - btnH, w, btnH );
    _pBtnPrint = new Flx_Button( pBtnGroup->x() + 10, 
                                 pBtnGroup->y() + 2, 
                                 70, 23, "print"  );
    _pBtnPrint->signalSelected.connect< PrintView, &PrintView::onPrint >( this );
    pBtnGroup->end();
    
    end();
}

void PrintView::addPrintablePage( PrintablePage &page ) {
    _pPrintScroll->add( page );
}

void PrintView::onPrint( flx::Flx_Button &, flx::ActionParm & ) {
    //signalPrint.send( *this, *_pPage );
}
   
PrintView::~PrintView( ) {
}

