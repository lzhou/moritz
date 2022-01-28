/*!

 @file
 @brief concrete visitor to search for a tree-node defined by an index-path

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
    16.12.2015     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    16.12.2015...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/


#define DEBUG_OUTPUT_LOG
#include "LogOutput.h"





#include <stdio.h>
#include <cstdlib>
#include <set>
#include <sstream>

#include <limits.h>

#include "Spirit185_Store.h"


using namespace std;


#ifndef DOXYGEN
//namespace TXTDIASM {
//namespace TDA_TinyParser {
//namespace DATA {
#endif //DOXYGEN



Spirit185_Store::Dflt_XML_String Spirit185_Store::DfltXML;



/* @MRTZ_describe Spirit185_Store

*/
Spirit185_Store::Spirit185_Store(void)
                :AssociationVisitor()
{
 Att.KeyWords      = nullptr;
 Att.KeyCharacters = nullptr;
 this->init(StoreMode_DF, nullptr);

 char* IntMin = nullptr;
 AssociationData::itoa(&IntMin,INT_MIN);

 Spirit185_Store::DfltXML.Tag               = "Tag";
 Spirit185_Store::DfltXML.Attribute.Integer = IntMin;
 Spirit185_Store::DfltXML.Attribute.Double  = "0.0";
 Spirit185_Store::DfltXML.Attribute.String  = "__EMPTY__";
 Spirit185_Store::DfltXML.String            = "__EMPTY__";

}



/* @MRTZ_describe Spirit185_Store
  just call init
*/
Spirit185_Store::Spirit185_Store(Spirit185_Store::StoreMode_TP mode, char** text)
            :AssociationVisitor()
{
 Att.KeyWords      = nullptr;
 Att.KeyCharacters = nullptr;
 this->init(mode, text);

 char* IntMin = nullptr;
 AssociationData::itoa(&IntMin,INT_MIN);

 Spirit185_Store::DfltXML.Tag               = "Tag";
 Spirit185_Store::DfltXML.Attribute.Integer = IntMin;
 Spirit185_Store::DfltXML.Attribute.Double  = "0.0";
 Spirit185_Store::DfltXML.Attribute.String  = "__EMPTY__";
 Spirit185_Store::DfltXML.String            = "__EMPTY__";

}





/* @MRTZ_describe ~Spirit185_Store

*/
Spirit185_Store::~Spirit185_Store(void)
{
 map<int,list<Template_TP* >*>::iterator Template;
 list<Template_TP* >::iterator           Detail;


 init(StoreMode_NV, nullptr);

 for(Template = Att.Template.begin();Template != Att.Template.end();++ Template)
 {
  for(Detail = (Template->second)->begin();Detail != (Template->second)->end();++ Detail)
  {
   delete[]((*Detail)->RawText);
  }
  (Template->second)->clear();
 }
 Att.Template.clear();

 set<const char*> ExistingString;        // to collect the really occupied memory fragments
 list<const char*>::iterator String;     // single element of output-text
 for(  String  = Att.OutputText.begin();
       String != Att.OutputText.end();
     ++String)                           //iterate over output-text that is reusing some memory-content several times
 {
  ExistingString.insert(*String);        // collect all used string-pointers while ignoring several occurrence
 }
 Att.OutputText.clear();


}





/* @MRTZ_describe setSpcialTag

*/
void Spirit185_Store::setSpcialTag(set<string>* keyWords, set<string>* keyCharacters)
{
 Att.KeyWords      = keyWords;
 Att.KeyCharacters = keyCharacters;
}


/* @MRTZ_describe xmlTemplate_set

*/
void Spirit185_Store::xmlTemplate_set(XML_TemplateKind templateID, const char* newContent)
{
 Att.Template[templateID] = stringTemplate(newContent);
}







