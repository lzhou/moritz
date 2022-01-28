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

//#define DEBUG_OUTPUT_LOG
#include "TiPa_Rule.h"
#include "TiPa_Reaction_Concrete.h"
#include "TiPa_Result.h"

#include <stdio.h>
#include <cstring>

using namespace std;

#ifndef DOXYGEN
//namespace TXTDIASM {
//namespace TDA_TinyParser {
////namespace CL_TIPA_CONCRETE {
//namespace CL_TIPA {
#endif //DOXYGEN

/* @MRTZ_describe TiPa_Rule

*/
 TiPa_Rule::TiPa_Rule(const char*                  name,
                      DataModel* contextModel)
           :TiPa_Concrete(contextModel,TiPa_Rule::Default)
 {

  if(name != nullptr)
  {
   Mbr.Name = new char[strlen(name)+1];
   strcpy(Mbr.Name, name);
   Mbr.Name[strlen(name)] = 0;
  }
  else
  {
   Mbr.Name = nullptr;
  }

  this->setName(name);

  TiPa_Concrete::Att.MaxOperand = 1;
 }






/* @MRTZ_describe TiPa_Rule

*/
 TiPa_Rule::TiPa_Rule(const char*                  name,
                      TiPa_Concrete*               root,
                      DataModel* contextModel,
                      Parser_id                    type)
           :TiPa_Concrete(contextModel, type)
 {

  if(name != nullptr)
  {
   Mbr.Name = new char[strlen(name)+1];
   strcpy(Mbr.Name, name);
   Mbr.Name[strlen(name)] = 0;
  }
  else
  {
   Mbr.Name = nullptr;
  }

  this->setName(name);
  this->init(root,type);
 }









/* @MRTZ_describe ~TiPa_Rule

*/
 TiPa_Rule::~TiPa_Rule(void)
 {
  delete[](Mbr.Name);
  Mbr.Name = nullptr;
 }






/* @MRTZ_describe TiPa_init

*/
TiPa_Rule*  TiPa_Rule::init(TiPa_Concrete* root, Parser_id type)
{
 TiPa_Concrete::Att.SubType    = type;
 TiPa_Concrete::Att.MaxOperand = 1;
 this->contractor_ParserInsert(root,0);

 return(this);
}







/* @MRTZ_describe id_Class

*/
TiPa_Concrete::TDA_TiPa_CLASS_TP TiPa_Rule::id_Class(void)
{
 return(TDA_TiPa_Rule);
}







/* @MRTZ_describe id_Type

*/
inline TiPa_Concrete::TDA_TiPa_CLASS_TP TiPa_Rule::id_Type(void)
{
 return(TDA_TiPa_Rule);
}



/* @MRTZ_describe TiPa_setName

*/
 void TiPa_Rule::setName(const char* name)
 {
  if(name != nullptr)
  {
   Mbr.Name = new char[strlen(name)+1];
   strcpy(Mbr.Name, name);
   Mbr.Name[strlen(name)] = 0;
  }
  else
  {
   Mbr.Name = nullptr;
  }
 }









/* @MRTZ_describe TiPa_init

*/
 const char* TiPa_Rule::getName(void)
 {
  return(Mbr.Name);
 }


















