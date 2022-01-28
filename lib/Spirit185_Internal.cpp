/*!

 @file
 @brief definitions of an concrete grammar-class for scanning a2x-scripts
        written in the notation of the old spirit 1.8.5

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
    08.03.2015     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    08.03.2015...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/

#include "Spirit185_Internal.h"

#include <stdio.h>
#include <cstring>
#include <limits.h>



#include "TiPa_Concrete.h"
#include "TiPa_Combination.h"
#include "TiPa_Counter.h"
#include "TiPa_String.h"
#include "TiPa_Character.h"

#define DEBUG_OUTPUT_LOG
#include "LogOutput.h"


using namespace std;

#ifndef DOXYGEN
//namespace TXTDIASM {
//namespace TDA_Grammar {
////namespace CL_TDA_GRMCONCRETE {
//namespace CL_SPIRIT185 {
#endif //DOXYGEN



/* !
  internal grammar used to analyse external rules
 Spirit185_Internal::Grammar Spirit185_Internal::
*/




/* @MRTZ_describe Spirit185_Internal

*/
 Spirit185_Internal::Spirit185_Internal(TiPa_Concrete::DataModel* contextModel,
                                        bool                      debugMode)
                    :TDA_GrmConcrete(contextModel, debugMode)
 {


  LOG_OUTPUT(LOG_OFF, "Spirit185_Internal(bool debugMode) start");
  DECLEARE_PARSER(TiPa_Rule, Primitive,    Spirit185_Internal::Primitive_rid,    "primitive parser");
  DECLEARE_PARSER(TiPa_Rule, Comment,      Spirit185_Internal::Comment_rid,      "comment inside the user-grammar");
  DECLEARE_PARSER(TiPa_Rule, Identifier,   Spirit185_Internal::Identifier_rid,   "identifying name of a user-rule");
  DECLEARE_PARSER(TiPa_Rule, Character,    Spirit185_Internal::Character_rid,    "character parsers");
  DECLEARE_PARSER(TiPa_Rule, KeyWord,      Spirit185_Internal::KeyWord_rid,      "keyword parsers");
  DECLEARE_PARSER(TiPa_Rule, SeqOperation, Spirit185_Internal::BinSequence_rid,  "sequence parser");
  DECLEARE_PARSER(TiPa_Rule, CndOperation, Spirit185_Internal::BinCondition_rid, "conditional parser");
  DECLEARE_PARSER(TiPa_Rule, UniOperation, Spirit185_Internal::UniOperation_rid, "unary parser");
  DECLEARE_PARSER(TiPa_Rule, SubParser,    Spirit185_Internal::SubParser_rid,    "sub parser framed with ( and )");
  DECLEARE_PARSER(TiPa_Rule, Parser,       Spirit185_Internal::Parser_rid,       "parser");
  DECLEARE_PARSER(TiPa_Rule, Rule,         Spirit185_Internal::Rule_rid,         "single rule");
  CREATE_PARSER(TiPa_Rule,   Root,         Spirit185_Internal::Root_rid,         "valid text content");
  CREATE_PARSER(TiPa_Rule,   Skip,         Spirit185_Internal::Skip_rid,         "text content to ignore");

  CREATE_PARSER(TiPa_Condition,   NewLine,         16, "new line");


  LOG_OUTPUT(LOG_OFF, "Spirit185_Internal(bool debugMode) create start");


  create_Token();
  create_Primitive();
  create_Comment();
  create_RuleIdentifier();
  create_RuleCharacter();
  create_RuleKeyWord();
  create_RuleBin();
  create_RuleUni();
  create_RuleParser();
  create_RuleSub();
  create_RuleRoot();

  LOG_OUTPUT(LOG_OFF, "Spirit185_Internal(bool debugMode) create end");

  TDA_GrmConcrete::Att.MainParser = Root;
  TDA_GrmConcrete::Att.SkipParser = Skip;
  TDA_GrmConcrete::Att.LineParser = NewLine;

  LOG_OUTPUT(LOG_OFF, "Spirit185_Internal(bool debugMode) end");
 }






/* @MRTZ_describe Spirit185_Internal
*/
 Spirit185_Internal::Spirit185_Internal(const char*               grammar,
                                        TiPa_Concrete::DataModel* contextModel,
                                        bool                      debugMode)
                    :TDA_GrmConcrete(contextModel, debugMode)
 {
  LOG_OUTPUT(LOG_OFF, "Spirit185_Internal(const char* rule,bool debugMode)");

  DECLEARE_PARSER(TiPa_Rule, Primitive,    Spirit185_Internal::Primitive_rid,    "primitive parser");
  DECLEARE_PARSER(TiPa_Rule, Comment,      Spirit185_Internal::Comment_rid,      "comment inside the user-grammar");
  DECLEARE_PARSER(TiPa_Rule, Identifier,   Spirit185_Internal::Identifier_rid,   "identifying name of a user-rule");
  DECLEARE_PARSER(TiPa_Rule, Character,    Spirit185_Internal::Character_rid,    "character parsers");
  DECLEARE_PARSER(TiPa_Rule, KeyWord,      Spirit185_Internal::KeyWord_rid,      "keyword parsers");
  DECLEARE_PARSER(TiPa_Rule, SeqOperation, Spirit185_Internal::BinSequence_rid,  "sequence parser");
  DECLEARE_PARSER(TiPa_Rule, CndOperation, Spirit185_Internal::BinCondition_rid, "conditional parser");
  DECLEARE_PARSER(TiPa_Rule, UniOperation, Spirit185_Internal::UniOperation_rid, "unary parser");
  DECLEARE_PARSER(TiPa_Rule, SubParser,    Spirit185_Internal::SubParser_rid,    "sub parser framed with ( and )");
  DECLEARE_PARSER(TiPa_Rule, Parser,       Spirit185_Internal::Parser_rid,       "parser");
  DECLEARE_PARSER(TiPa_Rule, Rule,         Spirit185_Internal::Rule_rid,         "single rule");
  CREATE_PARSER(TiPa_Rule,   Root,         Spirit185_Internal::Root_rid,         "valid text content");
  CREATE_PARSER(TiPa_Rule,   Skip,         Spirit185_Internal::Skip_rid,         "text content to ignore");

  CREATE_PARSER(TiPa_Condition,   NewLine,         16, "new line");

  LOG_OUTPUT(LOG_OFF, "Spirit185_Internal(const char* rule,bool debugMode) create start");


  create_Token();
  create_Primitive();
  create_Comment();
  create_RuleIdentifier();
  create_RuleCharacter();
  create_RuleKeyWord();
  create_RuleParser();
  create_RuleSub();
  create_RuleBin();
  create_RuleUni();
  create_RuleRoot();

  LOG_OUTPUT(LOG_OFF, "Spirit185_Internal(const char* rule,bool debugMode) create end");

  TDA_GrmConcrete::Att.MainParser = Root;
  TDA_GrmConcrete::Att.SkipParser = Skip;
  TDA_GrmConcrete::Att.LineParser = NewLine;

  LOG_OUTPUT(LOG_OFF, "Spirit185_Internal(const char* rule,bool debugMode) parse grammar");

  this->parse(grammar,grammar+strlen(grammar));

  LOG_OUTPUT(LOG_OFF, "Spirit185_Internal(const char* rule,bool debugMode) end");

 }







/* @MRTZ_describe ~Spirit185_Internal

*/
 Spirit185_Internal::~Spirit185_Internal(void)
 {
  LOG_OUTPUT(LOG_OFF, "~Spirit185_Internal(void) start");
 // if(TDA_GrmConcrete::Att.Root != nullptr)
   //TDA_GrmConcrete::Att.Root->result_clear();

  // this->treeData()->deleteNode();

  LOG_OUTPUT(LOG_OFF, "~Spirit185_Internal(void) end");

 }








