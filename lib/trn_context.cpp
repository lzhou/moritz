
/*!

 @file
 @brief    definition of an context parser-process defined by the user

 This file contains the definition of a user parser-process to analyse the context-areas.


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
    02.06.2012     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    02.06.2012...  @I Eckard Klotz
 @I Changes are documented in the comment of the changed element
 @TabEnd

*/
#include "trn_context.h"

//#include "TiXml_ao.h"

//#include "TiPa_Filter.h"


#ifndef DOXYGEN
//namespace CL_PROCESS {
//namespace CL_TRANSFORM {
//namespace CL_TRN_CONTEXT {
#endif //DOXYGEN


/* @MRTZ_describe Prcs_Trn_Context

*/
Prcs_Trn_Context::Prcs_Trn_Context(map<String_imp, _s_ContextType>& contextType,
                                   int                              positionOutput,
                                   bool                             showTextToParse,
                                   bool                             parseTolerant,
                                   int                              startLine,
                                   int                              startColumn)
{
 TextMakeup.StartLine    = startLine;
 TextMakeup.StartColumn  = startColumn;
 Att.PositionOutput      = positionOutput;
 Att.ShowTextToParse     = showTextToParse;
 Att.ParseTolerant       = parseTolerant;
 Att.ContextType         = contextType;

//#if defined(DEBUG_OUTPUT)
 map<String_imp, Prcs_Trn_Context::_s_ContextType>::iterator Context;
 list<_s_Sequence>::iterator                                 Sequence;

 Context = Att.ContextType.begin();
 while(Context != Att.ContextType.end())
 {
 cout << endl;
  cout << "Context     : " << Context->first << endl;
  if((Context->second).IsDefault == 1)
   cout << "IsDefault   : Yes"  << endl;
  else
   cout << "IsDefault   : No"   << endl;
  cout << "Replacement : " << (Context->second).Replacement << endl<< endl;

  Sequence = (Context->second).Sequence.begin();
  while(Sequence != (Context->second).Sequence.end())
  {
   cout << "  Sequence   : " << Sequence->Name << endl;
   cout << "  StartToken : " << Sequence->StartToken << endl;
   cout << "  EndToken   : " << Sequence->EndToken << endl << endl;
   ++ Sequence;
  }
  ++ Context;
 }

//#endif //DEBUG_OUTPUT


}


/* @MRTZ_describe ~Prcs_Trn_Context

*/
Prcs_Trn_Context::~Prcs_Trn_Context()
{
}





/* @MRTZ_describe analyse

*/
TiPa_Concrete::DataFellow* Prcs_Trn_Context::analyse(String_imp*     text,
                                                     TiPa_DataModel* model/*,
                                                     String_imp                   rule*/)
{
 TiPa_Concrete::DataFellow*  ReturnValue = nullptr;

// (*text) = (*text) + '\n';
// // a missing line-change on the end of the file may result a wrong INDENT

 if(Att.ShowTextToParse == true)
  printf("\n\nText to parse:\n%s\n",text->c_str());

 ContextModel.init();

 Grammar_Spirit185->pre_parse(text->c_str(),text->c_str()+text->size());
                                            // parse for line-changes to know line and column numbers
 Grammar_Spirit185->scan(text->c_str(),text->c_str()+text->size(),"pass");
                                            // scan for text-positions to manipulate temporarily
 TiPa_Concrete::DataFellow* GrammarTree = Grammar_Spirit185->scanData("pass");
                                            // scan result

 if(GrammarTree != nullptr)
 {
  ResultFilter.contextModel_set(model);
  GrammarTree->welcome(ResultFilter(Spirit185_Filter::KeepUndefined, model->focus_Fellow()), IterateDownwards);
                                           // reduce to level of interest
  postAnalysis(model, text->c_str());
  ReturnValue = model->focus_Fellow();
  TiPa_Data* ReturnData = ReturnValue->data_get();
//             ReturnData->userName_set((char*) ReturnData->secondaryData_add("UserName", "Content"));
             ReturnData->userName_set("Content");
             ReturnData->lineSet(1);
             ReturnData->columnSet(1);

  LOG_OUTPUT(LOG_ON,"...................... Grammar Tree created ...................");
 }
 else
 {
  LOG_OUTPUT(LOG_ON,"!!!!!!!!!!!!!!!!!!!!No Grammar Tree created!!!!!!!!!!!!!!!!!!!!");
 }

 Grammar_Spirit185->TDA_GrmConcrete::init();

 return(ReturnValue);
}


