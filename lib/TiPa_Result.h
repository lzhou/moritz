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
#ifndef TIPA_RESULT_H
 #define TIPA_RESULT_H

#include "TiPa_Result_Abstract.h"
#include "TiPa_Abstract.h"
#include <iostream>

/*!
 @brief store the result of a tiny parser object
*/
class TiPa_Result: public TiPa_Result_Abstract
{
 public:

 /// @brief  destination-object for data-collection
typedef enum Destination_TP
{
 CollectFor_Owner,       /// @brief collect for owning parser
 CollectFor_Sponsor,     /// @brief collect for sponsor
}Destination_TP;


/*!
 @brief default constructor
*/
 TiPa_Result(void);


/*!
 @brief default constructor must not be used

 create in every parser a local copy of the parent collector that will be deleted automatically after leaving the parsing method
 thus the stack will be not necessary any more
*/
 TiPa_Result(TiPa_Abstract*                                owner,
             TiPa_Result_Abstract*                         sponsor);






/*!
 @brief copy-constructor

 @param [in] source object to copy
*/
 TiPa_Result(const TiPa_Result& source);



/*!
 @brief destructor
*/
 virtual ~TiPa_Result(void);



/*!
 @brief assignment operator

 @param [in] source object to copy

 @return copy of given original
*/
 TiPa_Result& operator=(const TiPa_Result& source) override;






/*!
  @brief  cast to @ref TiPa_Result
*/
 TiPa_Result* as_TiPa_Result(void) override;

/*!
  @brief actually cast to @ref TiPa_Result_Collector but returns nullptr
*/
 virtual TiPa_Result_Collector* as_TiPa_Result_Collector(void) override;

/*!
  @brief actually cast to @ref TiPa_Result_Terminate but returns nullptr
*/
 virtual TiPa_Result_Terminate* as_TiPa_Result_Terminate(void) override;

/*!
  @brief actually cast to @ref TiPa_Result_Skip but returns nullptr
*/
 virtual TiPa_Result_Skip*      as_TiPa_Result_Skip(void) override;











/*!
 @brief store a single result of a parser-hit of a parser with sub-parsers

 if the sub-parser should skip its result it may use the parent parser storage to store its result
 thus the second storing will be not done.

 @param [in] begin            first character of the detected text-part
 @param [in] end              points directly behind the last character of the detected text-part

 @return iterator to currently stored parser-result
*/
  LastStorage_TP storeResult(const char*       begin,
                             const char*       end);






/*!
  @brief provide a contractor-parser result

  the result will be just stored temporarily and has to be accepted by the sponsor-parser to be stored as real sub-result

  @param data result to store temporarily
*/
inline void contractorResultProvide(Data_TP* data) override
{
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<" contractorResultProvide "<< this << data->Begin << "|"<<endl;
 if(Att.ResultTemporary != nullptr)
 {
  delete(Att.ResultTemporary );
 }
 Att.ResultTemporary = new Data_TP(*data);
}


/*!
  @brief get provided contractor-parser result

  the result is just stored temporarily and has to be accepted by the sponsor-parser to be stored as real sub-result

  @return result-data of last called contractor-parser
*/
 inline Data_TP* contractorResultGet(void)
 {
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<" contractorResultGet "<< this <<endl;
  return(Att.ResultTemporary);
 }



/*!
  @brief collect results of contractors to store them finally

  @return result-data that was accepted or nullptr if no result was stored temporarily
*/
 Data_TP* contractorResultAccept(void);

/*!
  @brief insert a result of a contractor to store it finally

  @param data result to store finally
*/
 void contractorResultStore(Data_TP*  data) override;



/*!
  @brief clear the all contractor-results already finally stored

*/
 void contractorResultClear(void) override;




/*!
 @brief return the context-model that is responsible to create result data-objects

 @return currently set context-model as a reference

 @htmlinclude ./des/TiPa_Result_contextModel_get.html
TiPa_Result::DataModel* contextModel_get(void);
*/





/*!
 @brief define the result storage manager

 @param sponsorGuard [in] result storage manager of the calling parser
 @param owner        [in] calling parser
 @param storageMode  [in] defines if and how the parser-hit-data should be stored
*/
static TiPa_Result_Abstract* defineResultGuard(TiPa_Result_Abstract*           sponsorGuard,
                                               TiPa_Abstract*                  owner);







 protected:




 /// @brief class attributes
  struct Att
  {
   map<const char*,Data_TP>* Destination{nullptr};      ///< @brief in to store data in
   TiPa_Result*              Sponsor{nullptr};          ///< @brief result-object of calling parser
   TiPa_Abstract*            Owner{nullptr};            ///< @brief using parser object

   Data_TP*                  ResultTemporary{nullptr};  ///< @brief result of the currently called contractor-parser
   list<Data_TP*>            ResultFinal;               ///< @brief container of final contractor result

   Att(void): Destination(nullptr),
              Sponsor(nullptr),
              Owner(nullptr),
              ResultTemporary(nullptr){};

   Att(map<const char*,Data_TP>* destination,
       TiPa_Result*              sponsor,
       TiPa_Abstract*            owner,
       Data_TP*                  resultTemporary
      ):
         Destination(destination),
         Sponsor(sponsor),
         Owner(owner),
         ResultTemporary(resultTemporary){};


   Att(const Att& original):
         Destination(    original.Destination),
         Sponsor(        original.Sponsor),
         Owner(          original.Owner),
         ResultTemporary(original.ResultTemporary),
         ResultFinal(    original.ResultFinal){};

   Att& operator = (const Att& original)
        {
         Destination     = original.Destination;
         Sponsor         = original.Sponsor;
         Owner           = original.Owner;
         ResultTemporary = original.ResultTemporary;
         ResultFinal     = original.ResultFinal;
         return(*this);
        };

   ~Att(void)
   {
    list<Data_TP*>::iterator Current = ResultFinal.begin();  // container of final contractor result
    while(Current != ResultFinal.end())
    {
     (*Current)->SubParser.clear();
     delete(*Current);
     ++ Current;
    }
   }
  }Att;

 private:




/*!
 @brief store finally collected contractor results

 @param data  stores current result
*/
//void contractorResultCopy(DataSponsor* association);
void contractorResultCopy(Data_TP* data);




} ;





#endif //TIPA_RESULT_H
