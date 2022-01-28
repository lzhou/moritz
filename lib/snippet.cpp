/*!

 @file
 @brief  definition of a user-defined Snippet

 This file contains the representation of the Snippet content defined by the user
 in a prepared version where the passive source-macros and the active commands
 are already separated and prepared.

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
    12.06.2011     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    12.06.2011...  @I Eckard Klotz
 @I Changes are documented in the comment of the changed element
 @TabEnd

*/
#include <dirent.h>

#include "app_tool.h"

#include"StringC_help.h"

#include "gen_nsd.h"
#include "command.h"
#include "cmnd_srcdata.h"
#include "cmnd_stack_strg.h"
#include "cmnd_dict_xml.h"
#include "cmnd_parser.h"

#include "snippet.h"


#ifndef DOXYGEN
//namespace CL_SNIPPET {
#endif //DOXYGEN

 list<String_imp>  SnippetExecution::Att_Caller;

/* @MRTZ_describe SnippetExecution

*/
SnippetExecution::SnippetExecution(void)
{
}

/* @MRTZ_describe SnippetExecution

*/
SnippetExecution::SnippetExecution(const list<_s_RawSequence_TP> &             snipetInfo,
                                   map<String_imp, SnippetExecution*> *        home,
                                   map<String_imp, list<SnippetExecution*> > * holiday,
                                   const String_imp&                           ownName,
                                   Prcs_Transformation*                        formater)
{
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

 Cmnd_Common    SequenceCreator;
 _s_Sequence_TP* Sequence = nullptr;

 Att.Home     = home;
 Att.Holiday  = holiday;
 Att.OwnName  = ownName;
 Att.Formater = formater;

 int        SequenceIndex = 0;
// String_imp ParameterText = "";
// String_imp Indent        = "";


 list<_s_RawSequence_TP>           SnipetInfo    = snipetInfo;
 list<_s_RawSequence_TP>::iterator Sequence_Crnt = SnipetInfo.begin();
 while(Sequence_Crnt != SnipetInfo.end())
 {
  ++ SequenceIndex;
  Sequence = new _s_Sequence_TP;
  Sequence->FirstCheck   = new  map<String_imp,_s_CommandData_TP>;
  Sequence->PreCommand   = new  map<String_imp,_s_CommandData_TP>;
  Sequence->ChildCommand = new  map<String_imp,_s_CommandData_TP>;
  Sequence->PostCommand  = new  map<String_imp,_s_CommandData_TP>;
  Sequence->LastCheck    = new  map<String_imp,_s_CommandData_TP>;

  Sequence->Type = Sequence_Crnt->Type;

  list<_s_RawCmnd_TP>::iterator Command_Crnt = (Sequence_Crnt->Content).begin();
  while(Command_Crnt != (Sequence_Crnt->Content).end())
  {
// @MRTZ_ifElseChain
   if(FirstCheck.find(Command_Crnt->Name)!= FirstCheck.end())
    SequenceCreator.assignSequence(Command_Crnt,(Sequence->FirstCheck));
   else if(  (PreCommand.find(Command_Crnt->Name) != PreCommand.end())
           ||(RawText.   find(Command_Crnt->Name) != RawText.end())
          )
    SequenceCreator.assignSequence(Command_Crnt,(Sequence->PreCommand));
   else if(PostCommand.find(Command_Crnt->Name)!= PostCommand.end())
    SequenceCreator.assignSequence(Command_Crnt,(Sequence->PostCommand));
   else if(  (LastCheck.find(Command_Crnt->Name) != LastCheck.end())
           ||(IfEmpty.  find(Command_Crnt->Name) != IfEmpty.end())
          )
    SequenceCreator.assignSequence(Command_Crnt,(Sequence->LastCheck));
   else if(ChildCommand.find(Command_Crnt->Name)!= ChildCommand.end())
    SequenceCreator.assignSequence(Command_Crnt,(Sequence->ChildCommand));

   else if(  (Command_Crnt->Name!=(MACRO + "_begin"))
           ||(Command_Crnt->Name!=(MACRO + "_end"))
          )
   {
   }
   else
   {
    cout << "unknown procedure " << Command_Crnt->Name << " found in snippet " << Att.OwnName << " !" << endl;
   }
   ++Command_Crnt;
  }
  Att.Sequence.push_back(Sequence);
  ++Sequence_Crnt;
 }

}



/* @MRTZ_describe ~SnippetExecution

*/
SnippetExecution::~SnippetExecution(void)
{

}

/* @MRTZ_describe showSelf

*/
void SnippetExecution::showSelf(void)
{

 list <_s_Sequence_TP *>::iterator           Sequence;
 int                                        Counter   = 0;
 map<String_imp,_s_CommandData_TP>*          Part      = nullptr;
 map<String_imp,_s_CommandData_TP>::iterator Procedure;
 map<String_imp , String_imp >::iterator    Parameter;


 Sequence = Att.Sequence.begin();

 while(Sequence != Att.Sequence.end())
 {
  switch((*Sequence)->Type)
  {
   case SEQUENCETYPE_RAWTEXT :
   {
    cout << "Sequence of Type Rawtext" << endl;
   }break;
   case SEQUENCETYPE_ONLYONCE:
   {
    cout << "Sequence of Type Onlyonce" << endl;
   }break;
   case SEQUENCETYPE_OPTION :
   {
    cout << "Sequence of Type Option" << endl;
   }break;
   case SEQUENCETYPE_FORMAT :
   {
    cout << "Sequence of Type Format" << endl;
   }break;
   case SEQUENCETYPE_MACRO  :
   default:
   {
    cout << "Sequence of unknown Type" << endl;
   }break;
  }

  for(Counter = 0; Counter <5;Counter ++)
  {
   switch(Counter)
   {
    case 0 : Part = (*Sequence)->FirstCheck;   cout << " First Checks : \n"  ; break;
    case 1 : Part = (*Sequence)->PreCommand;   cout << " Pre-Commands : \n"  ; break;
    case 2 : Part = (*Sequence)->ChildCommand; cout << " Child-Commands : \n"; break;
    case 3 : Part = (*Sequence)->PostCommand;  cout << " Post-Commands : \n" ; break;
    case 4 : Part = (*Sequence)->LastCheck;    cout << " Last Checks : \n"   ; break;
    default: Part = nullptr;                      cout << " Invalid Part : \n"  ; break;
   }
   if(Part != nullptr)
   {
    Procedure = Part->begin();
    while(Procedure != Part->end())
    {
     cout << "  Sequence-Key : " << Procedure->first <<endl;
     cout << "   Command(" << (Procedure->second).ID
          << ") : "        << (Procedure->second).Name << endl;

     Parameter = (Procedure->second).Parameter.begin();
     while(Parameter != (Procedure->second).Parameter.end())
     {
      cout << "    Parameter(" << (Parameter->first)  <<") = ";
      if((Parameter->second).find("\n") < (Parameter->second).size() )
       cout << endl << (Parameter->second) << endl;
      else
       cout <<         (Parameter->second) << endl;
      ++Parameter ;
     }
     ++Procedure ;
    }
   }
  }
  ++Sequence ;
 }
}




