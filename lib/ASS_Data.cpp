/*!

 @file
 @brief abstract manager of tree_data

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
    08.08.2015     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    08.08.2015...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/

#include "ASS_Data.h"

#include <stdio.h>
#include <sstream>
#include <iostream>
#include <limits.h>
#include <stdlib.h>


using namespace std;


#ifndef DOXYGEN
////namespace TXTDIASM {
//namespace ASSOCIATION {
#endif //DOXYGEN



/* @MRTZ_describe AssociationData

*/
AssociationData::AssociationData(void)
{

}





/* @MRTZ_describe ~AssociationData

*/
AssociationData::~AssociationData(void)
{
//#ifdef SORT_SECONDARY_DATA
// Keys.clear();
//#endif
// list<SecondaryData_TP*>::iterator Source = SecondaryData.Dictionary.begin();
// while(Source != SecondaryData.Dictionary.end())   //iterate over given data dictionary
// {
//  delete[]((*Source)->Key);
//  delete[]((*Source)->Val);
//  (*Source)->Key = nullptr;
//  (*Source)->Val = nullptr;
//  ++ Source;
// }
// SecondaryData.Dictionary.clear();
 init();
}

/* @MRTZ_describe void

*/
void AssociationData::init(void)
{
#ifdef SORT_SECONDARY_DATA
 Keys.clear();
#endif
 list<SecondaryData_TP*>::iterator Source = SecondaryData.Dictionary.begin();
 while(Source != SecondaryData.Dictionary.end())   //iterate over given data dictionary
 {
  delete[]((*Source)->Key);
  delete[]((*Source)->Val);
//  (*Source)->Key = nullptr;
//  (*Source)->Val = nullptr;
  ++ Source;
 }
 SecondaryData.Dictionary.clear();

}



/* @MRTZ_describe itoa

*/
void AssociationData::itoa(char** numberString, long numberValue)
{
 char* LocalDestination = new char[100];
 memset(LocalDestination,0,100);
 sprintf(LocalDestination,"%ld",numberValue);

 if((*numberString) != nullptr)                               //contains old data
 {
  delete[](*numberString);                                    // clear memory
  (*numberString) = nullptr;                                  // reinitialize pointer
 }
 (*numberString) = new char[strlen(LocalDestination)+1];      //allocate memory for maximum string and terminating 0

 strcpy(*numberString,LocalDestination);
 (*numberString)[strlen(LocalDestination)]=0;

 delete[] LocalDestination;
}



/* @MRTZ_describe char2xml

*/
const char* AssociationData::char2xml(char character)
{
 static char ANSI[256][6];
 static bool Initialsised = false;

 static char CR[]={/*'&','#','1','3',';',*/13,0};
 static char LF[]={/*'&','#','1','0',';',*/10,0};


 if(Initialsised == false)
 {
  ANSI[0][0] = 0;
  for(int Ordinal = 1; Ordinal <256; ++Ordinal)
  {
   if(Ordinal < 127)
   {
    ANSI[Ordinal][0] = ANSI[Ordinal-1][0] +1;
    ANSI[Ordinal][1] = 0;
   }
   else
   {
    ANSI[Ordinal][0] = '&';
    ANSI[Ordinal][1] =  Ordinal/100;
    ANSI[Ordinal][2] = (Ordinal-100*ANSI[Ordinal][1])/10;
    ANSI[Ordinal][3] = (Ordinal-100*ANSI[Ordinal][1]-10*ANSI[Ordinal][3]);
    ANSI[Ordinal][4] = ';';
    ANSI[Ordinal][5] = 0;
   }
  }
  Initialsised = true;
 }

 switch(character)
 {
  case   1: return("&#1;");  break;
  case   2: return("&#2;");  break;
  case   3: return("&#3;");  break;
  case   4: return("&#4;");  break;
  case   5: return("&#5;");  break;
  case   6: return("&#6;");  break;
  case   7: return("&#7;");  break;
  case   8: return("&#8;");  break;
  case   9: return("&#9;");  break;
  case  10: return(LF/*"&#10;"*/); break;

  case  11: return("&#11;"); break;
  case  12: return("&#12;"); break;
  case  13: return(CR/*"&#13;"*/); break;
  case  14: return("&#14;"); break;
  case  15: return("&#15;"); break;
  case  16: return("&#16;"); break;
  case  17: return("&#17;"); break;
  case  18: return("&#18;"); break;
  case  19: return("&#19;"); break;
  case  20: return("&#20;"); break;

  case  21: return("&#21;"); break;
  case  22: return("&#22;"); break;
  case  23: return("&#23;"); break;
  case  24: return("&#24;"); break;
  case  25: return("&#25;"); break;
  case  26: return("&#26;"); break;
  case  27: return("&#27;"); break;
  case  28: return("&#28;"); break;
  case  29: return("&#29;"); break;
  case  30: return("&#30;"); break;

  case  31: return("&#31;");   break;
  case  32: return(" "/*"&#32;"*/);   break;
  case  34: return("&quot;");  break;
  case  38: return("&amp;");   break;
  case  39: return("&#39;");   break;
  case  60: return("&lt;");    break;
  case  62: return("&gt;");    break;
  case  94: return("^"/*"&circ;"*/);  break;
  case 126: return("~"/*"&tilde;"*/); break;
  case 127: return("&#127;");  break;

  default:
  {
#if      (CHAR_MIN < 0)  // compiler treats char as signed
   if(character >= 0)
    return(ANSI[(int)character]);
   else
    return(ANSI[(int)(256 + character)]);
#else  //(CHAR_MIN == 0) // compiler treats char as unsigned
    return(ANSI[(int)character]);
#endif //(CHAR_MIN < 0
  }break;
 }
}



