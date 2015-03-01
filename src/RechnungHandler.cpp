/* 
 * File:   RechnungHandler.cpp
 * Author: max
 * 
 * Created on 21. Dezember 2013, 19:47
 */

#include "RechnungHandler.h"
#include "DetailTabs.h"
#include "RechnungGroup.h"
#include "RechnungIO.h"
#include "RechnungTableData.h"
#include "Rechnung.h"
#include "RechnungKenndaten.h"
#include "PrintHandler.h"

#include <my/CharBuffer.h>
#include <my/datetime.h>

#include <flx/Flx_Message.h>

#include <FL/Fl.H>

using namespace my;
using namespace flx;
using namespace std;

RechnungHandler::RechnungHandler( DetailTabs &tabs )
: _detailTabs( tabs ) 
{
}

void RechnungHandler::newRechnung( const RechnungKenndaten &kenn ) {
    printf( "newRechnung: kdnr = %d, rejahr = %d, renr = %d\n", 
            kenn.kdnr, kenn.rejahr, kenn.renr );
    Rechnung &rechng = createRechnung( kenn );
    rechng.setFlag( RECHNG_FLAG_NEW );
    rechng.setRedatum( MyDate( true ) );
    rechng.setName( RechnungIO::instance( ).getKundenname( kenn.kdnr )->get( ) );
    createRechnungGroup( rechng );
}

void RechnungHandler::openRechnung( const RechnungKenndaten &kenn ) {
    RechnungGroup *pRechngGrp = isRechnungOpen( kenn );
    if( pRechngGrp == NULL ) {
        RechnungTableData data;
        RechnungIO::instance( ).getRechnungData( kenn.renr, data );
        Rechnung &rechng = createRechnung( kenn );
        provideRechnungDaten( rechng, data );
        createRechnungGroup( rechng );
    } else {
        _detailTabs.value( pRechngGrp );
    }
}

RechnungGroup *RechnungHandler::isRechnungOpen( const RechnungKenndaten &kenn ) {
    for( int i = 0, imax = _detailTabs.getTabCount( ); i < imax; i++ ) {
        RechnungGroup &rechngGrp = _detailTabs.getRechnungGroup( i );
        const Rechnung &rechng = rechngGrp.getRechnung( );
        if( kenn.rejahr == rechng.getRejahr( ) && kenn.renr == rechng.getRenr( ) ) {
            return &rechngGrp;
        }
    }
    return NULL;
}

Rechnung &RechnungHandler::createRechnung( const RechnungKenndaten &kenn ) {
    Rechnung *pRechng = new Rechnung;
    pRechng->setKdnr( kenn.kdnr );
    pRechng->setRenr( kenn.renr );
    pRechng->setRejahr( kenn.rejahr == 0 ?
            getAktuellesRechnungsjahr( ) : kenn.rejahr );
    pRechng->setPreisProStd( RechnungIO::instance( ).getPreisProStd( kenn.kdnr ) );
    pRechng->setText( "Sehr geehrte Damen und Herren, \n\nfür den Monat xx.nnnn erlaube ich mir folgende Leistungen zu berechnen:\n\n" );
    _rechnungen.push_back( pRechng );
    return *pRechng;
}

int RechnungHandler::getAktuellesRechnungsjahr( ) const {
    my::MyDate today( true );
    return today.GetYear( );
}

const Rechnung *RechnungHandler::getActiveRechnung() const {
     RechnungGroup *pRechngGrp = (RechnungGroup*)_detailTabs.value();
     return pRechngGrp ? &(pRechngGrp->getRechnung()) : NULL;
}

RechnungGroup &RechnungHandler::createRechnungGroup( Rechnung &rechng ) {
    CharBuffer lbl;
    lbl.add( rechng.getName( ).get( ) );
    lbl.add( "/" );
    lbl.add( rechng.getRedatum( ).ToIsoString( ).c_str( ) );
//    int x, y, w, h;
//    _detailTabs.client_area( x, y, w, h );
//    printf( "createREchnungGroup: %d, %d, %d, %d\n", 
//            _detailTabs.x(), _detailTabs.y(), _detailTabs.w(), _detailTabs.h() );
//    printf( "createRechnungGroup: clientarea = %d, %d, %d, %d\n", x,y , w, h );
//    RechnungGroup *p = new RechnungGroup( x + 5, y, w - 10, h );
    
    RechnungGroup *p = new RechnungGroup( _detailTabs.x(), _detailTabs.y()+20, 
                                          _detailTabs.w(), _detailTabs.h()-20 );
    p->copy_label( lbl.get( ) );
    p->signalRechnungGroupAction.
            connect< RechnungHandler, &RechnungHandler::onRechnungGroupAction >( this );

    p->setRechnung( rechng );
    _detailTabs.add( p );
    _detailTabs.value( p );
    _detailTabs.redraw( );
    return *p;
}

