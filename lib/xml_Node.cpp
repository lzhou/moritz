/*!

 @file
 @brief user interface class for xml-associations

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
    03.03.2018     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    03.03.2018...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/
#include "xml_Node.h"

#include "xml_DataModel.h"
#include "xml_Save.h"





XML_Search    XML_Node::Undefined(XML_Data::NT_Undefined);
XML_Search    XML_Node::Document(XML_Data::NT_Document);
XML_Search    XML_Node::Element(XML_Data::NT_Element);
XML_Search    XML_Node::Text(XML_Data::NT_Text);
XML_Search    XML_Node::Comment(XML_Data::NT_Comment);
XML_Search    XML_Node::Declaration(XML_Data::NT_Declaration);

const char    XML_Node::EmptyString[1] ={0};

/* @MRTZ_describe XML_Node

*/
XML_Node::XML_Node(void)
{
 Att.Association = nullptr;
 Att.Context     = nullptr;

// Att.Parent      = nullptr;
}

/* @MRTZ_describe XML_Node

*/
XML_Node::XML_Node(DataModel* context, DataFellow* association)
{
 Att.Association = association;
 Att.Context     = context;
}


/* @MRTZ_describe XML_Node

*/
XML_Node::XML_Node(DataModel* context, XML_Data* xmlData)
{
 Att.Context     = context;
 Att.Association = Att.Context->fellow_create(xmlData);
}



/* @MRTZ_describe XML_Node

*/
XML_Node::XML_Node(DataModel* context , XML_Data::NodeType_TP type)
{
 Att.Context     = context;

 XML_Data* Data = Att.Context->data_create();
           Data->typeSet(type);

 Att.Association = Att.Context->fellow_create(Data);
}





/* @MRTZ_describe XML_Node

*/
XML_Node::XML_Node(DataModel* context, Construction_TP construction)
{
 Att.Context     = context;
 if(construction != Prepare)  // the node should be constructed if the preparation is not explicitly wanted
  Att.Association = Att.Context->fellow_create(context->data_create());
 else                         // the node should only be prepared
  Att.Association = nullptr;
}

/* @MRTZ_describe XML_Node

*/
XML_Node::XML_Node(const XML_Node& xmlNode)
{
 Att.Association = xmlNode.Att.Association;
 Att.Context     = xmlNode.Att.Context;
}





/* @MRTZ_describe ~XML_Node

*/
XML_Node::~XML_Node(void)
{

}



/* @MRTZ_describe operator=

*/
XML_Node& XML_Node::operator= (const XML_Node& xmlNode)
{
 if(this != &xmlNode)
 {
  XML_Node TemporaryNode(xmlNode);
  std::swap(Att.Context,     TemporaryNode.Att.Context);
  std::swap(Att.Association, TemporaryNode.Att.Association);
 }
 return(*this);
}



/* @MRTZ_describe cloneToOwnContext

*/
void XML_Node::cloneToOwnContext(const XML_Node& xmlNode)
{
 if(  (  this->Att.Context     != nullptr)
    &&(xmlNode.Att.Association != nullptr)
   )  // this node has a valid association context and the given node has a valid association
  Att.Association = Att.Context->fellow_create(xmlNode.Att.Association, XML_DataModel::DataClone);
 else // this node or the given node is not capable to support the tree-creation
  Att.Association = nullptr;
}






/* @MRTZ_describe associationNodeSet

*/
void XML_Node::associationNodeSet(DataFellow* association)
{
  Att.Association = association;
}

/* @MRTZ_describe associationNodeGet

*/
XML_Node::DataFellow* XML_Node::associationNodeGet(void)
{
 return(Att.Association);
}

/* @MRTZ_describe associationContextSet

*/
void XML_Node::associationContextSet(DataModel* context)
{
 Att.Context = context;
}

