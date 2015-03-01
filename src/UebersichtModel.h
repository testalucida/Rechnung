/* 
 * File:   UebersichtModel.h
 * Author: max
 *
 * Created on 19. Dezember 2013, 18:03
 */

#ifndef UEBERSICHTMODEL_H
#define	UEBERSICHTMODEL_H

#include <my/TableData.h>
#include <my/CharBuffer.h>

static const my::CharBuffer UebersichtColumnNames[] = {
    "name1", "name2", "kdnr"
    , "rejahr", "redatum", "renr", ""
};

enum enumUebersichtColumnNames {
    UEBERSICHTMODEL_NAME1 //pos 1 wg. Sortierung
    , UEBERSICHTMODEL_NAME2
    , UEBERSICHTMODEL_KDNR
    , UEBERSICHTMODEL_REJAHR
    , UEBERSICHTMODEL_REDATUM
    , UEBERSICHTMODEL_RENR
    , UEBERSICHTMODEL_UNK
};

class UebersichtModel : public my::TableData {
public:
    UebersichtModel();
    my::CharBufferPtr getColumnNames() const;
    virtual ~UebersichtModel();
private:
  
};

#endif	/* UEBERSICHTMODEL_H */

