/* 
 * File:   StatisticIO.cpp
 * Author: max
 * 
 * Created on 22. Februar 2014, 15:14
 */

#include "StatisticIO.h"
#include "password.h"

#include <my/TableData.h>

using namespace my;

StatisticIO *StatisticIO::_pThis = NULL;

StatisticIO &StatisticIO::instance() {
    if( !_pThis ) {
        _pThis = new StatisticIO();
        _pThis->connect();
        atexit( destroy );
    }
    return *_pThis;
}

StatisticIO::StatisticIO( ) {
}

void StatisticIO::getUmsaetze( int year, my::TableData &data ) {
    CharBuffer sql;
    sql.add( "SELECT k.kdnr, concat( k.name1, ' ', k.name2) as kunde, " );
    sql.add( "coalesce(resummenetto, 0) as summe " );
    sql.add( "FROM kunde k " );
    sql.add( "left outer join rechnung r on r.kdnr = k.kdnr and rejahr = " );
    sql.addInt( year );
    sql.add( " union " );
    sql.add( "select 0, \"Gesamt\", sum(resummenetto) as summe from rechnung" );
    _mysql.select( sql.get(), data );
}

int StatisticIO::getCurrentYear() {
    CharBuffer sql( "select year( curdate() ) " );
    TableData data;
    _mysql.select( sql.get(), data );
    return data.getIntValue( 0, 0 );
}

void StatisticIO::getRechnungsjahre( my::TableData &data ) {
    CharBuffer sql( "select distinct rejahr from rechnung " );
    _mysql.select( sql.get(), data );
}

void StatisticIO::connect() {
#ifdef _TEST_
    _mysql.connect( "root", "rechnung_test", password );
#else
    _mysql.connect( "root", "rechnung", password );   
#endif
    //_connected = true;
}

void StatisticIO::destroy() {
    _pThis->_mysql.disconnect();
    delete _pThis;
}

StatisticIO::~StatisticIO( ) {
}