/*!

 @file
 @brief definitions of an concrete parser-class to realise a combination of
        at least 2 other parsers

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
    08.03.2015     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    08.03.2015...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/
#ifndef TIPA_COMBINATION_H
 #define TIPA_COMBINATION_H




#include "TiPa_Concrete.h"
#include "TiPa_Data.h"

#include <set>
#include<map>
#include<list>



using namespace std;

#ifndef DOXYGEN
#define USING_NAMESPACE using namespace
//namespace TXTDIASM {
//namespace TDA_TinyParser {
////namespace CL_TIPA_CONCRETE {
//namespace CL_TIPA {
#endif //DOXYGEN



//#define IGNORE_UNUSED __attribute__ ((unused))

/// @ingroup UNUSED_DATA
/// @brief avoid compiler warning since the object is not used
/// @{
#define CONST_CHAR_UNUSED           __attribute__ ((unused)) const char
#define TIPA_RESULT_ABSTRACT_UNUSED __attribute__ ((unused)) TiPa_Result_Abstract
/// @}

/*!
@brief definitions of an concrete parser-class to search for a single character
*/
class TiPa_Sequence:public TiPa_Concrete
{

 public:

/// @brief describes type of sequence-parsers
  typedef enum Parser_id
  {
   Seq_Default   =  0, ///< parser of binary or sequence operator
   Seq_Seprt     =  1, ///< next part detection of table-part (%)
   Seq_SftSq     =  2, ///< next part detection of sequence-part (||)
   Seq_HrdSq     =  3, ///< next part detection of sequence-part (&&) or (>>)
   Seq_NotValide = -1, ///< not valid sequence
  }Parser_id;


/// @brief describes one of several details of behaviour
  typedef enum ParserDirective
  {
   PrDr_Default,              ///< not specified behaviour
   PrDr_First,                ///< or decisions take the first match
   PrDr_Last,                 ///< or decisions take the last match
   PrDr_Shortest,             ///< or decisions take the shortest match
   PrDr_Longest,              ///< or decisions take the longest match
  }ParserDirective;





/*!
 @brief default constructor

 @htmlinclude ./des/TiPa_Sequence_TiPa_Sequence.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    08.03.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 explicit TiPa_Sequence(DataModel* contextModel);






/*!
 @brief constructor to parse for one Character out of a set of characters

 @param parser0    first  contractor-parser
 @param parser1    second contractor-parser
 @param type       identifier of concrete parser-type


 @htmlinclude ./des/TiPa_Sequence_TiPa_Sequence.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    08.03.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 TiPa_Sequence(TiPa_Concrete* parser0,
               TiPa_Concrete* parser1,
               DataModel*     contextModel,
               Parser_id      type = Seq_Default);






/*!
 @brief constructor to parse for special combinations of sub-parsers

 @param operation  id of the special combination of contractor-parsers
 @param parser0    first  contractor-parser
 @param parser1    second contractor-parser
 @param directive  describes one of several details of behaviour


 @htmlinclude ./des/TiPa_Sequence_TiPa_Sequence.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    08.03.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 TiPa_Sequence(Parser_id        operation,
               TiPa_Concrete*   parser0,
               TiPa_Concrete*   parser1,
               DataModel*       contextModel,
               ParserDirective  directive = PrDr_Default);






/*!
 @brief destructor

 @htmlinclude "TiPa_Sequence__TiPa_Sequence.html"
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    08.03.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  virtual ~TiPa_Sequence(void);



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
inline TiPa_Sequence* as_TiPa_Sequence(void)override{return(this);};

/*!
 @brief cast this object to an object of the type @ref TiPa_Counter

 @return a pointer to a real existing object if conversion is possible
 @return nullptr if object could not be converted

*/
inline TiPa_Counter* as_TiPa_Counter(void)override{return(nullptr);};





/*!
 @brief initialize to parse for sequence of sub-parsers

 @param operation  id of the special combination of contractor-parsers
 @param parser0    first  contractor-parser
 @param parser1    second contractor-parser
 @param directive  describes one of several details of behaviour

 @return reference to this sequence

 @htmlinclude ./des/TiPa_Sequence_init.html
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
TiPa_Sequence*  init(Parser_id       operation,
                     TiPa_Concrete*  parser0,
                     TiPa_Concrete*  parser1,
                     ParserDirective directive = PrDr_Default);



/*!
 @brief initialize to parse for hard sequence of sub-parsers

 @param parser    first  contractor-parser
 @param directive  describes one of several details of behaviour

 @return reference to this extended sequence

 @htmlinclude ./des/TiPa_Sequence_hard.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    16.10.2016   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 TiPa_Sequence* hard(TiPa_Concrete*  parser0,
                     TiPa_Concrete*  parser1,
                     ParserDirective directive = PrDr_Default);


/*!
 @brief initialize to parse for soft sequence of sub-parsers

 @param parser    first  contractor-parser
 @param parser1    second contractor-parser

 @return reference to this extended sequence

 @htmlinclude ./des/TiPa_Sequence_soft.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    16.10.2016   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 TiPa_Sequence* soft(TiPa_Concrete*  parser0,
                     TiPa_Concrete*  parser1,
                     ParserDirective directive = PrDr_Default);


/*!
 @brief initialize to parse for table sequence of sub-parsers

 @param parser     first  contractor-parser
 @param separator  separating contractor-parser
 @param directive  describes one of several details of behaviour

 @return reference to this extended sequence

 @htmlinclude ./des/TiPa_Sequence_table.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    16.10.2016   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 TiPa_Sequence* table(TiPa_Concrete*  parser,
                      TiPa_Concrete*  separator,
                      ParserDirective directive = PrDr_Default);








/*!
 @brief extend a sequence of sub-parsers by adding one more at the end of the sequence

 @warning this makes only sense for hard and soft sequences

 @param parser    next  contractor-parser


 @htmlinclude ./des/TiPa_Sequence_include.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    15.10.2016   @I  Eckard Klotz
 @I extension of the design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
void include(TiPa_Concrete*  parser);



/*!
 @brief extend a sequence of sub-parsers by adding one more at the end of the sequence

 @warning this makes only sense for hard sequences

 @param parser    next contractor-parser

 @return reference to this extended sequence

 @htmlinclude ./des/TiPa_Sequence_hard.html
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
 TiPa_Sequence* hard(TiPa_Concrete*  parser);



/*!
 @brief extend a sequence of sub-parsers by adding one more at the end of the sequence

 @warning this makes only sense for soft sequences

 @param parser    next  contractor-parser

 @return reference to this extended sequence

 @htmlinclude ./des/TiPa_Sequence_soft.html
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
 TiPa_Sequence* soft(TiPa_Concrete*  parser);















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



 @htmlinclude ./des/TiPa_Sequence_parser_Test.html
 @I_______________________________________________________
    08.03.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 const char* parser_Test(const char* begin, const char* end, TiPa_Result_Abstract* sponsorGuard = nullptr) override;





 /*!

 @brief compare if given parser has the same type and the same configuration

 @note different parser-types may be configured in a way that they do the same
       but this will not be tested here
 @note if contractor-parsers are equal but not the same instance this and the given
       parser will be treated as not equal

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
 test the given string described with its begin and end to
 decide, if it starts with a construction, defined by the operation of given
 contractor parsers,
 the detection of a table-Line ( Spirit 1.8 operator A % B) is a match a list
 of one or more repetitions of A separated by occurrences of B.
 This is the same as A >> *(B >> A).

 @param [in]  begin       points to the first character of the given string
 @param [in]  end         points behind the last character of the given string
 @param [out] contractor  container that stores references to hits of contractor-parsers

 @return a pointer directly behind the found match if the given string starts
         with the construction defined by the sub parser and its combination.
 @return nullptr if the given string starts not
         with the construction defined by the parser  and its combination



 @htmlinclude ./des/TiPa_Sequence_parser_Test_Seprt.html
 @I_______________________________________________________
    08.03.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 const char* parser_Test_Seprt(const char*           begin,
                               const char*           end,
                               TiPa_Result_Abstract* sponsorGuard);








/*!
 test the given string described with its begin and end to
 decide, if it starts with a construction, defined by the operation of given
 contractor parsers,
 the detection of  sequential-or operation ( Spirit 1.8 operator A || B)
 reads as match A or B and in sequence, that is, if both A and B match,
 it must be in sequence; this is equivalent to (A >> !B) | (B),
 May be understood as a sequence where single parts are allowed to be not be available


 @param [in]  begin       points to the first character of the given string
 @param [in]  end         points behind the last character of the given string
 @param [out] contractor  container that stores references to hits of contractor-parsers

 @return a pointer directly behind the found match if the given string starts
         with the construction defined by the sub parser and its combination.
 @return nullptr if the given string starts not
         with the construction defined by the parser  and its combination



 @htmlinclude ./des/TiPa_Sequence_parser_Test_SftSq.html
 @I_______________________________________________________
    08.03.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 const char* parser_Test_SftSq(const char*           begin,
                               const char*           end,
                               TiPa_Result_Abstract* sponsorGuard);








/*!
 test the given string described with its begin and end to
 decide, if it starts with a construction, defined by the operation of given
 contractor parsers,
 the detection of a sequence ( Spirit 1.8 operator  A && B && C or A >> B >> C )
 expects that the given chain of contractor-parsers follow in the order defined by
 the operand id

 @param [in]  begin       points to the first character of the given string
 @param [in]  end         points behind the last character of the given string
 @param [out] contractor  container that stores references to hits of contractor-parsers

 @return a pointer directly behind the found match if the given string starts
         with the construction defined by the sub parser and its combination.
 @return nullptr if the given string starts not
         with the construction defined by the parser  and its combination



 @htmlinclude ./des/TiPa_Sequence_parser_Test_HrdSq.html
 @I_______________________________________________________
    08.03.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 const char* parser_Test_HrdSq(const char*           begin,
                               const char*           end,
                               TiPa_Result_Abstract* sponsorGuard);








/*!
 test the given string described with its begin and end to
 decide, if it starts with a construction, defined by the operation of given
 contractor parsers,
 the default-behaviour is currently not defined and thus thus operation
 fails currently

 @param [in]  begin       points to the first character of the given string
 @param [in]  end         points behind the last character of the given string
 @param [out] contractor  container that stores references to hits of contractor-parsers

 @return a pointer directly behind the found match if the given string starts
         with the construction defined by the sub parser and its combination.
 @return nullptr if the given string starts not
         with the construction defined by the parser  and its combination



 @htmlinclude ./des/TiPa_Sequence_parser_Test_Default.html
 @I_______________________________________________________
    08.03.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 const char* parser_Test_Default(CONST_CHAR_UNUSED*           begin,
                                 CONST_CHAR_UNUSED*           end,
                                 TIPA_RESULT_ABSTRACT_UNUSED* storage);















/*!
  @brief Mbr.ibutes of class
 */
  struct Mbr
  {
   ParserDirective   Dircetive;      ///< @brief describes one of several details of behaviour
   set<const char*>  AlreadyCalled;  ///< @brief to detect recursive calls of a rule

