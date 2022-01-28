/*!
 @file
 @brief concrete association visitor to find replacements in xml-data that should
        be expanded

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
    29.12.2018     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    29.12.2018...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/
#ifndef XML_REPLACE_H
 #define XML_REPLACE_H


#include "ASS_Visitor.hpp"
#include "xml_Data.h"
#include "xml_Node.h"
#include "xml_Replace_Grm.h"
#include "TiPa_Search.h"


/*!
 @brief concrete association visitor to store an xml-tree in a file
*/
class XML_Replace:public AssociationVisitor<XML_Data*, nullptr>
{
 public:
  typedef XML_Node::DataAssociation DataAssociation;
  typedef XML_Node::XML_Visitor     XML_Visitor;
//  typedef XML_Node::DataFellow      DataFellow;

/*!
 @brief default constructor

 @htmlinclude ./des/XML_Replace_XML_Replace.html
*/
   XML_Replace(void);


/*!
 @brief copy constructor

 @param [in] visitor object to copy

 @htmlinclude ./des/XML_Replace_XML_Replace.html
*/
   XML_Replace(const XML_Replace& visitor);




/*!
 @brief destructor

 @htmlinclude ./des/XML_Replace__XML_Replace.html
*/
  ~XML_Replace(void);





/*!
  @brief assignment operator

  @param [in] visitor object to assign

*/
XML_Replace& operator= (const XML_Replace& visitor);








/*!
 @brief initialize this visitor

 @param [in] context     xml-model used while operation

 @return pointer to initialized class-object

 @htmlinclude "./des/XML_Replace_operator().html"
*/
 XML_Replace* operator()(XML_Node::DataModel* context);











 /*!
 @brief start to evaluate a association

 @param node    the association to analyse

 @return direction of next iteration step

 @htmlinclude ./des/XML_Replace_evaluate.html
*/
DirectionOfIteration evaluate(DataAssociation* node);


 protected:

