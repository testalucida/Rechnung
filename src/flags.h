/* 
 * File:   flags.h
 * Author: max
 *
 * Created on 29. Dezember 2013, 11:03
 */

#ifndef FLAGS_H
#define	FLAGS_H

enum RechnungFlags {
    RECHNG_FLAG_NONE = 0x00,
    RECHNG_FLAG_NEW =  0x01,
    RECHNG_FLAG_CHANGED = 0x02,
    RECHNG_FLAG_DELETED = 0x04
};
   
#endif	/* FLAGS_H */
