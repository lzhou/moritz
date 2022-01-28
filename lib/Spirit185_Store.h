/*!

 @file
 @brief concrete visitor to search for a tree-node defined by an index-path

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
    16.12.2015     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    16.12.2015...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/

#ifndef SPIRIT185_STORE_H
#define SPIRIT185_STORE_H

#include <stdio.h>
#include <list>
#include <map>
//#include "Association.h"
//#include "ASS_Data.h"
#include "ASS_Visitor.hpp"
#include "TiPa_Data.h"

using namespace std;


#ifndef DOXYGEN
//namespace TXTDIASM {
//namespace TDA_TinyParser {
//namespace DATA {
#endif //DOXYGEN

//#define IGNORE_UNUSED __attribute__ ((unused))

/// @ingroup UNUSED_DATA
/// @brief avoid compiler warning since the object is not used
/// @{
#define DATA_ASSOCIATION_UNUSED __attribute__ ((unused)) DataAssociation
/// @}


/*!
 @brief concrete visitor to search for a tree-node defined by an index-path
*/
class Spirit185_Store:public AssociationVisitor<TiPa_Data*,nullptr>
{
 public:


 /// @brief store mode of this visitor
 typedef enum StoreMode_TP
 {
  Content2XML,                ///< @brief store the whole content as xml
  Content2Text,               ///< @brief store the whole content as raw-text
//  XML2Content,                ///< restore the whole content from xml
  StoreMode_DF = Content2XML, ///< @brief for initialisation purposes => valid
  StoreMode_NV,               ///< @brief for initialisation purposes => not valid
 }StoreMode_TP;



/// @brief element of a string template that describes what data detail or what raw-text should be used
 typedef struct Template_TP
 {
  int         Data   ;   ///< @brief data to insert
  const char* RawText;   ///< @brief raw text part


  /// @brief default constructor
  Template_TP(void):
   Data   (0),
   RawText(nullptr)
  {};

  /*!
   @brief copy constructor
   @param [in] src object to copy
  */
  Template_TP(const Template_TP& src):
   Data   (src.Data   ),
   RawText(src.RawText)
  {};
  /*!
   @brief assignment operator
   @param [in] src object to copy
   @return copied object
  */
  Template_TP& operator = (const Template_TP& src)
  {
   Data    = src.Data   ;
   RawText = src.RawText;
   return(*this);
  };
  /// @brief destructor
  ~Template_TP(void)
  {
  };


 }Template_TP;


/// @brief index-type for array @ref Att::Template and parameter-type for @ref xmlTemplate_set
typedef enum XML_TemplateKind
{
  XML_StartTag = 0, ///< @brief template used to define the opening tag of the xml-representation
  XML_Text     = 1, ///< @brief template used to define the text-content of the xml-representation
  XML_EndTag   = 2, ///< @brief template used to define the closing tag of the xml-representation
  XML_LeafTag  = 3, ///< @brief template used to define the tag of the xml-representation used for a leaf node
}XML_TemplateKind;

/// @brief evaluation sequence actions not defined by user templates
typedef enum SequenceAction
{
  Indent_Tag     = -1, ///< @brief normal indention
  Indent_Text    = -2, ///< @brief additional indention
  Indent_Child   = -3, ///< @brief normal indention and store of insert-position
}SequenceAction;

/// @brief numerical ID that represents a single association-data attribute
typedef enum DataID
{
 DataID_NV      = -1,            ///< invalid data id

 Parser         =  1,            ///< parser that creates this data
 Type           =  2,            ///< parser-type id
 SubType        =  3,            ///< sub parser-type id
 UserID         =  4,            ///< user defined parser id
 Content        =  5,            ///< the detected text-part
 Line           =  6,            ///< line in the scanned text
 Column         =  7,            ///< column in the scanned text
 Description    =  9,            ///< description by the user
 UserName       = 10,            ///< name given by the user
 SecondaryData  = 11,            ///< secondary data like attributes
}DataID;



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


