/*!

 @file
 @brief sponsor of a data-tree

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
#ifndef ASSOCIATION_FELLOWSHIP_HPP
 #define ASSOCIATION_FELLOWSHIP_HPP


#include "AssociationFellowship.h"
//#include "TDA_GrmConcrete.h"

#include <cstring>
#include <iostream>

//#define DEBUG_OUTPUT_LOG
#include "LogOutput.h"



#define INLINE_1 inline
#define INLINE_2 inline

#ifndef DOXYGEN
////namespace TXTDIASM {
//namespace ASSOCIATION {
#endif //DOXYGEN

/* @MRTZ_describe AssociationFellowship

*/
template <class DataType, DataType defaultData>
 AssociationFellowship<DataType, defaultData>::AssociationFellowship(void)
                                              :Association<DataType, defaultData>(),
                                               Att()
 {
//  Att.Sponsor         = nullptr;
//  Att.ContractorFirst = nullptr;
//  Att.ContractorLast  = nullptr;
//  Att.FellowBefore    = nullptr;
//  Att.FellowBehind    = nullptr;

 }

/* @MRTZ_describe AssociationFellowship
  transfer data to base-class constructor
*/
template <class DataType, DataType defaultData>
AssociationFellowship<DataType, defaultData>::AssociationFellowship(DataType data)
                                             :Association<DataType, defaultData>(data),
                                              Att()
{
//Att.Sponsor         = nullptr;
//Att.ContractorFirst = nullptr;
//Att.ContractorLast  = nullptr;
//Att.FellowBefore    = nullptr;
//Att.FellowBehind    = nullptr;
}

/* @MRTZ_describe AssociationFellowship
 copy the data of the given association and add its contractors by calling
 recursively this cast-constructor
*/
template <class DataType, DataType defaultData>
AssociationFellowship<DataType, defaultData>::AssociationFellowship(Association<DataType, defaultData>* association)
                                             :Att()
{
// Att.Sponsor         = nullptr;
// Att.ContractorFirst = nullptr;
// Att.ContractorLast  = nullptr;
// Att.FellowBefore    = nullptr;
// Att.FellowBehind    = nullptr;

 this->data_set(association->data_get());

 Association<DataType, defaultData>* Contractor = association->contractorFirst_get();
 while(Contractor != nullptr)
 {
  this->contractorLast_add(new AssociationFellowship<DataType, defaultData>(Contractor));
  Contractor = association->contractorBehind_get(Contractor);
 }
}




/* @MRTZ_describe AssociationFellowship
 copy the data of the given association and add its contractors by calling
 recursively this cast-constructor
*/
template <class DataType, DataType defaultData>
AssociationFellowship<DataType, defaultData>::AssociationFellowship(AssociationFellowship<DataType, defaultData>& association)
                                             :Att(association.Sponsor        ,
                                                  association.ContractorFirst,
                                                  association.ContractorLast ,
                                                  association.FellowBefore   ,
                                                  association.FellowBehind   )

{

 this->data_set(association.data_get());

 Association<DataType, defaultData>* Contractor = association.contractorFirst_get();
 while(Contractor != nullptr)
 {
  this->contractorLast_add(new AssociationFellowship<DataType, defaultData>(Contractor));
  Contractor = association.contractorBehind_get(Contractor);
 }
}






/* @MRTZ_describe ~AssociationFellowship

*/
template <class DataType, DataType defaultData>  AssociationFellowship<DataType, defaultData>::~AssociationFellowship(void)
{
}





/* @MRTZ_describe operator=

*/
template <class DataType, DataType defaultData> inline
AssociationFellowship<DataType, defaultData>& AssociationFellowship<DataType, defaultData>::operator= (Association<DataType, defaultData>* association)
{

 this->data_set(association->data_get());

 Association<DataType, defaultData>* Contractor = association->contractorFirst_get();
 while(Contractor != nullptr)
 {
  this->contractorLast_add(new AssociationFellowship<DataType, defaultData>(Contractor));
  Contractor = association->contractorBehind_get(Contractor);
 }

 return(*this);
}



/* @MRTZ_describe operator=

*/
template <class DataType, DataType defaultData> inline
AssociationFellowship<DataType, defaultData>& AssociationFellowship<DataType, defaultData>::operator= (AssociationFellowship<DataType, defaultData>& association)
{
 Att.Sponsor         = association.Att.Sponsor        ;
 Att.ContractorFirst = association.Att.ContractorFirst;
 Att.ContractorLast  = association.Att.ContractorLast ;
 Att.FellowBefore    = association.Att.FellowBefore   ;
 Att.FellowBehind    = association.Att.FellowBehind   ;

 this->data_set(association->data_get());

 Association<DataType, defaultData>* Contractor = association.contractorFirst_get();
 while(Contractor != nullptr)
 {
  this->contractorLast_add(new AssociationFellowship<DataType, defaultData>(Contractor));
  Contractor = association.contractorBehind_get(Contractor);
 }

 return(*this);
}


/* @MRTZ_describe to_TDA_AssociationSponsor

template <class DataType, DataType defaultData> inline / *INLINE_1* /
AssociationSponsor<DataType, defaultData>*  AssociationFellowship<DataType, defaultData>::as_AssociationSponsor(void)
{
 return(nullptr);
}
*/


/* @MRTZ_describe to_TDA_AssociationFellowship

*/
template <class DataType, DataType defaultData> inline /*INLINE_1*/
AssociationFellowship<DataType, defaultData>*  AssociationFellowship<DataType, defaultData>::as_AssociationFellowship(void)
{
 return(this);
}



/* @MRTZ_describe newObject

*/
template <class DataType, DataType defaultData> inline /*INLINE_1*/
Association<DataType, defaultData>* AssociationFellowship<DataType, defaultData>::newObject(void)
{
 return(new AssociationFellowship<DataType, defaultData>);
}



/* @MRTZ_describe newObject

*/
template <class DataType, DataType defaultData> inline /*INLINE_1*/
Association<DataType, defaultData>* AssociationFellowship<DataType, defaultData>::newObject(DataType data)
{
 return(new AssociationFellowship<DataType, defaultData>(data));
}



/* @MRTZ_describe newObject

*/
template <class DataType, DataType defaultData> inline /*INLINE_1*/
Association<DataType, defaultData>* AssociationFellowship<DataType, defaultData>::newObject(Association<DataType, defaultData>* association)
{
 return(new AssociationFellowship<DataType, defaultData>(association));
}



/* @MRTZ_describe sponsor_get
   simple return of attribute
*/
template <class DataType, DataType defaultData> inline /*INLINE_1*/
Association<DataType, defaultData>*  AssociationFellowship<DataType, defaultData>::sponsor_get(ASSOCIATION_UNUSED* sponsor)
{
 return(Att.Sponsor);
}









/* @MRTZ_describe contractorBefore_add

*/
template <class DataType, DataType defaultData> inline /*INLINE_2*/
Association<DataType, defaultData>* AssociationFellowship<DataType, defaultData>::contractorBefore_add(Association<DataType, defaultData>* beforeThis,
                                                                                                       Association<DataType, defaultData>* node)
{
 if(this->isContractor(beforeThis) != nullptr)             // beforeThis is a valid node
  return(beforeThis->fellowBefore_add(node));           // beforeThis knows how to do
 else                                                   // beforeThis is not a valid node
  return(nullptr);                                         // return no success
}



