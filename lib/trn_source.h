/*!

 @file
 @brief  definition of an source parser-process defined by the user

 This file contains the definition of a user parser-process to analyse the source.

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
    12.07.2009     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    12.07.2009...  @I Eckard Klotz
 @I changed design for spirit
 @I____________________________________________________________
    12.07.2009...  @I Eckard Klotz
 @I Changes are documented in the comment of the changed element
 @TabEnd

*/
#ifndef TRN_SOURCE_H
#define TRN_SOURCE_H


#include <iostream>
#include <list>
#include <map>
#include <set>

using namespace std;


#include "xml_DataModel.h"

#include "transform.h"



#ifndef DOXYGEN
//namespace CL_PROCESS {
//namespace CL_TRANSFORM {
//namespace CL_TRN_SOURCE {
#endif //DOXYGEN



/*!
 @brief
 Complex parser defined by user grammar to read and analyse
 specific sources.
 <br> The user-grammar will be read and analysed by a special
 notation-parser. As result of this process an object of the
 evaluation-class gets its own parser-tree to analyse specific
 source-files.
 some-times this source-files have to be preprocessed for example
 to delete comments or to add special tokens like INDENT or DEDENT.
 The result of evaluation-parser is a xml-representation of the
 analysed source-code that reflects its syntacticle structure.
 The xml-tags have attribute like L (line) and C (collumn) wich
 contain additional information like the position in the analysed
 text.

 @history
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    12.07.2009   @I  Eckard Klotz @I First Implementation @I
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
class Prcs_Trn_Source:public Prcs_Transformation
{
 public:


/*!
 default-constructor



 <br><br>
 @htmlinclude ./des/Prcs_Trn_Source_Prcs_Trn_Source.html
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
  Prcs_Trn_Source(void);

/*!
 user-constructor

 @param [in] positionOutput control of inserting position-info
                            (line/column) as attributes into xml-tag
 <br>        0 => no tag gets position info
 <br>        1 => leaf-tags with text inside only get position-Info
 <br>        2 => all tags get position info (knot-tags without text inside
             will get the position of their first child)
 @param [in] normlzKwrdsOfSource user-configuration if source-keyword
                                 should be turned into low-case characters
 @param [in] showTextToParse user-configuration if text to parse should
                             be printed shown in the terminal-output
 @param [in] parseTolerant   user-configuration if parsing-process should
                             be restated again behind the position that caused
                             a parser-fail
 @param [in] startLine       wanted number of the first text-line
                             used as base for line-attributes
 @param [in] startColumn     wanted number of the first text-column
                             used as base for column-attributes
 @param [in] tokenIndent     token-string of indent
                             to insert into text where an indent was detected
 @param [in] tokenDedent     token-string of dedent
                             to insert into text where an dedent was detected
 @param [in] tokenNewLine    token-string of new-line
                             to insert into text where an new-line was detected

 @return


 <br><br>
 @htmlinclude ./des/Prcs_Trn_Source_Prcs_Trn_Source.htm
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    ... 09.2009   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
    15.09.2011   @I  Eckard Klotz
 @I re-factoring to make class more independent from other classes
 @I constructor interface contains now all nessesary data
    to anlyse the text-positions without using the line-process class
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
  Prcs_Trn_Source(int            positionOutput,
                  bool           normlzKwrdsOfSource,
                  bool           showTextToParse = false,
                  bool           parseTolerant   = false,
                  int            startLine       = 1,
                  int            startColumn     = 1,
            const String_imp&    tokenIndent     = "INDENT",
            const String_imp&    tokenDedent     = "DEDENT",
            const String_imp&    tokenNewLine    = "NEWLINE");



/*!
 destructor


 <br><br>
 @htmlinclude ./des/Prcs_Trn_Source__Prcs_Trn_Source.html
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
  ~Prcs_Trn_Source(void);





/*!
 evaluate an given text and returns the result as xml-tree

 @param [in] text   text to analyse
 @param [in] model  contextModel management-object that creates and deletes associations and data-objects
 @param [in] rule   name of rule used for parsing

 @return xml-tree that represents the test to analyse


 <br><br>
 @htmlinclude ./des/Prcs_Trn_Source_analyse.html
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
    15.09.2011   @I  Eckard Klotz
 @I re-factoring to make class more independent from other classes
 @I analyses the text-positions without using the line-process class
 @I_______________________________________________________
    04.11.2012   @I  Eckard Klotz
 @I bug normalization of key-words is not working any more
    since implementation of context-parser
 @I normalization of key-words moved from comment-process
    to source-process
 @I_______________________________________________________
    02.08.2013   @I  Eckard Klotz
 @I re-factoring of base-design
 @I name of rule used for parsing is now an optional parameter
    normally set to pass
 @I_______________________________________________________
    20.12.2015   @I  Eckard Klotz
 @I implementation of new parser
 @I use of new parser and its visitors instead of own private
    methods
 @I_______________________________________________________
    07.05.2017   @I  Eckard Klotz
 @I exchanging tinyxml by association-tree
 @I re-factoring
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
TiPa_Concrete::DataFellow*  analyse(String_imp*     text,
                                    TiPa_DataModel* model,
                                    String_imp      rule = "pass");


 protected:

















  private:




/*!
 transform key-words into low-case strings

 @param [in] text text to analyse


 <br><br>
 @htmlinclude ./des/Prcs_Trn_Source__normalizeKeyWords.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    09.01.2011   @I  Eckard Klotz
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
void _normalizeKeyWords(String_imp* text);






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
  /// controls the output of position-values
  /// <br> 0 ==> no position-values will be added to xml-output
  /// <br> 1 ==> position-values will be added to xml-leaves with text inside
  /// <br> 2 ==> position-values will be added to xml-nodes also
  int PositionOutput;


  /// control of progress-output
  char Counter;
  bool NormlzKwrdsOfSource;
  bool ShowTextToParse;
  bool ParseTolerant;

  /// to evaluate text-positions of parser-results independent from temporary pseudo-content
  String_imp TokenIndent;
  String_imp TokenDedent;
  String_imp TokenNewLine;
  list<String_imp> SkipString;

  /// @brief default constructor
  Att(void):
   PositionOutput     (2    ),
   Counter            (' '  ),
   NormlzKwrdsOfSource(false),
   ShowTextToParse    (false),
   ParseTolerant      (false),
   TokenIndent        (""   ),
   TokenDedent        (""   ),
   TokenNewLine       (""   )
  {};

  /*!
   @brief copy constructor
   @param [in] src object to copy
  */
  Att(const Att& src):
   PositionOutput     (src.PositionOutput     ),
   Counter            (src.Counter            ),
   NormlzKwrdsOfSource(src.NormlzKwrdsOfSource),
   ShowTextToParse    (src.ShowTextToParse    ),
   ParseTolerant      (src.ParseTolerant      ),
   TokenIndent        (src.TokenIndent        ),
   TokenDedent        (src.TokenDedent        ),
   TokenNewLine       (src.TokenNewLine       ),
   SkipString         (src.SkipString         )
  {};
  /*!
   @brief assignment operator
   @param [in] src object to copy
   @return copied object
  */
  Att& operator = (const Att& src)
  {
   PositionOutput      = src.PositionOutput     ;
   Counter             = src.Counter            ;
   NormlzKwrdsOfSource = src.NormlzKwrdsOfSource;
   ShowTextToParse     = src.ShowTextToParse    ;
   ParseTolerant       = src.ParseTolerant      ;
   TokenIndent         = src.TokenIndent        ;
   TokenDedent         = src.TokenDedent        ;
   TokenNewLine        = src.TokenNewLine       ;
   SkipString          = src.SkipString         ;
   return(*this);
  };
  /// @brief destructor
  ~Att(void)
  {
   SkipString.clear();
  };
 } Att;




//  void init(void);




};


#ifndef DOXYGEN
#define USING_NAMESPACE using namespace
//}; USING_NAMESPACE CL_TRN_SOURCE;
//}; USING_NAMESPACE CL_TRANSFORM;
//}; USING_NAMESPACE CL_PROCESS;
#undef  USING_NAMESPACE
#endif //DOXYGEN


#endif //TRN_SOURCE_H
