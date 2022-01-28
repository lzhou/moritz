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

//#define DEBUG_OUTPUT_LOG
#include "TiPa_Combination.h"
#include "TiPa_Reaction_Concrete.h"
#include "TiPa_Result.h"

#include <stdio.h>
#include <cstring>
#include <limits.h>
using namespace std;

#ifndef DOXYGEN
#define USING_NAMESPACE using namespace
//namespace TXTDIASM {
//namespace TDA_TinyParser {
////namespace CL_TIPA_CONCRETE {
//namespace CL_TIPA {
#endif //DOXYGEN






/* @MRTZ_describe TiPa_Sequence

*/
 TiPa_Sequence::TiPa_Sequence(DataModel* contextModel)
               :TiPa_Concrete(contextModel)
 {
  TiPa_Concrete::Att.MaxOperand = 1;
  Mbr.Dircetive                 = PrDr_Default;
 }






/* @MRTZ_describe TiPa_Sequence

*/
 TiPa_Sequence::TiPa_Sequence(TiPa_Concrete* parser0,
                              TiPa_Concrete* parser1,
                              DataModel* contextModel,
                              Parser_id      type)
              :TiPa_Concrete(contextModel, type, 1)
 {
  Mbr.Dircetive = PrDr_Default;

  TiPa_Concrete::Att.MaxOperand = 2;

  this->contractor_ParserInsert(parser0,0);
  this->contractor_ParserInsert(parser1,1);
 }

/* @MRTZ_describe TiPa_Sequence

*/
 TiPa_Sequence::TiPa_Sequence(Parser_id       operation,
                              TiPa_Concrete*  parser0,
                              TiPa_Concrete*  parser1,
                              DataModel* contextModel,
                              ParserDirective directive)
               :TiPa_Concrete(contextModel, operation, 1)
{
  this->init(operation,
             parser0,
             parser1,
             directive);

}



/* @MRTZ_describe ~TiPa_Sequence

*/
 TiPa_Sequence::~TiPa_Sequence(void)
 {

 }




/* @MRTZ_describe init

*/
TiPa_Sequence* TiPa_Sequence::init(Parser_id      operation,
                                   TiPa_Concrete*  parser0,
                                   TiPa_Concrete*  parser1,
                                   ParserDirective directive)
 {
  TiPa_Concrete::Att.SubType = operation;

  switch(operation)
  {
   case Seq_Seprt :   // next part detection of table-part (%)
   {
    Mbr.Dircetive = directive;
    TiPa_Concrete::Att.MaxOperand = 1;
                     // since it is possible to add no more contractor-Parsers
    this->contractor_ParserInsert(parser0,0);
    this->contractor_ParserInsert(parser1,1);
   }break;
   case Seq_SftSq :   // next part detection of sequence-part (||)
   {
    Mbr.Dircetive = directive;
    TiPa_Concrete::Att.MaxOperand = INT_MAX;
                      // since it is possible to add more contractor-Parsers
    this->contractor_ParserInsert(parser0,0);
    this->contractor_ParserInsert(parser1,1);
   }break;
   case Seq_HrdSq :   // next part detection of sequence-part (&&) or (>>)
   {
    Mbr.Dircetive = directive;
    TiPa_Concrete::Att.MaxOperand = INT_MAX;
                      // since it is possible to add more contractor-Parsers
    this->contractor_ParserInsert(parser0,0);
    this->contractor_ParserInsert(parser1,1);
   }break;
   case Seq_NotValide :
   case Seq_Default   : // unspecified parser of binary or sequence operator
   default :
   {
    Mbr.Dircetive = directive;
    TiPa_Concrete::Att.MaxOperand = INT_MAX;
                      // since it is possible to add more contractor-Parsers
    TiPa_Concrete::Att.SubType = Seq_NotValide;
   }break;
  }
  return(this);
 }



/* @MRTZ_describe hard

*/
 TiPa_Sequence* TiPa_Sequence::hard(TiPa_Concrete*  parser0,
                                    TiPa_Concrete*  parser1,
                                    ParserDirective directive)
 {
  init(Seq_HrdSq, parser0, parser1, directive);
  return(this);
 }



/* @MRTZ_describe soft

*/
 TiPa_Sequence* TiPa_Sequence::soft(TiPa_Concrete*  parser0,
                                    TiPa_Concrete*  parser1,
                                    ParserDirective directive)
 {
  init(Seq_SftSq, parser0, parser1, directive);
  return(this);
 }



/* @MRTZ_describe table

*/
 TiPa_Sequence* TiPa_Sequence::table(TiPa_Concrete*  parser,
                                     TiPa_Concrete*  separator,
                                     ParserDirective directive)
 {
  init(Seq_Seprt, parser, separator, directive);
  return(this);
 }








