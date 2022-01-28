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
    20.06.2015     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    20.06.2015...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/
#ifndef SPIRIT185_EXTERNAL_H
 #define SPIRIT185_EXTERNAL_H



//#include <list>
#include <vector>
#include <string>
#include <sstream>
#include "TDA_GrmConcrete.h"
#include "Debug_Reaction.h"



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
class Spirit185_External:public TDA_GrmConcrete
{

 public:


  ///global user-rules-properties
  typedef  struct GlobalUserProperty_TP
   {
    set<string> Token;
    set<string> NotPhrased;
    set<string> Hide;
    set<string> SkipLevel;
   }GlobalUserProperty_TP;



/*
  typedef enum SpecialParser
  {
   Rule_Default = Identifier_id, ///< parser defined by a rule
  }SpecialParser;
*/
/*
/// describes one of several details of behaviour
  typedef enum ParserDirective
  {
   PrDr_Default,              ///< not specified behaviour
   PrDr_First,                ///< or decisions take the first match
   PrDr_Last,                 ///< or decisions take the last match
   PrDr_Shortest,             ///< or decisions take the shortest match
   PrDr_Longest,              ///< or decisions take the longest match
//   PrDr_,
//   PrDr_,
  }ParserDirective;
*/

 /*!
 @brief default constructor

 @param [in] contextModel management-object that creates and deletes associations and data-objects
 @param [in] debugMode    forces the grammar to store debug-data if set to true
 <br><br>
 @htmlinclude ./des/Spirit185_External_Spirit185_External.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    20.06.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
explicit Spirit185_External(TiPa_Concrete::DataModel* contextModel, bool debugMode = false);










 /*!
 constructor

 @param association           grammar-tree created by Spirit185_Internal
 @param rootRule              name of the rule to start parsing with
 @param skipRule              name of the rule that defines content to ignore in phrased rules
 @param lineRule              name of the rule that defines the change between two lines
 @param listOfNonPhrased      comma separated list of rules which are not phrased
 @param grammarTextIdentifier name of the text-file that contains the syntax definition
 @param debugMode             forces the grammar to store debug-data if set to true

 <br><br>
 @htmlinclude ./des/Spirit185_External_Spirit185_External.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    20.06.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  Spirit185_External(TiPa_Concrete::DataAssociation* association,
                     const char*                     rootRule,
                     const char*                     skipRule,
                     const char*                     lineRule,
                     const char*                     listOfNonPhrased,
                     const char*                     GrammarTextIdentifier,
                     TiPa_Concrete::DataModel*       contextModel,
                     bool                            debugMode = false);






 /*!
 destructor
 <br><br>
 @htmlinclude ./des/Spirit185_External__Spirit185_External.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    20.06.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 ~Spirit185_External(void);


 /*!
 initialize an object of Spirit185_External

 @param association           [in]  grammar-tree created by Spirit185_Internal
 @param rootRule              [in]  name of the rule to start parsing with
 @param skipRule              [in]  name of the rule that defines content to ignore in phrased rules
 @param lineRule              [in]  name of the rule that defines the change between two lines
 @param listOfNonPhrased      [in]  comma separated list of rules which are not phrased
 @param grammarTextIdentifier [in]  name of the text-file that contains the syntax definition
 @param debugMode             [in]  forces the grammar to store debug-data if set to true
 @param limitCallingTree      [in]  maximum number of calling-levels to analyse
 @param limitCallingNode      [in]  maximum number of calling rules  to analyse
 @param limitCallerTree       [in]  maximum number of caller-levels  to analyse
 @param limitCallerNode       [in]  maximum number of caller rules   to analyse

 <br><br>
 @htmlinclude ./des/Spirit185_External_init.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    02.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
void init(TiPa_Concrete::DataAssociation* association,
          const char*                     rootRule,
          const char*                     skipRule,
          const char*                     lineRule,
          const char*                     listOfNonPhrased,
          const char*                     grammarTextIdentifier,
          bool                            debugMode,
          int                             limitCallingTree = 5,
          int                             limitCallingNode = 30,
          int                             limitCallerTree  = 5,
          int                             limitCallerNode  = 30
         );







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

 @htmlinclude ./des/TDA_GrmConcrete_parse.html

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
 virtual const char * parse(const char* begin, const char* end, const char* rule = nullptr) override;
















/*!
  @brief set the path of the log-file that should contain the user-grammar as analysed

  @param folder string that defines the hard-disc location
*/
void setLogFile(const char* folder);




