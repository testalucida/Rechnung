/* 
 * File:   LeistungGroup.cpp
 * Author: max
 * 
 * Created on 18. Dezember 2013, 15:17
 */

#include "RechnungPosGroupPrint.h"

#include <flx/Flx_MultiLineInput.h>
#include <flx/Flx_FloatInput.h>
#include <flx/Flx_Box.h>

#include <my/convert.h>

#include <stdio.h>

using namespace flx;
using namespace my;

RechnungPosGroupPrint::RechnungPosGroupPrint( int x, int y, int w, int h ) 
: Flx_Group( x, y, w, h )
{
    int preisW = 50, preisH = 18;
    _pLeistung = new Flx_MultiLineInput( x, y, w - preisW, h );
    _pLeistung->textsize( 9 );
    _pLeistung->box( FL_NO_BOX );
    
    int X = _pLeistung->x() + _pLeistung->w();
    int Y = _pLeistung->y();
    _pWaehrung = new Flx_Box( X, Y, 30, preisH, "Eur" );
    _pWaehrung->box( FL_NO_BOX );
    _pWaehrung->labelsize( 9 );
    _pWaehrung->align( FL_ALIGN_INSIDE | FL_ALIGN_RIGHT );
    
    X += _pWaehrung->w();
    _pNettoPreisOut = new Flx_Box( X, Y, preisW, preisH );
    _pNettoPreisOut->box( FL_NO_BOX );
    _pNettoPreisOut->labelsize( 9 );
    _pNettoPreisOut->align( FL_ALIGN_INSIDE | FL_ALIGN_RIGHT );
    
    end();
}

void RechnungPosGroupPrint::setLeistung( const char *pText ) {
    _pLeistung->value( pText );
}

void RechnungPosGroupPrint::setNettoPreis( float preis, int underlines ) {
//    char buffer[11];
//    sprintf( buffer, "%.2f", preis );
//    _pNettoPreis->value( buffer );
    _pNettoPreisOut->copy_label( Convert::toString( preis )->c_str() );
    _pNettoPreisOut->setUnderline( underlines );
}

void RechnungPosGroupPrint::showEuroLabel( bool show ) {
    _pWaehrung->label( show ? "Eur" : "" );
}

RechnungPosGroupPrint::~RechnungPosGroupPrint( ) {
}

