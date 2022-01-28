/*!

 @file
 @brief  definition of a collection of snippet-commands to organize a xml-stack

 This file contains special snippet-commands used to manage a stack for xml-nodes
 used as temporary LiFo memory for part-results

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
    26.02.2012     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    26.02.2012...  @I Eckard Klotz
 @I Changes are documented in the comment of the changed element
 @TabEnd

*/
#ifndef CMND_DICT_XML_H
#define CMND_DICT_XML_H


//#include <iostream>
//#include <list>
#include <map>
//#include <fstream>
//#include <set>

using namespace std;



#include "snippet.h"
#include "command.h"


#include "xml_DataModel.h"














#ifndef DOXYGEN
//namespace CL_COMMAND {
//namespace CL_CMND_DICT_XML {
#endif //DOXYGEN




/*!
 @brief Concrete command to construct Snippet-content by defining new xml-trees.

 @history
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    27.8.2008   @I  Eckard Klotz @I First Implementation @I
 @I_______________________________________________________
    26.02.2012   @I  Eckard Klotz
 @I implementation of stack for xml-data
 @I renaming the class from Cmnd_Stack to Cmnd_Dict_XML
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/

class Cmnd_Dict_XML:public Cmnd_Common
{
 public:



/*!
 construktor
 <br><br>
 @htmlinclude Cmnd_Dict_XML_Cmnd_Dict_XML.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    26.02.2012   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  Cmnd_Dict_XML(void);











/*!
 destruktor
 <br><br>
 @htmlinclude "Cmnd_Dict_XML__Cmnd_Dict_XML.html"
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    26.02.2012   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  ~Cmnd_Dict_XML(void);


/*!
 write a value into the dictionary

 @param [in] name  identifier of the stack to write in
 @param [in] value value to push on the stack


 <br><br>
 @htmlinclude Cmnd_Dict_XML_addValue.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    26.02.2012   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  void addValue( String_imp name, XML_Node value);



/*!
 get a xml-element out of the dictionary

 @param [in] name        identifier of the stack to write in
 @param [in] tagPath     path of a sub-child to return
 @param [in] separator   separator used in the path
 @param [in] owner       snippet that has called this function if user-message
                         should be displayed in shell-window if an error was found
             <br>        or NULL if no message should be displayed


 <br><br>
 @htmlinclude Cmnd_Dict_XML_getValue.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    07.08.2013   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  XML_Node getValue(String_imp        name,
                    String_imp        tagPath   = "",
                    char              separator = '/',
                    SnippetExecution* owner     = NULL);




 /*!
  @brief initialize the context-model used for the internal xml-data management
 */
 static void xmlContext_init(void);

 /*!
  @brief return the context-model used for the xml-data management

  @return reference of the xml context model to use
 */
  XML_DataModel*  xmlContext_get(void);