 protected:

 private:


/*!
 defines the root of the parser-tree as the assignment

 @param [in] association grammar-tree created by PrimGrm_Spirit185
 @param [in] notPhrased  type of parser to build
        <br>             true  ==> parser ignores  white-space-characters
        <br>             false ==> parser analyses white-space-characters also
 @param id               user-id of the parser to create

 <br>

 @htmlinclude ./des/Spirit185_External_create_Rule.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    20.06.2015   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
    16.06.2016   @I  Eckard Klotz
 @I enabling debug-outputs
 @I use of method logRawResult
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  void   create_Rule(TiPa_Concrete::DataAssociation* association,
                     set<string>*                    notPhrased,
                     int                             id);


// @param [in] phrased     type of parser to build
//        <br>             true  ==> parser ignores  white-space-characters
//        <br>             false ==> parser analyses white-space-characters also


/*!
 @brief return a rule if defined or prepare a new rule for a later definition
 and return this

 Preparing a new rule means to create a rule-parser with out define its sub-parsers.
 This means the return-value fulfils the formal criteria to be used as sub-parser by
 an other rule but it contains no real functionality. The complete definition of the
 returned rule has to be done by calling @ref create_Rule where an association node
 with its definition-details. This definition is an independent process.


 @param [in] association grammar-tree created by PrimGrm_Spirit185

 <br>

 @return a already defined rule or a new prepared but not defined one

 @htmlinclude ./des/Spirit185_External_get_Rule.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    11.10.2015   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
TiPa_Rule* get_Rule(TiPa_Concrete::DataAssociation* association/*,
                    bool                phrased*/);









 /*!
 create a new parser that searches for spirit primitives or reuse an already existing one

 @param [in] association grammar-tree created by PrimGrm_Spirit185
 @param [in] phrased     type of parser to build
        <br>             true  ==> parser ignores  white-space-characters
        <br>             false ==> parser analyses white-space-characters also

 <br><br>
 @htmlinclude ./des/Spirit185_External_create_ParserPrimitive.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    12.10.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  TiPa_Concrete* create_ParserPrimitive(TiPa_Concrete::DataAssociation* association,
                                        bool                phrased);








 /*!
 create a new character-parser or reuse an already existing one

 @param [in] association grammar-tree created by PrimGrm_Spirit185
 @param [in] phrased     type of parser to build
        <br>             true  ==> parser ignores  white-space-characters
        <br>             false ==> parser analyses white-space-characters also

 <br><br>
 @htmlinclude ./des/Spirit185_External_create_ParserCharacter.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    21.06.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  TiPa_Character*   create_ParserCharacter(TiPa_Concrete::DataAssociation* association,
                                           bool                phrased);



 /*!
 convert a character description into the pure character
 @note supports no Unicode

 @param [in] symbol a string that contains just one character
                    or an escape-sequence that symbolizes a single character

 @return a single character that my contain the ordinal value 255 in
         the case of a Unicode character

 <br><br>
 @htmlinclude ./des/Spirit185_External_getPureCharacter.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    12.10.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 char getPureCharacter(const char* symbol);



 /*!
 create a new string-parser or reuse an already existing one

 @param [in] association grammar-tree created by PrimGrm_Spirit185
 @param [in] phrased     type of parser to build
        <br>             true  ==> parser ignores  white-space-characters
        <br>             false ==> parser analyses white-space-characters also

 <br><br>
 @htmlinclude ./des/Spirit185_External_create_ParserString.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    21.06.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  TiPa_String*      create_ParserString(TiPa_Concrete::DataAssociation* association,
                                        bool                phrased);



 /*!
 convert a string description into the pure string

 @param [in]  symbol      a string that may contain escape-sequences
                          which are symbolizing single characters
 @param [out] destination container of output

 @return a string of pure characters

 <br><br>
 @htmlinclude ./des/Spirit185_External_getPureString.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    12.10.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void getPureString(const char* symbol, char** destination);






 /*!
 create a new counter-parser or reuse an already existing one

 @param [in] association grammar-tree created by PrimGrm_Spirit185
 @param [in] phrased     type of parser to build
        <br>             true  ==> parser ignores  white-space-characters
        <br>             false ==> parser analyses white-space-characters also

 <br><br>
 @htmlinclude ./des/Spirit185_External_create_ParserCounter.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    21.06.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
    16.06.2016   @I  Eckard Klotz
 @I enabling debug-outputs
 @I use of method logRawResult
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  TiPa_Counter*     create_ParserCounter(TiPa_Concrete::DataAssociation* association,
                                         bool                            phrased);




 /*!
 create a new sequence-parser or reuse an already existing one

 @param [in] association grammar-tree created by PrimGrm_Spirit185
 @param [in] phrased     type of parser to build
        <br>             true  ==> parser ignores  white-space-characters
        <br>             false ==> parser analyses white-space-characters also

 <br><br>
 @htmlinclude ./des/Spirit185_External_create_ParserSequence.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    22.10.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
    16.06.2016   @I  Eckard Klotz
 @I enabling debug-outputs
 @I use of method logRawResult
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  TiPa_Sequence* create_ParserSequence(TiPa_Concrete::DataAssociation* association,
                                       bool                phrased);





 /*!
 create a new condition-parser or reuse an already existing one

 @param [in] association grammar-tree created by PrimGrm_Spirit185
 @param [in] phrased     type of parser to build
        <br>             true  ==> parser ignores  white-space-characters
        <br>             false ==> parser analyses white-space-characters also

 <br><br>
 @htmlinclude ./des/Spirit185_External_create_ParserCondition.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    22.10.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
    16.06.2016   @I  Eckard Klotz
 @I enabling debug-outputs
 @I use of method logRawResult
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  TiPa_Condition* create_ParserCondition(TiPa_Concrete::DataAssociation* association,
                                         bool                            phrased);


 /*!
 centralized call of man creation methods to keep other methods smaller

 @param [in] kind         user given identifier that describes the parser-element
                          to create
 @param [in] association  grammar-tree created by PrimGrm_Spirit185
 @param [in] phrased      type of parser to build
        <br>              true  ==> parser ignores  white-space-characters
        <br>              false ==> parser analyses white-space-characters also

 @return parser to create

 <br><br>
 @htmlinclude ./des/Spirit185_External_call_ParserCreation.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    10.10.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
TiPa_Concrete* call_ParserCreation(int                             kind,
                                   TiPa_Concrete::DataAssociation* association,
                                   bool                            phrased);



/*!
 @brief analyse a association tree and collect the node-data that describes
 details of the rule to create.

 The given data association created by a parsing process contains usually
 data-nodes which represent the notation syntax but contain no details
 about the new syntax rules to create. But their contractor-nodes or
 sub-contractors (sub-sub-con..., ...) do.


 @param [in]  source      root association of association tree to analyse
 @param [out] destination root association of association tree to create,
                          normally not for external use but for internal recursive calls

 @return a new association-tree that contains in its first contractor-level
         associations to the key data that describes the details of the rule
         to create

 <br><br>
 @htmlinclude ./des/Spirit185_External_collectKeyData.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    09.10.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
TiPa_Concrete::DataAssociation* collectKeyData(TiPa_Concrete::DataAssociation* source,
                                               TiPa_Concrete::DataAssociation* destination = nullptr);








/*!
 @brief defines the root-rule

 @param [in] ruleName name of an already defined rule that should
                      be used as root-rule
 @param      ruleID   user-id of the parser to create, will be incremented
                      with every created parser

 @return  the already defined rule if exist
          or a per default created one if it is not already defined

 <br><br>
 @htmlinclude ./des/Spirit185_External_defineRootRule.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    19.12.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
TiPa_Rule* defineRootRule(const char* ruleName, unsigned int& ruleID);



/*!
 @brief defines the skip-rule

 @param [in] ruleName name of an already defined rule that should
                      be used as skip-rule
 @param      ruleID   user-id of the parser to create, will be incremented
                      with every created parser

 @return  the already defined rule if exist
          or a per default created one if it is not already defined

 <br><br>
 @htmlinclude ./des/Spirit185_External_defineSkipRule.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    19.12.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
TiPa_Rule* defineSkipRule(const char* ruleName, unsigned int& ruleID);



/*!
 @brief defines the line-rule

 @param [in] ruleName name of an already defined rule that should
                      be used to define line changes
 @param      ruleID   user-id of the parser to create, will be incremented
                      with every created parser

 @return  the already defined rule if exist
          or a per default created one if it is not already defined

 <br><br>
 @htmlinclude ./des/Spirit185_External_defineLineRule.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    19.12.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
TiPa_Rule* defineLineRule(const char* ruleName, unsigned int& ruleID);



// @param [in] skip     already defined rule that describes for phrased rules
//                      content to ignore


/*!
 @brief defines the reserved-rule

 @param      ruleID   user-id of the parser to create, will be incremented
                      with every created parser

 @return  a per default created rule that is using all string-parsers
          defined by other rules followed by the given skip-parser
          to defined reserved words

 <br><br>
 @htmlinclude ./des/Spirit185_External_defineReservedRule.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    19.12.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
TiPa_Rule* defineReservedRule(unsigned int& ruleID);




 /*!
 @brief store part-result as notation specific raw-text in a greater log-text

 @param [in] text    part-text to be added to raw-log output

 @param [in] indent  indention of given text in the entire raw-log output

 @param [in] newLine  true : insert end-of-line behind given text
  <br>                false: keep the current line

 <br><br>
 @htmlinclude ./des/Spirit185_External_logRawResult.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    16.06.2016   @I  Eckard Klotz
 @I adding debug-outputs
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
void logRawResult(const char* text, int indent=0, bool newLine = false);

/*! parameter value for parameter text of @ref Spirit185_External::logRawResult*/
#define EMPTYLOG nullptr
/*! parameter value for parameter newLine of @ref Spirit185_External::logRawResult*/
#define NEWLOGLINE true


