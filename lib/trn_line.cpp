/*!

 @file
 @brief  definition of a line parser-process defined by the user

 This file contains the definition of a user parser-process to analyse the line-changes.

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
    27.08.2009     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    27.08.2009...  @I Eckard Klotz
 @I Changes are documented in the comment of the changed element
 @TabEnd

*/

#include "trn_line.h"


//#include "TiPa_Filter.h"


#ifndef DOXYGEN
//namespace CL_PROCESS {
//namespace CL_TRANSFORM {
//namespace CL_TRN_LINE {
#endif //DOXYGEN



const String_imp  CONTENT    = "Content";
const String_imp  LINECHANGE = "LineChange";



/* @MRTZ_describe Prcs_Trn_Line

*/
Prcs_Trn_Line::Prcs_Trn_Line(int               startLine,
                             int               startColumn,
                             int               tabSize,
                             const String_imp& tokenIndent,
                             const String_imp& tokenDedent,
                             const String_imp& tokenNewLine,
                             const String_imp& tokenEndMarker,
                             bool              showTextToParse)
{
  TextMakeup.StartLine     = startLine;
  TextMakeup.StartColumn   = startColumn;
  Att.TabSize              = tabSize;
  Att.ShowTextToParse      = showTextToParse;

  if(tokenIndent != "")
   Att.TokenIndent = tokenIndent + " ";
  else
   Att.TokenIndent = "";

  if(tokenDedent != "")
   Att.TokenDedent = tokenDedent + " ";
  else
   Att.TokenDedent = "";

  if(tokenNewLine != "")
   Att.TokenNewLine = tokenNewLine + " ";
  else
   Att.TokenNewLine = "";

  if(tokenEndMarker != "")
   Att.TokenEndMarker = tokenEndMarker + " ";
  else
   Att.TokenEndMarker = "";
}

/* @MRTZ_describe ~Prcs_Trn_Line

*/
Prcs_Trn_Line::~Prcs_Trn_Line()
{
}

#include "Spirit185_Store.h"

/* @MRTZ_describe analyse

   @MRTZ_describe physical_line_connections

   @MRTZ_describe evaluate_hits

   @MRTZ_describe build_new_text

*/
TiPa_Concrete::DataFellow* Prcs_Trn_Line::analyse(String_imp*       text,
                                                  TiPa_DataModel*   model/*,
                                                  const String_imp& rule*/)
{
 TiPa_Concrete::DataFellow*  ReturnValue = nullptr;

 while(!(Att.IndentionContainer.empty()))
 {
  Att.IndentionContainer.erase(Att.IndentionContainer.begin());
 };

 if(Att.ShowTextToParse == true)
 // printf("\n\nText to parse:\n%s\n",text->c_str());
  cout << "\n\nText to parse:\n" << *text << endl;

 // a missing line-change on the end of the file may result a wrong INDENT
 (*text) = (*text) + '\n';

 ContextModel.init();
 Grammar_Spirit185->pre_parse(text->c_str(),text->c_str()+text->size());
                                            // parse for line-changes to know line and column numbers
 Grammar_Spirit185->scan(text->c_str(),text->c_str()+text->size(),"precut");
                                            // scan for text-positions to manipulate temporarily
 TiPa_Concrete::DataFellow* GrammarTree = Grammar_Spirit185->scanData("precut");
                                            // scan result

 if(GrammarTree != nullptr)
 {
  ResultFilter.contextModel_set(model);

  GrammarTree->welcome(ResultFilter(Spirit185_Filter::KeepUndefined, model->focus_Fellow(), Spirit185_Filter::CloneData),IterateDownwards);
                                            // reduce to pre-cut level

  Spirit185_Store ResultStore;
  char*           ParsedText = nullptr ;
  model->focus_Fellow()->welcome(ResultStore(Spirit185_Store::Content2XML,&ParsedText),IterateDownwards);

  delete[]ParsedText;


  postAnalysis(model,text);
  ReturnValue = model->focus_Fellow();
  TiPa_Data* ReturnData = ReturnValue->data_get();
//             ReturnData->userName_set((char*) ReturnData->secondaryData_add("UserName", "Content"));
             ReturnData->userName_set(CONTENT.c_str());
             ReturnData->lineSet(1);
             ReturnData->columnSet(1);

  LOG_OUTPUT(LOG_ON,"...................... Grammar Tree created ...................");
 }
 else
 {
  LOG_OUTPUT(LOG_ON,"!!!!!!!!!!!!!!!!!!!!No Grammar Tree created!!!!!!!!!!!!!!!!!!!!");
 }

 Grammar_Spirit185->TDA_GrmConcrete::init();
 ContextModel.init();

#if defined(DEBUG_OUTPUT)
  Spirit185_Store ResultStore;
  char*           ParsedText = nullptr ;
  model->focus_Fellow()->welcome(ResultStore(Spirit185_Store::Content2XML,&ParsedText),IterateDownwards);

  cout << "Line output Result: " << endl;
  cout << ParsedText << endl;
#endif


 return(ReturnValue);
}










