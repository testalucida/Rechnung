
#include<FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Tile.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Float_Input.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_XPM_Image.H>
#include <FL/Fl_RGB_Image.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Shared_Image.H>

#include <flx/Flx_Window.h>
#include <flx/Flx_Group.h>
#include <flx/Flx_Button.h>
#include <flx/Flx_FloatInput.h>
#include <flx/Flx_Box.h>
#include <flx/Flx_Table.h>
#include "DetailTabs.h"

#include <my/TableData.h>

//#include "UebersichtGroup.h"
#include "UebersichtTree.h"
#include "PrintView.h"
#include "PrintHandler.h"
#include "PrintablePage.h"
#include "MainHandler.h"
#include "RechnungToolBar.h"
#include "../images/Kendel.xpm"
#include "../images/cancel_36x36.xpm"

#include <flx/Flx_Dialog.h>


using namespace flx;
using namespace my;

class TestListener {
public:
    TestListener( Fl_Group &grp ) : _grp( grp ) {}
    void showPreview( Flx_Button &, ActionParm & ) {
        Flx_Dialog *pDlg = new Flx_Dialog
                ( 100, 100, 800, 700, "Rechnungsverwaltung Kendel Büroservice" );
        int x, y, w, h;
        pDlg->getClientArea( x, y, w, h );
        Fl_Scroll *pScroll = new Fl_Scroll( x, y, w, h );
        FirstPrintablePage *pPage = new FirstPrintablePage( 0, 0 );
        pPage->addLeistung( "TestLeistung 1", 3, 32, 96 );
        pPage->addLeistung( "TestLeistung 2", 3, 32, 96 );
        pPage->addLeistung( "TestLeistung 3", 3, 32, 96 );
        pScroll->end();
      
        pDlg->add( pScroll );

        pDlg->show( true );
      
    }
    
    void onPrint( Flx_Button &, ActionParm & ) {

        Fl_Printer printer;
        printer.start_job( 1 );
        printer.start_page();
        printer.origin( 0, 0 );
        printer.print_widget( &_grp, 0, 0 );
        printer.end_page();
        printer.end_job();

    }
private:
    Fl_Group &_grp;
};



int main__() {
    fl_register_images();
    Flx_Window win( 100, 100, 800, 700, "Rechnungsverwaltung Kendel Büroservice" );
    
    Fl_Group g( 10, 10, 800 - 2*10, 700 - 50 );
    g.box( FL_FLAT_BOX );
    Fl_PNG_Image *pImg = new Fl_PNG_Image( "/home/max/cpp/fltk/Rechnung/images/Kendel.png" );
    //Fl_JPEG_Image *pImg = new Fl_JPEG_Image( "/home/max/cpp/fltk/Rechnung/images/Kendel.jpg" );
    //Fl_XPM_Image *pImg = new Fl_XPM_Image("/home/max/cpp/fltk/Rechnung/images/Kendel.xpm");
    Fl_Box box( 20, 20, 300, 300 );
    box.image( pImg );
    box.box( FL_FLAT_BOX );
    g.end();
    
    Flx_Button btn2( 50, 665, 100, 25, "Click for printing" );
    TestListener li( g );
    btn2.signalSelected.connect< TestListener, &TestListener::onPrint >( &li );
    win.end();
    win.show();
    return Fl::run();
}

int main_() {
    int tbh = 40; //toolbar height
    int uegw = 150; //uebersicht group width
    PrintHandler ph;
    
    Flx_Window win( 100, 100, 800, 700, "Rechnungsverwaltung Kendel Büroservice" );
    PrintView pv( 0, 0, 800, 700 );
//    pv.getPrintablePage().addLeistung( 
//            "Fortwährende Bemühungen\nAuch diesen Monat wieder\n"
//            "Vielen Dank auch\n10 Std. a € 32,--" );
//    pv.getPrintablePage().addLeistung( 
//            "Weitere fruchtlose Bemühungen\n8 Std. a € 32,--" );
//    pv.getPrintablePage().addLeistung( 
//            "Zusammenfassende Bemühungen", 8, 28 );
//    pv.getPrintablePage().addGesamtSumme( 0, 0, 19, 66, 334.21, 400.21 );
//    win.end();
//    
//    pv.signalPrint.connect< PrintHandler, &PrintHandler::onPrint >( &ph );
    
    win.show();
    return Fl::run();
}        
    

int main() {
    int tbh = 40; //toolbar height
    int uegw = 310; //uebersicht group width
    
    Flx_Window win( 100, 100, 900, 700, "Rechnungsverwaltung Kendel Büroservice" );
    RechnungToolBar tb( 0, 0, win.w(), tbh );
    
    Fl_Tile tile( 0, tbh, win.w(), win.h() - tbh );
    
    //UebersichtGroup ueberGrp( 0, tbh, uegw, tile.h() );
    UebersichtTree ueberTree( 0, tbh, uegw, tile.h() );
    
    DetailTabs detailView( ueberTree.x() + ueberTree.w(), 
                         ueberTree.y(), 
                         tile.w() - (ueberTree.x() + ueberTree.w() ),
                         ueberTree.h() );
    
    tile.end();
    win.end();
    
    MainHandler mainHandler( ueberTree, tb, detailView );
    mainHandler.init();
    
    win.show();
    return Fl::run();
}