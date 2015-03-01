/* 
 * File:   RechnungSumDialog.h
 * Author: max
 *
 * Created on 5. Januar 2014, 11:28
 */

#ifndef RECHNUNGSUMDIALOG_H
#define	RECHNUNGSUMDIALOG_H

#include <flx/Flx_Dialog.h>

#include <FL/Fl_Float_Input.H>

namespace flx {
    class Flx_FloatInput;
}

class RechnungSumDialog : public flx::Flx_Dialog {
public:
    RechnungSumDialog( int x, int y );
    ~RechnungSumDialog();
    void setNettoGesamtPreis( float );
    float getNettoGesamtPreis() const;
    void setGesamtStd( float );
    float getGesamtStd() const;
    
private:
     Fl_Float_Input *_pGesamtStd;
     Fl_Float_Input *_pNettoGesamtPreis;
//    flx::Flx_FloatInput *_pGesamtStd;
//    flx::Flx_FloatInput *_pNettoGesamtPreis;
};

#endif	/* RECHNUNGSUMDIALOG_H */

