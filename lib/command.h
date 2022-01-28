#ifndef HEADER_5F0BA1F6F482A9DB
#define HEADER_5F0BA1F6F482A9DB

/*!

 @file
 @brief  definition of a collection of common snippet-commands

 This file contains common snippet-commands used to navigate through
 the xml-tree and to find the snippets to use.

 Copyright (C) 2008-2020 by Eckard Klotz.

 Permission to use, copy, modify, and distribute this software and its
 documentation under the terms of the GNU General Public License is hereby
 granted. No representations are made about the suitability of this software
 for any purpose. It is provided "as is" without express or implied warranty.
 See the GNU General Public License for more details.

 Documents produced by Moritz are derivative works derived from the
 input used in their production; they are not affected by this license.

 <b> History </b>

 @TabBegin
    date           @I author          @I implementation/change
 @I____________________________________________________________
    11.06.2011     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    11.06.2011...  @I Eckard Klotz
 @I Changes are documented in the comment of the changed element
 @TabEnd

*/
#ifndef COMMAND_H
#define COMMAND_H


#include <map>
#include <fstream>
#include <set>

using namespace std;




#include "String_imp.h"

#ifndef DOXYGEN
//namespace CL_COMMAND {
#endif //DOXYGEN







#ifndef DOXYGEN
//namespace TYPDEF_COMMAND {
#endif //DOXYGEN


/*!
 @defgroup SNIPPET_COMMAND_DEF Diverse Definitions for Snippet-Commands

 This central definitions are used on diverse locations to identify snippet-commands
 to collect all their parts like identifiers and parameters and to execute them.
 Every new snippet-command has to be inserted here.

*/





