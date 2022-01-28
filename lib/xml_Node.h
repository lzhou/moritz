/*!

 @file
 @brief user interface class for xml-associations

 Copyright (C) 2018-2020 by Eckard Klotz.

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
    03.03.2018     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    03.03.2018...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/

#ifndef XML_NODE_H
#define XML_NODE_H

#include "AssociationFellowship.h"
#include "ASS_Model.hpp"

#include "xml_Data.h"
#include "xml_Search.h"



class XML_Node
{
 public:


  typedef AssociationModel<XML_Data, nullptr>       DataModel;
  typedef Association<XML_Data*, nullptr>           DataAssociation;
  typedef AssociationFellowship<XML_Data*, nullptr> DataFellow;
  typedef AssociationVisitor<XML_Data*, nullptr>    XML_Visitor;




  static XML_Search Undefined;       ///< @brief  visitor prepared to search for an unspecified xml-node
  static XML_Search Document;        ///< @brief  visitor prepared to search for a document xml-node
  static XML_Search Element;         ///< @brief  visitor prepared to search for an element xml-node
  static XML_Search Text;            ///< @brief  visitor prepared to search for an text xml-node
  static XML_Search Comment;         ///< @brief  visitor prepared to search for an comment xml-node
  static XML_Search Declaration;     ///< @brief  visitor prepared to search for an declaration xml-node

  static const char EmptyString[1];  ///< @brief  default-value for string parameters


/*!
  @brief default constructor

  @htmlinclude ./des/XML_Node_XML_Node.html
*/
  XML_Node(void);

/*!
  @brief constructor used to set up an xml node with an xml association

  @param context     [in] manager of association- and data-objects
  @param association [in] data association of the node
  @todo search for solution if second parameter is nullptr what results in confusions if it is actually used as a data

  @htmlinclude ./des/XML_Node_XML_Node.html
*/
  XML_Node(DataModel* context, DataFellow* association);

/*!
  @brief constructor used to set up an xml node with  xml data

  @param context [in] manager of association- and data-objects
  @param xmlData [in] xml-data of the node

  @todo search for solution if second parameter is nullptr what results in confusions if it is actually used as an association

  @htmlinclude ./des/XML_Node_XML_Node.html
*/
  XML_Node(DataModel* context , XML_Data* xmlData);


/*!
  @brief constructor used to set up an xml node with  with a specific node-type

  @param context [in] manager of association- and data-objects
  @param type    [in] type of new xml-node node


  @htmlinclude ./des/XML_Node_XML_Node.html
*/
  XML_Node(DataModel* context , XML_Data::NodeType_TP type);



 /// @brief control the set up an xml node just by an association context
 typedef enum Construction_TP
 {
  Prepare = 0,  /// @brief the node will just get the context but no new association, thus the node is still not valid
  Create  = 1,  /// @brief the new context will be used to create a new association and a new empty data-object
 }Construction_TP;




/*!
  @brief constructor used to set up an xml node just by an association context

  If the node will just be prepared no new association or data-object will be created.
  Thus the node is still not valid. But if the association should be defined by a
  following process, no unused dummy-objects will be created just to be replaced afterwards.

  If the node will be completely created the given context will be used to create
  a new association with a new data-object. Thus the xml-node is formally valid and the methods
  used to define attributes values and child-nodes could be used.


  @param context      [in] manager of association- and data-objects
  @param construction [in] Prepare ==>> the node will just know the context but will have no association
  <br>                     Create  ==>> the node will have an association with an empty data-object

  @htmlinclude ./des/XML_Node_XML_Node.html
*/
  XML_Node(DataModel* context, Construction_TP construction);


/*!
  @brief copy constructor

  @param xmlNode [in] source to copy

  @htmlinclude ./des/XML_Node_XML_Node.html
*/
  XML_Node(const XML_Node& xmlNode);




/*!
  @brief destructor

  @htmlinclude ./des/XML_Node__XML_Node.html
*/
  ~XML_Node(void);



/*!
  @brief assignment operator

  @param xmlNode [in] object to assign

  @htmlinclude ./des/XML_Node_operator=.html
*/
XML_Node& operator= (const XML_Node& xmlNode);




/*!
  @brief clone the tree-structure and all its data-objects of the given node to the own association context

  @param [in] xmlNode root-node of the tree to clone

  @pre  the xml-node object used to call this method needs an own valid association context
  @post the xml-node object used to call this method becomes the root-node of the cloned tree and data-structure

  @htmlinclude ./des/XML_Node_cloneToOwnContext.html
*/
void cloneToOwnContext(const XML_Node& xmlNode);




