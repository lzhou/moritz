/*!

 @file
 @brief transfer a grammar tree into an xml-tree

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
    16.12.2018     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    16.12.2018...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/

#ifndef SPIRIT185_XML_H
#define SPIRIT185_XML_H

#include <stdio.h>
#include <list>
#include <map>
#include "xml_DataModel.h"

#include "ASS_Visitor.hpp"
#include "TiPa_Data.h"

using namespace std;





/*!
 @brief transfer a grammar tree into an xml-tree
*/
class Spirit185_Xml:public AssociationVisitor<TiPa_Data*, nullptr>
{
 public:


 /// @brief store mode of this visitor
 typedef enum StoreMode_TP
 {
  Content2XML,                ///< @brief store the whole content as xml
  StoreMode_DF = Content2XML, ///< @brief for initialisation purposes => valid
  StoreMode_NV,               ///< @brief for initialisation purposes => not valid
 }StoreMode_TP;



///// @brief element of a string template that describes what data detail or what raw-text should be used
// typedef struct Template_TP
// {
//  int         Data   ;   ///< @brief data to insert
//  const char* RawText;   ///< @brief raw text part
// }Template_TP;


///// @brief parameter-type for @ref XmlTemplate_set and  @ref XmlRepresentation_get
//typedef enum XML_TemplateKind
//{
//  XML_StartTag = 0, ///< @brief template used to define the opening tag of the xml-representation
//  XML_Text     = 1, ///< @brief template used to define the text-content of the xml-representation
//  XML_EndTag   = 2, ///< @brief template used to define the closing tag of the xml-representation
//  XML_LeafTag  = 3, ///< @brief template used to define the tag of the xml-representation used for a leaf node
//}XML_TemplateKind;

///// @brief evaluation sequence actions not defined by user templates
//typedef enum SequenceAction
//{
//  Indent_Tag     = -1, ///< @brief normal indention
//  Indent_Text    = -2, ///< @brief additional indention
//  Indent_Child   = -3, ///< @brief normal indention and store of insert-position
//}SequenceAction;
//
/// @brief numerical ID that represents a single association-data attribute
//typedef enum DataID
//{
// DataID_NV      = -1,            ///< invalid data id
//
// Parser         =  1,            ///< parser that creates this data
// Type           =  2,            ///< parser-type id
// SubType        =  3,            ///< sub parser-type id
// UserID         =  4,            ///< user defined parser id
// Content        =  5,            ///< the detected text-part
// Line           =  6,            ///< line in the scanned text
// Column         =  7,            ///< column in the scanned text
//// UserID         =  8,            ///< id-number defined by the user
// Description    =  9,            ///< description by the user
// UserName       = 10,            ///< name given by the user
// SecondaryData  = 11,            ///< secondary data like attributes
//}DataID;



 /// @brief default definitions for data content that's user definition is invalid for xml-output
typedef struct Dflt_XML_String
 {
  const char* Tag;        ///< @brief identifying name of a tag

  struct Attribute
  {
   const char* Integer;   ///< @brief  integer value
   const char* Double;    ///< @brief  floating-point value
   const char* String;    ///< @brief  text

   /// @brief default constructor
   Attribute(void):
    Integer(nullptr),
    Double (nullptr),
    String (nullptr)
   {};

   /*!
    @brief copy constructor
    @param [in] src object to copy
   */
   Attribute(const Attribute& src):
    Integer(src.Integer),
    Double (src.Double ),
    String (src.String )
   {};
   /*!
    @brief assignment operator
    @param [in] src object to copy
    @return copied object
   */
   Attribute& operator = (const Attribute& src)
   {
    Integer = src.Integer;
    Double  = src.Double ;
    String  = src.String ;
    return(*this);
   };
   /// @brief destructor
   ~Attribute(void)
   {
   };

  }Attribute;             ///< @brief  content of undefined attributes

  const char* String;     ///< @brief  string-content of a text-node


  /// @brief default constructor
  Dflt_XML_String(void):
   Tag      (nullptr),
   Attribute(),
   String   (nullptr)
  {};

  /*!
   @brief copy constructor
   @param [in] src object to copy
  */
  Dflt_XML_String(const Dflt_XML_String& src):
   Tag      (src.Tag      ),
   Attribute(src.Attribute),
   String   (src.String   )
  {};
  /*!
   @brief assignment operator
   @param [in] src object to copy
   @return copied object
  */
  Dflt_XML_String& operator = (const Dflt_XML_String& src)
  {
   Tag       = src.Tag      ;
   Attribute = src.Attribute;
   String    = src.String   ;
   return(*this);
  };
  /// @brief destructor
  ~Dflt_XML_String(void)
  {
  };


 } Dflt_XML_String;



