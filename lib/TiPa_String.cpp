/*!

 @file
 @brief definitions of an concrete parser-class to search for a single
        string or character-sequence

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
    01.03.2015     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    01.03.2015...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/

#define DEBUG_OUTPUT_LOG
#include "TiPa_String.h"
#include "TiPa_Reaction_Concrete.h"
#include "TiPa_Result.h"

#include <stdio.h>
#include <cstring>
#include "StringC_help.h"

using namespace std;

#ifndef DOXYGEN
//namespace TXTDIASM {
//namespace TDA_TinyParser {
////namespace CL_TIPA_CONCRETE {
//namespace CL_TIPA {
#endif //DOXYGEN






/* @MRTZ_describe TiPa_String

*/
 TiPa_String::TiPa_String(DataModel* contextModel)
             :TiPa_Concrete(contextModel)
 {

 }






/* @MRTZ_describe TiPa_String

*/
 TiPa_String::TiPa_String(const char*                  string,
                          int                          size,
                          DataModel* contextModel,
                          Parser_id                    type)
             :TiPa_Concrete(contextModel, type)
 {
  this->init(string, size,type);
 }

/* @MRTZ_describe TiPa_String

*/
 TiPa_String::TiPa_String(const char*                  string,
                          DataModel* contextModel,
                          Parser_id                    type)
             :TiPa_Concrete(contextModel, type)
 {
  this->init(string, type);
 }




/* @MRTZ_describe TiPa_String

*/
 TiPa_String::TiPa_String(Parser_id                    stringSet,
                          DataModel* contextModel)
             :TiPa_Concrete(contextModel, stringSet)
 {
  this->init(stringSet);
 }









/* @MRTZ_describe ~TiPa_String

*/
 TiPa_String::~TiPa_String(void)
 {
  set<const char*>::iterator Item;

  Item = Mbr.ParseItem.begin();
  while(Item != Mbr.ParseItem.end())
  {
   delete[](*Item);
   ++Item;
  }
  Mbr.ParseItem.clear();

 }






/* @MRTZ_describe TiPa_init

*/
TiPa_String* TiPa_String::init(const char* string,
                               int         size,
                               Parser_id   type)
 {
  char* String;
  String = new char[size+1];

  memset(String,0,size+1);
  memcpy(String,string,size);
  Mbr.ParseItem.insert(String);

  TiPa_Concrete::Att.SubType = type;

  return(this);
 }

/* @MRTZ_describe TiPa_init

*/
TiPa_String* TiPa_String::init(const char*  string,
                               Parser_id    type)
 {
  char* String;
  int   size;

  size = strlen(string);
  String = new char[size+1];

  memset(String,0,size+1);
  memcpy(String,string,size);
  Mbr.ParseItem.insert(String);
  TiPa_Concrete::Att.SubType = type;

  return(this);
 }








/* @MRTZ_describe init

*/
TiPa_String* TiPa_String::init(Parser_id stringSet)
 {
  switch(stringSet)
  {
   case CommentSingle : // single comment-marker
   {
    this->include("//",2);
   }break;
   case CommentDouble : // comment-marker-pair
   {
    this->include("/*",2);
    this->include("*/",2);
   }break;
   case Default :
   default      :
   {
//    TiPa_Concrete::Att.Type = NotValidParser;
   }break;
  }

  return(this);
 }


/* @MRTZ_describe id_Class

*/
TiPa_Concrete::TDA_TiPa_CLASS_TP TiPa_String::id_Class(void)
{
 return(TDA_TiPa_String);
}


/* @MRTZ_describe id_Type

*/
inline TiPa_Concrete::TDA_TiPa_CLASS_TP TiPa_String::id_Type(void)
{
 return(TDA_TiPa_String);
}






/* @MRTZ_describe include

*/
TiPa_String* TiPa_String::include(const char* string, int size)
{
  if(size == -1)
   size = strlen(string);

  char* String = new char[size+1];

  memset(String,0,size+1);
  memcpy(String,string,size);
  Mbr.ParseItem.insert(String);

  return(this);
}






/* @MRTZ_describe exclude

*/
TiPa_String* TiPa_String::exclude(const char* string, int size)
{
//  set<const char*>::iterator Item;
//  char* String = nullptr;

  if(size == -1)
   size = strlen(string);

  char* String = new char[size+1];
  memset(String,0,size+1);
  memcpy(String,string,size);

  set<const char*>::iterator Item = Mbr.ParseItem.begin(); // first item to search for
  while(Item != Mbr.ParseItem.end())                       // over all items to search for
  {
    if(STRINGS_ARE_EQUAL(String,(*Item)) )                 // exact match of first characters and size
    {
     Mbr.ParseItem.erase(Item);
     break;
    }
    ++ Item;                                               // next item to search for
  }
  delete[](String);

  return(this);
}