/* @MRTZ_describe contractorBefore_add

*/
template <class DataType, DataType defaultData>
Association<DataType, defaultData>*  AssociationFellowship<DataType, defaultData>::contractorBefore_add(Association<DataType, defaultData>*        beforeThis,
                                                                                                        Association<DataType, defaultData>*        node,
                                                                                                        AssociationVisitor<DataType, defaultData>* visitor)
{
 Association<DataType, defaultData>* ReturnValue = nullptr;              // prepare sponsor pointer with non no success

 if(this->isContractor(beforeThis) != nullptr)                           // beforeThis is a valid node
 {
  beforeThis->welcome(visitor,IterateBackwards);
                                                                         // start search with given visitor
  Association<DataType, defaultData>* Contractor = visitor->node_get();  // result of search
  if(Contractor != nullptr)                                              // result is a valid node
   ReturnValue = contractorBefore_add(Contractor,node);
                                                                         // found node knows how to do
  else                                                                   // result is not a valid node
  { }                                                                    // return-value is already set to no success
 }
 else                                                                    // beforeThis is not a valid node
 { }                                                                     // return-value is already set to no success

 return(ReturnValue);                                                    // sponsor-pointer to this-class pointer
}






/* @MRTZ_describe contractorBefore_cut

*/
template <class DataType, DataType defaultData> inline /*INLINE_2*/
Association<DataType, defaultData>*  AssociationFellowship<DataType, defaultData>::contractorBefore_cut(Association<DataType, defaultData>* beforeThis)
{
 if(this->isContractor(beforeThis) != nullptr)                // beforeThis is a valid contractor
  return(beforeThis->fellowBefore_cut());                     // beforeThis knows how to do
 else                                                         // beforeThis is not a valid contractor
  return(nullptr);                                            // return no success
}



/* @MRTZ_describe contractorBefore_cut

*/
template <class DataType, DataType defaultData> Association<DataType, defaultData>*
AssociationFellowship<DataType, defaultData>::contractorBefore_cut(Association<DataType, defaultData>*        beforeThis,
                                                                   AssociationVisitor<DataType, defaultData>* visitor)
{
 Association<DataType, defaultData>* ReturnValue = nullptr;    // prepare no success
 Association<DataType, defaultData>* Contractor  = nullptr;    // fellow of beforeThis

 if(this->isContractor(beforeThis) != nullptr)                 // beforeThis is a valid contractor
 {
  beforeThis->welcome(visitor,IterateBackwards);               // start search with given visitor
  Contractor = visitor->node_get();                            // result of search
  if(Contractor != nullptr)                                    // result is a valid node
   ReturnValue = Contractor->fellowBefore_cut();               // found node knows how to do
  else                                                         // result is not a valid contractor
  { }                                                          // return-value is already set to no success
 }
 else                                                          // beforeThis is not a valid contractor
 { }                                                           // return-value is already set to no success

 return(ReturnValue);
}





/* @MRTZ_describe contractorBefore_delete

*/
template <class DataType, DataType defaultData> inline /*INLINE_2*/
Association<DataType, defaultData>*   AssociationFellowship<DataType, defaultData>::contractorBefore_delete(Association<DataType, defaultData>* beforeThis )
{

 if(this->isContractor(beforeThis) != nullptr)                   // beforeThis is a valid contractor
  return(beforeThis->fellowBefore_delete());                     // beforeThis knows how to do
 else                                                            // beforeThis is not a valid contractor
  return(nullptr);                                               // return no success

}




/* @MRTZ_describe contractorBefore_delete

*/
template <class DataType, DataType defaultData>
Association<DataType, defaultData>*  AssociationFellowship<DataType, defaultData>::contractorBefore_delete(Association<DataType, defaultData>*        beforeThis,
                                                                                                           AssociationVisitor<DataType, defaultData>* visitor)
{
 Association<DataType, defaultData>* ReturnValue = nullptr;     // prepare sponsor pointer with non no success
 Association<DataType, defaultData>* Contractor  = nullptr;     // fellow of beforeThis

 if(this->isContractor(beforeThis) != nullptr)                  // beforeThis is a valid contractor
 {
  beforeThis->welcome(visitor,IterateBackwards);
                                                                // start search with given visitor
  Contractor = visitor->node_get();                             // result of search
  if(Contractor != nullptr)                                     // result is a valid node
   ReturnValue = Contractor->fellowBefore_delete();             // found node knows how to do
  else                                                          // result is not a valid contractor
  { }                                                           // return-value is already set to no success
 }
 else                                                           // beforeThis is not a valid contractor
 { }                                                            // return-value is already set to no success

 return(ReturnValue);                                           // sponsor-pointer to this-class pointer
}





/* @MRTZ_describe contractorBefore_get

*/
template <class DataType, DataType defaultData> inline /*INLINE_2*/
Association<DataType, defaultData>*   AssociationFellowship<DataType, defaultData>::contractorBefore_get(Association<DataType, defaultData>* beforeThis)
{

 if(this->isContractor(beforeThis) != nullptr)           // beforeThis is a valid contractor
  return(beforeThis->fellowBefore_get());                // beforeThis knows how to do
 else                                                    // beforeThis is not a valid contractor
  return(nullptr);                                       // return no success
}



/* @MRTZ_describe contractorBefore_get

*/
template <class DataType, DataType defaultData>
Association<DataType, defaultData>*  AssociationFellowship<DataType, defaultData>::contractorBefore_get(Association<DataType, defaultData>*        beforeThis,
                                                                                                        AssociationVisitor<DataType, defaultData>* visitor)
{
 Association<DataType, defaultData>* ReturnValue = nullptr;      // prepare sponsor pointer with non no success
 Association<DataType, defaultData>* Contractor  = nullptr;      // fellow of beforeThis

 if(this->isContractor(beforeThis) != nullptr)                   // beforeThis is a valid contractor
 {
  beforeThis->welcome(visitor,IterateBackwards);
                                                                 // start search with given visitor
  Contractor = visitor->node_get();                              // result of search
  if(Contractor != nullptr)                                      // result is a valid node
   ReturnValue = Contractor->fellowBefore_get();                 // found node knows how to do
  else                                                           // result is not a valid contractor
  { }                                                            // return-value is already set to no success
 }
 else                                                            // beforeThis is not a valid contractor
 { }                                                             // return-value is already set to no success

 return(ReturnValue);                                            // sponsor-pointer to this-class pointer
}









/* @MRTZ_describe contractorBehind_add

*/
template <class DataType, DataType defaultData> inline /*INLINE_2*/
Association<DataType, defaultData>*   AssociationFellowship<DataType, defaultData>::contractorBehind_add(Association<DataType, defaultData>* behindThis,
                                                                                                         Association<DataType, defaultData>* node)
{
 if(this->isContractor(behindThis) != nullptr)         // behindThis is a valid contractor
  return( behindThis->fellowBehind_add(node));         // behindThis knows how to do
 else                                                  // behindThis is not a valid contractor
  return(nullptr);                                     // return no success
}



/* @MRTZ_describe contractorBehind_add

*/
template <class DataType, DataType defaultData>
Association<DataType, defaultData>*  AssociationFellowship<DataType, defaultData>::contractorBehind_add(Association<DataType, defaultData>*        behindThis,
                                                                                                        Association<DataType, defaultData>*        node,
                                                                                                        AssociationVisitor<DataType, defaultData>* visitor)
{
 Association<DataType, defaultData>* ReturnValue = nullptr;              // prepare sponsor pointer with non no success

 if(this->isContractor(behindThis) != nullptr)                           // behindThis is a valid contractor
 {
  behindThis->welcome(visitor,IterateForwards);
                                                                         // start search with given visitor
  Association<DataType, defaultData>* Contractor = visitor->node_get();  // result of search
  if(Contractor != nullptr)                                              // result is a valid node
   ReturnValue = this->contractorBehind_add(Contractor,node);            // found node knows how to do
  else                                                                   // result is not a valid node
  { }                                                                    // return-value is already set to no success
 }
 else                                                                    // behindThis is not a valid contractor
 { }                                                                     // return-value is already set to no success

 return(ReturnValue);                                                    // sponsor-pointer to this-class pointer
}


/* @MRTZ_describe contractorBehind_cut

*/
template <class DataType, DataType defaultData> inline /*INLINE_2*/
Association<DataType, defaultData>*  AssociationFellowship<DataType, defaultData>::contractorBehind_cut(Association<DataType, defaultData>* behindThis)
{

 if(this->isContractor(behindThis) != nullptr)           // behindThis is a valid contractor
  return(behindThis->fellowBehind_cut());                // behindThis knows how to do
 else                                                    // behindThis is not a valid contractor
  return(nullptr);                                       // return no success

}




