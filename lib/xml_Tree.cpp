/*!

 @file
 @brief create an xml-tree from xml-parser data

 Copyright (C) 2019-2020 by Eckard Klotz.

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
    27.12.2019     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    27.12.2019...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/


#define DEBUG_OUTPUT_LOG
#include "LogOutput.h"




#include <stdio.h>
#include <cstdlib>
#include <set>
#include <limits.h>

#include "xml_Tree.h"
#include "Spirit185_Internal.h"


using namespace std;



/* @MRTZ_describe XML_Tree

*/
XML_Tree::XML_Tree()
         :Att()
{
// Att.ContextModel   = nullptr;
// Att.KeepAboveID    = INT_MAX;
// Att.SkipAboveID    = INT_MAX;
// Att.LeafAboveID    = INT_MAX;
// Att.HideAboveID    = INT_MAX;
// Att.ParserProperty = nullptr;

 this->init(FilterMode_DF, /*CloneMode_DF, nullptr,*/ nullptr, nullptr, nullptr, nullptr);
}



/* @MRTZ_describe XML_Tree

*/
XML_Tree::XML_Tree(TiPa_Concrete::DataModel* contextModel,
                   TiPa_Concrete*            rootParser)
         :Att()
{
 Att.ContextModel   = contextModel;
 Att.RootParser     = rootParser;
// Att.KeepAboveID    = INT_MAX;
// Att.SkipAboveID    = INT_MAX;
// Att.LeafAboveID    = INT_MAX;
// Att.HideAboveID    = INT_MAX;
// Att.ParserProperty = nullptr;

 this->init(FilterMode_DF, nullptr, nullptr, nullptr, nullptr);
}



/* @MRTZ_describe XML_Tree
  just call init
*/
XML_Tree::XML_Tree(XML_Tree::FilterMode_TP         mode,
map<TiPa_Concrete*, TDA_GrmConcrete::Property_TP>* parserProperty,
                   TiPa_Concrete::DataModel*       contextModel,
                   TiPa_Concrete*                  rootParser,
                          set<int>*                keepNodes,
                          set<int>*                skipNodes,
                          set<int>*                leafNodes,
                          set<int>*                hideNodes)
         :Att()
{
 Att.ContextModel   = contextModel;
 Att.RootParser     = rootParser;
 Att.KeepAboveID    = INT_MAX;
 Att.SkipAboveID    = INT_MAX;
 Att.LeafAboveID    = INT_MAX;
 Att.HideAboveID    = INT_MAX;
 Att.ParserProperty = parserProperty;

 this->init(mode, keepNodes, skipNodes, leafNodes, hideNodes) ;
}





/* @MRTZ_describe ~XML_Tree

*/
XML_Tree::~XML_Tree(void)
{
 Att.KeepNodes.clear();
 Att.SkipNodes.clear();
 Att.LeafNodes.clear();
 Att.HideNodes.clear();
}




/* @MRTZ_describe init

*/
void XML_Tree::init(XML_Tree::FilterMode_TP mode,
                    set<int>*               keepNodes,
                    set<int>*               skipNodes,
                    set<int>*               leafNodes,
                    set<int>*               hideNodes )
{
 Att.CommonDirection = IterateAsBefore;
 Att.Mode            = mode;                       // set mode of store or restore

 LOG_OUTPUT(LOG_OFF, "XML_Tree::init");


 if(keepNodes != nullptr)
 {
  if(!(Att.KeepNodes.empty()))
   Att.KeepNodes.clear();
  Att.KeepNodes = (*keepNodes);
 }

 if(skipNodes != nullptr)
 {
  if(!(Att.SkipNodes.empty()))
   Att.SkipNodes.clear();
  Att.SkipNodes = (*skipNodes);
 }

 if(leafNodes != nullptr)
 {
  if(!(Att.LeafNodes.empty()))
   Att.LeafNodes.clear();
  Att.LeafNodes = (*leafNodes);
 }


 if(hideNodes != nullptr)
 {
  if(!(Att.HideNodes.empty()))
   Att.HideNodes.clear();
  Att.HideNodes = (*hideNodes);
 }
}

