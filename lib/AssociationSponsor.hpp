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
// @MRTZ_skip
#ifndef ASSOCIATION_SPONSOR_HPP
 #define ASSOCIATION_SPONSOR_HPP


//#define DEBUG_OUTPUT_LOG



#include "AssociationSponsor.h"
//#include "TDA_GrmConcrete.h"

#include <cstring>
#include <iostream>




#define INLINE_1 inline
#define INLINE_2 inline

#ifndef DOXYGEN
////namespace TXTDIASM {
//namespace ASSOCIATION {
#endif //DOXYGEN

/* @MRTZ_describe AssociationSponsordefaultData

*/
template <class DataType, DataType defaultData>
AssociationSponsor<DataType, defaultData>::AssociationSponsor(void)
                                          :Association<DataType, defaultData>(),
                                           Att()
{
}


/* @MRTZ_describe AssociationSponsor
  transfer data to base-class constructor
*/
template <class DataType, DataType defaultData>
AssociationSponsor<DataType, defaultData>::AssociationSponsor(DataType data)
                                          :Association<DataType, defaultData>(data),
                                           Att()
{
}


/* @MRTZ_describe AssociationSponsor
 copy the data of the given association and add its contractors by calling
 recursively this cast-constructor
*/
template <class DataType, DataType defaultData>
AssociationSponsor<DataType, defaultData>::AssociationSponsor(Association<DataType, defaultData>* association)
                                          :Att()
{
 this->data_set(association->data_get());

 Association<DataType, defaultData>* Contractor = association->contractorFirst_get();
 while(Contractor != nullptr)
 {
  this->contractorLast_add(new AssociationSponsor<DataType, defaultData>(Contractor));
  Contractor = association->contractorBehind_get(Contractor);
 }

}



/* @MRTZ_describe operator=

*/
template <class DataType, DataType defaultData> inline
AssociationSponsor<DataType, defaultData>& AssociationSponsor<DataType, defaultData>::operator= (Association<DataType, defaultData>& association)
{
 this->data_set(association->data_get());

 Association<DataType, defaultData>* Contractor = association->contractorFirst_get();
 while(Contractor != nullptr)
 {
  this->contractorLast_add(new AssociationSponsor<DataType, defaultData>(Contractor));
  Contractor = association->contractorBehind_get(Contractor);
 }

 return(*this);
}




/* @MRTZ_describe ~AssociationSponsor

*/
template <class DataType, DataType defaultData>
AssociationSponsor<DataType, defaultData>::~AssociationSponsor(void)
{
 Att.Contractor.clear();
}

/* @MRTZ_describe to_TDA_AssociationSponsor

*/
template <class DataType, DataType defaultData> inline /*INLINE_1*/
AssociationSponsor<DataType, defaultData>*  AssociationSponsor<DataType, defaultData>::as_AssociationSponsor(void)
{
 return(this);
}


/* @MRTZ_describe to_TDA_AssociationFellowship

*/
template <class DataType, DataType defaultData> inline /*INLINE_1*/
AssociationFellowship<DataType, defaultData>*  AssociationSponsor<DataType, defaultData>::as_AssociationFellowship(void)
{
 return(nullptr);
}



/* @MRTZ_describe newObject

*/
template <class DataType, DataType defaultData> inline /*INLINE_1*/
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::newObject(void)
{
 return(new AssociationSponsor<DataType, defaultData>);
}



/* @MRTZ_describe newObject

*/
template <class DataType, DataType defaultData> inline /*INLINE_1*/
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::newObject(DataType data)
{
 return(new AssociationSponsor<DataType, defaultData>(data));
}



/* @MRTZ_describe newObject

*/
template <class DataType, DataType defaultData> inline /*INLINE_1*/
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::newObject(Association<DataType, defaultData>* association)
{
 return(new AssociationSponsor<DataType, defaultData>(association));
}



/* @MRTZ_describe sponsor_get
   return the given sponsor if this association is its contractor
*/
template <class DataType, DataType defaultData> inline /*INLINE_2*/
  Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::sponsor_get(Association<DataType, defaultData>* sponsor)
{
 if(sponsor == nullptr)
  return(nullptr);
 else if(sponsor->isContractor(this) != nullptr)
  return(sponsor);
 else
  return(nullptr);
}







/* @MRTZ_describe contractorBefore_add

*/
template <class DataType, DataType defaultData> inline /*INLINE_1*/
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::contractorBefore_add(Association<DataType, defaultData>* beforeThis,
                                                                                                    Association<DataType, defaultData>* node)
{
 return(addNode(node, this, nullptr, beforeThis));
}



/* @MRTZ_describe contractorBefore_add

*/
template <class DataType, DataType defaultData>
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::contractorBefore_add(Association<DataType, defaultData>*        beforeThis,
                                                                                                    Association<DataType, defaultData>*        node,
                                                                                                    AssociationVisitor<DataType, defaultData>* visitor)
{
 Association<DataType, defaultData>* ReturnValue = nullptr;               // prepare with no success

 if(this->isContractor(beforeThis) != nullptr)                            // beforeThis is a valid node
 {
  beforeThis->welcome(visitor,IterateBackwards,this);
                                                                          // start search with given visitor
  Association<DataType, defaultData>* Contractor = visitor->node_get();   // result of search
  if(Contractor != nullptr)                                               // result is a valid node
   ReturnValue = addNode(node, this, nullptr, Contractor);                // add node before found contractor
  else                                                                    // result is not a valid node
  { }                                                                     // return-value is already set to no success
 }
 else                                                                     // beforeThis is not a valid node
 { }                                                                      // return-value is already set to no success

 return(ReturnValue);                                                     // return result
}




/* @MRTZ_describe contractorBefore_cut

*/
template <class DataType, DataType defaultData>
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::contractorBefore_cut(Association<DataType, defaultData>* beforeThis)
{
 Association<DataType, defaultData>*                 ReturnValue = nullptr; // prepare no success
 typename list< Association<DataType, defaultData>* >::iterator Contractor; // to iterate over Contractors

 Contractor = Att.Contractor.begin();                                       // first contractor
 while(Contractor != Att.Contractor.end())                                  // until last contractor
 {
  if((*Contractor == beforeThis))                                           // beforeThis found is contractor
  {
   if(Contractor != Att.Contractor.begin())                                 // until second contractor
   {
    --Contractor;                                                           // step back to the node to cut
    ReturnValue = cutNode(*Contractor);                                     // remove node as contractor
   }
   else                                                                     // result is not a valid contractor
    { }                                                                     // return-value is already set to no success
   break;
  }
  else
  {
   ++Contractor;                                                            // next contractor
  }
 }

 return(ReturnValue);
}


