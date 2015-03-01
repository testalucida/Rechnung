/* 
 * File:   DetailView.cpp
 * Author: max
 * 
 * Created on 16. Dezember 2013, 11:30
 */

#include "DetailTabs.h"
#include "RechnungGroup.h"
#include "Rechnung.h"
#include <FL/fl_draw.H>
#include <typeinfo>

using namespace flx;


DetailTabs::DetailTabs( int x, int y, int w, int h ) 
: Fl_Tabs( x, y, w, h )
{
    labelfont( fl_font() );
    labelsize( fl_size() );
    //box( FL_FLAT_BOX );
    color( FL_WHITE );
    
    begin();
    
    end();
    callback( staticOnTabChanged, this );
}

int DetailTabs::getTabCount() const {
    int n = 0;
    for( int i = 0, imax = children(); i < imax; i++ ) {
        Fl_Widget *pW = child( i );
        if( typeid( *pW ).name() == typeid( RechnungGroup ).name() ) {
            n++;
        }
    }
    return n;
}

RechnungGroup &DetailTabs::getRechnungGroup( int i ) const {
    for( int k = 0, kmax = children(); k < kmax; k++ ) {
        Fl_Widget *pW = child( k );
        if( typeid( *pW ).name() == typeid( RechnungGroup ).name() ) {
            if( k == i ) {
                return (RechnungGroup&)(*pW);
            }
        }
    }
    throw( "RechnungGroup nicht gefunden" );
}

void DetailTabs::dump() const {
    dump( this );
}

void DetailTabs::dump( const Fl_Group *pW ) const {
    const char *pName = typeid( *pW ).name();
    fprintf( stderr, "---------Children of %s (Address %p)----------\n", 
             pName, pW );
    for( int k = 0, kmax = pW->children(); k < kmax; k++ ) {
        Fl_Widget *pChild = pW->child( k );
        fprintf( stderr, "Child %d, class = %s, address = %p\n", 
                 k, typeid( *pChild ).name(), pChild );
        if( typeid( *pChild ).name() == typeid( RechnungGroup ).name() )
        {
            dump( (Fl_Group*)pChild );
        }
    }
    fprintf( stderr, "-------------------------------------------\n");
}

void DetailTabs::staticOnTabChanged( Fl_Widget *, void *pUserdata ) {
    DetailTabs *pThis = (DetailTabs*)pUserdata;
    Fl_Widget *pActive = pThis->value();
    int idx;
    if( pActive ) {
        idx = pThis->value( pActive );
    } else {
        idx = -1;
    }
    pThis->signalTabChanged.send( pThis, &idx );
}

DetailTabs::~DetailTabs( ) {
}