/* @MRTZ_describe associationContextGet

*/
XML_Node::DataModel* XML_Node::associationContextGet(void)
{
 return(Att.Context);
}


/* @MRTZ_describe valid

*/
bool XML_Node::valid()
{
 return(  (Att.Association != nullptr)
        &&(Att.Context     != nullptr)
       );
}



/* @MRTZ_describe typeSet

void XML_Node::typeSet(XML_Data::NodeType_TP type)
{

}
*/


/* @MRTZ_describe typeGet

*/
XML_Data::NodeType_TP XML_Node::typeGet(void)
{
  XML_Data::NodeType_TP ReturnValue = XML_Data::NT_Undefined;
  if(Att.Association != nullptr)
  {
    XML_Data* Data = Att.Association->data_get();
    if(Data != nullptr)
    {
     ReturnValue = Data->typeGet();
    }
    else
    {
     // keep the undefined value
    }
  }
  else
  {
   // keep the undefined value
  }

  return(ReturnValue);
}



/* @MRTZ_describe valueSet

*/
void XML_Node::valueSet(const char* value)
{
  if(Att.Association != nullptr)
  {
    XML_Data* Data = Att.Association->data_get();
    if(Data != nullptr)
    {
     Data->valueSet(value);
    }
    else
    {
     // nothing to do
    }
  }
  else
  {
   // nothing to do
  }
}


/* @MRTZ_describe valueGet

*/
const char* XML_Node::valueGet(void)
{
  const char* ReturnValue = nullptr;

  if(Att.Association != nullptr)
  {
    XML_Data* Data = Att.Association->data_get();
    if(Data != nullptr)
    {
     ReturnValue = Data->valueGet();
    }
    else
    {
     // keep the undefined value
    }
  }
  else
  {
   // keep the undefined value
  }

  return(ReturnValue);
}






/* @MRTZ_describe attributeSet

*/
const char* XML_Node::attributeSet(const char* key, const char* data)
{
  const char* ReturnValue = nullptr;

  if(Att.Association != nullptr)
  {
    XML_Data* Data = Att.Association->data_get();
    if(Data != nullptr)
    {
     ReturnValue = Data->attributeSet(key,data);
    }
    else
    {
     // keep the undefined value
    }
  }
  else
  {
   // keep the undefined value
  }

  return(ReturnValue);
}


/* @MRTZ_describe attributeSet

*/
const char* XML_Node::attributeSet(const char* key, int data)
{
  const char* ReturnValue = nullptr;

  if(Att.Association != nullptr)
  {
    XML_Data* Data = Att.Association->data_get();
    if(Data != nullptr)
    {
     ReturnValue = Data->attributeSet(key,data);
    }
    else
    {
     // keep the undefined value
    }
  }
  else
  {
   // keep the undefined value
  }

  return(ReturnValue);
}

/* @MRTZ_describe attributeSet

*/
const char* XML_Node::attributeSet(const char* key, double data)
{
  const char* ReturnValue = nullptr;

  if(Att.Association != nullptr)
  {
    XML_Data* Data = Att.Association->data_get();
    if(Data != nullptr)
    {
     ReturnValue = Data->attributeSet(key,data);
    }
    else
    {
     // keep the user defined data
    }
  }
  else
  {
    // keep the user defined data
  }

  return(ReturnValue);
}



/* @MRTZ_describe attributeGet

*/
const char* XML_Node::attributeGet(const char* key, const char* defaultData)
{
  const char* ReturnValue = defaultData;

  if(Att.Association != nullptr)
  {
    XML_Data* Data = Att.Association->data_get();
    if(Data != nullptr)
    {
     ReturnValue = Data->attributeGet(key,defaultData);
    }
    else
    {
     // keep the user defined default data
    }
  }
  else
  {
   // keep the user defined default data
  }

  return(ReturnValue);
}


