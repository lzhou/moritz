/*!

 @file
 @brief concrete manager of tree_data
        representing the data of a grammar associated parser-tree

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
    01.09.2015     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    01.09.2015...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/
#include "Spirit185_Data.h"

#include "TiPa_Character.h"
#include "TiPa_String.h"
#include "TiPa_Counter.h"
#include "TiPa_Combination.h"
#include "TiPa_Rule.h"



#include <cstring>
#include <stdlib.h>
#include <iostream>


using namespace std;


#ifndef DOXYGEN
//namespace TXTDIASM {
//namespace TDA_Grammar {
//namespace DATA {
#endif //DOXYGEN





/* @MRTZ_describe Spirit185_Data

*/
Spirit185_Data::Spirit185_Data(void)
                :AssociationData()
{
//   SourceData = nullptr;            ///< original node-Data extended by this
//
//   UsingTerminated.clear();         ///< nodes used by this one
//   UsedByTerminated.clear();        ///< nodes which use this one
//   UsingRecursive.clear();          ///< nodes used by this one
//   UsedByRecursive.clear();         ///< nodes which use this one
//
//   LevelRoot = 0;                   ///< maximum number of terminated nested contractor-nodes
//   LevelLeaf = 0;                   ///< maximum number of  sponsor-nodes
//   Phrased   = true;                ///< white-space characters will be ignored if rule is phrased
}



/* @MRTZ_describe Spirit185_Data_2

*/
Spirit185_Data::Spirit185_Data(Spirit185_Data& data)
{
 SourceData = data.SourceData;              ///< original node-Data extended by this
 LevelRoot  = data.LevelRoot;                  ///< maximum number of terminated nested contractor-nodes
 LevelLeaf  = data.LevelLeaf;                  ///< maximum number of  sponsor-nodes
 Phrased    = data.Phrased;                    ///< white-space characters will be ignored if rule is phrased

 list<Spirit185_DataAssociation*>::iterator Node = data.UsingTerminated.begin();
                                               ///< nodes used by this one
 while(Node != data.UsingTerminated.end())
 {
  UsingTerminated.push_back(*Node);
  ++ Node;
 }

 Node = data.UsedByTerminated.begin();         ///< nodes which use this one
 while(Node != data.UsedByTerminated.end())
 {
  UsedByTerminated.push_back(*Node);
  ++ Node;
 }

 Node = data.UsingRecursive.begin();           ///< nodes used by this one
 while(Node != data.UsingRecursive.end())
 {
  UsingRecursive.push_back(*Node);
  ++ Node;
 }

 Node = data.UsedByRecursive.begin();          ///< nodes which use this one
 while(Node != data.UsedByRecursive.end())
 {
  UsedByRecursive.push_back(*Node);
  ++ Node;
 }

 map <int, const char*>::iterator DetailString = data.Detail.begin();
                                               ///< detailed data found while analysis
 while(DetailString != data.Detail.end())
 {
  Detail.insert(*DetailString);
  ++ DetailString;
 }

 set<Spirit185_DataAssociation*>::iterator Rule = data.CalledRule.begin();
                                              ///< nodes used by this one
 while(Rule != data.CalledRule.end())
 {
  CalledRule.insert(*Rule);
  ++ Rule;
 }

 Rule = data.CallingRule.begin();                  ///< nodes which use this one
 while(Rule != data.CallingRule.end())
 {
  CallingRule.insert(*Rule);
  ++ Rule;
 }

 list<AssociationData::SecondaryData_TP*>* SourceSecondaryData = data.secondaryData_get();
 list<AssociationData::SecondaryData_TP*>::iterator SourceSecondary = SourceSecondaryData->begin();
 while(SourceSecondary != SourceSecondaryData->end())
 {
  secondaryData_add((*SourceSecondary)->Key, (*SourceSecondary)->Val);
  ++ SourceSecondary;
 }

}