/* @MRTZ_describe Spirit185_Internal_parse

*/
 const char* Spirit185_Internal::parse(const char* begin,
                                       const char* end,
                                       const char* rule)
{
  pre_parse( begin, end);                       // call the pre parser process to collect common attributes of the give text
  return(TDA_GrmConcrete::parse(begin, end, rule));   // call the main parsing process and return its result
}






















/* @MRTZ_describe Spirit185_Internal_create_Token

   @MRTZ_describe primary-rule
*/
void Spirit185_Internal::create_Token(void)
{



/* static bool Done = false;
 if(Done == false)
 {
 */
  CREATE_PARSER(TiPa_Character,   ParanthesisOpen,  1, "character: (");
  CREATE_PARSER(TiPa_Character,   ParanthesisClose, 2, "character: )");
  CREATE_PARSER(TiPa_Character,   Comma,            3, "character: ,");
  CREATE_PARSER(TiPa_Character,   UnderScore,       4, "character: _");
  CREATE_PARSER(TiPa_Character,   BackSlash,        5, "character: \\");
  CREATE_PARSER(TiPa_Character,   Alpha,            6, "characters: a...z and A...Z");
  CREATE_PARSER(TiPa_Character,   Digit,            7, "characters: 0...9");
  CREATE_PARSER(TiPa_Character,   Anychar,          8, "all characters");

  CREATE_PARSER(TiPa_Sequence,    Escape,           9, "escape sequences");

  CREATE_PARSER(TiPa_Character,   CR,              10, "control parser: Carriage Return");
  CREATE_PARSER(TiPa_Character,   LF,              12, "control character: Line Feed");
  CREATE_PARSER(TiPa_Sequence,    NL_MS,           13, "character-combination for new line in Microsoft operation systems");

  CREATE_PARSER(TiPa_Counter,     NL_UNIX,         14, "character-combination for new line in Unix like operation systems");
  CREATE_PARSER(TiPa_Counter,     NL_MAC,          15, "character-combination for new line in Macintosh operation systems");
  CREATE_PARSER(TiPa_Condition,   NewLine,         16, "new line");

  CREATE_PARSER(TiPa_Counter,     EndOfText,       17, "end of text to parse");

  CREATE_PARSER(TiPa_Character,   SkipDetails,     18, "characters to ignore");


  GET_PARSER(TiPa_Rule, Skip);



  ParanthesisOpen->init('(') ;// begin of sub-parser
  ParanthesisClose->init(')') ;// end of sub-parser

  Comma->init(',') ;// parameter splitter

  UnderScore->init('_') ;// underscore character
  BackSlash->init('\\');// begin of escape-sequence

  Alpha->init(TiPa_Character::Alpha)  ;// all Latin letters
  Digit->init(TiPa_Character::Digit)  ;// all single digits

  Anychar->init(TiPa_Character::Anychar);// all characters with an ordinal number between 1 and 255



//  Anychar           = new TiPa_Character(32,127);// all characters with an ordinal number between 1 and 255
  Escape->init(TiPa_Sequence::Seq_HrdSq, BackSlash, Anychar);

  CR->init(13);// carriage return
  LF->init(10);// line feed
  NL_MS->init(TiPa_Sequence::Seq_HrdSq,CR, LF);            // new line for Microsoft
  NL_UNIX->init(TiPa_Counter::Cnt_OneOrMore,LF);              // new line for Unix or Linux
  NL_MAC->init(TiPa_Counter::Cnt_OneOrMore,CR);               // new line for Apple-Macintosh
  NewLine->init(TiPa_Condition::Cnd_OrExc, NL_MS, NL_UNIX); // new line for Microsoft ex-or Unix/Linux
  NewLine->contractor_ParserInsert(NL_MAC,2);                 // new line for Microsoft ex-or Unix/Linux ex-or Apple-Macintosh

  EndOfText->init(TiPa_Counter::Cnt_AllButNot,Anychar);       //end of text to parse

  SkipDetails->init(1,32);  // all control-characters and space may be skipped
  Skip->contractor_ParserInsert(SkipDetails);

/*
  Done = true;
 }
*/
}





