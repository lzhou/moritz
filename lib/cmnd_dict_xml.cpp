/*!

 @file
 @brief  definition of a collection of snippet-commands to organize a xml-dictionary

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
    26.02.2012     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    26.02.2012...  @I Eckard Klotz
 @I Changes are documented in the comment of the changed element
 @TabEnd

*/

#include "xml_DataModel.h"

#include "gen_nsd.h"
#include "cmnd_dict_xml.h"
#include "cmnd_stack_strg.h"



#ifndef DOXYGEN
//namespace CL_COMMAND {
//namespace CL_CMND_DICT_XML {
#endif //DOXYGEN

map<String_imp, XML_Node>  Cmnd_Dict_XML::Att_Dict;
XML_DataModel              Cmnd_Dict_XML::XML_Context;    ///< manages the internal xml data




/* @MRTZ_describe Cmnd_Dict_XML

*/
Cmnd_Dict_XML::Cmnd_Dict_XML(void)
{
}


/* @MRTZ_describe ~Cmnd_Dict_XML

*/
Cmnd_Dict_XML::~Cmnd_Dict_XML(void)
{

//cout  << " Cmnd_Dict_XML::~Cmnd_Dict_XML Att_Dict.size()(" << Att_Dict.size() << ")" << endl;


// map<String_imp, XML_Node>::iterator Node = Att_Dict.begin();
// while(Node != Att_Dict.end())
// {
//  delete(Node->second);
//  ++ Node;
// }
// Att_Dict.clear();
}



/* @MRTZ_describe addValue

*/
void Cmnd_Dict_XML::addValue(String_imp name,
                             XML_Node  value)
{
#if defined(DEBUG_OUTPUT)
 cout << "addStackValue : ";
 cout << " name: "  << name;
 cout << " value: " << value   << endl;
#endif //DEBUG_OUTPUT

 Att_Dict[name] = value;

}




/* @MRTZ_describe getValue

*/
XML_Node  Cmnd_Dict_XML::getValue(String_imp        name,
                                  String_imp        tagPath,
                                  char              separator,
                                  SnippetExecution* owner)
{
 XML_Node    ReturnValue;

 if(Att_Dict.find(name) != Att_Dict.end())
 {
  XML_Node Root     = Att_Dict[name];
  XML_Node SubChild;

  if (tagPath != "")
  {
   SubChild = Root.firstGet(XML_Node::Element(XML_Search::Value,tagPath.c_str()));
   if(SubChild.valid() == false)
   {
    cout << "sub-element of node("<< name <<") not found!" <<endl;
    if(owner != NULL)
     cout << "  in snipet: " << owner->getCallerPath() << endl;
   }
  }
  else
   SubChild = Root;

  if(SubChild.valid() == true)
  {
   ReturnValue = SubChild;
  }
  else
  {
  // error-message ?
  }
 }
 else
 {
  // error-output independent xml not defined
   cout << "no independent xml-tree \"" << name << separator << tagPath << "\" defined" << endl;
   if(owner != NULL)
    cout << " in snipet: " << owner->getCallerPath() << endl;
 }

 return(ReturnValue);
}








/* @MRTZ_describe xmlContext_set

*/
void Cmnd_Dict_XML::xmlContext_init(void)
{
  Att_Dict.clear();
  XML_Context.init();
}


/* @ M R T Z_describe xmlContext_get
*/
XML_DataModel* Cmnd_Dict_XML::xmlContext_get(void)
{
 return(&XML_Context);
}












/* @MRTZ_describe xmlCreate

*/
void Cmnd_Dict_XML::xmlCreate(XML_Node                     source,
                              String_imp                   newName,
                              String_imp                   newPath,
                              char                         separator,
                              String_imp                   snipetName,
                              map<String_imp, String_imp>* replacement,
                              SnippetExecution*            owner)
{
//cout<<__FILE__<<"|Cmnd_Dict_XML::xmlCreate|"<<"("<<__LINE__<<") enter"<<endl;

 struct
 {
  Cmnd_Stack_Strg Stack;
 }Cmnd;

 _checkStack(&newName,&newPath,&separator,replacement);
 snipetName = Cmnd.Stack.exchange(snipetName,replacement);


#if defined(DEBUG_OUTPUT)
 cout << "1" << "xmlCreate"        << endl;
 cout << "2" << newName            << endl;
 cout << "3" << newPath            << endl;
 cout << "4" << snipetName         << endl;
 cout << "5" << source.valueGet() << endl;
#endif //DEBUG_OUTPUT


 list<String_imp>           NewContent;
 owner->snippet(source,
                source.valueGet(),
                replacement,
               &NewContent,
                false);
 if(!(NewContent.empty()))
 {
 String_imp Content = "";
  for (list<String_imp>::iterator Line  = NewContent.begin();
                                  Line != NewContent.end();
                                ++Line
      )
  {
   Content = Content + (*Line);
  }
  Content =   String_imp("<Content>")
            + Content
            + String_imp("</Content>");
  Content = owner->format(&Content);

  XML_Context.focus_Set(newName.c_str());

  if(XML_Context.parse(Content.c_str(),newName.c_str()) == true)
  {
   XML_Node Root;

   if(Att_Dict.find(newName) == Att_Dict.end())
   {
//    XML_Data* RootData = XML_Context.data_create();
//    RootData->valueSet(newName.c_str()) ;
//    RootData->typeSet(XML_Data::NT_Element);
//    Root = XML_Node(&XML_Context,RootData);
    Root = XML_Node(&XML_Context,XML_Data::NT_Element);
    Root.valueSet(newName.c_str());
    Att_Dict[newName] = Root;
   }
   else
   {
    Root = Att_Dict[newName];
   }

   list<String_imp>        SubTag = stringToList(newPath,separator);
   list<String_imp>::iterator Tag = SubTag.begin();
   while(Tag != SubTag.end())
   {
    XML_Node SubChild = Root.firstGet(XML_Node::Element(XML_Search::Value,Tag->c_str()));
    if(SubChild.valid() == false)
    {
     SubChild = Root.lastAdd(XML_Data::NT_Element);
     SubChild.valueSet(Tag->c_str());
    }
    else
    {
    }
    Root = SubChild;
    ++ Tag;
   }
   XML_Node SubChild    = XML_Context.rootNode().firstGet(XML_Node::Element());
   XML_Node SubSubChild = SubChild.firstGet(XML_Node::Element());
   while(SubSubChild.valid() == true)
   {
    SubSubChild = SubChild.nodeCut(SubSubChild);
    Root.lastAdd(SubSubChild);
    SubSubChild = SubChild.firstGet(XML_Node::Element());
   }
  }
  else
  {
   // error-output no valid snipet-content
   cout << "no valid snipet content found to create an independent xml-tree" << endl;
   if(owner != NULL)
    cout << " in snipet: " << owner->getCallerPath() << endl;
  }
 }
 else
 {
  // error-output no valid snipet
   cout << "no valid snipet found to create an independent xml-tree" << endl;
   if(owner != NULL)
    cout << " in snipet: " << owner->getCallerPath() << endl;
 }
//cout<<__FILE__<<"|Cmnd_Dict_XML::xmlCreate|"<<"("<<__LINE__<<") leave"<<endl;
}



