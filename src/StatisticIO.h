/* 
 * File:   StatisticIO.h
 * Author: max
 *
 * Created on 22. Februar 2014, 15:14
 */

#ifndef STATISTICIO_H
#define	STATISTICIO_H

#include "MySql.h"

#include <my/CharBuffer.h>

namespace my {
    class TableData;
}

class StatisticIO {
public:
    static StatisticIO &instance();
    StatisticIO();
    void getUmsaetze( int year, my::TableData & );
    int getCurrentYear();
    void getRechnungsjahre( my::TableData & );
    virtual ~StatisticIO();
private:
    void connect();
    static void destroy();
private:
    MySql _mysql;
    static StatisticIO *_pThis;

};

#endif	/* STATISTICIO_H */

