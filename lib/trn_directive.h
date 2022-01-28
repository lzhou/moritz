/*!

 @file
 @brief    definition of an expression evaluation

 This file contains the definition of a class to evaluate source expressions
 to force internal decisions


 Copyright (C) 2011-2020 by Eckard Klotz.

 Permission to use, copy, modify, and distribute this software and its
 documentation under the terms of the GNU General Public License is hereby
 granted. No representations are made about the suitability of this software
 for any purpose. It is provided "as is" without express or implied warranty.
 See the GNU General Public License for more details.

 Documents produced by the binary of this source are derivative works derived from the
 input used in their production; they are not affected by this license.

 <b> History </b>

 @TabBegin
    date           @I author          @I implementation/change
 @I____________________________________________________________
    25.09.2011     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    25.09.2011...  @I Eckard Klotz
 @I Changes are documented in the comment of the changed element
 @TabEnd

*/
#ifndef TRN_DIRECTIVE_H
#define TRN_DIRECTIVE_H




#if defined(DEBUG_OUTPUT)
 #define SRINGIZE( define ) #define


#define R_FDL_COMPILER   R_FDL_COMP_GHS
#define R_FDL_COMP_GHS   1

#if R_FDL_COMPILER == R_FDL_COMP_GHS
 #error "it works"
#else
 #error "it works not"
#endif

#endif //DEBUG_OUTPUT













using namespace std;



//#include "tinyxml.h"
 #include "xml_DataModel.h"

#include"String_imp.h"

#include "expression.h"
#include "coreflow.h"


#ifndef DOXYGEN
//namespace CL_PROCESS {
//namespace CL_TRANSFORM {
//namespace CL_TRN_DIRECTIVE {
#endif //DOXYGEN


const String_imp EMPTYSTRING = "__EMPTYSTRING__";


typedef struct _s_TextLine
{
 String_imp Content;
 int        LineNumber;
// bool       Active;
 _s_TextLine(void)                                            :Content(""),                LineNumber(-1){};                                ///< @brief default constructor
 _s_TextLine(const String_imp& content, const int& lineNumber):Content(content),           LineNumber(lineNumber){};                        ///< @brief initializing constructor
 _s_TextLine(const _s_TextLine& original)                     :Content(original.Content),  LineNumber(original.LineNumber){};               ///< @brief copy constructor
 _s_TextLine& operator = (const _s_TextLine& original)        {Content = original.Content; LineNumber = original.LineNumber;return(*this);};///< @brief assignment operator
 ~_s_TextLine(void)                                           {Content.clear();            LineNumber = -1;};                               ///< @brief destructor
} _s_TextLine;

///used-decision if the content of a switch-directive should be solved by commenting out
///inactive code-parts if all switch-paths can be parsed or not
typedef enum KEEP_VALIDE_CODE_TP
{
 KVC_NEVER    = 0, ///< never keep valid code of inactive switch-parts
 KVC_IMPLICIT = 1, ///< keep valid-code only if the activity of a switch-part
                   ///  is not full defined by the user constants or terms
                   ///  and can only be solved implicitly by the assumption that the user
                   ///  accepts that the undefined constants should be treated as undefined
 KVC_ALLWAYS  = 2  ///< always keep valid code of inactive switch-parts
}KEEP_VALIDE_CODE_TP;




