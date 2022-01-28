/*!
 @file
 @brief concrete association visitor to find replacements in xml-data that should
        be expanded

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
    29.12.2018     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    29.12.2018...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/

#include "xml_Replace.h"
#include "StringC_help.h"



/* @MRTZ_describe XML_Replace

*/
XML_Replace::XML_Replace(void)
         :AssociationVisitor(),
          Att()
{
 this->init();
}


/* @MRTZ_describe operator=

*/
XML_Replace::XML_Replace(const XML_Replace& visitor)
            :Att(visitor.Att)
{
 AssociationVisitor::Att.Node        = visitor.AssociationVisitor::Att.Node;
 AssociationVisitor::Att.Data        = visitor.AssociationVisitor::Att.Data;
 AssociationVisitor::Att.Direction   = visitor.AssociationVisitor::Att.Direction;

// Att.CommonDirection = visitor.Att.CommonDirection;
// Att.RootAssociation = visitor.Att.RootAssociation;
// Att.Context         = visitor.Att.Context;
// Att.Search          = visitor.Att.Search;
}




/* @MRTZ_describe ~XML_Replace

*/
XML_Replace::~XML_Replace(void)
{
 init();
}


/* @MRTZ_describe operator=

*/
XML_Replace& XML_Replace::operator= (const XML_Replace& visitor)
{
 AssociationVisitor::Att.Node        = visitor.AssociationVisitor::Att.Node     ;
 AssociationVisitor::Att.Data        = visitor.AssociationVisitor::Att.Data;
 AssociationVisitor::Att.Direction   = visitor.AssociationVisitor::Att.Direction;

 Att.CommonDirection = visitor.Att.CommonDirection;
 Att.RootAssociation = visitor.Att.RootAssociation;
 Att.Context         = visitor.Att.Context;
 Att.Search          = visitor.Att.Search;
 return(*this);
}



/* @MRTZ_describe operator()

*/
XML_Replace* XML_Replace::operator()(XML_Node::DataModel* context)
{
 XML_Visitor::init();
 this->init();

 Att.Context = context;
 return(this);
}



/* @MRTZ_describe evaluate

*/
DirectionOfIteration XML_Replace::evaluate(DataAssociation* node)
{
 if(Att.CommonDirection != IterateAsBefore)          // direction was temporarily changed after previous evaluation
 {
  XML_Visitor::Att.Direction = Att.CommonDirection;  // restore direction to iterate
  Att.CommonDirection        = IterateAsBefore;
 }
 else
 {
 }

 if(  (Att.RootAssociation        == nullptr)
    &&(XML_Visitor::Att.Direction != IterateNoMore)
   )
 {
  Att.RootAssociation = node;
  if(  (node                        != nullptr)
     &&(node->data_get()            != nullptr)
     &&(node->data_get()->typeGet() != XML_Data::NT_Comment)
     &&(node->data_get()->typeGet() != XML_Data::NT_Document)
     &&(node->data_get()->typeGet() != XML_Data::NT_Undefined)
    )
  {
   XML_Visitor::Att.Direction = evaluateXML(node);
  }
 }
 else if(  (Att.RootAssociation                           != node)
         &&(node                                          != nullptr)
         &&(node->data_get()                              != nullptr)
         &&(XML_Visitor::Att.Direction != IterateNoMore)
        )
 {
  XML_Visitor::Att.Direction = evaluateXML(node);
 }
 else
 {
   XML_Visitor::Att.Direction = IterateNoMore;        // whole evaluation is not completed
 }

 return(XML_Visitor::Att.Direction);
}








