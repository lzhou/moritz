/*!

 @file
 @brief  definition of a collection of common snippet-commands

 This file contains common snippet-commands used to navigate through
 the xml-tree and to find the snippets to use.

 Copyright (C) 2008-2020 by Eckard Klotz.

 Permission to use, copy, modify, and distribute this software and its
 documentation under the terms of the GNU General Public License is hereby
 granted. No representations are made about the suitability of this software
 for any purpose. It is provided "as is" without express or implied warranty.
 See the GNU General Public License for more details.

 Documents produced by Moritz are derivative works derived from the
 input used in their production; they are not affected by this license.

 <b> History </b>

 @TabBegin
    date           @I author          @I implementation/change
 @I____________________________________________________________
    11.06.2011     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    11.06.2011...  @I Eckard Klotz
 @I Changes are documented in the comment of the changed element
 @TabEnd

*/


#include "command.h"
#include "transform.h"
#include "snippet.h"
#include "cmnd_stack_strg.h"




#ifndef DOXYGEN
//namespace CL_COMMAND {
#endif //DOXYGEN



/* @MRTZ_describe Cmnd_Common

*/
Cmnd_Common::Cmnd_Common(void)
{
}





/* @MRTZ_describe ~Cmnd_Common

*/
Cmnd_Common::~Cmnd_Common(void)
{
}



