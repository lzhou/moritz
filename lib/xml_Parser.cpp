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

#include "xml_Parser.h"



#include "TiPa_Concrete.h"
#include "TiPa_Combination.h"
#include "TiPa_Counter.h"
#include "TiPa_String.h"
#include "TiPa_Character.h"

#include "xml_Tree.h"

//#define XML_DEBUG

/*  @MRTZ_describe XML_Parser

*/
XML_Parser::XML_Parser(TiPa_Concrete::DataModel* contextModel)
#ifdef  XML_DEBUG
           :TDA_GrmConcrete(contextModel, true),
#else //XML_DEBUG
           :TDA_GrmConcrete(contextModel, false),
#endif //XML_DEBUG
            ID()
{

 defineRules_WhiteSpace();
 defineRules_Name();
 defineRules_Reference();
 defineRules_Literals();
 defineRules_CDATA();
 defineRules_Comment();
// defineRules_StyleSheet();
 defineRules_ExternalEntity();
 defineRules_Entity();
// defineRules_Text();
 defineRules_Attribute();
 defineRules_Tag();
 defineRules_Element();
 defineRules_DocumentTypeDefinition();
 defineRules_Document();
 defineRules_Declaration();
 defineRules_Node();
 defineRules_Leaf();


 skipNonRuleResults();

 GET_PARSER(TiPa_Rule,        Document);
 GET_PARSER(TiPa_Rule,        Space);
 GET_PARSER(TiPa_Condition,   NewLine);

 TDA_GrmConcrete::Att.MainParser = Document;
 TDA_GrmConcrete::Att.SkipParser = Space;
 TDA_GrmConcrete::Att.LineParser = NewLine;

 DebugReaction.setProperty(&TDA_GrmConcrete::Att.Property);
}

/*  @MRTZ_describe XML_Parser

*/
XML_Parser::XML_Parser(void)
#ifdef  XML_DEBUG
           :TDA_GrmConcrete(nullptr, true),
#else //XML_DEBUG
           :TDA_GrmConcrete(nullptr, false),
#endif //XML_DEBUG
            ID()
{

 defineRules_WhiteSpace();
 defineRules_Name();
 defineRules_Reference();
 defineRules_Literals();
 defineRules_CDATA();
 defineRules_Comment();
// defineRules_StyleSheet();
 defineRules_ExternalEntity();
 defineRules_Entity();
// defineRules_Text();
 defineRules_Attribute();
 defineRules_Tag();
 defineRules_Element();
 defineRules_DocumentTypeDefinition();
 defineRules_Document();
 defineRules_Declaration();
 defineRules_Node();
 defineRules_Leaf();

 skipNonRuleResults();

 GET_PARSER(TiPa_Rule,        Document);
 GET_PARSER(TiPa_Rule,        Space);
 GET_PARSER(TiPa_Condition,   NewLine);

 TDA_GrmConcrete::Att.MainParser = Document;
 TDA_GrmConcrete::Att.SkipParser = Space;
 TDA_GrmConcrete::Att.LineParser = NewLine;

 DebugReaction.setProperty(&TDA_GrmConcrete::Att.Property);
}

/*  @MRTZ_describe ~XML_Parser

*/
XML_Parser::~XML_Parser(void)
{

}





/*  @MRTZ_describe parse

*/
const char * XML_Parser::parse(const char* begin, const char* end, const char* rule)
{
  if(TDA_GrmConcrete::Att.DebugMode == true)
   pre_parse( begin, end);                           // call the pre parser process to collect common attributes of the give text
  return(TDA_GrmConcrete::parse(begin, end, rule));  // call the main parsing process and return its result
}




/*  @MRTZ_describe scan

*/
const char * XML_Parser::scan(const char* begin, const char* end, const char* rule)
{
  if(TDA_GrmConcrete::Att.DebugMode == true)
   pre_parse( begin, end);                            // call the pre parser process to collect common attributes of the give text
  return(TDA_GrmConcrete::scan(begin, end, rule));   // call the main parsing process and return its result
}




/*  @MRTZ_describe filter_simple_XML

*/
TiPa_Concrete::DataFellow* XML_Parser::filter_simple_XML(const char* begin, const char* rule)
{
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"XML_Parser::filter_simple_XML enter"<<endl;

 TiPa_Concrete* Parser = Att.MainParser;
 if(rule != nullptr)
  Parser = TDA_GrmConcrete::Att.ParserRule[rule];

 XML_Tree Filter(XML_Tree::FilterMode_DF, &TDA_GrmConcrete::Att.Property, Att.ContextModel, Parser);

 Filter.specialNodes_insert(XML_Tree::NodesToKeep, property_UserID_Get("Attribute"));
 Filter.specialNodes_insert(XML_Tree::NodesToKeep, property_UserID_Get("CharData"));
 Filter.specialNodes_insert(XML_Tree::NodesToKeep, property_UserID_Get("Reference"));
 Filter.specialNodes_insert(XML_Tree::NodesToKeep, property_UserID_Get("CharNormal"));

 Filter.specialNodes_insert(XML_Tree::NodesToKeep, property_UserID_Get("AttValue"));
 Filter.specialNodes_insert(XML_Tree::NodesToKeep, property_UserID_Get("AttVal1"));
 Filter.specialNodes_insert(XML_Tree::NodesToKeep, property_UserID_Get("AttVal2"));
 Filter.specialNodes_insert(XML_Tree::NodesToKeep, property_UserID_Get("AttCharacter1"));
 Filter.specialNodes_insert(XML_Tree::NodesToKeep, property_UserID_Get("AttCharacter2"));


 Filter.specialNodes_insert(XML_Tree::NodesToKeep, property_UserID_Get("CData"));
// Filter.specialNodes_insert(XML_Tree::NodesToKeep, property_UserID_Get("Comment"));

// Filter.specialNodes_insert(XML_Tree::NodesToHide, property_UserID_Get("CommentOpen"));
 Filter.specialNodes_insert(XML_Tree::NodesToKeep, property_UserID_Get("CommentContent"));
// Filter.specialNodes_insert(XML_Tree::NodesToHide, property_UserID_Get("CommentClose"));

 Filter.specialNodes_insert(XML_Tree::NodesToKeep, property_UserID_Get("Document"));
 Filter.specialNodes_insert(XML_Tree::NodesToKeep, property_UserID_Get("Element"));
 Filter.specialNodes_insert(XML_Tree::NodesToKeep, property_UserID_Get("Name"));
// Filter.specialNodes_insert(XML_Tree::NodesToKeep, property_UserID_Get("Prolog"));
// Filter.specialNodes_insert(XML_Tree::NodesToKeep, property_UserID_Get("XMLDecl"));
 Filter.specialNodes_insert(XML_Tree::NodesToKeep, property_UserID_Get("Declaration"));



// TiPa_Concrete::DataFellow* ReturnValue = Att.ContextModel->fellow_create();
  TiPa_Concrete::DataFellow* ReturnValue = Filter.evaluate(begin, XML_Tree::SkipUndefined);

//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"XML_Parser::filter_simple_XML leave"<<endl;
 return(ReturnValue);
}





#define INCED_ID(id) ++(id)



/*  @MRTZ_describe defineRules_WhiteSpace
   	S	   ::=   	(#x20 | #x9 | #xD | #xA)+
*/
void XML_Parser::defineRules_WhiteSpace(void)
{
 CREATE_CHARACTER_PARSER(   CR,              INCED_ID(ID.Character), "control parser: Carriage Return");
 CREATE_CHARACTER_PARSER(   LF,              INCED_ID(ID.Character), "control character: Line Feed");
 CREATE_CHARACTER_PARSER(   HT,              INCED_ID(ID.Character), "control parser: Horizontal Tabulator");
 CREATE_CHARACTER_PARSER(   SP,              INCED_ID(ID.Character), "control parser: Space");

 CREATE_CHARACTER_PARSER(SpaceDetails,       INCED_ID(ID.Character), "characters to ignore");
 CREATE_RULE_PARSER(Space,                   INCED_ID(ID.Rule),      "text content to ignore");
                    Space->resultStorage_Set(TiPa_Concrete::ResStore_Skip);

 CREATE_SEQUENCE_PARSER(NL_MS,               INCED_ID(ID.Sequence),  "character-combination for new line in Microsoft operation systems");
 CREATE_CHARACTER_PARSER(NL_UNIX,            INCED_ID(ID.Character), "character-combination for new line in Unix like operation systems");
 CREATE_CONDITION_PARSER(NL_MAC,             INCED_ID(ID.Condition), "character-combination for new line in Macintosh operation systems");
 CREATE_CONDITION_PARSER(NewLine_cnd,        INCED_ID(ID.Condition), "kinds of new line definitions");
 CREATE_RULE_PARSER(NewLine,                 INCED_ID(ID.Rule),      "new line rule");
                    NewLine->resultStorage_Set(TiPa_Concrete::ResStore_Skip);

 CREATE_CHARACTER_PARSER(InlineSpace,        INCED_ID(ID.Character), "whites-pace characters not used to symbolise line-change");
 CREATE_COUNTER_PARSER(InlineSpace_cnt,      INCED_ID(ID.Counter),   "zero or more whites-pace characters not used to symbolise line-change");
 CREATE_SEQUENCE_PARSER(TagLineStart_seq,    INCED_ID(ID.Sequence),  "white-space sequence between begin of line and begin of Tag");
 CREATE_RULE_PARSER(TagLineStart,            INCED_ID(ID.Rule),      "rule of white-space sequence between begin of line and begin of Tag");
                    TagLineStart->resultStorage_Set(TiPa_Concrete::ResStore_Skip);
 CREATE_COUNTER_PARSER(TagLineStartOpt,      INCED_ID(ID.Counter),   "optional white-space sequence between begin of line and begin of Tag");



 CR->init(13);// carriage return
 LF->init(10);// line feed
 HT->init( 9);// horizontal tabulator
 SP->init(32);// space

 SpaceDetails->include(9)->include(32);  //->init(13)->include(10)

 Space->init(SpaceDetails);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  Space->reactionHit_set(&DebugReaction);


 NL_MS->hard(CR, LF);           // new line for Microsoft
 NL_UNIX->init(10);            // new line for Unix or Linux
 NL_MAC->exclusion(CR,NL_MS);   // new line for Apple-Macintosh
 NewLine_cnd->exOr(NL_MS, NL_UNIX)->exOr(NL_MAC);  // new line for Microsoft ex-or Unix/Linux ex-or Apple-Macintosh

 NewLine->init(NewLine_cnd);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  NewLine->reactionHit_set(&DebugReaction);

 InlineSpace->init(1,32)->exclude(10)->exclude(13);
 InlineSpace_cnt->zeroOrMore(InlineSpace);
// InlineSpace_cnt->resultTerminate();


 TagLineStart_seq->hard(NewLine,InlineSpace_cnt);
// TagLineStart_seq->resultTerminate();

 TagLineStart->init(TagLineStart_seq);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  TagLineStart->reactionHit_set(&DebugReaction);
 TagLineStartOpt->zeroOrMore(TagLineStart);
}



/*  @MRTZ_describe defineRules_Name
[4]   	NameStartChar	   ::=   	":" | [A-Z] | "_" | [a-z] | [#xC0-#xD6] | [#xD8-#xF6]
                                   | [#xF8-#x2FF] | [#x370-#x37D] | [#x37F-#x1FFF] | [#x200C-#x200D]
                                   | [#x2070-#x218F] | [#x2C00-#x2FEF] | [#x3001-#xD7FF] | [#xF900-#xFDCF]
                                   | [#xFDF0-#xFFFD] | [#x10000-#xEFFFF]
[4a]   	NameChar	   ::=   	NameStartChar | "-" | "." | [0-9] | #xB7
                                              | [#x0300-#x036F] | [#x203F-#x2040]
[5]   	Name	   ::=   	NameStartChar (NameChar)*
[6]   	Names	   ::=   	Name (#x20 Name)*
[7]   	Nmtoken	   ::=   	(NameChar)+
[8]   	Nmtokens	   ::=   	Nmtoken (#x20 Nmtoken)*

*/
void XML_Parser::defineRules_Name(void)
{
 CREATE_CHARACTER_PARSER( NameStartChar,   INCED_ID(ID.Character), "start of a name");
 CREATE_CHARACTER_PARSER( NameChar,        INCED_ID(ID.Character), "continue of a name");

 CREATE_COUNTER_PARSER(   NameBody,        INCED_ID(ID.Counter), "continue of a name");
 CREATE_SEQUENCE_PARSER(  Name_seq,        INCED_ID(ID.Sequence), "name (parser)");

 CREATE_SEQUENCE_PARSER(  Names,           INCED_ID(ID.Sequence), "sequence of names");
 CREATE_COUNTER_PARSER(   NmToken,         INCED_ID(ID.Counter), "name-token");
 CREATE_SEQUENCE_PARSER(  NmTokens,        INCED_ID(ID.Sequence), "sequence of name-token");

 CREATE_RULE_PARSER(      Name,            INCED_ID(ID.Rule),   "identifying name of a tag, attribute, ... (rule)");
                          Name->resultStorage_Set(TiPa_Concrete::ResStore_Terminate);


 GET_PARSER(TiPa_Character, SP);

 NameStartChar->init(':')->include('_')->include('a','z')->include('A','Z')->include((char)0xC0,(char)0xD6)->include((char)0xD8,(char)0xF6);
 NameChar->init(':')->include('_')->include('a','z')->include('A','Z')->include((char)0xC0,(char)0xD6)->include((char)0xD8,(char)0xF6)
         ->include('-')->include('.')->include('0','9')->include((char)0xB7);

 NameBody->zeroOrMore(NameChar);

 Name_seq->hard(NameStartChar, NameBody);
// Name_seq->resultTerminate();
 Names->init(TiPa_Sequence::Seq_Seprt,Name_seq,SP);

 NmToken ->init(TiPa_Counter::Cnt_OneOrMore,NameChar);
 NmTokens->init(TiPa_Sequence::Seq_Seprt,NmToken,SP);

 Name->init(Name_seq);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  Name->reactionHit_set(&DebugReaction);

}


