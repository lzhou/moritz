
/*!

 @file
 @brief    definition of an context parser-process defined by the user

 This file contains the definition of a user parser-process to analyse the context-areas.


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
    02.06.2012     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    02.06.2012...  @I Eckard Klotz
 @I Changes are documented in the comment of the changed element
 @TabEnd

*/
#ifndef TRN_CONTEXT_H
#define TRN_CONTEXT_H


//#include <iostream>
//#include <list>
//#include <map>
//#include <set>

using namespace std;


//#include "process.h"
//#include "action.h"
#include "transform.h"


#ifndef DOXYGEN
//namespace CL_PROCESS {
//namespace CL_TRANSFORM {
//namespace CL_TRN_CONTEXT {
#endif //DOXYGEN


/*!
 @brief
 Complex parser defined by user grammar to analyse contexts-areas.
 As result the analysed source will be split in different texts
 which contain only one context (only comments or only active text)
 for an easier parsing.
 <br>
 The user-grammar will be read and analysed by a special
 notation-parser. As result of this process an object of the
 evaluation-class gets its own parser-tree to analyse specific
 source-files.
 <br>
 The user has to define 2 basic rules in
 the grammar like this examples show:
 <br> skip = space_p;
 <br> pass = anychar_p - space_p;
 <br>
 (the real content has to be changed and extended in the normal case)
 @history
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    02.06.2012   @I  Eckard Klotz
 @I re-factoring of splitting comments and active code
 @I First Implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
class Prcs_Trn_Context:public Prcs_Transformation
{
 public:

 /// @brief defines start and end-token of a single context sequence
 typedef struct _s_Sequence
 {
  String_imp Name;       ///< @brief name of the context sequence
  String_imp StartToken; ///< @brief character-combination that starts the sequence
  String_imp EndToken;   ///< @brief character-combination that terminates the sequence

  /// @brief default constructor
  _s_Sequence(void):
   Name      (""),
   StartToken(""),
   EndToken  ("")
  {};

  /*!
   @brief copy constructor
   @param [in] src object to copy
  */
  _s_Sequence(const _s_Sequence& src):
   Name      (src.Name      ),
   StartToken(src.StartToken),
   EndToken  (src.EndToken  )
  {};
  /*!
   @brief assignment operator
   @param [in] src object to copy
   @return copied object
  */
  _s_Sequence& operator = (const _s_Sequence& src)
  {
   Name       = src.Name      ;
   StartToken = src.StartToken;
   EndToken   = src.EndToken  ;
   return(*this);
  };
  /// @brief destructor
  ~_s_Sequence(void)
  {
   Name      .clear();
   StartToken.clear();
   EndToken  .clear();
  };

 } _s_Sequence;


 /// container of all sequence-definitions for one kind of context
 typedef struct _s_ContextType
 {
  list<_s_Sequence> Sequence;    ///< container of different sequence-types which are associated with one context
  bool              IsDefault;   ///< default-text out of any context-sequence is implicit part of this context
  char              Replacement; ///< Character used to replace source-character not visible in this context

  /// @brief default constructor
  _s_ContextType(void):
   IsDefault  (false  ),
   Replacement(' ')
  {};

  /*!
   @brief copy constructor
   @param [in] src object to copy
  */
  _s_ContextType(const _s_ContextType& src):
   Sequence   (src.Sequence   ),
   IsDefault  (src.IsDefault  ),
   Replacement(src.Replacement)
  {};
  /*!
   @brief assignment operator
   @param [in] src object to copy
   @return copied object
  */
  _s_ContextType& operator = (const _s_ContextType& src)
  {
   Sequence    = src.Sequence   ;
   IsDefault   = src.IsDefault  ;
   Replacement = src.Replacement;
   return(*this);
  };
  /// @brief destructor
  ~_s_ContextType(void)
  {
   Sequence.clear();
  };
 } _s_ContextType;


/// necessary token-information to get a special context-part of a user-source
  typedef struct _s_Token
  {
   String_imp Type;
   String_imp Content;
   size_t     Index;
   size_t     Length;

   /// @brief default constructor
   _s_Token(void):
    Type   (""),
    Content(""),
    Index  (-1),
    Length (-1)
   {};

   /*!
    @brief copy constructor
    @param [in] src object to copy
   */
   _s_Token(const _s_Token& src):
    Type   (src.Type   ),
    Content(src.Content),
    Index  (src.Index  ),
    Length (src.Length )
   {};
   /*!
    @brief assignment operator
    @param [in] src object to copy
    @return copied object
   */
   _s_Token& operator = (const _s_Token& src)
   {
    Type    = src.Type   ;
    Content = src.Content;
    Index   = src.Index  ;
    Length  = src.Length ;
    return(*this);
   };
   /// @brief destructor
   ~_s_Token(void)
   {
    Type   .clear();
    Content.clear();
   };
  } _s_Token;


