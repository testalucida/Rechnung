/* 
 * File:   UebersichtGroup.h
 * Author: max
 *
 * Created on 16. Dezember 2013, 11:34
 */

#ifndef UEBERSICHTGROUP_H
#define	UEBERSICHTGROUP_H

#include <FL/Fl_Tile.H>

class Fl_Tree;

namespace flx {
    class Flx_Table;
}

class UebersichtGroup : public Fl_Tile {
public:
    UebersichtGroup( int x, int y, int w, int h );
    virtual ~UebersichtGroup();
private:
    flx::Flx_Table *_pKundenTable;
    Fl_Tree *_pRechnungTree;
};

#endif	/* UEBERSICHTGROUP_H */

