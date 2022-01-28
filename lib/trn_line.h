/*!

 @file
 @brief    definition of a line parser-process defined by the user

 This file contains the definition of a user parser-process to analyse the line-changes.


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
    27.08.2009     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    27.08.2009...  @I Eckard Klotz
 @I Changes are documented in the comment of the changed element
 @TabEnd

*/
#ifndef TRN_LINE_H
#define TRN_LINE_H


#include <map>

using namespace std;


#include "transform.h"

#ifndef DOXYGEN
//namespace CL_PROCESS {
//namespace CL_TRANSFORM {
//namespace CL_TRN_LINE {
#endif //DOXYGEN



/*!
 @brief
 Complex parser defined by user grammar to analyse line-changes.
 As result the analysed source contains special tokens like
 INDENT or DEDENT and this parser is able to analyse the text-position
 of text-parts found by the user-parser.
 <br>
 The user-grammar will be read and analysed by a special
 notation-parser. As result of this process an object of the
 evaluation-class gets its own parser-tree to analyse specific
 source-files.
 <br>
 The user has to define 2 basic rules  "skip" and "search"in
 the grammar like this examples show:
 <br> fail = (anychar_p - eol_p);
 <br> pass = (eol_p >> *blank_p);
 <br>
 The real content may be changed if necessary
 @history
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    27.08.2009   @I  Eckard Klotz @I First Implementation @I
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
class Prcs_Trn_Line:public Prcs_Transformation
{
 public:



 typedef struct Content_Details
 {
  String_imp Type;
  String_imp Content;
  char*      Start;
  char*      End;
  int        Size;

  /// @brief default constructor
  Content_Details(void):
   Type   (""),
   Content(""),
   Start  (nullptr),
   End    (nullptr),
   Size   (-1)
  {};

  /*!
   @brief copy constructor
   @param [in] src object to copy
  */
  Content_Details(const Content_Details& src):
   Type   (src.Type   ),
   Content(src.Content),
   Start  (src.Start  ),
   End    (src.End    ),
   Size   (src.Size   )
  {};
  /*!
   @brief assignment operator
   @param [in] src object to copy
   @return copied object
  */
  Content_Details& operator = (const Content_Details& src)
  {
   Type    = src.Type   ;
   Content = src.Content;
   Start   = src.Start  ;
   End     = src.End    ;
   Size    = src.Size   ;
   return(*this);
  };
  /// @brief destructor
  ~Content_Details(void)
  {
   Type.clear();
   Content.clear();
  };
 } Content_Details;


 typedef list<Content_Details>::iterator Iterator;


/*!
 user-constructor

 @param [in] startLine       wanted number of the first text-line
                             used as base for line-attributes
 @param [in] startColumn     wanted number of the first text-column
                             used as base for column-attributes
 @param [in] tabSize         maximum number of spaces to replace a tab
 @param [in] tokenIndent     token-string of indent
                             to insert into text where an indent was detected
 @param [in] tokenDedent     token-string of dedent
                             to insert into text where an dedent was detected
 @param [in] tokenNewLine    token-string of new-line
                             to insert into text where an new-line was detected
 @param [in] tokenEndMarker  token-string of file-end
                             to insert at end of text
 @param [in] showTextToParse user-configuration if text to parse should
                             be printed shown in the terminal-output

 <br><br>
 @htmlinclude ./des/Prcs_Trn_Line_Prcs_Trn_Line.html
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
 Prcs_Trn_Line(int               startLine       = 1,
               int               startColumn     = 1,
               int               tabSize         = 8,
               const String_imp& tokenIndent     = "INDENT",
               const String_imp& tokenDedent     = "DEDENT",
               const String_imp& tokenNewLine    = "NEWLINE",
               const String_imp& tokenEndMarker  = "ENDMARKER",
               bool              showTextToParse = false);

/*!
 destructor
 <br><br>
 @htmlinclude ./des/Prcs_Trn_Line__Prcs_Trn_Line.html
*/
  virtual ~Prcs_Trn_Line();