/*!
 @brief set the association-object

 @param association [in] pointer to xml-data association

 @htmlinclude ./des/XML_Node_associationNodeSet.html
*/
void associationNodeSet(DataFellow* association);



/*!
 @brief return the association-object

 @return pointer to xml-data association or nullptr

 @htmlinclude ./des/XML_Node_associationNodeGet.html
*/
DataFellow* associationNodeGet(void);




/*!
 @brief define the context-model

 @param context [in] pointer to new context model

 @htmlinclude ./des/XML_Node_associationContextSet.html
*/
void associationContextSet(DataModel* context);



/*!
 @brief return the context-model

 @return pointer to context or nullptr

 @htmlinclude ./des/XML_Node_associationContextGet.html
*/
DataModel* associationContextGet(void);



/*!
 @brief evaluate if context and association are set

 @return true  if context and association are set with pointers unequal to nullptr
 <br>    false if context or  association is  set with nullptr

 @htmlinclude ./des/XML_Node_valid.html
*/
bool valid();





/* !
 @brief define type of xml-node that contains the xml-data

 @param [in] type node-type

 @htmlinclude ./des/XML_Node_typeSet.html
  void typeSet(XML_Data::NodeType_TP type);
*/


/*!
 @brief return type of xml-node that contains the xml-data

 @return node-type

 @htmlinclude ./des/XML_Node_typeGet.html
*/
  XML_Data::NodeType_TP typeGet(void);



/*!
 @brief define value content

 @param value value-content

 @htmlinclude ./des/XML_Node_valueSet.html
*/
  void valueSet(const char* value);


/*!
 @brief return value content

 @return value-content or nullptr if no value-content is defined

 @htmlinclude ./des/XML_Node_valueGet.html
*/
  const char* valueGet(void);






/*!
 @brief add an text attribute

 @param key  [in  name of the attribute
 @param data [in] text used to represent the data

 @return added data as new string (stored and maintained as secondary data)

 @htmlinclude ./des/XML_Node_attributeSet.html
*/
  const char* attributeSet(const char* key, const char* data);


/*!
 @brief add an integer attribute

 @param key  [in  name of the attribute
 @param data [in] text used to represent the data

 @return added data as new string (stored and maintained as secondary data)

 @htmlinclude ./des/XML_Node_attributeSet.html
*/
  const char* attributeSet(const char* key, int data);

/*!
 @brief add a double attribute

 @param key  [in  name of the attribute
 @param data [in] text used to represent the data

 @return added data as new string (stored and maintained as secondary data)

 @htmlinclude ./des/XML_Node_attributeSet.html
*/
  const char* attributeSet(const char* key, double data);



/*!
 @brief return an attribute value as text

 @param key         [in] name of the attribute
 @param defaultData [in] return value used if the searched data is not existing or not convertible

 @return text used to represent the data

 @htmlinclude ./des/XML_Node_attributeGet.html
*/
  const char* attributeGet(const char* key, const char* defaultData = XML_Node::EmptyString);


/*!
 @brief return an attribute value as integer value

 @param key         [in] name of the attribute
 @param defaultData [in] return value used if the searched data is not existing or not convertible

 @return numerical content if data could be transferred into an integer number
 <br>    given default value if the searched data is not existing or not convertible

 @htmlinclude ./des/XML_Node_attributeGet.html
*/
  int attributeGet(const char* key, int defaultData);


/*!
 @brief return an attribute value as double value

 @param key         [in] name of the attribute
 @param defaultData [in] return value used if the searched data is not existing or not convertible

 @return numerical content if data could be transferred into an integer number
 <br>    given default value if the searched data is not existing or not convertible

 @htmlinclude ./des/XML_Node_attributeGet.html
*/
  double attributeGet(const char* key, double defaultData);









 /*!
 @ingroup ADVANCED_XML_STRING

 get the text-content of an xml-node

 @param returnValue [out] text-content of the given <b>node</b> or an empty string if
                          no content found, if the give node has more than one text-child
                          all part-texts will be concatenated
 @return collected text

 @htmlinclude ./des/XML_Node_textCollect.html
*/
char* textCollect(char** returnValue);




















/*!
 @brief return the directly owning xml-node (parent-node)

 @return  valid xml-node if requested node exists or nullptr if requested node is not existing

 @htmlinclude ./des/XML_Node_preGet.html
*/
  XML_Node preGet(void);


/* !
 @brief return an xml-node inside the owner-queue (parent of parent of par...)

 @param visitor [in] description of searched node

 @return  valid xml-node if requested node exists or nullptr if requested node is not existing

 @htmlinclude ./des/XML_Node_preGet.html
  XML_Node* preGet(XML_Visitor& visitor);
*/