/* @MRTZ_describe assignSequence

   @MRTZ_describe local_declarations

   @MRTZ_describe collect_data_for_RAWTEXT

   @MRTZ_describe collect_data_for_SNIPET

   @MRTZ_describe collect_data_for_DROP

   @MRTZ_describe collect_data_for_REPLACE

   @MRTZ_describe collect_data_for_TEXT

   @MRTZ_describe collect_data_for_DESTINATION

   @MRTZ_describe sub_ifElseChain_1

   @MRTZ_describe collect_data_for_USEFORSNIPETLOCAL

   @MRTZ_describe collect_data_for_USEFORSNIPETDOWNWARDS

   @MRTZ_describe collect_data_for_FORALL

   @MRTZ_describe collect_data_for_STATISTIC

   @MRTZ_describe collect_data_for_IFABSENT

   @MRTZ_describe collect_data_for_IFEMPTY

   @MRTZ_describe sub_ifElseChain_2

   @MRTZ_describe collect_data_for_TAG

   @MRTZ_describe collect_data_for_ATTRIBUTE

   @MRTZ_describe collect_data_for_STACKPUSH

   @MRTZ_describe collect_data_for_STACKREAD

   @MRTZ_describe collect_data_for_STACKREADALL

   @MRTZ_describe sub_ifElseChain_3

   @MRTZ_describe collect_data_for_STACKPOP

   @MRTZ_describe collect_data_for_STACKPOPALL

   @MRTZ_describe sub_ifElseChain_4

   @MRTZ_describe collect_data_for_IFSTACKEQUAL

   @MRTZ_describe collect_data_for_IFSTACKUNEQUAL

   @MRTZ_describe collect_data_for_IFOLDERAS

   @MRTZ_describe collect_data_for_IFNOTEXIST

   @MRTZ_describe collect_data_for_REPEAT_IFSTACKEQUAL

   @MRTZ_describe collect_data_for_REPEAT_IFSTACKUNEQUAL

   @MRTZ_describe collect_data_for_STACKPUSHSIZE

   @MRTZ_describe collect_data_for_STACKCLEAR

   @MRTZ_describe sub_ifElseChain_5

   @MRTZ_describe collect_data_for_XMLCREATE

   @MRTZ_describe collect_data_for_XMLCOPY

   @MRTZ_describe collect_data_for_XMLCUT

   @MRTZ_describe collect_data_for_XMLCODE

   @MRTZ_describe collect_data_for_XMLINSERT

   @MRTZ_describe collect_data_for_XMLSNIPET

   @MRTZ_describe collect_data_for_XMLDELETE

   @MRTZ_describe collect_data_for_XMLPRINT

   @MRTZ_describe collect_data_for_IFXMLEQUAL

   @MRTZ_describe collect_data_for_IFXMLUNEQUAL

   @MRTZ_describe collect_data_for_IFXMLEXISTING

   @MRTZ_describe collect_data_for_IFXMLMISSING

   @MRTZ_describe collect_data_for_PARSERSET

   @MRTZ_describe collect_data_for_PARSE

*/
void Cmnd_Common::assignSequence(list<_s_RawCmnd_TP>::iterator      command,
                                 map<String_imp,_s_CommandData_TP>* sequence)
{
// @MRTZ_exclude local_declarations
// @MRTZ_beginBlock

// String_imp   Parameter1 = "";
// String_imp   Parameter2 = "";
// String_imp   Parameter3 = "";
// String_imp   Parameter4 = "";
// String_imp   Parameter5 = "";
 String_imp   Key        = "";
 list<_s_RawParameter_TP>::iterator   Parameter_Crnt;
// @MRTZ_endBlock

 Parameter_Crnt = command->Parameter.begin();
// @MRTZ_ifElseChain
 if     (command->Name == String_imp(RAWTEXT))
 {
// @MRTZ_exclude collect_data_for_RAWTEXT
  while(Parameter_Crnt != command->Parameter.end())
  {
   if(  (Parameter_Crnt->Token == RAWTEXT)
      ||(Parameter_Crnt->Token == FORMAT)
      ||(Parameter_Crnt->Token == NEWLINE)
      ||(Parameter_Crnt->Token == INDEND)
      ||(Parameter_Crnt->Token == DEDEND)
      ||(Parameter_Crnt->Token == SPACE)
      ||(Parameter_Crnt->Token == TAB)
      ||(Parameter_Crnt->Token == ASCII)
     )
   {
    Key = command->Name;
    (*sequence)[Key].Name               = command->Name;
    (*sequence)[Key].ID                 = ID_RAWTEXT;
    (*sequence)[Key].Parameter[RAWTEXT] = Parameter_Crnt->Text;

#if defined(DEBUG_OUTPUT)
     cout << (*sequence)[Key].Name               << ", "
          << (*sequence)[Key].ID                 << ", "
          << (*sequence)[Key].Parameter[RAWTEXT] << endl;
#endif //DEBUG_OUTPUT
   }
   ++ Parameter_Crnt;
  }
 }
 else if(command->Name == String_imp(SNIPET))
 {
// @MRTZ_exclude collect_data_for_SNIPET
  while(Parameter_Crnt != command->Parameter.end())
  {
   if( Parameter_Crnt->Token =="tagName")
   {
    Key = Parameter_Crnt->Text;
    (*sequence)[Key].Name                 = command->Name;
    (*sequence)[Key].ID                   = ID_SNIPET;
    (*sequence)[Key].Parameter["tagName"] = Parameter_Crnt->Text;
   }
   else if( Parameter_Crnt->Token =="tagPath")
   {
    (*sequence)[Key].Parameter["tagPath"]   = (Parameter_Crnt->Text).substr(1);
    (*sequence)[Key].Parameter["separator"] = (String_imp(Parameter_Crnt->Text)[0]);
   }
   ++ Parameter_Crnt;
  }
 }
 else if(command->Name == String_imp(DROP))
 {
// @MRTZ_exclude collect_data_for_DROP
  while(Parameter_Crnt != command->Parameter.end())
  {
   if( Parameter_Crnt->Token =="tagName")
   {
    Key = Parameter_Crnt->Text;
    (*sequence)[Key].Name                 = command->Name;
    (*sequence)[Key].ID                   = ID_DROP;
    (*sequence)[Key].Parameter["tagName"] = Parameter_Crnt->Text;
   }
   ++ Parameter_Crnt;
  }
 }
 else if(command->Name == String_imp(REPLACE))
 {
// @MRTZ_exclude collect_data_for_REPLACE
// @MRTZ_beginBlock
  String_imp Parameter1  = "";
  String_imp Parameter2  = "";
  String_imp Parameter3  = "";
  while(Parameter_Crnt != command->Parameter.end())
  {
   if     ( Parameter_Crnt->Token =="oldPart")
    Parameter1 = Parameter_Crnt->Text;
   else if( Parameter_Crnt->Token =="newPart")
    Parameter2 = Parameter_Crnt->Text;
   else if( Parameter_Crnt->Token =="replaceReset")
    Parameter3 = Parameter_Crnt->Text;
   ++ Parameter_Crnt;
  }
  Key = REPLACE + String_imp("_") + Parameter1;
  (*sequence)[Key].Name = command->Name;
  (*sequence)[Key].ID   = ID_REPLACE;
  (*sequence)[Key].Parameter["oldPart"]      = Parameter1;
  (*sequence)[Key].Parameter["newPart"]      = Parameter2;
  (*sequence)[Key].Parameter["replaceReset"] = Parameter3;
// @MRTZ_endBlock
 }
 else if(command->Name == String_imp(TEXT))
 {
// @MRTZ_exclude collect_data_for_TEXT
 while(Parameter_Crnt != command->Parameter.end())
  {
   if( Parameter_Crnt->Token =="tagName")
   {
    Key = Parameter_Crnt->Text;
    (*sequence)[Key].Name = command->Name;
    (*sequence)[Key].ID   = ID_TEXT;
    (*sequence)[Key].Parameter["tagName"] = Parameter_Crnt->Text;
   }
   else if( Parameter_Crnt->Token =="tagPath")
   {
    (*sequence)[Key].Parameter["tagPath"]   = (Parameter_Crnt->Text).substr(1);
    (*sequence)[Key].Parameter["separator"] = (String_imp(Parameter_Crnt->Text)[0]);
   }
   ++ Parameter_Crnt;
  }
 }
 else if(command->Name == String_imp(DESTINATION))
 {
// @MRTZ_exclude collect_data_for_DESTINATION
  while(Parameter_Crnt != command->Parameter.end())
  {
   if( Parameter_Crnt->Token =="tagName")
   {
    Key = Parameter_Crnt->Text;
    (*sequence)[Key].Name = command->Name;
    (*sequence)[Key].ID   = ID_DESTINATION;
    (*sequence)[Key].Parameter["tagName"] = Parameter_Crnt->Text;
   }
   ++ Parameter_Crnt;
  }
 }
 else
// @MRTZ_exclude sub_ifElseChain_1
// @MRTZ_ifElseChain
      if(  (command->Name == String_imp(USEFORSNIPET))
         ||(command->Name == String_imp(USEFORSNIPETLOCAL))
        )
 {
  String_imp Parameter1 = "";
  String_imp Parameter2 = "";
// @MRTZ_exclude collect_data_for_USEFORSNIPETLOCAL
// @MRTZ_beginBlock
  while(Parameter_Crnt != command->Parameter.end())
  {
   if     ( Parameter_Crnt->Token =="tagName")
    Parameter1 = Parameter_Crnt->Text;
   else if( Parameter_Crnt->Token =="snipetName")
    Parameter2 = Parameter_Crnt->Text;
   ++ Parameter_Crnt;
  }
  Key = USEFORSNIPETLOCAL + String_imp("_") + Parameter1;
  (*sequence)[Key].Name                    = command->Name;
  (*sequence)[Key].ID                      = ID_USEFORSNIPETLOCAL;
  (*sequence)[Key].Parameter["tagName"]    = Parameter1;
  (*sequence)[Key].Parameter["snipetName"] = Parameter2;
// @MRTZ_endBlock
 }
 else if(command->Name == String_imp(USEFORSNIPETDOWNWARDS))
 {
  String_imp Parameter1 = "";
  String_imp Parameter2 = "";
// @MRTZ_exclude collect_data_for_USEFORSNIPETDOWNWARDS
// @MRTZ_beginBlock
  while(Parameter_Crnt != command->Parameter.end())
  {
   if     ( Parameter_Crnt->Token =="tagName")
    Parameter1 = Parameter_Crnt->Text;
   else if( Parameter_Crnt->Token =="snipetName")
    Parameter2 = Parameter_Crnt->Text;
   ++ Parameter_Crnt;
  }
  Key = USEFORSNIPETDOWNWARDS + String_imp("_") + Parameter1;
  (*sequence)[Key].Name                    = command->Name;
  (*sequence)[Key].ID                      = ID_USEFORSNIPETDOWNWARDS;
  (*sequence)[Key].Parameter["tagName"]    = Parameter1;
  (*sequence)[Key].Parameter["snipetName"] = Parameter2;
// @MRTZ_endBlock
 }
 else if(command->Name == String_imp(FORALL))
 {
  String_imp Parameter1 = "";
// @MRTZ_exclude collect_data_for_FORALL
// @MRTZ_beginBlock
  while(Parameter_Crnt != command->Parameter.end())
  {
   if( Parameter_Crnt->Token =="snipetName")
    Parameter1 = Parameter_Crnt->Text;
   ++ Parameter_Crnt;
  }
  Key = FORALL;
  (*sequence)[Key].Name                    = command->Name;
  (*sequence)[Key].ID                      = ID_FORALL;
  (*sequence)[Key].Parameter["snipetName"] = Parameter1;
// @MRTZ_endBlock
 }

 else if(command->Name == String_imp(STATISTIC))
 {
  String_imp Parameter1 = "";
  String_imp Parameter2 = "";
// @MRTZ_exclude collect_data_for_STATISTIC
// @MRTZ_beginBlock
  while(Parameter_Crnt != command->Parameter.end())
  {
   if     ( Parameter_Crnt->Token =="tagToCount")
    Parameter1 = Parameter_Crnt->Text;
   else if( Parameter_Crnt->Token =="tagToSave")
    Parameter2 = Parameter_Crnt->Text;
   ++ Parameter_Crnt;
  }
  Key = STATISTIC + String_imp("_") + Parameter1;
  (*sequence)[Key].Name                    = command->Name;
  (*sequence)[Key].ID                      = ID_STATISTIC;
  (*sequence)[Key].Parameter["tagToCount"] = Parameter1;
  (*sequence)[Key].Parameter["tagToSave"]  = Parameter2;
// @MRTZ_endBlock
 }







 else if(command->Name == String_imp(IFABSENT))
 {
// @MRTZ_exclude collect_data_for_IFABSENT
// @MRTZ_beginBlock
  String_imp Parameter1  = "";
  String_imp Parameter2  = "";
  String_imp Parameter3  = "";
  String_imp Parameter4  = "";
  while(Parameter_Crnt != command->Parameter.end())
  {
   if     ( Parameter_Crnt->Token =="tagName")
    Parameter1 = Parameter_Crnt->Text;
   else if( Parameter_Crnt->Token =="snipetName")
    Parameter2 = Parameter_Crnt->Text;
   else if( Parameter_Crnt->Token =="tagPath")
   {
    Parameter3  = (Parameter_Crnt->Text).substr(1);
    Parameter4  = (String_imp(Parameter_Crnt->Text)[0]);
   }
   ++ Parameter_Crnt;
  }
  Key = IFABSENT + String_imp("_") + Parameter1;
  (*sequence)[Key].Name                    = command->Name;
  (*sequence)[Key].ID                      = ID_IFABSENT;
  (*sequence)[Key].Parameter["tagName"]    = Parameter1;
  (*sequence)[Key].Parameter["snipetName"] = Parameter2;
   if( Parameter3  != "")
   {
    (*sequence)[Key].Parameter["tagPath"]   = Parameter3;
    (*sequence)[Key].Parameter["separator"] = Parameter4;
   }
// @MRTZ_endBlock
 }
 else if(command->Name == String_imp(IFEMPTY))
 {
// @MRTZ_exclude collect_data_for_IFEMPTY
// @MRTZ_beginBlock
  String_imp Parameter1  = "";
  while(Parameter_Crnt != command->Parameter.end())
  {
   if( Parameter_Crnt->Token =="snipetName")
    Parameter1 = Parameter_Crnt->Text;
   ++ Parameter_Crnt;
  }
  Key = IFEMPTY;
  (*sequence)[Key].Name                    = command->Name;
  (*sequence)[Key].ID                      = ID_IFEMPTY;
  (*sequence)[Key].Parameter["snipetName"] = Parameter1;
// @MRTZ_endBlock
 }
 else
// @MRTZ_exclude sub_ifElseChain_2
// @MRTZ_ifElseChain
      if(command->Name == String_imp(TAG))
 {
// @MRTZ_exclude collect_data_for_TAG
// @MRTZ_beginBlock
  Key = TAG;
  (*sequence)[Key].Name = command->Name;
  (*sequence)[Key].ID   = ID_TAG;
// @MRTZ_endBlock
 }
 else if(command->Name == String_imp(ATTRIBUTE))
 {
  String_imp Parameter1  = "";
// @MRTZ_exclude collect_data_for_ATTRIBUTE
// @MRTZ_beginBlock
  while(Parameter_Crnt != command->Parameter.end())
  {
   if( Parameter_Crnt->Token =="attributeName")
    Parameter1 = Parameter_Crnt->Text;
   ++ Parameter_Crnt;
  }
  Key = ATTRIBUTE + String_imp("_") + Parameter1;
  (*sequence)[Key].Name                       = command->Name;
  (*sequence)[Key].ID                         = ID_ATTRIBUTE;
  (*sequence)[Key].Parameter["attributeName"] = Parameter1;
// @MRTZ_endBlock
 }
 else if(command->Name == String_imp(STACKPUSH))
 {
// @MRTZ_exclude collect_data_for_STACKPUSH
// @MRTZ_beginBlock
  String_imp Parameter1  = "";
  String_imp Parameter2  = "";
  while(Parameter_Crnt != command->Parameter.end())
  {
   if     ( Parameter_Crnt->Token =="snipetName")
    Parameter1 = Parameter_Crnt->Text;
   else if( Parameter_Crnt->Token =="stackName")
    Parameter2 = Parameter_Crnt->Text;
   ++ Parameter_Crnt;
  }
  Key = Parameter1;
  (*sequence)[Key].Name                    = command->Name;
  (*sequence)[Key].ID                      = ID_STACKPUSH;
  (*sequence)[Key].Parameter["snipetName"] = Parameter1;
  (*sequence)[Key].Parameter["stackName"]  = Parameter2;
// @MRTZ_endBlock
 }
 else if(command->Name == String_imp(STACKREAD))
 {
// @MRTZ_exclude collect_data_for_STACKREAD
// @MRTZ_beginBlock
  String_imp Parameter1  = "";
  String_imp Parameter2  = "";
  while(Parameter_Crnt != command->Parameter.end())
  {
   if     ( Parameter_Crnt->Token =="value")
    Parameter1 = Parameter_Crnt->Text;
   else if( Parameter_Crnt->Token =="stackName")
    Parameter2 = Parameter_Crnt->Text;
   ++ Parameter_Crnt;
  }
  Key = STACKREAD + String_imp("_") + Parameter1 + String_imp("_") + Parameter2;
  (*sequence)[Key].Name                    = command->Name;
  (*sequence)[Key].ID                      = ID_STACKREAD;
  (*sequence)[Key].Parameter["value"]      = Parameter1;
  (*sequence)[Key].Parameter["stackName"]  = Parameter2;
// @MRTZ_endBlock
 }
 else if(command->Name == String_imp(STACKREADALL))
 {
// @MRTZ_exclude collect_data_for_STACKREADALL
// @MRTZ_beginBlock
  String_imp Parameter1  = "";
  String_imp Parameter2  = "";
  while(Parameter_Crnt != command->Parameter.end())
  {
   if     ( Parameter_Crnt->Token =="value")
    Parameter1 = Parameter_Crnt->Text;
   else if( Parameter_Crnt->Token =="stackName")
    Parameter2 = Parameter_Crnt->Text;
   ++ Parameter_Crnt;
  }
  Key = STACKREADALL + String_imp("_") + Parameter1 + String_imp("_") + Parameter2;
  (*sequence)[Key].Name                    = command->Name;
  (*sequence)[Key].ID                      = ID_STACKREADALL;
  (*sequence)[Key].Parameter["value"]      = Parameter1;
  (*sequence)[Key].Parameter["stackName"]  = Parameter2;
// @MRTZ_endBlock
 }
 else
// @MRTZ_exclude sub_ifElseChain_3
// @MRTZ_ifElseChain
      if(command->Name == String_imp(STACKPOP))
 {
// @MRTZ_exclude collect_data_for_STACKPOP
// @MRTZ_beginBlock
  String_imp Parameter1  = "";
  String_imp Parameter2  = "";
  while(Parameter_Crnt != command->Parameter.end())
  {
   if     ( Parameter_Crnt->Token =="value")
    Parameter1 = Parameter_Crnt->Text;
   else if( Parameter_Crnt->Token =="stackName")
    Parameter2 = Parameter_Crnt->Text;
   ++ Parameter_Crnt;
  }
  Key = STACKPOP + String_imp("_") + Parameter1 + String_imp("_") + Parameter2;
  (*sequence)[Key].Name                    = command->Name;
  (*sequence)[Key].ID                      = ID_STACKPOP;
  (*sequence)[Key].Parameter["value"]      = Parameter1;
  (*sequence)[Key].Parameter["stackName"]  = Parameter2;
// @MRTZ_endBlock
 }
 else if(command->Name == String_imp(STACKPOPALL))
 {
// @MRTZ_exclude collect_data_for_STACKPOPALL
// @MRTZ_beginBlock
  String_imp Parameter1  = "";
  String_imp Parameter2  = "";
  while(Parameter_Crnt != command->Parameter.end())
  {
   if     ( Parameter_Crnt->Token =="value")
    Parameter1 = Parameter_Crnt->Text;
   else if( Parameter_Crnt->Token =="stackName")
    Parameter2 = Parameter_Crnt->Text;
   ++ Parameter_Crnt;
  }
  Key = STACKPOPALL + String_imp("_") + Parameter1 + String_imp("_") + Parameter2;
  (*sequence)[Key].Name                    = command->Name;
  (*sequence)[Key].ID                      = ID_STACKPOPALL;
  (*sequence)[Key].Parameter["value"]      = Parameter1;
  (*sequence)[Key].Parameter["stackName"]  = Parameter2;
// @MRTZ_endBlock
 }
 else if(command->Name == String_imp(IFSTACKEQUAL))
 {
// @MRTZ_exclude collect_data_for_IFSTACKEQUAL
// @MRTZ_beginBlock
  String_imp Parameter1  = "";
  String_imp Parameter2  = "";
 while(Parameter_Crnt != command->Parameter.end())
  {
   if     ( Parameter_Crnt->Token =="value")
    Parameter1 = Parameter_Crnt->Text;
   else if( Parameter_Crnt->Token =="stackName")
    Parameter2 = Parameter_Crnt->Text;
   ++ Parameter_Crnt;
  }
  Key = IFSTACKEQUAL + String_imp("_") + Parameter1 + String_imp("_") + Parameter2;
  (*sequence)[Key].Name                    = command->Name;
  (*sequence)[Key].ID                      = ID_IFSTACKEQUAL;
  (*sequence)[Key].Parameter["value"]      = Parameter1;
  (*sequence)[Key].Parameter["stackName"]  = Parameter2;
// @MRTZ_endBlock
 }
 else if(command->Name == String_imp(IFSTACKUNEQUAL))
 {
  String_imp Parameter1  = "";
  String_imp Parameter2  = "";
// @MRTZ_exclude collect_data_for_IFSTACKUNEQUAL
// @MRTZ_beginBlock
  while(Parameter_Crnt != command->Parameter.end())
  {
   if     ( Parameter_Crnt->Token =="value")
    Parameter1 = Parameter_Crnt->Text;
   else if( Parameter_Crnt->Token =="stackName")
    Parameter2 = Parameter_Crnt->Text;
   ++ Parameter_Crnt;
  }
  Key = IFSTACKUNEQUAL + String_imp("_") + Parameter1 + String_imp("_") + Parameter2;
  (*sequence)[Key].Name                    = command->Name;
  (*sequence)[Key].ID                      = ID_IFSTACKUNEQUAL;
  (*sequence)[Key].Parameter["value"]      = Parameter1;
  (*sequence)[Key].Parameter["stackName"]  = Parameter2;
// @MRTZ_endBlock
 }

 else
// @MRTZ_exclude sub_ifElseChain_4
// @MRTZ_ifElseChain
      if(command->Name == String_imp(REPEAT_IFSTACKEQUAL))
 {
// @MRTZ_exclude collect_data_for_REPEAT_IFSTACKEQUAL
// @MRTZ_beginBlock
  String_imp Parameter1  = "";
  String_imp Parameter2  = "";
  while(Parameter_Crnt != command->Parameter.end())
  {
   if     ( Parameter_Crnt->Token =="value")
    Parameter1 = Parameter_Crnt->Text;
   else if( Parameter_Crnt->Token =="stackName")
    Parameter2 = Parameter_Crnt->Text;
   ++ Parameter_Crnt;
  }
  Key = IFSTACKEQUAL + String_imp("_") + Parameter1 + String_imp("_") + Parameter2;
  (*sequence)[Key].Name                    = command->Name;
  (*sequence)[Key].ID                      = ID_REPEAT_IFSTACKEQUAL;
  (*sequence)[Key].Parameter["value"]      = Parameter1;
  (*sequence)[Key].Parameter["stackName"]  = Parameter2;
// @MRTZ_endBlock
 }





 else if(command->Name == String_imp(IFOLDERAS))
 {
// @MRTZ_exclude collect_data_for_IFOLDERAS
// @MRTZ_beginBlock
  String_imp Parameter1  = "";
  String_imp Parameter2  = "";
  while(Parameter_Crnt != command->Parameter.end())
  {
   if     ( Parameter_Crnt->Token =="dstName")
    Parameter1 = Parameter_Crnt->Text;
   else if( Parameter_Crnt->Token =="dstPath")
    Parameter2 = Parameter_Crnt->Text;
   ++ Parameter_Crnt;
  }
  Key = IFOLDERAS + String_imp("_") + Parameter1 + String_imp("_") + Parameter2;
  (*sequence)[Key].Name                  = command->Name;
  (*sequence)[Key].ID                    = ID_IFOLDERAS;
  (*sequence)[Key].Parameter["dstName"]  = Parameter1;
  (*sequence)[Key].Parameter["dstPath"]  = Parameter2;
// @MRTZ_endBlock
 }
 else if(command->Name == String_imp(IFNOTEXIST))
 {
// @MRTZ_exclude collect_data_for_IFNOTEXIST
// @MRTZ_beginBlock
  String_imp Parameter1  = "";
  String_imp Parameter2  = "";
  while(Parameter_Crnt != command->Parameter.end())
  {
   if     ( Parameter_Crnt->Token =="dstName")
    Parameter1 = Parameter_Crnt->Text;
   else if( Parameter_Crnt->Token =="dstPath")
    Parameter2 = Parameter_Crnt->Text;
   ++ Parameter_Crnt;
  }
  Key = IFNOTEXIST + String_imp("_") + Parameter1 + String_imp("_") + Parameter2;
  (*sequence)[Key].Name                  = command->Name;
  (*sequence)[Key].ID                    = ID_IFNOTEXIST;
  (*sequence)[Key].Parameter["dstName"]  = Parameter1;
  (*sequence)[Key].Parameter["dstPath"]  = Parameter2;
// @MRTZ_endBlock
 }







 else if(command->Name == String_imp(REPEAT_IFSTACKUNEQUAL))
 {
// @MRTZ_exclude collect_data_for_REPEAT_IFSTACKUNEQUAL
// @MRTZ_beginBlock
  String_imp Parameter1  = "";
  String_imp Parameter2  = "";
  while(Parameter_Crnt != command->Parameter.end())
  {
   if     ( Parameter_Crnt->Token =="value")
    Parameter1 = Parameter_Crnt->Text;
   else if( Parameter_Crnt->Token =="stackName")
    Parameter2 = Parameter_Crnt->Text;
   ++ Parameter_Crnt;
  }
  Key = IFSTACKUNEQUAL + String_imp("_") + Parameter1 + String_imp("_") + Parameter2;
  (*sequence)[Key].Name                    = command->Name;
  (*sequence)[Key].ID                      = ID_REPEAT_IFSTACKUNEQUAL;
  (*sequence)[Key].Parameter["value"]      = Parameter1;
  (*sequence)[Key].Parameter["stackName"]  = Parameter2;
// @MRTZ_endBlock
 }
 else if(command->Name == String_imp(STACKPUSHSIZE))
 {
// @MRTZ_exclude collect_data_for_STACKPUSHSIZE
// @MRTZ_beginBlock
  String_imp Parameter1  = "";
  String_imp Parameter2  = "";
  while(Parameter_Crnt != command->Parameter.end())
  {
   if     ( Parameter_Crnt->Token =="sourceStack")
    Parameter1 = Parameter_Crnt->Text;
   else if( Parameter_Crnt->Token =="dstntnStack")
    Parameter2 = Parameter_Crnt->Text;
   ++ Parameter_Crnt;
  }
  Key = STACKPUSHSIZE + String_imp("_") + Parameter1 + String_imp("_") + Parameter2;
  (*sequence)[Key].Name                     = command->Name;
  (*sequence)[Key].ID                       = ID_STACKPUSHSIZE;
  (*sequence)[Key].Parameter["sourceStack"] = Parameter1;
  (*sequence)[Key].Parameter["dstntnStack"] = Parameter2;
// @MRTZ_endBlock
 }
 else if(command->Name == String_imp(STACKCLEAR))
 {
// @MRTZ_exclude collect_data_for_STACKCLEAR
// @MRTZ_beginBlock
//  String_imp Parameter1  = "";
  while(Parameter_Crnt != command->Parameter.end())
  {
   if( Parameter_Crnt->Token =="stackName")
   {
    String_imp Parameter1 = Parameter_Crnt->Text;
    Key = STACKCLEAR + String_imp("_") + Parameter_Crnt->Text;
    (*sequence)[Key].Name = command->Name;
    (*sequence)[Key].ID   = ID_STACKCLEAR;
    (*sequence)[Key].Parameter["stackName"] = Parameter1;
   }
   ++ Parameter_Crnt;
  }
// @MRTZ_endBlock
 }
 else


// @MRTZ_exclude sub_ifElseChain_5
// @MRTZ_ifElseChain
      if(command->Name == String_imp(XMLCREATE))
 {
// @MRTZ_exclude collect_data_for_XMLCREATE
// @MRTZ_beginBlock
  String_imp Parameter1  = "";
  String_imp Parameter2  = "";
  String_imp Parameter3  = "";
  String_imp Parameter4  = "";
  while(Parameter_Crnt != command->Parameter.end())
  {
   if     ( Parameter_Crnt->Token == "newName")
    Parameter1 = Parameter_Crnt->Text;
   else if( Parameter_Crnt->Token == "newPath")
   {
    Parameter2  = (Parameter_Crnt->Text).substr(1);
    Parameter3  = (String_imp(Parameter_Crnt->Text)[0]);
   }
   else if( Parameter_Crnt->Token == "snipetName")
    Parameter4 = Parameter_Crnt->Text;
   ++ Parameter_Crnt;
  }
  Key =  Parameter4;
  (*sequence)[Key].Name                    = command->Name;
  (*sequence)[Key].ID                      = ID_XMLCREATE;
  (*sequence)[Key].Parameter["newName"]    = Parameter1;
  (*sequence)[Key].Parameter["newPath"]    = Parameter2;
  (*sequence)[Key].Parameter["separator"]  = Parameter3;
  (*sequence)[Key].Parameter["snipetName"] = Parameter4;
// @MRTZ_endBlock
 }
 else if(command->Name == String_imp(XMLCOPY))
 {
// @MRTZ_exclude collect_data_for_XMLCOPY
// @MRTZ_beginBlock
  String_imp Parameter1  = "";
  String_imp Parameter2  = "";
  String_imp Parameter3  = "";
  String_imp Parameter4  = "";
  String_imp Parameter5  = "";
  while(Parameter_Crnt != command->Parameter.end())
  {
   if     ( Parameter_Crnt->Token =="newName")
   {
    Parameter1 = Parameter_Crnt->Text;
   }
   else if( Parameter_Crnt->Token =="newPath")
   {
    Parameter2 = (Parameter_Crnt->Text).substr(1);
    Parameter5  = (String_imp(Parameter_Crnt->Text)[0]);
   }
   else if( Parameter_Crnt->Token =="tagName")
   {
    Parameter3 = Parameter_Crnt->Text;
   }
   else if( Parameter_Crnt->Token =="tagPath")
   {
    Parameter4  = (Parameter_Crnt->Text).substr(1);
    Parameter5  = (String_imp(Parameter_Crnt->Text)[0]);
   }
   ++ Parameter_Crnt;
  }
  Key = XMLCOPY + String_imp("_") + Parameter1 + String_imp("_") + Parameter2;
  (*sequence)[Key].Name                   = command->Name;
  (*sequence)[Key].ID                     = ID_XMLCOPY;
  (*sequence)[Key].Parameter["newName"]   = Parameter1;
  (*sequence)[Key].Parameter["newPath"]   = Parameter2;
  (*sequence)[Key].Parameter["tagName"]   = Parameter3;
  (*sequence)[Key].Parameter["tagPath"]   = Parameter4;
  (*sequence)[Key].Parameter["separator"] = Parameter5;
// @MRTZ_endBlock
 }
 else if(command->Name == String_imp(XMLCUT))
 {
// @MRTZ_exclude collect_data_for_XMLCUT
// @MRTZ_beginBlock
  String_imp Parameter1  = "";
  String_imp Parameter2  = "";
  String_imp Parameter3  = "";
  String_imp Parameter4  = "";
  String_imp Parameter5  = "";
  while(Parameter_Crnt != command->Parameter.end())
  {
   if     ( Parameter_Crnt->Token =="newName")
   {
    Parameter1 = Parameter_Crnt->Text;
   }
   else if( Parameter_Crnt->Token =="newPath")
   {
    Parameter2 = (Parameter_Crnt->Text).substr(1);
    Parameter5 = (String_imp(Parameter_Crnt->Text)[0]);
   }
   else if( Parameter_Crnt->Token =="tagName")
   {
    Parameter3 = Parameter_Crnt->Text;
   }
   else if( Parameter_Crnt->Token =="tagPath")
   {
    Parameter4  = (Parameter_Crnt->Text).substr(1);
    Parameter5  = (String_imp(Parameter_Crnt->Text)[0]);
   }
   ++ Parameter_Crnt;
  }
  Key = XMLCUT + String_imp("_") + Parameter1 + String_imp("_") + Parameter2;
  (*sequence)[Key].Name                   = command->Name;
  (*sequence)[Key].ID                     = ID_XMLCUT;
  (*sequence)[Key].Parameter["newName"]   = Parameter1;
  (*sequence)[Key].Parameter["newPath"]   = Parameter2;
  (*sequence)[Key].Parameter["tagName"]   = Parameter3;
  (*sequence)[Key].Parameter["tagPath"]   = Parameter4;
  (*sequence)[Key].Parameter["separator"] = Parameter5;
// @MRTZ_endBlock
 }


 else if(command->Name == String_imp(XMLCODE))
 {
// @MRTZ_exclude collect_data_for_XMLCODE
// @MRTZ_beginBlock
  String_imp Parameter1  = "";
  String_imp Parameter2  = "";
  String_imp Parameter3  = "";
  String_imp Parameter4  = "";
  String_imp Parameter5  = "";
  while(Parameter_Crnt != command->Parameter.end())
  {
   if     ( Parameter_Crnt->Token =="newName")
   {
    Parameter1 = Parameter_Crnt->Text;
   }
   else if( Parameter_Crnt->Token =="newPath")
   {
    Parameter2 = (Parameter_Crnt->Text).substr(1);
    Parameter5 = (String_imp(Parameter_Crnt->Text)[0]);
   }
   else if( Parameter_Crnt->Token =="tagName")
   {
    Parameter3 = Parameter_Crnt->Text;
   }
   else if( Parameter_Crnt->Token =="tagPath")
   {
    Parameter4  = (Parameter_Crnt->Text).substr(1);
    Parameter5  = (String_imp(Parameter_Crnt->Text)[0]);
   }
   ++ Parameter_Crnt;
  }
  Key = XMLCODE + String_imp("_") + Parameter1 + String_imp("_") + Parameter2;
  (*sequence)[Key].Name                   = command->Name;
  (*sequence)[Key].ID                     = ID_XMLCODE;
  (*sequence)[Key].Parameter["newName"]   = Parameter1;
  (*sequence)[Key].Parameter["newPath"]   = Parameter2;
  (*sequence)[Key].Parameter["tagName"]   = Parameter3;
  (*sequence)[Key].Parameter["tagPath"]   = Parameter4;
  (*sequence)[Key].Parameter["separator"] = Parameter5;
// @MRTZ_endBlock
 }

 else if(command->Name == String_imp(XMLINSERT))
 {
// @MRTZ_exclude collect_data_for_XMLINSERT
// @MRTZ_beginBlock
  String_imp Parameter1  = "";
  String_imp Parameter2  = "";
  String_imp Parameter3  = "";
//  String_imp Parameter4  = "";
  String_imp Parameter5  = "";
  while(Parameter_Crnt != command->Parameter.end())
  {
   if     ( Parameter_Crnt->Token =="newName")
   {
    Parameter1 = Parameter_Crnt->Text;
   }
   else if( Parameter_Crnt->Token =="newPath")
   {
    Parameter2 = (Parameter_Crnt->Text).substr(1);
    Parameter5 = (String_imp(Parameter_Crnt->Text)[0]);
   }
   else if( Parameter_Crnt->Token =="position")
   {
    Parameter3 = Parameter_Crnt->Text;
   }
   ++ Parameter_Crnt;
  }
  Key = "__SELF__";
  (*sequence)[Key].Name                   = command->Name;
  (*sequence)[Key].ID                     = ID_XMLINSERT;
  (*sequence)[Key].Parameter["newName"]   = Parameter1;
  (*sequence)[Key].Parameter["newPath"]   = Parameter2;
  (*sequence)[Key].Parameter["position"]  = Parameter3;
  (*sequence)[Key].Parameter["separator"] = Parameter5;

// @MRTZ_endBlock
 }



 else if(command->Name == String_imp(XMLSNIPET))
 {
// @MRTZ_exclude collect_data_for_XMLSNIPET
// @MRTZ_beginBlock
  String_imp Parameter1  = "";
  String_imp Parameter2  = "";
  String_imp Parameter3  = "";
  String_imp Parameter4  = "";
  while(Parameter_Crnt != command->Parameter.end())
  {
   if     ( Parameter_Crnt->Token =="newName")
   {
    Parameter1 = Parameter_Crnt->Text;
   }
   else if( Parameter_Crnt->Token =="tagPath")
   {
    Parameter2  = (Parameter_Crnt->Text).substr(1);
    Parameter3  = (String_imp(Parameter_Crnt->Text)[0]);
   }
   else if( Parameter_Crnt->Token =="tolerant")
   {
    Parameter4  = Parameter_Crnt->Text;
   }
   ++ Parameter_Crnt;
  }
  Key = XMLSNIPET + String_imp("_") + Parameter1 + String_imp("_") + Parameter2;
  (*sequence)[Key].Name                   = command->Name;
  (*sequence)[Key].ID                     = ID_XMLSNIPET;
  (*sequence)[Key].Parameter["newName"]   = Parameter1;
  (*sequence)[Key].Parameter["tagPath"]   = Parameter2;
  (*sequence)[Key].Parameter["separator"] = Parameter3;
  (*sequence)[Key].Parameter["tolerant"]  = Parameter4;
// @MRTZ_endBlock
 }

 else if(command->Name == String_imp(XMLSAVE))
 {
// @MRTZ_exclude collect_data_for_XMLDELETE
// @MRTZ_beginBlock
  String_imp Parameter1  = "";
  String_imp Parameter2  = "";
  String_imp Parameter3  = "";
  String_imp Parameter4  = "";
  String_imp Parameter5  = "";
  while(Parameter_Crnt != command->Parameter.end())
  {
   if     ( Parameter_Crnt->Token == "newName")
    Parameter1 = Parameter_Crnt->Text;
   else if( Parameter_Crnt->Token == "newPath")
   {
    Parameter2 = (Parameter_Crnt->Text).substr(1);
    Parameter5 = (String_imp(Parameter_Crnt->Text)[0]);
   }
   else if( Parameter_Crnt->Token == "fileName")
    Parameter3 = Parameter_Crnt->Text;
   else if( Parameter_Crnt->Token == "filePath")
    Parameter4 = Parameter_Crnt->Text;
   ++ Parameter_Crnt;
  }
  Key = XMLSAVE + String_imp("_") + Parameter1;
  (*sequence)[Key].Name                    = command->Name;
  (*sequence)[Key].ID                      = ID_XMLSAVE;
  (*sequence)[Key].Parameter["newName"]    = Parameter1;
  (*sequence)[Key].Parameter["newPath"]    = Parameter2;
  (*sequence)[Key].Parameter["fileName"]   = Parameter3;
  (*sequence)[Key].Parameter["filePath"]   = Parameter4;
  (*sequence)[Key].Parameter["separator"]  = Parameter5;
// @MRTZ_endBlock
 }

else if(command->Name == String_imp(XMLDELETE))
 {
// @MRTZ_exclude collect_data_for_XMLDELETE
// @MRTZ_beginBlock
  String_imp Parameter1  = "";
  String_imp Parameter2  = "";
  String_imp Parameter3  = "";
  while(Parameter_Crnt != command->Parameter.end())
  {
   if     ( Parameter_Crnt->Token == "newName")
    Parameter1 = Parameter_Crnt->Text;
   else if( Parameter_Crnt->Token == "newPath")
   {
    Parameter2  = (Parameter_Crnt->Text).substr(1);
    Parameter3  = (String_imp(Parameter_Crnt->Text)[0]);
   }
   ++ Parameter_Crnt;
  }
  Key = XMLDELETE + String_imp("_") + Parameter1;
  (*sequence)[Key].Name                   = command->Name;
  (*sequence)[Key].ID                     = ID_XMLDELETE;
  (*sequence)[Key].Parameter["newName"]   = Parameter1;
  (*sequence)[Key].Parameter["newPath"]   = Parameter2;
  (*sequence)[Key].Parameter["separator"] = Parameter3;
// @MRTZ_endBlock
 }



 else if(command->Name == String_imp(XMLPRINT))
 {
// @MRTZ_exclude collect_data_for_IFXMLPRINT
// @MRTZ_beginBlock
  String_imp Parameter1  = "";
  String_imp Parameter2  = "";
  String_imp Parameter3  = "";
  String_imp Parameter4  = "";
  String_imp Parameter5  = "";
  while(Parameter_Crnt != command->Parameter.end())
  {
   if     ( Parameter_Crnt->Token =="prefix")
   {
    Parameter1 = Parameter_Crnt->Text;
   }
   else if( Parameter_Crnt->Token =="xmlProperty")
   {
    Parameter2 = Parameter_Crnt->Text;
   }
   else if( Parameter_Crnt->Token =="tagName")
   {
    Parameter3 = Parameter_Crnt->Text;
   }
   else if( Parameter_Crnt->Token =="tagPath")
   {
    Parameter4  = (Parameter_Crnt->Text).substr(1);
    Parameter5  = (String_imp(Parameter_Crnt->Text)[0]);
   }
   ++ Parameter_Crnt;
  }
  Key = XMLPRINT + String_imp("_") + Parameter1 + String_imp("_") + Parameter2;
  (*sequence)[Key].Name                     = command->Name;
  (*sequence)[Key].ID                       = ID_XMLPRINT;
  (*sequence)[Key].Parameter["prefix"]      = Parameter1;
  (*sequence)[Key].Parameter["xmlProperty"] = Parameter2;
  (*sequence)[Key].Parameter["tagName"]     = Parameter3;
  (*sequence)[Key].Parameter["tagPath"]     = Parameter4;
  (*sequence)[Key].Parameter["separator"]   = Parameter5;
// @MRTZ_endBlock
 }





 else if(command->Name == String_imp(IFXMLEQUAL))
 {
// @MRTZ_exclude collect_data_for_IFXMLEQUAL
// @MRTZ_beginBlock
  String_imp Parameter1  = "";
  String_imp Parameter2  = "";
  String_imp Parameter3  = "";
  String_imp Parameter4  = "";
  String_imp Parameter5  = "";
  while(Parameter_Crnt != command->Parameter.end())
  {
   if     ( Parameter_Crnt->Token =="value")
   {
    Parameter1 = Parameter_Crnt->Text;
   }
   else if( Parameter_Crnt->Token =="xmlProperty")
   {
    Parameter2 = Parameter_Crnt->Text;
   }
   else if( Parameter_Crnt->Token =="tagName")
   {
    Parameter3 = Parameter_Crnt->Text;
   }
   else if( Parameter_Crnt->Token =="tagPath")
   {
    Parameter4  = (Parameter_Crnt->Text).substr(1);
    Parameter5  = (String_imp(Parameter_Crnt->Text)[0]);
   }
   ++ Parameter_Crnt;
  }
  Key = IFXMLEQUAL + String_imp("_") + Parameter1 + String_imp("_") + Parameter2;
  (*sequence)[Key].Name                     = command->Name;
  (*sequence)[Key].ID                       = ID_IFXMLEQUAL;
  (*sequence)[Key].Parameter["value"]       = Parameter1;
  (*sequence)[Key].Parameter["xmlProperty"] = Parameter2;
  (*sequence)[Key].Parameter["tagName"]     = Parameter3;
  (*sequence)[Key].Parameter["tagPath"]     = Parameter4;
  (*sequence)[Key].Parameter["separator"]   = Parameter5;
// @MRTZ_endBlock
 }




 else if(command->Name == String_imp(IFXMLUNEQUAL))
 {
// @MRTZ_exclude collect_data_for_IFXMLUNEQUAL
// @MRTZ_beginBlock
  String_imp Parameter1  = "";
  String_imp Parameter2  = "";
  String_imp Parameter3  = "";
  String_imp Parameter4  = "";
  String_imp Parameter5  = "";
  while(Parameter_Crnt != command->Parameter.end())
  {
   if     ( Parameter_Crnt->Token =="value")
   {
    Parameter1 = Parameter_Crnt->Text;
   }
   else if( Parameter_Crnt->Token =="xmlProperty")
   {
    Parameter2 = Parameter_Crnt->Text;
   }
   else if( Parameter_Crnt->Token =="tagName")
   {
    Parameter3 = Parameter_Crnt->Text;
   }
   else if( Parameter_Crnt->Token =="tagPath")
   {
    Parameter4  = (Parameter_Crnt->Text).substr(1);
    Parameter5  = (String_imp(Parameter_Crnt->Text)[0]);
   }
   ++ Parameter_Crnt;
  }
  Key = IFXMLUNEQUAL + String_imp("_") + Parameter1 + String_imp("_") + Parameter2;
  (*sequence)[Key].Name                     = command->Name;
  (*sequence)[Key].ID                       = ID_IFXMLUNEQUAL;
  (*sequence)[Key].Parameter["value"]       = Parameter1;
  (*sequence)[Key].Parameter["xmlProperty"] = Parameter2;
  (*sequence)[Key].Parameter["tagName"]     = Parameter3;
  (*sequence)[Key].Parameter["tagPath"]     = Parameter4;
  (*sequence)[Key].Parameter["separator"]   = Parameter5;
// @MRTZ_endBlock
 }




 else if(command->Name == String_imp(IFXMLEXISTING))
 {
// @MRTZ_exclude collect_data_for_IFXMLEQUAL
// @MRTZ_beginBlock
  String_imp Parameter1  = "";
  String_imp Parameter2  = "";
  String_imp Parameter3  = "";
  String_imp Parameter4  = "";
  String_imp Parameter5  = "";
  while(Parameter_Crnt != command->Parameter.end())
  {
   if     ( Parameter_Crnt->Token =="xmlProperty")
   {
    Parameter2 = Parameter_Crnt->Text;
   }
   else if( Parameter_Crnt->Token =="tagName")
   {
    Parameter3 = Parameter_Crnt->Text;
   }
   else if( Parameter_Crnt->Token =="tagPath")
   {
    Parameter4  = (Parameter_Crnt->Text).substr(1);
    Parameter5  = (String_imp(Parameter_Crnt->Text)[0]);
   }
   ++ Parameter_Crnt;
  }
  Key = IFXMLEXISTING + String_imp("_") + Parameter1 + String_imp("_") + Parameter2;
  (*sequence)[Key].Name                     = command->Name;
  (*sequence)[Key].ID                       = ID_IFXMLEXISTING;
  (*sequence)[Key].Parameter["xmlProperty"] = Parameter2;
  (*sequence)[Key].Parameter["tagName"]     = Parameter3;
  (*sequence)[Key].Parameter["tagPath"]     = Parameter4;
  (*sequence)[Key].Parameter["separator"]   = Parameter5;
// @MRTZ_endBlock
 }




 else if(command->Name == String_imp(IFXMLMISSING))
 {
// @MRTZ_exclude collect_data_for_IFXMLMISSING
// @MRTZ_beginBlock
  String_imp Parameter1  = "";
  String_imp Parameter2  = "";
  String_imp Parameter3  = "";
  String_imp Parameter4  = "";
  String_imp Parameter5  = "";
  while(Parameter_Crnt != command->Parameter.end())
  {
   if     ( Parameter_Crnt->Token =="xmlProperty")
   {
    Parameter2 = Parameter_Crnt->Text;
   }
   else if( Parameter_Crnt->Token =="tagName")
   {
    Parameter3 = Parameter_Crnt->Text;
   }
   else if( Parameter_Crnt->Token =="tagPath")
   {
    Parameter4  = (Parameter_Crnt->Text).substr(1);
    Parameter5  = (String_imp(Parameter_Crnt->Text)[0]);
   }
   ++ Parameter_Crnt;
  }
  Key = IFXMLMISSING + String_imp("_") + Parameter1 + String_imp("_") + Parameter2;
  (*sequence)[Key].Name                     = command->Name;
  (*sequence)[Key].ID                       = ID_IFXMLMISSING;
  (*sequence)[Key].Parameter["xmlProperty"] = Parameter2;
  (*sequence)[Key].Parameter["tagName"]     = Parameter3;
  (*sequence)[Key].Parameter["tagPath"]     = Parameter4;
  (*sequence)[Key].Parameter["separator"]   = Parameter5;
// @MRTZ_endBlock
 }



















else if(command->Name == String_imp(PARSERSET))
 {
// @MRTZ_exclude collect_data_for_PARSERSET
// @MRTZ_beginBlock
  String_imp Parameter1  = "";
  String_imp Parameter2  = "";
  String_imp Parameter3  = "";
  String_imp Parameter4  = "";
  String_imp Parameter5  = "";
  while(Parameter_Crnt != command->Parameter.end())
  {
   if     ( Parameter_Crnt->Token == "cfg_path")
    Parameter1 = Parameter_Crnt->Text;
   else if( Parameter_Crnt->Token == "configuration")
   {
    Parameter2 = Parameter_Crnt->Text;
   }
   else if( Parameter_Crnt->Token == "grm_path")
   {
    Parameter3 = Parameter_Crnt->Text;
   }
   else if( Parameter_Crnt->Token == "grammar")
   {
    Parameter4 = Parameter_Crnt->Text;
   }
   else if( Parameter_Crnt->Token == "prs_root")
   {
    Parameter5 = Parameter_Crnt->Text;
   }
   ++ Parameter_Crnt;
  }
  Key = PARSERSET + String_imp("_") + Parameter1;
  (*sequence)[Key].Name                       = command->Name;
  (*sequence)[Key].ID                         = ID_PARSERSET;
  (*sequence)[Key].Parameter["cfg_path"]      = Parameter1;
  (*sequence)[Key].Parameter["configuration"] = Parameter2;
  (*sequence)[Key].Parameter["grm_path"]      = Parameter3;
  (*sequence)[Key].Parameter["grammar"]       = Parameter4;
  (*sequence)[Key].Parameter["prs_root"]      = Parameter5;
// @MRTZ_endBlock
 }

 else if(command->Name == String_imp(PARSE))
 {
// @MRTZ_exclude collect_data_for_PARSE
// @MRTZ_beginBlock
  String_imp Parameter1  = "";
  String_imp Parameter2  = "";
  String_imp Parameter3  = "";
  String_imp Parameter4  = "";
  String_imp Parameter5  = "";
  while(Parameter_Crnt != command->Parameter.end())
  {
   if     ( Parameter_Crnt->Token =="textToParse")
   {
    Parameter1 = Parameter_Crnt->Text;
   }
   else if( Parameter_Crnt->Token =="rule")
   {
    Parameter2 = (Parameter_Crnt->Text);
   }
   else if( Parameter_Crnt->Token =="newName")
   {
    Parameter3 = Parameter_Crnt->Text;
   }
   else if( Parameter_Crnt->Token =="newPath")
   {
    Parameter4  = (Parameter_Crnt->Text).substr(1);
    Parameter5  = (String_imp(Parameter_Crnt->Text)[0]);
   }
   ++ Parameter_Crnt;
  }
  Key = PARSE + String_imp("_") + Parameter1 + String_imp("_") + Parameter2;
  (*sequence)[Key].Name                     = command->Name;
  (*sequence)[Key].ID                       = ID_PARSE;
  (*sequence)[Key].Parameter["textToParse"] = Parameter1;
  (*sequence)[Key].Parameter["rule"]        = Parameter2;
  (*sequence)[Key].Parameter["newName"]     = Parameter3;
  (*sequence)[Key].Parameter["tnewPath"]    = Parameter4;
  (*sequence)[Key].Parameter["separator"]   = Parameter5;
// @MRTZ_endBlock
 }







 else
 {
#if defined(DEBUG_OUTPUT)
   cout<<"\nelse\n";
#endif //DEBUG_OUTPUT
 }
}






