/* @MRTZ_describe include

*/
void TiPa_Sequence::include(TiPa_Concrete*  parser)
{

  switch(TiPa_Concrete::Att.SubType)
  {
   case Seq_SftSq :   // next part detection of sequence-part (||)
   case Seq_HrdSq :   // next part detection of sequence-part (&&) or (>>)
   {
    this->contractor_ParserInsert(parser,-1); // insert at the end
   }break;
   case Seq_Seprt :   // next part detection of table-part (%)
   case Seq_Default : // unspecified parser of binary or sequence operator
   default :
   {
                      // ignore input
   }break;
  }
 }






/* @MRTZ_describe hard

*/
TiPa_Sequence* TiPa_Sequence::hard(TiPa_Concrete*  parser)
{
 if(TiPa_Concrete::Att.SubType == Seq_HrdSq)
 {
  this->contractor_ParserInsert(parser,-1); // insert at the end
 }
 else
 {
                                            // ignore input
 }

 return(this);
}







/* @MRTZ_describe soft

*/
TiPa_Sequence* TiPa_Sequence::soft(TiPa_Concrete*  parser)
{
 if(TiPa_Concrete::Att.SubType == Seq_SftSq)
 {
  this->contractor_ParserInsert(parser,-1); // insert at the end
 }
 else
 {
                                            // ignore input
 }
 return(this);
}





/* @MRTZ_describe id_Class

*/
TiPa_Concrete::TDA_TiPa_CLASS_TP TiPa_Sequence::id_Class(void)
{
 return(TDA_TiPa_Sequence);
}






/* @MRTZ_describe id_Type

*/
inline TiPa_Concrete::TDA_TiPa_CLASS_TP TiPa_Sequence::id_Type(void)
{
 return(TDA_TiPa_Sequence);
}













/* @MRTZ_describe parser_test

 */
 const char* TiPa_Sequence::parser_Test(const char* begin, const char* end, TiPa_Result_Abstract* sponsorGuard)
 {
  const char*    ReturnValue = nullptr;                                         // return of failure

  LOG_OUTPUT(LOG_OFF,  string("Sequence :") << begin);

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
    cout << endl << "invalid result-store content in TiPa_Sequence found" << endl;
   setCurrentHitLocation(begin, ReturnValue);
  }
  else if(  (begin                                 <  end)
          &&(Mbr.AlreadyCalled.find(begin)         == Mbr.AlreadyCalled.end())
          )                                                                     // not found before but valid hit

  {
   Mbr.AlreadyCalled.insert(begin);

   TiPa_Result_Abstract*  ResultGuard = TiPa_Result::defineResultGuard(sponsorGuard, this);

   switch(TiPa_Concrete::Att.SubType)
   {
    case Seq_Seprt :   // next part detection of table-part (%)
    {
 #if defined(DEBUG_OUTPUT)
     printf("Cmb_Seprt\n");
 #endif // defined(DEBUG_OUTPUT)
    ReturnValue = parser_Test_Seprt(begin, end, ResultGuard);
    }break;
    case Seq_SftSq :                                                            // next part detection of sequence-part (||)
    {
 #if defined(DEBUG_OUTPUT)
     printf("Cmb_SftSq\n");
 #endif // defined(DEBUG_OUTPUT_LOG)
     ReturnValue = parser_Test_SftSq(begin, end, ResultGuard);
    }break;
    case Seq_HrdSq :                                                            // next part detection of sequence-part (&&) or (>>)
    {
 #if defined(DEBUG_OUTPUT)
     LOG_OUTPUT(LOG_OFF,string("Cmb_HrdSq:") + begin);
 #endif // defined(DEBUG_OUTPUT)
     ReturnValue = parser_Test_HrdSq(begin, end, ResultGuard);
    }break;
    case Seq_Default :                                                          // unspecified parser of binary or sequence operator
    {
 #if defined(DEBUG_OUTPUT)
     printf("Cmb_Default\n");
 #endif // defined(DEBUG_OUTPUT)
     ReturnValue = parser_Test_Default(begin, end, ResultGuard);
    }break;
    default :
    {
 #if defined(DEBUG_OUTPUT)
     printf("??????  %d\n",TiPa_Concrete::Att.Type);
 #endif // defined(DEBUG_OUTPUT)
     ReturnValue = nullptr;
    }break;
   }
   Mbr.AlreadyCalled.erase(begin);

   if(ReturnValue   != nullptr)                                                 // existing Result should be stored for later analysis
   {
    LOG_OUTPUT(LOG_OFF, string("TiPa_Sequence::parser_Test hit ") + string(begin, ReturnValue) +"|");

    Storage.Current = ResultGuard->storeResult(begin,ReturnValue);

    if(TiPa_Concrete::Att.ReactionHit != nullptr)                               // user-reaction for parser-hit is defined
     TiPa_Concrete::Att.ReactionHit->processHit(this, Storage.Result[begin]);
                                                                                // start user reaction

    setCurrentHitLocation(begin, ReturnValue);
   }
   else                                                                        // negative result
   {
//     TiPa_Concrete::Att.NonHit.insert(begin);
    setCurrentHitLocation(nullptr, nullptr);
   }
   delete(ResultGuard);
  }
  else                                                                          // no text left after skip-parsing
  {
   if(Mbr.AlreadyCalled.find(begin) != Mbr.AlreadyCalled.end())
   {
    cout << "TiPa_Sequence recursive call with \n|" << begin << "| |" << endl;
   }
   ReturnValue = nullptr;                                                       // negative return
   setCurrentHitLocation(nullptr, nullptr);
  }

  return(ReturnValue);
 }




