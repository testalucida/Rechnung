/* 
 * File:   PrintView.h
 * Author: max
 *
 * Created on 16. Dezember 2013, 15:10
 */

#ifndef PRINTVIEW_H
#define	PRINTVIEW_H

//#include <FL/Fl_Scroll.H>

#include <flx/Flx_Group.h>
#include <my/Signal.hpp>

class Fl_Scroll;
class PrintablePage;
class FirstPrintablePage;

namespace flx {
    class Flx_Button;
    class Flx_MultiLineOutput;
    struct ActionParm;
}


class PrintView : public flx::Flx_Group {
public:
    my::Signal< PrintView, FirstPrintablePage > signalPrint;
public:
    PrintView( int x, int y, int w, int h );
    virtual ~PrintView();
    void addPrintablePage( PrintablePage & );
    void onPrint( flx::Flx_Button &, flx::ActionParm & );
//    FirstPrintablePage &getPrintablePage() const {
//        return *_pPage;
//    }
private:
    Fl_Scroll *_pPrintScroll;
    //FirstPrintablePage *_pPage;
    flx::Flx_Button *_pBtnPrint;
};

#endif	/* PRINTVIEW_H */

