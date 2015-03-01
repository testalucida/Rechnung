/* 
 * File:   PrintablePage.h
 * Author: max
 *
 * Created on 16. Dezember 2013, 15:21
 */

#ifndef PRINTABLEPAGE_H
#define	PRINTABLEPAGE_H

#include <flx/Flx_Group.h>

#include <vector>

class RechnungPosGroupPrint;

class Fl_PNG_Image;
class Fl_Box;

namespace flx {
    class Flx_Output;
    class Flx_MultiLineOutput;
    class Flx_Box;
}

///////////////////////////////////////////////////
///////////////////////////////////////////////////
/** Basisklasse für FirstPrintablePage und FollowingPrintablePage */
class PrintablePage : public flx::Flx_Group {
public:
    virtual ~PrintablePage();
    /** fügt eine Leistungsposition hinzu.
     Gibt true zurück, wenn die Position auf dieser
     Seite untergebracht werden konnte, sonst false. */
    bool addLeistung( const char *pText, 
                  float nStunden = 0.0,
                  float nettoPreisProStd = 0.0,
                  float nettoPreis = 0.0,
                  int nUnderlinesNettoPreis = 0 );
    void addGesamtSumme( float nStunden, 
                         float nettoPreisProStd,
                         float ustProz, float ust, 
                         float nettoGesamt, float bruttoGesamt );
    virtual int getMaxLeistungen() const = 0;
protected:
    PrintablePage( int x, int y );
    virtual int getVerticalSpace() const = 0;
    virtual int getNextY() const = 0;
    int getHeightNeeded( const char *pText ) const;
    int getFooterY() const { return _footerY; }
private:
    void createFooter();
    void createFooterAnschrift();
    void createFooterTkv();
    void createFooterMail();
    void createFooterKonto();
    void createFooterStNr();
protected:
    std::vector< RechnungPosGroupPrint* > _leistungen;
    int _leftMargin;
    int _footerY;
    int _distV; //Vertikaler Abstand zwischen den Leist.pos.
    int _summenblockH; //Höhe des abschließenden Summenblocks (3 Zeilen)
private:
    int _bottomMargin;
    int _footerH;
    flx::Flx_MultiLineOutput *_pFooterAnschrift;
    flx::Flx_MultiLineOutput *_pFooterTkv;
    flx::Flx_MultiLineOutput *_pFooterMail;
    flx::Flx_MultiLineOutput *_pFooterKonto;
    flx::Flx_MultiLineOutput *_pFooterStNr;
};

///////////////////////////////////////////////////
///////////////////////////////////////////////////

class FirstPrintablePage : public PrintablePage {
public:
    FirstPrintablePage( int x, int y );
    virtual ~FirstPrintablePage();
    /** setzt die Adresse des Kunden, an den die
     Rechnung geschickt werden soll. Zeilenumbrüche
     in pAdresse sind durch "\n" gekennzeichnet.*/
    void setAdresse( const char *pAdresse );
    /** setzt Datum, Rechnungsjahr und Rechnungsnummer.
        Wird in eine 2-zeilige Ausgabe umgearbeitet */
    void setDatumAndRenr( const char *pDatum, int rejahr, int renr );
    virtual int getMaxLeistungen() const { return 5; }
protected:
    int getVerticalSpace() const;
private:
    void createLogo( int x, int y );
    void createAbsender( int x, int y );
    void createAdresse();
    void createDatumReNr();
    void createMeineBemuehungen();
    void createEinschraenkung();
    int getNextY() const;
private:
    Fl_Box *_pLogoBox;
    Fl_PNG_Image *_pLogo;
    flx::Flx_Output *_pAbsender;
    flx::Flx_MultiLineOutput *_pAdresse;
    //flx::Flx_MultiLineOutput *_pDatum_ReNr;
    flx::Flx_Box *_pDatum_ReNr;
    flx::Flx_MultiLineOutput *_pMeineBemuehungen;
    flx::Flx_MultiLineOutput *_pEinschraenkung;
};  

#endif	/* PRINTABLEPAGE_H */