/* @MRTZ_describe generate

*/
void SnippetExecution::generate(XML_Node                         source,
//                                String_imp                       startTag,
                                map<String_imp , String_imp>*    replacement,
                                list<String_imp>*                diagram,
                                bool                             resetSnipets)
{
// cout<<__FILE__<<"|SnippetExecution::generate|"<<"("<<__LINE__<<") enter :" << endl;
 map<String_imp, list<SnippetExecution*> >   SnippetRetirement;
 map<String_imp , String_imp >    LocalReplacement;


 Att_Caller.push_back(Att.OwnName);

 if(resetSnipets == true)// no second call in the same sequence
 {
  _resetSnipets(nullptr);// reset the local changes from snipet called before
 }

 list <_s_Sequence_TP *>::iterator Current = Att.Sequence.begin();
 while(Current != Att.Sequence.end())
 {
  bool DoSequence =_doFirstCheck(((*Current)->FirstCheck),source,replacement);
  while(DoSequence == true)
  {
   if(LocalReplacement.empty() == false)
    LocalReplacement.clear();
   LocalReplacement = *replacement;

   _doPreCommand(((*Current)->PreCommand),
                 &SnippetRetirement,
                 source,
                 &LocalReplacement,
                 diagram);

   if(source.typeGet() == XML_Data::NT_Element)
   {
    _doChildCommand(((*Current)->ChildCommand),
                    SELF,
                    source,
                    &LocalReplacement,
                    diagram);
   }

   XML_Node Child = source.firstGet();
   bool UseAlternative = true;
   bool WasUsed        = false;
   while(Child.valid() == true)// != nullptr)
   {
    if(source.typeGet() == XML_Data::NT_Element)
    {
     WasUsed = _doChildCommand(((*Current)->ChildCommand),
                               Child.valueGet(),
                               Child,
                               &LocalReplacement,
                               diagram);
    }
    else
     WasUsed = false;

    XML_Node ChildBefore  = Child;
             Child        = Child.behindGet();

    if(WasUsed == true)
    {
     UseAlternative = false;

     if((*Current)->Type == SEQUENCETYPE_ONLYONCE)//every child should only be used for one processing
     {
      source.nodeCut(ChildBefore);
      ChildBefore.associationNodeSet(nullptr);
     }
    }
   }
   _doPostCommand(((*Current)->PostCommand),
                   source,
                   &LocalReplacement,
                   diagram);

    DoSequence =_doLastCheck(((*Current)->LastCheck),
                             source,
                             UseAlternative,
                             &LocalReplacement,
                             diagram);
  }
  _resetSnipets(nullptr);               // reset the local changes from this sequence
  _resetSnipets(&SnippetRetirement);    // reset changes for downwards
  ++ Current ;
 }

 Att_Caller.pop_back();

// cout<<__FILE__<<"|SnippetExecution::generate|"<<"("<<__LINE__<<") leave" << endl;
}



/* @MRTZ_describe writeTextFile

*/
void SnippetExecution::writeTextFile(String_imp fileName,
                                     String_imp content,
                                     bool       countExisting)
{
 struct
 {
  Cmnd_Stack_Strg Stack;
 }Cmnd;



#if defined(DEBUG_OUTPUT)
 printf("Text-Analyse 7 \n");
#endif

 String_imp UsedPathSeparator  = Cmnd.Stack.exchange("__USEDPATHSEPARATOR__");
 String_imp OsPathSeparator    = Cmnd.Stack.exchange("__OSPATHSEPARATOR__");
 String_imp NewName            = replacePartString(fileName,
                                                   UsedPathSeparator,
                                                   OsPathSeparator
                                                  );

 if(countExisting == true)
 {
  fstream ExistingFile((char*)(NewName.c_str()),ios::binary|ios::in);
  if(ExistingFile.good())
  {
   cout << endl <<"found existing file: " << NewName << endl;
   size_t Pos = fileName.find_last_of(".");
   if(Pos != String_imp::npos)
    fileName.insert(Pos,":@:@:@");
   else
    fileName = fileName + ":@:@:@.txt";
   int Number = 0;
   while(ExistingFile.good()) // file successfully opened
   {
    ++ Number;
    NewName = numberToString(Number);
    while(NewName.size()<3)
    {
     NewName = String_imp("0") + NewName;
    }
    NewName = "_" + NewName + ".";
    NewName = replacePartString(fileName,":@:@:@.",NewName,false);
    ExistingFile.close();
    ExistingFile.open((char*)(NewName.c_str()),ios::binary|ios::in);
   }
   cout <<" defined a new name: " << NewName << endl << endl;
  }
  else
  {
   ExistingFile.close();
  }
 }

 content = format(&content);
 fstream NewFile((char*)(NewName.c_str()),ios::binary|ios::out);
 if(NewFile.good()) // file successfully opened
 {
  NewFile.write((char*)content.c_str(),content.size());
  NewFile.close();
 }
 else
 {
  NewFile.clear();
  cout << "file not saved :" << endl << NewName << endl;
  cout << "try to construct destination-folder"  << endl;
  createFolder(NewName, OsPathSeparator[0]); // create destination-folder

  fstream NewFile2((char*)(NewName.c_str()),ios::binary|ios::out);
  if(NewFile2.good())                                                // file successfully opened
  {
   NewFile2.write((char*)content.c_str(),content.size());
   NewFile2.close();
  }
  else
  {
   NewFile2.clear();
   cout << "file finaly not saved :" << endl << NewName << endl;
  }
 }

}

