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
#ifndef TIPA_RESULT_SKIP_H
 #define TIPA_RESULT_SKIP_H

#include "TiPa_Result.h"
#include "TiPa_Concrete.h"

/// @ingroup UNUSED_DATA
/// @brief avoid compiler warning since the object is not used
/// @{
#define CONST_CHAR_UNUSED __attribute__ ((unused)) const char
/// @}


/*!
 @brief store the result of a tiny parser object
*/
class TiPa_Result_Skip: public TiPa_Result
{
 public:

/*!
 @brief constructor to be used by a parser

 create in every parser a local copy of the parent collector that will be deleted automatically after leaving the parsing method
 thus the stack will be not necessary any more
*/
 TiPa_Result_Skip(TiPa_Abstract*        owner,
                  TiPa_Result_Abstract* sponsor);


/*!
 @brief copy-constructor

 @param [in] original object to copy
*/
TiPa_Result_Skip(const TiPa_Result_Skip& original);


/*!
 @brief assignment operator

 @param [in] original object to copy

 @return copy of given original
*/
TiPa_Result_Skip& operator=(const TiPa_Result_Skip& original);



/*!
 @brief destructor
*/
  ~TiPa_Result_Skip(void);






/*!
  @brief actually cast to @ref TiPa_Result_Collector but returns nullptr
*/
TiPa_Result_Collector* as_TiPa_Result_Collector(void) override;

/*!
  @brief actually cast to @ref TiPa_Result_Terminate but returns nullptr
*/
TiPa_Result_Terminate* as_TiPa_Result_Terminate(void) override;

/*!
  @brief cast to @ref TiPa_Result_Skip
*/
TiPa_Result_Skip*      as_TiPa_Result_Skip(void) override;





/*!
 @brief store a single result of a parser-hit of a parser with sub-parsers

 if the sub-parser should skip its result it may use the parent parser storage to store its result
 thus the second storing will be not done.

 @param [in] begin            first character of the detected text-part
 @param [in] end              points directly behind the last character of the detected text-part

 @return iterator to currently stored parser-result
*/
  LastStorage_TP storeResult(CONST_CHAR_UNUSED* begin, CONST_CHAR_UNUSED* end);






 protected:

 private:
/*!
 @brief default constructor must not be used
*/
  TiPa_Result_Skip(void);



} ;





#endif //TIPA_RESULT_SKIP_H
