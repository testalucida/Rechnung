/* 
 * File:   RechnungIO.h
 * Author: max
 *
 * Created on 19. Dezember 2013, 17:29
 */

#ifndef RECHNUNGIO_H
#define	RECHNUNGIO_H

#include "MySql.h"

#include <my/CharBuffer.h>

class UebersichtModel;
class RechnungTableData;
class Rechnung;
class RechnungPos;
class Adresse;

class RechnungIO {
public:
    static RechnungIO &instance();
    virtual ~RechnungIO();
    void getUebersichtData( UebersichtModel & );
    void getRechnungData( int renr, RechnungTableData & );
    my::CharBufferPtr getKundenname( int kdnr );
    void getAdresse( int kdnr, Adresse & );
    float getPreisProStd( int kdnr );
    void insertRechnung( Rechnung &rechng );
    void updateRechnung( const Rechnung &rechng );
    void deleteRechnung( int renr );
//    void insertRechnungPos( int renr, const RechnungPos &pos );
//    void updateRechnungPos( int renr, const RechnungPos & pos );
//    void deleteRechnungPos( int renr, int posnr );
private:
    RechnungIO();
    void connect();
    int getNextRechngNr();
    my::CharBufferPtr getUebersichtSelect( UebersichtModel & ) ;
    my::CharBufferPtr getRechnungSelect( int renr );
    static void destroy();
private:
    MySql _mysql;
    //bool _connected;
    static RechnungIO *_pThis;
};

#endif	/* RECHNUNGIO_H */

