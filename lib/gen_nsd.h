#ifndef HEADER_CA2C246C9F0D35D0
#define HEADER_CA2C246C9F0D35D0

/*!

 @file
 @brief    definition of a script-generator

 This file contains the definition of a script generator with an own
 snippet-parser.


 Copyright (C) 2009-2020 by Eckard Klotz.

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
    06.12.2009     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    06.12.2009...  @I Eckard Klotz
 @I Changes are documented in the comment of the changed element
 @I____________________________________________________________
    18.08.2010...  @I Eckard Klotz
 @I In several names of functions variables defines and so on the
    word macro is replaced by the word sequence, since the word
    macro should be used for something else in the future.
 @TabEnd

*/
#ifndef GEN_NSD_H
#define GEN_NSD_H


#include <map>
#include <fstream>

using namespace std;

#include "xml_DataModel.h"



#include "transform.h"
#include "command.h"
#include "snippet.h"

#ifndef DOXYGEN
//namespace CL_PROCESS {
//namespace CL_TRANSFORM {
//namespace CL_GEN_NSD {
#endif //DOXYGEN


/// describes a format-symbol inserted by the user in a snippet and
/// contained by a generated text.
typedef struct _s_Format_TP
{
  String_imp   Name;    ///< identifier of the formatting symbol
  size_t       Number;  ///< parameter of the format action
  size_t       Begin;   ///< <b>first</b> character-index in the analysed
                        ///  text <b>of</b> the format symbol <b>itself</b>
  size_t       End;     ///< <b>first</b> character-index in the analysed
                        ///  text <b>behind</b> the format symbol
  String_imp   Part;    ///< text-part that follows the format-symbol until
                        ///  the next format-symbol


 /// @brief default constructor
 _s_Format_TP(void):
  Name(""),
  Number(0),
  Begin(0),
  End(0),
  Part("")
 {};

 /*!
  @brief initializing constructor
 */
 _s_Format_TP(const String_imp& name,
              const size_t&     number,
              const size_t&     begin,
              const size_t&     end,
              const String_imp& part):
  Name(name),
  Number(number),
  Begin(begin),
  End(end),
  Part(part)
 {};


 /*!
  @brief copy constructor
  @param [in] src object to copy
 */
 _s_Format_TP(const _s_Format_TP& src):
  Name(src.Name),
  Number(src.Number),
  Begin(src.Begin),
  End(src.End),
  Part(src.Part)
 {};
 /*!
  @brief assignment operator
  @param [in] src object to copy
  @return copied object
 */
 _s_Format_TP& operator = (const _s_Format_TP& src)
 {
  Name   = src.Name;
  Number = src.Number;
  Begin  = src.Begin;
  End    = src.End;
  Part   = src.Part;
  return(*this);
 };
 /// @brief destructor
 ~_s_Format_TP(void)
 {
  Name.clear();
  Part.clear();
 };



}_s_Format_TP;





/*!
 @brief
 Complex parser defined by user grammar to analyse comments.
 As result the analysed source contains no comments anymore.
 But all comments will be stored in an own xml-structure.
 <br>
 The user-grammar will be read and analysed by a special
 notation-parser. As result of this process an object of the
 evaluation-class gets its own parser-tree to analyse specific
 source-files.
 <br>
 The user has to define 2 basic rules in
 the grammar like this examples show:
 <br> fail = ???;
 <br> pass = ???;
 <br>
 The real content may be changed if necessary
 @history
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    06.12.2009   @I  Eckard Klotz @I First Implementation @I
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
class Generator_Nsd:public Prcs_Transformation
{
 public:


/*!
 default-constructor

 <br><br>
 @htmlinclude Generator_Nsd_Generator_Nsd.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    06.12.2009   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  Generator_Nsd();


/*!
 user-constructor

 @param [in] jumpIn comma separated list of xml-names
                    which are the start-points of generation

 <br><br>
 @htmlinclude Generator_Nsd_Generator_Nsd.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    14.02.2010   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 explicit Generator_Nsd(const String_imp& jumpIn);





/*!
 destructor
 <br><br>
 @htmlinclude "Generator_Nsd_~Generator_Nsd.html"
*/
  virtual ~Generator_Nsd();