/*!
 short-identification of the command-type that make the use of a switch-construct
 possible to root to the execution of the command
 @ingroup SHORT_EXECUTION
*/
typedef enum CommandID_TP
{
 ID_RAWTEXT               =  0, ///< only one text-part completely defined by the user
 ID_SNIPET                =  1, ///< call an other snippet to process a xml sub-child
 ID_SUBSNIPET             =  2, ///< call an other snippet to process a xml sub-child
 ID_DROP                  =  3, ///< delete a xml sub-child to provide its use
 ID_REPLACE               =  4, ///< replace parts of a result-text
 ID_USEFORSNIPET          =  5, ///< use an other snippet for a xml sub-child
                                ///  but only on this sequence-level
 ID_USEFORSNIPETLOCAL     =  6, ///< use an other snippet for a xml sub-child
                                ///  but only on this sequence-level
 ID_USEFORSNIPETDOWNWARDS =  7, ///< use an other snippet for a xml sub-child
                                ///  on this sequence-level and in all snippets called from here
 ID_TEXT                  =  8, ///< analyse the text-content of a xml sub-child
 ID_COLLECTION            =  9, ///< the same as snippet
                                ///  @note the command collection is not in use anymore
 ID_DESTINATION           = 10, ///< construct the name of a destination-file
                                ///  @note the command destination will be deprecated soon
 ID_FORALL                = 11, ///< use one snippet for all xml sub-childes

 ID_STATISTIC             = 12, ///< count sub-childes with a given name and
                                ///< save the result in a given child

 ID_IFABSENT              = 13, ///< use a snippet if a xml sub-child does not exist
 ID_IFEMPTY               = 14, ///< use a snippet if no xml sub-child does exist
 ID_TAG                   = 15, ///< analyse the tag-content of the current xml-element
 ID_ATTRIBUTE             = 16, ///< analyse the an attribute-content of the current xml-element
 ID_STACKPUSH             = 17, ///< buffer the result of a snippet on the top of a stack
 ID_STACKCLEAR            = 18, ///< clear a stack
 ID_STACKREAD             = 19, ///< read the top-content of a stack
 ID_STACKREADALL          = 20, ///< read the content of a stack from bottom to top
 ID_STACKPOP              = 21, ///< read the top-content of a stack and erase it from the stack
 ID_STACKPOPALL           = 22, ///< read the content of a stack from bottom to top
                                /// and erase the stack
 ID_IFSTACKEQUAL          = 23, ///< equality-compare the top-element of a stack with
                                ///< a user-defined text to decide if the sequence should be done
 ID_IFSTACKUNEQUAL        = 24, ///< inequality-compare the top-element of a stack with
                                ///< a user-defined text to decide if the sequence should be done

 ID_IFOLDERAS             = 25, ///< check if given destination file is older as source to analyse
                                ///< to decide if the rest of the current sequence should be processed

 ID_IFNOTEXIST            = 26, ///< check if given destination file not already exists to decide
                                ///< if the rest of the current sequence should be processed

 ID_REPEAT_IFSTACKEQUAL   = 27, ///< equality-compare the top-element of a stack with
                                ///< a user-defined text to decide if the sequence should be repeated
 ID_REPEAT_IFSTACKUNEQUAL = 28, ///< inequality-compare the top-element of a stack with
                                ///< a user-defined text to decide if the sequence should be repeated
 ID_STACKPUSHSIZE         = 29, ///< save the number of stack-elements as top-element
                                ///< of an other stack

 ID_XMLCREATE             = 30, ///< call a snippet that creates a source of a new independent xml-root and store it
                                ///< under the given tag-name
 ID_XMLCOPY               = 31, ///< copy the content of the given child or sub-child to create a new
                                ///< independent xml-root and store it under the given tag-name
 ID_XMLCUT                = 32, ///< cut out the content of the given child or sub-child to create a new
                                ///< independent xml-root and store it under the given tag-name
 ID_XMLCODE               = 33, ///< transfer the content of the given child or sub-child into its
                                ///< code-structure and create a new independent xml-root to store
                                ///< it under the given tag-name
 ID_XMLINSERT             = 34, ///< insert the content of an independently generated xml-node into
                                ///< the given destination
 ID_XMLSNIPET             = 35, ///< start the evaluation of an independent xml-root or node
 ID_XMLSAVE               = 36, ///< save an independent xml-root or node
 ID_XMLDELETE             = 37, ///< delete an independent xml-root or node
 ID_XMLPRINT              = 38, ///< print out the tag-name the text-content or an attribute content of an xml-node
 ID_IFXMLEQUAL            = 39, ///< equality-compare an property of an xml-element with
                                ///< a user-defined text to decide if the sequence should be done
 ID_IFXMLUNEQUAL          = 40, ///< inequality-compare an property of an xml-element with
                                ///< a user-defined text to decide if the sequence should be done
 ID_IFXMLEXISTING         = 41, ///< equality-compare an property of an xml-element with
                                ///< a user-defined text to decide if the sequence should be done
 ID_IFXMLMISSING          = 42, ///< inequality-compare an property of an xml-element with
                                ///< a user-defined text to decide if the sequence should be done

 ID_PARSERSET             = 43, ///< configure the parser and define its rules
 ID_PARSE                 = 44  ///< use the parser to analyse the given text and create a
                                ///< xml based parser-tree as result


} CommandID_TP;




/*!
 container that holds all data of a command ready to execute it
 @ingroup SHORT_EXECUTION
*/
typedef struct _s_CommandData_TP
{
 String_imp                    Name;      ///< name of the command
 CommandID_TP                  ID;        ///< identifier for short execution
 map<String_imp , String_imp > Parameter; ///< container of parameters
} _s_CommandData_TP;

/*!
 execution-type of a sequence
  @ingroup RAW_COMMAND
*/
typedef enum SequenceType_TP
{
  SEQUENCETYPE_RAWTEXT  = 0, ///< only one text-part completely defined by the user
  SEQUENCETYPE_ONLYONCE = 1, ///< commands for snippets which should be deleted after command execution to
                             ///< provide a second use somewhere else
  SEQUENCETYPE_OPTION   = 2, ///< commands for snippets which may be re-analysed somewhere else
  SEQUENCETYPE_MACRO    = 3, ///< only a reference to a other snippet content that will be replaced before
                             ///< a further processing
  SEQUENCETYPE_FORMAT   = 4  ///< formatting the output
} SequenceType_TP;



