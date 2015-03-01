/* 
 * File:   StatistikHandler.cpp
 * Author: max
 * 
 * Created on 22. Februar 2014, 14:03
 */

#include "StatistikHandler.h"
#include "StatisticIO.h"

#include <flx/Flx_Dialog.h>
#include <flx/Flx_Table.h>
#include <flx/Flx_Group.h>
#include <flx/Flx_Choice.h>
#include <flx/flx_signalparms.h>

#include <my/TableData.h>
#include <my/convert.h>

using namespace flx;
using namespace my;

StatistikHandler::StatistikHandler( ) {
}

void StatistikHandler::showStatistics( int x, int y ) {
    TableData rejahre;
    StatisticIO::instance().getRechnungsjahre( rejahre );
    int year = StatisticIO::instance().getCurrentYear();
    Flx_Dialog dlg( x, y, 500, 600, "Statistik" );
    int X, Y, W, H;
    dlg.getClientArea( X, Y, W, H );
    Flx_Group g( X, Y, W, H );
        Flx_Choice choice( X + 110, Y + 5, 70, 23, "Rechnungsjahr: " );
        choice.signalSelected.
          connect< StatistikHandler, &StatistikHandler::onYearChanged >( this );
        for( int r = 0, rmax = rejahre.getRowCount(); r < rmax; r++ ) {
            choice.add( rejahre.getValue( r, 0 ) );
        }
        CharBuffer cb;
        cb.addInt( year );
        choice.value( choice.find_index( cb.get() ) );
        int yy = Y + choice.y() + choice.h() + 10;
        int hh = H - yy;
        Flx_Table tbl( X, yy, W, hh );
    g.end();
    dlg.add( g );
    StatisticIO::instance().getUmsaetze( year, _umsaetze );
    tbl.setTableData( _umsaetze );
//    ActionParm parm;
//    onYearChanged( choice, parm );
    dlg.show( false );
}

void StatistikHandler::onYearChanged( Flx_Choice &choice, ActionParm & ) {
    const char *pYear = choice.text( choice.value() );
    int year = Convert::ToInt( pYear );
    _umsaetze.clear();
    StatisticIO::instance().getUmsaetze( year, _umsaetze );
}

StatistikHandler::~StatistikHandler( ) {
}