/*!
 evaluate an given text and saves the result to a specified location

 @param [in] text text to analyse
 @param [in] rule name of rule used for parsing

 @return


 <br><br>
 @htmlinclude Generator_Nsd_analyse.html
 @TabBegin
 @param [in] rule name of rule used for parsing
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    06.12.2009   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
    06.12.2009   @I  Eckard Klotz
 @I implementation of macro-feature
 @I iteration over all snippets to call the macro-replacement
 @I_______________________________________________________
    25.07.2013   @I  Eckard Klotz
 @I refactoring of base-design
 @I started to develop a xml-based log-output instead of
    a textual debug-output
 @I_______________________________________________________
    02.08.2013   @I  Eckard Klotz
 @I re factoring of base-design
 @I name of rule used for parsing is now an optional parameter
    normally set to pass
 @I_______________________________________________________
    02.08.2013   @I  Eckard Klotz
 @I re factoring of base-design
 @I name of rule used for parsing is now an optional parameter
    normally set to pass
 @I_______________________________________________________
    07.06.2014   @I  Eckard Klotz
 @I bug number of ascci characters in format procedures are not
    transferred correctly to node-attribute of snippet xml-log
 @I index of sub-string begin reduced from 3 to 2 since the
    third character of corresponding ascii rule has the index 2
    and not 3
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
  TiXmlDocument* analyse(IndepFellowTree& result,
                         String_imp*      text,
                         String_imp       rule = "pass");
*/
 TiPa_Concrete::DataFellow* analyse(String_imp*       text,
                                    TiPa_DataModel*   model,
                                    const String_imp& rule = "pass");







/*!
 start the search for a sub-tree in the xml-source and the
 diagram-generation for it driven by the object-attribute
 list of start-tags.

 @param [in] source   xml-tree of the source to analyse
 @param [in] destPath location of the generated diagram

 @todo check if parameter destPath is really necessary

 <br><br>
 @htmlinclude Generator_Nsd_generate.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    20.12.2009   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  void generate(XML_Node          source,
                const String_imp& destPath);


/*!
 write a value into a stack

 @param [in] name  identifier of the stack to write in
 @param [in] value value to push on the stack


 <br><br>
 @htmlinclude Generator_Nsd_addStackValue.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    28.08.2010   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
    21.12.2011   @I  Eckard Klotz
 @I refactoring elimination of include-circle problems
 @I change methode from class Generator_Nsd
    to a wraper of a class SnippetExecution methode
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  void addStackValue(const String_imp& name,
                     const String_imp& value);


 /*!
  @brief set the context-model used for the xml-data management

  @param xml_Context reference of xml context model to use
 */
  void xmlContext_set(XML_DataModel* xml_Context);

 /* !
  @brief return the context-model used for the xml-data management

  @return reference of the xml context model to use
  XML_DataModel*  xmlContext_get(void);
 */




/*!
 search for a sub-tree in the xml-source defined by the given start-tag
 and generate the diagram-snipet for it

 @param [in]  source       xml-tree of the source to analyse
 @param [in]  startTag     name of the tag that contains the searched sub-tree
 @param [in]  replacement  contains replacement-information to tailore
                           tags, attributes and texts
 @param [out] diagram      container of the diagram describing text
 @param [in]  resetSnipets true ==> reset the original snipet for a tag
                           if it was temporary replaced by an other one
 <br><br>
 @htmlinclude Generator_Nsd_snippet.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    20.12.2009   @I  Eckard Klotz
 @I re-factoring of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void snippet(XML_Node                       source,
              const String_imp&              startTag,
              map<String_imp , String_imp >* replacement,
              list<String_imp>*              diagram,
              bool                           resetSnipets = true);




 /*!
 change a given text by evaluating inserted format-symbols

 the following format-changes are done:
 <br> delete all natural new-line characters and replace them
      by linechanges defined by a newline- idend- or dedend formater
 <br> inseret indentions or dedentions defined by a idend-
      or dedend formater
 <br> insert a defined number of spaces defined by a space-formater
 <br> insert a tabyfying number of spaces defined by a tab-formater
 <br> insert a defined ascii-character defined by a numerical formater

 @param [in]  rawText text to change


 @return      changed text

 <br><br>
 @htmlinclude Cmnd_Common_format.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    10.07.2013   @I  Eckard Klotz
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
 evaluate an element of a parser-tree (result of parsing)

 @param [in] i parser part-result


 <br><br>
 @htmlinclude Generator_Nsd__eval_SearchRule.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    13.12.2009   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
    16.11.2013   @I  Eckard Klotz
 @I re-factoring to deal with different rule-definitions of
    snippet_name
 @I parser-tree of snippet_name will be serialized now instead
    of assuming to the tree level of the sub-rule name
 @I_______________________________________________________
    31.12.2015   @I  Eckard Klotz
 @I implementing the new parser TiPa
 @I parameter is now an association-pointer
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
  void _eval_SearchRule(iter_t const& i);
*/
  void  _eval_SearchRule(TiPa_Concrete::DataAssociation* hit);



