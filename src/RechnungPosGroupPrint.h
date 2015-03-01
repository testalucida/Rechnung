/* 
 * File:   LeistungGroup.h
 * Author: max
 *
 * Created on 18. Dezember 2013, 15:17
 */

#ifndef LEISTUNGGROUP_H
#define	LEISTUNGGROUP_H

#include <flx/Flx_Group.h>

namespace flx {
    class Flx_MultiLineInput;
    class Flx_FloatInput;
    class Flx_Box;
}

class RechnungPosGroupPrint : public flx::Flx_Group {
public:
    RechnungPosGroupPrint( int x, int y, int w, int h );
    virtual ~RechnungPosGroupPrint();
    void setLeistung( const char *pText );
    void setNettoPreis( float preis, int underlines = 0 );
    void showEuroLabel( bool );
private:
    flx::Flx_MultiLineInput *_pLeistung;
    flx::Flx_Box *_pWaehrung;
    flx::Flx_Box *_pNettoPreisOut; //Rechn.-Preview
};

#endif	/* LEISTUNGGROUP_H */

