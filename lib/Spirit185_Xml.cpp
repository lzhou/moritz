/*!

 @file
 @brief transfer a grammar tree into an xml-tree

 Copyright (C) 2018-2020 by Eckard Klotz.

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
    16.12.2018     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    16.12.2018...  @I Eckard Klotz
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

#include "StringC_help.h"
#include "Spirit185_Xml.h"


using namespace std;





Spirit185_Xml::Dflt_XML_String Spirit185_Xml::DfltXML;



/* @MRTZ_describe Spirit185_Xml

*/
Spirit185_Xml::Spirit185_Xml(void)
           :AssociationVisitor()
{
 Att.KeyWords      = nullptr;
 Att.KeyCharacters = nullptr;
 this->init(StoreMode_DF);

 char* IntMin = nullptr;
 AssociationData::itoa(&IntMin,INT_MIN);

 Spirit185_Xml::DfltXML.Tag               = "Tag";
 Spirit185_Xml::DfltXML.Attribute.Integer = IntMin;
 Spirit185_Xml::DfltXML.Attribute.Double  = "0.0";
 Spirit185_Xml::DfltXML.Attribute.String  = "__EMPTY__";
 Spirit185_Xml::DfltXML.String            = "__EMPTY__";

}



/* @MRTZ_describe Spirit185_Xml
  just call init
*/
Spirit185_Xml::Spirit185_Xml(Spirit185_Xml::StoreMode_TP mode)
              :AssociationVisitor()
{
 Att.KeyWords      = nullptr;
 Att.KeyCharacters = nullptr;
 this->init(mode);

 char* IntMin = nullptr;
 AssociationData::itoa(&IntMin,INT_MIN);

 Spirit185_Xml::DfltXML.Tag               = "Tag";
 Spirit185_Xml::DfltXML.Attribute.Integer = IntMin;
 Spirit185_Xml::DfltXML.Attribute.Double  = "0.0";
 Spirit185_Xml::DfltXML.Attribute.String  = "__EMPTY__";
 Spirit185_Xml::DfltXML.String            = "__EMPTY__";

}





/* @MRTZ_describe ~Spirit185_Xml

*/
Spirit185_Xml::~Spirit185_Xml(void)
{
// map<int,list<Template_TP* >*>::iterator Template;
// list<Template_TP* >::iterator           Detail;


 init(StoreMode_NV/*, nullptr*/);


}





/* @MRTZ_describe setSpcialTag

*/
void Spirit185_Xml::setSpcialTag(set<string>* keyWords, set<string>* keyCharacters)
{
 Att.KeyWords      = keyWords;
 Att.KeyCharacters = keyCharacters;
}








/* @MRTZ_describe init

*/
void Spirit185_Xml::init(Spirit185_Xml::StoreMode_TP mode)
{
 Att.CommonDirection = IterateAsBefore;
 Att.Mode            = mode;                    // set mode of store or restore
 Att.RootAssociation = nullptr;

 LOG_OUTPUT(LOG_OFF, "Spirit185_Xml::init");


 switch(Att.Mode)
 {
  case Spirit185_Xml::Content2XML :
  {
  }break;
  case Spirit185_Xml::StoreMode_NV:
  default :
  {
  }break;
 }
}



void Spirit185_Xml::contextModel_set(XML_DataModel* contextModel)
{
 Att.ContextModel = contextModel;
}






/* @MRTZ_ describe operator()

*/
Spirit185_Xml* Spirit185_Xml::operator()(Spirit185_Xml::StoreMode_TP mode, XML_Node* destination)
{

 LOG_OUTPUT(LOG_OFF, "Spirit185_Xml::operator()");

  TiPa_Visitor::init();
  this->init(mode);

  Att.DestinationRoot = destination->associationNodeGet();
  Att.ParentNode.push_front(Att.DestinationRoot);

  return(this);
}