/* @MRTZ_describe contractorBefore_cut

*/
template <class DataType, DataType defaultData>
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::contractorBefore_cut(Association<DataType, defaultData>*        beforeThis,
                                                                                                    AssociationVisitor<DataType, defaultData>* visitor)
{
 Association<DataType, defaultData>* ReturnValue = nullptr;               // prepare no success

 if(this->isContractor(beforeThis) != nullptr)                            // beforeThis is a valid contractor
 {
  beforeThis->welcome(visitor,IterateBackwards,this);
  Association<DataType, defaultData>* Contractor = visitor->node_get();   // result of search
  if(Contractor != nullptr)                                               // result is a valid node
  {
   ReturnValue = cutNode(this->contractorBefore_get(Contractor));
                                                                          // remove node as contractor
  }
  else                                                                    // result is not a valid contractor
  { }                                                                     // return-value is already set to no success
 }
 else                                                                     // beforeThis is not a valid contractor
 { }                                                                      // return-value is already set to no success

 return(ReturnValue);
}




/* @MRTZ_describe contractorBefore_delete

*/
template <class DataType, DataType defaultData>
 Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::contractorBefore_delete(Association<DataType, defaultData>* beforeThis)
{
 Association<DataType, defaultData>*                 ReturnValue = nullptr;          // prepare no success
 typename  list<Association<DataType, defaultData>*>::iterator Contractor;           // to iterate over Contractors

 Contractor = Att.Contractor.begin();                                                // first contractor
 while(Contractor != Att.Contractor.end())                                           // until last contractor
 {
  if((*Contractor == beforeThis))                                                    // beforeThis found is contractor
  {
   if(Contractor != Att.Contractor.begin())                                          // until second contractor
   {
    --Contractor;                                                                    // step back to the node to cut
    ReturnValue = Association<DataType, defaultData>::deleteNode(*Contractor,this);  // remove node as contractor
   }
   else                                                                              // result is not a valid contractor
    { }                                                                              // return-value is already set to no success
   break;
  }
  else
  {
   ++Contractor;                                                                     // next contractor
  }
 }

 return(ReturnValue);
}



/* @MRTZ_describe contractorBefore_delete

*/
template <class DataType, DataType defaultData>
 Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::contractorBefore_delete(Association<DataType, defaultData>*        beforeThis,
                                                                                                        AssociationVisitor<DataType, defaultData>* visitor)
{
 Association<DataType, defaultData>* ReturnValue = nullptr;               // prepare sponsor pointer with non no success

 if(this->isContractor(beforeThis) != nullptr)                            // beforeThis is a valid contractor
 {
  beforeThis->welcome(visitor,IterateBackwards,this);                     // start search with given visitor
  Association<DataType, defaultData>* Contractor = visitor->node_get();   // result of search
  if(Contractor != nullptr)                                               // result is a valid node
  {
   ReturnValue = Association<DataType, defaultData>::deleteNode(this->contractorBefore_get(Contractor),this);
                                                                          // remove node as contractor
  }
  else                                                                    // result is not a valid contractor
  { }                                                                     // return-value is already set to no success
 }
 else                                                                     // beforeThis is not a valid contractor
 { }                                                                      // return-value is already set to no success

 return(ReturnValue);                                                     // sponsor-pointer to this-class pointer
}






/* @MRTZ_describe contractorBefore_get

*/
template <class DataType, DataType defaultData>
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::contractorBefore_get(Association<DataType, defaultData>* beforeThis)
{
 Association<DataType, defaultData>*                 ReturnValue = nullptr;  // prepare no success
 typename list<Association<DataType, defaultData>*>::iterator Contractor;    // to iterate over Contractors

 Contractor = Att.Contractor.begin();                                        // first contractor
 while(Contractor != Att.Contractor.end())                                   // until last contractor
 {
  if((*Contractor == beforeThis))                                            // beforeThis found is contractor
  {
   if(Contractor != Att.Contractor.begin())                                  // until second contractor
   {
    --Contractor;                                                            // step back to the node to cut
    ReturnValue = (*Contractor);                                             // prepare return of found contractor
   }
   else                                                                      // result is not a valid contractor
    { }                                                                      // return-value is already set to no success
   break;
  }
  else
  {
   ++Contractor;                                                             // next contractor
  }
 }

 return(ReturnValue);
}


/* @MRTZ_describe contractorBefore_get

*/
template <class DataType, DataType defaultData>
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::contractorBefore_get(Association<DataType, defaultData>*        beforeThis,
                                                                                                    AssociationVisitor<DataType, defaultData>* visitor)
{
 Association<DataType, defaultData>* ReturnValue = nullptr;               // prepare sponsor pointer with non no success

 if(this->isContractor(beforeThis) != nullptr)                            // beforeThis is a valid contractor
 {
  beforeThis->welcome(visitor,IterateBackwards,this);                     // start search with given visitor
  Association<DataType, defaultData>* Contractor = visitor->node_get();   // result of search
  if(Contractor != nullptr)                                               // result is a valid node
  {
   ReturnValue = this->contractorBefore_get(Contractor);                  // prepare return of found contractor
  }
  else                                                                    // result is not a valid contractor
  { }                                                                     // return-value is already set to no success
 }
 else                                                                     // beforeThis is not a valid contractor
 { }                                                                      // return-value is already set to no success

 return(ReturnValue);                                                     // sponsor-pointer to this-class pointer
}








/* @MRTZ_describe contractorBehind_add

*/
template <class DataType, DataType defaultData> inline /*INLINE_1*/
 Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::contractorBehind_add(Association<DataType, defaultData>* behindThis,
                                                                                                     Association<DataType, defaultData>* node)
{
 return(addNode(node, this, behindThis, nullptr));
}


/* @MRTZ_describe contractorBehind_add

*/
template <class DataType, DataType defaultData>
 Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::contractorBehind_add(Association<DataType, defaultData>*        behindThis,
                                                                                                     Association<DataType, defaultData>*        node,
                                                                                                     AssociationVisitor<DataType, defaultData>*visitor)
{
 Association<DataType, defaultData>* ReturnValue = nullptr;              // prepare with no success

 behindThis->welcome(visitor,IterateForwards,this);                      // start search with given visitor
                                                                         // start search with given visitor
 Association<DataType, defaultData>* Contractor = visitor->node_get();   // result of search
 if(Contractor != nullptr)                                               // result is a valid node
  ReturnValue = addNode(node, this, Contractor, nullptr);                // add node before found contractor
 else                                                                    // result is not a valid node
 { }                                                                     // return-value is already set to no success

 return(ReturnValue);                                                    // return result
}



