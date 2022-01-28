/*!
 @file
 @brief definitions of an concrete grammar-class for managing xml-files

 Copyright (C) 2016-2020 by Eckard Klotz.

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
    09.10.2016     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    09.10.2016...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/
#ifndef XML_PARSER_H
 #define XML_PARSER_H



#include "TDA_GrmConcrete.h"
#include "Debug_Reaction.h"





class XML_Parser:public TDA_GrmConcrete
{
 public:

  /*!
   Constructor

   @htmlinclude ./des/XML_Parser_XML_Parser.html"
  */
 explicit XML_Parser(TiPa_Concrete::DataModel* contextModel);

  /*!
  Destructor

   @htmlinclude ./des/XML_Parser__XML_Parser.html"
  */
  ~XML_Parser(void);





/*!
 test the given string described with its begin and end to
 decide if it starts with a construction defined by the parser,
 a hit will be stored inside the parser and reused to save time.

 @param [in] begin points to the first character of the given string
 @param [in] end   points behind the last  character of the given string
 @param [in] rule  name of the rule if not the main-parser rule should be used

 @return a pointer directly behind the found match if the given string starts
         with the construction defined by the parser.
 @return nullptr if the given string starts not
         with the construction defined by the parser

 @htmlinclude ./des/XML_Parser_parse.html

 <br><br>
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    05.11.2016   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
const char * parse(const char* begin, const char* end, const char* rule = nullptr) override;




 /*!
 test the given string described with its begin and end to
 decide if it contains one or more constructions defined by the parser,
 all hits will be stored inside the parser and reused to save time.

 @param      begin points to the first character of the given string
         <br> once the first fitting part-string was found this parameter points
              to its first character
 @param [in] end   points behind the last character of the given string
 @param [in] rule  name of the rule if not the main-parser rule should be used

 @return a value behind the given <b>begin</b>  and before the given <b>end</b> that
         points directly to the last part of the given string that hits the
         construction of the parser.
 @return the value of the given <b>end</b> if the given string contains no
         with the construction defined by the parser
 @return nullptr in the case of an error or special event

 @htmlinclude ./des/XML_Parser_scan.html

 <br><br>
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    10.11.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
const char * scan(const char* begin, const char* end, const char* rule = nullptr);





/*!
 @brief return a reduced tree containing only simple xml data

 @param node xml-root node with more complex content

 @return root-node of a new tree with reduced content


 @htmlinclude ./des/XML_Parser_filter_simple_XML.html

 <br><br>
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    26.11.2016   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
TiPa_Concrete::DataFellow* filter_simple_XML(const char* begin, const char* rule = nullptr);




 protected:

 private:
  /*!
   Default Constructor forbidden to use

   @htmlinclude ./des/XML_Parser_XML_Parser.html
  */
  XML_Parser(void);






  /*!
S (white space) consists of one or more space (#x20) characters, carriage returns, line feeds, or tabs.
White Space
[3]   	S	   ::=   	(#x20 | #x9 | #xD | #xA)+

@note: The presence of #xD in the above production is maintained purely for
       backward compatibility with the First Edition. As explained in 2.11
       End-of-Line Handling, all #xD characters literally present in an XML
       document are either removed or replaced by #xA characters before any
       other processing is done. The only way to get a #xD character to match
       this production is to use a character reference in an entity value
       literal.

   @htmlinclude ./des/XML_Parser_defineRules_WhiteSpace.html
*/
  void defineRules_WhiteSpace(void);



  /*!
   ID of normal tag or attribute


   Names and Tokens
[4]   	NameStartChar	   ::=   	":" | [A-Z] | "_" | [a-z] | [#xC0-#xD6] | [#xD8-#xF6] | [#xF8-#x2FF] | [#x370-#x37D] | [#x37F-#x1FFF] | [#x200C-#x200D] | [#x2070-#x218F] | [#x2C00-#x2FEF] | [#x3001-#xD7FF] | [#xF900-#xFDCF] | [#xFDF0-#xFFFD] | [#x10000-#xEFFFF]
[4a]   	NameChar	   ::=   	NameStartChar | "-" | "." | [0-9] | #xB7 | [#x0300-#x036F] | [#x203F-#x2040]
[5]   	Name	   ::=   	NameStartChar (NameChar)*
[6]   	Names	   ::=   	Name (#x20 Name)*
[7]   	Nmtoken	   ::=   	(NameChar)+
[8]   	Nmtokens	   ::=   	Nmtoken (#x20 Nmtoken)*


   @htmlinclude ./des/XML_Parser_defineRules_Name.html
  */
  void defineRules_Name(void);



