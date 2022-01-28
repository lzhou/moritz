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
#include "TiPa_Result.h"
#include "TiPa_Result_Collector.h"
#include "TiPa_Result_Terminate.h"
#include "TiPa_Result_Skip.h"



/* @MRTZ_describe TiPa_Result

*/
TiPa_Result::TiPa_Result(TiPa_Abstract*                                owner,
                         TiPa_Result_Abstract*                         sponsor)
            :TiPa_Result_Abstract()
{
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"TiPa_Result:"<< this << " # "<< owner->id_Type() << endl;
 Att.Owner           = owner;
 Att.ResultTemporary = nullptr;

 if(sponsor != nullptr)
 {
  Att.Sponsor = sponsor->as_TiPa_Result();
 }
 else
 {
  Att.Sponsor = nullptr;
 }

 Att.Destination     = owner->as_TiPa_Concrete()->result_Dictionary();
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"TiPa_Result:"<< this << " # "<< owner->id_Type() << endl;
}










/* @MRTZ_describe TiPa_Result
  no initialisation necessary since already defined in class declaration
*/
TiPa_Result::TiPa_Result(void)
            :TiPa_Result_Abstract(),
             Att()
{
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"TiPa_Result:"<< this << " # " << endl;
}




TiPa_Result::TiPa_Result(const TiPa_Result& source)
            :TiPa_Result_Abstract(),
 Att(source.Att)
{
}




/* @MRTZ_describe ~TiPa_Result

*/
TiPa_Result::~TiPa_Result(void)
{
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"destructor "<< this <<endl;
 contractorResultClear();
}


TiPa_Result& TiPa_Result::operator=(const TiPa_Result& source)
{
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<""<< this <<endl;
 Att.Owner           = source.Att.Owner;
 Att.Sponsor         = source.Att.Sponsor;
 Att.ResultTemporary = source.Att.ResultTemporary;

 Att.Destination     = source.Att.Destination;
 return(*this);
}





/* @MRTZ_describe as_TiPa_Result

*/
TiPa_Result* TiPa_Result::as_TiPa_Result(void)
{
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"cast to TiPa_Result "<< this <<endl;
  return(this);
}




TiPa_Result_Collector* TiPa_Result::as_TiPa_Result_Collector(void)
{
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"TiPa_Result::as_TiPa_Result_Collector"<<endl;
 return(nullptr);
}

TiPa_Result_Terminate* TiPa_Result::as_TiPa_Result_Terminate(void)
{
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"TiPa_Result::as_TiPa_Result_Terminate"<<endl;
 return(nullptr);
}

TiPa_Result_Skip* TiPa_Result::as_TiPa_Result_Skip(void)
{
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"TiPa_Result::as_TiPa_Result_Skip"<<endl;
 return(nullptr);
}





/* @MRTZ_describe storeDeep

*/
TiPa_Result::LastStorage_TP TiPa_Result::storeResult(const char* begin,
                                                     const char* end)
{





(*Att.Destination)[begin]        =  Data_TP(begin, end, Att.Owner);

 this->contractorResultCopy(&((*Att.Destination)[begin]));
 if(Att.Sponsor != nullptr)
   Att.Sponsor->contractorResultProvide(&((*Att.Destination)[begin]));

 return(Att.Destination->find(begin));
}

/* @MRTZ_describe contractorResultCopy

*/
void TiPa_Result::contractorResultCopy(Data_TP* data)
{

 list<Data_TP*>::iterator ContractorResult    = Att.ResultFinal.begin();
 list<Data_TP*>::iterator ContractorResultEnd = Att.ResultFinal.end();
 while(ContractorResult != ContractorResultEnd)
 {
  if((*ContractorResult) != nullptr)
  {
   data->SubParser[(*ContractorResult)->Begin] = (*ContractorResult)->Parser;

  }
  ++ContractorResult;
 }
}





/* @MRTZ_describe contractorResultAccept

*/
 TiPa_Result::Data_TP*  TiPa_Result::contractorResultAccept(void)
 {
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<" contractorResultAccept "<< this <<endl;
  Data_TP*  ReturnValue = Att.ResultTemporary;
  if(Att.ResultTemporary != nullptr)
  {
   Att.ResultFinal.push_back(Att.ResultTemporary);
   Att.ResultTemporary = nullptr;
  }
  else
  {
   // do nothing
  }
  return(ReturnValue);
 }


