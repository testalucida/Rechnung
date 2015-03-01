/* 
 * File:   RechnungTableData.h
 * Author: max
 *
 * Created on 22. Dezember 2013, 10:40
 */

#ifndef RECHNUNGTABLEDATA_H
#define	RECHNUNGTABLEDATA_H

#include <my/TableData.h>

enum enumRechnungColumnNames {
    RECHNUNG_NAME1,
    RECHNUNG_NAME2,
    RECHNUNG_KDNR,
    RECHNUNG_PREISPROSTD,
    RECHNUNG_RENR,
    RECHNUNG_REJAHR,
    RECHNUNG_REDATUM,
    RECHNUNG_RESUMNETTO,
    RECHNUNG_GESAMTSTD,
    RECHNUNG_TEXT,
    RECHNUNGPOS_ANZAHLSTUNDEN,
    RECHNUNG_UNK
};

class RechnungTableData : public my::TableData {
public:
    RechnungTableData();
    virtual ~RechnungTableData();
private:

};

#endif	/* RECHNUNGTABLEDATA_H */