/* @MRTZ_describe replacmentSet

*/
void Cmnd_Common::replacmentSet(      String_imp             oldPart,
                                      String_imp             newPart,
                                const String_imp&            replaceReset,
                                map<String_imp, String_imp>* replacement)
{
 struct
 {
  Cmnd_Stack_Strg Stack;
 }Cmnd;

#if defined(DEBUG_OUTPUT)
 cout << " in |" << oldPart << "|>>>>>>>>>>>>>>" ;
#endif //DEBUG_OUTPUT

            oldPart = Cmnd.Stack.exchange(oldPart,replacement);
            newPart = Cmnd.Stack.exchange(newPart,replacement);

 String_imp OldPart = replacePartString(oldPart,"replace_","");


#if defined(DEBUG_OUTPUT)
 cout << " OldPart: |" << OldPart << "|" ;
 cout << " newPart: |" << newPart << "|" ;
#endif //DEBUG_OUTPUT



 if(  (OldPart.size()>1)
    &&(OldPart[0] == '\"')
   )
  OldPart = OldPart.substr(1,OldPart.size()-2);
 if(  (OldPart.size()>1)
    &&(OldPart[OldPart.size()-1] == '\"')
   )
  OldPart = OldPart.substr(0,OldPart.size()-2);

 if(  (newPart.size()>1)
    &&(newPart[0] == '\"')
   )
  newPart = newPart.substr(1,newPart.size()-2);
 if(  (newPart.size()>1)
    &&(newPart[newPart.size()-1] == '\"')
   )
  newPart = newPart.substr(0,newPart.size()-2);

#if defined(DEBUG_OUTPUT)
 cout << "replace : ";
 cout << " OldPart: |" << OldPart << "|" ;
 cout << " newPart: |" << newPart << "|" ;
 cout << " replaceReset : |" << replaceReset << "|" << endl;
#endif //DEBUG_OUTPUT


 if(replaceReset == "__RESET__")
 {
  replacement->clear();
 }
 else
 {
  if(OldPart == "")
   OldPart = EMPTYSTRING;

  if(newPart != OldPart)
  {
   (*replacement)[OldPart] = newPart;
  }
  else
//   if(replacement->find(OldPart)!= replacement->end())
    replacement->erase(OldPart);
 }
}




