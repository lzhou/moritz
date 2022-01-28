/*!

 @file
 @brief store the result of a tiny parser object

 Copyright (C) 2019-2020 by Eckard Klotz.

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
    07.02.2019     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    07.02.2019...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/
#ifndef TIPA_RESULT_COLLECTOR_H
 #define TIPA_RESULT_COLLECTOR_H

#include "TiPa_Result.h"

/*!
 @brief store the result of a tiny parser object
*/
class TiPa_Result_Collector: public TiPa_Result
{
 public:
/*!
 @brief constructor to be used by a parser

 @param parser      [in] using parser
 @param destination [in] container to store data in
 TiPa_Result_Collector(TiPa_Concrete*                                owner,
                       map<const char*,TiPa_Concrete::DataSponsor*>* destination);
*/




/*!
 @brief constructor to be used by a parser

 create in every parser a local copy of the parent collector that will be deleted automatically after leaving the parsing method
 thus the stack will be not necessary any more
*/
 TiPa_Result_Collector(TiPa_Abstract*        owner,
                       TiPa_Result_Abstract* sponsor,
                       Destination_TP        collectFor);





/*!
 @brief copy-constructor

 @param [in] original object to copy
*/
TiPa_Result_Collector(const TiPa_Result_Collector& original);


/*!
 @brief assignment operator

 @param [in] original object to copy

 @return copy of given original
*/
TiPa_Result_Collector& operator=(const TiPa_Result_Collector& original);


/*!
 @brief destructor
*/
  ~TiPa_Result_Collector(void);



/*!
  @brief cast to @ref TiPa_Result_Collector
*/
 TiPa_Result_Collector*  as_TiPa_Result_Collector(void) override;

/*!
  @brief actually cast to @ref TiPa_Result_Terminate  but returns nullptr
*/
 TiPa_Result_Terminate*  as_TiPa_Result_Terminate(void) override;

/*!
  @brief actually cast to @ref TiPa_Result_Skip but returns nullptr
*/
 TiPa_Result_Skip*       as_TiPa_Result_Skip(void) override;






/*!
 @brief store a single result of a parser-hit of a parser with sub-parsers

 if the sub-parser should skip its result it may use the parent parser storage to store its result
 thus the second storing will be not done.

 @param [in] begin            first character of the detected text-part
 @param [in] end              points directly behind the last character of the detected text-part

 @return iterator to currently stored parser-result
*/
  LastStorage_TP storeResult(const char* begin, const char* end);


 protected:

 private:
/*!
 @brief default constructor must not be used
*/
  TiPa_Result_Collector(void);

/*!
 @brief store finally collected contractor results if they are terminal-parsers

 @param association  stores current result
*/
 void contractorResultCopy(Data_TP* data);


/* !
 @brief check if single result node represents an operand-parser or a terminal-parser

 @param association [in] result to test

 @return true if node represents an operand-parser
 @return false if node represents a terminal-parser

 bool isNonTerminalParserResult(Data_TP* data);
*/


/*!
 @brief store finally collected sub-contractor results if they are terminal-parsers

 @param operand  contractor-number of first level contractor
 @param data     stores current result
*/
 void subContractorResultCopy(Data_TP* destination,  Data_TP* source);



/// @brief  data manager  of sponsor
 map<const char*, Data_TP>* DestinationContainer{nullptr};            ///< @brief dictionary of already known hits from earlier calls

/// @brief  destination-object for data-collection
 Destination_TP  CollectFor{CollectFor_Sponsor};


} ;





#endif //TIPA_RESULT_COLLECTOR_H
