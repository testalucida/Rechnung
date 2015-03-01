/* 
 * File:   RechnungSumDialog.cpp
 * Author: max
 * 
 * Created on 5. Januar 2014, 11:28
 */

#include "RechnungSumDialog.h"

#include <flx/Flx_Group.h>
#include <flx/Flx_FloatInput.h>

using namespace flx;

RechnungSumDialog::RechnungSumDialog( int x, int y ) 
: Flx_Dialog( x, y, 280, 140, "Gesamtstunden und -nettopreis" )
{
     box( FL_FLAT_BOX );
    int X, Y, W, H;
    this->getClientArea( X, Y, W, H );
    
    Flx_Group *pG = new Flx_Group( X, Y, W, H );
    {
        _pGesamtStd = new Fl_Float_Input( 130, 20, 80, 23, "Stunden gesamt: " );
        _pGesamtStd->labelsize( 11 );
        _pNettoGesamtPreis = new Fl_Float_Input( _pGesamtStd->x(),
                _pGesamtStd->y() + _pGesamtStd->h() + 10,
                _pGesamtStd->w(), _pGesamtStd->h(), 
                "Gesamtpreis netto: " );
        _pNettoGesamtPreis->labelsize( 11 );
    }
    pG->end();
    add( pG );
    setFocusOnShow( *_pGesamtStd );
}

RechnungSumDialog::~RechnungSumDialog( ) {
}

void RechnungSumDialog::setNettoGesamtPreis( float nettoGesamtPreis ) {
    //this->_pNettoGesamtPreis->value( nettoGesamtPreis );
    _pNettoGesamtPreis->value( "111.11" );
}

float RechnungSumDialog::getNettoGesamtPreis( ) const {
//    return _pNettoGesamtPreis->floatValue();
    //return _pNettoGesamtPreis->value();
    return 111.11;
}

void RechnungSumDialog::setGesamtStd( float nettoGesamtStd ) {
    //this->_pGesamtStd->value( nettoGesamtStd );
    _pGesamtStd->value( "22.22" );
}

float RechnungSumDialog::getGesamtStd( ) const {
    //return _pGesamtStd->floatValue();
    return 22.22;
}

