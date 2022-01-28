/*!

 @file
 @brief store the result of a tiny parser classes

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
#include "TiPa_Result_Collector.h"
#include "TiPa_Concrete.h"




/* @MRTZ_describe TiPa_Result_Collector
  do not call the bas constructor but initialize everything in a specific way
*/
TiPa_Result_Collector::TiPa_Result_Collector(TiPa_Abstract*        owner,
                                             TiPa_Result_Abstract* sponsor,
                                             Destination_TP        collectFor)
                      :TiPa_Result(owner, sponsor),
                       CollectFor(collectFor)
{
 if(CollectFor == CollectFor_Owner)
 {
  DestinationContainer = owner->as_TiPa_Concrete()->result_Dictionary();
 }
 else
 {
  DestinationContainer = new map<const char*, Data_TP>;
 }

 Att.Destination = owner->as_TiPa_Concrete()->result_Dictionary();
}






/* @MRTZ_describe TiPa_Result_Collector
  do not call the bas constructor but initialize everything in a specific way
*/
TiPa_Result_Collector::TiPa_Result_Collector(void)
                      :TiPa_Result(),
                       DestinationContainer(nullptr),
                       CollectFor(CollectFor_Sponsor)
{
}


/* @MRTZ_describe TiPa_Result_Collector

*/
TiPa_Result_Collector::TiPa_Result_Collector(const TiPa_Result_Collector& original)
                      :TiPa_Result(original),
                       DestinationContainer(original.DestinationContainer),
                       CollectFor          (original.CollectFor)
{
}



/* @MRTZ_describe operator=

*/
TiPa_Result_Collector& TiPa_Result_Collector::operator=(const TiPa_Result_Collector& original)
{
 TiPa_Result::Att     = original.TiPa_Result::Att;
 DestinationContainer = original.DestinationContainer;
 CollectFor           = original.CollectFor;
 return(*this);
}

/* @MRTZ_describe ~TiPa_Result_Collector

*/
TiPa_Result_Collector::~TiPa_Result_Collector(void)
{
 if(CollectFor != CollectFor_Owner)
 {
  map<const char*, Data_TP>::iterator Data = DestinationContainer->begin();
  while(Data != DestinationContainer->end())
  {
   Data->second.SubParser.clear();
   ++Data;
  }
  DestinationContainer->clear();

  delete(DestinationContainer);
 }
}



/* @MRTZ_describe as_TiPa_Result_Collector
  return pointer of this since class supports cast destination
*/
TiPa_Result_Collector* TiPa_Result_Collector::as_TiPa_Result_Collector(void)
{
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"TiPa_Result_Collector::as_TiPa_Result_Collector"<<endl;
 return(this);
}

/* @MRTZ_describe as_TiPa_Result_Terminate
  return nullptr since class does not support cast-destination
*/
TiPa_Result_Terminate* TiPa_Result_Collector::as_TiPa_Result_Terminate(void)
{
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"TiPa_Result_Collector::as_TiPa_Result_Terminate"<<endl;
 return(nullptr);
}

/* @MRTZ_describe as_TiPa_Result_Skip
  return nullptr since class does not support cast-destination
*/
TiPa_Result_Skip* TiPa_Result_Collector::as_TiPa_Result_Skip(void)
{
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"TiPa_Result_Collector::as_TiPa_Result_Skip"<<endl;
 return(nullptr);
}







/* @MRTZ_describe storeResult

*/
TiPa_Result_Collector::LastStorage_TP TiPa_Result_Collector::storeResult(const char* begin, const char* end)
{
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"TiPa_Result_Collector::storeResult enter"<<endl;

(*DestinationContainer)[begin] =  Data_TP(begin,end,Att.Owner);

 this->contractorResultCopy(&((*DestinationContainer)[begin]));

 if(Att.Sponsor != nullptr)                           // this collector collects for a sponsor
 {
  Att.Sponsor->contractorResultProvide(&((*DestinationContainer)[begin]));
 }

 if(CollectFor == CollectFor_Owner)                   // this is a root-collector
 {
  return(DestinationContainer->find(begin));
 }
 else
 {
  return(Att.Destination->end());
 }
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"TiPa_Result_Collector::storeResult leave"<<endl;
}

/* @MRTZ_describe contractorResultCopy

*/
void TiPa_Result_Collector::contractorResultCopy(Data_TP* data)
{
 list<Data_TP*>::iterator ContractorResult    = Att.ResultFinal.begin();
 list<Data_TP*>::iterator ContractorResultEnd = Att.ResultFinal.end();
 while(ContractorResult != ContractorResultEnd)
 {
  if((*ContractorResult) != nullptr)
  {
   const char *    Snippet  = (*ContractorResult)->Begin;
   TiPa_Abstract*  Parser   = (*ContractorResult)->Parser;

   if(Parser->as_TiPa_Concrete()->result_Tree(Snippet) == nullptr)
   {
    subContractorResultCopy(data,  (*ContractorResult));
   }
   else
   {
    data->SubParser[Snippet] = Parser;
   }
  }
  ++ ContractorResult;
 }
}

/* @MRTZ_describe subContractorResultStore

*/
void TiPa_Result_Collector::subContractorResultCopy(Data_TP* destination,  Data_TP* source)
{
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"TiPa_Result_Collector::subContractorResultCopy enter"<<endl;

 map<const char*, TiPa_Abstract*>::iterator ContractorResult = source->SubParser.begin();
 while(ContractorResult != source->SubParser.end())
 {
  TiPa_Abstract* Parser  = ContractorResult->second;
  const char*    Snippet = ContractorResult->first;

  destination->SubParser[Snippet] = Parser;

  ++ContractorResult;
 }
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"TiPa_Result_Collector::subContractorResultCopy leave"<<endl;
}



/* @MRTZ_describe isNonTerminalParserResult

bool TiPa_Result_Collector::isNonTerminalParserResult(Data_TP* data)
{
 if(  (data                     != nullptr)
    &&(data->Parser             != nullptr)
    &&(data->Parser->id_Type()  != TiPa_Concrete::TDA_TiPa_Concrete)
    &&(data->Parser->id_Type()  != TiPa_Concrete::TDA_TiPa_Character)
    &&(data->Parser->id_Type()  != TiPa_Concrete::TDA_TiPa_String)
    &&(data->Parser->id_Type()  != TiPa_Concrete::TDA_TiPa_Rule)
    &&(data->SubParser.empty()  != false)
   )             // result contains valid data,
                 // parser is not from a terminal parser
                 // and the result-node has contractor-results
 {
  return(true);     // the result-node represents an operand-parser
 }
 else            // result is not valid or is from a terminal-parser
 {
   return(false);    // the result-node represents a terminal-parser
 }
}
*/