/* @MRTZ_describe attributeGet

*/
int XML_Node::attributeGet(const char* key, int defaultData)
{
  int ReturnValue = defaultData;

  if(Att.Association != nullptr)
  {
    XML_Data* Data = Att.Association->data_get();
    if(Data != nullptr)
    {
     ReturnValue = Data->attributeGet(key, defaultData);
    }
    else
    {
     // keep the user defined default data
    }
  }
  else
  {
   // keep the user defined default data
  }

  return(ReturnValue);
}


/* @MRTZ_describe attributeGet

*/
double XML_Node::attributeGet(const char* key, double defaultData)
{
  double ReturnValue = defaultData;

  if(Att.Association != nullptr)
  {
    XML_Data* Data = Att.Association->data_get();
    if(Data != nullptr)
    {
     ReturnValue = Data->attributeGet(key, defaultData);
    }
    else
    {
     // keep the user defined default data
    }
  }
  else
  {
   // keep the user defined default data
  }

  return(ReturnValue);
}





/* @MRTZ_describe textCollect
    returns the found text or the given default text
   @MRTZ_describe create_error_message_1
    create a default-string
*/
char* XML_Node::textCollect(char** returnValue)
{
 int      Size  = 0;
 XML_Node Child = firstGet(XML_Node::Text());
 while(Child.valid() == true)
 {
  const char* Part = Child.valueGet();
  if(Part  != nullptr)
  {
   Size = Size + strlen(Part);
  }
  Child = Child.behindGet(XML_Node::Text());
 }

 if((*returnValue) != nullptr)
  delete[](*returnValue);
 (*returnValue)  =   new char[Size + 1];
 memset((*returnValue),0,Size + 1);

 Child = firstGet(XML_Node::Text());
 while(Child.valid() == true)
 {
  const char* Part = Child.valueGet();
  if(Part  != nullptr)
  {
   (*returnValue) = strcat((*returnValue), Part);
  }
  Child = Child.behindGet(XML_Node::Text());
 }
 return(*returnValue);
}








/* @MRTZ_describe preGet

*/
XML_Node XML_Node::preGet(void)
{
 XML_Node ReturnValue(Att.Context, XML_Node::Prepare);

 if(Att.Association != nullptr)
 {
  DataAssociation* Association = Att.Association->sponsor_get();

  if(Association != nullptr)
   ReturnValue.associationNodeSet(Association->as_AssociationFellowship());
  else
   {/* keep return-value as invalid*/}
 }

 return(ReturnValue);
}




/* @MRTZ_describe preGet

XML_Node* XML_Node::preGet(XML_Visitor& visitor)
{
 XML_Node* ReturnValue = nullptr;

// if(Att.Association != nullptr)
// {
//  DataFellow* Association = Att.Association->sponsor_get()->as_AssociationFellowship();
//
//  if(Association != nullptr)
//   ReturnValue = new XML_Node(Att.Context,Association);
//  else
//   {/ * keep return-value as invalid* /}
//   }
 return(ReturnValue);
}
*/





/* @MRTZ_describe firstGet

*/
XML_Node XML_Node::firstGet(void)
{
 XML_Node ReturnValue(Att.Context, XML_Node::Prepare);

 if(Att.Association != nullptr)
 {
  DataAssociation* Association = Att.Association->contractorFirst_get();

  if(Association != nullptr)
   ReturnValue.associationNodeSet(Association->as_AssociationFellowship());
  else
   {/* keep return-value as invalid*/}
 }

 return(ReturnValue);
}




/* @MRTZ_describe firstGet

*/
XML_Node XML_Node::firstGet(XML_Visitor* visitor)
{
 XML_Node ReturnValue(Att.Context, XML_Node::Prepare);

 if(Att.Association != nullptr)
 {
  DataAssociation* Association = Att.Association->contractorFirst_get(visitor);

  if(Association != nullptr)
   ReturnValue.associationNodeSet(Association->as_AssociationFellowship());
  else
   {/* keep return-value as invalid*/}
 }

 return(ReturnValue);
}




