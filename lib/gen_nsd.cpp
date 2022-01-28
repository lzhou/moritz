/*!

 @file
 @brief  definition of a script-generator

 This file contains the definition of a script generator with an own
 snippet-parser.

 Copyright (C) 2009-2020 by Eckard Klotz.

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
    06.12.2009     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    06.12.2009...  @I Eckard Klotz
 @I Changes are documented in the comment of the changed element
 @TabEnd

*/
#include <dirent.h>
#include "StringC_help.h"

#include "gen_nsd.h"
#include "snippet.h"


#include "Spirit185_Store.h"


#ifndef DOXYGEN
//namespace CL_PROCESS {
//namespace CL_TRANSFORM {
//namespace CL_GEN_NSD {
#endif //DOXYGEN


/* @MRTZ_describe Generator_Nsd

*/
Generator_Nsd::Generator_Nsd()
{
 Att.JumpIn = stringToList("Content");
}

/* @MRTZ_describe Generator_Nsd

*/
Generator_Nsd::Generator_Nsd(const String_imp& jumpIn)
{

 if(jumpIn != "")
  Att.JumpIn = stringToList(jumpIn);
 else
  Att.JumpIn = stringToList("Content");

}

/* @MRTZ_describe ~Generator_Nsd

*/
Generator_Nsd::~Generator_Nsd()
{
 map<String_imp, SnippetExecution*>::iterator  Snippet = Att.Snippet.begin();
 while(Snippet != Att.Snippet.end())
 {
  delete(Snippet->second);
  ++ Snippet;
 }
}