/*  @MRTZ_describe defineRules_Reference
[66]   	CharRef	   ::=   	'&#' [0-9]+ ';'
			| '&#x' [0-9a-fA-F]+ ';'	[WFC: Legal Character]

[68]   	EntityRef	   ::=   	'&' Name ';'	[WFC: Entity Declared]
				[VC: Entity Declared]
				[WFC: Parsed Entity]
				[WFC: No Recursion]
[69]   	PEReference	   ::=   	'%' Name ';'	[VC: Entity Declared]
				[WFC: No Recursion]
				[WFC: In DTD]

[67]   	Reference	   ::=   	EntityRef | CharRef



  */
void XML_Parser::defineRules_Reference(void)
{
 CREATE_CHARACTER_PARSER( Digit,               INCED_ID(ID.Character), "id-characters: 0...9");

 CREATE_STRING_PARSER(    CharStartDec,        INCED_ID(ID.String), "begin of decimal character definition");
 CREATE_STRING_PARSER(    CharStartHex,        INCED_ID(ID.String), "begin of hexadecimal character definition");
 CREATE_COUNTER_PARSER(   DigitDec_cnt,        INCED_ID(ID.Counter), "sequence of decimal digits");
 CREATE_COUNTER_PARSER(   DigitHex_cnt,        INCED_ID(ID.Counter), "sequence of hexadecimal digits");

 CREATE_CHARACTER_PARSER( Semicolon,           INCED_ID(ID.Character), "id-character: semicolon");
 CREATE_CHARACTER_PARSER( And,                 INCED_ID(ID.Character), "id-character: and");
 CREATE_CHARACTER_PARSER( Percent,             INCED_ID(ID.Character), "id-character: percent");

 CREATE_SEQUENCE_PARSER(  CharRefDec_seq,      INCED_ID(ID.Sequence), "decimal character reference ");
 CREATE_SEQUENCE_PARSER(  CharRefHex_seq,      INCED_ID(ID.Sequence), "hexadecimal character reference ");
 CREATE_CONDITION_PARSER( CharRef_con,         INCED_ID(ID.Condition), "character reference");


 CREATE_RULE_PARSER(      CharRef,             INCED_ID(ID.Rule),      "character reference (rule)");
                          CharRef->resultStorage_Set(TiPa_Concrete::ResStore_Skip);
 CREATE_SEQUENCE_PARSER(  EntityRef_seq,       INCED_ID(ID.Sequence),  "entity reference (parser)");
 CREATE_RULE_PARSER(      EntityRef,           INCED_ID(ID.Rule),      "entity reference (rule)");
                          EntityRef->resultStorage_Set(TiPa_Concrete::ResStore_Skip);
 CREATE_SEQUENCE_PARSER(  PEReference_seq,     INCED_ID(ID.Sequence),  "parameter-entity references (parser)");
 CREATE_RULE_PARSER(      PEReference,         INCED_ID(ID.Rule),      "parameter-entity reference (rule)");
                          PEReference->resultStorage_Set(TiPa_Concrete::ResStore_Skip);
 CREATE_SEQUENCE_PARSER(  PEReferenceLine,     INCED_ID(ID.Sequence),  "parameter-entity reference with optional white-space before");

 CREATE_CONDITION_PARSER( Reference_con,       INCED_ID(ID.Condition), "reference (parser)");
 CREATE_RULE_PARSER(      Reference,           INCED_ID(ID.Rule),      "reference (rule)");
                          Reference->resultStorage_Set(TiPa_Concrete::ResStore_Terminate);
 CREATE_SEQUENCE_PARSER(  ReferenceLine,       INCED_ID(ID.Sequence),  "reference with optional white-space before");

 CREATE_CHARACTER_PARSER( HexDigit,            INCED_ID(ID.Character), "hex-characters: 0...9, a...f, A...F");

 GET_PARSER(TiPa_Rule,         Name);
 GET_PARSER(TiPa_Counter,TagLineStartOpt);

 Digit       ->init(TiPa_Character::Digit);// all single digits

 HexDigit  ->init(TiPa_Character::HexDigit);// all single hex digits
 CharStartDec->init("&#");
 CharStartHex->init("&#x");   /// @todo optimize  reuse of CharStartDec  followed by 'x'

 DigitDec_cnt->init(TiPa_Counter::Cnt_OneOrMore,Digit);
 DigitHex_cnt->init(TiPa_Counter::Cnt_OneOrMore,HexDigit);

 Semicolon->init(';');
 And      ->init('&');
 Percent  ->init('%');

 CharRefDec_seq->hard(CharStartDec, DigitDec_cnt)->hard(Semicolon);
 CharRefHex_seq->hard(CharStartHex, DigitHex_cnt)->hard(Semicolon);
 CharRef_con->incOr(CharRefDec_seq, CharRefHex_seq);

 CharRef->init(CharRef_con);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  CharRef->reactionHit_set(&DebugReaction);

 EntityRef_seq->hard(And, Name)->hard(Semicolon);
 EntityRef->init(EntityRef_seq);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  EntityRef->reactionHit_set(&DebugReaction);

 PEReference_seq->hard(Percent, Name)->hard(Semicolon);
 PEReference->init(PEReference_seq);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  PEReference->reactionHit_set(&DebugReaction);
 PEReferenceLine->hard(TagLineStartOpt,PEReference);

 Reference_con->incOr(EntityRef, PEReference)->incOr(CharRef);
 Reference->init(Reference_con);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  Reference->reactionHit_set(&DebugReaction);
 ReferenceLine->hard(TagLineStartOpt,Reference);

}








/*  @MRTZ_describe defineRules_Literals
[9]   	EntityValue	   ::=   	'"' ([^%&"] | PEReference | Reference)* '"'
			|  "'" ([^%&'] | PEReference | Reference)* "'"
[10]   	AttValue	   ::=   	'"' ([^<&"] | Reference)* '"'
			|  "'" ([^<&'] | Reference)* "'"
[11]   	SystemLiteral	   ::=   	('"' [^"]* '"') | ("'" [^']* "'")
[12]   	PubidLiteral	   ::=   	'"' PubidChar* '"' | "'" (PubidChar - "'")* "'"
[13]   	PubidChar	   ::=   	#x20 | #xD | #xA | [a-zA-Z0-9] | [-'()+,./:=?;!*#@$_%]
*/
void XML_Parser::defineRules_Literals(void)
{
//{
 CREATE_CHARACTER_PARSER(   Quote,         INCED_ID(ID.Character),  "id-character: quote");
 CREATE_CHARACTER_PARSER(   Apostroph,     INCED_ID(ID.Character),  "id-character: apostrophe");
//}
//{
 CREATE_CHARACTER_PARSER(   EntityChar1,   INCED_ID(ID.Character),  "character: ^%&\"");
 CREATE_CHARACTER_PARSER(   EntityChar2,   INCED_ID(ID.Character),  "character: ^%&'");

 CREATE_CHARACTER_PARSER(   AttChar1,      INCED_ID(ID.Character),  "character: ^<&\"");
 CREATE_RULE_PARSER(        AttCharacter1, INCED_ID(ID.Rule),       "rule 1 of attribute characters: ^<&\"");
                            AttCharacter1->resultStorage_Set(TiPa_Concrete::ResStore_Terminate);
 CREATE_CHARACTER_PARSER(   AttChar2,      INCED_ID(ID.Character),  "character: ^<&'");
 CREATE_RULE_PARSER(        AttCharacter2, INCED_ID(ID.Rule),       "rule 2 of attribute characters: ^<&'");
                            AttCharacter2->resultStorage_Set(TiPa_Concrete::ResStore_Terminate);

 CREATE_CHARACTER_PARSER(   SystemChar1,   INCED_ID(ID.Character),  "character: ^\"");
 CREATE_CHARACTER_PARSER(   SystemChar2,   INCED_ID(ID.Character),  "character: ^\'");
 CREATE_CHARACTER_PARSER(   PubidChar,     INCED_ID(ID.Character),  "character: #x20 | #xD | #xA | [a-zA-Z0-9] | -'()+,./:=?;!*#@$_%");
 CREATE_CHARACTER_PARSER(   PubidChar2,    INCED_ID(ID.Character),  "character: #x20 | #xD | #xA | [a-zA-Z0-9] | -'()+,./:=?!*#@$_%");
//}
//{
 CREATE_CONDITION_PARSER(   EntityVal1_con, INCED_ID(ID.Condition), "body-character of EntityValue 1" );
 CREATE_COUNTER_PARSER(     EntityVal1_cnt, INCED_ID(ID.Counter),   "body-content of EntityValue 1" );
 CREATE_SEQUENCE_PARSER(    EntityVal1_seq, INCED_ID(ID.Sequence),  "parser of EntityValue 1" );
 CREATE_CONDITION_PARSER(   EntityVal2_con, INCED_ID(ID.Condition), "body-character of EntityValue 2" );
 CREATE_COUNTER_PARSER(     EntityVal2_cnt, INCED_ID(ID.Counter),   "body-content of EntityValue 2" );
 CREATE_SEQUENCE_PARSER(    EntityVal2_seq, INCED_ID(ID.Sequence),  "parser of EntityValue 2" );
 CREATE_CONDITION_PARSER(   EntityVal_con,  INCED_ID(ID.Condition), "parser of EntityValue  main" );

 CREATE_RULE_PARSER(        EntityValue,    INCED_ID(ID.Rule),      "rule of EntityValue" );
                            EntityValue->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
//}
//{
 CREATE_CONDITION_PARSER(   AttVal1_con,    INCED_ID(ID.Condition), "body-character of AttValue1" );
 CREATE_COUNTER_PARSER(     AttVal1_cnt,    INCED_ID(ID.Counter),   "body-content of AttValue1" );
 CREATE_RULE_PARSER(        AttVal1,        INCED_ID(ID.Rule),      "rule of AttValue1" );
                            AttVal1->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
 CREATE_SEQUENCE_PARSER(    AttVal1_seq,    INCED_ID(ID.Sequence),  "parser of AttValue1" );
 CREATE_CONDITION_PARSER(   AttVal2_con,    INCED_ID(ID.Condition), "body-character of AttValue2" );
 CREATE_COUNTER_PARSER(     AttVal2_cnt,    INCED_ID(ID.Counter),   "body-content of AttValue2" );
 CREATE_RULE_PARSER(        AttVal2,        INCED_ID(ID.Rule),      "rule of AttValue2" );
                            AttVal2->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
 CREATE_SEQUENCE_PARSER(    AttVal2_seq,    INCED_ID(ID.Sequence),  "parser of AttValue2" );
 CREATE_CONDITION_PARSER(   AttVal_con,     INCED_ID(ID.Condition), "body-character of AttValue main" );

 CREATE_RULE_PARSER(        AttValue,       INCED_ID(ID.Rule),      "rule of AttValue" );
                            AttValue->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
//}
//{
 CREATE_COUNTER_PARSER(     SysLit1_cnt,    INCED_ID(ID.Counter),   "body-content of AttValue1" );
 CREATE_SEQUENCE_PARSER(    SysLit1_seq,    INCED_ID(ID.Sequence),  "parser of AttValue1" );
 CREATE_COUNTER_PARSER(     SysLit2_cnt,    INCED_ID(ID.Counter),   "body-content of AttValue2" );
 CREATE_SEQUENCE_PARSER(    SysLit2_seq,    INCED_ID(ID.Sequence),  "parser of AttValue2" );
 CREATE_CONDITION_PARSER(   SysLit_con,     INCED_ID(ID.Condition), "body-character of AttValue main" );

 CREATE_RULE_PARSER(        SystemLiteral,  INCED_ID(ID.Rule),      "rule of AttValue" );
                            SystemLiteral->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
//}
//{
 CREATE_COUNTER_PARSER(     PubidLit1_cnt, INCED_ID(ID.Counter),    "body-content of PubidLiteral1" );
 CREATE_SEQUENCE_PARSER(    PubidLit1_seq, INCED_ID(ID.Sequence),   "parser of PubidLiteral" );
 CREATE_COUNTER_PARSER(     PubidLit2_cnt, INCED_ID(ID.Counter),    "body-content of PubidLiteral" );
 CREATE_SEQUENCE_PARSER(    PubidLit2_seq, INCED_ID(ID.Sequence),   "parser of PubidLiteral" );
 CREATE_CONDITION_PARSER(   PubidLit_con,  INCED_ID(ID.Condition),  "body-character of PubidLiteral main" );

 CREATE_RULE_PARSER(        PubidLiteral,  INCED_ID(ID.Rule),       "rule of PubidLiteral" );
                            PubidLiteral->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
//}
//{
 GET_PARSER(TiPa_Sequence,  PEReferenceLine);
 GET_PARSER(TiPa_Sequence,  ReferenceLine);
//}
//{
 Quote->init('\"');
 Apostroph->init('\'');
//}
//{

 EntityChar1->init(TiPa_Character::Anychar);
 EntityChar2->init(TiPa_Character::Anychar);
 AttChar1   ->init(TiPa_Character::Anychar);
 AttChar2   ->init(TiPa_Character::Anychar);
 SystemChar1->init(TiPa_Character::Anychar);
 SystemChar2->init(TiPa_Character::Anychar);

 EntityChar1->exclude("%&\"",3);
 EntityChar2->exclude("%&'",3);
 AttChar1   ->exclude("<&\"",3);
 AttChar2   ->exclude("<&'",3);
 SystemChar1->exclude("\"",1);
 SystemChar2->exclude("\'",1);

 AttCharacter1->init(AttChar1);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  AttCharacter1->reactionHit_set(&DebugReaction);
 AttCharacter2->init(AttChar2);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  AttCharacter2->reactionHit_set(&DebugReaction);

//}
//{
 PubidChar->init("-'()+,./:=?;!*#@$_%",19)
          ->include('a','z')
          ->include('A','Z')
          ->include('0','9')
          ->include(0x20)
          ->include(0x0D)
          ->include(0x0A);
 PubidChar2->init("-'()+,./:=?!*#@$_%",18)
           ->include('a','z')
           ->include('A','Z')
           ->include('0','9')
           ->include(0x20)
           ->include(0x0D)
           ->include(0x0A);
//}
//{
 EntityVal1_con->incOr(PEReferenceLine,ReferenceLine)->incOr(EntityChar1);
 EntityVal1_cnt->zeroOrMore(EntityVal1_con);
 EntityVal1_seq->hard(Quote,EntityVal1_cnt)->hard(Quote);

 EntityVal2_con->incOr(PEReferenceLine,ReferenceLine)->incOr(EntityChar2);
 EntityVal2_cnt->zeroOrMore(EntityVal2_con);
 EntityVal2_seq->hard(Apostroph,EntityVal2_cnt)->hard(Apostroph);

 EntityVal_con ->incOr(EntityVal1_seq,EntityVal2_seq);
 EntityValue   ->init(EntityVal_con);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  EntityValue->reactionHit_set(&DebugReaction);
//}
//{
 AttVal1_con->incOr(AttCharacter1,ReferenceLine);
 AttVal1_cnt->zeroOrMore(AttVal1_con);
 AttVal1->init(AttVal1_cnt);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  AttVal1->reactionHit_set(&DebugReaction);
 AttVal1_seq->hard(Quote,AttVal1)->hard(Quote);

 AttVal2_con->incOr(AttCharacter2,ReferenceLine);
 AttVal2_cnt->zeroOrMore(AttVal2_con);
 AttVal2->init(AttVal2_cnt);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  AttVal2->reactionHit_set(&DebugReaction);
 AttVal2_seq->hard(Apostroph,AttVal2)->hard(Apostroph);

 AttVal_con ->incOr(AttVal1_seq,AttVal2_seq);
 AttValue   ->init(AttVal_con);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  AttValue->reactionHit_set(&DebugReaction);
//}
//{
 SysLit1_cnt  ->zeroOrMore(SystemChar1);
 SysLit1_seq  ->hard(Quote,SysLit1_cnt)->hard(Quote);

 SysLit2_cnt  ->zeroOrMore(SystemChar2);
 SysLit2_seq  ->hard(Apostroph,SysLit2_cnt)->hard(Apostroph);

 SysLit_con   ->incOr(SysLit1_seq,SysLit2_seq);
 SystemLiteral->init(SysLit_con);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  SystemLiteral->reactionHit_set(&DebugReaction);
//}
//{
 PubidLit1_cnt->zeroOrMore(PubidChar);
 PubidLit1_seq->hard(Quote,PubidLit1_cnt)->hard(Quote);

 PubidLit2_cnt->zeroOrMore(PubidChar2);
 PubidLit2_seq->hard(Apostroph,PubidLit2_cnt)->hard(Apostroph);

 PubidLit_con->incOr(PubidLit1_seq,PubidLit2_seq);

 PubidLiteral->init(PubidLit_con);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  PubidLiteral->reactionHit_set(&DebugReaction);
//}





}



