/*!

 @file
 @brief definitions of an concrete parser-class to search for a specified
       number of hits of an other parser

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
    07.03.2015     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    07.03.2015...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/
#ifndef TIPA_COUNTER_H
 #define TIPA_COUNTER_H


#include<map>
#include<list>


#include "TiPa_Concrete.h"
#include "TiPa_Data.h"

#include <set>



using namespace std;

#ifndef DOXYGEN
//namespace TXTDIASM {
//namespace TDA_TinyParser {
////namespace CL_TIPA_CONCRETE {
//namespace CL_TIPA{
#endif //DOXYGEN


//#define IGNORE_UNUSED __attribute__ ((unused))

/// @ingroup UNUSED_DATA
/// @brief avoid compiler warning since the object is not used
/// @{
#define TIPA_RESULT_ABSTRACT_UNUSED __attribute__ ((unused)) TiPa_Result_Abstract
#define CONTRACTORLIST_TP_UNUSED    __attribute__ ((unused)) TiPa_Concrete::ContractorList_TP
/// @}





/*!
definitions of an concrete parser-class to search for a single character
*/
class TiPa_Counter:public TiPa_Concrete
{

 public:

/// @brief describes the types of counter parsers
  typedef enum Parser_id
  {
   Cnt_Default    = 0, ///< not specified counting operator
   Cnt_OneOrMore  = 1, ///< operator to find one or more
   Cnt_AllButNot  = 2, ///< operator to find every character except the defined
   Cnt_OptionMore = 3, ///< operator to find nothing or more
   Cnt_OptionOne  = 4, ///< operator to find nothing or one
  }Parser_id;




/*!
 default constructor

 @htmlinclude ./des/TiPa_Counter_TiPa_Counter.html
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
 explicit TiPa_Counter(DataModel* contextModel);






/*!
 constructor to parse for one Character out of a set of characters

 @param parser  contractor-parser
 @param min     allowed minimum of sequential hits
 @param max     allowed maximum of sequential hits
 @param type    identifier of concrete parser-type


 @htmlinclude ./des/TiPa_Counter_TiPa_Counter.html
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
 TiPa_Counter(TiPa_Concrete*                        parser,
              DataModel* contextModel,
              int                                    min  = 1,
              int                                    max  = 1,
              Parser_id                              type = Cnt_Default);






/*!
 constructor to parse for special character sets

 @param operation  id of the counting-operation
 @param parser     contractor-parser


 @htmlinclude ./des/TiPa_Counter_TiPa_Counter.html
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
 TiPa_Counter(Parser_id                             operation,
              TiPa_Concrete*                        parser,
              DataModel* contextModel);






/*!
 destructor

 @htmlinclude "TiPa_CounterTiPa_Counter.html
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
  virtual ~TiPa_Counter(void);



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
inline TiPa_Counter* as_TiPa_Counter(void)override{return(this);};




/*!
 @brief initialize to parse for special number of occurrences

 @param operation  id of the counting-operation
 @param parser     contractor-parser

 @return reference to this extended sequence

 @htmlinclude ./des/TiPa_Counter_TiPa_Counter.html
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
TiPa_Counter*  init(Parser_id operation, TiPa_Concrete* parser);






/*!
 @brief initialize to parse for zero or one of occurrence

 @param parser     contractor-parser

 @return reference to this extended sequence

 @htmlinclude ./des/TiPa_Counter_TiPa_Counter.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    16.10.2016   @I  Eckard Klotz
 @I extension of the design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
TiPa_Counter* zeroOrOne(TiPa_Concrete* parser);


/*!
 @brief initialize to parse for zero or more of occurrences

 @param parser     contractor-parser

 @return reference to this extended sequence

 @htmlinclude ./des/TiPa_Counter_TiPa_Counter.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    16.10.2016   @I  Eckard Klotz
 @I extension of the design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
TiPa_Counter* zeroOrMore(TiPa_Concrete* parser);


/*!
 @brief initialize to parse for one or more of occurrences

 @param parser     contractor-parser

 @return reference to this extended sequence

 @htmlinclude ./des/TiPa_Counter_TiPa_Counter.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    16.10.2016   @I  Eckard Klotz
 @I extension of the design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
TiPa_Counter* oneOrMore(TiPa_Concrete* parser);


/*!
 @brief initialize to parse for no of occurrence of the given one

 @param parser     contractor-parser

 @return reference to this extended sequence

 @htmlinclude ./des/TiPa_Counter_TiPa_Counter.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    16.10.2016   @I  Eckard Klotz
 @I extension of the design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
TiPa_Counter* allButNot(TiPa_Concrete* parser);







/*!
 return the kind of parser class

 @return parser class identifying number

 @htmlinclude ./des/TiPa_Concrete_type.html
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
 return the kind of parser class identifier

 @return parser type identifying number


 @htmlinclude ./des/TiPa_Concrete_id_SubType.html
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
 @brief search for parser hit at begin of given string

 test the given string described with its begin and end to
 decide, if it starts with a construction defined by the parser,
 a hit will be stored inside the parser and reused to save time.

 @param [in] begin         points to the first character of the given string
 @param [in] end           points behind the last character of the given string
 @param [in] resultStorage memorizing the parser result

 @return the given <b>begin</b> if the given string starts not
         with the construction defined by the sub parser and should not do so
         ( @ref UniAllButNot ).
 @return a pointer directly behind the found match if the given string starts
         with the construction defined by the sub parser the specified number of times.
 @return nullptr if the given string starts not
         with the construction defined by the parser but should do so



 @htmlinclude ./des/TiPa_Counter_parser_Test.html
 @I_______________________________________________________
    07.03.2015   @I  Eckard Klotz
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
 @note if contractor-parsers are equal but not the same instance this and the given
       parser will be treated as not equal

 @param [in] parser object to compare this parser with

 @return true  if given parser has the same type and configuration
 <br>    false if given parser differs in type or configuration


 @htmlinclude ./des/TiPa_Concrete_equal_Parser.html
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
 test the given string described with its begin and end to
 decide, if it starts with a construction ,defined by the given contractor parser,
 one or more times.
 a hit will be stored inside the parser and reused to save time.

 @param [in]  contractorParser points to the first character of the given string
 @param [in]  begin            points to the first character of the given string
 @param [in]  end              points behind the last character of the given string
 @param [in]  storage          memorizing the parser result
 @param [out] contractor       container that stores references to hits of contractor-parsers

 @return a pointer directly behind the found match if the given string starts
         with the construction defined by the sub parser the specified number of times.
 @return nullptr if the given string starts not
         with the construction defined by the parser



 @htmlinclude ./des/TiPa_Counter_parser_Test_OneOrMore.html
 @I_______________________________________________________
    07.03.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 const char* parser_Test_OneOrMore(TiPa_Concrete*        contractorParser,
                                   const char*           begin,
                                   const char*           end,
                                   TiPa_Result_Abstract* sponsorGuard);




/*!
 test the given string described with its begin and end to
 decide, if it starts not with a construction, defined by the given contractor parser,
 a hit will be stored inside the parser and reused to save time.

 @param [in]  contractorParser points to the first character of the given string
 @param [in]  begin            points to the first character of the given string
 @param [in]  end              points behind the last character of the given string
 @param [in]  storage          memorizing the parser result
 @param [out] contractor       container that stores references to hits of contractor-parsers


 @return the given <b>begin</b> if the given string starts not
         with the construction defined by the sub parser and should not do so
         ( @ref UniAllButNot ).
 @return nullptr if the given string starts
         with the construction defined by the parser



 @htmlinclude ./des/TiPa_Counter_parser_Test_AllButNot.html
 @I_______________________________________________________
    07.03.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 const char* parser_Test_AllButNot(TiPa_Concrete*               contractorParser,
                                   const char*                  begin,
                                   const char*                  end,
                                   TIPA_RESULT_ABSTRACT_UNUSED* sponsorGuard);




/*!
 test the given string described with its begin and end to
 decide, if it starts with a construction, defined by the given contractor parser,
 a not specified number of times including 0,
 a hit will be stored inside the parser and reused to save time.

 @param [in]  contractorParser points to the first character of the given string
 @param [in]  begin            points to the first character of the given string
 @param [in]  end              points behind the last character of the given string
 @param [in]  storage          memorizing the parser result
 @param [out] contractor       container that stores references to hits of contractor-parsers


 @return the given <b>begin</b> if the given string starts not
         with the construction defined by the sub parser
 @return a pointer directly behind the found match if the given string starts
         with the construction defined by the sub parser the specified number of times.



 @htmlinclude ./des/TiPa_Counter_parser_Test_OptionMore.html
 @I_______________________________________________________
    07.03.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 const char* parser_Test_OptionMore(TiPa_Concrete*        contractorParser,
                                    const char*           begin,
                                    const char*           end,
                                    TiPa_Result_Abstract* sponsorGuard);




/*!
 test the given string described with its begin and end to
 decide, if it starts with a construction, defined by the given contractor parser,
 at least one times or more often,
 a hit will be stored inside the parser and reused to save time.

 @param [in]  contractorParser points to the first character of the given string
 @param [in]  begin            points to the first character of the given string
 @param [in]  end              points behind the last character of the given string
 @param [in]  storage          memorizing the parser result
 @param [out] contractor       container that stores references to hits of contractor-parsers


 @return the given <b>begin</b> if the given string starts not
         with the construction defined by the sub parser
 @return a pointer directly behind the found match if the given string starts
         with the construction defined by the sub parser one times.
 @return nullptr if the given string starts more often
         with the construction defined by the parser



 @htmlinclude ./des/TiPa_Counter_parser_Test_OptionOne.html
 @I_______________________________________________________
    07.03.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 const char* parser_Test_OptionOne(TiPa_Concrete*        contractorParser,
                                   const char*           begin,
                                   const char*           end,
                                   TiPa_Result_Abstract* sponsorGuard);




/*!
 test the given string described with its begin and end to
 decide, if it starts with a construction, defined by the given contractor parser,
 the number of times specified by the class attributes Max and Min,
 a hit will be stored inside the parser and reused to save time.

 @param [in]  contractorParser points to the first character of the given string
 @param [in]  begin            points to the first character of the given string
 @param [in]  end              points behind the last character of the given string
 @param [in]  storage          memorizing the parser result
 @param [out] contractor       container that stores references to hits of contractor-parsers


 @return a pointer directly behind the found match if the given string starts
         with the construction defined by the sub parser the specified number of times.
 @return nullptr if the given string starts more or less often
         with the construction defined by the parser



 @htmlinclude ./des/TiPa_Counter_parser_Test_Default.html
 @I_______________________________________________________
    07.03.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 const char* parser_Test_Default(TiPa_Concrete*        contractorParser,
                                 const char*           begin,
                                 const char*           end,
                                 TiPa_Result_Abstract* sponsorGuard);





/*!
 Mbr.ibutes of class
 */
  struct Mbr
  {
   int               Min;            ///< allowed minimum of sequential hits
   int               Max;            ///< allowed maximum of sequential hits
   set<const char*>  AlreadyCalled;  ///< to detect recursive calls of a rule
   /// @brief default constructor
   Mbr(void):
    Min(-1),
    Max(-1)
   {};
   /*!
    @brief copy constructor
    @param [in] src object to copy
   */
   Mbr(const Mbr& src):
    Min          (src.Min          ),
    Max          (src.Max          ),
    AlreadyCalled(src.AlreadyCalled)
   {};
   /*!
    @brief assignment operator
    @param [in] src object to copy
    @return copied object
   */
   Mbr& operator = (const Mbr& src)
   {
    Min           = src.Min          ;
    Max           = src.Max          ;
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




#endif //TIPA_COUNTER_H
