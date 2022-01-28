/*!

 @file
 @brief  definition of a collection of snippet-commands to organize a stack

 This file contains special snippet-commands used to manage a stack
 used as temporary LiFo-memory for part-results

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

#include "gen_nsd.h"
#include "cmnd_stack_strg.h"


#ifndef DOXYGEN
//namespace CL_COMMAND {
//namespace CL_CMND_STACK_STRG {
#endif //DOXYGEN

map<String_imp, list<String_imp>* >Cmnd_Stack_Strg::Att_Stack;

/* @MRTZ_describe Cmnd_Stack_Strg

*/
Cmnd_Stack_Strg::Cmnd_Stack_Strg(void)
{
}



/* @MRTZ_describe ~Cmnd_Stack_Strg

*/
Cmnd_Stack_Strg::~Cmnd_Stack_Strg(void)
{
}


/* @MRTZ_describe addStackValue

*/
void Cmnd_Stack_Strg::addStackValue(String_imp name,String_imp value)
{
#if defined(DEBUG_OUTPUT)
 cout << "addStackValue : ";
 cout << " name: "  << name;
 cout << " value: " << value   << endl;
#endif //DEBUG_OUTPUT
 if(Att_Stack.find(name) == Att_Stack.end())
  Att_Stack[name] = new list<String_imp>;

 (Att_Stack[name])->push_front(value);
}