/* @MRTZ_describe postAnalysis

*/
 void Prcs_Trn_Context::postAnalysis(TiPa_DataModel* result, const char* text)
 {
   TiPa_Concrete::DataAssociation* Node   = result->focus_Fellow()->contractorFirst_get();
                                            // first child-node of parsing-result

   Att.Token.clear();                       // prepare container for context information

   while(  (Node   != nullptr)
        )                                   // parsing-result and document are OK
   {
    _s_Token        Token;                  // a single context switch
    TiPa_Data* Data = Node->data_get();      // a single parsing-data

    Token.Content = string(Data->Begin, Data->End);
                                            // context token
    Token.Index  = Data->Begin - text;
                                            // position of context token
    Data->secondaryData_add("index",  (int)Token.Index);
                                            // store in xml-node

    Token.Length = Data->End - Data->Begin; // size of context-token
    Data->secondaryData_add("length", (int)Token.Length);
                                            // store in xml-node

    Token.Type = Data->userName_get();      // type of token (already tag of xml-node)

    Att.Token.push_back(Token);             // store the context-switch to be used by getContext

    Node   = Node  ->fellowBehind_get(result->focus_Fellow());
                                            // next parser-result
   }

 }




/* @MRTZ_describe getContext

   @MRTZ_describe collect_sequence_definitions_wich_are_part_of_other_contexts
    create a dictionary of end-tokens to drop associated to their start-tokens
   @MRTZ_describe collect_sequence_definitions_wich_are_part_of_this_context
    create a dictionary of end-tokens to use associated to their start-tokens
   @MRTZ_describe process_text_outside_of_token-sequences
    copy all characters if they are common-parts of the context
    otherwise only white-spaces
   @MRTZ_describe process_text_inside_of_token-sequences
    copy all characters if the sequence-tokens are used in the current context
    otherwise only white-spaces

   @MRTZ_describe process_text_after_last_token-sequences
    copy all characters if they are common-parts of the context
    otherwise only white-spaces

*/
String_imp Prcs_Trn_Context::getContext(String_imp type, String_imp* text)
{
 String_imp                  ReturnValue = "";
 _s_ContextType              Context;
 list<_s_Sequence>::iterator Sequence;

 map<String_imp, _s_ContextType>::iterator Type;
 map<String_imp, String_imp> TokenToUse;
 map<String_imp, String_imp> TokenToDrop;

 list<_s_Token>::iterator    Token;
// size_t                      Index       = 0;
// String_imp                  EndType     = "";


 if(Att.ContextType.find(type) != Att.ContextType.end())
 {
// @MRTZ_exclude collect_sequence_definitions_wich_are_part_of_other_contexts
// @MRTZ_beginBlock
  Type = Att.ContextType.begin();
  while(Type != Att.ContextType.end())
  {
   if((Type->first) != type)
   {
    Sequence = Type->second.Sequence.begin();
    while(Sequence != Type->second.Sequence.end())
    {
#if defined(DEBUG_OUTPUT)
      cout << "Drop : " << Sequence->StartToken << " "<< Sequence->EndToken << endl;
#endif //DEBUG_OUTPUT
     TokenToDrop[Sequence->StartToken] = Sequence->EndToken;
     ++ Sequence;
    }
   }
   ++Type;
  }
// @MRTZ_endBlock


// @MRTZ_exclude collect_sequence_definitions_wich_are_part_of_this_context
// @MRTZ_beginBlock
  Context  = Att.ContextType[type];
  Sequence = Context.Sequence.begin();
  while(Sequence != Context.Sequence.end())
  {
#if defined(DEBUG_OUTPUT)
      cout << "Use  : " << Sequence->StartToken << " "<< Sequence->EndToken << endl;
#endif //DEBUG_OUTPUT
   TokenToUse[Sequence->StartToken] = Sequence->EndToken;
   ++ Sequence;
  }
// @MRTZ_endBlock



  ReturnValue.reserve(text->size());
  ReturnValue.insert(0,text->size(),' ');
  Token = Att.Token.begin();
  size_t Index = 0;
  while(Token != Att.Token.end())
  {
// @MRTZ_exclude process_text_outside_of_token-sequences
   if(Token->Index > Index)
   {
    while(  (Index <  text->size())
          &&(Index <  Token->Index)
         )
    {
     if(  (Context.IsDefault == true )
        ||(text->at(Index)   == ' '  )
        ||(text->at(Index)   == '\n' )
        ||(text->at(Index)   == '\r' )
        ||(text->at(Index)   == '\t' )
        ||(text->at(Index)   == '\v' )
       )//context contains the normal characters also
        //or white space for example line-brakes and tabs
     {
      ReturnValue[Index] = text->at(Index);
     }
     else
     {
      ReturnValue[Index] = Context.Replacement;
     }
     ++Index;
    }
   }
// @MRTZ_exclude process_text_inside_of_token-sequences
// @MRTZ_ifElseChain
   if     (TokenToUse.find(Token->Type)  != TokenToUse.end())
   {
    Index = Token->Index;
    String_imp EndType = TokenToUse[Token->Type];
    if(Token != Att.Token.end())
     ++ Token;
    while((Token != Att.Token.end())&&(Token->Type != EndType))
    {
     ++ Token;
    }
    while(  (Index <  text->size()              )
          &&(Index <= Token->Index+Token->Length-1)
         )
    {
     ReturnValue[Index] = text->at(Index);
     ++Index;
    }
   }
   else if(TokenToDrop.find(Token->Type) != TokenToDrop.end())
   {
    Index = Token->Index;
    String_imp EndType = TokenToDrop[Token->Type];
    ++ Token;
    while((Token != Att.Token.end())&&(Token->Type != EndType))
    {
     ++Token;
    }
    while(  (Index <  text->size()              )
          &&(Index <= Token->Index+Token->Length-1)
         )
    {
     if(  (text->at(Index)==' ' )
        ||(text->at(Index)=='\n')
        ||(text->at(Index)=='\r')
        ||(text->at(Index)=='\t')
        ||(text->at(Index)=='\v')
       )//white space for example line-brakes and tabs
     {
      ReturnValue[Index] = text->at(Index);
     }
     else
     {
      ReturnValue[Index] = Context.Replacement;
     }
     ++Index;
    }
   }
   else
   {
   }
   if(Token != Att.Token.end())
    ++Token;
  }

// @MRTZ_exclude process_text_after_last_token-sequences
  while(  (Index <  text->size())
//        &&(Index <  Token->Index)
       )
  {
   if(  (Context.IsDefault == true )
      ||(text->at(Index)   == ' '  )
      ||(text->at(Index)   == '\n' )
      ||(text->at(Index)   == '\r' )
      ||(text->at(Index)   == '\t' )
      ||(text->at(Index)   == '\v' )
     )//context contains the normal characters also
      //or white space for example line-brakes and tabs
   {
    ReturnValue[Index] = text->at(Index);
   }
   else
   {
    ReturnValue[Index] = Context.Replacement;
   }
   ++Index;
  }

 }
 else
 {
  cout << "undefined context-type [" <<  type << "] used !"
       << "please check type-names used in configuration"
       << endl;
 }

 return(ReturnValue);
}








#ifndef DOXYGEN
//};};};
#endif //DOXYGEN