/* @MRTZ_describe snippet

*/
void SnippetExecution::snippet(XML_Node                       source,
                               String_imp                     startTag,
                               map<String_imp , String_imp >* replacement,
                               list<String_imp>*              diagram,
                               bool                           resetSnipets)
{
//cout<<__FILE__<<"|SnippetExecution::snippet|"<<"("<<__LINE__<<") enter" <<endl;
// XML_Node    Ansister;
// String_imp  Ansisters = "";
#if defined(DEBUG_OUTPUT)
 cout << "SnippetExecution::snippet startTag: " << startTag << endl;
 cout << "SnippetExecution::snippet source.valueGet(): " << source.valueGet() << endl;
#endif //DEBUG_OUTPUT
  static int CallCounter = 0;
 ++ CallCounter;


 if((*Att.Home)[startTag] != nullptr)
 {
  (*Att.Home)[startTag]->generate(source,
//                                  startTag,
                                  replacement,
                                  diagram,
                                  resetSnipets);
 }
 else
 {
  String_imp Ansisters = source.valueGet();
  XML_Node   Ansister  = source.preGet();

  while(  (Ansister.valid()   == true                )
        &&(Ansister.typeGet() == XML_Data::NT_Element)
       )
  {
#if defined(DEBUG_OUTPUT)
    cout << "Ansister: " << Ansister.valueGet() <<endl;
#endif
   Ansisters = string(Ansister.valueGet()) + "/" + Ansisters;
   Ansister = Ansister.preGet();
  }

  if(Ansister.valid() == false)
    Ansister  = source;

  cout << endl;
  cout << "no valid snipet defined for: " << endl ;
  source.xmlText();
  cout << endl << "called in: " << Ansister.valueGet() << endl << "from: " << Ansisters  << endl;

  cout << "--> if you used the command \"useForSnipet\" before make sure that you\n"
       << "    don\'t use the parameter\"__SELF__\" in the used replacement-snipet,\n"
       << "    in this case try the \"useForSnipetDownwards\" or try to use \n"
       << "    \"useForSnipet\" for \"" << startTag << "\" in the replacement-snipet also."
       << endl;
 }
 -- CallCounter;
//cout<<__FILE__<<"|SnippetExecution::snippet|"<<"("<<__LINE__<<") leave"<<endl;

}






/* @MRTZ_describe addStackValue

*/
void SnippetExecution::addStackValue(String_imp name,String_imp value)
{
 Cmnd_Stack_Strg Temp;
 Temp.addStackValue(name, value);
}





/* @MRTZ_describe xmlContext_set

*/
void SnippetExecution::xmlContext_set(XML_DataModel* xml_Context)
{
 Att.XML_Context = xml_Context;
}


/* @MRTZ_describe xmlContext_get

*/
XML_DataModel*  SnippetExecution::xmlContext_get(void)
{
 return(Att.XML_Context);
}









/* @MRTZ_describe getCallerPath

*/
String_imp SnippetExecution::getCallerPath(void)
{
 String_imp ReturnValue = "";
 list<String_imp>::iterator Name;

 Name = Att_Caller.begin();
 while(Name != Att_Caller.end())
 {
  ReturnValue = ReturnValue + (*Name);
  ++ Name;
  if(Name != Att_Caller.end())
   ReturnValue = ReturnValue + "/";
 }
 return(ReturnValue);
}



/* @MRTZ_describe format

*/
String_imp SnippetExecution::format(String_imp* rawText)
{
 return(((Generator_Nsd*)(Att.Formater))->format(rawText));
}





/* @MRTZ_describe _doFirstCheck

*/
bool SnippetExecution::_doFirstCheck(map<String_imp,_s_CommandData_TP>* sequence,
                                     XML_Node                          source,
                                     map<String_imp, String_imp>*       replacement
                                    )
{
 bool                                       ReturnValue = true;
 bool                                       TempValue   = true;
// map<String_imp,_s_CommandData_TP>::iterator Current;
 _s_CommandData_TP                           Command;
 struct
 {
  Cmnd_Common     Misc;
  Cmnd_SrcData    XmlData;
  Cmnd_Stack_Strg Stack;
  Cmnd_Dict_XML   XmlDict;
 }Cmnd;

 map<String_imp,_s_CommandData_TP>::iterator Current = sequence->begin();
 while(Current != sequence->end())
 {
  Command = Current->second;
  switch(Command.ID)
  {
   case ID_IFSTACKEQUAL:
   {
    Cmnd.Stack.ifStackEqual(Command.Parameter["stackName"],
                            Command.Parameter["value"],
                            &TempValue);
   }break;
   case ID_IFSTACKUNEQUAL:
   {
    Cmnd.Stack.ifStackUnequal(Command.Parameter["stackName"],
                              Command.Parameter["value"],
                              &TempValue);
   }break;


   case ID_IFXMLEQUAL:
   {
    Cmnd.XmlDict.ifXmlEqual(source,
                            Command.Parameter["tagName"],
                            Command.Parameter["tagPath"],
                            Command.Parameter["xmlProperty"],
                            Command.Parameter["value"],
                            Command.Parameter["separator"][0],
                            replacement,
                            this,
                            &TempValue);
   }break;
   case ID_IFXMLUNEQUAL:
   {
    Cmnd.XmlDict.ifXmlUnequal(source,
                              Command.Parameter["tagName"],
                              Command.Parameter["tagPath"],
                              Command.Parameter["xmlProperty"],
                              Command.Parameter["value"],
                              Command.Parameter["separator"][0],
                              replacement,
                              this,
                              &TempValue);
   }break;


   case ID_IFXMLEXISTING:
   {
    Cmnd.XmlDict.ifXmlExisting(source,
                               Command.Parameter["tagName"],
                               Command.Parameter["tagPath"],
                               Command.Parameter["xmlProperty"],
                               Command.Parameter["separator"][0],
                               replacement,
//                               this,
                               &TempValue);
   }break;
   case ID_IFXMLMISSING:
   {
    Cmnd.XmlDict.ifXmlMissing(source,
                              Command.Parameter["tagName"],
                              Command.Parameter["tagPath"],
                              Command.Parameter["xmlProperty"],
                              Command.Parameter["separator"][0],
                              replacement,
//                              this,
                              &TempValue);
   }break;


   case ID_IFOLDERAS:
   {
    Cmnd.XmlData.ifOlderAs(Cmnd.Stack.exchange("__SOURCEFILE__"),
                           Command.Parameter["dstName"],
                           Command.Parameter["dstPath"],
                           Cmnd.Stack.exchange("__USEDPATHSEPARATOR__"),
                           Cmnd.Stack.exchange("__OSPATHSEPARATOR__"),
                           &TempValue);
   }break;

   case ID_IFNOTEXIST:
   {
    Cmnd.XmlData.ifNotExist(Command.Parameter["dstName"],
                            Command.Parameter["dstPath"],
                            Cmnd.Stack.exchange("__USEDPATHSEPARATOR__"),
                            Cmnd.Stack.exchange("__OSPATHSEPARATOR__"),
                            &TempValue);
   }break;



   case ID_RAWTEXT              :
   case ID_SNIPET               :
   case ID_SUBSNIPET            :
   case ID_DROP                 :
   case ID_REPLACE              :
   case ID_USEFORSNIPET         :
   case ID_USEFORSNIPETLOCAL    :
   case ID_USEFORSNIPETDOWNWARDS:
   case ID_TEXT                 :
   case ID_COLLECTION           :
   case ID_DESTINATION          :
   case ID_FORALL               :
   case ID_STATISTIC            :
   case ID_IFABSENT             :
   case ID_IFEMPTY              :
   case ID_TAG                  :
   case ID_ATTRIBUTE            :
   case ID_STACKPUSH            :
   case ID_STACKCLEAR           :
   case ID_STACKREAD            :
   case ID_STACKREADALL         :
   case ID_STACKPOP             :
   case ID_STACKPOPALL          :
   case ID_REPEAT_IFSTACKEQUAL  :
   case ID_REPEAT_IFSTACKUNEQUAL:
   case ID_STACKPUSHSIZE        :
   case ID_XMLCREATE            :
   case ID_XMLCOPY              :
   case ID_XMLCUT               :
   case ID_XMLCODE              :
   case ID_XMLINSERT            :
   case ID_XMLSNIPET            :
   case ID_XMLSAVE              :
   case ID_XMLDELETE            :
   case ID_XMLPRINT             :
   case ID_PARSERSET            :
   case ID_PARSE                :



   default:
   {

   }break;
  }
  ReturnValue = ReturnValue && TempValue;

  ++Current ;
 }


 return(ReturnValue);
}



