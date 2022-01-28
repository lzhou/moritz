/*!

 @file
 @brief    definition of an comment parser-process defined by the user

 This file contains the definition of a user parser-process to analyse the comments.


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
    28.08.2009     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    28.08.2009...  @I Eckard Klotz
 @I Changes are documented in the comment of the changed element
 @TabEnd

*/
#ifndef TRN_COMMENT_H
#define TRN_COMMENT_H


#include <map>

using namespace std;


#include "transform.h"


#ifndef DOXYGEN
//namespace CL_PROCESS {
//namespace CL_TRANSFORM {
//namespace CL_TRN_COMMENT {
#endif //DOXYGEN


/*!
 @brief
 Complex parser defined by user grammar to analyse comments.
 As result the anaylsed source contains no comments anymore.
 But all comments will be stored in an own xml-strucrure.
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
 The real content may be changed if neccessary
 @history
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    28.08.2009   @I  Eckard Klotz @I First Implementation @I
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
class Prcs_Trn_Comment:public Prcs_Transformation
{
 public:


// typedef struct Content_Details
// {
//  String_imp Type;
//  String_imp Content;
//  char*      Start;
//  char*      End;
//  int        Size;
//
//  /// @brief default constructor
//  Content_Details(void):
//   Type   (""),
//   Content(""),
//   Start  (nullptr),
//   End    (nullptr),
//   Size   (-1)
//  {};
//
//  /*!
//   @brief copy constructor
//   @param [in] src object to copy
//  */
//  Content_Details(const Content_Details& src):
//   Type   (src.Type   ),
//   Content(src.Content),
//   Start  (src.Start  ),
//   End    (src.End    ),
//   Size   (src.Size   )
//  {};
//  /*!
//   @brief assignment operator
//   @param [in] src object to copy
//   @return copied object
//  */
//  Content_Details& operator = (const Content_Details& src)
//  {
//   Type    = src.Type   ;
//   Content = src.Content;
//   Start   = src.Start  ;
//   End     = src.End    ;
//   Size    = src.Size   ;
//   return(*this);
//  };
//  /// @brief destructor
//  ~Content_Details(void)
//  {
//   Type.clear();
//   Content.clear();
//  };
//
// } Content_Details;
//
//
//
//
// typedef list<Content_Details>::iterator Iterator;




 typedef struct SpecialCommentToken
 {
  String_imp Start;
  String_imp End;

  /// @brief default constructor
  SpecialCommentToken(void):
   Start(""),
   End  ("")
  {};

  /*!
   @brief copy constructor
   @param [in] src object to copy
  */
  SpecialCommentToken(const SpecialCommentToken& src):
   Start(src.Start),
   End  (src.End  )
  {};
  /*!
   @brief assignment operator
   @param [in] src object to copy
   @return copied object
  */
  SpecialCommentToken& operator = (const SpecialCommentToken& src)
  {
   Start = src.Start;
   End   = src.End  ;
   return(*this);
  };
  /// @brief destructor
  ~SpecialCommentToken(void)
  {
   Start.clear();
   End  .clear();
  };
 } SpecialCommentToken;






 typedef struct SpecialCommentData
 {
  String_imp StartsWith;
  String_imp EndsWith;

  /// @brief default constructor
  SpecialCommentData(void):
   StartsWith(""),
   EndsWith  ("")
  {};

  /*!
   @brief copy constructor
   @param [in] src object to copy
  */
  SpecialCommentData(const SpecialCommentData& src):
   StartsWith(src.StartsWith),
   EndsWith  (src.EndsWith  )
  {};
  /*!
   @brief assignment operator
   @param [in] src object to copy
   @return copied object
  */
  SpecialCommentData& operator = (const SpecialCommentData& src)
  {
   StartsWith = src.StartsWith;
   EndsWith   = src.EndsWith  ;
   return(*this);
  };
  /// @brief destructor
  ~SpecialCommentData(void)
  {
   StartsWith.clear();
   EndsWith  .clear();
  };
 }SpecialCommentData;












/*!
 user-constructor

 @param [in] speclComntToken user-definition of begin- and end-token
                             of comments and special comments
                             (for example doxygen or moritz)
 @param [in] startLine       wanted number of the first text-line
                             used as base for line-attributes
 @param [in] startColumn     wanted number of the first text-column
                             used as base for collumn-attributes
 @param [in] showTextToParse user-configuration if text to parse should
                             be printed shown in the terminal-output
 <br><br>
 @htmlinclude ./des/Prcs_Trn_Comment_Prcs_Trn_Comment.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    ... 09.2009   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
    04.11.2012   @I  Eckard Klotz
 @I bug normalization of key-words is not working anymore
    since implementation of context-parser
 @I normalization of key-words moved from comment-process
    to source-process
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
explicit Prcs_Trn_Comment(map<String_imp, SpecialCommentToken > speclComntToken,
                          int   startLine           = 1,
                          int   startColumn         = 1,
                          bool  showTextToParse     = false);


/*!
 destructor
 <br><br>
 @htmlinclude ./des/Prcs_Trn_Comment_Prcs_Trn_Comment.html
*/
  virtual ~Prcs_Trn_Comment();


