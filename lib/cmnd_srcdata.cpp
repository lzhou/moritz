/*!

 @file
 @brief  definition of a collection of snippet-commands to get data from an xml-part

 This file contains special snippet-commands used to to read ot data out of the current
 xml-tag to analyze

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
#include <fstream>
#include "StringC_help.h"


#include "app_tool.h"
#include "cmnd_stack_strg.h"

#include "cmnd_srcdata.h"



#ifndef DOXYGEN
//namespace CL_COMMAND {
//namespace CL_CMND_SRCDATA {
#endif //DOXYGEN

/* @MRTZ_describe Cmnd_SrcData

*/
Cmnd_SrcData::Cmnd_SrcData(void)
{
}





/* @MRTZ_describe ~Cmnd_SrcData

*/
Cmnd_SrcData::~Cmnd_SrcData(void)
{


}




/* @MRTZ_describe text

   @MRTZ_describe replacements

*/
void Cmnd_SrcData::text(XML_Node                       source,
                        map<String_imp , String_imp >* replacement,
                        list<String_imp>*              diagram)
{
 if(source.valid()== true)// != NULL)
 {
  {
   XML_Node Child = source.firstGet();
   while(Child.valid() == true)// != NULL)
   {
// @MRTZ_ifElseChain
    if     ((Child.typeGet())== XML_Data::NT_Text)
    {
     String_imp  Text = Child.valueGet();
                 Text =  replacmentUse(Text,replacement);
     diagram->push_back(Text);
    }
    else if((Child.typeGet())== XML_Data::NT_Element)
    {
     text(Child, replacement, diagram);
    }
    else
    {
     cout << "invalid type of xml-node found: " << (Child.valueGet());
    }
    Child = Child.behindGet();
   }
  }
 }
 else
 {
  cout << "invalid xml-node found";
 }
}


/* @MRTZ_describe tag

   @MRTZ_describe replacements

*/
void Cmnd_SrcData::tag(XML_Node                     source,
                       map<String_imp, String_imp>* replacement,
                       list<String_imp>*            diagram)
{
 if((source.typeGet())== XML_Data::NT_Element)
 {
  String_imp Text = source.valueGet();
             Text = replacmentUse(Text,replacement);
  diagram->push_back(Text);
 }
}


/* @MRTZ_describe attribute

   @MRTZ_describe replacements

*/
void Cmnd_SrcData::attribute(XML_Node                       source,
                             const String_imp&              attributeName,
                             map<String_imp , String_imp >* replacement,
                             list<String_imp>*              diagram)
{
 if((source.typeGet())== XML_Data::NT_Element)
 {
  String_imp Text = "";
  const char* TextPntr = source.attributeGet(attributeName.c_str());
  if(TextPntr != nullptr)
  {
   Text = String_imp(TextPntr);
  }
  Text =  replacmentUse(Text,replacement);
  diagram->push_back(Text);
 }

}



/* @MRTZ_describe drop

*/
void Cmnd_SrcData::drop(XML_Node  source)
{
 if(source.valid() == true)
 {
  XML_Node Parent = source.preGet();
  XML_Node Sister = source.behindGet();
           Parent.nodeCut(source);
  source = Sister;
 }
 else
 {
  cout << "invalid xml-node found";
 }
}


/* @MRTZ_describe ifAbsent

*/
void Cmnd_SrcData::ifAbsent(XML_Node                       source,
                            const String_imp&              startTag,
                            const String_imp&              alternative,
                            map<String_imp , String_imp >* replacement,
                            list<String_imp>*              diagram,
                            SnippetExecution*              owner)
{
 String_imp Alternative = replacePartString(alternative,"ifAbsent_","");

 bool NotFound = true;
 XML_Node Child = source.firstGet(XML_Node::Element());
 while(Child.valid() == true)// != nullptr)
 {
  if(STRINGS_ARE_EQUAL(Child.valueGet(),startTag.c_str())) //searched sub-tree exists
  {
   NotFound = false;
   break;
  }
  Child = Child.behindGet(XML_Node::Element());
 }
 if(NotFound == true) // searched sub-tree is not existing
 {
  owner->snippet(source, Alternative, replacement, diagram);
 }
}