/* @MRTZ_describe _doPreCommand

*/
bool SnippetExecution::_doPreCommand(map<String_imp,_s_CommandData_TP>*  sequence,
                                     map<String_imp, list<SnippetExecution*> >* snippetRetirement,
                                     XML_Node                          source,
                                     map<String_imp, String_imp>*        replacement,
                                     list<String_imp>*                   diagram
                                     )
{
// cout<<__FILE__<<"|SnippetExecution::_doPreCommand|"<<"("<<__LINE__<<") enter"<<endl;
 bool                                        ReturnValue   = true;
 bool                                        TempValue     = true;
// map<String_imp,_s_CommandData_TP>::iterator Current;
 _s_CommandData_TP                           Procedure;

 struct
 {
  Cmnd_Common     Misc;
  Cmnd_SrcData    XmlData;
  Cmnd_Stack_Strg Stack;
  Cmnd_Dict_XML   XmlDict;
  Cmnd_Parser     Parser;
 }Cmnd;




 map<String_imp,_s_CommandData_TP>::iterator Current = sequence->begin();
 while(Current != sequence->end())
 {
  Procedure = Current->second;
  switch(Procedure.ID)
  {
   case ID_REPLACE:
   {
#if defined(DEBUG_OUTPUT)
    cout << "REPLACE" << endl;
#endif //DEBUG_OUTPUT

    Cmnd.Misc.replacmentSet(Procedure.Parameter["oldPart"],
                            Procedure.Parameter["newPart"],
                            Procedure.Parameter["replaceReset"],
                            replacement);
   }break;
   case ID_USEFORSNIPETDOWNWARDS:
   {
#if defined(DEBUG_OUTPUT)
    cout << "USEFORSNIPETDOWNWARDS" << endl;
#endif //DEBUG_OUTPUT
    _useForSnipet(Procedure.Parameter["tagName"],
                  Procedure.Parameter["snipetName"],
                  replacement,
                  snippetRetirement);

   }break;
   case ID_RAWTEXT:
   {
#if defined(DEBUG_OUTPUT)
    cout << "RAWTEXT" << Procedure.Parameter[RAWTEXT] << endl;
#endif //DEBUG_OUTPUT
    diagram->push_back(Procedure.Parameter[RAWTEXT]);

   }break;


   case ID_XMLCOPY:
   {
    Cmnd.XmlDict.xmlCopy(source,
                         Procedure.Parameter["newName"],
                         Procedure.Parameter["newPath"],
                         Procedure.Parameter["tagName"],
                         Procedure.Parameter["tagPath"],
                         Procedure.Parameter["separator"][0],
                         replacement,
                         this);
   }break;
   case ID_XMLCUT:
   {
    Cmnd.XmlDict.xmlCut(source,
                        Procedure.Parameter["newName"],
                        Procedure.Parameter["newPath"],
                        Procedure.Parameter["tagName"],
                        Procedure.Parameter["tagPath"],
                        Procedure.Parameter["separator"][0],
                        replacement,
                        this);
   }break;
   case ID_XMLCODE:
   {
    Cmnd.XmlDict.xmlCode(source,
                         Procedure.Parameter["newName"],
                         Procedure.Parameter["newPath"],
                         Procedure.Parameter["tagName"],
                         Procedure.Parameter["tagPath"],
                         Procedure.Parameter["separator"][0],
                         replacement,
                         this);
   }break;

   case ID_PARSERSET:
   {
     _parserSet(Procedure);
   }break;

   case ID_STATISTIC:
   {
    Cmnd.XmlData.statistic(source,
                           Procedure.Parameter["tagToCount"],
                           Procedure.Parameter["tagToSave"]);
   }break;


   case ID_SNIPET               :
   case ID_SUBSNIPET            :
   case ID_DROP                 :
   case ID_USEFORSNIPET         :
   case ID_USEFORSNIPETLOCAL    :
   case ID_TEXT                 :
   case ID_COLLECTION           :
   case ID_DESTINATION          :
   case ID_FORALL               :
   case ID_IFABSENT             :
   case ID_IFEMPTY              :
   case ID_TAG                  :
   case ID_ATTRIBUTE            :
   case ID_STACKPUSH            :
   case ID_STACKCLEAR           :
   case ID_STACKREAD            :
   case ID_STACKREADALL         :
   case ID_STACKPOP             :
   case ID_STACKPOPALL          :
   case ID_IFSTACKEQUAL         :
   case ID_IFSTACKUNEQUAL       :
   case ID_IFOLDERAS            :
   case ID_IFNOTEXIST           :
   case ID_REPEAT_IFSTACKEQUAL  :
   case ID_REPEAT_IFSTACKUNEQUAL:
   case ID_STACKPUSHSIZE        :
   case ID_XMLCREATE            :
   case ID_XMLINSERT            :
   case ID_XMLSNIPET            :
   case ID_XMLSAVE              :
   case ID_XMLDELETE            :
   case ID_XMLPRINT             :
   case ID_IFXMLEQUAL           :
   case ID_IFXMLUNEQUAL         :
   case ID_IFXMLEXISTING        :
   case ID_IFXMLMISSING         :
   case ID_PARSE                :


   default:
   {
#if defined(DEBUG_OUTPUT)
    cout << "unknow pre-procedure" << Procedure.Name << endl;
#endif //DEBUG_OUTPUT
   }break;
  }
  ReturnValue = ReturnValue && TempValue;

  ++Current ;
 }

// cout<<__FILE__<<"|SnippetExecution::_doPreCommand|"<<"("<<__LINE__<<") leave"<<endl;
 return(ReturnValue);
}


