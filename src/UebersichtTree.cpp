/* 
 * File:   UebersichtTree.cpp
 * Author: max
 * 
 * Created on 19. Dezember 2013, 17:07
 */

#include "UebersichtTree.h"
#include "../images/person_18x18.xpm"
#include "../images/folder_18x18.xpm"
#include "../images/editDoc_18x18.xpm"

#include <flx/flx_signalparms.h>

#include <FL/Fl_Pixmap.H>
#include <FL/Fl_Tree_Item.H>

UebersichtTree::UebersichtTree( int x, int y, int w, int h ) 
: Flx_Tree(x,y,w,h) 
, _pSelectedItem( NULL )
{
    int lblsize = 11;
    item_labelsize( lblsize );
    labelsize( lblsize );
    root()->labelsize( lblsize+1 );
    root_label( "Rechnungsverwaltung KENDEL Büroservice" );
    visible_focus( 0 );
    linespacing( 6 );
    selectmode( Fl_Tree_Select::FL_TREE_SELECT_SINGLE );
    signalTreeItem.connect< UebersichtTree, &UebersichtTree::onTreeAction >( this );
    
    _pKundeIcon = new Fl_Pixmap( person_xpm );
    _pJahrIcon = new Fl_Pixmap( folder_xpm );
    _pRechngIcon = new Fl_Pixmap( editDoc_xpm );
}


void UebersichtTree::onTreeAction( flx::Flx_Tree &, flx::TreeItemAction &action ) { 
    if( action.reason ==  (int) FL_TREE_REASON_SELECTED ) {
        _pSelectedItem = action.pItem;
    }    
}

void UebersichtTree::setIcons() {
    setIcons( root(), _pKundeIcon );
    for( int i = 0, imax = root()->children(); i < imax; i++ ) {
        setIcons( root()->child( i ), _pJahrIcon );
        for( int k = 0, kmax = root()->child( i )->children(); k < kmax; k++ ) {
            setIcons( root()->child( i )->child( k ), _pRechngIcon );
        }
    }
}

void UebersichtTree::setIcons( Fl_Tree_Item *pParent, Fl_Pixmap *pChildIcon ) {
    for( int i = 0, imax = pParent->children(); i < imax; i++ ) {
        pParent->child( i )->usericon( pChildIcon );
    }
}

void UebersichtTree::setRechnungIcon( Fl_Tree_Item *pItem ) {
    pItem->usericon( _pRechngIcon );
}

UebersichtTree::~UebersichtTree( ) {
    delete _pKundeIcon;
    delete _pJahrIcon;
    delete _pRechngIcon;
}