/* @MRTZ_describe analyse

   @MRTZ_describe local_declarations

   @MRTZ_describe evaluate_hits
*/
TiPa_Concrete::DataFellow* Generator_Nsd::analyse(String_imp*       text,
                                                  TiPa_DataModel*   model,
                                                  const String_imp& rule)
{

// @MRTZ_exclude local_declarations
// @MRTZ_beginBlock
 TiPa_Concrete::DataFellow* ReturnValue = nullptr;

// String_imp      FormatNumber     = "";
// String_imp      Text             = "";

 set<unsigned long>::iterator Command_ID;

 set<String_imp> Command_set;
 CREATE_COMMAND_ID_SET_mk(Command_set)

 list<_s_RawSequence_TP>  SnipetInfo;

 SnippetExecution* NewSnipet = NULL;

 static bool            Defined     = false;
 static set<String_imp> FirstCheck;
 static set<String_imp> PreCommand;
 static set<String_imp> RawText;
 static set<String_imp> ChildCommand;
 static set<String_imp> IfEmpty;
 static set<String_imp> PostCommand;
 static set<String_imp> LastCheck;

 if(Defined == false)
 {
  CREATE_FIRSTCHECK_SET_mk(FirstCheck);
  CREATE_PRECOMMAND_SET_mk(PreCommand);
  CREATE_RAWTEXT_SET_mk(RawText);
  CREATE_CHILDCOMMAND_SET_mk(ChildCommand);
  CREATE_IFEMPTY_SET_mk(IfEmpty);
  CREATE_POSTCOMMAND_SET_mk(PostCommand);
  CREATE_LASTCHECK_SET_mk(LastCheck);
  Defined    = true;
 }
// @MRTZ_endBlock



 Grammar_Spirit185->scan(text->c_str(),text->c_str()+text->size(),"precut");
                                            // scan for text-positions to replace by spaces since they are comments
 TiPa_Concrete::DataFellow* GrammarTree = Grammar_Spirit185->scanData("precut");
                                            // scan result
 if(GrammarTree != nullptr)
 {
  ResultFilter.contextModel_set(model);
                                              // filtered parsing-result
  GrammarTree->welcome(ResultFilter(Spirit185_Filter::KeepUndefined, model->focus_Fellow(),Spirit185_Filter::CloneData),IterateDownwards);

  TiPa_Concrete::DataAssociation* Comment = model->focus_Fellow()->contractorFirst_get();       // first text-Part to replace
  while(Comment != NULL)                                                             // iterate over all text-parts to replace
  {
   char* Character = (char*) (Comment->data_get()->Begin);                           // position of character to store
   while(Character != Comment->data_get()->End)                                      // iterate over found text-part
   {
    (*Character) = ' ';                                                              // replace
    ++Character;                                                                     // next character to save and replace
   }
   Comment = Comment->fellowBehind_get(model->focus_Fellow());                                // next text-part to replace
  }
 }

 Grammar_Spirit185->scan(text->c_str(),text->c_str()+text->size(),rule.c_str());

 TiPa_Concrete::DataFellow* MainTree = Grammar_Spirit185->scanData(rule.c_str());
                                                           // get text-positions to manipulate permanently

// @MRTZ_exclude evaluate_hits
// @MRTZ_beginBlock
 TiPa_Concrete::DataFellow  ReducedMain;
 MainTree->welcome(ResultFilter(Spirit185_Filter::KeepUndefined, &ReducedMain),IterateDownwards);
                                                                      // scan for text-positions to manipulate permanently

 TiPa_Data* ReducedData = ReducedMain.data_get();
 if(ReducedData == nullptr)
 {
  ReducedData = model->data_create();
  ReducedMain.data_set(ReducedData);
 }
 ReducedData->userName_set((char*) ReducedData->secondaryData_add("UserName", "Content"));
 ReducedData->lineSet(1);
 ReducedData->columnSet(1);



 Spirit185_Store  Store;
 char* ParsedGrammar = nullptr ;
 ReducedMain.welcome(Store(Spirit185_Store::Content2XML, &ParsedGrammar), IterateDownwards);

 ofstream  File("RawText.xml",ios_base::binary|ios_base::out);
 if(File.good()) // file successfully opened
 {
  File << ParsedGrammar;
  File.close();
 }

  _eval_SearchRule(&ReducedMain);                                             // evaluate text-parts to manipulate
// @MRTZ_endBlock

 model->focus_Set("Snippet");
 TiPa_Concrete::DataFellow* Root = model->focus_Fellow();

 map<String_imp, list<_s_SnippetPart_TP> >::iterator FirstSnippet = Att.RawSnippet.begin();
 map<String_imp, list<_s_SnippetPart_TP> >::iterator EndSnippet   = Att.RawSnippet.end();
 if(FirstSnippet != EndSnippet)
  for(map<String_imp, list<_s_SnippetPart_TP> >::iterator CurrentSnippet = FirstSnippet;
                                                          CurrentSnippet != EndSnippet;
                                                       ++ CurrentSnippet
     )
  {
   _replaceMacros(CurrentSnippet->first,&(CurrentSnippet->second));
   SnipetInfo = _preResolve(&(CurrentSnippet->second), & Command_set);

   TiPa_Data* SnippetData = model->data_create();
   SnippetData->userName_set((char*) SnippetData->secondaryData_add("UserName", CurrentSnippet->first.c_str()));
   TiPa_Concrete::DataFellow* Snippet = model->fellow_create(SnippetData);
   Root->contractorLast_add(Snippet);

#if defined(DEBUG_OUTPUT)
   cout << endl << "Snipet : " << CurrentSnippet->first << endl;
#endif //DEBUG_OUTPUT
   list<_s_RawSequence_TP>::iterator    Sequence_Crnt;
   list<_s_RawCmnd_TP>::iterator        Command_Crnt;
   list<_s_RawParameter_TP>::iterator   Parameter_Crnt;
   int SequenceIndex   = 0;
   String_imp ParameterText = "";
   String_imp Indent   = "";

   TiPa_Concrete::DataFellow* Sequence         = nullptr;
   TiPa_Concrete::DataFellow* SlotRawText      = nullptr;
   bool                       RawTextOccured   = false;

   Sequence_Crnt = SnipetInfo.begin();
   while(Sequence_Crnt != SnipetInfo.end())
   {

    TiPa_Concrete::DataFellow* SlotFirstCheck   = nullptr;
    TiPa_Concrete::DataFellow* SlotPreCommand   = nullptr;
    TiPa_Concrete::DataFellow* SlotChildCommand = nullptr;
    TiPa_Concrete::DataFellow* SlotIfEmpty      = nullptr;
    TiPa_Concrete::DataFellow* SlotPostCommand  = nullptr;
    TiPa_Concrete::DataFellow* SlotLastCheck    = nullptr;

    if(Sequence_Crnt->Type != SEQUENCETYPE_RAWTEXT)
    {
     TiPa_Data* SequenceData = model->data_create();
     SequenceData->userName_set((char*) SequenceData->secondaryData_add("UserName", ("Sequence_" + numberToString(SequenceIndex)).c_str()));
     Sequence = model->fellow_create(SequenceData);
     Snippet->contractorLast_add(Sequence);
     RawTextOccured   = false;
     SlotRawText = nullptr;
     ++ SequenceIndex;
    }
    else if(  (Sequence_Crnt->Type == SEQUENCETYPE_RAWTEXT)
            &&(RawTextOccured      == false)
           )
    {
     TiPa_Data* SequenceData = model->data_create();
     SequenceData->userName_set((char*) SequenceData->secondaryData_add("UserName", ("Sequence_" + numberToString(SequenceIndex)).c_str()));
     Sequence = model->fellow_create(SequenceData);
     Snippet->contractorLast_add(Sequence);
     RawTextOccured   = true;
     ++ SequenceIndex;
    }
    else
    {
    }


#if defined(DEBUG_OUTPUT)
    cout << " Sequence : " << SequenceIndex << endl;
#endif //DEBUG_OUTPUT
    Command_Crnt = (Sequence_Crnt->Content).begin();
    while(Command_Crnt != (Sequence_Crnt->Content).end())
    {
     TiPa_Data* ProcedureData = model->data_create();
     ProcedureData->userName_set((char*) ProcedureData->secondaryData_add("UserName", Command_Crnt->Name.c_str()));
     TiPa_Concrete::DataFellow* Procedure = model->fellow_create(ProcedureData);

     if     (FirstCheck.find(Command_Crnt->Name)!= FirstCheck.end())
     {
#if defined(DEBUG_OUTPUT)
      cout << "  procedure group : FirstCheck"  << endl;
#endif //DEBUG_OUTPUT
      if(SlotFirstCheck == NULL)
      {
       TiPa_Data* SlotFirstCheckData = model->data_create();
       SlotFirstCheckData->userName_set((char*) SlotFirstCheckData->secondaryData_add("UserName", "FirstCheck"));
       SlotFirstCheck = model->fellow_create(SlotFirstCheckData);
       Sequence->contractorLast_add(SlotFirstCheck);
      }
      SlotFirstCheck->contractorLast_add(Procedure);
     }
     else if(PreCommand.find(Command_Crnt->Name)!= PreCommand.end())
     {
#if defined(DEBUG_OUTPUT)
      cout << "  procedure group : PreCommand"  << endl;
#endif //DEBUG_OUTPUT
      if(SlotPreCommand == NULL)
      {
       TiPa_Data* SlotPreCommandData = model->data_create();
       SlotPreCommandData->userName_set((char*) SlotPreCommandData->secondaryData_add("UserName", "PreCommand"));
       SlotPreCommand = model->fellow_create(SlotPreCommandData);
       Sequence->contractorLast_add(SlotPreCommand);
      }
      SlotPreCommand->contractorLast_add(Procedure);
     }
     else if(RawText.find(Command_Crnt->Name)!= RawText.end())
     {
#if defined(DEBUG_OUTPUT)
      cout << "  procedure group : RawText"  << endl;
#endif //DEBUG_OUTPUT
      if(SlotRawText == nullptr)
      {
       TiPa_Data* SlotRawTextData = model->data_create();
       SlotRawTextData->userName_set((char*) SlotRawTextData->secondaryData_add("UserName", "RawText"));
       SlotRawText = model->fellow_create(SlotRawTextData);

       if (Sequence!= nullptr)
        Sequence->contractorLast_add(SlotRawText);
//       else
//        cout << __FILE__ << "|Generator_Nsd::analyse: no sequence for raw-text !|" << __LINE__ << endl;

      }
     }
     else if(ChildCommand.find(Command_Crnt->Name)!= ChildCommand.end())
     {
#if defined(DEBUG_OUTPUT)
      cout << "  procedure group : ChildCommand"  << endl;
#endif //DEBUG_OUTPUT
      if(SlotChildCommand == nullptr)
      {
       TiPa_Data* SlotChildCommandData = model->data_create();
       SlotChildCommandData->userName_set((char*) SlotChildCommandData->secondaryData_add("UserName", "ChildCommand"));
       SlotChildCommand = model->fellow_create(SlotChildCommandData);
       Sequence->contractorLast_add(SlotChildCommand);
      }
      SlotChildCommand->contractorLast_add(Procedure);
     }
     else if(IfEmpty.find(Command_Crnt->Name)  != IfEmpty.end())
     {
#if defined(DEBUG_OUTPUT)
      cout << "  procedure group : IfEmpty"  << endl;
#endif //DEBUG_OUTPUT
      if(SlotIfEmpty == NULL)
      {
       TiPa_Data* SlotIfEmptyData = model->data_create();
       SlotIfEmptyData->userName_set((char*) SlotIfEmptyData->secondaryData_add("UserName", "ChildCommand"));
       SlotIfEmpty = model->fellow_create(SlotIfEmptyData);
       Sequence->contractorLast_add(SlotIfEmpty);
      }
      SlotIfEmpty->contractorLast_add(Procedure);
     }
     else if(PostCommand.find(Command_Crnt->Name)!= PostCommand.end())
     {
#if defined(DEBUG_OUTPUT)
      cout << "  procedure group : PostCommand"  << endl;
#endif //DEBUG_OUTPUT
      if(SlotPostCommand == NULL)
      {
       TiPa_Data* SlotPostCommandData = model->data_create();
       SlotPostCommandData->userName_set((char*) SlotPostCommandData->secondaryData_add("UserName", "PostCommand"));
       SlotPostCommand = model->fellow_create(SlotPostCommandData);
       Sequence->contractorLast_add(SlotPostCommand);
      }
      SlotPostCommand->contractorLast_add(Procedure);
     }
     else if(LastCheck.find(Command_Crnt->Name)!= LastCheck.end())
     {
#if defined(DEBUG_OUTPUT)
      cout << "  procedure group : LastCheck"  << endl;
#endif //DEBUG_OUTPUT
      if(SlotLastCheck == NULL)
      {
       TiPa_Data* SlotLastCheckData = model->data_create();
       SlotLastCheckData->userName_set((char*) SlotLastCheckData->secondaryData_add("UserName", "LastCheck"));
       SlotLastCheck = model->fellow_create(SlotLastCheckData);
       Sequence->contractorLast_add(SlotLastCheck);
      }
      SlotLastCheck->contractorLast_add(Procedure);
     }
     else if((Command_Crnt->Name).find("macro_begin") == 0)
     {
#if defined(DEBUG_OUTPUT)
      cout << "  procedure group : Macro Begin"  << endl;
#endif //DEBUG_OUTPUT
      TiPa_Concrete::DataFellow* MacroParent    =  Snippet;

      Parameter_Crnt =  Command_Crnt->Parameter.begin();

      /*TiPa_Data* */ SnippetData = model->data_create();
      SnippetData->userName_set((char*) SnippetData->secondaryData_add("UserName", "Macro"));
      SnippetData->secondaryData_add("value", Parameter_Crnt->Text.c_str());
      Snippet = model->fellow_create(SnippetData);
      MacroParent->contractorLast_add(Snippet);
     }
     else if((Command_Crnt->Name).find("macro_end") == 0)
     {
#if defined(DEBUG_OUTPUT)
      cout << "  procedure group : Macro End"  << endl;
#endif //DEBUG_OUTPUT

      Snippet = Snippet->sponsor_get()->as_AssociationFellowship();
     }
     else
     {
#if defined(DEBUG_OUTPUT)
      cout << "   unknown procedure " << Command_Crnt->Name << endl;
#endif //DEBUG_OUTPUT
     }

     if(  ((Command_Crnt->Name).find("macro_begin") != 0)
        &&((Command_Crnt->Name).find("macro_end")   != 0)
       )
     {
#if defined(DEBUG_OUTPUT)
      cout << "  Command(" << Command_Crnt->ID << ") : " << Command_Crnt->Name << endl;
#endif //DEBUG_OUTPUT
      Parameter_Crnt = Command_Crnt->Parameter.begin();
      while(Parameter_Crnt != Command_Crnt->Parameter.end())
      {

       if(Parameter_Crnt->Token == RAWTEXT)
       {
        String_imp Text = Parameter_Crnt->Text;
        while(  (Text.size()>0)
              &&(  (Text[Text.size()-1]==' ')
                 ||(Text[Text.size()-1]=='\t')
                 ||(Text[Text.size()-1]=='\n')
                 ||(Text[Text.size()-1]=='\r')
                )
             )
         Text = Text.erase(Text.size()-1);

        if(Text != "")
        {
         ProcedureData = Procedure->data_get();
         ProcedureData->userName_set((char*) ProcedureData->secondaryData_add("UserName", "text"));
         ProcedureData->Begin = ProcedureData->secondaryData_add("TextContent",Text.c_str());
         ProcedureData->End   = ProcedureData->Begin + strlen(Text.c_str());
         SlotRawText->contractorLast_add(Procedure);
        }
       }
       else
       {
        String_imp FormatNumber = "";
        TiPa_Concrete::DataFellow* Parameter  = nullptr;
        if(  (Parameter_Crnt->Token == FORMAT)
           ||(Parameter_Crnt->Token == NEWLINE)
           ||(Parameter_Crnt->Token == INDEND)
           ||(Parameter_Crnt->Token == DEDEND)
           ||(Parameter_Crnt->Token == SPACE)
           ||(Parameter_Crnt->Token == TAB)
           ||(Parameter_Crnt->Token == ASCII)
          )
        {
         Parameter    =  Procedure;
         ProcedureData = Procedure->data_get();
         ProcedureData->userName_set((char*) ProcedureData->secondaryData_add("UserName", Parameter_Crnt->Token.c_str()));
         FormatNumber = Parameter_Crnt->Text;
         FormatNumber = FormatNumber.substr(2);
         FormatNumber = FormatNumber.substr(0,FormatNumber.size()-2);

         SlotRawText->contractorLast_add(Procedure);
        }
        else
        {
         TiPa_Data* ParameterData = model->data_create();
         ParameterData->userName_set((char*) ParameterData->secondaryData_add("UserName", "Parameter"));
         Parameter = model->fellow_create(ParameterData);
         Procedure->contractorLast_add(Parameter);

         //FormatNumber = "";
        }
        if(FormatNumber != "")
        {
         TiPa_Data* ParameterData = Parameter->data_get();
         ParameterData->secondaryData_add("number", FormatNumber.c_str());
        }
        TiPa_Data* ParameterData = Parameter->data_get();
        ParameterData->secondaryData_add("value", Parameter_Crnt->Text.c_str());
       }

#if defined(DEBUG_OUTPUT)
       ParameterText = String_imp("   Parameter(") + Parameter_Crnt->Token + String_imp(") : ");
       Indent   = "";
       while(Indent.size()<ParameterText.size())
        Indent = Indent + " ";
       ParameterText = ParameterText + replacePartString(Parameter_Crnt->Text,"\n","\n"+ Indent,false);
       cout << ParameterText<< endl;
#endif //DEBUG_OUTPUT
       ++Parameter_Crnt;
      }
     }
     ++Command_Crnt;
    }
    ++Sequence_Crnt;
   }

   NewSnipet = new SnippetExecution( SnipetInfo,
                                    &(Att.Snippet),
                                    &(Att.SnippetHoliday),
                                    CurrentSnippet->first,
                                    this);

   Att.Snippet[CurrentSnippet->first] = NewSnipet;
#if defined(DEBUG_OUTPUT)
   cout << endl << "---------------------------------------"
        << endl << "Snipet : " << CurrentSnippet->first
        << endl << "---------------------------------------"
        << endl;
   NewSnipet->showSelf();
#endif //DEBUG_OUTPUT
  }

 cout << "\nevaluation of snippets finished \n";

#if defined(DEBUG_OUTPUT)
 list<_s_SnippetPart_TP>::iterator FirstPart;
 list<_s_SnippetPart_TP>::iterator CurrentPart;
 list<_s_SnippetPart_TP>::iterator EndPart;

 FirstSnippet = Att.Snippet.begin();
 EndSnippet   = Att.Snippet.end();
 if(FirstSnippet != EndSnippet)
  for(CurrentSnippet = FirstSnippet;
      CurrentSnippet != EndSnippet;
      CurrentSnippet ++)
  {
   cout << endl << endl << endl <<"|"<< CurrentSnippet->first <<"|" << endl;
#if defined(DEBUG_OUTPUT)
   FirstPart = CurrentSnippet->second.begin();
   EndPart   = CurrentSnippet->second.end();
   if(FirstPart != EndPart)
    for(CurrentPart = FirstPart;
        CurrentPart != EndPart;
        CurrentPart ++)
    {
     if(CurrentPart->Type == SNIPPET_PART)
      cout << endl << "___LinePart___";
     else
      cout << endl << "___Sequence___";
     cout << CurrentPart->Text;
    }
#endif //DEBUG_OUTPUT

  }
#endif //DEBUG_OUTPUT

 Grammar_Spirit185->TDA_GrmConcrete::init();

 ReturnValue = model->focus_Fellow();

 TiPa_Data* ReturnData = ReturnValue->data_get();
            ReturnData->userName_set((char*) ReturnData->secondaryData_add("UserName", "Content"));
            ReturnData->lineSet(1);
            ReturnData->columnSet(1);

 return(ReturnValue);
}











