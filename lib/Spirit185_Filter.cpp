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
    16.12.2015     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    16.12.2015...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/


#define DEBUG_OUTPUT_LOG
#include "LogOutput.h"




#include <stdio.h>
#include <cstdlib>
#include <set>
#include <limits.h>

#include "Spirit185_Filter.h"
#include "Spirit185_Internal.h"


using namespace std;


#ifndef DOXYGEN
//namespace TXTDIASM {
//namespace TDA_TinyParser {
//namespace DATA {
#endif //DOXYGEN

/* @MRTZ_describe Spirit185_Filter

*/
Spirit185_Filter::Spirit185_Filter()
                 :AssociationVisitor()
{
 Att.ContextModel   = nullptr;
 Att.KeepAboveID    = INT_MAX;
 Att.SkipAboveID    = INT_MAX;
 Att.LeafAboveID    = INT_MAX;
 Att.HideAboveID    = INT_MAX;
 Att.ParserProperty = nullptr;

 this->init(FilterMode_DF, CloneMode_DF, nullptr, nullptr, nullptr, nullptr);
}



/* @MRTZ_describe Spirit185_Filter

*/
Spirit185_Filter::Spirit185_Filter(TiPa_Concrete::DataModel* contextModel)
                 :AssociationVisitor()
{
 Att.ContextModel   = contextModel;
 Att.KeepAboveID    = INT_MAX;
 Att.SkipAboveID    = INT_MAX;
 Att.LeafAboveID    = INT_MAX;
 Att.HideAboveID    = INT_MAX;
 Att.ParserProperty = nullptr;

 this->init(FilterMode_DF, CloneMode_DF, nullptr, nullptr, nullptr, nullptr);
}



/* @MRTZ_describe Spirit185_Filter
  just call init
*/
Spirit185_Filter::Spirit185_Filter(Spirit185_Filter::FilterMode_TP mode,
                                   Spirit185_Filter::CloneMode_TP  cloneMode,
                map<TiPa_Concrete*, TDA_GrmConcrete::Property_TP>* parserProperty,
                                 TiPa_Concrete::DataModel*         contextModel,
                                        set<int>*                  keepNodes,
                                        set<int>*                  skipNodes,
                                        set<int>*                  leafNodes,
                                        set<int>*                  hideNodes)
            :AssociationVisitor()
{
 Att.ContextModel   = contextModel;
 Att.KeepAboveID    = INT_MAX;
 Att.SkipAboveID    = INT_MAX;
 Att.LeafAboveID    = INT_MAX;
 Att.HideAboveID    = INT_MAX;
 Att.ParserProperty = parserProperty;

 this->init(mode, cloneMode, keepNodes, skipNodes, leafNodes, hideNodes) ;
}





/* @MRTZ_describe ~Spirit185_Filter

*/
Spirit185_Filter::~Spirit185_Filter(void)
{
   Att.KeepNodes.clear();
   Att.SkipNodes.clear();
   Att.LeafNodes.clear();
   Att.HideNodes.clear();
}




