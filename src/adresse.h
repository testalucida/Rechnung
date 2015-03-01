/* 
 * File:   adresse.h
 * Author: max
 *
 * Created on 26. Januar 2014, 16:12
 */

#ifndef ADRESSE_H
#define	ADRESSE_H

#include <my/CharBuffer.h>

class Adresse {
public:
    my::CharBuffer anrede;
    my::CharBuffer name;
    my::CharBuffer zusatz;
    my::CharBuffer str;
    my::CharBuffer plzOrt;
    const char *toString() const {
        _adr.clear();
        _adr.add( anrede );
        if( _adr.getLength() > 0 ) {
            _adr.add( "\n" );
        }
        _adr.add( name );
        _adr.add( "\n" );
        if( zusatz.getLength() > 0 ) {
            _adr.add( zusatz );
            _adr.add( "\n" );
        }
        _adr.add( str );
        _adr.add( "\n" );
        _adr.add( plzOrt );
        return _adr.get();
    }
private:
    mutable my::CharBuffer _adr; //für die toString-Ausgabe
};

#endif	/* ADRESSE_H */

