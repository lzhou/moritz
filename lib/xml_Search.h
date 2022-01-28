/*!

 @file
 @brief search for an xml node with a specific name and or tree-path

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
    01.05.2018     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    01.05.2018...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/

#ifndef XML_SEARCH_H
#define XML_SEARCH_H

#include <stdio.h>

#include "ASS_Visitor.hpp"
#include "xml_Data.h"

using namespace std;





/*!
 @brief concrete visitor to search for a tree-node defined by an index-path
*/
class XML_Search:public AssociationVisitor<XML_Data*,nullptr>
{
 public:


 /// search mode of this visitor
 typedef enum SearchMode_TP
 {
  Index,                    ///< evaluate the position inside a fellow-ship chain
  Type,                     ///< evaluate the xml-node type
  Value,                    ///< evaluate the parser-name given by the user
//  UserID,                  ///< evaluate the parser id-number given by the user
//  Content,                 ///< evaluate the string between Begin and End
  SearchMode_DF = Value,    ///< for initialisation purposes => valid
  SearchMode_NV,            ///< for initialisation purposes => not valid
 }SearchMode_TP;


 typedef Association<XML_Data*, nullptr>        DataAssociation;
 typedef AssociationVisitor<XML_Data*, nullptr> XML_Visitor;



/*!
 @brief default constructor

 <br><br>

 @htmlinclude ./des/XML_Search_XML_Search.html
*/
  XML_Search(void);



/*!
 @brief xml-node type specifying constructor

 @param [in] nodeType     node-type to search

 @htmlinclude ./des/XML_Search_XML_Search_1.html
*/
 explicit XML_Search(XML_Data::NodeType_TP nodeType);



/*!
 @brief all details specifying constructor

 @param [in] mode         kind of search
 @param [in] nodeType     node-type to search
 @param [in] path         filter data used to evaluate the data
 @param [in] separator    character used to split between the names in the
                          given type-path
 @param [in] indexStart   to initialize the call counter with the fellowship-index
                          of current association


 @htmlinclude ./des/XML_Search_XML_Search_2.html
*/
  XML_Search(SearchMode_TP mode, XML_Data::NodeType_TP nodeType, const char* path, char separator ='/', int indexStart = 0);

/*!
 @brief default destructor



 @htmlinclude ./des/XML_Search__XML_Search.html

*/

 virtual  ~XML_Search(void);



/*!
 @brief initialize this visitor

 @param [in] mode         kind of search
 @param [in] path         filter data used to evaluate the data
 @param [in] separator    character used to split between the names in the
                          given type-path
 @param [in] indexStart   to initialize the call counter with the fellowship-index
                          of current association

 @htmlinclude ./des/XML_Search_init.html
*/
 void init(SearchMode_TP mode, const char* path, char separator ='/', int indexStart = 0);







/*!
 @brief initialize this visitor

 @param [in] mode         kind of search
 @param [in] path         filter data used to evaluate the data
 @param [in] separator    character used to split between the names in the
                          given type-path
 @param [in] indexStart   to initialize the call counter with the fellowship-index
                          of current association

 @return pointer to initialized class-object

 @htmlinclude "./des/XML_Search_operator().html"
*/
 XML_Search* operator()(SearchMode_TP mode=Type, const char* path =XML_Search::IgnoreValue, char separator ='/', int indexStart = 0);










/*!
 @brief reinitialize the call-counter

 @param [in] indexStart   to initialize the call counter with the fellowship-index
                          of current association

 @htmlinclude ./des/XML_Search_setCallCounter.html
*/
 void setCallCounter(int indexStart);









// @param sponsor the sponsor of the association to analyse

/*!
 @brief start to evaluate an association

 @param node    the association to analyse


 @htmlinclude ./des/XML_Search_evaluate.html

*/
DirectionOfIteration evaluate(DataAssociation* node/*, DataAssociation* sponsor*/);



static const char* IgnoreValue; ///< @brief  default string used if no value associated search should be done


 protected:

 private:


/*!
 @brief implements details of index evaluation

 @param [in] node the tree-node to analyse
 @param [in] word reference-value to search for

 @return true  if node hits search criteria
 <br>    false if not

 @htmlinclude ./des/XML_Search_evaluateIndex.html
*/
 bool evaluateIndex(DataAssociation* node, const char* word);

/*!
 @brief implements details of xml-node type evaluation

 @param [in] node the tree-node to analyse

 @return true  if node hits search criteria
 <br>    false if not

 @htmlinclude ./des/XML_Search_evaluateType.html
*/
bool evaluateType(DataAssociation* node);



/*!
 @brief implements details of user-name evaluation

 @param [in] node the tree-node to analyse
 @param [in] word reference-value to search for

 @return true  if node hits search criteria
 <br>    false if not

 @htmlinclude ./des/XML_Search_evaluateValue.html
*/
 bool evaluateValue(DataAssociation* node, const char* word);




/* !
 @brief implements details of user id evaluation

 @param [in] node the tree-node to analyse
 @param [in] word reference-value to search for

 @return true  if node hits search criteria
 <br>    false if not

 @htmlinclude XML_Search_welcome.html
bool evaluateUserID(DataAssociation* node, const char* word);
*/











 struct Att
 {
  SearchMode_TP               Mode;            ///< @brief mode of search and evaluation
  XML_Data::NodeType_TP       NodeType;        ///< @brief node-type to search
  list<const char*>           Path;            ///< @brief reference data used for content-search
  list<const char*>::iterator Word;            ///< @brief current part of the path
  DirectionOfIteration        CommonDirection; ///< @brief stores the direction to iterate while temporary changes
  int                         CallCounter;     ///< @brief counts how many times the evaluation was called,

  /// @brief default constructor
  Att(void):
      Mode(SearchMode_DF),
      NodeType(XML_Data::NT_Undefined),
      Path(),
      Word(),
      CommonDirection(IterateAsBefore),
      CallCounter(0)
      {};
  /*!
   @brief copy constructor
   @param [in] src object to copy
  */
  Att(const Att& src):
   Mode           (src.Mode           ),
   NodeType       (src.NodeType       ),
   Path           (src.Path           ),
   Word           (src.Word           ),
   CommonDirection(src.CommonDirection),
   CallCounter    (src.CallCounter    )
  {};
  /*!
   @brief assignment operator
   @param [in] src object to copy
   @return copied object
  */
  Att& operator = (const Att& src)
  {
   Mode            = src.Mode           ;
   NodeType        = src.NodeType       ;
   Path            = src.Path           ;
   Word            = src.Word           ;
   CommonDirection = src.CommonDirection;
   CallCounter     = src.CallCounter    ;
   return(*this);
  };
  /// @brief destructor
  ~Att(void)
  {
   Path.clear();
  };
                                               ///< will be used for index evaluation
 }Att;


};





#endif // XML_SEARCH_H