/* @MRTZ_describe string2xml

*/
void AssociationData::string2xml(const char* source, char** destination )
{
//  ostringstream TextXML;

  if(   (  source      != nullptr)
     &&((*destination) == nullptr)
    )
  {
   // cout   << source;
   ostringstream TextXML;
   int Character = 0;
   while(source[Character] != 0)
   {
    TextXML << char2xml(source[Character]);
    ++Character;
   }
   (*destination) = new char[TextXML.str().size()+1];
   strcpy((*destination),TextXML.str().c_str());

   (*destination)[TextXML.str().size()]=0;
  }
  else
  {
   (*destination) = new char[1];
   (*destination)[0]=0;
   // don't touch the destination since the source is not existing
  }
}










/* @MRTZ_describe secondaryData_add
  key and data will be stored as independent strings not just by pointing to parameter sources
*/
const char* AssociationData::secondaryData_add(const char* key, const char* data)
{
 const char* ReturnValue = nullptr;

 if(  (key  != nullptr)
    &&(data != nullptr)
   )
 {
  bool              NewData = true;                     // key may be not in use until now
  SecondaryData_TP* Data    = secondaryData_key(key);   // check if key already exists
  if(Data == nullptr)                                   // key not found
  {
   Data = new SecondaryData_TP;

   Data->Key = new char[strlen(key)+1];                 // create fresh key
   memcpy(Data->Key,key,strlen(key));                  // set up content
   Data->Key[strlen(key)]=0;                            // ensure string termination
  }
  else                                                  // key already exists
  {
   NewData = false;                                     // store that key is already in use
   delete[](Data->Val);                                 // erase old value
  }

  Data->Val = new char[strlen(data)+1];                 // create new data location
  memcpy(Data->Val,data,strlen(data));                 // set up content
  Data->Val[strlen(data)] = 0;                          // ensure string termination

  if(NewData == true)                                   // key is really new
   SecondaryData.Dictionary.push_back(Data);            // insert new entry

  ReturnValue = Data->Val ;

#ifdef SORT_SECONDARY_DATA
 Keys.push_back(Key);
#endif
 }
 else
 {
  // keep ReturnValue as invalid
 }

 return(ReturnValue);
}


/* @MRTZ_describe secondaryData_add
  key and data will be stored as independent strings not just by pointing to parameter sources
*/
const char* AssociationData::secondaryData_add(const char* key, int data)
{
 bool              NewData = true;                     // key may be not in use until now
 SecondaryData_TP* Data    = secondaryData_key(key);   // check if key already exists
 if(Data == nullptr)                                   // key not found
 {
  Data = new SecondaryData_TP;

  Data->Key = new char[strlen(key)+1];                 // create fresh key
  memcpy(Data->Key,key,strlen(key));                  // set up content
  Data->Key[strlen(key)]=0;                            // ensure string termination
 }
 else                                                  //key already exists
 {
  NewData = false;                                     // store that key is already in use
  delete[](Data->Val);                                 // erase old value
 }

 Data->Val = nullptr;                                  // create new data location
 itoa(&Data->Val,data);                                // set up content

 if(NewData == true)                                   // key is really new
  SecondaryData.Dictionary.push_back(Data);            // insert new entry

#ifdef SORT_SECONDARY_DATA
 Keys.push_back(Key);
#endif

 return(Data->Val);
}


/* @MRTZ_describe secondaryData_add
  key and data will be stored as independent strings not just by pointing to parameter sources
*/
const char* AssociationData::secondaryData_add(const char* key, double data)
{
 bool              NewData = true;                     // key may be not in use until now
 SecondaryData_TP* Data    = secondaryData_key(key);   // check if key already exists
 if(Data == nullptr)                                   // key not found
 {
  Data = new SecondaryData_TP;

  Data->Key = new char[strlen(key)+1];                 // create fresh key
  memcpy(Data->Key,key,strlen(key));                  // set up content
  Data->Key[strlen(key)] = 0;                          // ensure string termination
 }
 else                                                  //key already exists
 {
  NewData = false;                                     // store that key is already in use
  delete[](Data->Val);                                 // erase old value
 }



 char* DoubleData = new char[256];                     // create new data location
 memset(DoubleData,0,256);                             // ensure string termination
 sprintf(DoubleData,"%lf",data);                       // set up content


 Data->Val = new char[strlen(DoubleData)+1];           // create new data location
 memcpy(Data->Val,DoubleData,strlen(DoubleData));     // set up content
 Data->Val[strlen(DoubleData)] = 0;                    // ensure string termination

 delete[] DoubleData;

 if(NewData == true)                                   // key is really new
  SecondaryData.Dictionary.push_back(Data);            // insert new entry

#ifdef SORT_SECONDARY_DATA
 Keys.push_back(Key);
#endif

 return(Data->Val);
}