typedef struct _s_Sequence_TP
{
 map<String_imp,_s_CommandData_TP>* FirstCheck;
 map<String_imp,_s_CommandData_TP>* PreCommand;
 map<String_imp,_s_CommandData_TP>* ChildCommand;
 map<String_imp,_s_CommandData_TP>* PostCommand;
 map<String_imp,_s_CommandData_TP>* LastCheck;
 SequenceType_TP                    Type;

 /// @brief default constructor
 _s_Sequence_TP(void):
  FirstCheck(nullptr),
  PreCommand(nullptr),
  ChildCommand(nullptr),
  PostCommand(nullptr),
  LastCheck(nullptr),
  Type(SEQUENCETYPE_RAWTEXT)
 {};
 /*!
  @brief copy constructor
  @param [in] src object to copy
 */
 _s_Sequence_TP(const _s_Sequence_TP& src):
  FirstCheck(  src.FirstCheck),
  PreCommand(  src.PreCommand),
  ChildCommand(src.ChildCommand),
  PostCommand( src.PostCommand),
  LastCheck(   src.LastCheck),
  Type(        src.Type)
 {};
 /*!
  @brief assignment operator
  @param [in] src object to copy
  @return copied object
 */
 _s_Sequence_TP& operator = (const _s_Sequence_TP& src)
 {
  FirstCheck   = src.FirstCheck;
  PreCommand   = src.PreCommand;
  ChildCommand = src.ChildCommand;
  PostCommand  = src.PostCommand;
  LastCheck    = src.LastCheck;
  Type         = src.Type;
  return(*this);
 };
 /// @brief destructor
 ~_s_Sequence_TP(void)
 {
 };


} _s_Sequence_TP;

/*!
 @defgroup SHORT_EXECUTION Command Data ready for Short-Execution
 @ingroup SNIPPET_COMMAND_DEF
 data-types to hold data ready to proceed for each command
 and their sequences
*/





/*!
 @defgroup RAW_COMMAND Raw-Command Data
 @ingroup SNIPPET_COMMAND_DEF
 data-types to hold parser-contents which are presorted for each command
 and their sequences
*/







/*!
 holds the raw-data of one command-parameter just as collection of the parser-result
 @ingroup RAW_COMMAND
*/
typedef struct _s_RawParameter_TP
{
 String_imp     Token;  ///< name of the parameter
 String_imp     Text;   ///< content of the parameter
} _s_RawParameter_TP;




/*!
 holds the raw data of a command just as collection of the parser-result
 @ingroup RAW_COMMAND
*/
typedef struct _s_RawCmnd_TP
{
 String_imp               Name;       ///<name of the command
// cppcheck-suppress unusedStructMember symbolName=_s_RawCmnd_TP::ID
 unsigned long            ID;         ///<parser-id of the command-parser
 list<_s_RawParameter_TP>  Parameter; ///<container of the parameter raw-data
} _s_RawCmnd_TP;


/*!
 holds the raw data of a command-sequence just as collection of the parser-result
 @ingroup RAW_COMMAND
*/
typedef struct _s_RawSequence_TP
{
 list<_s_RawCmnd_TP> Content; ///< raw-data of the commands
 SequenceType_TP    Type;     ///< execution-type
} _s_RawSequence_TP;


#ifndef DOXYGEN
#define USING_NAMESPACE using namespace
//};USING_NAMESPACE TYPDEF_COMMAND ;
#undef  USING_NAMESPACE
#endif //DOXYGEN


#ifndef DOXYGEN
//namespace CONST_COMMAND {
#endif //DOXYGEN


const String_imp  EMPTYSTRING = "__EMPTYSTRING__";
const String_imp  SELF        = "__SELF__";
const String_imp  LIVEOUT     = "__LIVEOUT__";




/*!
 @defgroup COMMAND_GRAMMAR Grammar of Snippet-Commands
 @ingroup SNIPPET_COMMAND_DEF
 parser-specific names and numeric identifiers
*/

/*!
 @defgroup GRAMMAR_KEY Key-Names of Snippet-Grammar
 @ingroup  COMMAND_GRAMMAR
 this names are used in the snippet-grammar for key-content
 to use while interpretation.

 @{

*/

