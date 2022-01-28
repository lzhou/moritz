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

#ifndef ASS_VISITOR_H
 #define ASS_VISITOR_H

#include <vector>

#include "ASS_Data.h"
#include "Association.hpp"







/*!
 abstract manager of tree_data

 this class describes an common interface between the data of a tree node and its
 node that is managing the tree-associations
*/
template <class DataType, DataType defaultData> class AssociationVisitor
{
 public:





/*!
 @brief default constructor

 <br><br>

 @htmlinclude ./des/AssociationVisitor_DataType_defaultData_AssociationVisitor.html

 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    08.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  AssociationVisitor(void);



/*!
 @brief default destructor


 @htmlinclude ./des/AssociationVisitor_DataType_defaultData__AssociationVisitor.html
 .html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    08.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
virtual  ~AssociationVisitor(void);




/*!
 @brief initialize this visitor


 @htmlinclude ./des/AssociationVisitor_DataType_defaultData_init.html
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
 void init(void);




/*!
 @brief return a special node found while visiting a tree

 @return a tree-node reference if node was found or nullptr if not


 @htmlinclude ./des/AssociationVisitor_DataType_defaultData_node_get.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    08.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 Association<DataType, defaultData>* node_get(void);

/*!
 @brief set the node used for evaluation purpose while visiting a tree

 @param node [in] a tree-data reference

 <br><br>

 @htmlinclude ./des/AssociationVisitor_DataType_defaultData_node_set.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    08.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void node_set(Association<DataType, defaultData>* node);

/*!
 @brief return the data of a special node found while visiting a tree

 @return a tree-data reference if node was found or nullptr if not

 @htmlinclude ./des/AssociationVisitor_DataType_defaultData_data_get.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    08.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 DataType data_get(void);

/*!
 @brief set the data used for evaluation purpose while visiting a tree

 @param data [in] a tree-data reference

 @htmlinclude ./des/AssociationVisitor_DataType_defaultData_data_set.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    08.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void data_set(DataType data);







/*!
 @brief controls a complete evaluation process without passing the visitor
 to the evaluated associations

 @param [in] node            the association-node to analyse
 @param [in] sponsor         the sponsor of the node to analyse
 @param [in] firstDirection  defines how to iterate until current path-part was not found
 @param [in] secondDirection defines how to iterate once current path-part was not found


 @htmlinclude ./des/AssociationVisitor_DataType_defaultData_travel.html
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
 void travel(Association<DataType, defaultData>*  node,
             Association<DataType, defaultData>*  sponsor,
             DirectionOfIteration     firstDirection,
             DirectionOfIteration     secondDirection);









// @param sponsor the sponsor of the association to analyse

/*!
 @brief start to evaluate a association

 @param node    the association to analyse

 @return direction of next iteration step

 @htmlinclude ./des/AssociationVisitor_DataType_defaultData_evaluate.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    08.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual DirectionOfIteration evaluate(Association<DataType, defaultData>* node) = 0;


/*!
 @brief return if evaluation was already successfully

 @param direction [in] the direction of the current iteration step done by the visited node

 @htmlinclude ./des/AssociationVisitor_DataType_defaultData_direction_set.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    03.09.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
 @I re-factoring from binary output to more specific enumeration-type
 @I the visitor has to communicate with its visited counterpart
    the direction of the iteration
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
void  direction_set(DirectionOfIteration direction);



/*!
 @brief return the direction of the next iteration-step to be done by the visited node
 or to stop the iteration since the evaluation is already done

 @return if the evaluation is not finished,
         the direction of the next iteration step to be done by the visited node
 @return if the evaluation is finished,
         the information that the iteration has to be stopped by the visited node

 @htmlinclude ./des/AssociationVisitor_DataType_defaultData_direction_get.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    15.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
    03.09.2015   @I  Eckard Klotz
 @I re-factoring from binary output to more specific enumeration-type
 @I the visitor has to communicate with its visited counterpart
    the direction of the iteration
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 DirectionOfIteration direction_get(void);








 protected:

 /*! @brief attributes of the class-object*/


 struct Att
 {
  Association<DataType, defaultData>*  Node{nullptr};                     ///< @brief reference-node for analysis or pointer to a node found
  DataType                             Data{defaultData};                 ///< @brief reference-data for analysis or pointer to   data found
  DirectionOfIteration                 Direction{IterateNoMore};          ///< @brief current state of evaluation

  Att(void):Node(nullptr),Data(defaultData),Direction(IterateNoMore){};   ///< @brief default initialization

  Att(Att& att):Node(att.Node),Data(att.Data),Direction(att.Direction){}; ///< @brief default initialization

  const Att& operator = (const Att& att)
  {
   Node      = att.Node;
   Data      = att.Data;
   Direction = att.Direction;
   return(*this);
  }
 }Att;

 private:





/*!
 iterates the given node and sponsor in the given direction

 @param [in] node       the association-node to analyse
 @param [in] sponsor    the sponsor of the node to analyse
 @param [in] direction  defines how to iterated


 @htmlinclude AssociationVisitor_DataType_defaultData_iterate.html
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
   void iterate(Association<DataType, defaultData>** node,
                Association<DataType, defaultData>** sponsor,
                DirectionOfIteration    direction);


};





#endif // ASS_VISITOR_H