/*!
 user-constructor

 @param [in] startLine       wanted number of the first text-line
                             used as base for line-attributes
 @param [in] startColumn     wanted number of the first text-column
                             used as base for column-attributes
 @param [in] showTextToParse user-configuration if text to parse should
                             be printed shown in the terminal-output
 @param [in] parseTolerant   user-configuration if parsing-process should
                             be restated again behind the position that
                             caused a parser-fail
 @param [in] contextType     container of associations between parser-tokens
                             and contexts
 @param [in] positionOutput  control if position output should be added
 <br>                        0 == no tag gets position info
 <br>                        1 == leaf-nodes with text inside only get position-Info
 <br>                        2 == all nodes get position info

 <br><br>
 @htmlinclude Prcs_Trn_Context_Prcs_Trn_Context.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    02.06.2012   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 Prcs_Trn_Context(map<String_imp, _s_ContextType>& contextType,
                  int                              positionOutput,
                  bool                             showTextToParse = false,
                  bool                             parseTolerant   = false,
                  int                              startLine       = 1,
                  int                              startColumn     = 1);

/*!
 destructor
 <br><br>
 @htmlinclude "Prcs_Trn_Context__Prcs_Trn_Context.html"
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    02.06.2012   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  virtual ~Prcs_Trn_Context();


/*!
 @brief evaluate an given text and returns the result as xml-tree

 Furthermore this method stores the position of context switching tokens
 and some more information in the attribute @ref Token to be usable
 by @ref TiPa_Concrete::getContext


 @param [in]  text  text to analyse
 @param [in]  model context-model used to create data-nodes

 @return xml-tree that represents the test to analyse


 <br><br>
 @htmlinclude Prcs_Trn_Context_analyse.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    02.06.2012   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
    02.08.2013   @I  Eckard Klotz
 @I re-factoring of base-design
 @I name of rule used for parsing is now an optional parameter
    normally set to pass
 @I_______________________________________________________
    24.12.2015   @I  Eckard Klotz
 @I implementation of new parser
 @I use of new parser and its visitors instead of own private
    methods
 @I_______________________________________________________
    06.05.2017   @I  Eckard Klotz
 @I exchanging tinyxml by association-tree
 @I re-factoring
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 TiPa_Concrete::DataFellow* analyse(String_imp*     text,
                                    TiPa_DataModel* model/*,
                                    String_imp      rule = "pass"*/);


















/*!
 evaluate an given text and returns a text that contains only those parts
 which are associated with the given context. All other characters except
 white-space characters will be replaced by spaces.
 @pre the method analyse has to be used at least one times with the given text
      to find the position off all context-tokens since this function cuts out
      the wanted text-part only. If the token positions are not valid this method
      is not able to work.

 @param [in] type type of context-content to return
 @param [in] text text to analyse

 @return only context containing text


 <br><br>
 @htmlinclude Prcs_Trn_Context_getContext.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    09.06.2012   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  String_imp getContext(String_imp type, String_imp* text);


 protected:



 private:




/*!
 @brief detailed analyse of parsed content

 @param [in] result parser-tree of context parsing
 @param [in] text text to analyse

 <br><br>
 @htmlinclude Prcs_Trn_Context_postAnalysis.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    29.04.2017   @I  Eckard Klotz
 @I re-factoring of implementation structure
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd

*/
 void postAnalysis(TiPa_DataModel* result, const char* text);





/* !
 evaluate an element of a parser-tree (result of parsing)

 @param [in] i     parser part-result
 @param [in] first points to the fist character of the analysed text


 @return xml-tree of parser-tree element


 <br><br>
 @htmlinclude Prcs_Trn_Context__eval_SearchRule.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    06.06.2012   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @TabEnd
  TiXmlElement _eval_SearchRule(iter_t const& i, char * first);
*/





/*!
 @brief common object-attributes

 to put the attributes into a structure makes it possible to
 set them apart from local variables and parameters of a method
 in the source-code by using the structure-name as prefix.

 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    02.06.2012   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/


 struct Att
 {
  /// @brief container of associations between parser-tokens and contexts
  map<String_imp, _s_ContextType> ContextType;

  /// @brief container of necessary parser-result to get a special context-part of a user-source
  /// filled by @ref analyse
  /// used   by @ref getContext
  list<_s_Token>    Token;

  /// @brief controls the output of position-values
  /// <br> 0 ==> no position-values will be added to xml-output
  /// <br> 1 ==> position-values will be added to xml-leaves with text inside
  /// <br> 2 ==> position-values will be added to xml-knots also
  int PositionOutput;

  /// @brief user command to output the source-text before its parsing for debugging purpose
  bool ShowTextToParse;

  /// @brief user command to restart parsing with the next character if the parser didn’t
  /// reached the end of the text
  bool ParseTolerant;

  /// @brief Character used to Replace source-character not visible in the active context
  char Replacement;

  /// @brief default constructor
  Att(void):
   PositionOutput (0),
   ShowTextToParse(false),
   ParseTolerant  (false),
   Replacement    (' ')
  {};

  /*!
   @brief copy constructor
   @param [in] src object to copy
  */
  Att(const Att& src):
   ContextType    (src.ContextType    ),
   Token          (src.Token          ),
   PositionOutput (src.PositionOutput ),
   ShowTextToParse(src.ShowTextToParse),
   ParseTolerant  (src.ParseTolerant  ),
   Replacement    (src.Replacement    )
  {};
  /*!
   @brief assignment operator
   @param [in] src object to copy
   @return copied object
  */
  Att& operator = (const Att& src)
  {
   ContextType     = src.ContextType    ;
   Token           = src.Token          ;
   PositionOutput  = src.PositionOutput ;
   ShowTextToParse = src.ShowTextToParse;
   ParseTolerant   = src.ParseTolerant  ;
   Replacement     = src.Replacement    ;
   return(*this);
  };
  /// @brief destructor
  ~Att(void)
  {
   ContextType.clear();
   Token      .clear();
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
//}; USING_NAMESPACE CL_TRN_CONTEXT;
//}; USING_NAMESPACE CL_TRANSFORM;
//}; USING_NAMESPACE CL_PROCESS;
#undef  USING_NAMESPACE
#endif //DOXYGEN








#endif //TRN_CONTEXT_H
