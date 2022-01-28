/*!

 @file
 @brief concrete manager of tree_data
        representing the data of a grammar associated parser-tree

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
    01.09.2015     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    01.09.2015...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/
#include "TiPa_Data.h"

#include "TiPa_Character.h"
#include "TiPa_String.h"
#include "TiPa_Counter.h"
#include "TiPa_Combination.h"
#include "TiPa_Rule.h"



#include <cstring>
#include <stdlib.h>
#include <iostream>


using namespace std;


#ifndef DOXYGEN
//namespace TXTDIASM {
//namespace TDA_TinyParser {
//namespace DATA {
#endif //DOXYGEN




const char TiPa_Data::EmptyString[1] = {0};


map<int, const char*> TiPa_Data::NumberString;


/* @MRTZ_describe TiPa_Data
 no initialization here, since already done in declaration
*/
TiPa_Data::TiPa_Data(void)
          :AssociationData(),
           Parser(nullptr),                               // parser that creates this data
           Begin(nullptr),                                // first character of the detected text-part
           End(nullptr),                                  // points directly behind the last character of the detected text-part

           ParserClass(TiPa_Abstract::TDA_TiPa_Concrete), // parser-class id
           UserID(-1),                                    // user defined parser id

           Content(nullptr),                              // buffer for getContent
           Line(nullptr),                                 // line-number where detected text-part starts
           Column(nullptr),                               // column-number where detected text-part starts

           UserName(nullptr),                             // user defined name of the parser that creates this data
           User_ID_String(nullptr),                       // string representation of user defined parser id
           UserDescription(nullptr)                       // user description of the parser

{
}


/* @MRTZ_describe TiPa_Data

*/
TiPa_Data::TiPa_Data(TiPa_Data& data)
//          :AssociationData(data)
{

// cout << __FILE__ << __LINE__ << endl;

   Parser      = data.Parser;                          // parser that creates this data
//   Operand     = data.Operand;                         // sub-parser number inside the calling parser operation
   Begin       = data.Begin;                           // first character of the detected text-part
   End         = data.End;                             // points directly behind the last character of the detected text-part
   Line        = data.Line;                            //  line-number where detected text-part starts
   Column      = data.Column;                          //  column-number where detected text-part starts

   ParserClass = data.ParserClass;                     // parser-class id
   UserID      = data.UserID;                          // user defined parser id

   copyString(&UserName,data.UserName);                // user defined name of the parser that creates this data
   copyString(&User_ID_String,data.User_ID_String);    // string representation of user defined parser id
   copyString(&UserDescription,data.UserDescription);  // user description of the parser

   Content = nullptr;

   list<AssociationData::SecondaryData_TP*>* SourceSecondaryData = data.secondaryData_get();
   list<AssociationData::SecondaryData_TP*>::iterator SourceSecondary = SourceSecondaryData->begin();
   while(SourceSecondary != SourceSecondaryData->end())
   {
    secondaryData_add((*SourceSecondary)->Key, (*SourceSecondary)->Val);
    ++ SourceSecondary;
   }

}




/* @MRTZ_describe operator=

*/
TiPa_Data& TiPa_Data::operator= (TiPa_Data& data)
{

// cout << __FILE__ << __LINE__ << endl;

 if(this != &data)
 {
   Parser      = data.Parser;               // parser that creates this data
//   Operand     = data.Operand;              // sub-parser number inside the calling parser operation
   Begin       = data.Begin;                // first character of the detected text-part
   End         = data.End;                  // points directly behind the last character of the detected text-part
   Line        = data.Line;                 //  line-number where detected text-part starts
   Column      = data.Column;               //  column-number where detected text-part starts

   ParserClass = data.ParserClass;          // parser-class id
   UserID      = data.UserID;               // user defined parser id

   copyString(&UserName,data.UserName);                // user defined name of the parser that creates this data
   copyString(&User_ID_String,data.User_ID_String);    // string representation of user defined parser id
   copyString(&UserDescription,data.UserDescription);  // user description of the parser

   Content = nullptr;

   list<AssociationData::SecondaryData_TP*>* SourceSecondaryData = data.secondaryData_get();
   list<AssociationData::SecondaryData_TP*>::iterator SourceSecondary = SourceSecondaryData->begin();
   while(SourceSecondary != SourceSecondaryData->end())
   {
    secondaryData_add((*SourceSecondary)->Key, (*SourceSecondary)->Val);
    ++ SourceSecondary;
   }


 }
 return(*this);
}



