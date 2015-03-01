/* 
 * File:   Rechnung.h
 * Author: max
 *
 * Created on 21. Dezember 2013, 23:28
 */

#ifndef RECHNUNG_H
#define	RECHNUNG_H

#include "RechnungPos.h"
#include "flags.h"

#include <my/datetime.h>
#include <my/CharBuffer.h>
#include <my/Signal.hpp>

#include <memory>

class Rechnung {
public:
    my::Signal< Rechnung, int > signalRechnungNummerSet;
public:
    Rechnung();
    ~Rechnung();
    void setName( const char * );
    const my::CharBuffer &getName() const;
    void setRedatum(my::MyDate redatum);
    my::MyDate getRedatum() const;
    void setRejahr(int rejahr);
    int getRejahr() const;
    void setKdnr(int kdnr);
    int getKdnr() const;
    void setRenr(int renr);
    int getRenr() const;
    void setPreisProStd( float );
    float getPreisProStd() const;
    void setRechngSummeNetto( float );
    float getRechngSummeNetto() const;
    void setGesamtStunden( float std ) { _gesamtStunden = std; }
    float getGesamtStunden() const { return _gesamtStunden; }
    void setText( const char * );
    const char *getText() const;
//    RechnungPos &addPos( int posNr, const char *pText, float nStd, float betrag );
//    /** löscht eine Position aus der Rechnung.  */
//    void deletePos( RechnungPos & );
//    /** setzt das Löschkennzeichen an einer Position */
//    void setDeleteFlag( RechnungPos & );
    RechnungFlags getFlags() const { return _flags; }
    /** setzt ein Flag oder eine Kombination von Flags im Rechnungskopfsatz.*/
    void setFlag( RechnungFlags );
    /** setzt alle Flags in den Positionen und im Kopfsatz auf
     * RECHNG_FLAG_NONE zurück, egal welches Flag vorher gesetzt war. */
    void clearFlags();
//    int getPosCount() const { return _allRechngPos.size(); }
//    RechnungPos &getPos( int i ) const { return *_allRechngPos[i]; }
    bool hasUnsavedChanges() const;
private:
    my::CharBuffer _name;
    int _renr;
    int _kdnr;
    int _rejahr;
    my::MyDate _redatum;
    my::CharBuffer _text;
//    std::vector< RechnungPos* > _allRechngPos;
    float _preisprostd;
    float _rechngSummeNetto;
    float _gesamtStunden;
    RechnungFlags _flags;
};

//typedef std::shared_ptr< Rechnung > RechnungPtr;

#endif	/* RECHNUNG_H */