DirectionOfIteration XML_Replace::evaluateXML(DataAssociation* node)
{
 LOG_OUTPUT(LOG_OFF, "XML_Replace::evaluateNode");

 if(XML_Visitor::Att.Direction != IterateUpwards)                                            // visit of next fellow or contractor to collect new data
 {
  switch(node->data_get()->typeGet())
  {
   case XML_Data::NT_Element:
   {
    replaceInAttributes(node);
   }break;

   case XML_Data::NT_Text:
   {
    replaceInText(node);
   }break;

   case XML_Data::NT_Comment:
   case XML_Data::NT_Declaration:
   case XML_Data::NT_Document:
   case XML_Data::NT_Undefined:
   default :
   {
   }break;
  }

  if(node->contractorFirst_get()      != nullptr)                                            // node has a contractor
  {
   XML_Visitor::Att.Direction = IterateDownwards;                                            // welcoming node should iteration over contractors
  }
  else if(  (node->fellowBehind_get() != nullptr)
          &&(node                     != Att.RootAssociation)
         )                                                                                   // node has a next-fellow but is not root of tree to evaluate
  {
   XML_Visitor::Att.Direction = IterateForwards;                                             // force visit of next fellow
  }
  else if(node                        != Att.RootAssociation)                                // node has no contractor and no next fellow and is not root of tree to evaluate
  {
   XML_Visitor::Att.Direction = IterateUpwards;                                              // force visit to sponsor again
  }
  else                                                                                       // node has no contractor and no next fellow and is root of tree to evaluate
  {
   XML_Visitor::Att.Direction = IterateNoMore;                                               // terminate visitation
  }

 }
 else                                                                                        // return to sponsor that data is already collected
 {
  if(  (node->fellowBehind_get() != nullptr)
     &&(node                     != Att.RootAssociation)
    )                                                                                        // node has a next-fellow but is not root of tree to evaluate
  {
   XML_Visitor::Att.Direction = IterateForwards;                                             // force visit to sponsor again
  }
  else if(node                   != Att.RootAssociation)                                     // node has no contractor and no next fellow and is not root of tree to evaluate
  {
   XML_Visitor::Att.Direction = IterateUpwards;                                              // force visit to sponsor again
  }
  else                                                                                       // node has no contractor and no next fellow and is root of tree to evaluate
  {
   XML_Visitor::Att.Direction = IterateNoMore;                                               // terminate visitation
  }
 }

 if(XML_Visitor::Att.Direction != IterateNoMore)
 {
  XML_Visitor::Att.Node      = node;                                                         // store root node
  XML_Visitor::Att.Data      = node->data_get();                                             // store root-node data
 }

 return(XML_Visitor::Att.Direction);
}






/* @MRTZ_describe init

void XML_Replace::init(char** text)
*/
void XML_Replace::init(void)
{
 Att.CommonDirection = IterateAsBefore;
 Att.RootAssociation = nullptr;


}


/* @MRTZ_describe replaceInAttributes

*/
void XML_Replace::replaceInAttributes(DataAssociation* node)
{
 if(node != nullptr)
 {
  XML_Data*  Data = node->data_get();
  list<AssociationData::SecondaryData_TP*>* Attributes = Data->secondaryData_get();
  list<AssociationData::SecondaryData_TP*>::iterator Attribute = Attributes->begin();
  while(Attribute != Attributes->end())
  {
//   cout << string("  ") << (*Attribute)->Key << " : " << (*Attribute)->Val << endl;
   char* NewText  = nullptr;
   XML_Node Node(Att.Context, node->as_AssociationFellowship());
//   cout << "replaceInAttributes : " << (*Attribute)->Val << endl;
   replaceDetails(&NewText, (*Attribute)->Val, Node);
   if(NewText != nullptr)
   {
    Data->attributeSet((*Attribute)->Key,NewText);
    delete[](NewText);
   }
   else
   {
    /// @todo define error reaction
   }
   ++Attribute;
  }
 }
}

