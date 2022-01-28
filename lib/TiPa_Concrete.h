/*!

 @file
 @brief definitions of an concrete parser-class as template
        for tiny parser classes

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
    07.02.2015     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    07.02.2015...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/
#ifndef TIPA_CONCRETE_H
 #define TIPA_CONCRETE_H



#include "TiPa_Abstract.h"

//#include "AssociationSponsor.hpp"
#include "TiPa_Reaction_Abstract.h"

#include "TiPa_Result_Abstract.h"

#include "TiPa_Data.h"
#include "ASS_Model.hpp"


#include <map>
#include <set>
#include <list>

#include <stdio.h>


using namespace std;

#ifndef DOXYGEN
//namespace TXTDIASM {
//namespace TDA_TinyParser {
////namespace CL_TIPA_CONCRETE {
#endif //DOXYGEN


class TiPa_Concrete:public TiPa_Abstract
{
/*
 friend class TiPa_Character;
 friend class TiPa_String;
 friend class TiPa_Counter;
 friend class TiPa_Character;
*/

 public:





 static const bool PHRASED    = true;
 static const bool NOTPHRASED = false;

 typedef Association<TiPa_Data*, nullptr>           DataAssociation;
 typedef AssociationFellowship<TiPa_Data*, nullptr> DataFellow;
 typedef AssociationSponsor<TiPa_Data*, nullptr>    DataSponsor;
 typedef AssociationModel<TiPa_Data, nullptr>       DataModel;
 typedef map<int,TiPa_Concrete*> ContractorParserDictionary;

 typedef TiPa_Result_Abstract::Data_TP Hit_TP;


 /*!
 @brief default constructor
 <br><br>
 @htmlinclude ./des/TiPa_Concrete_TiPa_Concrete.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    28.02.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 explicit TiPa_Concrete(DataModel* contextModel);




 /*!
 @brief constructor used by derived classes to initialize manager attributes

 @param contextModel identifier of parser-type
 @param type         identifier of parser-type
 @param maxOperand   allowed maximum of operand identifier


 <br><br>
 @htmlinclude ./des/TiPa_Concrete_TiPa_Concrete.html
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
 TiPa_Concrete(DataModel* contextModel,
               int        type,
               int        maxOperand = -1);







 /*!
 @brief destructor

 @htmlinclude ./des/TiPa_ConcreteTiPa_Concrete
  @I_______________________________________________________
    28.02.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  virtual ~TiPa_Concrete(void);


/*!
 @brief cast this object to an object of the type @ref TiPa_Concrete

 @return a pointer to a real existing object if conversion is possible
 @return nullptr if object could not be converted

*/
inline TiPa_Concrete* as_TiPa_Concrete(void)override{return(this);};

/*!
 @brief cast this object to an object of the type @ref TiPa_Character

 @return a pointer to a real existing object if conversion is possible
 @return nullptr if object could not be converted

*/
inline virtual TiPa_Character* as_TiPa_Character(void)override{return(nullptr);};

/*!
 @brief cast this object to an object of the type @ref TiPa_String

 @return a pointer to a real existing object if conversion is possible
 @return nullptr if object could not be converted

*/
inline virtual TiPa_String* as_TiPa_String(void)override{return(nullptr);};

/*!
 @brief cast this object to an object of the type @ref TiPa_Rule

 @return a pointer to a real existing object if conversion is possible
 @return nullptr if object could not be converted

*/
inline virtual TiPa_Rule* as_TiPa_Rule(void)override{return(nullptr);};

/*!
 @brief cast this object to an object of the type @ref TiPa_Condition

 @return a pointer to a real existing object if conversion is possible
 @return nullptr if object could not be converted

*/
inline virtual TiPa_Condition* as_TiPa_Condition(void)override{return(nullptr);};

/*!
 @brief cast this object to an object of the type @ref TiPa_Sequence

 @return a pointer to a real existing object if conversion is possible
 @return nullptr if object could not be converted

*/
inline virtual TiPa_Sequence* as_TiPa_Sequence(void)override{return(nullptr);};