/* @MRTZ_describe Spirit185_Internal_create_Primitive

   @MRTZ_describe primary-rule
*/
void Spirit185_Internal::create_Primitive(void)
{
/*
 static bool Done = false;
 if(Done == false)
 {
*/
  CREATE_PARSER(TiPa_String,      PrmAlnum,   Spirit185_Internal::PrmAlnum_rid,   "primitive parser: alpha numeric characters");
  CREATE_PARSER(TiPa_String,      PrmAlpha,   Spirit185_Internal::PrmAlpha_rid,   "primitive parser: alphabetic characters");
  CREATE_PARSER(TiPa_String,      PrmAnychar, Spirit185_Internal::PrmAnychar_rid, "primitive parser: any charcter");
  CREATE_PARSER(TiPa_String,      PrmBlank,   Spirit185_Internal::PrmBlank_rid,   "primitive parser: blank");
  CREATE_PARSER(TiPa_String,      PrmCntrl,   Spirit185_Internal::PrmCntrl_rid,   "primitive parser: control characters");
  CREATE_PARSER(TiPa_String,      PrmDigit,   Spirit185_Internal::PrmDigit_rid,   "primitive parser: digits");
  CREATE_PARSER(TiPa_String,      PrmGraph,   Spirit185_Internal::PrmGraph_rid,   "primitive parser: graphs");
  CREATE_PARSER(TiPa_String,      PrmLower,   Spirit185_Internal::PrmLower_rid,   "primitive parser: lower case characters");
  CREATE_PARSER(TiPa_String,      PrmPrint,   Spirit185_Internal::PrmPrint_rid,   "primitive parser: printable characters");
  CREATE_PARSER(TiPa_String,      PrmPunct,   Spirit185_Internal::PrmPunct_rid,   "primitive parser: punctuation");
  CREATE_PARSER(TiPa_String,      PrmSign,    Spirit185_Internal::PrmSign_rid,    "primitive parser: sign");
  CREATE_PARSER(TiPa_String,      PrmSpace,   Spirit185_Internal::PrmSpace_rid,   "primitive parser: space");
  CREATE_PARSER(TiPa_String,      PrmUpper,   Spirit185_Internal::PrmUpper_rid,   "primitive parser: upper case characters");
  CREATE_PARSER(TiPa_String,      PrmXdigit,  Spirit185_Internal::PrmXdigit_rid,  "primitive parser: hexadecimal digits ");
  CREATE_PARSER(TiPa_String,      PrmBin,     Spirit185_Internal::PrmBin_rid,     "primitive parser: binary digits");
  CREATE_PARSER(TiPa_String,      PrmHex,     Spirit185_Internal::PrmHex_rid,     "primitive parser: hexadecimal numbers");
  CREATE_PARSER(TiPa_String,      PrmOct,     Spirit185_Internal::PrmOct_rid,     "primitive parser: octal numbers");
  CREATE_PARSER(TiPa_String,      PrmEscape,  Spirit185_Internal::PrmEscape_rid,  "primitive parser: escape characters");
  CREATE_PARSER(TiPa_String,      PrmEol,     Spirit185_Internal::PrmEol_rid,     "primitive parser: end-of-line");
  CREATE_PARSER(TiPa_String,      PrmEnd,     Spirit185_Internal::PrmEnd_rid,     "primitive parser: end-of-input");
//  CREATE_PARSER(TiPa_String,      PrmInt,          Spirit185_Internal::PrmInt_rid,          "primitive parser");
//  CREATE_PARSER(TiPa_String,      PrmReal,         Spirit185_Internal::PrmReal_rid,         "primitive parser");
//  CREATE_PARSER(TiPa_String,      PrmStrict_real,  Spirit185_Internal::PrmStrict_real_rid,  "primitive parser");
//  CREATE_PARSER(TiPa_String,      PrmStrict_ureal, Spirit185_Internal::PrmStrict_ureal_rid, "primitive parser");
//  CREATE_PARSER(TiPa_String,      PrmUint,         Spirit185_Internal::PrmUint_rid,         "primitive parser");
//  CREATE_PARSER(TiPa_String,      PrmUreal,        Spirit185_Internal::PrmUreal_rid,        "primitive parser");
//  CREATE_PARSER(TiPa_String,      PrmEps,          Spirit185_Internal::PrmEps_rid,         ,"primitive parser");
//  CREATE_PARSER(TiPa_String,      PrmEpsilon,      Spirit185_Internal::PrmEpsilon_rid,      "primitive parser");
//  CREATE_PARSER(TiPa_String,      PrmNothing,      Spirit185_Internal::PrmNothing_rid,      "primitive parser");
//  CREATE_PARSER(TiPa_String,      PrmLex,          Spirit185_Internal::PrmLex_rid,          "primitive parser");
  CREATE_PARSER(TiPa_Condition,  KindOfPrimitive, 120, "kind of primitive");
  GET_PARSER(TiPa_Rule, Primitive);



  PrmAlnum->init("alnum_p")  ;// any Latin letter and digit
  PrmAlpha->init("alpha_p")  ;// any Latin letter
  PrmAnychar->init("anychar_p");// any character with an ordinal number between 1 and 255
  PrmBlank->init("blank_p")  ;// space or tab
  PrmCntrl->init("cntrl_p")  ;// any primitive parser
  PrmDigit->init("digit_p")  ;// any digit
  PrmGraph->init("graph_p")  ;// any characters with an ordinal number between 32 and 255
  PrmLower->init("lower_p")  ;// any lower case letter
  PrmPrint->init("print_p")  ;// any characters with an ordinal number between 32 and 255
  PrmPunct->init("punct_p")  ;// any character from ! ? . : , ;
  PrmSign->init("sign_p");   // any sign character (+ or -)
  PrmSpace->init("space_p")  ;// any white space
  PrmUpper->init("upper_p")  ;// any upper case letter
  PrmXdigit->init("xdigit_p") ;// any hexadecimal digit
  PrmBin->init("bin_p")    ;// any binary digit
  PrmHex->init("hex_p")    ;// any hexadecimal digit
  PrmOct->init("oct_p")    ;// any octagonal digit
  PrmEscape->init("c_escape_ch_p");
  PrmEol->init("eol_p") ;
  PrmEnd->init("end_p");



//  PrmInt->init("int_p")    ;
//  PrmReal->init("real_p");
//  PrmStrict_real->init("strict_real_p");
//  PrmStrict_ureal->init("strict_ureal_p");
//  PrmUint->init("uint_p") ;
//  PrmUreal->init("ureal_p");

//  PrmEps->init("eps_p")   ;
//  PrmEpsilon->init("epsilon_p");
//  PrmNothing->init("nothing_p");
//  PrmLex_escape_ch->init("lex_escape_ch_p");
//

  KindOfPrimitive->init(TiPa_Condition::Cnd_OrInc, PrmAlnum, PrmAlpha);     // any Latin letter and digit
  KindOfPrimitive->contractor_ParserInsert(PrmAnychar,  2);// any character with an ordinal number between 1 and 255
  KindOfPrimitive->contractor_ParserInsert(PrmBlank  ,  3);// space or tab
  KindOfPrimitive->contractor_ParserInsert(PrmCntrl  ,  4);// any primitive parser
  KindOfPrimitive->contractor_ParserInsert(PrmDigit  ,  5);// any digit
  KindOfPrimitive->contractor_ParserInsert(PrmGraph  ,  6);// any characters with an ordinal number between 32 and 255
  KindOfPrimitive->contractor_ParserInsert(PrmLower  ,  7);// any lower case letter
  KindOfPrimitive->contractor_ParserInsert(PrmPrint  ,  8);// any characters with an ordinal number between 32 and 255
  KindOfPrimitive->contractor_ParserInsert(PrmPunct  ,  9);// any character from ! ? . : , ;
  KindOfPrimitive->contractor_ParserInsert(PrmSign   , 10);// any sign character (+ or -)
  KindOfPrimitive->contractor_ParserInsert(PrmSpace  , 11);// any white space
  KindOfPrimitive->contractor_ParserInsert(PrmUpper  , 12);// any upper case letter
  KindOfPrimitive->contractor_ParserInsert(PrmXdigit , 13);// any hexadecimal digit
  KindOfPrimitive->contractor_ParserInsert(PrmBin    , 14);// any binary digit
  KindOfPrimitive->contractor_ParserInsert(PrmHex    , 15);// any hexadecimal digit
  KindOfPrimitive->contractor_ParserInsert(PrmOct    , 16);// any octagonal digit
  KindOfPrimitive->contractor_ParserInsert(PrmEol    ,17);
  KindOfPrimitive->contractor_ParserInsert(PrmEscape ,18);
  KindOfPrimitive->contractor_ParserInsert(PrmEnd    ,25); // end of input


//KindOfPrimitive->contractor_ParserInsert(PrmInt,19)           ;
//KindOfPrimitive->contractor_ParserInsert(PrmReal,20)          ;
//KindOfPrimitive->contractor_ParserInsert(PrmStrict_real,21)   ;
//KindOfPrimitive->contractor_ParserInsert(PrmStrict_ureal,22)  ;
//KindOfPrimitive->contractor_ParserInsert(PrmUint,23)          ;
//KindOfPrimitive->contractor_ParserInsert(PrmUreal,24)         ;
//KindOfPrimitive->contractor_ParserInsert(PrmEps,26)           ;
//KindOfPrimitive->contractor_ParserInsert(PrmEpsilon,27)       ;
//KindOfPrimitive->contractor_ParserInsert(PrmNothing,28)       ;
//KindOfPrimitive->contractor_ParserInsert(PrmLex_escape_ch,29) ;

  Primitive->init(KindOfPrimitive);
/*
  Done = true;
 }
*/
}














