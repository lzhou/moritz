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

#ifndef TDA_ASSOCIATION_H
 #define TDA_ASSOCIATION_H




#include<list>
#include<set>
#include <fstream>

#include "ASS_Data.h"



using namespace std;


#ifndef DOXYGEN
////namespace TXTDIASM {
//namespace ASSOCIATION {
#endif //DOXYGEN


 /// @brief parameter type for methods which iterate over fellows
 typedef enum DirectionOfIteration
 {
  IterateWithFound,        ///< @brief continue with the node found by the visitor
  IterateForwards,         ///< @brief forwards    in the direction to the last fellow
  IterateBackwards,        ///< @brief backwards   in the direction to the first fellow
  IterateUpwards,          ///< @brief upwards     in the direction to the first ancestor
  IterateDownwards,        ///< @brief downwards   in the direction to the first contractor
  IterateDownwardsReverse, ///< @brief downwards   in the direction to the last contractor
  IterateAsBefore,         ///< @brief continue    iteration as already defined
  IterateNoMore,           ///< @brief stop        iteration-process
 }DirectionOfIteration;





template <class DataType, DataType defaultData> class AssociationVisitor;

template <class DataType, DataType defaultData> class AssociationSponsor;
template <class DataType, DataType defaultData> class AssociationFellowship;