/* @MRTZ_describe equal_Parser

*/
 bool TiPa_Sequence::equal_Parser(TiPa_Concrete* parser)
 {
  bool ReturnValue = false;

  TiPa_Sequence* Parser = static_cast<TiPa_Sequence*>(parser) ;

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
  else if(  (Parser->TiPa_Concrete::Att.ContractorParser.size())
          !=(  this->TiPa_Concrete::Att.ContractorParser.size())
         )
   // the given parser has not the same number of contractor parsers as this parser
  {
   ReturnValue = false;
  }
  else
  // item of given parser is part of this parsers item container
  {
   map<int, TiPa_Concrete*>::iterator Item     = Parser->TiPa_Concrete::Att.ContractorParser.begin();
   map<int, TiPa_Concrete*>::iterator ThisItem =         TiPa_Concrete::Att.ContractorParser.begin();

   while(  (Item     != Parser->TiPa_Concrete::Att.ContractorParser.end())
         &&(ThisItem !=   this->TiPa_Concrete::Att.ContractorParser.end())
        )
   // iterate over configuration of this and the given parser
   {
    if((*Item) != (*ThisItem))
    // the contractor-parser of the given parser is not the same as the contractor parser of this one
    {
     ReturnValue = false;

     break;
    }
    else
    // both items have a different size or/and a different content
    {
     ++ Item;
     ++ ThisItem;
    }

   }
  }
  return(ReturnValue);
 }










/* @MRTZ_describe parser_Test_Seprt

*/
 const char* TiPa_Sequence::parser_Test_Seprt(const char*           begin,
                                              const char*           end,
                                              TiPa_Result_Abstract* sponsorGuard)
 {
  const char*                   ReturnValue       = nullptr;      // return of failure

  TiPa_Concrete* ContractorParser0 = TiPa_Concrete::Att.ContractorParser[0];
  TiPa_Concrete* ContractorParser1 = TiPa_Concrete::Att.ContractorParser[1];

  const char* Character = ContractorParser0->parser_Test(begin,end,sponsorGuard);

  while(  (Character   != nullptr)
        &&(Character   <= end )
       )
  {
   sponsorGuard->contractorResultAccept();

   ReturnValue = Character;
   Character   = skip_parsing(Character, end);             // skip text-parts which should be ignored
   Character   = ContractorParser1->parser_Test(Character,end,sponsorGuard);

   if(  (Character   != nullptr)
      &&(Character   <= end )
     )
   {
    sponsorGuard->contractorResultAccept();

    Character = skip_parsing(Character, end);            // skip text-parts which should be ignored
    Character = ContractorParser0->parser_Test(Character,end,sponsorGuard);
   }
   else
   { }
  }

  return(ReturnValue);
 }






/* @MRTZ_describe parser_Test_SftSq

*/
 const char* TiPa_Sequence::parser_Test_SftSq(const char*           begin,
                                              const char*           end,
                                              TiPa_Result_Abstract* sponsorGuard)
 {
  const char* ReturnValue = begin;
  const char* Character   = begin;

  int         Index       = 0;
  while(  (   TiPa_Concrete::Att.ContractorParser.find(Index)
           != TiPa_Concrete::Att.ContractorParser.end()
          )
        &&(Character < end)
       )
  {
                  Character         = skip_parsing(Character, end);            // skip text-parts which should be ignored
   TiPa_Concrete* ContractorParser  = TiPa_Concrete::Att.ContractorParser[Index];
                  Character         = ContractorParser->parser_Test(Character,end,sponsorGuard);

   if(  (Character != nullptr)
      &&(Character <= end    )
     )
   {
    sponsorGuard->contractorResultAccept();

    ReturnValue = Character;
   }
   else
   {
    Character = ReturnValue;
   }
   ++ Index; // prepare search for next contractor-parser
  }
  if(  (ReturnValue == begin)
     ||(ReturnValue >  end)
    )
  {
   sponsorGuard->contractorResultClear();

   ReturnValue = nullptr;
  }
  else
  {
  }

  return(ReturnValue);
 }