/* @MRTZ_describe firstAdd

*/
XML_Node XML_Node::firstAdd(XML_Node& nodeToAdd)
{
 XML_Node ReturnValue(Att.Context, XML_Node::Prepare);

 if(  (    this->Att.Association != nullptr)
    &&(nodeToAdd.Att.Association != nullptr)
   )
 {
  DataAssociation* Association = Att.Association->contractorFirst_add(nodeToAdd.Att.Association);
  if(Association != nullptr)
   ReturnValue.associationNodeSet(Association->as_AssociationFellowship());
  else
   {/* keep return-value as invalid*/}
 }
 else
  {/* keep return-value as invalid*/}

 return(ReturnValue);
}



/* @MRTZ_describe firstAdd

*/
XML_Node XML_Node::firstAdd(XML_Data::NodeType_TP type)
{
 XML_Node ReturnValue(Att.Context, XML_Node::Prepare);

 if(this->Att.Association != nullptr)
 {
  XML_Data* Data = Att.Context->data_create();
            Data->typeSet(type);

  DataAssociation* Association = Att.Context->fellow_create();
                   Association->data_set(Data);

  Att.Association->contractorFirst_add(Association);
  ReturnValue.associationNodeSet(Association->as_AssociationFellowship());
 }
 else
  {/* keep return-value as invalid*/}

 return(ReturnValue);
}







/* @MRTZ_describe lastGet

*/
XML_Node XML_Node::lastGet(void)
{
 XML_Node ReturnValue(Att.Context, XML_Node::Prepare);

 if(Att.Association != nullptr)
 {
  DataAssociation* Association = Att.Association->contractorLast_get();

  if(Association != nullptr)
   ReturnValue.associationNodeSet(Association->as_AssociationFellowship());
  else
   {/* keep return-value as invalid*/}
 }

 return(ReturnValue);
}




/* @MRTZ_describe lastGet

*/
XML_Node XML_Node::lastGet(XML_Visitor* visitor)
{
 XML_Node ReturnValue(Att.Context, XML_Node::Prepare);

 if(Att.Association != nullptr)
 {
  DataAssociation* Association = Att.Association->contractorLast_get(visitor);

  if(Association != nullptr)
   ReturnValue.associationNodeSet(Association->as_AssociationFellowship());
  else
   {/* keep return-value as invalid*/}
 }

 return(ReturnValue);
}





/* @MRTZ_describe lastAdd

*/
XML_Node XML_Node::lastAdd(XML_Node& nodeToAdd)
{
 XML_Node ReturnValue(Att.Context, XML_Node::Prepare);

 if(  (    this->Att.Association != nullptr)
    &&(nodeToAdd.Att.Association != nullptr)
   )
 {
  DataAssociation* Association = Att.Association->contractorLast_add(nodeToAdd.Att.Association);
  if(Association != nullptr)
   ReturnValue.associationNodeSet(Association->as_AssociationFellowship());
  else
   {/* keep return-value as invalid*/}
 }
 else
  {/* keep return-value as invalid*/}

 return(ReturnValue);
}

/* @MRTZ_describe lastAdd

*/
XML_Node XML_Node::lastAdd(XML_Data::NodeType_TP type)
{
 XML_Node ReturnValue(Att.Context, XML_Node::Prepare);

 if(this->Att.Association != nullptr)
 {
  XML_Data* Data = Att.Context->data_create();
            Data->typeSet(type);

  DataAssociation* Association = Att.Context->fellow_create();
                   Association->data_set(Data);

  Att.Association->contractorLast_add(Association);
  ReturnValue.associationNodeSet(Association->as_AssociationFellowship());
 }
 else
  {/* keep return-value as invalid*/}

 return(ReturnValue);
}





