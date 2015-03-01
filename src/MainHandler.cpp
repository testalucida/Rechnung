/* 
 * File:   MainHandler.cpp
 * Author: max
 * 
 * Created on 19. Dezember 2013, 17:10
 */

#include "MainHandler.h"
#include "TreeHandler.h"
#include "RechnungKenndaten.h"
#include "RechnungToolBar.h"
#include "RechnungHandler.h"
#include "actions.h"
#include "Rechnung.h"
#include "RechnungGroup.h"
#include "DetailTabs.h"
#include "StatistikHandler.h"
#include "PrintHandler.h"

#include <flx/flx_signalparms.h>

#include <FL/Fl_Window.H>

MainHandler::MainHandler( UebersichtTree &tree, RechnungToolBar &tb, DetailTabs &dv  ) 
: _pToolbar( &tb )
{
    _pToolbar->signalToolButtonSelected.
            connect< MainHandler, &MainHandler::onToolSelected >( this );
    
    _pTreeHandler = new TreeHandler( tree );
    _pTreeHandler->signalKundeSelected.
            connect< MainHandler, &MainHandler::onKundeSelected >( this );
    _pTreeHandler->signalRechngJahrSelected.
            connect< MainHandler, &MainHandler::onRechngJahrSelected >( this );
    _pTreeHandler->signalRechnungSelected.
            connect< MainHandler, &MainHandler::onRechnungSelected >( this );
    _pTreeHandler->signalDeselected.
            connect< MainHandler, &MainHandler::onDeselected >( this );
    
    _pRechngHandler = new RechnungHandler( dv );
    _pRechngHandler->signalRechnungChanged.
            connect< MainHandler, &MainHandler::onRechnungChanged >( this );
    _pRechngHandler->signalRechnungInserted.
        connect< MainHandler, &MainHandler::onRechnungInserted >( this );
    _pRechngHandler->signalRechnungSaved.
        connect< MainHandler, &MainHandler::onRechnungSaved >( this );
    _pRechngHandler->signalRechnungDeleted.
        connect< MainHandler, &MainHandler::onRechnungDeleted >( this );
//    _pRechngHandler->signalRechnungClosed.
//        connect< MainHandler, &MainHandler::onRechnungClosed >( this );
    
    dv.signalTabChanged.connect< MainHandler, &MainHandler::onTabChanged >( this );
}

void MainHandler::init() {
    _pTreeHandler->init();
}

void MainHandler::onToolSelected( flx::Flx_ToolBar &, flx::ToolAction &action ) {
    switch( action.ident )  {
        case RECHNG_ACTION_NEW:
        {
            const RechnungKenndaten *pKenn = _pTreeHandler->getSelectedItemKenndaten();
            if( pKenn ) {
                _pRechngHandler->newRechnung( *pKenn );
            } else {
                _pToolbar->setNewButtonActive( false );
            }
            break;
        }
        case RECHNG_ACTION_SAVE:
            _pRechngHandler->saveRechnung();
            _pToolbar->setSaveButtonActive( false );
            break;
        case RECHNG_ACTION_CLOSE:
        {
            Rechnung *pClosedRechng = _pRechngHandler->closeRechnung();
            syncAfterRechnungClosed( *pClosedRechng );
        }
            break;
        case RECHNG_ACTION_DELETE:
        {
            const Rechnung *pRechng = _pRechngHandler->getActiveRechnung();
            //da nach dem Delete die Rechnung weg ist, machen wir die
            //Synchronisierung vorher:
            const Rechnung &rechng = *pRechng;
            syncAfterRechnungClosed( rechng );
            _pRechngHandler->deleteRechnung();
        }
            break;
        case RECHNG_ACTION_PRINT:
        {
            const Rechnung *pRechng = _pRechngHandler->getActiveRechnung();
            PrintHandler ph;
            ph.print( *pRechng, true );
            break;
        }
        case RECHNG_ACTION_KUNDENADMIN:
            break;
        case RECHNG_ACTION_STATISTIK:
        {
            StatistikHandler statHandler;
            statHandler.showStatistics( _pToolbar->window()->x(), 
                                        _pToolbar->window()->y() );
        }
            break;
        default:
            break;
    }
    
    checkToolbars();
}