/* @MRTZ_describe replacmentUse

*/
String_imp Cmnd_Common::replacmentUse(const String_imp&            oldString,
                                      map<String_imp, String_imp>* replacement)
{
 map<String_imp, String_imp>::iterator Current;

 String_imp ReturnValue = oldString;
  Current  = replacement->begin();
#if defined(DEBUG_OUTPUT)
  cout << endl << "replace in StackRead :" << ReturnValue << endl;
#endif //DEBUG_OUTPUT
  while(Current != replacement->end())
  {
#if defined(DEBUG_OUTPUT)
   cout << " Old Part |" << Current->first  << "|" << endl;
   cout << " New Part |" << Current->second << "|" << endl;
#endif //DEBUG_OUTPUT
   ReturnValue = replacePartString(ReturnValue,Current->first,Current->second);
   ++ Current ;
  }
  if(ReturnValue == "" )//use default-value since tailored value is empty
  {
#if defined(DEBUG_OUTPUT)
   cout << " Text is empty " << endl;
   cout << " and will be replaced by : |" << (*replacement)[EMPTYSTRING] << "|" << endl;
#endif //DEBUG_OUTPUT
   ReturnValue = (*replacement)[EMPTYSTRING];
  }

#if defined(DEBUG_OUTPUT)
  cout << "new Text :" << ReturnValue << endl << endl;
#endif //DEBUG_OUTPUT


 return(ReturnValue);
}










#ifndef DOXYGEN
#define USING_NAMESPACE  using namespace
//}; USING_NAMESPACE CL_COMMAND ;
#undef  USING_NAMESPACE
#endif //DOXYGEN