   /// @brief default constructor
   Mbr(void):
    Dircetive    (PrDr_Default)
   {};
   /*!
    @brief copy constructor
    @param [in] src object to copy
   */
   Mbr(const Mbr& src):
    Dircetive    (src.Dircetive    ),
    AlreadyCalled(src.AlreadyCalled)
   {};
   /*!
    @brief assignment operator
    @param [in] src object to copy
    @return copied object
   */
   Mbr& operator = (const Mbr& src)
   {
    Dircetive     = src.Dircetive    ;
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





//}; USING_NAMESPACE CL_TIPA;


//namespace CL_TIPA {

/*!
@brief  definitions of an concrete parser-class to search for a text-part that follows a conditional combination of parsers
*/
class TiPa_Condition:public TiPa_Concrete
{

 public:

/// @brief describes the types of condition parsers
  typedef enum Parser_id
  {
   Cnd_Default   =  0, ///< parser of binary or sequence operator
   Cnd_OrExc     =  1, ///< next part detection of exclude-or (^)
   Cnd_OrInc     =  2, ///< next part detection of inclusive-or (|)
   Cnd_And       =  3, ///< next part detection of and (&)
   Cnd_WthOt     =  4, ///< next part detection of without (-)
   Cnd_NotValide = -1, ///< not valid condition

  }Parser_id;


  typedef enum ParserDirective
  {
   PrDr_Default,              ///< not specified behaviour
   PrDr_First,                ///< or decisions take the first match
   PrDr_Last,                 ///< or decisions take the last match
   PrDr_Shortest,             ///< or decisions take the shortest match
   PrDr_Longest,              ///< or decisions take the longest match
  }ParserDirective;





/*!
 @brief default constructor

 @htmlinclude ./des/TiPa_Condition_TiPa_Condition.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    08.03.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 explicit TiPa_Condition(DataModel* contextModel);






/*!
 @brief constructor to parse for one Character out of a set of characters

 @param parser0    first  contractor-parser
 @param parser1    second contractor-parser
 @param type       identifier of concrete parser-type


 @htmlinclude ./des/TiPa_Condition_TiPa_Condition.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    08.03.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 TiPa_Condition(TiPa_Concrete*                        parser0,
                TiPa_Concrete*                        parser1,
                DataModel* contextModel,
                Parser_id                             type = Cnd_Default);






/*!
 @brief constructor to parse for special combinations of sub-parsers

 @param operation  id of the special combination of contractor-parsers
 @param parser0    first  contractor-parser
 @param parser1    second contractor-parser
 @param directive  describes one of several details of behaviour


 @htmlinclude ./des/TiPa_Condition_TiPa_Condition.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    08.03.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 TiPa_Condition(Parser_id                             operation,
                TiPa_Concrete*                        parser0,
                TiPa_Concrete*                        parser1,
                DataModel* contextModel,
                ParserDirective                       directive = PrDr_Default);






/*!
 @brief destructor

 @htmlinclude "TiPa_Condition__TiPa_Condition.html"
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    08.03.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  virtual ~TiPa_Condition(void);




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
inline TiPa_Condition* as_TiPa_Condition(void)override{return(this);};

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
 @brief initialize to parse for special combinations of sub-parsers

 @param operation  id of the special combination of contractor-parsers
 @param parser0    first  contractor-parser
 @param parser1    second contractor-parser
 @param directive  describes one of several details of behaviour

 @return reference to this sequence

 @htmlinclude ./des/TiPa_Condition_init.html
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
TiPa_Condition*  init(Parser_id       operation,
                      TiPa_Concrete*  parser0,
                      TiPa_Concrete*  parser1,
                      ParserDirective directive = PrDr_Default);





/*!
 @brief initialize to parse for an inclusion combination of sub-parsers

 @param parser0    first  contractor-parser
 @param parser1    second contractor-parser
 @param directive  describes one of several details of behaviour

 @return reference to this extended condition

 @htmlinclude ./des/TiPa_Condition_inclusion.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    16.10.2016   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 TiPa_Condition* inclusion(TiPa_Concrete*  parser0,
                           TiPa_Concrete*  parser1,
                           ParserDirective directive = PrDr_Default);


/*!
 @brief initialize to parse for an inclusive or combination of sub-parsers

 @param parser0    first  contractor-parser
 @param parser1    second contractor-parser
 @param directive  describes one of several details of behaviour

 @return reference to this extended condition

 @htmlinclude ./des/TiPa_Condition_or.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    16.10.2016   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 TiPa_Condition* incOr(TiPa_Concrete*  parser0,
                       TiPa_Concrete*  parser1,
                       ParserDirective directive = PrDr_Default);


/*!
 @brief initialize to parse for an exclusive or combination of sub-parsers

 @param parser0    first  contractor-parser
 @param parser1    second contractor-parser
 @param directive  describes one of several details of behaviour

 @return reference to this extended condition

 @htmlinclude ./des/TiPa_Condition_exOr.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    16.10.2016   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 TiPa_Condition* exOr(TiPa_Concrete*  parser0,
                      TiPa_Concrete*  parser1,
                      ParserDirective directive = PrDr_Default);

/*!
 @brief initialize to parse for exclusion of sub-parsers

 @param parser0    first  contractor-parser
 @param parser1    second contractor-parser
 @param directive  describes one of several details of behaviour

 @return reference to this extended condition

 @htmlinclude ./des/TiPa_Condition_exclusion.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    16.10.2016   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 TiPa_Condition* exclusion(TiPa_Concrete*  parser,
                           TiPa_Concrete*  without,
                           ParserDirective directive = PrDr_Default);





/*!
 @brief extend a conditional combination of sub-parsers by adding one more

 @warning this makes no sense for the exclusion

 @param parser    next  contractor-parser


 @htmlinclude ./des/TiPa_Condition_include.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    15.10.2016   @I  Eckard Klotz
 @I extension of the design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
void include(TiPa_Concrete*  parser);






/*!
 @brief extend an inclusion combination of sub-parsers by adding one more

 @warning this makes only sense if the condition is initialized as inclusion

 @param parser    next  contractor-parser

 @return reference to this extended condition

 @htmlinclude ./des/TiPa_Condition_inclusive.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    15.10.2016   @I  Eckard Klotz
 @I extension of the design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 TiPa_Condition* inclusive(TiPa_Concrete*  parser);


/*!
 @brief extend an inclusive or combination of sub-parsers by adding one more

 @warning this makes only sense if the condition is initialized as inclusive or

 @param parser    next  contractor-parser

 @return reference to this extended condition

 @htmlinclude ./des/TiPa_Condition_or.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    15.10.2016   @I  Eckard Klotz
 @I extension of the design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 TiPa_Condition* incOr(TiPa_Concrete*  parser);


/*!
 @brief extend an exclusive or combination of sub-parsers by adding one more

 @warning this makes only sense if the condition is initialized as exclusive or

 @param parser    next  contractor-parser

 @return reference to this extended condition

 @htmlinclude ./des/TiPa_Condition_exOr.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    15.10.2016   @I  Eckard Klotz
 @I extension of the design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 TiPa_Condition* exOr(TiPa_Concrete*  parser);








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



 @htmlinclude ./des/TiPa_Condition_parser_Test.html
 @I_______________________________________________________
    08.03.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 const char* parser_Test(const char* begin, const char* end, TiPa_Result_Abstract* sponsorGuard = nullptr) override;





 /*!

 @brief compare if given parser has the same type and the same configuration

 @note different parser-types may be configured in a way that they do the same
       but this will not be tested here
 @note if contractor-parsers are equal but not the same instance this and the given
       parser will be treated as not equal

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
 test the given string described with its begin and end to
 decide, if it starts with a construction, defined by the operation of given
 contractor parsers,
 the detection of detection of exclude-or ( Spirit 1.8 operator A ^ B)
 match A or B, but not both.

 @param [in]  begin       points to the first character of the given string
 @param [in]  end         points behind the last character of the given string
 @param [in]  storage     memorizing the parser result
 @param [out] contractor  container that stores references to hits of contractor-parsers

 @return a pointer directly behind the found match if the given string starts
         with the construction defined by the sub parser and its combination.
 @return nullptr if the given string starts not
         with the construction defined by the parser  and its combination



 @htmlinclude ./des/TiPa_Condition_parser_TestOrExc.html
 @I_______________________________________________________
    08.03.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 const char* parser_Test_OrExc(const char*           begin,
                               const char*           end,
                               TiPa_Result_Abstract* sponsorGuard);







/*!
 test the given string described with its begin and end to
 decide, if it starts with a construction, defined by the operation of given
 contractor parsers,
 the detection of inclusive-or ( Spirit 1.8 operator A | B) match a or b

 @param [in]  begin       points to the first character of the given string
 @param [in]  end         points behind the last character of the given string
 @param [in]  storage     memorizing the parser result
 @param [out] contractor  container that stores references to hits of contractor-parsers

 @return a pointer directly behind the found match if the given string starts
         with the construction defined by the sub parser and its combination.
 @return nullptr if the given string starts not
         with the construction defined by the parser  and its combination



 @htmlinclude ./des/TiPa_Condition_parser_Test_OrInc.html
 @I_______________________________________________________
    08.03.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 const char* parser_Test_OrInc(const char*           begin,
                               const char*           end,
                               TiPa_Result_Abstract* sponsorGuard);








/*!
 test the given string described with its begin and end to
 decide, if it starts with a construction, defined by the operation of given
 contractor parsers,
 the detection of detection of and ( Spirit 1.8 operator  A & B) match A and B

 @param [in]  begin       points to the first character of the given string
 @param [in]  end         points behind the last character of the given string
 @param [in]  storage     memorizing the parser result
 @param [out] contractor  container that stores references to hits of contractor-parsers

 @return a pointer directly behind the found match if the given string starts
         with the construction defined by the sub parser and its combination.
 @return nullptr if the given string starts not
         with the construction defined by the parser  and its combination



 @htmlinclude ./des/TiPa_Condition_parser_Test_And.html
 @I_______________________________________________________
    08.03.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 const char* parser_Test_And(const char*           begin,
                             const char*           end,
                             TiPa_Result_Abstract* sponsorGuard);








/*!
 test the given string described with its begin and end to
 decide, if it starts with a construction, defined by the operation of given
 contractor parsers,
 the detection of detection of without ( Spirit 1.8 operator A - B)
 match A but not B. If both match and B's matched text is shorter
 than A's matched text, a successful match is made

 @param [in]  begin       points to the first character of the given string
 @param [in]  end         points behind the last character of the given string
 @param [in]  storage     memorizing the parser result
 @param [out] contractor  container that stores references to hits of contractor-parsers

 @return a pointer directly behind the found match if the given string starts
         with the construction defined by the sub parser and its combination.
 @return nullptr if the given string starts not
         with the construction defined by the parser  and its combination



 @htmlinclude ./des/TiPa_Condition_parser_Test_WthOt.html
 @I_______________________________________________________
    08.03.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 const char* parser_Test_WthOt(const char*           begin,
                               const char*           end,
                               TiPa_Result_Abstract* sponsorGuard);








/*!
 test the given string described with its begin and end to
 decide, if it starts with a construction, defined by the operation of given
 contractor parsers,
 the default-behaviour is currently not defined and thus thus operation
 fails currently

 @param [in]  begin       points to the first character of the given string
 @param [in]  end         points behind the last character of the given string
 @param [out] contractor  container that stores references to hits of contractor-parsers

 @return a pointer directly behind the found match if the given string starts
         with the construction defined by the sub parser and its combination.
 @return nullptr if the given string starts not
         with the construction defined by the parser  and its combination



 @htmlinclude ./des/TiPa_Condition_parser_Test_Default.html
 @I_______________________________________________________
    08.03.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 const char* parser_Test_Default(CONST_CHAR_UNUSED*            begin,
                                 CONST_CHAR_UNUSED*            end,
                                 TIPA_RESULT_ABSTRACT_UNUSED*  storage);















/*!
 @brief Mbr.ibutes of class
 */
  struct Mbr
  {
   ParserDirective   Dircetive;      ///< @brief describes one of several details of behaviour
   set<const char*>  AlreadyCalled;  ///< @brief to detect recursive calls of a rule

   /// @brief default constructor
   Mbr(void):
    Dircetive    (PrDr_Default)
   {};
   /*!
    @brief copy constructor
    @param [in] src object to copy
   */
   Mbr(const Mbr& src):
    Dircetive    (src.Dircetive    ),
    AlreadyCalled(src.AlreadyCalled)
   {};
   /*!
    @brief assignment operator
    @param [in] src object to copy
    @return copied object
   */
   Mbr& operator = (const Mbr& src)
   {
    Dircetive     = src.Dircetive    ;
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
//}; USING_NAMESPACE CL_TIPA;
//}; USING_NAMESPACE CL_TIPA_CONCRETE;
//}; USING_NAMESPACE TDA_TinyParser;
//}; USING_NAMESPACE TXTDIASM;
#undef  USING_NAMESPACE
#endif //DOXYGEN




#endif //TIPA_COMBINATION_H