void MainHandler::checkToolbars() const {
    if( _pRechngHandler->getActiveRechnung() ) {
        _pToolbar->setCloseButtonActive( true );
        _pToolbar->setDeleteButtonActive( false );
        _pToolbar->setPrintButtonActive( true );
    } else {
        _pToolbar->setCloseButtonActive( false );
        _pToolbar->setDeleteButtonActive( false );
        _pToolbar->setPrintButtonActive( false );
    }
}

void MainHandler::onKundeSelected( TreeHandler &, RechnungKenndaten &kenn ) {
    _pToolbar->setNewButtonActive( true );
}

void MainHandler::onRechngJahrSelected( TreeHandler &, RechnungKenndaten &kenn ) {
    _pToolbar->setNewButtonActive( true );
}

void MainHandler::onRechnungSelected( TreeHandler &, RechnungKenndaten &kenn ) {
    _pToolbar->setNewButtonActive( false );
//    _pToolbar->setPrintButtonActive( true );
    _pRechngHandler->openRechnung( kenn );
    checkToolbars();
}

void MainHandler::onDeselected( TreeHandler &, RechnungKenndaten &kenn ) {
    //_pToolbar->setNewButtonActive( false );
}

void MainHandler::onRechnungChanged( RechnungHandler &, Rechnung &rechng ) {
    //wird auch aufgerufen, wenn eine Rechng.Position gelöscht wird.
    //Wenn aufgrund einer vorherigen Änderung an genau dieser Rechn.pos. 
    //der Save-Button aktiviert wurde, dann kann er jetzt wieder inaktiviert
    //werden. Also prüfen, ob es an der REchnung etwas zu speichern gibt.
    _pToolbar->setSaveButtonActive( rechng.hasUnsavedChanges() );
}

void MainHandler::onRechnungInserted( RechnungHandler &, Rechnung &rechng ) {
    _pToolbar->setSaveButtonActive( false );
    _pTreeHandler->addRechnungItem( rechng.getName().get(), 
            rechng.getKdnr(),
            rechng.getRenr(), 
            rechng.getRejahr(), 
            rechng.getRedatum().ToIsoString().c_str() );
}

void MainHandler::onRechnungSaved( RechnungHandler &, Rechnung & ) {
    _pToolbar->setSaveButtonActive( false );
}

void MainHandler::onRechnungDeleted( RechnungHandler &, int &renr ) {
    if( renr > 0 ) { //0 ist die R. dann, wenn sie neu angelegt, aber noch
        //nicht gespeichert ist.
        _pToolbar->setSaveButtonActive( true );
        _pTreeHandler->removeRechnungItem( renr );
    }
}

void MainHandler::syncAfterRechnungClosed( const Rechnung &closedRechng ) {
    bool active = false;
    const Rechnung *pRechng = _pRechngHandler->getActiveRechnung();
    if( pRechng ) {
        active = pRechng->hasUnsavedChanges();
        _pTreeHandler->closeRechnungItem( closedRechng.getRenr() );
        _pTreeHandler->selectRechnungItem( pRechng->getRenr() );
    } else {
        if( closedRechng.getFlags() != RECHNG_FLAG_NEW ) {
            _pTreeHandler->selectRechnungParent( closedRechng.getRenr() );
        }
    }
    _pToolbar->setSaveButtonActive( active );
}

void MainHandler::onTabChanged( DetailTabs &tabs, int &newIndex ) {
    int renr = tabs.getRechnungGroup( newIndex ).getRechnung().getRenr();
    _pTreeHandler->selectRechnungItem( renr );
}

MainHandler::~MainHandler( ) {
    delete _pTreeHandler;
    delete _pRechngHandler;
}

