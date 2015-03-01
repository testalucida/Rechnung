/* 
 * File:   RechnungToolBar.h
 * Author: max
 *
 * Created on 20. Dezember 2013, 13:08
 */

#ifndef RECHNUNGTOOLBAR_H
#define	RECHNUNGTOOLBAR_H

#include <flx/Flx_ToolBar.h>

namespace flx {
    class Flx_ToolButton;
}

class RechnungToolBar : public flx::Flx_ToolBar {
public:
    RechnungToolBar( int x, int y, int w, int h );
    virtual ~RechnungToolBar();
    void setNewButtonActive( bool active );
    void setSaveButtonActive( bool active );
    void setCloseButtonActive( bool active );
    void setDeleteButtonActive( bool active );
    void setPrintButtonActive( bool active );
private:
    flx::Flx_ToolButton *_pPlusButton;
    flx::Flx_ToolButton *_pSaveButton;
    flx::Flx_ToolButton *_pCloseButton;
    flx::Flx_ToolButton *_pDeleteButton;
    flx::Flx_ToolButton *_pKdAdminButton;
    flx::Flx_ToolButton *_pPrintButton;
    flx::Flx_ToolButton *_pSummeButton;
};

#endif	/* RECHNUNGTOOLBAR_H */