/* @MRTZ_describe parser_Test_HrdSq

*/
 const char* TiPa_Sequence::parser_Test_HrdSq(const char*           begin,
                                              const char*           end,
                                              TiPa_Result_Abstract* sponsorGuard)
 {
  const char* ReturnValue = nullptr;      // return of failure

  int         Index       = 0;
  const char*  Character  = begin;
  while(  (   TiPa_Concrete::Att.ContractorParser.find(Index)
           != TiPa_Concrete::Att.ContractorParser.end()
          )
        &&(Character != nullptr)
       )
  {
   TiPa_Concrete* ContractorParser  = TiPa_Concrete::Att.ContractorParser[Index];
                  Character         = skip_parsing(Character, end);     // skip text-parts which should be ignored

   LOG_OUTPUT(LOG_OFF,  "Sequence Hard in: " << Character);

   Character         = ContractorParser->parser_Test(Character,end,sponsorGuard);

   if((Character!=nullptr)&&(Character <= end))
   {
    sponsorGuard->contractorResultAccept();

    ReturnValue = Character ;
   }
   else
   {
    sponsorGuard->contractorResultClear();

    ReturnValue = nullptr;
    break;
   }
   ++ Index; // prepare search for next contractor-parser
  }

  return(ReturnValue);
 }








/* @MRTZ_describe parser_Test_Default

*/
 const char* TiPa_Sequence::parser_Test_Default(CONST_CHAR_UNUSED*           begin,
                                                CONST_CHAR_UNUSED*           end,
                                                TIPA_RESULT_ABSTRACT_UNUSED* sponsorGuard)
 {
  const char*    ReturnValue = nullptr;      // return of failure
/*
  TiPa_Concrete* ContractorParser0 = nullptr;
  TiPa_Concrete* ContractorParser1 = nullptr;
  const char*    SearchChar  = nullptr;
  ParserResult*  ContractorResult = nullptr;

  ContractorParser0 = TiPa_Concrete::Att.ContractorParser[0];
  ContractorParser1 = TiPa_Concrete::Att.ContractorParser[1];
*/

  return(ReturnValue);
 }




















//}; USING_NAMESPACE CL_TIPA;


//namespace CL_TIPA {








/* @MRTZ_describe TiPa_Condition

*/
 TiPa_Condition::TiPa_Condition(DataModel* contextModel)
                :TiPa_Concrete(contextModel)
 {
  TiPa_Concrete::Att.MaxOperand = 1;
  Mbr.Dircetive                 = PrDr_Default;
 }






/* @MRTZ_describe TiPa_Condition

*/
 TiPa_Condition::TiPa_Condition(TiPa_Concrete* parser0,
                                TiPa_Concrete* parser1,
                  DataModel* contextModel,
                                Parser_id      type)
                :TiPa_Concrete(contextModel, type, 1)
 {
  Mbr.Dircetive = PrDr_Default;

  TiPa_Concrete::Att.MaxOperand = 2;

  this->contractor_ParserInsert(parser0,0);
  this->contractor_ParserInsert(parser1,1);
 }

/* @MRTZ_describe TiPa_Condition

*/
 TiPa_Condition::TiPa_Condition(Parser_id       operation,
                                TiPa_Concrete*  parser0,
                                TiPa_Concrete*  parser1,
                   DataModel* contextModel,
                                ParserDirective directive)
                :TiPa_Concrete(contextModel, (TiPa_ID)operation, 1)
{
  this->init(operation,
             parser0,
             parser1,
             directive);

}



/* @MRTZ_describe ~TiPa_Condition

*/
 TiPa_Condition::~TiPa_Condition(void)
 {

 }




/* @MRTZ_describe init

*/
TiPa_Condition* TiPa_Condition::init(Parser_id       operation,
                                     TiPa_Concrete*  parser0,
                                     TiPa_Concrete*  parser1,
                                     ParserDirective directive)
{
  TiPa_Concrete::Att.SubType = (TiPa_ID)operation;

  switch(operation)
  {
   case Cnd_OrExc :   // next part detection of exclude-or (^)
   {
    Mbr.Dircetive = directive;
    TiPa_Concrete::Att.MaxOperand = INT_MAX;
                      // since it is possible to add more contractor-Parsers
    this->contractor_ParserInsert(parser0,0);
    this->contractor_ParserInsert(parser1,1);
   }break;
   case Cnd_OrInc :   // next part detection of inclusive-or (|)
   {
    Mbr.Dircetive = directive;
    TiPa_Concrete::Att.MaxOperand = INT_MAX;
                      // since it is possible to add more contractor-Parsers
    this->contractor_ParserInsert(parser0,0);
    this->contractor_ParserInsert(parser1,1);
   }break;
   case Cnd_And :     // next part detection of and (&)
   {
    Mbr.Dircetive = directive;
    TiPa_Concrete::Att.MaxOperand = INT_MAX;
                     // since it is possible to add more contractor-Parsers
    this->contractor_ParserInsert(parser0,0);
    this->contractor_ParserInsert(parser1,1);
   }break;
   case Cnd_WthOt :   // next part detection of without (-)
   {
    Mbr.Dircetive = directive;
    TiPa_Concrete::Att.MaxOperand = 1;
                     // since it is possible to add no more contractor-Parsers
    this->contractor_ParserInsert(parser0,0);
    this->contractor_ParserInsert(parser1,1);
   }break;
   case Cnd_NotValide :
   case Cnd_Default   : // unspecified parser of binary or sequence operator
   default :
   {
    Mbr.Dircetive = directive;
    TiPa_Concrete::Att.MaxOperand = INT_MAX;
                      // since it is possible to add more contractor-Parsers
    TiPa_Concrete::Att.SubType = Cnd_NotValide;
   }break;
  }
  return(this);
}









