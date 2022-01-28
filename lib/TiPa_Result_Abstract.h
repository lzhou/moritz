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
#ifndef TIPA_RESULT_ABSTRACT_H
 #define TIPA_RESULT_ABSTRACT_H

 //#include "AssociationSponsor.hpp"
 //#include "ASS_Model.hpp"
 //#include "TiPa_Data.h"
 #include"TiPa_Abstract.h"
 #include <list>
 #include <map>
 #include <stack>

 using namespace std;


class TiPa_Result;
class TiPa_Result_Collector;
class TiPa_Result_Terminate;
class TiPa_Result_Skip;

/*!
 @brief store the result of a tiny parser object
*/
class TiPa_Result_Abstract
{
 public:

 /// @brief basic properties of a single positive parser result
 typedef struct Data_TP
 {
  const char*                      Begin;                                                 ///< @brief first character of the found text-part
  const char*                      End;                                                   ///< @brief character directly behind the found text-part
  TiPa_Abstract*                   Parser;                                                ///< @brief parsers used to identify the found text-part
  map<const char*, TiPa_Abstract*> SubParser;                                             ///< @brief dictionary of the sub-parsers which were used to identify the found text-part

/// @brief  default constructor
  Data_TP():Begin(nullptr),End(nullptr),Parser(nullptr){};

/// @brief  parameter constructor
  Data_TP(const char* begin, const char* end, TiPa_Abstract* parser):Begin(begin),End(end),Parser(parser){};

/// @brief  copy constructor
  Data_TP(const Data_TP& hit_TP)
  {
   Begin     = hit_TP.Begin;
   End       = hit_TP.End;
   Parser    = hit_TP.Parser;

   map<const char*, TiPa_Abstract*>::const_iterator Source = hit_TP.SubParser.begin();
   while(Source != hit_TP.SubParser.end())
   {
    SubParser[Source->first] = Source->second;
    ++ Source;
   }

  };

/// @brief  assignment operator
  Data_TP& operator = (const Data_TP& hit_TP)
  {
   Begin     = hit_TP.Begin;
   End       = hit_TP.End;
   Parser    = hit_TP.Parser;

   map<const char*, TiPa_Abstract*>::const_iterator Source = hit_TP.SubParser.begin();
   while(Source != hit_TP.SubParser.end())
   {
    SubParser[Source->first] = Source->second;
    ++ Source;
   }
   return(*this);
  };

/// @brief  destructor
  ~Data_TP()
  {
   Begin     = nullptr;
   End       = nullptr;
   Parser    = nullptr;
   while(SubParser.empty() == false)
   {
    SubParser.erase(SubParser.begin());
   }
  };

 }Data_TP;




/*!
 @brief constructor to be used by a parser

*/
  TiPa_Result_Abstract(void);

/*!
 @brief destructor
*/
 virtual ~TiPa_Result_Abstract(void);


/*!
 @brief assignment operator
*/
 virtual TiPa_Result& operator=(const TiPa_Result& source)= 0;


/*!
 @brief actually cast to derived class @ref TiPa_Result but returns nullptr if real class is different
*/
 virtual TiPa_Result*           as_TiPa_Result(void);

/*!
 @brief actually cast to derived class @ref TiPa_Result_Collector but returns nullptr if real class is different
*/
 virtual TiPa_Result_Collector* as_TiPa_Result_Collector(void);

/*!
 @brief actually cast to derived class @ref TiPa_Result_Terminate but returns nullptr if real class is different
*/
 virtual TiPa_Result_Terminate* as_TiPa_Result_Terminate(void);

/*!
 @brief actually cast to derived class @ref class TiPa_Result_Skip but returns nullptr if real class is different
*/
 virtual TiPa_Result_Skip*      as_TiPa_Result_Skip(void);


/*!
 @brief iterator to a stored parser-result
*/
//  typedef map<const char*, DataSponsor*>::iterator LastStorage_TP;
  typedef map<const char*, Data_TP>::iterator LastStorage_TP;




/*!
 @brief container of contractor data
*/
//  typedef list<DataSponsor*>    ContractorList_TP;
  typedef list<Data_TP*>    ContractorList_TP;


/*!
 @brief store a single result of a parser-hit

 @param [in] begin           first character of the detected text-part
 @param [in] end             points directly behind the last character of the detected text-part
 @param [in] dataContractor  sub-parser results

 @return iterator to currently stored parser-result
*/
 virtual LastStorage_TP storeResult(const char* begin, const char* end) = 0;



/*!
  @brief provide a contractor-parser result

  the result will be just stored temporarily and has to be accepted by the sponsor-parser to be stored as real sub-result

  @param data result to store temporarily
*/
// virtual void contractorResultProvide(DataSponsor* association) = 0;
 virtual void contractorResultProvide(Data_TP* data) = 0;


/*!
  @brief get provided contractor-parser result

  the result is just stored temporarily and has to be accepted by the sponsor-parser to be stored as real sub-result

  @return result-association of last called contractor-parser
*/
// virtual  DataSponsor* contractorResultGet(void) = 0;
 virtual  Data_TP* contractorResultGet(void) = 0;



/*!
  @brief collect results of contractors to store them finally

  @return result-association that was accepted or nullptr if no result was stored temporarily
*/
// virtual DataSponsor* contractorResultAccept(void) = 0;
 virtual Data_TP* contractorResultAccept(void) = 0;


/*!
  @brief insert a result of a contractor to store it finally

  @param data result to store finally
*/
// virtual void contractorResultStore(DataSponsor* association) = 0;
 virtual void contractorResultStore(Data_TP* data) = 0;




/*!
  @brief clear the all contractor-results already finally stored

*/
 virtual void contractorResultClear(void) = 0;




/*!
 @brief return the context-model that is responsible to create result data-objects

 @return currently set context-model as a reference

virtual DataModel* contextModel_get(void) = 0;
*/



 protected:

 private:
} ;





#endif //TIPA_RESULT_ABSTRACT_H
