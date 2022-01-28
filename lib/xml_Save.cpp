/*!

 @file
 @brief concrete association visitor to store an xml-tree in a file

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

#include "xml_Save.h"
#include <sstream>
#include "StringC_help.h"
#include <limits.h>


XML_Save::Dflt_XML_String XML_Save::DfltXML;



/* @MRTZ_describe XML_Save

*/
XML_Save::XML_Save(void)
         :AssociationVisitor()
{
 this->init(nullptr);

 char* IntMin = nullptr;
 AssociationData::itoa(&IntMin,INT_MIN);

 XML_Save::DfltXML.Tag               = "Tag";
 XML_Save::DfltXML.Attribute.Integer = IntMin;
 XML_Save::DfltXML.Attribute.Double  = "0.0";
 XML_Save::DfltXML.Attribute.String  = "__EMPTY__";
 XML_Save::DfltXML.String            = "__EMPTY__";

}

/* @MRTZ_describe ~XML_Save

*/
XML_Save::~XML_Save(void)
{
 map<int,list<Template_TP* >*>::iterator Template;
 list<Template_TP* >::iterator           Detail;


 init(nullptr);

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


/* @MRTZ_describe operator()

*/
XML_Save* XML_Save::operator()(char** text)
{
 XML_Visitor::init();
 this->init(text);

 return(this);
}



/* @MRTZ_describe evaluate

*/
DirectionOfIteration XML_Save::evaluate(DataAssociation* node/*, DataAssociation* sponsor*/)
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
     &&(node->data_get()->typeGet() != XML_Data::NT_Document)
     &&(node->data_get()->typeGet() != XML_Data::NT_Undefined)
    )
  {
   XML_Visitor::Att.Direction = evaluateXML(node/*,sponsor*/);
  }
 }
 else if(  (Att.RootAssociation                           != node)
         &&(node                                          != nullptr)
         &&(node->data_get()                              != nullptr)
         &&(XML_Visitor::Att.Direction != IterateNoMore)
        )
 {
  XML_Visitor::Att.Direction = evaluateXML(node/*,sponsor*/);
 }
 else
 {
   XML_Visitor::Att.Direction = IterateNoMore;        // whole evaluation is not completed
 }

 if(XML_Visitor::Att.Direction == IterateNoMore)
 {
  list<const char*>::iterator String;
  stringstream Text;

  for(String = Att.OutputText.begin(); String != Att.OutputText.end(); ++String)
  {
   Text << (*String);                                 // store the collected text content into a text-stream
  }

  (*Att.Text) = new char[Text.str().size() + 1];
  memcpy((*Att.Text),Text.str().c_str(),Text.str().size());
  (*Att.Text)[Text.str().size()] = 0;
 }
 else
 {
 }

 return(XML_Visitor::Att.Direction);
}








