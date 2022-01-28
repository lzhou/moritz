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

#define DEBUG_OUTPUT_LOG
#include "TiPa_Concrete.h"
#include "TiPa_Combination.h"
#include "TiPa_Counter.h"
#include "TiPa_Character.h"
#include "TiPa_String.h"
#include "TiPa_Rule.h"



#include "TiPa_Data.h"
//#include "TiPa_Result.h"
//#include "TiPa_Result_Collector.h"
//#include "TiPa_Result_Terminate.h"
//#include "TiPa_Result_Skip.h"
#include <ctime>
#include <cstring>


#ifndef DOXYGEN
//namespace TXTDIASM {
//namespace TDA_TinyParser {
////namespace CL_TIPA_CONCRETE {
#endif //DOXYGEN



 const char* TiPa_Concrete::Name[37] =
 {
   "character [one special]",
   "character [one of a range]",
   "character [one of a group]",
   "character {alphanumeric}",
   "character {letter}",
   "character {any}",
   "character {space or tab}",
   "character {control}",
   "character {digit}",
   "character {non-space printable}",
   "character {lower-case letter}",
   "character {printable}",
   "character {punctuation mark}",
   "character {plus or minus sign}",
   "character {white space character}",
   "character {upper-case letter}",
   "character {binary digit}",
   "character {octagonal digit}",
   "character {hexadecimal digit}",

   "string [common]",
   "string {begin of line comment}",
   "string {begin of block comment}",

   "count [min to max]",
   "count [one ore more]",
   "count [zero]",
   "count [zero or more]",
   "count [of zero or one]",

   "combination [common]",
   "combination [exclusive or (one of many)]",
   "combination [inclusive or (one or more of many)]",
   "combination [and (all of many)]",
   "combination [hit and exclusion (one but not an other)]",
   "combination [separator list(table sell sequence)]",
   "combination [soft sequence]",
   "combination [hard sequence]",

   "rule",

   "parser not valid !!! result of an error !!!"
 };






/* @MRTZ_describe TiPa_Concrete

*/
 TiPa_Concrete::TiPa_Concrete(DataModel* contextModel)
               :TiPa_Abstract()
 {
  Att.SubType        = -1,//NotValidParser;
  Att.MaxOperand     = -1;
  Att.RecursiveCalls = 0;
  Att.SkipParser     = nullptr;

  Storage.Current    = Storage.Result.end();
  Att.ContextModel   = contextModel;
  Att.ReactionHit    = nullptr;
 }



/* @MRTZ_describe TiPa_Concrete

*/
 TiPa_Concrete::TiPa_Concrete(DataModel* contextModel,
                              TiPa_ID    type,
                              int        maxOperand)
               :TiPa_Abstract()
 {
  Att.SubType        = type;
  Att.MaxOperand     = maxOperand;
  Att.RecursiveCalls = 0;
  Att.SkipParser     = nullptr;

  Storage.Current    = Storage.Result.end();

  Att.ContextModel   = contextModel;
  Att.ReactionHit    = nullptr;
 }




/* @MRTZ_describe ~TiPa_Concrete

*/
 TiPa_Concrete::~TiPa_Concrete(void)
 {
  Storage.Result.clear();
  Storage.NonHit.clear();

  Storage.Current = Storage.Result.end();

  Att.ContractorParser.clear();

  Att.SkipParser = nullptr;
  if(Att.ReactionHit == nullptr)
  {
//   Att.ReactionHit = nullptr;
  }
 }



///* @ MRTZ _ describe as_TiPa_Concrete
//
//*/
//inline TiPa_Concrete* TiPa_Concrete::as_TiPa_Concrete(void)
//{
// return(this);
//}



/* @MRTZ_describe init

*/
 void TiPa_Concrete::init(TiPa_ID type)
 {
   Att.SubType = type;
 }



/* @MRTZ_describe id_Class

*/
TiPa_Concrete::TDA_TiPa_CLASS_TP TiPa_Concrete::id_Class(void)
{
 return(TDA_TiPa_Concrete);
}