/* @MRTZ_describe xmlCopy

*/
void Cmnd_Dict_XML::xmlCopy(XML_Node                     source,
                            String_imp                   newName,
                            String_imp                   newPath,
                            String_imp                   tagName,
                            String_imp                   tagPath,
                            char                         separator,
                            map<String_imp, String_imp>* replacement,
                            SnippetExecution*            owner)
{
//cout<<__FILE__<<"|Cmnd_Dict_XML::xmlCopy|"<<"("<<__LINE__<<") enter"<<endl;

 _checkStack(&tagName,&tagPath,&separator,replacement);

#if defined(DEBUG_OUTPUT)
 cout << "xmlSnipet1 newName : " << newName << endl;
#endif //DEBUG_OUTPUT

 XML_Node ChildToCopy;
 if(  (tagName     != "")
    &&(tagName     != SELF)
   )
 {
  ChildToCopy = source.firstGet(XML_Node::Element(XML_Search::Value,tagName.c_str()));

  if(ChildToCopy.valid() == false)
  {
   cout << "sub-element of node("<< source.valueGet() <<") not found!" <<endl;
   if(owner != nullptr)
    cout << "  in snipet: " << owner->getCallerPath() << endl;
  }
  else if(tagPath != "")
  {
   ChildToCopy = ChildToCopy.firstGet(XML_Node::Element(XML_Search::Value,tagPath.c_str()));
   if(ChildToCopy.valid() == false)
   {
    cout << "sub-element of node("<<source.valueGet() << separator << tagName<<") not found!" <<endl;
    if(owner != nullptr)
     cout << "  in snipet: " << owner->getCallerPath() << endl;
   }
  }
  else
  {
  }
 }
 else if (tagName == SELF)
  ChildToCopy = source;
 else
  ChildToCopy.associationNodeSet(nullptr);

 if(ChildToCopy.valid() == true)
 {
  _checkStack(&newName,&newPath,&separator,replacement);

  XML_Node Root;
  if(Att_Dict.find(newName) == Att_Dict.end())
  {
//   Root = XML_Node(&XML_Context,XML_Context.focus_Fellow());
//   XML_Data* RootData = XML_Context.data_create();
//   RootData->valueSet(newName.c_str()) ;
//   RootData->typeSet(XML_Data::NT_Element);
//   Root = XML_Node(&XML_Context,RootData);
   Root = XML_Node(&XML_Context,XML_Data::NT_Element);
   Root.valueSet(newName.c_str());
   Att_Dict[newName] = Root;
  }
  else
  {
   Root = Att_Dict[newName];
  }

  list<String_imp>        SubTag = stringToList(newPath,separator);
  list<String_imp>::iterator Tag = SubTag.begin();
  while(Tag != SubTag.end())
  {
   XML_Node SubChild = Root.firstGet(XML_Node::Element(XML_Search::Value,Tag->c_str()));
   if(SubChild.valid() == false)
   {
    SubChild = Root.lastAdd(XML_Data::NT_Element);
    SubChild.valueSet(Tag->c_str());
   }
   else
   {
   }
   Root = SubChild;
   ++ Tag;
  }
//  Root.lastAdd(ChildToCopy);
  XML_Node NodeToAdd(Root.associationContextGet(), XML_Node::Prepare);
           NodeToAdd.cloneToOwnContext(ChildToCopy);
  Root.lastAdd(NodeToAdd);
 }
 else
 {
  cout << "no node to copy defined to create!" <<endl;
  if(owner != nullptr)
   cout << "  in snipet: " << owner->getCallerPath() << endl;
 }
//cout<<__FILE__<<"|Cmnd_Dict_XML::xmlCopy|"<<"("<<__LINE__<<") leave"<<endl;
}



/* @MRTZ_describe xmlCut

*/
void Cmnd_Dict_XML::xmlCut(XML_Node                     source,
                           String_imp                   newName,
                           String_imp                   newPath,
                           String_imp                   tagName,
                           String_imp                   tagPath,
                           char                         separator,
                           map<String_imp, String_imp>* replacement,
                           SnippetExecution*            owner)
{
//cout<<__FILE__<<"|Cmnd_Dict_XML::xmlCut|"<<"("<<__LINE__<<") enter"<<endl;

 _checkStack(&tagName,&tagPath,&separator,replacement);

 XML_Node ChildToCut;
 if(  (tagName     != ""  )
    &&(tagName     != SELF)
   )
 {
  ChildToCut = source.firstGet(XML_Node::Element(XML_Search::Value,tagName.c_str()));
  if(ChildToCut.valid() == false)// == nullptr)
  {
   cout << "sub-element of node("<< source.valueGet() <<") not found!" <<endl;
   if(owner != NULL)
    cout << "  in snipet: " << owner->getCallerPath() << endl;
  }
  else if(tagPath != "")
  {
   ChildToCut = ChildToCut.firstGet(XML_Node::Element(XML_Search::Value,tagPath.c_str()));
   if(ChildToCut.valid() == false)
   {
    cout << "sub-element of node("<<source.valueGet() << separator << tagName<<") not found!" <<endl;
    if(owner != NULL)
     cout << "  in snipet: " << owner->getCallerPath() << endl;
   }
  }
  else
  {
  }
 }
 else
  ChildToCut.associationNodeSet(nullptr);

 if(ChildToCut.valid() == true)
 {
  _checkStack(&newName,&newPath,&separator,replacement);

  XML_Node Root;
  if(Att_Dict.find(newName) == Att_Dict.end())
  {
   Root = XML_Node(&XML_Context,XML_Data::NT_Element);
   Root.valueSet(newName.c_str());
   Att_Dict[newName] = Root;
  }
  else
  {
   Root = Att_Dict[newName];
  }

  list<String_imp>        SubTag = stringToList(newPath,separator);
  list<String_imp>::iterator Tag = SubTag.begin();
  while(Tag != SubTag.end())
  {
   XML_Node SubChild = Root.firstGet(XML_Node::Element(XML_Search::Value,Tag->c_str()));
   if(SubChild.valid() == false)
   {
    SubChild = Root.lastAdd(XML_Data::NT_Element);
    SubChild.valueSet(Tag->c_str());
   }
   else
   {
   }
   Root = SubChild;
   ++ Tag;
  }
  ChildToCut = ChildToCut.preGet().nodeCut(ChildToCut);
  Root.lastAdd(ChildToCut);
 }
 else
 {
  cout << "no node to copy defined to create!" <<endl;
  if(owner != nullptr)
   cout << "  in snipet: " << owner->getCallerPath() << endl;
 }

//cout<<__FILE__<<"|Cmnd_Dict_XML::xmlCut|"<<"("<<__LINE__<<") leave"<<endl;
}





