/*!

 @file
 @brief concrete association visitor to create an xml-tree

 Copyright (C) 2017-2020 by Eckard Klotz.

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
    21.11.2017     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    21.11.2017...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/

#include "xml_DataModel.h"
//#include "AssociationFellowship.hpp"

#include "xml_Load.h"

#include "TiPa_Search.h"
#include "StringC_help.h"



/* @MRTZ_describe XML_Load

*/
XML_Load::XML_Load(void)
{
 Att.ContextModel    = nullptr;
 Att.DestinationRoot = nullptr;
 Att.NewAssociation  = nullptr;
 Att.RootAssociation = nullptr;
}


/* @MRTZ_describe ~XML_Load

*/
XML_Load::~XML_Load(void)
{

}





/* @MRTZ_describe init

*/
void XML_Load::init(void)
{

}



/* @MRTZ_describe contextModel_set

*/
void XML_Load::contextModel_set(DataModel* contextModel)
{
 Att.ContextModel = contextModel;
}



/* @MRTZ_describe operator()

*/
XML_Load* XML_Load::operator()(DataAssociation*      destination,
                               TiPa_DataAssociation* source      )
{

 TiPa_Visitor::init();
 this->init();

 TiPa_Visitor::Att.Node = source;

 if(destination != nullptr)
  Att.DestinationRoot = destination;
 else
  Att.DestinationRoot = Att.ContextModel->fellow_create();

 Att.ParentNode.push_front(Att.DestinationRoot);



 return(this);
}











/* @MRTZ_describe evaluate

*/
DirectionOfIteration XML_Load::evaluate(TiPa_DataAssociation* node/*, TiPa_DataAssociation* sponsor*/)
{
 if(  (Att.RootAssociation                           == nullptr)
    &&(TiPa_Visitor::Att.Direction != IterateNoMore)
   )
 {
  Att.RootAssociation = node;
 }
 else if(  (Att.RootAssociation                           != node)
         &&(node                                          != nullptr)
         &&(TiPa_Visitor::Att.Direction != IterateNoMore)
        )
 {
  // evaluate node
  TiPa_Search  Search;
  if(TiPa_Visitor::Att.Direction != IterateUpwards)                    // visit of next fellow or contractor to collect new data
  {
   TiPa_Data* SourceData = node->data_get();


   if(  (SourceData                              != nullptr)
      &&STRINGS_ARE_EQUAL(SourceData->userName_get(),"Document")
     )                                                                 // node is an element
   {
    DataAssociation* NewNode = createTextXML(node);                    // construct current node  and add to top node of parent stack
    if(NewNode != nullptr)
     (*Att.ParentNode.begin())->contractorLast_add(NewNode);
    TiPa_Visitor::Att.Direction = IterateDownwards;                    // force visit of next fellow
   }
   if(  (SourceData                              != nullptr)
      && (  STRINGS_ARE_EQUAL(SourceData->userName_get(),"CharData")
          ||STRINGS_ARE_EQUAL(SourceData->userName_get(),"CommentContent")
         )
     )                                                                 // node is an element
   {
    DataAssociation* NewNode = createTextXML(node);                    // construct current node  and add to top node of parent stack
    if(NewNode != nullptr)
     (*Att.ParentNode.begin())->contractorLast_add(NewNode);
    TiPa_Visitor::Att.Direction = IterateForwards;                     // force visit of next fellow
   }
   else if(  (SourceData                             != nullptr)
           &&(  STRINGS_ARE_EQUAL(SourceData->userName_get(),"Element")
              ||STRINGS_ARE_EQUAL(SourceData->userName_get(),"Declaration")
             )
          )                                                            // node is an element
   {
    DataAssociation* NewNode = createElementXML(node);                 // construct current node  and add to top node of parent stack
    if(NewNode != nullptr)
     (*Att.ParentNode.begin())->contractorLast_add(NewNode);

    if(  (node->contractorFirst_get(Search(TiPa_Search::UserName,"Element"))        != nullptr)
       ||(node->contractorFirst_get(Search(TiPa_Search::UserName,"Declaration"))    != nullptr)
       ||(node->contractorFirst_get(Search(TiPa_Search::UserName,"CommentContent")) != nullptr)
       ||(node->contractorFirst_get(Search(TiPa_Search::UserName,"CharData"))       != nullptr)
      )                                                                // node has a contractor
    {
     // store constructed node as new parent
     if(NewNode != nullptr)
      Att.ParentNode.push_front(NewNode);
     TiPa_Visitor::Att.Direction = IterateDownwards;                   // welcoming node should iteration over contractors
    }
    else if(node->fellowBehind_get() != nullptr)                       // node has no contractor but a next-fellow
    {
     TiPa_Visitor::Att.Direction = IterateForwards;                    // force visit of next fellow
    }
    else                                                               // node has no contractor and no next fellow
    {
     if(!(Att.ParentNode.empty()))                                     // if parent stack is not empty
      Att.ParentNode.pop_front();                                      // pop top parent
     TiPa_Visitor::Att.Direction = IterateUpwards;                     // force visit to sponsor again
    }
   }
   else if(  (node->contractorFirst_get(Search(TiPa_Search::UserName,"Element"))        != nullptr)
           ||(node->contractorFirst_get(Search(TiPa_Search::UserName,"Declaration"))    != nullptr)
           ||(node->contractorFirst_get(Search(TiPa_Search::UserName,"CommentContent")) != nullptr)
          )                                                            //node has element contractor since it is the xml-document
   {
    TiPa_Visitor::Att.Direction = IterateDownwards;                    // force visit of next fellow
   }
   else if(node->fellowBehind_get() != nullptr)                        // node has no contractor but a next-fellow
   {
    TiPa_Visitor::Att.Direction = IterateForwards;                     //force visit of next fellow
   }
   else                                                                // node has no contractor and no next fellow
   {
    if(!(Att.ParentNode.empty()))                                      // if parent stack is not empty
     Att.ParentNode.pop_front();                                       // pop top parent
    TiPa_Visitor::Att.Direction = IterateUpwards;                      // force visit to sponsor again
   }
  }
                                                                       // return to sponsor that data is already collected
  else if(node->fellowBehind_get() != nullptr)                         // node has no contractor but a next-fellow
  {
   TiPa_Visitor::Att.Direction = IterateForwards;                      // force visit to sponsor again
  }
  else                                                                 // node has no contractor and no next fellow
  {
   if(!(Att.ParentNode.empty()))                                       // if parent stack is not empty
    Att.ParentNode.pop_front();                                        // pop top parent
   TiPa_Visitor::Att.Direction = IterateUpwards;                       // force visit to sponsor again
  }

  if(TiPa_Visitor::Att.Direction != IterateNoMore)
  {
   TiPa_Visitor::Att.Node      = node;                                 // store root node
   TiPa_Visitor::Att.Data      = node->data_get();                     // store root-node data
  }

 }
 else
 {

  TiPa_Visitor::Att.Direction = IterateNoMore;                          //whole evaluation is not completed

  //take final action
 }



 return(TiPa_Visitor::Att.Direction);
}


