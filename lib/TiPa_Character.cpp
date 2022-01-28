/*!

 @file
 @brief definitions of an concrete parser-class to search for a single
        character

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
    15.02.2015     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    15.02.2015...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/

#define DEBUG_OUTPUT_LOG
#include "TiPa_Character.h"
#include "TiPa_Reaction_Concrete.h"
#include "TiPa_Result.h"


#include <stdio.h>
#include <limits.h>
//#include <sstream>


using namespace std;

#ifndef DOXYGEN
//namespace TXTDIASM {
//namespace TDA_TinyParser {
////namespace CL_TIPA_CONCRETE {
//namespace CL_TIPA {
#endif //DOXYGEN










/* @MRTZ_describe TiPa_Character

*/
 TiPa_Character::TiPa_Character(DataModel* contextModel)
                :TiPa_Concrete(contextModel)
 {
  memset(Mbr.Included,0,256);
  memset(Mbr.Excluded,0,256);
  TiPa_Concrete::Att.SubType = Single;
 }




/* @MRTZ_describe TiPa_Character

*/
 TiPa_Character::TiPa_Character(char                         character,
                                DataModel* contextModel,
                                Parser_id                    type)
                :TiPa_Concrete(contextModel, type)
 {
  memset(Mbr.Included,0,256);
  memset(Mbr.Excluded,0,256);
  this->init(character,type);
 }



/* @MRTZ_describe TiPa_Character

*/
 TiPa_Character::TiPa_Character(char                         firstCharacter,
                                char                         lastCharacter,
                                DataModel* contextModel,
                                Parser_id                    type)
                :TiPa_Concrete(contextModel,type)
 {
  memset(Mbr.Included,0,256);
  memset(Mbr.Excluded,0,256);
  this->init(firstCharacter, lastCharacter, type);
 }




/* @MRTZ_describe TiPa_Character

*/
 TiPa_Character::TiPa_Character(const char*                  characterArray,
                                int                          sizeOfArrary,
                                DataModel* contextModel,
                                Parser_id type)
                :TiPa_Concrete(contextModel,type)
 {
  memset(Mbr.Included,0,256);
  memset(Mbr.Excluded,0,256);
  this->init( characterArray, sizeOfArrary, type);
 }





/* @MRTZ_describe TiPa_Character

*/
 TiPa_Character::TiPa_Character(Parser_id                    characterSet,
                                DataModel* contextModel)
                :TiPa_Concrete(contextModel, characterSet)
 {
  memset(Mbr.Included,0,256);
  memset(Mbr.Excluded,0,256);
  this->init(characterSet);
 }








/* @MRTZ_describe ~TiPa_Character

*/
 TiPa_Character::~TiPa_Character(void)
 {
  memset(Mbr.Included,0,256);
  memset(Mbr.Excluded,0,256);
  Mbr.ParseItem.clear();
 }





/* @MRTZ_describe init

*/
TiPa_Character* TiPa_Character::init(char      character,
                                     Parser_id type)
 {
  LOG_OUTPUT(LOG_OFF, "init(char character, Parser_id type)");
  TiPa_Concrete::Att.SubType = type;
  Mbr.ParseItem.insert(character);

  return(this);
 }




/* @MRTZ_describe init

*/
TiPa_Character* TiPa_Character::init(char      firstCharacter,
                                     char      lastCharacter,
                                     Parser_id type)
 {
  TiPa_Concrete::Att.SubType = type;

  LOG_OUTPUT(LOG_OFF, "init(char firstCharacter, char lastCharacter, Parser_id type)");

  if(firstCharacter < lastCharacter)//common range of ansi
  {

   for(char Character = firstCharacter; Character<lastCharacter; ++Character)
   {
    if(Character != 0)
     Mbr.ParseItem.insert(Character);
   }
   Mbr.ParseItem.insert(lastCharacter);
  }
  else if(firstCharacter > lastCharacter)
                                    //extended range with ordinal-numbers less than 0 or greater than CHAR_MAX
  {
   for(char Character = lastCharacter; Character<firstCharacter; ++Character)
   {
    if(Character != 0)
     Mbr.ParseItem.insert(Character);
   }
   Mbr.ParseItem.insert(lastCharacter);
  }
  else//(firstCharacter == lastCharacter)
  {
   if(firstCharacter != 0)
    Mbr.ParseItem.insert(firstCharacter);
  }

  return(this);
}




