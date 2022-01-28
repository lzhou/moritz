/*!

 @file
 @brief    encapsulate the main process-sequence for all user-languages

 This file contains the definition of a class to encapsulate the work of
 the base-process to evaluate comments, line-changes and the source as well
 as the process to merge their results


 Copyright (C) 2008-2020 by Eckard Klotz.

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
    14.11.2011     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    14.11.2011...  @I Eckard Klotz
 @I Changes are documented in the comment of the changed element
 @TabEnd

*/
#ifndef COREFLOW_H
#define COREFLOW_H

#include <list>



#include "xml_DataModel.h"

#include "String_imp.h"
#include "app_tool.h"

//#include "ntn_spirit.h"      //to be replaced

#include "trn_context.h"
#include "trn_comment.h"
#include "trn_line.h"
#include "trn_source.h"
#include "merge.h"



#ifndef DOXYGEN
//namespace CL_COREFLOW {
#endif //DOXYGEN



/*!
 @brief managing of core-processes used for all parsing-processes.

 This processes are:
<br>  context-process to split comments and active part
<br>  comment-process to analyse special commands like the moritz
                      commands
<br>  line-process    to connect physical lines to locical lines and
                      to insert special indention-tokens for pythen
<br>  source-process  to analyse the active source code prepared by
                      the line-parser
<br>  merge-process   to merge the part-Results of comment-process,
                      line-process and source-process

 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    14.11.2011   @I  Eckard Klotz
 @I re-factoring to make main-file content smaler and better
    to maintain
 @I convert parts of the main-file into a methods of
    a class
 @I_______________________________________________________
    03.06.2012   @I  Eckard Klotz
 @I re-factoring of splitting comments and active code
 @I adding the context process
 @I_______________________________________________________
    12.10.2013      @I  Eckard Klotz
 @I re-factoring for better maintenance
 @I the own method _readTextFile will be dropped since
    it has the same functionality like the function readTextFile
    in the module app_tool. It makes no sense to maintain
    the same function in 2 modules.
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd


*/
class CoreFlow
{
 public:

/*!
 constructor

 @param [in] configuration     xml-part that contains the
                               user-defined configuration
 @param [in] usedPathSeparator character or character-sequence used as
                               separator of folder-path definitions in
                               user-configuration
 @param [in] osPathSeparator   character or character-sequence to be used
                               as separator of folder-path definitions in
                               current operation system of the computer
 @param [in] rootStrings       container of root-strings to be used for
                               file-paths if defined by user
 <br><br>
 @htmlinclude ./des/CoreFlow_CoreFlow.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    14.11.2011   @I  Eckard Klotz
 @I re-factoring to make main-file content smaller and better
    to maintain
 @I convert parts of the main-file into a methods of
    a class
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
  CoreFlow(XML_Node                    configuration,
           String_imp&                 usedPathSeparator,
           String_imp&                 osPathSeparator,
           map<String_imp,String_imp>& rootStrings);


/*!
 destructor
 <br><br>
 @htmlinclude ./des/CoreFlow__CoreFlow.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    14.11.2011   @I  Eckard Klotz
 @I re-factoring to make main-file content smaler and better
    to maintain
 @I convert parts of the main-file into a methods of
    a class
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  virtual ~CoreFlow();





/*!
 evaluate an given text and save the results as xml-files

 @param [in] configuration         user-configuration of the text to analyse
                                   containing the name of the file
                                   and things like doNotSkip and so on...
 @param [in] destinationPath       location folder to save the xml-file in
 @param [in] sourceID              file-name of analysed source-file
 @param [in] sourceRelativePath    relative folder-path of analysed source-file
 @param [in] sourceAbsolutePath    absolute folder-path of analysed source-file
 @param [in] variant               name of the directive-varant to use



 <br><br>
 @htmlinclude ./des/CoreFlow_analyse.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    14.11.2011   @I  Eckard Klotz
 @I re-factoring to make main-file content smaler and better
    to maintain
 @I convert parts of the main-file into a methods of
    a class
 @I_______________________________________________________
     03.06.2013      @I  Eckard Klotz
 @I re-factoring
 @I use of replacement-mechanism for separators in path-strings
 @I_______________________________________________________
     03.06.2013      @I  Eckard Klotz
 @I re-factoring
 @I use of replacement-mechanism for separators in path-strings
 @I_______________________________________________________
    12.10.2013      @I  Eckard Klotz
 @I bug: if a file contains only one line with out a line-brake
         at the end the read-loop is endless since end-of-file
         will not be detected.
 @I the own method _readTextFile will be used any more since
    it has the same functionality like the function readTextFile
    in the module app_tool what was already corrected.
 @I_______________________________________________________
    12.10.2014   @I  Eckard Klotz
 @I extending function to save source location in destination-file
 @I added parameters for relative and absolute folder-location
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  void analyse(      XML_Node    configuration,
               const String_imp& destinationPath,
               const String_imp& sourceID,
               const String_imp& sourceRelativePath,
               const String_imp& sourceAbsolutePath,
               const String_imp& variant = "");





/*!
 @brief transfer a association model into a xml-tree

 @deprecated this function should only be used while tinyxml is still in use
             and only for existing cases where absolutely necessary

 @param context association model that contains a filled fellow-DF tree
 @param keyWord set of texts which node-tags should be KeyWord
 @param keyChar set of texts which node-tags should be KeyChr

 @return a tinyxml document with the content of the fellow-DF tree
         of the given association model

 <br><br>
 @htmlinclude ./des/CoreFlow_analyse.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    01.05.2017   @I  Eckard Klotz
 @I change from tinyxml to associations
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
/// @todo this method will not be used any more without using TynyXML but will be replaced by the storeContext
 XML_DataModel* context2xml(TiPa_DataModel*  context,
                            set<String_imp>* keyWord,
                            set<String_imp>* keyChar);



 bool storeContext(TiPa_DataModel*  context,
                   set<String_imp>* keyWord,
                   set<String_imp>* keyChar,
                   const char* destination);





/*!
 evaluate an given text and save the results as xml-files

 @param [in] dataModel             management-object that creates and deletes associations and data-objects
 @param [in] sourceText            text to analyse
 @param [in] destinationPath       folder to save result-file
 @param [in] destinationName       base-name of the result-file
 @param [in] destinationAttachment name attachment of the result-file
 @param [in] sourceID              file-name of analysed source-file
 @param [in] sourceRelativePath    relative folder-path of analysed source-file
 @param [in] sourceAbsolutePath    absolute folder-path of analysed source-file

 @return success of process-sequence
  <br> true => all processes where able to parse the source or to merge the results
  <br> fale => one processes failed to parse the source or to merge the results


 <br><br>
 @htmlinclude ./des/CoreFlow_doSequence.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    20.11.2011   @I  Eckard Klotz
 @I re-factoring to make main-file content smaler and better
    to maintain
 @I convert parts of the main-file into a methods of
    a class
 @I_______________________________________________________
    12.10.2014   @I  Eckard Klotz
 @I extending function to save source location in destination-file
 @I added parameters for relative and absolute folder-location
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  bool doSequence(      TiPa_DataModel*  dataModel,
                        String_imp*      sourceText,
                  const String_imp&      destinationPath,
                  const String_imp&      destinationName,
                  const String_imp&      destinationAttachment,
                  const String_imp&      sourceID,
                        String_imp       sourceRelativePath,
                        String_imp       sourceAbsolutePath);



/*!
 check if the xml-tree has to be completed by loading additional xml-files,
 load this additional file and do the competetion.

 @param [in] destinationPath  path of files to search for
 @param [in] source           leading file-name of sources to search for

 @return content of file or empty string


 <br><br>
 @htmlinclude ./des/CoreFlow_checkNewSource.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    02.06.2011   @I  Eckard Klotz
 @I re-factoring: split xml-configuration into language dependend and user-dependent parts
 @I first implementation
 @I_______________________________________________________
    14.11.2011   @I  Eckard Klotz
 @I re-factoring to make main-file content smaler and better
    to maintain
 @I convert the function of the main-file into a method of
    a class
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
bool checkNewSource(const String_imp& destinationPath,
                    const String_imp& source);





/*!
 check if the given text can be parsed by the user parser-sequence

 @param [in] text       object to test

 @return true  -> text can be parsed
 <br>    false -> text can not be parsed


 <br><br>
 @htmlinclude ./des/CoreFlow_checkTextToParse.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    27.11.2011   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
bool checkTextToParse(String_imp text);


 protected:

 private:

/*!
 creating and configuration of an context-process object

 @param [in]  configuration    xml-part that contains the
                               user-defined configuration
 @param [in]  process          name of the root-tag to use
 @param [out] savePartResult   user-config to save part-result
 <br>                          true ==> part-result should be saved as file
 <br>                          false==> part-result should not be saved
 @param [out] attachment       file attachment for the file to save the
                               part-result in

 @return configured object ready to use


 <br><br>
 @htmlinclude ./des/CoreFlow_createContextProcess.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    03.06.2012   @I  Eckard Klotz
 @I re-factoring of splitting comments and active code
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
    12.10.2013   @I  Eckard Klotz
 @I bug: if a file contains only one line with out a line-brake
         at the end the read-loop is endless since end-of-file
         will not be detected.
 @I the own method _readTextFile will be used any more since
    it has the same functionality like the function readTextFile
    in the module app_tool what was already corrected.
 @I_______________________________________________________
    12.10.2013      @I  Eckard Klotz
 @I bug: xml-comments lead to crash
 @I xml-iterations will be done by using TixmlNode instead
    of TiXmlElement,
    as first action in the loop a macro checks if the
    current-element is a xml-comment and forces immediately
    the start of the next loop
 @I_______________________________________________________
    17.10.2013   @I  Eckard Klotz
 @I re-factoring
 @I deactivated using of EndMarker since it is not used
    anymore
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
Prcs_Trn_Context* _createContextProcess(      XML_Node    configuration,
                                        const String_imp& process,
                                              bool*       savePartResult,
                                              String_imp* attachment);




/*!
 creating and configuratin of an comment-process object

 @param [in] configuration     xml-part that contains the
                               user-defined configuration
 @param [out] savePartResult   user-config to save part-result
 <br>                          true ==> part-result should be saved as file
 <br>                          false==> part-result should not be saved
 @param [out] attachment       file attachment for the file to save the
                               part-result in

 @return configured object ready to use


 <br><br>
 @htmlinclude ./des/CoreFlow_createCommentProcess.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    ... 09.2009   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
    12.01.2010   @I  Eckard Klotz
 @I implementing new features
 @I configuration of saving part-results
 @I_______________________________________________________
    13.08.2010   @I  Eckard Klotz
 @I re-factoring to make code smaler and better to maintain
    and to implement a central output of config-file errors
 @I detail xml-operations moved to a new help-library tixml_ao
 @I_______________________________________________________
    14.11.2011   @I  Eckard Klotz
 @I re-factoring to make main-file content smaler and better
    to maintain
 @I convert the function of the main-file into a method of
    a class
 @I_______________________________________________________
    04.11.2012   @I  Eckard Klotz
 @I bug normalization of key-words is not working anymore
    since implementation of context-parser
 @I normalization of key-words moved from comment-process
    to source-process
 @I_______________________________________________________
     03.06.2013  @I  Eckard Klotz
 @I re-factoring
 @I use of replacement-mechanism for separators in path-strings
 @I_______________________________________________________
    09.06.2013   @I  Eckard Klotz
 @I re-factoring
 @I use of root-definition for relative path-strings
 @I_______________________________________________________
    12.10.2013   @I  Eckard Klotz
 @I bug: if a file contains only one line with out a line-brake
         at the end the read-loop is endless since end-of-file
         will not be detected.
 @I the own method _readTextFile will be used any more since
    it has the same functionality like the function readTextFile
    in the module app_tool what was already corrected.
 @I_______________________________________________________
    12.10.2013      @I  Eckard Klotz
 @I bug: xml-comments lead to crash
 @I xml-iterations will be done by using TixmlNode instead
    of TiXmlElement,
    as first action in the loop a macro checks if the
    current-element is a xml-comment and forces immediately
    the start of the next loop
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
Prcs_Trn_Comment* _createCommentProcess(XML_Node       configuration,
                                        bool*          savePartResult,
                                        String_imp*    attachment);



/*!
 creating and configuratin of an line-process object

 @param [in] configuration     xml-part that contains the
                               user-defined configuration
 @param [out] savePartResult   user-config to save part-result
 <br>                          true ==> part-result should be saved as file
 <br>                          false==> part-result should not be saved
 @param [out] attachment       file attachment for the file to save the
                               part-result in

 @return configured object ready to use


 <br><br>
 @htmlinclude ./des/CoreFlow_createLineProcess.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    ... 09.2009   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
    12.01.2010   @I  Eckard Klotz
 @I implementing new features
 @I configuration of saving part-results
 @I_______________________________________________________
    13.08.2010   @I  Eckard Klotz
 @I re-factoring to make code smaler and better to maintain
    and to implement a central output of config-file errors
 @I detail xml-operations moved to a new help-library tixml_ao
 @I_______________________________________________________
    14.11.2011   @I  Eckard Klotz
 @I re-factoring to make main-file content smaler and better
    to maintain
 @I convert the function of the main-file into a method of
    a class
 @I_______________________________________________________
    03.06.2013   @I  Eckard Klotz
 @I re-factoring
 @I use of replacement-mechanism for separators in path-strings
 @I_______________________________________________________
    09.06.2013   @I  Eckard Klotz
 @I re-factoring
 @I use of root-definition for relative path-strings
 @I_______________________________________________________
    12.10.2013   @I  Eckard Klotz
 @I bug: if a file contains only one line with out a line-brake
         at the end the read-loop is endless since end-of-file
         will not be detected.
 @I the own method _readTextFile will be used any more since
    it has the same functionality like the function readTextFile
    in the module app_tool what was already corrected.
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
Prcs_Trn_Line* _createLineProcess(XML_Node       configuration,
                                  bool*          savePartResult,
                                  String_imp*    attachment);




/*!
 creating and configuratin of an source-process object

 @param [in] configuration     xml-part that contains the
                               user-defined configuration
 @param [in] process           name of the root-tag to use
 @param [out] savePartResult   user-config to save part-result
 <br>                          true ==> part-result should be saved as file
 <br>                          false==> part-result should not be saved
 @param [out] attachment       file attachment for the file to save the
                               part-result in

 @return configured object ready to use


 <br><br>
 @htmlinclude ./des/CoreFlow_createSourceProcess.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    ... 09.2009   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
    12.01.2010   @I  Eckard Klotz
 @I implementing new features
 @I configuration of saving part-results
 @I_______________________________________________________
    13.08.2010   @I  Eckard Klotz
 @I re-factoring to make code smaler and better to maintain
    and to implement a central output of config-file errors
 @I detail xml-operations moved to a new help-library tixml_ao
 @I_______________________________________________________
    14.11.2011   @I  Eckard Klotz
 @I re-factoring to make main-file content smaler and better
    to maintain
 @I convert the function of the main-file into a method of
    a class
 @I_______________________________________________________
    04.11.2012   @I  Eckard Klotz
 @I bug normalization of key-words is not working anymore
    since implementation of context-parser
 @I normalization of key-words moved from comment-process
    to source-process
 @I_______________________________________________________
    03.06.2013   @I  Eckard Klotz
 @I re-factoring
 @I use of replacement-mechanism for separators in path-strings
 @I_______________________________________________________
    09.06.2013   @I  Eckard Klotz
 @I re-factoring
 @I use of root-definition for relative path-strings
 @I_______________________________________________________
    12.10.2013   @I  Eckard Klotz
 @I bug: if a file contains only one line with out a line-brake
         at the end the read-loop is endless since end-of-file
         will not be detected.
 @I the own method _readTextFile will be used any more since
    it has the same functionality like the function readTextFile
    in the module app_tool what was already corrected.
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
Prcs_Trn_Source* _createSourceProcess(      XML_Node    configuration,
                                      const String_imp& process,
                                            bool*       savePartResult,
                                            String_imp* attachment);

/*!
 creating and configuratin of an merge-process object

 @param [in] configuration xml-part that contains the
                           user-defined configuration

 @return configured object ready to use


 <br><br>
 @htmlinclude ./des/CoreFlow_createMergeProcess.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    10.01.2010   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
    13.08.2010   @I  Eckard Klotz
 @I re-factoring to make code smaler and better to maintain
    and to implement a central output of config-file errors
 @I detail xml-operations moved to a new help-library tixml_ao
 @I_______________________________________________________
    14.11.2011   @I  Eckard Klotz
 @I re-factoring to make main-file content smaler and better
    to maintain
 @I convert the function of the main-file into a method of
    a class
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
Prcs_Trn_Merge* _createMergeProcess(XML_Node   configuration);











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
 struct Att
 {
  String_imp                 UsedPathSeparator;
  String_imp                 OsPathSeparator;
  map<String_imp,String_imp> RootStrings;

  Prcs_Trn_Context*          Context_prcs;
  Prcs_Trn_Source*           Source_prcs;
  Prcs_Trn_Line*             Line_prcs;
  Prcs_Trn_Comment*          Comment_prcs;

  bool                       SaveContextPart;
  bool                       SaveCommentPart;
  bool                       SaveLinePart;
  bool                       SaveSourcePart;

  String_imp                 CntxtAttachment;
  String_imp                 CmntAttachment;
  String_imp                 LineAttachment;
  String_imp                 CodeAttachment;

  Prcs_Trn_Merge*            Merge_prcs;

   Att(void):
    UsedPathSeparator(""),
    OsPathSeparator  (""),
    Context_prcs     (nullptr),
    Source_prcs      (nullptr),
    Line_prcs        (nullptr),
    Comment_prcs     (nullptr),
    SaveContextPart  (false),
    SaveCommentPart  (false),
    SaveLinePart     (false),
    SaveSourcePart   (false),
    CntxtAttachment  (""),
    CmntAttachment   (""),
    LineAttachment   (""),
    CodeAttachment   (""),
    Merge_prcs       (nullptr)
   {
   }

   Att(const Att& att):
    UsedPathSeparator(att.UsedPathSeparator),
    OsPathSeparator  (att.OsPathSeparator  ),
    RootStrings      (att.RootStrings      ),
    Context_prcs     (att.Context_prcs     ),
    Source_prcs      (att.Source_prcs      ),
    Line_prcs        (att.Line_prcs        ),
    Comment_prcs     (att.Comment_prcs     ),
    SaveContextPart  (att.SaveContextPart  ),
    SaveCommentPart  (att.SaveCommentPart  ),
    SaveLinePart     (att.SaveLinePart     ),
    SaveSourcePart   (att.SaveSourcePart   ),
    CntxtAttachment  (att.CntxtAttachment  ),
    CmntAttachment   (att.CmntAttachment   ),
    LineAttachment   (att.LineAttachment   ),
    CodeAttachment   (att.CodeAttachment   ),
    Merge_prcs       (att.Merge_prcs       )
   {
   }

   Att& operator= (const Att& att)
   {
    UsedPathSeparator = att.UsedPathSeparator;
    OsPathSeparator   = att.OsPathSeparator  ;
    RootStrings       = att.RootStrings      ;
    Context_prcs      = att.Context_prcs     ;
    Source_prcs       = att.Source_prcs      ;
    Line_prcs         = att.Line_prcs        ;
    Comment_prcs      = att.Comment_prcs     ;
    SaveContextPart   = att.SaveContextPart  ;
    SaveCommentPart   = att.SaveCommentPart  ;
    SaveLinePart      = att.SaveLinePart     ;
    SaveSourcePart    = att.SaveSourcePart   ;
    CntxtAttachment   = att.CntxtAttachment  ;
    CmntAttachment    = att.CmntAttachment   ;
    LineAttachment    = att.LineAttachment   ;
    CodeAttachment    = att.CodeAttachment   ;
    Merge_prcs        = att.Merge_prcs       ;
    return(*this);
   };

  ~Att(void)
  {
   RootStrings.clear();
  }
 }Att;

};

#ifndef DOXYGEN
#define USING_NAMESPACE using namespace
//}; USING_NAMESPACE CL_COREFLOW;
#undef  USING_NAMESPACE
#endif //DOXYGEN

#endif//COREFLOW_H