/* @MRTZ_describe createElementXML

*/
XML_Load::DataAssociation* XML_Load::createElementXML(TiPa_DataAssociation* node)
{
 DataAssociation* ReturnValue = nullptr;

 if(  (node             != nullptr)
    &&(node->data_get() != nullptr)
   )                                              // node is valid and contains valid data
 {
  TiPa_Search Search;
  XML_Data*   Data       = Att.ContextModel->data_create();

  TiPa_Data* SourceData = node->data_get();
  if     (STRINGS_ARE_EQUAL(SourceData->userName_get(),"Element"))
    Data->typeSet(XML_Data::NT_Element);
  else if(STRINGS_ARE_EQUAL(SourceData->userName_get(),"Declaration"))
    Data->typeSet(XML_Data::NT_Declaration);
  else
    Data->typeSet(XML_Data::NT_Undefined);

  TiPa_DataAssociation* ElementName = node->contractorFirst_get(Search(TiPa_Search::UserName,"Name"));
  if(ElementName != nullptr)
  {
   Data->valueSet(ElementName->data_get()->getContent());
  }


  TiPa_DataAssociation* Attribute = node->contractorFirst_get(Search(TiPa_Search::UserName,"Attribute"));
  while(Attribute != nullptr)
  {
   char*       TextBuffer_temp = nullptr;
   const char* Key             = nullptr;
   const char* Value           = nullptr;
   TiPa_DataAssociation* AttributeName = Attribute->contractorFirst_get(Search(TiPa_Search::UserName,"Name"));
   if(AttributeName != nullptr)
   {
    Key = AttributeName->data_get()->getContent();
   }
   TiPa_DataAssociation* AttributeValue = Attribute->contractorFirst_get(Search(TiPa_Search::UserName,"AttValue"));
   if(AttributeValue != nullptr)
   {
    TiPa_DataAssociation* ValueContent = AttributeValue->contractorFirst_get(Search(TiPa_Search::UserName,"AttVal1"));
    if(ValueContent == nullptr)
                          ValueContent = AttributeValue->contractorFirst_get(Search(TiPa_Search::UserName,"AttVal2"));

    if(ValueContent != nullptr)
    {
     TiPa_DataAssociation* TextPart = ValueContent->contractorFirst_get();

     if(TextPart != nullptr)
     {
      list<const char*> String;                                // collection of text-note parts
      set<const char*>  ToDeleteAgain;                         // to store temporarily created strings which have to be removed again

      unsigned int Size = 0;                                   // size of whole text-content
      while(TextPart != nullptr)                               // iterate over all parts of the text-node
      {
       const char* Text    = nullptr;                          // part text
       TiPa_Data* TextData =  TextPart->data_get();            // part data
       if(STRINGS_ARE_EQUAL(TextData->userName_get(),"Reference"))   // referencing data
       {
        Text = solveReference(TextData->getContent());         // transfer into character
        ToDeleteAgain.insert(Text);                            // remember temporarily created part text
       }
       else                                                    // normal characters
       {
        Text = TextData->getContent();                         // use original text
       }
       Size = Size + strlen(Text) + 1;                         // increase text-size plus termination
       String.push_back(Text);
       TextPart = TextPart->fellowBehind_get();                // prepare next loop
      }
      TextBuffer_temp = new char[Size];                        // create memory merging all part-texts to one string
      memset(TextBuffer_temp,0,Size);                          // ensure termination of new string

      list<const char*>::iterator StringPart = String.begin();
      while(StringPart != String.end())                        // iterate over all found part-strings
      {
       strcat(TextBuffer_temp,*StringPart);                    // merge parts
       ++ StringPart;
      }
      Value = TextBuffer_temp;                                 // define xml-node content
      String.clear();                                          // remove list of part-strings
      while(!(ToDeleteAgain.empty()))                          // iterate over all temporarily created part texts
      {
       delete[](*ToDeleteAgain.begin());                       // delete temporarily created part texts content
       ToDeleteAgain.erase(ToDeleteAgain.begin());             // remove pointer from set
      }
     }
     else
      Value = ValueContent->data_get()->getContent();
    }
    else
      Value = nullptr;
   }

   if((Key != nullptr)&&(Value != nullptr))
    Data->attributeSet(Key,Value);
   else if(Key != nullptr)
    Data->attributeSet(Key,"");

   if(TextBuffer_temp != nullptr)
   {
    delete[](TextBuffer_temp);
    TextBuffer_temp = nullptr;
   }

   Attribute = Attribute->fellowBehind_get(Search(TiPa_Search::UserName,"Attribute"));
  }

  ReturnValue    = Att.ContextModel->fellow_create();
  ReturnValue->data_set(Data);
 }


 return(ReturnValue);
}