/* @MRTZ_describe xmlCode

*/
void Cmnd_Dict_XML::xmlCode(XML_Node                     source,
                            String_imp                   newName,
                            String_imp                   newPath,
                            String_imp                   tagName,
                            String_imp                   tagPath,
                            char                         separator,
                            map<String_imp, String_imp>* replacement,
                            SnippetExecution*            owner)
{
//cout<<__FILE__<<"|Cmnd_Dict_XML::xmlCode|"<<"("<<__LINE__<<") enter"<<endl;

 _checkStack(&tagName,&tagPath,&separator,replacement);

 XML_Node ChildToAnalyse;
 if(  (tagName     != ""  )
    &&(tagName     != SELF)
   )
 {
  ChildToAnalyse = source.firstGet(XML_Node::Element(XML_Search::Value,tagName.c_str()));
  if(ChildToAnalyse.valid() == false)// == nullptr)
  {
   cout << "sub-element of node("<< source.valueGet() <<") not found!" <<endl;
   if(owner != nullptr)
    cout << "  in snipet: " << owner->getCallerPath() << endl;
  }
  else if(tagPath != "")
  {
   ChildToAnalyse = ChildToAnalyse.firstGet(XML_Node::Element(XML_Search::Value,tagPath.c_str()));
   if(ChildToAnalyse.valid() == false)
   {
    cout << "sub-element of node("<<source.valueGet() << separator << tagName<<") not found!" <<endl;
    if(owner != nullptr)
     cout << "  in snipet: " << owner->getCallerPath() << endl;
   }
  }
  else
  {
  }
 }
 else if (tagName == SELF)
  ChildToAnalyse = source;
 else
  ChildToAnalyse.associationNodeSet(nullptr);

 if(ChildToAnalyse.valid() == true)
 {
  _checkStack(&newName,&newPath,&separator,replacement);
  XML_Node Root;

  if(Att_Dict.find(newName) == Att_Dict.end())
  {
   Root = XML_Node(&XML_Context,XML_Data::NT_Element);
   Root.valueSet(newName.c_str());

   Att_Dict[newName] = Root;
  }
  else
  {
   Root = Att_Dict[newName];
  }

  list<String_imp>        SubTag = stringToList(newPath,separator);
  list<String_imp>::iterator Tag = SubTag.begin();
  while(Tag != SubTag.end())
  {
   XML_Node SubChild = Root.firstGet(XML_Node::Element(XML_Search::Value,Tag->c_str()));
   if(SubChild.valid() == false)
   {
    SubChild = Root.lastAdd(XML_Data::NT_Element);
    SubChild.valueSet(Tag->c_str());
   }
   else
   {
   }
   Root = SubChild;
   ++ Tag;
  }
  XML_Node CodeFragments = _getCodeFragments(ChildToAnalyse);
  Root.lastAdd(CodeFragments);
 }
 else
 {
  cout << "no node to create a code-structure to create!" <<endl;
  if(owner != NULL)
   cout << "  in snipet: " << owner->getCallerPath() << endl;
 }
//cout<<__FILE__<<"|Cmnd_Dict_XML::xmlCode|"<<"("<<__LINE__<<") leave"<<endl;
}



/* @MRTZ_describe xmlInsert

*/
void Cmnd_Dict_XML::xmlInsert(XML_Node                     destination,
                              String_imp                   newName,
                              String_imp                   newPath,
                              const String_imp&            position,
                              char                         separator,
                              map<String_imp, String_imp>* replacement,
                              SnippetExecution*            owner)
{
#if defined(DEBUG_OUTPUT)
 cout << "Cmnd_Dict_XML::xmlInsert" << endl;
 cout << "newName  : " << newName   << endl;
 cout << "newPath  : " << newPath   << endl;
 cout << "position : " << position  << endl;
#endif //DEBUG_OUTPUT

 _checkStack(&newName,&newPath,&separator,replacement);


 if(Att_Dict.find(newName) != Att_Dict.end())
 {
  XML_Node      Root     = Att_Dict[newName];
  XML_Node      SubChild ;

  if (newPath != "")
  {
   SubChild = Root.firstGet(XML_Node::Element(XML_Search::Value,newPath.c_str()));
   if(SubChild.valid() == false)// == nullptr)
   {
     cout << "sub-element of node("<< newName <<") not found!" <<endl;
     if(owner != nullptr)
      cout << "  in snipet: " << owner->getCallerPath() << endl;
    }
  }
  else
   SubChild = Root;


  if(SubChild.valid() == true)
  {
   XML_Node NodeToAdd(destination.associationContextGet(), XML_Node::Prepare);
            NodeToAdd.cloneToOwnContext(SubChild);


   if     (position == "__BEFORE__")
   {
    destination.preGet().beforeAdd(destination, NodeToAdd);
   }
   else if(position == "__AFTER__")
   {
    destination.preGet().behindAdd(destination, NodeToAdd);
   }
   else if(position == "__FIRST__")
   {
    if(destination.firstGet(XML_Node::Element()).valid() == true)
    {
     XML_Node NodeBefore = destination.firstGet(XML_Node::Element());
     destination.beforeAdd(NodeBefore, NodeToAdd);
    }
    else
     destination.lastAdd(NodeToAdd);
   }
   else if(position == "__LAST__")
   {
    if(destination.lastGet(XML_Node::Element()).valid() == true)
    {
     XML_Node NodeBehind = destination.lastGet(XML_Node::Element());
     destination.behindAdd(NodeBehind,NodeToAdd);
    }
    else
     destination.lastAdd(NodeToAdd);
   }
   else // number that defines the position to insert in
   {
    int Number = stringToNumber(position);
    XML_Node Child = destination.firstGet(XML_Node::Element());
    while(  (Child.valid() == true)
          &&(Number > 0)
         )
    {
#if defined(DEBUG_OUTPUT)
     cout<< Number << endl;
#endif //DEBUG_OUTPUT
      -- Number;
     Child = Child.behindGet(XML_Node::Element());
    }
    if(Child.valid() == true)
    {
     destination.beforeAdd(Child,NodeToAdd);
    }
    else
    {
     destination.lastAdd(NodeToAdd);
    }
   }
  }
  else
  {
  // error-message ?
  }
 }
 else
 {
  // error-output independent xml not defined
   cout << "no independent xml-tree \"" << newName << separator << newPath << "\" defined" << endl;
   if(owner != NULL)
    cout << " in snipet: " << owner->getCallerPath() << endl;
 }
}








