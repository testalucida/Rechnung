/* 
 * File:   UebersichtModel.cpp
 * Author: max
 * 
 * Created on 19. Dezember 2013, 18:03
 */

#include "UebersichtModel.h"

using namespace my;

UebersichtModel::UebersichtModel( ) {
}

CharBufferPtr UebersichtModel::getColumnNames() const {
    CharBufferPtr pCols( new CharBuffer );
    for( int c = 0; c < UEBERSICHTMODEL_UNK; c++ ) {
        pCols->add( UebersichtColumnNames[c].get() );
        if( c < UEBERSICHTMODEL_UNK - 1 ) {
            pCols->add( "," );
        }
    }
    return pCols;
}

UebersichtModel::~UebersichtModel( ) {
}