/* @MRTZ_describe inclusion

*/
TiPa_Condition* TiPa_Condition::inclusion(TiPa_Concrete*  parser0,
                                          TiPa_Concrete*  parser1,
                                          ParserDirective directive)
{
 init(Cnd_And, parser0, parser1, directive);
 return(this);
}


/* @MRTZ_describe or

*/
TiPa_Condition* TiPa_Condition::incOr(TiPa_Concrete*  parser0,
                                      TiPa_Concrete*  parser1,
                                      ParserDirective directive)
{
 init(Cnd_OrInc, parser0, parser1, directive);
 return(this);
}



/* @MRTZ_describe exOr

*/
TiPa_Condition* TiPa_Condition::exOr(TiPa_Concrete*  parser0,
                                     TiPa_Concrete*  parser1,
                                     ParserDirective directive)
{
 init(Cnd_OrExc, parser0, parser1, directive);
 return(this);
}


/* @MRTZ_describe exclusion

*/
TiPa_Condition* TiPa_Condition::exclusion(TiPa_Concrete*  parser,
                                          TiPa_Concrete*  without,
                                          ParserDirective directive)
{
 init(Cnd_WthOt, parser, without, directive);
 return(this);
}
















/* @MRTZ_describe include

*/
void TiPa_Condition::include(TiPa_Concrete*  parser)
{

  switch(TiPa_Concrete::Att.SubType)
  {
   case Cnd_OrExc :   // next part detection of exclude-or (^)
   case Cnd_OrInc :   // next part detection of inclusive-or (|)
   case Cnd_And :     // next part detection of and (&)
   {
    this->contractor_ParserInsert(parser,-1); // insert at the end
   }break;
   case Cnd_WthOt :   // next part detection of without (-)
   case Cnd_Default : // unspecified parser of binary or sequence operator
   default :
   {
                      // ignore input
   }break;
  }
 }





/* @MRTZ_describe inclusive

*/
TiPa_Condition* TiPa_Condition::inclusive(TiPa_Concrete*  parser)
{
 if(TiPa_Concrete::Att.SubType == Cnd_And)
 {
  this->contractor_ParserInsert(parser,-1); // insert at the end
 }
 else
 {
                                            // ignore input
 }

 return(this);
}


/* @MRTZ_describe incOr

*/
TiPa_Condition* TiPa_Condition::incOr(TiPa_Concrete*  parser)
{
 if(TiPa_Concrete::Att.SubType == Cnd_OrInc)
 {
  this->contractor_ParserInsert(parser,-1); // insert at the end
 }
 else
 {
                                            // ignore input
 }

 return(this);
}


/* @MRTZ_describe exOr

*/
TiPa_Condition* TiPa_Condition::exOr(TiPa_Concrete*  parser)
{
 if(TiPa_Concrete::Att.SubType == Cnd_OrExc)
 {
  this->contractor_ParserInsert(parser,-1); // insert at the end
 }
 else
 {
                                            // ignore input
 }

 return(this);
}










/* @MRTZ_describe id_Class

*/
TiPa_Concrete::TDA_TiPa_CLASS_TP TiPa_Condition::id_Class(void)
{
 return(TDA_TiPa_Condition);
}






/* @MRTZ_describe id_Type

*/
inline TiPa_Concrete::TDA_TiPa_CLASS_TP TiPa_Condition::id_Type(void)
{
 return(TDA_TiPa_Condition);
}













