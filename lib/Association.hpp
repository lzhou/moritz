/*!

 @file
 @brief manager of a data-tree

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
    22.08.2015     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    22.08.2015...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/
// @MRTZ_skip
#ifndef TDA_ASSOCIATION_HPP
 #define TDA_ASSOCIATION_HPP

#include "Association.h"
//#include "TDA_GrmConcrete.h"

//#define DEBUG_OUTPUT_LOG
#include "LogOutput.h"



#include <cstring>
#include <iostream>


#define INLINE_1 inline

#ifndef DOXYGEN
////namespace TXTDIASM {
//namespace ASSOCIATION {
#endif //DOXYGEN

/* @MRTZ_describe Association

*/
template <class DataType, DataType defaultData>
Association<DataType, defaultData>::Association(void)
                                 :Data(defaultData)
{
}

/* @MRTZ_describe Association

*/
template <class DataType, DataType defaultData>
Association<DataType, defaultData>::Association(DataType data)
                                   :Data(data)
 {
 }

/* @MRTZ_describe Association

*/
template <class DataType, DataType defaultData>
Association<DataType, defaultData>::Association(const Association<DataType, defaultData>& association)
                                   :Data(association.Data)
{
}


/* @MRTZ_describe operator=

*/
template <class DataType, DataType defaultData> inline
Association<DataType, defaultData>& Association<DataType, defaultData>::operator= (const Association<DataType, defaultData>& association)
{
 Data = association.Data;
 return(*this);
}




/* @MRTZ_describe ~Association

*/
template <class DataType, DataType defaultData>  Association<DataType, defaultData>::~Association(void)
{
}


/* @MRTZ_describe as_AssociationSponsor

template <class DataType, DataType defaultData> inline / *INLINE_1* /
AssociationSponsor<DataType, defaultData>* Association<DataType, defaultData>::as_AssociationSponsor(void)
{
 return(nullptr);
}
*/

/* @MRTZ_describe as_AssociationFellowship

*/
template <class DataType, DataType defaultData> inline /*INLINE_1*/
AssociationFellowship<DataType, defaultData>* Association<DataType, defaultData>::as_AssociationFellowship(void)
{
 return(nullptr);
}




/* @MRTZ_describe newObject

*/
template <class DataType, DataType defaultData> inline /*INLINE_1*/
Association<DataType, defaultData>* Association<DataType, defaultData>::newObject(void)
{
 return(nullptr);
}




/* @MRTZ_describe Data_set
   simple assignment of attribute
*/
template <class DataType, DataType defaultData> inline /*INLINE_1*/
void Association<DataType, defaultData>::data_set(DataType data)
{
 Data = data;
}



/* @MRTZ_describe data_get
   simple return of attribute
*/
template <class DataType, DataType defaultData> inline /*INLINE_1*/
DataType Association<DataType, defaultData>::data_get(void)
{
 return (Data);
}








/* @MRTZ_describe deleteNode

*/
template <class DataType, DataType defaultData>
Association<DataType, defaultData>*  Association<DataType, defaultData>::deleteNode(Association<DataType, defaultData>* node,
                                                                                    Association<DataType, defaultData>* sponsor)
{
 Association<DataType, defaultData>* ReturnValue    = node;      //prepare a return of process failed
 Association<DataType, defaultData>* Contractor     = nullptr;   //loop over contractors

 if(node == nullptr)                                             //node is not a valid node
  node = this;                                                   //used for calling node

 Contractor = node->contractorFirst_get();                       //start with first contractor
 while(Contractor != nullptr)                                    //iteration over contractors
 {
  deleteNode(Contractor,sponsor);                                //delete contractors before node
  Contractor = node->contractorFirst_get();                      //next contractor
 }

 if(sponsor == nullptr)                                          //sponsor not defined
  sponsor = node->sponsor_get();                                 //try do get sponsor

 if(sponsor != nullptr)
  sponsor->cutNode(node);                                        //cut node from tree
 else
 {  }
 if(node != this)
 {
  delete(node);                                                  //eliminate node
  ReturnValue = nullptr;                                         //change return to process passed successfully
 }

 return(ReturnValue);                                            //return result
}







#ifndef DOXYGEN
#define USING_NAMESPACE using namespace
//}; USING_NAMESPACE ASSOCIATION;
//}; USING_NAMESPACE TXTDIASM;
#undef  USING_NAMESPACE
#endif //DOXYGEN


#endif //TDA_ASSOCIATION_HPP

