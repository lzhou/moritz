/*!

 @file
 @brief concrete manager of attributes and text-data of an xml-node

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
    18.11.2017     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    18.11.2017...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/

#ifndef XML_DATA_H
#define XML_DATA_H

#include "ASS_Data.h"



using namespace std;




/*!
 concrete manager of attributes and text-data of an xml-node

 this class describes the concrete data content of an xml-node
 but not its child-nodes
*/
class XML_Data:public AssociationData
{

 public:

/// @brief type of xml-node that contains the xml-data
  typedef enum NodeType_TP
  {
   NT_Undefined,     ///< @brief type not known
   NT_Document,      ///< @brief xml-file
   NT_Element,       ///< @brief xml-node that may contain attributes, and/or sub-nodes
   NT_Text,          ///< @brief xml-node that contains text-information
//   NT_Reference,     ///< @brief xml-node that contains referencing text-information
   NT_Comment,       ///< @brief xml-node used as comment
   NT_Declaration,   ///< @brief xml-node used as declaration for a standard xml-tool
  }NodeType_TP;


/// @brief type of  xml-data used for example by textual representation
  typedef enum Detail_TP
  {
   UnKnown   = -1,  ///< @brief  invalid xml-data request
   NodeType  =  1,  ///< @brief  type of xml-node as defined in @ref XML_Data::NodeType_TP
   Content   =  2,  ///< @brief  value-content depends on node-type
   Attribute =  3,  ///< @brief  xml-attribute
//   Raw       =  4,  ///< @brief  raw value-content of text-node with that already contains valid xml-definitions of special characters
  }Detail_TP;




/*!
 @brief default constructor

 @htmlinclude ./des/XML_Data_XML_Data.html
*/
  XML_Data(void);




/*!
 @brief copy constructor

 @param [in] data object to copy

 @htmlinclude ./des/XML_Data_XML_Data.html
*/
 explicit XML_Data(XML_Data& data);



/*!
 @brief destructor

 @htmlinclude ./des/XML_Data__XML_Data.html
*/
  ~XML_Data(void);





/*!
  @brief assignment operator

  @param [in] data object to assign

*/
XML_Data& operator= ( XML_Data& data);






/*!
 @brief check if data-pointer points to primary-data declared by concrete class

 If the concrete class implements string-pointers it may be that this strings have to be stored
 as secondary data even they are actually primary data. Once the data should be used this
 method could be used to differ between real secondary data and data that is already known by
 the concrete class.

 @param [in] data data-pointer to check

 @return false if given data is no primary data just stored as secondary data
 <br>    true if given data is not used with a primary pointer of the concrete class

 <br><br>
 @htmlinclude ./des/XML_Data_isRealSecondaryData.html
*/
 virtual  bool isRealSecondaryData(const char* data) override;


/*!
 @brief define type of xml-node that contains the xml-data

 @param [in] type node-type

 @htmlinclude ./des/XML_Data_typeSet.html
*/
  void typeSet(XML_Data::NodeType_TP type);


/*!
 @brief return type of xml-node that contains the xml-data

 @return node-type

 @htmlinclude ./des/XML_Data_typeGet.html
*/
  XML_Data::NodeType_TP typeGet(void) ;



/*!
 @brief define value content

 @param value value-content

 @htmlinclude ./des/XML_Data_valueSet.html
*/
  void valueSet(const char* value);


/*!
 @brief return value content

 @return value-content or nullptr if no value-content is defined

 @htmlinclude ./des/XML_Data_valueGet.html
*/
  const char* valueGet(void) ;






/*!
 @brief add an text attribute

 @param [in] key  name of the attribute
 @param [in] data text used to represent the data

 @return added data as new string (stored and maintained as secondary data)

 <br><br>
 @htmlinclude ./des/XML_Data_attributeSet.html
*/
  const char* attributeSet(const char* key, const char* data);


/*!
 @brief add an integer attribute

 @param [in] key  name of the attribute
 @param [in] data text used to represent the data

 @return added data as new string (stored and maintained as secondary data)

 <br><br>
 @htmlinclude ./des/XML_Data_attributeSet.html
*/
  const char* attributeSet(const char* key, int data);

/*!
 @brief add a double attribute

 @param [in] key  name of the attribute
 @param [in] data text used to represent the data

 @return added data as new string (stored and maintained as secondary data)

 <br><br>
 @htmlinclude ./des/XML_Data_attributeSet.html
*/
  const char* attributeSet(const char* key, double data);



/*!
 @brief return an attribute value as text

 @param [in] key         name of the attribute
 @param [in] defaultData return value used if the searched data is not existing or not convertible

 @return text used to represent the data

 <br><br>
 @htmlinclude ./des/XML_Data_attributeGet.html
*/
  const char* attributeGet(const char* key, const char* defaultData = "");


/*!
 @brief return an attribute value as integer value

 @param [in] key         name of the attribute
 @param [in] defaultData return value used if the searched data is not existing or not convertible

 @return numerical content if data could be transferred into an integer number
 <br>    given default value if the searched data is not existing or not convertible

 <br><br>
 @htmlinclude ./des/XML_Data_attributeGet.html
*/
  int attributeGet(const char* key, int defaultData );


/*!
 @brief return an attribute value as double value

 @param [in] key         name of the attribute
 @param [in] defaultData return value used if the searched data is not existing or not convertible

 @return numerical content if data could be transferred into an integer number
 <br>    given default value if the searched data is not existing or not convertible

 <br><br>
 @htmlinclude ./des/XML_Data_attributeGet.html
*/
  double attributeGet(const char* key, double defaultData);





 protected:

 private:

/// @brief type of xml-node that contains the xml-data
  XML_Data::NodeType_TP Type{XML_Data::NT_Undefined};

/// @brief value of node what depends on node type
///
/// @li name of node if node is an element or declaration
/// @li text content if node is a text-node or comment
/// @li path and name of source file if node is a document
  char* Value{nullptr} ;

};

#endif //XML_DATA_H
