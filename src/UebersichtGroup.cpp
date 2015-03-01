/* 
 * File:   UebersichtGroup.cpp
 * Author: max
 * 
 * Created on 16. Dezember 2013, 11:34
 */

#include "UebersichtGroup.h"

#include <FL/Fl_Browser.H>
#include <FL/Fl_Tree.H>

#include <flx/Flx_Table.h>

using namespace flx;

UebersichtGroup::UebersichtGroup(  int x, int y, int w, int h ) 
: Fl_Tile( x, y, w, h )
{
    begin();
    
    _pKundenTable = new Flx_Table( x, y, w, h/2 );

    
    int Y = _pKundenTable->y() + _pKundenTable->h();
    int H = h - _pKundenTable->h();
    _pRechnungTree = new Fl_Tree( x, Y, w, H );
    _pRechnungTree->end();
    
    end();
}

UebersichtGroup::~UebersichtGroup( ) {
}