/* @MRTZ_describe postAnalysis

   @MRTZ_describe physical_line_connections

   @MRTZ_describe evaluate_hits

   @MRTZ_describe build_new_text

*/
void   Prcs_Trn_Line::postAnalysis(TiPa_DataModel* result, String_imp* text)
{
 TiPa_Concrete::DataAssociation* LineChange   = result->focus_Fellow()->contractorFirst_get();
 while(LineChange != nullptr)
 {
  TiPa_Data*   Data = LineChange->data_get();                                    // a single parsing-data

//  Data->userName_set((char*)Data->secondaryData_add("UserName","LineChange"));
  Data->userName_set(LINECHANGE.c_str());
                                                                                 // replace tag name pre-cut by line-change
  LineChange = LineChange->fellowBehind_get();
 }


// @MRTZ_exclude physical_line_connections
// @MRTZ_beginBlock

 map<const char*, char*>         TempCutOut;                                     // container of original text-parts

                                                                                 // which should be replace temporarily
 TiPa_Concrete::DataAssociation* Line = result->focus_Fellow()->contractorFirst_get();       // first text-Part to replace
 while(Line != nullptr)                                                             // iterate over all text-parts to replace
 {
  char* Original = new char[Line->data_get()->End - Line->data_get()->Begin + 1];// create place to store original text-part
  int Index = 0;                                                                 // write position to store
  char* Character = (char*) (Line->data_get()->Begin);                           // position of character to store
  while(Character != Line->data_get()->End)                                      // iterate over found text-part
  {
    Original[Index] = (*Character);                                              // copy original character
    ++Index;                                                                     // next place to save original character
   (*Character) = ' ';                                                           // replace
   ++Character;                                                                  // next character to save and replace
  }
  Original[Index] = 0;                                                           // terminate copy

  TempCutOut[Line->data_get()->Begin] = Original;                                // store saved text-part

  Line = Line->fellowBehind_get(result->focus_Fellow());                         // next text-part to replace
 }


 Grammar_Spirit185->scan(text->c_str(),text->c_str()+text->size(),"pass");       // scan for text-positions to manipulate permanently

 Line = result->focus_Fellow()->contractorFirst_get();                           // first text-part to restore
 while(Line != nullptr)                                                             // iterate over all text-parts to restore
 {
  char* Original = TempCutOut[Line->data_get()->Begin];                          // original text-part
  char* Character = (char*) Line->data_get()->Begin;                             // character-position to fill with original content
  while(Character != Line->data_get()->End)                                      // iterate over found text-part
  {
   if((*Original) <= 32)                                                         // original character is not a control character or a white space
    (*Character) = (*Original) ;                                                 // restore original character
   ++Original;                                                                   // next original character
   ++Character;                                                                  // next character to replace
  }

  delete(TempCutOut[Line->data_get()->Begin]);                                   // erase single stored original
  TempCutOut[Line->data_get()->Begin] = nullptr;                                    // reinitialise pointer
  Line = Line->fellowBehind_get(result->focus_Fellow());                            // next text-part to restore
 }
 TempCutOut.clear();                                                             // reinitialize store-place
// @MRTZ_endBlock


// @MRTZ_exclude evaluate_hits
// @MRTZ_beginBlock

 TiPa_Concrete::DataFellow* MainTree = Grammar_Spirit185->scanData("pass");
                                                                                 // get text-positions to manipulate permanently
 TiPa_Concrete::DataFellow  ReducedMain;
 MainTree->welcome(ResultFilter(Spirit185_Filter::KeepUndefined, &ReducedMain),IterateDownwards);
                                                                                 // reduce to main-information


 TiPa_Concrete::DataAssociation* Hit = ReducedMain.contractorFirst_get();        // first text-part to manipulate permanently
 while(Hit != nullptr)                                                              // iterate over all text-parts to manipulate
 {
  _eval_SearchRule(Hit);                                                         // evaluate text-parts to manipulate
  Hit = Hit->fellowBehind_get(&ReducedMain);                                     // next text-part to manipulate permanently
 }
// @MRTZ_endBlock


// @MRTZ_exclude build_new_text
// @MRTZ_beginBlock
 if(Att.IndentionContainer.empty()== false)                                        // is empty for languages like c
 {
  String_imp      NewText;                                                         // new text with the manipulates content
  NewText.reserve((text->size())*2);                                               // ensure enough memory
  const char* PosRef  = text->c_str();                                                         // position reference

  Iterator Current = Att.IndentionContainer.begin();                               // first text-part to manipulate
  while(Current != Att.IndentionContainer.end())                                   // iterate over all text-parts to manipulate
  {
   size_t Index  = PosRef  - text->c_str();                                        // point to text to keep
   size_t Length = (Current->Start - PosRef);                                      // length of text to keep
   if(Current->Content.find('\n')<Current->Content.size())                         // line feed was parsed
    Length ++;
   if(Current->Content.find('\r')<Current->Content.size())                         // carriage return was parsed
    Length ++;
   NewText.append(text->substr(Index,Length));                                     // put original text part into new text
   NewText.append(Current->Type);                                                  // append additional tokens into new text
   PosRef = PosRef + Length;                                                       // new reference
   ++Current;                                                                      // next text-part to manipulate
  }
  NewText.append(Att.TokenEndMarker);                                              // add user defined text-end token

  while(!(Att.IndentionContainer.empty()))                                         // clear the container
  {
   Att.IndentionContainer.erase(Att.IndentionContainer.begin());
  };


  (*text) = NewText;                                                               // replace the text
 }
// @MRTZ_endBlock

}





