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

#ifndef ASSOCIATION_FELLOWSHIP_H
 #define ASSOCIATION_FELLOWSHIP_H



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
#define ASSOCIATION_UNUSED __attribute__ ((unused)) Association<DataType, defaultData>
/// @}




template <class DataType, DataType defaultData> class AssociationFellowship:public Association<DataType, defaultData>
{

 friend class AssociationSponsor<DataType, defaultData>;

 public:

/*!
 @brief default constructor

 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_AssociationFellowship.html
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
 AssociationFellowship(void);


/*!
 @brief data defining constructor
 <br><br>
 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_AssociationFellowship.html
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
 explicit AssociationFellowship(DataType data);



/*!
 @brief cast constructor that creates a copy of the given association

 while all contractor-dependencies will be transformed to this type
 the data connections will be copied

 @param [in] association original association-node to copy


 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_AssociationFellowship.html
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
 explicit AssociationFellowship(Association<DataType, defaultData>* association);



/*!
 @brief cast constructor that creates a copy of the given association

 while all contractor-dependencies will be transformed to this type
 the data connections will be copied

 @param [in] association original association-node to copy


 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_AssociationFellowship.html
*/
 explicit AssociationFellowship(AssociationFellowship<DataType, defaultData>& association);




/*!
 @brief destructor
 <br><br>
 @htmlinclude ./des/AssociationFellowship_DataType_defaultData__AssociationFellowship.html
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
  virtual ~AssociationFellowship(void);








/*!
  @brief assignment operator

  @param [in] Association object to assign

*/
AssociationFellowship<DataType, defaultData>& operator= (Association<DataType, defaultData>* association);



/*!
  @brief assignment operator

  @param [in] Association object to assign

*/
AssociationFellowship<DataType, defaultData>& operator= (AssociationFellowship<DataType, defaultData>& association);


/*!
 @brief cast this object to an object of the type AssociationSponsor


 @return a pointer to a real existing object if conversion is possible
 @return nullptr if object could not be converted


 <br><br>
 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_as_AssociationSponsor.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    22.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
 virtual AssociationSponsor<DataType, defaultData>* as_AssociationSponsor(void) override;
*/




/*!
 @brief cast this object to an object of the type AssociationFellowship


 @return a pointer to a real existing object if conversion is possible
 @return nullptr if object could not be converted


 <br><br>
 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_as_AssociationFellowship.html
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
 @brief create a new association object of a fellowship-association class,

 this method should ensure to get a new object from the same type as the called
 object even the called object is pointed by an abstract type pointer

 @note the new object will be created while runtime on the heap by using new
       and the user has to delete it manually.

 @return a pointer to a new association object if the called object itself is not
         an abstract one even the pointer has an abstract type.
 @return nullptr if the called object has the abstract type Association<DataType, defaultData>


 <br><br>
 @htmlinclude "Association_newObject.html
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
 @brief return the sponsor node

 @param sponsor this parameter will be ignored and
                is only defined for compatibility with the base-class

 @return a association node that represents the sponsor or nullptr if sponsor is not know

 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_sponsor_get.html
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

 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_contractorBefore_add.html
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

 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_contractorBefore_cut.html
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

 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_contractorBefore_delete.html
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

 @param beforeThis contractor after the node to get

 @return a tree node that represents the contractor
         or nullptr if the given node is not a contractor
         or nullptr if there are no contractors

 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_contractorBefore_get.html
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

 @param beforeThis contractor after the node to get
 @param visitor    a concrete association-visitor that is used to search for the node

 @return a tree node that represents the contractor
         or nullptr if the given node is not a contractor
         or nullptr if the given visitor finds no specified contractor
         or nullptr if there are no contractors

 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_contractorBefore_get.html
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

 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_contractorBehind_add.html
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

 virtual Association<DataType, defaultData>*  contractorBehind_add(Association<DataType, defaultData>*        behindThis,
                                                                   Association<DataType, defaultData>*        node,
                                                                   AssociationVisitor<DataType, defaultData>* visitor) override;





/*!
 @brief cut out the contractor-node behind the given one

 @param behindThis contractor before the node to cut

 @return a tree node that represents the cut contractor
         or nullptr if this was not possible for example since beforeThis was not a contractor

 @return a tree node that represents the  or nullptr if this is the tree-node

 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_contractorBehind_cut.html
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
 virtual Association<DataType, defaultData>*  contractorBehind_cut(Association<DataType, defaultData>* behindThis) override;

 virtual Association<DataType, defaultData>*  contractorBehind_cut(Association<DataType, defaultData>* behindThis,
                                                                   AssociationVisitor<DataType, defaultData>* visitor) override;







/*!
 @brief delete the contractor-node behind the given one inclusive its contractors and all data of this sub-tree

 @param behindThis contractor after the node to delete

 @return nullptr if deleting was possible
         or a node if this was not possible for example since behindThis was not a contractor

 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_contractorBehind_delete.html
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

 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_Sponsor_Get.html
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

 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_contractorBehind_get.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    22.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementationAssociation<DataType, defaultData>* behindThis,
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

 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_contractorFirst_add.html
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

 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_contractorFirst_cut.html
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

 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_contractorFirst_delete.html
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

 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_contractorFirst_get.html
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

 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_contractorFirst_get.html
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


 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_contractorLast_add.html
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

 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_contractorLast_cut.html
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

 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_contractorLast_delete.html
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

 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_contractorLast_get.html
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

 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_contractorLast_get.html
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

 @param node       new contractor to add
 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be returned

 @return a tree node that represents the new contractor
         or nullptr if this was not possible

 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_fellowBefore_add.html
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
 virtual Association<DataType, defaultData>*  fellowBefore_add(Association<DataType, defaultData>* node,
                                                               ASSOCIATION_UNUSED*                 sponsor = nullptr) override;

 virtual Association<DataType, defaultData>*  fellowBefore_add(Association<DataType, defaultData>*        node,
                                                               AssociationVisitor<DataType, defaultData>* visitor,
                                                               ASSOCIATION_UNUSED*                        sponsor = nullptr) override;




/*!
 @brief cut out the fellow-node before this one

 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be returned

 @return a tree node that represents the cut contractor
         or nullptr if this was not possible

 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_fellowBefore_cut.html
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
 virtual Association<DataType, defaultData>*  fellowBefore_cut(ASSOCIATION_UNUSED* sponsor = nullptr) override;

 virtual Association<DataType, defaultData>*  fellowBefore_cut(AssociationVisitor<DataType, defaultData>* visitor,
                                                               ASSOCIATION_UNUSED*                        sponsor = nullptr) override;








/*!
 @brief delete the fellow-node before this one inclusive its contractors and all data of this sub-tree

 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be returned

 @return nullptr if deleting was possible
         or a node if this was not possible

 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_fellowBefore_delete.html
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
 virtual Association<DataType, defaultData>*  fellowBefore_delete(ASSOCIATION_UNUSED* sponsor = nullptr) override;

 virtual Association<DataType, defaultData>*  fellowBefore_delete(AssociationVisitor<DataType, defaultData>* visitor,
                                                                  ASSOCIATION_UNUSED*                        sponsor = nullptr) override;

 /*!
 @brief return the fellow-node after in a chain of contractors

 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be returned


 @return a tree node that represents the fellow
         or nullptr if this is the last node in the chain

 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_fellowBefore_get.html
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
 virtual Association<DataType, defaultData>*  fellowBefore_get(ASSOCIATION_UNUSED* sponsor = nullptr) override;


/*!
 @brief return the fellow-node before in a chain of contractors defined by the given visitor

 <br><br>

 @param visitor a concrete association-visitor that is used to search for the node
 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be returned

 @return a tree node that represents the contractor
         or nullptr if the given visitor finds no specified contractor
         or nullptr if there are no fellows

 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_fellowBefore_get.html
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
 virtual Association<DataType, defaultData>*  fellowBefore_get(AssociationVisitor<DataType, defaultData>* visitor,
                                                               ASSOCIATION_UNUSED*                        sponsor = nullptr) override;





/*!
 @brief add a new node as a next fellow

 @param node       new contractor to add
 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be returned

 @return a tree node that represents the new contractor
         or nullptr if this was not possible

 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_fellowBehind_add.html
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
 virtual Association<DataType, defaultData>*  fellowBehind_add(Association<DataType, defaultData>* node,
                                                               ASSOCIATION_UNUSED*                 sponsor = nullptr) override;

 virtual Association<DataType, defaultData>*  fellowBehind_add(Association<DataType, defaultData>*        node,
                                                               AssociationVisitor<DataType, defaultData>* visitor,
                                                               ASSOCIATION_UNUSED*                        sponsor = nullptr) override;






/*!
 @brief cut out the fellow-node behind this one

 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be returned

 @return a tree node that represents the cut contractor
         or nullptr if this was not possible

 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_fellowBehind_cut.html
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
 virtual Association<DataType, defaultData>*  fellowBehind_cut(ASSOCIATION_UNUSED* sponsor = nullptr) override;

 virtual Association<DataType, defaultData>*  fellowBehind_cut(AssociationVisitor<DataType, defaultData>* visitor,
                                                               ASSOCIATION_UNUSED*                        sponsor = nullptr) override;






/*!
 @brief delete the fellow-node behind this one inclusive its contractors and all data of this sub-tree

 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be returned

 @return nullptr if deleting was possible
         or a node if this was not possible

 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_fellowBehind_delete.html
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
 virtual Association<DataType, defaultData>*  fellowBehind_delete(ASSOCIATION_UNUSED* sponsor = nullptr) override;

 virtual Association<DataType, defaultData>*  fellowBehind_delete(AssociationVisitor<DataType, defaultData>* visitor,
                                                                  ASSOCIATION_UNUSED*                        sponsor = nullptr) override;



 /*!
 @brief return the fellow-node before in a chain of contractors

 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be returned


 @return a tree node that represents the fellow
         or nullptr if this is the first node in the chain

 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_fellowBehind_get.html
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
 virtual Association<DataType, defaultData>*  fellowBehind_get(ASSOCIATION_UNUSED* sponsor = nullptr) override;

/*!
 @brief return the fellow-node after in a chain of contractors defined by the given visitor


 @param visitor    a concrete association-visitor that is used to search for the node
 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be returned

 @return a tree node that represents the contractor
         or nullptr if the given visitor finds no specified contractor
         or nullptr if there are no fellows

 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_fellowBehind_get.html
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
 virtual Association<DataType, defaultData>*  fellowBehind_get(AssociationVisitor<DataType, defaultData>* visitor,
                                                               ASSOCIATION_UNUSED*                        sponsor = nullptr) override;





/*!
 @brief add a new node as a first fellow

 @param node       new contractor to add
 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be returned

 @return a tree node that represents the new contractor
         or nullptr if this was not possible

 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_fellowFirst_add.html
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
 virtual Association<DataType, defaultData>*  fellowFirst_add(Association<DataType, defaultData>* node,
                                                              ASSOCIATION_UNUSED*                 sponsor = nullptr) override;





/*!
 @brief cut out the first fellow-node

 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be returned

 @return a tree node that represents the cut contractor
         or nullptr if this was not possible

 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_fellowFirst_cut.html
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
 virtual Association<DataType, defaultData>*  fellowFirst_cut(ASSOCIATION_UNUSED* sponsor = nullptr) override;

 virtual Association<DataType, defaultData>*  fellowFirst_cut(AssociationVisitor<DataType, defaultData>* visitor,
                                                              ASSOCIATION_UNUSED*                        sponsor = nullptr) override;






/*!
 @brief delete the first fellow-node inclusive its contractors and all data of this sub-tree

 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be returned

 @return nullptr if deleting was possible
         or a node if this was not possible

 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_fellowFirst_delete.html
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
 virtual Association<DataType, defaultData>*  fellowFirst_delete(ASSOCIATION_UNUSED* sponsor = nullptr) override;

 virtual Association<DataType, defaultData>*  fellowFirst_delete(AssociationVisitor<DataType, defaultData>* visitor,
                                                                 ASSOCIATION_UNUSED*                        sponsor = nullptr) override;


/*!
 @brief return the first fellow-node in a chain of contractors


 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be returned

 @return a tree node that represents the contractor
         or nullptr if there are no fellows

 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_fellowFirst_get.html
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
 virtual Association<DataType, defaultData>*  fellowFirst_get(ASSOCIATION_UNUSED* sponsor = nullptr) override;

/*!
 @brief return the first fellow-node in a chain of contractors defined by the given visitor


 @param visitor a concrete association-visitor that is used to search for the node
 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be returned

 @return a tree node that represents the contractor
         or nullptr if the given visitor finds no specified contractor
         or nullptr if there are no fellows

 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_fellowFirst_get.html
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
 virtual Association<DataType, defaultData>*  fellowFirst_get(AssociationVisitor<DataType, defaultData>* visitor,
                                                              ASSOCIATION_UNUSED*                        sponsor = nullptr) override;




/*!
 @brief add a new node as a last fellow

 @param node       new contractor to add
 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be returned

 @return a tree node that represents the new contractor
         or nullptr if this was not possible

 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_fellowLast_add.html
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
 virtual Association<DataType, defaultData>*  fellowLast_add(Association<DataType, defaultData>* node,
                                                             ASSOCIATION_UNUSED*                 sponsor = nullptr) override;





/*!
 @brief cut out the last fellow-node

 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be returned

 @return a tree node that represents the cut contractor
         or nullptr if this was not possible

 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_fellowLast_cut.html
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
 virtual Association<DataType, defaultData>*  fellowLast_cut(ASSOCIATION_UNUSED* sponsor = nullptr) override;

 virtual Association<DataType, defaultData>*  fellowLast_cut(AssociationVisitor<DataType, defaultData>* visitor,
                                                             ASSOCIATION_UNUSED*                       sponsor = nullptr) override;






/*!
 @brief delete the last fellow-node inclusive its contractors and all data of this sub-tree

 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be returned

 @return nullptr if deleting was possible
         or a node if this was not possible

 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_fellowLast_delete.html
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
 virtual Association<DataType, defaultData>*  fellowLast_delete(ASSOCIATION_UNUSED* sponsor = nullptr) override;


 virtual Association<DataType, defaultData>*  fellowLast_delete(AssociationVisitor<DataType, defaultData>* visitor,
                                                                ASSOCIATION_UNUSED*                        sponsor = nullptr) override;



/*!
 @brief return the last fellow-node in a chain of contractors

 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be returned

 @return a tree node that represents the contractor
         or nullptr if there are no fellows

 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_fellowLast_get.html
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
 virtual Association<DataType, defaultData>*  fellowLast_get(ASSOCIATION_UNUSED* sponsor = nullptr) override;


/*!
 @brief return the last fellow-node in a chain of contractors defined by the given visitor


 @param visitor a concrete association-visitor that is used to search for the node
 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be returned

 @return a tree node that represents the contractor
         or nullptr if the given visitor finds no specified contractor
         or nullptr if there are no fellows

 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_fellowLast_get.html
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
 virtual Association<DataType, defaultData>*  fellowLast_get(AssociationVisitor<DataType, defaultData>* visitor,
                                                             ASSOCIATION_UNUSED*                        sponsor = nullptr) override;




/*!
 @brief checks if the given node tree node object is an ancestor

 @param node the node-object to test
 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be returned

 @return a tree node that represents an ancestor
      or nullptr the given tree-node is not an ancestor

 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_isAncestor.html
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
 virtual Association<DataType, defaultData>* isAncestor(Association<DataType, defaultData>* node,
                                                        Association<DataType, defaultData>* sponsor = nullptr) override;



/*!
 @brief checks if the given node tree node object is the sponsor

 @param node the node-object to test

 @return a tree node that represents the sponsor
      or nullptr the given tree-node is not the sponsor


 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_isSponsor.html
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

 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_isContractor.html
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
                   from that the fellow should be returned

 @return a tree node that represents a fellow
      or nullptr the given tree-node is not a fellow

 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_isFellow.html
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
 virtual Association<DataType, defaultData>* isFellow(Association<DataType, defaultData>* node,
                                                      Association<DataType, defaultData>* sponsor = nullptr) override;



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

 virtual void welcome(AssociationVisitor<DataType, defaultData>* visitor,
                      DirectionOfIteration                       direction,
                      Association<DataType, defaultData>*        sponsor = nullptr) override;




/* !
 @brief return the data-content of the node


 @return the tree node data or nullptr if node-data was not defined

 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_data_get.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    22.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
 AssociationData*  data_get(void);
*/







/*!
 @brief exchange 2 given tree-nodes with their potential sub-nodes


 @param [in] node1   first node to exchange
 @param [in] node2   second node to exchange

 @return true if swapping was successfully done
 <br>    nullptr if swapping was not possible

 <br><br>
 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_swapNodes.html
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
 @brief cut a given tree-node with its potential sub-nodes as sub-tree from a specified location


 @param [in] node            node to cut

 @return reference to the inserted node if insertion was successfully done
 <br>    nullptr if insertion was not possible

 <br><br>
 @htmlinclude ./des/AssociationFellowship_DataType_defaultData_cutNode.html
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
    Association<DataType, defaultData>*  Sponsor{nullptr};         ///< @brief sponsor-node inside the tree
    Association<DataType, defaultData>*  FellowBehind{nullptr};    ///< @brief next fellow-node among the chain of contractor-nodes of a sponsor node
    Association<DataType, defaultData>*  FellowBefore{nullptr};    ///< @brief previous fellow-node among the chain of contractor-nodes of a sponsor node
    Association<DataType, defaultData>*  ContractorFirst{nullptr}; ///< @brief first contractor-node among the chain of contractor-nodes of a sponsor node
    Association<DataType, defaultData>*  ContractorLast{nullptr};  ///< @brief last contractor-node among the chain of contractor-nodes of a sponsor node


/// @brief default initialisation
    Att(void):Sponsor(nullptr),
              FellowBehind(nullptr),
              FellowBefore(nullptr),
              ContractorFirst(nullptr),
              ContractorLast(nullptr)
        {};

///< @brief user initialisation
    Att(Association<DataType, defaultData>* sponsor,
        Association<DataType, defaultData>* fellowBehind,
        Association<DataType, defaultData>* fellowBefore,
        Association<DataType, defaultData>* contractorFirst,
        Association<DataType, defaultData>* contractorLast)
         :Sponsor(sponsor),
          FellowBehind(fellowBehind),
          FellowBefore(fellowBefore),
          ContractorFirst(contractorFirst),
          ContractorLast(contractorLast)
        {};

/// @brief  copy constructor
    Att(const Att& att)
         :Sponsor(att.Sponsor),
          FellowBehind(att.FellowBehind),
          FellowBefore(att.FellowBefore),
          ContractorFirst(att.ContractorFirst),
          ContractorLast(att.ContractorLast)
        {};

/// @brief  assignment operator
  const Att& operator = (const Att& att)
  {
   Sponsor         = att.Sponsor;
   FellowBehind    = att.FellowBehind;
   FellowBefore    = att.FellowBefore;
   ContractorFirst = att.ContractorFirst;
   ContractorLast  = att.ContractorLast;
   return(*this);
  };




  }Att;





 private:




};



#ifndef DOXYGEN
#define USING_NAMESPACE using namespace
//}; USING_NAMESPACE ASSOCIATION;
//}; USING_NAMESPACE TXTDIASM;
#undef  USING_NAMESPACE
#endif //DOXYGEN


#endif //ASSOCIATION_FELLOWSHIP_H