/* @MRTZ_describe init

*/
TiPa_Character* TiPa_Character::init(const char* characterArray,
                                     int         sizeOfArrary,
                                     Parser_id   type)
 {
  LOG_OUTPUT(LOG_OFF, "init(const char* characterArray, int sizeOfArrary, Parser_id type)");
  TiPa_Concrete::Att.SubType = type;
  int Index = 0;

  for(Index = 0; Index<=sizeOfArrary; ++Index)
  {
   Mbr.ParseItem.insert(characterArray[Index]);
  }

  return(this);
}





/* @MRTZ_describe init

*/
TiPa_Character* TiPa_Character::init(Parser_id characterSet)
{
  LOG_OUTPUT(LOG_OFF, "init(SpecialParser characterSet)");

  switch(characterSet)
  {
   case Alnum : // alphanumeric character
   {
    this->include('0','9');
    this->include('a','b');
    this->include('A','B');
   }break;
   case Alpha : // any letter
   {
    this->include('a','b');
    this->include('A','B');
   }break;
   case Anychar :// any character
   {
    this->include(CharMin,CharMax);
    this->exclude(0);
   }break;
   case Blank : // space or tab
   {
    this->include(' ');
    this->include('\t');
//    this->include(10);
//    this->include(13);

   }break;
   case Cntrl : // any control character
   {
    this->include(1,31);
   }break;
   case Digit : // any digit
   {
    this->include('0','9');
   }break;
   case Graph : // any non-space printable character
   {
    this->include(CharMin,CharMax);
    this->exclude(' ');
    this->exclude('\t');
   }break;
   case Lower : // any lower-case letter
   {
    this->include('a','b');
   }break;
   case Print : // any printable character
   {
    this->include(CharMin,CharMax);
    this->exclude((char)0, (char)31);
   }break;
   case Punct : // any punctuation mark
   {
    this->include('!');
    this->include('?');
    this->include('.');
    this->include(':');
    this->include(',');
    this->include(';');
   }break;
   case Sign : // plus or minus sign
   {
    this->include('+');
    this->include('-');
   }break;
   case Space : // any white space character
   {
    this->include(' ');
    this->include('\t');
    this->include('\n');
    this->include('\r');
   }break;
   case Upper : // any upper-case letter
   {
    this->include('A','Z');
   }break;
   case BinDigit : // any binary digit
   {
    this->include('0','1');
   }break;
   case OctDigit : // any octagonal digit
   {
    this->include('0','7');
   }break;
   case HexDigit : // any hexadecimal digit
   {
    this->include('0','9');
    this->include('a','f');
    this->include('A','F');
   }break;
   case Default :
   case Single  :
   case Range   :
   case Group   :
   default      :
   {
   }break;
  }

  TiPa_Concrete::Att.SubType = /*(TiPa_ID)*/characterSet;
  return(this);
}



/* @MRTZ_describe id_Class

*/
TiPa_Concrete::TDA_TiPa_CLASS_TP TiPa_Character::id_Class(void)
{
 return(TDA_TiPa_Character);
}



/* @MRTZ_describe id_Type

*/
inline TiPa_Concrete::TDA_TiPa_CLASS_TP TiPa_Character::id_Type(void)
{
 return(TDA_TiPa_Character);
}




/* @MRTZ_describe include

*/
TiPa_Character* TiPa_Character::include(char character)
{
 Mbr.ParseItem.insert(character);
 TiPa_Concrete::Att.SubType = TiPa_Character::Group;

 return(this);
}



/* @MRTZ_describe include

*/
TiPa_Character* TiPa_Character::include(char firstCharacter, char lastCharacter)
{
 if(firstCharacter < lastCharacter)//common range of ansi
 {

  for(char Character = firstCharacter; Character<lastCharacter; ++Character)
  {
   Mbr.ParseItem.insert(Character);
  }
  Mbr.ParseItem.insert(lastCharacter);
 }
 else if(firstCharacter > lastCharacter)
                                   //extended range with ordinal-numbers less than 0 or greater than CHAR_MAX
 {
  for(char Character = lastCharacter; Character<firstCharacter; ++Character)
  {
   if(Character != 0)
    Mbr.ParseItem.insert(Character);
  }
  Mbr.ParseItem.insert(lastCharacter);
 }
 else//(firstCharacter == lastCharacter)
 {
  Mbr.ParseItem.insert(firstCharacter);
 }

 TiPa_Concrete::Att.SubType = TiPa_Character::Group;

 return(this);
}




/* @MRTZ_describe include

*/
TiPa_Character* TiPa_Character::include(const char* characterArray, int sizeOfArrary)
{
 for(int Index = 0; Index<=sizeOfArrary; ++Index)
 {
  Mbr.ParseItem.insert(characterArray[Index]);
 }

 TiPa_Concrete::Att.SubType = TiPa_Character::Group;

 return(this);
}