/* @MRTZ_describe createTextXML

*/
XML_Load::DataAssociation* XML_Load::createTextXML(TiPa_DataAssociation* node)
{
 DataAssociation* ReturnValue = nullptr;

 if(  (node             != nullptr)
    &&(node->data_get() != nullptr)
   )                                                        // node is valid and contains valid data
 {
  XML_Data* Data = Att.ContextModel->data_create();

  TiPa_Data* SourceData = node->data_get();
  if     (STRINGS_ARE_EQUAL(SourceData->userName_get(),"Document"))
    Data->typeSet(XML_Data::NT_Document);
  else if(STRINGS_ARE_EQUAL(SourceData->userName_get(),"CharData"))
    Data->typeSet(XML_Data::NT_Text);
  else if(STRINGS_ARE_EQUAL(SourceData->userName_get(),"CommentContent"))
    Data->typeSet(XML_Data::NT_Comment);
  else
    Data->typeSet(XML_Data::NT_Undefined);

  if(Data->typeGet() ==XML_Data::NT_Text)                   // text-node that may contain several parts
  {
   list<const char*> String;                                // collection of text-note parts
   set<const char*>  ToDeleteAgain;                         // to store temporarily created strings which have to be removed again

   unsigned int Size = 0;                                   // size of whole text-content
   TiPa_DataAssociation* TextPart = node->contractorFirst_get();
   while(TextPart != nullptr)                               // iterate over all parts of the text-node
   {
    const char* Text    = nullptr;                          // part text

    TiPa_Data* TextData =  TextPart->data_get();            // part data
    if(STRINGS_ARE_EQUAL(TextData->userName_get(),"Reference"))   // referencing data
    {
     Text = solveReference(TextData->getContent());         // transfer into character
     ToDeleteAgain.insert(Text);                            // remember temporarily created part text
    }
    else                                                    // normal characters
    {
     Text = TextData->getContent();                         // use original text
    }
    Size = Size + strlen(Text) + 1;                         // increase text-size plus termination
    String.push_back(Text);
    TextPart = TextPart->fellowBehind_get();                // prepare next loop
   }
   char* TextContent = new char[Size];                      // create memory merging all part-texts to one string
   memset(TextContent,0,Size);                              // ensure termination of new string

   list<const char*>::iterator StringPart = String.begin();
   while(StringPart != String.end())                        // iterate over all found part-strings
   {
    strcat(TextContent,*StringPart);                        // merge parts
    ++ StringPart;
   }
   Data->valueSet(TextContent);                             // define xml-node content
   String.clear();                                          // remove list of part-strings
   while(!(ToDeleteAgain.empty()))                          // iterate over all temporarily created part texts
   {
    delete[](*ToDeleteAgain.begin());                       // delete temporarily created part texts content
    ToDeleteAgain.erase(ToDeleteAgain.begin());             // remove pointer from set
   }
  }
  else                                                      // xml-comment
  {
   Data->valueSet(node->data_get()->getContent());          // use directly the content
  }

  ReturnValue = Att.ContextModel->fellow_create();          // new xml-node
  ReturnValue->data_set(Data);                              // over give found data
 }
 return(ReturnValue);
}



