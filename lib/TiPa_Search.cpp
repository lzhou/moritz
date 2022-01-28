
/*!

 @file
 @brief search for a association with specific data

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
    09.09.2015     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    09.09.2015...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/



//#define DEBUG_OUTPUT_LOG
#include "LogOutput.h"




#include <stdio.h>
#include <cstdlib>

#include "TiPa_Search.h"


using namespace std;


#ifndef DOXYGEN
//namespace TXTDIASM {
//namespace TDA_TinyParser {
//namespace DATA {
#endif //DOXYGEN



/* @MRTZ_describe TiPa_Search

*/
TiPa_Search::TiPa_Search(void)
            :AssociationVisitor(),
             Att()
{
 this->init(SearchMode_DF, nullptr, '/', 0);
}



/* @MRTZ_describe TiPa_Search
  just call init
*/
TiPa_Search::TiPa_Search(SearchMode_TP mode, const char* path, char separator, int indexStart)
            :AssociationVisitor(),
             Att()
{
 this->init(mode, path, separator, indexStart);
}


/* @MRTZ_describe TiPa_Search

*/
TiPa_Search::TiPa_Search(const TiPa_Search& visitor)
            :Att()
{
 AssociationVisitor::Att.Node        = visitor.AssociationVisitor::Att.Node;
 AssociationVisitor::Att.Data        = visitor.AssociationVisitor::Att.Data;
 AssociationVisitor::Att.Direction   = visitor.AssociationVisitor::Att.Direction;

 Att.Mode            = visitor.Att.Mode;
 Att.CommonDirection = visitor.Att.CommonDirection;
 Att.CallCounter     = visitor.Att.CallCounter;
// Att.FilterNumber    = visitor.Att.FilterNumber;

 Att.Word =  Att.Path.begin();
 list<const char*>::iterator Word = ((TiPa_Search)visitor).Att.Path.begin();
 while(Word != visitor.Att.Path.end())
 {
  char*      Text = new char[strlen(*Word)+1];
      memcpy(Text,*Word,strlen(*Word));
             Text[strlen(*Word)] = 0;
  Att.Path.push_back(Text);

  if(Word == visitor.Att.Word)
  {
   Att.Word = Att.Path.end(); // end-iterator is no element
   -- Att.Word;               // last element
  }
  ++Word;
 }

}



/* @MRTZ_describe ~TiPa_Search

*/
TiPa_Search::~TiPa_Search(void)
{

 Att.Word = Att.Path.begin();
 while(Att.Word != Att.Path.end())
 {
  delete(*Att.Word);
  (*Att.Word) = nullptr;
  ++ Att.Word;
 }
 Att.Path.clear();
}


/* @MRTZ_describe operator=

*/
TiPa_Search& TiPa_Search::operator= (const TiPa_Search& visitor)
{
 AssociationVisitor::Att.Node        = visitor.AssociationVisitor::Att.Node;
 AssociationVisitor::Att.Data        = visitor.AssociationVisitor::Att.Data;
 AssociationVisitor::Att.Direction   = visitor.AssociationVisitor::Att.Direction;

 Att.Mode            = visitor.Att.Mode;
 Att.CommonDirection = visitor.Att.CommonDirection;
 Att.CallCounter     = visitor.Att.CallCounter;
// Att.FilterNumber    = visitor.Att.FilterNumber;

 Att.Word =  Att.Path.begin();

 list<const char*>::iterator Word = ((TiPa_Search)visitor).Att.Path.begin();
 while(Word != visitor.Att.Path.end())
 {
  char*      Text = new char[strlen(*Word)+1];
      memcpy(Text,*Word,strlen(*Word));
             Text[strlen(*Word)] = 0;
  Att.Path.push_back(Text);

  if(Word == visitor.Att.Word)
  {
   Att.Word = Att.Path.end(); // end-iterator is no element
   -- Att.Word;               // last element
  }
  ++Word;
 }

 return(*this);
}