/*!
  [66]   	CharRef	   ::=   	'&#' [0-9]+ ';'
			| '&#x' [0-9a-fA-F]+ ';'	[WFC: Legal Character]

[67]   	Reference	   ::=   	EntityRef | CharRef
[68]   	EntityRef	   ::=   	'&' Name ';'	[WFC: Entity Declared]
				[VC: Entity Declared]
				[WFC: Parsed Entity]
				[WFC: No Recursion]
[69]   	PEReference	   ::=   	'%' Name ';'	[VC: Entity Declared]
				[WFC: No Recursion]
				[WFC: In DTD]



   @htmlinclude ./des/XML_Parser_defineRules_Reference.html
  */
  void defineRules_Reference(void);





  /*!
  Literals
[9]   	EntityValue	   ::=   	'"' ([^%&"] | PEReference | Reference)* '"'
			|  "'" ([^%&'] | PEReference | Reference)* "'"
[10]   	AttValue	   ::=   	'"' ([^<&"] | Reference)* '"'
			|  "'" ([^<&'] | Reference)* "'"
[11]   	SystemLiteral	   ::=   	('"' [^"]* '"') | ("'" [^']* "'")
[12]   	PubidLiteral	   ::=   	'"' PubidChar* '"' | "'" (PubidChar - "'")* "'"
[13]   	PubidChar	   ::=   	#x20 | #xD | #xA | [a-zA-Z0-9] | [-'()+,./:=?;!*#@$_%]

   @htmlinclude ./des/XML_Parser_defineRules_Literals.html
  */
  void defineRules_Literals(void);



  /* !
   <xsl:stylesheet, xmlns:xsl, ...
  void defineRules_XLS_ID(void);
  */


  /*!


[2]   	Char	   ::=   	[#x1-#xD7FF] | [#xE000-#xFFFD] | [#x10000-#x10FFFF]	// any Unicode character, excluding the surrogate blocks, FFFE, and FFFF.
[2a]   	RestrictedChar	   ::=   	[#x1-#x8] | [#xB-#xC] | [#xE-#x1F] | [#x7F-#x84] | [#x86-#x9F]



  Text consists of intermingled character data and markup. [Definition: Markup takes the form of start-tags, end-tags, empty-element tags, entity references, character references, comments, CDATA section delimiters, document type declarations, processing instructions, XML declarations, text declarations, and any white space that is at the top level of the document entity (that is, outside the document element and not inside any other markup).]

[Definition: All text that is not markup constitutes the character data of the document.]

The ampersand character (&) and the left angle bracket (<) MUST NOT appear in their literal form, except when used as markup delimiters, or within a comment, a processing instruction, or a CDATA section. If they are needed elsewhere, they MUST be escaped using either numeric character references or the strings "&amp;" and "&lt;" respectively. The right angle bracket (>) may be represented using the string "&gt;", and MUST, for compatibility, be escaped using either "&gt;" or a character reference when it appears in the string "]]>" in content, when that string is not marking the end of a CDATA section.

In the content of elements, character data is any string of characters which does not contain the start-delimiter of any markup or the CDATA-section-close delimiter, "]]>". In a CDATA section, character data is any string of characters not including the CDATA-section-close delimiter.

To allow attribute values to contain both single and double quotes, the apostrophe or single-quote character (') may be represented as "&apos;", and the double-quote character (") as "&quot;".
Character Data
[14]   	CharData	   ::=   	[^<&]* - ([^<&]* ']]>' [^<&]*)




 [Definition: CDATA sections may occur anywhere character data may occur; they are used to escape blocks of text containing characters which would otherwise be recognized as markup. CDATA sections begin with the string "<![CDATA[" and end with the string "]]>":]
CDATA Sections
[18]   	CDSect	   ::=   	CDStart CData CDEnd
[19]   	CDStart	   ::=   	'<![CDATA['
[20]   	CData	   ::=   	(Char* - (Char* ']]>' Char*))
[21]   	CDEnd	   ::=   	']]>'

Within a CDATA section, only the CDEnd string is recognized as markup, so that left angle brackets and ampersands may occur in their literal form; they need not (and cannot) be escaped using "&lt;" and "&amp;". CDATA sections cannot nest.

An example of a CDATA section, in which "<greeting>" and "</greeting>" are recognized as character data, not markup:

<![CDATA[<greeting>Hello, world!</greeting>]]>



   @htmlinclude ./des/XML_Parser_defineRules_CDATA.html
  */
  void defineRules_CDATA(void);

  /*!
  [Definition: Comments may appear anywhere in a document outside other markup; in addition, they may appear within the document type declaration at places allowed by the grammar. They are not part of the document's character data; an XML processor MAY, but need not, make it possible for an application to retrieve the text of comments. For compatibility, the string "--" (double-hyphen) MUST NOT occur within comments.] Parameter entity references MUST NOT be recognized within comments.
Comments
[15]   	Comment	   ::=   	'<!--' ((Char - '-') | ('-' (Char - '-')))* '-->'

   @htmlinclude ./des/XML_Parser_defineRules_Comment.html
  */
  void defineRules_Comment(void);


   /* !
   <?xml-stylesheet href="/selfxml.xsl" type="text/xsl" ?>
    [Definition: Processing instructions (PIs) allow documents to contain instructions for applications.]
Processing Instructions
[16]   	PI	   ::=   	'<?' PITarget (S (Char* - (Char* '?>' Char*)))? '?>'
[17]   	PITarget	   ::=   	Name - (('X' | 'x') ('M' | 'm') ('L' | 'l'))

PIs are not part of the document's character data, but MUST be passed through to the application. The PI begins with a target (PITarget) used to identify the application to which the instruction is directed. The target names "XML", "xml", and so on are reserved for standardization in this or future versions of this specification. The XML Notation mechanism may be used for formal declaration of PI targets. Parameter entity references MUST NOT be recognized within processing instructions.


  void defineRules_StyleSheet(void);
  */




