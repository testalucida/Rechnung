/* 
 * File:   RechnungKenndaten.h
 * Author: max
 *
 * Created on 20. Dezember 2013, 15:07
 */

#ifndef RECHNUNGKENNDATEN_H
#define	RECHNUNGKENNDATEN_H

#include <memory>

struct RechnungKenndaten {
    int renr;
    int kdnr;
    int rejahr;
    RechnungKenndaten *clone() {
        RechnungKenndaten *pClone = new RechnungKenndaten;
        pClone->kdnr = kdnr;
        pClone->rejahr = rejahr;
        pClone->renr = renr;
    }
};

typedef std::shared_ptr< RechnungKenndaten > RechnungKenndatenPtr;

#endif	/* RECHNUNGKENNDATEN_H */