/* @MRTZ_describe id_Type

*/
inline TiPa_Concrete::TDA_TiPa_CLASS_TP  TiPa_Concrete::id_Type(void)
{
 return(TDA_TiPa_Concrete);
}

/* @MRTZ_describe id_SubType

*/
inline int TiPa_Concrete::id_SubType(void)
{
 return(Att.SubType);
}




/* @MRTZ_describe skip_ParserSet

*/
 void TiPa_Concrete::skip_ParserSet(TiPa_Concrete* parser)
 {
   Att.SkipParser = parser;
 }

/* @MRTZ_describe skip_ParserGet

*/
 TiPa_Concrete* TiPa_Concrete::skip_ParserGet(void)
 {
  return(Att.SkipParser);
 }

/* @MRTZ_describe skip_parsing

*/
 const char* TiPa_Concrete::skip_parsing(const char* begin, const char* end)
 {
  const char* ReturnValue   = begin;    // start with first character of given string
  static bool AlreadyCalled = false;    // skip-parsing is already active

  if(AlreadyCalled == false)            // no nested call
  {
   AlreadyCalled = true;                // prevent endless skip-parsing loops by nested callings

   LOG_OUTPUT(LOG_OFF, "skip parsing begin ....  " << begin);

   if(Att.SkipParser != nullptr)
   {
    const char* Character = Att.SkipParser->parser_Test(begin,end);

    while(  (Character   != nullptr)
          &&(Character   < end )
         )
    {
     LOG_OUTPUT(LOG_OFF, "to skip : " << Character);
     ReturnValue = Character;
     Character   = Att.SkipParser->parser_Test(Character,end);
    }
   }
   else
   { }

   LOG_OUTPUT(LOG_OFF, " .... skip parsimg end "<<ReturnValue);

   AlreadyCalled = false;              // set free for next parser
  }

  return(ReturnValue);
 }



/* @MRTZ_describe contractor_ParserInsert

*/
 bool TiPa_Concrete::contractor_ParserInsert(TiPa_Concrete* contractorParser, int operand)
 {
  bool ReturnValue = true;

  if(  (operand >= 0             )
     &&(operand <= Att.MaxOperand)
    )
  {
   Att.ContractorParser[operand] = contractorParser;
  }
  else if(operand < 0)
  {
   Att.ContractorParser[ Att.ContractorParser.size()] = contractorParser;
  }
  else
  {
   ReturnValue = false;
  }

  return(ReturnValue);
 }


/* @MRTZ_describe contractor_ParserGet

*/
map<int, TiPa_Concrete*> TiPa_Concrete::contractor_ParserGet(void)
{
  return(Att.ContractorParser);
}


/* @MRTZ_describe contractor_ParserGet

*/
int TiPa_Concrete::contractor_ParserCounter(void)
{
 return(Att.ContractorParser.size());
}


/* @MRTZ_describe parser_Search

*/
 const char* TiPa_Concrete::parser_Search(const char* begin, const char* end)
 {
  const char* ReturnValue = begin;     // start with first character of given string

  while(  (ReturnValue                   != end)
        &&(parser_Test(ReturnValue, end) == nullptr)
        )//   until end of given string reached
         //or until current character contains a hit
  {
   ++ ReturnValue;                     // change to next character
  }
  return(ReturnValue);
 }


/* @MRTZ_describe parser_Scan

*/
 const char* TiPa_Concrete::parser_Scan(const char* begin, const char* end, ParserScanMode_TP overlap)
 {
  const char* ReturnValue      = end;          // return of no match found

  const char* CurrentCharacter = begin;        // start with first character of given string
  while(  (CurrentCharacter != nullptr)
        &&(CurrentCharacter <  end)
        )                                      // until end of given string reached
  {

   LOG_OUTPUT(LOG_OFF,  string(CurrentCharacter,end));

   const char* CurrentResult = parser_Test(CurrentCharacter, end);
   if(CurrentResult != nullptr)                // current character is a match
   {
    ReturnValue      = CurrentResult;          // store result
    if(  (overlap          == OverlappingScan)
       ||(CurrentCharacter == CurrentResult)
       )                                       // scan for all possible hits
                                               // if no hit is a valid hit (example zeroOrOne, zeroOrMore, ...)
     ++ CurrentCharacter;                      // restart parsing with next character of the given string
    else                                       // ignore overlapping hits
     CurrentCharacter = CurrentResult;         // restart parsing after last hit
   }
   else
   ++ CurrentCharacter;                        // change to next character
  }

  return(ReturnValue);
 }




