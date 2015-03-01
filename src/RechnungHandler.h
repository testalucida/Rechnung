/* 
 * File:   RechnungHandler.h
 * Author: max
 *
 * Created on 21. Dezember 2013, 19:47
 */

#ifndef RECHNUNGHANDLER_H
#define	RECHNUNGHANDLER_H

#include <my/Signal.hpp>

#include <vector>

class DetailTabs;
class Rechnung;
class RechnungPos;
class RechnungTableData;
class RechnungGroup;
class RechnungPosGroup;
struct RechnungKenndaten;
struct RechnungGroupParm;


class RechnungHandler {
public:
    my::Signal< RechnungHandler, Rechnung > signalRechnungChanged;
    my::Signal< RechnungHandler, Rechnung > signalRechnungInserted;
    my::Signal< RechnungHandler, Rechnung > signalRechnungSaved;
    my::Signal< RechnungHandler, int > signalRechnungDeleted;
    my::Signal< RechnungHandler, Rechnung > signalRechnungClosed;
public:
    RechnungHandler( DetailTabs & );
    ~RechnungHandler();
    /** erzeugt eine neue Rechnung*/
    void newRechnung( const RechnungKenndaten & );
    /** öffnet eine im Baum gewählte Rechnung*/
    void openRechnung( const RechnungKenndaten & );
    /**speichert die aktive Rechnung*/
    void saveRechnung();
    /** speichert die Löschung von Rechnungen*/
    void saveDeletedRechnungen();
    /** schließt die aktive Rechnung */
    Rechnung *closeRechnung();
    /** reagiert auf Aktionen, die innerhalb einer Rechnung (RechnungGroup)
        ausgelöst werden (Position neu/löschen */
    void onRechnungGroupAction( RechnungGroup &, RechnungGroupParm & );
//    void onTabChanged( DetailTabs &, int & );
    /** löscht die Rechnung auf der aktiven Tab-Seite */
    void deleteRechnung();
    int getAktuellesRechnungsjahr() const;
    /** liefert die aktuelle Rechnung zurück bzw. NULL, wenn keine
        offen ist */
    const Rechnung *getActiveRechnung() const;
private:
    Rechnung &createRechnung( const RechnungKenndaten & );
    RechnungGroup &createRechnungGroup( Rechnung & );
    void provideRechnungDaten( Rechnung &, const RechnungTableData & );
//    RechnungPosGroup &addRechnungPosGroup( RechnungGroup & );
    void setGesamtSummen( RechnungGroup & ) const;
    void insertRechnung( Rechnung & );
    void deleteRechnung( Rechnung & );
//    void updateRechnungPositionen( Rechnung & );
//    /** löscht eine Rechnungsposition und die zugehörige RechnungPosGroup*/
//    void deleteRechnungPosGroup( RechnungGroup &, RechnungPosGroup & );
    /** löscht die Rechnung und die zugehörige RechnungGroup*/
    void deleteRechnungGroup( RechnungGroup & );
    /** löscht eine RechnungGroup ohne die Rechnung zu löschen*/
    void removeRechnungGroup( RechnungGroup & );
    RechnungGroup *isRechnungOpen( const RechnungKenndaten &kenn );
    void printRechnung( const Rechnung & ) const;
private:
    DetailTabs &_detailTabs;
    std::vector< Rechnung *> _rechnungen;
};

#endif	/* RECHNUNGHANDLER_H */