/* @MRTZ_describe evaluate

*/
DirectionOfIteration Spirit185_Xml::evaluate(DataAssociation* node/*, DataAssociation* sponsor*/)
{
//   cout<<__FILE__<<"|Spirit185_Xml::evaluate|"<<"("<<__LINE__<<")enter "<<endl;
 LOG_OUTPUT(LOG_OFF, "Spirit185_Xml::evaluate");

 if(Att.CommonDirection != IterateAsBefore)           // direction was temporarily changed after previous evaluation
 {
  TiPa_Visitor::Att.Direction = Att.CommonDirection;  // restore direction to iterate
  Att.CommonDirection = IterateAsBefore;

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
    case Spirit185_Xml::Content2XML :
    {
     TiPa_Visitor::Att.Direction = evaluateXML(node/*,sponsor*/);
    }break;
    case Spirit185_Xml::StoreMode_NV:
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
    case Spirit185_Xml::Content2XML :
    {
     TiPa_Visitor::Att.Direction = evaluateXML(node/*,sponsor*/);
    }break;
    case Spirit185_Xml::StoreMode_NV:
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
//  TiPa_Visitor::Att.Direction = IterateNoMore;        // whole evaluation is not completed
 }
//   cout<<__FILE__<<"|Spirit185_Xml::evaluate|"<<"("<<__LINE__<<")leave "<<endl;
 return(TiPa_Visitor::Att.Direction);
}












/* @MRTZ_describe evaluateXML

*/
DirectionOfIteration Spirit185_Xml::evaluateXML(DataAssociation* node/*, DataAssociation* sponsor*/)
{
//   cout<<__FILE__<<"|Spirit185_Xml::evaluateXML|"<<"("<<__LINE__<<") enter"<<endl;

 LOG_OUTPUT(LOG_OFF, "Spirit185_Xml::evaluateNode");

 if(TiPa_Visitor::Att.Direction != IterateUpwards)                    // visit of next fellow or contractor to collect new data
 {
  XML_DataAssociation* NewNode = createElementXML(node);                             // construct current node  and add to top node of parent stack
  if(NewNode != nullptr)                                                                // node creation was successful
  {
   (*Att.ParentNode.begin())->contractorLast_add(NewNode);
   if((node->contractorFirst_get() == nullptr))                                         // create additional text-node
   {
    XML_DataAssociation* TextNode = createTextXML(node);                             // construct current node  and add to top node of parent stack
    if(TextNode != nullptr)                                                             // node creation was successful
    {
     NewNode->contractorLast_add(TextNode);
     XML_Data*   NodeData  = NewNode->data_get();
     XML_Data*   TextData  = TextNode->data_get();
     const char* Text      = TextData->valueGet();                                      // leaf-text that could be potential key-information
     if(  (Text != nullptr)
        &&(  (STRINGS_ARE_EQUAL(NodeData->valueGet(),"Str"))
           ||(STRINGS_ARE_EQUAL(NodeData->valueGet(),"Chr"))
          )
       )                                                                               // text is defined
     {
      if     (  (Att.KeyWords             != nullptr)
              &&(Att.KeyWords->find(Text) != Att.KeyWords->end())
              )                                                                         // text is defined as key-word
       NodeData->valueSet("Keyword");
      else if(  (Att.KeyCharacters             != nullptr)
              &&(Att.KeyCharacters->find(Text) != Att.KeyCharacters->end())
             )                                                                          // text is defined as key-character
       NodeData->valueSet("KeyChr");
      else                                                                              // no key-information
       {  /* keep own tag name */ }
     }
     else                                                                               // no text-content
     {  /* keep own tag name */ }
    }
    else
    { /*node not valid -> runtime-error*/ }
    TiPa_Visitor::Att.Direction = IterateForwards;                     // force visit of next fellow
   }
   else
   { /*no text-node to create*/ }
  }
  else
  { /*node not valid -> runtime-error*/  }


  if(node->contractorFirst_get()!=nullptr)                                              // node has a contractor
  {
   Att.ParentNode.push_front(NewNode);                                                  // insert position to insert-stack
   TiPa_Visitor::Att.Direction = IterateDownwards;                    // welcoming node should iteration over contractors
  }
  else if (node->fellowBehind_get()!=nullptr)                                           // node has no contractor but a next-fellow
  {
   TiPa_Visitor::Att.Direction = IterateForwards;                     // force visit of next fellow
  }
  else if(node != Att.RootAssociation)                                                  // node has no contractor and no next fellow and is not root of tree to evaluate
  {
   if(!(Att.ParentNode.empty()))                                                        // if parent stack is not empty
    Att.ParentNode.pop_front();                                                         // pop top of insert stack
   TiPa_Visitor::Att.Direction = IterateUpwards;                      // force visit to sponsor again
  }
  else                                                                                  // node has no contractor and no next fellow
  {
   Att.ParentNode.clear();                                                              // clear insert stack
   TiPa_Visitor::Att.Direction = IterateNoMore;                       // terminate visitation
  }

 }
 else                                                                                   // return to sponsor that data is already collected
 {
  if (node->fellowBehind_get()!=nullptr)                                                //node has no contractor but a next-fellow
  {
   TiPa_Visitor::Att.Direction = IterateForwards;                     //force visit to sponsor again
  }
  else if(node != Att.RootAssociation)                                                  // node has no contractor and no next fellow and is not root of tree to evaluate
  {
   if(!(Att.ParentNode.empty()))
    Att.ParentNode.pop_front();                                                         // pop top of insert stack
   TiPa_Visitor::Att.Direction = IterateUpwards;                      // force visit to sponsor again
  }
  else                                                                                  // node has no contractor and no next fellow
  {
   Att.ParentNode.clear();                                                              // clear insert stack
   TiPa_Visitor::Att.Direction = IterateNoMore;                       // terminate visitation
  }
 }


 if(TiPa_Visitor::Att.Direction != IterateNoMore)
 {
  TiPa_Visitor::Att.Node      = node;                                // store root node
  TiPa_Visitor::Att.Data      = node->data_get();                    // store root-node data
 }
//   cout<<__FILE__<<"|Spirit185_Xml::evaluateXML|"<<"("<<__LINE__<<") leave"<<endl;
 return(TiPa_Visitor::Att.Direction);
}




