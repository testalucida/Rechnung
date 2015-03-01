/* 
 * File:   RechnungPos.h
 * Author: max
 *
 * Created on 21. Dezember 2013, 23:29
 */

#ifndef RECHNUNGPOS_H
#define	RECHNUNGPOS_H

#include "flags.h"

#include <my/CharBuffer.h>

class RechnungPos {
public:
    RechnungPos();
    ~RechnungPos();
    void setPosBetrag(float posBetrag);
    float getPosBetrag() const;
    void setAnzahlStunden(float anzahlStunden);
    float getAnzahlStunden() const;
    void setPosnr(int posnr);
    int getPosnr() const;
    const my::CharBuffer &getPosText() const;
    void setPosText( const char * );
    void setPreisProStd( float preis );
    float getPreisProStd() const;
    void setFlag( RechnungFlags flags ) { _flags = flags;}
    RechnungFlags getFlag() const { return _flags; }
//    void setRenr(int _renr);
//    int getRenr() const;
private:
//    int _renr;
    int _posnr;
    my::CharBuffer _text;
    float _anzahlStunden;
    float _posBetrag; //netto
    float _preisProStd;
    RechnungFlags _flags; //delete-/change-info
};

#endif	/* RECHNUNGPOS_H */