/* @MRTZ_describe Spirit185_Internal_create_Comment

*/
void Spirit185_Internal::create_Comment(void)
{
/*
 static bool Done = false;
 if(Done == false)
 {
  create_Token();
*/
  CREATE_PARSER(TiPa_String,      CommentLineBegin,        211, "begin of single line comment");
  CREATE_PARSER(TiPa_Character,   Comment_Line_Character,  212, "character inside a single line comment");
  CREATE_PARSER(TiPa_Counter,     Comment_Line_Content,    213, "content of a single line comment");
  CREATE_PARSER(TiPa_Condition,   Comment_Line_End,        214, "end of a comment line ");
  CREATE_PARSER(TiPa_Sequence,    Comment_Line,            210, "single line comment");
  CREATE_PARSER(TiPa_String,      CommentBlockBegin,       221, "begin of a comment block");
  CREATE_PARSER(TiPa_String,      CommentBlockEnd,         222, "end of a comment block ");
  CREATE_PARSER(TiPa_Condition,   Comment_Block_Character, 223, "character inside a comment block");
  CREATE_PARSER(TiPa_Counter,     Comment_Block_Content,   224, "content of a comment block");
  CREATE_PARSER(TiPa_Sequence,    Comment_Block,           220, "comment block");
  CREATE_PARSER(TiPa_Condition,   KindOfComment,           230, "kind of comment");


  GET_PARSER(TiPa_Rule,        Comment);
  GET_PARSER(TiPa_Condition,   NewLine);
  GET_PARSER(TiPa_Character,   Anychar);
  GET_PARSER(TiPa_Counter,     EndOfText);



  CommentLineBegin->init("//");// begin of line comment

  Comment_Line_Character->init(TiPa_Character::CharMin,TiPa_Character::CharMax);
  Comment_Line_Character->exclude(10);
  Comment_Line_Character->exclude(13);

  Comment_Line_Content->init(TiPa_Counter::Cnt_OptionMore, Comment_Line_Character);

  Comment_Line_End->init(TiPa_Condition::Cnd_OrInc,NewLine,EndOfText);

  Comment_Line->init(TiPa_Sequence::Seq_HrdSq,CommentLineBegin,
                                              Comment_Line_Content);
  Comment_Line->contractor_ParserInsert(      Comment_Line_End,2);

  CommentBlockBegin->init("/*");// begin of block-comment

  CommentBlockEnd->init("*/");// end of block-comment

  Comment_Block_Character->init(TiPa_Condition::Cnd_WthOt, Anychar, CommentBlockEnd);

  Comment_Block_Content->init(TiPa_Counter::Cnt_OptionMore, Comment_Block_Character);

  Comment_Block->init(TiPa_Sequence::Seq_HrdSq,CommentBlockBegin,
                                               Comment_Block_Content);
  Comment_Block->contractor_ParserInsert(      CommentBlockEnd,2);

  KindOfComment->init(TiPa_Condition::Cnd_OrInc,Comment_Line,Comment_Block);

  Comment->init(KindOfComment);
/*
  Done = true;
 }
*/
}




/* @MRTZ_describe Spirit185_Internal_create_RuleIdentifier

*/
void Spirit185_Internal::create_RuleIdentifier(void)
{

/*
 static bool Done = false;
 if(Done == false)
 {
  //create_Token();
*/
  CREATE_PARSER(TiPa_Character,   IdentifierBegin,   301, "first character of an identifier");
  CREATE_PARSER(TiPa_Character,   IdentifierInside,  302, "further characters of an identifier");
  CREATE_PARSER(TiPa_Counter,     IdentifierFurther, 303, "sequence of further characters of an identifier");
  CREATE_PARSER(TiPa_Sequence,    IdentifierActive,  304, "actual character sequence of an identifier");
  CREATE_PARSER(TiPa_Counter,     IdentifierComment, 305, "potential comment of an identifier");
  CREATE_PARSER(TiPa_Sequence,    IdentifierContent, 310, "identifying name of a MuLanPa rule");

  GET_PARSER(TiPa_Rule,   Identifier);
  GET_PARSER(TiPa_Rule,   Comment);

  IdentifierBegin->init('_');
  IdentifierBegin->include('a','z');
  IdentifierBegin->include('A','Z');// characters allowed at the begin of an identifier-name

  IdentifierInside->init('_');
  IdentifierInside->include('a','z');
  IdentifierInside->include('A','Z');
  IdentifierInside->include('0','9');// characters allowed inside an identifier-name

  IdentifierFurther->init(TiPa_Counter::Cnt_OptionMore, IdentifierInside);
                                                  // may occur zero ore more times
  IdentifierActive->init(TiPa_Sequence::Seq_HrdSq,
                                IdentifierBegin,
                                IdentifierFurther);

  IdentifierComment->init(TiPa_Counter::Cnt_OptionMore, Comment);
                                                  // may occur zero ore more times
  IdentifierContent->init(TiPa_Sequence::Seq_HrdSq, IdentifierActive, IdentifierComment);

  Identifier->init(IdentifierContent);
/*
  Done = true;
 }
*/


}



/* @MRTZ_describe Spirit185_Internal_create_RuleCharacter

*/
void Spirit185_Internal::create_RuleCharacter(void)
{
/*
 static bool Done = false;
 if(Done == false)
 {
  create_Token();
*/
  CREATE_PARSER(TiPa_Character,   LimiterCharacter,    Spirit185_Internal::LimiterCharacter_rid,
                "begin and end of character");
  CREATE_PARSER(TiPa_Character,   CharCharacter,       Spirit185_Internal::CharCharacter_rid,
                "any char except framing character");
  CREATE_PARSER(TiPa_Condition,   CharacterID,         Spirit185_Internal::CharacterID_rid,
                "identifier of a character");
  CREATE_PARSER(TiPa_Sequence,    CharacterParameter,  Spirit185_Internal::CharacterParameter_rid,
                "parameter of a MuLanPa character parser function");
  CREATE_PARSER(TiPa_String,      Character_Ch_p,      411,
                "identifier of the MuLanPa character parser function for one single character");
  CREATE_PARSER(TiPa_Sequence,    CharacterSingleFull, 412,
                "MuLanPa character parser function for one single character");
  CREATE_PARSER(TiPa_Condition,   CharacterSingle,     Spirit185_Internal::CharacterSingle_rid,
                "MuLanPa character parser for one single character");
  CREATE_PARSER(TiPa_String,      Character_Range_p,   421,
                "identifier of the MuLanPa character parser function for a character range");
  CREATE_PARSER(TiPa_Sequence,    CharacterRange,      Spirit185_Internal::CharacterRange_rid,
                "MuLanPa parser function for a character range");
  CREATE_PARSER(TiPa_Condition,   CharacterActive,     405,
                "actual MuLanPa character parser");
  CREATE_PARSER(TiPa_Counter,     CharacterComment,    406,
                "potential comment");
  CREATE_PARSER(TiPa_Sequence,    KindOfCharacter,     430,
                "kind of character parser");

  GET_PARSER(TiPa_Rule,      Character);
  GET_PARSER(TiPa_Sequence,  Escape);
  GET_PARSER(TiPa_Character, ParanthesisOpen);
  GET_PARSER(TiPa_Character, ParanthesisClose);
  GET_PARSER(TiPa_Character, Comma);
  GET_PARSER(TiPa_Rule,      Skip);
  GET_PARSER(TiPa_Rule,      Comment);




  LimiterCharacter->init('\'');

  CharCharacter->init(TiPa_Character::CharMin,TiPa_Character::CharMax);
  CharCharacter->exclude('\'');
  CharCharacter->exclude('\\');

  CharacterID->init(TiPa_Condition::Cnd_OrExc, Escape, CharCharacter) ;
  CharacterParameter->init(TiPa_Sequence::Seq_HrdSq, LimiterCharacter, CharacterID);
  CharacterParameter->contractor_ParserInsert(LimiterCharacter,2);

  Character_Ch_p->init("ch_p")     ;//
  CharacterSingleFull->init(TiPa_Sequence::Seq_HrdSq, Character_Ch_p, ParanthesisOpen);
  CharacterSingleFull->contractor_ParserInsert(CharacterParameter,2);
  CharacterSingleFull->contractor_ParserInsert(ParanthesisClose,  3);
  CharacterSingleFull->skip_ParserSet(Skip);
  CharacterSingle->init(TiPa_Condition::Cnd_OrExc, CharacterSingleFull, CharacterParameter);
  CharacterSingle->skip_ParserSet(Skip);

  Character_Range_p->init("range_p")  ;// range of characters
  CharacterRange->init(TiPa_Sequence::Seq_HrdSq, Character_Range_p, ParanthesisOpen);
  CharacterRange->contractor_ParserInsert(CharacterParameter,2);
  CharacterRange->contractor_ParserInsert(Comma,             3);
  CharacterRange->contractor_ParserInsert(CharacterParameter,4);
  CharacterRange->contractor_ParserInsert(ParanthesisClose,  5);
  CharacterRange->skip_ParserSet(Skip);

  CharacterActive->init(TiPa_Condition::Cnd_OrExc,
                                   CharacterSingle,
                                   CharacterRange) ;// character parser

  CharacterComment->init(TiPa_Counter::Cnt_OptionMore, Comment);
                                                      // may occur zero ore more times
  KindOfCharacter->init(TiPa_Sequence::Seq_HrdSq,CharacterActive,CharacterComment);

  Character->init(KindOfCharacter);
/*
  Done = true;
 }
*/
}