/* @MRTZ_describe evaluateXML

*/
DirectionOfIteration XML_Save::evaluateXML(DataAssociation* node/*, DataAssociation* sponsor*/)
{
 LOG_OUTPUT(LOG_OFF, "XML_Save::evaluateNode");

 if(XML_Visitor::Att.Direction != IterateUpwards)                                            // visit of next fellow or contractor to collect new data
 {
  char*  Indention1         = new char[Att.Indention+1];
  memset(Indention1,' ',Att.Indention);
  Indention1[Att.Indention] = 0;
  bool Indention1Used       = false;

  char*  Indention2         = new char[Att.Indention+1];
  memset(Indention2,' ',Att.Indention);
  Indention2[Att.Indention] = 0;
  bool Indention2Used       = false;

  char* EndOfLine = new char[3];
  memset(EndOfLine,0,3);
  strcpy(EndOfLine,"\n");
  bool EndOfLineUsed      = false;

  list<const char*>::iterator  InsertPosition;
  if(Att.InsertPosition.empty())
  {
   InsertPosition = Att.OutputText.end();
  }
  else
  {
   InsertPosition = *(Att.InsertPosition.begin());
  }

  list<const char*>::iterator  ChildInsertsBefore;
  switch(node->data_get()->typeGet())
  {
   case XML_Data::NT_Element:
   {
    if(node->contractorFirst_get() != nullptr)                                               // element with childes
    {
     Att.OutputText.insert(InsertPosition,Indention1);                                       // store indention tag (start or end)
     Indention1Used = true;                                                                  // set flag to avoid delete of Indention
     char* Text = nullptr;                                                                   // clear text-pointer
     stringRepresentation(node->data_get(), Att.Template[XML_Save::XML_StartTag], &Text, ConvertAll);
                                                                                             // get data-representation
     Att.OutputText.insert(InsertPosition,Text);                                             // store data-representation
     Att.OutputText.insert(InsertPosition,EndOfLine);                                        // store indention tag (start or end)
     EndOfLineUsed = true;                                                                   // set flag to avoid delete of Indention
     ChildInsertsBefore = Att.OutputText.insert(InsertPosition,Indention2);                  // store indention tag (start or end)
     Indention2Used = true;                                                                  // set flag to avoid delete of Indention
     Text = nullptr;                                                                         // clear text-pointer
     stringRepresentation(node->data_get(), Att.Template[XML_Save::XML_EndTag], &Text, ConvertAll);
                                                                                             // get data-representation
     Att.OutputText.insert(InsertPosition,Text);                                             // store data-representation
    }
    else                                                                                     // leaf-element
    {
     Att.OutputText.insert(InsertPosition,Indention1);                                       // store indention tag (start or end)
     Indention1Used = true;                                                                  // set flag to avoid delete of Indention
     char* Text = nullptr;                                                                         // clear text-pointer
     stringRepresentation(node->data_get(), Att.Template[XML_Save::XML_LeafTag], &Text, ConvertAll);
                                                                                             // get data-representation
     Att.OutputText.insert(InsertPosition,Text);                                             // store data-representation
     Att.OutputText.insert(InsertPosition,EndOfLine);                                        // store indention tag (start or end)
     EndOfLineUsed = true;                                                                   // set flag to avoid delete of Indention
    }
   }break;
   case XML_Data::NT_Comment:
   {
     Att.OutputText.insert(InsertPosition,Indention1);                                       // store indention tag (start or end)
     Indention1Used = true;                                                                  // set flag to avoid delete of Indention
     char* Text = nullptr;                                                                         // clear text-pointer
     stringRepresentation(node->data_get(), Att.Template[XML_Save::XML_Comment], &Text, KeppBelowASCII32);
                                                                                             // get data-representation
     Att.OutputText.insert(InsertPosition,Text);                                             // store data-representation
     Att.OutputText.insert(InsertPosition,EndOfLine);                                        // store indention tag (start or end)
     EndOfLineUsed = true;                                                                   // set flag to avoid delete of Indention
   }break;

   case XML_Data::NT_Declaration:
   {
     Att.OutputText.insert(InsertPosition,Indention1);                                       // store indention tag (start or end)
     Indention1Used = true;                                                                  // set flag to avoid delete of Indention
     char* Text = nullptr;                                                                         // clear text-pointer
     stringRepresentation(node->data_get(), Att.Template[XML_Save::XML_Declaration], &Text, ConvertAll);
                                                                                             // get data-representation
     Att.OutputText.insert(InsertPosition,Text);                                             // store data-representation
     Att.OutputText.insert(InsertPosition,EndOfLine);                                        // store indention tag (start or end)
     EndOfLineUsed = true;                                                                   // set flag to avoid delete of Indention
   }break;

   case XML_Data::NT_Text:
   {
     char* Text = nullptr;                                                                   // clear text-pointer
     stringRepresentation(node->data_get(), Att.Template[XML_Save::XML_Text], &Text, ConvertAll);
                                                                                             // get data-representation

     if(  (node->fellowBefore_get() == nullptr)
        &&(node->fellowBehind_get() == nullptr)
        &&(strchr(Text,10)          == nullptr)
        &&(strchr(Text,13)          == nullptr)
       )                                                                                     // lonely text that contains no carriage return and no line-feed
     {
      list<const char*>::iterator ChangePosition = InsertPosition;

      -- ChangePosition;                                                                     // line before
      if(STRINGS_ARE_EQUAL((*ChangePosition),EndOfLine))                                     // new line inserted before after opening tag
       ((char*)(*ChangePosition))[0] = 0;

      ++ ChangePosition;                                                                     // Indention inserted before closing tag
      ((char*)(*ChangePosition))[0] = 0;

      Att.OutputText.insert(InsertPosition,Text);                                            // store data-representation
     }
     else
     {
      Att.OutputText.insert(InsertPosition,Indention1);                                      // store indention tag (start or end)
      Indention1Used = true;                                                                 // set flag to avoid delete of Indention
      Att.OutputText.insert(InsertPosition,Text);                                            // store data-representation
      Att.OutputText.insert(InsertPosition,EndOfLine);                                       // store indention tag (start or end)
      EndOfLineUsed = true;                                                                  // set flag to avoid delete of Indention
     }

   }break;

   case XML_Data::NT_Document:
   case XML_Data::NT_Undefined:
   default :
   {
                                                                                              // nothing to store
   }break;
  }

  if(node->contractorFirst_get() != nullptr)                                                  // node has a contractor
  {
   Att.InsertPosition.push_front(ChildInsertsBefore);                                         // insert position to insert-stack
   XML_Visitor::Att.Direction = IterateDownwards;                                             // welcoming node should iteration over contractors
   Att.Indention = Att.Indention + 2;
  }
  else if(  (node->fellowBehind_get() != nullptr)
          &&(node                     != Att.RootAssociation)
         )                                                                                    // node has a next-fellow but is not root of tree to evaluate
  {
   XML_Visitor::Att.Direction = IterateForwards;                                              // force visit of next fellow
  }
  else if(node                     != Att.RootAssociation)                                    // node has no contractor and no next fellow and is not root of tree to evaluate
  {
   if(!(Att.InsertPosition.empty()))
    Att.InsertPosition.pop_front();                                                           // pop top of insert stack
   XML_Visitor::Att.Direction = IterateUpwards;                                               // force visit to sponsor again
   if( Att.Indention >= 2)
    Att.Indention = Att.Indention - 2;
  }
  else                                                                                        // node has no contractor and no next fellow and is root of tree to evaluate
  {
   Att.InsertPosition.clear();                                                                // clear insert stack
   XML_Visitor::Att.Direction = IterateNoMore;                                                // terminate visitation
   if( Att.Indention >= 2)
    Att.Indention = Att.Indention - 2;
  }

  if(Indention1Used   == false)                                                               // string was not used
   delete[](Indention1);                                                                      // free memory
  if(Indention2Used   == false)                                                               // string was not used
   delete[](Indention2);                                                                      // free memory
  if(EndOfLineUsed   == false)                                                                // string was not used
   delete[](EndOfLine);                                                                       // free memory
 }
 else                                                                                         // return to sponsor that data is already collected
 {
  if(  (node->fellowBehind_get() != nullptr)
     &&(node                     != Att.RootAssociation)
    )                                                                                        // node has a next-fellow but is not root of tree to evaluate
  {
   XML_Visitor::Att.Direction = IterateForwards;                                             // force visit to sponsor again
  }
  else if(node                     != Att.RootAssociation)                                   // node has no contractor and no next fellow and is not root of tree to evaluate
  {
   if(!(Att.InsertPosition.empty()))
    Att.InsertPosition.pop_front();                                                          // pop top of insert stack
   XML_Visitor::Att.Direction = IterateUpwards;                                              // force visit to sponsor again
   if( Att.Indention >= 2)
    Att.Indention = Att.Indention - 2;
  }
  else                                                                                       // node has no contractor and no next fellow and is root of tree to evaluate
  {
   Att.InsertPosition.clear();                                                               // clear insert stack
   XML_Visitor::Att.Direction = IterateNoMore;                                               // terminate visitation
   if( Att.Indention >= 2)
    Att.Indention = Att.Indention - 2;
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

*/
void XML_Save::init(char** text)
{
 Att.CommonDirection = IterateAsBefore;
 Att.Text            = text;                    // file to work with
 Att.Indention       = 0;
 Att.RootAssociation = nullptr;

 set<const char*> ExistingString;               // to collect the really occupied memory fragments
 list<const char*>::iterator String;            // single element of output-text
 for(String = Att.OutputText.begin();String != Att.OutputText.end();++String)
                                                //iterate over output-text that is reusing some memory-content several times
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


 if(Att.Template.find(XML_Save::XML_StartTag)    == Att.Template.end())
    Att.Template[XML_Save::XML_StartTag]    = stringTemplate("<$Value$$Attribute$>");     // splitter between tag-name and attribute will be added while attribute creation
 if(Att.Template.find(XML_Save::XML_EndTag)      == Att.Template.end())
    Att.Template[XML_Save::XML_EndTag]      = stringTemplate("</$Value$>\n");
 if(Att.Template.find(XML_Save::XML_LeafTag)     == Att.Template.end())
    Att.Template[XML_Save::XML_LeafTag]     = stringTemplate("<$Value$$Attribute$/>");    // splitter between tag-name and attribute will be added while attribute creation

 if(Att.Template.find(XML_Save::XML_Text)        == Att.Template.end())
    Att.Template[XML_Save::XML_Text]        = stringTemplate("$Value$");

 if(Att.Template.find(XML_Save::XML_Comment)     == Att.Template.end())
    Att.Template[XML_Save::XML_Comment]     = stringTemplate("<!-- $Value$ -->");
 if(Att.Template.find(XML_Save::XML_Declaration) == Att.Template.end())
    Att.Template[XML_Save::XML_Declaration] = stringTemplate("<? $Value$$Attribute$?>");  // splitter between tag-name and attribute will be added while attribute creation


}




/* @MRTZ_describe stringTemplate_set

*/
list<XML_Save::Template_TP* >* XML_Save::stringTemplate(const char* text, char separator)
{

 list<Template_TP* >* ReturnValue  = new list<Template_TP* >;

 const char* Character = text;                     // iteration start
 const char* TextEnd   = text + (strlen(text)-1);  // iteration end
 const char* WordBegin = nullptr;                  //begin of the current detail in given text
 while(Character <= TextEnd)                       // iteration over given text
 {
  if((*Character) == separator)                    // non raw-text part framed completely with separators
   ++Character;                                    // jump over very opening separator

  WordBegin = Character;                           // begin of text-part to analyse next
  ++Character;                                     // jump over normal text-character that is not a separator

  while(  (*Character != separator)
        &&( Character <= TextEnd)
       )                                           // iteration over text part
  {
   ++Character;                                    // jump over normal text-character that is not a separator
  }
  char* Word = new char[Character-WordBegin+1];    // prepare a copy of the found text-part
  memcpy(Word,WordBegin,Character-WordBegin);      // copy part
  Word[Character-WordBegin]=0;                     // terminate part
  Template_TP* Detail = new Template_TP;           // prepare storing element
               Detail->RawText = Word;             // store found part
               Detail->Data    = dataID_get(Word); // store association-data attribute identifier or raw-text key
  ReturnValue->push_back(Detail);                  // add to template

  ++Character;                                     // jump over closing separator
 }

 return(ReturnValue);                              // return the new template
}








/* @MRTZ_describe stringRepresentation
    collect single data and assemble it
   @MRTZ_describe create_representation_list
    use the template to create a list of single part-strings where each represents a single association-data attribute
   @MRTZ_describe create_output_text
    assemble all part strings to the output-string
*/
void XML_Save::stringRepresentation(XML_Data* data,  list<Template_TP* >* textTemplate, char** text, Character2XML_Mode_TP keepBelow )
{
// @MRTZ_exclude create_representation_list
// @MRTZ_beginBlock
 list<Template_TP* >::iterator Detail;                          // template for one
                                                                // association-data attribute
 list<const char*>             Representations;                 // representation of all
                                                                // association-data attribute
 unsigned int                  WriteSize        = 0;            // size of output string

 Detail = textTemplate->begin();
 while(Detail != textTemplate->end())                           // iterate over template
 {
  switch((*Detail)->Data)
// use the detail data id in a switch to choose the action that creates the associated text part
// !!!refer the method dataID_get to learn what id is associated with what association-data attribute!!!
  {
   case XML_Data::UnKnown:                                      // identifies a raw-text detail
   {
    Representations.push_back((*Detail)->RawText);              // store template content
   }break;
   case XML_Data::NodeType:                                     // parser-type id
   {
    char* Text0 = nullptr;                                      // decouple previous content
    XML_Data::itoa(&Text0,data->typeGet());                     // convert number to digit-string
    Representations.push_back(Text0);                           // store part-string
   }break;
   case XML_Data::Content:                                      // the detected text-part
   {
    const char* Text0 = data->valueGet();                       // evaluate attributes Begin and End
    char* TextXML = nullptr;
    string2xml(Text0,&TextXML,keepBelow);
    Representations.push_back(TextXML);                         // store part-string
   }break;


   case XML_Data::Attribute:                                    // secondary data
   {
    list<AssociationData::SecondaryData_TP*>* Dictionary = data->secondaryData_get();

#ifdef SORT_SECONDARY_DATA
    list<char*>::iterator Attribute = data->Keys.begin();
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
     if(  (Dictionary->find(*Attribute)                         != Dictionary->end())
        &&(data->isRealSecondaryData((*Dictionary)[*Attribute]) == true             )
       )
#else
     if(data->isRealSecondaryData((*Attribute)->Val) == true)
#endif
     {
      Representations.push_back(" ");
      WriteSize = WriteSize + 1;                                // splitter to tag-name or attribute before

      char* Text0 = nullptr;                                    // decouple previous content
#ifdef SORT_SECONDARY_DATA
      string2xml((char*)(*Attribute),&Text0);                   // store name of attribute
#else
      string2xml((char*)(*Attribute)->Key,&Text0,keepBelow);    // store name of attribute
#endif
      Representations.push_back(Text0);
      WriteSize = WriteSize + strlen(Text0);

      Representations.push_back("=\"");
      WriteSize = WriteSize + 2;

      Text0 = nullptr;                                          // decouple previous content
#ifdef SORT_SECONDARY_DATA
      string2xml((*Dictionary)[*Attribute],&Text0);             // store value of attribute
#else
      string2xml((char*)(*Attribute)->Val,&Text0);              // store value of attribute
#endif
      Representations.push_back(Text0);
      WriteSize = WriteSize + strlen(Text0);
//      Representations.push_back("\" ");
//      WriteSize = WriteSize + 2;
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
     Representations.push_back(TextXML);                        // store attribute value

   }break;
  }

  if(*(Representations.rbegin())!=nullptr)                      // representation contains a valid string
   WriteSize = WriteSize + strlen(*(Representations.rbegin())); // calculate size of text to output

  ++ Detail;                                                    // next template detail
 }

 if((*text)== nullptr)                                          // given text is empty
  (*text) = new char[WriteSize +1];                             // prepare memory
 else if (WriteSize > strlen(*text))                            // given text seems to be not empty but is to small
  WriteSize = strlen(*text);                                    // reduce output size
 else                                                           // given text seems to be not empty and big enough
 { /* do nothing*/  }
// @MRTZ_endBlock


// @MRTZ_exclude create_output_text
// @MRTZ_beginBlock

 char* Write    = *text;                                        // initialize write-position
 char* WriteEnd = (*text) + WriteSize;                          // directly behind end of valid write-memory

 for(   list<const char*>::iterator Representation =  Representations.begin();
                                    Representation != Representations.end();
                                 ++ Representation
    )                                                           // iterate over Representations to create output text
 {
  if(*Representation!=nullptr)                                  // representation contains a valid string
  {
   const char* ReadEnd = (*Representation) + strlen(*Representation);
                                                                // directly  behind string to read
   for(const char*Read = (*Representation); Read < ReadEnd; ++Read)
   {                                                            // iterate over string to read
    if(Write < WriteEnd)                                        // end of output text is not reached
    {
     (*Write) = (*Read);                                        // copy character into output text
      ++ Write;                                                 // increment write-position
    }
   }
  }
 }
 (*Write) = 0;                                                  // terminate output-string
// @MRTZ_endBlock
}




/* @MRTZ_describe dataID_get

*/
int XML_Save::dataID_get(const char* text)
{
 int ReturnValue = XML_Data::UnKnown;

 if     (strstr(text, "Type")      == text)             // node-type
  ReturnValue = XML_Data::NodeType;
 else if(strstr(text, "Value")     == text)             // text content may be transferred into valid xml-format
  ReturnValue = XML_Data::Content;
 else if(strstr(text, "Attribute") == text)             // xml-attributes
  ReturnValue = XML_Data::Attribute;
 else                                                   // association data attribute not known
 {/*keep as unknown*/}


 return(ReturnValue);
}







/* @MRTZ_describe char2xml

*/
const char* XML_Save::char2xml(char character)
{
 static char ANSI[256][7];

 static bool Initialsised = false;
 if(Initialsised == false)
 {
  memset(ANSI[0],0,7);
  for(int Ordinal = 1; Ordinal <256; ++Ordinal)
  {
   memset(ANSI[Ordinal],0,7);
   switch(Ordinal)
   {
    case   1: strcpy(ANSI[Ordinal],"&#1;");  break;
    case   2: strcpy(ANSI[Ordinal],"&#2;");  break;
    case   3: strcpy(ANSI[Ordinal],"&#3;");  break;
    case   4: strcpy(ANSI[Ordinal],"&#4;");  break;
    case   5: strcpy(ANSI[Ordinal],"&#5;");  break;
    case   6: strcpy(ANSI[Ordinal],"&#6;");  break;
    case   7: strcpy(ANSI[Ordinal],"&#7;");  break;
    case   8: strcpy(ANSI[Ordinal],"&#8;");  break;
    case   9: strcpy(ANSI[Ordinal],"&#9;");  break;
    case  10: strcpy(ANSI[Ordinal],"&#10;"); break;

    case  11: strcpy(ANSI[Ordinal],"&#11;"); break;
    case  12: strcpy(ANSI[Ordinal],"&#12;"); break;
    case  13: strcpy(ANSI[Ordinal],"&#13;"); break;
    case  14: strcpy(ANSI[Ordinal],"&#14;"); break;
    case  15: strcpy(ANSI[Ordinal],"&#15;"); break;
    case  16: strcpy(ANSI[Ordinal],"&#16;"); break;
    case  17: strcpy(ANSI[Ordinal],"&#17;"); break;
    case  18: strcpy(ANSI[Ordinal],"&#18;"); break;
    case  19: strcpy(ANSI[Ordinal],"&#19;"); break;
    case  20: strcpy(ANSI[Ordinal],"&#20;"); break;

    case  21: strcpy(ANSI[Ordinal],"&#21;"); break;
    case  22: strcpy(ANSI[Ordinal],"&#22;"); break;
    case  23: strcpy(ANSI[Ordinal],"&#23;"); break;
    case  24: strcpy(ANSI[Ordinal],"&#24;"); break;
    case  25: strcpy(ANSI[Ordinal],"&#25;"); break;
    case  26: strcpy(ANSI[Ordinal],"&#26;"); break;
    case  27: strcpy(ANSI[Ordinal],"&#27;"); break;
    case  28: strcpy(ANSI[Ordinal],"&#28;"); break;
    case  29: strcpy(ANSI[Ordinal],"&#29;"); break;
    case  30: strcpy(ANSI[Ordinal],"&#30;"); break;

    case  31: strcpy(ANSI[Ordinal],"&#31;");   break;
    case  32: strcpy(ANSI[Ordinal]," "/*"&#32;"*/);   break;
    case  34: strcpy(ANSI[Ordinal],"&quot;");  break;
    case  38: strcpy(ANSI[Ordinal],"&amp;");   break;
    case  39: strcpy(ANSI[Ordinal],"&#39;");   break;
    case  60: strcpy(ANSI[Ordinal],"&lt;");    break;
    case  62: strcpy(ANSI[Ordinal],"&gt;");    break;
    case  94: strcpy(ANSI[Ordinal],"^"/*"&circ;"*/);  break;
    case 126: strcpy(ANSI[Ordinal],"~"/*"&tilde;"*/); break;
    case 127: strcpy(ANSI[Ordinal],"&#127;");  break;

    default:
     if(Ordinal < 127)
     {
      ANSI[Ordinal][0] = Ordinal;
      ANSI[Ordinal][1] = 0;
     }
     else
     {
      char  DigitOfHundred = (Ordinal                                     ) / 100;
      char  DigitOfTen     = (Ordinal - DigitOfHundred*100                ) /  10;
      char  DigitOfOne     = (Ordinal - DigitOfHundred*100 - DigitOfTen*10) /   1;
      ANSI[Ordinal][0] = '&';
      ANSI[Ordinal][1] = '#';
      ANSI[Ordinal][2] =  DigitOfHundred + 48; // digit of 100 plus ASCII number for 0
      ANSI[Ordinal][3] =      DigitOfTen + 48; // digit of  10 plus ASCII number for 0
      ANSI[Ordinal][4] =      DigitOfOne + 48; // digit of   1 plus ASCII number for 0
      ANSI[Ordinal][5] = ';';
      ANSI[Ordinal][6] = 0;
     }
    break;
   }
  }
  Initialsised = true;
 }
#if      (CHAR_MIN < 0)     // compiler treats char as signed
 if(character >= 0)
  return(ANSI[(int)character]);
 else
  return(ANSI[(int)(256 + character)]);
#else  //(CHAR_MIN == 0)    // compiler treats char as unsigned
  return(ANSI[(int)character]);
#endif //(CHAR_MIN < 0)
}



/* @MRTZ_describe string2xml

*/
void XML_Save::string2xml(const char* source, char** destination, Character2XML_Mode_TP keepBelow )
{
  if(   ( source       != nullptr)
     &&((*destination) == nullptr)
    )
  {
   ostringstream TextXML;
   int           Character = 0;

   while(source[Character] != 0)
   {

#if     (CHAR_MIN < 0)  // compiler treats char as signed
    bool KeepCharacter =(source[Character] > 0)  && (source[Character] < (char) keepBelow);
#else //(CHAR_MIN == 0) // compiler treats char as unsigned
    bool KeepCharacter =                            (source[Character] < (char) keepBelow);
#endif//(CHAR_MIN < 0)
    if(KeepCharacter == true)
     TextXML << source[Character];
    else
     TextXML << char2xml(source[Character]);

    ++Character;
   }
   (*destination) = new char[TextXML.str().size()+1];
   strcpy((*destination),TextXML.str().c_str());

   (*destination)[TextXML.str().size()]=0;
  }
  else
  {
   // don't touch the destination since the source is not existing
  }
}