/* @MRTZ_describe ~TiPa_Data

*/
TiPa_Data::~TiPa_Data(void)
{
 Parser = nullptr;                           // parser that creates this data
 Begin  = nullptr;                           // first character of the detected text-part
 End    = nullptr;                           // points directly behind the last character of the detected text-part

// ContractorData.clear();

 Line            = nullptr;                  //  line-number where detected text-part starts
 Column          = nullptr;                  //  column-number where detected text-part starts

 if(UserName != nullptr)
   delete[](UserName);                       //  user defined name of the parser that creates this data
 if(User_ID_String != nullptr)
   delete[](User_ID_String);                 //  string representation of user defined parser id
 if(UserDescription != nullptr)
   delete[](UserDescription);                //  user description of the parser

 if(Content != nullptr)
   delete[](Content);
  AssociationData::init();
}









/* @MRTZ_describe isRealSecondaryData

*/
bool TiPa_Data::isRealSecondaryData(const char* data)
{
//@MRTZ_showSource
 return(  (data !=               Begin)                   // first character of the detected text-part
        &&(data !=               End)                     // points directly behind the last character of the detected text-part
        &&(data !=(const  char*) Line)                    // line-number where detected text-part starts
        &&(data !=(const  char*) Column)                  // column-number where detected text-part starts
        &&(data !=(const  char*) userName_get())          // user defined name of the parser that creates this data
        &&(data !=(const  char*) user_ID_String_get())    // string representation of user defined parser id
        &&(data !=(const  char*) userDescription_get())   // user description of the parser
       );
}



/* @MRTZ_describe getContent

*/
const char* TiPa_Data::getContent(void)
{
//  cout<<__FILE__<<"|TiPa_Data::getContent|"<<"("<<__LINE__<<")"<<endl;
 if (Content != nullptr)           // content already analysed
 {
  return(Content);
 }
 else if(  (Begin   != nullptr)
         &&(End     != nullptr)
         &&(End     >  Begin  )
        )                          // empty content-buffer but content exists
 {
  unsigned int Size = End - Begin; // size of detected text-part
  Content  = new char[ Size+1];    // one more for terminating zero
  memcpy(Content, Begin, Size );  // copy detected text-part
  (Content)[Size] = 0;             // terminate with zero
//  cout<<__FILE__<<"|TiPa_Data::getContent|"<<"("<<__LINE__<<")"<<endl;
  return(Content);
 }
 else                              // content already analysed
 {
//  cout<<__FILE__<<"|TiPa_Data::getContent|"<<"("<<__LINE__<<")"<<endl;
  return(TiPa_Data::EmptyString);
 }
}







/* @MRTZ_describe lineSet

*/
void TiPa_Data::lineSet(int number)
{
 map<int, const char*>::iterator Number = TiPa_Data::NumberString.find(number);

 if(Number == TiPa_Data::NumberString.end()) // number is new
 {
  char* String = nullptr;                    // new number string
  itoa(&String, number);                     // create string content
  TiPa_Data::NumberString[number] = String;  // store string
  Line = String;                             // associate data
 }
 else                                        // number is already known
 {
  Line = Number->second;                     // associate data
 }
}


/* @MRTZ_describe lineGet

*/
const char* TiPa_Data::lineGet(void)
{
 return(Line);
}

/* @MRTZ_describe columnSet

*/
void TiPa_Data::columnSet(int number)
{
 map<int, const char*>::iterator Number = TiPa_Data::NumberString.find(number);

 if(Number == TiPa_Data::NumberString.end()) // number is new
 {
  char* String = nullptr;                    // new number string
  itoa(&String, number);                     // create string content
  TiPa_Data::NumberString[number] = String;  // store string
  Column = String;                           // associate data
 }
 else                                        // number is already known
 {
  Column = Number->second;                   // associate data
 }
}


/* @MRTZ_describe columnGet

*/
const char* TiPa_Data::columnGet(void)
{
 return(Column);
}



#ifndef DOXYGEN
#define USING_NAMESPACE using namespace
//}; USING_NAMESPACE DATA;
//}; USING_NAMESPACE TDA_TinyParser;
//}; USING_NAMESPACE TXTDIASM;
#undef  USING_NAMESPACE
#endif //DOXYGEN
