/*!

 @file
 @brief concrete manager of attributes and text-data of an xml-node

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
    18.11.2017     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    18.11.2017...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/


#include "xml_Data.h"

#include <cstring>

/* @MRTZ_describe XML_Data

*/
XML_Data::XML_Data(void):AssociationData()
{
//  Type = XML_Data::NT_Undefined;
//  Value = nullptr;
  Value    = new char[1];
  Value[0] = 0;
}


/* @MRTZ_describe XML_Data

*/
XML_Data::XML_Data(XML_Data& data)
{
 this->typeSet(data.typeGet());
 this->valueSet(data.valueGet());

 list<AssociationData::SecondaryData_TP*>* SourceSecondaryData = data.secondaryData_get();
 list<AssociationData::SecondaryData_TP*>::iterator SourceSecondary = SourceSecondaryData->begin();
 while(SourceSecondary != SourceSecondaryData->end())
 {
  secondaryData_add((*SourceSecondary)->Key, (*SourceSecondary)->Val);
  ++ SourceSecondary;
 }
}




/* @MRTZ_describe ~XML_Data

*/
XML_Data::~XML_Data(void)
{
  if(Value != nullptr)
   delete[](Value);
  AssociationData::init();
// list<SecondaryData_TP*>::iterator Source = SecondaryData.Dictionary.begin();
// while(Source != SecondaryData.Dictionary.end())   //iterate over given data dictionary
// {
//  delete[]((*Source)->Key);
//  delete[]((*Source)->Val);
//  (*Source)->Key = nullptr;
//  (*Source)->Val = nullptr;
//  ++ Source;
// }
// SecondaryData.Dictionary.clear();
}




/* @MRTZ_describe operator=

*/
XML_Data& XML_Data::operator= ( XML_Data& data)
{
 if(this != &data)
 {
//  XML_Data TemporaryNode(xmlData);
//  std::swap(Type,          TemporaryNode.Type);
//  std::swap(Value,         TemporaryNode.Value);
//  std::swap(SecondaryData, TemporaryNode.SecondaryData);

  this->typeSet(data.typeGet());
  this->valueSet(data.valueGet());
  this->AssociationData::init();

  list<AssociationData::SecondaryData_TP*>* SourceSecondaryData = data.secondaryData_get();
  list<AssociationData::SecondaryData_TP*>::iterator SourceSecondary = SourceSecondaryData->begin();
  while(SourceSecondary != SourceSecondaryData->end())
  {
   secondaryData_add((*SourceSecondary)->Key, (*SourceSecondary)->Val);
   ++ SourceSecondary;
  }
 }
 return(*this);
}











/* @MRTZ_describe isRealSecondaryData

*/
bool XML_Data::isRealSecondaryData(const char* data)
{
// @MRTZ_showSource
 return(data != Value);//text content if node is a text-node
}



/* @MRTZ_describe typeSet

*/
void XML_Data::typeSet(XML_Data::NodeType_TP type)
{
 Type = type;
}


/* @MRTZ_describe type_get

*/
XML_Data::NodeType_TP XML_Data::typeGet(void)
{
 return(Type);
}



/* @MRTZ_describe valueSet

*/
void XML_Data::valueSet(const char* value)
{
 if(Value != nullptr)                      // destination already in use
  delete[](Value);                         // erase destination

 if(value != nullptr)                      // source contains real data
 {
  unsigned int SourceSize = strlen(value); // read out one time instead of several time later

  Value = new char[SourceSize + 1];        // source-size + termination
  memcpy(Value, value, SourceSize);       // copy source
  Value[SourceSize] = 0;                   // terminate new string
 }
 else                                      // source is empty
 {
  Value = nullptr;                         // initialize as empty
 }
}


/* @MRTZ_describe valueGet

*/
const char* XML_Data::valueGet(void)
{
 return(Value);
}




/* @MRTZ_describe attributeSet
  wrapper of base-class method secondaryData_add
*/
const char* XML_Data::attributeSet(const char* key, const char* data)
{
 return(secondaryData_add(key,data));
}


/* @MRTZ_describe attributeSet
  wrapper of base-class method secondaryData_add
*/
const char* XML_Data::attributeSet(const char* key, int data)
{
 return(secondaryData_add(key,data));
}


/* @MRTZ_describe attributeSet
  wrapper of base-class method secondaryData_add
*/
const char* XML_Data::attributeSet(const char* key, double data)
{
 return(secondaryData_add(key,data));
}



/* @MRTZ_describe attributeGet
  wrapper of base-class method secondaryData_get
*/
const char* XML_Data::attributeGet(const char* key, const char* defaultData)
{
 return(secondaryData_get(key,defaultData));
}


/* @MRTZ_describe attributeGet
  wrapper of base-class method secondaryData_get
*/
int XML_Data::attributeGet(const char* key, int defaultData )
{
 return(secondaryData_get(key,defaultData));
}


/* @MRTZ_describe attributeGet
  wrapper of base-class method secondaryData_get
*/
double XML_Data::attributeGet(const char* key, double defaultData)
{
 return(secondaryData_get(key,defaultData));
}



