/* @MRTZ_describe exclude

*/
TiPa_Character* TiPa_Character::exclude(char character)
{
  Mbr.ParseItem.erase(character);
  TiPa_Concrete::Att.SubType = TiPa_Character::Group;

  return(this);
}



/* @MRTZ_describe exclude

*/
TiPa_Character* TiPa_Character::exclude(char firstCharacter, char lastCharacter)
{
 if(firstCharacter < lastCharacter)//common range of ansi
 {
  for(char Character = firstCharacter; Character<lastCharacter; ++Character)
  {
   Mbr.ParseItem.erase(Character);
  }
  Mbr.ParseItem.erase(lastCharacter);
 }
 else if(firstCharacter > lastCharacter)
                                   //extended range with ordinal-numbers less than 0 or greater than CHAR_MAX
 {
  for(char Character = lastCharacter; Character<firstCharacter; ++Character)
  {
   if(Character != 0)
    Mbr.ParseItem.erase(Character);
  }
  Mbr.ParseItem.erase(lastCharacter);
 }
 else//(firstCharacter == lastCharacter)
 {
  Mbr.ParseItem.erase(firstCharacter);
 }

 TiPa_Concrete::Att.SubType = TiPa_Character::Group;

 return(this);
}



/* @MRTZ_describe exclude

*/
TiPa_Character* TiPa_Character::exclude(const char* characterArray, int sizeOfArrary)
{
 int Index = 0;

 for(Index = 0; Index<=sizeOfArrary; ++Index)
 {
  Mbr.ParseItem.erase(characterArray[Index]);
 }

 TiPa_Concrete::Att.SubType = TiPa_Character::Group;

 return(this);
}







/* @MRTZ_describe parser_test
 if a previous search already detected a hit the previous positive result will
 be returned otherwise the character pointed by begin will be searched in the
 parse item set.
*/
 const char* TiPa_Character::parser_Test(const char*                  begin,
                                         const char*                  end,
                                         TIPA_RESULT_ABSTRACT_UNUSED* sponsorGuard)
 {
  const char*   ReturnValue = nullptr;                                          // return of failure

  LOG_OUTPUT(LOG_OFF, string("TiPa_Character::parser_Test{") << TiPa_Concrete::Att.SubType << "} : <"<< (int)*begin << ">"<<begin);

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

   LOG_OUTPUT(LOG_OFF, string("TiPa_Character::parser_Test already known  ") + begin + " without |" + (begin+1) +"|");
   ReturnValue                   = begin+1;                                     // positive return

   if((ReturnValue < begin) && (ReturnValue > end))
    cout << endl << "invalid result-store content in TiPa_Character found" << endl;

   Storage.Current = Storage.Result.find(begin);
   setCurrentHitLocation(begin, ReturnValue);
  }
  else if(  (begin <  end)
          &&(testSpecific(*begin))
         )                                                                      // not found before but valid hit
  {
   LOG_OUTPUT(LOG_OFF, string("TiPa_Character::parser_Test{") << TiPa_Concrete::Att.SubType << "} hit |" << (int)*begin <<"|");

   {

    TiPa_Result_Abstract*  ResultGuard = TiPa_Result::defineResultGuard(sponsorGuard, this);


    if(Storage.StorageType == ResStore_Skip)                                    // result not of interest
     { /* don't store anything*/}
    else                                                                        // own tool defined
     Storage.Current = ResultGuard->storeResult(begin, begin+1);

    if(TiPa_Concrete::Att.ReactionHit != nullptr)                               // user-reaction for parser-hit is defined
     TiPa_Concrete::Att.ReactionHit->processHit(this, Storage.Result[begin]);
                                                                                // start user reaction
    delete(ResultGuard);
   }
   ReturnValue          = begin+1;                                              // positive return
   setCurrentHitLocation(begin, ReturnValue);
  }
  else                                                                          // no match found
  {
   LOG_OUTPUT(LOG_OFF, string("TiPa_Character::parser_Test{") << TiPa_Concrete::Att.SubType << "} failed |" << (int)*begin <<"|");
   ReturnValue = nullptr;                                                       // negative return
   setCurrentHitLocation(nullptr, nullptr);
  }

  return(ReturnValue);
 }






