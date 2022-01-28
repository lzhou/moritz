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

#define DEBUG_OUTPUT_LOG
#include "TiPa_Counter.h"
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





/* @MRTZ_describe TiPa_Counter

*/
 TiPa_Counter::TiPa_Counter(DataModel* contextModel)
              :TiPa_Concrete(contextModel)
 {
  Mbr.Min                       = -1;
  Mbr.Max                       = -1;
  TiPa_Concrete::Att.MaxOperand =  1;
 }






/* @MRTZ_describe TiPa_Counter

*/
 TiPa_Counter::TiPa_Counter(TiPa_Concrete*               parser,
                            DataModel* contextModel,
                            int                          min,
                            int                          max,
                            Parser_id                    type)
              :TiPa_Concrete(contextModel, type, 0)
 {
  Mbr.Min                       = min;
  Mbr.Max                       = max;
  TiPa_Concrete::Att.MaxOperand =  1;
  this->TiPa_Concrete::contractor_ParserInsert(parser);
 }


/* @MRTZ_describe TiPa_Counter

*/
 TiPa_Counter::TiPa_Counter(Parser_id      operation,
                            TiPa_Concrete* parser,
                            DataModel*     contextModel)
              :TiPa_Concrete(contextModel, (TiPa_ID)operation, 0)
 {
  this->init(operation, parser);
 }







/* @MRTZ_describe ~TiPa_Counter

*/
 TiPa_Counter::~TiPa_Counter(void)
 {

 }


/* @MRTZ_describe init

*/
TiPa_Counter* TiPa_Counter::init(Parser_id operation, TiPa_Concrete* parser)
 {
  TiPa_Concrete::Att.SubType = operation;
  TiPa_Concrete::Att.MaxOperand =  1;

  switch(operation)
  {
   case Cnt_OneOrMore : // operator to find one or more
   {
    Mbr.Min                       =  1;
    Mbr.Max                       = -1;
    this->TiPa_Concrete::contractor_ParserInsert(parser);
   }break;
   case Cnt_AllButNot : // operator to find every character except the defined
   {
    Mbr.Min                       = -1;
    Mbr.Max                       =  0;
    this->TiPa_Concrete::contractor_ParserInsert(parser);
   }break;
   case Cnt_OptionMore : // operator to find nothing or more
   {
    Mbr.Min                       =  0;
    Mbr.Max                       = -1;
    this->TiPa_Concrete::contractor_ParserInsert(parser);
   }break;
   case Cnt_OptionOne :  // operator to find nothing or one
   {
    Mbr.Min                       =  1;
    Mbr.Max                       =  1;
    this->TiPa_Concrete::contractor_ParserInsert(parser);
   }break;
   case Cnt_Default :  // not pre-specified operator
   default :
   {
//    TiPa_Concrete::Att.Type = NotValidParser;
   }break;
  }
  return(this);
 }





/* @MRTZ_describe zeroOrOne

*/
TiPa_Counter* TiPa_Counter::zeroOrOne(TiPa_Concrete* parser)
{
 init(Cnt_OptionOne,  parser);
 return(this);
}


/* @MRTZ_describe zeroOrMore

*/
TiPa_Counter* TiPa_Counter::zeroOrMore(TiPa_Concrete* parser)
{
 init(Cnt_OptionMore,  parser);
 return(this);
}


/* @MRTZ_describe oneOrMore

*/
TiPa_Counter* TiPa_Counter::oneOrMore(TiPa_Concrete* parser)
{
 init(Cnt_OneOrMore,  parser);
 return(this);
}


/* @MRTZ_describe allButNot

*/
TiPa_Counter* TiPa_Counter::allButNot(TiPa_Concrete* parser)
{
 init(Cnt_AllButNot,  parser);
 return(this);
}






/* @MRTZ_describe id_Class

*/
TiPa_Concrete::TDA_TiPa_CLASS_TP TiPa_Counter::id_Class(void)
{
 return(TDA_TiPa_Counter);
}






/* @MRTZ_describe id_Type

*/
inline TiPa_Concrete::TDA_TiPa_CLASS_TP TiPa_Counter::id_Type(void)
{
 return(TDA_TiPa_Counter);
}