/* @MRTZ_describe parser_test

 */
 const char* TiPa_Condition::parser_Test(const char* begin, const char* end, TiPa_Result_Abstract* sponsorGuard)
 {
  const char*    ReturnValue = nullptr;                                         // return of failure

  LOG_OUTPUT(LOG_OFF,  string("Condition :") << begin);

  begin = skip_parsing(begin, end);                                             // skip text-parts which should be ignored

  if(   Storage.Result.find(begin)
     != Storage.Result.end()
    )// already found before
  {
   if(sponsorGuard != nullptr)
    sponsorGuard->contractorResultProvide(&Storage.Result[begin]);

   ReturnValue = endOfHitResult(begin);                                         // positive return
   if((ReturnValue < begin) && (ReturnValue > end))
    cout << endl << "invalid result-store content in TiPa_Condition found" << endl;

   Storage.Current = Storage.Result.find(begin);                                // positive return
                                                                                // buffer last result
   setCurrentHitLocation(begin, ReturnValue);
  }
  else if(  (begin                                 <  end)
          &&(Mbr.AlreadyCalled.find(begin)         == Mbr.AlreadyCalled.end())
         )                                                                      // not found before but valid hit

  {

   Mbr.AlreadyCalled.insert(begin);

   TiPa_Result_Abstract*  ResultGuard = TiPa_Result::defineResultGuard(sponsorGuard, this);

   switch(TiPa_Concrete::Att.SubType)
   {
    case Cnd_OrExc :   // next part detection of exclude-or (^)
    {
 #if defined(DEBUG_OUTPUT)
     printf("Cmb_OrExc\n");
 #endif // defined(DEBUG_OUTPUT_LOG)
     ReturnValue = parser_Test_OrExc(begin, end, ResultGuard);
    }break;
    case Cnd_OrInc :                                                            // next part detection of inclusive-or (|)
    {
 #if defined(DEBUG_OUTPUT)
      printf("Cmb_OrInc\n");
 #endif // defined(DEBUG_OUTPUT)
     ReturnValue = parser_Test_OrInc(begin, end, ResultGuard);
    }break;
    case Cnd_And :                                                              // next part detection of and (&)
    {
 #if defined(DEBUG_OUTPUT)
     printf("Cmb_And\n");
 #endif // defined(DEBUG_OUTPUT)
     ReturnValue = parser_Test_And(begin, end, ResultGuard);
    }break;
    case Cnd_WthOt :                                                            // next part detection of without (-)
    {
 #if defined(DEBUG_OUTPUT)
      printf("Cmb_WthOt\n");
 #endif // defined(DEBUG_OUTPUT)
     ReturnValue = parser_Test_WthOt(begin, end, ResultGuard);
    }break;
    case Cnd_Default :                                                          // unspecified parser of binary or sequence operator
    {
 #if defined(DEBUG_OUTPUT)
     printf("Cmb_Default\n");
 #endif // defined(DEBUG_OUTPUT)
     ReturnValue = parser_Test_Default(begin, end, ResultGuard);
    }break;
    default :
    {
 #if defined(DEBUG_OUTPUT)
     printf("??????  %d\n",TiPa_Concrete::Att.Type);
 #endif // defined(DEBUG_OUTPUT)
     ReturnValue = nullptr;
    }break;
   }
   Mbr.AlreadyCalled.erase(begin);

   if(ReturnValue   != nullptr)                                                 // existing Result should be stored for later analysis
   {
    LOG_OUTPUT(LOG_OFF, string("TiPa_Condition::parser_Test hit ") + string(begin, ReturnValue) +"|");
     Storage.Current = ResultGuard->storeResult(begin, ReturnValue);

    if(TiPa_Concrete::Att.ReactionHit != nullptr)                               // user-reaction for parser-hit is defined
     TiPa_Concrete::Att.ReactionHit->processHit(this, Storage.Result[begin]);
                                                                                // start user reaction
    setCurrentHitLocation(begin, ReturnValue);
   }
   else                                                                         // negative result
   {
    setCurrentHitLocation(nullptr, nullptr);
   }
   delete(ResultGuard);
  }
  else                                                                          // no text left after skip-parsing
  {
   if(Mbr.AlreadyCalled.find(begin) != Mbr.AlreadyCalled.end())
   {
    cout << "TiPa_Condition recursive call with \n|" << begin << "| |" << endl;
   }
   ReturnValue = nullptr;                                                       // negative return
   setCurrentHitLocation(nullptr, nullptr);
 }

  return(ReturnValue);
 }




/* @MRTZ_describe equal_Parser

*/
 bool TiPa_Condition::equal_Parser(TiPa_Concrete* parser)
 {
  bool                               ReturnValue = false;
  map<int, TiPa_Concrete*>::iterator Item;
  map<int, TiPa_Concrete*>::iterator ThisItem;
  TiPa_Condition*                    Parser      = static_cast<TiPa_Condition*>(parser) ;


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
  else if(  (Parser->TiPa_Concrete::Att.ContractorParser.size())
          !=(  this->TiPa_Concrete::Att.ContractorParser.size())
         )
  // the given parser has not the same number of contractor parsers as this parser
  {
   ReturnValue = false;
  }
  else
  // item of given parser is part of this parsers item container
  {
   Item     = Parser->TiPa_Concrete::Att.ContractorParser.begin();
   ThisItem =         TiPa_Concrete::Att.ContractorParser.begin();

   while(  (Item     != Parser->TiPa_Concrete::Att.ContractorParser.end())
         &&(ThisItem !=   this->TiPa_Concrete::Att.ContractorParser.end())
        )
   // iterate over configuration of this and the given parser
   {
    if((*Item) != (*ThisItem))
    // the contractor-parser of the given parser is not the same as the contractor parser of this one
    {
     ReturnValue = false;

     break;
    }
    else
    // both items have a different size or/and a different content
    {
     ++ Item;
     ++ ThisItem;
    }
   }
  }
  return(ReturnValue);
 }








