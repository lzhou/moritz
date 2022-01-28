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
    10.05.2015     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    10.05.2015...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/
#ifndef SPIRIT185_INTERNAL_H
 #define SPIRIT185_INTERNAL_H


#include<set>
#include<map>
//#include<list>
#include<vector>


#include "TDA_GrmConcrete.h"



using namespace std;

#ifndef DOXYGEN
//namespace TXTDIASM {
//namespace TDA_Grammar {
////namespace CL_TDA_GRMCONCRETE {
//namespace CL_SPIRIT185 {
#endif //DOXYGEN

/*!
definitions of an concrete parser-class to search for a single character
*/
class Spirit185_Internal:public TDA_GrmConcrete
{

 public:


 /// main rules wich define the key content of the spirit 1.8.5 parser-syntax as defined for MuLanPa
 typedef enum Rule_ID
 {
   Primitive_rid             =  100,      ///< primitive parser
   PrmAlnum_rid              =  101,      ///< primitive parser: alpha numeric characters
   PrmAlpha_rid              =  102,      ///< primitive parser: alphabetic characters
   PrmAnychar_rid            =  103,      ///< primitive parser: any charcter
   PrmBlank_rid              =  104,      ///< primitive parser: blank
   PrmCntrl_rid              =  105,      ///< primitive parser: control characters
   PrmDigit_rid              =  106,      ///< primitive parser: digits
   PrmGraph_rid              =  107,      ///< primitive parser: graphs
   PrmLower_rid              =  108,      ///< primitive parser: lower case characters
   PrmPrint_rid              =  109,      ///< primitive parser: printable characters
   PrmPunct_rid              =  110,      ///< primitive parser: punctuation
   PrmSign_rid               =  111,      ///< primitive parser: sign
   PrmSpace_rid              =  112,      ///< primitive parser: space
   PrmUpper_rid              =  113,      ///< primitive parser: upper case characters
   PrmXdigit_rid             =  114,      ///< primitive parser: hexadecimal digits
   PrmBin_rid                =  115,      ///< primitive parser: binary digits
   PrmHex_rid                =  116,      ///< primitive parser: hexadecimal numbers
   PrmOct_rid                =  117,      ///< primitive parser: octal numbers
   PrmEscape_rid             =  118,      ///< primitive parser: escape characters
   PrmEol_rid                =  119,      ///< primitive parser: end-of-line
   PrmEnd_rid                =  126,      ///< primitive parser: end of input/text to parse

   Comment_rid               =  200,      ///< comment inside the user-grammar

   Identifier_rid            =  300,      ///< identifying name of a user-rule

   Character_rid             =  400,      ///< character parsers
   LimiterCharacter_rid      =  Character_rid +  1, ///< begin and end of character
   CharCharacter_rid         =  Character_rid +  2, ///< any char except framing character
   CharacterID_rid           =  Character_rid +  3, ///< identifier of a character
   CharacterParameter_rid    =  Character_rid +  4, ///< parameter of a MuLanPa character parser function
   CharacterSingle_rid       =  Character_rid + 10, ///< character parser for one single character
   CharacterRange_rid        =  Character_rid + 20, ///< parser function for a character range

   KeyWord_rid               =  500,      ///< keyword parsers
   KeyWordCharacterCount_rid =  KeyWord_rid +  4, ///< character sequence of a string");
   KeyWordCommentSingle_rid  =  KeyWord_rid + 10, ///< parser function for a single line commenting string
   KeyWordCommentDouble_rid  =  KeyWord_rid + 20, ///< parser function for a block commenting string
   KeyWordString_rid         =  KeyWord_rid + 30, ///< parser for a real string
   KeyWordCharSequence_rid   =  KeyWord_rid + 40, ///< parser function for a character sequence

   BinSequence_rid           =  600,      ///< sequence parser
   BinCondition_rid          =  601,      ///< condition parser
   BinOperand_HrdSeq_rid     =  610,      ///< multi part of operation for serial sequence
   BinOperand_Seprt_rid      =  620,      ///< multi part of operation for table sequence
   BinOperand_SftSq_rid      =  630,      ///< multi part of operation for inclusive-or sequence

   BinOperand_WthOt_rid      =  640,      ///< multi part of operation for without operation
   BinOperand_And_rid        =  650,      ///< multi part of operation for and operation character
   BinOperand_OrInc_rid      =  660,      ///< multi part of operation for inclusive-or operation character
   BinOperand_OrExc_rid      =  670,      ///< multi part of operation for exclusive-or operation

   UniOperation_rid          =  700,      ///< unary parser
   UniOperand_OptionOne_rid  =  710,      ///< operation  one match or nothing
   UniOperand_OptionMore_rid =  720,      ///< operation zero or more matches
   UniOperand_OneOrMore_rid  =  730,      ///< operation one or more matches
   UniOperand_AllButNot_rid  =  740,      ///< operation every character without

   SubParser_rid             =  800,      ///< sub parser framed with ( and )

   Parser_rid                =  900,      ///< parser

   Rule_rid                  = 1000,      ///< single rule
   RuleContent_rid           = Rule_rid + 4,  ///< actual MuLanPa grammar rule
   Root_rid                  = 1100,      ///< valid text content
   RootElement_rid           = Root_rid +  5, ///< one MuLanPa grammar rule or comment
   RootContent_rid           = Root_rid + 10, ///< all grammar rules

   Skip_rid                  = 0,         ///< content to ignore

 }Rule_ID;