/* @MRTZ_describe contractorBehind_cut

*/
template <class DataType, DataType defaultData>
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::contractorBehind_cut(Association<DataType, defaultData>* behindThis)
{
 Association<DataType, defaultData>*                 ReturnValue = nullptr;   // prepare no success
 typename list<Association<DataType, defaultData>*>::iterator Contractor;     // to iterate over Contractors

 Contractor = Att.Contractor.begin();                                         // first contractor
 while(Contractor != Att.Contractor.end())                                    // until last contractor
 {
  if((*Contractor == behindThis))                                             // beforeThis found is contractor
  {
   ++Contractor;                                                              // step forwards to the node to cut
   if(Contractor != Att.Contractor.end())                                     // until last contractor
    ReturnValue = cutNode(*Contractor);                                       // remove node as contractor
   else                                                                       // result is not a valid contractor
    { }                                                                       // return-value is already set to no success
   break;
  }
  else
  {
   ++Contractor;                                                              // next contractor
  }
 }

 return(ReturnValue);
}



/* @MRTZ_describe contractorBehind_cut

*/
template <class DataType, DataType defaultData>
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::contractorBehind_cut(Association<DataType, defaultData>*        behindThis,
                                                                                                    AssociationVisitor<DataType, defaultData>* visitor)
{
 Association<DataType, defaultData>* ReturnValue = nullptr;              // prepare no success

 behindThis->welcome(visitor,IterateForwards,this);                      // start search with given visitor
 Association<DataType, defaultData>* Contractor = visitor->node_get();   // result of search
 if(Contractor != nullptr)                                               // result is a valid node
 {
  ReturnValue = cutNode(this->contractorBehind_get(Contractor));
                                                                         // remove node as contractor
 }
 else                                                                    // result is not a valid contractor
  { }                                                                    // return-value is already set to no success

 return(ReturnValue);
}






/* @MRTZ_describe contractorBehind_delete

*/
template <class DataType, DataType defaultData>
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::contractorBehind_delete(Association<DataType, defaultData>* behindThis)
{
 Association<DataType, defaultData>*                 ReturnValue = nullptr;           // prepare no success
 typename  list<Association<DataType, defaultData>*>::iterator Contractor;            // to iterate over Contractors

 Contractor = Att.Contractor.begin();                                                 // first contractor
 while(Contractor != Att.Contractor.end())                                            // until last contractor
 {
  if((*Contractor == behindThis))                                                     // beforeThis found is contractor
  {
   ++Contractor;                                                                      // step forwards to the node to delete
   if(Contractor != Att.Contractor.end())                                             // until last contractor
    ReturnValue = Association<DataType, defaultData>::deleteNode(*Contractor,this);   // remove node as contractor
   else                                                                               // result is not a valid contractor
    { }                                                                               // return-value is already set to no success
   break;
  }
  else
  {
   ++Contractor;                                                                     // next contractor
  }
 }

 return(ReturnValue);
}



/* @MRTZ_describe contractorBehind_delete

*/
template <class DataType, DataType defaultData>
 Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::contractorBehind_delete(Association<DataType, defaultData>*        behindThis,
                                                                                                        AssociationVisitor<DataType, defaultData>* visitor)
{
 Association<DataType, defaultData>* ReturnValue = nullptr;              // prepare no success

 behindThis->welcome(visitor,IterateForwards,this);                      // start search with given visitor
 Association<DataType, defaultData>* Contractor = visitor->node_get();   // result of search
 if(Contractor != nullptr)                                               // result is a valid node
 {
  ReturnValue = Association<DataType, defaultData>::deleteNode(this->contractorBehind_get(Contractor),this);
                                                                         // remove node as contractor
 }
 else                                                                    // result is not a valid contractor
 { }                                                                     // return-value is already set to no success

 return(ReturnValue);
}






/* @MRTZ_describe contractorBehind_get

*/
template <class DataType, DataType defaultData>
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::contractorBehind_get(Association<DataType, defaultData>* behindThis)
{
 Association<DataType, defaultData>*                 ReturnValue = nullptr;        // prepare no success
 typename  list<Association<DataType, defaultData>*>::iterator Contractor;         // to iterate over Contractors

 Contractor = Att.Contractor.begin();                                              // first contractor
 while(Contractor != Att.Contractor.end())                                         // until last contractor
 {
  if((*Contractor == behindThis))                                                  // beforeThis found is contractor
  {
   ++Contractor;
   if(Contractor != Att.Contractor.end())                                          // until last contractor
    ReturnValue = (*Contractor);                                                   // prepare return of found contractor
   else                                                                            // result is not a valid contractor
   { }                                                                             // return-value is already set to no success
   break;


  }
  else
  {
   ++Contractor;                                                                   // next contractor
  }
 }

 return(ReturnValue);
}



/* @MRTZ_describe contractorBehind_get

*/
template <class DataType, DataType defaultData>
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::contractorBehind_get(Association<DataType, defaultData>*        behindThis,
                                                                                                    AssociationVisitor<DataType, defaultData>* visitor)
{
 Association<DataType, defaultData>* ReturnValue = nullptr;              // prepare sponsor pointer with non no success

 behindThis->welcome(visitor,IterateForwards,this);                      // start search with given visitor
 Association<DataType, defaultData>* Contractor = visitor->node_get();   // result of search
 if(Contractor != nullptr)                                               // result is a valid node
 {
  ReturnValue = this->contractorBehind_get(Contractor);                  // prepare return of found contractor
 }
 else                                                                    // result is not a valid contractor
 { }                                                                     // return-value is already set to no success

 return(ReturnValue);                                                    // sponsor-pointer to this-class pointer
}










/* @MRTZ_describe contractorFirst_add

*/
template <class DataType, DataType defaultData> inline /*INLINE_1*/
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::contractorFirst_add(Association<DataType, defaultData>* node)
{
 Att.Contractor.push_front(node);
 return(node);
}




/* @MRTZ_describe contractorFirst_cut

*/
template <class DataType, DataType defaultData> inline /*INLINE_2*/
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::contractorFirst_cut(void)
{
 if(Att.Contractor.empty())
  return(nullptr);
 else
  return(cutNode(*(Att.Contractor.begin())));
}


/* @MRTZ_describe contractorFirst_cut

*/
template <class DataType, DataType defaultData>
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::contractorFirst_cut(AssociationVisitor<DataType, defaultData>*visitor)
{
 (*(Att.Contractor.begin()))->welcome(visitor,IterateForwards,this);
                                                                          // start search with given visitor
 Association<DataType, defaultData>* Contractor  = visitor->node_get();   // result of search
 Association<DataType, defaultData>* ReturnValue = cutNode(Contractor);   // remove node as contractor

 return(ReturnValue);
}





/* @MRTZ_describe contractorFirst_delete

*/
template <class DataType, DataType defaultData> inline /*INLINE_2*/
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::contractorFirst_delete(void)
{
 if(Att.Contractor.empty())
  return(nullptr);
 else
  return(Association<DataType, defaultData>::deleteNode(*(Att.Contractor.begin()),this));
}