/* @MRTZ_describe parser_Test_OrExc

*/
 const char* TiPa_Condition::parser_Test_OrExc(const char*           begin,
                                               const char*           end,
                                               TiPa_Result_Abstract* sponsorGuard)
 {
  const char* ReturnValue       = nullptr;      // return of failure

  int         Index             = 0;
  while(   TiPa_Concrete::Att.ContractorParser.find(Index)
        != TiPa_Concrete::Att.ContractorParser.end()
       )
  {
   TiPa_Concrete* ContractorParser  = TiPa_Concrete::Att.ContractorParser[Index];
   ++ Index; // prepare search for next contractor-parser

   const char* Character = ContractorParser->parser_Test(begin,end,sponsorGuard);

   if(  (ReturnValue == nullptr)
      &&(Character   != nullptr)
      &&(Character   <= end )
     )// no match before and currently valid match found
   {
    sponsorGuard->contractorResultAccept();

    ReturnValue = Character ;
   }
   else if(  (ReturnValue != nullptr)
           &&(Character   != nullptr)
           &&(Character   <= end )
     )// match already found before and currently valid match found
   {
    sponsorGuard->contractorResultClear();

    ReturnValue = nullptr;      // return of failure
    break;                      // stop search since exclusive condition finally failed by second match
   }
   else
   {
   }
  }
  return(ReturnValue);
 }







/* @MRTZ_describe parser_Test_OrInc

*/
 const char* TiPa_Condition::parser_Test_OrInc(const char*           begin,
                                               const char*           end,
                                               TiPa_Result_Abstract* sponsorGuard)
 {
  const char*                  ReturnValue      = nullptr;      // return of failure
  unsigned int                 Size             = TiPa_Concrete::Att.ContractorParser.size();
  const char**                 Character        = new const char*[Size];
//  TiPa_Concrete::DataSponsor** ContractorResult = new TiPa_Concrete::DataSponsor*[Size];
  Hit_TP**                     ContractorResult = new Hit_TP*[Size];
  int                          Index            = 0;

  while(   TiPa_Concrete::Att.ContractorParser.find(Index)
        != TiPa_Concrete::Att.ContractorParser.end()
       )
  {
   TiPa_Concrete* ContractorParser  = TiPa_Concrete::Att.ContractorParser[Index];
   Character[Index]  = ContractorParser->parser_Test(begin,end,sponsorGuard);

   if((Character[Index]!=nullptr)&&(Character[Index] <= end))
   {
    ContractorResult[Index] = sponsorGuard->contractorResultGet();

    ReturnValue        = Character[Index] ;

    if(  (Mbr.Dircetive == PrDr_First)
       ||(Mbr.Dircetive == PrDr_Default)
      ) // no need for further tests
    {
     break; // avoid recursive calls
    }

   }
   else
   {
   }
   ++ Index; // prepare search for next contractor-parser
  }

  if(ReturnValue!=nullptr)
  {
   for(int Result = 0; Result <= Index; ++Result)
   {
    if(Character[Result] != nullptr)
    {
     switch(Mbr.Dircetive)
     {
      case PrDr_Longest:
      {
       if(ReturnValue < Character[Result])
       {
        if(ContractorResult[Result] != nullptr)
        {
         sponsorGuard->contractorResultStore(ContractorResult[Result]);
        }
        ReturnValue = Character[Result];
       }
       else
       { }
      }
      break;

      case PrDr_Shortest:
      {
       if(ReturnValue > Character[Result])
       {
        if(ContractorResult[Result] != nullptr)
        {
         sponsorGuard->contractorResultStore(ContractorResult[Result]);
        }
        ReturnValue = Character[Result];
       }
       else
       { }
      }
      break;

      case PrDr_Last:
      {
       sponsorGuard->contractorResultClear();

       if(ContractorResult[Result] != nullptr)
       {
        sponsorGuard->contractorResultStore(ContractorResult[Result]);
       }
       ReturnValue = Character[Result];
      }
      break;

      case PrDr_First:
      case PrDr_Default:
      default:
      {
       sponsorGuard->contractorResultClear();

       if(ContractorResult[Result] != nullptr)
       {
        sponsorGuard->contractorResultStore(ContractorResult[Result]);
       }
       else
       {
       }
       ReturnValue = Character[Result];
       Result      = Index + 1;
      }
      break;
     }
    }
    else
    {
    }
   }
  }
  delete[](Character);
  delete[](ContractorResult);

  return(ReturnValue);
 }







