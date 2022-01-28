
/*!

 @file
 @brief search for an xml node with a specific name and or tree-path

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
    01.05.2018     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    01.05.2018...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/



//#define DEBUG_OUTPUT_LOG
#include "LogOutput.h"




#include <stdio.h>
#include <cstdlib>

#include "StringC_help.h"
#include "xml_Search.h"


using namespace std;


const char* XML_Search::IgnoreValue = ">>IgnoreValue<<";



/* @MRTZ_describe XML_Search

*/
XML_Search::XML_Search(void)
            :AssociationVisitor()
{
 Att.NodeType = XML_Data::NT_Undefined;
 this->init(SearchMode_DF, nullptr, '/', 0);
}



/* @MRTZ_describe XML_Search
  just call init
*/
XML_Search::XML_Search(XML_Data::NodeType_TP nodeType)
            :AssociationVisitor()
{
 Att.NodeType = nodeType;
 this->init(SearchMode_DF, nullptr, '/', 0);
}



/* @MRTZ_describe XML_Search
  just call init
*/
XML_Search::XML_Search(SearchMode_TP mode, XML_Data::NodeType_TP nodeType, const char* path, char separator, int indexStart)
            :AssociationVisitor()
{
 Att.NodeType = nodeType;
 this->init(mode, path, separator, indexStart);
}





/* @MRTZ_describe ~XML_Search

*/
XML_Search::~XML_Search(void)
{

 Att.Word = Att.Path.begin();
 while(Att.Word != Att.Path.end())
 {
  delete[](*Att.Word);
  (*Att.Word) = nullptr;
  ++ Att.Word;
 }
 Att.Path.clear();
}




/* @MRTZ_describe init

*/
void XML_Search::init(SearchMode_TP mode, const char* path, char separator, int indexStart)
{
 Att.CommonDirection = IterateAsBefore;
 Att.Mode            = mode;                       // set mode of search and evaluation
 Att.CallCounter     = indexStart;

 while(!(Att.Path.empty()))
 {
  delete[](*Att.Path.begin());
  Att.Path.pop_front();
 }

 if(  (path         != nullptr)
    &&(strlen(path) >  0)
   )                                           // given path is valid
 {
  int          Size  = strlen(path);           // length of  given path
  const char*  Begin = path;                   // begin of first path-part
  const char*  End   = strchr(path,separator); // end of first path-part

  if(End==nullptr)                             // path contains no separator
   End = path + Size;                          // end of first path-part is end of path

  while(  (End   != nullptr)
        &&(Begin <  path + Size)
       )                                       // begin and end are inside of path
  {
   char*   Word = new char[Size+1];            // container for current path-part
   memcpy(Word,Begin,End-Begin);              // copy content of current path-part
   Word[End-Begin] = 0;                        // ensure the termination of the string

   Att.Path.push_back(Word);                   // set reference data used for content-search
   Begin = End + 1;                            // begin of next path-part
   End   = strchr(Begin,separator);            // end of next path-part
   if(End==nullptr)                            // path contains no more separator
    End = path + Size;                         // end of next path-part is end of path
  }
 }
 else
 {
                                               // let Word and Number empty
 }
 Att.Word = Att.Path.begin();
}



/* @MRTZ_describe operator()

*/
XML_Search* XML_Search::operator()(SearchMode_TP mode, const char* path, char separator, int indexStart)
{
  XML_Visitor::init();
  this->init(mode, path, separator, indexStart);

  return(this);
}



/* @MRTZ_describe setCallCounter

*/
void XML_Search::setCallCounter(int indexStart)
{
 Att.CallCounter = indexStart;
}




