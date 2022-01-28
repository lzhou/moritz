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
#ifndef TDA_NOTATION_H
 #define TDA_NOTATION_H

#include<list>

using namespace std;


/*!
 @brief  a user-friendly notation of TxtDiaAsm syntax rules inside cpp source-code
*/
 class TDA_Notation
 {
   public:

/*!
 @brief default constructor


 @htmlinclude ./des/TDA_Notation__TDA_Notation.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    29.10.2016   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
   TDA_Notation(void);

/*!
 @brief initialize notation of TxtDiaAsm syntax with 1 sub-notation

 @param contractor  first sub notation


 @htmlinclude ./des/TDA_Notation_TDA_Notation_1.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    29.10.2016   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
   TDA_Notation(const TDA_Notation& contractor);

/*!
 @brief initialize notation of TxtDiaAsm syntax with 2 sub-notations

 @param contractor1  first sub notation
 @param contractor2  second sub notation


 @htmlinclude ./des/TDA_Notation_TDA_Notation_2.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    29.10.2016   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
   TDA_Notation(const TDA_Notation& contractor1,
                const TDA_Notation& contractor2);

/*!
 @brief destructor


 @htmlinclude ./des/TDA_Notation__TDA_Notation.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    29.10.2016   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
   ~TDA_Notation(void);

/*!
 @brief add a sub notation

 @param contractor  sub notation to add


 @htmlinclude ./des/TDA_Notation_include.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    29.10.2016   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
   void include(const TDA_Notation& contractor);




/*!
 @brief operator assignment

 @param contractor   notation to assign


 @htmlinclude "./des/TDA_Notation_operator=.html"
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    29.10.2016   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
TDA_Notation& operator = (const TDA_Notation& contractor);


   protected:







   private:

   list<TDA_Notation> Contractors;


 };











#endif //TDA_NOTATION_H