/*  @MRTZ_describe

  void XML_Parser::defineRules_XLS_ID(void)
{

}
*/


/*  @MRTZ_describe defineRules_CDATA

[2]   	Char	   ::=   	[#x1-#xD7FF] | [#xE000-#xFFFD] | [#x10000-#x10FFFF]
       // any Unicode character, excluding the surrogate blocks, FFFE, and FFFF.
[2a]   	RestrictedChar	   ::=   	[#x1-#x8] | [#xB-#xC] | [#xE-#x1F] | [#x7F-#x84] | [#x86-#x9F]

[18]   	CDSect	   ::=   	CDStart CData CDEnd
[19]   	CDStart	   ::=   	'<![CDATA['
[20]   	CData	   ::=   	(Char* - (Char* ']]>' Char*))
[21]   	CDEnd	   ::=   	']]>'


*/
void XML_Parser::defineRules_CDATA(void)
{
 CREATE_CHARACTER_PARSER(   Char,              INCED_ID(ID.Character), "all characters");

 CREATE_STRING_PARSER(      CharStart,         INCED_ID(ID.String), "opening token of CData");
 CREATE_STRING_PARSER(      CharEnd,           INCED_ID(ID.String), "closing token of CData");

 CREATE_COUNTER_PARSER(     CData_cnt,         INCED_ID(ID.Counter), "many characters");
 CREATE_CONDITION_PARSER(   CData_con,         INCED_ID(ID.Condition), "parser of CData");
 CREATE_RULE_PARSER(        CData,             INCED_ID(ID.Rule),   "rule of CData");
                            CData->resultStorage_Set(TiPa_Concrete::ResStore_Terminate);

 CREATE_SEQUENCE_PARSER(    CDSect_seq,        INCED_ID(ID.Sequence), "parser of CD section");
 CREATE_RULE_PARSER(        CDSect,            INCED_ID(ID.Rule),   "rule of CD section");
                            CDSect->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
 CREATE_SEQUENCE_PARSER(    CDSectLine,        INCED_ID(ID.Sequence), " CD section  with optional white-space before");

 GET_PARSER(TiPa_Counter,TagLineStartOpt);

 Char          ->init(TiPa_Character::Anychar);// all characters with an ordinal number between 1 and 255

 CharStart     ->init("<![CDATA[");                    /// @todo optimize '<' followed by '!' followed by string
 CharEnd       ->init("]]>");

 CData_con     ->exclusion(Char, CharEnd);
 CData_cnt     ->zeroOrMore(CData_con);
 CData         ->init(CData_cnt);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  CData->reactionHit_set(&DebugReaction);

 CDSect_seq    ->hard(CharStart, CData)->hard(CharEnd);
 CDSect        ->init(CDSect_seq);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  CDSect->reactionHit_set(&DebugReaction);
 CDSectLine->hard(TagLineStartOpt,CDSect);
}


/*  @MRTZ_describe defineRules_Comment
[15]   	Comment	   ::=   	'<!--' ((Char - '-') | ('-' (Char - '-')))* '-->'

*/
void XML_Parser::defineRules_Comment(void)
{
 CREATE_CHARACTER_PARSER(   Minus,                INCED_ID(ID.Character), "id-character: minus");

 CREATE_STRING_PARSER(      CommentStart,         INCED_ID(ID.String),    "opening token of Comment");
 CREATE_STRING_PARSER(      CommentEnd,           INCED_ID(ID.String),    "closing token of Comment");
 CREATE_CONDITION_PARSER(   AnyBtNtMinus,         INCED_ID(ID.Condition), "any character but not Minus");
 CREATE_SEQUENCE_PARSER(    Minus_seq,            INCED_ID(ID.Sequence),  "minus in a comment");
 CREATE_CONDITION_PARSER(   CommentChar,          INCED_ID(ID.Condition), "a character inside a comment");
 CREATE_COUNTER_PARSER(     CommentBody,          INCED_ID(ID.Counter),   "characters inside a comment");

 CREATE_SEQUENCE_PARSER(    Comment_seq,          INCED_ID(ID.Sequence),  "parser of a comment");
 CREATE_RULE_PARSER(        CommentOpen,          INCED_ID(ID.Rule),      "rule of a comment begin");
                            CommentOpen->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
 CREATE_RULE_PARSER(        CommentContent,       INCED_ID(ID.Rule),      "rule of a comment content");
                            CommentContent->resultStorage_Set(TiPa_Concrete::ResStore_Terminate);
 CREATE_RULE_PARSER(        CommentClose,         INCED_ID(ID.Rule),      "rule of a comment close");
                            CommentClose->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
 CREATE_RULE_PARSER(        Comment,              INCED_ID(ID.Rule),      "rule of a comment");
                            Comment->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
 CREATE_SEQUENCE_PARSER(    CommentLine,          INCED_ID(ID.Sequence),  "comment with optional white-space before");

 GET_PARSER(TiPa_Character, Char);
 GET_PARSER(TiPa_Counter,TagLineStartOpt);

 Minus         ->init('-');

 CommentStart  ->init("<!--");
 CommentEnd    ->init("-->");
 CommentOpen   ->init(CommentStart);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  CommentOpen->reactionHit_set(&DebugReaction);
 CommentClose  ->init(CommentEnd);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  CommentClose->reactionHit_set(&DebugReaction);

 AnyBtNtMinus  ->exclusion(Char,Minus);
 Minus_seq     ->hard(Minus,AnyBtNtMinus);
 CommentChar   ->incOr(AnyBtNtMinus,Minus_seq);
 CommentBody   ->zeroOrMore(CommentChar);
 CommentContent->init(CommentBody);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  CommentContent->reactionHit_set(&DebugReaction);

 Comment_seq->hard(CommentOpen, CommentContent)->hard(CommentClose);

 Comment->init(Comment_seq);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  Comment->reactionHit_set(&DebugReaction);
 CommentLine->hard(TagLineStartOpt,Comment);

}


/*  @MRTZ_describe
[16]   	PI	   ::=   	'<?' PITarget (S (Char* - (Char* '?>' Char*)))? '?>'
[17]   	PITarget	   ::=   	Name - (('X' | 'x') ('M' | 'm') ('L' | 'l'))

void XML_Parser::defineRules_StyleSheet(void)
{
//{
 CREATE_CHARACTER_PARSER(X,              INCED_ID(ID.Character), "character: x or X");
 CREATE_CHARACTER_PARSER(M,              INCED_ID(ID.Character), "character: m or M");
 CREATE_CHARACTER_PARSER(L,              INCED_ID(ID.Character), "character: l or L");

 CREATE_SEQUENCE_PARSER(XML_seq,         INCED_ID(ID.Sequence),  "character-sequence of xml");
 CREATE_CONDITION_PARSER(PITarget_con,   INCED_ID(ID.Condition), "parser of PITarget");
 CREATE_RULE_PARSER(PITarget,            INCED_ID(ID.Rule),      "rule of PITarget");
//}
//{
//CREATE_STRING_PARSER(DeclarationOpen,    INCED_ID(ID.String),    "open a style sheet tag");
//CREATE_STRING_PARSER(DeclarationClose,   INCED_ID(ID.String),    "close a style sheet tag");
CREATE_COUNTER_PARSER(CharOptional,      INCED_ID(ID.Counter),   "many characters" );
CREATE_SEQUENCE_PARSER(PInonContent,     INCED_ID(ID.Sequence),  "no style sheet tag character");
CREATE_CONDITION_PARSER(PIContent,       INCED_ID(ID.Condition), "style sheet tag characters");
CREATE_SEQUENCE_PARSER(PIContent_seq,    INCED_ID(ID.Sequence),  "style sheet tag content");
CREATE_COUNTER_PARSER(PIContentOptional, INCED_ID(ID.Counter),   "optional style sheet tag content");
CREATE_SEQUENCE_PARSER(PI_seq,           INCED_ID(ID.Sequence),  "parser of PI");
CREATE_RULE_PARSER(PI,                   INCED_ID(ID.Rule),      "rule of PI");
//}

//{
 GET_PARSER(TiPa_Rule,      Name);
 GET_PARSER(TiPa_Character, Char);
 GET_PARSER(TiPa_Rule,      Space);
 GET_PARSER(TiPa_String,    DeclarationOpen);
 GET_PARSER(TiPa_String,    DeclarationClose);



// GET_PARSER(TiPa_Counter, CharOptional);
//}



//{
 X->init('x')->include('X');
 M->init('m')->include('M');
 L->init('l')->include('L');
 XML_seq     ->hard(X, M)->hard(L);
 PITarget_con->exclusion(Name,XML_seq);
 PITarget    ->init(PITarget_con);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  PITarget->reactionHit_set(&DebugReaction);
//}
//{
// DeclarationOpen        ->init("<?");
// DeclarationClose       ->init("?>");
 CharOptional         ->zeroOrMore(Char);
 PInonContent     ->hard(CharOptional,DeclarationClose)->hard(CharOptional);
 PIContent        ->exclusion(CharOptional,PInonContent);
 PIContent_seq    ->hard(Space, PIContent);
 PIContentOptional->zeroOrOne(PIContent_seq);
 PI_seq           ->hard(DeclarationOpen,PITarget)->hard(PIContentOptional)->hard(DeclarationClose);
 PI               ->init(PI_seq);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  PI->reactionHit_set(&DebugReaction);

//}



}
*/