/* @MRTZ_describe contractorBehind_cut

*/
template <class DataType, DataType defaultData>
Association<DataType, defaultData>* AssociationFellowship<DataType, defaultData>::contractorBehind_cut(Association<DataType, defaultData>*        behindThis,
                                                                                                       AssociationVisitor<DataType, defaultData>* visitor)
{
 Association<DataType, defaultData>* ReturnValue = nullptr;      // prepare sponsor pointer with non no success
 Association<DataType, defaultData>* Contractor  = nullptr;      // fellow of beforeThis

 if(this->isContractor(behindThis) != nullptr)                   // behindThis is a valid contractor
 {
  behindThis->welcome(visitor,IterateForwards);
                                                                 // start search with given visitor
  Contractor = visitor->node_get();                              // result of search
  if(Contractor != nullptr)                                      // result is a valid node
   ReturnValue = Contractor->fellowBehind_cut();                 // found node knows how to do
  else                                                           // result is not a valid contractor
  { }                                                            // return-value is already set to no success
 }
 else                                                            // behindThis is not a valid contractor
 { }                                                             // return-value is already set to no success

 return(ReturnValue);                                            // sponsor-pointer to this-class pointer
}





/* @MRTZ_describe contractorBehind_delete

*/
template <class DataType, DataType defaultData> inline /*INLINE_2*/
Association<DataType, defaultData>*   AssociationFellowship<DataType, defaultData>::contractorBehind_delete(Association<DataType, defaultData>* behindThis)
{
 if(this->isContractor(behindThis) != nullptr)         // behindThis is a valid contractor
  return(behindThis->fellowBehind_delete());           // behindThis knows how to do
 else                                                  // behindThis is not a valid contractor
  return(nullptr);                                     // return no success
}



/* @MRTZ_describe contractorBehind_delete

*/
template <class DataType, DataType defaultData>
Association<DataType, defaultData>*  AssociationFellowship<DataType, defaultData>::contractorBehind_delete(Association<DataType, defaultData>*        behindThis,
                                                                                                           AssociationVisitor<DataType, defaultData>* visitor)
{
 Association<DataType, defaultData>* ReturnValue = nullptr;      // prepare sponsor pointer with non no success
 Association<DataType, defaultData>* Contractor  = nullptr;      // fellow of beforeThis

 if(this->isContractor(behindThis) != nullptr)                   // behindThis is a valid contractor
 {
  behindThis->welcome(visitor,IterateForwards);
                                                                 // start search with given visitor
  Contractor = visitor->node_get();                              // result of search
  if(Contractor != nullptr)                                      // result is a valid node
   ReturnValue = Contractor->fellowBehind_delete();              // found node knows how to do
  else                                                           // result is not a valid contractor
  { }                                                            // return-value is already set to no success
 }
 else                                                            // behindThis is not a valid contractor
 { }                                                             // return-value is already set to no success

 return(ReturnValue);                                            // sponsor-pointer to this-class pointer
}





/* @MRTZ_describe contractorBehind_get

*/
template <class DataType, DataType defaultData> inline /*INLINE_2*/
Association<DataType, defaultData>*   AssociationFellowship<DataType, defaultData>::contractorBehind_get(Association<DataType, defaultData>* behindThis)
{

 if(this->isContractor(behindThis) != nullptr)               // behindThis is a valid contractor
  return(behindThis->fellowBehind_get());                    // behindThis knows how to do
 else                                                        // behindThis is not a valid contractor
  return(nullptr);                                           // return no success

}



/* @MRTZ_describe contractorBehind_get

*/
template <class DataType, DataType defaultData>
Association<DataType, defaultData>*  AssociationFellowship<DataType, defaultData>::contractorBehind_get(Association<DataType, defaultData>*        behindThis,
                                                                                                        AssociationVisitor<DataType, defaultData>* visitor)
{
 Association<DataType, defaultData>* ReturnValue = nullptr;      // prepare sponsor pointer with non no success
 Association<DataType, defaultData>* Contractor  = nullptr;      // fellow of beforeThis

 if(this->isContractor(behindThis) != nullptr)                   // behindThis is a valid contractor
 {
  behindThis->welcome(visitor,IterateForwards);
                                                                 // start search with given visitor
  Contractor = visitor->node_get();                              // result of search
  if(Contractor != nullptr)                                      // result is a valid node
   ReturnValue = Contractor->fellowBehind_get();                 // found node knows how to do
  else                                                           // result is not a valid contractor
  { }                                                            // return-value is already set to no success
 }
 else                                                            // behindThis is not a valid contractor
 { }                                                             // return-value is already set to no success

 return(ReturnValue);                                            // sponsor-pointer to this-class pointer
}









/* @MRTZ_describe contractorFirst_add

*/
template <class DataType, DataType defaultData> inline /*INLINE_1*/
Association<DataType, defaultData>* AssociationFellowship<DataType, defaultData>::contractorFirst_add(Association<DataType, defaultData>* node)
{
 return(addNode(node,this,nullptr,Att.ContractorFirst));
}




/* @MRTZ_describe contractorFirst_cut

*/
template <class DataType, DataType defaultData> inline /*INLINE_1*/
Association<DataType, defaultData>*  AssociationFellowship<DataType, defaultData>::contractorFirst_cut(void)
{
 return(cutNode(Att.ContractorFirst));
}


/* @MRTZ_describe contractorFirst_cut

*/
template <class DataType, DataType defaultData>
Association<DataType, defaultData>* AssociationFellowship<DataType, defaultData>::contractorFirst_cut(AssociationVisitor<DataType, defaultData>* visitor)
{
 Association<DataType, defaultData>* ReturnValue = nullptr;             // prepare sponsor pointer with non no success

 if(Att.ContractorFirst != nullptr)
 {
  Att.ContractorFirst->welcome(visitor,IterateForwards);                // start search with given visitor
  Association<DataType, defaultData>* Contractor = visitor->node_get(); // result of search

  if(Contractor != nullptr)                                             // result is a valid node
   ReturnValue = cutNode(Contractor);                                   // cut out found node
  else                                                                  // result is not a valid contractor
  {}                                                                    // return-value is already set to no success
 }
 return(ReturnValue);                                                   // sponsor-pointer to this-class pointer
}





/* @MRTZ_describe contractorFirst_delete

*/
template <class DataType, DataType defaultData> inline /*INLINE_1*/
Association<DataType, defaultData>*   AssociationFellowship<DataType, defaultData>::contractorFirst_delete(void)
{
 return(Association<DataType, defaultData>::deleteNode(Att.ContractorFirst, this));
}



/* @MRTZ_describe contractorFirst_delete

*/
template <class DataType, DataType defaultData>
Association<DataType, defaultData>*  AssociationFellowship<DataType, defaultData>::contractorFirst_delete(AssociationVisitor<DataType, defaultData>* visitor)
{
 Association<DataType, defaultData>* ReturnValue = nullptr;                        // prepare sponsor pointer with non no success

 if(Att.ContractorFirst != nullptr)
 {
  Att.ContractorFirst->welcome(visitor,IterateForwards);                           // start search with given visitor
  Association<DataType, defaultData>* Contractor = visitor->node_get();            // result of search

  if(Contractor != nullptr)                                                        // result is a valid node
   ReturnValue = Association<DataType, defaultData>::deleteNode(Contractor, this); // delete found node
  else                                                                             // result is not a valid contractor
  {}                                                                               // return-value is already set to no success
 }

 return(ReturnValue);                                                              // sponsor-pointer to this-class pointer
}