/* @MRTZ_describe beforeGet

*/
XML_Node XML_Node::beforeGet(void)
{
 XML_Node ReturnValue(Att.Context, XML_Node::Prepare);

 if(Att.Association != nullptr)
 {
  DataAssociation* Association = Att.Association->fellowBefore_get();

  if(Association != nullptr)
   ReturnValue.associationNodeSet(Association->as_AssociationFellowship());
  else
   {/* keep return-value as invalid*/}
 }

 return(ReturnValue);
}




/* @MRTZ_describe beforeGet

*/
XML_Node XML_Node::beforeGet(XML_Visitor* visitor)
{
 XML_Node ReturnValue(Att.Context, XML_Node::Prepare);

 if(Att.Association != nullptr)
 {
  DataAssociation* Association = Att.Association->fellowBefore_get(visitor);

  if(Association != nullptr)
   ReturnValue.associationNodeSet(Association->as_AssociationFellowship());
  else
   {/* keep return-value as invalid*/}
 }

 return(ReturnValue);
}






/* @MRTZ_describe beforeAdd

*/
XML_Node XML_Node::beforeAdd(XML_Node& beforeThis, XML_Node& nodeToAdd)
{
 XML_Node ReturnValue(Att.Context, XML_Node::Prepare);

 if(  (     this->Att.Association != nullptr)
    &&(beforeThis.Att.Association != nullptr)
    &&( nodeToAdd.Att.Association != nullptr)
   )
 {
  DataAssociation* Association = Att.Association->contractorBefore_add(beforeThis.Att.Association,
                                                                        nodeToAdd.Att.Association);
  if(Association != nullptr)
   ReturnValue.associationNodeSet(Association->as_AssociationFellowship());
  else
   {/* keep return-value as invalid*/}
 }
 else
  {/* keep return-value as invalid*/}

 return(ReturnValue);
}

/* @MRTZ_describe beforeAdd

*/
XML_Node XML_Node::beforeAdd(XML_Node& beforeThis, XML_Data::NodeType_TP type)
{
 XML_Node ReturnValue(Att.Context, XML_Node::Prepare);

 if(  (     this->Att.Association != nullptr)
    &&(beforeThis.Att.Association != nullptr)
   )
 {
  XML_Data* Data = Att.Context->data_create();
            Data->typeSet(type);

  DataAssociation* Association = Att.Context->fellow_create();
                   Association->data_set(Data);

  Att.Association->contractorBefore_add(beforeThis.Att.Association, Association);
  ReturnValue.associationNodeSet(Association->as_AssociationFellowship());
 }
 else
  {/* keep return-value as invalid*/}

 return(ReturnValue);
}









/* @MRTZ_describe behindGet

*/
XML_Node XML_Node::behindGet(void)
{
 XML_Node ReturnValue(Att.Context, XML_Node::Prepare);

 if(Att.Association != nullptr)
 {
  DataAssociation* Association = Att.Association->fellowBehind_get();

  if(Association != nullptr)
   ReturnValue.associationNodeSet(Association->as_AssociationFellowship());
  else
  {/* keep return-value as invalid*/}
 }

 return(ReturnValue);
}




/* @MRTZ_describe behindGet

*/
XML_Node XML_Node::behindGet(XML_Visitor* visitor)
{
 XML_Node ReturnValue(Att.Context, XML_Node::Prepare);

 if(Att.Association != nullptr)
 {
  DataAssociation* Association = Att.Association->fellowBehind_get(visitor);

  if(Association != nullptr)
   ReturnValue.associationNodeSet(Association->as_AssociationFellowship());
  else
  {/* keep return-value as invalid*/}
 }

 return(ReturnValue);
}