/* @MRTZ_describe result_Dictionary

*/
 map<const char*, TiPa_Concrete::Hit_TP >* TiPa_Concrete::result_Dictionary(void)
 {
  return(&(Storage.Result));
 }






/* @MRTZ_describe result_Hit

*/
 TiPa_Concrete::Hit_TP* TiPa_Concrete::result_Hit(const char* begin)
 {
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<" TiPa_Concrete::result_Hit enter"<< this <<"|"<<begin<<"|"<<endl;
//  TiPa_Concrete::DataSponsor* ReturnValue = nullptr;
  TiPa_Concrete::Hit_TP* ReturnValue = nullptr;

  if(  (begin            == nullptr            )
     &&(Storage.Current != Storage.Result.end())
    )
  {
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<" TiPa_Concrete::result_Hit "<< this <<endl;
   ReturnValue = &(Storage.Current->second);
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<" TiPa_Concrete::result_Hit "<< this <<endl;
  }
  else if(  (begin                      != nullptr             )
          &&(Storage.Result.find(begin) != Storage.Result.end())
         )
  {
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<" TiPa_Concrete::result_Hit "<< this <<endl;
   ReturnValue = &(Storage.Result.find(begin)->second);
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<" TiPa_Concrete::result_Hit "<< this <<endl;
  }
//  else if(Att.ContractorParser.empty() == false)
//  {
//   map<int, TiPa_Concrete*>::iterator SubParser = Att.ContractorParser.begin();
//   while(SubParser != Att.ContractorParser.end())
//   {
//    ReturnValue = SubParser->second->result_Hit(begin);
//    if(ReturnValue == nullptr)
//     ++ SubParser;
//    else
//     SubParser = Att.ContractorParser.end();
//   }
//  // ;
//  }
  else
  {
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<" TiPa_Concrete::result_Hit "<< this <<endl;
  // ReturnValue = nullptr;
  // keep return-value undefined
  }
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<" TiPa_Concrete::result_Hit leave"<< this <<endl;

  return(ReturnValue);
 }








/* @MRTZ_describe result_Tree

*/
 TiPa_Concrete::Hit_TP* TiPa_Concrete::result_Tree(const char* begin)
 {
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<" TiPa_Concrete::result_Tree enter"<< this <<endl;
#if defined(DEBUG_OUTPUT)
 static int Counter = 0;
  ++Counter;
#endif //DEBUG_OUTPUT


  TiPa_Concrete::Hit_TP* ReturnValue = this -> result_Hit(begin);
//  if(ReturnValue != nullptr)
//  {
//   TiPa_Data* ContractorData = nullptr;
//
//   TiPa_Concrete::DataAssociation* Contractor = ReturnValue->contractorFirst_get();
//   while(Contractor != nullptr)
//   {
//    ContractorData = Contractor->data_get();
//
//    if(ContractorData != nullptr)
//    {
//     ContractorData->Parser->as_TiPa_Concrete()->result_Tree(ContractorData->Begin);
//    }
//
//    Contractor = ReturnValue->contractorBehind_get(Contractor);
//   }
//  }
//  else
//  {
//  }

#if defined(DEBUG_OUTPUT)
  -- Counter;
#endif //DEBUG_OUTPUT
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<" TiPa_Concrete::result_Tree leave"<< this <<endl;
  return(ReturnValue);
 }









