/*!
 @file
 @brief central manager-class of parser-data and its associations

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
#ifndef XML_DATAMODEL_H
#define XML_DATAMODEL_H

#include "ASS_Model.hpp"
//#include "xml_Data.h"
#include "xml_Node.h"
#include "xml_Load.h"
#include "xml_Save.h"



/*!
 @brief central manager-class of parser-data and its associations
*/
class XML_DataModel : public AssociationModel<XML_Data, nullptr>
{
 public:

 typedef Association<XML_Data*,nullptr>                                 DataAssociation;
 typedef AssociationFellowship<XML_Data*,nullptr>                       Fellow;
// typedef AssociationSponsor<XML_Data*,nullptr>                          Sponsor;
 typedef AssociationModel<XML_Data, nullptr>::CloneData_TP              CloneData_TP;



/*!
 @brief default constructor

 @htmlinclude ./des/XML_DataModel_XML_DataModel.html
*/
  XML_DataModel(void);

/*!
 @brief initialising constructor

 @param [in] srcPath file that describes an xml-tree

 @htmlinclude ./des/XML_DataModel_XML_DataModel.html
*/
 explicit XML_DataModel(const char* srcPath);

/*!
 @brief default destructor

 @htmlinclude ./des/XML_DataModel__XML_DataModel.html
*/
  ~XML_DataModel(void);



/*!
 @brief load an xml-file

 @param [in] srcPath  name and path of source file that describes an xml-tree

 @return true as success false as failure while opening the file

 @htmlinclude ./des/XML_DataModel_load.html
*/
  bool load(const char* srcPath);


/*!
 @brief parse an xml-text

 @param [in] text  source text that describes an xml-tree
 @param [in] rootContent  text content of root-node
 <br>                     nullptr results in using the given text as content

 @return true as success false as failure while parsing the text

 @htmlinclude ./des/XML_DataModel_parse.html
*/
  bool parse(const char* text, const char* rootContent = nullptr);






/*!
 @brief store the xml-tree into a file

 @param [in] dstPath   file to store the tree in
 @param [in] childNode root of sub-tree that should be stored

 @return true as success false as failure while storing the file

 @htmlinclude ./des/XML_DataModel_save.html
*/
  bool save(const char* dstPath, XML_Node childNode = XML_Node());

/*!
 @brief return xml root-node

 @return return the root node of the xml-tree

 @htmlinclude ./des/XML_DataModel_rootNode.html
*/
  XML_Node rootNode(void);

 protected:

 private:




/*!
 @brief read a text file

 @param [in] srcPath file to read
 @return content of file

 @htmlinclude ./des/XML_DataModel_readTextFile.html
*/
 const char*  readTextFile(const char* srcPath);




};



#endif // XML_DATAMODEL_H