/* @MRTZ_describe init

*/
void Spirit185_Store::init(Spirit185_Store::StoreMode_TP mode, char** text)
{
 Att.CommonDirection = IterateAsBefore;
 Att.Mode            = mode;                    // set mode of store or restore
 Att.Text            = text;                    // file to work with
 Att.Indention       = 2;
 Att.RootAssociation = nullptr;

 LOG_OUTPUT(LOG_OFF, "Spirit185_Store::init");


 set<const char*> ExistingString;               // to collect the really occupied memory fragments
 list<const char*>::iterator String;            // single element of output-text
 for(String = Att.OutputText.begin();String != Att.OutputText.end();++String)
                                                // iterate over output-text that is reusing some memory-content several times
 {
  ExistingString.insert(*String);               // collect all used string-pointers while ignoring several occurrence
 }
 Att.OutputText.clear();


 while(!(ExistingString.empty()))               //iterate over the occupied memory-locations
 {
  if(*(ExistingString.begin()) != nullptr)      //nothing to delete
  {
   delete[](*(ExistingString.begin()));         //free occupied memory
  }
  ExistingString.erase(ExistingString.begin()); //next string
 }


 Att.EvaluationSequence.clear();

 switch(Att.Mode)
 {
  case Spirit185_Store::Content2XML :
  {
   if(Att.Template.find(Spirit185_Store::XML_StartTag) == Att.Template.end())
      Att.Template[Spirit185_Store::XML_StartTag]
         = stringTemplate("<$UserName$ L=\"$Line$\" C=\"$Column$\"$SecondaryData$>");// splitter between tag-name and attribute will be added while attribute creation
   if(Att.Template.find(Spirit185_Store::XML_EndTag)   == Att.Template.end())
      Att.Template[Spirit185_Store::XML_EndTag]
         = stringTemplate("</$UserName$>\n");
   if(Att.Template.find(Spirit185_Store::XML_LeafTag)  == Att.Template.end())
      Att.Template[Spirit185_Store::XML_LeafTag]
         = stringTemplate("<$UserName$ L=\"$Line$\" C=\"$Column$\"$SecondaryData$ />");// splitter between tag-name and attribute will be added while attribute creation
   if(Att.Template.find(Spirit185_Store::XML_Text)     == Att.Template.end())
      Att.Template[Spirit185_Store::XML_Text]
         = stringTemplate("$Content$");

   Att.EvaluationSequence.push_back(Spirit185_Store::Indent_Tag);
   Att.EvaluationSequence.push_back(Spirit185_Store::XML_StartTag);
   //Att.EvaluationSequence.push_back(Spirit185_Store::Indent_Tag);
   Att.EvaluationSequence.push_back(Spirit185_Store::XML_Text);

   Att.EvaluationSequence.push_back(Spirit185_Store::Indent_Text);

   Att.EvaluationSequence.push_back(Spirit185_Store::Indent_Child);
   Att.EvaluationSequence.push_back(Spirit185_Store::XML_EndTag);
  }break;
  case Spirit185_Store::Content2Text :
  {
  }break;
  default :
  {
  }break;
 }
}





/* @MRTZ_ describe operator()

*/
Spirit185_Store* Spirit185_Store::operator()(Spirit185_Store::StoreMode_TP mode, char** text)
{

 LOG_OUTPUT(LOG_OFF, "Spirit185_Store::operator()");

  TiPa_Visitor::init();
  this->init(mode, text);

  return(this);
}