/* @MRTZ_describe result_Text

*/
 char* TiPa_Concrete::result_Text(char* text, int size, const char* begin)
 {
  TiPa_Concrete::Hit_TP* Hit = this -> result_Hit(begin);

  if(  (Hit        != nullptr)
     &&(Hit->Begin != nullptr)
     &&(Hit->End   != nullptr)
    )
  {
   unsigned int Size = 0;
   if(size <= 0)                                   // size not given by user
    Size = (Hit->End - Hit->Begin)+1;              // calculate size of result
   else                                            // valid size given by user
    Size = size;

   if(text == nullptr)                             // user provides a pointer only
   {
    text = new char[Size];                         // create new buffer
   }
   else                                            // user provides a buffer with its size
   {
    if(strlen(text) < Size)                        // result is smaller than the buffer
     Size = strlen(text);                          // reduce size
   }
   memset(text,0,Size);                            // clear buffer content

   if( Hit->Begin < Hit->End )
   {
    memcpy(text,Hit->Begin,Size);                  // copy the result or a part
   }
   else
   {
   }
  }
  else
  {
  }
  return(text);
 }




/* @MRTZ_describe result_clear

*/
 void TiPa_Concrete::result_clear(void)
 {
  Storage.NonHit.clear();

  if(!(Storage.Result.empty()))                         // result contains something
  {
//   Storage.Result.clear();                              //clear local content

   while(Storage.Result.empty() == false)
   {
    Storage.Result.erase(Storage.Result.begin());
   }


   Storage.Current = Storage.Result.end();                  // reset current result

   map<int, TiPa_Concrete*>::iterator Contractor = Att.ContractorParser.begin();
   while(Contractor != Att.ContractorParser.end())  // check contractor-parsers
   {
    if((Contractor->second)!= nullptr)
     (Contractor->second)->result_clear();
    ++Contractor;
   }
  }
  else // result is already deleted one call before
  {
   // no action necessary since contractor-parsers where cleared before also
  }

  if(Att.SkipParser != nullptr)
   Att.SkipParser->result_clear();

 }


/* describe contextModel_set

*/
void TiPa_Concrete::contextModel_set(DataModel* contextModel)
{
 Att.ContextModel = contextModel;
}



/* describe contextModel_get

*/
TiPa_Concrete::DataModel* TiPa_Concrete::contextModel_get(void)
{
 return(Att.ContextModel);
}




/* describe contextModel_set

*/
void TiPa_Concrete::reactionHit_set(TiPa_Reaction_Abstract* reaction)
{
 Att.ReactionHit = reaction;
}









/* describe resultTerminate

void TiPa_Concrete::resultTerminate(void)
{
 Storage.TerminateResult = true;
}
*/


/* @MRTZ_describe resultSkip

void TiPa_Concrete::resultStorage_Set(ResultStorage_TP mode)
{
 Storage.StorageType = mode;
}
*/