/* @MRTZ_describe contextModel_set

*/
void XML_Tree::contextModel_set(TiPa_Concrete::DataModel* contextModel)
{
 Att.ContextModel = contextModel;
}



/* @MRTZ_describe operator()

*/
//XML_Tree* XML_Tree::operator()(XML_Tree::FilterMode_TP mode,
//                               XML_Tree::DataFellow*   destination,
//                               const char*             text/*,
//                               XML_Tree::CloneMode_TP          cloneMode*/)
//{
//
// LOG_OUTPUT(LOG_OFF, "XML_Tree::operator()");
//
//// TiPa_Visitor::init();
// this->init(mode, /*cloneMode,text,*/  nullptr, nullptr, nullptr, nullptr);
//
// /*TiPa_Visitor::*/Att.Node = destination;
// return(this);
//}




/* @MRTZ_ describe specialNodes_set

*/
void XML_Tree::specialNodes_set(SpecialNodes_TP nodeType,
                                        const char*     separatedList,
                                        char            separator)
{

 set<int>* SpecialNodes = nullptr;
 switch(nodeType)
 {
  case XML_Tree::NodesToKeep: SpecialNodes = &(Att.KeepNodes); break;
  case XML_Tree::NodesToSkip: SpecialNodes = &(Att.SkipNodes); break;
  case XML_Tree::NodesAsLeaf: SpecialNodes = &(Att.LeafNodes); break;
  case XML_Tree::NodesToHide: SpecialNodes = &(Att.HideNodes); break;
  default:                            SpecialNodes = nullptr;          break;
 }

 if(!(SpecialNodes->empty()))
  SpecialNodes->clear();

 if((separatedList != nullptr)&&(strlen(separatedList)>0)) // given separatedList is valid
 {
  int          Size  = strlen(separatedList);           // length of  given separatedList
  const char*  Begin = separatedList;                   // begin of first separatedList-part
  const char*  End   = strchr(separatedList,separator); // end of first separatedList-part
  char*        Word  = new char[Size+1];                // container for current separatedList-part

  if(End==nullptr)                                // separatedList contains no separator
   End = separatedList + Size;                 // end of first separatedList-part is end of separatedList

  while(  (End   != nullptr)
        &&(Begin <  separatedList + Size)
       )                                       // begin and end are inside of separatedList
  {
    while(  (Begin[0] <'0')
          &&(Begin[0] >'9')
          &&(Begin    <  End)
         )                                     // non numerical character found and end of separated list not reached
     ++Begin;                                  // skip the character

   memcpy(Word,Begin,End-Begin);              // copy content of current separatedList-part
   Word[End-Begin] = 0;                        // ensure the termination of the string

   SpecialNodes->insert(atoi(Word));           // set reference data used for content-search
   Begin = End + 1;                            // begin of next separatedList-part
   End   = strchr(Begin,separator);            // end of next separatedList-part
   if(End==nullptr)                               // separatedList contains no more separator
    End = separatedList + Size;                // end of next separatedList-part is end of separatedList
  }
  delete[](Word);
 }
 else
 {
                                               // let Word and Number empty
 }


}






/* @MRTZ_ describe specialNodes_set

*/
void XML_Tree::specialNodes_set(SpecialNodes_TP nodeType,
                                   int             lowerLimit)
{
 switch(nodeType)
 {
  case XML_Tree::NodesToKeep: Att.KeepAboveID = lowerLimit; break;
  case XML_Tree::NodesToSkip: Att.SkipAboveID = lowerLimit; break;
  case XML_Tree::NodesAsLeaf: Att.LeafAboveID = lowerLimit; break;
  case XML_Tree::NodesToHide: Att.HideAboveID = lowerLimit; break;
  default                      : {                       } break;
 }

}



