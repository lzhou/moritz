/*!

 @file
 @brief definitions of very simple parser-functions just to create an
 parser-tree

 Copyright (C) 2014-2018 by Eckard Klotz.

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
    27.07.2014     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    27.07.2014...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/




#include <cstring>

/**/
#include <iostream>

#include "tinyprsr.h"



#ifndef DOXYGEN
//namespace TXTDIASM{
#endif //DOXYGEN

using namespace std;









/* @MRTZ_describe TerminatedRule_parse

*/
 list<TerminatedResult_TP*> TerminatedRule_parse(const char* textBegin,
                                                 const char* textEnd,
                                                 const char* identifier,
                                                 const char* startToken,
                                                 const char* endToken )
 {
  list<TerminatedResult_TP*> ReturnValue;
  unsigned int               NestedCounter = 0;
  char*                      CurrentChar   = (char*) textBegin;


  TerminatedResult_TP* PlainText = new TerminatedResult_TP;
                       PlainText->ContentBegin  = CurrentChar;
                       PlainText->ContentEnd    = CurrentChar;
                       PlainText->ContentLength = 0;
                       PlainText->Identifier    = "PlainText";
                       PlainText->StartToken    = nullptr;
                       PlainText->EndToken      = nullptr;


  while(CurrentChar < textEnd)                         // until end of text
  {
    if(strstr(CurrentChar, startToken) == CurrentChar) // start token found
    {

     if(PlainText->ContentLength > 0)                  // plain text has to be saved
     {
      PlainText->ContentLength = (PlainText->ContentEnd)-(PlainText->ContentBegin) + 1;
      ReturnValue.push_back(PlainText);
      PlainText = new TerminatedResult_TP;
     }
     else                                              // no plain text found before
     {}

     CurrentChar = CurrentChar + strlen(startToken);
     PlainText->ContentBegin  = CurrentChar;
     PlainText->ContentEnd    = CurrentChar;
     PlainText->ContentLength = 0;
     PlainText->Identifier    = identifier;
     PlainText->StartToken    = startToken;
     PlainText->EndToken      = endToken;
     //++ CurrentChar;

     while(  (  (strstr(CurrentChar, endToken) != CurrentChar)
              ||(NestedCounter                 != 0        )
             )
           &&(CurrentChar < textEnd)
          ) // end-token found that is not part of nested pattern and end of text not reached
     {
      if     (strstr(CurrentChar, startToken) == CurrentChar) // nested pattern start
       ++ NestedCounter;
      else if(strstr(CurrentChar, endToken  ) == CurrentChar) // nested pattern end
       -- NestedCounter;
      else
      { /*keep NestedCounter as it is*/ }
      ++ CurrentChar;
      PlainText->ContentEnd       = CurrentChar;

     }

    PlainText->ContentLength=(PlainText->ContentEnd)-(PlainText->ContentBegin);


     if(CurrentChar < textEnd)
      CurrentChar = CurrentChar + strlen(endToken);
     else
      PlainText->Identifier  = "Invalid";

     if(PlainText->ContentLength > 0)// plain text has to be saved
     {
      ReturnValue.push_back(PlainText);

      PlainText = new TerminatedResult_TP;
      PlainText->ContentBegin  = CurrentChar;
      PlainText->ContentEnd    = CurrentChar;
      PlainText->ContentLength = 0;
      PlainText->Identifier    = "PlainText";
      PlainText->StartToken    = nullptr;
      PlainText->EndToken      = nullptr;
     }
     CurrentChar = CurrentChar + strlen(endToken);
    }



   if(  (CurrentChar <= textEnd)
     )// no end of text
   {
     PlainText->ContentEnd    = CurrentChar;
     ++ PlainText->ContentLength;
   }

   ++ CurrentChar;
  }

  if(PlainText->ContentLength > 0)// plain text has to be saved
  {
   ++ PlainText->ContentLength;
   ReturnValue.push_back(PlainText);
  }

  return(ReturnValue);
 }



/* @MRTZ_describe SpliterRule_parse

*/
 list<TerminatedResult_TP*> SpliterRule_parse(const char* textBegin,
                                              const char* textEnd,
                                              const char* splitToken)

 {
  list<TerminatedResult_TP*> ReturnValue;
  char*                      CurrentChar = (char*)textBegin;

  TerminatedResult_TP* PlainText = new TerminatedResult_TP;
                       PlainText->ContentBegin  = CurrentChar;
                       PlainText->ContentEnd    = CurrentChar;
                       PlainText->ContentLength = 0;
                       PlainText->Identifier    = "PlainText";
                       PlainText->StartToken    = nullptr;
                       PlainText->EndToken      = nullptr;


  while(  (CurrentChar < textEnd)
       )// until end of text
  {

   if(strstr(CurrentChar, splitToken) == CurrentChar) // splitter token found
   {

    if(PlainText->ContentLength > 0)                  // plain text has to be saved
    {
     ReturnValue.push_back(PlainText);
     CurrentChar = CurrentChar + strlen(splitToken);

      PlainText = new TerminatedResult_TP;
      PlainText->ContentBegin  = CurrentChar;
      PlainText->ContentEnd    = CurrentChar;
      PlainText->ContentLength = 0;
      PlainText->Identifier    = "PlainText";
      PlainText->StartToken    = nullptr;
      PlainText->EndToken      = nullptr;
    }
    else                                              // no plain text found before
    {}
   }

   if(CurrentChar < textEnd)                          // no end of text or end of part described by end token
   {
     PlainText->ContentEnd    = CurrentChar;
     ++ PlainText->ContentLength;
   }

    ++ CurrentChar;
  }

  if(PlainText->ContentLength > 0)                    // plain text has to be saved
  {
   ++ PlainText->ContentLength;
   ReturnValue.push_back(PlainText);

  }

  return(ReturnValue);
 }


bool ParserNode_getText(char** text, ParserNode_TP* parsernode)
{
 bool ReturnValue = true;                               // trust in given inputs

 if(  (*text == nullptr)
    &&(parsernode->Length > 0)
   )                                                    // return-pointer is valid and parser node really contains some text
 {
  (*text) = new char[parsernode->Length+1];             // allocate memory with additional place for final termination
  strncpy((*text),parsernode->Begin,parsernode->Length);// copy content
  (*text)[parsernode->Length]=0;                        // ensure termination of string
 }
 else                                                   // no valid return-pointer or parser-node is empty
 {
  ReturnValue = false;                                  // trust was disappointed
 }

 return(ReturnValue);
}















#ifndef DOXYGEN
#define USING_NAMESPACE using namespace
//}; USING_NAMESPACE TXTDIASM;
#undef  USING_NAMESPACE
#endif //DOXYGEN