/* @MRTZ_describe createElementXML

*/
Spirit185_Xml::XML_DataAssociation* Spirit185_Xml::createElementXML(DataAssociation* node)
{
 XML_DataAssociation* ReturnValue = nullptr;
// cout<<__FILE__<<"|Spirit185_Xml::createElementXML|"<<"("<<__LINE__<<") enter"<<endl;

 if(  (node             != nullptr)
    &&(node->data_get() != nullptr)
   )                                              // node is valid and contains valid data
 {
  TiPa_Data* SourceData      = node->data_get();
  XML_Data*  DestinationData = Att.ContextModel->data_create();
  DestinationData->typeSet(XML_Data::NT_Element);

  DestinationData->valueSet(SourceData->userName_get());

  DestinationData->attributeSet("L",SourceData->lineGet());
  DestinationData->attributeSet("C",SourceData->columnGet());

  ReturnValue = Att.ContextModel->fellow_create();
  ReturnValue->data_set(DestinationData);

  list<AssociationData::SecondaryData_TP*>* Dictionary = SourceData->secondaryData_get();
  list<AssociationData::SecondaryData_TP*>::iterator Attribute = Dictionary->begin();

  while(Attribute != Dictionary->end())
  {
   if(SourceData->isRealSecondaryData((*Attribute)->Val) == true)
   {
    char*  Key  = nullptr;                                      // attribute-name
    AssociationData::string2xml((char*)(*Attribute)->Key,&Key); // store name of attribute

    char* Val = nullptr;                                        // attribute-value
    AssociationData::string2xml((char*)(*Attribute)->Val,&Val); // store value of attribute

    DestinationData->attributeSet(Key,Val);
    delete[](Val);
    delete[](Key);
   }
   else
   {
    // nothing to do
   }
   ++Attribute;
  }
 }
// cout<<__FILE__<<"|Spirit185_Xml::createElementXML|"<<"("<<__LINE__<<") leave"<<endl;
 return(ReturnValue);
}

//   if(Att.Template.find(Spirit185_Xml::XML_Text)     == Att.Template.end())
//      Att.Template[Spirit185_Xml::XML_Text]
//         = stringTemplate("$Content$");


/* @MRTZ_describe createTextXML

*/
Spirit185_Xml::XML_DataAssociation* Spirit185_Xml::createTextXML(DataAssociation* node)
{

// cout<<__FILE__<<"|Spirit185_Xml::createTextXML|"<<"("<<__LINE__<<") enter"<<endl;

 XML_DataAssociation* ReturnValue = nullptr;

 if(  (node             != nullptr)
    &&(node->data_get() != nullptr)
   )                                                        // node is valid and contains valid data
 {
  TiPa_Data* SourceData      = node->data_get();
  XML_Data*  DestinationData = Att.ContextModel->data_create();
  DestinationData->typeSet(XML_Data::NT_Text);

  DestinationData->valueSet(SourceData->getContent());      // use directly the content


  ReturnValue = Att.ContextModel->fellow_create();          // new xml-node
  ReturnValue->data_set(DestinationData);                   // over give found data
 }
 return(ReturnValue);

//  cout<<__FILE__<<"|Spirit185_Xml::createTextXML|"<<"("<<__LINE__<<") leave"<<endl;
}
