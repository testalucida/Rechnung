/* 
 * File:   RechnungPos.cpp
 * Author: max
 * 
 * Created on 21. Dezember 2013, 23:29
 */

#include "RechnungPos.h"

RechnungPos::RechnungPos( ) : _flags( RECHNG_FLAG_NONE ) {
}

RechnungPos::~RechnungPos( ) {
}

void RechnungPos::setPosBetrag( float posBetrag ) {
    this->_posBetrag = posBetrag;
}

float RechnungPos::getPosBetrag( ) const {
    return _posBetrag;
}

void RechnungPos::setAnzahlStunden( float anzahlStunden ) {
    this->_anzahlStunden = anzahlStunden;
}

float RechnungPos::getAnzahlStunden( ) const {
    return _anzahlStunden;
}

void RechnungPos::setPosnr( int posnr ) {
    this->_posnr = posnr;
}

int RechnungPos::getPosnr( ) const {
    return _posnr;
}

const my::CharBuffer &RechnungPos::getPosText() const {
    return _text;
}

void RechnungPos::setPosText( const char *pText ) {
    _text.clear();
    _text.add( pText );
}

void RechnungPos::setPreisProStd( float preisStd ) {
    this->_preisProStd = preisStd;
}

float RechnungPos::getPreisProStd( ) const {
    return _preisProStd;
}

//void RechnungPos::setRenr( int renr ) {
//    this->_renr = renr;
//}
//
//int RechnungPos::getRenr( ) const {
//    return _renr;
//}