/* @MRTZ_describe xmlSnipet

*/
void Cmnd_Dict_XML::xmlSnipet(String_imp                    newName,
                              String_imp                    tagPath,
                              char                          separator,
//                              const String_imp&             tolerant,
                              map<String_imp , String_imp>* replacement,
                              list<String_imp>*             diagram,
                              SnippetExecution*             owner)
{
//cout<<__FILE__<<"|Cmnd_Dict_XML::xmlSnipet|"<<"("<<__LINE__<<") enter"<<endl;

 _checkStack(&newName,&tagPath,&separator,replacement);

#if defined(DEBUG_OUTPUT)
 cout << "xmlSnipet1 newName : " << newName << endl;
#endif //DEBUG_OUTPUT

 if(Att_Dict.find(newName) != Att_Dict.end())
 {
  XML_Node Root = Att_Dict[newName];
  XML_Node SubChild;
  if (tagPath != "")
  {
   SubChild = Root.firstGet(XML_Node::Element(XML_Search::Value,tagPath.c_str()));
   if(SubChild.valid() == false)
    {
     cout << "sub-element of node("<< newName <<") not found!" <<endl;
     if(owner != nullptr)
      cout << "  in snipet: " << owner->getCallerPath() << endl;
    }
  }
  else
  {
    SubChild = Root;
  }

  if(SubChild.valid() == true)
  {
   owner->snippet(SubChild,
                  SubChild.valueGet(),
                  replacement,diagram,
                  false);
  }
  else
  {
  // error-message ?
  }
 }
 else
 {
  // error-output independent xml not defined
   cout << " #####no independent xml-tree \"" << newName << separator << tagPath << "\" defined" << endl;
   if(owner != NULL)
    cout << " in snipet: " << owner->getCallerPath() << endl;
 }
//cout<<__FILE__<<"|Cmnd_Dict_XML::xmlSnipet|"<<"("<<__LINE__<<") leave"<<endl;
}


/* @MRTZ_describe xmlSave

*/
void Cmnd_Dict_XML::xmlSave(String_imp                   newName,
                            String_imp                   newPath,
                            char                         separator,
                            const String_imp&            fileName,
                            const String_imp&            filePath,

                            const String_imp&            usedPathSeparator,
                            const String_imp&            osPathSeparator,

                            map<String_imp, String_imp>* replacement,
                            SnippetExecution*            owner)
{
// cout<<__FILE__<<"|Cmnd_Dict_XML::xmlSave|"<<"("<<__LINE__<<") enter"<<endl;

 _checkStack(&newName,&newPath,&separator,replacement);

 if(Att_Dict.find(newName) != Att_Dict.end())
 {
  XML_Node Root     = Att_Dict[newName];
  XML_Node SubChild;

  if (newPath != "")
   SubChild = Root.firstGet(XML_Node::Element(XML_Search::Value,newPath.c_str()));
  else
    SubChild = Root;

  if(SubChild.valid() == true)
  {
   String_imp FileLocation = "";
   if(filePath != "")
    FileLocation = replacePartString(filePath + osPathSeparator + fileName,
                                     usedPathSeparator,osPathSeparator) ;
   else
    FileLocation = fileName;

   char* ParsedText = nullptr;    // xml-text
   SubChild.xmlText(&ParsedText);
   if(FileLocation != "")
   {
    ofstream  File(FileLocation.c_str(),ios_base::binary|ios_base::out);

    if(File.good()) // file successfully opened
    {
     File << ParsedText;
     File.close();
    }
   }
   delete[]ParsedText;
  }
  else
  {
  // error-message ?
   if(owner != nullptr)
    cout << "  in snipet: " << owner->getCallerPath() << endl;
  }
}
 else
 {
  // error-output independent xml not defined
   cout << "no independent xml-tree \"" << newPath << "\" defined"<< endl;
   if(owner != nullptr)
    cout << " in snipet: " << owner->getCallerPath() << endl;
 }
//cout<<__FILE__<<"|Cmnd_Dict_XML::xmlSave|"<<"("<<__LINE__<<") leave"<<endl;
}




/* @MRTZ_describe xmlDelete

*/
void Cmnd_Dict_XML::xmlDelete(String_imp                   newName,
                              String_imp                   newPath,
                              char                         separator,
                              map<String_imp, String_imp>* replacement,
                              SnippetExecution*            owner)
{
//cout<<__FILE__<<"|Cmnd_Dict_XML::xmlDelete|"<<"("<<__LINE__<<") enter"<<endl;
  _checkStack(&newName,&newPath,&separator,replacement);
#if defined(DEBUG_OUTPUT)
 cout << "1" << "xmlDelete"        << endl;
 cout << "2" << newName            << endl;
 cout << "3" << newPath            << endl;
#endif //DEBUG_OUTPUT

  XML_Node Root;
  if(Att_Dict.find(newName) == Att_Dict.end())
  {
//   Root = XML_Node(&XML_Context,XML_Context.focus_Fellow());
   Root = XML_Node(&XML_Context,XML_Data::NT_Element);
   Root.valueSet(newName.c_str());
   Att_Dict[newName] = Root;
  }
  else
  {
   Root = Att_Dict[newName];
  }

  list<String_imp>        SubTag = stringToList(newPath,separator);
  list<String_imp>::iterator Tag = SubTag.begin();
  while(Tag != SubTag.end())
  {
   XML_Node SubChild = Root.firstGet(XML_Node::Element(XML_Search::Value,Tag->c_str()));

   if(SubChild.valid() == true)
   {
    Root = SubChild;
    ++ Tag;
   }
   else
   {
    Root.associationNodeSet(nullptr);
    Tag = SubTag.end();
   }
  }

  if(Root.valid() == true)
  {
   if(Root.preGet().valid() == true)// only sub-tree should be erased
   {
    Root = Root.preGet().nodeCut(Root);
   }
   else // whole new xml-tree should be erased
   {
    Att_Dict.erase(newName);
   }
  }
  else
  {
   cout << "no node to delete \"" << newName << separator << newPath << "\" found !" << endl;
   if(owner != nullptr)
    cout << "  in snipet: " << owner->getCallerPath() << endl;
  }
//cout<<__FILE__<<"|Cmnd_Dict_XML::xmlDelete|"<<"("<<__LINE__<<") leave"<<endl;
}










