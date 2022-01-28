#ifndef HEADER_6499B5386BB405D
#define HEADER_6499B5386BB405D

/*!

 @file
 @brief  definition of a user-defined Snippet

 This file contains the representation of the Snippet content defined by the user
 in a pre-parsed version where the passive source-macros and the active commands
 are already separated and prepared.

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
    12.06.2011     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    12.06.2011...  @I Eckard Klotz
 @I Changes are documented in the comment of the changed element
 @TabEnd

*/
#ifndef SNIPPET_H
#define SNIPPET_H

#include <iostream>
#include <list>
#include <map>

#include "xml_DataModel.h"


using namespace std;

#include "String_imp.h"
#include "transform.h"
#include "command.h"

#ifndef DOXYGEN
//namespace CL_SNIPPET {
#endif //DOXYGEN





/*!
 @defgroup SNIPPET_SEQUENCE_DEF Definitions for Procedures-Groups in a Snippet-Sequence

 This central definitions are used on diverse locations to identify procedure-groups
 to collect all their identifiers.
 Every new snippet-procedures has to be inserted herer.

*/


/*!
 @ingroup  SNIPPET_SEQUENCE_DEF
 this procedures are used at the beginning of a sequence
 to decide of the sequence should be done or not

 their parser-identifiers are used for as quick-reference
*/
#define CREATE_FIRSTCHECK_SET_mk(set)               \
  set.insert(IFSTACKEQUAL  );\
  set.insert(IFSTACKUNEQUAL);\
  set.insert(IFXMLEQUAL    );\
  set.insert(IFXMLUNEQUAL  );\
  set.insert(IFXMLEXISTING );\
  set.insert(IFXMLMISSING  );\
  set.insert(IFOLDERAS     );\
  set.insert(IFNOTEXIST    );




/*!
 @ingroup  SNIPPET_SEQUENCE_DEF
 this procedures are used at the beginning of a sequence
 to prepare the seuence of tag-associated procedures

 their parser-identifiers are used for as quick-reference
*/
#define CREATE_PRECOMMAND_SET_mk(set)               \
  set.insert(REPLACE);\
  set.insert(USEFORSNIPETDOWNWARDS);\
  set.insert(XMLCOPY);\
  set.insert(XMLCUT);\
  set.insert(XMLCODE);\
  set.insert(PARSERSET);\
  set.insert(STATISTIC);

/*!
 @ingroup  SNIPPET_SEQUENCE_DEF
 this is not a procedures but it contains a constnt text-part

 its parser-identifiers are used for as quick-reference
*/
#define CREATE_RAWTEXT_SET_mk(set)               \
  set.insert(RAWTEXT);





/*!
 @ingroup  SNIPPET_SEQUENCE_DEF
 this procedures are used as child-tag associated procedures

 their parser-identifiers are used for as quick-reference
*/
#define CREATE_CHILDCOMMAND_SET_mk(set)               \
  set.insert(DROP);\
  set.insert(SNIPET);\
  set.insert(COLLECTION);\
  set.insert(TEXT);\
  set.insert(DESTINATION);\
  set.insert(STACKPUSH);\
  set.insert(USEFORSNIPET);\
  set.insert(USEFORSNIPETLOCAL);\
  set.insert(XMLCREATE);\
  set.insert(XMLINSERT);


/*!
 @ingroup  SNIPPET_SEQUENCE_DEF
 this procedures are used at the end of a sequence
 to start a snippet in the case if no child-tag exists

 their parser-identifiers are used for as quick-reference
*/
#define CREATE_IFEMPTY_SET_mk(set)               \
  set.insert(IFEMPTY);