template <class DataType, DataType defaultData> class Association
{

 friend class AssociationSponsor<DataType, defaultData>;
 friend class AssociationFellowship<DataType, defaultData>;


 public:

 const set<DataType>* NoDump = nullptr;

/*!
 @brief default constructor
 <br><br>
 @htmlinclude ./des/Association_DataType_defaultData__Association.html
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
 Association(void);

/*!
 @brief data defining constructor
 <br><br>
 @htmlinclude ./des/Association_DataType_defaultData__Association.html
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
 explicit Association(DataType data);

/*!
 @brief data copy constructor

 @param [in] association object to copy

 @htmlinclude ./des/Association_DataType_defaultData__Association.html
*/
 explicit Association(const Association<DataType, defaultData>& association);





/*!
  @brief assignment operator

  @param [in] association object to assign

*/
Association<DataType, defaultData>& operator= (const Association<DataType, defaultData>& association);




/*!
 @brief destructor
 <br><br>
 @htmlinclude ./des/Association_DataType_defaultData__Association.html
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
  virtual ~Association(void);



/*!
 @brief cast this object to an object of the type AssociationSponsor


 @return a pointer to a real existing object if conversion is possible
 @return nullptr if object could not be converted


 <br><br>
 @htmlinclude ./des/Association_DataType_defaultData_as_AssociationSponsor.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    22.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
  virtual AssociationSponsor<DataType, defaultData>* as_AssociationSponsor(void);
*/




/*!
 @brief cast this object to an object of the type  AssociationFellowship


 @return a pointer to a real existing object if conversion is possible
 @return nullptr if object could not be converted


 <br><br>
 @htmlinclude ./des/Association_DataType_defaultData_as_AssociationFellowship.html
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
  virtual AssociationFellowship<DataType, defaultData>* as_AssociationFellowship(void);



/*!
 @brief create a new association object of a concrete association class,

 this method should ensure to get a new object from the same type as the called
 object even the called object is pointed by an abstract type pointer

 @note the new object will be created while runtime on the heap by using new
       and the user has to delete it manually.

 @return a pointer to a new association object if the called object itself is not
         an abstract one even the pointer has an abstract type.
 @return nullptr if the called object has the abstract type Association<DataType, defaultData>


 <br><br>
 @htmlinclude ./des/Association_DataType_defaultData_newObject.html
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
  virtual Association<DataType, defaultData>* newObject(void);

  virtual Association<DataType, defaultData>* newObject(DataType data) = 0;







/*!
 @brief return the data-content of the node


 @return  the tree node data

 @htmlinclude ./des/Association_DataType_defaultData_data_get.html
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
  DataType data_get(void);





/*!
 @brief define the data-content of the node

 @param data new data-content


 @htmlinclude ./des/Association_DataType_defaultData_data_set.html
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
 void           data_set(DataType data);





/*!
 @brief cut a given tree-node with its potential sub-nodes as sub-tree from a specified location


 @param [in] node            node to cut

 @return reference to the cut node if cutting was successfully done
 <br>    nullptr if cutting was not possible

 <br><br>
 @I_______________________________________________________
    19.09.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/

 virtual Association<DataType, defaultData>* cutNode(Association<DataType, defaultData>* node) = 0;








/*!
 @brief exchange 2 given tree-nodes with their potential sub-nodes


 @param [in] node1   first node to exchange
 @param [in] node2   second node to exchange

 @return true if swapping was successfully done
 <br>    nullptr if swapping was not possible

 <br><br>
 @I_______________________________________________________
    13.05.2018   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual bool swapNodes(Association<DataType, defaultData>* node1,
                        Association<DataType, defaultData>* node2) = 0;












/*!
 @brief cut a given tree-node with its potential sub-nodes as sub-tree from a specified location
 and delete it

 @param [in] node            node to delete
 @param [in] sponsor         sponsor of node to delete

 @return nullptr if it was possible to delete the node and its data-elements
 <br>    reference to the node to delete if the deleting was not possible

 <br><br>
 @htmlinclude ./des/Association_DataType_defaultData_deleteNode.html
 @I_______________________________________________________
    19.09.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/

 Association<DataType, defaultData>* deleteNode(Association<DataType, defaultData>* node    = nullptr,
                                                Association<DataType, defaultData>* sponsor = nullptr);








/*!
 @brief return the sponsor node to realise a common interface

 @param  sponsor possible sponsor of this node

 @return sponsor association if known
 @return nullptr if known sponsor is not known

 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    09.09.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual Association<DataType, defaultData>* sponsor_get(Association<DataType, defaultData>* sponsor = nullptr) = 0;









/*!
 @brief add a new node before an already existing one

 @param beforeThis already existing contractor to add the new one before
 @param node       new contractor to add

 @return a tree node that represents the new contractor
         or nullptr if this was not possible for example since beforeThis was not a contractor

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
                                                                   Association<DataType, defaultData>* node)=0;

 virtual Association<DataType, defaultData>*  contractorBefore_add(Association<DataType, defaultData>*        beforeThis,
                                                                   Association<DataType, defaultData>*        node,
                                                                   AssociationVisitor<DataType, defaultData>* visitor)=0;






/*!
 @brief cut out the contractor-node before the given one

 @param beforeThis contractor after the node to cut

 @return a tree node that represents the cut contractor
         or nullptr if this was not possible for example since beforeThis was not a contractor

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
 virtual Association<DataType, defaultData>*  contractorBefore_cut(Association<DataType, defaultData>* beforeThis)=0;

 virtual Association<DataType, defaultData>*  contractorBefore_cut(Association<DataType, defaultData>*        beforeThis,
                                                                   AssociationVisitor<DataType, defaultData>* visitor)=0;





/*!
 @brief delete the contractor-node before the given one inclusive its contractors and all data of this sub-tree

 @param beforeThis contractor after the node to delete

 @return nullptr if deleting was possible
         or a node if this was not possible for example since beforeThis was not a contractor

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
 virtual Association<DataType, defaultData>*  contractorBefore_delete(Association<DataType, defaultData>* beforeThis)=0;


 virtual Association<DataType, defaultData>*  contractorBefore_delete(Association<DataType, defaultData>*        beforeThis,
                                                                      AssociationVisitor<DataType, defaultData>* visitor)=0;


 /*!
 @brief return the contractor node before the given one

 @param beforeThis contractor after the node to delete

 @return a tree node that represents the contractor
         or nullptr if the given node is not a contractor
         or nullptr if there are no contractors

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
 virtual Association<DataType, defaultData>*  contractorBefore_get(Association<DataType, defaultData>* beforeThis)=0;


 /*!
 @brief return a contractor node somewhere before the given one defined by the given visitor

 @param beforeThis contractor after the node to delete
 @param visitor    a concrete association-visitor that is used to search for the node

 @return a tree node that represents the contractor
         or nullptr if the given node is not a contractor
         or nullptr if the given visitor finds no specified contractor
         or nullptr if there are no contractors

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
                                                                   AssociationVisitor<DataType, defaultData>* visitor)=0;




/*!
 @brief add a new node behind an already existing one

 @param behindThis already existing contractor to add the new one behind
 @param node       new contractor to add

 @return a tree node that represents the new contractor
         or nullptr if this was not possible

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
                                                                   Association<DataType, defaultData>* node)=0;

 virtual Association<DataType, defaultData>*  contractorBehind_add(Association<DataType, defaultData>*        behindThis,
                                                                   Association<DataType, defaultData>*        node,
                                                                   AssociationVisitor<DataType, defaultData>* visitor)=0;





/*!
 @brief cut out the contractor-node behind the given one

 @param behindThis contractor before the node to cut

 @return a tree node that represents the cut contractor
         or nullptr if this was not possible for example since beforeThis was not a contractor

 @return a tree node that represents the  or nullptr if this is the tree-node

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
 virtual Association<DataType, defaultData>*  contractorBehind_cut(Association<DataType, defaultData>* behindThis)=0;

 virtual Association<DataType, defaultData>*  contractorBehind_cut(Association<DataType, defaultData>*        behindThis,
                                                                   AssociationVisitor<DataType, defaultData>* visitor)=0;







/*!
 @brief delete the contractor-node behind the given one inclusive its contractors and all data of this sub-tree

 @param behindThis contractor after the node to delete

 @return nullptr if deleting was possible
         or a node if this was not possible for example since behindThis was not a contractor

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
 virtual Association<DataType, defaultData>*  contractorBehind_delete(Association<DataType, defaultData>* behindThis)=0;

 virtual Association<DataType, defaultData>*  contractorBehind_delete(Association<DataType, defaultData>*        behindThis,
                                                                      AssociationVisitor<DataType, defaultData>* visitor)=0;


 /*!
 @brief return the contractor node after the given one

 @param behindThis contractor after the node to delete

 @return a tree node that represents the contractor
         or nullptr if the given node is not a contractor
         or nullptr if there are no contractors

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
 virtual Association<DataType, defaultData>*  contractorBehind_get(Association<DataType, defaultData>* behindThis)=0;


/*!
 @brief return a contractor node somewhere after the given one defined by the given visitor

 <br><br>

 @param behindThis contractor after the node to delete
 @param visitor    a concrete association-visitor that is used to search for the node

 @return a tree node that represents the contractor
         or nullptr if the given node is not a contractor
         or nullptr if the given visitor finds no specified contractor
         or nullptr if there are no contractors

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
                                                                   AssociationVisitor<DataType, defaultData>* visitor)=0;





/*!
 @brief add a new node as the first contractor

 @param node       new contractor to add

 @return a tree node that represents the new contractor
         or nullptr if this was not possible

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
 virtual Association<DataType, defaultData>*  contractorFirst_add(Association<DataType, defaultData>* node)=0;





/*!
 @brief cut out the first contractor-node

 @return a tree node that represents the cut contractor
         or nullptr if this was not possible

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
 virtual Association<DataType, defaultData>*  contractorFirst_cut(void)=0;

 virtual Association<DataType, defaultData>*  contractorFirst_cut(AssociationVisitor<DataType, defaultData>* visitor)=0;




/*!
 @brief delete the first contractor-node inclusive its contractors and all data of this sub-tree

 @return nullptr if deleting was possible
         or a node if this was not possible

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
 virtual Association<DataType, defaultData>*  contractorFirst_delete(void)=0;


 virtual Association<DataType, defaultData>*  contractorFirst_delete(AssociationVisitor<DataType, defaultData>* visitor)=0;



 /*!
 @brief return the the first contractor-node in a chain of contractors


 @return a tree node that represents the contractor
         or nullptr if this node has no contractors

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
 virtual Association<DataType, defaultData>*  contractorFirst_get(void)=0;



/*!
 @brief return the first contractor defined by the given visitor

 <br><br>

 @param visitor a concrete association-visitor that is used to search for the node

 @return a tree node that represents the contractor
         or nullptr if the given visitor finds no specified contractor
         or nullptr if there are no contractors

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
 virtual Association<DataType, defaultData>*  contractorFirst_get(AssociationVisitor<DataType, defaultData>* visitor)=0;







/*!
 @brief add a new node as the last contractor

 @param node       new contractor to add

 @return a tree node that represents the new contractor
         or nullptr if this was not possible


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
 virtual Association<DataType, defaultData>*  contractorLast_add(Association<DataType, defaultData>* node)=0;





/*!
 @brief cut out the last contractor-node

 @return a tree node that represents the cut contractor
         or nullptr if this was not possible

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
 virtual Association<DataType, defaultData>*  contractorLast_cut(void)=0;

 virtual Association<DataType, defaultData>*  contractorLast_cut(AssociationVisitor<DataType, defaultData>* visitor)=0;






/*!
 @brief delete the last contractor-node inclusive its contractors and all data of this sub-tree

 @return nullptr if deleting was possible
         or a node if this was not possible

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
 virtual Association<DataType, defaultData>*  contractorLast_delete(void)=0;

 virtual Association<DataType, defaultData>*  contractorLast_delete(AssociationVisitor<DataType, defaultData>* visitor)=0;


/*!
 @brief return the the last contractor-node in a chain of contractors


 @return a tree node that represents the contractor
         or nullptr if this node has no contractors

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
 virtual Association<DataType, defaultData>*  contractorLast_get(void)=0;



/*!
 @brief return the last contractor defined by the given visitor

 <br><br>

 @param visitor a concrete association-visitor that is used to search for the node

 @return a tree node that represents the contractor
         or nullptr if the given visitor finds no specified contractor
         or nullptr if there are no contractors

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
 virtual Association<DataType, defaultData>*  contractorLast_get(AssociationVisitor<DataType, defaultData>* visitor)=0;









/*!
 @brief add a new node as a previous fellow

 @param node       new fellow to add
 @param sponsor    node that manages the chain of contractors
                   in that the new fellow should be inserted

 @return a tree node that represents the new contractor
         or nullptr if this was not possible

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
                                                               Association<DataType, defaultData>* sponsor = nullptr)=0;





/*!
 @brief add a new node as a previous fellow

 @param node       new fellow to add
 @param sponsor    node that manages the chain of contractors
                   in that the new fellow should be inserted
 @param visitor    a concrete association-visitor that is used to search for the node

 @return a tree node that represents the new contractor
         or nullptr if this was not possible

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
                                                               Association<DataType, defaultData>*        sponsor = nullptr)=0;





/*!
 @brief cut out the fellow-node before this one

 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be cut out


 @return a tree node that represents the cut contractor
         or nullptr if this was not possible

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
 virtual Association<DataType, defaultData>*  fellowBefore_cut(Association<DataType, defaultData>* sponsor = nullptr)=0;





/*!
 @brief cut out the fellow-node before this one

 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be cut out
 @param visitor    a concrete association-visitor that is used to search for the node



 @return a tree node that represents the cut contractor
         or nullptr if this was not possible

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
                                                               Association<DataType, defaultData>*        sponsor = nullptr)=0;





/*!
 @brief delete the fellow-node before this one inclusive its contractors and all data of this sub-tree

 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be deleted

 @return nullptr if deleting was possible
         or a node if this was not possible

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
 virtual Association<DataType, defaultData>*  fellowBefore_delete(Association<DataType, defaultData>* sponsor = nullptr)=0;







/*!
 @brief delete the fellow-node before this one inclusive its contractors and all data of this sub-tree

 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be deleted
 @param visitor    a concrete association-visitor that is used to search for the node


 @return nullptr if deleting was possible
         or a node if this was not possible

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
                                                                  Association<DataType, defaultData>*        sponsor = nullptr)=0;




 /*!
 @brief return the fellow-node after in a chain of contractors

 @param sponsor    node that manages the chain of contractors
                   from that the  fellow should be returned

 @return a tree node that represents the fellow
         or nullptr if this is the last node in the chain

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
 virtual Association<DataType, defaultData>*  fellowBefore_get(Association<DataType, defaultData>* sponsor = nullptr)=0;




 /*!
 @brief return the fellow-node after in a chain of contractors

 @param sponsor    node that manages the chain of contractors
                   from that the  fellow should be returned
 @param visitor    a concrete association-visitor that is used to search for the node


 @return a tree node that represents the fellow
         or nullptr if this is the last node in the chain

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
                                                               Association<DataType, defaultData>*        sponsor = nullptr)=0;






/*!
 @brief add a new node as a next fellow

 @param node       new contractor to add
 @param sponsor    node that manages the chain of contractors
                   in that the new fellow should be inserted


 @return a tree node that represents the new contractor
         or nullptr if this was not possible

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
                                                               Association<DataType, defaultData>* sponsor = nullptr)=0;







/*!
 @brief add a new node as a next fellow

 @param node       new contractor to add
 @param sponsor    node that manages the chain of contractors
                   in that the new fellow should be inserted
 @param visitor    a concrete association-visitor that is used to search for the node



 @return a tree node that represents the new contractor
         or nullptr if this was not possible

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
 virtual Association<DataType, defaultData>*  fellowBehind_add(Association<DataType, defaultData>*        node,
                                                               AssociationVisitor<DataType, defaultData>* visitor,
                                                               Association<DataType, defaultData>*        sponsor = nullptr)=0;





/*!
 @brief cut out the fellow-node behind this one

 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be cut out


 @return a tree node that represents the cut contractor
         or nullptr if this was not possible

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
 virtual Association<DataType, defaultData>*  fellowBehind_cut(Association<DataType, defaultData>* sponsor = nullptr)=0;





/*!
 @brief cut out the fellow-node behind this one

 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be cut out
 @param visitor    a concrete association-visitor that is used to search for the node



 @return a tree node that represents the cut contractor
         or nullptr if this was not possible

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
                                                               Association<DataType, defaultData>*        sponsor = nullptr)=0;





/*!
 @brief delete the fellow-node behind this one inclusive its contractors and all data of this sub-tree

 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be deleted


 @return nullptr if deleting was possible
         or a node if this was not possible

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
 virtual Association<DataType, defaultData>*  fellowBehind_delete(Association<DataType, defaultData>* sponsor = nullptr)=0;





/*!
 @brief delete the fellow-node behind this one inclusive its contractors and all data of this sub-tree

 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be deleted
 @param visitor    a concrete association-visitor that is used to search for the node



 @return nullptr if deleting was possible
         or a node if this was not possible

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
                                                                  Association<DataType, defaultData>*        sponsor = nullptr)=0;


/*!
 @brief return the fellow-node before in a chain of contractors

 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be returned


 @return a tree node that represents the fellow
         or nullptr if this is the first node in the chain

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
 virtual Association<DataType, defaultData>*  fellowBehind_get(Association<DataType, defaultData>* sponsor = nullptr)=0;


/*!
 @brief return the fellow-node before in a chain of contractors

 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be returned
 @param visitor    a concrete association-visitor that is used to search for the node



 @return a tree node that represents the fellow
         or nullptr if this is the first node in the chain

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
                                                               Association<DataType, defaultData>*        sponsor = nullptr)=0;






/*!
 @brief add a new node as a first fellow

 @param node       new contractor to add
 @param sponsor    node that manages the chain of contractors
                   in that the new fellow should be inserted


 @return a tree node that represents the new contractor
         or nullptr if this was not possible

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
                                                              Association<DataType, defaultData>* sponsor = nullptr)=0;





/*!
 @brief cut out the first fellow-node

 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be cut out


 @return a tree node that represents the cut contractor
         or nullptr if this was not possible

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
 virtual Association<DataType, defaultData>*  fellowFirst_cut(Association<DataType, defaultData>* sponsor = nullptr)=0;





/*!
 @brief cut out the first fellow-node

 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be cut out
 @param visitor    a concrete association-visitor that is used to search for the node



 @return a tree node that represents the cut contractor
         or nullptr if this was not possible

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
                                                              Association<DataType, defaultData>*        sponsor = nullptr)=0;





/*!
 @brief delete the first fellow-node inclusive its contractors and all data of this sub-tree

 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be deleted


 @return nullptr if deleting was possible
         or a node if this was not possible

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
 virtual Association<DataType, defaultData>*  fellowFirst_delete(Association<DataType, defaultData>* sponsor = nullptr)=0;




/*!
 @brief delete the first fellow-node inclusive its contractors and all data of this sub-tree

 @param visitor    a concrete association-visitor that is used to search for the node
 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be deleted



 @return nullptr if deleting was possible
         or a node if this was not possible

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
                                                                 Association<DataType, defaultData>*        sponsor = nullptr)=0;


/*!
 @brief return the first fellow-node in a chain of contractors

 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be returned


 @param visitor a concrete association-visitor that is used to search for the node

 @return a tree node that represents the contractor
         or nullptr if there are no fellows

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
 virtual Association<DataType, defaultData>*  fellowFirst_get(Association<DataType, defaultData>* sponsor = nullptr)=0;



/*!
 @brief return the first fellow-node in a chain of contractors

 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be returned
 @param visitor    a concrete association-visitor that is used to search for the node


 @return a tree node that represents the contractor
         or nullptr if there are no fellows

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
                                                              Association<DataType, defaultData>*        sponsor = nullptr)=0;





/*!
 @brief add a new node as a last fellow

 @param node       new contractor to add
 @param sponsor    node that manages the chain of contractors
                   in that the new fellow should be inserted


 @return a tree node that represents the new contractor
         or nullptr if this was not possible

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
                                                             Association<DataType, defaultData>* sponsor = nullptr)=0;





/*!
 @brief cut out the last fellow-node

 @param sponsor    node that manages the chain of contractors
                   from that the new fellow should be cut out


 @return a tree node that represents the cut contractor
         or nullptr if this was not possible

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
 virtual Association<DataType, defaultData>*  fellowLast_cut(Association<DataType, defaultData>* sponsor = nullptr)=0;





/*!
 @brief cut out the last fellow-node

 @param sponsor    node that manages the chain of contractors
                   from that the new fellow should be cut out
 @param visitor    a concrete association-visitor that is used to search for the node



 @return a tree node that represents the cut contractor
         or nullptr if this was not possible

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
                                                             Association<DataType, defaultData>*        sponsor = nullptr)=0;





/*!
 @brief delete the last fellow-node inclusive its contractors and all data of this sub-tree

 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be deleted


 @return nullptr if deleting was possible
         or a node if this was not possible

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
 virtual Association<DataType, defaultData>*  fellowLast_delete(Association<DataType, defaultData>* sponsor = nullptr)=0;





/*!
 @brief delete the last fellow-node inclusive its contractors and all data of this sub-tree

 @param sponsor    node that manages the chain of contractors
                   from that the fellow should be deleted
 @param visitor    a concrete association-visitor that is used to search for the node



 @return nullptr if deleting was possible
         or a node if this was not possible

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
                                                                Association<DataType, defaultData>*        sponsor = nullptr)=0;


/*!
 @brief return the last fellow-node in a chain of contractors

 @param sponsor    node that manages the chain of contractors
                   from that the new fellow should be returned


 @return a tree node that represents the contractor
         or nullptr if there are no fellows

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
 virtual Association<DataType, defaultData>*  fellowLast_get(Association<DataType, defaultData>* sponsor = nullptr)=0;


/*!
 @brief return the last fellow-node in a chain of contractors

 @param sponsor    node that manages the chain of contractors
                   from that the new fellow should be returned
 @param visitor    a concrete association-visitor that is used to search for the node



 @return a tree node that represents the contractor
         or nullptr if there are no fellows

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
                                                            Association<DataType, defaultData>*        sponsor = nullptr)=0;









/*!
 @brief checks if the given node tree node object is an ancestor

 @param node       the node-object to test
 @param sponsor    node that manages the chain of contractors
                   from that the new fellow should be returned



 @return a tree node that represents an ancestor
      or nullptr the given tree-node is not an ancestor

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
                                                       Association<DataType, defaultData>* sponsor = nullptr)=0;



/*!
 @brief checks if the given node tree node object is the sponsor

 @param node the node-object to test

 @return a tree node that represents the sponsor
      or nullptr the given tree-node is not the sponsor


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
virtual Association<DataType, defaultData>* isSponsor(Association<DataType, defaultData>* node)=0;



/*!
 @brief checks if the given node tree node object is a contractor

 @param node the node-object to test

 @return a tree node that represents a contractor
      or nullptr the given tree-node is not a contractor

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
virtual Association<DataType, defaultData>* isContractor(Association<DataType, defaultData>* node)=0;



/*!
 @brief checks if the given node tree node object is a fellow

 @param node the node-object to test
 @param sponsor    node that manages the chain of contractors
                   where the asking contractor is managed

 @return a tree node that represents a fellow
      or nullptr the given tree-node is not a fellow

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
                                                     Association<DataType, defaultData>* sponsor = nullptr)=0;







 virtual void welcome(AssociationVisitor<DataType, defaultData>*  visitor,
                      DirectionOfIteration                        direction,
                      Association<DataType, defaultData>*         sponsor = nullptr)=0;


























 protected:


// /*!
// Attributes of class
// */
//  struct Att
//  {
//  }Att;



/*!
 @brief  data of the tree-node
*/
    DataType Data{defaultData};



 private:




};



#ifndef DOXYGEN
#define USING_NAMESPACE using namespace
//}; USING_NAMESPACE ASSOCIATION;
//}; USING_NAMESPACE TXTDIASM;
#undef  USING_NAMESPACE
#endif //DOXYGEN
//typedef Association<class TiPa_Data*>           TiPa_Concrete::DataAssociation;
//typedef AssociationFellowship<class TiPa_Data*> TiPa_Concrete::DataFellow;
//typedef AssociationSponsor<class TiPa_Data*>   TiPa_Concrete:: DataSponsor;

#endif //TDA_ASSOCIATION_H