/* @MRTZ_describe xmlPrint

*/
void Cmnd_Dict_XML::xmlPrint(XML_Node   source,
                             String_imp  prefix,
                             String_imp  tagName,
                             String_imp  tagPath,
                             String_imp  xmlProperty,
                             char        separator,
            map<String_imp, String_imp>* replacement,
                       SnippetExecution* owner)
{

#if defined(DEBUG_OUTPUT)
 cout << "Cmnd_Dict_XML::XmPrint" << endl;
 cout << "source      : " << source->ValueStr() << endl;
 cout << "prefix      : " << prefix    << endl;
 cout << "tagName     : " << tagName   << endl;
 cout << "tagPath     : " << tagPath   << endl;
 cout << "xmlProperty : |" << xmlProperty  << "|" << endl;
#endif //DEBUG_OUTPUT


 prefix = replacePartString(prefix,"\\\"","_@_@_@_@_@_");
 prefix = replacePartString(prefix,"\"","");
 prefix = replacePartString(prefix,"_@_@_@_@_@_","\\\"");
 prefix = replacePartString(prefix,"\\n","\n");
 prefix = replacePartString(prefix,"\\t","\t");

 cout << prefix;

 _checkStack(&tagName,&tagPath,&separator,replacement);

 XML_Node ChildToAnalyse;
 if((tagName != "") &&(tagName != SELF))
 {
  ChildToAnalyse = source.firstGet(XML_Node::Element(XML_Search::Value,tagName.c_str()));
  if(ChildToAnalyse.valid() == false)
  {
   cout << "sub-element of node("<< source.valueGet() <<") not found!" <<endl;
   if(owner != nullptr)
    cout << "  in snipet: " << owner->getCallerPath() << endl;
  }
  else if(tagPath != "")
  {
   ChildToAnalyse = ChildToAnalyse.firstGet(XML_Node::Element(XML_Search::Value,tagPath.c_str()));
   if(ChildToAnalyse.valid() == false)
   {
    cout << "sub-element of node("<<source.valueGet() << separator << tagName<<") not found!" <<endl;
    if(owner != nullptr)
     cout << "  in snipet: " << owner->getCallerPath() << endl;
   }
  }
  else
  {
  }
 }
 else if (tagName == SELF)
  ChildToAnalyse = source;
 else
  ChildToAnalyse.associationNodeSet(nullptr);


// @MRTZ_ifElseChain
 if(ChildToAnalyse.valid() == false)          // xml-path is not existing
 {
 }
 else if(xmlProperty == "")                   // xml node is existing
 {
  cout << ChildToAnalyse.valueGet();
 }
 else if(xmlProperty == "\"\"")               // check text content
 {
  String_imp Content = "";
  XML_Node   SubChild = ChildToAnalyse.firstGet(XML_Node::Text());
  while(SubChild.valid() == true)             // collect text
  {
   Content = Content + SubChild.valueGet();
   SubChild = SubChild.behindGet(XML_Node::Text());
  }
  cout << Content ;
 }
 else                                         // check attribute content
 {
  String_imp  Content = "";
  xmlProperty         = replacePartString(xmlProperty,"\"","");
  const char* Text    = ChildToAnalyse.attributeGet(xmlProperty.c_str());
  if(Text != NULL)
   Content = String_imp(Text);
  cout << Content ;
 }


}





/* @MRTZ_describe ifXmlEqual

*/
void Cmnd_Dict_XML::ifXmlEqual(XML_Node    source,
                               String_imp  tagName,
                               String_imp  tagPath,
                               String_imp  xmlProperty,
                               String_imp  refValue,
                               char        separator,
              map<String_imp, String_imp>* replacement,
                         SnippetExecution* owner,
                               bool*       result)
{

#if defined(DEBUG_OUTPUT)
 cout << "Cmnd_Dict_XML::ifXmlEqual" << endl;
 cout << "source      : " << source->ValueStr() << endl;
 cout << "tagName     : " << tagName   << endl;
 cout << "tagPath     : " << tagPath   << endl;
 cout << "xmlProperty : |" << xmlProperty  << "|" << endl;
 cout << "refValue    : |" << refValue     << "|" << endl;
#endif //DEBUG_OUTPUT

 refValue = replacePartString(refValue,"ifXmlEqual_","");
 refValue = replacePartString(refValue,"\"","");
 _checkStack(&tagName,&tagPath,&separator,replacement);


 XML_Node ChildToAnalyse;
 if((tagName != "") &&(tagName != SELF))
 {
  ChildToAnalyse = source.firstGet(XML_Node::Element(XML_Search::Value,tagName.c_str()));
  if(ChildToAnalyse.valid() == false)
  {
   cout << "sub-element of node("<< source.valueGet() <<") not found!" <<endl;
   if(owner != nullptr)
    cout << "  in snipet: " << owner->getCallerPath() << endl;
  }
  else if(tagPath != "")
  {
   ChildToAnalyse = ChildToAnalyse.firstGet(XML_Node::Element(XML_Search::Value,tagPath.c_str()));
   if((ChildToAnalyse.valid() == false) && (xmlProperty != "")/*&&(tolerant !="__TOLERANT__")*/)
   {
    cout << "sub-element of node("<<source.valueGet() << separator << tagName<<") not found!" <<endl;
    if(owner != nullptr)
     cout << "  in snipet: " << owner->getCallerPath() << endl;
   }
  }
  else
  {
  }
 }
 else if (tagName == SELF)
  ChildToAnalyse = source;
 else
  ChildToAnalyse.associationNodeSet(nullptr);

// @MRTZ_ifElseChain
 if(ChildToAnalyse.valid() == false)         // xml-path is not existing
 {
  (*result = false);
 }
 else if(xmlProperty == "")                  // xml node is existing
 {
  (*result = true);
 }
 else if(xmlProperty == "\"\"")              // check text content
 {
  String_imp Content = "";

  XML_Node SubChild = ChildToAnalyse.firstGet(XML_Node::Text());
  while(SubChild.valid() == true)           // collect text
  {
   Content = Content + SubChild.valueGet();
   SubChild = SubChild.behindGet(XML_Node::Text());
  }
  if(Content == refValue)
  {
   (*result = true);
  }
  else
  {
   (*result = false);
  }

 }
 else                                       // check attribute content
 {
  String_imp Content = "";
  xmlProperty = replacePartString(xmlProperty,"\"","");
  const char* Text = ChildToAnalyse.attributeGet(xmlProperty.c_str());
  if(Text != nullptr)
   Content = String_imp(Text);
  if(Content == refValue)
  {
   (*result = true);
  }
  else
  {
   (*result = false);
  }
 }
}


