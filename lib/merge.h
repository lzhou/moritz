/*!

 @file
 @brief  definition of backus-naur-form

 This file contains the definition of a tool that merges the content of the
 3 (or more) result-files of the transform-processes which describe the
 same source or script.

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
    25.12.2009     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    25.12.2009...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/
#ifndef Merge_H
#define Merge_H

#include <iostream>
#include <list>



#include "transform.h"
#include "String_imp.h"

using namespace std;


#ifndef DOXYGEN
//namespace CL_PROCESS {
//namespace CL_TRN_MERGE {
#endif //DOXYGEN


const String_imp  COMMAND = "__command__";
const String_imp  BLOCK   = "__block__";
const String_imp  COMMENT = "Comment";
const String_imp  CODE    = "__code__";
const String_imp  LINE    = "__line__";
const String_imp  SPACE   = "sp";




/*!
 @brief abstract parser-action

 the analysis of every source or script-file produces 3 (or more)
 xml-files which contain different aspects of the original content.
 the Prcs_Trn_Merge-tool has to reassemble the three xml-trees again.

 @history
 @TabBegin
  <b>date</b>       @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    25.12.2009   @I  Eckard Klotz @I First Implementation @I
 @I_______________________________________________________
    18.04.2010   @I  Eckard Klotz
    @I implementation of parsing of comment-commands
    @I class will now be derived from Prcs_Transformation
 @I_______________________________________________________
                     @I               @I              @I
 @TabEnd
*/
class Prcs_Trn_Merge
{
 public:


  typedef  struct MergeConfig
  {
   bool                              Use;
   int                               LimitToImportBehind;
   int                               LimitToImportBefore;
   map <String_imp, set<String_imp> >ImportLevel;


   /// @brief default constructor
   MergeConfig(void):
    Use(false),
    LimitToImportBehind(-1),
    LimitToImportBefore(-1)
   {};
   /*!
    @brief copy constructor
    @param [in] src object to copy
   */
   MergeConfig(const MergeConfig& src):
    Use                (src.Use                ),
    LimitToImportBehind(src.LimitToImportBehind),
    LimitToImportBefore(src.LimitToImportBefore),
    ImportLevel        (src.ImportLevel        )
   {};
   /*!
    @brief assignment operator
    @param [in] src object to copy
    @return copied object
   */
   MergeConfig& operator = (const MergeConfig& src)
   {
    Use                 = src.Use                ;
    LimitToImportBehind = src.LimitToImportBehind;
    LimitToImportBefore = src.LimitToImportBefore;
    ImportLevel         = src.ImportLevel        ;
    return(*this);
   };
   /// @brief destructor
   ~MergeConfig(void)
   {
    ImportLevel.clear();
   };

  }MergeConfig;






 typedef struct SpecialCommentData
 {
  String_imp StartsWith;
  String_imp EndsWith;
  /// @brief default constructor
  SpecialCommentData(void):
   StartsWith(""),
   EndsWith("")
  {};
  /*!
   @brief initializing constructor
  */
  SpecialCommentData(const String_imp& att1, const String_imp& att2):
   StartsWith(att1),
   EndsWith(att2)
  {};
  /*!
   @brief copy constructor
   @param [in] src object to copy
  */
  SpecialCommentData(const SpecialCommentData& src):
   StartsWith(src.StartsWith),
   EndsWith(src.EndsWith)
  {};
  /*!
   @brief assignment operator
   @param [in] src object to copy
   @return copied object
  */
  SpecialCommentData& operator = (const SpecialCommentData& src)
  {
   StartsWith = src.StartsWith;
   EndsWith = src.EndsWith;
   return(*this);
  };
  /// @brief destructor
  ~SpecialCommentData(void)
  {
   StartsWith.clear();
   EndsWith.clear();
  };
 }SpecialCommentData;