 typedef Association<XML_Data*, nullptr>           XML_DataAssociation;
 typedef AssociationVisitor<XML_Data*,nullptr>     XML_Visitor;
 typedef AssociationModel<XML_Data, nullptr>       XML_DataModel;

 typedef Association<TiPa_Data*, nullptr>          DataAssociation;
 typedef AssociationVisitor<TiPa_Data*,nullptr>    TiPa_Visitor;


/*!
 @brief default constructor

 <br><br>

 @htmlinclude ./des/Spirit185_Xml_Spirit185_Xml.html
*/
  Spirit185_Xml(void);


/*!
 @brief specifying constructor

 @param [in] mode         kind of search

 @htmlinclude ./des/Spirit185_Xml_Spirit185_Xml.html
*/
 explicit Spirit185_Xml(StoreMode_TP mode);



/*!
 @brief default destructor

 @htmlinclude ./des/Spirit185_Xml__Spirit185_Xml.html

*/

 virtual  ~Spirit185_Xml(void);







/*!
 @brief define key-words and key-characters to identify the content
 of leaf-nodes which should get as tag-name associated words like KeyWord or KeyChar

 @param [in] keyWords         kind of search
 @param [in] keyCharacters         representing file to store to or restore from

 @htmlinclude ./des/Spirit185_Xml_setSpcialTag.html
*/
 void setSpcialTag(set<string>* keyWords, set<string>* keyCharacters);




/* !
 @brief reset specific xml templates used while the assembly of the output-result


 @example

 Currently used:
 @code
  Template[Spirit185_Xml::XML_StartTag] = "<$UserName$ L=\"$Line$\" C=\"$Column$\" $SecondaryData$ >";
  Template[Spirit185_Xml::XML_EndTag  ] = "</$UserName$>\n";
  Template[Spirit185_Xml::XML_LeafTag ] = "<$UserName$ L=\"$Line$\" C=\"$Column$\" $SecondaryData$ />";
  Template[Spirit185_Xml::XML_Text    ] = "$Content$";
 @endcode

 Further examples:
 @code
  Template[Spirit185_Xml::XML_StartTag] = "<$ParserAttribute0$ L=\"$ParserAttribute3$\" C=\"$ParserAttribute4$\" userID=\"$ParserAttribute1$\" description=\"$ParserAttribute2$($Parser$)\" type=\"$Type$.$SubType$\">\n";
  Template[Spirit185_Xml::XML_StartTag] = "<$ParserAttribute0$ L=\"$ParserAttribute3$\" C=\"$ParserAttribute4$\">";
  Template[Spirit185_Xml::XML_EndTag  ] = "</$ParserAttribute0$>\n");
  Template[Spirit185_Xml::XML_LeafTag ] = "<$ParserAttribute0$ L=\"$ParserAttribute3$\" C=\"$ParserAttribute4$\" userID=\"$ParserAttribute1$\" description=\"$ParserAttribute2$($Parser$)\" type=\"$Type$.$SubType$\"/>\n";
  Template[Spirit185_Xml::XML_LeafTag ] = "<$ParserAttribute0$ L=\"$ParserAttribute3$\" C=\"$ParserAttribute4$\"/>";
  Template[Spirit185_Xml::XML_Text    ] = "$Content$";
  Template[Spirit185_Xml::XML_StartTag] = "<$ParserAttribute0$ L=\"$ParserAttribute3$\" C=\"$ParserAttribute4$\" userID=\"$ParserAttribute1$\" description=\"$ParserAttribute2$($Parser$)\" type=\"$Type$.$SubType$\">\n";
  Template[Spirit185_Xml::XML_LeafTag ] = "<$UserName$ L=\"$Line$\" C=\"$Column$\" userID=\"$UserID$\" description=\"$Description$($Parser$)\" type=\"$Type$.$SubType$\"/>\n";
 @endcode

 Place-holder words written between <b>$<b/> characters will be evaluated by the method @ref Spirit185_Xml::dataID_get
 to prepare their replacement by data-content. Please refer the documentation of this method to learn about the current
 meaning of the different place-holders.

 @param [in] templateID   identifier of the template to modify
 @param [in] newContent   new content of template

 @htmlinclude ./des/Spirit185_Xml_xmlTemplate_set.html
 void xmlTemplate_set(XML_TemplateKind templateID, const char* newContent);
*/







/*!
 @brief initialize this visitor

 @param [in] mode         kind of search
 @param [in] text         location to store to

 @htmlinclude ./des/Spirit185_Xml_init.html
*/
 void init(StoreMode_TP mode);



/*!
 @brief define the context-model

 @param [in] contextModel management-object that creates and deletes associations and data-objects

 @htmlinclude ./des/Spirit185_Xml_contextModel_set.html

*/
void contextModel_set(XML_DataModel* contextModel);




/*!
 @brief initialize this visitor

 @param [in] mode         kind of search
 @param [in] destination  location to store to

 @return pointer to initialized class-object

 @htmlinclude ./des/Spirit185_Xml_operator().html
*/
 Spirit185_Xml* operator()(StoreMode_TP mode, XML_Node* destination);



// @param sponsor the sponsor of the association to analyse

/*!
 @brief start to evaluate an association

 @param node    the association to analyse


 @htmlinclude ./des/Spirit185_Xml_evaluate.html

*/
DirectionOfIteration evaluate(DataAssociation* node/*, DataAssociation* sponsor*/);











