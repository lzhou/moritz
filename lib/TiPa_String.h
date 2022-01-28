/*!

 @file
 @brief definitions of an concrete parser-class to search for a single
        string or character-sequence

 Copyright (C) 2015-2020 by Eckard Klotz.

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
    01.03.2015     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    01.03.2015...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/
#ifndef TIPA_STRING_H
 #define TIPA_STRING_H




#include "TiPa_Concrete.h"
#include "TiPa_Data.h"

#include <set>
#include<map>
#include<list>



using namespace std;

#ifndef DOXYGEN
//namespace TXTDIASM {
//namespace TDA_TinyParser {
////namespace CL_TIPA_CONCRETE {
//namespace CL_TIPA {
#endif //DOXYGEN


/// @ingroup UNUSED_DATA
/// @brief avoid compiler warning since the object is not used
/// @{
#define TIPA_RESULT_ABSTRACT_UNUSED __attribute__ ((unused)) TiPa_Result_Abstract
/// @}





/*!
definitions of an concrete parser-class to search for a single character
*/
class TiPa_String:public TiPa_Concrete
{

 public:

 /// @brief describes the types of string parsers
 typedef enum Parser_id
  {
   Default        = 0, ///< not specified string parser
   CommentSingle  = 1, ///< single comment-marker
   CommentDouble  = 2, ///< comment-marker-pair
  }Parser_id;


/*!
 @brief default constructor

 @param contextModel [in] management-object that creates and deletes associations and data-objects

 @htmlinclude ./des/TiPa_String_TiPa_String.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    01.03.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 explicit TiPa_String(DataModel* contextModel);






/*!
 @brief constructor to parse for one Character out of a set of characters

 @param string       [in] set of character to search for
 @param size         [in] length of the array used as set
 @param contextModel [in] management-object that creates and deletes associations and data-objects
 @param type         [in]identifier of parser-type


 @htmlinclude ./des/TiPa_String_TiPa_String.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    01.03.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 TiPa_String(const char*                  string,
             int                          size,
             DataModel* contextModel,
             Parser_id                    type = Default);




/*!
 @brief constructor to parse for one Character out of a set of characters

 @param string       [in] set of character to search for
 @param contextModel [in] management-object that creates and deletes associations and data-objects
 @param type         [in] identifier of parser-type


 @htmlinclude ./des/TiPa_String_TiPa_String.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    07.03.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 TiPa_String(const char*                  string,
             DataModel* contextModel,
             Parser_id                    type = Default);







/*!
 @brief constructor to parse for special string sets

 @param stringSet    [in] id of string-collection to search for
 @param contextModel [in] management-object that creates and deletes associations and data-objects


 @htmlinclude ./des/TiPa_String_TiPa_String.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    01.03.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  TiPa_String(Parser_id                    stringSet,
              DataModel* contextModel);






/*!
 @brief destructor

 @htmlinclude ./des/TiPa_StringTiPa_String.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    01.03.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  virtual ~TiPa_String(void);






/*!
 @brief cast this object to an object of the type @ref TiPa_Character

 @return a pointer to a real existing object if conversion is possible
 @return nullptr if object could not be converted

*/
inline TiPa_Character* as_TiPa_Character(void)override{return(nullptr);};

/*!
 @brief cast this object to an object of the type @ref TiPa_String

 @return a pointer to a real existing object if conversion is possible
 @return nullptr if object could not be converted

*/
inline TiPa_String* as_TiPa_String(void)override{return(this);};

/*!
 @brief cast this object to an object of the type @ref TiPa_Rule

 @return a pointer to a real existing object if conversion is possible
 @return nullptr if object could not be converted

*/
inline TiPa_Rule* as_TiPa_Rule(void)override{return(nullptr);};

/*!
 @brief cast this object to an object of the type @ref TiPa_Condition

 @return a pointer to a real existing object if conversion is possible
 @return nullptr if object could not be converted

*/
inline TiPa_Condition* as_TiPa_Condition(void)override{return(nullptr);};

/*!
 @brief cast this object to an object of the type @ref TiPa_Sequence

 @return a pointer to a real existing object if conversion is possible
 @return nullptr if object could not be converted

*/
inline TiPa_Sequence* as_TiPa_Sequence(void)override{return(nullptr);};

/*!
 @brief cast this object to an object of the type @ref TiPa_Counter

 @return a pointer to a real existing object if conversion is possible
 @return nullptr if object could not be converted

*/
inline TiPa_Counter* as_TiPa_Counter(void)override{return(nullptr);};








/*!
 @brief initialize to parse for one Character out of a set of characters

 @param string  set of character to search for
 @param size    length of the array used as set
 @param type    identifier of parser-type

 @return reference to this string-parser

 @htmlinclude ./des/TiPa_String_init.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    05.04.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
TiPa_String* init(const char* string, int size, Parser_id type=Default);




/*!
 @brief initialize to parse for one Character out of a set of characters

 @param string  set of character to search for
 @param type    identifier of parser-type

 @return reference to this string-parser

 @htmlinclude ./des/TiPa_String_init.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    05.04.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
TiPa_String* init(const char* string, Parser_id type=Default);












/*!
 @brief initialize to parse for special character sets

 @param stringSet  id of character-collection to search for

 @return reference to this string-parser

 @htmlinclude ./des/TiPa_String_init.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    05.04.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
TiPa_String* init(Parser_id stringSet);








 /*!
 @brief return the kind of parser class

 @return parser class identifying number


 @htmlinclude "TiPa_Concrete_type.html"
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    04.07.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
static TDA_TiPa_CLASS_TP id_Class(void);



/*!
 @brief return the kind of parser class identifier

 @return parser type identifying number


 @htmlinclude "TiPa_Concrete_id_SubType.html"
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    02.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual TDA_TiPa_CLASS_TP id_Type(void) override;








/*!
 @brief extent the parser to to parse for one more string

 @param string  additional string to search for
 @param size    length of string to use in the case that the given is not terminated

 @return reference to this extended string-parser

 @htmlinclude ./des/TiPa_String_include.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    01.03.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
TiPa_String* include(const char* string, int size=-1);




/*!
 @brief reduce the amount of strings to search for

 @param string  additional string to search for
 @param size    length of string to use in the case that the given is not terminated

 @return reference to this extended string-parser

 @htmlinclude ./des/TiPa_String_exclude.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    01.03.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
TiPa_String* exclude(const char* string, int size=-1);




/*!
 @brief search for parser hit at begin of given string

 test the given string described with its begin and end to
 decide, if it starts with a construction defined by the parser,
 a hit will be stored inside the parser and reused to save time.

 @param [in] begin         points to the first character of the given string
 @param [in] end           points behind the last character of the given string
 @param [in] resultStorage memorizing the parser result

 @return a pointer directly behind the found match if the given string starts
         with the construction defined by the parser.
 @return nullptr if the given string starts not
         with the construction defined by the parser



 @htmlinclude ./des/TiPa_String_parser_Test.html
 @I_______________________________________________________
    01.03.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 const char* parser_Test(const char*                  begin,
                         const char*                  end,
                         TIPA_RESULT_ABSTRACT_UNUSED* sponsorGuard = nullptr) override;





 /*!
 @brief test the given string is specified by the specific parser definition.


 @param [in] begin  first character of test-object
 @param [in] end    first character behind test-object

 @return size of specified string  if the given string starts with this specified one
 @return -1    if the given string is not specified


 @htmlinclude ./des/TiPa_String_testSpecific.html
 @I_______________________________________________________
    13.12.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
int testSpecific(const char* begin, const char* end);





/*!

 compare if given parser has the same type and the same configuration

 @note different parser-types may be configured in a way that they do the same
       but this will not be tested here

 @param [in] parser object to compare this parser with

 @return true  if given parser has the same type and configuration
 <br>    false if given parser differs in type or configuration


 @htmlinclude "TiPa_Concrete_equal_Parser.html"
 @I_______________________________________________________
    21.06.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual bool equal_Parser(TiPa_Concrete* parser) override;




 protected:

 private:

/*!
 Mbr.ibutes of class
 */
  struct Mbr
  {
   set<const char*> ParseItem; ///< contains the characters to parse or search for

   /// @brief default constructor
   Mbr(void)
   {
   };
   /*!
    @brief copy constructor
    @param [in] src object to copy
   */
   Mbr(const Mbr& src):
   ParseItem(src.ParseItem)
   {
   };
   /*!
    @brief assignment operator
    @param [in] src object to copy
    @return copied object
   */
   Mbr& operator = (const Mbr& src)
   {
    ParseItem = src.ParseItem;
    return(*this);
   };
   /// @brief destructor
   ~Mbr(void)
   {
    ParseItem.clear();
   };

  }Mbr;



};



#ifndef DOXYGEN
#define USING_NAMESPACE using namespace
//}; USING_NAMESPACE CL_TIPA;
//}; USING_NAMESPACE CL_TIPA_CONCRETE;
//}; USING_NAMESPACE TDA_TinyParser;
//}; USING_NAMESPACE TXTDIASM;
#undef  USING_NAMESPACE
#endif //DOXYGEN




#endif //TIPA_STRING_H
