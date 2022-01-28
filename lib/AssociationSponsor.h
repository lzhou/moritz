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

#ifndef ASSOCIATION_SPONSOR_H
 #define ASSOCIATION_SPONSOR_H



#include<list>
#include <fstream>

//#include "Association.h"
#include "Association.hpp"

#include "ASS_Data.h"
//#include "ASS_Visitor.h"
#include "ASS_Visitor.hpp"




using namespace std;


#ifndef DOXYGEN
////namespace TXTDIASM {
//namespace ASSOCIATION {
#endif //DOXYGEN


//#define IGNORE_UNUSED __attribute__ ((unused))

/// @ingroup UNUSED_DATA
/// @brief avoid compiler warning since the object is not used
/// @{
#define ASSOCIATIONVISITOR_UNUSED __attribute__ ((unused))    AssociationVisitor<DataType, defaultData>
/// @}



//class AssociationFellowship;


template <class DataType, DataType defaultData> class AssociationSponsor:public Association<DataType, defaultData>
{

 friend class AssociationFellowship<DataType, defaultData>;

 public:

/*!
 @brief default constructor

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_AssociationSponsor.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    22.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 AssociationSponsor(void);

/*!
 @brief data defining constructor

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_AssociationSponsor.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    19.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 explicit AssociationSponsor(DataType data);



/*!
 @brief cast constructor that creates a copy of the given association

 while all contractor-dependencies will be transformed to this type
 the data connections will be copied

 @param [in] association original association-node to copy

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_AssociationSponsor.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    06.09.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 explicit AssociationSponsor(Association<DataType, defaultData>* association);




/*!
  @brief assignment operator

  @param [in] Association object to assign

*/
AssociationSponsor<DataType, defaultData>& operator= (Association<DataType, defaultData>& association);


/*!
 @brief destructor

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData__AssociationSponsor.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    22.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  virtual ~AssociationSponsor(void);


/*!
 cast this object to an object of the type AssociationSponsor


 @return a pointer to a AssociationVisited object if conversion is possible
 @return nullptr if object could not be converted


 <br><br>
 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_as_AssociationSponsor.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    22.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual AssociationSponsor<DataType, defaultData>* as_AssociationSponsor(void) override;




/*!
 @brief cast this object to an object of the type AssociationFellowship

 @return a pointer to a AssociationVisited object if conversion is possible
 @return nullptr if object could not be converted


 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_as_AssociationFellowship.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    22.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual AssociationFellowship<DataType, defaultData>* as_AssociationFellowship(void) override;







/*!
 @brief create a new association object of a concrete sponsor-association class,

 this method should ensure to get a new object from the same type as the called
 object even the called object is pointed by an abstract type pointer

 @note the new object will be created while runtime on the heap by using new
       and the user has to delete it manually.

 @return a pointer to a new association object if the called object itself is not
         an abstract one even the pointer has an abstract type.
 @return nullptr if the called object has the abstract type Association<DataType, defaultData>


 @htmlinclude ./des/AssociationSponsor_DataType_defaultData__newObject.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    12.11.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>* newObject(void) override;

 virtual Association<DataType, defaultData>* newObject(DataType data) override;

Association<DataType, defaultData>* newObject(Association<DataType, defaultData>* association);












/*!
 @brief return the sponsor node to realise a common interface

 @param  sponsor possible sponsor of this node

 @return sponsor association if known
 @return nullptr if known sponsor is not known

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_sponsor_get.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    22.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>* sponsor_get(Association<DataType, defaultData>* sponsor = nullptr) override;






/*!
 @brief add a new node before an already existing one

 @param beforeThis already existing contractor to add the new one before
 @param node       new contractor to add

 @return a tree node that represents the new contractor
         or nullptr if this was not possible for example since beforeThis was not a contractor

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_contractorBefore_add.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    22.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>*  contractorBefore_add(Association<DataType, defaultData>* beforeThis,
                                                                   Association<DataType, defaultData>* node) override;

 virtual Association<DataType, defaultData>*  contractorBefore_add(Association<DataType, defaultData>*        beforeThis,
                                                                   Association<DataType, defaultData>*        node,
                                                                   AssociationVisitor<DataType, defaultData>* visitor) override;






/*!
 @brief cut out the contractor-node before the given one

 @param beforeThis contractor after the node to cut

 @return a tree node that represents the cut contractor
         or nullptr if this was not possible for example since beforeThis was not a contractor

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_contractorBefore_cut.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    22.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>*  contractorBefore_cut(Association<DataType, defaultData>* beforeThis) override;

 virtual Association<DataType, defaultData>*  contractorBefore_cut(Association<DataType, defaultData>*        beforeThis,
                                                                   AssociationVisitor<DataType, defaultData>* visitor) override;





/*!
 @brief delete the contractor-node before the given one inclusive its contractors and all data of this sub-tree

 @param beforeThis contractor after the node to delete

 @return nullptr if deleting was possible
         or a node if this was not possible for example since beforeThis was not a contractor

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_contractorBefore_delete.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    22.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>*  contractorBefore_delete(Association<DataType, defaultData>* beforeThis) override;


 virtual Association<DataType, defaultData>*  contractorBefore_delete(Association<DataType, defaultData>*        beforeThis,
                                                                      AssociationVisitor<DataType, defaultData>* visitor) override;


/*!
 @brief return the contractor node before the given one

 @param beforeThis contractor after the node to delete

 @return a tree node that represents the contractor
         or nullptr if the given node is not a contractor
         or nullptr if there are no contractors

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_contractorBefore_get.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    22.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>*  contractorBefore_get(Association<DataType, defaultData>* beforeThis) override;


/*!
 @brief return a contractor node somewhere before the given one defined by the given visitor

 @param beforeThis contractor after the node to delete
 @param visitor   a concrete association-visitor that is used to search for the node

 @return a tree node that represents the contractor
         or nullptr if the given node is not a contractor
         or nullptr if the given visitor finds no specified contractor
         or nullptr if there are no contractors

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_contractorBefore_get.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    22.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>*  contractorBefore_get(Association<DataType, defaultData>*        beforeThis,
                                                                   AssociationVisitor<DataType, defaultData>* visitor) override;




/*!
 @brief add a new node behind an already existing one

 @param behindThis already existing contractor to add the new one behind
 @param node       new contractor to add

 @return a tree node that represents the new contractor
         or nullptr if this was not possible

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_contractorBehind_add.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    22.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>*  contractorBehind_add(Association<DataType, defaultData>* behindThis,
                                                                   Association<DataType, defaultData>* node) override;

 virtual Association<DataType, defaultData>*  contractorBehind_add(Association<DataType, defaultData>* behindThis,
                                                                   Association<DataType, defaultData>* node,
                                                                   AssociationVisitor<DataType, defaultData>* visitor) override;





/*!
 @brief cut out the contractor-node behind the given one

 @param behindThis contractor before the node to cut

 @return a tree node that represents the cut contractor
         or nullptr if this was not possible for example since beforeThis was not a contractor

 @return a tree node that represents the  or nullptr if this is the tree-node

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_contractorBehind_cut.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    22.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>*  contractorBehind_cut(Association<DataType, defaultData>*        behindThis) override;

 virtual Association<DataType, defaultData>*  contractorBehind_cut(Association<DataType, defaultData>*        behindThis,
                                                                   AssociationVisitor<DataType, defaultData>* visitor) override;







/*!
 @brief delete the contractor-node behind the given one inclusive its contractors and all data of this sub-tree

 @param behindThis contractor after the node to delete

 @return nullptr if deleting was possible
         or a node if this was not possible for example since behindThis was not a contractor

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_contractorBehind_delete.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    22.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>*  contractorBehind_delete(Association<DataType, defaultData>* behindThis) override;

 virtual Association<DataType, defaultData>*  contractorBehind_delete(Association<DataType, defaultData>*        behindThis,
                                                                      AssociationVisitor<DataType, defaultData>* visitor) override;


/*!
 @brief return the contractor node after the given one

 @param behindThis contractor after the node to get

 @return a tree node that represents the contractor
         or nullptr if the given node is not a contractor
         or nullptr if there are no contractors

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_Sponsor_Get.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    22.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>*  contractorBehind_get(Association<DataType, defaultData>* behindThis) override;


/*!
 @brief return a contractor node somewhere after the given one defined by the given visitor

 @param behindThis contractor after the node to get
 @param visitor a concrete association-visitor that is used to search for the node

 @return a tree node that represents the contractor
         or nullptr if the given node is not a contractor
         or nullptr if the given visitor finds no specified contractor
         or nullptr if there are no contractors

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_contractorBehind_get.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    22.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementationTDA_Tree* behindThis,
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>*  contractorBehind_get(Association<DataType, defaultData>*        behindThis,
                                                                   AssociationVisitor<DataType, defaultData>* visitor) override;





/*!
 @brief add a new node as the first contractor

 @param node       new contractor to add

 @return a tree node that represents the new contractor
         or nullptr if this was not possible

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_contractorFirst_add.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    22.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>*  contractorFirst_add(Association<DataType, defaultData>* node) override;





/*!
 @brief cut out the first contractor-node

 @return a tree node that represents the cut contractor
         or nullptr if this was not possible

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_contractorFirst_cut.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    22.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>*  contractorFirst_cut(void) override;

 virtual Association<DataType, defaultData>*  contractorFirst_cut(AssociationVisitor<DataType, defaultData>* visitor) override;




/*!
 @brief delete the first contractor-node inclusive its contractors and all data of this sub-tree

 @return nullptr if deleting was possible
         or a node if this was not possible

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_contractorFirst_delete.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    22.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>*  contractorFirst_delete(void) override;

 virtual Association<DataType, defaultData>*  contractorFirst_delete(AssociationVisitor<DataType, defaultData>* visitor) override;




 /*!
 @brief return the the first contractor-node in a chain of contractors

 @return a tree node that represents the contractor
         or nullptr if this node has no contractors

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_contractorFirst_get.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    22.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>*  contractorFirst_get(void) override;



/*!
 @brief return the first contractor defined by the given visitor

 @param visitor a concrete association-visitor that is used to search for the node

 @return a tree node that represents the contractor
         or nullptr if the given visitor finds no specified contractor
         or nullptr if there are no contractors

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_contractorFirst_get.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    22.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>*  contractorFirst_get(AssociationVisitor<DataType, defaultData>* visitor) override;







/*!
 @brief add a new node as the last contractor

 @param node       new contractor to add

 @return a tree node that represents the new contractor
         or nullptr if this was not possible


 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_contractorLast_add.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    22.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>*  contractorLast_add(Association<DataType, defaultData>* node) override;





/*!
 @brief cut out the last contractor-node

 @return a tree node that represents the cut contractor
         or nullptr if this was not possible

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_contractorLast_cut.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    22.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>*  contractorLast_cut(void) override;

 virtual Association<DataType, defaultData>*  contractorLast_cut(AssociationVisitor<DataType, defaultData>* visitor) override;






/*!
 @brief delete the last contractor-node inclusive its contractors and all data of this sub-tree

 @return nullptr if deleting was possible
         or a node if this was not possible

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_contractorLast_delete.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    22.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>*  contractorLast_delete(void) override;

 virtual Association<DataType, defaultData>*  contractorLast_delete(AssociationVisitor<DataType, defaultData>* visitor) override;


/*!
 @brief return the the last contractor-node in a chain of contractors


 @return a tree node that represents the contractor
         or nullptr if this node has no contractors

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_contractorLast_get.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    22.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>*  contractorLast_get(void) override;



/*!
 @brief return the last contractor defined by the given visitor

 @param visitor a concrete association-visitor that is used to search for the node

 @return a tree node that represents the contractor
         or nullptr if the given visitor finds no specified contractor
         or nullptr if there are no contractors

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_contractorLast_get.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    22.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>*  contractorLast_get(AssociationVisitor<DataType, defaultData>* visitor) override;









/*!
 @brief add a new node as a previous fellow

 @param node       new fellow to add
 @param sponsor    node that manages the chain of contractors
                   in that the new fellow should be inserted

 @return a tree node that represents the new contractor
         or nullptr if this was not possible

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_fellowBefore_add.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    29.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>*  fellowBefore_add(Association<DataType, defaultData>* node,
                                                               Association<DataType, defaultData>* sponsor) override;





/*!
 @brief add a new node as a previous fellow

 @param node       new fellow to add
 @param sponsor    node that manages the chain of contractors
                   in that the new fellow should be inserted
 @param visitor    a concrete association-visitor that is used to search for the node

 @return a tree node that represents the new contractor
         or nullptr if this was not possible

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_fellowBefore_add.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    29.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>*  fellowBefore_add(Association<DataType, defaultData>*        node,
                                                               AssociationVisitor<DataType, defaultData>* visitor,
                                                               Association<DataType, defaultData>*        sponsor) override;





/*!
 @brief cut out the fellow-node before this one

 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be cut out


 @return a tree node that represents the cut contractor
         or nullptr if this was not possible

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_fellowBefore_cut.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    29.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>*  fellowBefore_cut(Association<DataType, defaultData>* sponsor) override;





/*!
 @brief cut out the fellow-node before this one

 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be cut out
 @param visitor    a concrete association-visitor that is used to search for the node



 @return a tree node that represents the cut contractor
         or nullptr if this was not possible

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_fellowBefore_cut.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    29.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>*  fellowBefore_cut(AssociationVisitor<DataType, defaultData>* visitor,
                                                               Association<DataType, defaultData>*        sponsor) override;





/*!
 @brief delete the fellow-node before this one inclusive its contractors and all data of this sub-tree

 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be deleted

 @return nullptr if deleting was possible
         or a node if this was not possible

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_fellowBefore_delete.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    29.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>*  fellowBefore_delete(Association<DataType, defaultData>* sponsor) override;







/*!
 @brief delete the fellow-node before this one inclusive its contractors and all data of this sub-tree

 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be deleted
 @param visitor    a concrete association-visitor that is used to search for the node


 @return nullptr if deleting was possible
         or a node if this was not possible

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_fellowBefore_delete.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    29.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>*  fellowBefore_delete(AssociationVisitor<DataType, defaultData>* visitor,
                                                                  Association<DataType, defaultData>*        sponsor) override;




/*!
 @brief return the fellow-node after in a chain of contractors

 @param sponsor    node that manages the chain of contractors
                   from that the  fellow should be returned

 @return a tree node that represents the fellow
         or nullptr if this is the last node in the chain

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_fellowBefore_get.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    29.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>*  fellowBefore_get(Association<DataType, defaultData>* sponsor) override;




/*!
 @brief return the fellow-node after in a chain of contractors

 @param sponsor    node that manages the chain of contractors
                   from that the  fellow should be returned
 @param visitor    a concrete association-visitor that is used to search for the node


 @return a tree node that represents the fellow
         or nullptr if this is the last node in the chain

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_fellowBefore_get.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    29.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>*  fellowBefore_get(AssociationVisitor<DataType, defaultData>* visitor,
                                                               Association<DataType, defaultData>*        sponsor) override;






/*!
 @brief add a new node as a next fellow

 @param node       new contractor to add
 @param sponsor    node that manages the chain of contractors
                   in that the new fellow should be inserted

 @return a tree node that represents the new contractor
         or nullptr if this was not possible

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_fellowBehind_add.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    29.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>*  fellowBehind_add(Association<DataType, defaultData>* node,
                                                               Association<DataType, defaultData>* sponsor) override;







/*!
 @brief add a new node as a next fellow

 @param node       new contractor to add
 @param sponsor    node that manages the chain of contractors
                   in that the new fellow should be inserted
 @param visitor    a concrete association-visitor that is used to search for the node

 @return a tree node that represents the new contractor
         or nullptr if this was not possible

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_fellowBehind_add.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    29.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>*  fellowBehind_add(Association<DataType, defaultData>* node,
                                                               ASSOCIATIONVISITOR_UNUSED*          visitor,
                                                               Association<DataType, defaultData>* sponsor) override;





/*!
 @brief cut out the fellow-node behind this one

 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be cut out

 @return a tree node that represents the cut contractor
         or nullptr if this was not possible

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_fellowBehind_cut.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    29.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>*  fellowBehind_cut(Association<DataType, defaultData>* sponsor) override;





/*!
 @brief cut out the fellow-node behind this one

 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be cut out
 @param visitor    a concrete association-visitor that is used to search for the node

 @return a tree node that represents the cut contractor
         or nullptr if this was not possible

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_fellowBehind_cut.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    29.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>*  fellowBehind_cut(AssociationVisitor<DataType, defaultData>* visitor,
                                                               Association<DataType, defaultData>*        sponsor) override;





/*!
 @brief delete the fellow-node behind this one inclusive its contractors and all data of this sub-tree

 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be deleted

 @return nullptr if deleting was possible
         or a node if this was not possible

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_fellowBehind_delete.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    29.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>*  fellowBehind_delete(Association<DataType, defaultData>* sponsor) override;





/*!
 @brief delete the fellow-node behind this one inclusive its contractors and all data of this sub-tree

 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be deleted
 @param visitor    a concrete association-visitor that is used to search for the node



 @return nullptr if deleting was possible
         or a node if this was not possible

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_fellowBehind_delete.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    29.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>*  fellowBehind_delete(AssociationVisitor<DataType, defaultData>* visitor,
                                                                  Association<DataType, defaultData>*        sponsor) override;


/*!
 @brief return the fellow-node before in a chain of contractors

 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be returned


 @return a tree node that represents the fellow
         or nullptr if this is the first node in the chain

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_fellowBehind_get.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    29.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>*  fellowBehind_get(Association<DataType, defaultData>* sponsor) override;


/*!
 @brief return the fellow-node before in a chain of contractors

 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be returned
 @param visitor    a concrete association-visitor that is used to search for the node

 @return a tree node that represents the fellow
         or nullptr if this is the first node in the chain

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_fellowBehind_get.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    29.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>*  fellowBehind_get(AssociationVisitor<DataType, defaultData>* visitor,
                                                               Association<DataType, defaultData>*        sponsor) override;






/*!
 @brief add a new node as a first fellow

 @param node       new contractor to add
 @param sponsor    node that manages the chain of contractors
                   in that the new fellow should be inserted


 @return a tree node that represents the new contractor
         or nullptr if this was not possible

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_fellowFirst_add.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    29.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>*  fellowFirst_add(Association<DataType, defaultData>* node,
                                                              Association<DataType, defaultData>* sponsor) override;





/*!
 @brief cut out the first fellow-node

 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be cut out

 @return a tree node that represents the cut contractor
         or nullptr if this was not possible

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_fellowFirst_cut.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    29.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>*  fellowFirst_cut(Association<DataType, defaultData>* sponsor) override;





/*!
 @brief cut out the first fellow-node

 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be cut out
 @param visitor    a concrete association-visitor that is used to search for the node

 @return a tree node that represents the cut contractor
         or nullptr if this was not possible

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_fellowFirst_cut.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    29.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>*  fellowFirst_cut(AssociationVisitor<DataType, defaultData>* visitor,
                                                              Association<DataType, defaultData>*        sponsor) override;





/*!
 @brief delete the first fellow-node inclusive its contractors and all data of this sub-tree

 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be deleted

 @return nullptr if deleting was possible
         or a node if this was not possible

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_fellowFirst_delete.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    29.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>*  fellowFirst_delete(Association<DataType, defaultData>* sponsor) override;




/*!
 @brief delete the first fellow-node inclusive its contractors and all data of this sub-tree

 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be deleted
 @param visitor    a concrete association-visitor that is used to search for the node



 @return nullptr if deleting was possible
         or a node if this was not possible

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_fellowFirst_delete.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    29.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>*  fellowFirst_delete(AssociationVisitor<DataType, defaultData>* visitor,
                                                                 Association<DataType, defaultData>*        sponsor) override;


/*!
 @brief return the first fellow-node in a chain of contractors

 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be returned

 @return a tree node that represents the contractor
         or nullptr if there are no fellows

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_fellowFirst_get.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    29.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>*  fellowFirst_get(Association<DataType, defaultData>* sponsor) override;



/*!
 @brief return the first fellow-node in a chain of contractors

 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be returned
 @param visitor    a concrete association-visitor that is used to search for the node


 @return a tree node that represents the contractor
         or nullptr if there are no fellows

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_fellowFirst_get.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    29.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>*  fellowFirst_get(AssociationVisitor<DataType, defaultData>* visitor,
                                                              Association<DataType, defaultData>*        sponsor) override;





/*!
 @brief add a new node as a last fellow

 @param node       new contractor to add
 @param sponsor    node that manages the chain of contractors
                   in that the new fellow should be inserted

 @return a tree node that represents the new contractor
         or nullptr if this was not possible

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_fellowLast_add.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    29.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>*  fellowLast_add(Association<DataType, defaultData>* node,
                                                             Association<DataType, defaultData>* sponsor) override;





/*!
 @brief cut out the last fellow-node

 @param sponsor    node that manages the chain of contractors
                   from that the new fellow should be cut out

 @return a tree node that represents the cut contractor
         or nullptr if this was not possible

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_fellowLast_cut.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    29.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>*  fellowLast_cut(Association<DataType, defaultData>* sponsor) override;





/*!
 @brief cut out the last fellow-node

 @param sponsor    node that manages the chain of contractors
                   from that the new fellow should be cut out
 @param visitor    a concrete association-visitor that is used to search for the node

 @return a tree node that represents the cut contractor
         or nullptr if this was not possible

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_fellowLast_cut.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    29.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>*  fellowLast_cut(AssociationVisitor<DataType, defaultData>* visitor,
                                                             Association<DataType, defaultData>*        sponsor) override;





/*!
 @brief delete the last fellow-node inclusive its contractors and all data of this sub-tree

 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be deleted


 @return nullptr if deleting was possible
         or a node if this was not possible

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_fellowLast_delete.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    29.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>*  fellowLast_delete(Association<DataType, defaultData>* sponsor) override;





/*!
 @brief delete the last fellow-node inclusive its contractors and all data of this sub-tree

 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be deleted
 @param visitor    a concrete association-visitor that is used to search for the node



 @return nullptr if deleting was possible
         or a node if this was not possible

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_fellowLast_delete.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    29.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>*  fellowLast_delete(AssociationVisitor<DataType, defaultData>* visitor,
                                                                Association<DataType, defaultData>*        sponsor) override;


/*!
 @brief return the last fellow-node in a chain of contractors

 @param sponsor    node that manages the chain of contractors
                   from that the new fellow should be returned


 @return a tree node that represents the contractor
         or nullptr if there are no fellows

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_fellowLast_get.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    29.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>*  fellowLast_get(Association<DataType, defaultData>* sponsor) override;

/*!
 @brief return the last fellow-node in a chain of contractors

 @param sponsor    node that manages the chain of contractors
                   from that the new fellow should be returned
 @param visitor    a concrete association-visitor that is used to search for the node


 @return a tree node that represents the contractor
         or nullptr if there are no fellows

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_fellowLast_get.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    29.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>*  fellowLast_get(AssociationVisitor<DataType, defaultData>* visitor,
                                                             Association<DataType, defaultData>*        sponsor) override;






/*!
 @brief checks if the given node tree node object is an ancestor

 @param node       the node-object to test
 @param sponsor    node that manages the chain of contractors
                   from that the new fellow should be returned

 @return a tree node that represents an ancestor
      or nullptr the given tree-node is not an ancestor

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_isAncestor.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    29.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>* isAncestor(Association<DataType, defaultData>* node,
                                                        Association<DataType, defaultData>* sponsor) override;



/*!
 @brief checks if the given node tree node object is the sponsor

 @param node the node-object to test

 @return a tree node that represents the sponsor
      or nullptr the given tree-node is not the sponsor


 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_isSponsor.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    22.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>* isSponsor(Association<DataType, defaultData>* node) override;



/*!
 @brief checks if the given node tree node object is a contractor

 @param node the node-object to test

 @return a tree node that represents a contractor
      or nullptr the given tree-node is not a contractor

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_isContractor.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    22.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>* isContractor(Association<DataType, defaultData>* node) override;



/*!
 @brief checks if the given node tree node object is a fellow

 @param node the node-object to test
 @param sponsor    node that manages the chain of contractors
                   where the asking contractor is managed

 @return a tree node that represents a fellow
      or nullptr the given tree-node is not a fellow

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_isFellow.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    29.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>* isFellow(Association<DataType, defaultData>* node,
                                                      Association<DataType, defaultData>* sponsor) override;




/*
 /// parameter type for methods which iterate over fellows
 typedef enum DirectionOfIteration
 {
  IterateForwards,         ///< forwards    in the direction to the last fellow
  IterateBackwards,        ///< backwards   in the direction to the first fellow
  IterateUpwards,          ///< upwards     in the direction to the first ancestor
  IterateDownwards,        ///< downwards   in the direction to the first contractor
  IterateDownwardsReverse, ///< downwards   in the direction to the last contractor
 }DirectionOfIteration;
*/

/*!
 @brief checks if the given node tree node object is a fellow

 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_isFellow.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    29.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual void welcome(AssociationVisitor<DataType, defaultData>*  visitor,
                      DirectionOfIteration                        direction,
                      Association<DataType, defaultData>*         sponsor = nullptr) override;









/*!
 @brief exchange 2 given tree-nodes with their potential sub-nodes


 @param [in] node1   first node to exchange
 @param [in] node2   second node to exchange

 @return true if swapping was successfully done
 <br>    nullptr if swapping was not possible

 <br><br>
 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_swapNodes.html
 @I_______________________________________________________
    19.09.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual inline bool swapNodes(Association<DataType, defaultData>* node1,
                               Association<DataType, defaultData>* node2) override;












 protected:

/*!
 @brief insert a given tree-node with its potential sub-nodes as sub-tree on a specified location


 @param [in] node        node to insert
 @param [in] sponsor     node to use as sponsor for given node
 @param [in] beforeThis  node to use as fellow before the given node in a chain of fellows
 @param [in] behindThis  node to use as fellow after the given node in a chain of fellows

 @return reference to the inserted node if insertion was successfully done
 <br>    nullptr if insertion was not possible

 <br><br>
 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_addNode.html
 @I_______________________________________________________
    22.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/

  static inline Association<DataType, defaultData>* addNode(Association<DataType, defaultData>* node,
                                                            Association<DataType, defaultData>* sponsor,
                                                            Association<DataType, defaultData>* behindThis,
                                                            Association<DataType, defaultData>* beforeThis);


 /*!
 cut a given tree-node with its potential sub-nodes as sub-tree from a specified location


 @param [in] node            node to cut

 @return reference to the inserted node if insertion was successfully done
 <br>    nullptr if insertion was not possible

 <br><br>
 @htmlinclude ./des/AssociationSponsor_DataType_defaultData_cutNode.html
 @I_______________________________________________________
    22.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/

 virtual  inline Association<DataType, defaultData>* cutNode(Association<DataType, defaultData>* node) override;







 /*!
  @brief Attributes of class
 */
  struct Att
  {
   list<Association<DataType, defaultData>*> Contractor{}; ///< @brief contractor-nodes of this sponsor node
   Att(void):Contractor(){}
  }Att;





 private:




};



#ifndef DOXYGEN
#define USING_NAMESPACE using namespace
//}; USING_NAMESPACE ASSOCIATION;
//}; USING_NAMESPACE TXTDIASM;
#undef  USING_NAMESPACE
#endif //DOXYGEN

#endif //ASSOCIATION_SPONSOR_H