/* @MRTZ_describe Spirit185_Internal_create_RuleKeyWord

*/
void Spirit185_Internal::create_RuleKeyWord(void)
{
/*
 static bool Done = false;
 if(Done == false)
 {
  create_Token();
*/
  CREATE_PARSER(TiPa_Character,   LimiterString,           501,
                "begin and end of string");
  CREATE_PARSER(TiPa_Character,   KeyWord_StringCharacter, 502,
                "any char except framing character");
  CREATE_PARSER(TiPa_Condition,   KeyWordCharacter,        503,
                "character inside a string");
  CREATE_PARSER(TiPa_Counter,     KeyWordCharacterCount,   504,
                "character sequence of a string");
  CREATE_PARSER(TiPa_Sequence,    KeyWordParameter,        505,
                "actual string");
  CREATE_PARSER(TiPa_String,      KeyWord_Comment,         511,
                "identifier of the MuLanPa character parser function for a commenting string");
  CREATE_PARSER(TiPa_Sequence,    KeyWordCommentSingle,    Spirit185_Internal::KeyWordCommentSingle_rid,
                "MuLanPa parser function for a single line commenting string");
  CREATE_PARSER(TiPa_Sequence,    KeyWordCommentDouble,    Spirit185_Internal::KeyWordCommentDouble_rid,
                "MuLanPa parser function for a block commenting string");
  CREATE_PARSER(TiPa_String,      KeyWord_Str,             531,
                "identifier of the MuLanPa character parser function for a real string");
  CREATE_PARSER(TiPa_Sequence,    KeyWordStringFull,       532,
                "MuLanPa parser function for a real string");
  CREATE_PARSER(TiPa_Condition,   KeyWordString,           Spirit185_Internal::KeyWordString_rid,
                "MuLanPa parser for a real string");
  CREATE_PARSER(TiPa_String,      KeyWord_ChSeq,           541,
                "identifier of the MuLanPa character parser function for a character sequence");
  CREATE_PARSER(TiPa_Sequence,    KeyWordCharSequence,     Spirit185_Internal::KeyWordCharSequence_rid,
                "MuLanPa parser function for a character sequence");
  CREATE_PARSER(TiPa_Counter,     KeyWordComment,          506,
                "potential comment");
  CREATE_PARSER(TiPa_Condition,   KeyWordActive,           507,
                "actual MuLanPa keyword parsers");
//  CREATE_PARSER(TiPa_,   KeyWordComment,"KeyWordComment","key word comment",508);
  CREATE_PARSER(TiPa_Sequence,    KindOfKeyWord,           550,
                "kind of keyword parser");

  GET_PARSER(TiPa_Rule,      KeyWord);
  GET_PARSER(TiPa_Sequence,  Escape);
  GET_PARSER(TiPa_Character, ParanthesisOpen);
  GET_PARSER(TiPa_Character, ParanthesisClose);
  GET_PARSER(TiPa_Character, Comma);
  GET_PARSER(TiPa_Rule,      Skip);
  GET_PARSER(TiPa_Rule,      Comment);



  LimiterString->init('"');

  KeyWord_StringCharacter->init(TiPa_Character::CharMin,TiPa_Character::CharMax);
  KeyWord_StringCharacter->exclude('"');
  KeyWord_StringCharacter->exclude('\\');

  KeyWordCharacter->init(TiPa_Condition::Cnd_OrExc, Escape, KeyWord_StringCharacter) ;

  KeyWordCharacterCount->init(TiPa_Counter::Cnt_OptionMore, KeyWordCharacter);

  KeyWordParameter->init(TiPa_Sequence::Seq_HrdSq, LimiterString, KeyWordCharacterCount);
  KeyWordParameter->contractor_ParserInsert(LimiterString,2);

  KeyWord_Comment->init("comment_p");// c/c++ comment

  KeyWordCommentSingle->init(TiPa_Sequence::Seq_HrdSq, KeyWord_Comment, ParanthesisOpen);
  KeyWordCommentSingle->contractor_ParserInsert(KeyWordParameter,2);
  KeyWordCommentSingle->contractor_ParserInsert(ParanthesisClose,3);
  KeyWordCommentSingle->skip_ParserSet(Skip);

  KeyWordCommentDouble->init(TiPa_Sequence::Seq_HrdSq, KeyWord_Comment, ParanthesisOpen);
  KeyWordCommentDouble->contractor_ParserInsert(KeyWordParameter,2);
  KeyWordCommentDouble->contractor_ParserInsert(Comma,           3);
  KeyWordCommentDouble->contractor_ParserInsert(KeyWordParameter,4);
  KeyWordCommentDouble->contractor_ParserInsert(ParanthesisClose,5);
  KeyWordCommentDouble->skip_ParserSet(Skip);

  KeyWord_Str->init("str_p")    ;// string

  KeyWordStringFull->init(TiPa_Sequence::Seq_HrdSq, KeyWord_Str, ParanthesisOpen);
  KeyWordStringFull->contractor_ParserInsert(KeyWordParameter,2);
  KeyWordStringFull->contractor_ParserInsert(ParanthesisClose,3);
  KeyWordStringFull->skip_ParserSet(Skip);

  KeyWordString->init(TiPa_Condition::Cnd_OrExc, KeyWordStringFull, KeyWordParameter);

  KeyWord_ChSeq->init("chseq_p")  ;// character sequence

  KeyWordCharSequence->init(TiPa_Sequence::Seq_HrdSq, KeyWord_ChSeq, ParanthesisOpen);
  KeyWordCharSequence->contractor_ParserInsert(KeyWordParameter,2);
  KeyWordCharSequence->contractor_ParserInsert(ParanthesisClose,3);
  KeyWordCharSequence->skip_ParserSet(Skip);

  KeyWordComment->init(TiPa_Counter::Cnt_OptionMore, Comment);
                                                      // may occur zero ore more times
  KeyWordActive->init(TiPa_Condition::Cnd_OrExc,
                                         KeyWordCommentSingle,
                                         KeyWordCommentDouble);
  KeyWordActive->contractor_ParserInsert(KeyWordString      ,2);
  KeyWordActive->contractor_ParserInsert(KeyWordCharSequence,3);

  KeyWordComment->init(TiPa_Counter::Cnt_OptionMore, Comment);
                                                      // may occur zero ore more times
  KindOfKeyWord->init(TiPa_Sequence::Seq_HrdSq, KeyWordActive, KeyWordComment);

  KeyWord->init(KindOfKeyWord);
/*
  Done = true;
 }
*/
}