/* @MRTZ_describe parser_test

 */
 const char* TiPa_Counter::parser_Test(const char* begin, const char* end, TiPa_Result_Abstract* sponsorGuard)
 {
  const char*    ReturnValue      = nullptr;                                    // return of failure

  LOG_OUTPUT(LOG_OFF,  string("Counter :") << begin);

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
    cout << endl << "invalid result-store content in TiPa_Counter found" << endl;
   setCurrentHitLocation(begin, ReturnValue);
  }
  else if(  (Mbr.AlreadyCalled.find(begin)         == Mbr.AlreadyCalled.end())
          )                                                                     // not found before but valid hit
  {
   ReturnValue = end;                                                           // reinitialize with negative return
   if(   TiPa_Concrete::Att.ContractorParser.find(0)
      != TiPa_Concrete::Att.ContractorParser.end()
     )
   {
    TiPa_Concrete* ContractorParser = TiPa_Concrete::Att.ContractorParser[0];
    Mbr.AlreadyCalled.insert(begin);

    TiPa_Result_Abstract*  ResultGuard = TiPa_Result::defineResultGuard(sponsorGuard, this);

    switch(TiPa_Concrete::Att.SubType)
    {
     case Cnt_OneOrMore :                                                       // operator to find one or more
     {
      ReturnValue = parser_Test_OneOrMore(ContractorParser, begin, end, ResultGuard);
     }break;
     case Cnt_AllButNot :                                                       // operator to find every character except the defined
     {
      ReturnValue = parser_Test_AllButNot(ContractorParser, begin, end, ResultGuard);
     }break;
     case Cnt_OptionMore :                                                      // operator to find nothing or more
     {
      ReturnValue = parser_Test_OptionMore(ContractorParser, begin, end, ResultGuard);
     }break;
     case Cnt_OptionOne :                                                       // operator to find nothing or one
     {
      ReturnValue = parser_Test_OptionOne(ContractorParser, begin, end, ResultGuard);
     }break;
     case Cnt_Default :                                                         // not specified unary operator
     {
      ReturnValue = parser_Test_Default(ContractorParser, begin, end, ResultGuard);
     }break;
     default :
     {
      ReturnValue = nullptr;
     }break;
    }
    Mbr.AlreadyCalled.erase(begin);

    if(ReturnValue   != nullptr)                                                // existing Result should be stored for later analysis
    {
     LOG_OUTPUT(LOG_OFF, string("TiPa_Counter::parser_Test hit |") + string(begin,ReturnValue) +"|");

     if(ReturnValue   != begin)                                                 // existing Result should be stored for later analysis
      Storage.Current = ResultGuard->storeResult(begin, ReturnValue);
     else // result not of interest
     {   }

     if(TiPa_Concrete::Att.ReactionHit != nullptr)                              // user-reaction for parser-hit is defined
      TiPa_Concrete::Att.ReactionHit->processHit(this, Storage.Result[begin]);
                                                                                // start user reaction

     setCurrentHitLocation(begin, ReturnValue);
    }
    else                                                                        // negative result
    {
     setCurrentHitLocation(nullptr, nullptr);
    }
    delete(ResultGuard);
   }
  }
  else                                                                          // no text left after skip-parsing
  {
   if(Mbr.AlreadyCalled.find(begin) != Mbr.AlreadyCalled.end())
   {
    cout << "TiPa_Counter recursive call with \n|" << begin << "| |" << endl;
   }
   ReturnValue = nullptr;                                                       // negative return
   setCurrentHitLocation(nullptr, nullptr);
  }

  return(ReturnValue);
 }




/* @MRTZ_describe equal_Parser

*/
 bool TiPa_Counter::equal_Parser(TiPa_Concrete* parser)
 {
  bool ReturnValue = true;

  TiPa_Counter* Parser = static_cast<TiPa_Counter*>(parser) ;


  if(this->TiPa_Concrete::Att.SubType != Parser->TiPa_Concrete::Att.SubType)
  // type is not the same
  {
   ReturnValue = false;
  }
  else if(Parser->TiPa_Concrete::Att.SkipParser != this->TiPa_Concrete::Att.SkipParser)
  // the skip-parser is different
  {
   ReturnValue = false;
  }
  else if(   this  ->TiPa_Concrete::Att.ContractorParser.begin()->second
          != Parser->TiPa_Concrete::Att.ContractorParser.begin()->second)
   // contractor-parser of this parser and the given parser is not the same
  {
   ReturnValue = false;
  }
  else
  // contractor-parser of this parser and the given parser is not the same
  {
   if(  (this->Mbr.Min!= Parser->Mbr.Min)
      ||(this->Mbr.Max!= Parser->Mbr.Max)
      )
   // counting range of this parser and the given one is not the same
   {
    ReturnValue = false;
   }

  }
  return(ReturnValue);
 }








/* @MRTZ_describe parser_Test_OneOrMore

*/
 const char* TiPa_Counter::parser_Test_OneOrMore(TiPa_Concrete*        contractorParser,
                                                 const char*           begin,
                                                 const char*           end,
                                                 TiPa_Result_Abstract* sponsorGuard)
 {
  const char* ReturnValue = nullptr;      // return of failure
  int         Count       = 0;

  const char* Character   = begin;
  while(  (Character != nullptr)
        &&(Character <  end)
       )
  {
   Character  = contractorParser->parser_Test(Character,end,sponsorGuard);

   if((Character!=nullptr)&&(Character <= end))
   {
    LOG_OUTPUT(LOG_OFF, string("TiPa_Counter::parser_Test_OneOrMore ") + string(begin,Character) );

    sponsorGuard->contractorResultAccept();

    ReturnValue = Character ;
    ++ Count;
   }
   else
   {
    break;
   }
  }



  if(Count == 0)
  {
   ReturnValue = nullptr;
  }
  else
  {
  }

  return(ReturnValue);
 }