/*!
 [Definition: If the entity is not internal, it is an external entity, declared as follows:]
External Entity Declaration


[75]   	ExternalID	   ::=   	'SYSTEM' S SystemLiteral
			| 'PUBLIC' S PubidLiteral S SystemLiteral
[76]   	NDataDecl	   ::=   	S 'NDATA' S Name 	[VC: Notation Declared]


   @htmlinclude ./des/XML_Parser_defineRules_ExternalEntity.html
*/
  void defineRules_ExternalEntity(void);




  /*!
 [Definition: Entities are declared thus:]
Entity Declaration
[70]   	EntityDecl	   ::=   	GEDecl | PEDecl
[71]   	GEDecl	   ::=   	'<!ENTITY' S Name S EntityDef S? '>'
[72]   	PEDecl	   ::=   	'<!ENTITY' S '%' S Name S PEDef S? '>'
[73]   	EntityDef	   ::=   	EntityValue | (ExternalID NDataDecl?)
[74]   	PEDef	   ::=   	EntityValue | ExternalID

   @htmlinclude ./des/XML_Parser_defineRules_Entity.html
  */
  void defineRules_Entity(void);






  /* !


   <?xml version="1.0" encoding="ISO-8859-1" standalone="yes"?>

[23]   	XMLDecl	   ::=   	'<?xml' VersionInfo EncodingDecl? SDDecl? S? '?>'
[24]   	VersionInfo	   ::=   	S 'version' Eq ("'" VersionNum "'" | '"' VersionNum '"')

[25]   	Eq	   ::=   	S? '=' S?
[26]   	VersionNum	   ::=   	'1.1'
[27]   	Misc	   ::=   	Comment | PI | S

Standalone Document Declaration
[32]   	SDDecl	   ::=   	S 'standalone' Eq (("'" ('yes' | 'no') "'") | ('"' ('yes' | 'no') '"')) 	[VC: Standalone Document Declaration]



External parsed entities SHOULD each begin with a text declaration.
Text Declaration
[77]   	TextDecl	   ::=   	'<?xml' VersionInfo? EncodingDecl S? '?>'

The text declaration MUST be provided literally, not by reference to a parsed entity. The text declaration MUST NOT appear at any position other than the beginning of an external parsed entity. The text declaration in an external parsed entity is not considered part of its replacement text.
Encoding Declaration
[80]   	EncodingDecl	   ::=   	S 'encoding' Eq ('"' EncName '"' | "'" EncName "'" )
[81]   	EncName	   ::=   	[A-Za-z] ([A-Za-z0-9._] | '-')*	// Encoding name contains only Latin characters

  void defineRules_Text(void);
  */







    /*!


[41]   	Attribute	   ::=   	Name Eq AttValue 	[VC: Attribute Value Type]
				[WFC: No External Entity References]
				[WFC: No < in Attribute Values]



[52]   	AttlistDecl	   ::=   	'<!ATTLIST' S Name AttDef* S? '>'
[53]   	AttDef	   ::=   	S Name S AttType S DefaultDecl



[54]	AttType	   ::=   	StringType | TokenizedType | EnumeratedType
[55]   	StringType	   ::=   	'CDATA'
[56]   	TokenizedType	   ::=   	'ID'	[VC: ID]
				[VC: One ID per Element Type]
				[VC: ID Attribute Default]
			| 'IDREF'	[VC: IDREF]
			| 'IDREFS'	[VC: IDREF]
			| 'ENTITY'	[VC: Entity Name]
			| 'ENTITIES'	[VC: Entity Name]
			| 'NMTOKEN'	[VC: Name Token]
			| 'NMTOKENS'	[VC: Name Token]

Enumerated Attribute Types
[57]   	EnumeratedType	   ::=   	NotationType | Enumeration
[58]   	NotationType	   ::=   	'NOTATION' S '(' S? Name (S? '|' S? Name)* S? ')' 	[VC: Notation Attributes]
				[VC: One Notation Per Element Type]
				[VC: No Notation on Empty Element]
				[VC: No Duplicate Tokens]
[59]   	Enumeration	   ::=   	'(' S? Nmtoken (S? '|' S? Nmtoken)* S? ')'	[VC: Enumeration]
				[VC: No Duplicate Tokens]
[60]   	DefaultDecl	   ::=   	'#REQUIRED' | '#IMPLIED'
			| (('#FIXED' S)? AttValue)	[VC: Required Attribute]
				[VC: Attribute Default Value Syntactically Correct]
				[WFC: No < in Attribute Values]
				[VC: Fixed Attribute Default]
				[WFC: No External Entity References]

   @htmlinclude ./des/XML_Parser_defineRules_Attribute.html
*/
  void defineRules_Attribute(void);







  /*!
  <ID>, </ID> or <ID/>




Start-tag
[40]   	STag	   ::=   	'<' Name (S Attribute)* S? '>'	[WFC: Unique Att Spec]

End-tag
[42]   	ETag	   ::=   	'</' Name S? '>'


Tags for Empty Elements
[44]   	EmptyElemTag	   ::=   	'<' Name (S Attribute)* S? '/>'	[WFC: Unique Att Spec]


   @htmlinclude ./des/XML_Parser_defineRules_Tag.html
  */
  void defineRules_Tag(void);


  /*!

   [Definition: Each XML document contains one or more elements, the boundaries of which are either delimited by start-tags and end-tags, or, for empty elements, by an empty-element tag. Each element has a type, identified by name, sometimes called its "generic identifier" (GI), and may have a set of attribute specifications.] Each attribute specification has a name and a value.
Element
[39]   	element	   ::=   	EmptyElemTag
			| STag content ETag 	[WFC: Element Type Match]
				[VC: Element Valid]


Content of Elements
[43]   	content	   ::=   	CharData? ((element | Reference | CDSect | PI | Comment) CharData?)*

[45]   	elementdecl	   ::=   	'<!ELEMENT' S Name S contentspec S? '>'	[VC: Unique Element Type Declaration]
[46]   	contentspec	   ::=   	'EMPTY' | 'ANY' | Mixed | children

[47]   	children	   ::=   	(choice | seq) ('?' | '*' | '+')?
[48]   	cp	   ::=   	(Name | choice | seq) ('?' | '*' | '+')?
[49]   	choice	   ::=   	'(' S? cp ( S? '|' S? cp )+ S? ')'	[VC: Proper Group/PE Nesting]
[50]   	seq	   ::=   	'(' S? cp ( S? ',' S? cp )* S? ')'	[VC: Proper Group/PE Nesting]

[51]   	Mixed	   ::=   	'(' S? '#PCDATA' (S? '|' S? Name)* S? ')*'
			| '(' S? '#PCDATA' S? ')' 	[VC: Proper Group/PE Nesting]

   @htmlinclude ./des/XML_Parser_defineRules_Element.html
  */
  void defineRules_Element(void);








  /*!

The document type declaration MUST appear before the first element in the document.
Prolog
[22]   	prolog	   ::=   	XMLDecl Misc* (doctypedecl Misc*)?


  <!DOCTYPE Name [.. DTD ..]> or <!DOCTYPE Name SYSTEM "Name.dtd">


   [Definition: The XML document type declaration contains or points to markup declarations that provide a grammar for a class of documents. This grammar is known as a document type definition, or DTD. The document type declaration can point to an external subset (a special kind of external entity) containing markup declarations, or can contain the markup declarations directly in an internal subset, or can do both. The DTD for a document consists of both subsets taken together.]

[Definition: A markup declaration is an element type declaration, an attribute-list declaration, an entity declaration, or a notation declaration.] These declarations may be contained in whole or in part within parameter entities, as described in the well-formedness and validity constraints below. For further information, see 4 Physical Structures.
Document Type Definition
[28]   	doctypedecl	   ::=   	'<!DOCTYPE' S Name (S ExternalID)? S? ('[' intSubset ']' S?)? '>'	[VC: Root Element Type]
				[WFC: External Subset]
[28a]   	DeclSep	   ::=   	PEReference | S 	[WFC: PE Between Declarations]
[28b]   	intSubset	   ::=   	(markupdecl | DeclSep)*
[29]   	markupdecl	   ::=   	elementdecl | AttlistDecl | EntityDecl | NotationDecl | PI | Comment 	[VC: Proper Declaration/PE Nesting]
				[WFC: PEs in Internal Subset]

Note that it is possible to construct a well-formed document containing a doctypedecl that neither points to an external subset nor contains an internal subset.

The markup declarations may be made up in whole or in part of the replacement text of parameter entities. The productions later in this specification for individual nonterminals (elementdecl, AttlistDecl, and so on) describe the declarations after all the parameter entities have been included.

Parameter entity references are recognized anywhere in the DTD (internal and external subsets and external parameter entities), except in literals, processing instructions, comments, and the contents of ignored conditional sections (see 3.4 Conditional Sections). They are also recognized in entity value literals. The use of parameter entities in the internal subset is restricted as described below.

Validity constraint: Root Element Type

The Name in the document type declaration MUST match the element type of the root element.

Validity constraint: Proper Declaration/PE Nesting

Parameter-entity replacement text MUST be properly nested with markup declarations. That is to say, if either the first character or the last character of a markup declaration (markupdecl above) is contained in the replacement text for a parameter-entity reference, both MUST be contained in the same replacement text.

Well-formedness constraint: PEs in Internal Subset

In the internal DTD subset, parameter-entity references MUST NOT occur within markup declarations; they may occur where markup declarations can occur. (This does not apply to references that occur in external parameter entities or to the external subset.)

Well-formedness constraint: External Subset

The external subset, if any, MUST match the production for extSubset.

Well-formedness constraint: PE Between Declarations

The replacement text of a parameter entity reference in a DeclSep MUST match the production extSubsetDecl.

Like the internal subset, the external subset and any external parameter entities referenced in a DeclSep MUST consist of a series of complete markup declarations of the types allowed by the non-terminal symbol markupdecl, interspersed with white space or parameter-entity references. However, portions of the contents of the external subset or of these external parameter entities may conditionally be ignored by using the conditional section construct; this is not allowed in the internal subset but is allowed in external parameter entities referenced in the internal subset.
External Subset
[30]   	extSubset	   ::=   	TextDecl? extSubsetDecl
[31]   	extSubsetDecl	   ::=   	( markupdecl | conditionalSect | DeclSep)*

The external subset and external parameter entities also differ from the internal subset in that in them, parameter-entity references are permitted within markup declarations, not only between markup declarations.

An example of an XML document with a document type declaration:

<?xml version="1.1"?>
<!DOCTYPE greeting SYSTEM "hello.dtd">
<greeting>Hello, world!</greeting>

The system identifier "hello.dtd" gives the address (a URI reference) of a DTD for the document.

The declarations can also be given locally, as in this example:

<?xml version="1.1" encoding="UTF-8" ?>
<!DOCTYPE greeting [
<!ELEMENT greeting (#PCDATA)>
]>
<greeting>Hello, world!</greeting>

If both the external and internal subsets are used, the internal subset MUST be considered to occur before the external subset. This has the effect that entity and attribute-list declarations in the internal subset take precedence over those in the external subset.

If a document is well-formed or valid XML 1.0, and provided it does not contain any control characters in the range [#x7F-#x9F] other than as character escapes, it may be made well-formed or valid XML 1.1 respectively simply by changing the version number.


Conditional Section
[61]   	conditionalSect	   ::=   	includeSect | ignoreSect
[62]   	includeSect	   ::=   	'<![' S? 'INCLUDE' S? '[' extSubsetDecl ']]>' 	[VC: Proper Conditional Section/PE Nesting]
[63]   	ignoreSect	   ::=   	'<![' S? 'IGNORE' S? '[' ignoreSectContents* ']]>'	[VC: Proper Conditional Section/PE Nesting]
[64]   	ignoreSectContents	   ::=   	Ignore ('<![' ignoreSectContents ']]>' Ignore)*
[65]   	Ignore	   ::=   	Char* - (Char* ('<![' | ']]>') Char*)



[82]   	NotationDecl	   ::=   	'<!NOTATION' S Name S (ExternalID | PublicID) S? '>'	[VC: Unique Notation Name]
[83]   	PublicID	   ::=   	'PUBLIC' S PubidLiteral


   @htmlinclude ./des/XML_Parser_defineRules_DocumentTypeDefinition.html
*/
  void defineRules_DocumentTypeDefinition(void);