/* @MRTZ_describe evaluate

*/
DirectionOfIteration Spirit185_Store::evaluate(DataAssociation* node/*, DataAssociation* sponsor*/)
{
//   cout<<__FILE__<<"|Spirit185_Store::evaluate|"<<"("<<__LINE__<<") enter"<<endl;
 LOG_OUTPUT(LOG_OFF, "Spirit185_Store::evaluate");

 if(Att.CommonDirection != IterateAsBefore)                             //direction was temporarily changed after previous evaluation
 {
  TiPa_Visitor::Att.Direction = Att.CommonDirection;  // restore direction to iterate
  Att.CommonDirection                           = IterateAsBefore;

 }
 else
 {
 }

 if(  (Att.RootAssociation                           == nullptr)
    &&(TiPa_Visitor::Att.Direction != IterateNoMore)
   )
 {
  Att.RootAssociation = node;
  if(  (node                        != nullptr)
     &&(node->data_get()            != nullptr)
    )
  {
   switch(Att.Mode)
   {
    case Spirit185_Store::Content2XML :
    {
     TiPa_Visitor::Att.Direction = evaluateXML(node/*,sponsor*/);
    }break;
    case Spirit185_Store::Content2Text :
    {
     TiPa_Visitor::Att.Direction = evaluateText(node/*,sponsor*/);
    }break;
    default :
    {
    }break;
   }
  }
  else if(node->contractorFirst_get() == nullptr)
  {
   TiPa_Visitor::Att.Direction = IterateNoMore;        // whole evaluation completed before it starts
  }
 }
 else if(  (Att.RootAssociation                           != node)
         &&(node                                          != nullptr)
         &&(node->data_get()                              != nullptr)
         &&(TiPa_Visitor::Att.Direction != IterateNoMore)
        )
 {
   switch(Att.Mode)
   {
    case Spirit185_Store::Content2XML :
    {
     TiPa_Visitor::Att.Direction = evaluateXML(node/*,sponsor*/);
    }break;
    case Spirit185_Store::Content2Text :
    {
     TiPa_Visitor::Att.Direction = evaluateText(node/*,sponsor*/);
    }break;
    default :
    {
    }break;
   }
 }
 else
 {
  TiPa_Visitor::Att.Direction = IterateNoMore;         // whole evaluation completed before it starts
 }

 if(TiPa_Visitor::Att.Direction == IterateNoMore)
 {
  list<const char*>::iterator String;
  stringstream Text;

  TiPa_Visitor::Att.Direction = IterateNoMore;        // whole evaluation is not completed

//  Text << "<Content L=\"1\" C=\"1\">\n";
  for(String = Att.OutputText.begin(); String != Att.OutputText.end(); ++String)
  {
   Text << (*String);                                                   // store the collected text content into a text-stream
  }
//  Text << "</Content>";

  (*Att.Text) = new char[Text.str().size() + 1];
  memcpy((*Att.Text),Text.str().c_str(),Text.str().size());
  (*Att.Text)[Text.str().size()] = 0;

 }
//   cout<<__FILE__<<"|Spirit185_Store::evaluate|"<<"("<<__LINE__<<") leave"<<endl;
 return(TiPa_Visitor::Att.Direction);
}















