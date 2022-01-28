/*!

 @file
 @brief concrete association visitor to store an xml-tree in a file

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
#ifndef XML_SAVE_H
 #define XML_SAVE_H


#include "ASS_Visitor.hpp"
#include "xml_Data.h"


/*!
 @brief concrete association visitor to store an xml-tree in a file
*/
class XML_Save:public AssociationVisitor<XML_Data*, nullptr>
{
 public:


/// @brief element of a string template that describes what data detail or what raw-text should be used
 typedef struct Template_TP
 {
  int         Data   ;   ///< @brief data to insert
  const char* RawText;   ///< @brief raw text part
 }Template_TP;


/// @brief index-type for array @ref Att::Template
typedef enum XML_TemplateKind
{
  XML_StartTag    = 0, ///< @brief opening tag of the xml-representation
  XML_Text        = 1, ///< @brief text-content of the xml-representation
//  XML_Reference   = 2, ///< @brief character-referencing text-content of the xml-representation
  XML_EndTag      = 3, ///< @brief closing tag of the xml-representation
  XML_LeafTag     = 4, ///< @brief tag of the xml-representation used for a leaf node
  XML_Comment     = 5, ///< @brief xml-comment
  XML_Declaration = 6, ///< @brief xml-declaration
}XML_TemplateKind;

/// @brief evaluation sequence actions not defined by user templates
typedef enum SequenceAction
{
  Indent_Tag     = -1, ///< @brief normal indention
  Indent_Text    = -2, ///< @brief additional indention
  Indent_Child   = -3, ///< @brief normal indention and store of insert-position
}SequenceAction;




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


 /// @brief default definitions for data content that's user definition is invalid for xml-output
 static Dflt_XML_String DfltXML ;



 typedef Association<XML_Data*, nullptr>           DataAssociation;
 typedef AssociationVisitor<XML_Data*,nullptr>     XML_Visitor;







/*!
 @brief default constructor

 @htmlinclude ./des/XML_Save_XML_Save.html
*/
   XML_Save(void);






/*!
 @brief destructor

 @htmlinclude ./des/XML_Save__XML_Save_.html
*/
  ~XML_Save(void);










/*!
 @brief initialize this visitor

 @param [in] text         location to store in

 @return pointer to initialized class-object

 @htmlinclude "./des/XML_Save_operator().html"

*/
 XML_Save* operator()(char** text);










// @param sponsor the sponsor of the association to analyse

 /*!
 @brief start to evaluate a association

 @param node    the association to analyse

 @return direction of next iteration step

 @htmlinclude ./des/XML_Save_evaluate.html
*/
DirectionOfIteration evaluate(DataAssociation* node/*, DataAssociation* sponsor*/);


 protected:

 private:


// @param sponsor the sponsor of the association to analyse

/*!
 @brief evaluate an association and its contractors to store the content in an xml-file

 @param node    the association to analyse


 @htmlinclude ./des/XML_Save_evaluateXML.html

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
DirectionOfIteration evaluateXML(DataAssociation* node/*, DataAssociation* sponsor*/);




/*!
 @brief initialize this visitor

 @param [in] text         location to store in

 @htmlinclude ./des/XML_Save_init.html
*/
 void init(char** text);




/*!
 @brief define a template of a string used to represent
        all or some association-data attributes


 @param [in]  text       template definition
 @param [in]  separator  separates the data replacements from the
              raw-text sections in the given text

 @htmlinclude ./des/XML_Save_stringTemplate.html
*/
list<Template_TP* >* stringTemplate(const char* text, char separator='$');



/// @brief mode of character conversion while creating an xml-representation
typedef enum Character2XML_Mode_TP
{
 ConvertAll       = 0, ///< @brief convert all characters if they are no valid xml-characters
 KeppBelowASCII32 = 32,///< @brief keep control characters with and ordinal number below 32
}Character2XML_Mode_TP;



/*!
 @brief get a string-representation of a single node

 @param [in]  data          data to analyse
 @param [in]  textTemplate  template definition
 @param [out] text          output string
 @param [in]  keepBelow     keep all characters below this ordinal number unchanged



 @htmlinclude ./des/XML_Save_stringRepresentation.html
*/
void stringRepresentation(XML_Data* data, list<Template_TP* >* textTemplate, char** text, Character2XML_Mode_TP keepBelow);







/*!
 @brief return a numerical ID that represents a single association-data attribute,
        used by @ref stringTemplate

 @param [in]  text potential name of association-data attribute
 @return      a value >=0 that is a valid identifier of an existing attribute
 <br>         or -1 if the given text is not a name of an existing attribute

 @htmlinclude ./des/XML_Save_dataID_get.html
*/
 int dataID_get(const char* text);









/*!
 @brief return an xml compatible symbol for the given character

 @param [in] character   should be analysed and perhaps replaced

 @return character itself or xml-replacement

 @htmlinclude ./des/XML_Save_char2xml.html

*/
 const char* char2xml(char character);



/*!
 @brief convert into xml-compatible string
 replace in the given source string not xml compatible symbols by compatible one
 and return the result as the given destination string


 @param [in]  source        should be analysed for correction
 @param [out] destination   return value that has to be NULL
 @param [in]  keepBelow     keep all characters below this ordinal number unchanged

 @return character itself or xml-replacement


 @htmlinclude ./des/XML_Save_string2xml.html
*/
 void string2xml(const char* source, char** destination, Character2XML_Mode_TP keepBelow = ConvertAll);














/// @brief common object attributes
 struct Att
 {
  char**                            Text{nullptr};                    ///< @brief location to store in

  DirectionOfIteration              CommonDirection{IterateAsBefore}; ///< @brief stores the direction to iterate while temporary changes

  map<int,list<Template_TP* > *>    Template{};                       ///< @brief container of string-templates used to represent
                                                                      ///         all or some association-data attributes
  list<const char*>                 OutputText{};                     ///< @brief sequence of strings that represents all nodes of an
                                                                      ///<        evaluated association tree
  int                               Indention{0};                     ///< @brief number of spaces to insert at the line begin
                                                                      ///<        to have a nice looking text
  list<list<const char*>::iterator> InsertPosition{};                 ///< @brief current position to insert a line into
                                                                      ///<        the output-text
  DataAssociation*                  RootAssociation{nullptr};         ///< @brief first association that is visited
                                                                      ///<        while one evaluation-process
   /// @brief default constructor
  Att(void):
   Text              (nullptr        ),
   CommonDirection   (IterateAsBefore),
   Indention         (0              ),
   RootAssociation   (nullptr        )
  {};

  /*!
   @brief copy constructor
   @param [in] src object to copy
  */
  Att(const Att& src):
   Text              (src.Text              ),
   CommonDirection   (src.CommonDirection   ),
   Template          (src.Template          ),
   OutputText        (src.OutputText        ),
   Indention         (src.Indention         ),
   InsertPosition    (src.InsertPosition    ),
   RootAssociation   (src.RootAssociation   )
  {};

  /*!
   @brief assignment operator
   @param [in] src object to copy
   @return copied object
  */
  Att& operator = (const Att& src)
  {
   Text               = src.Text              ;
   CommonDirection    = src.CommonDirection   ;
   Template           = src.Template          ;
   OutputText         = src.OutputText        ;
   Indention          = src.Indention         ;
   InsertPosition     = src.InsertPosition    ;
   RootAssociation    = src.RootAssociation   ;
   return(*this);
  };

  /// @brief destructor
  ~Att(void)
  {
   Template          .clear();
   OutputText        .clear();
   InsertPosition    .clear();
  };



 }Att;
};



#endif // XML_SAVE_H