/* @MRTZ_describe contractorFirst_delete

*/
template <class DataType, DataType defaultData>
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::contractorFirst_delete(AssociationVisitor<DataType, defaultData>* visitor)
{
 (*(Att.Contractor.begin()))->welcome(visitor,IterateForwards,this);                                                // start search with given visitor

 Association<DataType, defaultData>* Contractor  = visitor->node_get();                                             // result of search
 Association<DataType, defaultData>* ReturnValue = Association<DataType, defaultData>::deleteNode(Contractor,this); // remove node as contractor

 return(ReturnValue);
}






/* @MRTZ_describe contractorFirst_get
   simple return of attribute
*/
template <class DataType, DataType defaultData> inline /*INLINE_2*/
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::contractorFirst_get(void)
{
 if(Att.Contractor.empty())
  return(nullptr);
 else
  return(*(Att.Contractor.begin()));
}


/* @MRTZ_describe contractorFirst_get

*/
template <class DataType, DataType defaultData>
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::contractorFirst_get(AssociationVisitor<DataType, defaultData>*visitor)
{
 (*(Att.Contractor.begin()))->welcome(visitor,IterateForwards,this);         // start search with given visitor
 Association<DataType, defaultData>* ReturnValue  = visitor->node_get();     // result of search

 return(ReturnValue);
}










/* @MRTZ_describe contractorLast_add

*/
template <class DataType, DataType defaultData> inline /*INLINE_1*/
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::contractorLast_add(Association<DataType, defaultData>* node)
{
 Att.Contractor.push_back(node);
 return(node);
}


/* @MRTZ_describe contractorLast_cut

*/
template <class DataType, DataType defaultData> inline /*INLINE_2*/
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::contractorLast_cut(void)
{
 if(Att.Contractor.empty())
  return(nullptr);
 else
  return(cutNode(*(Att.Contractor.rbegin())));
}


/* @MRTZ_describe contractorLast_cut

*/
template <class DataType, DataType defaultData>
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::contractorLast_cut(AssociationVisitor<DataType, defaultData>*visitor)
{
 (*(Att.Contractor.rbegin()))->welcome(visitor,IterateBackwards,this);         // start search with given visitor
 Association<DataType, defaultData>* Contractor  = visitor->node_get();        // result of search
 Association<DataType, defaultData>* ReturnValue = cutNode(Contractor);        // remove node as contractor

 return(ReturnValue);
}


/* @MRTZ_describe contractorLast_delete

*/
template <class DataType, DataType defaultData> inline /*INLINE_2*/
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::contractorLast_delete(void)
{
 if(Att.Contractor.empty())
  return(nullptr);
 else
  return(Association<DataType, defaultData>::deleteNode(*(Att.Contractor.rbegin()), this));
}


/* @MRTZ_describe contractorLast_delete

*/
template <class DataType, DataType defaultData>
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::contractorLast_delete(AssociationVisitor<DataType, defaultData>* visitor)
{
 (*(Att.Contractor.rbegin()))->welcome(visitor,IterateBackwards,this);                           // start search with given visitor
 Association<DataType, defaultData>* Contractor  = visitor->node_get();                          // result of search
 Association<DataType, defaultData>* ReturnValue = Association<DataType, defaultData>::deleteNode(Contractor, this);
                                                                                                 // remove node as contractor
 return(ReturnValue);
}




/* @MRTZ_describe contractorLast_get
   simple return of attribute
*/
template <class DataType, DataType defaultData> inline /*INLINE_2*/
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::contractorLast_get(void)
{
 if(Att.Contractor.empty())
  return(nullptr);
 else
  return(*(Att.Contractor.rbegin()));
}




/* @MRTZ_describe contractorLast_get

*/
template <class DataType, DataType defaultData> inline /*INLINE_2*/
 Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::contractorLast_get(AssociationVisitor<DataType, defaultData>* visitor)
{
 (*(Att.Contractor.rbegin()))->welcome(visitor,IterateBackwards,this);  // start search with given visitor
 return(visitor->node_get());                                           // result of search
}











/* @MRTZ_describe fellowBefore_add

*/
template <class DataType, DataType defaultData> inline /*INLINE_2*/
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::fellowBefore_add(Association<DataType, defaultData>* node,
                                                                                                Association<DataType, defaultData>* sponsor)
{

 if(sponsor != nullptr)                                    // this is a valid sponsor
  return(sponsor->contractorBefore_add(this,node));        // sponsor adds as contractor
 else                                                      // sponsor is not a valid node
  return(nullptr);                                         // return-value is already set to no success
}






/* @MRTZ_describe fellowBefore_add

*/
template <class DataType, DataType defaultData> inline /*INLINE_2*/
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::fellowBefore_add(Association<DataType, defaultData>*        node,
                                                                                                AssociationVisitor<DataType, defaultData>* visitor,
                                                                                                Association<DataType, defaultData>*        sponsor)
{
 if(sponsor != nullptr)                                     // this is a valid sponsor
  return(sponsor->contractorBefore_add(this,node,visitor)); // sponsor adds as contractor
 else                                                       // sponsor is not a valid node
  return(nullptr);                                          // return-value is already set to no success
}




/* @MRTZ_describe fellowBefore_cut

*/
template <class DataType, DataType defaultData> inline /*INLINE_2*/
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::fellowBefore_cut(Association<DataType, defaultData>* sponsor)
{
 if(sponsor != nullptr)                                    // this is a valid sponsor
  return(sponsor->contractorBefore_cut(this));             // sponsor cuts out contractor
 else                                                      // sponsor is not a valid node
  return(nullptr);                                         // return no success
}




/* @MRTZ_describe fellowBefore_cut

*/
template <class DataType, DataType defaultData> inline /*INLINE_2*/
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::fellowBefore_cut(AssociationVisitor<DataType, defaultData>* visitor,
                                                                                                Association<DataType, defaultData>*        sponsor)
{
 if(sponsor != nullptr)                                    // this is a valid sponsor
  return(sponsor->contractorBefore_cut(this,visitor));     // sponsor cuts out contractor
 else                                                      // sponsor is not a valid node
  return(nullptr);                                         // return no success
}







/* @MRTZ_describe fellowBefore_delete

*/
template <class DataType, DataType defaultData> inline /*INLINE_2*/
 Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::fellowBefore_delete(Association<DataType, defaultData>* sponsor)
{
 if(sponsor != nullptr)                                    // this is a valid sponsor
  return(sponsor->contractorBefore_delete(this));          // sponsor deletes contractor
 else                                                      // sponsor is not a valid node
  return(nullptr);                                         // return no success
}