/* @MRTZ_describe forAll

*/
void Cmnd_SrcData::forAll(XML_Node                       source,
                          const String_imp&              snipetName,
                          map<String_imp , String_imp >* replacement,
                          list<String_imp>*              diagram,
                          SnippetExecution*              owner)
{
 XML_Node Child = source.firstGet(XML_Node::Element());
 while(Child.valid() == true)// != nullptr)
 {
  owner->snippet(Child, snipetName, replacement, diagram);
  Child = Child.behindGet(XML_Node::Element());
 }
}



/* @MRTZ_describe statistic

*/
void Cmnd_SrcData::statistic(XML_Node          source,
                             const String_imp& tagToCount,
                             const String_imp& tagToSave)
{
 int Result = _count(source,tagToCount);

#if defined(DEBUG_OUTPUT)
  cout << "-statistic- "    << source->ValueStr()
       << "  tagToCount : " << tagToCount
       << "  tagToSave  : " << tagToSave
       << "  Result     : " << Result
       << endl;
#endif //DEBUG_OUTPUT

 XML_Node Statistic = source.firstGet(XML_Node::Element(XML_Search::Value,tagToSave.c_str()));

 if(Statistic.valid() == false)// == nullptr)
 {
  Statistic = source.lastAdd(XML_Data::NT_Element);
  Statistic.valueSet(tagToSave.c_str());
 }

 XML_Node NumberOff = Statistic.firstGet(XML_Node::Element(XML_Search::Value,"NumberOf"));
 while(                       (NumberOff.valid() == true                         )// != nullptr)
      && STRINGS_ARE_NOT_EQUAL(NumberOff.attributeGet("name"), tagToCount.c_str())
      )
 {
  NumberOff = NumberOff.behindGet(XML_Node::Element(XML_Search::Value,"NumberOf"));
 }

 if(  (NumberOff.valid() == false)// == nullptr)
    ||STRINGS_ARE_NOT_EQUAL(NumberOff.attributeGet("name"), tagToCount.c_str())
      )
 {
  NumberOff = Statistic.lastAdd(XML_Data::NT_Element);
  NumberOff.valueSet("NumberOff");
 }

 NumberOff.attributeSet("name",  tagToCount.c_str());
 NumberOff.attributeSet("value", numberToString(Result).c_str());

}


/* @MRTZ_describe ifOlderAs

*/
void Cmnd_SrcData::ifOlderAs(const String_imp& source,
                             const String_imp& dstFile,
                             const String_imp& dstPath,
                             const String_imp& usedPathSeparator,
                             const String_imp& osPathSeparator,
                             bool*             result)
{
 struct
 {
  Cmnd_Stack_Strg Stack;
 }Cmnd;

 list<String_imp>  Destination;
                   Destination.push_back(dstPath + Cmnd.Stack.exchange(dstFile));

 (*result) = checkNewSource(source,Destination,
                            usedPathSeparator,
                            osPathSeparator);
}




/* @MRTZ_describe ifNotExist

*/
void Cmnd_SrcData::ifNotExist(const String_imp& dstFile,
                              const String_imp& dstPath,
                              const String_imp& usedPathSeparator,
                              const String_imp& osPathSeparator,
                              bool*             result)

{
 struct
 {
  Cmnd_Stack_Strg Stack;
 }Cmnd;

 String_imp Destination = dstPath + Cmnd.Stack.exchange(dstFile);
 if(usedPathSeparator != osPathSeparator) //do it only if it has to be done
  Destination = replacePartString(Destination,usedPathSeparator,osPathSeparator);


 fstream  File((char*)Destination.c_str(),ios::binary|ios::in);
 if(File.good()) // source file successfully opened
 {
  (*result) = false;
   File.close();
 }
 else
 {
  (*result) = true;
 }
}




/* @MRTZ_describe _count

*/
int Cmnd_SrcData::_count(XML_Node          source,
                         const String_imp& tagToCount)
{
 int ReturnValue = 0;

 XML_Node Child = source.firstGet(XML_Node::Element());
 while(Child.valid() == true)// != nullptr)
 {
  ReturnValue =  ReturnValue + _count(Child,tagToCount);
  Child = Child.behindGet(XML_Node::Element());
 }

 if(STRINGS_ARE_EQUAL(source.valueGet(), tagToCount.c_str()))
 {
  ReturnValue = ReturnValue + 1;
 }
 return(ReturnValue);
}













#ifndef DOXYGEN
//};};
#endif //DOXYGEN