/* @MRTZ_describe _doChildCommand

*/
bool SnippetExecution::_doChildCommand(map<String_imp,_s_CommandData_TP>* sequence,
                                       const String_imp&                  startTag,
                                       XML_Node                           source,
                                       map<String_imp, String_imp>*       replacement,
                                       list<String_imp>*                  diagram)
{
//cout<<__FILE__<<"|SnippetExecution::_doChildCommand|"<<"("<<__LINE__<<") enter"<<endl;
 bool                                       ReturnValue = false;
// map<String_imp,_s_CommandData_TP>::iterator Current;
 _s_CommandData_TP                           Procedure;
 XML_Node                                    SubChild;
 struct
 {
  Cmnd_Common     Misc;
  Cmnd_SrcData    XmlData;
  Cmnd_Stack_Strg Stack;
  Cmnd_Dict_XML   XmlDict;
  Cmnd_Parser     Parser;
 }Cmnd;


 map<String_imp,_s_CommandData_TP>::iterator Current = sequence->begin();
 while(Current != sequence->end())
 {
  Procedure = Current->second;
  switch(Procedure.ID)
  {
   case ID_USEFORSNIPET:
   case ID_USEFORSNIPETLOCAL:
   //redo remaining for local changes since downwards called snippets restored
   //the original content of the snippet container
   {
#if defined(DEBUG_OUTPUT)
    cout << "USEFORSNIPETLOCAL"               << "/"
         << Procedure.Parameter["tagName"]    << "/"
         << Procedure.Parameter["snipetName"] << endl;
#endif //DEBUG_OUTPUT
    _useForSnipet(Procedure.Parameter["tagName"],
                  Procedure.Parameter["snipetName"],
                  replacement);

   }break;



   case ID_RAWTEXT              :
   case ID_SNIPET               :
   case ID_SUBSNIPET            :
   case ID_DROP                 :
   case ID_REPLACE              :
   case ID_USEFORSNIPETDOWNWARDS:
   case ID_TEXT                 :
   case ID_COLLECTION           :
   case ID_DESTINATION          :
   case ID_FORALL               :
   case ID_STATISTIC            :
   case ID_IFABSENT             :
   case ID_IFEMPTY              :
   case ID_TAG                  :
   case ID_ATTRIBUTE            :
   case ID_STACKPUSH            :
   case ID_STACKCLEAR           :
   case ID_STACKREAD            :
   case ID_STACKREADALL         :
   case ID_STACKPOP             :
   case ID_STACKPOPALL          :
   case ID_IFSTACKEQUAL         :
   case ID_IFSTACKUNEQUAL       :
   case ID_IFOLDERAS            :
   case ID_IFNOTEXIST           :
   case ID_REPEAT_IFSTACKEQUAL  :
   case ID_REPEAT_IFSTACKUNEQUAL:
   case ID_STACKPUSHSIZE        :
   case ID_XMLCREATE            :
   case ID_XMLCOPY              :
   case ID_XMLCUT               :
   case ID_XMLCODE              :
   case ID_XMLINSERT            :
   case ID_XMLSNIPET            :
   case ID_XMLSAVE              :
   case ID_XMLDELETE            :
   case ID_XMLPRINT             :
   case ID_IFXMLEQUAL           :
   case ID_IFXMLUNEQUAL         :
   case ID_IFXMLEXISTING        :
   case ID_IFXMLMISSING         :
   case ID_PARSERSET            :
   case ID_PARSE                :


   default:
   {
   }break;
  }
  ++ Current;
 }
 Current = sequence->begin();
 while(Current != sequence->end())
 {
  if((Current->first) == startTag)
  {
   Procedure = Current->second;
   switch(Procedure.ID)
   {
    case ID_DROP:
    {
     Cmnd.XmlData.drop(source/*,
                        Procedure.Parameter["tagName"]*/);
    }break;
    case ID_SNIPET:
    {
     if(startTag == SELF)
     {
#if defined(DEBUG_OUTPUT)
      cout<< "snippet for SELF"<<endl;
#endif //DEBUG_OUTPUT
       snippet(source,
               source.valueGet(),
               replacement,diagram,
               false);
     }
     else if(Procedure.Parameter.find("tagPath")!=Procedure.Parameter.end())
     {
#if defined(DEBUG_OUTPUT)
      cout<< "_doChildCommand ID_SNIPET"<<endl;
#endif //DEBUG_OUTPUT

       SubChild = source.firstGet(XML_Node::Element(XML_Search::Value,
                                                     Procedure.Parameter["tagPath"].c_str(),
                                                     Procedure.Parameter["separator"][0]));

       if(SubChild.valid() == true)// != nullptr)
        snippet(SubChild,
                SubChild.valueGet(),
                replacement,diagram,
                true);
     }

     else
     {
#if defined(DEBUG_OUTPUT)
      cout<< "_do else"<<endl;
#endif //DEBUG_OUTPUT
      snippet(source,
              source.valueGet(),
              replacement,diagram,
              true);
     }
    }break;
    case ID_COLLECTION:
    {
#if defined(DEBUG_OUTPUT)
      cout<< "_do collection"<<endl;
#endif //DEBUG_OUTPUT
     snippet(source,
             source.valueGet(),
             replacement,
             diagram);

    }break;
    case ID_TEXT:
    {
     if(Procedure.Parameter.find("tagPath")!=Procedure.Parameter.end())
     {
#if defined(DEBUG_OUTPUT)
      cout<< "_doChildCommand ID_TEXT"<<endl;
#endif //DEBUG_OUTPUT
      SubChild = source.firstGet(XML_Node::Element(XML_Search::Value,
                                                    Procedure.Parameter["tagPath"].c_str(),
                                                    Procedure.Parameter["separator"][0]));
     if(SubChild.valid() == true)// != nullptr)
       Cmnd.XmlData.text(SubChild,
                          replacement,
                          diagram);
     }
     else
      Cmnd.XmlData.text(source,
                         replacement,
                         diagram);

    }break;
    case ID_DESTINATION:// not used anymore
    {
//     Cmnd.Misc->destination(source,
//                            replacement,
//                            Procedure.Parameter["tagName"] );
//
    }break;
    case ID_STACKPUSH:
    {
     Cmnd.Stack.stackPush(source,
                          Procedure.Parameter["snipetName"],
                          replacement,
                          Procedure.Parameter["stackName"],
                          this);
    }break;
    case ID_XMLCREATE:
    {
     Cmnd.XmlDict.xmlCreate(source,
                            Procedure.Parameter["newName"],
                            Procedure.Parameter["newPath"],
                            Procedure.Parameter["separator"][0],
                            Procedure.Parameter["snipetName"],
                            replacement,
                            this);
    }break;
    case ID_XMLINSERT:
    {
     Cmnd.XmlDict.xmlInsert(source,
                            Procedure.Parameter["newName"],
                            Procedure.Parameter["newPath"],
                            Procedure.Parameter["position"],
                            Procedure.Parameter["separator"][0],
                            replacement,
                            this);
    }break;



   case ID_RAWTEXT              :
   case ID_SUBSNIPET            :
   case ID_REPLACE              :
   case ID_USEFORSNIPET         :
   case ID_USEFORSNIPETLOCAL    :
   case ID_USEFORSNIPETDOWNWARDS:
   case ID_FORALL               :
   case ID_STATISTIC            :
   case ID_IFABSENT             :
   case ID_IFEMPTY              :
   case ID_TAG                  :
   case ID_ATTRIBUTE            :
   case ID_STACKCLEAR           :
   case ID_STACKREAD            :
   case ID_STACKREADALL         :
   case ID_STACKPOP             :
   case ID_STACKPOPALL          :
   case ID_IFSTACKEQUAL         :
   case ID_IFSTACKUNEQUAL       :
   case ID_IFOLDERAS            :
   case ID_IFNOTEXIST           :
   case ID_REPEAT_IFSTACKEQUAL  :
   case ID_REPEAT_IFSTACKUNEQUAL:
   case ID_STACKPUSHSIZE        :
   case ID_XMLCOPY              :
   case ID_XMLCUT               :
   case ID_XMLCODE              :
   case ID_XMLSNIPET            :
   case ID_XMLSAVE              :
   case ID_XMLDELETE            :
   case ID_XMLPRINT             :
   case ID_IFXMLEQUAL           :
   case ID_IFXMLUNEQUAL         :
   case ID_IFXMLEXISTING        :
   case ID_IFXMLMISSING         :
   case ID_PARSERSET            :
   case ID_PARSE                :


    default:
    {

    }break;
   }
   ReturnValue = ReturnValue || true;
  }
  ++Current ;
 }
 //cout<<__FILE__<<"|SnippetExecution::_doChildCommand|"<<"("<<__LINE__<<") leave"<<endl;
 return(ReturnValue);
}