/* @MRTZ_describe ~Spirit185_Data

*/
Spirit185_Data::~Spirit185_Data(void)
{
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<""<<endl;
   SourceData = nullptr;              ///< original node-Data extended by this

   UsingTerminated.clear();         ///< nodes used by this one
   UsedByTerminated.clear();        ///< nodes which use this one
   UsingRecursive.clear();          ///< nodes used by this one
   UsedByRecursive.clear();         ///< nodes which use this one
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<""<<endl;

   if(  (Detail.find(Spirit185_Data::attUsing)  != Detail.end())
      &&((Detail[Spirit185_Data::attUsing])     != nullptr)
      &&(strlen(Detail[Spirit185_Data::attUsing]) > 0)
     )
   {
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<""<<endl;
//    cout << "|" << Detail[Spirit185_Data::attUsing] << "|" << strlen((Detail[Spirit185_Data::attUsing])) << endl;
//    if(strlen(Detail[Spirit185_Data::attUsing]) > 0)
     delete[](Detail[Spirit185_Data::attUsing]);
//    else
//     delete(Detail[Spirit185_Data::attUsing]);
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<""<<endl;
   }
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<""<<endl;
   if(  (Detail.find(Spirit185_Data::attUsedBy) != Detail.end())
      &&((Detail[Spirit185_Data::attUsedBy]) != nullptr)
      &&(strlen(Detail[Spirit185_Data::attUsedBy]) > 0)
     )
   {
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<""<<endl;
//    cout << "|" << Detail[Spirit185_Data::attUsedBy] << "|" << endl;
    delete[](Detail[Spirit185_Data::attUsedBy]);
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<""<<endl;
   }
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<""<<endl;
   if(  (Detail.find(Spirit185_Data::attLeafLevel) != Detail.end())
      &&((Detail[Spirit185_Data::attLeafLevel]) != nullptr)
      &&(strlen(Detail[Spirit185_Data::attLeafLevel]) > 0)
     )
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<""<<endl;
    delete[](Detail[Spirit185_Data::attLeafLevel]);
   if(  (Detail.find(Spirit185_Data::attRootLevel) != Detail.end())
      &&((Detail[Spirit185_Data::attRootLevel]) != nullptr)
      &&(strlen(Detail[Spirit185_Data::attRootLevel]) > 0)
     )
    delete[](Detail[Spirit185_Data::attRootLevel]);
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<""<<endl;
//   if(Detail.find(Spirit185_Data::attV) != Detail.end())
//    delete[](Detail[Spirit185_Data::attV]);
   if(  (Detail.find(Spirit185_Data::attC) != Detail.end())
      &&((Detail[Spirit185_Data::attC]) != nullptr)
      &&(strlen(Detail[Spirit185_Data::attC]) > 0)
     )
    delete[](Detail[Spirit185_Data::attC]);
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<""<<endl;
}





/* @MRTZ_describe operator=

*/
Spirit185_Data& Spirit185_Data::operator= (Spirit185_Data& data)
{
 if(this != &data)
 {
  SourceData = data.SourceData;              ///< original node-Data extended by this
  LevelRoot  = data.LevelRoot;                  ///< maximum number of terminated nested contractor-nodes
  LevelLeaf  = data.LevelLeaf;                  ///< maximum number of  sponsor-nodes
  Phrased    = data.Phrased;                    ///< white-space characters will be ignored if rule is phrased

  list<Spirit185_DataAssociation*>::iterator Node = data.UsingTerminated.begin();
                                                ///< nodes used by this one
  while(Node != data.UsingTerminated.end())
  {
   UsingTerminated.push_back(*Node);
   ++ Node;
  }

  Node = data.UsedByTerminated.begin();         ///< nodes which use this one
  while(Node != data.UsedByTerminated.end())
  {
   UsedByTerminated.push_back(*Node);
   ++ Node;
  }

  Node = data.UsingRecursive.begin();           ///< nodes used by this one
  while(Node != data.UsingRecursive.end())
  {
   UsingRecursive.push_back(*Node);
   ++ Node;
  }

  Node = data.UsedByRecursive.begin();          ///< nodes which use this one
  while(Node != data.UsedByRecursive.end())
  {
   UsedByRecursive.push_back(*Node);
   ++ Node;
  }

  map <int, const char*>::iterator DetailString = data.Detail.begin();
                                                ///< detailed data found while analysis
  while(DetailString != data.Detail.end())
  {
   Detail.insert(*DetailString);
   ++ DetailString;
  }

  set<Spirit185_DataAssociation*>::iterator Rule = data.CalledRule.begin();
                                               ///< nodes used by this one
  while(Rule != data.CalledRule.end())
  {
   CalledRule.insert(*Rule);
   ++ Rule;
  }

  Rule = data.CallingRule.begin();                  ///< nodes which use this one
  while(Rule != data.CallingRule.end())
  {
   CallingRule.insert(*Rule);
   ++ Rule;
  }

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
bool Spirit185_Data::isRealSecondaryData(CONST_CHAR_UNUSED* data)
{
 return(true); // this class is nor declaring string pointers
}












#ifndef DOXYGEN
#define USING_NAMESPACE using namespace
//}; USING_NAMESPACE DATA;
//}; USING_NAMESPACE TDA_Grammar;
//}; USING_NAMESPACE TXTDIASM;
#undef  USING_NAMESPACE
#endif //DOXYGEN
