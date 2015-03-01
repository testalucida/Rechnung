/* 
 * File:   RechnungIO.cpp
 * Author: max
 * 
 * Created on 19. Dezember 2013, 17:29
 */

#include "RechnungIO.h"
#include "UebersichtModel.h"
#include "Rechnung.h"
#include "RechnungTableData.h"
#include "RechnungPos.h"
#include "adresse.h"
#include "password.h"

using namespace my;

RechnungIO *RechnungIO::_pThis = NULL;

RechnungIO &RechnungIO::instance() {
    if( !_pThis ) {
        _pThis = new RechnungIO();
        _pThis->connect();
        atexit( destroy );
    }
    return *_pThis;
}

RechnungIO::RechnungIO( ) { //: _connected( false ) {
}

void RechnungIO::getUebersichtData( UebersichtModel &data )  {
    CharBufferPtr pSql = getUebersichtSelect( data );
    _mysql.select( pSql->get(), data );
}

void RechnungIO::getRechnungData( int renr, RechnungTableData &data )  {
    CharBufferPtr pSql = getRechnungSelect( renr );
    _mysql.select( pSql->get(), data );
}

my::CharBufferPtr RechnungIO::getKundenname( int kdnr ) {
    CharBufferPtr pName( new CharBuffer );
    CharBuffer sql = "select name1, name2 from kunde where kdnr = ";
    sql.addInt( kdnr );
    TableData data;
    _mysql.select( sql.get(), data );
    pName->add( data.getValue( 0, 0 ) );
    pName->add( " " );
    pName->add( data.getValue( 0, 1 ) );
    return pName;
}

void RechnungIO::getAdresse( int kdnr, Adresse &adr ) {
    CharBuffer sql( "select anrede, titel, name1, name2, name3, zusatz, " );
    ///                      0        1      2      3      4       5
    sql.add( "strasse, plz, ort " );
    ///          6      7    8
    sql.add( "from kunde " );
    sql.add( "where kdnr = " );
    sql.addInt( kdnr );
    TableData data;
    _mysql.select( sql.get(), data );
    
    //Anrede
    adr.anrede.add( data.getValue( 0, 0 ) );
    int namIdx = adr.anrede.getLength() > 0 ? 3 : 2;
    //Titel
    adr.name.add( data.getValue( 0, 1 ) );
    if( adr.name.getLength() > 0 ) { //es gibt einen Titel
        adr.name.add( " " );
    }
    //Name1 bzw. Name2 bei nat. Pers.
    adr.name.add( data.getValue( 0, namIdx ) );
    namIdx = ( namIdx == 3 ) ? 2 : 3;
    //Name2 bzw. Name1 bei nat. Pers.
    CharBuffer name2 = data.getValue( 0, namIdx );
    if( name2.getLength() > 0 ) {
        adr.name.add( " " );
        adr.name.add( name2 );
    }
    //Name3
    CharBuffer name3 = data.getValue( 0, 4 );
    if( name3.getLength() > 0 ) {
        adr.name.add( " " );
        adr.name.add( name3 );
    }
    //Zusatz
    adr.zusatz.add( data.getValue( 0, 5 ) );
    //Straße
    adr.str.add( data.getValue( 0, 6 ) );
    //PLZ/Ort
    adr.plzOrt.add( data.getValue( 0, 7 ) );
    adr.plzOrt.add( " " );
    adr.plzOrt.add( data.getValue( 0, 8 ) );
}

float RechnungIO::getPreisProStd( int kdnr ) {
    CharBuffer sql( "select preisprostd from kunde where kdnr = " );
    sql.addInt( kdnr );
    TableData data;
    _mysql.select( sql.get(), data );
    return data.getFloatValue( 0, 0, 0 );
}