/* @MRTZ_describe evaluateXML

*/
DirectionOfIteration Spirit185_Store::evaluateXML(DataAssociation* node)
{
 list<const char*>::iterator  InsertPosition;
 list<const char*>::iterator  ChildInsertsBefore;
 list<int>::iterator          Step;
 char*                        Text         = nullptr;





 LOG_OUTPUT(LOG_OFF, "Spirit185_Store::evaluateNode");


 if(TiPa_Visitor::Att.Direction != IterateUpwards)                                      // visit of next fellow or contractor to collect new data
 {
  char*  Indention         = new char[Att.Indention+1];
  memset(Indention,' ',Att.Indention);
  Indention[Att.Indention] = 0;
  bool IndentionUsed       = false;

  char* EndOfLine = new char[3];
  memset(EndOfLine,0,3);
  strcpy(EndOfLine,"\n");
  bool EndOfLineUsed   = false;

  bool MultiLineText   = false;

  if(Att.InsertPosition.empty())
  {
   InsertPosition = Att.OutputText.end();
  }
  else
  {
   InsertPosition = *(Att.InsertPosition.begin());
  }

  for(Step = Att.EvaluationSequence.begin();Step != Att.EvaluationSequence.end();++Step)
  {
   switch(*Step)
   {
    case Spirit185_Store::Indent_Tag:
    {
     Att.OutputText.insert(InsertPosition,Indention);                                   // store indention tag (start or end)
     IndentionUsed = true;                                                              // set flag to avoid delete of Indention

    }break;

    case Spirit185_Store::Indent_Text:
    {
     if(  (node->contractorFirst_get() == nullptr)
        &&(MultiLineText               == true) )                                       // only for leaf-nodes and text with line-brake
     {
      Att.OutputText.insert(InsertPosition,Indention);                                  // store indention tag (start or end)
      IndentionUsed = true;                                                             // set flag to avoid delete of Indention
     }

    }break;
    case Spirit185_Store::Indent_Child:
    {
     if(node->contractorFirst_get() != nullptr)
     {
                           Att.OutputText.insert(InsertPosition,EndOfLine);             // store indention tag (start or end)
      EndOfLineUsed = true;                                                             // set flag to avoid delete of Indention
      ChildInsertsBefore = Att.OutputText.insert(InsertPosition,Indention);             // store indention tag (start or end)
      IndentionUsed = true;                                                             // set flag to avoid delete of Indention
     }

                                                                                        // and store insert position

    }break;

    default :
    {
     if( ((*Step)>=0)
        &&(  (*Step                       != Spirit185_Store::XML_Text)
           ||(node->contractorFirst_get() == nullptr)
          )                                                                             // no special step and text-output only for leaf-nodes
       )
     {
      Text = nullptr;                                                                   // clear text-pointer
      stringRepresentation(node->data_get(), Att.Template[(*Step)], &Text);             // get data-representation
      Att.OutputText.insert(InsertPosition,Text);                                       // store data-representation

      if(  (strchr(Text,10) != nullptr)
         ||(strchr(Text,13) != nullptr)
        )                                                                               // text contains carriage return or line-feed
       MultiLineText = true;
      else
       MultiLineText = false;
     }
     else
     {
     }
    }break;
   }
  }

                                                                                        //and store insert-position of contractor node

  if(node->contractorFirst_get()!=nullptr)                                              // node has a contractor
  {
   Att.InsertPosition.push_front(ChildInsertsBefore);                                   // insert position to insert-stack
   TiPa_Visitor::Att.Direction = IterateDownwards;                                      // welcoming node should iteration over contractors
   Att.Indention = Att.Indention + 2;
  }
  else if (node->fellowBehind_get()!=nullptr)                                           // node has no contractor but a next-fellow
  {
   TiPa_Visitor::Att.Direction = IterateForwards;                                       // force visit of next fellow
  }
  else if(node != Att.RootAssociation)                                                  // node has no contractor and no next fellow and is not root of tree to evaluate
  {
   if(!(Att.InsertPosition.empty()))
    Att.InsertPosition.pop_front();                                                     // pop top of insert stack
   TiPa_Visitor::Att.Direction = IterateUpwards;                                        // force visit to sponsor again
   if( Att.Indention >= 2)
    Att.Indention = Att.Indention - 2;
  }
  else                                                                                  // node has no contractor and no next fellow
  {
   Att.InsertPosition.clear();                                                          // clear insert stack
   TiPa_Visitor::Att.Direction = IterateNoMore;                                         // terminate visitation
   if( Att.Indention >= 2)
    Att.Indention = Att.Indention - 2;
  }

  if(IndentionUsed == false)                                                            // string was not used
   delete[](Indention);                                                                 // free memory

  if(EndOfLineUsed == false)                                                            // string was not used
   delete[](EndOfLine);                                                                 // free memory
 }
 else                                                                                   // return to sponsor that data is already collected
 {
  if (node->fellowBehind_get()!=nullptr)                                                //node has no contractor but a next-fellow
  {
   TiPa_Visitor::Att.Direction = IterateForwards;                                       //force visit to sponsor again
  }
  else if(node != Att.RootAssociation)                                                  // node has no contractor and no next fellow and is not root of tree to evaluate
  {
   if(!(Att.InsertPosition.empty()))
    Att.InsertPosition.pop_front();                                                     // pop top of insert stack
   TiPa_Visitor::Att.Direction = IterateUpwards;                                        // force visit to sponsor again
   if( Att.Indention >= 2)
    Att.Indention = Att.Indention - 2;
  }
  else                                                                                  // node has no contractor and no next fellow
  {
   Att.InsertPosition.clear();                                                          // clear insert stack
   TiPa_Visitor::Att.Direction = IterateNoMore;                                         // terminate visitation
   if( Att.Indention >= 2)
    Att.Indention = Att.Indention - 2;
  }
 }


 if(TiPa_Visitor::Att.Direction != IterateNoMore)
 {
  TiPa_Visitor::Att.Node      = node;                                                   // store root node
  TiPa_Visitor::Att.Data      = node->data_get();                                       // store root-node data
 }


 return(TiPa_Visitor::Att.Direction);
}



