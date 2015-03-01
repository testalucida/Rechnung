/* 
 * File:   UebersichtTree.h
 * Author: max
 *
 * Created on 19. Dezember 2013, 17:07
 */

#ifndef UEBERSICHTTREE_H
#define	UEBERSICHTTREE_H

#include "actions.h"

#include <flx/Flx_Tree.h>

#include <my/Signal.hpp>

//static enum enumRechnungAction {
//      RECHNG_ACTION_SHOW
//    , RECHNG_ACTION_NEW
//    , RECHNG_ACTION_PRINT
//};

struct RechnungAction {
    enumRechnungAction action;
    int renr;
    int kdnr;
};

class Fl_Tree_Item;
class Fl_Pixmap;

namespace flx {
    struct TreeItemAction;
}

class UebersichtTree : public flx::Flx_Tree {
public:
    my::Signal< UebersichtTree, RechnungAction > signalRechnungAction;
public:
    UebersichtTree( int x, int y, int w, int h );
    virtual ~UebersichtTree();
    void setIcons();
    void setRechnungIcon( Fl_Tree_Item * );
    void onTreeAction( flx::Flx_Tree &, flx::TreeItemAction & );
private:
    void setIcons( Fl_Tree_Item *pParent, Fl_Pixmap *pChildIcon );
private:
    Fl_Pixmap *_pKundeIcon;
    Fl_Pixmap *_pJahrIcon;
    Fl_Pixmap *_pRechngIcon;
    Fl_Tree_Item *_pSelectedItem;
};

#endif	/* UEBERSICHTTREE_H */