void RechnungHandler::provideRechnungDaten( Rechnung &rech, const RechnungTableData &data ) 
{
    if( data.getRowCount( ) == 0 ) return;

    //kundennummer, rechnungsnummer und rechnungsjahr in rech sind 
    //bereits versorgt.

    CharBuffer name( data.getValue( 0, RECHNUNG_NAME1 ) );
    name.add( " " );
    name.add( data.getValue( 0, RECHNUNG_NAME2 ) );
    rech.setName( name.get( ) );
    rech.setRedatum( data.getValue( 0, RECHNUNG_REDATUM ) );
    rech.setPreisProStd( data.getFloatValue( 0, RECHNUNG_PREISPROSTD ) );
    rech.setRechngSummeNetto( data.getFloatValue( 0, RECHNUNG_RESUMNETTO ) );
    rech.setGesamtStunden( data.getFloatValue( 0, RECHNUNG_GESAMTSTD ) );
    rech.setText( data.getValue( 0, RECHNUNG_TEXT ) );

//    for( int r = 0, rmax = data.getRowCount( ); r < rmax; r++ ) {
//        RechnungPos &rechngPos = 
//                rech.addPos( data.getIntValue( r, RECHNUNGPOS_POSNR ),
//                data.getValue( r, RECHNUNGPOS_POSTEXT ),
//                data.getFloatValue( r, RECHNUNGPOS_ANZAHLSTUNDEN ),
//                data.getFloatValue( r, RECHNUNGPOS_POSBETRAG ) );
//        rechngPos.setFlag( RECHNG_FLAG_NONE );
//    }
}

Rechnung *RechnungHandler::closeRechnung( ) {
    //wenn es eine aktive RechnungGroup gibt, speichern:
    RechnungGroup *pGrp = (RechnungGroup*) _detailTabs.value( );
    if( !pGrp ) return NULL; //es gibt keine RechnungGroup mehr
    
    //sind Änderungen offen? Wenn ja, fragen, ob speichern:
    //TODO
    
    //Lasche schließen:
    Rechnung &rechng = pGrp->getRechnung();
    removeRechnungGroup( *pGrp );
    return &rechng;
}

void RechnungHandler::deleteRechnung() {
    //aktive RechnungGroup holen:
    RechnungGroup *pGrp = (RechnungGroup*) _detailTabs.value( );
    if( !pGrp ) return; //es gibt keine RechnungGroup mehr
    Rechnung &rechng = pGrp->getRechnung();
    deleteRechnung( rechng );
}

void RechnungHandler::saveRechnung( ) {
    //ggf. gelöschte Rechnungen speichern:
    saveDeletedRechnungen();
    //wenn es eine aktive RechnungGroup gibt, speichern:
    RechnungGroup *pGrp = (RechnungGroup*) _detailTabs.value( );
    if( !pGrp ) return; //es gibt keine RechnungGroup mehr
    
    Rechnung &rechng = pGrp->getRechnung( );
//    if( rechng.getPosCount() == 0 ) {
//        Flx_Message::failed( "Eine Rechnung ohne Positionen kann nicht gespeichert werden." );
//        return;
//    }
    try {
        if( rechng.getRenr( ) == 0 ) {
            //neue Rechnung 
            insertRechnung( rechng );
            signalRechnungInserted.send( this, &rechng );
        } else {
            //update oder delete bestehende Rechnung
            int renr = rechng.getRenr();
            RechnungFlags flags = rechng.getFlags();
            if( ( flags & RECHNG_FLAG_DELETED ) == RECHNG_FLAG_DELETED ) {
                //hier dürfen wir nicht hinkommen!
                throw( "Programmierfehler!" );
                //ganze Rechnung löschen
//                deleteRechnung( rechng );
//                signalRechnungDeleted.send( this, &renr );
            } else {
//                updateRechnungPositionen( rechng ); 
 
//                if( rechng.getPosCount() == 0 ) {
//                    //Löschung der letzten Position führt zur 
//                    //Löschung der ganzen Rechnung
//                    deleteRechnungGroup( *pGrp );  
//                    deleteRechnung( rechng );
//                    signalRechnungDeleted.send( this, &renr );
//                    return;
//                } else {
                    RechnungIO::instance( ).updateRechnung( rechng );
//                }
                signalRechnungSaved.send( this, &rechng );
            }
        }
        rechng.clearFlags();
    } catch( MySqlException ex ) {
        CharBuffer msg( "RechnungHandler::saveRechnung():\n" );
        msg.add( ex.what() );
        Flx_Message::failed( msg.get() );
    }
}