/* @MRTZ_describe parser_test
 if a previous search already detected a hit the previous positive result will
 be returned otherwise the string pointed by begin will be compared with all
 strings pointed by the content of the parse item set.
 */
 const char* TiPa_String::parser_Test(const char*                  begin,
                                      const char*                  end,
                                      TIPA_RESULT_ABSTRACT_UNUSED* sponsorGuard)
 {
  const char*    ReturnValue = nullptr;                                         // return of failure

  LOG_OUTPUT(LOG_OFF,  "String :" << begin);

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
   ReturnValue     = Storage.Result[begin].End;                                // positive return

   if((ReturnValue < begin) && (ReturnValue > end))
    cout << endl << "invalid result-store content in TiPa_String found" << endl;
   setCurrentHitLocation(begin, ReturnValue);
  }
  else if(begin < end)                                                          // still some text left after skip-parsing
  {
    int StringSize = testSpecific(begin, end);
    if(StringSize!= -1)
    {
     LOG_OUTPUT(LOG_OFF, string("TiPa_String::parser_Test hit ") + begin + " without |" + (begin + StringSize) +"|");

     TiPa_Result_Abstract*  ResultGuard = TiPa_Result::defineResultGuard(sponsorGuard, this
                                                                         );


     Storage.Current = ResultGuard->storeResult(begin, begin+StringSize);

     if(TiPa_Concrete::Att.ReactionHit != nullptr)                              // user-reaction for parser-hit is defined
      TiPa_Concrete::Att.ReactionHit->processHit(this, Storage.Result[begin]);
                                                                                // start user reaction
     ReturnValue = begin+StringSize;                                            // positive return
     setCurrentHitLocation(begin, ReturnValue);
     delete(ResultGuard);
    }
    else
    {
//     TiPa_Concrete::Att.NonHit.insert(begin);
     LOG_OUTPUT(LOG_OFF, string("TiPa_String::parser_Test fail: ") + begin + "|");
     ReturnValue = nullptr;                                                     // negative return
     setCurrentHitLocation(nullptr, nullptr);
    }
  }
  else                                                                          // no text left after skip-parsing
  {
   ReturnValue = nullptr;                                                       // negative return
  }

  return(ReturnValue);
 }

/* @MRTZ_describe testSpecific

*/
 int TiPa_String::testSpecific(const char* begin, const char* end)
 {
  int  ReturnValue = -1;                               // no hit found

  set<const char*>::iterator Item     = Mbr.ParseItem.begin();
  set<const char*>::iterator ItemLast = Mbr.ParseItem.end();
  while(  (ReturnValue == -1)
        &&(Item        != ItemLast)
       )                                               // over all items to search for until hit found
  {
   const char* String     = *Item;                     // string specified for this parser
   int         Character  = 0;                         // first character-position to search for
   int         StringSize = strlen(String) ;           // last character-position to search for


   ReturnValue        = StringSize;                    // no mismatch found
   while(  (ReturnValue != -1)
         &&(Character   < StringSize)
        )                                              // over all characters of item until mismatch found
   {
    if(  ( begin[Character]   != String[Character])
       ||((begin + Character) == end              )
       )                                               // if mismatch found  or end of given string reached
    {
     ReturnValue = -1;                                 // memorize mismatch
    }
    ++ Character;                                      // next character-position to search for
   }
   ++ Item;                                            // next item to search for
  }
  return(ReturnValue);
 }



/* @MRTZ_describe equal_Parser

*/
 bool TiPa_String::equal_Parser(TiPa_Concrete* parser)
 {
  bool ReturnValue = true;
  set<const char*>::iterator Item;
  set<const char*>::iterator ThisItem;

  TiPa_String* Parser = static_cast<TiPa_String*>(parser);


  if(this->TiPa_Concrete::Att.SubType != Parser->TiPa_Concrete::Att.SubType)
  // type is not the same
  {
   ReturnValue = false;
  }
  else
  // equal type
  {
   Item = Parser->Mbr.ParseItem.begin();
   while(Item != Parser->Mbr.ParseItem.end())
   // iterate over configuration of given parser
   {
    ThisItem = Mbr.ParseItem.begin();
    while(ThisItem != Mbr.ParseItem.end())
    // iterate over configuration of this parser
    {
     if(  (strstr((*Item),(*ThisItem)) == (*Item)      )
        &&(strlen(*ThisItem)           == strlen(*Item))
       )
     // both items have the same size and the same content
     {
      break;
     }
     else
     // both items have a different size or/and a different content
     {
      ++ ThisItem;
     }
    }

    if(ThisItem == Mbr.ParseItem.end())
    // item of given parser is not found in this parser
    {
     ReturnValue = false;
     break;
    }
    else
    // item of given parser is part of this parsers item container
    {
     ++Item;
    }
   }
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