/*  @MRTZ_describe defineRules_ExternalEntity
 [Definition: If the entity is not internal, it is an external entity, declared as follows:]
External Entity Declaration


[75]   	ExternalID	   ::=   	'SYSTEM' S SystemLiteral
			| 'PUBLIC' S PubidLiteral S SystemLiteral
[76]   	NDataDecl	   ::=   	S 'NDATA' S Name 	[VC: Notation Declared]



*/
void XML_Parser::defineRules_ExternalEntity(void)
{
//{
 CREATE_STRING_PARSER(System,            INCED_ID(ID.String), "string: SYSTEM");
 CREATE_STRING_PARSER(Public,            INCED_ID(ID.String), "string: PUBLIC");
 CREATE_STRING_PARSER(NData,             INCED_ID(ID.String), "string: NDATA");

 CREATE_SEQUENCE_PARSER(System_seq,      INCED_ID(ID.Sequence), "system sequence");
 CREATE_SEQUENCE_PARSER(Public_seq,      INCED_ID(ID.Sequence), "public sequence");
 CREATE_SEQUENCE_PARSER(NData_seq,       INCED_ID(ID.Sequence),  "ndata sequence");

 CREATE_CONDITION_PARSER(ExternalID_con, INCED_ID(ID.Condition), "parser of external ID");
 CREATE_RULE_PARSER(ExternalID,          INCED_ID(ID.Rule), "rule of external ID");
                    ExternalID->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
 CREATE_RULE_PARSER(NDataDecl,           INCED_ID(ID.Rule),   "rule of n-data declaration");
                    NDataDecl->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
//}
//{
 GET_PARSER(TiPa_Rule, SystemLiteral);
 GET_PARSER(TiPa_Rule, PubidLiteral);
 GET_PARSER(TiPa_Rule, Space);
 GET_PARSER(TiPa_Rule, Name);
//}
//{
 System->init("SYSTEM");
 Public->init("PUBLIC");
 NData ->init("NDATA");
//}
//{
 System_seq->hard(System,Space)->hard(SystemLiteral);
 Public_seq->hard(Public,Space)->hard(PubidLiteral)->hard(Space)->hard(SystemLiteral);
 NData_seq ->hard(Space,NData)->hard(Space)->hard(Name);
//}

//{
 ExternalID_con->incOr(System,Public);
 ExternalID->init(ExternalID_con);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  ExternalID->reactionHit_set(&DebugReaction);
 NDataDecl->init(NData_seq);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  NDataDecl->reactionHit_set(&DebugReaction);
//}
}







/*  @MRTZ_describe defineRules_Entity
 [Definition: Entities are declared thus:]
Entity Declaration
[70]   	EntityDecl ::=   	GEDecl | PEDecl
[71]   	GEDecl	   ::=   	'<!ENTITY' S Name S EntityDef S? '>'
[72]   	PEDecl	   ::=   	'<!ENTITY' S '%' S Name S PEDef S? '>'
[73]   	EntityDef  ::=   	EntityValue | (ExternalID NDataDecl?)
[74]   	PEDef	   ::=   	EntityValue | ExternalID

  */
void XML_Parser::defineRules_Entity(void)
{
//{
 CREATE_STRING_PARSER(EntityOpen,         INCED_ID(ID.String), "string: open a entity declaration ");
 CREATE_COUNTER_PARSER(SpaceOptional,     INCED_ID(ID.Counter), "zero or one space");
 CREATE_COUNTER_PARSER(SpaceMulti,        INCED_ID(ID.Counter), "one or more space");
 CREATE_COUNTER_PARSER(NDataDeclOptional, INCED_ID(ID.Counter), "zero or one n-data declaration");

 CREATE_CONDITION_PARSER(PEDef_con,       INCED_ID(ID.Condition), "parser of pe-def");
 CREATE_RULE_PARSER(PEDef,                INCED_ID(ID.Rule),   "rule of pe-def");
                     PEDef->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
 CREATE_SEQUENCE_PARSER(EntityDef_seq,    INCED_ID(ID.Sequence), "possibility 2 of entity-definition");
 CREATE_CONDITION_PARSER(EntityDef_con,   INCED_ID(ID.Condition), "parser of entity-definition");
 CREATE_RULE_PARSER(EntityDef,            INCED_ID(ID.Rule),   "rule of entity-definition");
                    EntityDef->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
 CREATE_SEQUENCE_PARSER(PEDecl_seq,       INCED_ID(ID.Sequence), "parser of pe-declaration");
 CREATE_RULE_PARSER(PEDecl,               INCED_ID(ID.Rule),   "rule of pe-declaration");
                    PEDecl->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
 CREATE_SEQUENCE_PARSER(GEDecl_seq,       INCED_ID(ID.Sequence), "parser of ge-declaration");
 CREATE_RULE_PARSER(GEDecl,               INCED_ID(ID.Rule),   "rule of ge-declaration");
                    GEDecl->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
 CREATE_CONDITION_PARSER(EntityDecl_con,  INCED_ID(ID.Condition), "parser of entity-declaration");
 CREATE_RULE_PARSER(EntityDecl,           INCED_ID(ID.Rule),   "rule of entity-declaration");
                    EntityDecl->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
 CREATE_RULE_PARSER(SpacePreparse,        INCED_ID(ID.Rule),   "rule for pre-parsing of spaces");
                    SpacePreparse->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
//}
//{
 GET_PARSER(TiPa_Character, TagClose);
 GET_PARSER(TiPa_Character, Percent);
 GET_PARSER(TiPa_Rule, Space);
 GET_PARSER(TiPa_Rule, Name);
 GET_PARSER(TiPa_Rule, EntityValue);
 GET_PARSER(TiPa_Rule, ExternalID);
 GET_PARSER(TiPa_Rule, NDataDecl);
//}
//{
 EntityOpen->init("<!ENTITY");
 SpaceOptional->zeroOrOne(Space);
 SpaceMulti->oneOrMore(Space);

 NDataDeclOptional->zeroOrOne(NDataDecl);

//}
//{
   PEDef_con->incOr(EntityValue, ExternalID);
   PEDef->init(PEDef_con);
   if(TDA_GrmConcrete::Att.DebugMode == true)
    PEDef->reactionHit_set(&DebugReaction);

   EntityDef_seq->hard(ExternalID,NDataDeclOptional);
   EntityDef_con->incOr(EntityValue,EntityDef_seq);
   EntityDef->init(EntityDef_con);
   if(TDA_GrmConcrete::Att.DebugMode == true)
    EntityDef->reactionHit_set(&DebugReaction);

   PEDecl_seq->hard(EntityOpen,Space)->hard(Percent)->hard(Name)->hard(Space)
             ->hard(PEDef)->hard(SpaceOptional)->hard(TagClose);
   PEDecl->init(PEDecl_seq);
   if(TDA_GrmConcrete::Att.DebugMode == true)
    PEDecl->reactionHit_set(&DebugReaction);

   GEDecl_seq->hard(EntityOpen,Space)->hard(Name)->hard(Space)
             ->hard(EntityDef)->hard(SpaceOptional)->hard(TagClose);
   GEDecl->init(GEDecl_seq);
   if(TDA_GrmConcrete::Att.DebugMode == true)
    GEDecl->reactionHit_set(&DebugReaction);

   EntityDecl_con->incOr(GEDecl, PEDecl);
   EntityDecl->init(EntityDecl_con);
   if(TDA_GrmConcrete::Att.DebugMode == true)
    EntityDecl->reactionHit_set(&DebugReaction);
//}

//{
   SpacePreparse->init(SpaceOptional);
   if(TDA_GrmConcrete::Att.DebugMode == true)
    SpacePreparse->reactionHit_set(&DebugReaction);

//}
}





/*  @MRTZ_describe
[23]   	XMLDecl	   ::=   	'<?xml' VersionInfo EncodingDecl? SDDecl? S? '?>'
[24]   	VersionInfo	   ::=   	S 'version' Eq ("'" VersionNum "'" | '"' VersionNum '"')

[25]   	Eq	   ::=   	S? '=' S?
[26]   	VersionNum	   ::=   	'1.1'
[27]   	Misc	   ::=   	Comment | PI | S

Standalone Document Declaration
[32]   	SDDecl	   ::=   	S 'standalone' Eq (("'" ('yes' | 'no') "'") | ('"' ('yes' | 'no') '"')) 	[VC: Standalone Document Declaration]


[77]   	TextDecl	   ::=   	'<?xml' VersionInfo? EncodingDecl S? '?>'

[80]   	EncodingDecl	   ::=   	S 'encoding' Eq ('"' EncName '"' | "'" EncName "'" )
[81]   	EncName	   ::=   	[A-Za-z] ([A-Za-z0-9._] | '-')*	// Encoding name contains only Latin characters

void XML_Parser::defineRules_Text(void)
{
//{
  CREATE_CHARACTER_PARSER(Equal,             INCED_ID(ID.Character), "character: =");
  CREATE_SEQUENCE_PARSER(EQ_seq,             INCED_ID(ID.Sequence), "parser of equal");
  CREATE_RULE_PARSER(EQ,                     INCED_ID(ID.Rule),   "rule of equal");
  CREATE_STRING_PARSER(VersionNum_str,       INCED_ID(ID.String), "parser of version number");
  CREATE_RULE_PARSER(VersionNum,             INCED_ID(ID.Rule),   "rule of version number");
  CREATE_CONDITION_PARSER(Misc_con,          INCED_ID(ID.Condition), "parser of misc");
  CREATE_RULE_PARSER(Misc,                   INCED_ID(ID.Rule),   "rule of misc");

//}
//{
 CREATE_CHARACTER_PARSER(EncNameStart,       INCED_ID(ID.Character), "start of encoding name");
 CREATE_CHARACTER_PARSER(EncNameContinue,    INCED_ID(ID.Character), "continue of encoding name");
 CREATE_COUNTER_PARSER(EncNameBody,          INCED_ID(ID.Counter), "body of encoding name");
 CREATE_SEQUENCE_PARSER(EncName_seq,         INCED_ID(ID.Sequence), "parser of encoding name");
 CREATE_RULE_PARSER(EncName,                 INCED_ID(ID.Rule),   "rule of encoding name");
//}
//{
 CREATE_STRING_PARSER(Encoding_str,          INCED_ID(ID.String), "key word: encoding");
 CREATE_SEQUENCE_PARSER(EncodingValue1,      INCED_ID(ID.Sequence), "first encoding value variant");
 CREATE_SEQUENCE_PARSER(EncodingValue2,      INCED_ID(ID.Sequence), "second encoding value variant");
 CREATE_CONDITION_PARSER(EncodingValue,      INCED_ID(ID.Condition), "encoding value");
 CREATE_SEQUENCE_PARSER(EncodingDecl_seq,    INCED_ID(ID.Sequence), "parser of encoding");
 CREATE_RULE_PARSER(EncodingDecl,            INCED_ID(ID.Rule)  , "rule of encoding");
//}
//{
 CREATE_STRING_PARSER(VersionInfo_str,       INCED_ID(ID.String), "key word: version info");
 CREATE_SEQUENCE_PARSER(VersionInfoValue1,   INCED_ID(ID.Sequence), "first version info value variant");
 CREATE_SEQUENCE_PARSER(VersionInfoValue2,   INCED_ID(ID.Sequence), "second version info value variant");
 CREATE_CONDITION_PARSER(VersionInfoValue,   INCED_ID(ID.Condition), "version info value");
 CREATE_SEQUENCE_PARSER(VersionInfo_seq,     INCED_ID(ID.Sequence), "parser of version info");
 CREATE_RULE_PARSER(VersionInfo,             INCED_ID(ID.Rule)  , "rule of version info");
//}
//{
 CREATE_STRING_PARSER(SDDecl_str,            INCED_ID(ID.String), "key word: standalone declaration");
 CREATE_STRING_PARSER(YesOrNo_str,           INCED_ID(ID.String), "key words: yes | no");
 CREATE_SEQUENCE_PARSER(SDDeclValue1,        INCED_ID(ID.Sequence), "first standalone declaration value variant");
 CREATE_SEQUENCE_PARSER(SDDeclValue2,        INCED_ID(ID.Sequence), "second standalone declaration value variant");
 CREATE_CONDITION_PARSER(SDDeclValue,        INCED_ID(ID.Condition), "standalone declaration value");
 CREATE_SEQUENCE_PARSER(SDDecl_seq,          INCED_ID(ID.Sequence), "parser of standalone declaration");
 CREATE_RULE_PARSER(SDDecl,                  INCED_ID(ID.Rule)  , "rule of standalone declaration");
//}
//{

//}
//{
 CREATE_STRING_PARSER(XML_DeclTag,              INCED_ID(ID.String), "start of xml and text declaration tag");
 CREATE_COUNTER_PARSER(EncodingDeclOptional, INCED_ID(ID.Counter), "optional occurrence of encoding declaration");
 CREATE_COUNTER_PARSER(SDDeclOptional,       INCED_ID(ID.Counter), "optional occurrence of standalone declaration");
 CREATE_SEQUENCE_PARSER(XMLDecl_seq,         INCED_ID(ID.Sequence), "parser of xml declaration");
 CREATE_RULE_PARSER(XMLDecl,                 INCED_ID(ID.Rule),   "rule of xml declaration");
//}
//{
 CREATE_COUNTER_PARSER(VersionInfoOptional,  INCED_ID(ID.Counter), "optional occurrence of version info");
 CREATE_SEQUENCE_PARSER(TextDecl_seq,        INCED_ID(ID.Sequence), "parser of text declaration");
 CREATE_RULE_PARSER(TextDecl,                INCED_ID(ID.Rule),   "rule of text declaration");
//}


//}

//{
 GET_PARSER(TiPa_Rule,      Space);
 GET_PARSER(TiPa_Counter,   SpaceOptional);
// GET_PARSER(TiPa_Rule,      PI);
 GET_PARSER(TiPa_Rule,      Declaration);
 GET_PARSER(TiPa_Rule,      Comment);
 GET_PARSER(TiPa_Character, Quote);
 GET_PARSER(TiPa_Character, Apostroph);
 GET_PARSER(TiPa_String,    DeclarationOpen);
 GET_PARSER(TiPa_String,    DeclarationClose);
//}
//{
 Equal->init('=');
 EQ_seq->hard(SpaceOptional,Equal)->hard(SpaceOptional);
 EQ->init(EQ_seq);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  EQ->reactionHit_set(&DebugReaction);

 VersionNum_str->init("1.0");
 VersionNum->init(VersionNum_str);
// Misc_con->incOr(Comment,PI)->incOr(Space);
 Misc_con->incOr(Comment,Declaration)->incOr(Space);
 Misc->init(Misc_con);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  Misc->reactionHit_set(&DebugReaction);
//}
//{
 EncNameStart   ->init('a','z')->include('A','Z');
 EncNameContinue->init('a','z')->include('A','Z')->include('0','9')->include('.')->include('_')->include('-');
 EncNameBody    ->zeroOrMore(EncNameContinue);
 EncName_seq    ->hard(EncNameStart,EncNameBody);
 EncName        ->init(EncName_seq);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  EncName->reactionHit_set(&DebugReaction);
//}
//{
 Encoding_str->init("encoding");
 EncodingValue1->hard(Quote,    EncName)->hard(Quote);
 EncodingValue2->hard(Apostroph,EncName)->hard(Apostroph);
 EncodingValue->incOr(EncodingValue1,EncodingValue2);
 EncodingDecl_seq->hard(Space,Encoding_str)->hard(EQ)->hard(EncodingValue);
 EncodingDecl->init(EncodingDecl_seq);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  EncodingDecl->reactionHit_set(&DebugReaction);

//}
//{
 VersionInfo_str->init("version");
 VersionInfoValue1->hard(Quote,    VersionNum)->hard(Quote);
 VersionInfoValue2->hard(Apostroph,VersionNum)->hard(Apostroph);
 VersionInfoValue->incOr(VersionInfoValue1,VersionInfoValue2);
 VersionInfo_seq->hard(Space,VersionInfo_str)->hard(EQ)->hard(VersionInfoValue);
 VersionInfo->init(VersionInfo_seq);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  VersionInfo->reactionHit_set(&DebugReaction);
//}
//{
 SDDecl_str->init("standalone");
 YesOrNo_str->init("yes")->include("no");
 SDDeclValue1->hard(Quote,    YesOrNo_str)->hard(Quote);
 SDDeclValue2->hard(Apostroph,YesOrNo_str)->hard(Apostroph);
 SDDeclValue->incOr(SDDeclValue1,SDDeclValue2);
 SDDecl_seq->hard(Space,SDDecl_str)->hard(EQ)->hard(SDDeclValue);
 SDDecl->init(SDDecl_seq);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  SDDecl->reactionHit_set(&DebugReaction);
//}
//{
 XML_DeclTag->init("xml");
 EncodingDeclOptional->zeroOrOne(EncodingDecl);
 SDDeclOptional->zeroOrOne(SDDecl);
 XMLDecl_seq->hard(DeclarationOpen,XML_DeclTag)->hard(VersionInfo)
            ->hard(EncodingDeclOptional)->hard(SDDeclOptional)->hard(SpaceOptional)
            ->hard(DeclarationClose);
 XMLDecl->init(XMLDecl_seq);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  XMLDecl->reactionHit_set(&DebugReaction);
//}
//{
 VersionInfoOptional->zeroOrOne(VersionInfo);
 TextDecl_seq->hard(DeclarationOpen,XML_DeclTag)->hard(VersionInfoOptional)
             ->hard(EncodingDecl)->hard(SpaceOptional)
             ->hard(DeclarationClose);
 TextDecl->init(TextDecl_seq);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  TextDecl->reactionHit_set(&DebugReaction);
//}
}
*/