/* @MRTZ_describe generate

*/
void Generator_Nsd::generate(XML_Node          source,
                             const String_imp& destPath)
{
//cout<<__FILE__<<"|Generator_Nsd::generate|"<<"("<<__LINE__<<") enter"<<endl;
 list<String_imp>::iterator   StartTag;

 if(source.valid() == true)// != nullptr)
 {
  StartTag = Att.JumpIn.begin();
  while(StartTag != Att.JumpIn.end())
  {
   _search(source, destPath,(*StartTag));
   ++StartTag;
  }
 }
 else
 {
  cout << "invalid xml-node found";
 }
//cout<<__FILE__<<"|Generator_Nsd::generate|"<<"("<<__LINE__<<") leave"<<endl;
}



/* @MRTZ_describe addStackValue

*/
void Generator_Nsd::addStackValue(const String_imp& name,
                                  const String_imp& value)
{
 SnippetExecution Temp;
#if defined(DEBUG_OUTPUT)
 cout << "Stack(" << name << ") " << value << endl;
#endif //DEBUG_OUTPUT
 Temp.addStackValue(name, value);
}



/* @MRTZ_describe xmlContext_set

*/
void Generator_Nsd::xmlContext_set(XML_DataModel* xml_Context)
{
  SnippetExecution Temp;
  Temp.xmlContext_set(xml_Context);
  Att.XML_Context = xml_Context;
}