/* @MRTZ_describe ifXmlUnequal

*/
void Cmnd_Dict_XML::ifXmlUnequal(XML_Node    source,
                                 String_imp  tagName,
                                 String_imp  tagPath,
                                 String_imp  xmlProperty,
                                 String_imp  refValue,
                                 char        separator,
                map<String_imp, String_imp>* replacement,
                           SnippetExecution* owner,
                                 bool*       result)
{
#if defined(DEBUG_OUTPUT)
 cout << "Cmnd_Dict_XML::ifXmlUnequal" << endl;
 cout << "source      : " << source->ValueStr() << endl;
 cout << "tagName     : " << tagName   << endl;
 cout << "tagPath     : " << tagPath   << endl;
 cout << "xmlProperty : " << xmlProperty  << endl;
 cout << "refValue    : " << refValue  << endl;
#endif //DEBUG_OUTPUT

 refValue = replacePartString(refValue,"ifXmlUnequal_","");
 refValue = replacePartString(refValue,"\"","");
 _checkStack(&tagName,&tagPath,&separator,replacement);



 XML_Node ChildToAnalyse;
 if((tagName != "") &&(tagName != SELF))
 {
  ChildToAnalyse = source.firstGet(XML_Node::Element(XML_Search::Value,tagName.c_str()));
  if(ChildToAnalyse.valid() == false)
  {
   cout << "sub-element of node("<< source.valueGet() <<") not found!" <<endl;
   if(owner != nullptr)
    cout << "  in snipet: " << owner->getCallerPath() << endl;
  }
  else if(tagPath != "")
  {
   ChildToAnalyse = ChildToAnalyse.firstGet(XML_Node::Element(XML_Search::Value,tagPath.c_str()));
   if((ChildToAnalyse.valid() == false) && (xmlProperty != "")/*&&(tolerant !="__TOLERANT__")*/)
   {
    cout << "sub-element of node("<<source.valueGet() << separator << tagName<<") not found!" <<endl;
    if(owner != nullptr)
     cout << "  in snipet: " << owner->getCallerPath() << endl;
   }
  }
  else
  {
  }
 }
 else if (tagName == SELF)
  ChildToAnalyse = source;
 else
  ChildToAnalyse.associationNodeSet(nullptr);

// @MRTZ_ifElseChain
 if(ChildToAnalyse.valid() == false)   // xml-path is not existing
 {
  (*result = true);
 }
 else if(xmlProperty == "")            // xml node is existing
 {
  (*result = false);

 }
 else if(xmlProperty == "\"\"")        // check text content
 {
  String_imp Content = "";

  XML_Node SubChild = ChildToAnalyse.firstGet(XML_Node::Text());
  while(SubChild.valid() == true)      // collect text
  {
   Content = Content + SubChild.valueGet();
   SubChild = SubChild.behindGet(XML_Node::Text());
  }
  if(Content == refValue)
   (*result = false);
  else
   (*result = true);

 }
 else                                  // check attribute content
 {
  String_imp Content = "";
  xmlProperty = replacePartString(xmlProperty,"\"","");

  const char* Text = ChildToAnalyse.attributeGet(xmlProperty.c_str());
  if(Text != nullptr)
   Content = String_imp(Text);
  if(Content == refValue)
   (*result = false);
  else
   (*result = true);
 }


}





/* @MRTZ_describe ifXmlExisting

*/
void Cmnd_Dict_XML::ifXmlExisting(XML_Node    source,
                                  String_imp  tagName,
                                  String_imp  tagPath,
                                  String_imp  xmlProperty,
                                  char        separator,
                 map<String_imp, String_imp>* replacement,
//                            SnippetExecution* owner,
                                  bool*       result)
{

#if defined(DEBUG_OUTPUT)
 cout << "Cmnd_Dict_XML::ifXmlExisting" << endl;
 cout << "source      : " << source->ValueStr() << endl;
 cout << "tagName     : " << tagName   << endl;
 cout << "tagPath     : " << tagPath   << endl;
 cout << "xmlProperty : |" << xmlProperty  << "|" << endl;
#endif //DEBUG_OUTPUT

 _checkStack(&tagName,&tagPath,&separator,replacement);




 XML_Node ChildToAnalyse ;
 if((tagName != "") &&(tagName != SELF))
 {
  ChildToAnalyse = source.firstGet(XML_Node::Element(XML_Search::Value,tagName.c_str()));
  if(ChildToAnalyse.valid() == false)
  {
#if defined(DEBUG_OUTPUT)
   cout << "sub-element of node("<< source->valueGet() <<") not found!" <<endl;
   if(owner != NULL)
    cout << "  in snipet: " << owner->getCallerPath() << endl;
#endif //DEBUG_OUTPUT
  }
  else if(tagPath != "")
  {
   ChildToAnalyse = ChildToAnalyse.firstGet(XML_Node::Element(XML_Search::Value,tagPath.c_str()));
#if defined(DEBUG_OUTPUT)
   if((ChildToAnalyse.valid() == false)&&(xmlProperty != ""))
   {
    cout << "sub-element of node("<<source->valueGet() << separator << tagName<<") not found!" <<endl;
    if(owner != nullptr)
     cout << "  in snipet: " << owner->getCallerPath() << endl;
   }
#endif //DEBUG_OUTPUT
  }
  else
  {
  }
 }
 else if (tagName == SELF)
  ChildToAnalyse = source;
 else
  ChildToAnalyse.associationNodeSet(nullptr);

// @MRTZ_ifElseChain
 if(ChildToAnalyse.valid() == false)          // xml-path is not existing
 {
  (*result = false);
 }
 else if(xmlProperty == "")                   // xml node is existing
 {
  (*result = true);
 }
 else if(xmlProperty == "\"\"")               // check text content
 {
  (*result = false);

  XML_Node SubChild = ChildToAnalyse.firstGet(XML_Node::Text());
  if(SubChild.valid() == true)                // collect text
  {
  (*result = true);
  }
 }
 else                                         // check attribute content
 {
  xmlProperty = replacePartString(xmlProperty,"\"","");
  const char* Text = ChildToAnalyse.attributeGet(xmlProperty.c_str());
  if(Text != nullptr)
   (*result = true);
  else
   (*result = false);
 }
}


/* @MRTZ_describe ifXmlMissing

*/
void Cmnd_Dict_XML::ifXmlMissing(XML_Node    source,
                                 String_imp  tagName,
                                 String_imp  tagPath,
                                 String_imp  xmlProperty,
                                 char        separator,
                map<String_imp, String_imp>* replacement,
//                           SnippetExecution* owner,
                                 bool*       result)
{
#if defined(DEBUG_OUTPUT)
 cout << "Cmnd_Dict_XML::ifXmlMissing" << endl;
 cout << "source      : " << source->ValueStr() << endl;
 cout << "tagName     : " << tagName   << endl;
 cout << "tagPath     : " << tagPath   << endl;
 cout << "xmlProperty : |" << xmlProperty  << "|" << endl;
#endif //DEBUG_OUTPUT
 _checkStack(&tagName,&tagPath,&separator,replacement);

 XML_Node ChildToAnalyse;
 if((tagName != "") &&(tagName != SELF))
 {
  ChildToAnalyse = source.firstGet(XML_Node::Element(XML_Search::Value,tagName.c_str()));
  if(ChildToAnalyse.valid() == false)
  {
#if defined(DEBUG_OUTPUT)
   cout << "sub-element of node("<< source->valueGet() <<") not found!" <<endl;
   if(owner != nullptr)
    cout << "  in snipet: " << owner->getCallerPath() << endl;
#endif //DEBUG_OUTPUT
  }
  else if(tagPath != "")
  {
   ChildToAnalyse = ChildToAnalyse.firstGet(XML_Node::Element(XML_Search::Value,tagPath.c_str()));
#if defined(DEBUG_OUTPUT)
   if(  (ChildToAnalyse.valid() == false)
      &&(xmlProperty            != ""   )
     )
   {
    cout << "sub-element of node("<<source->valueGet() << separator << tagName<<") not found!" <<endl;
    if(owner != nullptr)
     cout << "  in snipet: " << owner->getCallerPath() << endl;
   }
#endif //DEBUG_OUTPUT
  }
  else
  {
  }
 }
 else if (tagName == SELF)
  ChildToAnalyse = source;
 else
  ChildToAnalyse.associationNodeSet(nullptr);

// @MRTZ_ifElseChain
 if(ChildToAnalyse.valid() == false)        // xml-path is not existing
 {
  (*result = true);
 }
 else if(xmlProperty == "")                 // xml node is existing
 {
  (*result = false);

 }
 else if(xmlProperty == "\"\"")             // check text content
 {
  (*result = true);
  XML_Node SubChild = ChildToAnalyse.firstGet(XML_Node::Text());
  if(SubChild.valid() == true)              // collect text
  {
    (*result = false);
  }
 }
 else                                       // check attribute content
 {
  xmlProperty = replacePartString(xmlProperty,"\"","");
  const char* Text = ChildToAnalyse.attributeGet(xmlProperty.c_str());
  if(Text != nullptr)
   (*result = false);
  else
   (*result = true);
 }
}