/* @MRTZ_describe testSpecific

*/
bool TiPa_Character::testSpecific(char begin)
 {

  switch(TiPa_Concrete::Att.SubType)
  {
   case Alnum : // alphanumeric character
   {
    LOG_OUTPUT(LOG_OFF, string("TiPa_Character::testSpecific(Alnum) : ")<<begin);
    return(  ((begin >= 'a')&&(begin <= 'z'))
           ||((begin >= 'A')&&(begin <= 'Z'))
           ||((begin >= '0')&&(begin <= '9'))
          );
   }break;
   case Alpha : // any letter
   {
    LOG_OUTPUT(LOG_OFF, string("TiPa_Character::testSpecific(Alpha) : ")<<begin);
    return(  ((begin >= 'a')&&(begin <= 'z'))
           ||((begin >= 'A')&&(begin <= 'Z'))
          );
   }break;
   case Anychar :// any character
   {
    LOG_OUTPUT(LOG_OFF, string("TiPa_Character::testSpecific(Anychar) : ")<<begin);
    return(begin!=0);
   }break;
   case Blank : // space or tab
   {
    LOG_OUTPUT(LOG_OFF, string("TiPa_Character::testSpecific(Blank) : ")<<begin);
    return(  (begin == ' ')
//           ||(begin == 10)
//           ||(begin == 13)
           ||(begin == '\t')
          );
   }break;
   case Cntrl : // any control character
   {
    LOG_OUTPUT(LOG_OFF, string("TiPa_Character::testSpecific(Cntrl) : ")<<begin);
    return((begin >= 1)&&(begin <= 31));
   }break;
   case Digit : // any digit
   {
    LOG_OUTPUT(LOG_OFF, string("TiPa_Character::testSpecific(Digit) : ")<<begin);
    return((begin >= '0')&&(begin <= '9'));
   }break;
   case Graph : // any non-space printable character
   {
    LOG_OUTPUT(LOG_OFF, string("TiPa_Character::testSpecific(Graph) : ")<<begin);
    return(  (begin == 0)
           ||(begin == ' ')
           ||(begin == '\t')
          );
   }break;
   case Lower : // any lower-case letter
   {
    LOG_OUTPUT(LOG_OFF, string("TiPa_Character::testSpecific(Lower) : ")<<begin);
    return((begin >= 'a')&&(begin <= 'z'));
   }break;
   case Print : // any printable character
   {
    LOG_OUTPUT(LOG_OFF, string("TiPa_Character::testSpecific(Print) : ")<<begin);
#if     (CHAR_MIN < 0)  // compiler treats char as signed
    return((begin < 0)||(begin > 31));
#else //(CHAR_MIN == 0) // compiler treats char as unsigned
    return(begin > 31);
#endif//(CHAR_MIN < 0)
   }break;
   case Punct : // any punctuation mark
   {
    LOG_OUTPUT(LOG_OFF, string("TiPa_Character::testSpecific(Punct) : ")<<begin);
    return(  (begin == ';')
           ||(begin == ',')
           ||(begin == '.')
           ||(begin == ':')
           ||(begin == '!')
           ||(begin == '?')
          );
   }break;
   case Sign : // plus or minus sign
   {
    LOG_OUTPUT(LOG_OFF, string("TiPa_Character::testSpecific(Sign) : ")<<begin);
    return(  (begin == '+')
           ||(begin == '-')
          );
   }break;
   case Space : // any white space character
   {
    LOG_OUTPUT(LOG_OFF, string("TiPa_Character::testSpecific(Space) : ")<<begin);
    return(  (begin == ' ')
           ||(begin == '\n')
           ||(begin == '\r')
           ||(begin == '\t')
          );
   }break;
   case Upper : // any upper-case letter
   {
    LOG_OUTPUT(LOG_OFF, string("TiPa_Character::testSpecific(Upper) : ")<<begin);
    return((begin >= 'A')&&(begin <= 'Z'));
   }break;
   case BinDigit : // any binary digit
   {
    LOG_OUTPUT(LOG_OFF, string("TiPa_Character::testSpecific(BinDigit) : ")<<begin);
    return(  (begin == '0')
           ||(begin == '1')
          );
   }break;
   case OctDigit : // any octagonal digit
   {
    LOG_OUTPUT(LOG_OFF, string("TiPa_Character::testSpecific(OctDigit) : ")<<begin);
    this->include('0','7');
    return((begin >= '0')&&(begin <= '7'));
   }break;
   case HexDigit : // any hexadecimal digit
   {
    LOG_OUTPUT(LOG_OFF, string("TiPa_Character::testSpecific(HexDigit) : ")<<begin);
    return(  ((begin >= '0')&&(begin <= '9'))
           ||((begin >= 'A')&&(begin <= 'F'))
           ||((begin >= 'a')&&(begin <= 'f'))
          );
   }break;
   default :
   {
    LOG_OUTPUT(LOG_OFF, string("TiPa_Character::testSpecific(default) : ")<<begin);
    return(Mbr.ParseItem.find(begin) != Mbr.ParseItem.end());    // given character is specified

//    bool ReturnValue  = false;
//    stringstream Output;
    if(Mbr.Included[0]!=0)                                            // specified characters already listed
    {
//   cout << "if(Mbr.Included[0]!=0) " << begin << endl;
//     cout << Mbr.Included << endl;
     int Index = 0;
     while(  (Mbr.Included[Index] != begin)
           &&(Mbr.Included[Index] != 0)
           &&(Index               <  255)
          ) ++ Index;
//     Output << "Att.Included[" << Index << "] " <<Att.Included[Index] << endl;
//     ReturnValue  = ((Mbr.Included[Index] == begin));                         // return if hit inside specified characters found
     return((Mbr.Included[Index] == begin));                         // return if hit inside specified characters found
    }
    else if(Mbr.Excluded[0]!=0)                                      // unspecified characters already listed
    {
//   cout << "else if(Mbr.Excluded[0]!=0)  " << begin << endl;
     int Index = 0;
     while(  (Mbr.Excluded[Index] != begin)
           &&(Mbr.Excluded[Index] != 0)
           &&(Index               <  255)
          ) ++ Index;

//     Output << "Att.Excluded[" << Index << "] " <<Att.Excluded[Index] << endl;
//     ReturnValue  = ((Mbr.Excluded[Index] != begin));                         // return if hit inside unspecified characters  not found
     return((Mbr.Excluded[Index] != begin));                         // return if hit inside unspecified characters  not found
    }
    else if(Mbr.ParseItem.size() < 128)                               // no characters listed and less Characters specified than unspecified
    {
//     cout << "else if(Mbr.ParseItem.size()< 128)   " << begin << endl;
//     bool ReturnValue  = false;
     int Index         = 0;
     for(char Character = CharMin; Character < CharMax ; ++Character )     //over all characters
     {
      if(Mbr.ParseItem.find(Character) != Mbr.ParseItem.end())// character is specified
      {
       if(Character != 0)                                           // valid ascii character
        Mbr.Included[Index] = Character;                      // add character to specified list
       ++Index;                                                     // next list-position
      }
     }
//     if(Mbr.ParseItem.find(begin) != Mbr.ParseItem.end())    // given character is specified
//        ReturnValue = true;                                        // output hit
     return(Mbr.ParseItem.find(begin) != Mbr.ParseItem.end());    // given character is specified
   // return(ReturnValue);
    }
    else                                                            //no characters listed and less Characters unspecified than specified
    {
//     cout << "else " << begin << endl;
//     bool ReturnValue  = false;
     int Index         = 0;
     for(char Character = CharMin; Character < CharMax ; ++Character )     //over all characters
     {
     if(Mbr.ParseItem.find(Character) == Mbr.ParseItem.end())// character is specified
      {
       if(Character != 0)                                           // valid ascii character
        Mbr.Excluded[Index] = Character;                      // add character to unspecified list
       ++Index;                                                     // next list-position
      }
     }
//     if(Mbr.ParseItem.find(begin) != Mbr.ParseItem.end())    // given character is specified
//        ReturnValue = true;                                        // output hit
     return(Mbr.ParseItem.find(begin) != Mbr.ParseItem.end());    // given character is specified
  //  return(ReturnValue);
    }
//    if (ReturnValue != ((Mbr.ParseItem.find(begin) != Mbr.ParseItem.end()) ) )
//    {
//     cout << "-----------------------------------" << endl;
//     cout << Output.str() << endl;
//     cout << "-----------------------------------" << endl;
//     cout << "Att.Included (" << strlen(Mbr.Included) << ") : " << Mbr.Included << endl;
//     cout << "Att.Excluded (" << strlen(Mbr.Excluded) << ") : " << Mbr.Excluded << endl;
//     cout << "Att.ParseItem(" << Mbr.ParseItem.size() << ") : " ;
//     for(set<char>::iterator Item = Mbr.ParseItem.begin(); Item != Mbr.ParseItem.end();++Item)
//      cout << *Item;
//     cout << endl;
//     cout << "-----------------------------------" << endl;
//
//    }
//    return(Mbr.ParseItem.find(begin) != Mbr.ParseItem.end());
//    return(ReturnValue);
   }break;
  }

 }













/* @MRTZ_describe equal_Parser

*/
 bool TiPa_Character::equal_Parser(TiPa_Concrete* parser)
 {
  bool ReturnValue = true;
  set<char>::iterator Item;

  TiPa_Character* Parser = static_cast<TiPa_Character*>(parser);


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
    if(Mbr.ParseItem.find(*Item)==Mbr.ParseItem.end())
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



