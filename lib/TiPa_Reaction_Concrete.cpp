/*!

 @file
 @brief concrete reaction-class for a parser event


 Copyright (C) 2017-2020 by Eckard Klotz.

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
    14.10.2017     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    14.10.2017...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/
#include "TiPa_Reaction_Concrete.h"
#include "TiPa_Data.h"

/* @MRTZ_describe TiPa_Reaction_Concrete

*/
TiPa_Reaction_Concrete::TiPa_Reaction_Concrete(void)
                       :TiPa_Reaction_Abstract()
{

}

/* @MRTZ_describe ~TiPa_Reaction_Concrete

*/
TiPa_Reaction_Concrete::~TiPa_Reaction_Concrete(void)
{

}


/* @MRTZ_describe asTiPa_Reaction_Concrete

*/
TiPa_Reaction_Concrete* TiPa_Reaction_Concrete::asTiPa_Reaction_Concrete(void)
{
 return(this);
}