/*!
 @brief cast this object to an object of the type @ref TiPa_Counter

 @return a pointer to a real existing object if conversion is possible
 @return nullptr if object could not be converted

*/
inline virtual TiPa_Counter* as_TiPa_Counter(void)override{return(nullptr);};



 /*!
 @brief initialize the parser

 @param type        identifier of parser-type



<br><br>
 @htmlinclude ./des/TiPa_Concrete_init.html
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
 void init(TiPa_ID type);




/*!
 @brief return the kind of parser class

 @return parser class identifying number

<br><br>
 @htmlinclude ./des/TiPa_Concrete_id_Class.html
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

<br><br>
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
 @brief return the kind of parser type identifier

 @return parser type identifying number

<br><br>
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
 virtual int id_SubType(void) override;




/*!
 @brief set a parser that defines a text-part in the text to parse that should be
 ignored

 @param [in] parser   parser to identify text-parts to be ignored before
                      the match

 @htmlinclude ./des/TiPa_Concrete_skip_ParserSet.html


 <br><br>
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
 void skip_ParserSet(TiPa_Concrete* parser);


/*!
 @brief get the parser that defines a text-part in the text to parse that should be
 ignored

 @return parser to identify text-parts to be ignored before the match
 <br>    or nullptr if a skip-parser is not defined

 @htmlinclude ./des/TiPa_Concrete_skip_ParserGet.html

 <br><br>
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    07.08.2016   @I  Eckard Klotz
 @I implementation of debug outputs
 @I adding this method
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 TiPa_Concrete* skip_ParserGet(void);




/*!
 @brief test the given string described with its begin and end to
 decide if it starts with a construction that should be ignored.

 @param [in] begin        points to the first character of the given string
 @param [in] end          points behind the last  character of the given string

 @return a pointer directly behind the found match if the given string starts
         with the construction defined by the own skip-Parser.
 @return given <b>begin</b> if the given string starts not
         with the construction defined by the own skip-Parser


 <br><br>
 @htmlinclude ./des/TiPa_Concrete_skip_parsing.html
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
 const char * skip_parsing(const char* begin, const char* end);




/*!
 value for @ref contractor_ParserInsert parameter operand to force an
 insertion as next contractor-parser.
*/
 enum ParserInsert
 {
  InsertNext = -1,
 };
