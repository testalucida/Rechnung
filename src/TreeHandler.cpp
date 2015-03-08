/* 
 * File:   TreeHandler.cpp
 * Author: max
 * 
 * Created on 19. Dezember 2013, 17:51
 */

#include "TreeHandler.h"
#include "RechnungIO.h"
#include "UebersichtTree.h"
#include "UebersichtModel.h"

#include <flx/flx_signalparms.h>

#include <my/CharBuffer.h>

#include <FL/Fl_Tree_Item.H>

using namespace my;
using namespace flx;

TreeHandler::TreeHandler( UebersichtTree &tree ) 
: _tree( tree ) 
, _model( *(new UebersichtModel ) ) 
{
    _tree.signalTreeItem.connect< TreeHandler, &TreeHandler::onTreeAction >( this );
}

void TreeHandler::init() {
    RechnungIO::instance().getUebersichtData( _model );
    populateTree();
}

void TreeHandler::onTreeAction( Flx_Tree &, TreeItemAction &action ) { 
    Fl_Tree_Item *pItem = action.pItem;
    RechnungKenndaten *pKenn = (RechnungKenndaten*)(pItem->user_data());
    switch( action.reason ) {
        case FL_TREE_REASON_SELECTED:
            if( pKenn ) { //root hat keine Kenndaten
                if( pKenn->rejahr == 0 ) {
                    signalKundeSelected.send( this, pKenn );
                } else if( pKenn->renr == 0 ) {
                    signalRechngJahrSelected.send( this, pKenn );
                } else {
                    signalRechnungSelected.send( this, pKenn );
                }
            }
            break;
        case FL_TREE_REASON_DESELECTED:
            signalDeselected.send( this, pKenn );
        default:
            break;
    }
}

void TreeHandler::populateTree() {
    for( int r = 0, rmax = _model.getRowCount(); r < rmax; r++ ) {
        CharBuffer name;
        name.add( _model.getValue( r, UEBERSICHTMODEL_NAME1 ) );
        name.add( " " );
        name.add( _model.getValue( r, UEBERSICHTMODEL_NAME2 ) );
        addTreeItem(
                name.get(),
//            _model.getValue( r, UEBERSICHTMODEL_NAME1 ),
//            _model.getValue( r, UEBERSICHTMODEL_NAME2 ),
            _model.getIntValue( r, UEBERSICHTMODEL_KDNR ),
            _model.getIntValue( r, UEBERSICHTMODEL_RENR ),
            _model.getIntValue( r, UEBERSICHTMODEL_REJAHR ),
            _model.getValue( r, UEBERSICHTMODEL_REDATUM ) );
    }
    _tree.setIcons();
    
    for( Fl_Tree_Item *pItem = _tree.root(); pItem; pItem = pItem->next() ) {
        pItem->close();
    }
    _tree.root()->open();
}

void TreeHandler::addRechnungItem( const char *pName,
                            int kdnr,
                            int renr,
                            int rejahr,
                            const char *pRedatum )
{
    Fl_Tree_Item *pItem = 
            addTreeItem(pName, kdnr, renr, rejahr, pRedatum );
    _tree.setRechnungIcon( pItem );
}

const RechnungKenndaten *TreeHandler::getSelectedItemKenndaten() const {
    //Fl_Tree_Item *pItem = _tree.item_clicked(); 
    Fl_Tree_Item &item = _tree.getSelectedItem(); 
    return &item ? (RechnungKenndaten*)(item.user_data()) : NULL;
}

void TreeHandler::removeRechnungItem( int renr ) {
    Fl_Tree_Item *pItem = getTreeItem( renr );
    RechnungKenndaten *pKenn = (RechnungKenndaten*)pItem->user_data();
    delete pKenn;
    _tree.remove( pItem );
    _tree.redraw();
}

void TreeHandler::closeRechnungItem( int renr ) {
    Fl_Tree_Item *pSelectedItem = &_tree.getSelectedItem();
    if( pSelectedItem ) {
        Fl_Tree_Item *pParent = pSelectedItem->parent();
        if( renr > 0 ) {
            pSelectedItem->select( 0 );            
        } 
        if( pParent && pParent != _tree.root() ) {
            pParent->close();
        }
        _tree.redraw();
    }
}

void TreeHandler::selectRechnungItem( int renr ) {
    _tree.getSelectedItem().select( 0 );
    getTreeItem( renr )->select();
    _tree.redraw();
}

void TreeHandler::selectRechnungParent( int renr ) {
    _tree.getSelectedItem().select( 0 );
    getTreeItem( renr )->parent()->select();
    _tree.redraw();
}

Fl_Tree_Item *TreeHandler::getTreeItem( int renr ) const {
    for( Fl_Tree_Item *pItem = _tree.first(); pItem; pItem = _tree.next( pItem ) ) {
        RechnungKenndaten *pKenn = (RechnungKenndaten*)pItem->user_data();
        if( pKenn && pKenn->renr == renr ) {
            return pItem;
        }
    }   
    throw( "TreeHandler::getTreeItem(): Rechnungsnummer nicht gefunden." );
}

Fl_Tree_Item *TreeHandler::addTreeItem( const char *pName,
                                        int kdnr,
                                        int renr,
                                        int rejahr,
                                        const char *pRedatum )
{
    CharBuffer path;
    path.add( pName );
//    path.add( pName1 );
//    path.add( " " );
//    path.add( pName2 );
    if( rejahr > 0 ) {
        path.add( "/" );
        path.addInt( rejahr );
        path.add( "/" );
        path.add( pRedatum );
    }
    Fl_Tree_Item *pItem = _tree.add( path.get() );
    RechnungKenndaten *pKenn = new RechnungKenndaten;
    pKenn->kdnr = kdnr;
    pKenn->renr = renr;
    pKenn->rejahr = rejahr;
    pItem->user_data( pKenn );
    Fl_Tree_Item *pParent = pItem->parent();
    if( pParent && !pParent->user_data() ) {
        pKenn = pKenn->clone();
        pKenn->renr = 0;
        pParent->user_data( pKenn );
        pParent = pParent->parent();
        if( pParent && !pParent->user_data() ) {
            pKenn = pKenn->clone();
            pKenn->rejahr = 0;
            pParent->user_data( pKenn );
        }
    }
    return pItem;
}

TreeHandler::~TreeHandler( ) {
    for( Fl_Tree_Item *pItem = _tree.first(); pItem; pItem = _tree.next( pItem ) ) {
        RechnungKenndaten *pKenn = (RechnungKenndaten*)pItem->user_data();
        delete pKenn;
    }
    delete &_model;
}