 private:



/*!
 @brief evaluate an association and its contractors to store the content in an xml-file

 @param node    the association to analyse


 @htmlinclude ./des/XML_Replace_evaluateXML.html

*/
DirectionOfIteration evaluateXML(DataAssociation* node);




/*!
 @brief initialize this visitor


 @htmlinclude ./des/XML_Replace_init.html
*/
 void init(void);





/*!
 @brief process replacement in xml-attributes

 @param [in] node        xml-element that contains the attributes

 @htmlinclude ./des/XML_Replace_replaceInAttributes.html
*/
 void replaceInAttributes(DataAssociation* node);



/*!
 @brief process replacement in xml text child-nodes

 @param [in] node        xml-element that contains the text child-nodes


 @htmlinclude ./des/XML_Replace_replaceInText.html
*/
 void replaceInText(DataAssociation* node);



/*!
 @brief exchange replacements by other texts located somewhere in the xml-tree

 @param [out] returnValue    pointer to the expanded text.
 @param [in]  text           text to expand
 @param [in]  currentNode    xml-node where all xml-path definitions should be relative to

 @htmlinclude ./des/XML_Replace_replaceDetails.html
*/
 void replaceDetails(char** returnValue, const char* text, XML_Node currentNode);


/*!
 @brief parse the given text

 @param text            [in]  text to analyse
 @param replaceContext  [in]  context-model that supports the parsing-process

 @return root of parser-tree reduced to rule-nodes

 @htmlinclude ./des/XML_Replace_parseText.html
*/
TiPa_Concrete::DataAssociation* parseText(const char* text, TiPa_Concrete::DataModel* replaceContext);









/*!
 @brief get a container of all replacement parts

 @param [out] returnValue           pointer to the container to fill.

 @param [in]  replacementDefinition parser-node that contains the replacement information
 @param [in]  currentNode           xml-node where all xml-path definitions should be relative to

 @return number of characters of all new new text parts

 @htmlinclude ./des/XML_Replace_collectNewTextParts.html
*/
unsigned int collectNewTextParts(list<const char*>*              returnValue,
                                 TiPa_Concrete::DataAssociation* replacementDefinition,
                                 XML_Node                        currentNode);



/*!
 @brief assemble all replacement parts as new text

 @param [out] returnValue           pointer to the text fill.

 @param [in]  replacementDefinition container of new text parts
 @param [in]  newSize               size of the new text

 @return number of characters of all new new text parts

 @htmlinclude ./des/XML_Replace_collectNewTextParts.html
*/
void assembleNewTextParts(char**              returnValue,
                          list<const char*>*  replacementDefinition,
                          unsigned int        newSize);





/*!
 @brief get single replacement

 @param [out] returnValue           pointer to the replacement text to create.

 @param [in]  replacementDefinition parser-node that contains the replacement information
 @param [in]  currentNode           xml-node where all xml-path definitions should be relative to

 @htmlinclude ./des/XML_Replace_replacementGet.html
*/
void replacementGet(char** returnValue, TiPa_Concrete::DataAssociation* replacementDefinition, XML_Node currentNode);


/*!
 @brief get xml-node that contains the data to replace with

 @param [in]  searchDefinition parser-node that defines the xml node to search
 @param [in]  currentNode      xml-node where all xml-path definitions should be relative to

 @return xml-node that contains the data to replace with

 @htmlinclude ./des/XML_Replace_dataNodeGet.html
*/
XML_Node dataNodeGet(TiPa_Concrete::DataAssociation* searchDefinition, XML_Node currentNode);



/*!
 @brief search xml-node in xml-tree

 @param [in]  pathXML          parser-node that defines the relative or absolute path in  the given xml-tree
 @param [in]  currentNode      xml-node where all xml-path definitions should be relative to

 @return xml-node that contains the data to replace with

 @htmlinclude ./des/XML_Replace_dataNodeGet.html
*/
XML_Node dataNodeSearch(TiPa_Concrete::DataAssociation* pathXML, XML_Node currentNode);


/*!
 @brief jump to root if path is absolute

 @param [in]  pathXML          parser-node that defines the relative or absolute path in  the given xml-tree
 @param [in]  currentNode      xml-node where all xml-path definitions should be relative to

 @return given node if path is relative or its tree rot if path is absolute

 @htmlinclude ./des/XML_Replace_startNodeGet.html
*/
XML_Node startNodeGet(TiPa_Concrete::DataAssociation* pathXML, XML_Node currentNode);


/*!
 @brief follow the given xml-path and return data node

 @param [in]  pathXML        parser-node that defines the relative or absolute path in  the given xml-tree
 @param [in]  startNode      xml-node used to start process

 @return last node of path as parent node for the node to search for

 @htmlinclude ./des/XML_Replace_dataPathFollow.html
*/
XML_Node dataPathFollow(TiPa_Concrete::DataAssociation* pathXML, XML_Node startNode);


/*!
 @brief return searched node at the end of the path

 @param [in]  pathXML        parser-node that defines the relative or absolute path in  the given xml-tree
 @param [in]  parentNode     xml parent node of searched leaf

 @return found node or empty node if xml path is not valid

 @htmlinclude ./des/XML_Replace_startNodeGet.html
*/
XML_Node leafNodeGet(TiPa_Concrete::DataAssociation* pathXML, XML_Node parentNode);





/*!
 @brief get xml-data to replace with

 @param [out] returnValue    pointer to the replacement text to create.

 @param [in]  dataDefinition parser-node that defines the xml-property used to define the text to replace with
 @param [in]  dataNode       xml-node that contains the data to replace with

 @htmlinclude ./des/XML_Replace_dataContentGet.html
*/
void dataContentGet(char** returnValue, TiPa_Concrete::DataAssociation* dataDefinition, XML_Node dataNode);





/*!
 @brief get xml-text content to replace with

 @param [out] returnValue    pointer to the replacement text to create.

 @param [in]  dataNode       xml-node that contains the data to replace with

 @htmlinclude ./des/XML_Replace_dataContentGet.html
*/
void dataTextGet(char** returnValue, XML_Node dataNode);





/*!
 @brief get xml-attribute content to replace with

 @param [out] returnValue    pointer to the replacement text to create.

 @param [in]  attributeName  name of the attribute that contains text to replace with
 @param [in]  dataNode       xml-node that contains the data to replace with

 @htmlinclude ./des/XML_Replace_dataContentGet.html
*/
void dataAttributeGet(char** returnValue, const char* attributeName, XML_Node dataNode);




/// @brief common object attributes
 struct Att
 {
  DirectionOfIteration                     CommonDirection{IterateAsBefore}; ///< @brief stores the direction to iterate while temporary changes
  DataAssociation*                         RootAssociation{nullptr};         ///< @brief first association that is visited while one evaluation-process
  XML_Node::DataModel*                     Context{nullptr};                 ///< @brief xml data model

  TiPa_Search                              Search;                           ///< @brief search for details in definition parser-tree

  Att(void):
      CommonDirection(IterateAsBefore),
      RootAssociation(nullptr),
      Context(nullptr),
      Search()
      {};

  Att(const Att& att):
      CommonDirection(att.CommonDirection),
      RootAssociation(att.RootAssociation),
      Context(att.Context),
      Search(att.Search)
      {};

  Att& operator=(const Att& att){CommonDirection = att.CommonDirection;
                                 RootAssociation = att.RootAssociation;
                                 Context         = att.Context;
                                 Search          = att.Search;
                                 return(*this);
                                };
 }Att;                                                                       ///< @brief initialisation
};



#endif // XML_REPLACE_H