/* @MRTZ_describe snipet

*/
void Generator_Nsd::snippet(XML_Node                       source,
                            const String_imp&              startTag,
                            map<String_imp , String_imp >* replacement,
                            list<String_imp>*              diagram,
                            bool                           resetSnipets)
{
//cout<<__FILE__<<"|Generator_Nsd::snippet|"<<"("<<__LINE__<<") enter"<<endl;

 if(source.valid() == false)// == nullptr) // empty source
 {
  // define dummy node to satisfy further process
  XML_Data* Data = Att.XML_Context->data_create();
            Data->typeSet(XML_Data::NT_Element);
            Data->valueSet("NoContent");
  source = XML_Node(Att.XML_Context, Data);
 }

 if(Att.Snippet[startTag] != NULL)
 {
  Att.Snippet[startTag]->generate(source,
//                                  startTag,
                                  replacement,
                                  diagram,
                                  resetSnipets);
 }
 else
 {
  String_imp Ansisters = source.valueGet();
  XML_Node   Ansister  = source.preGet();
  if(Ansister.valid() == true)
  {
   while(Ansister.typeGet() == XML_Data::NT_Element)
   {
#if defined(DEBUG_OUTPUT)
     cout << "Ansister: " << Ansister->ValueStr() <<endl;
#endif
    Ansisters = string(Ansister.valueGet()) + "/" + Ansisters;
    Ansister = Ansister.preGet();
   }
  }
  else
  {
   Ansisters =  "no Ansister";
  }
  cout << "!!!!!!!!!!!!!!!!!!!!1 no valid snipet defined for tag: " << startTag ;
  cout << " called in " << Ansister.valueGet()<< " from: " << Ansisters  << endl;
  cout << "--> if you used the command \"useForSnipet\" before make sure that you\n"
       << "    don\'t use the parameter\"__SELF__\" in the used replacement-snipet,\n"
       << "    in this case try the \"useForSnipetDownwards\" or try to use \n"
       << "    \"useForSnipet\" for \"" << startTag << "\" in the replacement-snipet also."
       << endl;
 }
//cout<<__FILE__<<"|Generator_Nsd::snippet|"<<"("<<__LINE__<<") leave"<<endl;
}



/* @MRTZ_describe format

*/
String_imp Generator_Nsd::format(String_imp* rawText)
{
 String_imp ReturnValue = "";

 String_imp          LineChange = newLine();
 list<_s_Format_TP>  Lines      = _split(rawText);
// ReturnValue = (*rawText);

 ReturnValue = replacePartString(ReturnValue,"\n","");
 ReturnValue = replacePartString(ReturnValue,"\r","");
 while(ReturnValue[0] ==' ') // until a leading space is existing
  ReturnValue.erase(0,1);    // delete first leading space

#if defined(DEBUG_OUTPUT)
     cout << "format : " << *rawText << endl;
#endif //DEBUG_OUTPUT

 size_t     LineLength = 0;
 String_imp Indend     = "";
 list<_s_Format_TP>::iterator OriginalLine = Lines.begin();
 while(OriginalLine != Lines.end())
 {

#if defined(DEBUG_OUTPUT)
     cout << "|" << OriginalLine->Part << endl;
#endif //DEBUG_OUTPUT

  if     ((OriginalLine->Name) == NEWLINE)
  {

#if defined(DEBUG_OUTPUT)
       cout << "newLine found" << "  Indend: |" << Indend << "|" << endl;
#endif //DEBUG_OUTPUT
   if(  (OriginalLine->Part     != "")
      ||((OriginalLine->Number) >  0 )
     )
   {
    rawText->append(LineChange + Indend);
    rawText->append(OriginalLine->Number,' ');
   }
   LineLength = Indend.size() + OriginalLine->Number + (OriginalLine->Part).size();
  }
  else if((OriginalLine->Name) == INDEND)
  {
   Indend.append(OriginalLine->Number,' ');
#if defined(DEBUG_OUTPUT)
       cout << "indend found" << "  Indend: |" << Indend << "|" << endl;
#endif //DEBUG_OUTPUT
   if(OriginalLine->Part != "")
   {
    rawText->append(LineChange + Indend);
   }
   LineLength = Indend.size() + (OriginalLine->Part).size();
  }
  else if((OriginalLine->Name) == DEDEND)
  {
   Indend.erase(0,OriginalLine->Number);
#if defined(DEBUG_OUTPUT)
       cout << "dedend found" << "  Indend: |" << Indend << "|" << endl;
#endif //DEBUG_OUTPUT
   if(OriginalLine->Part != "")
   {
    rawText->append(LineChange + Indend);
   }
    LineLength = Indend.size() + (OriginalLine->Part).size();
  }
  else if((OriginalLine->Name) == SPACE)
  {
#if defined(DEBUG_OUTPUT)
       cout << "space found" << "  Indend: |" << Indend << "|" << endl;
#endif //DEBUG_OUTPUT
   rawText->append(OriginalLine->Number,' ');
   LineLength = LineLength + OriginalLine->Number + (OriginalLine->Part).size();
  }
  else if((OriginalLine->Name) == TAB)
  {

#if defined(DEBUG_OUTPUT)
       cout << "tab found" << "  Indend: |" << Indend << "|" << endl;
#endif //DEBUG_OUTPUT

   size_t TabValue = LineLength % OriginalLine->Number;
          TabValue = OriginalLine->Number - TabValue;
   rawText->append(TabValue,' ');
   LineLength = LineLength + TabValue + (OriginalLine->Part).size();
  }
  else if((OriginalLine->Name) == ASCII)
  {
   char Character = OriginalLine->Number;
#if defined(DEBUG_OUTPUT)
       cout << "ascii found" << "  Number: |" << OriginalLine->Number << "|" << endl;
#endif //DEBUG_OUTPUT
   rawText->append(1,Character);
   LineLength = LineLength + 1 + (OriginalLine->Part).size();
  }
  else
  {
   cout << "invalid format found" << endl;
  }
  rawText->append(OriginalLine->Part);


  ++OriginalLine;
 }

 ReturnValue = (*rawText);


 return(ReturnValue);
}