const String_imp  PASS                  ="pass";
const String_imp  SKIP                  ="skip";
const String_imp  FAIL                  ="fail";
const String_imp  NAME                  ="name";
const String_imp  SNIPET_STRING         ="string";
const String_imp  SNIPET_PARAMETER      ="parameter";

const String_imp  LINEPART              ="linePart";
const String_imp  RAW_SEQUENCE          ="raw_sequence";
const String_imp  USEALSOFOR            ="useAlsoFor";
const String_imp  SNIPET_NAME           ="snipet_name";
const String_imp  RAW_TEXT              ="raw_text";

const String_imp  OPTION                ="option";
const String_imp  ONLYONCE              ="onlyOnce";
const String_imp  MACRO                 ="macro";
const String_imp  SEQUENCE              ="sequence";
const String_imp  PARAMETER             ="parameter";
const String_imp  TAGNMAE               ="tagName";
const String_imp  TAGPATH               ="tagPath";
const String_imp  PATHSEP               ="pathSep";

const String_imp  RAWTEXT               ="RawText";
const String_imp  SNIPET                ="snipet";
const String_imp  DROP                  ="drop";
const String_imp  REPLACE               ="replace";
const String_imp  USEFORSNIPET          ="useForSnipet";
const String_imp  USEFORSNIPETLOCAL     ="useForSnipetLocal";
const String_imp  USEFORSNIPETDOWNWARDS ="useForSnipetDownwards";
const String_imp  TEXT                  ="text";
const String_imp  COLLECTION            ="collection";
const String_imp  DESTINATION           ="destination";
const String_imp  FORALL                ="forAll";
const String_imp  STATISTIC             ="statistic";

const String_imp  IFOLDERAS             ="ifOlderAs";
const String_imp  IFNOTEXIST            ="ifNotExist";

const String_imp  IFABSENT              ="ifAbsent";
const String_imp  IFEMPTY               ="ifEmpty";
const String_imp  TAG                   ="tag";
const String_imp  ATTRIBUTE             ="attribute";
const String_imp  STACKPUSH             ="stackPush";
const String_imp  STACKCLEAR            ="stackClear";
const String_imp  STACKREAD             ="stackRead";
const String_imp  STACKREADALL          ="stackReadAll";
const String_imp  STACKPOP              ="stackPop";
const String_imp  STACKPOPALL           ="stackPopAll";
const String_imp  IFSTACKEQUAL          ="ifStackEqual";
const String_imp  IFSTACKUNEQUAL        ="ifStackUnequal";
const String_imp  REPEAT_IFSTACKEQUAL   ="repeat_ifStackEqual";
const String_imp  REPEAT_IFSTACKUNEQUAL ="repeat_ifStackUnequal";
const String_imp  STACKPUSHSIZE         ="stackPushSize";

const String_imp  XMLCREATE             ="xmlCreate";
const String_imp  XMLCOPY               ="xmlCopy";
const String_imp  XMLCUT                ="xmlCut";
const String_imp  XMLCODE               ="xmlCode";
const String_imp  XMLINSERT             ="xmlInsert";
const String_imp  XMLSNIPET             ="xmlSnipet";
const String_imp  XMLSAVE               ="xmlSave";
const String_imp  XMLDELETE             ="xmlDelete";
const String_imp  XMLPRINT              ="xmlPrint";
const String_imp  IFXMLEQUAL            ="ifXmlEqual";
const String_imp  IFXMLUNEQUAL          ="ifXmlUnequal";
const String_imp  IFXMLEXISTING         ="ifXmlExisting";
const String_imp  IFXMLMISSING          ="ifXmlMissing";

const String_imp  PARSERSET             ="parserSet";
const String_imp  PARSE                 ="parse";

const String_imp  FORMAT                ="format";
const String_imp  NEWLINE               ="newLine";
const String_imp  INDEND                ="indend";
const String_imp  DEDEND                ="dedend";
const String_imp  SPACE                 ="space";
const String_imp  TAB                   ="tab";
const String_imp  ASCII                 ="ascii";
const String_imp  NUMBER                ="number";

const String_imp  OLDPART               ="oldPart";
const String_imp  NEWPART               ="newPart";

