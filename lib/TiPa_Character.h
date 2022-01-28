/*!

 @file
 @brief definitions of an concrete parser-class to search for a single
        character

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
    15.02.2015     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    15.02.2015...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/
#ifndef TIPA_CHARCTER_H
 #define TIPA_CHARCTER_H




#include "TiPa_Concrete.h"
#include "TiPa_Data.h"

#include <set>
#include <map>
#include <list>
#include <limits.h>



using namespace std;

#ifndef DOXYGEN
//namespace TXTDIASM {
//namespace TDA_TinyParser {
////namespace CL_TIPA_CONCRETE {
//namespace CL_TIPA{
#endif //DOXYGEN


/// @ingroup UNUSED_DATA
/// @brief avoid compiler warning since the object is not used
/// @{
#define TIPA_RESULT_ABSTRACT_UNUSED __attribute__ ((unused)) TiPa_Result_Abstract
/// @}





/*!
definitions of an concrete parser-class to search for a single character
*/
class TiPa_Character:public TiPa_Concrete
{

 public:

/// @brief describes the types of character parsers
  typedef enum Parser_id
  {
   Default  =  0  , ///< not specified character parser
   Single   =  1  , ///< single character
   Range    =  2  , ///< character range
   Group    =  3  , ///< character group
   Alnum    =  4  , ///< alphanumeric character
   Alpha    =  5  , ///< any letter
   Anychar  =  6  , ///< any character
   Blank    =  7  , ///< space or tab
   Cntrl    =  8  , ///< any control character
   Digit    =  9  , ///< any digit
   Graph    = 10  , ///< any non-space printable character
   Lower    = 11  , ///< any lower-case letter
   Print    = 12  , ///< any printable character
   Punct    = 13  , ///< any punctuation mark
   Sign     = 14  , ///< plus or minus sign
   Space    = 15  , ///< any white space character
   Upper    = 16  , ///< any upper-case letter
   BinDigit = 17  , ///< any binary digit
   OctDigit = 18  , ///< any octagonal digit
   HexDigit = 19  , ///< any hexadecimal digit
  }Parser_id;

/// @brief borders of char-range as defined for the compiler
 enum CharacterLimits
  {
    CharMin = CHAR_MIN,   ///< smallest ordinal-number
    CharMax = CHAR_MAX,   ///< greatest ordinal-number
  };



/*!
 @brief default constructor

 @param [in] contextModel management-object that creates and deletes associations and data-objects

 @htmlinclude ./des/TiPa_Character_TiPa_Character.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    15.02.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 explicit TiPa_Character(DataModel* contextModel);




/*!
 @brief constructor to search for one special character

 @param [in] character    character to search for
 @param [in] contextModel management-object that creates and deletes associations and data-objects
 @param [in] type         identifier of parser-type



 @htmlinclude ./des/TiPa_Character_TiPa_Character.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    21.02.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 TiPa_Character(char       character,
                DataModel* contextModel,
                Parser_id  type = Default);



/*!
 @brief constructor to search for one character as part of a range of characters

 @param [in] firstCharacter first character in the range of characters to search for
 @param [in] lastCharacter  last  character in the range of characters to search for
 @param [in] contextModel   management-object that creates and deletes associations and data-objects
 @param [in] type           identifier of parser-type


 @htmlinclude ./des/TiPa_Character_TiPa_Character.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    21.02.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 TiPa_Character(char       firstCharacter,
                char       lastCharacter,
                DataModel* contextModel,
                Parser_id  type = Range);



/*!
 @brief constructor to parse for one Character out of a set of characters

 @param [in] characterArray  set of character to search for
 @param [in] sizeOfArray     length of the array used as set
 @param [in] contextModel    management-object that creates and deletes associations and data-objects
 @param [in] type            identifier of parser-type


 @htmlinclude ./des/TiPa_Character_TiPa_Character.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    21.02.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 TiPa_Character(const char* characterArray,
                int         sizeOfArrary,
                DataModel*  contextModel,
                Parser_id   type = Group);


/*!
 @brief constructor to parse for special character sets

 @param [in] characterSet  id of character-collection to search for
 @param [in] contextModel management-object that creates and deletes associations and data-objects


 @htmlinclude ./des/TiPa_Character_TiPa_Character.html
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
  TiPa_Character(Parser_id  characterSet,
                 DataModel* contextModel);






/*!
 @brief destructor

 @htmlinclude "TiPa_Character__TiPa_Character.html"
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    15.02.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  virtual ~TiPa_Character(void);



/*!
 @brief cast this object to an object of the type @ref TiPa_Character

 @return a pointer to a real existing object if conversion is possible
 @return nullptr if object could not be converted

*/
inline TiPa_Character* as_TiPa_Character(void)override{return(this);};

/*!
 @brief cast this object to an object of the type @ref TiPa_String

 @return a pointer to a real existing object if conversion is possible
 @return nullptr if object could not be converted

*/
inline TiPa_String* as_TiPa_String(void)override{return(nullptr);};

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
 @brief initialize to search for one special character

 @param character character to search for
 @param type      identifier of parser-type

 @return reference to this character-parser