/* @MRTZ_describe _eval_SearchRule

   @MRTZ_describe local_declarations

   @MRTZ_describe react_to_sequence_part

   @MRTZ_describe react_to_snipet_name

   @MRTZ_describe react_to_linePart

   @MRTZ_describe react_to_sequence

   @MRTZ_describe react_to_useAlsoFor

   @MRTZ_describe react_to_pass

*/
void Generator_Nsd::_eval_SearchRule(TiPa_Concrete::DataAssociation* hit)
{
#if defined(DEBUG_OUTPUT)
// static int Counter = 0;
#endif //DEBUG_OUTPUT
// @MRTZ_exclude local_declarations
// @MRTZ_beginBlock
 static list<_s_SnippetPart_TP> SnippetPart;
 static String_imp           SnippetName = "";
 static list<String_imp>     CloneList;
// @MRTZ_endBlock


#if defined(DEBUG_OUTPUT)
// Counter++;
#endif //DEBUG_OUTPUT

  TiPa_Concrete::DataAssociation* Child = hit->contractorFirst_get();
                                         // first text-part to analyse
  while(Child != NULL)                   // iterate over all text-parts to analyse

  {
#if defined(DEBUG_OUTPUT)
  printf("Sub__%d_  _-%s-_\n",(Child->value.id()).to_long(),String_imp(Child->value.begin(),Child->value.end()).c_str());
   cout << String_imp( Child->value.begin(), Child->value.end() ) << endl;
#endif //DEBUG_OUTPUT
   TiPa_Data* Data = Child->data_get();  // details to analyse

   if(Data->ParserClass == TiPa_Abstract::TDA_TiPa_Rule)
   {
    string RuleName = Data->Parser->as_TiPa_Rule()->getName();

//@MRTZ_exclude react_to_sequence_part
//@MRTZ_ifElseChain
    if(RuleName == SNIPET_NAME)
    {
//@MRTZ_exclude react_to_snipet_name
//@MRTZ_beginBlock
     SnippetName = String_imp(Data->Begin, Data->End-1);
     TiPa_Concrete::DataAssociation* NamePart = Child->contractorFirst_get();
     while(  (NamePart                          != nullptr)
           &&(NamePart->data_get()              != nullptr)
           &&(NamePart->data_get()->ParserClass == TiPa_Abstract::TDA_TiPa_Rule)
          )
     {
      TiPa_Data* NamePartData = NamePart->data_get();  // details to analyse
      string Name = NamePartData->Parser->as_TiPa_Rule()->getName();

      if(Name == NAME)
      {
       SnippetName = String_imp(NamePartData->Begin, NamePartData->End);
#if defined(DEBUG_OUTPUT)
       cout << "SnippetName : " << SnippetName << endl;
#endif //DEBUG_OUTPUT
      }
      else
      {
#if defined(DEBUG_OUTPUT)
       cout << Grm.ID_Dictionary[(*NamePart)->value.id()] << "(" << ((*NamePart)->value.id().to_long()) <<") : ";
       cout << String_imp( (*NamePart)->value.begin(), (*NamePart)->value.end()) << endl;
#endif //DEBUG_OUTPUT
      }
      NamePart = NamePart->fellowBehind_get(Child); // next text-part to analyse
     }
//@MRTZ_endBlock
    }
    else if(RuleName == LINEPART)
    {
//@MRTZ_exclude react_to_linePart
//@MRTZ_beginBlock
      _s_SnippetPart_TP SnpPrt;
      SnpPrt.Type = SNIPPET_PART;
      SnpPrt.Text = String_imp(Data->Begin,Data->End);

//      char LineFeed[]     = {0x0A, 0x00};
//      char CarageReturn[] = {0x0D, 0x00};
//      if(SnpPrt.Text.compare(0,0,LineFeed) == 0)//find(0x0A) == 0)
      if(SnpPrt.Text[0] == 0x0A)
       SnpPrt.Text.erase(0,1);
//      if(SnpPrt.Text.compare(0,0,CarageReturn) == 0)//find(0x0D) == 0)
      if(SnpPrt.Text[0] == 0x0D)
       SnpPrt.Text.erase(0,1);
//      if(SnpPrt.Text.compare(0,0,LineFeed) == 0)//find(0x0A) == 0)
      if(SnpPrt.Text[0] == 0x0A)
       SnpPrt.Text.erase(0,1);
      SnippetPart.push_back(SnpPrt);
//@MRTZ_endBlock
    }
    else if(RuleName == RAW_SEQUENCE)
    {
//@MRTZ_exclude react_to_sequence
//@MRTZ_beginBlock
      _s_SnippetPart_TP SnpPrt;
      SnpPrt.Type = SNIPPET_SEQUENCE;
      SnpPrt.Text = String_imp(Data->Begin,Data->End);

//      char LineFeed[]     = {0x0A, 0x00};
//      char CarageReturn[] = {0x0D, 0x00};
//      if(SnpPrt.Text.compare(0,0,LineFeed) == 0)//find(0x0A) == 0)
      if(SnpPrt.Text[0] == 0x0A)
       SnpPrt.Text.erase(0,1);
//      if(SnpPrt.Text.compare(0,0,CarageReturn) == 0)//find(0x0D) == 0)
      if(SnpPrt.Text[0] == 0x0D)
       SnpPrt.Text.erase(0,1);
//      if(SnpPrt.Text.compare(0,0,LineFeed) == 0)//find(0x0A) == 0)
      if(SnpPrt.Text[0] == 0x0A)
       SnpPrt.Text.erase(0,1);
      SnippetPart.push_back(SnpPrt);
//@MRTZ_endBlock
    }
    else if(RuleName == USEALSOFOR)
    {
//@MRTZ_exclude react_to_useAlsoFor
//@MRTZ_beginBlock

     TiPa_Concrete::DataAssociation* Clone = Child->contractorFirst_get();

     while(Clone != nullptr)
     {
      TiPa_Data* CloneData = Clone->data_get();  // details to analyse

      if(CloneData->ParserClass == TiPa_Abstract::TDA_TiPa_Rule)
      {
       string CloneID = CloneData->Parser->as_TiPa_Rule()->getName();
       if(CloneID == PARAMETER)
       {
        CloneList.push_back(String_imp(CloneData->Begin, CloneData->End));
       }
      }
      Clone = Clone->fellowBehind_get(Child); // next text-part to analyse
     }
//@MRTZ_endBlock
    }
    else if(  (RuleName == PASS)
            ||(RuleName == RAW_TEXT)
           )
    {
//@MRTZ_exclude react_to_pass
//@MRTZ_beginBlock
     _eval_SearchRule(Child);
     if((SnippetName != "")&&(SnippetPart.size()>0))
     {
      Att.RawSnippet[SnippetName] = SnippetPart;
#if defined(DEBUG_OUTPUT)
      cout << "SnippetName : " << SnippetName << endl;
#endif //DEBUG_OUTPUT
      SnippetName == "";
      list<String_imp>::iterator CloneName = CloneList.begin();
      while(CloneName != CloneList.end())
      {
       Att.RawSnippet[*CloneName] = SnippetPart;
#if defined(DEBUG_OUTPUT)
       cout << "*CloneName : " << (*CloneName) << endl;
#endif //DEBUG_OUTPUT
       ++CloneName;
      }
      CloneList.clear();
      SnippetPart.clear();
     }
//@MRTZ_endBlock
    }
    else
    {
    }
   }
   else
   {
    _eval_SearchRule(Child);
   }
   Child = Child->fellowBehind_get(hit); // next text-part to analyse
  }
#if defined(DEBUG_OUTPUT)
// Counter--;
#endif //DEBUG_OUTPUT

}






/* @MRTZ_describe _search

   @MRTZ_describe search_in_child_tags

*/
void Generator_Nsd::_search(XML_Node          source,
                            const String_imp& destPath,
                            const String_imp& startTag)
{
//cout<<__FILE__<<"|Generator_Nsd::_search|"<<"("<<__LINE__<<") enter"<<endl;


 if  (source.valid() == true)// != nullptr)
 {
  if(  STRINGS_ARE_EQUAL(source.valueGet(), startTag.c_str())
     &&(source.typeGet() == XML_Data::NT_Element             )
    )
  {
#if defined(DEBUG_OUTPUT)
    cout << " source" << " _ " << source->ValueStr() << " _\n";
    source->Print(stdout,1);
#endif //DEBUG_OUTPUT

   map<String_imp, String_imp> ReplacementDummi;
   list<String_imp>            Diagram;
   Att.Snippet[startTag]->generate(source,
//                                   startTag,
                                   &ReplacementDummi,
                                   &Diagram,
                                   true);
  }
  else if((source.typeGet()) != XML_Data::NT_Text)
  {
//@MRTZ_exclude search_in_child_tags
//@MRTZ_beginBlock
   XML_Node Child = source.firstGet(XML_Node::Element());
   while(Child.valid() == true)// != nullptr)
   {
   _search(Child, destPath, startTag);
#if defined(DEBUG_OUTPUT)
    cout << " next child found" << "_"<<Child->ValueStr()<<"_\n";
#endif //DEBUG_OUTPUT
    Child = Child.behindGet(XML_Node::Element());
   }
//@MRTZ_endBlock
  }
  else
  {
  }
 }
 else
 {
  cout << "invalid xml-node found";
 }
//cout<<__FILE__<<"|Generator_Nsd::_search|"<<"("<<__LINE__<<") leave"<<endl;
}