/* @MRTZ_describe replaceInText

*/
void XML_Replace::replaceInText(DataAssociation* node)
{
 if(node != nullptr)
 {
  XML_Data*                                 Data = node->data_get();

  char* NewText  = nullptr;
  TiPa_Concrete::DataModel ReplaceContext;

  XML_Node Node(Att.Context, node->as_AssociationFellowship());

//  cout << "replaceInText : " << Data->valueGet() << endl;

  replaceDetails(&NewText, Data->valueGet(), Node);

  if(NewText != nullptr)
  {
   Data->valueSet(NewText);
   delete[](NewText);
  }
  else
  {
   /// @todo define error reaction
  }
 }
}

#include "Spirit185_Store.h"


/* @MRTZ_describe replaceDetails

*/
void XML_Replace::replaceDetails(char** returnValue, const char* text, XML_Node currentNode)
{
//cout<<__FILE__<<"|XML_Replace::replaceDetails|"<<"("<<__LINE__<<") enter"<<endl;
 TiPa_Concrete::DataModel ReplaceContext;

 TiPa_Concrete::DataAssociation*  TextTree = parseText(text, &ReplaceContext);
 if(TextTree != nullptr)
 {

//
//   Spirit185_Store                  Store;
//   char* TextXML = nullptr;
//   TextTree->welcome(Store(Spirit185_Store::Content2XML,&TextXML),IterateDownwards);
//   cout << endl << TextXML << endl;
//   delete[]TextXML;
//


  list<const char*> NewTextDetail;                            // collects content used as new text
  unsigned int      NewTextSize = collectNewTextParts(&NewTextDetail, TextTree, currentNode);
                                                              // collect new content
                                  assembleNewTextParts(returnValue, &NewTextDetail, NewTextSize);
                                                              // create the new text used to replace
//  if((*returnValue) != nullptr)
//   cout << "returnValue : " << (*returnValue) << endl;
//  else
//   cout << "returnValue : nullptr" <<  endl;
  list<const char*>::iterator ReplacementPart = NewTextDetail.begin();
  while(ReplacementPart != NewTextDetail.end())               // iterate over whole content
  {
   if(*ReplacementPart != nullptr)                            // valid part content
   {
    delete[](*ReplacementPart);                               // free memory of content-part in collection
   }
   ++ ReplacementPart;                                        // next content-part
  }
 }

 ReplaceContext.init();
//cout<<__FILE__<<"|XML_Replace::replaceDetails|"<<"("<<__LINE__<<") leave"<<endl;
}







/* @MRTZ_describe parseText

*/
TiPa_Concrete::DataAssociation* XML_Replace::parseText(const char* text, TiPa_Concrete::DataModel* replaceContext)
{
//cout<<__FILE__<<"|XML_Replace::parseText|"<<"("<<__LINE__<<") enter"<<endl;
// TiPa_Concrete::DataAssociation* ReturnValue;

 XML_Replace_Grm ReplaceGrammar(replaceContext);
 ReplaceGrammar.parse(text, text + strlen(text));

 TiPa_Concrete::DataFellow* TextTree = ReplaceGrammar.treeData(text);

 TiPa_Concrete::DataAssociation* ReturnValue = ReplaceGrammar.filter_simple(TextTree);
 //ReplaceGrammar.TDA_GrmConcrete::init();
//cout<<__FILE__<<"|XML_Replace::parseText|"<<"("<<__LINE__<<") leave"<<endl;
 return(ReturnValue);
}