void RechnungHandler::saveDeletedRechnungen( ) {
    vector< Rechnung* >::iterator itr;
    int nDeleted = 0;
    for( itr = _rechnungen.begin(); itr != _rechnungen.end(); itr++ ) {
        Rechnung *pRechng = *itr;
        if( ( pRechng->getFlags() & RECHNG_FLAG_DELETED ) == RECHNG_FLAG_DELETED ) {
            int renr = pRechng->getRenr();
            deleteRechnung( *pRechng );
            nDeleted++;
            saveDeletedRechnungen();
            break;
        }
    }
    if( nDeleted++ ) {
        signalRechnungSaved.send( this, NULL );
    }
}

void RechnungHandler::insertRechnung( Rechnung &rechng ) {
    RechnungIO::instance( ).insertRechnung( rechng );
//    for( int i = 0, imax = rechng.getPosCount( ); i < imax; i++ ) {
//        RechnungPos &pos = rechng.getPos( i );
//        if( pos.getFlag() == RECHNG_FLAG_DELETED ) { 
//            //eine Position, die nie in der DB gespeichert war, soll
//            //aus der Rechnung gelöscht werden
//            rechng.deletePos( pos );
//        } else {
//            RechnungIO::instance( ).insertRechnungPos( rechng.getRenr( ),
//                    rechng.getPos( i ) );
//        }
//    }
}



void RechnungHandler::deleteRechnung( Rechnung &rechng ) {
    int renr = rechng.getRenr();
//    for( int i = 0, imax = rechng.getPosCount(); i < imax; i++ ) {
//        RechnungIO::instance().deleteRechnungPos( renr, i );
//    }
    
    RechnungIO::instance().deleteRechnung( renr );
    
    vector< Rechnung* >::iterator itr;
    for( itr = _rechnungen.begin(); itr != _rechnungen.end(); itr++ ) {
        if( *itr == &rechng ) {
            delete &rechng;
            _rechnungen.erase( itr );
            break;
        }
    }
}

//void RechnungHandler::updateRechnungPositionen( Rechnung &rechng ) {
//    for( int i = 0, imax = rechng.getPosCount( ); i < imax; i++ ) {
//        RechnungPos &pos = rechng.getPos( i );
//        if( pos.getFlag() == RECHNG_FLAG_CHANGED ) {
//            RechnungIO::instance( ).updateRechnungPos( rechng.getRenr( ),
//                    rechng.getPos( i ) );
//        } else if( pos.getFlag() == RECHNG_FLAG_NEW ) {
//            RechnungIO::instance( ).insertRechnungPos( rechng.getRenr( ),
//                        rechng.getPos( i ) );
//        } else if( pos.getFlag() == RECHNG_FLAG_DELETED ) {
//            RechnungIO::instance().deleteRechnungPos( rechng.getRenr(),
//                        rechng.getPos( i ).getPosnr() );
//            rechng.deletePos( rechng.getPos( i ) );
//        } else {
//            ; //nix tun
//        }
//    }
//}