/* @MRTZ_describe secondaryData_get

*/
const char* AssociationData::secondaryData_get(const char* key, const char* defaultData)
{
 const char* ReturnValue = defaultData;

 SecondaryData_TP* Data = secondaryData_key(key);             // check if key already exists
 if(Data != nullptr)                                          // key found
 {
  ReturnValue = Data->Val;                                    // return stored data
 }

 return(ReturnValue);
}



/* @MRTZ_describe secondaryData_get
 convert stored text data into integer
*/
int AssociationData::secondaryData_get(const char* key, int defaultData)
{
 int ReturnValue = defaultData;

 SecondaryData_TP* Data = secondaryData_key(key);             // check if key already exists
 if(Data != nullptr)                                          // key found
 {
  ReturnValue = atoi(Data->Val);                              // return stored and converted data
 }

 return(ReturnValue);
}


/* @MRTZ_describe secondaryData_get
 convert stored text data into float
*/
double AssociationData::secondaryData_get(const char* key, double defaultData)
{
 double ReturnValue = defaultData;

 SecondaryData_TP* Data = secondaryData_key(key);             // check if key already exists
 if(Data != nullptr)                                          // key found
 {
  ReturnValue = atof(Data->Val);                              // return stored and converted data
 }

 return(ReturnValue);
}



/* @MRTZ_describe secondaryData_get

*/
list<AssociationData::SecondaryData_TP*>* AssociationData::secondaryData_get(void)
{
 return(&SecondaryData.Dictionary);
}




/* @MRTZ_describe secondaryData_key

*/
AssociationData::SecondaryData_TP* AssociationData::secondaryData_key(const char* text)
{
 SecondaryData_TP* ReturnValue = nullptr;      // initialize return with not found

 list<SecondaryData_TP*>::iterator Data = SecondaryData.Dictionary.begin();
 while(Data != SecondaryData.Dictionary.end())   //iterate over given data dictionary
 {
  if(  (strstr((*Data)->Key,text) == (*Data)->Key)
     &&(strlen((*Data)->Key)      == strlen(text))
    )                                           // given text is equivalent to current key
  {
   ReturnValue = (*Data);                       // reinitialize return with key
   break;                                       // stop iteration
  }
  else                                          // text and current key differ
  {
   ++Data;                                      // next dictionary entry
   continue;                                    // continue iteration
  }
 }

 return(ReturnValue);                           // return search result
}







/* @MRTZ_describe secondaryData_data

*/
AssociationData::SecondaryData_TP* AssociationData::secondaryData_data(const char* text)
{
 SecondaryData_TP* ReturnValue = nullptr;      // initialize return with not found

 list<SecondaryData_TP*>::iterator Data = SecondaryData.Dictionary.begin();
 while(Data != SecondaryData.Dictionary.end())   //iterate over given data dictionary
 {
  if(  (strstr((*Data)->Val,text) == (*Data)->Val)
     &&(strlen((*Data)->Val)      == strlen(text))
    )                                           // given text is equivalent to current key
  {
   ReturnValue = (*Data);                       // reinitialize return with key
   break;                                       // stop iteration
  }
  else                                          // text and current key differ
  {
   ++Data;                                      // next dictionary entry
   continue;                                    // continue iteration
  }
 }

 return(ReturnValue);                           // return search result
}




/* @MRTZ_describe copyString

*/
void AssociationData::copyString(char** destination, const char* source)
{
 if ((*destination) != nullptr)           // destination already contains a string
  delete[](*destination);                 // delete old string

 if(source != nullptr)                    // given string is valid
 {
  unsigned int Size = strlen(source);     // size of given string
  (*destination)  = new char[ Size+1];    // one more for terminating zero
  memcpy((*destination), source, Size);   // copy given string
  ((*destination))[Size] = 0;             // terminate with zero
 }
 else                                     // given string is not valid
 {
  (*destination) = nullptr;               // reinitialize destination
 }
}








#ifndef DOXYGEN
#define USING_NAMESPACE using namespace
//}; USING_NAMESPACE ASSOCIATION;
//}; USING_NAMESPACE TXTDIASM;
#undef  USING_NAMESPACE
#endif //DOXYGEN