/* @MRTZ_describe init

*/
void Spirit185_Filter::init(Spirit185_Filter::FilterMode_TP mode,
                            Spirit185_Filter::CloneMode_TP  cloneMode,
                            set<int>*                       keepNodes,
                            set<int>*                       skipNodes,
                            set<int>*                       leafNodes,
                            set<int>*                       hideNodes )
{
 Att.CommonDirection = IterateAsBefore;
 Att.Mode            = mode;                       // set mode of store or restore
 Att.CloneMode       = cloneMode;


 //Att.RootAssociation = nullptr;

 LOG_OUTPUT(LOG_OFF, "Spirit185_Filter::init");


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
void Spirit185_Filter::contextModel_set(TiPa_Concrete::DataModel* contextModel)
{
 Att.ContextModel = contextModel;
}



/* @MRTZ_describe operator()

*/
Spirit185_Filter* Spirit185_Filter::operator()(Spirit185_Filter::FilterMode_TP mode,
                                               TiPa_Concrete::DataAssociation* destination,
                                               Spirit185_Filter::CloneMode_TP  cloneMode)
{

 LOG_OUTPUT(LOG_OFF, "Spirit185_Filter::operator()");

 TiPa_Visitor::init();
 this->init(mode, cloneMode, nullptr, nullptr, nullptr, nullptr);

 TiPa_Visitor::Att.Node = destination;

 return(this);
}




/* @MRTZ_ describe specialNodes_set

*/
void Spirit185_Filter::specialNodes_set(SpecialNodes_TP nodeType,
                                        const char*     separatedList,
                                        char            separator)
{

 set<int>* SpecialNodes = nullptr;
 switch(nodeType)
 {
  case Spirit185_Filter::NodesToKeep: SpecialNodes = &(Att.KeepNodes); break;
  case Spirit185_Filter::NodesToSkip: SpecialNodes = &(Att.SkipNodes); break;
  case Spirit185_Filter::NodesAsLeaf: SpecialNodes = &(Att.LeafNodes); break;
  case Spirit185_Filter::NodesToHide: SpecialNodes = &(Att.HideNodes); break;
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
void Spirit185_Filter::specialNodes_set(SpecialNodes_TP nodeType,
                                   int             lowerLimit)
{
 switch(nodeType)
 {
  case Spirit185_Filter::NodesToKeep: Att.KeepAboveID = lowerLimit; break;
  case Spirit185_Filter::NodesToSkip: Att.SkipAboveID = lowerLimit; break;
  case Spirit185_Filter::NodesAsLeaf: Att.LeafAboveID = lowerLimit; break;
  case Spirit185_Filter::NodesToHide: Att.HideAboveID = lowerLimit; break;
  default                      : {                       } break;
 }

}



/* @MRTZ_ describe specialNodes_set

*/
void Spirit185_Filter::specialNodes_insert(SpecialNodes_TP nodeType,
                                           int             idToFilter)
{
 switch(nodeType)
 {
  case Spirit185_Filter::NodesToKeep: Att.KeepNodes.insert(idToFilter); break;
  case Spirit185_Filter::NodesToSkip: Att.SkipNodes.insert(idToFilter); break;
  case Spirit185_Filter::NodesAsLeaf: Att.LeafNodes.insert(idToFilter); break;
  case Spirit185_Filter::NodesToHide:
  default                           : {                               } break;
 }

}





/* @MRTZ_ describe specialNodes_set

*/
void Spirit185_Filter::specialNodes_search(SpecialNodes_TP nodeType,
                                           const char*     separatedList,
                                           char            separator)
{
 set<int>* SpecialNodes = nullptr;
 switch(nodeType)
 {
  case Spirit185_Filter::NodesToKeep: SpecialNodes = &(Att.KeepNodes); break;
  case Spirit185_Filter::NodesToSkip: SpecialNodes = &(Att.SkipNodes); break;
  case Spirit185_Filter::NodesAsLeaf: SpecialNodes = &(Att.LeafNodes); break;
  case Spirit185_Filter::NodesToHide: SpecialNodes = &(Att.HideNodes); break;
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
void Spirit185_Filter::specialNode_search(SpecialNodes_TP nodeType,
                                          const char*     parserName)
{
 map<TiPa_Concrete*, TDA_GrmConcrete::Property_TP>::iterator Property;
 set<int>* SpecialNodes = nullptr;
 switch(nodeType)
 {
  case Spirit185_Filter::NodesToKeep: SpecialNodes = &(Att.KeepNodes); break;
  case Spirit185_Filter::NodesToSkip: SpecialNodes = &(Att.SkipNodes); break;
  case Spirit185_Filter::NodesAsLeaf: SpecialNodes = &(Att.LeafNodes); break;
  case Spirit185_Filter::NodesToHide: SpecialNodes = &(Att.HideNodes); break;
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
void Spirit185_Filter::parserProperties_set(map<TiPa_Concrete*, TDA_GrmConcrete::Property_TP>* parserProperties)
{
 Att.ParserProperty = parserProperties;
}








/* @MRTZ_describe evaluate

*/
DirectionOfIteration Spirit185_Filter::evaluate(TiPa_Concrete::DataAssociation* node/*, TiPa_Concrete::DataAssociation* sponsor*/)
{
 LOG_OUTPUT(LOG_OFF, "Spirit185_Filter::evaluate");

 if(  (node             != nullptr)
    &&(Att.ContextModel != nullptr)
   )
 {
  if(TiPa_Visitor::Att.Node == nullptr)
  {
   if(node->as_AssociationFellowship()!=nullptr)
    TiPa_Visitor::Att.Node = Att.ContextModel->fellow_create(node);
   else
    {/*TiPa_Visitor::Att.Node = nullptr;*/}
//   else if(node->as_AssociationSponsor()!=nullptr)
//    TiPa_Visitor::Att.Node = Att.ContextModel->sponsor_create(node);
  }
  else
  {
   //nothing to do since destination was defined outside
  }

  switch(Att.Mode)
  {
   case Spirit185_Filter::KeepUndefined :
   {
    evaluateSkip(node,TiPa_Visitor::Att.Node);                                //store root node
    TiPa_Visitor::Att.Data = TiPa_Visitor::Att.Node->data_get();                    //store root-node data
    TiPa_Visitor::Att.Direction = IterateNoMore;

   }break;
   case Spirit185_Filter::SkipUndefined :
   {
    evaluateKeep(node,TiPa_Visitor::Att.Node);                                //store root node
    TiPa_Visitor::Att.Data = TiPa_Visitor::Att.Node->data_get();                    //store root-node data
    TiPa_Visitor::Att.Direction = IterateNoMore;

   }break;
   default :
   {
   }break;
  }
 }
 else if(Att.ContextModel==nullptr)
 {
   cout << "filter without context model called !" << endl ;
 }
 else
 {
 }

 return(TiPa_Visitor::Att.Direction);
}




/* @MRTZ_describe evaluateKeep

*/
TiPa_Concrete::DataAssociation* Spirit185_Filter::evaluateKeep(TiPa_Concrete::DataAssociation* source,
                                                   TiPa_Concrete::DataAssociation* destination)
{
 if(destination == nullptr)
 {
  if(source->as_AssociationFellowship()!=nullptr)
   destination = Att.ContextModel->fellow_create(source);
  else
   {/*destination = nullptr*/};
//  else if(source->as_AssociationSponsor()!=nullptr)
//   destination = Att.ContextModel->sponsor_create(source);
 }
 else
 {
  //nothing to do since destination was defined outside
 }


 TiPa_Concrete::DataAssociation* ContractorIn = source->contractorFirst_get();
 while(ContractorIn != nullptr)
 {
  if(ContractorIn->data_get() != nullptr)
  {
   TiPa_Data* Data  = nullptr;
   if(Att.CloneMode == ReuseData)
    Data = ContractorIn->data_get();
   else
    Data = Att.ContextModel->data_create(ContractorIn->data_get());

   if(  (Data->UserID                     >= Att.KeepAboveID)
      ||(Att.KeepNodes.find(Data->UserID) != Att.KeepNodes.end())
     )
   //actions for associations which contain needed data to keep
   //and which contain sub-associations with additional data
   {
    TiPa_Concrete::DataAssociation* NewAssociation = nullptr;
    if(destination->as_AssociationFellowship()!=nullptr)
     NewAssociation = Att.ContextModel->fellow_create(Data);
    else
    {/* NewAssociation = nullptr; */}
//    else if(destination->as_AssociationSponsor()!=nullptr)
//     NewAssociation = Att.ContextModel->sponsor_create(Data);

    destination->contractorLast_add(NewAssociation); // add new node to destination tree
    evaluateKeep(ContractorIn,NewAssociation);       // recursive continue of analysis
   }
   else if(  (Data->UserID                     >= Att.LeafAboveID)
           ||(Att.LeafNodes.find(Data->UserID) != Att.LeafNodes.end())
          )
   //actions for associations which contain needed data
   //but which contain no sub-associations with additional needed data
   {
    TiPa_Concrete::DataAssociation* NewAssociation = nullptr;
    if(destination->as_AssociationFellowship()!=nullptr)
     NewAssociation = Att.ContextModel->fellow_create(Data);
    else
    {/* NewAssociation = nullptr; */}
//    else if(destination->as_AssociationSponsor()!=nullptr)
//     NewAssociation = Att.ContextModel->sponsor_create(Data);
    destination->contractorLast_add(NewAssociation); // add new node to destination tree
   }
   else
   //actions for associations which don't contain needed to create a parser
   //but which contain sub-associations with needed data
   {
    evaluateKeep(ContractorIn,destination);          // recursive continue of analysis
   }
  }
  else
  {
   LOG_OUTPUT(LOG_OFF, "data content of association node is not valid");
  }
  ContractorIn = ContractorIn->fellowBehind_get();
 }

 return(destination);
}




/* @MRTZ_describe evaluateKeep

*/
TiPa_Concrete::DataAssociation* Spirit185_Filter::evaluateSkip(TiPa_Concrete::DataAssociation* source,
                                                        TiPa_Concrete::DataAssociation* destination)
{

 if(destination == nullptr)
 {
  if(source->as_AssociationFellowship()!=nullptr)
   destination = Att.ContextModel->fellow_create(source);
  else
   {/*destination = nullptr;*/}
//  else if(source->as_AssociationSponsor()!=nullptr)
//   destination = Att.ContextModel->sponsor_create(source);
 }
 else
 {
  //nothing to do since destination was defined outside
 }


 TiPa_Concrete::DataAssociation* ContractorIn = source->contractorFirst_get();
 while(ContractorIn != nullptr)
 {

  if(ContractorIn->data_get() != nullptr)
  {
   TiPa_Data* Data  = nullptr;
   if(Att.CloneMode == ReuseData)
    Data = ContractorIn->data_get();
   else
   {
//    cout << "................" << endl;
    Data = Att.ContextModel->data_create(ContractorIn->data_get());
    //Data->getContent();
   }

   if(  (Data->UserID                     >= Att.HideAboveID)
      ||(Att.HideNodes.find(Data->UserID) != Att.HideNodes.end())
     )  // nodes which should be hidden
   {
    // do nothing
   }
   else if(  (  (Data->UserID                     >= Att.SkipAboveID)
              ||(Att.SkipNodes.find(Data->UserID) != Att.SkipNodes.end())
             )
           &&(ContractorIn->contractorFirst_get() != nullptr)
           )
   //actions for associations which don't contain needed to create a parser
   //but which contain sub-associations with needed data
   {
    evaluateSkip(ContractorIn,destination);          // recursive continue of analysis

   }
   else if(  (Data->UserID                        >= Att.LeafAboveID)
           ||(Att.LeafNodes.find(Data->UserID)    != Att.LeafNodes.end())
           ||(  (ContractorIn->contractorFirst_get() == nullptr)
              &&(  (Data->ParserClass == TiPa_Abstract::TDA_TiPa_String)
                 ||(Data->ParserClass == TiPa_Abstract::TDA_TiPa_Character)
                )
             )
          )
   //actions for associations which contain needed data
   //but which contain no sub-associations with additional needed data
   {
    TiPa_Concrete::DataAssociation* NewAssociation = nullptr;
    if(destination->as_AssociationFellowship()!=nullptr)
     NewAssociation = Att.ContextModel->fellow_create(Data);
    else
     {/*NewAssociation = nullptr;*/}
//    else if(destination->as_AssociationSponsor()!=nullptr)
//     NewAssociation = Att.ContextModel->sponsor_create(Data);
    destination->contractorLast_add(NewAssociation); // add new node to destination tree
   }
   else if(ContractorIn->contractorFirst_get() != nullptr)
   //actions for associations which contain needed data to keep
   //and which contain sub-associations with additional data
   {
    TiPa_Concrete::DataAssociation* NewAssociation = nullptr;
    if(destination->as_AssociationFellowship()!=nullptr)
     NewAssociation = Att.ContextModel->fellow_create(Data);
    else
     {/*NewAssociation = nullptr;*/}
//    else if(destination->as_AssociationSponsor()!=nullptr)
//     NewAssociation = Att.ContextModel->sponsor_create(Data);
    destination->contractorLast_add(NewAssociation); // add new node to destination tree
    evaluateSkip(ContractorIn,NewAssociation);       // recursive continue of analysis

    if(  (Data->columnGet()    != nullptr)
       &&(Data->columnGet()[0] == '-')
      )// column number is existing but not valid
    {
     TiPa_Data*  ChildData   = NewAssociation->contractorFirst_get()->data_get();             // get first contractor-data
//     const char* ChildColumn = ChildData->columnGet();                                             // column number of contractor-data
//     char* StringC = new char[strlen(ChildColumn) +1];                                        // new string
//
//     strcpy(StringC,ChildColumn);                                                             // copy contractor column
//     StringC[strlen(ChildColumn)] = 0;                                                        // terminate string
//
//     delete[](Data->Column);                         // delete old column number
//     Data->Column = StringC;                         // assign new column number

     Data->columnSet(atoi(ChildData->columnGet()));
    }

   }
   else
   {
   }
  }
  else
  {
   LOG_OUTPUT(LOG_OFF, "data content of association node is not valid");
  }
  ContractorIn = ContractorIn->fellowBehind_get();
 }

 return(destination);
}









#ifndef DOXYGEN
#define USING_NAMESPACE using namespace
//}; USING_NAMESPACE DATA;
//}; USING_NAMESPACE TDA_TinyParser;
//}; USING_NAMESPACE TXTDIASM;
#undef  USING_NAMESPACE
#endif //DOXYGEN