/* @MRTZ_describe solveReference

*/
const char* XML_Load::solveReference(const char* symbol)
{
 char* ReturnValue = new char[2];
 ReturnValue[1] = 0;                          // terminate string;

 if(symbol[0] == '%')                         // PEReference
 {
   if     (STRINGS_ARE_EQUAL(symbol+1,"quot;"))
    ReturnValue[0] = 34;
   else if(STRINGS_ARE_EQUAL(symbol+1,";amp"))
    ReturnValue[0] = 38;
   else if(STRINGS_ARE_EQUAL(symbol+1,"lt;"))
    ReturnValue[0] = 60;
   else if(STRINGS_ARE_EQUAL(symbol+1,"gt;"))
    ReturnValue[0] = 62;
   else if(STRINGS_ARE_EQUAL(symbol+1,"circ;"))
    ReturnValue[0] = 94;
   else if(STRINGS_ARE_EQUAL(symbol+1,"tilde;"))
    ReturnValue[0] = 126;
 }
 else if(symbol[0] == '&')                    // CharRef or EntityRef
 {
  if(symbol[1] == '#')                        // numeric symbol
  {
   if((symbol[2] == 'x')||(symbol[2] == 'X')) // hexadecimal number
   {
    char OrdinalNumber = 0;
    int Index = 3;
    char Character = symbol[Index];
    while(  ((Character>='0')&&(Character<='9'))
          ||((Character>='a')&&(Character<='f'))
          ||((Character>='A')&&(Character<='F'))
         )
    {
     if     ((Character>= '0' )&&(Character<= '0' ))
     {
      OrdinalNumber = (OrdinalNumber*16) + (Character - '0');
     }
     else if((Character>='a')&&(Character<='f'))
     {
      OrdinalNumber = (OrdinalNumber*16) + (Character - 'a') + 10;
     }
     else
     {
      OrdinalNumber = (OrdinalNumber*16) + (Character - 'A') + 10;
     }
     ++ Index;
     Character = symbol[Index];
    }
    ReturnValue[0] = OrdinalNumber;
   }
   else                                       //decimal number
   {
    char OrdinalNumber = 0;
    int Index = 3;
    char Character = symbol[Index];
    while(  ((Character>='0')&&(Character<='9'))
         )
    {
     OrdinalNumber = OrdinalNumber*10 + Character - '0';
     ++ Index;
     Character = symbol[Index];
    }
    ReturnValue[0] = OrdinalNumber;
   }
  }
  else                                       // name
  {
   if     (STRINGS_ARE_EQUAL(symbol+1,"quot;"))
    ReturnValue[0] = 34;
   else if(STRINGS_ARE_EQUAL(symbol+1,"amp;"))
    ReturnValue[0] = 38;
   else if(STRINGS_ARE_EQUAL(symbol+1,"lt;"))
    ReturnValue[0] = 60;
   else if(STRINGS_ARE_EQUAL(symbol+1,"gt;"))
    ReturnValue[0] = 62;
   else if(STRINGS_ARE_EQUAL(symbol+1,"circ;"))
    ReturnValue[0] = 94;
   else if(STRINGS_ARE_EQUAL(symbol+1,"tilde;"))
    ReturnValue[0] = 126;
  }
 }
 else                                        // symbol is not valid
 {
  ReturnValue[0] = 0;                        // empty string;
 }

 return(ReturnValue);
}