/*  @MRTZ_describe defineRules_Attribute



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

*/
void XML_Parser::defineRules_Attribute(void)
{
//{

 CREATE_STRING_PARSER(DefaultDecl_str,       INCED_ID(ID.String), "first strings of default declarations");
 CREATE_STRING_PARSER(Fixed_str,             INCED_ID(ID.String), "third string of default declarations");
 CREATE_SEQUENCE_PARSER(Fixed1_seq,          INCED_ID(ID.Sequence), "first sequence of default declarations");
 CREATE_COUNTER_PARSER(Fixed_cnt,            INCED_ID(ID.Counter), "option of default declarations");
 CREATE_SEQUENCE_PARSER(Fixed2_seq,          INCED_ID(ID.Sequence), "second sequence of default declarations");
 CREATE_CONDITION_PARSER(DefaultDecl_con,    INCED_ID(ID.Condition), "parser of default declarations");
 CREATE_RULE_PARSER(DefaultDecl,             INCED_ID(ID.Rule),   "rule of default declarations");
                    DefaultDecl->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
//}
//{
 CREATE_CHARACTER_PARSER(ParaOpen,           INCED_ID(ID.Character),"character: parenthesis open");
 CREATE_CHARACTER_PARSER(ParaClose,          INCED_ID(ID.Character),"character: parenthesis close");
 CREATE_CHARACTER_PARSER(OrLine,             INCED_ID(ID.Character),"character: parenthesis close");

 CREATE_SEQUENCE_PARSER(Nmtoken_tab,         INCED_ID(ID.Sequence), "internal sequence of nm tokens");
 CREATE_COUNTER_PARSER(Nmtoken_lst,          INCED_ID(ID.Counter), "tabled list of nm tokens");
 CREATE_SEQUENCE_PARSER(Enumeration2_seq,    INCED_ID(ID.Sequence), "parser of enumeration");
 CREATE_RULE_PARSER(Enumeration,             INCED_ID(ID.Rule),   "rule of enumeration");
                    Enumeration->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
//}
//{
 CREATE_STRING_PARSER(Notation_str,          INCED_ID(ID.String), "first strings of notation type");

 CREATE_SEQUENCE_PARSER(Name_tab,            INCED_ID(ID.Sequence), "internal sequence of names ");
 CREATE_COUNTER_PARSER(Name_lst,             INCED_ID(ID.Counter), "tabled list of names");
 CREATE_SEQUENCE_PARSER(NotationType2_seq,   INCED_ID(ID.Sequence), "parser of notation type");
 CREATE_RULE_PARSER(NotationType,            INCED_ID(ID.Rule),   "rule of notation type");
                    NotationType->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
//}
//{
 CREATE_CONDITION_PARSER(EnumeratedType_con, INCED_ID(ID.Condition), "parser of enumeration type");
 CREATE_RULE_PARSER(EnumeratedType,          INCED_ID(ID.Rule),   "rule of enumeration type");
                    EnumeratedType->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
//}
//{
  CREATE_STRING_PARSER(TokenizedType_str,    INCED_ID(ID.String), "parser of tokenized type");
  CREATE_RULE_PARSER(TokenizedType,          INCED_ID(ID.Rule),   "rule of tokenized type");
                     TokenizedType->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
  CREATE_STRING_PARSER(StringType_str,       INCED_ID(ID.String), "parser of string type");
  CREATE_RULE_PARSER(StringType,             INCED_ID(ID.Rule),   "rule of string type");
                     StringType->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
  CREATE_CONDITION_PARSER(AttType_cnd,       INCED_ID(ID.Condition), "parser of attribute type");
  CREATE_RULE_PARSER(AttType,                INCED_ID(ID.Rule),   "parser of attribute type");
                     AttType->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
//}
//{
  CREATE_SEQUENCE_PARSER(AttDef_seq,         INCED_ID(ID.Sequence), "parser of attribute definition");
  CREATE_RULE_PARSER(AttDef,                 INCED_ID(ID.Rule),   "rule of attribute definition");
                     AttDef->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
  CREATE_STRING_PARSER(AttlistDecl_str,      INCED_ID(ID.String), "opening tag of attribute list declaration");
  CREATE_COUNTER_PARSER(AttDef_cnt,          INCED_ID(ID.Counter), "many optional attribute definitions");
  CREATE_SEQUENCE_PARSER(AttlistDecl_seq,    INCED_ID(ID.Sequence), "parser of attribute list declaration");
  CREATE_RULE_PARSER(AttlistDecl,            INCED_ID(ID.Rule),   "rule of attribute list declaration");
                     AttlistDecl->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
//}
//{
  CREATE_CHARACTER_PARSER(Equal,             INCED_ID(ID.Character), "character: =");
  CREATE_SEQUENCE_PARSER(EQ_seq,             INCED_ID(ID.Sequence), "parser of equal");
  CREATE_RULE_PARSER(EQ,                     INCED_ID(ID.Rule),   "rule of equal");
                     EQ->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
//}
//{
  CREATE_SEQUENCE_PARSER(Attribute_seq,      INCED_ID(ID.Sequence), "parser of attribute");
  CREATE_RULE_PARSER(Attribute,              INCED_ID(ID.Rule),   "rule of attribute");
                     Attribute->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
//}


//{
 GET_PARSER( TiPa_Rule,      AttValue);
 GET_PARSER( TiPa_Rule,      Space);
 GET_PARSER( TiPa_Counter,   SpaceOptional);
 GET_PARSER( TiPa_Rule,      Nmtoken);
 GET_PARSER( TiPa_Rule,      Name);
 GET_PARSER( TiPa_Character, TagClose);

//}
//{
 DefaultDecl_str->init("#REQUIRED")->include("#IMPLIED");   /// @todo optimize   '#' followed by string
 Fixed_str->init("#FIXED");                                 /// @todo optimize   '#' followed by string
 Fixed1_seq->hard(Fixed_str,Space);
 Fixed_cnt->zeroOrOne(Fixed1_seq);
 Fixed2_seq->hard(Fixed_cnt,AttValue);
 DefaultDecl_con->incOr(DefaultDecl_str,Fixed2_seq);
 DefaultDecl->init(DefaultDecl_con);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  DefaultDecl->reactionHit_set(&DebugReaction);
//}
//{
 ParaOpen ->init('(');
 ParaClose->init(')');
 OrLine   ->init('|');
 Nmtoken_tab->hard(SpaceOptional,OrLine)->hard(SpaceOptional)->hard(Nmtoken);
 Nmtoken_lst ->zeroOrMore(Nmtoken_tab);
 Enumeration2_seq->hard(ParaOpen,SpaceOptional)->hard(Nmtoken)
                 ->hard(Nmtoken_lst)->hard(SpaceOptional)->hard(ParaClose);
 Enumeration->init(Enumeration2_seq);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  Enumeration->reactionHit_set(&DebugReaction);

//}

//{
 Notation_str     ->init("NOTATION");
 Name_tab->hard(SpaceOptional,OrLine)->hard(SpaceOptional)->hard(Name);
 Name_lst ->zeroOrMore(Name_tab);
 NotationType2_seq->hard(Notation_str,Space)->hard(ParaOpen)->hard(SpaceOptional)
                  ->hard(Name)->hard(Name_lst)->hard(SpaceOptional)->hard(ParaClose);
 NotationType     ->init(NotationType2_seq);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  NotationType->reactionHit_set(&DebugReaction);

//}
//{
 EnumeratedType_con->incOr(Enumeration,NotationType);
 EnumeratedType->init(EnumeratedType_con);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  EnumeratedType->reactionHit_set(&DebugReaction);
//}
//{
  TokenizedType_str->init("ID")->include("IDREF")->include("IDREFS")
                   ->include("ENTITY") ->include("ENTITIES")
                   ->include("NMTOKEN")->include("NMTOKENS");
  TokenizedType->init(TokenizedType_str);
  if(TDA_GrmConcrete::Att.DebugMode == true)
   TokenizedType->reactionHit_set(&DebugReaction);
  StringType_str->init("CDATA");
  StringType->init(StringType_str);
  if(TDA_GrmConcrete::Att.DebugMode == true)
   StringType->reactionHit_set(&DebugReaction);
  AttType_cnd->incOr(StringType,TokenizedType)->incOr(EnumeratedType);
  AttType->init(AttType_cnd);
  if(TDA_GrmConcrete::Att.DebugMode == true)
   AttType->reactionHit_set(&DebugReaction);
//}
//{
 AttDef_seq->hard(Space,Name)->hard(Space)->hard(AttType)->hard(Space)->hard(DefaultDecl);
 AttDef->init(AttDef_seq);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  AttDef->reactionHit_set(&DebugReaction);
 AttlistDecl_str->init("<!ATTLIST");
 AttDef_cnt->zeroOrMore(AttDef);
 AttlistDecl_seq->hard(AttlistDecl_str,Space)->hard(Name)->hard(AttDef_cnt)->hard(SpaceOptional)->hard(TagClose);
 AttlistDecl->init(AttlistDecl_seq);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  AttlistDecl->reactionHit_set(&DebugReaction);
//}

//{
 Equal->init('=');
 EQ_seq->hard(SpaceOptional,Equal)->hard(SpaceOptional);
 EQ->init(EQ_seq);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  EQ->reactionHit_set(&DebugReaction);
//}

//{
 Attribute_seq->hard(Name,EQ)->hard(AttValue);
 Attribute->init(Attribute_seq);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  Attribute->reactionHit_set(&DebugReaction);

//}
}




