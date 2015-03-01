/* 
 * File:   DetailView.h
 * Author: max
 *
 * Created on 16. Dezember 2013, 11:30
 */

#ifndef DETAILVIEW_H
#define	DETAILVIEW_H

#include <flx/Flx_Tabs.h>

#include <my/Signal.hpp>

class RechnungGroup;

class DetailTabs : public Fl_Tabs /*flx::Flx_Tabs*/ {
public:
    my::Signal< DetailTabs, int > signalTabChanged;
public:
    DetailTabs( int x, int y, int w, int h );
    virtual ~DetailTabs();
    int getTabCount() const;
    RechnungGroup &getRechnungGroup( int ) const;
    void dump() const;
    static void staticOnTabChanged( Fl_Widget *, void *pUserdata );
private:
    void dump( const Fl_Group *pW ) const;
};

#endif	/* DETAILVIEW_H */