/*!
 call a snipet that creates a source of a new independent xml-root
 and store it under the given tag-name or as a child of an existing
 given node in the given new-path

 @param [in] source      xml-tree of the source to analyse
 @param [in] newName     identifier of the new independent xml-root
 @param [in] newPath     path of a sub-child to generate
 @param [in] separator   separator used in the path
 @param [in] snipetName  Snippet to call for creation
 @param [in] replacement contains replacement-information to tailor
                         tags, attributes and texts
 @param [in] owner       snippet that has called this function if user-message
                         should be displayed in shell-window if an error was found
             <br>        or NULL if no message should be displayed


 <br><br>
 @htmlinclude Cmnd_Dict_XML_xmlCreate.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    16.08.2012   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
    10.07.2013   @I  Eckard Klotz
 @I re-factoring of base-design to align the output
 @I using a formatting method provided by the owner
 @I_______________________________________________________
    12.10.2013      @I  Eckard Klotz
 @I bug: xml-comments lead to crash
 @I xml-iterations will be done by using TixmlNode instead
    of TiXmlElement,
    as first action in the loop a macro checks if the
    current-element is a xml-comment and forces immediate
    the start of the next loop
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  void xmlCreate(XML_Node                     source,
                 String_imp                   newName,
                 String_imp                   newPath,
                 char                         separator,
                 String_imp                   snipetName,
                 map<String_imp, String_imp>* replacement,
                 SnippetExecution*            owner);

/*!
 copy the content of the given child or sub-child to create a new
 independent xml-root and store it under the given tag-name or as
 a child of an existing given node in the given new-path

 @param [in] source      xml-tree of the source to analyse
 @param [in] newName     identifier of the new independent xml-root
 @param [in] newPath     path of a sub-child to generate
 @param [in] tagName     identifier of the xml-root to copy from
 @param [in] tagPath     identifier-path of the xml-element to copy
 @param [in] separator   separator used in the path
 @param [in] replacement contains replacement-information to tailor
                         tags, attributes and texts
 @param [in] owner       snippet that has called this function if user-message
                         should be displayed in shell-window if an error was found
             <br>        or NULL if no message should be displayed


 <br><br>
 @htmlinclude Cmnd_Dict_XML_xmlCopy.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    16.08.2012   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  void xmlCopy(XML_Node                     source,
               String_imp                   newName,
               String_imp                   newPath,
               String_imp                   tagName,
               String_imp                   tagPath,
               char                         separator,
               map<String_imp, String_imp>* replacement,
               SnippetExecution*            owner);

/*!
 cut out the content of the given child or sub-child to create a new
 independent xml-root and store it under the given tag-name or as
 a child of an existing given node in the given new-path

 @param [in] source      xml-tree of the source to analyse
 @param [in] newName     identifier of the new independent xml-root
 @param [in] newPath     path of a sub-child to generate
 @param [in] tagName     identifier of the xml-root to copy from
 @param [in] tagPath     identifier-path of the xml-element to copy
 @param [in] separator   separator used in the path
 @param [in] replacement contains replacement-information to tailor
                         tags, attributes and texts
 @param [in] owner       snippet that has called this function if user-message
                         should be displayed in shell-window if an error was found
             <br>        or NULL if no message should be displayed


 <br><br>
 @htmlinclude Cmnd_Dict_XML_xmlCut.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    16.08.2012   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  void xmlCut(XML_Node                     source,
              String_imp                   newName,
              String_imp                   newPath,
              String_imp                   tagName,
              String_imp                   tagPath,
              char                         separator,
              map<String_imp, String_imp>* replacement,
              SnippetExecution*            owner);






/*!

 transfer the content of the given child or sub-child into its
 code-structure and create a new independent xml-root to store
 it under the given tag-name or as a child of an existing given
 node in the given new-path

 @param [in] source      xml-tree of the source to analyse
 @param [in] newName     identifier of the new independent xml-root
 @param [in] newPath     path of a sub-child to generate
 @param [in] tagName     identifier of the xml-root to copy from
 @param [in] tagPath     identifier-path of the xml-element to copy
 @param [in] separator   separator used in the path
 @param [in] replacement contains replacement-information to tailor
                         tags, attributes and texts
 @param [in] owner       snippet that has called this function if user-message
                         should be displayed in shell-window if an error was found
             <br>        or NULL if no message should be displayed


 <br><br>
 @htmlinclude Cmnd_Dict_XML_xmlCode.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    16.06.2012   @I  Eckard Klotz
 @I expending of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  void xmlCode(XML_Node                     source,
               String_imp                   newName,
               String_imp                   newPath,
               String_imp                   tagName,
               String_imp                   tagPath,
               char                         separator,
               map<String_imp, String_imp>* replacement,
               SnippetExecution*            owner);




/*!

 insert the content of an independently generated xml-node into the given
 destination

 @param [in] destination xml-tree of the destination to insert in
 @param [in] newName     identifier of the independent xml-root to insert
 @param [in] newPath     path of a sub-child to insert
 @param [in] position    identifies the position to insert
 <br>                    __BEFORE__ before the give destination
 <br>                    __AFTER__  after the given destination
 <br>                    __FIRST__  as first child of the given destination
 <br>                    __LAST__   as last child of the given destination
 <br>                    number     an integer that describes the position to insert as child

 @param [in] separator   separator used in the path
 @param [in] replacement contains replacement-information to tailor
                         tags, attributes and texts
 @param [in] owner       snippet that has called this function if user-message
                         should be displayed in shell-window if an error was found
             <br>        or NULL if no message should be displayed


 <br><br>
 @htmlinclude Cmnd_Dict_XML_xmlInsert.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    15.09.2014   @I  Eckard Klotz
 @I re factoring to implement the generation of modified sources
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  void xmlInsert(XML_Node                     destination,
                 String_imp                   newName,
                 String_imp                   newPath,
                 const String_imp&            position,
                 char                         separator,
                 map<String_imp, String_imp>* replacement,
                 SnippetExecution*            owner);






// @param [in] tolerant    user-decision if non existing xml-nodes are acceptable or not

/*!
 start the evaluation of an independent xml-root or node

 @param [in] newName     identifier of the independent xml-root to evaluate
 @param [in] newPath     identifier-path of the independent xml-element to evaluate
 @param [in] separator   separator used in the path
 <br>                    if the given value is <b>__TOLERANT__</b> no message will be displayed
 <br>                    otherwise missing xml-nodes result in an message-output
 @param [in] replacement contains replacement-information to tailor
                         tags, attributes and texts
 @param [out] diagram    container of the diagram describing text
 @param [in]  owner      snipet that has called this function if user-message
                         should be displayed in shell-window if an error was found
             <br>        or NULL if no message should be displayed


 <br><br>
 @htmlinclude Cmnd_Dict_XML_xmlSnipet.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    16.08.2012   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  void xmlSnipet(String_imp                   newName,
                 String_imp                   newPath,
                 char                         separator,
//                 const String_imp&            tolerant,
                 map<String_imp, String_imp>* replacement,
                 list<String_imp>*            diagram,
                 SnippetExecution*            owner);




/*!
 save an independent xml-root or node in a file

 @param [in] newName     identifier of the independent xml-root to delete in
 @param [in] tagPath     identifier-path of the independent xml-element to delete
 @param [in] separator   separator used in the path
 @param [in] fileName    name of the file to save in
 @param [in] filePath    path of the file to save in

 @param [in] usedPathSeparator character or character-sequence used as
                               separator of folder-path definitions in
                               user-configuration
 @param [in] osPathSeparator   character or character-sequence to be used
                               as separator of folder-path definitions in
                               current operation system of the computer

 @param [in] replacement contains replacement-information to tailor
                         tags, attributes and texts
 @param [in] owner       snipet that has called this function if user-message
                         should be displayed in shell-window if an error was found
             <br>        or NULL if no message should be displayed


 <br><br>
 @htmlinclude Cmnd_Dict_XML_xmlSave.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    20.08.2012   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  void xmlSave(String_imp                   newName,
               String_imp                   tagPath,
               char                         separator,
               const String_imp&            fileName,
               const String_imp&            filePath,

               const String_imp&            usedPathSeparator,
               const String_imp&            osPathSeparator,

               map<String_imp, String_imp>* replacement,
               SnippetExecution*            owner);




/*!
 delete the evaluation of an independent xml-root or node

 @param [in] newName     identifier of the independent xml-root to delete in
 @param [in] newPath     identifier-path of the independent xml-element to delete
 @param [in] separator   separator used in the path
 @param [in] replacement contains replacement-information to tailor
                         tags, attributes and texts
 @param [in] owner       snipet that has called this function if user-message
                         should be displayed in shell-window if an error was found
             <br>        or NULL if no message should be displayed


 <br><br>
 @htmlinclude Cmnd_Dict_XML_xmlDelete.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    16.08.2012   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  void xmlDelete(String_imp                   newName,
                 String_imp                   newPath,
                 char                         separator,
                 map<String_imp, String_imp>* replacement,
                 SnippetExecution*            owner);




 /*!
 print of the given xml-element to live-output

 @param [in]   source      xml-tree of the source to analyse
 @param [in]   prefix      additional string printed before the xml-content
 <br>                      may be an empty-string
 <br>                      following escape sequences are supported \n \t
 @param [in]   tagName     identifier of the xml-root to check
 @param [in]   tagPath     identifier-path of the xml-element to check
 @param [in]   xmlProperty name of an attribute in quotes to check the its content
 <br>                      empty quotes to check the text-content
 <br>                      empty string to check the existence of the last node in the given path
 @param [in]   separator   separator used in the path
 @param [in]   replacement contains replacement-information to tailor
                           tags, attributes and texts
 @param [in]   owner       snippet that has called this function if user-message
                           should be displayed in shell-window if an error was found
             <br>          or NULL if no message should be displayed

 <br><br>
 @htmlinclude Cmnd_Dict_XML_xmlPrint.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    23.09.2014   @I  Eckard Klotz
 @I extension of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void xmlPrint(XML_Node       source,
               String_imp     prefix,
               String_imp     tagName,
               String_imp     tagPath,
               String_imp     xmlProperty,
               char           separator,
 map<String_imp, String_imp>* replacement,
            SnippetExecution* owner);






 /*!
 compare if content of the given xml-element is equal to a ref-content

 @param [in]   source      xml-tree of the source to analyse
 @param [in]   tagName     identifier of the xml-root to check
 @param [in]   tagPath     identifier-path of the xml-element to check
 @param [in]   xmlProperty name of an attribute in quotes to check the its content
 <br>                      empty quotes to check the text-content
 <br>                      empty string to check the existence of the last node in the given path
 @param [in]   refValue    value to compare with
 @param [in]   separator   separator used in the path
 @param [in]   replacement contains replacement-information to tailor
                           tags, attributes and texts
 @param [in]   owner       snippet that has called this function if user-message
                           should be displayed in shell-window if an error was found
             <br>          or NULL if no message should be displayed
 @param [out]  result      will be set to false if compare-result is unequal

 <br><br>
 @htmlinclude Cmnd_Dict_XML_ifXmlEqual.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    22.09.2014   @I  Eckard Klotz
 @I extension of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void ifXmlEqual(XML_Node       source,
                 String_imp     tagName,
                 String_imp     tagPath,
                 String_imp     xmlProperty,
                 String_imp     refValue,
                 char           separator,
   map<String_imp, String_imp>* replacement,
              SnippetExecution* owner,
                 bool*          result);



/*!
 compare if content of the given xml-element is unequal to a ref-content

 @param [in]   source      xml-tree of the source to analyse
 @param [in]   tagName     identifier of the xml-root to check
 @param [in]   tagPath     identifier-path of the xml-element to check
 @param [in]   xmlProperty name of an attribute in quotes to check the its content
 <br>                      empty quotes to check the text-content
 <br>                      empty string to check the existence of the last node in the given path
 @param [in]   refValue    value to compare with
 @param [in]   separator   separator used in the path
 @param [in]   replacement contains replacement-information to tailor
                           tags, attributes and texts
 @param [in]   owner       snippet that has called this function if user-message
                           should be displayed in shell-window if an error was found
             <br>          or NULL if no message should be displayed
 @param [out]  result      will be set to false if compare-result is unequal

 <br><br>
 @htmlinclude Cmnd_Dict_XML_ifXmlUnequal.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    22.09.2014   @I  Eckard Klotz
 @I extension of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void ifXmlUnequal(XML_Node    source,
                   String_imp  tagName,
                   String_imp  tagPath,
                   String_imp  xmlProperty,
                   String_imp  refValue,
                   char        separator,
  map<String_imp, String_imp>* replacement,
             SnippetExecution* owner,
                   bool*       result);





 /*!
 check if the given xml-element is existing

 @param [in]   source      xml-tree of the source to analyse
 @param [in]   tagName     identifier of the xml-root to check
 @param [in]   tagPath     identifier-path of the xml-element to check
 @param [in]   xmlProperty name of an attribute in quotes to check the its content
 <br>                      empty quotes to check the text-content
 <br>                      empty string to check the existence of the last node in the given path
 @param [in]   separator   separator used in the path
 @param [in]   replacement contains replacement-information to tailor
                           tags, attributes and texts
 @param [out]  result      will be set to false if compare-result is unequal

 <br><br>
 @htmlinclude Cmnd_Dict_XML_ifXmlExisting.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    23.09.2014   @I  Eckard Klotz
 @I extension of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void ifXmlExisting(XML_Node       source,
                    String_imp     tagName,
                    String_imp     tagPath,
                    String_imp     xmlProperty,
                    char           separator,
      map<String_imp, String_imp>* replacement,
                    bool*          result);



/*!
 check if the given xml-element is not existing

 @param [in]   source      xml-tree of the source to analyse
 @param [in]   tagName     identifier of the xml-root to check
 @param [in]   tagPath     identifier-path of the xml-element to check
 @param [in]   xmlProperty name of an attribute in quotes to check the its content
 <br>                      empty quotes to check the text-content
 <br>                      empty string to check the existence of the last node in the given path
 @param [in]   separator   separator used in the path
 @param [in]   replacement contains replacement-information to tailor
                           tags, attributes and texts
 @param [out]  result      will be set to false if compare-result is unequal

 <br><br>
 @htmlinclude Cmnd_Dict_XML_ifXmlMissing.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    23.09.2014   @I  Eckard Klotz
 @I extension of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void ifXmlMissing(XML_Node    source,
                   String_imp  tagName,
                   String_imp  tagPath,
                   String_imp  xmlProperty,
                   char        separator,
  map<String_imp, String_imp>* replacement,
                   bool*       result);













 protected:





 private:

/*!
 check if the given leadName is used as stack identifier and if so
 the value saved as stack top-value will be used to redefine the values o
 given lead-name and pat, otherwise it will be checked if the given name
 is used as stack-identifier for replacing the given path-value, in the case
 of a redefinition of the path the separaotr will be redifined also

 @param [in]  leadName    leading name of a file- or xml-path
 @param [in]  path        rest of the file or xml-path
 @param [in]  separator   separator used in the path
 @param [in]  replacement contains replacement-information to tailore
                          tags, attributes and texts


 <br><br>
 @htmlinclude Cmnd_Dict_XML_checkStack.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    23.08.2012   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
void _checkStack(String_imp*                   leadName,
                 String_imp*                   path,
                 char*                         separator,
                 map<String_imp , String_imp>* replacement);





/*!
 read out the text-content of the given xml-node and its childes
 and transform it into a xml-structure that represents the document-structure
 and not the algorithm-structure.

 @param [in]  source      root-node of the xml-tree to evaluate
 @param [in]  minCol      controls the analysis of leading spaces
 <br>  if not used or a number greater as the column-number of the most left non-space character
       the method tries to cut the minimum number of leading spaces found in the whole text
 <br>  if a number less  as the column-number of the most left character is used
       the method tries to leave some leading spaces controlled by the difference of
       the column-number of the most left non-space character and the used value of minCol

 @return text-content that was read-out

 <br><br>
 @htmlinclude Cmnd_Dict_XML_getCodeFragments.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    19.10.2010   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
    16.06.2013   @I  Eckard Klotz
 @I expending of base-design
 @I method created as copy from Prcs__Abstract in process.h
 @I_______________________________________________________
    12.10.2013      @I  Eckard Klotz
 @I bug: xml-comments lead to crash
 @I xml-iterations will be done by using TixmlNode instead
    of TiXmlElement,
    as first action in the loop a macro checks if the
    current-element is a xml-comment and forces immediate
    the start of the next loop
  @I_______________________________________________________
     15.09.2014   @I  Eckard Klotz
 @I re factoring to implement the generation of modified sources
 @I not existing lines will be inserted as EMPTYLINE elements
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 XML_Node _getCodeFragments(XML_Node source, int minCol = INT_MAX);



/*!
 create line-number orientated map of lists which contain only those
 xml-elements which are direct parents of text-elements
 @param [in]  source      root-node of the xml-tree to evaluate
 @param [out] text        container of all direct parent-tags with only text-elements
 @param [in]  maxNumber   maximum of reached line-number while recursive call
 <br><br>
 @htmlinclude Cmnd_Dict_XML_getText.html
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
    16.06.2013   @I  Eckard Klotz
 @I expending of base-design
 @I method created as copy from Prcs__Abstract in process.h
 @I_______________________________________________________
     15.09.2014   @I  Eckard Klotz
 @I re factoring to implement the generation of modified sources
 @I attribute new will be copied if existing and
    text-elements without childes will get an empty text-element
    to be treated as text-carrier
 @I_______________________________________________________
                @I               @I              @I
 @TabEnd
*/
void _getText(XML_Node                   source,
              map<int, list<XML_Node> >* text,
              int*                       maxNumber);




/*!
 evaluate if given source describes more than one code-line and
 add each separated line into the destination

 @param [in]  destination receives the separated line-nodes
 @param [in]  source      root-node of the xml-tree to evaluate

 <br><br>
 @htmlinclude Cmnd_Dict_XML_insertNewLines.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    15.09.2014   @I  Eckard Klotz
 @I re factoring to implement the generation of modified sources
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
void _insertNewLines(XML_Node destination, XML_Node source);








static map<String_imp, XML_Node> Att_Dict;       ///< @brief container of new xml-trees
static XML_DataModel             XML_Context;    ///< @brief manages the xml data

};



#ifndef DOXYGEN
#define USING_NAMESPACE  using namespace
//}; USING_NAMESPACE CL_CMND_DICT_XML ;
//}; USING_NAMESPACE CL_COMMAND ;
#undef  USING_NAMESPACE
#endif //DOXYGEN



#endif //CMND_DICT_XML_H