/* @MRTZ_describe contractorFirst_get
   simple return of attribute
*/
template <class DataType, DataType defaultData> inline /*INLINE_1*/
Association<DataType, defaultData>*   AssociationFellowship<DataType, defaultData>::contractorFirst_get(void)
{
 return(Att.ContractorFirst);
}



/* @MRTZ_describe contractorFirst_get

*/
template <class DataType, DataType defaultData> Association<DataType, defaultData>*  AssociationFellowship<DataType, defaultData>::contractorFirst_get(AssociationVisitor<DataType, defaultData>* visitor)
{

 if(Att.ContractorFirst != nullptr)
 {
  Att.ContractorFirst->welcome(visitor,IterateForwards);          // start search with given visitor
  return(visitor->node_get());                                    // result of search
 }
 else
 {
  return(nullptr);                                                // no child found
 }

}









/* @MRTZ_describe contractorLast_add

*/
template <class DataType, DataType defaultData> inline /*INLINE_1*/
Association<DataType, defaultData>*   AssociationFellowship<DataType, defaultData>::contractorLast_add(Association<DataType, defaultData>* node)
{
 return(addNode(node,this,Att.ContractorLast,nullptr));
}


/* @MRTZ_describe contractorLast_cut

*/
template <class DataType, DataType defaultData> inline /*INLINE_1*/
Association<DataType, defaultData>* AssociationFellowship<DataType, defaultData>::contractorLast_cut(void)
{
 return(cutNode(Att.ContractorLast));
}


/* @MRTZ_describe contractorLast_cut

*/
template <class DataType, DataType defaultData> Association<DataType, defaultData>* AssociationFellowship<DataType, defaultData>::contractorLast_cut(AssociationVisitor<DataType, defaultData>* visitor)
{
 Association<DataType, defaultData>* ReturnValue = nullptr;              // prepare sponsor pointer with non no success

 if(Att.ContractorLast != nullptr)
 {
  Att.ContractorLast->welcome(visitor,IterateBackwards);                 // start search with given visitor
  Association<DataType, defaultData>* Contractor = visitor->node_get();  // result of search

  if(Contractor != nullptr)                                              // result is a valid node
   ReturnValue = cutNode(Contractor);                                    // cut out found node
  else                                                                   // result is not a valid contractor
  {}                                                                     // return-value is already set to no success
 }
 return(ReturnValue);                                                    // return no success
}



/* @MRTZ_describe contractorLast_delete

*/
template <class DataType, DataType defaultData> inline /*INLINE_1*/
Association<DataType, defaultData>* AssociationFellowship<DataType, defaultData>::contractorLast_delete(void)
{
 return(Association<DataType, defaultData>::deleteNode(Att.ContractorLast, this));
}

/* @MRTZ_describe contractorLast_delete

*/
template <class DataType, DataType defaultData>
Association<DataType, defaultData>*  AssociationFellowship<DataType, defaultData>::contractorLast_delete(AssociationVisitor<DataType, defaultData>* visitor)
{
 Association<DataType, defaultData>* ReturnValue = nullptr;                        // prepare sponsor pointer with non no success
 if(Att.ContractorLast != nullptr)
 {
  Att.ContractorLast->welcome(visitor,IterateBackwards);                           // start search with given visitor
  Association<DataType, defaultData>* Contractor = visitor->node_get();            // result of search

  if(Contractor != nullptr)                                                        // result is a valid node
   ReturnValue = Association<DataType, defaultData>::deleteNode(Contractor, this); // delete found node
  else                                                                             // result is not a valid contractor
  {}                                                                               // return-value is already set to no success
 }
 return(ReturnValue);                                                              // return-value is already set to no success
}




/* @MRTZ_describe contractorLast_get
   simple return of attribute
*/
template <class DataType, DataType defaultData> inline /*INLINE_1*/
Association<DataType, defaultData>* AssociationFellowship<DataType, defaultData>::contractorLast_get(void)
{
 return(Att.ContractorLast);
}


/* @MRTZ_describe contractorLast_get

*/
template <class DataType, DataType defaultData> Association<DataType, defaultData>*  AssociationFellowship<DataType, defaultData>::contractorLast_get(AssociationVisitor<DataType, defaultData>* visitor)
{

 if(Att.ContractorLast != nullptr)
 {
  Att.ContractorLast->welcome(visitor,IterateBackwards);          // start search with given visitor
  return(visitor->node_get());                                    // result of search
 }
 else
 {
  return(nullptr);                                                // no child found
 }

}






/* @MRTZ_describe fellowBefore_add

*/
template <class DataType, DataType defaultData> inline /*INLINE_2*/
Association<DataType, defaultData>*   AssociationFellowship<DataType, defaultData>::fellowBefore_add(Association<DataType, defaultData>* node,
                                                                                                     ASSOCIATION_UNUSED*                 sponsor)
{
 if(this->Att.Sponsor != nullptr)                                // this is a contractor of an other node
  return(addNode(node,Att.Sponsor,Att.FellowBefore,this));       // add the node as fellow
 else                                                            // no sponsor defined
  return(nullptr);                                               // return no success
}



/* @MRTZ_describe fellowBefore_add

*/
template <class DataType, DataType defaultData>
Association<DataType, defaultData>*  AssociationFellowship<DataType, defaultData>::fellowBefore_add(Association<DataType, defaultData>*        node,
                                                                                                    AssociationVisitor<DataType, defaultData>* visitor,
                                                                                                    ASSOCIATION_UNUSED*                        sponsor)
{
 if(this->Att.Sponsor != nullptr)                                       // this is a contractor of an other node
 {
  this->welcome(visitor,IterateBackwards);                              // start search with given visitor
  Association<DataType, defaultData>* Contractor = visitor->node_get(); // result of search

  if(Contractor != nullptr)                                             // result is a valid node
   return(Contractor->fellowBefore_add(node));                          // found node knows how to do
  else                                                                  // result is not a valid contractor
   return(nullptr);                                                     // return no success
 }
 else                                                                   // this is a root node without own sponsor
  return(nullptr);                                                      // return no success

}




/* @MRTZ_describe fellowBefore_cut

*/
template <class DataType, DataType defaultData> inline /*INLINE_1*/
Association<DataType, defaultData>* AssociationFellowship<DataType, defaultData>::fellowBefore_cut(ASSOCIATION_UNUSED* sponsor)
{
 return(cutNode(Att.FellowBefore));
}



/* @MRTZ_describe fellowBefore_cut

*/
template <class DataType, DataType defaultData>
Association<DataType, defaultData>*  AssociationFellowship<DataType, defaultData>::fellowBefore_cut(AssociationVisitor<DataType, defaultData>* visitor,
                                                                                                    ASSOCIATION_UNUSED*                        sponsor)
{
 Association<DataType, defaultData>* ReturnValue = nullptr;

 if(Att.FellowBefore != nullptr)                                  // next fellow is existing
 {
  Att.FellowBefore->welcome(visitor,IterateBackwards);            // start search with given visitor
  ReturnValue = visitor->node_get();                              // result of search
  if(ReturnValue != nullptr)                                      // result is a valid node
   ReturnValue = ReturnValue->fellowBehind_get()->fellowBefore_cut();
                                                                  // found node knows how to do
  else                                                            // result is a invalid node
  {/* keep ReturnValue as an invalid node */ }
 }
 else                                                             // next fellow is not existing
 {/* keep ReturnValue as an invalid node */ }

 return(ReturnValue);                                             // found node knows how to do
}







/* @MRTZ_describe fellowBefore_delete

*/
template <class DataType, DataType defaultData> inline /*INLINE_1*/
Association<DataType, defaultData>* AssociationFellowship<DataType, defaultData>::fellowBefore_delete(ASSOCIATION_UNUSED* sponsor)
{
 return(Association<DataType, defaultData>::deleteNode(Att.FellowBefore,this));
}