 /*!
 @brief default constructor

 @param [in] contextModel management-object that creates and deletes associations and data-objects
 @param [in] debugMode    forces the grammar to store debug-data if set to true
 <br><br>
 @htmlinclude Spirit185_Internal_Spirit185_Internal.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    10.05.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
explicit Spirit185_Internal(TiPa_Concrete::DataModel* contextModel, bool debugMode = false);






 /*!
 @brief constructor

 @param [in] grammar      script-text written in the notation of spirit 1.8.5
 @param [in] contextModel management-object that creates and deletes associations and data-objects
 @param [in] debugMode    forces the grammar to store debug-data if set to true

 <br><br>
 @htmlinclude Spirit185_Internal_Spirit185_Internal.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    10.05.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd

*/
explicit  Spirit185_Internal(const char*               grammar,
                             TiPa_Concrete::DataModel* contextModel,
                             bool                      debugMode = false);






 /*!
 @brief destructor
 <br><br>
 @htmlinclude "Spirit185_Internal__Spirit185_Internal.html"
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    10.05.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
   ~Spirit185_Internal(void);








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

 @htmlinclude "Spirit185_Internal__parse.html"

 <br><br>
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    28.07.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 const char * parse(const char* begin, const char* end, const char* rule = nullptr) override;




typedef enum Attributes
{
  UserName        = 0,
  UserID          = 1,
  UserDescription = 2,
  Line            = 3,
  Column          = 4,
}
Attributes;


/* !
 return the attributes of a parser known by the grammar

 @param [out] returnValue container to fill
 @param [in]  parser      source of parser describing attributes
 @param [in]  character   actual begin of parser-result


 @return a list of all attributes containing the identifiers as well as the values


 <br><br>
 @htmlinclude "Spirit185_Internal__tree.html"
 @I_______________________________________________________
    28.07.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
void attributes(vector<TiPa_Data::ParserAttribute_TP>* returnValue,
                TiPa_Concrete*                         parser,
                const char*                            character);

*/










 protected:

 private:



/*!
 defines a collection of basic token parsers
 <br><br>
 @htmlinclude Spirit185_Internal_create_Token.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    10.05.2015   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  void   create_Token(void);



/*!
 defines a collection of basic token parsers
 <br><br>
 @htmlinclude Spirit185_Internal_create_Primitive.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    10.05.2015   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  void   create_Primitive(void);




/*!
 defines the rule that describes a comment inside the MuLanPa rule
 <br><br>
 @htmlinclude Spirit185_Internal_create_Token.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    10.05.2015   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  void   create_Comment(void);




/*!
 defines the construction of a name used as identifier
 or rulenames

 <br>

  Grm.Identifier = (
                    (
                     (    (ch_p('_') | alpha_p)
                      >> *(ch_p('_') | alpha_p | digit_p)
                     )
                     - "lexeme_d"
                    )//[Act_GrammarDebugger("ID")]
                   );

 <br>

 @htmlinclude Spirit185_Internal_create_RuleIdentifier.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    10.05.2015   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  void   create_RuleIdentifier(void);


/*!
 difines a single character or a range of characters

 <br>

  Grm.Character1      = (c_escape_ch_p | anychar_p);
  Grm.Character2      = (c_escape_ch_p | anychar_p);

  Grm.CharacterSingle = (    str_p("ch_p")
                          >> ch_p('(')
                          >> ch_p('\'')
                          >> Grm.Character1//[Act_GrammarDebugger("ch_p")]
                          >> ch_p('\'')
                          >> ch_p(')')
                        )
                       |(    ch_p('\'')
                         >>  Grm.Character1//[Act_GrammarDebugger("ch_p")]
                         >>  ch_p('\'')
                        );

  Grm.CharacterRange = (   str_p("range_p")
                         >> ch_p('(')
                         >> (    ch_p('\'')
                              >> Grm.Character1
                              >> ch_p('\'')
                              >> ch_p(',')
                              >> ch_p('\'')
                              >> Grm.Character2
                              >> ch_p('\'')
                            )//[Act_GrammarDebugger("range_p")]
                         >> ch_p(')')
                       );

  Grm.Character = (Grm.CharacterSingle | Grm.CharacterRange);

 <br>

 @htmlinclude Spirit185_Internal_create_RuleCharacter.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    10.05.2015   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  void   create_RuleCharacter(void);

/*!
 defines strings, character-sequences and comment-keys

 <br>

  Grm.KeyWord1             = (c_escape_ch_p | (anychar_p ^ ch_p('\"')));
  Grm.KeyWord2             = (c_escape_ch_p | (anychar_p ^ ch_p('\"')));

  Grm.KeyWordCommentSingle = (    str_p("comment_p")
                               >> ch_p('(')
                               >> confix_p( ch_p('\"'), *Grm.KeyWord1, ch_p('\"')
                                          )//[Act_GrammarDebugger("comment_p")]
                               >> ch_p(')')
                             );

  Grm.KeyWordCommentDouble = (   str_p("comment_p")
                               >> ch_p('(')
                               >> (    confix_p( ch_p('\"'), *Grm.KeyWord1, ch_p('\"'))
                                    >> ch_p(',')
                                    >> confix_p( ch_p('\"'), *Grm.KeyWord2, ch_p('\"'))
                                  )//[Act_GrammarDebugger("comment_p")]
                               >> ch_p(')')
                             );

  Grm.KeyWordString        = (    str_p("str_p")
                               >> ch_p('(')
                               >> confix_p( ch_p('\"'), *Grm.KeyWord1, ch_p('\"')
                                         )//[Act_GrammarDebugger("str_p")]
                               >> ch_p(')')
                             )
                            |confix_p( ch_p('\"'), *Grm.KeyWord1, ch_p('\"')
                                     );//[Act_GrammarDebugger("str_p")]

  Grm.KeyWordCharSequence = (    str_p("chseq_p")
                              >> ch_p('(')
                              >> confix_p( ch_p('\"'), *Grm.KeyWord1, ch_p('\"')
                                         )//[Act_GrammarDebugger("chseq_p")]
                              >> ch_p(')')
                            );

  Grm.KeyWord =   Grm.KeyWordCommentSingle
                | Grm.KeyWordCommentDouble
                | Grm.KeyWordString
                | Grm.KeyWordCharSequence;

 <br>

 @htmlinclude Spirit185_Internal_create_RuleKeyWord.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    10.05.2015   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  void   create_RuleKeyWord(void);


/*!
 defines rules which combine 2 or more other parsers
 as special terms
 <br>

  Grm.BinFirst =   (  Grm.Primitive    | Grm.Character | Grm.KeyWord
                    | Grm.Identifier   | Grm.Uni       | Grm.Sub
                   );//first oparant of a bin-oparaor sequenze

  Grm.BinFldBy =   (str_p(">>") | str_p("&&"))
                >> (  Grm.Primitive    | Grm.Character | Grm.KeyWord
                    | Grm.Identifier   | Grm.Uni       | Grm.Sub
                   ); // next part of serial sequenze

  Grm.Bin1oFld =   str_p("||")
                >> (  Grm.Primitive    | Grm.Character | Grm.KeyWord
                    | Grm.Identifier   | Grm.Uni       | Grm.Sub
                   ); // next part of inclusive-or sequenze

  Grm.BinSeprt =   str_p("%")
                >> (  Grm.Primitive    | Grm.Character | Grm.KeyWord
                    | Grm.Identifier   | Grm.Uni       | Grm.Sub
                   ); // next part of table sequenze

  Grm.BinWthOt =  str_p("-")
                >> (  Grm.Primitive  | Grm.Character | Grm.KeyWord
                    | Grm.Identifier | Grm.Uni | Grm.Sub
                   ); // next part of without operation

  Grm.BinAnd   =   str_p("&")
                >> (  Grm.Primitive    | Grm.Character | Grm.KeyWord
                    | Grm.Identifier   | Grm.Uni       | Grm.Sub
                   ); // next part of and operation

  Grm.BinOrInc =   str_p("|")
                >>(  Grm.Primitive    | Grm.Character | Grm.KeyWord
                   | Grm.Identifier   | Grm.Uni       | Grm.Sub
                  ); // next part of inclusive-or operation

  Grm.BinOrExc =   str_p("^")
                >>(  Grm.Primitive    | Grm.Character | Grm.KeyWord
                   | Grm.Identifier   | Grm.Uni       | Grm.Sub
                  ); // next part of exclusive-or operation

  Grm.Bin = (    Grm.BinFirst
              >> (   +(Grm.BinFldBy)//[Act_GrammarDebugger("FldBy")]
                   | +(Grm.Bin1oFld)//[Act_GrammarDebugger("1oFld")]
                   | +(Grm.BinSeprt)//[Act_GrammarDebugger("Seprt")]
                   | +(Grm.BinWthOt)//[Act_GrammarDebugger("WthOt")]
                   | +(Grm.BinAnd  )//[Act_GrammarDebugger("And"  )]
                   | +(Grm.BinOrInc)//[Act_GrammarDebugger("OrInc")]
                   | +(Grm.BinOrExc)//[Act_GrammarDebugger("OrExc")]
                  )
            );
 <br>

 @htmlinclude Spirit185_Internal_create_RuleBin.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    10.05.2015   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  void   create_RuleBin(void);

/*!
 defines rules which make a operation with one other parser

 <br>

  Grm.UniOptionOne  =    str_p("!")
                      >> (  Grm.Primitive    | Grm.Character | Grm.KeyWord
                          | Grm.Identifier | Grm.Sub
                         ); // one match or nothing

  Grm.UniOptionMore =    str_p("*")
                      >> (  Grm.Primitive    | Grm.Character | Grm.KeyWord
                          | Grm.Identifier | Grm.Sub
                         ); // zero or mor matches

  Grm.UniOneOrMore  =    str_p("+")
                      >> (  Grm.Primitive    | Grm.Character | Grm.KeyWord
                          | Grm.Identifier | Grm.Sub
                         ); // one or mor matches

  Grm.UniAllButNot  =    str_p("~")
                      >> (  Grm.Primitive    | Grm.Character | Grm.KeyWord
                          | Grm.Identifier | Grm.Sub
                         ); // every character without

  Grm.Uni = (   (Grm.UniOptionOne) //[Act_GrammarDebugger("Option_One")]
              | (Grm.UniOptionMore)//[Act_GrammarDebugger("Option_More")]
              | (Grm.UniOneOrMore) //[Act_GrammarDebugger("OneOrMore")]
              | (Grm.Uni) //[Act_GrammarDebugger("AllButNot")]
            );

 <br>

 @htmlinclude Spirit185_Internal_create_RuleUni.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    10.05.2015   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  void   create_RuleUni(void);


/*!
 defines how a couple of parsers has to be set between two
 parenthesis
 <br>

  Grm.Sub =    (   str_p("(")//[Act_GrammarDebugger("(")]
                >> Grm.Parser
                >> str_p(")")//[Act_GrammarDebugger(")")]
               );//[Act_GrammarDebugger("Sb")]

 <br>

 @htmlinclude Spirit185_Internal_create_RuleSub.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    10.05.2015   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  void   create_RuleSub(void);

/*!
 defines the collection of rule-constructions wich may be used to
 define a single grammar-rule.
 <br>

  Grm.Parser = (  Grm.Bin          //[Act_GrammarDebugger("BinParser")]
                | Grm.Uni          //[Act_GrammarDebugger("UniParser")]
                | (  Grm.Primitive
                   | Grm.Character
                   | Grm.KeyWord
                   | Grm.Identifier
                  )                //[Act_GrammarDebugger("BaseParser")]
                | Grm.Sub          //[Act_GrammarDebugger("SubParser")]
               );

 <br>

 @htmlinclude Spirit185_Internal_create_RuleParser.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    10.05.2015   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  void   create_RuleParser(void);
/*!
 defines the root of the parser-tree as the assignment
 <br> rulename = rule

 <br>

  Grm.Root  =  +( (    Grm.Identifier// [Act_GrammarDebugger("Var")]
                    >> (   str_p("=")//[Act_GrammarDebugger("=")]
                        >> Grm.Parser
                        >> str_p(";")//[Act_GrammarDebugger(";")]
                       )//[Act_GrammarDebugger("Def")]
                   )//[Act_GrammarDebugger("Rule")]
                  |(  comment_p("//")
                    | comment_p("/ *", "* /")
                   )//[Act_GrammarDebugger("Comment")]
                 );

 <br>

 @htmlinclude Spirit185_Internal_create_RuleRoot.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    22.03.2015   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  void   create_RuleRoot(void);






// /* !
// Attributes of class
// */
//  struct Att
//  {
//
//  }Att;







#ifdef UNITTEST
 public:
#else // UNITTEST
 private:
#endif // UNITTEST



};



#ifndef DOXYGEN
#define USING_NAMESPACE using namespace
//}; USING_NAMESPACE CL_SPIRIT185;
//}; USING_NAMESPACE CL_TDA_GRMCONCRETE;
//}; USING_NAMESPACE TDA_Grammar;
//}; USING_NAMESPACE TXTDIASM;
#undef  USING_NAMESPACE
#endif //DOXYGEN




#endif //SPIRIT185_INTERNAL_H