/* @MRTZ_describe fellowBefore_delete

*/
template <class DataType, DataType defaultData> inline /*INLINE_2*/
 Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::fellowBefore_delete(AssociationVisitor<DataType, defaultData>* visitor,
                                                                                                    Association<DataType, defaultData>*        sponsor)
{
 if(sponsor != nullptr)                                    // this is a valid sponsor
  return(sponsor->contractorBefore_delete(this,visitor));  // sponsor deletes contractor
 else                                                      // sponsor is not a valid node
  return(nullptr);                                         // return no success
}



/* @MRTZ_describe fellowBefore_get
   simple return of attribute
*/
template <class DataType, DataType defaultData> inline /*INLINE_2*/
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::fellowBefore_get(Association<DataType, defaultData>* sponsor)
{
 if(sponsor != nullptr)                                    // this is a valid sponsor
  return(sponsor->contractorBefore_get(this));             // sponsor returns contractor
 else                                                      // sponsor is not a valid node
  return(nullptr);                                         // return no success
}




/* @MRTZ_describe fellowBefore_get
   simple return of attribute
*/
template <class DataType, DataType defaultData> inline /*INLINE_2*/
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::fellowBefore_get(AssociationVisitor<DataType, defaultData>* visitor,
                                                                                                Association<DataType, defaultData>*        sponsor)
{
 if(sponsor != nullptr)                                    // this is a valid sponsor
  return(sponsor->contractorBefore_get(this,visitor));     // sponsor returns contractor
 else                                                      // sponsor is not a valid node
  return(nullptr);                                         // return no success
}









/* @MRTZ_describe fellowBehind_add

*/
template <class DataType, DataType defaultData> inline /*INLINE_2*/
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::fellowBehind_add(Association<DataType, defaultData>* node,
                                                                                                Association<DataType, defaultData>* sponsor)
{
 if(sponsor != nullptr)                                    // this is a valid sponsor
  return(sponsor->contractorBehind_add(this,node));        // sponsor adds as contractor
 else                                                      // sponsor is not a valid node
  return(nullptr);                                         // return no success
}









/* @MRTZ_describe fellowBehind_add

*/
template <class DataType, DataType defaultData> inline /*INLINE_2*/
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::fellowBehind_add(Association<DataType, defaultData>* node,
                                                                                                ASSOCIATIONVISITOR_UNUSED*          visitor,
                                                                                                Association<DataType, defaultData>* sponsor)
{
 if(sponsor != nullptr)                                    // this is a valid sponsor
  return(sponsor->contractorBehind_add(this,node));        // sponsor adds as contractor
 else                                                      // sponsor is not a valid node
  return(nullptr);                                         // return no success
}





/* @MRTZ_describe fellowBehind_cut

*/
template <class DataType, DataType defaultData> inline /*INLINE_2*/
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::fellowBehind_cut(Association<DataType, defaultData>* sponsor)
{
 if(sponsor != nullptr)                                    // this is a valid sponsor
  return(sponsor->contractorBehind_cut(this));             // sponsor cuts out a contractor
 else                                                      // sponsor is not a valid node
  return(nullptr);                                         // return no success
}






/* @MRTZ_describe fellowBehind_cut

*/
template <class DataType, DataType defaultData> inline /*INLINE_2*/
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::fellowBehind_cut(AssociationVisitor<DataType, defaultData>* visitor,
                                                                                                Association<DataType, defaultData>*        sponsor)
{
 if(sponsor != nullptr)                                    // this is a valid sponsor
  return(sponsor->contractorBehind_cut(this,visitor));     // sponsor cuts out a contractor
 else                                                      // sponsor is not a valid node
  return(nullptr);                                         // return no success
}



/* @MRTZ_describe fellowBehind_delete

*/
template <class DataType, DataType defaultData> inline /*INLINE_2*/
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::fellowBehind_delete(Association<DataType, defaultData>* sponsor)
{
 if(sponsor != nullptr)                                    // this is a valid sponsor
  return(sponsor->contractorBehind_delete(this));          // sponsor deletes a contractor
 else                                                      // sponsor is not a valid node
  return(nullptr);                                         // return no success
}




/* @MRTZ_describe fellowBehind_delete

*/
template <class DataType, DataType defaultData> inline /*INLINE_2*/
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::fellowBehind_delete(AssociationVisitor<DataType, defaultData>* visitor,
                                                                                                   Association<DataType, defaultData>*        sponsor)
{
 if(sponsor != nullptr)                                         // this is a valid sponsor
  return(sponsor->contractorBehind_delete(this,visitor));       // sponsor deletes a contractor
 else                                                           // sponsor is not a valid node
  return(nullptr);                                              // return no success
}




/* @MRTZ_describe fellowBehind_get
   simple return of attribute
*/
template <class DataType, DataType defaultData> inline /*INLINE_2*/
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::fellowBehind_get(Association<DataType, defaultData>* sponsor)
{
 if(sponsor != nullptr)                                    // this is a valid sponsor
  return(sponsor->contractorBehind_get(this));             // sponsor returns a contractor
 else                                                      // sponsor is not a valid node
  return(nullptr);                                         // return no success
}



/* @MRTZ_describe fellowBehind_get
   simple return of attribute
*/
template <class DataType, DataType defaultData> inline /*INLINE_2*/
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::fellowBehind_get(AssociationVisitor<DataType, defaultData>* visitor,
                                                                                                Association<DataType, defaultData>*        sponsor)
{
 if(sponsor != nullptr)                                    // this is a valid sponsor
  return(sponsor->contractorBehind_get(this,visitor));     // sponsor returns a contractor
 else                                                      // sponsor is not a valid node
  return(nullptr);                                         // return no success
}









/* @MRTZ_describe fellowFirst_add

*/
template <class DataType, DataType defaultData> inline /*INLINE_2*/
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::fellowFirst_add(Association<DataType, defaultData>* node,
                                                                                               Association<DataType, defaultData>* sponsor)
{
 if(sponsor != nullptr)                               // this is a contractor of an other node
  return(sponsor->contractorFirst_add(node));         // sponsor adds a contractor
 else                                                 // beforeThis is not a valid node
  return(nullptr);                                    // return no success
}





/* @MRTZ_describe fellowFirst_cut

*/
template <class DataType, DataType defaultData> inline /*INLINE_2*/
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::fellowFirst_cut(Association<DataType, defaultData>* sponsor)
{
 if(sponsor != nullptr)                               // this is a contractor of an other node
  return(sponsor->contractorFirst_cut());             // sponsor cuts out a contractor
 else                                                 // beforeThis is not a valid node
  return(nullptr);                                    // return no success
}





/* @MRTZ_describe fellowFirst_cut

*/
template <class DataType, DataType defaultData> inline /*INLINE_2*/
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::fellowFirst_cut(AssociationVisitor<DataType, defaultData>* visitor,
                                                                                               Association<DataType, defaultData>*        sponsor)
{
 if(sponsor != nullptr)                                // this is a contractor of an other node
  return(sponsor->contractorFirst_cut(visitor));       // sponsor cuts out a contractor
 else                                                  // beforeThis is not a valid node
  return(nullptr);                                     // return no success
}