/* @MRTZ_describe fellowBefore_delete

*/
template <class DataType, DataType defaultData> Association<DataType, defaultData>*
AssociationFellowship<DataType, defaultData>::fellowBefore_delete(AssociationVisitor<DataType, defaultData>* visitor,
                                                                  ASSOCIATION_UNUSED*                        sponsor)
{
 Association<DataType, defaultData>* ReturnValue = nullptr;

 if(Att.FellowBefore != nullptr)                                  // next fellow is existing
 {
  Att.FellowBefore->welcome(visitor,IterateBackwards);            // start search with given visitor
  ReturnValue = visitor->node_get();                              // result of search
  if(ReturnValue != nullptr)                                      // result is a valid node
   ReturnValue = ReturnValue->fellowBehind_get()->fellowBefore_delete();
                                                                  // found node knows how to do
  else                                                            // result is a invalid node
  {/* keep ReturnValue as an invalid node */ }
 }
 else                                                             // next fellow is not existing
 {/* keep ReturnValue as an invalid node */ }


 return(ReturnValue);                                             // found node knows how to do
}




/* @MRTZ_describe fellowBefore_get
   simple return of attribute
*/
template <class DataType, DataType defaultData> inline /*INLINE_1*/
Association<DataType, defaultData>* AssociationFellowship<DataType, defaultData>::fellowBefore_get(ASSOCIATION_UNUSED* sponsor)
{
 return(Att.FellowBefore);
}




/* @MRTZ_describe fellowBefore_get

*/
template <class DataType, DataType defaultData>
Association<DataType, defaultData>*  AssociationFellowship<DataType, defaultData>::fellowBefore_get(AssociationVisitor<DataType, defaultData>* visitor,
                                                                                                    ASSOCIATION_UNUSED*                        sponsor)
{
 Association<DataType, defaultData>* ReturnValue = nullptr;

 if(Att.FellowBefore != nullptr)                                  // next fellow is existing
 {
  Att.FellowBefore->welcome(visitor,IterateBackwards);            // start search with given visitor
  ReturnValue = visitor->node_get();                              // result of search
 }
 else                                                             // next fellow is not existing
 {/* keep ReturnValue as an invalid node */ }


 return(ReturnValue);                                             // found node knows how to do
}








/* @MRTZ_describe fellowBehind_add

*/
template <class DataType, DataType defaultData> inline /*INLINE_2*/
Association<DataType, defaultData>*   AssociationFellowship<DataType, defaultData>::fellowBehind_add(Association<DataType, defaultData>* node,
                                                                                                     ASSOCIATION_UNUSED*                 sponsor)
{
 if(this->Att.Sponsor != nullptr)                                       // this is a contractor of an other node
  return(addNode(node,Att.Sponsor,this,Att.FellowBehind));              // add the node as fellow
 else                                                                   // no sponsor defined
  return(nullptr);                                                      // return no success
}



/* @MRTZ_describe fellowBehind_add

*/
template <class DataType, DataType defaultData>
Association<DataType, defaultData>*  AssociationFellowship<DataType, defaultData>::fellowBehind_add(Association<DataType, defaultData>*        node,
                                                                                                    AssociationVisitor<DataType, defaultData>* visitor,
                                                                                                    ASSOCIATION_UNUSED*                        sponsor)
{
 if(this->Att.Sponsor != nullptr)                                       // this is a contractor of an other node
 {
  this->welcome(visitor,IterateForwards);                               // start search with given visitor
  Association<DataType, defaultData>* Contractor = visitor->node_get(); // result of search

  if(Contractor != nullptr)                                             // result is a valid node
   return(Contractor->fellowBehind_add(node));                          // found node knows how to do
  else                                                                  // result is not a valid contractor
   return(nullptr);                                                     // return no success
 }
 else                                                                   // this is a root-node without own sponsor
  return(nullptr);                                                      // return no success
}






/* @MRTZ_describe

*/
template <class DataType, DataType defaultData> inline /*INLINE_1*/
Association<DataType, defaultData>* AssociationFellowship<DataType, defaultData>::fellowBehind_cut(ASSOCIATION_UNUSED* sponsor)
{
 return(cutNode(Att.FellowBehind));
}



/* @MRTZ_describe fellowBehind_cut

*/
template <class DataType, DataType defaultData>
Association<DataType, defaultData>*  AssociationFellowship<DataType, defaultData>::fellowBehind_cut(AssociationVisitor<DataType, defaultData>* visitor,
                                                                                                    ASSOCIATION_UNUSED*                        sponsor)
{
 Association<DataType, defaultData>* ReturnValue = nullptr;

 if(Att.FellowBehind != nullptr)                                  // next fellow is existing
 {
  Att.FellowBehind->welcome(visitor,IterateForwards);             // start search with given visitor
  ReturnValue = visitor->node_get();                              // result of search
  if(ReturnValue != nullptr)                                      // result is a valid node
   ReturnValue = ReturnValue->fellowBefore_get()->fellowBehind_cut();
                                                                  // found node knows how to do
  else                                                            // result is a invalid node
  {/* keep ReturnValue as an invalid node */ }
 }
 else                                                             // next fellow is not existing
 {/* keep ReturnValue as an invalid node */ }

 return(ReturnValue);                                             // found node knows how to do
}




/* @MRTZ_describe fellowBehind_delete

*/
template <class DataType, DataType defaultData> inline /*INLINE_1*/
Association<DataType, defaultData>* AssociationFellowship<DataType, defaultData>::fellowBehind_delete(ASSOCIATION_UNUSED* sponsor)
{
 return(Association<DataType, defaultData>::deleteNode(Att.FellowBehind, this));
}



/* @MRTZ_describe fellowBehind_delete

*/
template <class DataType, DataType defaultData>
Association<DataType, defaultData>*  AssociationFellowship<DataType, defaultData>::fellowBehind_delete(AssociationVisitor<DataType, defaultData>* visitor,
                                                                                                       ASSOCIATION_UNUSED*                        sponsor)
{
 Association<DataType, defaultData>* ReturnValue = nullptr;

 if(Att.FellowBehind != nullptr)                                  // next fellow is existing
 {
  Att.FellowBehind->welcome(visitor,IterateForwards);             // start search with given visitor
  ReturnValue = visitor->node_get();                              // result of search
  if(ReturnValue != nullptr)                                      // result is a valid node
   ReturnValue = ReturnValue->fellowBefore_get()->fellowBehind_delete();
                                                                  // found node knows how to do
  else                                                            // result is a invalid node
  {/* keep ReturnValue as an invalid node */ }
 }
 else                                                             // next fellow is not existing
 {/* keep ReturnValue as an invalid node */ }

 return(ReturnValue);                                             // found node knows how to do
}




/* @MRTZ_describe fellowBehind_get
   simple return of attribute
*/
template <class DataType, DataType defaultData> inline /*INLINE_1*/
Association<DataType, defaultData>* AssociationFellowship<DataType, defaultData>::fellowBehind_get(ASSOCIATION_UNUSED* sponsor)
{
 return(Att.FellowBehind);
}



/* @MRTZ_describe fellowBehind_get

*/
template <class DataType, DataType defaultData>
Association<DataType, defaultData>*  AssociationFellowship<DataType, defaultData>::fellowBehind_get(AssociationVisitor<DataType, defaultData>* visitor,
                                                                                                    ASSOCIATION_UNUSED*                        sponsor)
{
 Association<DataType, defaultData>* ReturnValue = nullptr;

 if(Att.FellowBehind != nullptr)                                  // next fellow is existing
 {
  Att.FellowBehind->welcome(visitor,IterateForwards);             // start search with given visitor
  ReturnValue = visitor->node_get();                              // result of search
 }
 else                                                             // next fellow is not existing
 {/* keep ReturnValue as an invalid node */ }

 return(ReturnValue);                                             // found node knows how to do
}









