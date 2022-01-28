/*!

 @file
 @brief definitions of an concrete parser-class to represent a grammatical rule
        defined by using terminal parsers and parser-operations

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
    27.06.2015     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    27.06.2015...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/
#ifndef TIPA_RULE_H
 #define TIPA_RULE_H




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

/*!
definitions of an concrete parser-class to search for a single character
*/
class TiPa_Rule:public TiPa_Concrete
{

 public:




  typedef enum Parser_id
  {
   Default        = 0, ///< normal rule
  }Parser_id;




/*!
 @brief default constructor


 @param name  name of the rule

 @htmlinclude ./des/TiPa_Rule_TiPa_Rule.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    27.06.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
explicit TiPa_Rule(const char*                  name,
                   DataModel* contextModel);






/*!
 @brief constructor to parse for one Character out of a set of characters

 @param name  name of the rule
 @param root  root-parser of the parser-combination that defines a grammatical rule
 @param type  identifier of parser-type


 @htmlinclude ./des/TiPa_Rule_TiPa_Rule.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    27.06.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 TiPa_Rule(const char*     name,
           TiPa_Concrete*  root,
           DataModel*      contextModel,
           Parser_id       type = TiPa_Rule::Default);








/*!
 @brief destructor

 @htmlinclude "TiPa_Rule__TiPa_Rule.html"
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    27.06.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  virtual ~TiPa_Rule(void);






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
inline TiPa_String* as_TiPa_String(void)override{return(nullptr);};

/*!
 @brief cast this object to an object of the type @ref TiPa_Rule

 @return a pointer to a real existing object if conversion is possible
 @return nullptr if object could not be converted

*/
inline TiPa_Rule* as_TiPa_Rule (void)override{return(this);};

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

 @param root  root-parser of the parser-combination that defines a grammatical rule
 @param type  identifier of parser-type

 @return reference to this rule

 @htmlinclude ./des/TiPa_Rule_init.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    27.06.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
TiPa_Rule* init(TiPa_Concrete* root, Parser_id type = TiPa_Rule::Default);




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
 @brief return the name of this rule

 @param [in] name name-string of the rule

 @htmlinclude ./des/TiPa_Rule_setName.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    05.07.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void setName(const char* name);






/*!
 @brief return the name of this rule

 @return name-string of the rule
 @return nullptr no valid name is defined

 @htmlinclude ./des/TiPa_Rule_getName.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    27.06.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 const char* getName(void);







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



 @htmlinclude ./des/TiPa_Rule_parser_Test.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    27.06.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 const char* parser_Test(const char* begin, const char* end, TiPa_Result_Abstract* sponsorGuard = nullptr) override;






/*!

 compare if given parser has the same type and the same configuration

 @note different parser-types may be configured in a way that they do the same
       but this will not be tested here

 @param [in] parser object to compare this parser with

 @return true  if given parser has the same type and configuration
 <br>    false if given parser differs in type or configuration


 @htmlinclude "TiPa_Concrete_equal_Parser.html"
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
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
   char* Name;                       ///< contains the characters to parse or search for
   set<const char*>  AlreadyCalled;  ///< to detect recursive calls of a rule
   /// @brief default constructor
   Mbr(void):
    Name(nullptr)
   {};
   /*!
    @brief copy constructor
    @param [in] src object to copy
   */
   Mbr(const Mbr& src):
    Name         (src.Name         ),
    AlreadyCalled(src.AlreadyCalled)
   {};
   /*!
    @brief assignment operator
    @param [in] src object to copy
    @return copied object
   */
   Mbr& operator = (const Mbr& src)
   {
    Name          = src.Name         ;
    AlreadyCalled = src.AlreadyCalled;
    return(*this);
   };
   /// @brief destructor
   ~Mbr(void)
   {
    AlreadyCalled.clear();
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




#endif //TIPA_RULE_H