/* @MRTZ_describe defineResultGuard


TiPa_Result_Abstract* TiPa_Concrete::defineResultGuard(TiPa_Result_Abstract* sponsorGuard)
{
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"TiPa_Concrete::defineResultGuard Enter : " << (int)this <<endl;
  TiPa_Result_Abstract* Destination;

  switch(Storage.StorageType)                                                                          // check owner configuration
  {
   case ResStore_CollectTerminals:                                                                     // store only the results of character-, string- and rule parsers of directly or indirectly called sub-parsers
   {
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"TiPa_Concrete::defineResultGuard "<<endl;
    Destination = new TiPa_Result_Collector(this, &Storage.Result, sponsorGuard, TiPa_Result_Collector::CollectFor_Owner);
   } break;

   case ResStore_Terminate:                                                                            // provide a calling parser the own result as a leaf-result
   {
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"TiPa_Concrete::defineResultGuard "<<endl;
    Destination = new TiPa_Result_Terminate(this, &Storage.Result, sponsorGuard);
   } break;

   case ResStore_Skip:                                                                                 // provide a calling parser just the hit but no result-details
   {
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"TiPa_Concrete::defineResultGuard "<<endl;
    Destination = new TiPa_Result_Skip(this, &Storage.Result, sponsorGuard);
   } break;

   case ResStore_Default:                                                                              // store every single result
   {
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"TiPa_Concrete::defineResultGuard "<<endl;
    Destination = new TiPa_Result(this, &Storage.Result, sponsorGuard);
   } break;

   case ResStore_NV:                                                                                   // no valid user-configuration
   default:                                                                                            // no owner-configuration
   {
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"TiPa_Concrete::defineResultGuard "<<endl;
                                                                                                       // check sponsor-type
    if(sponsorGuard->as_TiPa_Result_Collector() != nullptr)                                            // sponsor stores terminal parser-results directly
    {
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"TiPa_Concrete::defineResultGuard "<<endl;
     Destination = new TiPa_Result_Collector(this, &Storage.Result, sponsorGuard,
                                             TiPa_Result_Collector::CollectFor_Sponsor);               // collect for sponsor
    }
    else if(sponsorGuard->as_TiPa_Result_Terminate() != nullptr)                                       // sponsor stores only own result by skipping sub-parser-results
    {
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"TiPa_Concrete::defineResultGuard "<<endl;
     Destination = new TiPa_Result_Skip(this, &Storage.Result, sponsorGuard);                          // skip own result
    }
    else if(sponsorGuard->as_TiPa_Result_Skip() != nullptr)                                            // sponsor skips its own results
    {
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"TiPa_Concrete::defineResultGuard "<<endl;
     Destination = new TiPa_Result_Skip(this, &Storage.Result, sponsorGuard);                          // skip own result
    }
    else                                                                                               // sponsor stores its own results but not by skipping sub-results
    {
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"TiPa_Concrete::defineResultGuard "<<endl;
     Destination = new TiPa_Result(this, &Storage.Result, sponsorGuard);                               // store own result
    }
   } break;
  }
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"TiPa_Concrete::defineResultGuard leave"<<endl;
  return(Destination);
}

*/





/* @MRTZ_describe endOfHitResult

*/
const char* TiPa_Concrete::endOfHitResult(const char* begin)
{

 if(Storage.Result.find(begin)!=Storage.Result.end())
 {
  TiPa_Concrete::Hit_TP  Data = Storage.Result[begin];
  return(Data.End);
 }
 else
 {
  return(nullptr);
 }
}


/* @MRTZ_describe currentBegin

*/
const char* TiPa_Concrete::currentBegin(void)
{
 return(Storage.CurrentBegin);
}

/* @MRTZ_describe currentEnd

*/
const char* TiPa_Concrete::currentEnd(void)
{
 return(Storage.CurrentEnd);
}