/* @MRTZ_describe fellowFirst_add

*/
template <class DataType, DataType defaultData> inline /*INLINE_2*/
Association<DataType, defaultData>*   AssociationFellowship<DataType, defaultData>::fellowFirst_add(Association<DataType, defaultData>* node,
                                                                                                    ASSOCIATION_UNUSED*                 sponsor)
{
 if(this->Att.Sponsor != nullptr)                        // this is a contractor of an other node
  return(Att.Sponsor->contractorFirst_add(node));        // sponsor knows how to do
 else                                                    // beforeThis is not a valid node
  return(nullptr);                                       // return no success
}





/* @MRTZ_describe fellowFirst_cut

*/
template <class DataType, DataType defaultData> inline /*INLINE_2*/
Association<DataType, defaultData>*   AssociationFellowship<DataType, defaultData>::fellowFirst_cut(ASSOCIATION_UNUSED* sponsor)
{
 if(this->Att.Sponsor != nullptr)                     // this is a contractor of an other node
  return(Att.Sponsor->contractorFirst_cut());         // sponsor knows how to do
 else                                                 // beforeThis is not a valid node
  return(nullptr);                                    // return no success
}



/* @MRTZ_describe fellowFirst_cut

*/
template <class DataType, DataType defaultData>
Association<DataType, defaultData>*  AssociationFellowship<DataType, defaultData>::fellowFirst_cut(AssociationVisitor<DataType, defaultData>* visitor,
                                                                                                   ASSOCIATION_UNUSED*                        sponsor)
{
 Association<DataType, defaultData>* Sponsor = this->Att.Sponsor;  // sponsor-class to this class

 if(Sponsor != nullptr)                                            // this is a contractor of an other node
  return(Sponsor->contractorFirst_cut(visitor));                   // sponsor knows how to do
 else                                                              // beforeThis is not a valid node
  return(nullptr);                                                 // return no success
}





/* @MRTZ_describe fellowFirst_delete

*/
template <class DataType, DataType defaultData>  inline /*INLINE_2*/
Association<DataType, defaultData>*   AssociationFellowship<DataType, defaultData>::fellowFirst_delete(ASSOCIATION_UNUSED* sponsor)
{
 if(this->Att.Sponsor != nullptr)                      // this is a contractor of an other node
  return(Att.Sponsor->contractorFirst_delete());       // sponsor knows how to do
 else                                                  // beforeThis is not a valid node
  return(nullptr);                                     // return no success
}



/* @MRTZ_describe fellowFirst_delete

*/
template <class DataType, DataType defaultData>  inline /*INLINE_2*/
Association<DataType, defaultData>*  AssociationFellowship<DataType, defaultData>::fellowFirst_delete(AssociationVisitor<DataType, defaultData>* visitor,
                                                                                                      ASSOCIATION_UNUSED*                        sponsor)
{
 Association<DataType, defaultData>* Sponsor = this->Att.Sponsor; // sponsor-class to this class

 if(Sponsor != nullptr)                                           // this is a contractor of an other node
  return(Sponsor->contractorFirst_delete(visitor));               // sponsor knows how to do
 else                                                             // beforeThis is not a valid node
  return(nullptr);                                                // return no success
}




/* @MRTZ_describe fellowFirst_get

*/
template <class DataType, DataType defaultData>  inline /*INLINE_2*/
Association<DataType, defaultData>*   AssociationFellowship<DataType, defaultData>::fellowFirst_get(ASSOCIATION_UNUSED* sponsor)
{
 if(this->Att.Sponsor != nullptr)                     // this is a contractor of an other node
  return(Att.Sponsor->contractorFirst_get());         // sponsor knows how to do
 else                                                 // beforeThis is not a valid node
  return(nullptr);                                    // return no success
}




/* @MRTZ_describe fellowFirst_get

*/
template <class DataType, DataType defaultData>  inline /*INLINE_2*/
Association<DataType, defaultData>*  AssociationFellowship<DataType, defaultData>::fellowFirst_get(AssociationVisitor<DataType, defaultData>* visitor,
                                                                                                   ASSOCIATION_UNUSED*                        sponsor)
{
 Association<DataType, defaultData>* Sponsor = this->Att.Sponsor; // sponsor-class to this class

 if(Sponsor != nullptr)                                           // this is a contractor of an other node
  return(Sponsor->contractorFirst_get(visitor));                  // sponsor knows how to do
 else                                                             // beforeThis is not a valid node
  return(nullptr);                                                // return no success
}











/* @MRTZ_describe fellowLast_add

*/
template <class DataType, DataType defaultData>  inline /*INLINE_2*/
Association<DataType, defaultData>*   AssociationFellowship<DataType, defaultData>::fellowLast_add(Association<DataType, defaultData>* node,
                                                                                                   ASSOCIATION_UNUSED*                 sponsor)
{
 if(this->Att.Sponsor != nullptr)                      // this is a contractor of an other node
  return(Att.Sponsor->contractorLast_add(node));       // sponsor knows how to do
 else                                                  // beforeThis is not a valid node
  return(nullptr);                                     // return no success
}



/* @MRTZ_describe fellowLast_cut

*/
template <class DataType, DataType defaultData>  inline /*INLINE_2*/
Association<DataType, defaultData>*   AssociationFellowship<DataType, defaultData>::fellowLast_cut(ASSOCIATION_UNUSED* sponsor)
{
 if(this->Att.Sponsor != nullptr)                     // this is a contractor of an other node
  return(Att.Sponsor->contractorLast_cut());          // sponsor knows how to do
 else                                                 // beforeThis is not a valid node
  return(nullptr);                                    // return no success
}



/* @MRTZ_describe fellowLast_cut

*/
template <class DataType, DataType defaultData>
Association<DataType, defaultData>*  AssociationFellowship<DataType, defaultData>::fellowLast_cut(AssociationVisitor<DataType, defaultData>* visitor,
                                                                                                  ASSOCIATION_UNUSED*                        sponsor)
{
 Association<DataType, defaultData>* Sponsor = this->Att.Sponsor;   // sponsor-class to this class

 if(Sponsor != nullptr)                                             // this is a contractor of an other node
  return(Sponsor->contractorLast_cut(visitor));                     // sponsor knows how to do
 else                                                               // beforeThis is not a valid node
  return(nullptr);                                                  // return no success
}




/* @MRTZ_describe fellowLast_delete

*/
template <class DataType, DataType defaultData>  inline /*INLINE_2*/
Association<DataType, defaultData>*   AssociationFellowship<DataType, defaultData>::fellowLast_delete(ASSOCIATION_UNUSED* sponsor )
{
 if(this->Att.Sponsor != nullptr)                        // this is a contractor of an other node
  return(Att.Sponsor->contractorLast_delete());          // sponsor knows how to do
 else                                                    // beforeThis is not a valid node
  return(nullptr);                                       // return no success
}



/* @MRTZ_describe fellowLast_delete

*/
template <class DataType, DataType defaultData>  inline /*INLINE_2*/
Association<DataType, defaultData>*  AssociationFellowship<DataType, defaultData>::fellowLast_delete(AssociationVisitor<DataType, defaultData>* visitor,
                                                                                                     ASSOCIATION_UNUSED*                        sponsor)
{
 Association<DataType, defaultData>* Sponsor = this->Att.Sponsor;     // sponsor-class to this class

 if(Sponsor != nullptr)                                               // this is a contractor of an other node
  return(Sponsor->contractorLast_delete(visitor));                    // sponsor knows how to do
 else                                                                 // beforeThis is not a valid node
  return(nullptr);                                                    // return no success
}





/* @MRTZ_describe fellowLast_get

*/
template <class DataType, DataType defaultData>  inline /*INLINE_2*/
Association<DataType, defaultData>*   AssociationFellowship<DataType, defaultData>::fellowLast_get(ASSOCIATION_UNUSED* sponsor)
{
 if(this->Att.Sponsor != nullptr)                     // this is a contractor of an other node
  return(Att.Sponsor->contractorLast_get());          // sponsor knows how to do
 else                                                 // beforeThis is not a valid node
  return(nullptr);                                    // return no success
}