 @htmlinclude ./des/TiPa_Character_TiPa_Character.html
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
TiPa_Character* init(char character, Parser_id type=Single);



/*!
 @brief initialize to search for one character as part of a range of characters

 @param firstCharacter first character in the range of characters to search for
 @param lastCharacter  last  character in the range of characters to search for
 @param type           identifier of parser-type

 @return reference to this character-parser

 @htmlinclude ./des/TiPa_Character_TiPa_Character.html
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
TiPa_Character* init(char firstCharacter, char lastCharacter, Parser_id type=Range);



/*!
 @brief initialize to parse for one Character out of a set of characters

 @param characterArray  set of character to search for
 @param sizeOfArray     length of the array used as set
 @param type            identifier of parser-type

 @return reference to this character-parser

 @htmlinclude ./des/TiPa_Character_TiPa_Character.html
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
TiPa_Character* init(const char* characterArray, int sizeOfArrary, Parser_id type=Group);






/*!
 @brief initialize to parse for special character sets

 @param characterSet  id of character-collection to search for

 @return reference to this character-parser

 @htmlinclude ./des/TiPa_Character_init.html
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
TiPa_Character* init(Parser_id characterSet);




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
 @brief extent the parser to search for one more special character

 @param character additional character to search for

 @return reference to this extended character-parser

 @htmlinclude ./des/TiPa_Character_include.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    21.02.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
TiPa_Character* include(char character);



/*!
 @brief extent the parser to search for one character as part of an additional range of characters

 @param firstCharacter first character in the additional range of characters to search for
 @param lastCharacter  last  character in the additional range of characters to search for

 @return reference to this extended character-parser

 @htmlinclude ./des/TiPa_Character_include.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    21.02.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
TiPa_Character* include(char firstCharacter, char lastCharacter);



/*!
 @brief extent the parser to to parse for one Character out of an additional set of characters

 @param characterArray  set of additional characters to search for
 @param sizeOfArray     length of the array used as set

 @return reference to this extended character-parser

 @htmlinclude ./des/TiPa_Character_include.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    21.02.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
TiPa_Character* include(const char* characterArray, int sizeOfArrary);




/*!
 @brief reduce the amount of characters to search for by one special character

 @param character character to exclude from search

 @return reference to this extended character-parser

 @htmlinclude ./des/TiPa_Character_exclude.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    21.02.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
TiPa_Character* exclude(char character);



/*!
 @brief reduce the amount of characters to search for by a range of characters

 @param firstCharacter first character in the range of characters to exclude from search
 @param lastCharacter  last  character in the range of characters to exclude from search

 @return reference to this extended character-parser

 @htmlinclude ./des/TiPa_Character_exclude.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    21.02.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
TiPa_Character* exclude(char firstCharacter, char lastCharacter);



/*!
 @brief reduce the amount of characters to search for by a set of characters

 @param characterArray  set of characters to exclude from search
 @param sizeOfArray     length of the array used as set

 @return reference to this extended character-parser

 @htmlinclude ./des/TiPa_Character_exclude.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    21.02.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
TiPa_Character* exclude(const char* characterArray, int sizeOfArrary);










/*!
 @brief search for parser hit at begin of given string

 test the given string described with its begin and end to
 decide, if it starts with a construction defined by the parser,
 a hit will be stored inside the parser and reused to save time.

 @param [in] begin   points to the first character of the given string
 @param [in] end     points behind the last character of the given string
 @param [in] storage memorizing the parser result

 @return a pointer directly behind the found match if the given string starts
         with the construction defined by the parser.
 @return nullptr if the given string starts not
         with the construction defined by the parser


 @htmlinclude ./des/TiPa_Character_parser_Test.html
 @I_______________________________________________________
    15.02.2015   @I  Eckard Klotz
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
 @brief test the given character is specified by the specific parser definition.

 already known sub-types of a character-parser may be tested faster this way.

 @param [in] begin  test-object

 @return true  if the given character is specified
 @return false if the given character is not specified


 @htmlinclude ./des/TiPa_Character_testSpecific.html
 @I_______________________________________________________
    13.12.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
bool testSpecific(char begin);


/*!

 compare if given parser has the same type and the same configuration

 @note different parser-types may be configured in a way that they do the same
       but this will not be tested here

 @param [in] parser object to compare this parser with

 @return true  if given parser has the same type and configuration
 <br>    false if given parser differs in type or configuration


 @htmlinclude ./des/TiPa_Character_equal_Parser.html
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
   set<char> ParseItem; ///< contains the characters to parse or search for
   char Included[256];  ///< specified characters
   char Excluded[256];  ///< unspecified characters

   /// @brief default constructor
   Mbr(void)
   {
    memset(Included,0,256);
    memset(Excluded,0,256);
   };
   /*!
    @brief copy constructor
    @param [in] src object to copy
   */
   Mbr(const Mbr& src):
   ParseItem(src.ParseItem)
   {
    memcpy(Included,src.Included,256);
    memcpy(Excluded,src.Excluded,256);
   };
   /*!
    @brief assignment operator
    @param [in] src object to copy
    @return copied object
   */
   Mbr& operator = (const Mbr& src)
   {
    ParseItem = src.ParseItem;
    memcpy(Included,src.Included,256);
    memcpy(Excluded,src.Excluded,256);
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




#endif //TIPA_CHARCTER_H