/*!
 evaluate an given text and returns the result as xml-tree

 @param [in]  text  text to analyse
 @param [in]  model context-model used to create data-nodes

 @return xml-tree that represents the test to analyse


 <br><br>
 @htmlinclude ./des/Prcs_Trn_Line_analyse.html
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
    29.12.2010    @I  Eckard Klotz
 @I bug: ellipsis-token other than backslash was not replaced
 @I using of " replacePartString(CurrentLine->second,"\\"," ")"
    is now replaced by a loop that replaces all non white-space characters
 @I_______________________________________________________
    02.08.2013   @I  Eckard Klotz
 @I re-factoring of base-design
 @I name of rule used for parsing is now an optional parameter
    normally set to pass
  @I_______________________________________________________
    24.12.2015   @I  Eckard Klotz
 @I implementation of new parser
 @I use of new parser and its visitors instead
    of precut and re-paste
 @I_______________________________________________________
    06.05.2017   @I  Eckard Klotz
 @I exchanging tinyxml by association-tree
 @I re-factoring
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
TiPa_Concrete::DataFellow* analyse(String_imp*       text,
                                   TiPa_DataModel*   model/*,
                                   const String_imp& rule = "pass"*/);





 protected:



 private:





/*!
 @brief detailed analyse of parsed content

 @param [in] result parser-tree of comment-text parsing
 @param [in] text text to analyse


 <br><br>
 @htmlinclude ./des/Prcs_Trn_Line_postAnalysis.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    06.05.2017   @I  Eckard Klotz
 @I re-factoring of implementation structure
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd

*/
 void postAnalysis(TiPa_DataModel* result, String_imp* text);












/*!
 analyse the main parser-result to detect text-parts to manipulate


 @param [in] hit parser-result

 <br><br>
 @htmlinclude ./des/Prcs_Trn_Line__eval_SearchRule.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    ... 09.2009   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
    23.12.2015   @I  Eckard Klotz
 @I implementing the new parser TiPa
 @I parameter is now an association-pointer
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  void  _eval_SearchRule(TiPa_Concrete::DataAssociation* hit);





/*!
 analyse the kind of indention and store this in the @ref IndentionContainer

  @param [in] str first character of the part-text to analyse
  @param [in] end first character behind the part-text to analyse

 <br><br>
 @htmlinclude ./des/Prcs_Trn_Line__detect_Indention.html
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
  void _detect_Indention(char const* str, char const* end);



/*!
 @brief common object-attributes

 to put the attributes into a structure makes it possible to
 set them apart from local variables and parameters of a method
 in the source-code by using the struct-name as prefix.

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
  list<Prcs_Trn_Line::Content_Details> IndentionContainer; ///< @brief container of text-parts to manipulate

  int TabSize;                                             ///< @brief number of spaces used to replace a tabulator -token

  String_imp TokenIndent;                                  ///< @brief token to insert for a line intention
  String_imp TokenDedent;                                  ///< @brief token to insert for a line detention
  String_imp TokenNewLine;                                 ///< @brief token to insert for a new line
  String_imp TokenEndMarker;                               ///< @brief token to insert for the end of the text

  bool ShowTextToParse;                                    ///< @brief user choice if the input-text should be printed out for debugging

  /// @brief default constructor
  Att(void):
   TabSize           (1     ),
   TokenIndent       (""    ),
   TokenDedent       (""    ),
   TokenNewLine      (""    ),
   TokenEndMarker    (""    ),
   ShowTextToParse   (false )
  {};

  /*!
   @brief copy constructor
   @param [in] src object to copy
  */
  Att(const Att& src):
   IndentionContainer(src.IndentionContainer),
   TabSize           (src.TabSize           ),
   TokenIndent       (src.TokenIndent       ),
   TokenDedent       (src.TokenDedent       ),
   TokenNewLine      (src.TokenNewLine      ),
   TokenEndMarker    (src.TokenEndMarker    ),
   ShowTextToParse   (src.ShowTextToParse   )
  {};
  /*!
   @brief assignment operator
   @param [in] src object to copy
   @return copied object
  */
  Att& operator = (const Att& src)
  {
   IndentionContainer= src.IndentionContainer;
   TabSize           = src.TabSize           ;
   TokenIndent       = src.TokenIndent       ;
   TokenDedent       = src.TokenDedent       ;
   TokenNewLine      = src.TokenNewLine      ;
   TokenEndMarker    = src.TokenEndMarker    ;
   ShowTextToParse   = src.ShowTextToParse   ;
   return(*this);
  };
  /// @brief destructor
  ~Att(void)
  {
   IndentionContainer.clear();
  };

 } Att;


};


#ifndef DOXYGEN
#define USING_NAMESPACE using namespace
//}; USING_NAMESPACE CL_TRN_LINE;
//}; USING_NAMESPACE CL_TRANSFORM;
//}; USING_NAMESPACE CL_PROCESS;
#undef  USING_NAMESPACE
#endif //DOXYGEN











#endif //TRN_LINE_H