/* @MRTZ_ describe specialNodes_set

*/
void XML_Tree::specialNodes_insert(SpecialNodes_TP nodeType,
                                           int             idToFilter)
{
 switch(nodeType)
 {
  case XML_Tree::NodesToKeep: Att.KeepNodes.insert(idToFilter); break;
  case XML_Tree::NodesToSkip: Att.SkipNodes.insert(idToFilter); break;
  case XML_Tree::NodesAsLeaf: Att.LeafNodes.insert(idToFilter); break;
  case XML_Tree::NodesToHide:
  default                           : {                               } break;
 }

}





/* @MRTZ_ describe specialNodes_set

*/
void XML_Tree::specialNodes_search(SpecialNodes_TP nodeType,
                                           const char*     separatedList,
                                           char            separator)
{
 set<int>* SpecialNodes = nullptr;
 switch(nodeType)
 {
  case XML_Tree::NodesToKeep: SpecialNodes = &(Att.KeepNodes); break;
  case XML_Tree::NodesToSkip: SpecialNodes = &(Att.SkipNodes); break;
  case XML_Tree::NodesAsLeaf: SpecialNodes = &(Att.LeafNodes); break;
  case XML_Tree::NodesToHide: SpecialNodes = &(Att.HideNodes); break;
  default:                            SpecialNodes = nullptr;          break;
 }

 if(!(SpecialNodes->empty()))
  SpecialNodes->clear();

 if((separatedList != nullptr)&&(strlen(separatedList)>0)) // given separatedList is valid
 {
  int          Size  = strlen(separatedList);           // length of  given separatedList
  const char*  Begin = separatedList;                   // begin of first separatedList-part
  const char*  End   = strchr(separatedList,separator); // end of first separatedList-part
  char*        Word  = new char[Size+1];                // container for current separatedList-part

  if(End==nullptr)                                // separatedList contains no separator
   End = separatedList + Size;                 // end of first separatedList-part is end of separatedList

  while(  (End   != nullptr)
        &&(Begin <  separatedList + Size)
       )                                       // begin and end are inside of separatedList
  {
    while(  (Begin[0] <=  32)
          &&(Begin    <  End)
         )                                     // non numerical character found and end of separated list not reached
     ++Begin;                                  // skip the character

   memcpy(Word,Begin,End-Begin);              // copy content of current separatedList-part
   int  Index = 0;
   while(  (  (Index       <(End-Begin))
            &&(Word[Index] >  32)
            &&(Word[Index] != separator)
           )
        )                                     // non numerical character found and end of separated list not reached
   {
     ++Index;
   }
   Word[Index] = 0;                        // ensure the termination of the string

   specialNode_search(nodeType,Word);

   Begin = End + 1;                            // begin of next separatedList-part
   End   = strchr(Begin,separator);            // end of next separatedList-part
   if(End==nullptr)                               // separatedList contains no more separator
    End = separatedList + Size;                // end of next separatedList-part is end of separatedList

  }
  delete[](Word);
 }
 else
 {
                                               // let Word and Number empty
 }


}



/* @MRTZ_ describe specialNodes_set

*/
void XML_Tree::specialNode_search(SpecialNodes_TP nodeType,
                                          const char*     parserName)
{
 map<TiPa_Concrete*, TDA_GrmConcrete::Property_TP>::iterator Property;
 set<int>* SpecialNodes = nullptr;
 switch(nodeType)
 {
  case XML_Tree::NodesToKeep: SpecialNodes = &(Att.KeepNodes); break;
  case XML_Tree::NodesToSkip: SpecialNodes = &(Att.SkipNodes); break;
  case XML_Tree::NodesAsLeaf: SpecialNodes = &(Att.LeafNodes); break;
  case XML_Tree::NodesToHide: SpecialNodes = &(Att.HideNodes); break;
  default:                            SpecialNodes = nullptr;          break;
 }


 if(Att.ParserProperty != nullptr)
 {
  Property = Att.ParserProperty->begin();
  while( Property != Att.ParserProperty->end())
  {
   if(  (strstr(parserName, Property->second.Name) == parserName)
      &&(strlen(Property->second.Name)             == strlen(parserName))
     )
   {
    SpecialNodes->insert(Property->second.User_ID);           // set reference data used for content-search
    break;
   }
   ++ Property;
  }
 }
}