/* @MRTZ_describe contractorResultStore

*/
inline void TiPa_Result::contractorResultStore(Data_TP*  data)
{
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<" contractorResultStore "<<endl;
 Att.ResultFinal.push_back(data);
}



/* @MRTZ_describe contractorResultClear

*/
void TiPa_Result::contractorResultClear(void)
{
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<" contractorResultClear "<<endl;
  list<Data_TP*>::iterator Current = Att.ResultFinal.begin();  // container of final contractor result
  while(Current != Att.ResultFinal.end())
  {
   (*Current)->SubParser.clear();
   delete(*Current);
   ++ Current;
  }

  Att.ResultFinal.clear();
}






//#define TEST_RESULTBASE


/* @MRTZ_describe defineResultGuard

*/
TiPa_Result_Abstract* TiPa_Result::defineResultGuard(TiPa_Result_Abstract* sponsorGuard,
                                                     TiPa_Abstract*        owner)
{
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"TiPa_Concrete::defineResultGuard Enter : " << (int)this <<endl;
  TiPa_Result_Abstract* Destination;

#ifdef    TEST_RESULTBASE
  Destination = new TiPa_Result(owner, sponsorGuard);

#else  // TEST_RESULTBASE
  switch(owner->as_TiPa_Concrete()->resultStorage_Get())                                                                   // check owner configuration
  {
   case TiPa_Concrete::ResStore_CollectTerminals:                                                      // store only the results of character-, string- and rule parsers of directly or indirectly called sub-parsers
   {
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"TiPa_Concrete::defineResultGuard "<<endl;
    Destination = new TiPa_Result_Collector(owner, sponsorGuard, TiPa_Result_Collector::CollectFor_Owner);
   } break;

   case TiPa_Concrete::ResStore_Terminate:                                                             // provide a calling parser the own result as a leaf-result
   {
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"TiPa_Concrete::defineResultGuard "<<endl;
    Destination = new TiPa_Result_Terminate(owner, sponsorGuard);
   } break;

   case TiPa_Concrete::ResStore_Skip:                                                                  // provide a calling parser just the hit but no result-details
   {
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"TiPa_Concrete::defineResultGuard "<<endl;
    Destination = new TiPa_Result_Skip(owner, sponsorGuard);
   } break;

   case TiPa_Concrete::ResStore_Default:                                                               // store every single result
   {
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"TiPa_Concrete::defineResultGuard "<<endl;
    Destination = new TiPa_Result(owner, sponsorGuard);
   } break;

   case TiPa_Concrete::ResStore_NV:                                                                    // no valid user-configuration
   default:                                                                                            // no owner-configuration
   {
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"TiPa_Concrete::defineResultGuard "<<endl;
                                                                                                       // check sponsor-type
    if(sponsorGuard->as_TiPa_Result_Collector() != nullptr)                                            // sponsor stores terminal parser-results directly
    {
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"TiPa_Concrete::defineResultGuard "<<endl;
     Destination = new TiPa_Result_Collector(owner, sponsorGuard, TiPa_Result_Collector::CollectFor_Sponsor);               // collect for sponsor
    }
    else if(sponsorGuard->as_TiPa_Result_Terminate() != nullptr)                                       // sponsor stores only own result by skipping sub-parser-results
    {
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"TiPa_Concrete::defineResultGuard "<<endl;
     Destination = new TiPa_Result_Skip(owner, sponsorGuard);                                          // skip own result
    }
    else if(sponsorGuard->as_TiPa_Result_Skip() != nullptr)                                            // sponsor skips its own results
    {
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"TiPa_Concrete::defineResultGuard "<<endl;
     Destination = new TiPa_Result_Skip(owner, sponsorGuard);                                          // skip own result
    }
    else                                                                                               // sponsor stores its own results but not by skipping sub-results
    {
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"TiPa_Concrete::defineResultGuard "<<endl;
     Destination = new TiPa_Result(owner, sponsorGuard);                                               // store own result
    }
   } break;
  }
#endif // TEST_RESULTBASE
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"TiPa_Concrete::defineResultGuard leave"<<endl;
  return(Destination);
}