/* @MRTZ_describe _replaceMacros

   @MRTZ_describe local_declarations

   @MRTZ_describe use_Replacements

   @MRTZ_describe evaluate_hits

   @MRTZ_describe collect_data_of_snipet_to_insert

   @MRTZ_describe search_name_of_snipet_to_insert

   @MRTZ_describe set_replacements_for_next_macro

*/
void Generator_Nsd::_replaceMacros(const String_imp&        snipetName,
                                   list<_s_SnippetPart_TP>* snipet)
{
// @MRTZ_exclude local_declarations
// @MRTZ_beginBlock
 list<_s_SnippetPart_TP>::iterator FirstPart;
 list<_s_SnippetPart_TP>::iterator CurrentPart;
 list<_s_SnippetPart_TP>::iterator NextPart;
 list<_s_SnippetPart_TP>::iterator EndPart;

// String_imp                            Name    = "";
// String_imp                            OldPart = "";
// String_imp                            NewPart = "";
 set<String_imp>                       SetOfNames;
 map<String_imp, String_imp>           Replacement;
 map<String_imp, String_imp>::iterator CurrentReplacement;

 list<_s_SnippetPart_TP>               MacroSnipet;
 list<_s_SnippetPart_TP>::iterator     MacroPart;

// @MRTZ_endBlock


 SetOfNames = stringToSet(snipetName);


 FirstPart = snipet->begin();
 EndPart   = snipet->end();
 if(FirstPart != EndPart)
 {
  CurrentPart = FirstPart;
  NextPart    = FirstPart;
  while(CurrentPart != EndPart)
  {
   ++NextPart;
   if(CurrentPart->Type == SNIPPET_SEQUENCE)
   {
    Grammar_Spirit185->parse((CurrentPart->Text).c_str(),
                             (CurrentPart->Text).c_str()+(CurrentPart->Text).size(),
                             MACRO.c_str());
    TiPa_Concrete::DataFellow* MainTree = Grammar_Spirit185->treeData((CurrentPart->Text).c_str(),MACRO.c_str());

// @MRTZ_exclude evaluate_hits
// @MRTZ_beginBlock
                                                           // get text-positions to manipulate permanently
    TiPa_Concrete::DataFellow  Reduced;
    MainTree->welcome(ResultFilter(Spirit185_Filter::KeepUndefined, &Reduced),IterateDownwards);
    TiPa_Concrete::DataAssociation* Macro = &Reduced;

#if defined(DEBUG_OUTPUT)
    Spirit185_Store  Store;
    char* ParsedGrammar = nullptr ;
    Reduced.welcome(Store(Spirit185_Store::Content2XML, &ParsedGrammar), IterateDownwards);

    if(ParsedGrammar != nullptr)
     cout << ParsedGrammar << endl;
    else
     cout << "ParsedGrammar is empty" << endl;
#endif //DEBUG_OUTPUT





     Replacement.clear();
// @MRTZ_exclude collect_data_of_snipet_to_insert
// @MRTZ_beginBlock
     if (  (Macro                       != nullptr)
         &&(Macro->contractorFirst_get()!= nullptr)
        )// macro-pointer is valid and contains something really defined as macro-content
     {
      String_imp Name = "";
      TiPa_Concrete::DataAssociation* Sequence = Macro->contractorFirst_get();
      while  ( Sequence != nullptr)
      {
       TiPa_Data* SequenceData = Sequence->data_get();

       if(SequenceData->ParserClass == TiPa_Abstract::TDA_TiPa_Rule)
       {
        string RuleName = SequenceData->Parser->as_TiPa_Rule()->getName();
        string SnippetName = string(SequenceData->Begin, SequenceData->End);
        if(RuleName == NAME)
        {
// @MRTZ_exclude search_name_of_snipet_to_insert
// @MRTZ_beginBlock
         if(  Name == ""
            ||(/*  (Name != "")
               &&*/( RuleName.size()< Name.size())
              )
           )// Name is still not found or new found name-value
            // is shorter since no skip-characters where part of it
          Name = SnippetName;
// @MRTZ_endBlock
        }
        else if(RuleName == REPLACE)
        {
// @MRTZ_exclude set_replacements_for_next_macro
// @MRTZ_beginBlock
         TiPa_Concrete::DataAssociation* ReplacePart = Sequence->contractorFirst_get();

         String_imp OldPart = "";
         String_imp NewPart = "";

         while(ReplacePart != nullptr)
         {
          TiPa_Data* ReplaceData = ReplacePart->data_get();
          string ReplaceText(ReplaceData->Begin, ReplaceData->End);

          if(  (ReplaceData->ParserClass                       == TiPa_Abstract::TDA_TiPa_Rule)
             &&(ReplaceData->Parser->as_TiPa_Rule()->getName() == OLDPART                     )
           )
          {
           if(  OldPart == ""
            ||(  /*(OldPart != "")
               &&*/(ReplaceText.size() < OldPart.size())
              )
           )// OldPart is still not found or new found name-value
            // is shorter since no skip-characters where part of it
           OldPart = ReplaceText;
          }
          else if(  (ReplaceData->ParserClass                       == TiPa_Abstract::TDA_TiPa_Rule)
                  &&(ReplaceData->Parser->as_TiPa_Rule()->getName() == NEWPART                     )
           )
          {
           if(  NewPart == ""
            ||(/*  (NewPart != "")
               &&*/(ReplaceText.size() < NewPart.size())
              )
           )// NewPart is still not found or new found name-value
            // is shorter since no skip-characters where part of it
           NewPart = ReplaceText;
          }
          else
          {
          }
          ReplacePart = ReplacePart->fellowBehind_get(Sequence);
         }
         OldPart = replacePartString(OldPart,"\"","");
         NewPart = replacePartString(NewPart,"\"","");

         if(OldPart == "")
          OldPart = EMPTYSTRING;

         if(NewPart != OldPart)
         {
          Replacement[OldPart] = NewPart;
         }
         else if(Replacement.find(OldPart)!= Replacement.end())
          Replacement.erase(OldPart);
// @MRTZ_endBlock
        }

       }

       Sequence = Sequence->fellowBehind_get(Macro);
      }
     // @MRTZ_ifElseChain
      if(  (Att.RawSnippet.find(Name) != Att.RawSnippet.end())
         &&(SetOfNames.find(Name)  == SetOfNames.end())
        )
      {
#if defined(DEBUG_OUTPUT)
      cout <<"insert macro-snipet %" << Name
           <<"% in snipet : "        << replacePartString(snipetName,",",">>")
           << endl;
#endif //DEBUG_OUTPUT
       _replaceMacros(snipetName +","+Name, &(Att.RawSnippet[Name]));

      // create a copy of Att.RawSnippet[Name] and do the replacement there
      // insert this replaced copy
       MacroSnipet = Att.RawSnippet[Name];

// @MRTZ_exclude use_Replacements
       if(!(Replacement.empty()))
       {
        MacroPart   = MacroSnipet.begin();
        while(MacroPart != MacroSnipet.end())
        {
         CurrentReplacement  = Replacement.begin();
         while(CurrentReplacement != Replacement.end())
         {
          MacroPart->Text = replacePartString(MacroPart->Text,CurrentReplacement->first,CurrentReplacement->second);
         ++ CurrentReplacement;
         }
         if(MacroPart->Text == "" )//use default-value since tailored value is empty
         {
          MacroPart->Text = Replacement[EMPTYSTRING];
         }
         ++ MacroPart;
        }
       }
       CurrentPart->Text = Name;
       CurrentPart->Type = SNIPPET_MACRO;
       snipet->insert(CurrentPart, (*CurrentPart));
       snipet->insert(CurrentPart, MacroSnipet.begin(), MacroSnipet.end());
      }
      else if(Att.RawSnippet.find(Name) != Att.RawSnippet.end())
      {
       cout <<"circular macro-snipet %" << Name
            <<"% used in snipet : "     << replacePartString(snipetName,",",">>")
            << endl;
      }
      else
      {
       cout <<"unknown macro-snipet %" << Name
            <<"% used in snipet : "    << replacePartString(snipetName,",",">>")
            << endl << CurrentPart->Text << endl
            << endl;
      }

     }

// @MRTZ_endBlock

// @MRTZ_endBlock

   }
   CurrentPart = NextPart;
  }
 }
}