/* @MRTZ_describe fellowFirst_delete

*/
template <class DataType, DataType defaultData> inline /*INLINE_2*/
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::fellowFirst_delete(Association<DataType, defaultData>* sponsor)
{
 if(sponsor != nullptr)                                  // this is a contractor of an other node
  return(sponsor->contractorFirst_delete());             // sponsor deletes a contractor
 else                                                    // beforeThis is not a valid node
  return(nullptr);                                       // return no success
}





/* @MRTZ_describe fellowFirst_delete

*/
template <class DataType, DataType defaultData> inline /*INLINE_2*/
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::fellowFirst_delete(AssociationVisitor<DataType, defaultData>* visitor,
                                                                                                  Association<DataType, defaultData>*        sponsor)
{
 if(sponsor != nullptr)                                      // this is a contractor of an other node
  return(sponsor->contractorFirst_delete(visitor));          // sponsor deletes a contractor
 else                                                        // beforeThis is not a valid node
  return(nullptr);                                           // return no success
}




/* @MRTZ_describe fellowFirst_get

*/
template <class DataType, DataType defaultData> inline /*INLINE_2*/
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::fellowFirst_get(Association<DataType, defaultData>* sponsor)
{
 if(sponsor != nullptr)                               // this is a contractor of an other node
  return(sponsor->contractorFirst_get());             // sponsor returns a contractor
 else                                                 // beforeThis is not a valid node
  return(nullptr);                                    // return-value no success
}





/* @MRTZ_describe fellowFirst_get

*/
template <class DataType, DataType defaultData> inline /*INLINE_2*/
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::fellowFirst_get(AssociationVisitor<DataType, defaultData>* visitor,
                                                                                               Association<DataType, defaultData>*        sponsor)
{
 if(sponsor != nullptr)                                // this is a contractor of an other node
  return(sponsor->contractorFirst_get(visitor));       // sponsor returns a contractor
 else                                                  // beforeThis is not a valid node
  return(nullptr);                                     // return no success
}










/* @MRTZ_describe fellowLast_add

*/
template <class DataType, DataType defaultData> inline /*INLINE_2*/
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::fellowLast_add(Association<DataType, defaultData>* node,
                                                                                              Association<DataType, defaultData>* sponsor)
{
 if(sponsor != nullptr)                               // this is a contractor of an other node
  return(sponsor->contractorLast_add(node));          // sponsor adds a contractor
 else                                                 // beforeThis is not a valid node
  return(nullptr);                                    // return no success
}



/* @MRTZ_describe fellowLast_cut

*/
template <class DataType, DataType defaultData> inline /*INLINE_2*/
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::fellowLast_cut(Association<DataType, defaultData>* sponsor)
{
 if(sponsor != nullptr)                               // this is a contractor of an other node
  return(sponsor->contractorLast_cut());              // sponsor cuts out a contractor
 else                                                 // beforeThis is not a valid node
  return(nullptr);                                    // return no success
}



/* @MRTZ_describe fellowLast_cut

*/
template <class DataType, DataType defaultData> inline /*INLINE_2*/
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::fellowLast_cut(AssociationVisitor<DataType, defaultData>* visitor,
                                                                                              Association<DataType, defaultData>*        sponsor)
{
 if(sponsor != nullptr)                               // this is a contractor of an other node
  return(sponsor->contractorLast_cut(visitor));       // sponsor cuts out a contractor
 else                                                 // beforeThis is not a valid node
  return(nullptr);                                    // return no success
}



/* @MRTZ_describe fellowLast_delete

*/
template <class DataType, DataType defaultData> inline /*INLINE_2*/
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::fellowLast_delete(Association<DataType, defaultData>* sponsor)
{
 if(sponsor != nullptr)                                  // this is a contractor of an other node
  return(sponsor->contractorLast_delete());              // sponsor deletes a contractor
 else                                                    // beforeThis is not a valid node
  return(nullptr);                                       // return no success
}




/* @MRTZ_describe fellowLast_delete

*/
template <class DataType, DataType defaultData> inline /*INLINE_2*/
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::fellowLast_delete(AssociationVisitor<DataType, defaultData>* visitor,
                                                                                                 Association<DataType, defaultData>*        sponsor)
{
 if(sponsor != nullptr)                                     // this is a contractor of an other node
  return(sponsor->contractorLast_delete(visitor));          // sponsor deletes a contractor
 else                                                       // beforeThis is not a valid node
  return(nullptr);                                          // return no success

// return(ReturnValue);
}





/* @MRTZ_describe fellowLast_get

*/
template <class DataType, DataType defaultData> inline /*INLINE_2*/
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::fellowLast_get(Association<DataType, defaultData>* sponsor)
{
 if(sponsor != nullptr)                               // this is a contractor of an other node
  return(sponsor->contractorLast_get());              // sponsor returns a contractor
 else                                                 // beforeThis is not a valid node
  return(nullptr);                                    // return no success
}




/* @MRTZ_describe fellowLast_get

*/
template <class DataType, DataType defaultData> inline /*INLINE_2*/
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::fellowLast_get(AssociationVisitor<DataType, defaultData>* visitor,
                                                                                              Association<DataType, defaultData>*        sponsor)
{
 if(sponsor != nullptr)                               // this is a contractor of an other node
  return(sponsor->contractorLast_get(visitor));       // sponsor returns a contractor
 else                                                 // beforeThis is not a valid node
  return(nullptr);                                    // return no success
}