/*!
 @brief return first sub-node

 @return  valid xml-node if requested node exists or nullptr if requested node is not existing

 @htmlinclude ./des/XML_Node_firstGet.html
*/
  XML_Node firstGet(void);


/*!
 @brief return the a specified sub node or sub-sub.. searched from the fist to the last

 @param [in] visitor description of searched node

 @return  valid xml-node if requested node exists or nullptr if requested node is not existing

 @htmlinclude ./des/XML_Node_firstGet.html
*/
  XML_Node firstGet(XML_Visitor* visitor);



/*!
 @brief add an existing as last child

 @param nodeToAdd  [in] description of searched node

 @return  child-node added
 @return  nullptr if this node has no valid content
 @return  nullptr if given node to add is not valid

 @htmlinclude ./des/XML_Node_firstAdd.html
*/
  XML_Node firstAdd(XML_Node& nodeToAdd);

/*!
 @brief add a new node as last child

 @param type       [in] type of new xml-node node

 @return  child-node added if this node has a valid context-model
 <br>  or nullptr if this node has not a valid context-model

 @htmlinclude ./des/XML_Node_firstAdd.html
*/
  XML_Node firstAdd(XML_Data::NodeType_TP type);









/*!
 @brief return the last sub-node

 @return  valid xml-node if requested node exists or nullptr if requested node is not existing

 @htmlinclude ./des/XML_Node_lastGet.html
*/
  XML_Node lastGet(void);


/*!
 @brief return the a specified sub node or sub-sub.. searched from the last to the fist

 @param visitor [in] description of searched node

 @return  valid xml-node if requested node exists or nullptr if requested node is not existing

 @htmlinclude ./des/XML_Node_lastGet.html
*/
  XML_Node lastGet(XML_Visitor* visitor);







/*!
 @brief add an existing as last child

 @param nodeToAdd  [in] description of searched node

 @return  child-node added
 @return  nullptr if this node has no valid content
 @return  nullptr if given node to add is not valid

 @htmlinclude ./des/XML_Node_lastAdd.html
*/
  XML_Node lastAdd(XML_Node& nodeToAdd);

/*!
 @brief add a new node as last child

 @param type       [in] type of new xml-node node

 @return  child-node added if this node has a valid context-model
 <br>  or nullptr if this node has not a valid context-model

 @htmlinclude ./des/XML_Node_lastAdd.html
*/
  XML_Node lastAdd(XML_Data::NodeType_TP type);









/*!
 @brief return the direct xml-node before

 @return  valid xml-node if requested node exists or nullptr if requested node is not existing

 @htmlinclude ./des/XML_Node_beforeGet.html
*/
  XML_Node beforeGet(void);


/*!
 @brief return a specified xml-node before

 @param visitor [in] description of searched node

 @return  valid xml-node if requested node exists or nullptr if requested node is not existing

 @htmlinclude ./des/XML_Node_beforeGet.html
*/
  XML_Node beforeGet(XML_Visitor* visitor);










/*!
 @brief add an existing node before a given child-node

 @param beforeThis [in] describes the position where to add
 @param nodeToAdd  [in] description of searched node

 @return  child-node added if given position node exists
 @return  nullptr if this node has no valid content
 @return  nullptr if given position node is not existing
 @return  nullptr if given node to add is not valid

 @htmlinclude ./des/XML_Node_beforeAdd.html
*/
  XML_Node beforeAdd(XML_Node& beforeThis, XML_Node& nodeToAdd);

/*!
 @brief add a new node before a given child-node

 @param beforeThis [in] describes the position where to add
 @param type       [in] type of new xml-node node

 @return  child-node added if given position node exists and this node has a valid context-model
 <br>  or nullptr if given position node is not existing or  this node has not a valid context-model

 @htmlinclude ./des/XML_Node_beforeAdd.html
*/
  XML_Node beforeAdd(XML_Node& beforeThis, XML_Data::NodeType_TP type);




















/*!
 @brief return the direct xml-node behind

 @return  valid xml-node if requested node exists or nullptr if requested node is not existing

 @htmlinclude ./des/XML_Node_behindGet.html
*/
  XML_Node behindGet(void);


/*!
 @brief return a specified node behind

 @param visitor [in] description of searched node

 @return  valid xml-node if requested node exists or nullptr if requested node is not existing

 @htmlinclude ./des/XML_Node_behindGet.html
*/
  XML_Node behindGet(XML_Visitor* visitor);





/*!
 @brief add an existing node behind a given child-node

 @param behindThis [in] describes the position where to add
 @param nodeToAdd  [in] description of searched node

 @return  child-node added if given position node exists
 @return  nullptr if this node has no valid content
 @return  nullptr if given position node is not existing
 @return  nullptr if given node to add is not valid

 @htmlinclude ./des/XML_Node_behindAdd.html
*/
  XML_Node behindAdd(XML_Node& behindThis, XML_Node& nodeToAdd);