/* @MRTZ_describe replaceDetails

*/
unsigned int XML_Replace::collectNewTextParts(list<const char*>*              returnValue,
                                              TiPa_Concrete::DataAssociation* replacementDefinition,
                                              XML_Node                        currentNode)
{
//cout<<__FILE__<<"|XML_Replace::collectNewTextParts|"<<"("<<__LINE__<<") enter"<<endl;
 unsigned int      NewTextSize = 0;

 if(replacementDefinition != nullptr)
 {
  TiPa_Concrete::DataAssociation* DetailText = replacementDefinition->contractorFirst_get();
  while(DetailText != nullptr)
  {
   TiPa_Data* DetailData = DetailText->data_get();
   if(DetailData != nullptr)
   {
    if(STRINGS_ARE_EQUAL(DetailData->userName_get(),"RawText"))
    {
//     cout << "RawText : " << DetailData->getContent() << endl;
     const char* RawContent = DetailData->getContent();
           char* RawText    = new char[strlen(RawContent) + 1];
     memcpy(RawText, RawContent, strlen(RawContent));
     RawText[strlen(RawContent)] = 0;

     returnValue->push_back(RawText);
     NewTextSize = NewTextSize + strlen(RawText);
    }
    else
    {
     char* ReplacementText = nullptr;
     replacementGet(&ReplacementText,DetailText,currentNode);
     if(ReplacementText != nullptr)
     {
//      cout << "Replacement : " << ReplacementText << endl;
      returnValue->push_back(ReplacementText);
      NewTextSize = NewTextSize + strlen(ReplacementText);
     }
     else
     {
//      cout << "Replacement : not valid" << endl;
      /// @todo define error reaction
     }
    }
   }
   DetailText = DetailText->fellowBehind_get();
  }
 }
//cout<<__FILE__<<"|XML_Replace::collectNewTextParts|"<<"("<<__LINE__<<") leave"<<endl;
 return(NewTextSize);
}



/* @MRTZ_describe assembleNewTextParts

*/
void XML_Replace::assembleNewTextParts(char**              returnValue,
                                       list<const char*>*  replacementDefinition,
                                       unsigned int        newSize)
{
//cout<<__FILE__<<"|XML_Replace::assembleNewTextParts|"<<"("<<__LINE__<<") enter"<<endl;
 if((*returnValue) != nullptr)                                // destination already used
  delete[]((*returnValue));                                   // free old memory

 if(  (replacementDefinition          != nullptr)
    &&(replacementDefinition->empty() == false  )
   )                                                          // new content is existing
 {
  (*returnValue) = new char[newSize + 1];                     // allocate new memory
  memset((*returnValue),0,newSize + 1);                       // initialize memory terminated

  list<const char*>::iterator ReplacementPart = replacementDefinition->begin();
  while(ReplacementPart != replacementDefinition->end())      // iterate over whole content
  {
   if(*ReplacementPart != nullptr)                            // valid part content
   {
    strcat((*returnValue),(*ReplacementPart));                // copy content-part at the end
   }
   ++ ReplacementPart;                                        // next content-part
  }
 }
 else
 {
  (*returnValue) = nullptr;
 }
//cout<<__FILE__<<"|XML_Replace::assembleNewTextParts|"<<"("<<__LINE__<<") leave"<<endl;
}










/* @MRTZ_describe replacementGet

*/
void XML_Replace::replacementGet(char** returnValue,TiPa_Concrete::DataAssociation* replacementDefinition, XML_Node currentNode)
{
//cout<<__FILE__<<"|XML_Replace::replacementGet|"<<"("<<__LINE__<<") enter"<<endl;

 if(replacementDefinition != nullptr)
 {
  TiPa_Concrete::DataAssociation* SearchDefinition = replacementDefinition->contractorFirst_get(Att.Search(TiPa_Search::UserName,"Search"));
  XML_Node                        DataNode         = dataNodeGet(SearchDefinition, currentNode);              // get searched node

  TiPa_Concrete::DataAssociation* DataDefinition   = replacementDefinition->contractorFirst_get(Att.Search(TiPa_Search::UserName,"Data"));
  if(DataNode.valid())
  {
   dataContentGet( returnValue, DataDefinition, DataNode);   // get data
  }
  else
  {
   /// @todo define error reaction
  }
 }
//cout<<__FILE__<<"|XML_Replace::replacementGet|"<<"("<<__LINE__<<") leave"<<endl;
}