/*!
[1]   	document	   ::=   	( prolog element Misc* ) - ( Char* RestrictedChar Char* )

   @htmlinclude ./des/XML_Parser_defineRules_Document.html
*/
  void defineRules_Document(void);



 /*!


   @htmlinclude ./des/XML_Parser_defineRules_Declaration.html
 */
  void defineRules_Declaration(void);





  /*!
   <ID attribute  attribute ...> ... </ID>

   @htmlinclude ./des/XML_Parser_defineRules_Node.html
  */
  void defineRules_Node(void);

  /*!
   <ID attribute attribute .../>

   @htmlinclude ./des/XML_Parser_defineRules_Leaf.html
  */
  void defineRules_Leaf(void);




  /*!

   @htmlinclude ./des/XML_Parser_skipNonRuleResults.html
  */
  void skipNonRuleResults(void);



  struct ID
  {
    int Character;
    int String;
    int Counter;
    int Condition;
    int Sequence;
    int Rule;

    ID(void):
     Character   (0),
     String    (300),
     Counter   (600),
     Condition(1000),
     Sequence (2000),
     Rule      (500){};

    ID( const ID& id):
     Character(id.Character),
     String   (id.String   ),
     Counter  (id.Counter  ),
     Condition(id.Condition),
     Sequence (id.Sequence ),
     Rule     (id.Rule     ){};


    ID& operator=( const ID& id)
    {
     Character = id.Character;
     String    = id.String   ;
     Counter   = id.Counter  ;
     Condition = id.Condition;
     Sequence  = id.Sequence ;
     Rule      = id.Rule     ;
     return(*this);
    };

    ~ID(void){};
  }ID;

  Debug_Reaction      DebugReaction;



//
//
//  /*!
//  */
//  void defineRules_(void);
//
//  /*!
//  */
//  void defineRules_(void);
//

} ;






#endif // XML_PARSER_H
