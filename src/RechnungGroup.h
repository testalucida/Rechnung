/* 
 * File:   RechnungGroup.h
 * Author: max
 *
 * Created on 21. Dezember 2013, 12:56
 */

#ifndef RECHNUNGGROUP_H
#define	RECHNUNGGROUP_H

//#include <flx/Flx_Group.h>
#include <FL/Fl_Group.H>

#include <my/Signal.hpp>

#include <vector>

class RechnungPosGroup;
class Rechnung;


class Fl_Pixmap;
class Fl_Scroll;
class Fl_Text_Editor;

namespace flx {
    class Flx_Box;
    class Flx_DateChooser;
    class Flx_Button;
    class Flx_FloatInput;
    class Flx_NumericInput;
    struct ActionParm;
}

namespace my {
    class MyDate;
}

enum RechnungGroupAction {
//    RECHGRP_ACTION_NEW_POS,
//    RECHGRP_ACTION_DELETE_RECHNG,
//    RECHGRP_ACTION_DELETE_POS,
//    RECHGRP_ACTION_ADD_SUM,
//    RECHGRP_ACTION_CHANGE_POS,
    RECHGRP_ACTION_CHANGE_SUM,
    RECHGRP_ACTION_CHANGE_DATE,
    RECHGRP_ACTION_CHANGE_TEXT,
//    RECHGRP_ACTION_SAVE,
//    RECHGRP_ACTION_PRINT,
//    RECHGRP_ACTION_CLOSE_RECHNG
};
struct RechnungGroupParm {
    RechnungGroupAction action;
};

/**
 * RechnungGroup enthält einen "Header", der die Rechnungsdaten anzeigt,
 * die nicht leistungsbezogen sind: Kundennummer, Rechn.nummer, 
 * Rechn.jahr.
 * Darunter sind soviele RechnungPosGrp-Instanzen, wie die Rechnung
 * Rechnungspositionen hat.
 */
class RechnungGroup : public Fl_Group { //flx::Flx_Group {
public:
    my::Signal< RechnungGroup, RechnungGroupParm > signalRechnungGroupAction;
public:
    RechnungGroup( int x, int y, int w, int h, const char *pLabel = 0 );
    ~RechnungGroup();
    void setRechnung( Rechnung & );
//    RechnungPosGroup &addNewPosition( RechnungPos & );
//    void deletePosition( RechnungPosGroup & );
    Rechnung &getRechnung();
    const Rechnung &getRechnung() const { return *_pRechng; }
    /** setzen von Gesamtstunden und Rechnungssumme */
    void setSummen( float gesamtstunden, float resumme );
    void getSummen( float &gesamtstunden, float &resumme ) const;
//    void onNewPos( flx::Flx_Button &, flx::ActionParm& );
    void onDeleteRechnung( flx::Flx_Button &, flx::ActionParm& );
//    void onDeleteRechnungPosGrp( RechnungPosGroup &, flx::ActionParm & );
    /** wird aufgerufen, wenn der Button "Summen eingeben" gedrückt wird*/
    void onAddSum( flx::Flx_Button &, flx::ActionParm& );
    void onSave( flx::Flx_Button &, flx::ActionParm& );
    void onPrint( flx::Flx_Button &, flx::ActionParm& );
//    void onRechnungPosChanged( RechnungPosGroup &, RechnungPosAttr & );
//    void onFocusChanged( RechnungPosGroup &, bool & );
    void onRechnungNummerSet( Rechnung &, int & );
    void onSummeChanged( flx::Flx_NumericInput &, flx::ActionParm & );
    void onRedatumChanged( flx::Flx_DateChooser &, my::MyDate & );
    //void onCloseRechnung( flx::Flx_Button &, flx::ActionParm& );
    int getVertSpace() const;
private:
    void setKopfdaten();
    void setPositionen();
    void setRechnungsnummer();
//    RechnungPosGroup &createRechnungPosGroup( int y, RechnungPos & );
//    RechnungPosGroup *getActiveRechnungPosGroup() const;
    /** Summe Stunden und Summe Preis aller Pos. neu berechnen*/
    void computeSummen();
    static void staticOnTextChanged( Fl_Widget *, void * );
    void onTextChanged( );
private:
    flx::Flx_Box *_pRenr;
    flx::Flx_Box *_pKundeName;
    flx::Flx_DateChooser *_pRedatum;
//    flx::Flx_Button *_pNewPartBtn;
//    flx::Flx_Button *_pDeleteBtn;
//    flx::Flx_Button *_pCloseBtn;
    flx::Flx_Button *_pSumBtn;
//    flx::Flx_Button *_pSaveBtn;
//    flx::Flx_Button *_pPrintBtn;
    Fl_Group *_pSummeGrp;
//    flx::Flx_FloatInput *_pSummeStd;
    flx::Flx_FloatInput *_pSummeNet;
    Fl_Pixmap *_pNewIcon;
    Fl_Pixmap *_pDeleteIcon;
    Fl_Pixmap *_pCloseIcon;
    Fl_Pixmap *_pSumIcon;
    Fl_Pixmap *_pSaveIcon;
    Fl_Pixmap *_pPrintIcon;
    Fl_Group *_pDetails; //hier sind alle RechnungPosGroup-Instanzen drin
    Fl_Text_Editor *_pEdi;
    Rechnung *_pRechng;
//    RechnungPosGroup *_pFocusedGroup;
//    RechnungPosGroup *_pFocusLostGroup;
};

#endif	/* RECHNUNGGROUP_H */