/* @MRTZ_describe Spirit185_Internal_create_RuleBin

*/
void Spirit185_Internal::create_RuleBin(void)
{
/*
 static bool Done = false;
 if(Done == false)
 {
//  create_Primitive();
//  create_RuleCharacter();
//  create_RuleKeyWord();
//  create_RuleIdentifier();
//  create_RuleUni();
//  create_RuleSub();
*/



  CREATE_PARSER(TiPa_Condition, BinOperand,          602,
                "operands of a MuLanPa binary operation");

  CREATE_PARSER(TiPa_String,      BinGtGt,             Spirit185_Internal::BinOperand_HrdSeq_rid+1,
                "shift variant");
  CREATE_PARSER(TiPa_String,      BinAndAnd,           Spirit185_Internal::BinOperand_HrdSeq_rid+2,
                "and variant");
  CREATE_PARSER(TiPa_Condition,   BinHrdSeq_Operator,  Spirit185_Internal::BinOperand_HrdSeq_rid+3,
                "operator for serial sequence");
  CREATE_PARSER(TiPa_Sequence,    BinOperation_HrdSeq, Spirit185_Internal::BinOperand_HrdSeq_rid+4,
                "second part of operation for serial sequence");
  CREATE_PARSER(TiPa_Counter,     BinOperand_HrdSeq,   Spirit185_Internal::BinOperand_HrdSeq_rid,
                "multi part of operation for serial sequence");

  CREATE_PARSER(TiPa_Character,   BinPerCent,          Spirit185_Internal::BinOperand_Seprt_rid+1,
                "operator for table sequence");
  CREATE_PARSER(TiPa_Sequence,    BinOperation_Seprt,  Spirit185_Internal::BinOperand_Seprt_rid+2,
                "second part of operation for table sequence");
  CREATE_PARSER(TiPa_Counter,     BinOperand_Seprt,    Spirit185_Internal::BinOperand_Seprt_rid,
                "multi part of operation for table sequence");

  CREATE_PARSER(TiPa_String,      BinOrOr,             Spirit185_Internal::BinOperand_SftSq_rid+1,
                "operator for inclusive-or sequence");
  CREATE_PARSER(TiPa_Sequence,    BinOperation_SftSq,  Spirit185_Internal::BinOperand_SftSq_rid+2,
                "second part of operation for inclusive-or sequence");
  CREATE_PARSER(TiPa_Counter,     BinOperand_SftSq,    Spirit185_Internal::BinOperand_SftSq_rid,
                "multi part of operation for inclusive-or sequence");

  CREATE_PARSER(TiPa_Character,   BinMinus,            Spirit185_Internal::BinOperand_WthOt_rid+1,
                "operator for without operation");
  CREATE_PARSER(TiPa_Sequence,    BinOperation_WthOt,  Spirit185_Internal::BinOperand_WthOt_rid+2,
                "second part of operation for without operation");
  CREATE_PARSER(TiPa_Counter,     BinOperand_WthOt,    Spirit185_Internal::BinOperand_WthOt_rid,
                "multi part of operation for without operation");

  CREATE_PARSER(TiPa_Character,   BinAndCharacter,     Spirit185_Internal::BinOperand_And_rid+1,
                "operator for and operation character");
  CREATE_PARSER(TiPa_Condition,   BinAnd,              Spirit185_Internal::BinOperand_And_rid+2,
                "exclude and and");
  CREATE_PARSER(TiPa_Sequence,    BinOperation_And,    Spirit185_Internal::BinOperand_And_rid+3,
                "second part of operation for and operation character");
  CREATE_PARSER(TiPa_Counter,     BinOperand_And,      Spirit185_Internal::BinOperand_And_rid,
                "multi part of operation for and operation character");

  CREATE_PARSER(TiPa_Character,   BinOrCharacter,      Spirit185_Internal::BinOperand_OrInc_rid+1,
                "operator for inclusive-or operation character");
  CREATE_PARSER(TiPa_Condition,   BinOr,               Spirit185_Internal::BinOperand_OrInc_rid+2,
                "exclude or or");
  CREATE_PARSER(TiPa_Sequence,    BinOperation_OrInc,  Spirit185_Internal::BinOperand_OrInc_rid+3,
                "second part of operation for inclusive-or operation character");
  CREATE_PARSER(TiPa_Counter,     BinOperand_OrInc,    Spirit185_Internal::BinOperand_OrInc_rid,
                "multi part of operation for inclusive-or operation character");

  CREATE_PARSER(TiPa_Character,   BinExOr,             Spirit185_Internal::BinOperand_OrExc_rid+1,
                "operator for exclusive-or operation");
  CREATE_PARSER(TiPa_Sequence,    BinOperation_OrExc,  Spirit185_Internal::BinOperand_OrExc_rid+2,
                "second part of operation for exclusive-or operation");
  CREATE_PARSER(TiPa_Counter,     BinOperand_OrExc,    Spirit185_Internal::BinOperand_OrExc_rid,
                "multi part of operation for exclusive-or operation");





  CREATE_PARSER(TiPa_Condition, SeqSecond,             603,
                "second part of binary parsers");
  CREATE_PARSER(TiPa_Sequence,  SeqOperationActive,    604,
                "actual MuLanPa binary parsers");
  CREATE_PARSER(TiPa_Sequence, KindOfSeqOperation,     605,
                "kind of binary parser");

  CREATE_PARSER(TiPa_Condition, CndSecond,             606,
                "second part of binary parsers");
  CREATE_PARSER(TiPa_Sequence,  CndOperationActive,    607,
                "actual MuLanPa binary parsers");

  CREATE_PARSER(TiPa_Sequence, KindOfCndOperation,     608,
                "kind of binary parser");


  CREATE_PARSER(TiPa_Counter,     BinComment,          609,
                "potential comment");


//  GET_PARSER(TiPa_Rule, BinOperation);
  GET_PARSER(TiPa_Rule, SeqOperation);
  GET_PARSER(TiPa_Rule, CndOperation);
  GET_PARSER(TiPa_Rule, Primitive);
  GET_PARSER(TiPa_Rule, Character);
  GET_PARSER(TiPa_Rule, KeyWord);
  GET_PARSER(TiPa_Rule, Identifier);
  GET_PARSER(TiPa_Rule, UniOperation);
  GET_PARSER(TiPa_Rule, SubParser);
  GET_PARSER(TiPa_Rule, Skip);
  GET_PARSER(TiPa_Rule, Comment);


  BinOperand->init(TiPa_Condition::Cnd_OrInc,
                                      Primitive,
                                      Character,      TiPa_Condition::PrDr_Default);
  BinOperand->contractor_ParserInsert(KeyWord     ,2);
  BinOperand->contractor_ParserInsert(Identifier  ,3);
  BinOperand->contractor_ParserInsert(UniOperation,4);
  BinOperand->contractor_ParserInsert(SubParser   ,5);

  BinGtGt->init(">>");
  BinAndAnd->init("&&");
  BinHrdSeq_Operator->init(TiPa_Condition::Cnd_OrExc, BinGtGt, BinAndAnd);
  BinOperation_HrdSeq->init(TiPa_Sequence::Seq_HrdSq, BinHrdSeq_Operator, BinOperand);
  BinOperation_HrdSeq->skip_ParserSet(Skip);
  BinOperand_HrdSeq->init(TiPa_Counter::Cnt_OneOrMore, BinOperation_HrdSeq);

  BinPerCent->init('%');
  BinOperation_Seprt->init(TiPa_Sequence::Seq_HrdSq, BinPerCent, BinOperand);
  BinOperation_Seprt->skip_ParserSet(Skip);
  BinOperand_Seprt->init(TiPa_Counter::Cnt_OneOrMore, BinOperation_Seprt);

  BinOrOr->init("||")  ;
  BinOperation_SftSq->init(TiPa_Sequence::Seq_HrdSq, BinOrOr, BinOperand);
  BinOperation_SftSq->skip_ParserSet(Skip);
  BinOperand_SftSq->init(TiPa_Counter::Cnt_OneOrMore,BinOperation_SftSq);

  BinMinus->init('-');
  BinOperation_WthOt->init(TiPa_Sequence::Seq_HrdSq, BinMinus, BinOperand);
  BinOperation_WthOt->skip_ParserSet(Skip);
  BinOperand_WthOt->init(TiPa_Counter::Cnt_OneOrMore, BinOperation_WthOt);

  BinAndCharacter->init('&');
  BinAnd->init(TiPa_Condition::Cnd_WthOt, BinAndCharacter, BinAndAnd);// and operation
  BinOperation_And->init(TiPa_Sequence::Seq_HrdSq, BinAnd, BinOperand);
  BinOperation_And->skip_ParserSet(Skip);
  BinOperand_And->init(TiPa_Counter::Cnt_OneOrMore, BinOperation_And);

  BinOrCharacter->init('|');//
  BinOr->init(TiPa_Condition::Cnd_WthOt, BinOrCharacter, BinOrOr);// inclusive-or operation
  BinOperation_OrInc->init(TiPa_Sequence::Seq_HrdSq, BinOr, BinOperand);
  BinOperation_OrInc->skip_ParserSet(Skip);
  BinOperand_OrInc->init(TiPa_Counter::Cnt_OneOrMore, BinOperation_OrInc);

  BinExOr->init('^');
  BinOperation_OrExc->init(TiPa_Sequence::Seq_HrdSq, BinExOr, BinOperand);
  BinOperation_OrExc->skip_ParserSet(Skip);
  BinOperand_OrExc->init(TiPa_Counter::Cnt_OneOrMore, BinOperation_OrExc);






  SeqSecond->init(TiPa_Condition::Cnd_OrExc,
                                      BinOperand_HrdSeq,
                                      BinOperand_Seprt) ;
  SeqSecond->contractor_ParserInsert( BinOperand_SftSq,2);


  CndSecond->init(TiPa_Condition::Cnd_OrExc,
                                      BinOperand_WthOt,
                                      BinOperand_And) ;
  CndSecond->contractor_ParserInsert( BinOperand_OrInc,2);
  CndSecond->contractor_ParserInsert( BinOperand_OrExc,3);


  SeqOperationActive->init(TiPa_Sequence::Seq_HrdSq,
                                          BinOperand,
                                          SeqSecond);

  CndOperationActive->init(TiPa_Sequence::Seq_HrdSq,
                                          BinOperand,
                                          CndSecond);



  BinComment->init(TiPa_Counter::Cnt_OptionMore, Comment);
                                                      // may occur zero ore more times
  KindOfSeqOperation->init(TiPa_Sequence::Seq_HrdSq, SeqOperationActive, BinComment);
  KindOfSeqOperation->skip_ParserSet(Skip);

  SeqOperation->init(KindOfSeqOperation);

  KindOfCndOperation->init(TiPa_Sequence::Seq_HrdSq, CndOperationActive, BinComment);
  KindOfCndOperation->skip_ParserSet(Skip);

  CndOperation->init(KindOfCndOperation);





/*
  Done = true;
 }
*/
}