/* @MRTZ_describe fellowLast_get

*/
template <class DataType, DataType defaultData>  inline /*INLINE_2*/
Association<DataType, defaultData>*  AssociationFellowship<DataType, defaultData>::fellowLast_get(AssociationVisitor<DataType, defaultData>* visitor,
                                                                                                  ASSOCIATION_UNUSED*                        sponsor)
{
 Association<DataType, defaultData>* Sponsor = this->Att.Sponsor;  // sponsor-class to this class

 if(Sponsor != nullptr)                                            // this is a contractor of an other node
  return(Sponsor->contractorLast_get(visitor));                    // sponsor knows how to do
 else                                                              // beforeThis is not a valid node
  return(nullptr);                                                 // return no success
}















/* @MRTZ_describe addNode

*/
template <class DataType, DataType defaultData>
Association<DataType, defaultData>*  AssociationFellowship<DataType, defaultData>::addNode(Association<DataType, defaultData>* node,
                                                                                           Association<DataType, defaultData>* sponsor,
                                                                                           Association<DataType, defaultData>* behindThis,
                                                                                           Association<DataType, defaultData>* beforeThis)
{
 Association<DataType, defaultData>* ReturnValue = nullptr;      //prepare a return of process failed
 AssociationFellowship* Sponsor     = nullptr;

 if(sponsor != nullptr)
  Sponsor      = sponsor ->as_AssociationFellowship();

 if(Sponsor != nullptr)                                          //sponsor is a valid node
 {
  AssociationFellowship* Node        = nullptr;
  AssociationFellowship* BeforeThis  = nullptr;
  AssociationFellowship* BehindThis  = nullptr;

  if(node != nullptr)
   Node         = node    ->as_AssociationFellowship();
  if(beforeThis != nullptr)
   BeforeThis = beforeThis->as_AssociationFellowship();
  if(behindThis != nullptr)
   BehindThis = behindThis->as_AssociationFellowship();

  if(Node != nullptr)
  {
   Node->Att.Sponsor      = sponsor;                             //node gets its new sponsor
   Node->Att.FellowBefore = behindThis;                          //node gets new fellow before
   Node->Att.FellowBehind = beforeThis;                          //node gets its new fellow behind
  }
  else                                                           //fellow is contractor inside of the chain of fellows
  {}
                                                                 //nothing to do
  if(Sponsor->Att.ContractorFirst == beforeThis)                 //fellow was first contractor of sponsor
   Sponsor->Att.ContractorFirst = node;                          //node is new first contractor of sponsor
  else                                                           //fellow is contractor inside of the chain of fellows
   {}                                                            //nothing to do
  if(Sponsor->Att.ContractorLast == behindThis)                  //fellow was last contractor of sponsor
   Sponsor->Att.ContractorLast = node;                           //node is new last contractor of sponsor
  else                                                           //fellow is contractor inside of the chain of fellows
   {}                                                            //nothing to do

  if(BeforeThis != nullptr)                                      //fellow before is an existing fellow
   BeforeThis->Att.FellowBefore = node;                          //fellow before gets its new fellow behind
  else                                                           //fellow before is not existing
   {}                                                            //nothing to do

  if(BehindThis != nullptr)                                      //fellow before is an existing fellow
   BehindThis->Att.FellowBehind = node;                          //fellow behind gets its new fellow before
  else                                                           //fellow behind is not existing
   {}                                                            //nothing to do

  ReturnValue = node;                                            //change return to process passed successfully
 }
 else                                                            //sponsor is not valid
 {
                                                                 //no adding possible
                                                                 //but ReturnValue is already nullptr
 }
 return(ReturnValue);                                            //return result
}


/* @MRTZ_describe cutNode

*/
template <class DataType, DataType defaultData>
Association<DataType, defaultData>*  AssociationFellowship<DataType, defaultData>::cutNode(Association<DataType, defaultData>* node)
{
 Association<DataType, defaultData>* ReturnValue  = nullptr;          //prepare a return of process failed
 AssociationFellowship* Node         = nullptr;

 if(node != nullptr)
  Node         = node    ->as_AssociationFellowship();

 if(Node != nullptr)                                                  //node is a valid node
 {

  AssociationFellowship* Sponsor      = nullptr;
  AssociationFellowship* FellowBefore = nullptr;
  AssociationFellowship* FellowBehind = nullptr;

  if(Node->Att.Sponsor!= nullptr)
   Sponsor      = Node->Att.Sponsor     ->as_AssociationFellowship(); //already known by node
  if(Node->Att.FellowBefore!= nullptr)
   FellowBefore = Node->Att.FellowBefore->as_AssociationFellowship(); //already known by node
  if(Node->Att.FellowBehind!= nullptr)
   FellowBehind = Node->Att.FellowBehind->as_AssociationFellowship(); //already known by node

  Node->Att.Sponsor = nullptr;                                        //node looses its sponsor
  if(  (Sponsor != nullptr)
     &&(Sponsor->Att.ContractorFirst == node)
    )                                                                 //node was first contractor of sponsor
   Sponsor->Att.ContractorFirst = FellowBehind;                       //fellow is new first contractor of sponsor
  else                                                                //node was contractor inside of the chain of fellows
   {}                                                                 //nothing to do
  if(  (Sponsor != nullptr)
     &&(Sponsor->Att.ContractorLast == node)
    )                                                                 //node was last contractor of sponsor
   Sponsor->Att.ContractorLast = FellowBefore;                        //fellow is new last contractor of sponsor
  else                                                                //fellow is contractor inside of the chain of fellows
   {}                                                                 //nothing to do

  Node->Att.FellowBefore = nullptr;                                   //node looses new fellow before
  if(FellowBefore != nullptr)                                         //fellow before is an existing fellow
   FellowBefore->Att.FellowBehind = FellowBehind;                     //fellow before gets its new fellow behind
  else                                                                //fellow before is not existing
   {}                                                                 //nothing to do

  Node->Att.FellowBehind = nullptr;                                   //node looses its new fellow behind
  if(FellowBehind != nullptr)                                         //fellow before is an existing fellow
   FellowBehind->Att.FellowBefore = FellowBefore;                     //fellow behind gets its new fellow before
  else                                                                //fellow behind is not existing
   {}                                                                 //nothing to do

  ReturnValue = node;                                                 //change return to process passed successfully
 }
 else                                                                 //node is not valid
 {
                                                                      //no adding possible
                                                                      //but ReturnValue is already nullptr
 }
 return(ReturnValue);                                                 //return result
}











