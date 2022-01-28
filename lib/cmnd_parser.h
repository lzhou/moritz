/*!

 @file
 @brief  definition of a collection of snippet-commands to parse text

 This file contains special snippet-commands to parse tag-identifiers,
 attribute-values or the content of xml text-elements to transfer
 it into a new detailed xml-tree

 Copyright (C) 2008-2018 by Eckard Klotz.

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
    01.08.2013     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    01.08.2013...  @I Eckard Klotz
 @I Changes are documented in the comment of the changed element
 @TabEnd

*/
#ifndef CMND_PARSER_H
#define CMND_PARSER_H


#include "xml_DataModel.h"


#include "trn_source.h"


#include "command.h"









#ifndef DOXYGEN
//namespace CL_COMMAND {
//namespace CL_CMND_PARSER {
#endif //DOXYGEN
















/*!
 @brief Concrete command to construct Snipet-content by parsing text.

 @history
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    01.08.2013   @I  Eckard Klotz @I First Implementation @I
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/

class Cmnd_Parser:public Cmnd_Common
{
 public:




/*!
 construktor
 <br><br>
 @htmlinclude Cmnd_Parser_Cmnd_Parser.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    01.08.2013   @I  Eckard Klotz
 @I refactoring of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  Cmnd_Parser(void);











/*!
 destruktor
 <br><br>
 @htmlinclude Cmnd_Parser__Cmnd_Parser.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    01.08.2013   @I  Eckard Klotz
 @I refactoring of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  ~Cmnd_Parser(void);





/*!
 configure the parser and define its rules

 @param [in] configuration xml-configuration of the parser
 @param [in] grammar       textual definition of parser-rules

 <br><br>
 @htmlinclude Cmnd_Parser_setParser.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    01.08.2013   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void setParser (XML_Node          configuration,
                 const String_imp& grammar);


/*!
 use the parser to analyse the given text and create a
 xml based parser-tree as result

 @param [in]  text    text to parse
 @param [in]  rule    identifier of root-rule used to parse
 @param [out] result  root of parser-tree that contains the result of parsing

 <br><br>
 @htmlinclude Cmnd_Parser_useParser.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    04.08.2013   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void useParser (const String_imp& text,
                 const String_imp& rule,
                 XML_Node*         result);

















/*!

 configure how to manipulate with file-folder strings

 @param [in] usedPathSeparator character or character-sequence used as
                               separator of folder-path definitions in
                               user-configuration
 @param [in] osPathSeparator   character or character-sequence to be used
                               as separator of folder-path definitions in
                               current operation system of the computer
 @param [in] rootStrings       container of root-strings to be used for
                               file-paths if defined by user

 <br><br>
 @htmlinclude Cmnd_Parser_setFolderRoots.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    10.08.2013   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd

*/
static void setFolderRoots(const String_imp&                 usedPathSeparator,
                           const String_imp&                 osPathSeparator,
                           const map<String_imp,String_imp>& rootStrings);






 protected:

 private:
/*!
 creating and configuration of the parser-process object

 @param [in] configuration     xml-part that contains the
                               user-defined configuration
 @param [in] grammar           grammar definition used by the parser

 @return configured parser object ready to use

 <br><br>
 @htmlinclude Cmnd_Parser_createSourceProcess.html

 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
 @I re-factoring of base-design
 @I first implementation by copying and modifying
    a method from MuLanPa
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
Prcs_Trn_Source* _createSourceProcess(XML_Node          configuration,
                                      const String_imp& grammar);



/*!
 @brief common object-attributes

 to put the attributes into a structure makes it possible to
 set them apart from local variables and parameters of a method
 in the source-code by using the struct-name as prefix.

 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    13.09.2011   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
    03.06.2013   @I  Eckard Klotz
 @I re-factoring
 @I use of replacement-mechanism for separators in path-strings
 @I_______________________________________________________
    09.06.2013   @I  Eckard Klotz
 @I re-factoring
 @I use of root-definition for relative path-strings
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/

  static String_imp                 UsedPathSeparator;
  static String_imp                 OsPathSeparator;
  static map<String_imp,String_imp> RootStrings;

  static String_imp                 NotationCfg;
  static Prcs_Trn_Source*           Parser;


};





#ifndef DOXYGEN
#define USING_NAMESPACE  using namespace
//}; USING_NAMESPACE CL_CMND_PARSER ;
//}; USING_NAMESPACE CL_COMMAND ;
#undef  USING_NAMESPACE
#endif //DOXYGEN




#endif //CMND_PARSER_H

