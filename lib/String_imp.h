/*!

 @file
 @brief implementation of a string-class

 First I started with the string-class of wxWidgets. But then I decided to
 design my program as terminal- or shell- application. So I also decided to
 use only standard libs of c/c++. But I wanted also be able to use othe libs
 again. <br>
 This file provides a generic definition of a string-type and functions or
 methods to deal with it.
 <br><br>
 At the moment it contains only a definition as standard-string of c++ and there
 are a lot of todo's to implement a real bridge-pattern to use several
 string-types;

 Copyright (C) 2004-2020 by Eckard Klotz.

 Permission to use, copy, modify, and distribute this software and its
 documentation under the terms of the GNU General Public License is hereby
 granted. No representations are made about the suitability of this software
 for any purpose. It is provided "as is" without express or implied warranty.
 See the GNU General Public License for more details.


 <b> History </b>

 @TabBegin
    date           @I author          @I implementation/change
 @I____________________________________________________________
    2004-05.2005   @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    06.2006 -      @I Eckard Klotz
 @I Changes are documented in the comment of the changed element
 @TabEnd

*/



#ifndef STRING_IMP_H
#define STRING_IMP_H

//#define STRING_IMP_WX
#define ORIGINAL_STRING

//#ifdef STRING_IMP_WX
// // For compilers that supports precompilation , includes "wx/wx.h"
// #include "wx/wxprec.h"
// #ifndef WX_PRECOMP
//  #include "wx/wx.h"
// #endif
//#else  //STRING_IMP_WX
//#endif //STRING_IMP_WX

#include <string>
#include <sstream>
#include <list>
//#include <map>
#include <set>
using namespace std;




#ifdef ORIGINAL_STRING
#ifndef DOXYGEN
 //namespace F_STRING_IMP{
#endif //DOXYGEN



 #define String_imp string

///////////////////////////////////////////////////////////////////////////////
/// changes oll upercase-characters to loercase-characters
/// @param [in] text case-mixed string
/// @return     changed text
/// <br><br>
/// @htmlinclude String_imp_cpp_F_lowCaseString.html
/// <br><br><br>
///////////////////////////////////////////////////////////////////////////////
 String_imp lowCaseString(String_imp text);

///////////////////////////////////////////////////////////////////////////////
/// replaces all oldPart-strings with newPart-strings
/// @param [in] text source-text to change
/// @param [in] oldPart part string to replace
/// @param [in] newPart new string to insert insted
/// @param [in] ReplaceInNewPart replaces also oldPart-strings wich were formed
///             by inserting of newPart (example if the user wants to replace
///             double-blanks by one blank in a string with more 3 blanks behind
///             another the replacement of the first ddouble blank creates the
///             next one)
/// @return changed text-string
/// <br><br>
/// @htmlinclude String_imp_cpp_F_replacePartString.html
/// <br><br><br>
///////////////////////////////////////////////////////////////////////////////
 String_imp replacePartString(const String_imp& text,
                              const String_imp& oldPart,
                              const String_imp& newPart,
                              bool              ReplaceInNewPart = true);

///////////////////////////////////////////////////////////////////////////////
/// converts a number in to a string
/// @param [in] number value to convert
/// @return numeric string
/// <br><br>
/// @htmlinclude String_imp_cpp_F_numberToString.html
/// <br><br><br>
///////////////////////////////////////////////////////////////////////////////
 String_imp numberToString(long number);

///////////////////////////////////////////////////////////////////////////////
/// converts a string in to a number
/// @param [in] number string to convert
/// @return numeric valu of the string
///         0 if there are no numeric characters in the string
/// <br><br>
/// @htmlinclude String_imp_cpp_F_stringToNumber.html
/// <br><br><br>
///////////////////////////////////////////////////////////////////////////////
 long   stringToNumber(String_imp number);