/* @MRTZ_describe cutNode

*/
template <class DataType, DataType defaultData> bool
AssociationFellowship<DataType, defaultData>::swapNodes(Association<DataType, defaultData>* node1,
                                                        Association<DataType, defaultData>* node2)
{
 bool                   ReturnValue  = false;                           //prepare a return of process failed
 AssociationFellowship* Node1        = nullptr;                         //to store first iterator to swap
 AssociationFellowship* Node2        = nullptr;                         //to store second iterator to swap

 if(node1 != nullptr)
  Node1  = node1    ->as_AssociationFellowship();

 if(node2 != nullptr)
  Node2  = node2    ->as_AssociationFellowship();





 AssociationFellowship* Sponsor1      = nullptr;
 AssociationFellowship* FellowBefore1 = nullptr;
 AssociationFellowship* FellowBehind1 = nullptr;

 AssociationFellowship* Sponsor2      = nullptr;
 AssociationFellowship* FellowBefore2 = nullptr;
 AssociationFellowship* FellowBehind2 = nullptr;

 if(Node1 != nullptr)                                                   //node is a valid node
 {

  if(Node1->Att.Sponsor!= nullptr)
   Sponsor1      = Node1->Att.Sponsor     ->as_AssociationFellowship(); //already known by node
  if(Node1->Att.FellowBefore!= nullptr)
   FellowBefore1 = Node1->Att.FellowBefore->as_AssociationFellowship(); //already known by node
  if(Node1->Att.FellowBehind!= nullptr)
   FellowBehind1 = Node1->Att.FellowBehind->as_AssociationFellowship(); //already known by node
 }

 if(Node2 != nullptr)                                                    //node is a valid node
 {

  if(Node2->Att.Sponsor!= nullptr)
   Sponsor2      = Node2->Att.Sponsor     ->as_AssociationFellowship(); //already known by node
  if(Node2->Att.FellowBefore!= nullptr)
   FellowBefore2 = Node2->Att.FellowBefore->as_AssociationFellowship(); //already known by node
  if(Node2->Att.FellowBehind!= nullptr)
   FellowBehind2 = Node2->Att.FellowBehind->as_AssociationFellowship(); //already known by node
 }

 if(  (Node1    != nullptr)
    &&(Node2    != nullptr)
    &&(Sponsor1 != nullptr)
    &&(Sponsor1 == Sponsor2)
   )
 {
  if     (Sponsor1->Att.ContractorFirst == node1)                       //first node to swap was first contractor of sponsor
   Sponsor1->Att.ContractorFirst = node2;                               //second node to swap is new first contractor of sponsor
  else if(Sponsor1->Att.ContractorFirst == node2)                       //second node to swap was first contractor of sponsor                                                              //node was contractor inside of the chain of fellows
   Sponsor1->Att.ContractorFirst = node1;                               //first node to swap is new first contractor of sponsor
  else                                                                  //node was contractor inside of the chain of fellows
   {}                                                                   //nothing to do

       if(Sponsor2->Att.ContractorLast == node1)                        //first node to swap was last contractor of sponsor
   Sponsor2->Att.ContractorLast = node2;                                //second node to swap is new last contractor of sponsor
  else if(Sponsor2->Att.ContractorLast == node2)                        //second node to swap was last contractor of sponsor                                                              //node was contractor inside of the chain of fellows
   Sponsor2->Att.ContractorLast = node1;                                //first node to swap is new last contractor of sponsor
  else                                                                  //node was contractor inside of the chain of fellows
   {}                                                                   //nothing to do
 }
 else                                                                   //node is not valid
 {
 }


 if(  (Node1    != nullptr)
    &&(Node2    != nullptr)
    &&(Sponsor1 == Sponsor2)
   )
 {
  Node1->Att.FellowBefore = FellowBefore2;
  if(FellowBefore2 != nullptr)                                          //fellow before is an existing fellow
   FellowBefore2->Att.FellowBehind = Node1;
  else                                                                  //fellow before is not existing
   {}                                                                   //nothing to do

  Node1->Att.FellowBehind = FellowBehind2;
  if(FellowBehind2 != nullptr)                                          //fellow before is an existing fellow
   FellowBehind2->Att.FellowBefore = Node1;
  else                                                                  //fellow before is not existing
   {}                                                                   //nothing to do

  Node2->Att.FellowBefore = FellowBefore1;
  if(FellowBefore1 != nullptr)                                          //fellow before is an existing fellow
   FellowBefore1->Att.FellowBehind = Node2;
  else                                                                  //fellow before is not existing
   {}                                                                   //nothing to do

  Node2->Att.FellowBehind = FellowBehind1;
  if(FellowBehind1 != nullptr)                                          //fellow before is an existing fellow
   FellowBehind1->Att.FellowBefore = Node2;
  else                                                                  //fellow before is not existing
   {}                                                                   //nothing to do
  ReturnValue = true;                                                   //change return to process passed successfully
 }
 else                                                                   //node is not valid
 {
 }

 return(ReturnValue);                                                   //return result
}











/* @MRTZ_describe isAncestor

*/
template <class DataType, DataType defaultData>
Association<DataType, defaultData>*   AssociationFellowship<DataType, defaultData>::isAncestor(Association<DataType, defaultData>* node,
                                                                                               ASSOCIATION_UNUSED*                 sponsor)
{
 if     (Att.Sponsor == node)
  return(node);
 else if(Att.Sponsor != nullptr)
  return(Att.Sponsor->isAncestor(node));
 else
  return(nullptr);
}



/* @MRTZ_describe isSponsor

*/
template <class DataType, DataType defaultData>
Association<DataType, defaultData>*   AssociationFellowship<DataType, defaultData>::isSponsor(Association<DataType, defaultData>* node)
{
 if(Att.Sponsor == node)
  return(node);
 else
  return(nullptr);
}



/* @MRTZ_describe isContractor

*/
template <class DataType, DataType defaultData>
Association<DataType, defaultData>*   AssociationFellowship<DataType, defaultData>::isContractor(Association<DataType, defaultData>* node)
{
 Association<DataType, defaultData>* ReturnValue = this->Att.ContractorFirst;
 while(  (ReturnValue != nullptr)
       &&(ReturnValue != node)
      )
 {
  ReturnValue = ReturnValue->as_AssociationFellowship()->Att.FellowBehind;
 }

 return(ReturnValue);
}



/* @MRTZ_describe isFellow

*/
template <class DataType, DataType defaultData>
Association<DataType, defaultData>*   AssociationFellowship<DataType, defaultData>::isFellow(Association<DataType, defaultData>* node,
                                                                                             ASSOCIATION_UNUSED*                 sponsor)
{
 Association<DataType, defaultData>* ReturnValue = this->fellowFirst_get();

 if(node != this)
 {
  while(  (ReturnValue != nullptr)
        &&(ReturnValue != node)
       )
  {
   ReturnValue = ReturnValue->fellowBehind_get();
  }
 }
 else
 {
  ReturnValue = nullptr;
 }

 return(ReturnValue);
}









/* @MRTZ_describe welcome

*/
template <class DataType, DataType defaultData>
void AssociationFellowship<DataType, defaultData>::welcome(AssociationVisitor<DataType, defaultData>*  visitor,
                                                           DirectionOfIteration                        direction,
                                                           ASSOCIATION_UNUSED*                         sponsor)
{
 Association<DataType, defaultData>* CurrentNode  = this;


 visitor  -> direction_set(direction);                   // set the direction as defined by user

 while(  (CurrentNode  != nullptr)
       &&(direction    != IterateNoMore)
      )
 {

  direction = visitor->evaluate(CurrentNode/*,Att.Sponsor*/); // change of  direction as defined while the evaluation

  switch(direction)
  {
   case IterateWithFound:
   {
//     LOG_OUTPUT(LOG_OFF, "IterateWithFound");
     CurrentNode = visitor->node_get();
   }break;

   case IterateForwards:
   {
//     LOG_OUTPUT(LOG_OFF, "IterateForwards");
     CurrentNode = CurrentNode->fellowBehind_get();
   }break;

   case IterateBackwards:
   {
//     LOG_OUTPUT(LOG_OFF, "IterateBackwards");
     CurrentNode = CurrentNode->fellowBefore_get();
   }break;

   case IterateUpwards:
   {
//     LOG_OUTPUT(LOG_OFF, "IterateUpwards");
     CurrentNode = CurrentNode->sponsor_get();
   }break;

   case IterateDownwards:
   {
//     LOG_OUTPUT(LOG_OFF, "IterateDownwards");
     CurrentNode = CurrentNode->contractorFirst_get();
   }break;

   case IterateDownwardsReverse:
   {
//      LOG_OUTPUT(LOG_OFF, "IterateDownwardsReverse");
      CurrentNode = CurrentNode->contractorLast_get();
   }break;

   case IterateAsBefore:
   case IterateNoMore:
   default:
   {
//    LOG_OUTPUT(LOG_OFF, "Iteration finished");
//    printf("found node : %d \n",CurrentNode);

    direction = IterateNoMore; // fail-reaction
   }break;
  }
 }
}









#ifndef DOXYGEN
#define USING_NAMESPACE using namespace
//}; USING_NAMESPACE ASSOCIATION;
//}; USING_NAMESPACE TXTDIASM;
#undef  USING_NAMESPACE
#endif //DOXYGEN


#endif // ASSOCIATION_FELLOWSHIP_HPP