 typedef AssociationVisitor<TiPa_Data*,nullptr>  TiPa_Visitor;
 typedef Association<TiPa_Data*, nullptr>        DataAssociation;




/*!
 @brief default constructor

 <br><br>

 @htmlinclude ./des/Spirit185_Store_Spirit185_Store.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    16.12.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  Spirit185_Store(void);


/*!
 @brief specifying constructor

 @param [in] mode         kind of search
 @param [in] text         location to store to


 @htmlinclude ./des/Spirit185_Store_Spirit185_Store.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    16.12.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  Spirit185_Store(StoreMode_TP mode, char** text);

/*!
 @brief default destructor

 @htmlinclude ./des/Spirit185_Store__Spirit185_Store.html

 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    16.12.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/

 virtual  ~Spirit185_Store(void);







/*!
 @brief define key-words and key-characters to identify the content
 of leaf-nodes which should get as tag-name associated words like KeyWord or KeyChar

 @param [in] keyWords         kind of search
 @param [in] keyCharacters         representing file to store to or restore from

 @htmlinclude ./des/Spirit185_Store_setSpcialTag.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
   17.12.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void setSpcialTag(set<string>* keyWords, set<string>* keyCharacters);




/*!
 @brief reset specific xml templates used while the assembly of the output-result


 @example

 Currently used:
 @code
  Template[Spirit185_Store::XML_StartTag] = "<$UserName$ L=\"$Line$\" C=\"$Column$\" $SecondaryData$ >";
  Template[Spirit185_Store::XML_EndTag  ] = "</$UserName$>\n";
  Template[Spirit185_Store::XML_LeafTag ] = "<$UserName$ L=\"$Line$\" C=\"$Column$\" $SecondaryData$ />";
  Template[Spirit185_Store::XML_Text    ] = "$Content$";
 @endcode

 Further examples:
 @code
  Template[Spirit185_Store::XML_StartTag] = "<$ParserAttribute0$ L=\"$ParserAttribute3$\" C=\"$ParserAttribute4$\" userID=\"$ParserAttribute1$\" description=\"$ParserAttribute2$($Parser$)\" type=\"$Type$.$SubType$\">\n";
  Template[Spirit185_Store::XML_StartTag] = "<$ParserAttribute0$ L=\"$ParserAttribute3$\" C=\"$ParserAttribute4$\">";
  Template[Spirit185_Store::XML_EndTag  ] = "</$ParserAttribute0$>\n");
  Template[Spirit185_Store::XML_LeafTag ] = "<$ParserAttribute0$ L=\"$ParserAttribute3$\" C=\"$ParserAttribute4$\" userID=\"$ParserAttribute1$\" description=\"$ParserAttribute2$($Parser$)\" type=\"$Type$.$SubType$\"/>\n";
  Template[Spirit185_Store::XML_LeafTag ] = "<$ParserAttribute0$ L=\"$ParserAttribute3$\" C=\"$ParserAttribute4$\"/>";
  Template[Spirit185_Store::XML_Text    ] = "$Content$";
  Template[Spirit185_Store::XML_StartTag] = "<$ParserAttribute0$ L=\"$ParserAttribute3$\" C=\"$ParserAttribute4$\" userID=\"$ParserAttribute1$\" description=\"$ParserAttribute2$($Parser$)\" type=\"$Type$.$SubType$\">\n";
  Template[Spirit185_Store::XML_LeafTag ] = "<$UserName$ L=\"$Line$\" C=\"$Column$\" userID=\"$UserID$\" description=\"$Description$($Parser$)\" type=\"$Type$.$SubType$\"/>\n";
 @endcode

 Place-holder words written between <b>$</b> characters will be evaluated by the method @ref Spirit185_Store::dataID_get
 to prepare their replacement by data-content. Please refer the documentation of this method to learn about the current
 meaning of the different place-holders.

 @param [in] templateID   identifier of the template to modify
 @param [in] newContent   new content of template

 @htmlinclude ./des/Spirit185_Store_xmlTemplate_set.html

 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    20.05.2017   @I  Eckard Klotz
 @I extending the diversity of use
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void xmlTemplate_set(XML_TemplateKind templateID, const char* newContent);







/*!
 @brief initialize this visitor

 @param [in] mode         kind of search
 @param [in] text         location to store to

 @htmlinclude ./des/Spirit185_Store_init.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    16.12.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void init(StoreMode_TP mode, char** text);







/*!
 @brief initialize this visitor

 @param [in] mode         kind of search
 @param [in] text         location to store to

 @return pointer to initialized class-object

 @htmlinclude "./des/Spirit185_Store_operator().html"
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    16.12.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 Spirit185_Store* operator()(StoreMode_TP mode, char** text);



// @param sponsor the sponsor of the association to analyse

/*!
 @brief start to evaluate an association

 @param node    the association to analyse


 @htmlinclude ./des/Spirit185_Store_evaluate.html

 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    16.12.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
DirectionOfIteration evaluate(DataAssociation* node/*, DataAssociation* sponsor*/);











 protected:

 private:


/*!
 @brief evaluate an association and its contractors to store the content in an xml-file

 @param node    the association to analyse


 @htmlinclude ./des/Spirit185_Store_evaluateXML.html

 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    16.12.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
DirectionOfIteration evaluateXML(DataAssociation* node);


/*!
 @brief evaluate an association and its contractors to store the content in a text-file

 @param node    the association to analyse


 @htmlinclude ./des/Spirit185_Store_evaluateText.html

 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    16.12.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
DirectionOfIteration evaluateText(DATA_ASSOCIATION_UNUSED* node);







/*!
 @brief define a template of a string used to represent
        all or some association-data attributes


 @param [in]  text       template definition
 @param [in]  separator  separates the data replacements from the
              raw-text sections in the given text



 @htmlinclude ./des/Spirit185_Store_stringTemplate.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    17.12.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
list<Template_TP* >* stringTemplate(const char* text, char separator='$');


/*!
 @brief get a string-representation of a single node

 @param [in]  data          data to analyse
 @param [in]  textTemplate  describes the design of the output-text
 @param [out] text          template definition



 @htmlinclude ./des/Spirit185_Store_stringRepresentation.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    17.12.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
void stringRepresentation(TiPa_Data* data, list<Template_TP* >* textTemplate, char** text);



 /*!
 @brief return a numerical ID that represents a single association-data attribute,
        used by @ref stringTemplate

 @param [in]  text potential name of association-data attribute
 @return      a value >=0 that is a valid identifier of an existing attribute
 <br>         or -1 if the given text is not a name of an existing attribute

 @htmlinclude ./des/Spirit185_Store_dataID_get.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    17.12.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 int dataID_get(const char* text);













 /// @brief default definitions for data content that's user definition is invalid for xml-output
 static Dflt_XML_String DfltXML ;







 /// @brief common object attributes
 struct Att
 {
  StoreMode_TP                             Mode{Content2XML};                ///< @brief mode of search and evaluation

  char**                                   Text{nullptr};                    ///< @brief location to store to

  DirectionOfIteration                     CommonDirection{IterateAsBefore}; ///< @brief stores the direction to iterate while temporary changes
  map<int,list<Template_TP* > *>           Template{};                       ///< @brief container of string-templates used to represent
                                                                             ///         all or some association-data attributes
  list<const char*>                        OutputText{};                     ///< @brief sequence of strings that represents all nodes of an
                                                                             ///<        evaluated association tree
  int                                      Indention;                        ///< @brief number of spaces to insert at the line begin
                                                                             ///<        to have a nice looking text
  list<list<const char*>::iterator>        InsertPosition{};                 ///< @brief current position to insert a line into
                                                                             ///<        the output-text
  DataAssociation*                         RootAssociation{nullptr};         ///< @brief first association that is visited
                                                                             ///<        while one evaluation-process
  list<int>                                EvaluationSequence{};             ///< @brief defines the construction of the text while the evaluation process

  set<string>*                             KeyWords{nullptr};
  set<string>*                             KeyCharacters{nullptr};

  /// @brief default constructor
  Att(void):
   Mode              (Content2XML    ),
   Text              (nullptr        ),
   CommonDirection   (IterateAsBefore),
   Indention         (0              ),
   RootAssociation   (nullptr        ),
   KeyWords          (nullptr        ),
   KeyCharacters     (nullptr        )
  {};

  /*!
   @brief copy constructor
   @param [in] src object to copy
  */
  Att(const Att& src):
   Mode              (src.Mode              ),
   Text              (src.Text              ),
   CommonDirection   (src.CommonDirection   ),
   Template          (src.Template          ),
   OutputText        (src.OutputText        ),
   Indention         (src.Indention         ),
   InsertPosition    (src.InsertPosition    ),
   RootAssociation   (src.RootAssociation   ),
   EvaluationSequence(src.EvaluationSequence),
   KeyWords          (src.KeyWords          ),
   KeyCharacters     (src.KeyCharacters     )
  {};

  /*!
   @brief assignment operator
   @param [in] src object to copy
   @return copied object
  */
  Att& operator = (const Att& src)
  {
   Mode               = src.Mode              ;
   Text               = src.Text              ;
   CommonDirection    = src.CommonDirection   ;
   Template           = src.Template          ;
   OutputText         = src.OutputText        ;
   Indention          = src.Indention         ;
   InsertPosition     = src.InsertPosition    ;
   RootAssociation    = src.RootAssociation   ;
   EvaluationSequence = src.EvaluationSequence;
   KeyWords           = src.KeyWords          ;
   KeyCharacters      = src.KeyCharacters     ;
   return(*this);
  };

  /// @brief destructor
  ~Att(void)
  {
   Template          .clear();
   OutputText        .clear();
   InsertPosition    .clear();
   EvaluationSequence.clear();
  };

 }Att;


};



#ifndef DOXYGEN
#define USING_NAMESPACE using namespace
//}; USING_NAMESPACE DATA;
//}; USING_NAMESPACE TDA_TinyParser;
//}; USING_NAMESPACE TXTDIASM;
#undef  USING_NAMESPACE
#endif //DOXYGEN


#endif // SPIRIT185_STORE_H