/* @MRTZ_describe _eval_SearchRule

*/
void   Prcs_Trn_Line::_eval_SearchRule(TiPa_Concrete::DataAssociation* hit)
{
 static int  ProcessOff_counter = 0;    //counter of nested code-parts like (), [], [], ...
 static bool ProcessSwitch      = true; //counter of context switching code-parts like " or '

 TiPa_Concrete::DataAssociation* Child = hit->contractorFirst_get();
                                        // first text-part to analyse
 while(Child != nullptr)                   // iterate over all text-parts to analyse
 {
  TiPa_Data* Data = Child->data_get();  // details to analyse

  if(Data->ParserClass == TiPa_Abstract::TDA_TiPa_Rule)
  {
   string RuleName = Data->Parser->as_TiPa_Rule()->getName();

   if     (  (ProcessSwitch      == true)
           &&(RuleName           == String_imp("process_on"))
          )                             // inside active code and next step into a nesting-part
   {
    ProcessOff_counter ++;              // increment nesting-level
   }
   else if(  (ProcessSwitch      == true)
           &&(RuleName           == String_imp("process_off"))
          )                             // inside active code and next leaving of a nesting-part
   {
    ProcessOff_counter --;              // decrement nesting-level
   }
   else if(   RuleName           == String_imp("process_swt") )
                                        // context switch found
   {
    if(ProcessSwitch == true)           // until now active code
    {
     ProcessSwitch = false;             // change to passive code like a string or a comment
    }
    else                                // until now passive code
    {
     ProcessSwitch = true;              // change to active-code
    }
   }
   else if(  (ProcessOff_counter == 0)
           &&(RuleName           == String_imp("process_do"))
          )                             // outside of a nested code-part and manipulation point like line-change found
   {

    _detect_Indention(Data->Begin, Data->End);
                                        // analysis of intention or detention compared with the line before
   }
   else                                 // common text-part
   {
    _eval_SearchRule(Child);            // sub-analysis
   }

  }
  else                                  // common text-part
   _eval_SearchRule(Child);             // sub-analysis

  Child = Child->fellowBehind_get(hit); // next text-part to analyse
 }
}