/* @MRTZ_describe dataNodeGet

*/
XML_Node XML_Replace::dataNodeGet(TiPa_Concrete::DataAssociation* searchDefinition, XML_Node currentNode)
{
//cout<<__FILE__<<"|XML_Replace::dataNodeGet|"<<"("<<__LINE__<<") enter"<<endl;
 XML_Node ReturnValue;

 if(searchDefinition != nullptr)
 {
  TiPa_Concrete::DataAssociation* Location = searchDefinition->contractorFirst_get(Att.Search(TiPa_Search::UserName,"Location"));
  TiPa_Concrete::DataAssociation* PathFile = Location->contractorFirst_get(Att.Search(TiPa_Search::UserName,"PathFile"));
  TiPa_Concrete::DataAssociation* PathXML  = Location->contractorFirst_get(Att.Search(TiPa_Search::UserName,"PathXML"));

  if(PathFile == nullptr)
  {
   ReturnValue = dataNodeSearch(PathXML, currentNode);
  }
  else
  {
   cout << "loading of additional xml-file is currently not supported !" << endl;
  }
//  XML_Node DataNode = currentNode.firstGet(XML_Node::Element(XML_Search::Value,"Search"));//get searched node
 }
//cout<<__FILE__<<"|XML_Replace::dataNodeGet|"<<"("<<__LINE__<<") leave"<<endl;
 return(ReturnValue);
}


/* @MRTZ_describe dataNodeSearch

*/
XML_Node XML_Replace::dataNodeSearch(TiPa_Concrete::DataAssociation* pathXML, XML_Node currentNode)
{
//cout<<__FILE__<<"|XML_Replace::dataNodeSearch|"<<"("<<__LINE__<<") enter"<<endl;
 XML_Node     ReturnValue;

 if(pathXML != nullptr)
 {
  XML_Node StartNode   = startNodeGet(  pathXML, currentNode);
  if(StartNode.valid())
  {
//   cout << "StartNode" << StartNode.firstGet().valueGet() << endl;
   XML_Node PathEnd     = dataPathFollow(pathXML, StartNode);
   if(PathEnd.valid())
   {
    ReturnValue = leafNodeGet(   pathXML, PathEnd);
   }
   else
   {
    /// @todo define error reaction
   }
  }
  else
  {
   /// @todo define error reaction
  }
 }
//cout<<__FILE__<<"|XML_Replace::dataNodeSearch|"<<"("<<__LINE__<<") leave"<<endl;
 return(ReturnValue);
}

/* @MRTZ_describe startNodeGet

*/
XML_Node XML_Replace::startNodeGet(TiPa_Concrete::DataAssociation* pathXML, XML_Node currentNode)
{
//cout<<__FILE__<<"|XML_Replace::startNodeGet|"<<"("<<__LINE__<<") enter"<<endl;
 XML_Node     ReturnValue = currentNode;

 if(pathXML != nullptr)
 {
  TiPa_Concrete::DataAssociation* Root = pathXML->contractorFirst_get(Att.Search(TiPa_Search::UserName,"Root"));
  TiPa_Concrete::DataAssociation* Path = pathXML->contractorFirst_get(Att.Search(TiPa_Search::UserName,"Path"));
  TiPa_Concrete::DataAssociation* Node = pathXML->contractorFirst_get(Att.Search(TiPa_Search::UserName,"Node"));

  TiPa_Data* Data = nullptr;
  if(Path != nullptr)
   Data  = Path->contractorFirst_get()->data_get();
  else if(Node != nullptr)
   Data  = Node->data_get();
  else
  {/* keep data not valid */}

  if(  (Root != nullptr)
     ||(  (Data != nullptr                             )
        &&(STRINGS_ARE_NOT_EQUAL(Data->userName_get(),"Here"))
        &&(STRINGS_ARE_NOT_EQUAL(Data->userName_get(),"Up")  )
       )
    )                     // path is absolute
  {
 //  cout << ReturnValue.valueGet() << endl;
   XML_Node Parent = ReturnValue.preGet();  // get parent of given node
   while(  (Parent.valid()                )
         &&(strlen(Parent.valueGet()) != 0)
        )                  // as long as root-node is not reached
   {
    ReturnValue = Parent;                   // upwards to root
    Parent      = ReturnValue.preGet();       // get parent of parent
   }
   if(Root == nullptr)  // absolute path only implicitly defined
   {
    if(Path != nullptr)
     Path->contractorFirst_cut();  // remove root node from path
    else if(Node != nullptr)
     pathXML->contractorFirst_cut();
    else
     {/** @todo define error reaction */}
   }
  }
 }
// if(ReturnValue.valid())
//  cout<<__FILE__<<"|XML_Replace::startNodeGet|"<<"("<<__LINE__<<") leave: "<<  ReturnValue.valueGet()<<endl;
// else
//  cout<<__FILE__<<"|XML_Replace::startNodeGet|"<<"("<<__LINE__<<") leave: "<<  "nothing found"<<endl;
 return(ReturnValue);
}