/*!
 @}
*/

#ifndef DOXYGEN
#define USING_NAMESPACE using namespace
//}; USING_NAMESPACE CONST_COMMAND ;
#undef  USING_NAMESPACE
#endif //DOXYGEN


/*!
 @ingroup  COMMAND_GRAMMAR
 this names are used in the snipet-grammar to define substitution-parsers
 to split long parser-rules into smaler pices and are not used as result,
 their parser-identifiers are used for as quick-reference
#define CREATE_SKIP_ID_SET_mk(set,grammar)                  \
  set.insert(grammar[NAME                 ].id().to_long());\
  set.insert(grammar[SNIPET_STRING        ].id().to_long());\
  set.insert(grammar[SNIPET_PARAMETER     ].id().to_long());

*/
#define CREATE_SKIP_ID_SET_mk(set) \
  set.insert(NAME            );    \
  set.insert(SNIPET_STRING   );    \
  set.insert(SNIPET_PARAMETER);



/*!
 @ingroup  COMMAND_GRAMMAR
 this names are used in the snipet-grammar to define core-parsers
 are used as result,
 their parser-identifiers are used for as quick-reference

#define CREATE_COMMAND_ID_SET_mk(set,grammar)               \
  set.insert(grammar[SNIPET               ].id().to_long());\
  set.insert(grammar[DROP                 ].id().to_long());\
  set.insert(grammar[REPLACE              ].id().to_long());\
  set.insert(grammar[USEFORSNIPET         ].id().to_long());\
  set.insert(grammar[USEFORSNIPETLOCAL    ].id().to_long());\
  set.insert(grammar[USEFORSNIPETDOWNWARDS].id().to_long());\
  set.insert(grammar[TEXT                 ].id().to_long());\
  set.insert(grammar[COLLECTION           ].id().to_long());\
  set.insert(grammar[DESTINATION          ].id().to_long());\
  set.insert(grammar[FORALL               ].id().to_long());\
  set.insert(grammar[STATISTIC            ].id().to_long());\
  set.insert(grammar[IFABSENT             ].id().to_long());\
  set.insert(grammar[IFEMPTY              ].id().to_long());\
  set.insert(grammar[TAG                  ].id().to_long());\
  set.insert(grammar[ATTRIBUTE            ].id().to_long());\
  set.insert(grammar[STACKPUSH            ].id().to_long());\
  set.insert(grammar[STACKCLEAR           ].id().to_long());\
  set.insert(grammar[STACKREAD            ].id().to_long());\
  set.insert(grammar[STACKREADALL         ].id().to_long());\
  set.insert(grammar[STACKPOP             ].id().to_long());\
  set.insert(grammar[STACKPOPALL          ].id().to_long());\
  set.insert(grammar[IFSTACKEQUAL         ].id().to_long());\
  set.insert(grammar[IFSTACKUNEQUAL       ].id().to_long());\
  set.insert(grammar[IFOLDERAS            ].id().to_long());\
  set.insert(grammar[IFNOTEXIST           ].id().to_long());\
  set.insert(grammar[REPEAT_IFSTACKEQUAL  ].id().to_long());\
  set.insert(grammar[REPEAT_IFSTACKUNEQUAL].id().to_long());\
  set.insert(grammar[STACKPUSHSIZE        ].id().to_long());\
  set.insert(grammar[XMLCREATE            ].id().to_long());\
  set.insert(grammar[XMLCOPY              ].id().to_long());\
  set.insert(grammar[XMLCUT               ].id().to_long());\
  set.insert(grammar[XMLCODE              ].id().to_long());\
  set.insert(grammar[XMLINSERT            ].id().to_long());\
  set.insert(grammar[XMLSNIPET            ].id().to_long());\
  set.insert(grammar[XMLSAVE              ].id().to_long());\
  set.insert(grammar[XMLDELETE            ].id().to_long());\
  set.insert(grammar[XMLPRINT             ].id().to_long());\
  set.insert(grammar[IFXMLEQUAL           ].id().to_long());\
  set.insert(grammar[IFXMLUNEQUAL         ].id().to_long());\
  set.insert(grammar[IFXMLEXISTING        ].id().to_long());\
  set.insert(grammar[IFXMLMISSING         ].id().to_long());\
  set.insert(grammar[PARSERSET            ].id().to_long());\
  set.insert(grammar[PARSE                ].id().to_long());

*/
#define CREATE_COMMAND_ID_SET_mk(set)  \
  set.insert(SNIPET               );   \
  set.insert(DROP                 );   \
  set.insert(REPLACE              );   \
  set.insert(USEFORSNIPET         );   \
  set.insert(USEFORSNIPETLOCAL    );   \
  set.insert(USEFORSNIPETDOWNWARDS);   \
  set.insert(TEXT                 );   \
  set.insert(COLLECTION           );   \
  set.insert(DESTINATION          );   \
  set.insert(FORALL               );   \
  set.insert(STATISTIC            );   \
  set.insert(IFABSENT             );   \
  set.insert(IFEMPTY              );   \
  set.insert(TAG                  );   \
  set.insert(ATTRIBUTE            );   \
  set.insert(STACKPUSH            );   \
  set.insert(STACKCLEAR           );   \
  set.insert(STACKREAD            );   \
  set.insert(STACKREADALL         );   \
  set.insert(STACKPOP             );   \
  set.insert(STACKPOPALL          );   \
  set.insert(IFSTACKEQUAL         );   \
  set.insert(IFSTACKUNEQUAL       );   \
  set.insert(IFOLDERAS            );   \
  set.insert(IFNOTEXIST           );   \
  set.insert(REPEAT_IFSTACKEQUAL  );   \
  set.insert(REPEAT_IFSTACKUNEQUAL);   \
  set.insert(STACKPUSHSIZE        );   \
  set.insert(XMLCREATE            );   \
  set.insert(XMLCOPY              );   \
  set.insert(XMLCUT               );   \
  set.insert(XMLCODE              );   \
  set.insert(XMLINSERT            );   \
  set.insert(XMLSNIPET            );   \
  set.insert(XMLSAVE              );   \
  set.insert(XMLDELETE            );   \
  set.insert(XMLPRINT             );   \
  set.insert(IFXMLEQUAL           );   \
  set.insert(IFXMLUNEQUAL         );   \
  set.insert(IFXMLEXISTING        );   \
  set.insert(IFXMLMISSING         );   \
  set.insert(PARSERSET            );   \
  set.insert(PARSE                );