 protected:

 private:

// @param sponsor the sponsor of the association to analyse

/*!
 @brief evaluate an association and its contractors to store the content in an xml-file

 @param node    the association to analyse


 @htmlinclude ./des/Spirit185_Xml_evaluateXML.html

*/
DirectionOfIteration evaluateXML(DataAssociation* node/*, DataAssociation* sponsor*/);













 XML_DataAssociation* createElementXML(DataAssociation* node);

 XML_DataAssociation* createTextXML(DataAssociation* node);











 /// @brief default definitions for data content that's user definition is invalid for xml-output
 static Dflt_XML_String DfltXML ;







 /// @brief common object attributes
 struct Att
 {
  StoreMode_TP                     Mode;               ///< @brief mode of search and evaluation

  DirectionOfIteration             CommonDirection;    ///< @brief stores the direction to iterate while temporary changes
  list<XML_DataAssociation*>       ParentNode;         ///< @brief current position to insert a line into
                                                       ///< the output-tree

  XML_DataAssociation*             DestinationRoot;    ///< @brief root of association tree with the data to analyse
  XML_DataAssociation*             NewAssociation;     ///< @brief root of new association tree

  DataAssociation*                 RootAssociation;    ///< @brief first association that is visited
                                                       ///<        while one evaluation-process

  set<string>*                     KeyWords;           ///< @brief special text-content where the tag \< KeyWrd \> should be used
  set<string>*                     KeyCharacters;      ///< @brief special text-content where the tag \< KeyChr \> should be used

  XML_DataModel*                   ContextModel;       ///< @brief manages the data to create




  /// @brief default constructor
  Att(void):
   Mode           (Content2XML    ),
   CommonDirection(IterateAsBefore),
   DestinationRoot(nullptr        ),
   NewAssociation (nullptr        ),
   RootAssociation(nullptr        ),
   KeyWords       (nullptr        ),
   KeyCharacters  (nullptr        ),
   ContextModel   (nullptr        )
 {};

  /*!
   @brief copy constructor
   @param [in] src object to copy
  */
  Att(const Att& src):
   Mode           (src.Mode           ),
   CommonDirection(src.CommonDirection),
   ParentNode     (src.ParentNode     ),
   DestinationRoot(src.DestinationRoot),
   NewAssociation (src.NewAssociation ),
   RootAssociation(src.RootAssociation),
   KeyWords       (src.KeyWords       ),
   KeyCharacters  (src.KeyCharacters  ),
   ContextModel   (src.ContextModel   )
  {};

  /*!
   @brief assignment operator
   @param [in] src object to copy
   @return copied object
  */
  Att& operator = (const Att& src)
  {
   Mode            = src.Mode           ;
   CommonDirection = src.CommonDirection;
   ParentNode      = src.ParentNode     ;
   DestinationRoot = src.DestinationRoot;
   NewAssociation  = src.NewAssociation ;
   RootAssociation = src.RootAssociation;
   KeyWords        = src.KeyWords       ;
   KeyCharacters   = src.KeyCharacters  ;
   ContextModel    = src.ContextModel   ;
   return(*this);
  };

  /// @brief destructor
  ~Att(void)
  {
   ParentNode   .clear();
  };

 }Att;


};





#endif // SPIRIT185_XML_H

