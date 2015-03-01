/* 
 * File:   Rechnung.cpp
 * Author: max
 * 
 * Created on 21. Dezember 2013, 23:28
 */

#include <vector>

#include "Rechnung.h"

using namespace my;
using namespace std;

Rechnung::Rechnung( ) 
: _renr(0)
, _kdnr( 0 )
, _rejahr( 0 )
, _preisprostd( 0 )
, _rechngSummeNetto( 0 )
, _gesamtStunden( 0 )
, _flags( RECHNG_FLAG_NONE )
{    
}

const CharBuffer &Rechnung::getName() const {
    return _name;
}

void Rechnung::setName( const char *pName ) {
    _name = pName;
}

void Rechnung::setRedatum( my::MyDate redatum ) {
    this->_redatum = redatum;
}

my::MyDate Rechnung::getRedatum( ) const {
    return _redatum;
}

void Rechnung::setRejahr( int rejahr ) {
    this->_rejahr = rejahr;
}

int Rechnung::getRejahr( ) const {
    return _rejahr;
}

void Rechnung::setKdnr( int kdnr ) {
    this->_kdnr = kdnr;
}

int Rechnung::getKdnr( ) const {
    return _kdnr;
}

void Rechnung::setRenr( int renr ) {
    this->_renr = renr;
    signalRechnungNummerSet.send( this, &renr );
}

int Rechnung::getRenr( ) const {
    return _renr;
}

void Rechnung::setPreisProStd( float preis ) {
    _preisprostd = preis;
}

float Rechnung::getPreisProStd() const {
    return _preisprostd;
}

float Rechnung::getRechngSummeNetto() const {
    return _rechngSummeNetto;
}

void Rechnung::setRechngSummeNetto( float sumNet ) {
    _rechngSummeNetto = sumNet;
}

void Rechnung::setText( const char *pTxt ) {
    _text.clear();
    _text.add( pTxt );
}

const char *Rechnung::getText() const {
    return _text.get();
}


void Rechnung::setFlag( RechnungFlags flags ) {
    _flags = flags;
    if( flags == RECHNG_FLAG_DELETED ) {
        //wir vererben es *nicht* auf die Positionen, da dann im Undo-Fall
        //die Flags der Positionen nicht wieder hergestellt werden könnten.
    }
}

void Rechnung::clearFlags() {
    _flags = RECHNG_FLAG_NONE;
}

bool Rechnung::hasUnsavedChanges() const {
    if( _flags != RECHNG_FLAG_NONE ) {
        //irgendein Änderungsflag ist gesetzt; aber NEW und keine Position
        //gilt nicht:
//        if( ( _flags & RECHNG_FLAG_NEW ) == RECHNG_FLAG_NEW && getPosCount() == 0 ) {
//            return false;
//        }
        return true;
    }
    //prüfen, ob eine Position geändert wurde/neu ist/gelöscht werden soll:
//    for( int i = 0, imax = getPosCount(); i < imax; i++ ) {
//        RechnungPos &pos = getPos( i );
//        if( pos.getFlag() != RECHNG_FLAG_NONE ) {
//            return true;
//        }
//    }
    return false;
}

Rechnung::~Rechnung( ) {
//    vector< RechnungPos* >::iterator itr = _allRechngPos.begin();
//    for( ; itr != _allRechngPos.end(); itr++ ) {
//        delete *itr;
//    }
}