/*!
 @ingroup  SNIPPET_SEQUENCE_DEF
 this procedures are used at the end of a sequence
 to finish the seuence of child-tag associated procedures

 their parser-identifiers are used for as quick-reference
*/
#define CREATE_POSTCOMMAND_SET_mk(set)               \
  set.insert(FORALL);\
  set.insert(IFABSENT);\
  set.insert(TAG);\
  set.insert(ATTRIBUTE);\
  set.insert(STACKPUSHSIZE);\
  set.insert(STACKREAD);\
  set.insert(STACKREADALL);\
  set.insert(STACKPOP);\
  set.insert(STACKPOPALL);\
  set.insert(STACKCLEAR);\
  set.insert(XMLSNIPET);\
  set.insert(XMLSAVE);\
  set.insert(XMLDELETE);\
  set.insert(XMLPRINT);\
  set.insert(PARSE);



/*!
 @ingroup  SNIPPET_SEQUENCE_DEF
 this procedures are used at the end of a sequence
 to decide of the sequence should be done once more or not

 their parser-identifiers are used for as quick-reference
*/
#define CREATE_LASTCHECK_SET_mk(set)               \
  set.insert(REPEAT_IFSTACKEQUAL);\
  set.insert(REPEAT_IFSTACKUNEQUAL);














typedef enum SnippetType_TP
{
 SNIPPET_PART     = 1,
 SNIPPET_SEQUENCE = 2,
 SNIPPET_MACRO    = 3
} SnippetType_TP;




typedef struct _s_SnippetPart_TP
{
 SnippetType_TP Type;
 String_imp     Text;
}_s_SnippetPart_TP;