enum
{
 LocalParserID_Min = 10000,
};



 /*!
  @brief diverse Attributes of class
 */
  struct Mbr
  {
   const char*         GrammarTextIdentifier{nullptr};
   unsigned int        LocalParserID{LocalParserID_Min};
   Debug_Reaction      DebugReaction{};

   Mbr(void):GrammarTextIdentifier(nullptr),
             LocalParserID(LocalParserID_Min),
             DebugReaction(){};                           ///< @brief default initialization
   Mbr(const Spirit185_External::Mbr& mbr):GrammarTextIdentifier(mbr.GrammarTextIdentifier),
                                           LocalParserID(mbr.LocalParserID),
                                           DebugReaction(mbr.DebugReaction){};
                                                          ///< @brief copy initialization
   Spirit185_External::Mbr& operator= (const Spirit185_External::Mbr& mbr)
                            {
                             GrammarTextIdentifier = mbr.GrammarTextIdentifier;
                             LocalParserID         = mbr.LocalParserID;
                             DebugReaction         = mbr.DebugReaction;
                             return(*this);
                            }                             ///< @brief assignment
  }Mbr;



/*!
 @brief data used while raw log output of the user-grammar
*/
  struct Log
  {
   int                 Indent{0};              ///< @brief  currently used indention
                                               ///< (spaces between line-begin and first character of the line)
   list<int>           IndentOffset{};         ///< @brief  positive change of the indention
   stringstream        Text{};                 ///< @brief  log-text
   char*               File{nullptr};          ///< @brief file to store the log-text


   char*               Path{nullptr};          ///< @brief folder path
   char*               Name{nullptr};          ///< @brief file name
   char*               Attachment{nullptr};    ///< @brief file attachment
   char*               Path_end{nullptr};      ///< @brief position of last splitter before file_name
   char*               Name_end{nullptr};      ///< @brief position of splitting dot before file-attachment

   Log(void):Indent(0),
             IndentOffset(),
             Text(),
             File(nullptr),
             Path(nullptr),
             Name(nullptr),
             Attachment(nullptr),
             Path_end(nullptr),
             Name_end(nullptr){};              ///< @brief default initialization
   Log(const Spirit185_External::Log& log):Indent(log.Indent),
                                           IndentOffset(log.IndentOffset),
                                           Text(),
                                           File(log.File),
                                           Path(log.Path),
                                           Name(log.Name),
                                           Attachment(log.Attachment),
                                           Path_end(log.Path_end),
                                           Name_end(log.Name_end){};
                                               ///< @brief copy initialization
   Spirit185_External::Log& operator= (const Spirit185_External::Log& log)
                            {
                             Indent = log.Indent;
                             IndentOffset = log.IndentOffset;
                             //Text;
                             File = log.File;
                             Path = log.Path;
                             Name = log.Name;
                             Attachment = log.Attachment;
                             Path_end = log.Path_end;
                             Name_end = log.Name_end;
                             return(*this);
                            }
                                               ///< @brief assignment





  }Log;




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




#endif //SPIRIT185_EXTERNAL_H
