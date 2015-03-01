/* 
 * File:   TreeHandler.h
 * Author: max
 *
 * Created on 19. Dezember 2013, 17:51
 */

#ifndef TREEHANDLER_H
#define	TREEHANDLER_H

#include "RechnungKenndaten.h"

#include <my/Signal.hpp>

class UebersichtTree;
class UebersichtModel;

class Fl_Tree_Item;

namespace flx {
    class Flx_Tree;
    struct TreeItemAction;
}

//namespace my {
//    class CharBuffer;
//}

class TreeHandler {
public:
    my::Signal< TreeHandler, RechnungKenndaten > signalKundeSelected;
    my::Signal< TreeHandler, RechnungKenndaten > signalRechngJahrSelected;
    my::Signal< TreeHandler, RechnungKenndaten > signalRechnungSelected;
    my::Signal< TreeHandler, RechnungKenndaten > signalDeselected;
public:
    TreeHandler( UebersichtTree &tree );
    virtual ~TreeHandler();
    void init();
    void onTreeAction( flx::Flx_Tree &, flx::TreeItemAction & );
    void addRechnungItem( const char *pName,
                        int kdnr,
                        int renr,
                        int rejahr,
                        const char *pRedatum );
    /** liefert die Kenndaten des selektierten Baumeintrags*/
    const RechnungKenndaten *getSelectedItemKenndaten() const;
    void removeRechnungItem( int renr );
    void closeRechnungItem( int renr );
    void selectRechnungItem( int renr );
    void selectRechnungParent( int renr );
private:
    Fl_Tree_Item *addTreeItem( const char *pName,                              
                                int kdnr,
                                int renr = 0,
                                int rejahr = 0,
                                const char *pRedatum = 0 );
    void populateTree();
    Fl_Tree_Item *getTreeItem( int renr ) const;
private:
    UebersichtTree &_tree;
    UebersichtModel &_model;
};

#endif	/* TREEHANDLER_H */