/* @MRTZ_describe _detect_Indention

   @MRTZ_describe typed_result

   @MRTZ_describe empty_IndentionContainer

   @MRTZ_describe filled_IndentionContainer

   @MRTZ_describe evaluate_IndentionContainer

   @MRTZ_describe non_typed_result

*/
void Prcs_Trn_Line::_detect_Indention(char const* str, char const* end)
{
 String_imp             StringContent(str, end);
 Prcs_Trn_Line::Content_Details Result;
 Result.Content = replaceTabs(& StringContent, Att.TabSize);

 if(Result.Content.find(' ') < Result.Content.size()) // no space in content
  Result.Size    = Result.Content.size() - Result.Content.find(' ');
 else
  Result.Size    = 0 ;
 Result.Start   = (char*)str;
 Result.End     = (char*)end;
 Result.Type    = "";


 if(  (*(Result.End   +0 ) != ' ' )
    &&(*(Result.End   +0 ) != '\n')
    &&(*(Result.End   +0 ) != '\r')
    &&(*(Result.Start -1 ) != '\\')
   )
 {
// @MRTZ_exclude typed_result
// @MRTZ_beginBlock
  if(((Att.IndentionContainer).size()) == 0)
  {
// @MRTZ_exclude empty_IndentionContainer
// @MRTZ_beginBlock

   if(Result.Size > 0)
    Result.Type    = Att.TokenNewLine + Att.TokenIndent;
   else
   {
    Result.Type = Att.TokenNewLine;
   }

// @MRTZ_endBlock
  }
  else
  {
// @MRTZ_exclude filled_IndentionContainer
// @MRTZ_beginBlock
   list<Prcs_Trn_Line::Content_Details>::iterator Before = Att.IndentionContainer.end();
   --Before ;

   if(Before->Size <  Result.Size)
   {
    Result.Type    = Att.TokenNewLine + Att.TokenIndent;
   }
   else
   {
// @MRTZ_exclude evaluate_IndentionContainer
// @MRTZ_beginBlock
    list<Prcs_Trn_Line::Content_Details>::iterator Forbidden = (Att.IndentionContainer).begin();
    -- Forbidden ;
    int IdentCounter = 0;
    while (  (Before       != Forbidden)
           &&(Before->Size >  Result.Size)
          )
    {

     if((*Before).Type.find(Att.TokenNewLine + Att.TokenIndent) == 0)
      IdentCounter++;
     if((*Before).Type.find(Att.TokenNewLine + Att.TokenDedent) == 0)
      IdentCounter =   IdentCounter
                     - ( ((*Before).Type.size()-String_imp(Att.TokenNewLine).size())
                        / String_imp(Att.TokenDedent).size()
                       );
     --Before ;
    }
    Result.Type  = Result.Type + Att.TokenNewLine;
    while(IdentCounter > 0)
    {
     Result.Type  = Result.Type + Att.TokenDedent;
     IdentCounter--;
    }
    if(Result.Type == "")
    {
     Result.Type = Att.TokenNewLine;
     if(((Att.IndentionContainer).size()) != 0)
     {
      Result.Content = ((Att.IndentionContainer).back()).Content;
      Result.Size    = ((Att.IndentionContainer).back()).Size;
     }
    }
// @MRTZ_endBlock
   }
// @MRTZ_endBlock
  }
// @MRTZ_endBlock
 }
 else
 {
// @MRTZ_exclude non_typed_result
// @MRTZ_beginBlock
  Result.Type = "";
  if(((Att.IndentionContainer).size()) != 0)
  {
   Result.Content = ((Att.IndentionContainer).back()).Content;
   Result.Size    = ((Att.IndentionContainer).back()).Size;
  }
  if(*(Result.Start-1) == '\\') // "no-new-line" found
   (*(Result.Start-1)) = ' '; // clear backspace to prevent errors
// @MRTZ_endBlock
 }

 if(Result.Type != "")
  (Att.IndentionContainer).push_back(Result);
}




#ifndef DOXYGEN
//};};};
#endif //DOXYGEN