/*!
 evaluate an given text and returns the result as data-tree

 @param [in]  text  text to analyse
 @param [in]  model context-model used to create data-nodes

 @return data-tree that represents the test to analyse


 <br><br>
 @htmlinclude ./des/Prcs_Trn_Comment_analyse.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    ... 09.2009   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
    25.12.2009    @I  Eckard Klotz
 @I re-factoring for merging part xml-results
 @I changing return-value from processed text to result of analysis
 @I_______________________________________________________
    23.01.2011    @I  Eckard Klotz
 @I implementing parsers others than for python-sources
 @I the #-character will not be deleted anymore
 @I_______________________________________________________
    04.11.2012   @I  Eckard Klotz
 @I bug normalization of key-words is not working anymore
    since implementation of context-parser
 @I normalization of key-words moved from comment-process
    to source-process
 @I_______________________________________________________
    02.08.2013   @I  Eckard Klotz
 @I re-factoring of base-design
 @I name of rule used for parsing is now an optional parameter
    normally set to pass
 @I_______________________________________________________
    01.05.2017   @I  Eckard Klotz
 @I exchanging tinyxml by association-tree
 @I re-factoring
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
TiPa_Concrete::DataFellow* analyse(String_imp*     text,
                                   TiPa_DataModel* model/*,
                                   const String_imp&            rule = "pass"*/);







 protected:



 private:



/*!
 @brief detailed analyse of parsed content

 @param [in] result parser-tree of comment-text parsing


 <br><br>
 @htmlinclude ./des/Prcs_Trn_Comment_postAnalysis.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    22.04.2017   @I  Eckard Klotz
 @I re-factoring of implementation structure
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd

*/
 void postAnalysis(TiPa_DataModel* result);











/*!
 @brief detect special comments

 @param [in] comment text to analyse

 @return the kind of the special comment as a string
 <br>    or nullptr if the given comment is not a special one

 <br><br>
 @htmlinclude ./des/Prcs_Trn_Comment_detectSpecialComment.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    27.12.2015   @I  Eckard Klotz
 @I implementation of new TiPa parser
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd

*/
const char* detectSpecialComment(const char* comment);




/*!
 @brief replace comment tokens and line-changes

 @param text [in] text to analyse

 @return the educed content of the given text

 <br><br>
 @htmlinclude ./des/Prcs_Trn_Comment_deleteNormalCommentTokens.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    28.12.2015   @I  Eckard Klotz
 @I implementation of new TiPa parser
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd

*/
String_imp deleteNormalCommentTokens(String_imp text);










/*!
 @brief common object-attributes

 to put the attributes into a structure makes it possible to
 set them apart from local variables and parameters of a method
 in the source-code by using the structure-name as prefix.

 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    ... 09.2009   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/


 struct Att
 {


//  /// @brief purpose of special : tag-name to use for
//  list<Prcs_Trn_Comment::Content> IndentionContainer;

  /// @brief purpose of special : tag-name to use for
  map<String_imp, String_imp>     CommandTag;

  /// @brief type and pseudo-tag of special comment : data to detect it
  map<String_imp, SpecialCommentData > SpecialComment;

  /// @brief special token-sets to symbolise special comment-types
  map<String_imp, SpecialCommentToken > SpeclComntToken;

  /// @brief special token-sets to symbolise normal comment-types
  map<String_imp, SpecialCommentToken > NormlComntToken;

  /// @brief user-configuration if source-keyword should be turned into low-case characters
  bool ShowTextToParse;


  /// @brief default constructor
  Att(void)
  {};

  /*!
   @brief copy constructor
   @param [in] src object to copy
  */
  Att(const Att& src):
//   IndentionContainer(src.IndentionContainer   ),
   CommandTag        (src.CommandTag),
   SpecialComment    (src.SpecialComment  ),
   SpeclComntToken   (src.SpeclComntToken    ),
   NormlComntToken   (src.NormlComntToken   ),
   ShowTextToParse   (src.ShowTextToParse   )
  {};

  /*!
   @brief assignment operator
   @param [in] src object to copy
   @return copied object
  */
  Att& operator = (const Att& src)
  {
//   IndentionContainer = src.IndentionContainer;
   CommandTag         = src.CommandTag        ;
   SpecialComment     = src.SpecialComment    ;
   SpeclComntToken    = src.SpeclComntToken   ;
   NormlComntToken    = src.NormlComntToken   ;
   ShowTextToParse    = src.ShowTextToParse   ;
   return(*this);
  };

  /// @brief destructor
  ~Att(void)
  {
//   IndentionContainer.clear();
   CommandTag        .clear();
   SpecialComment    .clear();
   SpeclComntToken   .clear();
   NormlComntToken   .clear();
  };

 } Att;

  enum
  {
   Skip_id   =  1,
   Search_id =  2
  };

};









#ifndef DOXYGEN
#define USING_NAMESPACE using namespace
//}; USING_NAMESPACE CL_TRN_COMMENT;
//}; USING_NAMESPACE CL_TRANSFORM;
//}; USING_NAMESPACE CL_PROCESS;
#undef  USING_NAMESPACE
#endif //DOXYGEN








#endif //TRN_COMMENT_H