void RechnungHandler::onRechnungGroupAction( RechnungGroup &rechngGrp, RechnungGroupParm &parm ) {
    Rechnung &rechng = rechngGrp.getRechnung( );
//    
    switch( parm.action ) {
//        case RECHGRP_ACTION_DELETE_RECHNG:
//            {
//                int renr = rechng.getRenr();
//                deleteRechnungGroup( rechngGrp );
//                signalRechnungDeleted.send( this, &renr );
//            }
//            break;
        case RECHGRP_ACTION_CHANGE_SUM:
        case RECHGRP_ACTION_CHANGE_DATE:
        case RECHGRP_ACTION_CHANGE_TEXT:
            {
                RechnungFlags flags = rechng.getFlags();
                if( ( flags & RECHNG_FLAG_CHANGED ) != RECHNG_FLAG_CHANGED ) {
                    int newflags = flags | RECHNG_FLAG_CHANGED;
                    rechng.setFlag( (RechnungFlags)newflags );
                    signalRechnungChanged.send( this, &rechng );
                }
            }  
            break;
//        case RECHGRP_ACTION_SAVE:
//            saveRechnung();
//            break;
//        case RECHGRP_ACTION_PRINT:
//            printRechnung( rechng );
//            break;
//        case RECHGRP_ACTION_CLOSE_RECHNG:
//            removeRechnungGroup( rechngGrp );
//            break;
     }
}

//void RechnungHandler::onTabChanged( DetailTabs &, int &newIndex ) {
//    
//}

//RechnungPosGroup &RechnungHandler::addRechnungPosGroup( RechnungGroup &rechngGroup ) {
//    //RechnungGroup *pGrp = (RechnungGroup*)_detailTabs.value();
//    if( rechngGroup.getVertSpace( ) < 100 ) {
//        Flx_Message::failed( "Eine weitere Leistungsposition kann nicht erfasst werden." );
//        throw( "no_more_space_available" );
//    }
//    Rechnung &rechng = rechngGroup.getRechnung( );
//    RechnungPos &pos =
//            rechng.addPos( rechng.getPosCount( ) + 1, "", 0, 0 );
//    return rechngGroup.addNewPosition( pos );
//}

void RechnungHandler::setGesamtSummen( RechnungGroup &rechngGrp ) const {
//    Rechnung &rechng = rechngGrp.getRechnung();
//    RechnungSumDialog dlg( 100, 100 );
//    Fl_Group *pParent = dlg.parent();
//    dlg.parent( NULL );
//    //dlg.setNettoGesamtStd( rechng.getRechngSummeNetto() );
//    dlg.setNettoGesamtPreis( rechng.getRechngSummeNetto() );
//    int rc = dlg.show( true );
//    if( rc == 1 ) {
//        rechngGrp.setSummen( dlg.getGesamtStd(), dlg.getNettoGesamtPreis() );
//        rechng.setGesamtStunden( dlg.getGesamtStd() );
//        rechng.setRechngSummeNetto( dlg.getNettoGesamtPreis() );
//    }
}

//void RechnungHandler::deleteRechnungPosGroup( RechnungGroup &rechngGroup,
//                                              RechnungPosGroup &rechngPosGrp ) 
//{
//    Rechnung &rechng = rechngGroup.getRechnung( );
//    RechnungPos &rechngPos = rechngPosGrp.getRechnungPos();
//    RechnungFlags flags = rechngPos.getFlag();
//    if( ( flags & RECHNG_FLAG_NEW ) == RECHNG_FLAG_NEW ) {
//        //Position noch nicht gespeichert; gleich wegwerfen
//        rechng.deletePos( rechngPos );
//    } else {
//        //Pos. war schon gespeichert; deshalb nur das Delete-Flag setzen
//        rechng.setDeleteFlag( rechngPos );
//    }
//    rechngGroup.deletePosition( rechngPosGrp );
//}

void RechnungHandler::deleteRechnungGroup( RechnungGroup &rechngGroup ) {
    // 1. In der Rechnung das Delete-Flag setzen
    // 2. Die Tab-Seite entfernen.
    Rechnung &rechng = rechngGroup.getRechnung( );
    rechng.setFlag( RECHNG_FLAG_DELETED );
    removeRechnungGroup( rechngGroup );
}

void RechnungHandler::removeRechnungGroup( RechnungGroup &rechngGroup ) {
    for( int i = 0, imax = _detailTabs.getTabCount(); i < imax; i++ ) {
        if( &(_detailTabs.getRechnungGroup( i )) == &rechngGroup ) {
            _detailTabs.remove( rechngGroup );
            _detailTabs.window()->redraw();
            break;
        }
    }
}

void RechnungHandler::printRechnung(  const Rechnung &rechng ) const {
    PrintHandler ph;
    ph.print( rechng, true );
}

RechnungHandler::~RechnungHandler( ) {
    for( vector< Rechnung* >::iterator itr = _rechnungen.begin( );
            itr != _rechnungen.end( ); itr++ ) 
    {
        delete *itr;
    }
}