/*!
 @brief insert a contractor-parser

 @param [in] contractorParser  specific sub-parser
 @param [in] operand           identifier of the operand that specifies the special
                               meaning of the sub-parser while this parser-operation
 <br>                          the use of @ref InsertNext forces an insertion as last
                               operand of the current chain of operands

 @return true  if parser is possible to insert
 <br>    false if parsers is not allowed to be used as sub-parser for the this parser


 <br><br>
 @htmlinclude ./des/TiPa_Concrete_contractor_ParserInsert.html
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
 bool contractor_ParserInsert(TiPa_Concrete* contractorParser, int operand = 0);


/*!
 @brief get a map of the contractor-parsers

 @return a map with an operand used as key and the contractorParsers used as data
 <br> operand           identifier of the operand that specifies the special
                        meaning of the sub-parser while this parser-operation
 <br> contractorParser  specific sub-parser


 @htmlinclude ./des/TiPa_Concrete_contractor_ParserGet.html

 <br><br>
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    07.08.2016   @I  Eckard Klotz
 @I implementation of debug outputs
 @I adding this method
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 map<int, TiPa_Concrete*> contractor_ParserGet(void);


/*!
 @brief return number of already defined contractor parsers

 @note primitive parsers, character and string parsers will return
       always 0. depending on the functionality of other parsers
       they may have a specific maximum number or case depending
       number of contractor parsers.

 @return 1 or more if    contractor parser are defined
 <br>    0         if no contractor parser is  defined

 @htmlinclude ./des/TiPa_Concrete_contractor_ParserGet.html

 <br><br>
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    07.08.2016   @I  Eckard Klotz
 @I implementation of debug outputs
 @I adding this method
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
int contractor_ParserCounter(void);



/// @brief memorizing the parser result
typedef enum ResultStoring_TP
{
 ResultStore,  /// @brief parser-result will be stored for later analysis
 ResultSkip,   /// @brief parser result will be not stored
}ResultStoring_TP;

/*!
 test the given string described with its begin and end to
 decide if it starts with a construction defined by the parser,
 a hit will be stored inside the parser and reused to save time.

 @param [in] begin         points to the first character of the given string
 @param [in] end           points behind the last  character of the given string
 @param [in] storage       memorizing the parser result

 @return a pointer directly behind the found match if the given string starts
         with the construction defined by the parser.
 @return nullptr if the given string starts not
         with the construction defined by the parser


 @htmlinclude ./des/TiPa_Concrete_parser_Test.html

 <br><br>
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    28.02.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual const char * parser_Test(const char* begin, const char* end, TiPa_Result_Abstract* sponsorGuard = nullptr) = 0;


/*!
 test the given string described with its begin and end to
 decide if it contains somewhere a construction defined by the parser,
 a hit will be stored inside the parser and reused to save time.

 @param [out] begin points to the first character of the given string
         <br> once the first fitting part-string was found this parameter points
              to its first character
 @param [in]  end   points behind the last  character of the given string

 @return a value behind the given <b>begin</b> and before the given <b>end</b> that
         points directly to the first part of the given string that hits the
         construction of the parser.
 @return the value of the given <b>end</b> if the given string contains no
         with the construction defined by the parser
 @return nullptr in the case of an error or special event


 <br><br>

 @htmlinclude ./des/TiPa_Concrete_parser_Search.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    28.02.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 const char * parser_Search(const char* begin, const char* end);





 typedef enum ParserScanMode_TP
 {
  OverlappingScan = true,
  SequentialScan  = false,
 }ParserScanMode_TP ;

/*!
 test the given string described with its begin and end to
 decide if it contains one or more constructions defined by the parser,
 all hits will be stored inside the parser and reused to save time.

 @param [in out] begin points to the first character of the given string
         <br>          once the first fitting part-string was found this parameter points
                       to its first character
 @param [in]  end      points behind the last character of the given string
 @param [in]  overlap  OverlappingScan =>  restart the parsing with every character every,
                                           thus found results may overlap each other
     <br>              SequentialScan => restart the parsing not inside a text-part that was
                                         already detected as a hit before but behind them,
                                         thus found results will not overlap each other

 @return a value behind the given <b>begin</b>  and before the given <b>end</b> that
         points directly to the last part of the given string that hits the
         construction of the parser.
 @return the value of the given <b>end</b> if the given string contains no
         with the construction defined by the parser
 @return nullptr in the case of an error or special event


 @htmlinclude ./des/TiPa_Concrete_parser_Scan.html

 <br><br>
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    28.02.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 const char* parser_Scan(const char* begin, const char* end, ParserScanMode_TP overlap = OverlappingScan);




/*!
 return the parser-result dictionary that contains all hits
 found while all calls of the parser-methods like @ref parser_Hit,
 @ref TiPa_Concrete::parser_Search and @ref TiPa_Concrete::parser_Scan


 @return dictionary of information about all results of the parser
         without valid data about the result of its sub-parsers


 <br><br>
 @htmlinclude ./des/TiPa_Concrete_result_Dictionary.html
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
// map<const char*, TiPa_Concrete::DataSponsor* >* result_Dictionary(void);
 map<const char*, Hit_TP >* result_Dictionary(void);






/*!
 @brief return the parser-result associated with the given string-position

 @param [in] begin points to the first character of the result if known

 @return information about the result of the parser without valid data
         about the result of its sub-parsers


 <br><br>
 @htmlinclude ./des/TiPa_Concrete_result_HitCopy.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    01.09.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
TiPa_Concrete::DataSponsor result_HitCopy(const char* begin=nullptr);





/*!
 @brief return a reference to the parser-result associated with the given string-position

 @param [in] begin points to the first character of the result if known

 @return pointer to the result of the parser


 <br><br>
 @htmlinclude ./des/TiPa_Concrete_result_Hit.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    01.09.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
//TiPa_Concrete:: DataSponsor* result_Hit(const char* begin=nullptr);
Hit_TP*  result_Hit(const char* begin=nullptr);









/*!
 @brief return the parser-tree

 @param [in] begin points to the first character of the result if known

 @return information about the result of the parser together with valid data
         about the result of its sub-parsers and their sub-parsers


 <br><br>
 @htmlinclude ./des/TiPa_Concrete_result_Tree.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    01.09.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
Hit_TP* result_Tree(const char* begin=nullptr);



/*!
 @brief output a copy of the result-text

 @param [out] text  provided buffer array to copy the result-text in.
                    if text is a nullptr pointer the function allocates the needed buffer but
                    the user is responsible to delete it correctly to prevent runtime-errors
 @param [in]  size  length of the provided buffer array if given text is no nullptr pointer.
                    if given text is a nullptr pointer size will be ignored.
 @param [in]  begin points to the first character of the result if known

 @return pointer to result-text, in the case that the given text was just a pointer to nullptr
         the function return is the only possibility to access the result since the parameter text
         is after leaving the function again a pointer to nullptr
 <br><br>
 @htmlinclude ./des/TiPa_Concrete_result_Text.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    28.02.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 char* result_Text(char* text = nullptr, int size = -1, const char* begin = nullptr);




/*!
 @brief clear the whole collected result from earlier tests

 <br><br>
 @htmlinclude ./des/TiPa_Concrete_result_clear.html
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
 void result_clear(void);


/*!

 @brief compare if given parser has the same type and the same configuration

 @note different parser-types may be configured in a way that they do the same
       but this will not be tested here

 @param [in] parser object to compare this parser with

 @return true  if given parser has the same type and configuration
 <br>    false if given parser differs in type or configuration

 <br><br>
 @htmlinclude ./des/TiPa_Concrete_equal_Parser.html
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
 virtual bool equal_Parser(TiPa_Concrete* parser) = 0;


/*!

 @brief set the context-model that is responsible to create result data-objects

 @param contextModel [in] manages the creation, storing and destruction of
                          associations and their data-objects


 <br><br>
 @htmlinclude ./des/TiPa_Concrete_contextModel_set.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    27.04.2016   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
void contextModel_set(DataModel* contextModel);



/*!
 @brief return the context-model that is responsible to create result data-objects

 @return currently set context-model as a reference

 @htmlinclude ./des/TiPa_Concrete_contextModel_get.html
*/
TiPa_Concrete::DataModel* contextModel_get(void);




