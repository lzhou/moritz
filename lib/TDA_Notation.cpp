/*!

 @file
 @brief  a user-friendly notation of TxtDiaAsm syntax rules inside cpp source-code

 Copyright (C) 2016-2017 by Eckard Klotz.

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
    29.10.2016     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    29.10.2016...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/

#include "TDA_Notation.h"

/* MRTZ_describe

*/
TDA_Notation::TDA_Notation(void)
{
}

/* MRTZ_describe

*/
TDA_Notation::TDA_Notation(const TDA_Notation& contractor)
{
 Contractors.push_back(contractor);
}

/* MRTZ_describe

*/
TDA_Notation::TDA_Notation(const TDA_Notation& contractor1,
                           const TDA_Notation& contractor2)
{
 Contractors.push_back(contractor1);
 Contractors.push_back(contractor2);
}

/* MRTZ_describe

*/
TDA_Notation::~TDA_Notation(void)
{
 Contractors.clear();
}



/* MRTZ_describe

*/
void TDA_Notation::include(const TDA_Notation& contractor)
{
 Contractors.push_back(contractor);
}