class Prcs_Trn_Directive:public Prcs_Trn_Source
{
 public:



/*!
 constructor

 @param [in] positionOutput control of inserting position-info
                            (line/column) as attributes into xml-tag
 <br>        0 => no tag gets position info
 <br>        1 => leaf-tags with text inside only get position-Info
 <br>        2 => all tags get position info (knot-tags without text inside
             will get the position of their first child)
 @param [in] normlzKwrdsOfSource user-configuration if source-keyword
                                 should be turned into low-case characters
 @param [in] showTextToParse user-configuration if text to parse should
                             be printed shown in the terminal-output
 @param [in] parseTolerant   user-configuration if parsing-process should
                             be restated again behind the position that caused
                             a parser-fail
 @param [in] startLine       wanted number of the first text-line
                             used as base for line-attributes
 @param [in] startColumn     wanted number of the first text-column
                             used as base for column-attributes
 @param [in] tokenIndent     token-string of indent
                             to insert into text where an indent was detected
 @param [in] tokenDedent     token-string of de-dent
                             to insert into text where an de-dent was detected
 @param [in] tokenNewLine    token-string of new-line
                             to insert into text where an new-line was detected
 @param [in] commentBegin    token-string of beginning special content used to keep an
                             inactive compiler-switch part in the source
 @param [in] commentEnd      token-string of ending special content used to keep an
                             inactive compiler-switch part in the source

 <br><br>
 @htmlinclude ./des/Prcs_Trn_Directive_Prcs_Trn_Directive.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    25.09.2011   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
    04.11.2012   @I  Eckard Klotz
 @I bug normalization of key-words is not working any more
    since implementation of context-parser
 @I normalization of key-words moved from comment-process
    to source-process
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 Prcs_Trn_Directive(int            positionOutput,
                    bool           normlzKwrdsOfSource,
                    bool           showTextToParse = false,
                    bool           parseTolerant   = false,
                    int            startLine       = 1,
                    int            startColumn     = 1,
              const String_imp&    tokenIndent     = "",
              const String_imp&    tokenDedent     = "",
              const String_imp&    tokenNewLine    = "",
              const String_imp&    commentBegin    = "/*- ",
              const String_imp&    commentEnd      = " -*/");

/*!
 destructor
 <br><br>
 @htmlinclude ./des/Prcs_Trn_Directive__Prcs_Trn_Directive.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    25.09.2011   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  virtual ~Prcs_Trn_Directive();



/*!
 create a new tool-object to evaluate a switch-expressions
 and defines set its constants like configured by the user.

 @param [in] variant XML-node that hods the user configurations
                     with the constant-values to use

 @htmlinclude ./des/Prcs_Trn_Directive_configureConstants.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    02.11.2011   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
    20.10.2013      @I  Eckard Klotz
 @I bug: XML-comments lead to crash
 @I XML-iterations will be done by using TiXMLNode instead
    of TiXmlElement,
    as first action in the loop a macro checks if the
    current-element is a XML-comment and forces immediately
    the start of the next loop
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void configureConstants(XML_Node  variant);


/*!
  set the core-sequence that should be used to test if switched text-parts
  contain valid code-parts

 @param [in] testParser user define parser-sequence

 @htmlinclude ./des/Prcs_Trn_Directive_setTestParser.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    01.12.2011   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void setTestParser(CoreFlow* testParser);



/*!
  set list of XML node-names that should be used while re-merging
  parser-results of directive-set variants

 @param [in] mergeLevel comma separated list of tag-names
 @param [in] variantID tag-name used to insert new tag levels inside of tags to merge,
                       which contain the child-tags of the variants

 @htmlinclude ./des/Prcs_Trn_Directive_setMergeLevel.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    17.12.2011   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void setMergeLevel(String_imp& mergeLevel, String_imp& variantID);



/*!
 evaluate an given XML-tree to find basic directive-conditions and their value-content

 @param [in]  root           root-element of the XML-tree to analyse
 @param [out] term           output-container that will be used for recursive calls also
 @param [in]  treatAsDefined false => the condition will be evaluated as if-condition
                             with the possible content true, false or unknown
              <br>           true => the condition will be evaluated as ifdef/ifndef-condition
                             with the possible content defined, undefined or unknown



 <br><br>
 @htmlinclude ./des/Prcs_Trn_Directive_getLogicTerms.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    25.09.2011   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @TabEnd
*/
  void  getLogicTerms(DataAssociation*                root,
                      map<String_imp,SwitchState_TP>* term,
                      bool                            treatAsDefined = false);




/*!
 evaluate an given text and returns the result as XML-tree

 @param [in] text   text to analyse
 @param [in] model  management-object that creates and deletes associations and data-objects
 @param [in] rule   name of rule used for parsing

 @return XML-tree that represents the test to analyse


 <br><br>
 @htmlinclude ./des/Prcs_Trn_Directive_analyse.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    25.09.2011   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
    02.08.2013   @I  Eckard Klotz
 @I re-factoring of base-design
 @I name of rule used for parsing is now an optional parameter
    normaly set to pass
 @TabEnd
*/
  TiPa_Concrete::DataFellow* analyse(String_imp*     text,
                                     TiPa_DataModel* model,
                                     String_imp      rule = "pass");





/*!
 create a map of source-parts associated to their line-number

 @param [in]  rootNew       root-node of the source XML-tree to evaluate
 @param [in]  context       management-object that creates and deletes associations and data-objects

 @return  container of source-snippets with the line-number of their
          begin as key-value

 @htmlinclude ./des/Prcs_Trn_Directive_getSourceParts.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    23.10.2011   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  map<int,String_imp>getSourceParts(DataAssociation* rootNew,
                                    TiPa_DataModel*  context);



/*!
 analyse the XML-tree of a compiler-switched source and marks all
 non-directive lines as active or not active

 @param [in]  keepValideCode  user decision if directive-switches
                              with completely valid code inside of all
                              switch-paths should be kept as living code
 @param [in]  rootNew         root-node of the XML-tree to evaluate
 @param [in]  context         management-object that creates and deletes associations and data-objects
 @param [in]  expressionCheck knows how to analyse expressions

 @return true if the content of the analysed root-node describes a code-part that
         can be parsed without commenting-out the inactive switch-path
 <br>    false if the parsing fails

 <br><br>
 @htmlinclude ./des/Prcs_Trn_Directive_analyze_SwitchedText.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    02.10.2011   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 bool analyze_SwitchedText(KEEP_VALIDE_CODE_TP keepValideCode,
                           DataAssociation*    rootNew         = nullptr,
                           TiPa_DataModel*     context         = nullptr,
                           Prsd_Expression*    expressionCheck = nullptr);


/*!
 split the pre-parsed source-text into its text-lines and switching
 directives

 @param [in]  rootNew      root-node of the XML-tree to evaluate
 @param [in]  context      management-object that creates and deletes associations and data-objects
 @param [out] analysedText list of text-lines and switching directives


 <br><br>
 @htmlinclude ./des/rcs_Trn_Directive_splitSource.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    19.10.2011   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void  splitSource(DataAssociation*   rootNew,
                   TiPa_DataModel*    context,
                   list<_s_TextLine>* analysedText);




/*!
 reconstruct the split parts of the analysed source to a new one where
 lines detected as not active will be commented out

 @param [in] commentOut     information witch lines should be commented out
                            since they are not active
 @param [in] splitSource  original text split in text-lines and directives

 @return the new source-text
 <br><br>
 @htmlinclude ./des/Prcs_Trn_Directive_splitSource.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    30.10.2011   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
    05.08.2012   @I  Eckard Klotz
 @I bug: multi-line directive are not completely out-commented with line comments
 @I line comment-beginners will now be inserted after every line-change inside
 @I_______________________________________________________
    18.12.2012   @I  Eckard Klotz
 @I implementation of new parser
 @I line comment-beginners and empty lines will not be inserted
    if the new parameter restoreEmptyLines is false
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 String_imp reassembleSource(map<int,bool>*     commentOut       = nullptr,
                             list<_s_TextLine>* splitSource      = nullptr,
                             bool               restoreEmtyLines = true);





/*!
  re-merge parser-results of directive-set variants

 @param [in] common      path and name of the file that holds the common result
 @param [in] variant     path and name of the file that holds the result variant
 @param [in] variantName name used in the variant-tag of the remerge-tree

 @htmlinclude ./des/Prcs_Trn_Directive_remerge.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    17.12.2011   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void remerge(const char* common,
              const char* variant,
              const char* variantName);


 protected:




 private:


/*!
 analyse the content of a text-block

 @param [in]  keepValideCode  user decision if directive-switches
                              with completely valid code inside of all
                              switch-paths should be kept as living code
 @param [in]  rootNew         root-node of the XML-tree to evaluate
 @param [in]  parentOn        activity of outer switch-path
 @param [in]  context         management-object that creates and deletes associations and data-objects
 @param [in]  expressionCheck object that is able to evaluate a switch-condition
 @param [out] commentOut      information witch lines should be commented out
                              since they are not active
 @return true if the content of the analysed root-node describes a code-part that
         can be parsed without commenting-out the inactive switch-path
 <br>    false if the parsing fails

 <br><br>
 @htmlinclude ./des/Prcs_Trn_Directive__analyze_P_Block.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    02.10.2011   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  bool _analyze_P_Block(KEEP_VALIDE_CODE_TP  keepValideCode,
                        DataAssociation*     rootNew,
                        TiPa_DataModel*      context,
                        bool                 parentOn,
                        Prsd_Expression*     expressionCheck,
                        map<int,bool>*       commentOut);

/*!
 analyse the content of a directive-expression

 @param [in]  keepValideCode  user decision if directive-switches
                              with completely valid code inside of all
                              switch-paths should be kept as living code
 @param [in]  rootNew         root-node of the XML-tree to evaluate
 @param [in]  context         management-object that creates and deletes associations and data-objects
 @param [in]  parentOn        activity of outer switch-path
 @param [in]  expressionCheck object that is able to evaluate a switch-condition
 @param [out] commentOut      information witch lines should be commented out
                              since they are not active

 @return true if the content of the analysed root-node describes a code-part that
         can be parsed without commenting-out the inactive switch-path
 <br>    false if the parsing fails

 <br><br>
 @htmlinclude ./des/Prcs_Trn_Directive__analyze_Preprocedure.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    02.10.2011   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  bool _analyze_Preprocedure(KEEP_VALIDE_CODE_TP keepValideCode,
                             DataAssociation*    rootNew,
                             TiPa_DataModel*     context,
                             bool                parentOn,
                             Prsd_Expression*    expressionCheck,
                             map<int,bool>*      commentOut);

/*!
 analyse the content of a switching directive-expression

 @param [in]  keepValideCode  user decision if directive-switches
                              with completely valid code inside of all
                              switch-paths should be kept as living code
 @param [in]  rootNew         root-node of the XML-tree to evaluate
 @param [in]  context         management-object that creates and deletes associations and data-objects
 @param [in]  parentOn        activity of outer switch-path
 @param [in]  expressionCheck object that is able to evaluate a switch-condition
 @param [out] commentOut      information witch lines should be commented out
                              since they are not active
 @return true if the content of the analysed root-node describes a code-part that
         can be parsed without commenting-out the inactive switch-path
 <br>    false if the parsing fails

 <br><br>
 @htmlinclude ./des/Prcs_Trn_Directive__analyze_compilerSwitch.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    02.10.2011   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  bool _analyze_compilerSwitch(KEEP_VALIDE_CODE_TP keepValideCode,
                               DataAssociation*    rootNew,
                               TiPa_DataModel*     context,
                               bool                parentOn,
                               Prsd_Expression*    expressionCheck,
                               map<int,bool>*      commentOut);

/*!
 analyse the activity-state of a switch-path

 @param [in]  keepValideCode  user decision if directive-switches
                              with completely valid code inside of all
                              switch-paths should be kept as living code
 @param [in]  rootNew         root-node of the XML-tree to evaluate
 @param [in]  context         management-object that creates and deletes associations and data-objects
 @param [in]  parentOn        activity of outer switch-path
 @param [in]  expressionCheck object that is able to evaluate a switch-condition
 @param [out] commentOut      information witch lines should be commented out
                              since they are not active
 @param [in]  wantedResult    defines the result for <b>switch-path is on</b>
 <br>                         that may differ for <b>elif</b> and <b>else</b>
 @param [out] onFound         information if the currently analysed switch-path
                              is active
 @return true if the content of the analysed root-node describes a code-part that
         can be parsed without commenting-out the inactive switch-path
 <br>    false if the parsing fails

 <br><br>
 @htmlinclude ./des/Prcs_Trn_Directive__analyze_SwitchContent.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    02.10.2011   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  bool _analyze_SwitchContent(KEEP_VALIDE_CODE_TP keepValideCode,
                              DataAssociation*    rootNew,
                              TiPa_DataModel*     context,
                              bool                parentOn,
                              Prsd_Expression*    expressionCheck,
                              map<int,bool>*      commentOut,
                              SwitchState_TP      wantedResult,
                              bool*               onFound);


/*!
 @brief read out the text-content of the given XML-node and its childes

 @param [in]  root      root-node of the XML-tree to evaluate
 @param [in]  context         management-object that creates and deletes associations and data-objects

 @return text-content that was read-out

 <br><br>
 @htmlinclude ./des/Prcs_Trn_Directive__reconstructSource.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    19.10.2011   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 String_imp _reconstructSource(DataAssociation* root,
                               TiPa_DataModel*  context);



/*!
 @brief try to pares a given source-part with to find out if

 @param [in]  source      root-node of the XML-tree to evaluate
 @param [in]  context     management-object that creates and deletes associations and data-objects

 @return true if the content of the analysed root-node describes
         a code-part that can be parsed
 <br>    false if the parsing fails

 <br><br>
 @htmlinclude ./des/Prcs_Trn_Directive__tryToParse.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    30.11.2011   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
bool _tryToParse(DataAssociation* root,
                 TiPa_DataModel*  context);


/*!
  re-merge sub-nodes of parser-results of directive-set variants

 @param [in] common          sub-node of the common result
 @param [in] commonNew       ?????
 @param [in] variantTable    two dimensional table of leave nodes from the result variant
 @param [in] variantTableNew ?????
 @param [in] variantName     name used in the variant-tag of the re-merge tree

 @htmlinclude ./des/Prcs_Trn_Directive__merge.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    17.12.2011   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
void _merge(XML_Node                               common,
            DataAssociation*                       commonNew,
            map<int, map<int ,XML_Node > >*        variantTable,
            map<int, map<int ,DataAssociation*> >* variantTableNew,
            String_imp                             variantName);


/*!
 create a two dimensional table of all XML-nodes sorted by lines and than by columns
 @param [in]  source      root-node of the XML-tree to evaluate
 @param [in]  rootNew     ?????
 @param [out] table       two dimensional table of leave nodes
 @param [out] tableNew    ?????


 <br><br>
 @htmlinclude ./des/Prcs_Trn_Directive__getLeaveTable.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    17.12.2011   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
void _getLeaveTable(XML_Node                               source,
                    DataAssociation*                       rootNew,
                    map<int, map<int ,XML_Node > >*        table,
                    map<int, map<int ,DataAssociation*> >* tableNew);



/*!
  add new sub-nodes of parser-results of directive-set variants which can not be re-merged

 @param [in] common           sub-node of the common result
 @param [in] commonNew        ?????
 @param [in] variantTable     two dimensional table of leave nodes from the result variant
 @param [in] variantTableNew  ?????
 @param [in] variantName      name used in the variant-tag of the re-merge tree

 @htmlinclude ./des/Prcs_Trn_Directive__add.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    18.12.2011   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
void _add(XML_Node                               common,
          DataAssociation*                       commonNew,
          map<int, map<int ,XML_Node > >*        variantTable,
          map<int, map<int ,DataAssociation*> >* variantTableNew,
          String_imp                             variantName);



/*!
 search for an XML-node in the given common XML tree that has the same tag-name and
 the same L- and C- attributes like a ansister of a variant-node in the given list
 that is the nearest ansitster also.

 @param [in] variantAnsisters       list of all ansisters of the variant-node
 @param [in] commonRoot             root-node of the common XML-tree to search in

 @return the nearest ansister of the variant-node that is also found in the
         common XML-tree, where the nearest ansitser means not a node of the
         given ansister-list but a node from the common XML-tree with the same
         tag-name and the same L- and C- attributes

 @htmlinclude ./des/Prcs_Trn_Directive__lastCommonAnsister.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    18.12.2011   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
XML_Node  _lastCommonAnsister(list<XML_Node >*       variantAnsisters,
                              XML_Node               commonRoot);

DataAssociation* _lastCommonAnsister(list<DataAssociation*>* variantAnsisters,
                                     DataAssociation*        commonRoot);




/*!
 compare the text-position of two XML-elements

 @param [in] node1       first node to compare against
 @param [in] node2       second node to compare with

 @return -1 ==> node1 in front of node2
 @return  0 ==> node1 and node1 on the same place
 @return +1 ==> node1 behind   of node1

 @htmlinclude ./des/Prcs_Trn_Directive__add.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    18.12.2011   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
int _compareNodes(DataAssociation* node1,
                  DataAssociation* node2);


int _compareNodes(XML_Node  node1,
                  XML_Node  node2);


/*!
 create line-number orientated map oo lists wich contain only those
 XML-elements which are direct parents of text-elements
 @param [in]  source      root-node of the XML-tree to evaluate
 @param [out] text        container of all direct parent-tags with only text-elements

 <br><br>
 @htmlinclude ./des/Prcs_Trn_Directive__getText.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    ... 10.2011   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
    19.10.2011   @I  Eckard Klotz
 @I need to use this function in more than one child-class
 @I move implementation from merge-process to abstract parent
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
void _getText(DataAssociation*                   source,
              map<int, list<DataAssociation*> >* textNew,
              TiPa_DataModel*                    context);






/*!
 read out the text-content of the given XML-node and its childs
 and transform it into a XML-structure that represents the document-structure
 and not the algorithm-structure.

 @param [in]  source      root-node of the XML-tree to evaluate
 @param [in]  minCol      controls the analysis of leading spaces
 <br>  if not used or a number greater as the column-number of the most left non-space character
       the method tries to cut the minimum number of leading spaces found in the whole text
 <br>  if a number less  as the column-number of the most left character is used
       the method tries to leave some leading spaces controlled by the difference of
       the column-number of the most left non-space character and the used value of minCol

 @return text-content that was read-out

 <br><br>
 @htmlinclude ./des/Prcs_Trn_Directive__getCodeFragments.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    19.10.2010   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 DataAssociation* _getCodeFragments(DataAssociation* sourceNew,
                                    TiPa_DataModel*  context,
                                    int              minCol = INT_MAX);







/*!
 @brief common object-attributes

 to put the attributes into a structure makes it possible to
 set them apart from local variables and parameters of a method
 in the source-code by using the structure-name as prefix.

 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    13.09.2011   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/


 struct Att
 {
   map<String_imp ,String_imp>  Replacement;           ///< @brief to minimize the text of user-checks

   TiPa_Concrete::DataFellow*   CodeRoot;

   TiPa_DataModel*              DataModel;

   list<_s_TextLine>            SplitedSource;         ///< @brief original text split in text-lines and directives
   map<int,bool>                CommentOut;            ///< @brief variant defined activity of text-lines and directives

   Prsd_Expression*             ExpressionCheck;       ///< @brief tool to evaluate switching expressions to decide if the
                                                       ///         switched text-part is on or off
   String_imp                   CommentBegin;          ///< @brief will be added on the begin of off-switched text-parts
   String_imp                   CommentEnd;            ///< @brief will be added on the end of off-switched text-parts

   CoreFlow*                    TestParser;            ///< @brief user defined core-sequence used to test switched text-parts

   bool                         AbleToParseDirectives; ///< @brief will be set to false if a directive-expression is not completely defined

   set<String_imp>              MergeLevel;            ///< @brief list of XML node-names that should be used while remerging
                                                       ///         parser-results of directive-set variants
   String_imp                   VariantID;             ///< @brief tag-name used to insert new tag levels inside of tags to merge,
                                                       ///         which contain the child-tags of the variants



  /// @brief default constructor
  Att(void):
   CodeRoot             (nullptr),
   DataModel            (nullptr),
   ExpressionCheck      (nullptr),
   CommentBegin         (""     ),
   CommentEnd           (""     ),
   TestParser           (nullptr),
   AbleToParseDirectives(false  ),
   VariantID            (""     )
  {};

  /*!
   @brief copy constructor
   @param [in] src object to copy
  */
  Att(const Att& src):
   Replacement          (src.Replacement          ),
   CodeRoot             (src.CodeRoot             ),
   DataModel            (src.DataModel            ),
   SplitedSource        (src.SplitedSource        ),
   CommentOut           (src.CommentOut           ),
   ExpressionCheck      (src.ExpressionCheck      ),
   CommentBegin         (src.CommentBegin         ),
   CommentEnd           (src.CommentEnd           ),
   TestParser           (src.TestParser           ),
   AbleToParseDirectives(src.AbleToParseDirectives),
   MergeLevel           (src.MergeLevel           ),
   VariantID            (src.VariantID            )
  {};
  /*!
   @brief assignment operator
   @param [in] src object to copy
   @return copied object
  */
  Att& operator = (const Att& src)
  {
   Replacement           = src.Replacement          ;
   CodeRoot              = src.CodeRoot             ;
   DataModel             = src.DataModel            ;
   SplitedSource         = src.SplitedSource        ;
   CommentOut            = src.CommentOut           ;
   ExpressionCheck       = src.ExpressionCheck      ;
   CommentBegin          = src.CommentBegin         ;
   CommentEnd            = src.CommentEnd           ;
   TestParser            = src.TestParser           ;
   AbleToParseDirectives = src.AbleToParseDirectives;
   MergeLevel            = src.MergeLevel           ;
   VariantID             = src.VariantID            ;
   return(*this);
  };
  /// @brief destructor
  ~Att(void)
  {
   Replacement  .clear();
   SplitedSource.clear();
   CommentOut   .clear();
   CommentBegin .clear();
   CommentEnd   .clear();
   MergeLevel   .clear();
   VariantID    .clear();
  };
 } Att;

};

#ifndef DOXYGEN
#define USING_NAMESPACE using namespace
//}; USING_NAMESPACE CL_TRN_DIRECTIVE;
//}; USING_NAMESPACE CL_TRANSFORM;
//}; USING_NAMESPACE CL_PROCESS;
#undef  USING_NAMESPACE
#endif //DOXYGEN







#endif //TRN_DIRECTIVE_H