/*  @MRTZ_describe defineRules_Tag




Start-tag
[40]   	STag	   ::=   	'<' Name (S Attribute)* S? '>'	[WFC: Unique Att Spec]

End-tag
[42]   	ETag	   ::=   	'</' Name S? '>'


Tags for Empty Elements
[44]   	EmptyElemTag	   ::=   	'<' Name (S Attribute)* S? '/>'	[WFC: Unique Att Spec]


*/
void XML_Parser::defineRules_Tag(void)
{
//{
  CREATE_CHARACTER_PARSER(   TagOpen,        INCED_ID(ID.Character), "character: <");
  CREATE_CHARACTER_PARSER(   TagClose,       INCED_ID(ID.Character), "character: >");
  CREATE_STRING_PARSER(ETagOpen,             INCED_ID(ID.String), "open an end-tag");
  CREATE_STRING_PARSER(EmptyElemTagClose,    INCED_ID(ID.String), "close an empty-element tag");
  CREATE_COUNTER_PARSER(     EndOfText,      INCED_ID(ID.Counter), "end of text to parse");
//}
//{
  CREATE_SEQUENCE_PARSER(Attribute_tab,      INCED_ID(ID.Sequence), "tabled attribute ");
  CREATE_COUNTER_PARSER(Attribute_list,      INCED_ID(ID.Counter), "attribute list ");
//}
//{
  CREATE_SEQUENCE_PARSER(STag_seq,           INCED_ID(ID.Sequence), "parser of start tag");
  CREATE_RULE_PARSER(STag,                   INCED_ID(ID.Rule),   "rule of start tag");
                     STag->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
  CREATE_SEQUENCE_PARSER(ETag_seq,           INCED_ID(ID.Sequence), "parser of end tag");
  CREATE_RULE_PARSER(ETag,                   INCED_ID(ID.Rule),   "rule of end tag");
                     ETag->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
  CREATE_SEQUENCE_PARSER(EmptyElemTag_seq,   INCED_ID(ID.Sequence), "parser of empty-element tag");
  CREATE_RULE_PARSER(EmptyElemTag,           INCED_ID(ID.Rule),   "rule of empty-element tag");
                     EmptyElemTag->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);

//}
//{
 GET_PARSER(TiPa_Character, Char);
 GET_PARSER(TiPa_Rule,      Attribute);
 GET_PARSER(TiPa_Counter,   SpaceOptional);
 GET_PARSER(TiPa_Counter,   SpaceMulti);
 GET_PARSER(TiPa_Rule,      Name);

//}
//{
  TagOpen->init('<') ;// begin of start, end and empty-tag
  TagClose->init('>') ;// end of start, end and empty-tag
  EmptyElemTagClose->init("/>");
  ETagOpen->init("</");
  EndOfText->allButNot(Char);       //end of text to parse
//}
//{
 Attribute_tab->hard(SpaceMulti,Attribute);
 Attribute_list->zeroOrMore(Attribute_tab);
//}

//{
 STag_seq->hard(TagOpen,Name)->hard(Attribute_list)->hard(SpaceOptional)->hard(TagClose);
 STag->init(STag_seq);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  STag->reactionHit_set(&DebugReaction);
 ETag_seq->hard(ETagOpen,Name)->hard(SpaceOptional)->hard(TagClose);
 ETag->init(ETag_seq);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  ETag->reactionHit_set(&DebugReaction);

 EmptyElemTag_seq->hard(TagOpen,Name)->hard(Attribute_list)->hard(SpaceOptional)->hard(EmptyElemTagClose);
 EmptyElemTag->init(EmptyElemTag_seq);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  EmptyElemTag->reactionHit_set(&DebugReaction);
//}

//{

//}
}











/*  @MRTZ_describe defineRules_Element
Element
[39]   	element	   ::=   	EmptyElemTag
			| STag content ETag 	[WFC: Element Type Match]
				[VC: Element Valid]


Content of Elements

[14]   	CharData   ::=   	[^<&]* - ([^<&]* ']]>' [^<&]*)


[43]   	content	   ::=   	CharData? ((element | Reference | CDSect | PI | Comment) CharData?)*

[45]   	elementdecl	   ::=   	'<!ELEMENT' S Name S contentspec S? '>'	[VC: Unique Element Type Declaration]
[46]   	contentspec	   ::=   	'EMPTY' | 'ANY' | Mixed | children

[47]   	children	   ::=   	(choice | seq) ('?' | '*' | '+')?
[48]   	cp	   ::=   	(Name | choice | seq) ('?' | '*' | '+')?
[49]   	choice	   ::=   	'(' S? cp ( S? '|' S? cp )+ S? ')'	[VC: Proper Group/PE Nesting]
[50]   	seq	       ::=   	'(' S? cp ( S? ',' S? cp )* S? ')'	[VC: Proper Group/PE Nesting]

[51]   	Mixed	   ::=   	'(' S? '#PCDATA' (S? '|' S? Name)* S? ')*'
			| '(' S? '#PCDATA' S? ')' 	[VC: Proper Group/PE Nesting]


*/
void XML_Parser::defineRules_Element(void)
{
//{
  CREATE_STRING_PARSER(ElementOpen,          INCED_ID(ID.String), "open an element declaration");
  CREATE_STRING_PARSER(ContntSpc_str,        INCED_ID(ID.String), "string : EMPTY | ANY");
  CREATE_STRING_PARSER(PCDATA_str,           INCED_ID(ID.String), "string : #PCDATA");
  CREATE_STRING_PARSER(MixedClose_str,       INCED_ID(ID.String), "string : )*");
  CREATE_CHARACTER_PARSER(ChildChar,         INCED_ID(ID.Character), "element operators");
  CREATE_COUNTER_PARSER(ChildCharOption,     INCED_ID(ID.Counter), "element operators");
  CREATE_CHARACTER_PARSER(   Comma,          INCED_ID(ID.Character), "character: ,");
//}
//{
  CREATE_SEQUENCE_PARSER(Mixed1_seq,         INCED_ID(ID.Sequence), "first possible mixed sequence");
  CREATE_SEQUENCE_PARSER(Mixed2_seq,         INCED_ID(ID.Sequence), "second possible mixed sequence");
  CREATE_CONDITION_PARSER(Mixed_cnd,         INCED_ID(ID.Condition), "parser of mixed");
  CREATE_RULE_PARSER(Mixed,                  INCED_ID(ID.Rule),   "rule of mixed");
                     Mixed->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
//}
//{
  CREATE_SEQUENCE_PARSER(SeqIntern_seq,      INCED_ID(ID.Sequence), "internal element sequence");
  CREATE_COUNTER_PARSER( SeqIntern_cnt,      INCED_ID(ID.Counter), "internal element sequence optional");
  CREATE_SEQUENCE_PARSER(Seq_seq,            INCED_ID(ID.Sequence), "parser of element sequence");
  CREATE_RULE_PARSER(Seq,                    INCED_ID(ID.Rule),   "rule of element sequence");
                     Seq->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
  CREATE_SEQUENCE_PARSER(ChoiceIntern_seq,   INCED_ID(ID.Sequence), "internal element choice sequence");
  CREATE_COUNTER_PARSER( ChoiceIntern_cnt,   INCED_ID(ID.Counter), "internal element choice sequence optional");
  CREATE_SEQUENCE_PARSER(Choice_seq,         INCED_ID(ID.Sequence), "parser of element choice");
  CREATE_RULE_PARSER(Choice,                 INCED_ID(ID.Rule),   "rule of element choice");
                     Choice->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
//}
//{
  CREATE_CONDITION_PARSER(CP_cnd,            INCED_ID(ID.Condition), "internal alternative of cp");
  CREATE_SEQUENCE_PARSER(CP_seq,             INCED_ID(ID.Sequence), "parser of cp");
  CREATE_RULE_PARSER(CP,                     INCED_ID(ID.Rule),   "rule of cp");
                     CP->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
  CREATE_CONDITION_PARSER(Children_cnd,      INCED_ID(ID.Condition), "internal alternative of children");
  CREATE_SEQUENCE_PARSER(Children_seq,       INCED_ID(ID.Sequence), "parser of children");
  CREATE_RULE_PARSER(Children,               INCED_ID(ID.Rule),   "rule of children");
                     Children->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
//}
//{

 CREATE_CHARACTER_PARSER(   CharData_grp,      INCED_ID(ID.Character), "group of CharData characters");

 CREATE_CONDITION_PARSER(   CharData_con,      INCED_ID(ID.Condition), "first parser of CharData");
 CREATE_CONDITION_PARSER(   CharData_con2,     INCED_ID(ID.Condition), "second parser of CharData");
 CREATE_COUNTER_PARSER(     CharData_cnt,      INCED_ID(ID.Counter), "first CharData sequence");
 CREATE_RULE_PARSER(        CharNormal,        INCED_ID(ID.Rule),   "rule of normal CharData sequence");
                            CharNormal->resultStorage_Set(TiPa_Concrete::ResStore_Terminate);
 CREATE_COUNTER_PARSER(     CharData_cnt2,     INCED_ID(ID.Counter), "second CharData sequence");

 CREATE_RULE_PARSER(        CharData,          INCED_ID(ID.Rule),   "rule of CharData");
                            CharData->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
 CREATE_SEQUENCE_PARSER(CharDataLine,          INCED_ID(ID.Sequence), "char-data with optional white-space before");




//}
//{
  CREATE_CONDITION_PARSER(Contentspec_cnd,   INCED_ID(ID.Condition), "parser of content specification");
  CREATE_RULE_PARSER(Contentspec,            INCED_ID(ID.Rule),   "rule of content specification");
                     Contentspec->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
  CREATE_SEQUENCE_PARSER(Elementdecl_seq,    INCED_ID(ID.Sequence), "parser of element declaration");
  CREATE_RULE_PARSER(Elementdecl,            INCED_ID(ID.Rule),   "rule of element declaration");
                     Elementdecl->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
  CREATE_COUNTER_PARSER(CharDataOption,      INCED_ID(ID.Counter), "optional chard data");
  CREATE_CONDITION_PARSER(Content_cnd,       INCED_ID(ID.Condition), "internal element content condition");
  CREATE_COUNTER_PARSER(Content_lst,         INCED_ID(ID.Counter), "list of internal element content ");
  CREATE_RULE_PARSER(Content,                INCED_ID(ID.Rule),   "rule of internal element content ");
                     Content->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
//}
//{
  CREATE_SEQUENCE_PARSER(Element_seq,        INCED_ID(ID.Sequence), "not empty element");
  CREATE_CONDITION_PARSER(Element_cnd,       INCED_ID(ID.Condition), "parser of element");
  CREATE_RULE_PARSER(Element,                INCED_ID(ID.Rule),   "rule of element");
                     Element->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
  CREATE_SEQUENCE_PARSER(ElementLine,        INCED_ID(ID.Sequence), "element with optional white-space before");

//}
//{
  GET_PARSER(TiPa_Rule,EmptyElemTag);
  GET_PARSER(TiPa_Rule,STag);
  GET_PARSER(TiPa_Rule,ETag);
  GET_PARSER(TiPa_String,CharEnd);
  GET_PARSER(TiPa_Rule,Reference);
  GET_PARSER(TiPa_Sequence,CDSectLine);
  GET_PARSER(TiPa_Sequence,DeclarationLine);
  GET_PARSER(TiPa_Sequence,CommentLine);
  GET_PARSER(TiPa_Rule,Name);
  GET_PARSER(TiPa_Rule,Space);
  GET_PARSER(TiPa_Counter,SpaceOptional);
  GET_PARSER(TiPa_Character,ParaOpen);
  GET_PARSER(TiPa_Character,ParaClose);
  GET_PARSER(TiPa_Character,TagClose);
  GET_PARSER(TiPa_Character,OrLine);
  GET_PARSER(TiPa_Sequence,Name_lst);
  GET_PARSER(TiPa_Counter,TagLineStartOpt);
//}



//}
//{
 ElementOpen    ->init("<!ELEMENT");                    /// @todo optimize '<' followed by '!' followed by string
 ContntSpc_str  ->init("EMPTY")->include("ANY");
 PCDATA_str     ->init("#PCDATA");                      /// @todo optimize  '#' followed by string
 MixedClose_str ->init(")*");
 ChildChar      ->init("?*+",3);
 ChildCharOption->zeroOrOne(ChildChar);
 Comma          ->init(',') ;
//}
//{
 Mixed1_seq->hard(ParaOpen,SpaceOptional)->hard(PCDATA_str)->hard(Name_lst)
           ->hard(SpaceOptional)->hard(MixedClose_str);
 Mixed2_seq->hard(ParaOpen,SpaceOptional)->hard(PCDATA_str)
           ->hard(SpaceOptional)->hard(ParaClose);
 Mixed_cnd->incOr(Mixed1_seq,Mixed2_seq);
 Mixed->init(Mixed_cnd);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  Mixed->reactionHit_set(&DebugReaction);
//}
//{
 SeqIntern_seq->hard(SpaceOptional,Comma)->hard(SpaceOptional)->hard(CP);
 SeqIntern_cnt->zeroOrMore(SeqIntern_seq);
 Seq_seq      ->hard(ParaOpen,SpaceOptional)->hard(CP)->hard(SeqIntern_cnt)->hard(SpaceOptional)->hard(ParaClose);
 Seq          ->init(Seq_seq);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  Seq->reactionHit_set(&DebugReaction);

 ChoiceIntern_seq->hard(SpaceOptional,OrLine)->hard(SpaceOptional)->hard(CP);
 ChoiceIntern_cnt->oneOrMore(ChoiceIntern_seq);
 Choice_seq      ->hard(ParaOpen,SpaceOptional)->hard(CP)->hard(ChoiceIntern_cnt)->hard(SpaceOptional)->hard(ParaClose);
 Choice          ->init(Choice_seq);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  Choice->reactionHit_set(&DebugReaction);
//}
//{
 CP_cnd->incOr(Name,Choice)->incOr(Seq);
 CP_seq->hard(CP_cnd,ChildCharOption);
 CP->init(CP_seq);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  CP->reactionHit_set(&DebugReaction);
 Children_cnd->incOr(Choice,Seq);
 Children_seq->hard(Children_cnd,ChildCharOption);
 Children->init(Children_seq);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  Children->reactionHit_set(&DebugReaction);
//}

//{

 CharData_grp  ->init(TiPa_Character::Anychar);
 CharData_grp  ->exclude("<&",2);
 CharData_grp  ->exclude(10);
 CharData_grp  ->exclude(13);


 CharData_con  ->exclusion(CharData_grp, CharEnd);
 CharData_cnt  ->oneOrMore( CharData_con);
 CharNormal    ->init(CharData_cnt);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  CharNormal->reactionHit_set(&DebugReaction);
 CharData_con2 ->incOr(CharNormal,Reference);
 CharData_cnt2  ->oneOrMore( CharData_con2);

 CharData      ->init(CharData_cnt2);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  CharData->reactionHit_set(&DebugReaction);
 CharDataLine->hard(TagLineStartOpt,CharData);

//}

//{
 Contentspec_cnd->incOr(Children,Mixed)->incOr(ContntSpc_str);
 Contentspec->init(Contentspec_cnd);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  Contentspec->reactionHit_set(&DebugReaction);
 Elementdecl_seq->hard(ElementOpen,Space)->hard(Name)->hard(Space)->hard(Contentspec)->hard(SpaceOptional)->hard(TagClose);
 Elementdecl->init(Elementdecl_seq);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  Elementdecl->reactionHit_set(&DebugReaction);
 CharDataOption->zeroOrOne(CharDataLine);
 Content_cnd->incOr(ElementLine,CommentLine)->incOr(CharDataLine)->incOr(CDSectLine)->incOr(DeclarationLine);

 Content_lst->zeroOrMore(Content_cnd);
 Content->init(Content_lst);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  Content->reactionHit_set(&DebugReaction);
//}

//{
 Element_seq->hard(STag,Content)->hard(TagLineStartOpt)->hard(ETag);
 Element_cnd->incOr(Element_seq,EmptyElemTag);
 Element->init(Element_cnd);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  Element->reactionHit_set(&DebugReaction);
 ElementLine->hard(TagLineStartOpt,Element);
//}

//{
//}
}






