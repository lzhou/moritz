/*!

 @file
 @brief tools to manage classic c-strings

 Copyright (C) 2018-2020 by Eckard Klotz.

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
    21.11.2017     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    21.11.2017...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/
#ifndef STRINGC_HELP_H
#define STRINGC_HELP_H




/*!
 @brief check if the 2 given c-strings str1 and str2 have the same content
 @param str1 a valid c-string
 @param str2 a valid c-string
 @return true  if both strings have exactly the same content until their termination
 <br>    false if the strings have different content or length
*/
#define STRINGS_ARE_EQUAL(str1,str2) ((str1!=nullptr)&&(str2!=nullptr)&&(strstr(str1,str2)==str1)&&((strlen(str1)==strlen(str2))))

/*!
 @brief check if the 2 given c-strings str1 and str2 have not the same content
 @param str1 a valid c-string
 @param str2 a valid c-string
 @return true  if both strings have exactly the same not content until their termination
 <br>    false if the strings have the content and length
*/
#define STRINGS_ARE_NOT_EQUAL(str1,str2) ((strstr(str1,str2)!=str1)||(strlen(str1)!=strlen(str2)))

/*!
 @brief check if the given association has contractors
 @param association a valid data association
 @return true  if the given association has at least one contractor
 <br>    false if the given association has at no contractor
*/
#define ASSOCIATION_IS_NOT_LEAF(association)(  (association->contractorFirst_get() != nullptr )\
                                             &&(association->contractorLast_get()  != nullptr ))


/*!
 @brief check if the given association has no contractors
 @param association a valid data association
 @return true  if the given association has at no contractor
 <br>    false if the given association has at least one contractor
*/
#define ASSOCIATION_IS_LEAF(association)(  (association->contractorFirst_get() == nullptr )\
                                         &&(association->contractorLast_get()  == nullptr ))


#endif // STRINGC_HELP_H