/* @MRTZ_ describe parserProperties_set

*/
void XML_Tree::parserProperties_set(map<TiPa_Concrete*, TDA_GrmConcrete::Property_TP>* parserProperties)
{
 Att.ParserProperty = parserProperties;
}








/* @MRTZ_describe evaluate

*/
XML_Tree::DataFellow* XML_Tree::evaluate(const char*   text,
                                         FilterMode_TP mode)
{
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"XML_Tree::evaluate enter"<<endl;
 XML_Tree::DataFellow* ReturnValue = Att.ContextModel->fellow_create();
 LOG_OUTPUT(LOG_OFF, "XML_Tree::evaluate");

  switch(mode)
  {
   case XML_Tree::KeepUndefined :
   {
    TiPa_Concrete::Hit_TP* Result  = Att.RootParser->result_Tree(text);
    TiPa_Data*             Data    = defineDataContent(Result);
    ReturnValue->data_set(Data);
    evaluateSkip(Result, ReturnValue);                                //store root node

   }break;
   case XML_Tree::SkipUndefined :
   {
    TiPa_Concrete::Hit_TP* Result  = Att.RootParser->result_Tree(text);

    TiPa_Data*             Data    = defineDataContent(Result);
    ReturnValue->data_set(Data);
    evaluateKeep(Result, ReturnValue);                                //store root node

   }break;
   default :
   {
   }break;
  }
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"XML_Tree::evaluate leave"<<endl;
 return(ReturnValue);
}




/* @MRTZ_describe evaluateKeep

*/
XML_Tree::DataFellow* XML_Tree::evaluateKeep(TiPa_Concrete::Hit_TP* result,
                                             XML_Tree::DataFellow*  destination)
{
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"XML_Tree::evaluateKeep enter" <<endl;

 if(result != nullptr)
 {
  map<const char*, TiPa_Abstract*>::iterator SubResult = result->SubParser.begin();               //dictionary of the sub-parsers which were used to identify the found text-part
  while(SubResult != result->SubParser.end())
  {
   if((SubResult->second)->as_TiPa_Concrete() != nullptr)
   {
    TiPa_Concrete*         Parser  = (SubResult->second)->as_TiPa_Concrete();
    const char*            Snippet =  SubResult->first;
    TiPa_Concrete::Hit_TP* Result  = Parser->result_Tree(Snippet);

    int Parser_UserID  = (*Att.ParserProperty)[Parser].User_ID;
    if(  (Parser_UserID                     >= Att.KeepAboveID)
       ||(Att.KeepNodes.find(Parser_UserID) != Att.KeepNodes.end())
      )
    //actions for associations which contain needed data to keep
    //and which contain sub-associations with additional data
    {
     if(destination == nullptr)
        destination = Att.ContextModel->fellow_create();

     TiPa_Data* Data = defineDataContent(Result);

     XML_Tree::DataFellow* NewAssociation = nullptr;
     if(destination->as_AssociationFellowship()!=nullptr)
      NewAssociation = Att.ContextModel->fellow_create(Data);
     else
     {/* NewAssociation = nullptr; */}

     destination->contractorLast_add(NewAssociation);    // add new node to destination tree
     evaluateKeep(Result, NewAssociation); // recursive continue of analysis
    }
    else if(  (Parser_UserID                     >= Att.LeafAboveID)
            ||(Att.LeafNodes.find(Parser_UserID) != Att.LeafNodes.end())
           )
    //actions for associations which contain needed data
    //but which contain no sub-associations with additional needed data
    {
     if(destination == nullptr)
        destination = Att.ContextModel->fellow_create();

     TiPa_Data* Data = defineDataContent(Result);

     XML_Tree::DataFellow* NewAssociation = nullptr;
     if(destination->as_AssociationFellowship()!=nullptr)
      NewAssociation = Att.ContextModel->fellow_create(Data);
     else
     {/* NewAssociation = nullptr; */}
     destination->contractorLast_add(NewAssociation);    // add new node to destination tree
    }
    else
    //actions for associations which don't contain needed to create a parser
    //but which contain sub-associations with needed data
    {
     evaluateKeep(Result, /*ContractorIn,*/ destination);    // recursive continue of analysis
    }
   }
   else
   {
    LOG_OUTPUT(LOG_OFF, "data content of association node is not valid");
   }
   ++ SubResult;
  }
 }
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"XML_Tree::evaluateKeep leave"<<endl;
 return(destination);
}