/* @MRTZ_describe parser_Test_And

*/
 const char* TiPa_Condition::parser_Test_And(const char*           begin,
                                             const char*           end,
                                             TiPa_Result_Abstract* sponsorGuard)
 {
  const char*                  ReturnValue      = nullptr;      // return of failure
  unsigned int                 Size             = TiPa_Concrete::Att.ContractorParser.size();
  const char**                 Character        = new const char*[Size];
//  TiPa_Concrete::DataSponsor** ContractorResult = new TiPa_Concrete::DataSponsor*[Size];
  Hit_TP**                     ContractorResult = new Hit_TP*[Size];
  int                          Index            = 0;

  while(   TiPa_Concrete::Att.ContractorParser.find(Index)
        != TiPa_Concrete::Att.ContractorParser.end()
       )
  {
   TiPa_Concrete* ContractorParser  = TiPa_Concrete::Att.ContractorParser[Index];

   Character[Index] = ContractorParser->parser_Test(begin,end,sponsorGuard);

   if((Character[Index]!=nullptr)&&(Character[Index] <= end))
   {
    ContractorResult[Index] = sponsorGuard->contractorResultGet();

    ReturnValue        = Character[Index] ;
   }
   else
   {
    sponsorGuard->contractorResultClear();

    ReturnValue = nullptr;      // return of failure
    break;
   }
   ++ Index;                    // prepare search for next contractor-parser
  }

  if(ReturnValue!=nullptr)
  {
   for(int Result = 0; Result <= Index; ++Result)
   {
    if(Character[Result] != nullptr)
    {
     switch(Mbr.Dircetive)
     {
      case PrDr_Longest:
      {
       if(ReturnValue < Character[Result])
       {
        if(ContractorResult[Result] != nullptr)
        {
         sponsorGuard->contractorResultStore(ContractorResult[Result]);
        }
        ReturnValue = Character[Result];
       }
       else
       { }
      }
      break;

      case PrDr_Shortest:
      {
       if(ReturnValue > Character[Result])
       {
        if(ContractorResult[Result] != nullptr)
        {
         sponsorGuard->contractorResultStore(ContractorResult[Result]);
        }
        ReturnValue = Character[Result];
       }
       else
       { }
      }
      break;

      case PrDr_Last:
      {
       sponsorGuard->contractorResultClear();

       if(ContractorResult[Result] != nullptr)
       {
        sponsorGuard->contractorResultStore(ContractorResult[Result]);
       }
       ReturnValue = Character[Result];
      }
      break;

      case PrDr_First:
      case PrDr_Default:
      default:
      {
       sponsorGuard->contractorResultClear();

       if(ContractorResult[Result] != nullptr)
       {
        sponsorGuard->contractorResultStore(ContractorResult[Result]);
       }
       ReturnValue = Character[Result];
       Result = Index + 1;
      }
      break;
     }
    }
    else
    {
    }
   }
  }
  delete[](Character);
  delete[](ContractorResult);

  return(ReturnValue);
 }







/* @MRTZ_describe parser_Test_WthOt

*/
 const char* TiPa_Condition::parser_Test_WthOt(const char*           begin,
                                               const char*           end,
                                               TiPa_Result_Abstract* sponsorGuard)
 {
  const char*     ReturnValue       = nullptr;                                // return of failure
  TiPa_Concrete*  ContractorParser1 = TiPa_Concrete::Att.ContractorParser[1];

  if(ContractorParser1->parser_Test(begin,end,sponsorGuard) == nullptr)       // parser-1 fails
  {
   TiPa_Concrete*  ContractorParser0 = TiPa_Concrete::Att.ContractorParser[0];

   ReturnValue = ContractorParser0->parser_Test(begin,end,sponsorGuard);

   sponsorGuard->contractorResultAccept();
  }
  else
  {
   sponsorGuard->contractorResultClear();

   ReturnValue  = nullptr;                                                    // return of failure
  }

  return(ReturnValue);
 }












/* @MRTZ_describe parser_Test_Default

*/
 const char* TiPa_Condition::parser_Test_Default(CONST_CHAR_UNUSED*            begin,
                                                 CONST_CHAR_UNUSED*            end,
                                                 TIPA_RESULT_ABSTRACT_UNUSED*  sponsorGuard)
 {
  const char*    ReturnValue = nullptr;      // return of failure
/*
  TiPa_Concrete* ContractorParser0 = nullptr;
  TiPa_Concrete* ContractorParser1 = nullptr;
  const char*    SearchChar  = nullptr;
  ParserResult*  ContractorResult = nullptr;

  ContractorParser0 = TiPa_Concrete::Att.ContractorParser[0];
  ContractorParser1 = TiPa_Concrete::Att.ContractorParser[1];
*/

  return(ReturnValue);
 }







#ifndef DOXYGEN
//}; USING_NAMESPACE CL_TIPA;
//}; USING_NAMESPACE CL_TIPA_CONCRETE;
//}; USING_NAMESPACE TDA_TinyParser;
//}; USING_NAMESPACE TXTDIASM;
#undef  USING_NAMESPACE
#endif //DOXYGEN