/*!
 tries to findout to reconstruct the line-change-characters used
 by the operation-system and returns it

 @return charater combination as string defined by operation-system

 <br><br>
 @htmlinclude String_imp_cpp_F_newLine.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    03.03.2013   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
    14.07.2013   @I  Eckard Klotz
 @I redesign
 @I use of stream-manipulator endl instead of parameter
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
String_imp newLine();







/*!
 produces an string-set out of a comma-separated string, where
 white-spaces are ignored and not copied

 @param [in] text      comma-separated string, that defines
                       the content of the stringset to build
 @param [in] separator optional pararameter if an other
                       separation-character should be used


 @return set of part-strings

 <br><br>
 @htmlinclude String_imp_cpp_F_stringToSet.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    12.01.2010   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
    18.04.2010   @I  Eckard Klotz
 @I re-factoring
 @I moved this procedure from class Prcs__Abstract (abc2xml)
    to this module and renamed it from _getStringList to
    string2Set
  @I_______________________________________________________
   14.08.2011   @I  Eckard Klotz
 @I re-factoring
 @I added optional parameter for an optional separation-character
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  set<String_imp> stringToSet(String_imp text, char separator=',' );



/*!
 produces an string-list out of a comma-separated string, where
 white-spaces are ignored and not copied

 @param [in] text      comma-separated string, that defines
                       the content of the stringset to build
 @param [in] separator optional pararameter if an other
                       separation-character should be used

 @return list of part-strings

 <br><br>
 @htmlinclude String_imp_cpp_F_stringToList.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    17.03.2010   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
    18.04.2010   @I  Eckard Klotz
 @I re-factoring
 @I moved this procedure from class Prcs__Abstract (abc2xml)
    to this module and renamed it from _getStringList to
    string2List
  @I_______________________________________________________
   14.08.2011   @I  Eckard Klotz
 @I re-factoring
 @I added optional parameter for an optional separation-character
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  list<String_imp> stringToList(String_imp text, char separator=',' );








// With C++20 you can use std::string::starts_with().
bool starts_with ( const std::string& str, const std::string& pre );








#ifndef DOXYGEN
#define USING_NAMESPACE using namespace
//}; USING_NAMESPACE F_STRING_IMP;
#undef  USING_NAMESPACE
#endif //DOXYGEN





#else //ORIGINAL_STRING


///////////////////////////////////////////////////////////////////////////////
/// capsuletes the string-implementation. Depending to the aplication it may be
/// the standard-string of c++ or another string-class like wxString from
/// wxWidgets. <br>
/// this section is still under construction!
///////////////////////////////////////////////////////////////////////////////
class String_imp : public string
{
 public:
///Default constructor.
  String_imp()
  :string(){};

///Copy constructor.
  String_imp(const String_imp& x)
//  String_imp( String_imp& x)
  :string((string&)x){};




///Constructs a string of n copies of character ch.
  String_imp(char ch, size_t n = 1)
  :string(ch,n){};




/// Takes first nLength characters from the C string psz. The default value of
/// wxSTRING_MAXLEN means to take all the string.
/// Note that this constructor may be used even if psz points to a buffer with
/// binary data (i.e. containing NUL characters) as long as you provide the
/// correct value for nLength. However, the default form of it works only with
/// strings without intermediate NULs because it uses strlen() to calculate the
/// effective length and it will not give correct results otherwise.
//  String_imp(const char* psz, size_t nLength = STRING_MAXLEN)
  String_imp(const char* psz, size_t nLength)
  :string(psz,nLength){};




/// For compilers using unsigned char: takes first nLength characters from the
/// C string psz. The default value of wxSTRING_MAXLEN means take all the
/// string.
//  String_imp(const unsigned char* psz, size_t nLength = wxSTRING_MAXLEN)
//  String_imp(const unsigned char* psz, size_t nLength )
//  :string(psz, nLength){};



///Constructs a string from the wide (UNICODE) string.

//  String_imp(const wchar_t* psz)
//  :string(psz){};


  ~String_imp(){};


//  String_imp& operator =(const String_imp& str)
//  :wxString& operator =(str){};
//
//  String_imp& operator =(const char* psz)
//  :wxString& operator =(psz){};
//
//  String_imp& operator =(char c)
//  :wxString& operator =(c){};
//
//  String_imp& operator =(const unsigned char* psz)
//  :wxString& operator =(psz){};
//
//  String_imp& operator =(const wchar_t* pwz)
//  :wxString& operator =(pwz){};














  protected:

  private:

};


#endif //ORIGINAL_STRING






#endif //STRING_IMP