/* @MRTZ_describe typeString

*/
const char* TiPa_Concrete::typeString(void)
{
 switch(/*ParserClass*/id_Type())
 {
  case TiPa_Abstract::TDA_TiPa_Character:
  {
   switch(/*Parser->*/id_SubType())
   {
    case TiPa_Character::Single/*Character_Single*/    : return(Name[ 0]); break;
    case TiPa_Character::Range/*Character_Range*/      : return(Name[ 1]); break;
    case TiPa_Character::Group/*Character_Group*/      : return(Name[ 2]); break;
    case TiPa_Character::Alnum/*Alnum*/                : return(Name[ 3]); break;
    case TiPa_Character::Alpha/*Alpha*/                : return(Name[ 4]); break;
    case TiPa_Character::Anychar/*Anychar*/            : return(Name[ 5]); break;
    case TiPa_Character::Blank/*Blank*/                : return(Name[ 6]); break;
    case TiPa_Character::Cntrl/*Cntrl*/                : return(Name[ 7]); break;
    case TiPa_Character::Digit /*Digit*/               : return(Name[ 8]); break;
    case TiPa_Character::Graph/*Graph*/                : return(Name[ 9]); break;
    case TiPa_Character::Lower/*Lower*/                : return(Name[10]); break;
    case TiPa_Character::Print /*Print*/               : return(Name[11]); break;
    case TiPa_Character::Punct/*Punct*/                : return(Name[12]); break;
    case TiPa_Character::Sign /*Sign*/                 : return(Name[13]); break;
    case TiPa_Character::Space/*Space*/                : return(Name[14]); break;
    case TiPa_Character::Upper/*Upper*/                : return(Name[15]); break;
    case TiPa_Character::BinDigit/*BinDigit*/          : return(Name[16]); break;
    case TiPa_Character::OctDigit/*OctDigit*/          : return(Name[17]); break;
    case TiPa_Character::HexDigit/*HexDigit*/          : return(Name[18]); break;
    default                                            : return(Name[36]); break;
   }
  } break;
  case TiPa_Abstract::TDA_TiPa_String:
  {
   switch(/*Parser->*/id_SubType())
   {
    case TiPa_String::Default      /*String_Default*/  : return(Name[19]); break;
    case TiPa_String::CommentSingle/*CommentSingle*/   : return(Name[20]); break;
    case TiPa_String::CommentDouble/*CommentDouble*/   : return(Name[21]); break;
    default                                            : return(Name[36]); break;
   }
  } break;
  case TiPa_Abstract::TDA_TiPa_Counter:
  {
   switch(/*Parser->*/id_SubType())
   {
    case TiPa_Counter::Cnt_OneOrMore/*Uni_OneOrMore*/   : return(Name[23]); break;
    case TiPa_Counter::Cnt_AllButNot/*Uni_AllButNot*/   : return(Name[24]); break;
    case TiPa_Counter::Cnt_OptionMore/*Uni_OptionMore*/ : return(Name[25]); break;
    case TiPa_Counter::Cnt_OptionOne/*Uni_OptionOne*/   : return(Name[26]); break;
    default                                             : return(Name[36]); break;
   }
  } break;
  case TiPa_Abstract::TDA_TiPa_Sequence:
  {
   switch(/*Parser->*/id_SubType())
   {
    case TiPa_Sequence::Seq_Seprt/*Bin_Seprt*/         : return(Name[32]); break;
    case TiPa_Sequence::Seq_SftSq/*Bin_SftSq*/         : return(Name[33]); break;
    case TiPa_Sequence::Seq_HrdSq/*Bin_HrdSq*/         : return(Name[34]); break;
    default                                            : return(Name[36]); break;
   }
  } break;
  case TiPa_Abstract::TDA_TiPa_Condition:
  {
   switch(/*Parser->*/id_SubType())
   {
    case TiPa_Condition::Cnd_OrExc/*Bin_OrExc*/        : return(Name[28]); break;
    case TiPa_Condition::Cnd_OrInc/*Bin_OrInc*/        : return(Name[29]); break;
    case TiPa_Condition::Cnd_And  /*Bin_And*/          : return(Name[30]); break;
    case TiPa_Condition::Cnd_WthOt/*Bin_WthOt*/        : return(Name[31]); break;

   default                                             : return(Name[36]); break;
   }
  } break;
  case TiPa_Abstract::TDA_TiPa_Rule:
  {
   switch(/*Parser->*/id_SubType())
   {
    case TiPa_Rule::Default /*id of a rule*/           : return(Name[35]); break;
    default                                            : return(Name[36]); break;
   }
  } break;

  case TiPa_Abstract::TDA_TiPa_Concrete:
  default                                              : return(Name[36]); break;
 }

}












/* @MRTZ_describe setCurrentHitLocation

*/
void TiPa_Concrete::setCurrentHitLocation(const char* begin, const char* end)
{
 Storage.CurrentBegin = begin;
 Storage.CurrentEnd   = end;
}



#ifndef DOXYGEN
#define USING_NAMESPACE using namespace
//}; USING_NAMESPACE CL_TIPA_CONCRETE;
//}; USING_NAMESPACE TDA_TinyParser;
//}; USING_NAMESPACE TXTDIASM;
#undef  USING_NAMESPACE
#endif //DOXYGEN



