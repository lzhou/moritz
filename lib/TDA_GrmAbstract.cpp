/*!

 @file
 @brief definitions of an abstract grammar-class as template
         to manage tiny parser classes and their extensions

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
    10.05.2015     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    10.05.2015...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/

#include "TDA_GrmAbstract.h"


#ifndef DOXYGEN
//namespace TXTDIASM {
//namespace TDA_Grammar {
#endif //DOXYGEN

/* @MRTZ_describe TDA_GrmAbstract

*/
 TDA_GrmAbstract::TDA_GrmAbstract(void)
 {
  LOG_OUTPUT(LOG_OFF, "TDA_GrmAbstract(void)");
 }

/* @MRTZ_describe ~TDA_GrmAbstract

*/
 TDA_GrmAbstract::~TDA_GrmAbstract(void)
 {
  LOG_OUTPUT(LOG_OFF, "~TDA_GrmAbstract(void)");
 }







#ifndef DOXYGEN
#define USING_NAMESPACE using namespace
//}; USING_NAMESPACE TDA_Grammar;
//}; USING_NAMESPACE TXTDIASM;
#undef  USING_NAMESPACE
#endif //DOXYGEN