/* @MRTZ_describe dataPathFollow

*/
XML_Node XML_Replace::dataPathFollow(TiPa_Concrete::DataAssociation* pathXML, XML_Node startNode)
{
//cout<<__FILE__<<"|XML_Replace::dataPathFollow|"<<"("<<__LINE__<<") enter"<<endl;
 XML_Node      ReturnValue = startNode;

 if(pathXML != nullptr)
 {
  TiPa_Concrete::DataAssociation* Path   = pathXML->contractorFirst_get(Att.Search(TiPa_Search::UserName,"Path"));

  TiPa_Concrete::DataAssociation* Folder = nullptr;
  if(  (Path                        != nullptr)
     &&(Path->contractorFirst_get() != nullptr)
    )
   Folder = Path->contractorFirst_get();
  else
   Folder = pathXML->contractorFirst_get(Att.Search(TiPa_Search::UserName,"Node"));

  while(Folder != nullptr)
  {

   TiPa_Data* Data = Folder->data_get();
   if(Data != nullptr)
   {
//    cout << Data->UserName << " : " << Data->getContent() << endl;
    if(STRINGS_ARE_EQUAL(Data->userName_get(), "Up"))
    {
     if(ReturnValue.preGet().valid())
     {
//      cout << "Up" << endl;
      ReturnValue = ReturnValue.preGet() ;
     }
     else
     {
      /// @todo define error reaction
     }
    }
    else if(STRINGS_ARE_EQUAL(Data->userName_get(), "Here"))
    {
//      cout << "Here" << endl;
     // keep current folder
    }
    else if(STRINGS_ARE_EQUAL(Data->userName_get(), "Name"))
    {
//     ReturnValue.xmlText();
//      cout << "Name: " << Data->getContent() << endl;
//     XML_Node    ChildNode = ReturnValue.firstGet(XML_Node::Element(XML_Search::Value,Data->getContent()));
//     ChildNode.xmlText();
//
//     ReturnValue = ChildNode;
//     ReturnValue.xmlText();
//     cout << "Name" << endl;
     ReturnValue = ReturnValue.firstGet(XML_Node::Element(XML_Search::Value,Data->getContent()));
    }
    else
    {
//      cout << "not valid" << endl;
     /// @todo define error reaction
    }

   }
   else
   {
     /// @todo define error reaction
   }

   Folder = Folder->fellowBehind_get();
  }
//  ReturnValue.xmlText();
 }

//cout<<__FILE__<<"|XML_Replace::dataPathFollow|"<<"("<<__LINE__<<") leave: "<<  ReturnValue.valueGet()<<endl;

 return(ReturnValue);
}