/* @MRTZ_describe _doPostCommand

*/
bool SnippetExecution::_doPostCommand(map<String_imp,_s_CommandData_TP>* sequence,
                                      XML_Node                   source,
                                      map<String_imp, String_imp>* replacement,
                                      list<String_imp>*            diagram)
{
// cout<<__FILE__<<"|SnippetExecution::_doPostCommand|"<<"("<<__LINE__<<") enter"<<endl;
 bool ReturnValue = true;
 bool                                       TempValue   = true;
// map<String_imp,_s_CommandData_TP>::iterator Current;
 _s_CommandData_TP                           Procedure;
 XML_Node                                    SubChild;
 struct
 {
  Cmnd_Common     Misc;
  Cmnd_SrcData    XmlData;
  Cmnd_Stack_Strg Stack;
  Cmnd_Dict_XML   XmlDict;
 }Cmnd;

 map<String_imp,_s_CommandData_TP>::iterator Current = sequence->begin();
 while(Current != sequence->end())
 {
  Procedure = Current->second;
  switch(Procedure.ID)
  {
   case ID_FORALL:
   {
    Cmnd.XmlData.forAll(source,
                        Procedure.Parameter["snipetName"],
                        replacement, diagram,
                        this);
   }break;
   case ID_IFABSENT:
   {
    if(Procedure.Parameter.find("tagPath")!=Procedure.Parameter.end())
    {
#if defined(DEBUG_OUTPUT)
      cout<< "_doPostCommand ID_IFABSENT"<<endl;
#endif //DEBUG_OUTPUT
     SubChild = source.firstGet(XML_Node::Element(XML_Search::Value,
                                                  Procedure.Parameter["tagPath"].c_str(),
                                                  Procedure.Parameter["separator"][0]));
     if(SubChild.valid() == false)// == nullptr)
      snippet(source,
              Procedure.Parameter["tagName"],
              replacement,diagram );
    }
    else
    {
     Cmnd.XmlData.ifAbsent(source,
                            Procedure.Parameter["tagName"],
                            Procedure.Parameter["snipetName"],
                            replacement, diagram,
                            this);
    }
   }break;
   case ID_TAG:
   {
    Cmnd.XmlData.tag(source, replacement, diagram);
  }break;
   case ID_ATTRIBUTE:
   {
    Cmnd.XmlData.attribute(source,
                            Procedure.Parameter["attributeName"],
                            replacement, diagram);
   }break;
   case ID_STACKPUSHSIZE:
   {
    Cmnd.Stack.stackPushSize(Procedure.Parameter["dstntnStack"],
                              Procedure.Parameter["sourceStack"]);
   }break;
   case ID_STACKREAD:
   {
   Cmnd.Stack.stackSave(Procedure.Parameter["stackName"],
                          Procedure.Name + "_" + Procedure.Parameter["value"],
                          replacement, diagram,
                          this);
   }break;
   case ID_STACKREADALL:
   {
    Cmnd.Stack.stackSaveAllReverse(Procedure.Parameter["stackName"],
                                   Procedure.Name + "_" + Procedure.Parameter["value"],
                                   replacement, diagram,
                                   this);
   }break;
   case ID_STACKPOP:
   {
    Cmnd.Stack.stackSave(Procedure.Parameter["stackName"],
                          Procedure.Name + "_" + Procedure.Parameter["value"],
                          replacement, diagram,
                          this);
   }break;
   case ID_STACKPOPALL:
   {
    Cmnd.Stack.stackSaveAllReverse(Procedure.Parameter["stackName"],
                                   Procedure.Name + "_" + Procedure.Parameter["value"],
                                   replacement, diagram,
                                   this);
  }break;
   case ID_STACKCLEAR:
   {
    Cmnd.Stack.stackClear(Procedure.Parameter["stackName"]);
   }break;

   case ID_XMLSNIPET:
   {
    Cmnd.XmlDict.xmlSnipet(Procedure.Parameter["newName"],
                           Procedure.Parameter["tagPath"],
                           Procedure.Parameter["separator"][0],
//                           Procedure.Parameter["tolerant"],
                           replacement,diagram,
                           this);
   }break;
   case ID_XMLSAVE:
   {
    Cmnd.XmlDict.xmlSave(Procedure.Parameter["newName"],
                         Procedure.Parameter["newPath"],
                         Procedure.Parameter["separator"][0],
                         Procedure.Parameter["fileName"],
                         Procedure.Parameter["filePath"],

                         Cmnd.Stack.exchange("__USEDPATHSEPARATOR__"),
                         Cmnd.Stack.exchange("__OSPATHSEPARATOR__"),

                         replacement,
                         this);
   }break;
   case ID_XMLDELETE:
   {
    Cmnd.XmlDict.xmlDelete(Procedure.Parameter["newName"],
                           Procedure.Parameter["newPath"],
                           Procedure.Parameter["separator"][0],
                           replacement,
                           this);
  }break;

   case ID_XMLPRINT:
   {
   Cmnd.XmlDict.xmlPrint(source,
                          Procedure.Parameter["prefix"],
                          Procedure.Parameter["tagName"],
                          Procedure.Parameter["tagPath"],
                          Procedure.Parameter["xmlProperty"],
                          Procedure.Parameter["separator"][0],
                          replacement,
                          this);

   }break;

   case ID_PARSE:
   {
    _parse(Procedure.Parameter["textToParse"],Procedure,replacement);
   }break;



   case ID_RAWTEXT              :
   case ID_SNIPET               :
   case ID_SUBSNIPET            :
   case ID_DROP                 :
   case ID_REPLACE              :
   case ID_USEFORSNIPET         :
   case ID_USEFORSNIPETLOCAL    :
   case ID_USEFORSNIPETDOWNWARDS:
   case ID_TEXT                 :
   case ID_COLLECTION           :
   case ID_DESTINATION          :
   case ID_STATISTIC            :
   case ID_IFEMPTY              :
   case ID_STACKPUSH            :
   case ID_IFSTACKEQUAL         :
   case ID_IFSTACKUNEQUAL       :
   case ID_IFOLDERAS            :
   case ID_IFNOTEXIST           :
   case ID_REPEAT_IFSTACKEQUAL  :
   case ID_REPEAT_IFSTACKUNEQUAL:
   case ID_XMLCREATE            :
   case ID_XMLCOPY              :
   case ID_XMLCUT               :
   case ID_XMLCODE              :
   case ID_XMLINSERT            :
   case ID_IFXMLEQUAL           :
   case ID_IFXMLUNEQUAL         :
   case ID_IFXMLEXISTING        :
   case ID_IFXMLMISSING         :
   case ID_PARSERSET            :


   default:
   {
   }break;
  }
  ReturnValue = ReturnValue && TempValue;

  ++Current ;
 }
// cout<<__FILE__<<"|SnippetExecution::_doPostCommand|"<<"("<<__LINE__<<") leave"<<endl;
 return(ReturnValue);
}