/* @MRTZ_describe _preResolve

   @MRTZ_describe local_declarations

*/
list<_s_RawSequence_TP>  Generator_Nsd::_preResolve(list<_s_SnippetPart_TP>* snipet,
                                                    set<String_imp>*         command_set)
{
// @MRTZ_exclude local_declarations
// @MRTZ_beginBlock

 list<_s_RawSequence_TP> ReturnValue;
 _s_RawSequence_TP       Sequence;
 _s_RawCmnd_TP           RawCommand;
 _s_RawParameter_TP      RawAtom;

 list<_s_SnippetPart_TP>::iterator FirstPart;
 list<_s_SnippetPart_TP>::iterator CurrentPart;
 list<_s_SnippetPart_TP>::iterator NextPart;
 list<_s_SnippetPart_TP>::iterator EndPart;

 list<String_imp> MacroName;


 static set<String_imp> Skip_set;
// if(Skip_set.empty() == true)
// {
  CREATE_SKIP_ID_SET_mk(Skip_set);
// }

// @MRTZ_endBlock


 FirstPart = snipet->begin();
 EndPart   = snipet->end();
 if(FirstPart != EndPart)
 {
  CurrentPart = FirstPart;
  NextPart    = FirstPart;
  while(CurrentPart != EndPart)
  {
   Sequence.Content.clear();
   if(CurrentPart->Type == SNIPPET_SEQUENCE)
   {
#if defined(DEBUG_OUTPUT)
      cout << "Snipet to parse :\n" << string((CurrentPart->Text).c_str(),(CurrentPart->Text).c_str()+(CurrentPart->Text).size()) << endl;
#endif //DEBUG_OUTPUT

    LOG_ACTIVE();
    Grammar_Spirit185->scan((CurrentPart->Text).c_str(),(CurrentPart->Text).c_str()+(CurrentPart->Text).size(),SEQUENCE.c_str());
    LOG_PASSIVE();

    TiPa_Concrete::DataFellow* MainTree = Grammar_Spirit185->scanData(SEQUENCE.c_str());
                                                           // get text-positions to manipulate permanently
    TiPa_Concrete::DataFellow  Reduced;
    MainTree->welcome(ResultFilter(Spirit185_Filter::KeepUndefined, &Reduced),IterateDownwards);
    TiPa_Concrete::DataAssociation* Function        = Reduced.contractorFirst_get();
    TiPa_Concrete::DataAssociation* FunctionContent = nullptr;


#if defined(DEBUG_OUTPUT)
    Spirit185_Store  Store;
    char* ParsedGrammar = nullptr ;
    Reduced.welcome(Store(Spirit185_Store::Content2XML, &ParsedGrammar), IterateDownwards);

    if(ParsedGrammar != nullptr)
     cout << ParsedGrammar << endl;
    else
     cout << "ParsedGrammar is empty" << endl;
#endif //DEBUG_OUTPUT

     while  ( Function != nullptr)
     {
      TiPa_Data* FunctionData = Function->data_get();

      if(FunctionData->ParserClass == TiPa_Abstract::TDA_TiPa_Rule)
      {
       string FunctionName = FunctionData->Parser->as_TiPa_Rule()->getName();
       if(   (FunctionName==OPTION  )
           ||(FunctionName==ONLYONCE)
           ||(FunctionName==FORMAT  )
         )
       {
        if    (FunctionName == OPTION)
         Sequence.Type = SEQUENCETYPE_OPTION;
        else if(FunctionName == ONLYONCE)
         Sequence.Type = SEQUENCETYPE_ONLYONCE;
        else if(FunctionName == FORMAT)
         Sequence.Type = SEQUENCETYPE_FORMAT;
        else {}

        FunctionContent = Function->contractorFirst_get();
        break;
       }
       else
       {
#if defined(DEBUG_OUTPUT)
        cout << "+++++++++++++++++" << endl;
        cout << "unknown sequence:\n" << string((CurrentPart->Text).c_str(),(CurrentPart->Text).c_str()+(CurrentPart->Text).size()) << endl;
        cout << "+++++++++++++++++" << endl;
#endif //DEBUG_OUTPUT

       }
      }
      Function = Function->fellowBehind_get(&Reduced);
     }
#if defined(DEBUG_OUTPUT)
      cout << "option found: " << String_imp((*Function)->value.begin(), (*Function)->value.end()) << endl;
#endif //DEBUG_OUTPUT
     while( FunctionContent != nullptr)
     {
      TiPa_Data* ContentData = FunctionContent->data_get();

      if(ContentData->ParserClass != TiPa_Abstract::TDA_TiPa_Rule)
      {
       FunctionContent = FunctionContent->fellowBehind_get(Function);
       continue;
      }
      string     ContentName(ContentData->Begin, ContentData->End);
      unsigned long FunctionID = ContentData->UserID;

      if(command_set->find(ContentData->Parser->as_TiPa_Rule()->getName()) != command_set->end())    ///????????????????????????????????ß
      {
       RawCommand.Name = ContentData->Parser->as_TiPa_Rule()->getName();
       RawCommand.ID   = FunctionID;
       RawCommand.Parameter.clear();

       TiPa_Concrete::DataAssociation* Command = FunctionContent->contractorFirst_get();
       while( Command != nullptr)
       {
        TiPa_Data* CommandData = Command->data_get();

        if(CommandData->ParserClass != TiPa_Abstract::TDA_TiPa_Rule)
        {
         Command = Command->fellowBehind_get(FunctionContent);
         continue;
        }
        string CommandName = CommandData->Parser->as_TiPa_Rule()->getName() ;

        if(  (CommandData->ParserClass        == TiPa_Abstract::TDA_TiPa_Rule)
           &&(command_set->find(CommandName ) == command_set->end())
           &&(Skip_set.find(CommandName )     == Skip_set.end())  ///????????????????????????
          )
         {
          RawAtom.Token = CommandData->Parser->as_TiPa_Rule()->getName();
          RawAtom.Text  = String_imp(CommandData->Begin, CommandData->End);
          RawCommand.Parameter.push_back(RawAtom);
         }
        Command = Command->fellowBehind_get(FunctionContent);
       }
       Sequence.Content.push_back(RawCommand);
      }
      else if(Sequence.Type==SEQUENCETYPE_FORMAT)
      {
       RawAtom.Text  = CurrentPart->Text;
       RawAtom.Token = ContentData->Parser->as_TiPa_Rule()->getName();

       RawCommand.Name = RAWTEXT;
       RawCommand.ID   = 0;
       RawCommand.Parameter.clear();
       RawCommand.Parameter.push_back(RawAtom);
       Sequence.Content.push_back(RawCommand);
       Sequence.Type = SEQUENCETYPE_RAWTEXT;
       break;
      }
      FunctionContent = FunctionContent->fellowBehind_get(Function);

     }
     ReturnValue.push_back(Sequence);
   }
   else if(CurrentPart->Type == SNIPPET_MACRO)
   {
    // ignore macros since they are allready inserted

    if(  (!(MacroName.empty()))
       &&(  MacroName.back() == CurrentPart->Text)
       )
    {
     MacroName.pop_back();
     RawAtom.Token   = MACRO + "_end";
     RawCommand.Name = MACRO + "_end";

    }
    else
    {
     MacroName.push_back(CurrentPart->Text);
     RawAtom.Token   = MACRO + "_begin";
     RawCommand.Name = MACRO + "_begin";
    }
    RawAtom.Text    = CurrentPart->Text;
    RawCommand.ID   = 0;
    RawCommand.Parameter.clear();
    RawCommand.Parameter.push_back(RawAtom);
    Sequence.Content.push_back(RawCommand);
    Sequence.Type = SEQUENCETYPE_MACRO;
    ReturnValue.push_back(Sequence);
   }
   else
   {
    RawAtom.Token   = RAWTEXT;
    RawAtom.Text    = CurrentPart->Text;
    RawCommand.Name = RAWTEXT;
    RawCommand.ID   = 0;
    RawCommand.Parameter.clear();
    RawCommand.Parameter.push_back(RawAtom);
    Sequence.Content.push_back(RawCommand);
    Sequence.Type = SEQUENCETYPE_RAWTEXT;
    ReturnValue.push_back(Sequence);
   }
   ++CurrentPart;

  }
 }
 return(ReturnValue);
}