/* @MRTZ_describe addNode

*/
  template <class DataType, DataType defaultData>
  Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::addNode(Association<DataType, defaultData>* node,
                                                                                         Association<DataType, defaultData>* sponsor,
                                                                                         Association<DataType, defaultData>* behindThis,
                                                                                         Association<DataType, defaultData>* beforeThis)
{
 Association<DataType, defaultData>*        ReturnValue = nullptr;          // prepare a return of process failed
 AssociationSponsor* Sponsor     = nullptr;

 if(sponsor != nullptr)
  Sponsor      = sponsor->as_AssociationSponsor();

 if(Sponsor != nullptr)                                                     //sponsor is a valid node
 {

  if(beforeThis != nullptr)                                                 // next contractor defined but may be not a valid one
  {
   typename list<Association<DataType, defaultData>*>::iterator Contractor; // to iterate over Contractors

   Contractor = Sponsor->Att.Contractor.begin();                            // first contractor
   while(Contractor != Sponsor->Att.Contractor.end())                       // until last contractor
   {
    if((*Contractor == beforeThis))                                         // contractorNext found
    {
     Sponsor->Att.Contractor.insert(Contractor,node);                       // add node before contractorNext
     ReturnValue = node;                                                    // prepare return success
     break;
    }
    else
    {
     ++Contractor;                                                          // next contractor
    }
   }
  }
  else if(behindThis != nullptr)                                            // previous contractor defined but may be not a valid one
  {
   typename list<Association<DataType, defaultData>*>::iterator Contractor; // to iterate over Contractors

   Contractor = Sponsor->Att.Contractor.begin();                            // behind last contractor
 //  --Contractor;                                                          // last contractor
 //  do
   while(Contractor != Sponsor->Att.Contractor.end())                       // until last contractor
   {
    if((*Contractor == behindThis))                                         // contractorBefore found
    {
     ++Contractor;                                                          // prepare adding node

     if(Contractor != Sponsor->Att.Contractor.end())                        // if contractor is a valid element
      Sponsor->Att.Contractor.insert(Contractor,node);                      // add node after contractorBefore
     else                                                                   // end of contractor list reached
      Sponsor->Att.Contractor.push_back(node);                              // add node as new last element

     ReturnValue = node;                                                    // prepare return success
     break;
    }
    else
    {
     ++Contractor;                                                          // previous contractor
    }
   }
  }
  else                                                                      // no contractor defined
  {
   Sponsor->Att.Contractor.push_back(node);                                 // add at end
   ReturnValue = node;                                                      // prepare return success
  }

 }

 return(ReturnValue);                                                       // return result
}


/* @MRTZ_describe cutNode

*/
template <class DataType, DataType defaultData>
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::cutNode(Association<DataType, defaultData>* node)
{
 Association<DataType, defaultData>*                           ReturnValue = nullptr; // prepare a return of process failed
 typename  list<Association<DataType, defaultData>*>::iterator Contractor;            // to iterate over Contractors

 Contractor = Att.Contractor.begin();                                                 // first contractor
 while(Contractor != Att.Contractor.end())                                            // until last contractor
 {
  if((*Contractor == node))                                                           // contractorNext found
  {
   ReturnValue = *Contractor;                                                         // prepare return success
   Att.Contractor.erase(Contractor);                                                  // remove node as contractor
   break;
  }
  else
  {
   ++Contractor;                                                                      // next contractor
  }
 }


 return(ReturnValue);                                                                 // return result
}














/* @MRTZ_describe swapNodes

*/
template <class DataType, DataType defaultData>
bool AssociationSponsor<DataType, defaultData>::swapNodes(Association<DataType, defaultData>* node1,
                                                          Association<DataType, defaultData>* node2)
{
 bool                                             ReturnValue = false;              // prepare a return of process failed
 typename  list<Association<DataType, defaultData>*>::iterator Contractor;          // to iterate over Contractors
 typename  list<Association<DataType, defaultData>*>::iterator Contractor1 =  Att.Contractor.end();
                                                                                    // to store first iterator to swap
 typename  list<Association<DataType, defaultData>*>::iterator Contractor2 =  Att.Contractor.end();
                                                                                    // to store second iterator to swap

 Contractor = Att.Contractor.begin();                                               // first contractor
 while(Contractor != Att.Contractor.end())                                          // until last contractor
 {
  if((*Contractor == node1))                                                        // contractor of first node to swap found
  {
   Contractor1 = Contractor;                                                        // prepare return success
  }
  else if((*Contractor == node2))                                                   // contractor of second node to swap found
  {
   Contractor2 = Contractor;                                                        // prepare return success
  }
  else if(  (Contractor1 !=  Att.Contractor.end())
          &&(Contractor2 !=  Att.Contractor.end())
         )                                                                          // both nodes are found
  {
   ReturnValue = true;
   break;
  }
  else
  {
   ++Contractor;                                                                    // next contractor
  }
 }

 if(ReturnValue == true)                                                            // both nodes are found
 {
                                                                                    // exchange the nodes
  Att.Contractor.insert(Contractor1,*Contractor2);
  Att.Contractor.insert(Contractor2,*Contractor1);
  Att.Contractor.erase(Contractor1);
  Att.Contractor.erase(Contractor2);
 }

 return(ReturnValue);                                                               // return result
}


















/* @MRTZ_describe isAncestor

*/
template <class DataType, DataType defaultData>
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::isAncestor(Association<DataType, defaultData>* node,
                                                                                          Association<DataType, defaultData>* sponsor)
{
 Association<DataType, defaultData>* ReturnValue = nullptr;


  if(  (sponsor != nullptr)
     &&(sponsor != node)
    )
  {
   ReturnValue = this->isSponsor(sponsor);
   if (ReturnValue != nullptr)
    ReturnValue = sponsor->isSponsor(node);
   else
   { }
  }
  else
  {
   ReturnValue = this->isSponsor(node);
  }


 return(ReturnValue);
}



/* @MRTZ_describe isSponsor

*/
template <class DataType, DataType defaultData>
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::isSponsor(Association<DataType, defaultData>* node)
{
 if(  (node                     != nullptr)
    &&(node->isContractor(this) == this)
   )
  return(node);
 else
  return(nullptr);
}



/* @MRTZ_describe isContractor

*/
template <class DataType, DataType defaultData>
 Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::isContractor(Association<DataType, defaultData>* node)
{
 Association<DataType, defaultData>* ReturnValue = nullptr;
 typename  list<Association<DataType, defaultData>*>::iterator Contractor;         // to iterate over Contractors

 Contractor = Att.Contractor.begin();                                              // first contractor
 while(Contractor != Att.Contractor.end())                                         // until last contractor
 {
  if((*Contractor == node))                                                        // contractorNext found
  {
   ReturnValue = *Contractor;                                                      // prepare return success
   break;
  }
  else
  {
   ++Contractor;                                                                   // next contractor
  }
 }

 return(ReturnValue);
}



/* @MRTZ_describe isFellow

*/
template <class DataType, DataType defaultData>
Association<DataType, defaultData>* AssociationSponsor<DataType, defaultData>::isFellow(Association<DataType, defaultData>* node,
                                                                                        Association<DataType, defaultData>* sponsor)
{
 if(  (sponsor != nullptr)
    &&(node    != this)
    &&(sponsor != this)
   )
 {
  return(sponsor->isContractor(node));
 }
 else
  return(nullptr);
}