/* @MRTZ_describe leafNodeGet

*/
XML_Node  XML_Replace::leafNodeGet(TiPa_Concrete::DataAssociation* pathXML, XML_Node parentNode)
{
//cout<<__FILE__<<"|XML_Replace::leafNodeGet|"<<"("<<__LINE__<<") enter"<<endl;
 XML_Node ReturnValue = parentNode;

 if(pathXML != nullptr)
 {
  TiPa_Concrete::DataAssociation* Node = pathXML->contractorFirst_get(Att.Search(TiPa_Search::UserName,"Node"));
  if(Node != nullptr)
  {
   TiPa_Data* Data = Node->data_get();
   if(Data != nullptr)
   {
    ReturnValue = parentNode.firstGet(XML_Node::Element(XML_Search::Value,Data->getContent()));
   }
   else
   {
    /// @todo define error reaction
   }
  }
  else
  {
   // keep parent-node since there is no further leaf node defined
  }
 }
//cout<<__FILE__<<"|XML_Replace::leafNodeGet|"<<"("<<__LINE__<<") leave: "<<  ReturnValue.valueGet()<<endl;
 return(ReturnValue);
}




/* @MRTZ_describe dataContentGet

*/
void XML_Replace::dataContentGet(char** returnValue,TiPa_Concrete::DataAssociation* dataDefinition, XML_Node dataNode)
{
//cout<<__FILE__<<"|XML_Replace::dataContentGet|"<<"("<<__LINE__<<") enter"<<endl;
 if(dataDefinition != nullptr)
 {
  TiPa_Concrete::DataAssociation* Text = dataDefinition->contractorFirst_get(Att.Search(TiPa_Search::UserName,"Text"));
  if(Text != nullptr)
  {
   dataTextGet(returnValue, dataNode);
  }
  else
  {
   TiPa_Concrete::DataAssociation* AttributeDefinition = dataDefinition->contractorFirst_get(Att.Search(TiPa_Search::UserName,"Attribute/Name"));

   if(AttributeDefinition != nullptr)
   {
    TiPa_Data* Data = AttributeDefinition->data_get();
    if(Data != nullptr)
    {
//     const char* AttributeName = dataNode.attributeGet(Data->getContent(),nullptr);
     const char* AttributeName = Data->getContent();
     dataAttributeGet( returnValue, AttributeName, dataNode);
    }
    else
    {
     /// @todo define error reaction
    }
   }
   else
   {
   /// @todo define error reaction
   }
  }
 }
//cout<<__FILE__<<"|XML_Replace::dataContentGet|"<<"("<<__LINE__<<") leave"<<endl;
}



/* @MRTZ_describe dataTextGet

*/
void XML_Replace::dataTextGet(char** returnValue, XML_Node dataNode)
{
//cout<<__FILE__<<"|XML_Replace::dataTextGet|"<<"("<<__LINE__<<") enter"<<endl;
 if((*returnValue) != nullptr)
 {
  delete[](*returnValue);
          (*returnValue) = nullptr;
 }

 dataNode.textCollect(returnValue);
//cout<<__FILE__<<"|XML_Replace::dataTextGet|"<<"("<<__LINE__<<") leave"<<endl;
}




/* @MRTZ_describe dataAttributeGet

*/
void XML_Replace::dataAttributeGet(char** returnValue, const char* attributeName, XML_Node dataNode)
{
//cout<<__FILE__<<"|XML_Replace::dataAttributeGet|"<<"("<<__LINE__<<") enter"<<endl;
 if((*returnValue) != nullptr)
  delete[](*returnValue);

 if(attributeName != nullptr)
 {
  const char* AttributeContent = dataNode.attributeGet(attributeName,nullptr);
  int         AttributeSize    = strlen(AttributeContent);
//  cout << "AttributeSize" << AttributeSize << "Content : " << AttributeContent << endl;

  (*returnValue)    = new char[AttributeSize + 1];
  memcpy((*returnValue), AttributeContent, AttributeSize);
  (*returnValue)[AttributeSize] = 0;
 }
 else
 {
  /// @todo define error reaction
  (*returnValue) = nullptr;
 }
//cout<<__FILE__<<"|XML_Replace::dataAttributeGet|"<<"("<<__LINE__<<") leave"<<endl;
}