  typedef Prcs_Transformation::DataAssociation DataAssociation;





/*!
 default constructor

 <br><br>
 @htmlinclude ./des/Prcs_Trn_Merge_Prcs_Trn_Merge.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    25.12.2009   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 Prcs_Trn_Merge();



/*!
 constructor

 @param useComment
 @param limitToImportBeforeComment
 @param limitToImportBehindComment
 @param importLevelComment
 @param useLine
 @param limitToImportBeforeLine
 @param limitToImportBehindLine
 @param importLevelLine
 @param useCommand
 @param limitToImportBeforeCommand
 @param limitToImportBehindCommand
 @param importLevelCommand


 <br><br>
 @htmlinclude ./des/Prcs_Trn_Merge_Prcs_Trn_Merge_001.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    31.12.2009   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
    22.04.2010   @I  Eckard Klotz
 @I implementing parser for special commands in comments
 @I define a string to mark the end of the text to pars
 @I_______________________________________________________
    17.10.2013   @I  Eckard Klotz
 @I re-factoring
 @I deactivated using of Att.TokenEndMarker since it is
    not used anymore
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 Prcs_Trn_Merge(bool                        useComment,
                int                         limitToImportBeforeComment,
                int                         limitToImportBehindComment,
                String_imp&                 importLevelComment,
                bool                        useLine,
                int                         limitToImportBeforeLine,
                int                         limitToImportBehindLine,
                String_imp&                 importLevelLine,
                bool                        useCommand,
                int                         limitToImportBeforeCommand,
                int                         limitToImportBehindCommand,
                map<String_imp,String_imp>  importLevelCommand);







/*!
 destructor

 <br><br>
 @htmlinclude ./des/Prcs_Trn_Merge__Prcs_Trn_Merge.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    25.12.2009   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  ~Prcs_Trn_Merge();










/*!
 anlyse a parser-tree or its sub tree to generate a list of all
 sub-elements

 @param [in]  contextModel management-object that creates and deletes associations and data-objects
 @param [in]  codeTree     base xml-content, its content will be
                           extended by the content of the other files
 @param [in]  lineTree     xml-content of line-process result
                           that should be merged in
 @param [in]  comment      xml-content of comment-process result
                           that should be merged in

 @return xml-tree with the extended content

 @htmlinclude ./des/Prcs_Trn_Merge_merge.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    25.12.2009      @I  Eckard Klotz
 @I help-function to avoid recursive search-algorithms in applications
 @I first implementation
 @I_______________________________________________________
    18.04.2010      @I  Eckard Klotz
 @I implementation of parser to analyse comment-commands
 @I rename this function from analyse to merge since this
    class is now derived from Prcs_Transform with an other
    definition of the method analyse
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
  TiPa_DataModel* merge(TiPa_DataModel* codeTree,
                                     TiPa_DataModel* lineDoc,
                                     TiPa_DataModel* commentDoc);
*/
  void merge(TiPa_DataModel* dataModel,
             const char*     code,
             const char*     line,
             const char*     comment);

 protected :