/*  @MRTZ_describe defineRules_DocumentTypeDefinition

[22]   	prolog	   ::=   	XMLDecl Misc* (doctypedecl Misc*)?

[27]   	Misc	   ::=   	Comment | PI | S

[28]   	doctypedecl	   ::=   	'<!DOCTYPE' S Name (S ExternalID)? S? ('[' intSubset ']' S?)? '>'	[VC: Root Element Type]
				[WFC: External Subset]
[28a]   	DeclSep	   ::=   	PEReference | S 	[WFC: PE Between Declarations]
[28b]   	intSubset	   ::=   	(markupdecl | DeclSep)*
[29]   	markupdecl	   ::=   	elementdecl | AttlistDecl | EntityDecl | NotationDecl | PI | Comment 	[VC: Proper Declaration/PE Nesting]
[30]   	extSubset	   ::=   	TextDecl? extSubsetDecl
[31]   	extSubsetDecl	   ::=   	( markupdecl | conditionalSect | DeclSep)*


Conditional Section
[61]   	conditionalSect	   ::=   	includeSect | ignoreSect
[62]   	includeSect	   ::=   	'<![' S? 'INCLUDE' S? '[' extSubsetDecl ']]>' 	[VC: Proper Conditional Section/PE Nesting]
[63]   	ignoreSect	   ::=   	'<![' S? 'IGNORE' S? '[' ignoreSectContents* ']]>'	[VC: Proper Conditional Section/PE Nesting]
[64]   	ignoreSectContents	   ::=   	Ignore ('<![' ignoreSectContents ']]>' Ignore)*
[65]   	Ignore	   ::=   	Char* - (Char* ('<![' | ']]>') Char*)



[82]   	NotationDecl	   ::=   	'<!NOTATION' S Name S (ExternalID | PublicID) S? '>'	[VC: Unique Notation Name]
[83]   	PublicID	   ::=   	'PUBLIC' S PubidLiteral



*/
void XML_Parser::defineRules_DocumentTypeDefinition(void)
{
//{
  CREATE_STRING_PARSER(NotationOpen,              INCED_ID(ID.String), "open a notation");
  CREATE_STRING_PARSER(DocTypeOpen,               INCED_ID(ID.String), "open a document type");
  CREATE_STRING_PARSER(IgnoreOpen,                INCED_ID(ID.String), "open an ignore or include section");
  CREATE_STRING_PARSER(IgnoreClose,               INCED_ID(ID.String), "close an ignore or include section");
  CREATE_CHARACTER_PARSER(SubOpen,                INCED_ID(ID.Character), "open a  sub-section");
  CREATE_CHARACTER_PARSER(SubClose,               INCED_ID(ID.Character), "close a  sub-section");
  CREATE_STRING_PARSER(Include_str,               INCED_ID(ID.String), "key word include");
  CREATE_STRING_PARSER(Ignore_str,                INCED_ID(ID.String), "keyword ignore");
//}
//{
  CREATE_SEQUENCE_PARSER(PublicID_seq,            INCED_ID(ID.Sequence), "parser of public ID");
  CREATE_RULE_PARSER(PublicID,                    INCED_ID(ID.Rule),   "rule of public ID");
                     PublicID->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
  CREATE_CONDITION_PARSER(NotationDecl_con,       INCED_ID(ID.Condition), "internal id alternative of notation declaration");
  CREATE_SEQUENCE_PARSER(NotationDecl_seq,        INCED_ID(ID.Sequence), "parser of  notation declaration");
  CREATE_RULE_PARSER(NotationDecl,                INCED_ID(ID.Rule),   "rule of  notation declaration");
                     NotationDecl->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
//}
//{
  CREATE_CONDITION_PARSER(Ignore_con,             INCED_ID(ID.Condition), "internal id alternative of ignore");
  CREATE_CONDITION_PARSER(Ignore_excl,            INCED_ID(ID.Condition), "characters not to ignore");
  CREATE_COUNTER_PARSER(Ignore_cnt,               INCED_ID(ID.Counter),   "parser of ignore");
  CREATE_RULE_PARSER(Ignore,                      INCED_ID(ID.Rule),      "rule of ignore");
                     Ignore->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
//}
//{
  CREATE_SEQUENCE_PARSER(IgnoreSectContents_seqIa, INCED_ID(ID.Sequence), "internal sequence of ignore sect contents a");
  CREATE_SEQUENCE_PARSER(IgnoreSectContents_seqIb, INCED_ID(ID.Sequence), "internal sequence of ignore sect contents b");
  CREATE_CONDITION_PARSER(IgnoreSectContents_conab,INCED_ID(ID.Condition), "one of internal sequence of ignore sect contents");

  CREATE_COUNTER_PARSER( IgnoreSectContents_cntI, INCED_ID(ID.Counter), "many internal sequences of ignore sect contents");
  CREATE_SEQUENCE_PARSER(IgnoreSectContents_seqE, INCED_ID(ID.Sequence), "parser of ignore sect contents");
  CREATE_RULE_PARSER(IgnoreSectContents,          INCED_ID(ID.Rule),   "rule of ignore sect contents");
                     IgnoreSectContents->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
  CREATE_COUNTER_PARSER(IgnoreSectContents_cnt,   INCED_ID(ID.Counter), "many of ignore sect contents");
  CREATE_SEQUENCE_PARSER(IgnoreSect_seq,          INCED_ID(ID.Sequence), "parser of ignore section");
  CREATE_RULE_PARSER(IgnoreSect,                  INCED_ID(ID.Rule),   "rule of ignore section");
                     IgnoreSect->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
  CREATE_SEQUENCE_PARSER(IncludeSect_seq,         INCED_ID(ID.Sequence), "parser of include section");
  CREATE_RULE_PARSER(IncludeSect,                 INCED_ID(ID.Rule),   "rule of include section");
                     IncludeSect->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
  CREATE_CONDITION_PARSER(ConditionalSect_cnd,    INCED_ID(ID.Condition), "parser of ignore");
  CREATE_RULE_PARSER(ConditionalSect,             INCED_ID(ID.Rule),   "rule of ignore");
                     ConditionalSect->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
//}
//{
  CREATE_CONDITION_PARSER(Markupdecl_con,         INCED_ID(ID.Condition), "parser of mark-up declaration");
  CREATE_RULE_PARSER(Markupdecl,                  INCED_ID(ID.Rule),   "rule of mark-up declaration");
                     Markupdecl->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
  CREATE_CONDITION_PARSER(DeclSep_con,            INCED_ID(ID.Condition), "parser of declaration separator");
  CREATE_RULE_PARSER(DeclSep,                     INCED_ID(ID.Rule),   "rule of declaration separator");
                     DeclSep->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
  CREATE_CONDITION_PARSER(ExtSubsetDecl_con,      INCED_ID(ID.Condition), "internal alternative of declaration separator");
  CREATE_COUNTER_PARSER(ExtSubsetDecl_cnt,        INCED_ID(ID.Counter), "parser of declaration separator");
  CREATE_RULE_PARSER(ExtSubsetDecl,               INCED_ID(ID.Rule),   "rule of external sub-set declaration");
                     ExtSubsetDecl->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
//}
//{
  CREATE_COUNTER_PARSER(TextDeclOptional,         INCED_ID(ID.Counter), "zero or one text declaration");
  CREATE_SEQUENCE_PARSER(EextSubset_seq,          INCED_ID(ID.Sequence), "parser of external subset");
  CREATE_RULE_PARSER(EextSubset,                  INCED_ID(ID.Rule),   "rule of external subset");
                     EextSubset->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
  CREATE_CONDITION_PARSER(IntSubset_cnd,          INCED_ID(ID.Condition), "alternative of internal subset");
  CREATE_COUNTER_PARSER(IntSubset_cnt,            INCED_ID(ID.Counter), "parser of internal subset");
  CREATE_RULE_PARSER(IntSubset,                   INCED_ID(ID.Rule),   "rule of internal subset");
                     IntSubset->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
//}

//{
  CREATE_SEQUENCE_PARSER(ExternalIDtbd,          INCED_ID(ID.Sequence), "single tabled external identifier");
  CREATE_COUNTER_PARSER(ExternalIDtbdOpt,        INCED_ID(ID.Counter), "optional single tabled external identifier");
  CREATE_SEQUENCE_PARSER(IntSubsetTbd,           INCED_ID(ID.Sequence), "single tabled internal subset");
  CREATE_COUNTER_PARSER(IntSubsetTbdOpt,         INCED_ID(ID.Counter), "optional single tabled internal subset");
  CREATE_SEQUENCE_PARSER(Doctypedecl_seq,        INCED_ID(ID.Sequence), "parser of doc-type declaration");
  CREATE_RULE_PARSER(Doctypedecl,                INCED_ID(ID.Rule),   "parser of doc-type declaration");
                     Doctypedecl->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
//}
//{
  CREATE_CONDITION_PARSER(Misc_con,              INCED_ID(ID.Condition), "parser of misc");
  CREATE_RULE_PARSER(Misc,                       INCED_ID(ID.Rule),   "rule of misc");
                     Misc->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
  CREATE_COUNTER_PARSER(Misc_cnt,                INCED_ID(ID.Counter), "many occurrences of misc");
//}
//{
  CREATE_SEQUENCE_PARSER(DoctypedeclTbd,         INCED_ID(ID.Sequence), "single tabled  doc-type declaration");
  CREATE_COUNTER_PARSER(DoctypedeclTbdOpt,       INCED_ID(ID.Counter), "optional single tabled  doc-type declaration");
  CREATE_SEQUENCE_PARSER(Prolog_seq,             INCED_ID(ID.Sequence), "parser of prologue");
  CREATE_RULE_PARSER(Prolog,                     INCED_ID(ID.Rule),   "rule of prologue");
                     Prolog->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
//}
//{
  GET_PARSER(TiPa_Rule,      Public);
  GET_PARSER(TiPa_Rule,      PublicLiteral);
  GET_PARSER(TiPa_Rule,      Name);
  GET_PARSER(TiPa_Rule,      Space);
  GET_PARSER(TiPa_Counter,   SpaceOptional);
  GET_PARSER(TiPa_Rule,      ExternalID);
  GET_PARSER(TiPa_Rule,      Elementdecl);
  GET_PARSER(TiPa_Rule,      AttlistDecl);
  GET_PARSER(TiPa_Rule,      EntityDecl);
  GET_PARSER(TiPa_Sequence,  DeclarationLine);
  GET_PARSER(TiPa_Sequence,  CommentLine);
  GET_PARSER(TiPa_Sequence,  PEReferenceLine);
  GET_PARSER(TiPa_Character, TagClose);
  GET_PARSER(TiPa_Character, Char);
//}
//{
 NotationOpen->init("<!NOTATION");   /// @todo optimize '<' followed by '!' followed by string
 DocTypeOpen ->init("<!DOCTYPE");    /// @todo optimize '<' followed by '!' followed by string
 SubOpen     ->init('[');
 SubClose    ->init(']');
 IgnoreOpen  ->init("<![");          /// @todo optimize '<' followed by '!' followed by '['
 IgnoreClose ->init("]]>");
 Ignore_str  ->init("IGNORE");
 Include_str ->init("INCLUDE");
//}
//{
 PublicID_seq    ->hard(Public,PublicLiteral);
 PublicID        ->init(PublicID_seq);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  PublicID->reactionHit_set(&DebugReaction);

 NotationDecl_con->incOr(ExternalID, PublicID);
 NotationDecl_seq->hard(NotationOpen,Space)->hard(Name)->hard(Space)
                 ->hard(NotationDecl_con)->hard(SpaceOptional)->hard(TagClose);
 NotationDecl    ->init(NotationDecl_seq);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  NotationDecl->reactionHit_set(&DebugReaction);
//}
//{
 Ignore_con    ->incOr(IgnoreOpen,IgnoreClose);
 Ignore_excl   ->exclusion(Char,Ignore_con);
 Ignore_cnt    ->oneOrMore(Ignore_excl);
 Ignore        ->init(Ignore_cnt);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  Ignore->reactionHit_set(&DebugReaction);
//}
//{
 IgnoreSectContents_seqIa->hard(IgnoreOpen,IgnoreSectContents)->hard(IgnoreClose)->hard(Ignore);
 IgnoreSectContents_seqIb->hard(IgnoreOpen,IgnoreSectContents)->hard(IgnoreClose);
 IgnoreSectContents_conab->incOr(IgnoreSectContents_seqIa,IgnoreSectContents_seqIb);
 IgnoreSectContents_cntI->zeroOrMore(IgnoreSectContents_conab);

 IgnoreSectContents_seqE->soft(Ignore,IgnoreSectContents_cntI);

 IgnoreSectContents->init(IgnoreSectContents_seqE);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  IgnoreSectContents->reactionHit_set(&DebugReaction);

 IgnoreSectContents_cnt->zeroOrMore(IgnoreSectContents);


// CREATE_RULE_PARSER(Test,INCED_ID(ID.Rule),"rule to test a parser") ;
//                    Test->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
// Test->init(IgnoreSectContents_cnt);
// if(TDA_GrmConcrete::Att.DebugMode == true)
//  Test->reactionHit_set(&DebugReaction);


 IgnoreSect_seq->hard(IgnoreOpen,SpaceOptional)->hard(Ignore_str)->hard(SpaceOptional)
               ->hard(SubOpen)->hard(IgnoreSectContents_cnt)->hard(IgnoreClose);
 IgnoreSect->init(IgnoreSect_seq);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  IgnoreSect->reactionHit_set(&DebugReaction);

 IncludeSect_seq->hard(IgnoreOpen,SpaceOptional)->hard(Include_str)->hard(SpaceOptional)
                ->hard(SubOpen)->hard(ExtSubsetDecl)->hard(IgnoreClose);
 IncludeSect->init(IncludeSect_seq);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  IncludeSect->reactionHit_set(&DebugReaction);

 ConditionalSect_cnd->incOr(IgnoreSect,IncludeSect);
 ConditionalSect->init(ConditionalSect_cnd);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  ConditionalSect->reactionHit_set(&DebugReaction);
//}
//{
 Markupdecl_con->incOr(Elementdecl, AttlistDecl)->incOr(EntityDecl)
               ->incOr(NotationDecl)->incOr(DeclarationLine)->incOr(CommentLine);
 Markupdecl->init(Markupdecl_con);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  Markupdecl->reactionHit_set(&DebugReaction);

 DeclSep_con->incOr(PEReferenceLine, Space);
 DeclSep->init(DeclSep_con);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  DeclSep->reactionHit_set(&DebugReaction);

 ExtSubsetDecl_con->incOr(Markupdecl, ConditionalSect)->incOr(DeclSep);
 ExtSubsetDecl_cnt->zeroOrMore(ExtSubsetDecl_con);
 ExtSubsetDecl->init(ExtSubsetDecl_cnt);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  ExtSubsetDecl->reactionHit_set(&DebugReaction);
//}
//{
 TextDeclOptional->zeroOrOne(DeclarationLine);
 EextSubset_seq->hard(TextDeclOptional,ExtSubsetDecl);
 EextSubset->init(EextSubset_seq);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  EextSubset->reactionHit_set(&DebugReaction);

 IntSubset_cnd->incOr(Markupdecl, DeclSep);
 IntSubset_cnt->zeroOrMore(IntSubset_cnd);
 IntSubset->init(IntSubset_cnt);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  IntSubset->reactionHit_set(&DebugReaction);
//}
//{
 ExternalIDtbd->hard(Space,ExternalID);
 ExternalIDtbdOpt->zeroOrOne(ExternalIDtbd);
 IntSubsetTbd->hard(SubOpen,IntSubset)->hard(SubClose);
 IntSubsetTbdOpt->zeroOrOne(IntSubsetTbd);
 Doctypedecl_seq->hard(DocTypeOpen,Space)->hard(Name)->hard(ExternalIDtbdOpt)
                ->hard(SpaceOptional)->hard(IntSubsetTbdOpt)->hard(TagClose);
 Doctypedecl->init(Doctypedecl_seq);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  Doctypedecl->reactionHit_set(&DebugReaction);

//}
//{
// Misc_con->incOr(Comment,PI)->incOr(Space);




 Misc_con->incOr(CommentLine,DeclarationLine)->incOr(Space);
 Misc->init(Misc_con);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  Misc->reactionHit_set(&DebugReaction);
 Misc_cnt->zeroOrMore(Misc);
//}
//{
 DoctypedeclTbd->hard(Doctypedecl,Misc_cnt);
 DoctypedeclTbdOpt->zeroOrOne(DoctypedeclTbd);
 Prolog_seq->hard(DeclarationLine,Misc_cnt)->hard(DoctypedeclTbdOpt);
 Prolog->init(Prolog_seq);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  Prolog->reactionHit_set(&DebugReaction);
//}
}




