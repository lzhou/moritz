/*!

 @file
 @brief  definition of a collection of snippet-commands to get data from an xml-part

 This file contains special snippet-commands used to to read ot data out of the current
 xml-tag to analyze

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
#ifndef CMND_SRCDATA_H
#define CMND_SRCDATA_H


//#include <iostream>
//#include <list>
//#include <map>
//#include <fstream>
//#include <set>

using namespace std;



#include "xml_DataModel.h"

#include "command.h"
#include "snippet.h"











#ifndef DOXYGEN
//namespace CL_COMMAND {
//namespace CL_CMND_SRCDATA {
#endif //DOXYGEN


/*!
 @brief Concrete command to construct snippet content by analysing xml-content.

 @history
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    27.8.2008   @I  Eckard Klotz @I First Implementation @I
 @I_______________________________________________________
    26.02.2012   @I  Eckard Klotz
 @I implementation of stack for xml-data
 @I renaming the class from Cmnd_xmlData to Cmnd_SrcData
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/

class Cmnd_SrcData:public Cmnd_Common
{
 public:



/*!
 construktor
 <br><br>
 @htmlinclude Cmnd_SrcData_Cmnd_SrcData.html
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
//  Cmnd_SrcData(Generator_Nsd* owner);
//  Cmnd_SrcData(SnippetExecution* owner);
  Cmnd_SrcData(void);






/*!
 destruktor
 <br><br>
 @htmlinclude "Cmnd_SrcData__Cmnd_SrcData.html"
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
  ~Cmnd_SrcData(void);



/*!
 search for a sub-tree in the xml-source defined by the given start-tag
 and generate the diagram-text for it

 @param [in]  source      xml-tree of the source to analyse
 @param [in]  replacement contains replacement-information to tailore
                          tags, attributes, texts and so on
 @param [out] diagram     container of the diagram describing text


 <br><br>
 @htmlinclude Cmnd_SrcData_text.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    20.12.2009   @I  Eckard Klotz
 @I refactoring of base-design
 @I first implementation
 @I_______________________________________________________
    08.04.2010   @I  Eckard Klotz
 @I update from tinyxml ver.2.5.3 to ver 2.6.1
 @I first changed nodetype-enum from XYZ to TINYXML_XYZ
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void text(XML_Node                       source,
           map<String_imp , String_imp >* replacement,
           list<String_imp>*              diagram);




/*!
 put the name of the root-tag of the given xml-source into the diagram

 @param [in]  source      xml-tree of the source to analyse
 @param [in]  replacement contains replacement-information to tailore
                          tags, attributes, texts and so on
 @param [out] diagram     container of the diagram describing text


 <br><br>
 @htmlinclude Cmnd_SrcData_tag.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    06.02.2010   @I  Eckard Klotz
 @I refactoring of base-design
 @I first implementation
 @I_______________________________________________________
    08.04.2010   @I  Eckard Klotz
 @I update from tinyxml ver.2.5.3 to ver 2.6.1
 @I first changed nodetype-enum from XYZ to TINYXML_XYZ
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void tag(XML_Node                     source,
          map<String_imp, String_imp>* replacement,
          list<String_imp>*            diagram);



/*!
 put the value of the given attribute if found in the root-tag of the given
 xml-source into the diagram.


 @param [in]  source         xml-tree of the source to analyse
 @param [in]  attributeName  name of the tag-attribute that contains the
                             searched information
 @param [in]  replacement    contains replacement-information to tailore
                             tags, attributes, texts and so on
 @param [out] diagram        container of the diagram describing text


 <br><br>
 @htmlinclude Cmnd_SrcData_attribute.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    06.02.2010   @I  Eckard Klotz
 @I refactoring of base-design
 @I first implementation
 @I_______________________________________________________
    08.04.2010   @I  Eckard Klotz
 @I update from tinyxml ver.2.5.3 to ver 2.6.1
 @I first changed nodetype-enum from XYZ to TINYXML_XYZ
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void attribute(XML_Node                       source,
                const String_imp&              attributeName,
                map<String_imp , String_imp >* replacement,
                list<String_imp>*              diagram);



// @param [in]  startTag    name of the tag that contains the sub-tree to delete

/*!
 search for a sub-tree in the xml-source defined by the given start-tag
 and delete it from the given source-tree

 @param [in]  source      xml-tree of the source to delete from


 <br><br>
 @htmlinclude Cmnd_SrcData_drop.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    10.02.2010   @I  Eckard Klotz
 @I refactoring of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void drop(XML_Node          source/*,
           const String_imp& startTag*/);