/* @MRTZ_describe parser_Test_AllButNot

*/
 const char* TiPa_Counter::parser_Test_AllButNot(TiPa_Concrete*               contractorParser,
                                                 const char*                  begin,
                                                 const char*                  end,
                                                 TIPA_RESULT_ABSTRACT_UNUSED* sponsorGuard)
 {
  const char*    ReturnValue = nullptr;      // return of failure

  if(contractorParser->parser_Test(begin,end,sponsorGuard) == nullptr)
  {
   LOG_OUTPUT(LOG_OFF, string("TiPa_Counter::parser_Test_AllButNot ") + string(begin) );
   ReturnValue = begin;
  }
  else
  {
//   contractor->clear();
   ReturnValue = nullptr;
  }

  return(ReturnValue);
 }



/* @MRTZ_describe parser_Test_OptionMore

*/
 const char* TiPa_Counter::parser_Test_OptionMore(TiPa_Concrete*        contractorParser,
                                                  const char*           begin,
                                                  const char*           end,
                                                  TiPa_Result_Abstract* sponsorGuard)
 {
  const char* ReturnValue = nullptr;      // return of failure
  int         Count       = 0;

  const char* Character   = begin;
  while(  (Character != nullptr)
        &&(Character <  end)
       )
  {
//   cout << endl << endl << endl << "-+|" << Character << "|" ;
   Character  = contractorParser->parser_Test(Character,end,sponsorGuard);

   if(  (Character != nullptr)
      &&(Character <= end    )
     )
   {
//   cout << "+-|" << Character << "|" ;
    LOG_OUTPUT(LOG_OFF, string("TiPa_Counter::parser_Test_OptionMore ") + string(begin,Character) );

    sponsorGuard->contractorResultAccept();

    ReturnValue = Character ;
    ++ Count;
   }
   else
   {
    break;
   }
  }

  if(Count == 0)
  {
   ReturnValue = begin;
  }
  else //Count>0
  {
  }

  return(ReturnValue);
 }



/* @MRTZ_describe parser_Test_OptionOne

*/
 const char* TiPa_Counter::parser_Test_OptionOne(TiPa_Concrete*        contractorParser,
                                                 const char*           begin,
                                                 const char*           end,
                                                 TiPa_Result_Abstract* sponsorGuard)
 {
  const char*          ReturnValue      = nullptr;      // return of failure
  int                  Count            = 0;

  const char*          Character        = begin;
  while(  (Character   != nullptr)
        &&(Character   <  end)
        &&(ReturnValue != Character)
       )
  {
   Character  = contractorParser->parser_Test(Character,end,sponsorGuard);

   if((Character!=nullptr)&&(Character <= end))
   {
    LOG_OUTPUT(LOG_OFF, string("TiPa_Counter::parser_Test_OptionOne ") + string(begin,Character) );

    sponsorGuard->contractorResultAccept();

    ReturnValue = Character ;
    ++ Count;
   }
   else
   {
    break;
   }
  }

  if(Count == 0)
  {
   ReturnValue = begin;
  }
  else if(Count > 1)
  {
   sponsorGuard->contractorResultClear();

   ReturnValue = nullptr;
  }
  else //Count == 1
  {
  }

  return(ReturnValue);
 }



/* @MRTZ_describe parser_Test_Default

*/
 const char* TiPa_Counter::parser_Test_Default(TiPa_Concrete*        contractorParser,
                                               const char*           begin,
                                               const char*           end,
                                               TiPa_Result_Abstract* sponsorGuard)
 {
  const char* ReturnValue = nullptr;      // return of failure
  int         Count       = 0;

  const char* Character  = begin;
  while(  (Character != nullptr)
        &&(Character <  end)
       )
  {
   Character  = contractorParser->parser_Test(Character,end,sponsorGuard);

   if((Character!=nullptr)&&(Character <= end))
   {
    LOG_OUTPUT(LOG_OFF, string("TiPa_Counter::parser_Test_Default ") + string(begin,Character) );

    sponsorGuard->contractorResultAccept();

    ReturnValue = Character ;
    ++ Count;
   }
   else
   {
    break;
   }
  }

  if(  (Count < Mbr.Min)
     ||(Count > Mbr.Max)
    )
  {
   sponsorGuard->contractorResultClear();

   ReturnValue = nullptr;
  }
  else // (Count >= Mbr.Min) &&(Count <= Mbr.Max)
  {
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



