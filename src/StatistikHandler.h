/* 
 * File:   StatistikHandler.h
 * Author: max
 *
 * Created on 22. Februar 2014, 14:03
 */

#ifndef STATISTIKHANDLER_H
#define	STATISTIKHANDLER_H

#include <my/TableData.h>

namespace flx {
    class Flx_Choice;
    struct ActionParm;
}

class StatistikHandler {
public:
    StatistikHandler();
    void showStatistics( int x, int y ) ;
    void onYearChanged( flx::Flx_Choice &, flx::ActionParm & );
    virtual ~StatistikHandler();
private:
    my::TableData _umsaetze;
};

#endif	/* STATISTIKHANDLER_H */