/*!
 use one special snipet if one sub-tree is not found

 @param [in]  source      xml-tree of the source to analyse
 @param [in]  startTag    name of the searched sub-tree
 @param [in]  alternative name of the snipet that schould be used instead
 @param [in]  replacement contains replacement-information to tailore
                          tags, attributes, texts and so on
 @param [out] diagram     container of the diagram describing text
 @param [in]  owner       snipet that has called this function if user-message
                          should be displayed in shell-window if an error was found
              <br>        or NULL if no message should be displayed


 <br><br>
 @htmlinclude Cmnd_SrcData_ifAbsent.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    07.02.2010   @I  Eckard Klotz
 @I refactoring of base-design
 @I first implementation
 @I_______________________________________________________
    19.10.2011   @I  Eckard Klotz
 @I bug parameter startTag and alternative weres used wrong
 @I the internal using of both string is now exchanged thus
    startTag will beused as the tag to search for and
    alternative is the snipet name to use if startTag
    is not found
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void ifAbsent(XML_Node                       source,
               const String_imp&              startTag,
               const String_imp&              alternative,
               map<String_imp , String_imp >* replacement,
               list<String_imp>*              diagram,
               SnippetExecution*              owner);


/*!
 use one special snipet for all sub-trees in the xml-source,
 if one sub-tree will be used from an other command it may be
 processed twice and if a sub-tree does not fit to the used
 snipet it will be processed wrong or it will be ignored completly

 @param [in]  source      xml-tree of the source to analyse
 @param [in]  snipetName  name of the snipet that schould be used
 @param [in]  replacement contains replacement-information to tailore
                          tags, attributes, texts and so on
 @param [out] diagram     container of the diagram describing text
 @param [in]  owner       snipet that has called this function if user-message
                          should be displayed in shell-window if an error was found
              <br>        or NULL if no message should be displayed


 <br><br>
 @htmlinclude Cmnd_SrcData_forAll.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    06.02.2010   @I  Eckard Klotz
 @I refactoring of base-design
 @I first implementation
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
 void forAll(XML_Node                       source,
             const String_imp&              snipetName,
             map<String_imp , String_imp >* replacement,
             list<String_imp>*              diagram,
             SnippetExecution*              owner);





/*!
 start a count-process through the sub tree of the given source-node
 to get the number of childes and sub childes and sub-sub childes ...
 with the given tag-id and save the result in the other given child-node

 @param [in]  source      xml-tree of the source to analyse
 @param [in]  tagToCount  name of the tag that should be counted in subTree
 @param [in]  tagToSave   name of sub child to save the count-result in


 <br><br>
 @htmlinclude Cmnd_SrcData_statistic.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    23.06.2013   @I  Eckard Klotz
 @I extending of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void statistic(XML_Node          source,
                const String_imp& tagToCount,
                const String_imp& tagToSave);






/*!
 check if given destination file is older as source to analyse
 to decide if the rest of the current sequence should be processed

 @param [in]  source   file and its path to analyse
 @param [in]  dstFile           file to generate
 @param [in]  dstpath           folder-path to generate in
 @param [in]  usedPathSeparator character or character-sequence used as
                                separator of folder-path definitions in
                                user-configuration
 @param [in]  osPathSeparator   character or character-sequence to be used
                                as separator of folder-path definitions in
                                current operation system of the computer
 @param [in]  rootStrings       container of root-strings to be used for
                                file-paths if defined by user
 @param [out]  result           will be set to false if compare-result is unequal


 <br><br>
 @htmlinclude Cmnd_SrcData_ifOlderAs.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    25.06.2013   @I  Eckard Klotz
 @I extending of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void ifOlderAs(const String_imp& source,
                const String_imp& dstFile,
                const String_imp& dstPath,
                const String_imp& usedPathSeparator,
                const String_imp& osPathSeparator,
                bool*             result);






/*!
 check if given destination file not already exists to decide
 if the rest of the current sequence should be processed

 @param [in]  dstFile           file to generate
 @param [in]  dstPath           folder-path to generate in
 @param [in]  usedPathSeparator character or character-sequence used as
                                separator of folder-path definitions in
                                user-configuration
 @param [in]  osPathSeparator   character or character-sequence to be used
                                as separator of folder-path definitions in
                                current operation system of the computer
 @param [out] result            will be set to false if compare-result is unequal


 <br><br>
 @htmlinclude Cmnd_SrcData_ifNotExist.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    25.06.2013   @I  Eckard Klotz
 @I extending of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void ifNotExist(const String_imp& dstFile,
                 const String_imp& dstPath,
                 const String_imp& usedPathSeparator,
                 const String_imp& osPathSeparator,
                 bool*             result);














 private:



/*!
 do the count-process through the subtree of the given source-node
 to get the number of childs and suchilds and sub-subchilds ...
 with the given tag-id and return the reusult

 @param [in]  source      xml-tree of the source to analyse
 @param [in]  tagToCount  name of the tag that should be counted in subTree

 @return Number of found elements

 <br><br>
 @htmlinclude Cmnd_SrcData_count.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    23.06.2013   @I  Eckard Klotz
 @I extending of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 int _count(XML_Node          source,
            const String_imp& tagToCount);


};


#ifndef DOXYGEN
#define USING_NAMESPACE using namespace
//}; USING_NAMESPACE CL_CMND_SRCDATA;
//}; USING_NAMESPACE CL_COMMAND ;
#undef USING_NAMESPACE
#endif //DOXYGEN


#endif //CMND_SRCDATA