/* @MRTZ_describe evaluateText

*/
DirectionOfIteration Spirit185_Store::evaluateText(DATA_ASSOCIATION_UNUSED* node)
{
 DirectionOfIteration ReturnValue = IterateAsBefore;

 return(ReturnValue);
}









/* @MRTZ_describe stringTemplate

*/
list<Spirit185_Store::Template_TP* >* Spirit185_Store::stringTemplate(const char* text, char separator)
{

 list<Template_TP* >* ReturnValue  = new list<Template_TP* >;
// Template_TP*         Detail;

// const char*               Character = nullptr;      // iterator through given text
// const char*               TextEnd   = nullptr;      // end of given text
// char*                     Word      = nullptr ;     // part of given text that describes a detail


 const char* WordBegin = nullptr;                    // begin of the current detail in given text
 const char* Character = text;                       // iteration start

 if((*Character)== separator)                        // text starts with non raw-text part framed completely with separators
  ++Character;                                       // jump over very first separator at begin of text

 const char* TextEnd   = text+(strlen(text)-1);      // iteration end
 while(Character<=TextEnd)                           // iteration over given text
 {
  WordBegin = Character;                             // begin of text-part to analyse next
  ++Character;                                       // jump over normal text-character that is not a separator
  while(  (*Character != separator)
        &&( Character <= TextEnd)
       )                                             // iteration over text part
  {
   ++Character;                                      // jump over normal text-character that is not a separator
  }
  char* Word = new char[Character-WordBegin+1];      // prepare a copy of the found text-part
  memcpy(Word,WordBegin,Character-WordBegin);        // copy part
  Word[Character-WordBegin]=0;                       // terminate part
  Template_TP* Detail = new Template_TP;             // prepare storing element
               Detail->RawText = Word;               // store found part
               Detail->Data    = dataID_get(Word);   // store association-data attribute identifier or raw-text key
  ReturnValue->push_back(Detail);                    // add to template

  ++Character;                                       // jump over separator
 }

 return(ReturnValue);                                // return the new template
}