/*!

 @brief set the user defined reaction for a parser hit

 @param reaction [in]  reaction object


 <br><br>
 @htmlinclude ./des/TiPa_Concrete_reactionHit_set.html
*/
void  reactionHit_set(TiPa_Reaction_Abstract* reaction);


/// @brief parser-result storage-types
typedef enum ResultStorage_TP
{
 ResStore_Default,            /// @brief  store every single result
 ResStore_CollectTerminals,   /// @brief  store only the results of character-, string- and rule parsers of directly or indirectly called sub-parsers
 ResStore_Terminate,          /// @brief  provide a calling parser the own result as a leaf-result
 ResStore_Skip,               /// @brief  provide a calling parser just the hit but no result-details
 ResStore_NV,                 /// @brief  no valid user-configuration
}ResultStorage_TP;


/*!
 @brief adjust how to store the parser-result

 @param mode [in] type of storage

 @htmlinclude ./des/TiPa_Concrete_resultStorage_Set.html
*/
inline void resultStorage_Set(ResultStorage_TP mode)
/* @MRTZ_describe resultStorage_Set
 just store the parameter
*/
{
 Storage.StorageType = mode;
}


/*!
 @brief return how to store the parser-result

 @return type of storage

 @htmlinclude ./des/TiPa_Concrete_resultStorage_Get.html
*/
inline ResultStorage_TP  resultStorage_Get(void)
/* @MRTZ_describe resultStorage_Get
 just return the atrribute-value
*/
{
 return(Storage.StorageType);
}








/*!
 @brief return last hit begin

 @return pointer to first character of the last parse result

 @htmlinclude ./des/TiPa_Concrete_currentBegin.html
*/
const char* currentBegin(void);

/*!
 @brief return last hit end

 @return pointer behind last character of the last parse result

 @htmlinclude ./des/TiPa_Concrete_currentEnd.html
*/
const char* currentEnd(void);










/*!
 @brief return type describing string defined for the parser that's part of the data set

 @return the describing string
         or a nullptr pointer if no valid parser is defined



 @htmlinclude ./des/TiPa_Data_typeString
 .html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    04.09.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
const char* typeString(void) override;








 protected:

/*!
 @brief store last hit

 @param begin [in] pointer to first character of the last parse result
 @param end   [in] pointer behind last character of the last parse result
*/
void setCurrentHitLocation(const char* begin, const char* end);



/* !
 @brief define the result storage manager

 @param destination  [in] new local result storage manager
 @param sponsorGuard [in] result storage manager of the calling parser
TiPa_Result_Abstract* defineResultGuard(TiPa_Result_Abstract* sponsorGuard);
*/








