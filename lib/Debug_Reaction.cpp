/*!

 @file
 @brief abstract reaction-class for a parser event


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
    14.10.2017     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    14.10.2017...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/
#include "Debug_Reaction.h"
#include <iostream>


/* @MRTZ_describe Debug_Reaction
 no initialization since already done in declaration
*/
Debug_Reaction::Debug_Reaction(void)
               :TiPa_Reaction_Concrete(),
                Property(nullptr)
{
 //Property = nullptr;
}

/* @MRTZ_describe Debug_Reaction_2

*/
Debug_Reaction::Debug_Reaction(const Debug_Reaction& debug_Reaction)
{
 Property = debug_Reaction.Property;
}



/* @MRTZ_describe operator=

*/
Debug_Reaction& Debug_Reaction::operator= (const Debug_Reaction& debug_Reaction)
{
 Property = debug_Reaction.Property;

 return(*this);
}




/* @MRTZ_describe ~Debug_Reaction

*/
Debug_Reaction::~Debug_Reaction(void)
{

}



/* @MRTZ_describe setProperty

*/
void Debug_Reaction::setProperty(map<TiPa_Concrete*, TDA_GrmConcrete::Property_TP>* property)
{
 Property = property;
}




/* @MRTZ_describe processHit

*/
void Debug_Reaction::processHit(TiPa_Abstract* owner, TiPa_Result::Data_TP&  data)
{
 if (owner != nullptr)
 {
  const char* Type = nullptr;
  if(owner->as_TiPa_Concrete()->typeString() != nullptr)
   Type = owner->as_TiPa_Concrete()->typeString();
  else
   Type = "Unknown Type" ;

  const char* UserName = nullptr;
  if(owner->userName_get() != nullptr)
   UserName = owner->userName_get();
  else if(Property->find(owner->as_TiPa_Concrete()) != Property->end())
  {
   UserName = Property->at(owner->as_TiPa_Concrete()).Name;
  }
  else
   UserName = "No UserName" ;

  if((data.Begin != nullptr) &&(data.End != nullptr))
  {
//   Content = data.getContent();
   unsigned int ContentSize = data.End - data.Begin;
   char*        Content     = new char[ContentSize + 1];
   memset(Content,0,         ContentSize+1);
   memcpy(Content,data.Begin,ContentSize);
//   Content[ContentSize] = 0;
   cout << Type << "(" << UserName << "): |" << Content << "|" << endl;
   delete[]Content;
  }
  else
   cout << Type << "(" << UserName << "): |Empty Content|" << endl;

 }
 else
 {
  // nothing to do
 }
}