void RechnungIO::insertRechnung( Rechnung &rechng ) {
    int renr = getNextRechngNr();   
    //workaround um bug in TableData:
    renr = ( renr == 0 ) ? 1 : renr;
    CharBuffer sql;
    sql.add( "insert into rechnung " );
    sql.add( "(renr, rejahr, kdnr, redatum, resummenetto, reustsatz, gesamtstunden, retext)" );
    sql.add( "values( " );
    sql.addInt( renr );
    sql.add( "," );
    sql.addInt( rechng.getRejahr() );
    sql.add( "," );
    sql.addInt( rechng.getKdnr() );
    sql.add( ",'" );
    sql.add( rechng.getRedatum().ToIsoString().c_str() );
    sql.add( "'," );
    sql.addFloat( rechng.getRechngSummeNetto() );
    sql.add( "," );
    sql.addFloat( 19.0 );
    sql.add( "," );
    sql.addFloat( rechng.getGesamtStunden() );
    sql.add( ",'" ).add( rechng.getText() ).add( "' " );
    sql.add( ") " );
  
    _mysql.exec( sql.get() );
    rechng.setRenr( renr );
}

int RechnungIO::getNextRechngNr() {
    CharBuffer sql;
    sql.add( "select max(renr) + 1 from rechnung " );
    TableData data;
    _mysql.select( sql.get(), data );       
    return data.getIntValue( 0, 0, 1 );    
}

void RechnungIO::updateRechnung( const Rechnung &rechng ) {
    CharBuffer sql;
    sql.add( "update rechnung " );
    sql.add( "set rejahr = " );
    sql.addInt( rechng.getRejahr() );
    sql.add( ", redatum = '" );
    sql.add( rechng.getRedatum().ToIsoString().c_str() );
    sql.add( "', resummenetto = " );
    sql.addFloat( rechng.getRechngSummeNetto() );
    sql.add( ", gesamtstunden = " );
    sql.addFloat( rechng.getGesamtStunden() );
    sql.add( ", retext = '" ).add( rechng.getText() ).add( "' " );
    sql.add( " where renr = " );
    sql.addInt( rechng.getRenr() );
    
    _mysql.exec( sql.get() );
}

void RechnungIO::deleteRechnung( int renr ) {
    CharBuffer sql;
    sql.add( "delete from rechnung where renr = " );
    sql.addInt( renr );
    _mysql.exec( sql.get() );
}

void RechnungIO::connect() {
#ifdef _TEST_
    _mysql.connect( "root", "rechnung_test", password );
#else
    _mysql.connect( "root", "rechnung", password );   
#endif
    //_connected = true;
}

CharBufferPtr RechnungIO::getUebersichtSelect( UebersichtModel &data ) {
    CharBufferPtr pSql( new CharBuffer );
    CharBuffer cols( data.getColumnNames()->get() );
    //wenn eine Spalte kdnr dabei ist, durch kunde.kdnr ersetzen:
    cols.replaceAll( "kdnr", "kunde.kdnr" );
    pSql->add( "select " );
    pSql->add( cols.get() );
    pSql->add( " from kunde " );
    pSql->add( "left outer join rechnung on rechnung.kdnr = kunde.kdnr " );
    //pSql->add( "inner join rechnung on rechnung.kdnr = kunde.kdnr " );
    pSql->add( "order by 1 " );
    return pSql;
}

CharBufferPtr RechnungIO::getRechnungSelect( int renr ) {
    CharBufferPtr pSql( new CharBuffer );
    pSql->add( "select k.name1, k.name2, k.kdnr, k.preisprostd, " );
    pSql->add( "r.renr, r.rejahr, r.redatum, r.resummenetto, r.gesamtstunden, r.retext " );
    pSql->add( " from kunde k " );
    pSql->add( "inner join rechnung r on r.kdnr = k.kdnr " );
    pSql->add( "where r.renr = " );
    pSql->addInt( renr );
    
    return pSql;
}

void RechnungIO::destroy() {
    _pThis->_mysql.disconnect();
    delete _pThis;
}

RechnungIO::~RechnungIO( ) {
}