/* @MRTZ_describe behindAdd

*/
XML_Node XML_Node::behindAdd(XML_Node& behindThis, XML_Node& nodeToAdd)
{
 XML_Node ReturnValue(Att.Context, XML_Node::Prepare);

 if(  (     this->Att.Association != nullptr)
    &&(behindThis.Att.Association != nullptr)
    &&( nodeToAdd.Att.Association != nullptr)
   )
 {
  DataAssociation* Association = Att.Association->contractorBehind_add(behindThis.Att.Association,
                                                                        nodeToAdd.Att.Association);
  if(Association != nullptr)
   ReturnValue.associationNodeSet(Association->as_AssociationFellowship());
  else
  {/* keep return-value as invalid*/}
 }
 else
 {/* keep return-value as invalid*/}

 return(ReturnValue);
}

/* @MRTZ_describe behindAdd

*/
XML_Node XML_Node::behindAdd(XML_Node& behindThis, XML_Data::NodeType_TP type)
{
 XML_Node ReturnValue(Att.Context, XML_Node::Prepare);

 if(  (     this->Att.Association != nullptr)
    &&(behindThis.Att.Association != nullptr)
   )
 {
  XML_Data* Data = Att.Context->data_create();
            Data->typeSet(type);

  DataAssociation* Association = Att.Context->fellow_create();
                   Association->data_set(Data);

  Att.Association->contractorBehind_add(behindThis.Att.Association, Association);
  ReturnValue.associationNodeSet(Association->as_AssociationFellowship());
 }
 else
 {/* keep return-value as invalid*/}

 return(ReturnValue);
}



/* @MRTZ_describe nodeCut

*/
XML_Node XML_Node::nodeCut(XML_Node& nodeToCut)
{
 XML_Node ReturnValue(Att.Context, XML_Node::Prepare);

 if(nodeToCut.valid() == true)
 {
  if(  (this->Att.Association != nullptr)
     &&(Att.Association->isContractor(nodeToCut.Att.Association))
    )
  {
   DataAssociation* Association = nodeToCut.Att.Association->fellowBefore_get();
   if(Association != nullptr)
   {
    ReturnValue.associationNodeSet(Association->fellowBehind_cut()->as_AssociationFellowship());
   }
   else
   {
    Association = nodeToCut.Att.Association->fellowBehind_get();
    if(Association != nullptr)
    {
     ReturnValue.associationNodeSet(Association->fellowBefore_cut()->as_AssociationFellowship());
    }
    else
    {
     ReturnValue.associationNodeSet(Att.Association->contractorFirst_cut()->as_AssociationFellowship());
    }
   }

  }
  else
  {/* keep return-value as invalid*/}

 }

 return(ReturnValue);
}

/* @MRTZ_describe nodeSwap

*/
bool XML_Node::nodeSwap(XML_Node& node1, XML_Node& node2)
{
 bool ReturnValue = false;

 if(  (this->Att.Association != nullptr)
    &&(Att.Association->isContractor(node1.Att.Association))
    &&(Att.Association->isContractor(node2.Att.Association))
   )
 {
  ReturnValue = Att.Association->swapNodes(node1.Att.Association, node2.Att.Association);
 }
 else
 {/* keep return-value as invalid*/}



 return(ReturnValue);
}



/* @MRTZ_describe xmlText

*/
void XML_Node::xmlText( char** destination)
{
 XML_Save OutputGenerator;

 Att.Association->welcome(OutputGenerator(destination),IterateDownwards);
}



/* @MRTZ_describe xmlText

*/
void XML_Node::xmlText(void)
{
 char* XML_Text = nullptr;    // xml-text

 xmlText(& XML_Text);

 if(XML_Text != nullptr)
 {
  char   NL_MS[3] = {13,10,0};
  size_t Size     = strlen(XML_Text);

  for(size_t Character = 0; Character < Size; ++Character)
  {
   if(strstr(XML_Text + Character,NL_MS) == XML_Text+Character)
   {
    cout << endl;
    ++ Character;
   }
   else
    cout << XML_Text[Character];
  }
  delete[]XML_Text;
 }
 else
 {
  printf("xml node is not defined!");
 }
}