/* @MRTZ_describe stackPush

   @MRTZ_describe local_declarations

*/
void Cmnd_Stack_Strg::stackPush(XML_Node                     source,
                                String_imp                   startTag,
                                map<String_imp, String_imp>* replacement,
                                String_imp                   keyName,
                                SnippetExecution*            owner)
{
// @MRTZ_exclude local_declarations
// @MRTZ_beginBlock
 list<String_imp>           Diagram;
 list<String_imp>::iterator Line;
 String_imp                 Text = "";
 list<String_imp>::iterator Current ;
// @MRTZ_endBlock

#if defined(DEBUG_OUTPUT)
 cout << "stackPush : ";
 cout << " source: "   << source.valueGet();
 cout << " startTag: " << startTag ;
 cout << " keyName: "  << keyName  << endl;
 cout << " in snipet: " << owner->getCallerPath() << endl;
#endif //DEBUG_OUTPUT


#if defined(DEBUG_OUTPUT)
 map<String_imp, list<_s_SnippetPart_TP> >::iterator LocalSnipet;
 list<_s_SnippetPart_TP>::iterator FirstPart;
 list<_s_SnippetPart_TP>::iterator CurrentPart;
 list<_s_SnippetPart_TP>::iterator EndPart;

 LocalSnipet = Att.Snippet.find(startTag);
  {
   cout << endl <<"|"<< LocalSnipet->first <<"|" << endl;
#if defined(DEBUG_OUTPUT)
   FirstPart = LocalSnipet->second.begin();
   EndPart   = LocalSnipet->second.end();
   if(FirstPart != EndPart)
    for(CurrentPart = FirstPart;
        CurrentPart != EndPart;
        CurrentPart ++)
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

 if(Att_Stack.find(keyName) == Att_Stack.end())
  Att_Stack[keyName] = new list<String_imp>;

 if(startTag == SELF)
  startTag = source.valueGet();
 Current =  Att_Stack[keyName]->begin();

 owner->snippet(source, startTag, replacement, &Diagram, false);

 Line = Diagram.begin();
 while(Line != Diagram.end())
 {
#if defined(DEBUG_OUTPUT)
  cout << "Line :" << (*Line) << ":" << endl;
#endif //DEBUG_OUTPUT
  Text = Text + (*Line);
  ++ Line;
 }

 (Att_Stack[keyName])->insert(Current,Text);

#if defined(DEBUG_OUTPUT)
 if((keyName == "_CompoundName_")||(keyName == "_CompoundKind_"))
 {
  list<String_imp>::iterator Dump;
  Dump = (Att_Stack[keyName])->begin();
  while(Dump != (Att_Stack[keyName])->end())
  {
   cout << " Stack Push(" << keyName << ") : " << (*Dump) << endl;
//  if((Dump->second)->begin() != (Dump->second)->end())
//   cout << " Key(" << Dump->first << "/" << (Dump->second)<< ") : " << (*(Dump->second)->begin()) <<endl;
//  else
//   cout << " Key(" << Dump->first << ") : is empty "  <<endl;
   Dump++;
  }
// cout << "--PushName : " << keyName << endl;

 }

#endif //DEBUG_OUTPUT




}




/* @MRTZ_describe stackPushSize

   @MRTZ_describe local_declarations

*/
void Cmnd_Stack_Strg::stackPushSize(String_imp  destination,
                                    String_imp  source)
{
// @MRTZ_exclude local_declarations
// @MRTZ_beginBlock
 map<String_imp, list<String_imp>* > ::iterator Stack;

 source = replacePartString(source,"stackPushSize_","");
 source = replacePartString(source,"\"","");
 Stack  = Att_Stack.find(source);
// @MRTZ_endBlock
#if defined(DEBUG_OUTPUT)
 cout << "stackPushSize : ";
 cout << " source: "   << source;
 cout << " startTag: " << destination  << endl;
#endif //DEBUG_OUTPUT


 if(Stack == Att_Stack.end())           // stack is not defined
 {
#if defined(DEBUG_OUTPUT)
  cout << "stack : " << source << " not found" << endl;
  map<String_imp, list<String_imp> >::iterator Dump;
  Dump = Att_Stack.begin();
  while(Dump != Att_Stack.end())
  {
   cout << "Key :" << Dump->first << "#" << (Dump->second).size() << ": Key" << endl;

   Dump++;
  }
#endif //DEBUG_OUTPUT

 if(Att_Stack.find(destination) == Att_Stack.end())
  Att_Stack[destination] = new list<String_imp>;
 (Att_Stack[destination])->push_front("-1");
 }
 else
 {
  if(Att_Stack.find(destination) == Att_Stack.end())
   Att_Stack[destination] = new list<String_imp>;
 (Att_Stack[destination])->push_front(numberToString((Stack->second)->size()));
 }

}




/* @MRTZ_describe stackSave

   @MRTZ_describe local_declarations

   @MRTZ_describe read_FileName

   @MRTZ_describr read_Content

   @MRTZ_describe save_text_content

*/
void Cmnd_Stack_Strg::stackSave(String_imp                   keyDiagram,
                                String_imp                   keyFile,
                                map<String_imp, String_imp>* replacement,
                                list<String_imp>*            diagram,
                                SnippetExecution*            owner)
{
//@MRTZ_exclude local_declarations
//@MRTZ_beginBlock
 list<String_imp>::iterator  Content;
 list<String_imp>::iterator  FileName;
 String_imp                  Destination   = "";

 bool                        PopContent    = false;
 bool                        SaveNext      = true;
// String_imp                  Text          = "";
//@MRTZ_endBlock


#if defined(DEBUG_OUTPUT)
 cout << "stackSave : ";
 cout << " keyFile :"    << keyFile  << ":";
 cout << " keyDiagram :" << keyDiagram  << ":" << endl;
#endif //DEBUG_OUTPUT

#if defined(DEBUG_OUTPUT)
 map<String_imp, list<String_imp>* >::iterator Dump;
 Dump = Att_Stack.begin();
 while(Dump != Att_Stack.end())
 {
  cout << "Key :" << Dump->first << "#" << (Dump->second)->size() << ": Key" << endl;

  Dump++;
 }

#endif //DEBUG_OUTPUT


//@MRTZ_ifElseChain
 if     (keyFile.find("stackRead") < keyFile.size())
 {
  PopContent  = false;
  Destination = replacePartString(keyFile,"stackRead_","");
 }
 else if(keyFile.find("stackPop") < keyFile.size())
 {
  PopContent  = true;
  Destination = replacePartString(keyFile,"stackPop_","");
 }
 else
 {
  PopContent  = false;
  Destination = "";
 }
 Destination = replacePartString(Destination,"\"","");
#if defined(DEBUG_OUTPUT)
 cout << "Destination :" << Destination  << ":" << endl;
#endif //DEBUG_OUTPUT

 if((Destination != "")&&(Destination != LIVEOUT)) //save in diagramm
 {
//@MRTZ_exclude read_FileName
  if (  (Att_Stack.find(Destination)    != Att_Stack.end())
    &&(!(Att_Stack[Destination]->empty()))
     )
  {
   FileName = (Att_Stack[Destination])->begin();
#if defined(DEBUG_OUTPUT)
    cout << "..." << Destination <<"..|.."<< *FileName << "..."  << endl;
#endif //DEBUG_OUTPUT
  }
  else
 {
   SaveNext = false;
#if defined(DEBUG_OUTPUT)
//    cout << "???" << Destination << "???"  << endl;
   if(owner !=nullptr)
   {
    cout << "for destination-name a"                << endl;
    if(Att_Stack.find(Destination) == Att_Stack.end())
     cout << " missing stack: " << Destination         << endl;
    else if(Att_Stack[Destination]->empty())
     cout << " empty stack: " << Destination         << endl;

    if(owner != nullptr)
     cout << " in snippet: " << owner->getCallerPath() << endl;
    else
     cout << " in invalid snippet "  << endl;
   }
#endif //DEBUG_OUTPUT
  }
 }


//@MRTZ_exclude read_Content
 if(  (Att_Stack.find(keyDiagram)    != Att_Stack.end())
    &&(!(Att_Stack[keyDiagram]->empty()))
    )
 {
  Content     = (Att_Stack[keyDiagram])->begin();
#if defined(DEBUG_OUTPUT)
   if(!(Att_Stack[keyDiagram]->empty()))
    cout << "d.." << keyDiagram /*<< "..d.." << *Content << "..d"*/ << endl;
   else
    cout << "???.." << keyDiagram << "..???"  << endl;
#endif //DEBUG_OUTPUT
 }
 else
 {
  SaveNext = false;
  if(owner != nullptr)
  {
   cout << "for destination-content a"                << endl;
   if(Att_Stack.find(keyDiagram) == Att_Stack.end())
    cout << " missing stack: " << keyDiagram         << endl;
   else if(Att_Stack[keyDiagram]->empty())
    cout << " empty stack: " << keyDiagram         << endl;

//   if(owner != nullptr)
    cout << " in snipet: " << owner->getCallerPath() << endl;
//   else
//    cout << " in invalid snippet "  << endl;
  }
#if defined(DEBUG_OUTPUT)
 map<String_imp, list<String_imp>* >::iterator Dump;
 Dump = Att_Stack.begin();
 while(Dump != Att_Stack.end())
 {
  cout << "Key :" << Dump->first << "#" << (Dump->second)->size() << ": Key" << endl;

  Dump++;
 }

#endif //DEBUG_OUTPUT


 }

 if(SaveNext == true)
 {
  String_imp Text = "";
// @MRTZ_exclude save_text_content
// @MRTZ_beginBlock
  if(  (!(Att_Stack[keyDiagram]->empty()))
     && (Content != (Att_Stack[keyDiagram])->end())
    )
  {
   Text = (*Content);
   Text =  replacmentUse(Text,replacement);
  }
  else
   Text= "";

  if(Text != "")
  {
   if(Destination == "") //save in diagram
   {
    diagram->push_back(Text);
   }
   else if(Destination == LIVEOUT)
   {
    cout << Text << endl;
   }
   else              //save in file
   {
#if defined(DEBUG_OUTPUT)
    cout << "try to save" << endl;
#endif //DEBUG_OUTPUT
    if(owner !=nullptr)
    {
     owner->writeTextFile(*FileName, Text);
    }
   }
  }
// @MRTZ_endBlock

  if(PopContent == true )
  {
   if((Destination != "")&&(Destination != LIVEOUT)) //save in diagramm
   {
    if (Att_Stack.find(Destination) != Att_Stack.end())
    {
#if defined(DEBUG_OUTPUT)
     cout << "2Destination : " << Destination << endl;
#endif //DEBUG_OUTPUT
     if(!(Att_Stack[Destination]->empty()))
      (Att_Stack[Destination])->erase(FileName);

     FileName     = (Att_Stack[Destination])->begin();
#if defined(DEBUG_OUTPUT)
     cout << "2Destination : end"  << endl;
#endif //DEBUG_OUTPUT
    }
    else if(owner !=nullptr)
    {
#if defined(DEBUG_OUTPUT)
//     cout << "popContent???" << Destination << "???"  << endl;
   cout << "for destination-name b"                << endl;
   if(Att_Stack.find(Destination) == Att_Stack.end())
    cout << " missing stack: " << Destination         << endl;
   else if(Att_Stack[Destination]->empty())
    cout << " empty stack: " << Destination         << endl;

   if(owner != nullptr)
    cout << " in snipet: " << owner->getCallerPath() << endl;
   else
    cout << " in invalid snippet "  << endl;
#endif //DEBUG_OUTPUT
    }
    else{}
   }

#if defined(DEBUG_OUTPUT)
   cout << "keyDiagram : " << keyDiagram << endl;
#endif //DEBUG_OUTPUT
   if(  (Att_Stack.find(keyDiagram)    != Att_Stack.end())
      &&(!(Att_Stack[keyDiagram]->empty()))
     )
   {
     (Att_Stack[keyDiagram])->erase(Content);

     Content     = (Att_Stack[keyDiagram])->begin();
#if defined(DEBUG_OUTPUT)
   if(!(Att_Stack[keyDiagram]->empty()))
    cout << "d.." << keyDiagram /*<< "..d.." << *Content*/ << "..d" << endl;
   else
    cout << "???.." << keyDiagram << "..???"  << endl;
#endif //DEBUG_OUTPUT

   }
   else if(owner !=nullptr)
   {
#if defined(DEBUG_OUTPUT)
//    cout << "popKey???" << keyDiagram << "???"  << endl;
   cout << "for destination-content b"                << endl;
   if(Att_Stack.find(keyDiagram) == Att_Stack.end())
    cout << " missing stack: " << keyDiagram         << endl;
   else if(Att_Stack[keyDiagram]->empty())
    cout << " empty stack: " << keyDiagram         << endl;

   if(owner != nullptr)
    cout << " in snipet: " << owner->getCallerPath() << endl;
   else
    cout << " in invalid snippet "  << endl;

#endif //DEBUG_OUTPUT
   }
   else {}
  }
  else
  {
  }

 }

#if defined(DEBUG_OUTPUT)
 cout << "stackSave  OK: ";
 cout << " keyFile :"    << keyFile  << ":";
 cout << " keyDiagram :" << keyDiagram  << ":" << endl;
#endif //DEBUG_OUTPUT
}


/* @MRTZ_describe stackSaveAllReverse

   @MRTZ_describe local_declarations

   @MRTZ_describe read_first_FileName

   @MRTZ_describe read_first_Content

   @MRTZ_describe save_loop

   @MRTZ_describe save_text_content

   @MRTZ_describe define_SaveNext_as_true_or_false

*/
void Cmnd_Stack_Strg::stackSaveAllReverse(String_imp                   keyDiagram,
                                          String_imp                   keyFile,
                                          map<String_imp, String_imp>* replacement,
                                          list<String_imp>*            diagram,
                                          SnippetExecution*            owner)
{
//@MRTZ_exclude local_declarations
//@MRTZ_beginBlock
 list<String_imp>::reverse_iterator  Content;
 list<String_imp>::reverse_iterator  FileName;
 String_imp                  Destination   = "";

 bool                        PopContent    = false;
 bool                        SaveNext      = true;
// String_imp                  Text          = "";
//@MRTZ_endBlock


#if defined(DEBUG_OUTPUT)
 cout << "stackSave : ";
 cout << " keyFile :"    << keyFile  << ":";
 cout << " keyDiagram :" << keyDiagram  << ":" << endl;
#endif //DEBUG_OUTPUT

#if defined(DEBUG_OUTPUT)
 map<String_imp, list<String_imp>* >::iterator Dump;
 Dump = Att_Stack.begin();
 while(Dump != Att_Stack.end())
 {
  cout << "Key :" << Dump->first << "#" << (Dump->second)->size() << ": Key" << endl;

  Dump++;
 }

#endif //DEBUG_OUTPUT


//@MRTZ_ifElseChain
 if     (keyFile.find("stackReadAll") < keyFile.size())
 {
  PopContent  = false;
  Destination = replacePartString(keyFile,"stackReadAll_","");
 }
 else if(keyFile.find("stackPopAll") < keyFile.size())
 {
  PopContent  = true;
  Destination = replacePartString(keyFile,"stackPopAll_","");
 }
 else
 {
  PopContent  = false;
  Destination = "";
 }
 Destination = replacePartString(Destination,"\"","");
#if defined(DEBUG_OUTPUT)
 cout << "Destination :" << Destination  << ":" << endl;
#endif //DEBUG_OUTPUT

 if((Destination != "")&&(Destination != LIVEOUT)) //save in diagramm
 {
//@MRTZ_exclude read_first_FileName
  if (  (Att_Stack.find(Destination)    != Att_Stack.end())
    &&(!(Att_Stack[Destination]->empty()))
     )
  {
    FileName = (Att_Stack[Destination])->rbegin();
#if defined(DEBUG_OUTPUT)
    cout << "..." << Destination <<"..|.."<< *FileName << "..."  << endl;
#endif //DEBUG_OUTPUT
  }
  else
  {
   SaveNext = false;
#if defined(DEBUG_OUTPUT)
//    cout << "???" << Destination << "???"  << endl;
   if(owner !=nullptr)
   {
    cout << "for destination-name a"                << endl;
    if(Att_Stack.find(Destination) == Att_Stack.end())
     cout << " missing stack: " << Destination         << endl;
    else if(Att_Stack[Destination]->empty())
     cout << " empty stack: " << Destination         << endl;

    if(owner != nullptr)
     cout << " in snippet: " << owner->getCallerPath() << endl;
    else
     cout << " in invalid snippet "  << endl;
   }
#endif //DEBUG_OUTPUT
  }
 }


//@MRTZ_exclude read_first_Content
 if(  (Att_Stack.find(keyDiagram)    != Att_Stack.end())
    &&(!(Att_Stack[keyDiagram]->empty()))
    )
 {
   Content     = (Att_Stack[keyDiagram])->rbegin();
#if defined(DEBUG_OUTPUT)
   if(!(Att_Stack[keyDiagram]->empty()))
    cout << "d.." << keyDiagram /*<< "..d.." << *Content << "..d"*/ << endl;
   else
    cout << "???.." << keyDiagram << "..???"  << endl;
#endif //DEBUG_OUTPUT
 }
 else
 {
  SaveNext = false;
  if(owner !=nullptr)
  {
   cout << "for destination-content a"                << endl;
   if(Att_Stack.find(keyDiagram) == Att_Stack.end())
    cout << " missing stack: " << keyDiagram         << endl;
   else if(Att_Stack[keyDiagram]->empty())
    cout << " empty stack: " << keyDiagram         << endl;

//   if(owner != nullptr)
    cout << " in snipet: " << owner->getCallerPath() << endl;
//   else
//    cout << " in invalid snippet "  << endl;
  }
#if defined(DEBUG_OUTPUT)
 map<String_imp, list<String_imp>* >::iterator Dump;
 Dump = Att_Stack.begin();
 while(Dump != Att_Stack.end())
 {
  cout << "Key :" << Dump->first << "#" << (Dump->second)->size() << ": Key" << endl;

  Dump++;
 }

#endif //DEBUG_OUTPUT


 }

//@MRTZ_exclude save_loop
 while(SaveNext == true)
 {
  String_imp Text = "";
// @MRTZ_exclude save_text_content
// @MRTZ_beginBlock
  if(  (!(Att_Stack[keyDiagram]->empty()))
     && (Content != (Att_Stack[keyDiagram])->rend())
    )
  {
   Text = (*Content);
   Text =  replacmentUse(Text,replacement);
  }
  else
   Text= "";

  if(Text != "")
  {
   if(Destination == "") //save in diagramm
   {
    diagram->push_back(Text);
   }
   else if(Destination == LIVEOUT)
   {
    cout << Text << endl;
   }
   else              //save in file
   {
#if defined(DEBUG_OUTPUT)
    cout << "try to save" << endl;
#endif //DEBUG_OUTPUT
    if(owner !=nullptr)
    {
     owner->writeTextFile(*FileName, Text);
    }
   }
  }
// @MRTZ_endBlock

  if(PopContent == true )
  {
   if((Destination != "")&&(Destination != LIVEOUT)) //save in diagram
   {
    if (Att_Stack.find(Destination) != Att_Stack.end())
    {
#if defined(DEBUG_OUTPUT)
     cout << "2Destination : " << Destination << endl;
#endif //DEBUG_OUTPUT
     if(!(Att_Stack[Destination]->empty()))
      (Att_Stack[Destination])->pop_back();

     FileName     = (Att_Stack[Destination])->rbegin();
#if defined(DEBUG_OUTPUT)
     cout << "2Destination : end"  << endl;
#endif //DEBUG_OUTPUT
    }
    else if(owner !=nullptr)
    {
#if defined(DEBUG_OUTPUT)
//     cout << "popContent???" << Destination << "???"  << endl;
   cout << "for destination-name b"                << endl;
   if(Att_Stack.find(Destination) == Att_Stack.end())
    cout << " missing stack: " << Destination         << endl;
   else if(Att_Stack[Destination]->empty())
    cout << " empty stack: " << Destination         << endl;

   if(owner != nullptr)
    cout << " in snipet: " << owner->getCallerPath() << endl;
   else
    cout << " in invalid snippet "  << endl;
#endif //DEBUG_OUTPUT
    }
    else{}
   }

#if defined(DEBUG_OUTPUT)
   cout << "keyDiagram : " << keyDiagram << endl;
#endif //DEBUG_OUTPUT
   if(  (Att_Stack.find(keyDiagram)    != Att_Stack.end())
      &&(!(Att_Stack[keyDiagram]->empty()))
     )
   {
     (Att_Stack[keyDiagram])->pop_back();

     Content     = (Att_Stack[keyDiagram])->rbegin();
#if defined(DEBUG_OUTPUT)
   if(!(Att_Stack[keyDiagram]->empty()))
    cout << "d.." << keyDiagram /*<< "..d.." << *Content*/ << "..d" << endl;
   else
    cout << "???.." << keyDiagram << "..???"  << endl;
#endif //DEBUG_OUTPUT

   }
   else if(owner !=nullptr)
   {
#if defined(DEBUG_OUTPUT)
//    cout << "popKey???" << keyDiagram << "???"  << endl;
   cout << "for destination-content b"                << endl;
   if(Att_Stack.find(keyDiagram) == Att_Stack.end())
    cout << " missing stack: " << keyDiagram         << endl;
   else if(Att_Stack[keyDiagram]->empty())
    cout << " empty stack: " << keyDiagram         << endl;

   if(owner != nullptr)
    cout << " in snipet: " << owner->getCallerPath() << endl;
   else
    cout << " in invalid snippet "  << endl;

#endif //DEBUG_OUTPUT
   }
   else {}
  }
  else
  {

   if((Destination != "")&&(Destination != LIVEOUT)) //save in diagramm
   {
     ++ FileName;
   }
   ++ Content;

  }

// @MRTZ_exclude define_SaveNext_as_true_or_false
// @MRTZ_beginBlock
// @MRTZ_showSource
  if(  (  ((Destination != "")&&(Destination != LIVEOUT))
        &&(  Att_Stack.find(Destination) != Att_Stack.end())
        &&(!(Att_Stack[Destination]->empty()))
        &&(  Att_Stack.find(keyDiagram) != Att_Stack.end())
        &&(!(Att_Stack[keyDiagram]->empty()))
        &&(Content != (Att_Stack[keyDiagram])->rend())
       )
     ||(  ((Destination == "")||(Destination == LIVEOUT))
        &&(  Att_Stack.find(keyDiagram) != Att_Stack.end())
        &&(!(Att_Stack[keyDiagram]->empty()))
        &&(Content != (Att_Stack[keyDiagram])->rend())
       )
    )
   SaveNext = true;
  else
   SaveNext = false;
// @MRTZ_endBlock


 }

#if defined(DEBUG_OUTPUT)
 cout << "stackSave  OK: ";
 cout << " keyFile :"    << keyFile  << ":";
 cout << " keyDiagram :" << keyDiagram  << ":" << endl;
#endif //DEBUG_OUTPUT
}




/* @MRTZ_describe stackClear

*/
void Cmnd_Stack_Strg::stackClear(String_imp keyName)
{
#if defined(DEBUG_OUTPUT)
 cout << "stackClear : ";
 cout << " keyName: "  << keyName  << endl;
#endif //DEBUG_OUTPUT

 if(Att_Stack.find(keyName)!=Att_Stack.end())
 {
  delete(Att_Stack[keyName]);
  Att_Stack.erase(keyName);
 }

#if defined(DEBUG_OUTPUT)
 map<String_imp, list<String_imp>* >::iterator Dump;
 Dump = Att_Stack.begin();
 while(Dump != Att_Stack.end())
 {
  cout << "Key :" << Dump->first << "#" << (Dump->second)->size() << ": Key" << endl;

  Dump++;
 }

 cout << "clear OK" << endl;
#endif //DEBUG_OUTPUT
}





/* @MRTZ_describe ifStackEqual

   @MRTZ_describe local_declarations

*/
void Cmnd_Stack_Strg::ifStackEqual(String_imp  stcName,
                                   String_imp  refValue,
                                   bool*       result)
{
// @MRTZ_exclude local_declarations
// @MRTZ_beginBlock
 map<String_imp, list<String_imp>* > ::iterator Stack;

 Stack =(Att_Stack).find(stcName);
 refValue = replacePartString(refValue,"ifStackEqual_","");
 refValue = replacePartString(refValue,"\"","");
// @MRTZ_endBlock

#if defined(DEBUG_OUTPUT)
 cout<<"_ifStackEqual(" << refValue<<"|"<<stcName << ") :" << endl;
#endif //DEBUG_OUTPUT


// @MRTZ_ifElseChain
 if(Stack == Att_Stack.end())           // stack is not defined
 {
#if defined(DEBUG_OUTPUT)
  cout << "stack : " << stcName << " not found" << endl;
  if(*result)
   cout << "(*result = true) " <<endl;
  else
   cout << "(*result = false) " <<endl;
#endif //DEBUG_OUTPUT
#if defined(DEBUG_OUTPUT)
  cout << "stack : " << stcName << " not found" << endl;
  map<String_imp, list<String_imp> >::iterator Dump;
  Dump = Att_Stack.begin();
  while(Dump != Att_Stack.end())
  {
   cout << "Key :" << Dump->first << "#" << (Dump->second).size() << ": Key" << endl;

   Dump++;
  }

#endif //DEBUG_OUTPUT
//  (*result = false);
 }
 else if(*(Stack->second->begin()) != refValue) // uper value is unequal
 {
  (*result = false);
#if defined(DEBUG_OUTPUT)
   cout << "(*result = false)" << endl;
#endif //DEBUG_OUTPUT
 }
 else                                  // uper value is equal
 {
  (*result = true);
#if defined(DEBUG_OUTPUT)
  cout << "(*result = true)" << endl;
#endif //DEBUG_OUTPUT
 }


}


/* @MRTZ_describe ifStackUnequal

   @MRTZ_describe local_declarations

*/
void Cmnd_Stack_Strg::ifStackUnequal(String_imp  stcName,
                                     String_imp  refValue,
                                     bool*       result)
{
// @MRTZ_exclude local_declarations
// @MRTZ_beginBlock
 map<String_imp, list<String_imp>* > ::iterator Stack;

 Stack    = Att_Stack.find(stcName);
 refValue = replacePartString(refValue,"ifStackUnequal_","");
 refValue = replacePartString(refValue,"\"","");
// @MRTZ_endBlock

#if defined(DEBUG_OUTPUT)
 cout<<"_ifStackUnequal(" << refValue<<"|"<<stcName << ") :" << endl;
#endif //DEBUG_OUTPUT


// @MRTZ_ifElseChain
 if(Stack == Att_Stack.end())           // stack is not defined
 {
#if defined(DEBUG_OUTPUT)
  cout << "stack : " << stcName << " not found" << endl;
  if(*result)
   cout << "(*result = true) " <<endl;
  else
   cout << "(*result = false) " <<endl;
#endif //DEBUG_OUTPUT
#if defined(DEBUG_OUTPUT)
  cout << "stack : " << stcName << " not found" << endl;
  map<String_imp, list<String_imp> >::iterator Dump;
  Dump = Att_Stack.begin();
  while(Dump != Att_Stack.end())
  {
   cout << "Key :" << Dump->first << "#" << (Dump->second).size() << ": Key" << endl;

   Dump++;
  }

#endif //DEBUG_OUTPUT
//  (*result = false);
 }
 else if(*(Stack->second->begin()) != refValue) // uper value is unequal
 {
  (*result = true);
#if defined(DEBUG_OUTPUT)
  cout << "(*result = true)" << endl;
#endif //DEBUG_OUTPUT
 }
 else                                  // uper value is equal
 {
  (*result = false);
#if defined(DEBUG_OUTPUT)
   cout << "(*result = false)" << endl;
#endif //DEBUG_OUTPUT
 }


}



/* @MRTZ_describe exchange

*/
String_imp Cmnd_Stack_Strg::exchange(const String_imp&            stackName,
                                     map<String_imp, String_imp>* replacement)
{
 String_imp                   ReturnValue = "";
 list<String_imp>             StackProbe;
 map<String_imp , String_imp> NoReplacement;

 if(replacement == nullptr)
  replacement = &NoReplacement;

 stackSave(stackName, "",replacement, &StackProbe, nullptr);

 if(!(StackProbe.empty()))// a stack with the name given as old-part exists
 {
  ReturnValue = *(StackProbe.begin());
  StackProbe.clear();
 }
 else
 {
  ReturnValue = stackName;
 }

 return(ReturnValue);
}








#ifndef DOXYGEN
//};};
#endif //DOXYGEN