class SnippetExecution
{
 public:
 /*!
 construktor
 <br><br>
 @htmlinclude SnippetExecution_SnippetExecution.html
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
  SnippetExecution(void);


 /*!
 construktor
 @param [in] snipetInfo raw data of sequences and their commands
                        which should be used by this SnippetExecution
 @param [in] home       container of all snippets to use for call other snipets
 @param [in] holiday    buffer if a snippet should be temporary replaced
 @param [in] ownName   name of this snippet in the container-elements
 @param [in] formats    list of format-symbols

 <br><br>
 @htmlinclude SnippetExecution_SnippetExecution_001.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    05.06.2011   @I  Eckard Klotz
 @I re-factoring of base-design
 @I first implementation
 @I_______________________________________________________
    16.08.2012   @I  Eckard Klotz
 @I using of independent xml-trees
 @I enabling the calling of the associated pre/post-commands
 @I_______________________________________________________
    10.07.2013   @I  Eckard Klotz
 @I re-factoring of base-design
 @I adding a pointer.parameter to the diagram generator
    since it owns a method to evaluate format-symbols
 @I_______________________________________________________
    24.07.2013   @I  Eckard Klotz
 @I re-factoring of base-design
 @I using in predefined sets to decide where to assign
    procedures
 @I_______________________________________________________
    28.07.2013   @I  Eckard Klotz
 @I started to develop a xml-based log-output instead of
    a textual debug-output
 @I ignore macros for warning-messages since they occur
    regularly even they are already solved
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  SnippetExecution(const list<_s_RawSequence_TP> &             snipetInfo,
                   map<String_imp, SnippetExecution*> *        home,
                   map<String_imp, list<SnippetExecution*> > * holiday,
                   const String_imp&                           ownName,
                   Prcs_Transformation*                        formater);




/*!
 destruktor
 <br><br>
 @htmlinclude "SnippetExecution__SnippetExecution.html"
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    06.05.2011   @I  Eckard Klotz
 @I re-factoring of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  ~SnippetExecution(void);








/*!
debug-routine that shows the construction of the snippet
 <br><br>
 @htmlinclude SnippetExecution_showSelf.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    17.07.2011   @I  Eckard Klotz
 @I re-factoring of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  void showSelf(void);





// @param [in] startTag      name of the tag that should be processed

/*!
 generates the diagram-part controlled by the user defined raw-text and
 embedded command-sequences

 @param [in] source        xml-tree that contains the sub-tree to process

 @param [out] replacement       contains replacement-information to tailor
                                tags, attributes and texts
 @param [out] diagram      container of the diagram describing text
 @param [in]  resetSnipets true ==> reset the original snippet for a tag
                           if it was temporary replaced by an other one


 <br><br>
 @htmlinclude SnippetExecution_generate.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    03.07.2010   @I  Eckard Klotz
 @I re-factoring of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  void generate(XML_Node                         source,
//                String_imp                       startTag,
                map<String_imp , String_imp>*    replacement,
                list<String_imp>*                diagram,
                bool                             resetSnipets = true);










/*!
 tries to save the file with the given name

 @param [in] fileName      path and name of the text-file to read
 @param [in] content       text to save
 @param [in] countExisting true  ==>> existing file-names get an counter postfix
 <br>                      false ==>> already existing files will be overwritten
 <br><br>
 @htmlinclude SnippetExecution_writeTextFile.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    21.12.2009   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
  @I_______________________________________________________
   14.08.2011   @I  Eckard Klotz
 @I re-factoring
 @I tries now to create the associated directory if a simple
    save-action fails
 @I_______________________________________________________
   20.12.2011   @I  Eckard Klotz
 @I re-factoring elimination of include-circle problems
 @I implementation of this wrapper-function to call
    the real implementation indirectly
 @I_______________________________________________________
   30.06.2013   @I  Eckard Klotz
 @I re-factoring avoid to create additional files if not needed
 @I the creation of counting sub-fixes is switch-able now
    and per default this functionality is switched off
 @I_______________________________________________________
    10.07.2013   @I  Eckard Klotz
 @I re-factoring of base-design to align the output
 @I using a formatting method before saving the text
 @I_______________________________________________________
    22.12.2014   @I  Eckard Klotz
 @I re-factoring
 @I use of service-function to create folder if not existing
 @I_______________________________________________________
    31.12.2014   @I  Eckard Klotz
 @I bug saved text is not formatted if new folder was created
 @I move formatting line to a location in front of NewFile block
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
void writeTextFile(String_imp fileName,
                   String_imp content,
                   bool       countExisting = false);



/*!
 search for a sub-tree in the xml-source defined by the given start-tag
 and generate the diagram-snippet for it

 @param [in]  source       xml-tree of the source to analyse
 @param [in]  startTag     name of the tag that contains the searched sub-tree
 @param [in]  replacement  contains replacement-information to tailor
                           tags, attributes and texts
 @param [out] diagram      container of the diagram describing text
 @param [in]  resetSnipets true ==> reset the original snippet for a tag
                           if it was temporary replaced by an other one
 <br><br>
 @htmlinclude SnippetExecution_snippet.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    20.12.2009   @I  Eckard Klotz
 @I re-factoring of base-design
 @I first implementation
 @I_______________________________________________________
    20.12.2011   @I  Eckard Klotz
 @I re-factoring elimination of include-circle problems
 @I implementation of this wrapper-function to call
    the real implementation indirectly
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void snippet(XML_Node                       source,
              String_imp                     startTag,
              map<String_imp , String_imp >* replacement,
              list<String_imp>*              diagram,
              bool                           resetSnipets = true);







/*!
 write a value into a stack

 @param [in] name  identifier of the stack to write in
 @param [in] value value to push on the stack


 <br><br>
 @htmlinclude SnippetExecution_addStackValue.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    28.08.2010   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
    21.12.2011   @I  Eckard Klotz
 @I re-factoring elimination of include-circle problems
 @I copy method from class Generator_Nsd
    to class SnippetExecution as wrapper
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  void addStackValue(String_imp name,
                     String_imp value);





 /*!
  @brief set the context-model used for the xml-data management

  @param xml_Context reference of xml context model to use
 */
  void xmlContext_set(XML_DataModel* xml_Context);

 /*!
  @brief return the context-model used for the xml-data management

  @return reference of the xml context model to use
 */
  XML_DataModel*  xmlContext_get(void);