/* @MRTZ_describe Spirit185_Internal_create_RuleUni

*/
void Spirit185_Internal::create_RuleUni(void)
{
/*
 static bool Done = false;
 if(Done == false)
 {
//  create_Primitive();
//  create_RuleCharacter();
//  create_RuleKeyWord();
//  create_RuleIdentifier();
//  create_RuleSub();
*/
  CREATE_PARSER(TiPa_Condition, UniOperand,            701,
                "operands of a MuLanPa unary operation");

  CREATE_PARSER(TiPa_Character,   UniNot,                Spirit185_Internal::UniOperand_OptionOne_rid+1,
                "operator for one match or nothing");
  CREATE_PARSER(TiPa_Sequence, UniOperand_OptionOne,     Spirit185_Internal::UniOperand_OptionOne_rid,
                "operation  one match or nothing");

  CREATE_PARSER(TiPa_Character,   UniStar,               Spirit185_Internal::UniOperand_OptionMore_rid+1,
                "operator for zero or more matches");
  CREATE_PARSER(TiPa_Sequence, UniOperand_OptionMore,    Spirit185_Internal::UniOperand_OptionMore_rid,
                "operation zero or more matches");

  CREATE_PARSER(TiPa_Character,   UniPlus,               Spirit185_Internal::UniOperand_OneOrMore_rid+1,
                "operator for one or more matches");
  CREATE_PARSER(TiPa_Sequence, UniOperand_OneOrMore,     Spirit185_Internal::UniOperand_OneOrMore_rid,
                "operation one or more matches");

  CREATE_PARSER(TiPa_Character,   UniTilde,              Spirit185_Internal::UniOperand_AllButNot_rid+1,
                "operator for every character without");
  CREATE_PARSER(TiPa_Sequence, UniOperand_AllButNot,     Spirit185_Internal::UniOperand_AllButNot_rid,
                "operation every character without");

  CREATE_PARSER(TiPa_Condition, UniOperationActive,      702,
                "actual MuLanPa unary parsers");
  CREATE_PARSER(TiPa_Counter,     UniComment,            703,
                "potential comment");
  CREATE_PARSER(TiPa_Sequence, KindOfUniOperation,       750,
                "kind of unary parser");


  GET_PARSER(TiPa_Rule, UniOperation);
  GET_PARSER(TiPa_Rule, Primitive);
  GET_PARSER(TiPa_Rule, Character);
  GET_PARSER(TiPa_Rule, KeyWord);
  GET_PARSER(TiPa_Rule, Identifier);
  GET_PARSER(TiPa_Rule, SubParser);
  GET_PARSER(TiPa_Rule, Skip);
  GET_PARSER(TiPa_Rule, Comment);

  UniOperand->init(TiPa_Condition::Cnd_OrInc, Primitive,
                                              Character,  TiPa_Condition::PrDr_Default) ;
  UniOperand->contractor_ParserInsert(        Identifier, 2);
  UniOperand->contractor_ParserInsert(        KeyWord   , 3);
  UniOperand->contractor_ParserInsert(        SubParser , 4);

  UniNot->init('!');
  UniOperand_OptionOne->init(TiPa_Sequence::Seq_HrdSq, UniNot, UniOperand);
  UniOperand_OptionOne->skip_ParserSet(Skip);

  UniStar->init('*');
  UniOperand_OptionMore->init(TiPa_Sequence::Seq_HrdSq, UniStar, UniOperand);
  UniOperand_OptionMore->skip_ParserSet(Skip);

  UniPlus->init('+');
  UniOperand_OneOrMore->init(TiPa_Sequence::Seq_HrdSq, UniPlus, UniOperand);
  UniOperand_OneOrMore->skip_ParserSet(Skip);

  UniTilde->init('~');
  UniOperand_AllButNot->init(TiPa_Sequence::Seq_HrdSq, UniTilde, UniOperand);
  UniOperand_AllButNot->skip_ParserSet(Skip);

  UniOperationActive->init(TiPa_Condition::Cnd_OrExc, UniOperand_OptionOne,
                                                      UniOperand_OptionMore) ;
  UniOperationActive->contractor_ParserInsert(        UniOperand_OneOrMore,2);
  UniOperationActive->contractor_ParserInsert(        UniOperand_AllButNot,3);

  UniComment->init(TiPa_Counter::Cnt_OptionMore, Comment);
                                                      // may occur zero ore more times
  KindOfUniOperation->init(TiPa_Sequence::Seq_HrdSq, UniOperationActive,  UniComment);
  KindOfUniOperation->skip_ParserSet(Skip);

  UniOperation->init(KindOfUniOperation);
/*
  Done = true;
 }
*/
}