/*  @MRTZ_describe defineRules_Document
[1]   	document	   ::=   	( prolog element Misc* ) - ( Char* RestrictedChar Char* )
*/
void XML_Parser::defineRules_Document(void)
{
//{
  CREATE_CHARACTER_PARSER(RestrictedChar,             INCED_ID(ID.Character), "restricted characters");

  CREATE_SEQUENCE_PARSER(DocumentContent,             INCED_ID(ID.Sequence),  "content of document");
  CREATE_SEQUENCE_PARSER(DocumentNonContent,          INCED_ID(ID.Sequence),  "not content of document");
  CREATE_CONDITION_PARSER(Document_cnd,               INCED_ID(ID.Condition), "parser of document");
  CREATE_RULE_PARSER(Document,                        INCED_ID(ID.Rule),      "rule of document");
                     Document->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
  CREATE_COUNTER_PARSER(CharOptional,                 INCED_ID(ID.Counter),   "many characters" );
//}
//{
 GET_PARSER(TiPa_Counter,   SpaceMulti);
 GET_PARSER(TiPa_Rule,Prolog);
 GET_PARSER(TiPa_Sequence,ElementLine);
 GET_PARSER(TiPa_Counter,Misc_cnt);
 GET_PARSER(TiPa_Character, Char);
 GET_PARSER(TiPa_Character, SpaceOptional);
//}
//{
 RestrictedChar->init   ((char)0x01,(char)0x08)
               ->include((char)0x0B,(char)0x0C)
               ->include((char)0x0E,(char)0x0F)
               ->include((char)0x7F,(char)0x84)
               ->include((char)0x86,(char)0x9F);
 CharOptional   ->zeroOrMore(Char);
//}
//{
 DocumentContent->soft(SpaceMulti,Prolog)->soft(ElementLine)->soft(Misc_cnt);
// DocumentNonContent->hard(SpaceOptional,CharOptional)->hard(RestrictedChar)->hard(CharOptional)->hard(SpaceOptional);
 DocumentNonContent->hard(CharOptional,RestrictedChar)->hard(CharOptional)->hard(SpaceOptional);
 Document_cnd->exclusion(DocumentContent,DocumentNonContent);
 Document->init(Document_cnd);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  Document->reactionHit_set(&DebugReaction);
//}
}





/*  @MRTZ_describe defineRules_Declaration

*/
void XML_Parser::defineRules_Declaration(void)
{
 CREATE_STRING_PARSER(DeclarationOpen,      INCED_ID(ID.String),  "open a style sheet tag or declaration");
 CREATE_STRING_PARSER(DeclarationClose,     INCED_ID(ID.String),  "close a style sheet tag or declaration");
 CREATE_SEQUENCE_PARSER(DeclarationTag_seq, INCED_ID(ID.Sequence),"parser of declaration");
 CREATE_RULE_PARSER(Declaration,            INCED_ID(ID.Rule),    "rule of declaration tag");
                    Declaration->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
 CREATE_SEQUENCE_PARSER(DeclarationLine,    INCED_ID(ID.Sequence),"declaration  with optional white-space before");

 GET_PARSER( TiPa_Counter,   Attribute_list);
 GET_PARSER( TiPa_Counter,   SpaceOptional);
 GET_PARSER(TiPa_Rule,      Name);
 GET_PARSER(TiPa_Counter,TagLineStartOpt);




//{
 DeclarationOpen        ->init("<?");
 DeclarationClose       ->init("?>");
 DeclarationTag_seq->hard(DeclarationOpen,Name)
                   ->hard(Attribute_list)
                   ->hard(SpaceOptional)
                   ->hard(DeclarationClose);
 Declaration->init(DeclarationTag_seq);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  Declaration->reactionHit_set(&DebugReaction);

 DeclarationLine->hard(TagLineStartOpt,Declaration);
//}
//{

//}
//{

//}
//{

//}

//{

//}
}


/*  @MRTZ_describe defineRules_Node

*/
void XML_Parser::defineRules_Node(void)
{
//{

//}
//{

//}
//{

//}
//{

//}

//{

//}
}

/*  @MRTZ_describe defineRules_Leaf

*/
void XML_Parser::defineRules_Leaf(void)
{
//{

//}
//{

//}
//{

//}
//{

//}

//{

//}
}

/*  @MRTZ_describe skipNonRuleResults

*/
void XML_Parser::skipNonRuleResults(void)
{
//  map<string,TiPa_Rule*>::iterator CurrentRule = Att.ParserRule.begin();
//  while(CurrentRule != Att.ParserRule.end())
//  {
//   CurrentRule->second->resultStorage_Set(TiPa_Concrete::ResStore_CollectTerminals);
//   ++ CurrentRule;
//  }

//  GET_PARSER(TiPa_Rule,      Name);
//  Name->resultStorage_Set(TiPa_Concrete::ResStore_Terminate);
//  GET_PARSER(TiPa_Rule,      AttCharacter1);
//  AttCharacter1->resultStorage_Set(TiPa_Concrete::ResStore_Terminate);
//  GET_PARSER(TiPa_Rule,      AttCharacter2);
//  AttCharacter2->resultStorage_Set(TiPa_Concrete::ResStore_Terminate);
//  GET_PARSER(TiPa_Rule,      Reference);
//  Reference->resultStorage_Set(TiPa_Concrete::ResStore_Terminate);
//  GET_PARSER(TiPa_Rule,      CharNormal);
//  CharNormal->resultStorage_Set(TiPa_Concrete::ResStore_Terminate);
//  GET_PARSER(TiPa_Rule,      CommentContent);
//  CommentContent->resultStorage_Set(TiPa_Concrete::ResStore_Terminate);
//  GET_PARSER(TiPa_Rule,      CData);
//  CData->resultStorage_Set(TiPa_Concrete::ResStore_Terminate);

  map<string,TiPa_Character*>::iterator CurrentCharacter = Att.ParserCharacter.begin();
  while(CurrentCharacter != Att.ParserCharacter.end())
  {
   CurrentCharacter->second->resultStorage_Set(TiPa_Concrete::ResStore_NV);
   ++ CurrentCharacter;
  }

  map<string,TiPa_String*>::iterator CurrentString = Att.ParserString.begin();
  while(CurrentString != Att.ParserString.end())
  {
   CurrentString->second->resultStorage_Set(TiPa_Concrete::ResStore_NV);
   ++ CurrentString;
  }

  map<string,TiPa_Counter*>::iterator CurrentCounter = Att.ParserCounter.begin();
  while(CurrentCounter != Att.ParserCounter.end())
  {
   CurrentCounter->second->resultStorage_Set(TiPa_Concrete::ResStore_NV);
   ++ CurrentCounter;
  }

  map<string,TiPa_Sequence*>::iterator CurrentSequence = Att.ParserSequence.begin();
  while(CurrentSequence != Att.ParserSequence.end())
  {
   CurrentSequence->second->resultStorage_Set(TiPa_Concrete::ResStore_NV);
   ++ CurrentSequence;
  }

  map<string,TiPa_Condition*>::iterator CurrentCondition = Att.ParserCondition.begin();
  while(CurrentCondition != Att.ParserCondition.end())
  {
   CurrentCondition->second->resultStorage_Set(TiPa_Concrete::ResStore_NV);
   ++ CurrentCondition;
  }

}