 /*!
 return a slash separated list of snippet-names of snippets which
 have called the current snippet.


 @return      slash separated list of snippet-names


 <br><br>
 @htmlinclude Cmnd_Common_format.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    25.12.2011   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 String_imp getCallerPath(void);



 /*!
 change a given text by evaluating inserted format-symbols

 the following format-changes are done:
 <br> delete all natural new-line characters and replace them
      by line-changes defined by a newline- intend- or detend formatter
 <br> inserted indentions or detentions defined by a intent-
      or detend formatter
 <br> insert a defined number of spaces defined by a space-formatter
 <br> insert a tabifying number of spaces defined by a tab-formatter
 <br> insert a defined ascii-character defined by a numerical formatter

 this function is a wrapper of a method implemented in an other class
 and is used to make the using class independent from the providing class
 both will be connected over the snippet execution as mediator

 @param [in]  rawText text to change


 @return      changed text

 <br><br>
 @htmlinclude Cmnd_Common_format.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    18.07.2013   @I  Eckard Klotz
 @I refactoring of base-design to allign the output
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 String_imp format(String_imp* rawText);






 protected:



 private:





/*!
 doing the checks before starting the rest of the commands

 @param [in] sequence    container of the sequence-procedures

 @return  true if the check-result is a pass or false if not

 <br><br>
 @htmlinclude SnippetExecution__doFirstCheck.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    04.07.2011   @I  Eckard Klotz
 @I refactoring of base-design
 @I first implementation
 @I_______________________________________________________
    16.08.2012   @I  Eckard Klotz
 @I using of independent xml-trees
 @I added command-object to process independent xml-node
 @I_______________________________________________________
    22.09.2014   @I  Eckard Klotz
 @I extending of base-design
 @I added equal and unequal tests for xml-content
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
bool _doFirstCheck(map<String_imp,_s_CommandData_TP>* sequence,
                   XML_Node                           source,
                   map<String_imp, String_imp>*       replacement
                  );


/*!
 doing some preparations before starting the xml-tree depending commands

 @param [in]  sequence          container of the sequence-procedures
 @param [out] snippetRetirement container for downwards replaced sequences
 @param [in]  source            xml-tree that contains the sub-tree to process
 @param [out] replacement       contains replacement-information to tailor
                                tags, attributes and texts
 @param [out] diagram           container of the diagram describing text

 @return  true

 <br><br>
 @htmlinclude SnippetExecution__doPreCommand.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    04.07.2011   @I  Eckard Klotz
 @I re-factoring of base-design
 @I first implementation
 @I_______________________________________________________
    16.08.2012   @I  Eckard Klotz
 @I using of independent xml-trees
 @I added command-object to process independent xml-noded
 @I_______________________________________________________
    17.08.2012   @I  Eckard Klotz
 @I using of independent xml-trees
 @I added the call of xmlCreate, xmlCopy and xmlCut
 @I_______________________________________________________
    16.06.2013   @I  Eckard Klotz
 @I new feature
 @I call of xmlCode method
 @I_______________________________________________________
    23.06.2013   @I  Eckard Klotz
 @I new feature
 @I call of statistic method
 @I_______________________________________________________
    08.08.2013   @I  Eckard Klotz
 @I started to develop a parser-command
 @I new procedure parserSet added
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
bool _doPreCommand(map<String_imp,_s_CommandData_TP>*         sequence,
                   map<String_imp, list<SnippetExecution*> >* snippetRetirement,
                   XML_Node                                   source,
                   map<String_imp, String_imp>*               replacement,
                   list<String_imp>*                          diagram
                  );


/*!
 doing the commands defined for special xml-nodes but only if they exist

 @param [in] sequence    container of the sequence-procedures
 @param [in] startTag    name of the tag that should be processed
 @param [in] source      xml-tree that contains the sub-tree to process
 @param [in] replacement contains replacement-information to tailor
                         tags, attributes and texts
 @param [out] diagram    container of the diagram describing text

 @return  true if at least one defined child xml-node exists
       or false if not

 <br><br>
 @htmlinclude SnippetExecution__doChildCommand.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    04.07.2011   @I  Eckard Klotz
 @I re factoring of base-design
 @I first implementation
 @I_______________________________________________________
    16.08.2012   @I  Eckard Klotz
 @I using of independent xml-trees
 @I added command-object to process independent xml-nodes
 @I_______________________________________________________
    08.08.2013   @I  Eckard Klotz
 @I started to develop a parser-command
 @I new procedure parse added
 @I_______________________________________________________
    15.09.2014   @I  Eckard Klotz
 @I re factoring to implement the generation of modified sources
 @I new procedures xml-insert added
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
bool _doChildCommand(map<String_imp,_s_CommandData_TP>* sequence,
                     const String_imp&                  startTag,
                     XML_Node                           source,
                     map<String_imp, String_imp>*       replacement,
                     list<String_imp>*                  diagram);


/*!
 doing the jobs after processing the xml-tree depending commands

 @param [in] sequence    container of the sequence-procedures
 @param [in] source      xml-tree that contains the sub-tree to process
 @param [in] replacement contains replacement-information to tailor
                         tags, attributes and texts
 @param [out] diagram    container of the diagram describing text

 @return  true

 <br><br>
 @htmlinclude SnippetExecution__doPostCommand.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    04.07.2011   @I  Eckard Klotz
 @I re-factoring of base-design
 @I first implementation
 @I_______________________________________________________
    16.08.2012   @I  Eckard Klotz
 @I using of independent xml-trees
 @I added command-object to process independent xml-node
 @I_______________________________________________________
    17.08.2012   @I  Eckard Klotz
 @I using of independent xml-trees
 @I added the call of xmlSnippet and xmlDelete
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
bool _doPostCommand(map<String_imp,_s_CommandData_TP>* sequence,
                    XML_Node                           source,
                    map<String_imp, String_imp>*       replacement,
                    list<String_imp>*                  diagram);


/*!
 doing the last checks after the rest of the commands

 @param [in] sequence       container of the sequence-procedures
 @param [in] source         xml-tree that contains the sub-tree to process
 @param [in] useAlternative inverted result of @ref _doChildCommand
                            to activate the use of an alternative snippet
                            if the current xml-node contains no child
                            with an associated snippet
 @param [in] replacement    contains replacement-information to tailor
                            tags, attributes and texts
 @param [out] diagram       container of the diagram describing text

 @return  true

 <br><br>
 @htmlinclude SnippetExecution__doLastCheck.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    04.07.2011   @I  Eckard Klotz
 @I refactoring of base-design
 @I first implementation
 @I_______________________________________________________
    16.08.2012   @I  Eckard Klotz
 @I using of independent xml-trees
 @I added command-object to process independent xml-noded
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
bool _doLastCheck(map<String_imp,_s_CommandData_TP>* sequence,
                  XML_Node                           source,
                  bool                               useAlternative,
                  map<String_imp, String_imp>*       replacement,
                  list<String_imp>*                  diagram);







/*!
 cut-out of a snippet temporary, replace it with an other one
 and buffer the original one for a later re-paste

 @param [in]  oldPart        name of the snippet to replace
 @param [in]  newPart        name of the snippet to insert instead
 @param [in] replacement     contains replacement-information to tailor
                             tags, attributes and texts
 @param [out] snippetHoliday temporary buffer for original snippet
                             that should be replaced by an other one

 <br><br>
 @htmlinclude SnippetExecution__useForSnipet.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    17.03.2010   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
    21.12.2011   @I  Eckard Klotz
 @I re-factoring elimination of include-circle problems
 @I moving method from class Generator_Nsd
                     to class SnippetExecution
 @I_______________________________________________________
    21.08.2012   @I  Eckard Klotz
 @I re-factoring of design
 @I old-part and/or new-part of replacement may be the name
    of a stack now in this case the top-value of this stack
    will be used as old/new-value
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void _useForSnipet(String_imp                                 oldPart,
                    String_imp                                 newPart,
                    map<String_imp, String_imp>*               replacement,
                    map<String_imp, list<SnippetExecution*> >* snippetHoliday = nullptr);


/*!
 redo the cut-out of a snippet temporary, and its replacement it with
 an other one by using the buffer of the original one

 @param [out] snippetHoliday   temporary buffer for original snippet
                               that should be replaced by an other one

 <br><br>
 @htmlinclude SnippetExecution__resetSnipets.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    10.07.2011   @I  Eckard Klotz
 @I re-factoring of base-design
 @I first implementation
 @I_______________________________________________________
    21.12.2011   @I  Eckard Klotz
 @I re-factoring elimination of include-circle problems
 @I moving method from class Generator_Nsd
                     to class SnippetExecution
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void _resetSnipets(map<String_imp, list<SnippetExecution*> >* snippetHoliday = nullptr);



/*!
 configuration of parser-command reads the xml-configuration
 and a2x-gramma as defined in the given procedure-parameters
 and orders the creation of a new parser-opbject

 @param [in] procedure   container of parameters

 <br><br>
 @htmlinclude SnippetExecution__setParser.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    11.08.2013   @I  Eckard Klotz
 @I started to develop a parser-command
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void _parserSet( _s_CommandData_TP  procedure);



/*!
 parse a text to create a xml-tree

 @param [in] textToParse text that should be transferred into
                         a xml-tree or the associated stack-name
                         used to buffer it
 @param [in] procedure   container of parameters which describe
                         which parser-rule should be used and
                         where to place the parser-result
 @param [in] replacement contains replacement-information to tailor
                         tags, attributes and texts

 <br><br>
 @htmlinclude SnippetExecution__parse.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    11.08.2013   @I  Eckard Klotz
 @I started to develop a parser-command
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void _parse(String_imp                   textToParse,
             _s_CommandData_TP            procedure,
             map<String_imp, String_imp>* replacement
            );














/*!
 @brief common object-attributes

 to put the attributes into a structure makes it possible to
 set them apart from local variables and parameters of a method
 in the source-code by using the struct-name as prefix.

 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    12.06.2009   @I  Eckard Klotz
 @I re-factoring of base-design
 @I first implementation
 @I_______________________________________________________
    10.07.2013   @I  Eckard Klotz
 @I re-factoring of base-design
 @I adding a pointer to the diagram generator since it
    owns a method to evaluate format-symbols
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 struct Att
 {
  map<unsigned long, String_imp>             FunctionName;
  list <_s_Sequence_TP *>                    Sequence;
  map<String_imp , String_imp >              Replacement;
  map<String_imp, SnippetExecution*>*        Home;
  map<String_imp, list<SnippetExecution*> >* Holiday;
  String_imp                                 OwnName;
  Prcs_Transformation*                       Formater;
  XML_DataModel*                             XML_Context;    ///< manages the xml data



 /// @brief default constructor
 Att(void):
  Home(nullptr),
  Holiday(nullptr),
  OwnName(""),
  Formater(nullptr),
  XML_Context(nullptr)
 {};
 /*!
  @brief copy constructor
  @param [in] src object to copy
 */
 Att(const Att& src):
  FunctionName(src.FunctionName),
  Sequence(src.Sequence),
  Replacement(src.Replacement),
  Home(src.Home),
  Holiday(src.Holiday),
  OwnName(src.OwnName),
  Formater(src.Formater),
  XML_Context(src.XML_Context)
 {};
 /*!
  @brief assignment operator
  @param [in] src object to copy
  @return copied object
 */
 Att& operator = (const Att& src)
 {
  FunctionName = src.FunctionName;
  Sequence     = src.Sequence;
  Replacement  = src.Replacement;
  Home         = src.Home;
  Holiday      = src.Holiday;
  OwnName      = src.OwnName;
  Formater     = src.Formater;
  XML_Context  = src.XML_Context;
  return(*this);
 };
 /// @brief destructor
 ~Att(void)
 {
  FunctionName.clear();
  Sequence.clear();
  Replacement.clear();
 };







 } Att;
 static list<String_imp>              Att_Caller;


};


#ifndef DOXYGEN
#define USING_NAMESPACE using namespace
//}; USING_NAMESPACE CL_SNIPPET;
#undef  USING_NAMESPACE
#endif //DOXYGEN


#endif // SNIPPET_H
#endif // header guard