/*!
 @brief return end-data of a single  parser-hit

 @param [in] begin          first character of the detected text-part
 @return  pointer directly behind the last character of the detected text-part



 <br><br>
 @htmlinclude ./des/TiPa_Concrete_storeResult.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    01.09.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
const char* endOfHitResult(const char* begin);





 /*!
   Attributes of class
 */
  struct Att
  {
   TiPa_ID                                 SubType;            ///< type of parser

   map<int, TiPa_Concrete*>                ContractorParser;   ///< sub-parsers of operator-parsers and rule-parsers
   int                                     MaxOperand;         ///< allowed maximum of operand identifier

   TiPa_Concrete*                          SkipParser;         ///< to identify text-parts which may be ignored wile parsing

   int                                     RecursiveCalls;     ///< counts the number of method-calls while traversing through sub-parser tree


   DataModel*                              ContextModel;       ///< manages the analysed data

   TiPa_Reaction_Abstract*                 ReactionHit;        ///< user defined reaction for a parser hit

   Att(void):SubType(-1),
             MaxOperand(-1),
             SkipParser(nullptr),
             RecursiveCalls(0),
             ContextModel(nullptr),
             ReactionHit(nullptr){};

   Att(const TiPa_ID&                 subType ,
       const int&                     maxOperand,
             TiPa_Concrete*           skipParser,
       const int&                     recursiveCalls,
             DataModel*               contextModel,
             TiPa_Reaction_Abstract*  reactionHit):
             SubType(       subType),
             MaxOperand(    maxOperand),
             SkipParser(    skipParser),
             RecursiveCalls(recursiveCalls),
             ContextModel(  contextModel),
             ReactionHit(   reactionHit){};

   Att(const Att& original):
             SubType(         original.SubType),
             ContractorParser(original.ContractorParser),
             MaxOperand(      original.MaxOperand),
             SkipParser(      original.SkipParser),
             RecursiveCalls(  original.RecursiveCalls),
             ContextModel(    original.ContextModel),
             ReactionHit(     original.ReactionHit){};

   Att& operator = (const Att& original)
            {
             SubType          = original.SubType;
             ContractorParser = original.ContractorParser;
             MaxOperand       = original.MaxOperand;
             SkipParser       = original.SkipParser;
             RecursiveCalls   = original.RecursiveCalls;
             ContextModel     = original.ContextModel;
             ReactionHit      = original.ReactionHit;
             return(*this);
            };

   ~Att(void)
   {
    ContractorParser.clear();   ///< sub-parsers of operator-parsers and rule-parsers
   };


  }Att;




 /*!
   @brief process memory
 */
  struct Storage
  {
   map<const char*, Hit_TP>                Result;                        ///< @brief dictionary of already known hits from earlier calls
   map<const char*, Hit_TP>::iterator      Current;                       ///< @brief result of test or find
   set<const char*>                        NonHit;                        ///< @brief text parts already known as not fitting from earlier calls

   const char*                             CurrentBegin;                  ///< @brief first character of the last parse result
   const char*                             CurrentEnd;                    ///< @brief behind last character of the last parse result

   ResultStorage_TP                        StorageType{ResStore_Default}; ///< @brief parser-result storage-types

   Storage(void):CurrentBegin(nullptr),
                 CurrentEnd(nullptr),
                 StorageType(ResStore_Default){};


   Storage(const Storage& src):
    Result      (src.Result      ),
    Current     (src.Current     ),
    NonHit      (src.NonHit      ),
    CurrentBegin(src.CurrentBegin),
    CurrentEnd  (src.CurrentEnd  ),
    StorageType (src.StorageType )
   {};

   /*!
    @brief assignment operator
    @param [in] src object to copy
    @return copied object
   */
   Storage& operator = (const Storage& src)
   {
    Result       = src.Result      ;
    Current      = src.Current     ;
    NonHit       = src.NonHit      ;
    CurrentBegin = src.CurrentBegin;
    CurrentEnd   = src.CurrentEnd  ;
    StorageType  = src.StorageType ;
    return(*this);
   };



   ~Storage(void)
   {
    Result.clear();                                                       // dictionary of already known hits from earlier calls
    NonHit.clear();
    Current = Result.end();                                                     // text parts already known as not fitting from earlier calls
   }


  }Storage;

 private:


  static const char* Name[37];                                                     ///< @brief names and short descriptions of TiPa parsers



};



#ifndef DOXYGEN
#define USING_NAMESPACE using namespace
//}; USING_NAMESPACE CL_TIPA_CONCRETE;
//}; USING_NAMESPACE TDA_TinyParser;
//}; USING_NAMESPACE TXTDIASM;
#undef  USING_NAMESPACE
#endif //DOXYGEN




#endif //TIPA_CONCRETE_H