/* @MRTZ_describe evaluateSkip

*/
XML_Tree::DataFellow* XML_Tree::evaluateSkip(TiPa_Concrete::Hit_TP* result,
                                             XML_Tree::DataFellow*  destination)
{
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"XML_Tree::evaluateSkip enter"<<endl;

// if(destination == nullptr)
// {
//  if(source->as_AssociationFellowship()!=nullptr)
//   destination = Att.ContextModel->fellow_create(source);
//  else
//   {/*destination = nullptr;*/}
// }
// else
// {
//  //nothing to do since destination was defined outside
// }

 if(result != nullptr)
 {
// TiPa_Concrete::DataAssociation* ContractorIn = source->contractorFirst_get();
// while(ContractorIn != nullptr)
  map<const char*, TiPa_Abstract*>::iterator SubResult = result->SubParser.begin();               //dictionary of the sub-parsers which were used to identify the found text-part
  while(SubResult != result->SubParser.end())
  {

//  if(ContractorIn->data_get() != nullptr)
   if((SubResult->second)->as_TiPa_Concrete() != nullptr)
   {
    TiPa_Concrete*         Parser  = (SubResult->second)->as_TiPa_Concrete();
    const char*            Snippet =  SubResult->first;
    TiPa_Concrete::Hit_TP* Result  = Parser->result_Tree(Snippet);
//   TiPa_Data* Data  = nullptr;
//   if(Att.CloneMode == ReuseData)
//    Data = ContractorIn->data_get();
//   else
//   {
//    Data = Att.ContextModel->data_create(ContractorIn->data_get());
//   }
//   if(  (Data->UserID                     >= Att.HideAboveID)
//      ||(Att.HideNodes.find(Data->UserID) != Att.HideNodes.end())
//     )  // nodes which should be hidden
    int Parser_UserID  = (*Att.ParserProperty)[Parser].User_ID;

    if(  (Parser_UserID                     >= Att.HideAboveID)
       ||(Att.HideNodes.find(Parser_UserID) != Att.HideNodes.end())
      )  // nodes which should be hidden
    {
     // do nothing
    }
//   else if(  (  (Data->UserID                     >= Att.SkipAboveID)
//              ||(Att.SkipNodes.find(Data->UserID) != Att.SkipNodes.end())
//             )
//           &&(ContractorIn->contractorFirst_get() != nullptr)
//           )
    else if(  (  (Parser_UserID                     >= Att.SkipAboveID)
               ||(Att.SkipNodes.find(Parser_UserID) != Att.SkipNodes.end())
              )
//           &&(ContractorIn->contractorFirst_get() != nullptr)
            &&(Result->SubParser.empty()            != true)
            )
    //actions for associations which don't contain needed to create a parser
    //but which contain sub-associations with needed data
    {
     evaluateSkip(Result, /*ContractorIn,*/ destination);          // recursive continue of analysis

    }
//   else if(  (Data->UserID                        >= Att.LeafAboveID)
//           ||(Att.LeafNodes.find(Data->UserID)    != Att.LeafNodes.end())
//           ||(  (ContractorIn->contractorFirst_get() == nullptr)
//              &&(  (Data->ParserClass == TiPa_Abstract::TDA_TiPa_String)
//                 ||(Data->ParserClass == TiPa_Abstract::TDA_TiPa_Character)
//                )
//             )
//          )
    else if(  (Parser_UserID                        >= Att.LeafAboveID)
            ||(Att.LeafNodes.find(Parser_UserID)    != Att.LeafNodes.end())
//           ||(  (ContractorIn->contractorFirst_get() == nullptr)
            ||(  (Result->SubParser.empty() != true)
               &&(  (Parser->id_Type()      == TiPa_Abstract::TDA_TiPa_String)
                  ||(Parser->id_Type()      == TiPa_Abstract::TDA_TiPa_Character)
                 )
              )
           )
    //actions for associations which contain needed data
    //but which contain no sub-associations with additional needed data
    {
     if(destination == nullptr)
        destination = Att.ContextModel->fellow_create();

     TiPa_Data* Data = defineDataContent(result);

     XML_Tree::DataFellow* NewAssociation = nullptr;
     if(destination->as_AssociationFellowship()!=nullptr)
      NewAssociation = Att.ContextModel->fellow_create(Data);
     else
      {/*NewAssociation = nullptr;*/}
     destination->contractorLast_add(NewAssociation);    // add new node to destination tree
    }
//   else if(ContractorIn->contractorFirst_get() != nullptr)
    else if(Result->SubParser.empty() != true)
    //actions for associations which contain needed data to keep
    //and which contain sub-associations with additional data
    {
     if(destination == nullptr)
        destination = Att.ContextModel->fellow_create();

     TiPa_Data* Data = defineDataContent(result);

     XML_Tree::DataFellow* NewAssociation = nullptr;
     if(destination->as_AssociationFellowship()!=nullptr)
      NewAssociation = Att.ContextModel->fellow_create(Data);
     else
      {/*NewAssociation = nullptr;*/}
     destination->contractorLast_add(NewAssociation);    // add new node to destination tree
     evaluateSkip(Result, /*ContractorIn,*/ NewAssociation); // recursive continue of analysis

//    if(  (Data->columnGet()    != nullptr)
//       &&(Data->columnGet()[0] == '-')
//      )// column number is existing but not valid
//    {
//     TiPa_Data*  ChildData   = NewAssociation->contractorFirst_get()->data_get();             // get first contractor-data
//
//     Data->columnSet(atoi(ChildData->columnGet()));
//    }

    }
    else
    {
    }
   }
   else
   {
    LOG_OUTPUT(LOG_OFF, "data content of association node is not valid");
   }
//  ContractorIn = ContractorIn->fellowBehind_get();
   ++ SubResult;
  }
 }
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"XML_Tree::evaluateSkip leave"<<endl;
 return(destination);
}



TiPa_Data* XML_Tree::defineDataContent(TiPa_Concrete::Hit_TP* source)
{
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"XML_Tree::defineDataContent enter" <<endl;
 TiPa_Data* Data = Att.ContextModel->data_create();
 if(source != nullptr)
 {
  Data->Begin       = source->Begin;
  Data->End         = source->End;
  Data->Parser      = source->Parser;

  if(  (   source->Parser
        != nullptr
       )
     &&(   Att.ParserProperty
        != nullptr
       )
     &&(   Att.ParserProperty->find(source->Parser->as_TiPa_Concrete())
        != Att.ParserProperty->end()
       )
    )
  {
   Data->ParserClass = source->Parser->id_Type();
   TDA_GrmConcrete::Property_TP Property = (*Att.ParserProperty)[source->Parser->as_TiPa_Concrete()];

   Data->UserID = Property.User_ID;
   Data->userName_set(Property.Name);
//   Data->user_ID_String_set(Property.User_ID_String);
//   Data->userDescription_set(Property.Description);
  }
 }

//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"XML_Tree::defineDataContent leave"<<endl;
 return(Data);
}






