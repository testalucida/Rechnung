/* 
 * File:   PrintHandler.h
 * Author: max
 *
 * Created on 17. Dezember 2013, 20:05
 */

#ifndef PRINTHANDLER_H
#define	PRINTHANDLER_H

#include <FL/Fl_Printer.H>

#include <vector>

class PrintView;
class PrintablePage;
class FirstPrintablePage;
class Rechnung;

class PrintHandler {
public:
    PrintHandler();
    virtual ~PrintHandler();
    /////nur TEST////
    void onPrint( PrintView &, FirstPrintablePage & );
    void print( const Rechnung &, bool preview = true );
private:
    bool showPreview() const;
    void stopPrinter();
    /** erzeugt soviele PrintablePage-Objekte wie notwendig
        (ist abhängig von der ANzahl der Rechnungspositionen)*/
    void createPrintablePages( const Rechnung & );
private:
    Fl_Printer _printer;
    std::vector< PrintablePage* > _pages;
};

#endif	/* PRINTHANDLER_H */

