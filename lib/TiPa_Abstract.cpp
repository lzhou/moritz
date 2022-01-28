/*!

 @file
 @brief definitions of an abstract parser-class as template
        for tiny parser classes

 Copyright (C) 2015-2017 by Eckard Klotz.

 Permission to use, copy, modify, and distribute this software and its
 documentation under the terms of the GNU General Public License is hereby
 granted. No representations are made about the suitability of this software
 for any purpose. It is provided "as is" without express or implied warranty.
 See the GNU General Public License for more details.

 Documents produced by this add-on functions are derivative works derived from
 the input used in their production; they are not affected by this license.

 <b> History </b>

 @TabBegin
    date           @I author          @I implementation/change
 @I____________________________________________________________
    07.02.2015     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    07.02.2015...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/

#include "TiPa_Abstract.h"


#ifndef DOXYGEN
//namespace TXTDIASM {
//namespace TDA_TinyParser {
#endif //DOXYGEN

/* @MRTZ_describe TiPa_Abstract

*/
 TiPa_Abstract::TiPa_Abstract(void)
               :UserName(nullptr),             // user defined name of the parser that creates this data
                User_ID_String(nullptr),       // string representation of user defined parser id
                UserDescription(nullptr)       // user description of the parser

 {
 }

/* @MRTZ_describe ~TiPa_Abstract

*/
 TiPa_Abstract::~TiPa_Abstract(void)
 {
 }


/* @MRTZ _ describe as_TiPa_Concrete

TiPa_Concrete* TiPa_Abstract::as_TiPa_Concrete(void)
{
 return(nullptr);
}
*/





#ifndef DOXYGEN
#define USING_NAMESPACE using namespace
//}; USING_NAMESPACE TDA_TinyParser;
//}; USING_NAMESPACE TXTDIASM;
#undef  USING_NAMESPACE
#endif //DOXYGEN