/* @MRTZ_describe _checkStack

*/
void Cmnd_Dict_XML::_checkStack(String_imp*                   leadName,
                                String_imp*                   path,
                                char*                         separator,
                                map<String_imp , String_imp>* replacement)
{
 struct
 {
  Cmnd_Stack_Strg Stack;
 }Cmnd;

 String_imp  NewName = Cmnd.Stack.exchange((*leadName),replacement);

 if(NewName != (*leadName))
 {
  (*separator) = Cmnd.Stack.exchange("__SEPARATOR__")[0];
  size_t SplitPos  = NewName.find(*separator);
  if(SplitPos < NewName.size())             // spliter found
   (*path)   = NewName.substr(SplitPos+ 1);
  else
   (*path)   = "";

  (*leadName)   = NewName.substr(0,SplitPos);
 }
 else
 {
  String_imp NewPath = Cmnd.Stack.exchange((*path),replacement);
  if(NewPath != (*path))
   (*separator) = Cmnd.Stack.exchange("__SEPARATOR__")[0];
  (*path) = NewPath;
 }
}




/* @MRTZ_describe _getCodeFragments

   @MRTZ_describe  iterate_over_lines

   @MRTZ_describe iterate_over_line_parts

   @MRTZ_describe build_code_lines

   @MRTZ_describe define_MinCol

*/
XML_Node Cmnd_Dict_XML::_getCodeFragments(XML_Node source, int minCol)
{
// cout<<__FILE__<<"|Cmnd_Dict_XML::_getCodeFragments|"<<"("<<__LINE__<<") enter"<<endl;
 XML_Node                            ReturnValue(&XML_Context,XML_Data::NT_Element);

 XML_Node CodeChild = XML_Node(source);

 if(CodeChild.valid() == true)// != NULL)
 {
  ReturnValue.valueSet("CODE");
  map<int, list<XML_Node> >  Lines;
  int                        MaxLineBuffer = 0;
  _getText(CodeChild, &Lines, &MaxLineBuffer);
  map<int, list<XML_Node> >::iterator Line = Lines.begin();
  list <int>                          Numbers;
  while(Line != Lines.end())
  {
   Numbers.push_back(Line->first);
   ++Line ;
  }
  Numbers.sort();
  int              LastNumber    = 1;
  list <int>::iterator Number = Numbers.begin();
// @MRTZ_exclude iterate_over_lines
  while(Number != Numbers.end())
  {
   while((LastNumber) < (*Number))
   {
    XML_Node CodeLine = ReturnValue.lastAdd(XML_Data::NT_Element);
             CodeLine.valueSet("EMPTYLINE");
             CodeLine.attributeSet("L", LastNumber);
             CodeLine.attributeSet("C", 1);

    XML_Node InnerCodeLine = CodeLine.lastAdd(XML_Data::NT_Element);
             InnerCodeLine.valueSet("EMPTYLINE");
             InnerCodeLine.attributeSet("L", LastNumber);
             InnerCodeLine.attributeSet("C", 1);
    ++ LastNumber;
   }
   LastNumber = (*Number) +1;

   XML_Node CodeLine = XML_Node(&XML_Context, XML_Data::NT_Element);
            CodeLine.valueSet("LINE");
            CodeLine.attributeSet("L", *Number);
            CodeLine.attributeSet("C", 1);

   list<XML_Node>           Fragments   = Lines[(*Number)];
   list<XML_Node>::iterator Fragment    = Fragments.begin();

// @MRTZ_exclude iterate_over_line_parts
   while(Fragment != Fragments.end())
   {
    int FragmentCol  = (*Fragment).attributeGet("C",0);
    XML_Node CodeFragment = CodeLine.lastGet(XML_Node::Element());
    if(CodeFragment.valid() == true)// != nullptr)
    {
     int CodeCol = CodeFragment.attributeGet("C",0);
     while(  (CodeCol                                             >  FragmentCol)
           &&(CodeFragment.valid()                                == true       )
           &&(CodeFragment.beforeGet(XML_Node::Element()).valid() == true       )
          )
     {
      CodeFragment = CodeFragment.beforeGet(XML_Node::Element());
      int CodeFragmentAttC = CodeFragment.attributeGet("C",0) ;
        CodeCol = CodeFragmentAttC;
     }
     if(CodeFragment.valid() == true)// != nullptr)
     {
      CodeLine.behindAdd(CodeFragment, *Fragment) ;
     }
     else
     {
      CodeFragment = CodeLine.firstGet(XML_Node::Element());
      CodeLine.beforeAdd(CodeFragment,*Fragment) ;
     }
    }
    else
    {
     CodeLine.lastAdd(*Fragment);
    }
    ++Fragment ;
   }
   _insertNewLines(ReturnValue, CodeLine);

   ++Number ;
 }

// @MRTZ_exclude build_code_lines
// @MRTZ_beginBlock

// @MRTZ_exclude define_MinCol
// @MRTZ_beginBlock
   XML_Node SortedLine = ReturnValue.firstGet(XML_Node::Element());
   while(  (SortedLine.valid()                               == true)
         &&(SortedLine.firstGet(XML_Node::Element()).valid() == true)
         &&(minCol                                           >  0   )
        )
   {
    int CodeCol = SortedLine.firstGet(XML_Node::Element()).attributeGet("C",0);
    if(minCol > CodeCol)
     minCol = CodeCol;
    SortedLine = SortedLine.behindGet(XML_Node::Element());
   }
// @MRTZ_endBlock
   SortedLine = ReturnValue.firstGet(XML_Node::Element());
   while(SortedLine.valid() == true)
   {
    SortedLine.attributeSet("C", minCol);

    XML_Node CodeFragment = SortedLine.firstGet(XML_Node::Element());
    int      CodeCol      = CodeFragment.attributeGet("C",0);
    for(int Collumn = minCol; Collumn < CodeCol; Collumn ++)
    {
     XML_Node NewNode = XML_Node(&XML_Context, XML_Data::NT_Element);
              NewNode = SortedLine.beforeAdd(CodeFragment, NewNode);
              NewNode.valueSet("SP");
              NewNode.attributeSet("L",CodeFragment.attributeGet("L"));
              NewNode.attributeSet("C",Collumn);
    }
    int   Collumn = 0;

    char* Text = nullptr;
    Text    = CodeFragment.textCollect(&Text);
    if(Text != NULL)
     Collumn = CodeCol + String_imp(Text).size();
    else
     Collumn = CodeCol;

    CodeFragment = CodeFragment.behindGet(XML_Node::Element());

    while(CodeFragment.valid() == true)
    {
     CodeCol = CodeFragment.attributeGet("C",0);
     while(Collumn < CodeCol)
     {
      XML_Node NewNode = XML_Node(&XML_Context, XML_Data::NT_Element);
               NewNode = SortedLine.beforeAdd(CodeFragment, NewNode);
               NewNode.valueSet("SP");
               NewNode.attributeSet("L",CodeFragment.attributeGet("L"));
               NewNode.attributeSet("C",Collumn);

      ++Collumn;
     }
     Text = CodeFragment.textCollect(&Text);
     if(Text != NULL)
      Collumn = CodeCol + String_imp(Text).size();
     else
      Collumn = CodeCol;

     CodeFragment = CodeFragment.behindGet(XML_Node::Element());
    }
    SortedLine = SortedLine.behindGet(XML_Node::Element());
   }
// @MRTZ_endBlock
 }
 else
 {
 }
// cout<<__FILE__<<"|Cmnd_Dict_XML::_getCodeFragments|"<<"("<<__LINE__<<") leave"<<endl;
 return(ReturnValue);
}


