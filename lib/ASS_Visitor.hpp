
/*!

 @file
 @brief abstract visitor of a data-tree

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
    08.08.2015     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    08.08.2015...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/
// @MRTZ_skip
#ifndef ASS_VISITOR_HPP
 #define ASS_VISITOR_HPP

#include <stdio.h>

#include "ASS_Visitor.h"
//#include "Association.h"


using namespace std;




/* @MRTZ_describe AssociationVisitor

*/
template <class DataType, DataType defaultData> AssociationVisitor<DataType, defaultData>::AssociationVisitor(void)
                                                                                          :Att()
{
 init();
}



/* @MRTZ_describe ~AssociationVisitor

*/
template <class DataType, DataType defaultData> AssociationVisitor<DataType, defaultData>::~AssociationVisitor(void)
{
}





/* @MRTZ_describe init

*/
template <class DataType, DataType defaultData> void AssociationVisitor<DataType, defaultData>::init(void)
{
 Att.Node        = nullptr;
 Att.Data        = defaultData;
 Att.Direction   = IterateNoMore;
}




/* @MRTZ_describe travel

*/
template <class DataType, DataType defaultData> void AssociationVisitor<DataType, defaultData>::travel(Association<DataType, defaultData>* node,
                                                                    Association<DataType, defaultData>* sponsor,
                                                                    DirectionOfIteration    firstDirection,
                                                                    DirectionOfIteration    secondDirection)
{
 Association<DataType, defaultData>* NextNode = node;


 while(  (NextNode                                       != nullptr)
       &&(Att.Direction != IterateNoMore)
      )                                                       // node is valid and evaluation is not complete
 {
  evaluate(NextNode);

  if(Att.Direction != IterateNoMore)  // current part evaluation is not complete
  {
   iterate(&NextNode,&sponsor,firstDirection);
  }
  else                                                        // current part evaluation is complete
  {
   Att.Direction != IterateNoMore;                                  // next part evaluation is not complete
   iterate(&NextNode,&sponsor,secondDirection);
  }
 }
}







/* @MRTZ_describe node_get

*/
template <class DataType, DataType defaultData>  Association<DataType, defaultData>* AssociationVisitor<DataType, defaultData>::node_get(void)
 {
  return(AssociationVisitor<DataType, defaultData>::Att.Node);
 }

 /* @MRTZ_describe node_set

*/
template <class DataType, DataType defaultData>  void AssociationVisitor<DataType, defaultData>::node_set(Association<DataType, defaultData>* node)
 {
  AssociationVisitor<DataType, defaultData>::Att.Node = node;
 }

 /* @MRTZ_describe data_get

*/
template <class DataType, DataType defaultData>  DataType AssociationVisitor<DataType, defaultData>::data_get(void)
 {
   return(AssociationVisitor<DataType, defaultData>::Att.Data);
 }

/* @MRTZ_describe data_set

*/
template <class DataType, DataType defaultData>  void AssociationVisitor<DataType, defaultData>::data_set(DataType data)
 {
  AssociationVisitor<DataType, defaultData>::Att.Data = data;
 }

/* @MRTZ_describe direction_set

*/
template <class DataType, DataType defaultData>  void AssociationVisitor<DataType, defaultData>::direction_set(DirectionOfIteration direction)
 {
  AssociationVisitor<DataType, defaultData>::Att.Direction = direction;
 }

/* @MRTZ_describe direction_get

*/
template <class DataType, DataType defaultData>  DirectionOfIteration AssociationVisitor<DataType, defaultData>::direction_get(void)
 {
  return(AssociationVisitor<DataType, defaultData>::Att.Direction);
 }










template <class DataType, DataType defaultData>   void AssociationVisitor<DataType, defaultData>::iterate(Association<DataType, defaultData>** node,
                                                                       Association<DataType, defaultData>** sponsor,
                                                                       DirectionOfIteration    direction)
{
  if(  (node!=nullptr)
     &&(sponsor!=nullptr)
    )
  {
   switch(direction)                                           // choose next node
   {
    case IterateForwards:
    {
     (*node) =(*sponsor)->contractorBehind_get(*node);
    }break;

    case IterateBackwards:
    {
     (*node) =(*sponsor)->contractorBefore_get(*node);
    }break;

    case IterateUpwards:
    {
     (*node) = (*node)->sponsor_get(*sponsor);
    }break;

    case IterateDownwards:
    {
     (*sponsor) = (*node);                                     // current node is sponsor of its contractors
     (*node)    = (*node)->contractorFirst_get();              // jump to first contractor
    }break;

    case IterateDownwardsReverse:
    {
     (*sponsor) = (*node);                                     // current node is sponsor of its contractors
     (*node)    = (*node)->contractorLast_get();               // jump to last contractor
    }break;

    default:
    {
     (*node) = nullptr;                                           //terminate loop
    }break;
   }
  }
 }







#endif // ASS_VISITOR_HPP

