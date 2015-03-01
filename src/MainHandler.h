/* 
 * File:   MainHandler.h
 * Author: max
 *
 * Created on 19. Dezember 2013, 17:10
 */

#ifndef MAINHANDLER_H
#define	MAINHANDLER_H

class UebersichtTree;
class TreeHandler;
class Rechnung;
struct RechnungKenndaten;
class RechnungToolBar;
class DetailTabs;
class RechnungHandler;

namespace flx {
    class Flx_ToolBar;
    struct ToolAction;
}

class MainHandler {
public:
    MainHandler( UebersichtTree &tree, RechnungToolBar &, DetailTabs & );
    //make the handlers query the database
    void init();
    /** Callback für die Toolbar-Buttons */
    void onToolSelected( flx::Flx_ToolBar &, flx::ToolAction & );
    void onKundeSelected( TreeHandler &, RechnungKenndaten & );
    void onRechngJahrSelected( TreeHandler &, RechnungKenndaten & );
    void onRechnungSelected( TreeHandler &, RechnungKenndaten & );
    void onDeselected( TreeHandler &, RechnungKenndaten & );
    void onRechnungChanged( RechnungHandler &, Rechnung & );
    void onRechnungInserted( RechnungHandler &, Rechnung & );
    void onRechnungSaved( RechnungHandler &, Rechnung & );
    void onRechnungDeleted( RechnungHandler &, int & );
    void syncAfterRechnungClosed( const Rechnung & );
    void onTabChanged( DetailTabs &, int & );
    virtual ~MainHandler();
private:
    void checkToolbars() const;
private:
    RechnungToolBar *_pToolbar;
    //DetailTabs *_pDetailView;
    TreeHandler *_pTreeHandler;
    RechnungHandler *_pRechngHandler;
};

#endif	/* MAINHANDLER_H */