/* @MRTZ_describe _getFormatSymbols

*/
void Generator_Nsd::_getFormatSymbols(String_imp* text, list<_s_Format_TP>* returnValue)
{
 _s_Format_TP Action = {"",0,0,0,""};


 static set<String_imp> Format_set;
// if(Format_set.empty() == true)
// {
  CREATE_FORMAT_ID_SET_mk(Format_set);
// }



#if defined(DEBUG_OUTPUT)
 cout << "_getFormatSymbols Snipet to parse :\n" << (*text) << endl;
#endif //DEBUG_OUTPUT

  Grammar_Spirit185->scan(text->c_str(), text->c_str() + text->size(), FORMAT.c_str());

  TiPa_Concrete::DataFellow* MainTree = Grammar_Spirit185->scanData(FORMAT.c_str());

  ResultFilter.contextModel_set(&ContextModel);
  TiPa_Concrete::DataFellow  Reduced;
  MainTree->welcome(ResultFilter(Spirit185_Filter::KeepUndefined, &Reduced),IterateDownwards);
  TiPa_Concrete::DataAssociation* Package        = &Reduced;

#if defined(DEBUG_OUTPUT)
    Spirit185_Store  Store;
    char* ParsedGrammar = nullptr ;
    Reduced.welcome(Store(Spirit185_Store::Content2XML, &ParsedGrammar), IterateDownwards);

    if(ParsedGrammar != nullptr)
     cout << ParsedGrammar << endl;
    else
     cout << "ParsedGrammar is empty" << endl;
#endif //DEBUG_OUTPUT

  while(Package != nullptr)
  {
   TiPa_Concrete::DataAssociation* Hit = Package->contractorFirst_get();
   while( Hit != nullptr)
   {
    TiPa_Data* HitData = Hit->data_get();
#if defined(DEBUG_OUTPUT)
    cout << "Hit: "  << String_imp(HitData->Begin, HitData->End) << endl;
#endif //DEBUG_OUTPUT

    if(HitData->Parser->as_TiPa_Rule()->getName()==FORMAT)
    {
#if defined(DEBUG_OUTPUT)
     cout << "Format: "  << String_imp(HitData->Begin, HitData->End) << endl;
#endif //DEBUG_OUTPUT
     Action.Begin = HitData->Begin - text->c_str();
     Action.End   = HitData->End   - text->c_str();

     TiPa_Concrete::DataAssociation* Format = Hit->contractorFirst_get();
     if(Format != nullptr)
     {
      TiPa_Data* FormatData = Format->data_get();
      string FormatRule = FormatData->Parser->as_TiPa_Rule()->getName();
#if defined(DEBUG_OUTPUT)
    cout << "FormatRule(" << FormatRule << "): "  << String_imp(FormatData->Begin, FormatData->End) << endl;
#endif //DEBUG_OUTPUT

      Action.Name = FormatRule;
      TiPa_Concrete::DataAssociation* Number = Format->contractorFirst_get();

      while(Number != nullptr)
      {
       TiPa_Data* NumberData = Number->data_get();
#if defined(DEBUG_OUTPUT)
    cout << "Number: "  << String_imp(NumberData->Begin, NumberData->End) << endl;
#endif //DEBUG_OUTPUT

#if defined(DEBUG_OUTPUT)
       cout <<     "Number to parse: "  << String_imp((*Detail)->value.begin(), (*Detail)->value.end()) << endl;
       cout <<     "Length to parse: "  << ((*Detail)->value.end())-((*Detail)->value.begin()) << endl ;
#endif //DEBUG_OUTPUT
       if(  (NumberData->ParserClass                       == TiPa_Abstract::TDA_TiPa_Rule)
          &&(NumberData->Parser->as_TiPa_Rule()->getName() == NUMBER                      )
         )
       {
        Action.Number = stringToNumber(String_imp(NumberData->Begin, NumberData->End));
        break;
       }
       else
       {
        Number = Number->fellowBehind_get(Format);
       }
      }
     }
#if defined(DEBUG_OUTPUT)
     cout <<     "Action: "  << Action.Name
          << "    Number: "  << Action.Number
          << "    Begin: "   << Action.Begin
          << "    End: "     << Action.End << endl;
#endif //DEBUG_OUTPUT
     returnValue->push_back(Action);

    }
    Hit = Hit->fellowBehind_get(Package);
   }
   Package = Package->fellowBehind_get(&Reduced);
  }

 Grammar_Spirit185->TDA_GrmConcrete::init();
 ContextModel.init();

}




/* @MRTZ_describe _split

*/
list<_s_Format_TP> Generator_Nsd::_split(String_imp* text)
{

 list<_s_Format_TP> ReturnValue;
 String_imp  Line;

 list<_s_Format_TP>::reverse_iterator Format;


 _getFormatSymbols(text,&ReturnValue);

#if defined(DEBUG_OUTPUT)
 cout << "Format-Size :" << ReturnValue.size() << endl;
#endif //DEBUG_OUTPUT

 Format = ReturnValue.rbegin(); // begin from end
 while(Format != ReturnValue.rend())
 // iterate through formats from end to begin since with every
 // split action the index-values behind get invalid
 {

  Line = text->substr((*Format).Begin);
  Line = replacePartString(Line,"\n","");
  Line = replacePartString(Line,"\r","");

  text->erase((*Format).Begin);

  Format->End   = Format->End - Format->Begin;
  Format->Begin = 0;
  Format->Part  = Line.erase(Format->Begin,Format->End);

  if(((*Format).Name)!="ascii")
  // do only for newLine, indend, dedend, space and tab
   while((Format->Part)[0] ==' ') // until a leading space is existing
    (Format->Part).erase(0,1);    // delete first leading space

#if defined(DEBUG_OUTPUT)
     cout <<     "Action: "  << (*Format).Name
          << "    Number: "  << (*Format).Number
          << "    Begin: "   << (*Format).Begin
          << "    End: "     << (*Format).End
          << "    Part: "    << (*Format).Part << endl;
#endif //DEBUG_OUTPUT
  ++Format;// step back;
 }

 return(ReturnValue);
}









#ifndef DOXYGEN
//};// CL_GEN_NSD;
//};// CL_TRANSFORM;
//};// CL_PROCESS;
#endif //DOXYGEN