/*!
 @brief add a new node behind a given child-node

 @param behindThis [in] describes the position where to add
 @param type       [in] type of new xml-node node

 @return  child-node added if given position node exists and this node has a valid context-model
 <br>  or nullptr if given position node is not existing or  this node has not a valid context-model

 @htmlinclude ./des/XML_Node_behindAdd.html
*/
  XML_Node behindAdd(XML_Node& behindThis, XML_Data::NodeType_TP type);



/*!
 @brief release a child-node and return it

 @param nodeToCut [in] node that should be cut out

 @return  child-node cut out if node is a valid child node
 <br>  or nullptr if given node is not a valid child node

 @htmlinclude ./des/XML_Node_nodeCut.html
*/
  XML_Node nodeCut(XML_Node& nodeToCut);



/*!
 @brief exchange the position of 2 child-nodes

 @param node1 [in] first node to swap
 @param node2 [in] last node to swap

 @return  true if positions are exchanged
 <br>  or nullptr if exchange was not possible for example since one or both nodes are no valid child nodes

 @htmlinclude ./des/XML_Node_nodeSwap.html
*/
  bool nodeSwap(XML_Node& node1, XML_Node& node2);


/*!
 @brief store xml text-representation

 @param destination [out] variable to store text-representation in

 @htmlinclude ./des/XML_Node_xmlText.html
*/
  void xmlText(char** destination);

/*!
 @brief print out the xml text-representation over standard out (as over cout)



 @htmlinclude ./des/XML_Node_xmlText.html
*/
  void xmlText(void);



 protected:

 private:
 struct Att
 {
  DataFellow* Association;
  DataModel*  Context;

 /// @brief default constructor
 Att(void):
  Association(nullptr),
  Context    (nullptr)
 {};
 /*!
  @brief initializing constructor
 */
 Att(DataFellow* association, DataModel* context):
  Association(association),
  Context    (context    )
 {};
 /*!
  @brief copy constructor
  @param [in] src object to copy
 */
 Att(const Att& src):
  Association(src.Association),
  Context    (src.Context    )
 {};
 /*!
  @brief assignment operator
  @param [in] src object to copy
  @return copied object
 */
 Att& operator = (const Att& src)
 {
  Association = src.Association;
  Context     = src.Context    ;
  return(*this);
 };
 /// @brief destructor
 ~Att(void)
 {
 };

 }Att;

};











/*!
 @brief get the attribute-content of a sub-child ( a child of a child of a ...) of an xml-node

 splitter character not used as part of a child name that will be used to define in <b>path</b>
 where one name ends and the next name begins is <b>/</b>.

 @param [in] node       xml root-node to start the search in
 @param [in] path       <b>splitter</b> separated list of child-names
                        if <b>node</b> has a child named as the first list-element
                        this function will be called recursively with this child
                        as <b>node</b> and with the rest of the name-list as <b>path</b>
 @param [in] attribute  name of the attribute to read out
 @param [in] dfltReturn will be retuned if no valid xml-content exists

 @return pointer to the searched child node if found or NULL if the <b>path</b> leads
         to no valid node if more than one child with the searched name exist the first
         one will be returned.
 <br><br>
 @htmlinclude xml_Node_h_M_XMLNODE_GET_SUBCHILD_ATTRIBUTE.html
*/
#define XMLNODE_GET_SUBCHILD_ATTRIBUTE(node, path, attribute, dfltReturn) \
 node.firstGet(XML_Node::Element(XML_Search::Value,path)).attributeGet(attribute,dfltReturn)





/*!
 @ingroup XML_NODE

 @brief get the text-content of a sub-child ( a child of a child of a ...) of an xml-node

 splitter character not used as part of a child name that will be used to define in <b>path</b>
 where one name ends and the next name begins is <b>/</b>.

 @param node [in]       xml root-node to start the search in
 @param path [in]       <b>splitter</b> separated list of child-names
                        if <b>node</b> has a child named as the first list-element
                        this function will be called recursively with this child
                        as <b>node</b> and with the rest of the name-list as <b>path</b>
 @param return [out]    output of collected text

 @return collected text

 @htmlinclude  xml_Node_h_M_XMLNODE_GET_SUBCHILD_TEXT.html
*/
#define XMLNODE_GET_SUBCHILD_TEXT(node, path, return)                            \
 node.firstGet(XML_Node::Element(XML_Search::Value,path)).textCollect(return)
















#endif // XML_NODE_H