/* @MRTZ_describe stringRepresentation
    collect single data and assemble it
   @MRTZ_describe create_representation_list
    use the template to create a list of single part-strings where each represents a single association-data attribute
   @MRTZ_describe create_output_text
    assemble all part strings to the output-string
*/
void Spirit185_Store::stringRepresentation(TiPa_Data* data,  list<Template_TP* >* textTemplate, char** text)
{
// @MRTZ_exclude create_representation_list
// @MRTZ_beginBlock
 list<Template_TP* >::iterator Detail;                              // template for one
                                                                    // association-data attribute
 list<const char*>             Representations;                     // representation of all
                                                                    // association-data attribute
 char*                         Text0            = nullptr;          // association-data attribute as text
 unsigned int                  WriteSize        = 0;                // size of output string

 Detail = textTemplate->begin();
 while(Detail != textTemplate->end())                               // iterate over template
 {
  switch((*Detail)->Data)
// use the detail data id in a switch to choose the action that creates the associated text part
// !!!refer the method dataID_get to learn what id is associated with what association-data attribute!!!
  {
   case Spirit185_Store::DataID_NV://-1:                            // identifies a raw-text detail
   {
    Representations.push_back((*Detail)->RawText);                  // store template content
   }break;
   case Spirit185_Store::Parser://1:                                // parser that creates this data
   {
    Text0 = nullptr;                                                // decouple previous content
    //Text0 = (char*)typeString();                                  // textual description
    AssociationData::string2xml((char*)data->typeString(),&Text0);
    Representations.push_back(Text0);                               // store part-string
   }break;
   case Spirit185_Store::Type://2:                                  // parser-type id
   {
    Text0 = nullptr;                                                // decouple previous content
    TiPa_Data::itoa(&Text0,data->ParserClass);                      // convert number to digit-string
    Representations.push_back(Text0);                               // store part-string
   }break;
   case Spirit185_Store::SubType://3:                               // sub-parser type id
   {
    Text0 = nullptr;                                                // decouple previous content
    AssociationData::itoa(&Text0,data->Parser->id_SubType());
                                                                    // convert number to digit-string
    Representations.push_back(Text0);                               // store part-string
   }break;
   case Spirit185_Store::UserID://4:                                // user defined parser id
   {
    Text0 = nullptr;                                                // decouple previous content
    AssociationData::itoa(&Text0,data->UserID);                     // convert number to digit-string
    Representations.push_back(Text0);                               // store part-string
   }break;
   case Spirit185_Store::Content://5:                               // the detected text-part
   {
    const char* Text = data->getContent();                          // evaluate attributes Begin and End

    char* TextXML = nullptr;
    AssociationData::string2xml(Text,&TextXML);


    Representations.push_back(TextXML);                             // store part-string
   }break;


   case Spirit185_Store::Line://6:
   {
    Text0 = nullptr;                                                // decouple previous content
    AssociationData::string2xml((char*)data->lineGet(),&Text0);
    if(  (Text0         != nullptr)
       &&(strlen(Text0) > 0)
      )                                                             // content found
     Representations.push_back(Text0);                              // store part-string
    else                                                            // no content
    {
     Representations.push_back(Spirit185_Store::DfltXML.Attribute.Integer);
    }
                                                                    // store default-string
   }break;
   case Spirit185_Store::Column://7:
   {
    Text0 = nullptr;                                                // decouple previous content
    AssociationData::string2xml((char*)data->columnGet(),&Text0);
    if(  (Text0         != nullptr)
       &&(strlen(Text0) > 0)
      )                                                             // content found
     Representations.push_back(Text0);                              // store part-string
    else                                                            // no content
    {
     Representations.push_back(Spirit185_Store::DfltXML.Attribute.Integer);
    }

   }break;
   case Spirit185_Store::Description://9:
   {
    Text0 = nullptr;                                                // decouple previous content
    AssociationData::string2xml((char*)data->userDescription_get(),&Text0);
    Representations.push_back(Text0);                               // store part-string

   }break;

   case Spirit185_Store::UserName://10:                             // grammar associated properties of the detecting parses
   {
    Text0  = nullptr;                                               // decouple previous content for attribute identifier
    if(  (data->ParserClass == TiPa_Abstract::TDA_TiPa_String)
       ||(data->ParserClass == TiPa_Abstract::TDA_TiPa_Character)
      )
                                                                    // parser-name of a string- or character-parser
    {


     char* TextXML = nullptr;

     const char* DataContent = data->getContent();                  //  get parser-result

     if     (  (Att.KeyWords                != nullptr)
             &&(Att.KeyWords->find(DataContent) != Att.KeyWords->end())
            ) //parser-result is defined as key-word
     {
      char Tag_KeyWord[8] = "Keyword";
      AssociationData::string2xml(Tag_KeyWord,&TextXML);
     }
     else if(  (Att.KeyCharacters                != nullptr)
             &&(Att.KeyCharacters->find(DataContent) != Att.KeyCharacters->end())
            )//parser-result is defined as key-character
     {
      char Tag_KeyChar[8] = "KeyChr";
      AssociationData::string2xml(Tag_KeyChar,&TextXML);            // parser-result is not specified
     }
     else
      AssociationData::string2xml(data->userName_get(),&TextXML);
     Representations.push_back(TextXML);                            // store attribute identifier
    }
    else if(data->userName_get() != nullptr)                        // even number and valid data
    {
     char* TextXML = nullptr;

     AssociationData::string2xml(data->userName_get(),&TextXML);
     Representations.push_back(TextXML);                            // store attribute identifier
    }
    else                                                            // data not valid
    {
      // nothing to do
     char* TextXML = (char*)Spirit185_Store::DfltXML.Tag;
     Representations.push_back(TextXML);                            // store attribute identifier
    }
   }break;

   case Spirit185_Store::SecondaryData://11:                        // secondary data
   {
    list<AssociationData::SecondaryData_TP*>* Dictionary = data->secondaryData_get();

#ifdef SORT_SECONDARY_DATA
    list<char*>::iterator Attribute = data->Keys.begin();

    cout << "-------Size------" << data->Keys.size() << " / " <<  Dictionary->size() << endl;
#else
    list<AssociationData::SecondaryData_TP*>::iterator Attribute = Dictionary->begin();
#endif

#ifdef SORT_SECONDARY_DATA
    while(Attribute != data->Keys.end())
#else
    while(Attribute != Dictionary->end())
#endif
    {
#ifdef SORT_SECONDARY_DATA
 //     cout << *Attribute << " = " << (*Dictionary)[*Attribute] << endl;
     if(  (Dictionary->find(*Attribute)                         != Dictionary->end())
        &&(data->isRealSecondaryData((*Dictionary)[*Attribute]) == true             )
       )
#else
     if(data->isRealSecondaryData((*Attribute)->Val) == true)
#endif
     {
      Representations.push_back(" ");                               // splitter to tag-name or attribute before
      WriteSize = WriteSize + 1;

      Text0 = nullptr;                                              // decouple previous content
#ifdef SORT_SECONDARY_DATA
      AssociationData::string2xml((char*)(*Attribute),&Text0);      // store name of attribute
#else
      AssociationData::string2xml((char*)(*Attribute)->Key,&Text0); // store name of attribute
#endif
      Representations.push_back(Text0);
      WriteSize = WriteSize + strlen(Text0);

      Representations.push_back("=\"");
      WriteSize = WriteSize + 2;

      Text0 = nullptr;                                              // decouple previous content
#ifdef SORT_SECONDARY_DATA
      AssociationData::string2xml((*Dictionary)[*Attribute],&Text0);// store value of attribute
#else
      AssociationData::string2xml((char*)(*Attribute)->Val,&Text0);// store value of attribute
#endif
      Representations.push_back(Text0);
      WriteSize = WriteSize + strlen(Text0);
      Representations.push_back("\"");
      WriteSize = WriteSize + 1;
     }
     else
     {
      // nothing to do
     }
     ++Attribute;
    }
   }break;


   default:
   {
     char* TextXML = nullptr;
     Representations.push_back(TextXML);                           // store attribute value

   }break;
  }

  if(*(Representations.rbegin())!=nullptr)                         // representation contains a valid string
   WriteSize = WriteSize + strlen(*(Representations.rbegin()));    // calculate size of text to output

  ++ Detail;                                                       // next template detail
 }

 if((*text)== nullptr)                                             // given text is empty
  (*text) = new char[WriteSize +1];                                // prepare memory
 else if (WriteSize > strlen(*text))                               // given text seems to be not empty but is to small
  WriteSize = strlen(*text);                                       // reduce output size
 else                                                              // given text seems to be not empty and big enough
 { /* do nothing*/  }
// @MRTZ_endBlock


// @MRTZ_exclude create_output_text
// @MRTZ_beginBlock
// list<const char*>::iterator Representation;                       // representation of one association-data attribute

// char*                       WriteEnd  = nullptr;                  // points behind of output-string
// char*                       Write     = nullptr;                  // current write-position


 char*       Write = *text;                                        // initialize write-position
 char*       WriteEnd = (*text) + WriteSize;                       // directly behind end of valid write-memory
 const char* ReadEnd   = nullptr;                                  // end of part string to copy in output string
 const char* Read      = nullptr;                                  // current read position

 for(list<const char*>::iterator   Representation =  Representations.begin();
                                   Representation != Representations.end();
                                ++ Representation
    )                                                              // iterate over Representations to create output text
 {
  if(*Representation!=nullptr)                                     // representation contains a valid string
  {
   ReadEnd = (*Representation) + strlen(*Representation);
                                                                   // directly  behind string to read
   for(Read = (*Representation); Read < ReadEnd; ++Read)
   {                                                               // iterate over string to read
    if(Write < WriteEnd)                                           // end of output text is not reached
    {
     (*Write) = (*Read);                                           // copy character into output text
      ++ Write;                                                    // increment write-position
    }
   }
  }
 }
 (*Write) = 0;                                                     // terminate output-string
// @MRTZ_endBlock
}