/* @MRTZ_describe parser_test
 if a previous search already detected a hit the previous positive result will
 be returned otherwise the string pointed by begin will be compared with all
 strings pointed by the content of the parse item set.
 */
 const char* TiPa_Rule::parser_Test(const char* begin, const char* end, TiPa_Result_Abstract* sponsorGuard)
 {
  const char*              ReturnValue   = nullptr;                             // return of failure

#ifdef DEBUG_OUTPUT_LOG
 if(  (strstr(Mbr.Name,"skip")!= Mbr.Name)
    &&(strstr(Mbr.Name,"Skip")!= Mbr.Name)
   )
  {
   LOG_OUTPUT(LOG_ON,  string(Mbr.Name)<< ":" << begin);
  }
#endif // DEBUG_OUTPUT_LOG

  begin = skip_parsing(begin, end);                                             // skip text-parts which should be ignored


  if(   Storage.Result.find(begin)
     != Storage.Result.end()
    )                                                                           // already found before
  {
   if(sponsorGuard != nullptr)
    sponsorGuard->contractorResultProvide(&Storage.Result[begin]);

   if(TiPa_Concrete::Att.ReactionHit != nullptr)                                // user-reaction for parser-hit is defined
    TiPa_Concrete::Att.ReactionHit->processHit(this, Storage.Result[begin]);
                                                                                // start user reaction
   Storage.Current = Storage.Result.find(begin);                                // buffer last result

   ReturnValue = endOfHitResult(begin);                                         // positive return
   if((ReturnValue < begin) && (ReturnValue > end))
    cout << endl << "invalid result-store content in TiPa_Rule found" << endl;

   setCurrentHitLocation(begin, ReturnValue);
  }
  else if(  (begin                                      <  end)
          &&(TiPa_Concrete::Att.ContractorParser.size() >  0  )
          &&(Storage.NonHit.find(begin)                 == Storage.NonHit.end())
          &&(Mbr.AlreadyCalled.find(begin)              == Mbr.AlreadyCalled.end())
         )                                                                      // not found before but valid hit
  {
   TiPa_Concrete* ContractorParser = TiPa_Concrete::Att.ContractorParser[0];
   Mbr.AlreadyCalled.insert(begin);
   TiPa_Result_Abstract*  ResultGuard = TiPa_Result::defineResultGuard(sponsorGuard, this);

   ReturnValue = ContractorParser->parser_Test(begin, end, ResultGuard);

   Mbr.AlreadyCalled.erase(begin);
   if(ReturnValue   != nullptr)                                                 // existing Result should be stored for later analysis
   {

//    DataAssociation* ContractorResult = ResultGuard->contractorResultAccept();
    Hit_TP* ContractorResult = ResultGuard->contractorResultAccept();


#ifdef DEBUG_OUTPUT_LOG
   if(  (strstr(Mbr.Name,"skip")!= Mbr.Name)
      &&(strstr(Mbr.Name,"Skip")!= Mbr.Name)
     )
     {
      LOG_OUTPUT(LOG_ON, string("TiPa_Rule{") << string(Mbr.Name) << string("}|") << string(begin, ReturnValue) << string("|") << (int)(ReturnValue-begin) << string("|---------"));
     }
#endif // DEBUG_OUTPUT_LOG

    if(Storage.StorageType == ResStore_Skip)                                    // result not of interest
     { /* don't store anything*/}
    else
     Storage.Current = ResultGuard->storeResult(ContractorParser->currentBegin(), ReturnValue);

    if(  (TiPa_Concrete::Att.ReactionHit != nullptr)
       &&(ContractorResult               != nullptr)
      )                                                                         // user-reaction for parser-hit is defined and contractor data is known
    {
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<""<<endl;
     TiPa_Concrete::Att.ReactionHit->processHit(this, Storage.Result[ContractorResult->Begin]);
                                                                                // start user reaction with data from called parser
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<""<<endl;
    }
    else if(TiPa_Concrete::Att.ReactionHit != nullptr)                          // user-reaction for parser-hit is defined bud no contractor data is known
    {
     TiPa_Concrete::Att.ReactionHit->processHit(this, Storage.Result[begin]);
                                                                                // start user reaction with data of theis parser
    }
    else
    {
                                                                                // start no user reaction
    }
    setCurrentHitLocation(ContractorParser->currentBegin(), ReturnValue);
   }
   else                                                                         // root returned negative result
   {
    Storage.NonHit.insert(begin);
#ifdef DEBUG_OUTPUT_LOG
    if(  (strstr(Mbr.Name,"skip")!= Mbr.Name)
       &&(strstr(Mbr.Name,"Skip")!= Mbr.Name)
    )
    {
     LOG_OUTPUT(LOG_OFF, string("TiPa_Rule{") + string(Mbr.Name) + string("} no hit \n|") + begin + "|" );
    }
#endif // DEBUG_OUTPUT_LOG
    setCurrentHitLocation(nullptr, nullptr);
   }
   delete(ResultGuard);
  }
  else                                                                          // no text left after skip-parsing
  {
   if(Mbr.AlreadyCalled.find(begin) != Mbr.AlreadyCalled.end())
   {
    cout << string("TiPa_Rule{") + string(Mbr.Name) + string("} recursive call with \n|") + begin + "| |" << endl;
   }
                                                                                // or rule is not defined
   ReturnValue = nullptr;                                                       // negative return
   setCurrentHitLocation(nullptr, nullptr);
  }
  return(ReturnValue);
 }




/* @MRTZ_describe equal_Parser

*/
 bool TiPa_Rule::equal_Parser(TiPa_Concrete* parser)
 {
  bool           ReturnValue = true;
  TiPa_Concrete* Item;
  TiPa_Concrete* ThisItem;

  TiPa_Rule* Parser = static_cast<TiPa_Rule*>(parser);


  if(this->TiPa_Concrete::Att.SubType != Parser->TiPa_Concrete::Att.SubType)
  // type is not the same
  {
   ReturnValue = false;
  }
  else if(  (Parser->TiPa_Concrete::Att.ContractorParser.size() > 0)
          &&(this  ->TiPa_Concrete::Att.ContractorParser.size() > 0)
         )
  // equal type and rule contains a contractor-parser
  {
   Item        = Parser->TiPa_Concrete::Att.ContractorParser[0];
   ThisItem    = this  ->TiPa_Concrete::Att.ContractorParser[0];

   if(ThisItem != Item)
   // root of given parser is not the same as the root of of this parsers
   {
    ReturnValue = false;
   }
   else
   // root of given parser is the same as the root of of this parsers
   {
   }
  }
  else
  // equal type but rule contains no contractor-parser
  {
   ReturnValue = false;
  }

  return(ReturnValue);
 }
















#ifndef DOXYGEN
#define USING_NAMESPACE using namespace
//}; USING_NAMESPACE CL_TIPA;
//}; USING_NAMESPACE CL_TIPA_CONCRETE;
//}; USING_NAMESPACE TDA_TinyParser;
//}; USING_NAMESPACE TXTDIASM;
#undef  USING_NAMESPACE
#endif //DOXYGEN