/* @MRTZ_describe evaluate

*/
DirectionOfIteration XML_Search::evaluate(DataAssociation* node/*, DataAssociation* sponsor*/)
{
 if(Att.CommonDirection != IterateAsBefore)                //direction was temporarily changed after previous evaluation
 {
  XML_Visitor::Att.Direction = Att.CommonDirection;        // restore direction to iterate
  Att.CommonDirection        = IterateAsBefore;
 }
 else
 {
 }

 if(  (Att.Word                   != Att.Path.end())
    &&(node                       != nullptr)
    &&(XML_Visitor::Att.Direction != IterateNoMore )
   )
 {
  bool Found = false;
  switch(Att.Mode)
  {
   case XML_Search::Index :
   {
    Found = evaluateIndex(node,*Att.Word);
   }break;
   case XML_Search::Type :
   {
    Found = evaluateType(node);
   }break;
   case XML_Search::Value :
   {
    Found = evaluateValue(node,*Att.Word);
   }break;
   case XML_Search::SearchMode_NV :
   default :
   {
   }break;
  }

  if(  (Found    == true)
     &&  (                     Att.Word != Att.Path.end()          )
     &&(STRINGS_ARE_NOT_EQUAL(*Att.Word ,  XML_Search::IgnoreValue))
     )                                                     // part evaluation succeeded and next part evaluation is existing
  {
   XML_Visitor::Att.Node      = node->contractorFirst_get();
//   XML_Visitor::Att.Data      = XML_Visitor::Att.Node->data_get();
   if(XML_Visitor::Att.Node != nullptr)
    XML_Visitor::Att.Data = XML_Visitor::Att.Node->data_get();
   else
    XML_Visitor::Att.Data = nullptr;

   Att.CommonDirection = XML_Visitor::Att.Direction;       // next part evaluation
   XML_Visitor::Att.Direction = IterateWithFound;          //temporary change only
   LOG_OUTPUT(LOG_OFF, *Att.Word);
// Found = false;
  }
  else if(  (Found    == true)
          &&(Att.Word == Att.Path.end())
         )                                                 // part evaluation succeeded and last part evaluation is ready
  {
   XML_Visitor::Att.Direction = IterateNoMore;             // whole evaluation is not completed
  }
  else // nothing found
  {
   XML_Visitor::Att.Node      = nullptr;
   XML_Visitor::Att.Data      = nullptr;
  }
 }
 return(XML_Visitor::Att.Direction);
}



/* @MRTZ_describe evaluateIndex

*/
bool XML_Search::evaluateIndex(DataAssociation* node, const char* word)
{
  bool        ReturnValue   = false;

  if(node != nullptr)
  {
   XML_Data* Data  = node->data_get();
   if(Data != nullptr)
   {
    if(  (Data->typeGet() == Att.NodeType)
       ||(Data->typeGet() == XML_Data::NT_Undefined)
      )// node type as defined and number of calls correct
    {
     if(Att.CallCounter == atoi(word))
     {
      XML_Visitor::Att.Node      = node;
      XML_Visitor::Att.Data      = node->data_get();
      ReturnValue                                   = true;
      ++ Att.Word;
     }
     ++ Att.CallCounter;
    }
    else
    {
     //XML_Visitor::Att.Direction = IterateAsBefore;
    }
   }
  }
 return(ReturnValue);
}


/* @MRTZ_describe evaluateOperand

*/
bool XML_Search::evaluateType(DataAssociation* node)
{
  bool        ReturnValue   = false;
  if(node != nullptr)
  {
   XML_Data* Data  = node->data_get();
   if(Data != nullptr)
   {
    if(Data->typeGet() == Att.NodeType)
    {
     XML_Visitor::Att.Node      = node;
     XML_Visitor::Att.Data      = Data;
     ReturnValue                                  = true;
     ++ Att.Word;
    }
    else
    {
    // XML_Visitor::Att.Direction = IterateAsBefore;
    }
   }

  }
 return(ReturnValue);
}




/* @MRTZ_describe evaluateValue

*/
bool XML_Search::evaluateValue(DataAssociation* node, const char* word)
{
  bool        ReturnValue   = false;

  if(node != nullptr)
  {
   XML_Data* Data  = node->data_get();
   if(Data != nullptr)
   {
     const char* String = Data->valueGet();
     if(  (Data->typeGet() == Att.NodeType)
        ||(Data->typeGet() == XML_Data::NT_Undefined)
       )
    {
     if(  (strstr(String, word) ==        String )
        &&(strlen(word)         == strlen(String))
       ) // node type as defined and content starts with word and has the same size
     {
      XML_Visitor::Att.Node      = node;
      XML_Visitor::Att.Data      = Data;
      ReturnValue                                  = true;
      ++ Att.Word;
     }
    }
    else
    {
     // XML_Visitor::Att.Direction = IterateAsBefore;
    }

   }
  }
 return(ReturnValue);
}