/* @MRTZ_describe dataID_get


*/
int Spirit185_Store::dataID_get(const char* text)
{
 int ReturnValue;// = Spirit185_Store::DataID_NV;//-1;
 if     (strstr(text,"ParserAttribute" ) == text)            // grammar associated properties of the detecting parses
 {
  ReturnValue =  Spirit185_Store::UserName/*10*/
               + atoi(text+strlen("ParserAttribute"))*2;     // vector-index for Identifier
  if(strstr(text,"Value") != nullptr)
    ++ReturnValue;                                           // vector-index for value
 }
 else if(strstr(text, "Parser")  == text)                    // parser that creates this data
  ReturnValue = Spirit185_Store::Parser;//1;
 else if(strstr(text, "Type")    == text)                    // parser-type id
  ReturnValue = Type;//2;
 else if(strstr(text, "SubType") == text)                    // sub parser-type id
  ReturnValue = Spirit185_Store::SubType;//3;
 else if(strstr(text, "UserID")  == text)                    // user defined parser id
  ReturnValue = Spirit185_Store::UserID;//4;
 else if(strstr(text, "Content") == text)                    // the detected text-part
  ReturnValue = Spirit185_Store::Content;//5;
 else if(strstr(text, "Line") == text)                       // the detected text-part
  ReturnValue = Spirit185_Store::Line;//6;
 else if(strstr(text, "Column") == text)                     // the detected text-part
  ReturnValue = Spirit185_Store::Column;//7;
 else if(strstr(text, "Description") == text)                // the detected text-part
  ReturnValue = Spirit185_Store::Description;//9;
 else if(strstr(text, "UserName") == text)                   // the detected text-part
  ReturnValue = Spirit185_Store::UserName;//10;
 else if(strstr(text, "SecondaryData") == text)              // the detected text-part
  ReturnValue = Spirit185_Store::SecondaryData;//11;
 else                                                        // association data attribute not known
                                                             // or the use in a string template is not supported
  ReturnValue = Spirit185_Store::DataID_NV;//-1;             // identifies a raw-text detail

 return(ReturnValue);
}







#ifndef DOXYGEN
#define USING_NAMESPACE using namespace
//}; USING_NAMESPACE DATA;
//}; USING_NAMESPACE TDA_TinyParser;
//}; USING_NAMESPACE TXTDIASM;
#undef  USING_NAMESPACE
#endif //DOXYGEN