/* @MRTZ_describe _doLastCheck

*/
bool SnippetExecution::_doLastCheck(map<String_imp,_s_CommandData_TP>* sequence,
                                XML_Node                        source,
                                bool                              useAlternative,
                                map<String_imp, String_imp>*      replacement,
                                list<String_imp>*                 diagram)
{
//cout<<__FILE__<<"|SnippetExecution::_doLastCheck|"<<"("<<__LINE__<<") leave"<<endl;
 bool                                       ReturnValue = false;
 bool                                       TempValue   = false;
// map<String_imp,_s_CommandData_TP>::iterator Current;
 _s_CommandData_TP                           Command;
 struct
 {
  Cmnd_Common     Misc;
  Cmnd_SrcData    XmlData;
  Cmnd_Stack_Strg Stack;
  Cmnd_Dict_XML   XmlDict;
 }Cmnd;



 map<String_imp,_s_CommandData_TP>::iterator Current = sequence->begin();
 while(Current != sequence->end())
 {
  Command = Current->second;
  switch(Command.ID)
  {
   case ID_IFEMPTY:
   {
#if defined(DEBUG_OUTPUT)
      cout<< "_doLastCheck ID_IFEMPTY"<<endl;
#endif //DEBUG_OUTPUT

    if(useAlternative == true)
     snippet(source,
             Command.Parameter["snipetName"],
             replacement, diagram);

   }break;
   case ID_REPEAT_IFSTACKEQUAL:
   {
    TempValue  = true;
    Cmnd.Stack.ifStackEqual(Command.Parameter["stackName"],
                             Command.Parameter["value"],
                             &TempValue);
   }break;
   case ID_REPEAT_IFSTACKUNEQUAL:
   {
    TempValue  = true;
    Cmnd.Stack.ifStackUnequal(Command.Parameter["stackName"],
                               Command.Parameter["value"],
                               &TempValue);
   }break;



   case ID_RAWTEXT              :
   case ID_SNIPET               :
   case ID_SUBSNIPET            :
   case ID_DROP                 :
   case ID_REPLACE              :
   case ID_USEFORSNIPET         :
   case ID_USEFORSNIPETLOCAL    :
   case ID_USEFORSNIPETDOWNWARDS:
   case ID_TEXT                 :
   case ID_COLLECTION           :
   case ID_DESTINATION          :
   case ID_FORALL               :
   case ID_STATISTIC            :
   case ID_IFABSENT             :
   case ID_TAG                  :
   case ID_ATTRIBUTE            :
   case ID_STACKPUSH            :
   case ID_STACKCLEAR           :
   case ID_STACKREAD            :
   case ID_STACKREADALL         :
   case ID_STACKPOP             :
   case ID_STACKPOPALL          :
   case ID_IFSTACKEQUAL         :
   case ID_IFSTACKUNEQUAL       :
   case ID_IFOLDERAS            :
   case ID_IFNOTEXIST           :
   case ID_STACKPUSHSIZE        :
   case ID_XMLCREATE            :
   case ID_XMLCOPY              :
   case ID_XMLCUT               :
   case ID_XMLCODE              :
   case ID_XMLINSERT            :
   case ID_XMLSNIPET            :
   case ID_XMLSAVE              :
   case ID_XMLDELETE            :
   case ID_XMLPRINT             :
   case ID_IFXMLEQUAL           :
   case ID_IFXMLUNEQUAL         :
   case ID_IFXMLEXISTING        :
   case ID_IFXMLMISSING         :
   case ID_PARSERSET            :
   case ID_PARSE                :


   default:
   {

   }break;
  }
  ReturnValue = ReturnValue || TempValue;
  ++Current ;
}

// cout<<__FILE__<<"|SnippetExecution::_doLastCheck|"<<"("<<__LINE__<<") leave"<<endl;
 return(ReturnValue);
}





/* @MRTZ_describe useForSnipet

*/
void SnippetExecution::_useForSnipet(String_imp oldPart,
                                     String_imp newPart,
                   map<String_imp, String_imp>* replacement,
     map<String_imp, list<SnippetExecution*> >* snippetHoliday)
{

 String_imp                  OldPart = "";

 struct
 {
  Cmnd_Stack_Strg Stack;
 }Cmnd;

 oldPart = Cmnd.Stack.exchange(oldPart,replacement);
 newPart = Cmnd.Stack.exchange(newPart,replacement);


 if(snippetHoliday == nullptr)
 {
  snippetHoliday = Att.Holiday;
 }

 OldPart = oldPart;

 if(  (newPart != OldPart)
    &&(   snippetHoliday->find(OldPart)
       == snippetHoliday->end()
      )
   ) // first change of original snipet thus send it to holiday
 {
#if defined(DEBUG_OUTPUT)
  cout << "use snipet " << newPart << " now for " << OldPart << endl;
#endif //DEBUG_OUTPUT

  (*snippetHoliday)[OldPart].push_back((*Att.Home)[OldPart]);
  (*Att.Home)[OldPart]       = (*Att.Home)[newPart];
 }



#if defined(DEBUG_OUTPUT)
 map<String_imp, list<_s_SnippetPart_TP> >::iterator LocalSnipet;
 list<_s_SnippetPart_TP>::iterator FirstPart;
 list<_s_SnippetPart_TP>::iterator CurrentPart;
 list<_s_SnippetPart_TP>::iterator EndPart;

 LocalSnipet = (Att.Snippet)->find(OldPart);
  {
   cout << endl <<"|"<< LocalSnipet->first <<"|" << endl;
#if defined(DEBUG_OUTPUT)
   FirstPart = LocalSnipet->second.begin();
   EndPart   = LocalSnipet->second.end();
   if(FirstPart != EndPart)
    for(  CurrentPart = FirstPart;
          CurrentPart != EndPart;
        ++CurrentPart)
    {
     if(CurrentPart->Type == SNIPPET_PART)
      cout << "___LinePart___" << endl;
     else
      cout << "___Sequence___" << endl;
     cout << CurrentPart->Text <<endl;
    }
#endif //DEBUG_OUTPUT

  }
#endif //DEBUG_OUTPUT

}