/* @MRTZ_describe init

*/
void TiPa_Search::init(SearchMode_TP mode, const char* path, char separator, int indexStart)
{
 Att.CommonDirection = IterateAsBefore;
 Att.Mode            = mode;                       // set mode of search and evaluation
 Att.CallCounter     = indexStart;

 while(!(Att.Path.empty()))
 {
  delete[](*Att.Path.begin());
  Att.Path.pop_front();
 }

 if((path != nullptr)&&(strlen(path)>0))       // given path is valid
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



/* @MRTZ_ describe operator()

*/
TiPa_Search* TiPa_Search::operator()(SearchMode_TP mode, const char* path, char separator, int indexStart)
{
  TiPa_Visitor::init();
  this->init(mode, path, separator, indexStart);

 return(this);
}



/* @MRTZ_describe setCallCounter

*/
void TiPa_Search::setCallCounter(int indexStart)
{
 Att.CallCounter = indexStart;
}




/* @MRTZ_describe evaluate

*/
DirectionOfIteration TiPa_Search::evaluate(DataAssociation* node/*, DataAssociation* sponsor*/)
{
 if(Att.CommonDirection != IterateAsBefore)            //direction was temporarily changed after previous evaluation
 {
  TiPa_Visitor::Att.Direction = Att.CommonDirection;   // restore direction to iterate
  Att.CommonDirection         = IterateAsBefore;
 }
 else
 {
 }

 if(  (Att.Word                    != Att.Path.end())
    &&(node                        != nullptr)
    &&(TiPa_Visitor::Att.Direction != IterateNoMore)
   )
 {
  bool Found = false;
  switch(Att.Mode)
  {
   case TiPa_Search::Index :
   {
    Found = evaluateIndex(node,*Att.Word);
   }break;
//   case TiPa_Search::Operand :
//   {
//    Found = evaluateOperand(node,*Att.Word);
//   }break;
   case TiPa_Search::Content :
   {
    Found = evaluateContent(node,*Att.Word);
   }break;
   case TiPa_Search::UserName :
   {
    Found = evaluateUserName(node,*Att.Word);
   }break;
   case TiPa_Search::UserID       :
   case TiPa_Search::SearchMode_NV:
   default :
   {
   }break;
  }

  ++ Att.CallCounter;
  ++ Att.Word;
  if(  (Found    == true)
     &&(Att.Word != Att.Path.end())
     )                                                 // part evaluation succeeded and next part evaluation is existing
  {
   Att.CommonDirection = TiPa_Visitor::Att.Direction;  // next part evaluation
    TiPa_Visitor::Att.Direction = IterateDownwards;    // temporary change only
   LOG_OUTPUT(LOG_OFF, *Att.Word);
  }
  else if(  (Found    == true)
          &&(Att.Word == Att.Path.end())
         )                                             // part evaluation succeeded and last part evaluation is ready
  {
    TiPa_Visitor::Att.Direction = IterateNoMore;       // whole evaluation is not completed
  }
  else                                                 // nothing found
  {
   -- Att.Word;                                        // continue iteration with the same search-word as before
  }
 }
 return( TiPa_Visitor::Att.Direction);
}



/* @MRTZ_describe evaluateIndex

*/
bool TiPa_Search::evaluateIndex(DataAssociation* node, const char* word)
{
  bool        ReturnValue   = false;

  if(  (node != nullptr)
     &&(word != nullptr)
    )
  {
    int Value = atoi(word);

    if(Att.CallCounter == Value)
    {
     TiPa_Visitor::Att.Node      = node;
     TiPa_Visitor::Att.Data      = node->data_get();
     ReturnValue                                   = true;
    }
    else
    {
    }
   }
 return(ReturnValue);
}


/* @MRTZ_describe evaluateOperand

bool TiPa_Search::evaluateOperand(DataAssociation* node, const char* word)
{
  bool        ReturnValue   = false;

  if(  (node != nullptr)
     &&(word != nullptr)
    )
  {
   TiPa_Data* Data  = node->data_get();
   if(Data != nullptr)
   {
    int Value = atoi(word);

    if(Data->Operand == Value)
    {
     TiPa_Visitor::Att.Node      = node;
     TiPa_Visitor::Att.Data      = Data;
     ReturnValue                                   = true;
    }
    else
    {
    }
   }

  }
 return(ReturnValue);
}
*/


/* @MRTZ_describe evaluateContent

*/
bool TiPa_Search::evaluateContent(DataAssociation* node, const char* word)
{
 bool        ReturnValue   = false;

  if(  (node != nullptr)
     &&(word != nullptr)
    )
  {
   TiPa_Data* Data  = node->data_get();
   if(Data != nullptr)
   {
    if(  (strstr(Data->Begin,word) ==  Data->Begin             )
       &&(((int)strlen(word))      == (Data->End - Data->Begin))
      ) //content starts with word and has the same size
    {
     TiPa_Visitor::Att.Node      = node;
     TiPa_Visitor::Att.Data      = Data;
     ReturnValue                                   = true;
    }
    else
    {
    }
   }
  }
 return(ReturnValue);
}




/* @MRTZ_describe evaluateUserName

*/
bool TiPa_Search::evaluateUserName(DataAssociation* node, const char* word)
{
  bool        ReturnValue   = false;

  if(  (node != nullptr)
     &&(word != nullptr)
    )
  {
   TiPa_Data* Data  = node->data_get();
   if(Data != nullptr)
   {

    if(  (strstr(Data->userName_get(),word) ==        Data->userName_get() )
       &&(strlen(word)                      == strlen(Data->userName_get()))
      ) //content starts with word and has the same size
    {
     TiPa_Visitor::Att.Node      = node;
     TiPa_Visitor::Att.Data      = Data;
     ReturnValue                                   = true;

    }
    else
    {
    }

   }
  }
 return(ReturnValue);
}




#ifndef DOXYGEN
#define USING_NAMESPACE using namespace
//}; USING_NAMESPACE DATA;
//}; USING_NAMESPACE TDA_TinyParser;
//}; USING_NAMESPACE TXTDIASM;
#undef  USING_NAMESPACE
#endif //DOXYGEN