/* @MRTZ_describe Spirit185_Internal_create_RuleSub

*/
void Spirit185_Internal::create_RuleSub(void)
{
/*
 static bool Done = false;
 if(Done == false)
 {
*/
  CREATE_PARSER(TiPa_Sequence, SubParserActive,  801, "actual sub parser");
  CREATE_PARSER(TiPa_Counter,  SubParserComment, 802, "potential comment");
  CREATE_PARSER(TiPa_Sequence, SubParserContent, 810, "content of a sub parser");

  GET_PARSER(TiPa_Character,   ParanthesisOpen);
  GET_PARSER(TiPa_Character,   ParanthesisClose);

  GET_PARSER(TiPa_Rule, SubParser);
  GET_PARSER(TiPa_Rule, Parser);
  GET_PARSER(TiPa_Rule, Skip);
  GET_PARSER(TiPa_Rule, Comment);


  SubParserActive->init(TiPa_Sequence::Seq_HrdSq,
                                         ParanthesisOpen,
                                         Parser);
  SubParserActive->contractor_ParserInsert(ParanthesisClose,2);
  SubParserActive->skip_ParserSet(Skip);

  SubParserComment->init(TiPa_Counter::Cnt_OptionMore, Comment);
                                                      // may occur zero ore more times
  SubParserContent->init(TiPa_Sequence::Seq_HrdSq,SubParserActive,SubParserComment);
  SubParserContent->skip_ParserSet(Skip);

  SubParser->init(SubParserContent);
/*
  Done = true;
 }
*/
}



/* @MRTZ_describe Spirit185_Internal_create_RuleParser

*/
void Spirit185_Internal::create_RuleParser(void)
{
/*
 static bool Done = false;
 if(Done == false)
 {
//  create_RuleBin();
//  create_RuleUni();
//  create_Primitive();
//  create_RuleCharacter();
//  create_RuleKeyWord();
//  create_RuleIdentifier();
//  create_RuleSub();
*/

  CREATE_PARSER(TiPa_Condition, ParserSecond,  901, "primary part of a parser");
  CREATE_PARSER(TiPa_Condition, ParserActive,  902, "secondary part of a parser");
  CREATE_PARSER(TiPa_Counter,   ParserComment, 903, "potential comment");
  CREATE_PARSER(TiPa_Sequence,  ParserContent, 910, "content of parser");


  GET_PARSER(TiPa_Rule, Parser);
  GET_PARSER(TiPa_Rule, Primitive);
  GET_PARSER(TiPa_Rule, Character);
  GET_PARSER(TiPa_Rule, KeyWord);
  GET_PARSER(TiPa_Rule, Identifier);
//  GET_PARSER(TiPa_Rule, BinOperation);
  GET_PARSER(TiPa_Rule, SeqOperation);
  GET_PARSER(TiPa_Rule, CndOperation);
  GET_PARSER(TiPa_Rule, UniOperation);
  GET_PARSER(TiPa_Rule, SubParser);
  GET_PARSER(TiPa_Rule, Skip);
  GET_PARSER(TiPa_Rule, Comment);



  ParserSecond->init(TiPa_Condition::Cnd_OrInc,
                                        Primitive,
                                        Character,        TiPa_Condition::PrDr_Default) ;
  ParserSecond->contractor_ParserInsert(KeyWord   ,2);
  ParserSecond->contractor_ParserInsert(Identifier,3);

  ParserActive->init(TiPa_Condition::Cnd_OrInc,
                                        SeqOperation,
                                        CndOperation,     TiPa_Condition::PrDr_Default);
  ParserActive->contractor_ParserInsert(UniOperation,2);
  ParserActive->contractor_ParserInsert(ParserSecond,3);
  ParserActive->contractor_ParserInsert(SubParser   ,4);
  ParserActive->skip_ParserSet(Skip);

  ParserComment->init(TiPa_Counter::Cnt_OptionMore, Comment);
                                                      // may occur zero ore more times
  ParserContent->init(TiPa_Sequence::Seq_HrdSq, ParserActive, ParserComment);

  Parser->init(ParserContent);
/*
  Done = true;
 }
*/
}





/* @MRTZ_describe Spirit185_Internal_create_RuleRoot

*/
void Spirit185_Internal::create_RuleRoot(void)
{
/*
 static bool Done = false;
 if(Done == false)
 {
//  create_Token();
//  create_RuleIdentifier();
//  create_RuleParser();
//  create_Comment();
*/

  CREATE_PARSER(TiPa_Sequence,    RuleContent   ,Spirit185_Internal::RuleContent_rid,
                "actual MuLanPa grammar rule");

  CREATE_PARSER(TiPa_Condition,   RootElement   ,Spirit185_Internal::RootElement_rid,
                 "one MuLanPa grammar rule or comment");
  CREATE_PARSER(TiPa_Counter,     RootContent   ,Spirit185_Internal::RootContent_rid,
                 "all grammar rules");
  CREATE_PARSER(TiPa_Character,   RootAssign    ,Spirit185_Internal::Root_rid + 1,
                 "assign symbol of a MuLanPa grammar rule");
  CREATE_PARSER(TiPa_Character,   RootSemikolon ,Spirit185_Internal::Root_rid + 2,
                 "termination symbol of a MuLanPa grammar rule");
  //CREATE_PARSER(TiPa_Counter,     RootComment   ,Spirit185_Internal::Root_rid + 3,
  //              "potential comment");


  GET_PARSER(TiPa_Rule, Root);
  GET_PARSER(TiPa_Rule, Rule);
  GET_PARSER(TiPa_Rule, Parser);
  GET_PARSER(TiPa_Rule, Identifier);
  GET_PARSER(TiPa_Rule, Skip);
  GET_PARSER(TiPa_Rule, Comment);


  RootAssign->init('=') ;// assignment of rule to identifier
  RootSemikolon->init(';') ;// end of rule

//  RootComment->init(TiPa_Counter::Cnt_OptionMore, Comment);
//  RootComment->skip_ParserSet(Skip);
                                                      // may occur zero ore more times
  RuleContent->init(TiPa_Sequence::Seq_HrdSq,
                                       Identifier,
                                       RootAssign,      TiPa_Sequence::PrDr_Longest);
  RuleContent->contractor_ParserInsert(Parser       ,2);
  RuleContent->contractor_ParserInsert(RootSemikolon,3);
  //RuleContent->contractor_ParserInsert(Comment  ,4);
  RuleContent->skip_ParserSet(Skip);

  Rule->init(RuleContent);

  RootElement->init(TiPa_Condition::Cnd_OrInc, Rule, Comment);
  RootElement->skip_ParserSet(Skip);

  RootContent->init(TiPa_Counter::Cnt_OneOrMore, RootElement); // may occur ones ore more times
  //RootContent->skip_ParserSet(Skip);

  Root->init(RootContent);
/*
  Done = true;
 }
*/
}




#ifndef DOXYGEN
#define USING_NAMESPACE using namespace
//}; USING_NAMESPACE CL_SPIRIT185;
//}; USING_NAMESPACE CL_TDA_GRMCONCRETE;
//}; USING_NAMESPACE TDA_Grammar;
//}; USING_NAMESPACE TXTDIASM;
#undef  USING_NAMESPACE
#endif //DOXYGEN