/*!
 @ingroup  COMMAND_GRAMMAR
 this names are used in the snipet-grammar to define format-symbols,
 their parser-identifiers are used for as quick-reference

#define CREATE_FORMAT_ID_SET_mk(set,grammar)                \
  set.insert(grammar[NEWLINE              ].id().to_long());\
  set.insert(grammar[INDEND               ].id().to_long());\
  set.insert(grammar[DEDEND               ].id().to_long());\
  set.insert(grammar[SPACE                ].id().to_long());\
  set.insert(grammar[TAB                  ].id().to_long());\
  set.insert(grammar[ASCII                ].id().to_long());
*/

#define CREATE_FORMAT_ID_SET_mk(set)                \
  set.insert(NEWLINE);\
  set.insert(INDEND );\
  set.insert(DEDEND );\
  set.insert(SPACE  );\
  set.insert(TAB    );\
  set.insert(ASCII  );




/*!
 @brief collection of comon commands to construct snipet-content

 @history
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    11.06.2011   @I  Eckard Klotz @I First Implementation @I
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/

class Cmnd_Common
{
 public:



/*!
 construktor
 <br><br>
 @htmlinclude Cmnd_Common_Cmnd_Common.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    05.06.2011   @I  Eckard Klotz
 @I refactoring of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  Cmnd_Common(void);




/*!
 destruktor
 <br><br>
 @htmlinclude "Cmnd_Common__Cmnd_Common.html"
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    06.05.2011   @I  Eckard Klotz
 @I refactoring of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  ~Cmnd_Common(void);



/*!
 creates a for every command a parameter-command and adds it
 to the sequence-container. multi-commands for example for
 more than one snippet are split into single commands

 @param [out] command     container command raw-data
 @param [out] sequence    container of the sequence-procedures


 <br><br>
 @htmlinclude Cmnd_Common_assignSequence.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    26.06.2011   @I  Eckard Klotz
 @I re-factoring of base-design
 @I first implementation
 @I_______________________________________________________
    16.08.2012   @I  Eckard Klotz
 @I using of independent xml-trees
 @I enabling the assigning of the associated commands
 @I_______________________________________________________
    16.06.2013   @I  Eckard Klotz
 @I new feature
 @I prepare use of xmlCode method
 @I_______________________________________________________
    23.06.2013   @I  Eckard Klotz
 @I new feature
 @I prepare use of statistic method
 @I_______________________________________________________
    28.07.2013   @I  Eckard Klotz
 @I started to develop a xml-based log-output instead of
    a textual debug-output
 @I format-tokens will be coded not as FORMAT but as
    NEWLINE, INDEND, DEDEND, ...
 @I_______________________________________________________
    08.08.2013   @I  Eckard Klotz
 @I started to develop a parser-command
 @I new procedures paserset and parse added
 @I_______________________________________________________
    15.09.2014   @I  Eckard Klotz
 @I re factoring to implement the generation of modified sources
 @I new procedures xml-insert added
 @I_______________________________________________________
    16.09.2014   @I  Eckard Klotz
 @I bug xml-sub node could not be saved since separator was
    not saved
 @I tag-path and separator will be saved as different objects
    as expected from xml-save
 @I_______________________________________________________
    22.09.2014   @I  Eckard Klotz
 @I extending of base-design
 @I added equal and unequal tests for xml-content
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
void assignSequence(list<_s_RawCmnd_TP>::iterator      command,
                    map<String_imp,_s_CommandData_TP>* sequence);






/*!
 fills the given container with information needed to replace special parts
 of tags, attributes or texts-parts for tailoring-actions

 @param [in]  oldPart part string to replace
 @param [in]  newPart new  string to insert inserted
 @param [in]  replaceReset decision of the user to define an independent
                           replacement for the current sequence and the
                           snippets called by it
 @param [out] replacement  contains replacement-information to tailor
                           tags, attributes, texts and so on


 <br><br>
 @htmlinclude Cmnd_Common_replacmentSet.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    14.02.2010   @I  Eckard Klotz
 @I re-factoring of base-design
 @I first implementation
 @I_______________________________________________________
    21.08.2012   @I  Eckard Klotz
 @I expanding of design
 @I old-part and/or new-part of replacement may be the name
    of a stack now in this case the top-value of this stack
    will be used as old/new-value
 @I_______________________________________________________
    22.08.2012   @I  Eckard Klotz
 @I expanding of design
 @I user is able to reset the inherited replacements
    to use an independent replacement for the current
    sequence and the snipptes called by it
 @I_______________________________________________________
    02.06.2013   @I  Eckard Klotz
 @I bug quote-character will not be used as replacement pattern
 @I over all replacement of quote-character was changed to a
    replacement only on beginning and end of oldPart and newPart
    user has to define 3 quotes for using a single quote alone
    as pattern since leading and ending quote will be still deleted
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void replacmentSet(      String_imp             oldPart,
                          String_imp             newPart,
                    const String_imp&            replaceReset,
                    map<String_imp, String_imp>* replacement);




/*!
 change a given text by using a the given container of replacements

 @param [in]  oldString text o change by using the predefined replacements
 @param [in]  replacement  contains replacement-information to tailor
                           tags, attributes, texts and so on
 @return      changed text

 <br><br>
 @htmlinclude Cmnd_Common_replacmentUse.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    24.07.2011   @I  Eckard Klotz
 @I refactoring of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 String_imp replacmentUse(const String_imp&            oldString,
                          map<String_imp, String_imp>* replacement);






 protected:



 private:




};


#ifndef DOXYGEN
#define USING_NAMESPACE using namespace
//}; USING_NAMESPACE CL_COMMAND;
#undef  USING_NAMESPACE
#endif //DOXYGEN



#endif //COMMAND_H
#endif // header guard