/*!

 search for a sub-tree in the xml-source defined by the given start-tag
 and generate the diagram for it

 @param [in] source    xml-tree of the source to analyse
 @param [in] destPath  location of the generated diagram
 @param [in] startTag  name of the tag that contains the searched sub-tree

 @todo check if parameter destPath is really necessary

 <br><br>
 @htmlinclude Generator_Nsd__search.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    15.03.2010   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
    17.08.2012   @I  Eckard Klotz
 @I bug: an additional fill will be generated if the xml-tree
         contains a text equal to a xml-node tag mentioned between
         \<Generate\> and \</Generate\> in the configuration
 @I start-snippet will only be generated if an element-node is found
    and in addition no search-iteration over the childes of text-nodes
    will be done any more
 @I_______________________________________________________
    12.10.2013      @I  Eckard Klotz
 @I bug: xml-comments lead to crash
 @I xml-iterations will be done by using TixmlNode instead
    of TiXmlElement,
    as first action in the loop a macro checks if the
    current-element is a xml-comment and forces emidietly
    the start of the next loop
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
void _search(XML_Node          source,
             const String_imp& destPath,
             const String_imp& startTag);



/*!

 replace in the given snipet a macro-sequence by the content
 of an other snipet where user defined part-strings will be replaced by
 other user-defined strings

 @param [in] snipetName   name of the snipet to replace macros in
 @param [in] snipet       snipet to replace macros in

 <br><br>
 @htmlinclude Generator_Nsd__replaceMacros.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    19.09.2010   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
    23.04.2013   @I  Eckard Klotz
 @I making makros more flexible
 @I use replacements to realize something like parameters
 @I_______________________________________________________
    25.07.2013   @I  Eckard Klotz
 @I refactoring of base-design
 @I leave macro-sequences parts after inserting their
    replacement insert an additional copy of it after the
    replacement but only for creating log-output
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
void _replaceMacros(const String_imp&            snipetName,
                    list<_s_SnippetPart_TP>*     snipet);



/*!

 convert snipet in list of sequence-lists

 @param [in] snipet       snipet to replace macros in
 @param [in] command_set  set of id-numbers to identifiy the used commands

 @return list of snipet row-commands

 <br><br>
 @htmlinclude Generator_Nsd__preResolve.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    20.06.2011   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
    25.07.2013   @I  Eckard Klotz
 @I refactoring of base-design
 @I evaluate macro-sequences but only for creating log-output
 @I_______________________________________________________
    28.07.2013   @I  Eckard Klotz
 @I started to develop a xml-based log-output instead of
    a textual debug-output
 @I format-tokens will be coded not as FORMAT but as
    NEWLINE, INDEND, DEDEND, ...
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
 list<_s_RawSequence_TP>  _preResolve(list<_s_SnippetPart_TP>* snipet, set<unsigned long>* command_set);
*/
 list<_s_RawSequence_TP>  _preResolve(list<_s_SnippetPart_TP>* snipet, set<String_imp>* command_set);





 /*!
 return a describing list of format-symbols

 @param [in]   text        text to analyse
 @param [out]  returnValue list of format-symbols


 <br><br>
 @htmlinclude Cmnd_Common__getFormatSymbols.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    14.07.2013   @I  Eckard Klotz
 @I refactoring of base-design to allign the output
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
void _getFormatSymbols(String_imp* text, list<_s_Format_TP>* returnValue);


/*!
 return a list of text-parts with a formating symbol at the beginning
 while the over given text will be be nearly erased except the fist part
 with no formating symbol if existing

 @param []  text text to analyse


 @return      list of text-parts

 <br><br>
 @htmlinclude Cmnd_Common__split.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    14.07.2013   @I  Eckard Klotz
 @I refactoring of base-design to allign the output
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 list<_s_Format_TP> _split(String_imp* text);







/*!
 @brief common object-attributes

 to put the attributes into a structure makes it possible to
 set them apart from local variables and parameters of a method
 in the source-code by using the struct-name as prefix.

 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    06.12.2009   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 struct Att
 {
  map<String_imp, list<_s_SnippetPart_TP> >  RawSnippet;

  map<String_imp, SnippetExecution*>         Snippet;
  map<String_imp, list<SnippetExecution*> >  SnippetHoliday;

  list<String_imp>                           JumpIn;

// cppcheck-suppress unusedStructMember symbolName=Att::XML_Context
  XML_DataModel*                             XML_Context;    ///< @brief manages the xml data
 } Att;


// _s_CmndTool_TP Cmnd;

 enum
  {
   Skip_id   =  1,
   Search_id =  2
  };





};




#ifndef DOXYGEN
#define USING_NAMESPACE using namespace
//};USING_NAMESPACE  CL_GEN_NSD;
//};USING_NAMESPACE  CL_TRANSFORM;
//};USING_NAMESPACE  CL_PROCESS;
#undef  USING_NAMESPACE
#endif //DOXYGEN









#endif //GEN_NSD_H
#endif // header guard