/* @MRTZ_describe _getText

   @MRTZ_describe save_text

*/
void Cmnd_Dict_XML::_getText(XML_Node                   source,
                             map<int, list<XML_Node> >* text,
                             int*                       maxNumber)
{
// static int CallCounter = 0;
// ++ CallCounter;
// cout<<__FILE__<<"|Cmnd_Dict_XML::_getText|"<<"("<<__LINE__<<")enter : " << CallCounter<<endl;

 if(source.valid() == true)// !=  nullptr)
 {
   String_imp    Text         = "";
   bool          CarierOfText = false;
   XML_Node      Child        = source.firstGet();
   while(Child.valid() == true)
   {
// @MRTZ_ifElseChain
    if     (Child.typeGet()== XML_Data::NT_Text)//child is leave
    {
     Text = Text + Child.valueGet();
     CarierOfText = true;
    }
    else if(Child.typeGet()== XML_Data::NT_Element)
    {
     if(  (Child.firstGet().valid() == false)
        &&(Child.lastGet() .valid() == false)
       )
     {
      XML_Node EmptyText = Child.lastAdd(XML_Data::NT_Text);
               EmptyText.valueSet("");
     }
     _getText(Child, text, maxNumber);
    }
    else
    {
     cout << "invalid type of xml-node found: " << (Child.valueGet());
    }
    Child = Child.behindGet();
   }
   if(CarierOfText == true)
   {
// @MRTZ_exclude save_text
// @MRTZ_beginBlock
    XML_Node Fragment = XML_Node(&XML_Context, XML_Data::NT_Element);
    Fragment.valueSet(source.valueGet());
    Fragment.attributeSet("L", source.attributeGet("L"));
    Fragment.attributeSet("C", source.attributeGet("C"));
//    int LineNumber = Fragment.attributeGet("L",0);
    if(source.attributeGet("new",nullptr) != nullptr)
    {
     Fragment.attributeSet("new", source.attributeGet("new"));
     if(Fragment.attributeGet("new",0) >=0 )
      Fragment.attributeSet("L", *maxNumber);
    }

    Text = replacePartString(Text,"\r","");
    Text = replacePartString(Text,"\n","");
    XML_Node Content = Fragment.lastAdd(XML_Data::NT_Text);
             Content.valueSet(Text.c_str());

    int LineNumber = Fragment.attributeGet("L",0);
    ((*text)[LineNumber]).push_back(Fragment);
    if((*maxNumber)<LineNumber)
     (*maxNumber) = LineNumber;
// @MRTZ_endBlock
   }
 }
 else
 {
  cout << "invalid xml-node found";
 }
// cout<<__FILE__<<"|Cmnd_Dict_XML::_getText|"<<"("<<__LINE__<<")leave : "<< CallCounter <<endl;
// -- CallCounter;
}


/* @MRTZ_describe _insertNewLines

*/
void Cmnd_Dict_XML::_insertNewLines(XML_Node destination, XML_Node source)
{
//cout<<__FILE__<<"|Cmnd_Dict_XML::_insertNewLines|"<<"("<<__LINE__<<") enter"<<endl;
 map<int, list<XML_Node> >           NewLines;
 XML_Node Fragment = source.firstGet(XML_Node::Element());
 while(Fragment.valid() == true)// != NULL)
 {
  if(Fragment.attributeGet("new",nullptr) != nullptr)
  {
   XML_Node FragmentToMove = Fragment;
   Fragment       = Fragment.behindGet(XML_Node::Element());
   FragmentToMove = source.nodeCut(FragmentToMove);//->ToElement();
   (NewLines[FragmentToMove.attributeGet("new",0)]).push_back(FragmentToMove);
  }
  else
  {
   Fragment = Fragment.behindGet(XML_Node::Element());
  }
 }
 destination.lastAdd(source);
 XML_Node InsertBefore = source;
 XML_Node InsertAfter  = source;

 map<int, list<XML_Node> >::iterator Line = NewLines.begin();
 while(Line != NewLines.end())
 {
  XML_Node NewLine = XML_Node(&XML_Context, XML_Data::NT_Element);
           NewLine.valueSet("LINE");

  list<XML_Node>::iterator  Part = (*Line).second.begin();
  while(Part != (*Line).second.end())
  {
   if(NewLine.attributeGet("L",nullptr) == nullptr)
   {
    NewLine.attributeSet("L",  (*Part).attributeGet("L"));
    NewLine.attributeSet("C",  (*Part).attributeGet("C"));
    NewLine.attributeSet("new",(*Part).attributeGet("new"));
   }
   NewLine.lastAdd(*Part);

   ++Part;
  }
  if((*Line).first >= 0) // insert behind line
  {
   destination.behindAdd(InsertAfter, NewLine);
   InsertAfter = *Part;
  }
  else                   // insert after line
  {
   destination.beforeAdd(InsertBefore, NewLine);
   InsertBefore = *Part;
  }
  ++ Line;
 }

//cout<<__FILE__<<"|Cmnd_Dict_XML::_insertNewLines|"<<"("<<__LINE__<<") leave"<<endl;
}




#ifndef DOXYGEN
//};};
#endif //DOXYGEN