/* @MRTZ_describe _resetSnipets

*/
void SnippetExecution::_resetSnipets(map<String_imp, list<SnippetExecution*> >* snippetHoliday)
{
 map<String_imp, list<SnippetExecution*>  >::iterator Current;

 if(snippetHoliday == nullptr)
 {
  snippetHoliday = Att.Holiday;
 }

 if((snippetHoliday->empty()) == false)
 {
  Current = snippetHoliday->begin();
  while(Current != snippetHoliday->end())
  {
//   if(Current->second != nullptr)
   if(Current->second.begin() != Current->second.end())
   {
//    (*Att.Home)[Current->first] = Current->second;
    (*Att.Home)[Current->first] = *(Current->second.rbegin());
    Current->second.pop_back();
#if defined(DEBUG_OUTPUT)
    cout << "the original snipet for " << Current->first << " will be used again" << endl;
#endif //DEBUG_OUTPUT
   }
   else
   {
    (*Att.Home).erase(Current->first);
#if defined(DEBUG_OUTPUT)
    cout << "the temporary snipet for " << Current->first << " is droped now" << endl;
#endif //DEBUG_OUTPUT
   }
   ++Current ;
  }
  snippetHoliday->clear();
 }
}


/* @MRTZ_describe _setParser

*/
void SnippetExecution::_parserSet( _s_CommandData_TP  procedure)
{
 //cout<<__FILE__<<"|SnippetExecution::_parserSet|"<<"("<<__LINE__<<") enter"<<endl;
// String_imp                                  Text          = "";
// String_imp                                  Path          = "";

 struct
 {
  Cmnd_Stack_Strg Stack;
  Cmnd_Parser     Parser;
 }Cmnd;


 String_imp  Path = Cmnd.Stack.exchange(procedure.Parameter["prs_root"]);
 if(   (Path != "")
    && (Path.rfind(Cmnd.Stack.exchange("__OSPATHSEPARATOR__")) < Path.size()-1)
   )
  Path = Path + Cmnd.Stack.exchange("__OSPATHSEPARATOR__");
 Path = Path + Cmnd.Stack.exchange(procedure.Parameter["cfg_path"]);
 cout << Path  << procedure.Parameter["configuration"] << endl;

 String_imp Text = readTextFile(Path +
                                procedure.Parameter["configuration"],
                                Cmnd.Stack.exchange("__USEDPATHSEPARATOR__"),
                                Cmnd.Stack.exchange("__OSPATHSEPARATOR__")
                               );
 XML_Node       Configuration;
 XML_DataModel  ConfigurationModel;
 if(ConfigurationModel.parse( Text.c_str(),
                             (Path + procedure.Parameter["configuration"]).c_str()
                            ) == true)
 {
  XML_Node ModelRoot = ConfigurationModel.rootNode();
  Configuration      = ModelRoot.firstGet(XML_Node::Element());
 }

 Path = Cmnd.Stack.exchange(procedure.Parameter["prs_root"]);
 if(   (Path != "")
    && (Path.rfind(Cmnd.Stack.exchange("__OSPATHSEPARATOR__")) < Path.size()-1)
   )
  Path = Path + Cmnd.Stack.exchange("__OSPATHSEPARATOR__");
 Path = Path + Cmnd.Stack.exchange(procedure.Parameter["grm_path"]);
 cout << Path << procedure.Parameter["grammar"] << endl;

 Text = readTextFile(Path +
                     procedure.Parameter["grammar"],
                     Cmnd.Stack.exchange("__USEDPATHSEPARATOR__"),
                     Cmnd.Stack.exchange("__OSPATHSEPARATOR__")
                     );

#if defined(DEBUG_OUTPUT)
 cout << "Grammar: " << Procedure.Parameter["grammar"] << endl;
 cout << "|" << Text << "|" << endl;
#endif //DEBUG_OUTPUT

 if(  (Configuration.valid() == true)// != nullptr)
    &&(Text          != ""     )
   )
 {
  Cmnd.Parser.setParser(Configuration, Text);
 }
 else
 {
// error-output independent xml not defined
  cout << "no valid parser-configuration \""
       << procedure.Parameter["configuration"]
       << "\" or grammar \""
       << procedure.Parameter["grammar"]
       <<"\" defined \"" << endl;
  cout << " in snipet: " << getCallerPath() << endl;
 }

}



/* @MRTZ_describe _setParser

*/
void SnippetExecution::_parse(String_imp                   textToParse,
                              _s_CommandData_TP            procedure,
                              map<String_imp, String_imp>* replacement
                             )
{
//cout<<__FILE__<<"|SnippetExecution::_parse|"<<"("<<__LINE__<<") enter"<<endl;

 struct
 {
  Cmnd_Stack_Strg Stack;
  Cmnd_Dict_XML   XmlDict;
  Cmnd_Parser     Parser;
 }Cmnd;

 String_imp Text = Cmnd.Stack.exchange(textToParse);


 XML_Node    Result(Cmnd.XmlDict.xmlContext_get(), XML_Data::NT_Element);
 Cmnd.Parser.useParser(Text, procedure.Parameter["rule"], &Result);

 if(Result.valid() == false)// == nullptr)
 {
  cout << "parser-error in snipet: " << getCallerPath() << endl;
 }
 else
 {
  Cmnd.XmlDict.xmlCut(Result,
                      procedure.Parameter["newName"],
                      procedure.Parameter["newPath"],
                      procedure.Parameter["rule"],
                      procedure.Parameter[""],
                      procedure.Parameter["separator"][0],
                      replacement,
                      this);
 }
//cout<<__FILE__<<"|SnippetExecution::_parse|"<<"("<<__LINE__<<") leave"<<endl;
}



//};



