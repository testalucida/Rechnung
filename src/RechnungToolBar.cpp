/* 
 * File:   RechnungToolBar.cpp
 * Author: max
 * 
 * Created on 20. Dezember 2013, 13:08
 */

#include "RechnungToolBar.h"
#include "actions.h"
#include "../images/plus_36x36.xpm"
#include "../images/plus_deact_36x36.xpm"
#include "../images/save_36x36.xpm"
#include "../images/save_deact_36x36.xpm"
#include "../images/close_36x36.xpm"
#include "../images/cancel_36x36.xpm"
#include "../images/persons_36x36.xpm"
#include "../images/print_36x36.xpm"
#include "../images/print_deact_36x36.xpm"
#include "../images/summe_36x36.xpm"
#include "UebersichtTree.h"


using namespace flx;

RechnungToolBar::RechnungToolBar( int x, int y, int w, int h ) 
: Flx_ToolBar( x, y, w, h )
{
    _pPlusButton = &addButton( plus_xpm, plus_deact_xpm, 
               "Neue Rechnung für ausgewählten Kunden erfassen", 
                RECHNG_ACTION_NEW, NULL );
    _pPlusButton->deactivate();
    
    _pSaveButton = &addButton( save_xpm, save_deact_xpm,
               "Rechnung speichern", RECHNG_ACTION_SAVE, NULL );
    _pSaveButton->deactivate();
    
    _pCloseButton = &addButton( close_xpm, close_xpm, 
                "Rechnung schließen", RECHNG_ACTION_CLOSE, NULL );
    _pCloseButton->deactivate();
    
    _pDeleteButton = &addButton( cancel_xpm, cancel_xpm,
                "Rechnung löschen", RECHNG_ACTION_DELETE, NULL );
    _pDeleteButton->deactivate();
    
    _pPrintButton = &addButton( print_xpm, print_deact_xpm,
                "Rechnung drucken", RECHNG_ACTION_PRINT, NULL );
    _pPrintButton->deactivate();
    
    _pKdAdminButton = &addButton( persons_xpm, persons_xpm,
               "Kundenverwaltung öffnen", RECHNG_ACTION_KUNDENADMIN, NULL );
    _pSummeButton = &addButton( summe_xpm, summe_xpm,
               "Statistikfunktionen", RECHNG_ACTION_STATISTIK, NULL );
}

void RechnungToolBar::setNewButtonActive( bool active ) {
    if( active )
        _pPlusButton->activate();
    else
        _pPlusButton->deactivate();
}

void RechnungToolBar::setSaveButtonActive( bool active ) {
    if( active )
        _pSaveButton->activate();
    else
        _pSaveButton->deactivate();
}

void RechnungToolBar::setCloseButtonActive( bool active ) {
    if( active )
        _pCloseButton->activate();
    else
        _pCloseButton->deactivate();
}

void RechnungToolBar::setDeleteButtonActive( bool active ) {
    if( active )
        _pDeleteButton->activate();
    else
        _pDeleteButton->deactivate();
}

void RechnungToolBar::setPrintButtonActive( bool active ) {
    if( active )
        _pPrintButton->activate();
    else
        _pPrintButton->deactivate();
}

RechnungToolBar::~RechnungToolBar( ) {
}

