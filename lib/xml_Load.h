/*!

 @file
 @brief concrete association visitor to create an xml-tree

 Copyright (C) 2017-2020 by Eckard Klotz.

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
    21.11.2017     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    21.11.2017...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/
#ifndef XML_LOAD_H
 #define XML_LOAD_H

#include "ASS_Model.hpp"

#include "ASS_Visitor.hpp"
#include "TiPa_Data.h"
#include "xml_Data.h"



/*!
 @brief concrete association visitor to create an xml-tree
*/
class XML_Load:public AssociationVisitor<TiPa_Data*,nullptr>
{
 public:


  typedef AssociationModel<XML_Data, nullptr>       DataModel;
  typedef Association<XML_Data*, nullptr>           DataAssociation;

  typedef Association<TiPa_Data*, nullptr>          TiPa_DataAssociation;
  typedef AssociationVisitor<TiPa_Data*,nullptr>    TiPa_Visitor;


  XML_Load(void);
  ~XML_Load(void);



/*!
 initialize this visitor


 @htmlinclude XML_Load_init.html
*/
 void init(void);




/*!
 @brief define the context-model

 @param [in] contextModel management-object that creates and deletes associations and data-objects

 @htmlinclude ./des/XML_Load_contextModel_set.html

*/
void contextModel_set(DataModel* contextModel);



/*!
 initialize this visitor

 @param [out] destination  root node of the new association tree to create
 @param [in]  source       root node of the association tree that contains the the data to use

 @return pointer to initialized class-object

 @htmlinclude ./des/XML_Load_operator().html
*/
XML_Load* operator()(DataAssociation*  destination,
                     TiPa_DataAssociation* source     );



















// @param sponsor the sponsor of the association to analyse

 /*!
 start to evaluate a association

 @param node    the association to analyse

 @return direction of next iteration step

 @htmlinclude ./des/XML_Load_evaluate.html
*/
DirectionOfIteration evaluate(TiPa_DataAssociation* node/*, TiPa_DataAssociation* sponsor*/);






 protected:

 private:



/*!
 @brief create an xml element-node

 @param [in] node    the parser association that contains the element-information

 @return xml element-node

 @htmlinclude ./des/XML_Load_createElementXML.html
*/
 DataAssociation* createElementXML(TiPa_DataAssociation* node);



/*!
 @brief create an xml text-node

 @param [in] node    the parser association that contains the text-information

 @return xml text-node

 @htmlinclude ./des/XML_Load_createTextXML.html
*/
 DataAssociation* createTextXML(TiPa_DataAssociation* node);



/*!
 @brief return ascii character symbolized as xml-reference

 @param symbol    xml-reference

 @return ascii character

 @htmlinclude ./des/XML_Load_solveReference.html
*/
 const char* solveReference(const char* symbol);




 struct Att
 {
//  DirectionOfIteration           CommonDirection; ///< stores the direction to iterate while temporary changes

  DataModel*                 ContextModel;    ///< manages the analysed data

  DataAssociation*           DestinationRoot; ///< root of association tree with the data to analyse
  DataAssociation*           NewAssociation;  ///< root of new association tree

  TiPa_DataAssociation*      RootAssociation; ///< first association that is visited
                                              ///< while one evaluation-process
  list<DataAssociation*>     ParentNode;      ///< current position to insert a line into
                                              ///< the output-text


  /// @brief default constructor
  Att(void):
   ContextModel   (nullptr        ),
   DestinationRoot(nullptr        ),
   NewAssociation (nullptr        ),
   RootAssociation(nullptr        )
 {};

  /*!
   @brief copy constructor
   @param [in] src object to copy
  */
  Att(const Att& src):
   ContextModel   (src.ContextModel   ),
   DestinationRoot(src.DestinationRoot),
   NewAssociation (src.NewAssociation ),
   RootAssociation(src.RootAssociation),
   ParentNode     (src.ParentNode     )
  {};

  /*!
   @brief assignment operator
   @param [in] src object to copy
   @return copied object
  */
  Att& operator = (const Att& src)
  {
   ContextModel    = src.ContextModel   ;
   DestinationRoot = src.DestinationRoot;
   NewAssociation  = src.NewAssociation ;
   RootAssociation = src.RootAssociation;
   ParentNode      = src.ParentNode     ;
   return(*this);
  };

  /// @brief destructor
  ~Att(void)
  {
   ParentNode   .clear();
  };



 }Att;





};





#endif // XML_LOAD_H