 private:





/*!
 search the place for an given xml-element in the destination
 xml-structure to include there

 @param [in] destination         xml-element to include in
 @param [in] import              xml-element to be included
 @param [in] limitToImportBehind user-cofiguration of max-distance to import behind
 @param [in] limitToImportBefore user-cofiguration of max-distance to import before
 @param [in] importLevel         user-configuration of tag-names to put new-elemts in

 @return next xml-element to import

 <br><br>
 @htmlinclude ./des/Prcs_Trn_Merge__assemble.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    26.12.2009   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
    08.04.2010   @I  Eckard Klotz
 @I update from tinyxml ver.2.5.3 to ver 2.6.1
 @I first changed nodetype-enum from XYZ to TINYXML_XYZ
 @I_______________________________________________________
    09.08.2010   @I  Eckard Klotz
 @I re-factoring
 @I split into subfunctions for easier maintainment
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
DataAssociation* _assemble(DataAssociation* destination,
                           DataAssociation* import,
                           int              limitToImportBehind,
                           int              limitToImportBefore,
                           set<String_imp>* importLevel);



/*!
 search the place for an given xml-element in child-values of the destination
 xml-structure to include there

 @param [in] destination         xml-element to include in
 @param [in] import              xml-element to be included
 @param [in] limitToImportBehind user-cofiguration of max-distance to import behind
 @param [in] limitToImportBefore user-cofiguration of max-distance to import before
 @param [in] importLevel         user-configuration of tag-names to put new-elemts in

 @return next xml-element to import

 <br><br>
 @htmlinclude ./des/Prcs_Trn_Merge__assembleDownwards.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    09.08.2010   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
DataAssociation* _assembleDownwards(DataAssociation* destination,
                                            DataAssociation* import,
                                            int                      limitToImportBehind,
                                            int                      limitToImportBefore,
                                            set<String_imp>*         importLevel);




/*!
  include the given xml-element before the destination

 @param [in] destination         xml-element to include in
 @param [in] import              xml-element to be included
 @param [in] importLevel         user-configuration of tag-names to put new-elemts in

 @return next xml-element to import

 <br><br>
 @htmlinclude ./des/Prcs_Trn_Merge__assembleBefore.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    09.08.2010   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
DataAssociation* _assembleBefore(DataAssociation* destination,
                                         DataAssociation* import,
                                         set<String_imp>*         importLevel);


/*!
 include the given xml-element between a two childes of the given destination

 @param [in] destination         xml-element to include in
 @param [in] import              xml-element to be included
 @param [in] limitToImportBehind user-configuration of max-distance to import behind
 @param [in] limitToImportBefore user-configuration of max-distance to import before
 @param [in] differenceBehind    existing distance to child for importing behind
 @param [in] differenceBefore    existing distance to child for importing before
 @param [in] importLevel         user-configuration of tag-names to put new-elements in

 @return next xml-element to import

 <br><br>
 @htmlinclude ./des/Prcs_Trn_Merge__assembleBetween.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    09.08.2010   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
DataAssociation* _assembleBetween(DataAssociation* destination,
                                          DataAssociation* import,
                                          int                      limitToImportBehind,
                                          int                      limitToImportBefore,
                                          int                      differenceBehind,
                                          int                      differenceBefore,
                                          set<String_imp>*         importLevel);


/*!
  include the given xml-element behind the destination

 @param [in] destination         xml-element to include in
 @param [in] import              xml-element to be included
 @param [in] importLevel         user-configuration of tag-names to put new-elements in

 @return next xml-element to import

 <br><br>
 @htmlinclude ./des/Prcs_Trn_Merge__assembleBehind.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    09.08.2010   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
    26.12.2013   @I  Eckard Klotz
 @I bug last comments behind last command are added in wrong
    order
 @I before pasting next comment after command a check is done
    if already comments are existing behind and if so the this
    comment will be added behind the last existing.
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
DataAssociation* _assembleBehind(DataAssociation* destination,
                                         DataAssociation* import,
                                         set<String_imp>*         importLevel);






/*!
 buffers the first element of a block defined by a special command
 or puts all elements of this block under the block-element

 @param [in] import     current element that may be a special-command
                        to begin or end a block
 @param [in] blockBegin first code element of the block o NULL if
                        end of block is reached


 <br><br>
 @htmlinclude ./des/Prcs_Trn_Merge__assembleDownwards.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    09.08.2010   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
    23.06.2013   @I  Eckard Klotz
 @I re-factoring warning-output
 @I a lonely mrtz_endBlock will be mentioned with its line-number now
 @I_______________________________________________________
                 @I               @I              @I
    29.12.2015   @I  Eckard Klotz
 @I implementation of new parser TiPa
 @I mrtz_endBlock will be deleted again after its merge
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
void  _assembleBlock(DataAssociation* import,
                     DataAssociation* blockBegin = nullptr);














/*!
 compare the text-position of two xml-elements

 @param [in] unknown xml-element that defines the unknown point
 @param [in] fix     xml-element that defines the fix-point

 @return -1 ==> unknown in front of fix
 @return  0 ==> unknown and fix on the same place
 @return +1 ==> unknown behind   of fix

 <br><br>
 @htmlinclude ./des/Prcs_Trn_Merge__compare.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    26.12.2009   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
    08.04.2010   @I  Eckard Klotz
 @I update from tinyxml ver.2.5.3 to ver 2.6.1
 @I first changed nodetype-enum from XYZ to TINYXML_XYZ
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 signed int _compare(DataAssociation* unknown, DataAssociation* fix);





/*!
 search first inner child-element without own childs (except a text)

 @param [in] parent  xml-element that defines the start-parent

 @return found sub-child

 <br><br>
 @htmlinclude ./des/Prcs_Trn_Merge__searchFirstLeafChild.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    29.12.2009   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
    08.04.2010   @I  Eckard Klotz
 @I update from tinyxml ver.2.5.3 to ver 2.6.1
 @I first changed node-type enum from XYZ to TINYXML_XYZ
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 DataAssociation* _searchFirstLeafChild(DataAssociation* parent);




/*!
 search last inner child-element without own childes (except a text)

 @param [in] parent  xml-element that defines the start-parent

 @return found sub-child

 <br><br>
 @htmlinclude ./des/Prcs_Trn_Merge__searchLastLeafChild.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    26.12.2009   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
    08.04.2010   @I  Eckard Klotz
 @I update from tinyxml ver.2.5.3 to ver 2.6.1
 @I first changed node-type enum from XYZ to TINYXML_XYZ
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 DataAssociation* _searchLastLeafChild(DataAssociation* parent);







/*!
 search first inner child-element without own childes (except a text)
 or that is listed as import-level

 @param [in] parent      xml-element that defines the start-parent
 @param [in] importLevel user-configuration of tag-names to put new-elements in
 @param [in] import      xml-element to be included

 @return found sub-child

 <br><br>
 @htmlinclude ./des/Prcs_Trn_Merge__searchFirstImportChild.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    31.12.2009   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
    08.04.2010   @I  Eckard Klotz
 @I update from tinyxml ver.2.5.3 to ver 2.6.1
 @I first changed node-type enum from XYZ to TINYXML_XYZ
 @I_______________________________________________________
    26.10.2014   @I  Eckard Klotz
 @I bug two following comments will be merged in wrong order
    since this function skips the evaluation of already existing
    comments for importing comments
 @I by adding the node to import as parameter this method is able
    to differ between commands and comments to import and skips
    the evaluation of comments only for importing commands
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 DataAssociation* _searchFirstImportChild(DataAssociation* parent,
                                          set<String_imp>* importLevel,
                                          DataAssociation* import);




/*!
 search last inner child-element without own childes (except a text)
 or that is listed as import-level

 @param [in] parent      xml-element that defines the start-parent
 @param [in] importLevel user-configuration of tag-names to put new-elements in
 @param [in] import      xml-element to be included

 @return found sub-child

 <br><br>
 @htmlinclude ./des/Prcs_Trn_Merge__searchLastImportChild.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    31.12.2009   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
    08.04.2010   @I  Eckard Klotz
 @I update from tinyxml ver.2.5.3 to ver 2.6.1
 @I first changed node-type enum from XYZ to TINYXML_XYZ
 @I_______________________________________________________
    26.10.2014   @I  Eckard Klotz
 @I bug two following comments will be merged in wrong order
    since this function skips the evaluation of already existing
    comments for importing comments
 @I by adding the node to import as parameter this method is able
    to differ between commands and comments to import and skips
    the evaluation of comments only for importing commands
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 DataAssociation* _searchLastImportChild(DataAssociation* parent,
                                         set<String_imp>* importLevell,
                                         DataAssociation* import);





/*!
 move parts of the code under a special command (defined as comment)

 @param [in] codeTree code to analyse if parts have to be moved
 @param [in] codeModel     management-object that creates and deletes associations and data-objects

 <br><br>
 @htmlinclude ./des/Prcs_Trn_Merge__moveCodePart.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    20.06.2010   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
    26.12.2011   @I  Eckard Klotz
 @I improvement to reduce the amount of begin and end block-commands
 @I if an other command follows an exclude-command that
    has no further content the other command and its content
    will be moved into the block of the exclude-command
 @I_______________________________________________________
    18.06.2013   @I  Eckard Klotz
 @I re-factoring
 @I code lines will not be assembled any more in abc2xml
 @I_______________________________________________________
    12.11.2014   @I  Eckard Klotz
 @I bug moritz command insertLink contains source-code after merge
 @I added insertLink to same if-filter as describe and independent
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
void _moveCodePart(DataAssociation* codeTree, TiPa_DataModel* codeModel);





/*!
 assemble comments to special commands wich are responsible for commands

 @param [in] import       current element to import while merge-process
 @param [in] nextChild    following element to import
 @param [in] codeModel     management-object that creates and deletes associations and data-objects

 @return copy of nextChild-pointer or a pointer to the child after nextChild
 <br><br>
 @htmlinclude ./des/Prcs_Trn_Merge__assembleCommentsToCommands.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    11.08.2010   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
    17.09.2013   @I  Eckard Klotz
 @I bug: if after the last moritz-command now comment follows
         abc2xml crashes
 @I by checking if next child is not NULL it will be ensured
    that the method does not to try to assemble not existing
    comments
 @I_______________________________________________________
    12.11.2014   @I  Eckard Klotz
 @I bug moritz command insertLink will be merged to wrong place
 @I added insertLink to same if-filter as describe and independent
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
DataAssociation* _assembleCommentsToCommands(DataAssociation* import,
                                             DataAssociation* nextChild,
                                             TiPa_DataModel*  codeModel);










/*!
 @brief common object-attributes

 to put the attributes into a structure makes it possible to
 set them apart from local variables and parameters of a method
 in the source-code by using the struct-name as prefix.

 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    30.12.2009   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 struct Att
 {
  MergeConfig Comment;
  MergeConfig Line;
  MergeConfig Command;
  list<DataAssociation*> BlockStack;

///purpose of special : tag-name to use for
  map<String_imp, String_imp>     CommandTag;

///type and pseudo-tag of special comment : data to detect it
  map<String_imp, SpecialCommentData > SpecialComment;


 } Att;



};

#ifndef DOXYGEN
#define USING_NAMESPACE using namespace
//}; USING_NAMESPACE CL_TRN_MERGE;
//}; USING_NAMESPACE CL_PROCESS;
#undef  USING_NAMESPACE
#endif //DOXYGEN









#endif //Merge_H