/* @MRTZ_describe welcome
  since a sponsor association is not knowing its own sponsor but only its
  contractors welcome method has to store in its history-stacks the visited sequence
  of associations while visiting downwards and he has to pop the left associations
  while visiting upwards.
*/
template <class DataType, DataType defaultData>
void AssociationSponsor<DataType, defaultData>::welcome(AssociationVisitor<DataType, defaultData>* visitor,
                                                        DirectionOfIteration                       direction,
                                                        Association<DataType, defaultData>*        sponsor)
{
 typename list<Association<DataType, defaultData>*>::iterator CurrentNode;
 typename list<Association<DataType, defaultData>*>::iterator BehindLast;
 typename list<Association<DataType, defaultData>*>::iterator BeforeFirst;
 AssociationSponsor* Sponsor = nullptr;

 list<typename list<Association<DataType, defaultData>*>::iterator> NodeHistory;
 list<AssociationSponsor*>                             SponsorHistory;


 visitor  -> direction_set(direction);                   // set the direction as defined by user

 if(sponsor != nullptr)
 {
  Sponsor     = sponsor->as_AssociationSponsor();
  BehindLast  = Sponsor->Att.Contractor.end();
  BeforeFirst = Sponsor->Att.Contractor.begin();
  -- BeforeFirst ;

  CurrentNode = Sponsor->Att.Contractor.begin();
  LOG_OUTPUT(LOG_OFF, "AssociationSponsor<DataType, defaultData>:: common prepare");
  while(  (CurrentNode    != BehindLast)
        &&((*CurrentNode) != this)
       )                                                 // pre-iteration until this node is reached
  {
   ++ CurrentNode;
  }
 }
 else if(direction == IterateDownwards)
 {
  LOG_OUTPUT(LOG_OFF, "AssociationSponsor<DataType, defaultData>:: prepare IterateDownwards");
  direction   = visitor->evaluate(this/*,sponsor*/);
  //first evaluation with this and not with CurrentNode as done otherwise since Sponsor of this is not known
  //the common evaluation will be in this case the second one

  SponsorHistory.push_front(Sponsor);                    // to prepare iterate upwards
  NodeHistory.push_front(CurrentNode);                   // to prepare iterate upwards

  Sponsor     = this->as_AssociationSponsor();           // this is next sponsor
  CurrentNode = Sponsor->Att.Contractor.begin();
  BehindLast  = Sponsor->Att.Contractor.end();
  BeforeFirst = Sponsor->Att.Contractor.begin();
  --BeforeFirst;

 }

 else if(direction == IterateDownwardsReverse)
 {
  LOG_OUTPUT(LOG_OFF, "AssociationSponsor<DataType, defaultData>:: prepare IterateDownwardsReverse");
  direction   = visitor->evaluate(this/*,sponsor*/);
  //first evaluation with this and not with CurrentNode as done otherwise since Sponsor of this is not known
  //the common evaluation will be in this case the second one

  SponsorHistory.push_front(Sponsor);                    // to prepare iterate upwards
  NodeHistory.push_front(CurrentNode);                   // to prepare iterate upwards

  Sponsor     = this->as_AssociationSponsor();           // this is next sponsor
  CurrentNode = Sponsor->Att.Contractor.end();
  -- CurrentNode;
  BehindLast  = Sponsor->Att.Contractor.end();
  BeforeFirst = Sponsor->Att.Contractor.begin();
  --BeforeFirst;

 }


 LOG_OUTPUT(LOG_OFF, "AssociationSponsor<DataType, defaultData>::welcome");


 if (Sponsor     == nullptr)
  {LOG_OUTPUT(LOG_ON, "AssociationSponsor<DataType, defaultData>::welcome current Sponsor is not valid");}
 if (direction   == IterateNoMore)
  {LOG_OUTPUT(LOG_ON, "AssociationSponsor<DataType, defaultData>::welcome current Direction is not valid");}
 if (CurrentNode == BehindLast)
  {LOG_OUTPUT(LOG_ON, "AssociationSponsor<DataType, defaultData>::welcome current node behind last");}
 if (CurrentNode == BeforeFirst)
  {LOG_OUTPUT(LOG_ON, "AssociationSponsor<DataType, defaultData>::welcome current node before first");}


 while(  (CurrentNode  != BehindLast)
       &&(CurrentNode  != BeforeFirst)
       &&(direction    != IterateNoMore)
       &&(Sponsor      != nullptr)
       )
 {
  LOG_OUTPUT(LOG_OFF, "AssociationSponsor<DataType, defaultData>::welcome call evaluate");
  direction = visitor->evaluate(*CurrentNode/*,Sponsor*/);
 if (direction == IterateNoMore)
  {LOG_OUTPUT(LOG_OFF, "AssociationSponsor<DataType, defaultData>::welcome node found");}

  switch(direction)
  {
   case IterateForwards:
   {
     LOG_OUTPUT(LOG_OFF, "IterateForwards");
      ++ CurrentNode;

   }break;

   case IterateBackwards:
   {
     LOG_OUTPUT(LOG_OFF, "IterateBackwards 1");
      --CurrentNode;
   }break;

   case IterateUpwards:
   {

     if     (!(  (NodeHistory   .empty())
               ||(SponsorHistory.empty())
              )
             )
     {
      LOG_OUTPUT(LOG_OFF, "IterateUpwards");
      CurrentNode = *(NodeHistory.begin());
      NodeHistory.pop_front();
      Sponsor     = *(SponsorHistory.begin());
      SponsorHistory.pop_front();
     }
     else if (Sponsor->isContractor(this))
     {
      visitor->evaluate(Sponsor/*,nullptr*/);
      CurrentNode = BehindLast;         // since the sponsor of the sponsor is not known
                                        // CurrentNode can not be redefined
      direction = IterateNoMore;        // stop iteration since it is not possible for sponsor-associations
     }
     else
     {
      CurrentNode = BehindLast;         // since the sponsor of the sponsor is not known
                                        // CurrentNode can not be redefined
      direction = IterateNoMore;        // stop iteration since it is not possible for sponsor-associations

     }

   }break;

   case IterateDownwards:
   {
     LOG_OUTPUT(LOG_OFF, "IterateDownwards");
     Sponsor     = (*CurrentNode)->as_AssociationSponsor();
     CurrentNode = Sponsor->Att.Contractor.begin();
     BehindLast  = Sponsor->Att.Contractor.end();
     BeforeFirst = Sponsor->Att.Contractor.begin();
     --BeforeFirst;
//    }
   }break;

   case IterateDownwardsReverse:
   {
     LOG_OUTPUT(LOG_OFF, "IterateDownwardsReverse");
     Sponsor     = (*CurrentNode)->as_AssociationSponsor();
     CurrentNode = Sponsor->Att.Contractor.end();
     -- CurrentNode;
     BehindLast  = Sponsor->Att.Contractor.end();
     BeforeFirst = Sponsor->Att.Contractor.begin();
     --BeforeFirst;
   }break;


   case IterateWithFound:
   case IterateAsBefore:
   case IterateNoMore:
   default:
   {
    LOG_OUTPUT(LOG_OFF, "Iteration finished");
    direction   = IterateNoMore; // fail-reaction
    CurrentNode = BehindLast;    // fail-reaction
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



#endif // ASSOCIATION_SPONSOR_HPP

