/*!

 @file
 @brief  abstract definition of an parser-process defined by the user

 This file contains the abstract definition of a user parser-process.

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
 @I changed design for spirit
 @I____________________________________________________________
    27.08.2009...  @I Eckard Klotz
 @I Changes are documented in the comment of the changed element
 @TabEnd

*/
#ifndef TRANSFORM_H
#define TRANSFORM_H



#include <iostream>
#include <list>
#include <map>
#include <set>

using namespace std;


#include "String_imp.h"
#include "Spirit185_External.h"
#include "Spirit185_Filter.h"

//#include "ASS_Model.hpp"
#include "TiPa_DataModel.h"






#ifndef DOXYGEN
//namespace CL_PROCESS {
//namespace CL_TRANSFORM {
#endif //DOXYGEN



/*!
 @brief
 Complex parser defined by user grammar to read and analyse
 specific sources.
 <br>
 The user-grammar will be read and analysed by a special
 notation-parser. As result of this process an object of the
 evaluation-class gets its own parser-tree to analyse specific
 source-files.
 <br>

 @history
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    27.8.2008   @I  Eckard Klotz @I First Implementation @I
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/

class Prcs_Transformation//:public Prcs__Abstract
{
 public:


 typedef Association<TiPa_Data*,nullptr>                                 DataAssociation;
 typedef AssociationFellowship<TiPa_Data*,nullptr>                       DataFellow;
 typedef AssociationSponsor<TiPa_Data*,nullptr>                          DataSponsor;

// typedef TiPa_DataModel::IndepAssociationFellowship IndepFellowTree;





///global identifier of user-rules-propperties
typedef enum TP_UserRuleProperty
{
 URP_TOKEN,
 URP_NOTPHRASED,
 URP_HIDE,
 URP_SKIPLEVEL,
}TP_UserRuleProperty;


///global user-rules-properties
 typedef  struct TP_UsrRlPrptGlb
 {
  set<String_imp> Token;
  set<String_imp> NotPhrased;
  set<String_imp> Hide;
  set<String_imp> SkipLevel;

  /// @brief default constructor
  TP_UsrRlPrptGlb(void)
  {};

  /*!
   @brief copy constructor
   @param [in] src object to copy
  */
  TP_UsrRlPrptGlb(const TP_UsrRlPrptGlb& src):
   Token(     src.Token),
   NotPhrased(src.NotPhrased),
   Hide(      src.Hide),
   SkipLevel( src.SkipLevel)
  {};
  /*!
   @brief assignment operator
   @param [in] src object to copy
   @return copied object
  */
  TP_UsrRlPrptGlb& operator = (const TP_UsrRlPrptGlb& src)
  {
   Token      = src.Token;
   NotPhrased = src.NotPhrased;
   Hide       = src.Hide;
   SkipLevel  = src.SkipLevel;
   return(*this);
  };
  /// @brief destructor
  ~TP_UsrRlPrptGlb(void)
  {
   Token     .clear();
   NotPhrased.clear();
   Hide      .clear();
   SkipLevel .clear();
  };
 }TP_UsrRlPrptGlb;

///local user-rules-properties
 typedef  struct TP_UsrRlPrptLcl
 {
  map<String_imp, set<String_imp> > Token;
  map<String_imp, set<String_imp> > Hide;
  map<String_imp, set<String_imp> > SkipLevel;

  /// @brief default constructor
  TP_UsrRlPrptLcl(void)
  {};

  /*!
   @brief copy constructor
   @param [in] src object to copy
  */
  TP_UsrRlPrptLcl(const TP_UsrRlPrptLcl& src):
   Token    (src.Token),
   Hide     (src.Hide),
   SkipLevel(src.SkipLevel)
  {};
  /*!
   @brief assignment operator
   @param [in] src object to copy
   @return copied object
  */
  TP_UsrRlPrptLcl& operator = (const TP_UsrRlPrptLcl& src)
  {
   Token     = src.Token    ;
   Hide      = src.Hide     ;
   SkipLevel = src.SkipLevel;
   return(*this);
  };
  /// @brief destructor
  ~TP_UsrRlPrptLcl(void)
  {
   Token    .clear();
   Hide     .clear();
   SkipLevel.clear();
  };

 }TP_UsrRlPrptLcl;



/// Contains all information about the user defined grammar of a parser
 typedef struct  TP_GrammmarStuff
 {
  /// scan- and output-properties of the user-rules
  TP_UsrRlPrptGlb                   URPG;
  /// user-specification of symbols like keywords or special strings
  map<String_imp, set<String_imp> > SymbolMap;

  /// @brief default constructor
  TP_GrammmarStuff(void)
  {};

  /*!
   @brief copy constructor
   @param [in] src object to copy
  */
  TP_GrammmarStuff(const TP_GrammmarStuff& src):
   URPG     (src.URPG     ),
   SymbolMap(src.SymbolMap)
  {};
  /*!
   @brief assignment operator
   @param [in] src object to copy
   @return copied object
  */
  TP_GrammmarStuff& operator = (const TP_GrammmarStuff& src)
  {
   URPG      = src.URPG     ;
   SymbolMap = src.SymbolMap;
   return(*this);
  };
  /// @brief destructor
  ~TP_GrammmarStuff(void)
  {
   SymbolMap.clear();
  };

 }TP_GrammmarStuff;


 /// size of a text-part found by a parser
 typedef struct TP_TextSize
 {
  int Height; ///< @brief number of lines
  int Width ; ///< @brief number of characters in the longest line

  /// @brief default constructor
  TP_TextSize(void):
   Height(0),
   Width (0)
  {};
  /*!
   @brief initializing constructor
  */
  TP_TextSize(const int& height, const int& width):
   Height(height),
   Width (width )
  {};
  /*!
   @brief copy constructor
   @param [in] src object to copy
  */
  TP_TextSize(const TP_TextSize& src):
   Height(src.Height),
   Width (src.Width )
  {};
  /*!
   @brief assignment operator
   @param [in] src object to copy
   @return copied object
  */
  TP_TextSize& operator = (const TP_TextSize& src)
  {
   Height = src.Height;
   Width  = src.Width ;
   return(*this);
  };
  /// @brief destructor
  ~TP_TextSize(void)
  {
  };

 }TP_TextSize;









/*!
 constructor
 <br><br>
 @htmlinclude ./des/Prcs_Transformation_Prcs_Transformation.html
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
  Prcs_Transformation(void);




/*!
 @brief copy constructor not allowed to use
 @param [in] src object to copy
*/
  Prcs_Transformation(const Prcs_Transformation& src) = delete;

/*!
 @brief assignment operator not allowed to use
 @param [in] src object to copy
 @return copied object
*/
  Prcs_Transformation& operator= (const Prcs_Transformation& src) = delete;









/*!
 destruktor
 <br><br>
 @htmlinclude ./des/Prcs_Transformation_Prcs_Transformation.html
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
 virtual ~Prcs_Transformation(void);






/*!
 returns the data-object that holds the memory-location of the grammar

 @return pointer to the memory-location of the grammar

 <br><br>
 @htmlinclude ./des/Prcs_Transformation_Grammar_get.html

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
                 @I               @I              @I
 @TabEnd
*/
  TP_GrammmarStuff* Grammar_get(void);




/*!
 set file that should store the parser-log

 @param [in] parserLogFile file (path and name) where to save the parser-log

 @htmlinclude ./des/Prcs_Transformation_ParserLogFile_set.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    29.11.2010      @I  Eckard Klotz
 @I improvement of parser-debuging
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  void ParserLogFile_set(const String_imp& parserLogFile);



/*!
 add the symbols given as komma-sepparated list in the container
 specified as symbol-class

 @param [in] className user-defined name of the symbol-class to set
 @param [in] members komma-sperated list of strings,
                     white-spaces outside of \"...\" are ignored

 <br><br>
 @htmlinclude ./des/Prcs_Transformation_UserSymbolMap_set.html

 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    21.09.2009   @I  Eckard Klotz
 @I first initialisation of xml-generation
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  void UserSymbolMap_set(String_imp className, String_imp members);

/*!
 clear the symbols given as komma-sepparated list from the container
 specified as symbol-class or clear the whol container if the list-string
 is empty

 @param [in] className user-defined name of the symbol-class to set
 @param [in] members komma-sperated list of strings,
                     white-spaces outside of \"...\" are ignored

 <br><br>
 @htmlinclude ./des/Prcs_Transformation_UserSymbolMap_clr.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    21.09.2009   @I  Eckard Klotz
 @I first initialisation of xml-generation
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  void UserSymbolMap_clr(String_imp className, String_imp members = "");




/*!
 add the rule-names given as comma-sepparated list in the proberty-container
 specified as property

 @param [in] property specifies the kind of property to set
 @param [in] ruleName comma-sperated list of rule-names, white-spaces are ignored

 <br><br>
 @htmlinclude ./des/Prcs_Transformation_UserRulePropertyGlobal_set.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    ... 09.2009   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
    12.01.2010   @I  Eckard Klotz
 @I re-factoring
 @I using new method of Prcs__Abstract to create set of strings
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  void UserRulePropertyGlobal_set(TP_UserRuleProperty property, const String_imp& ruleName);

/*!
 clear the rule-names given as comma-sepparated list from the proberty-container
 specified as property or clear the whol container if the list-string is empty

 @param [in] property specifies the kind of property to clear
 @param [in] ruleName comma-sperated list of rule-names, white-spaces are ignored

 <br><br>
 @htmlinclude ./des/Prcs_Transformation_UserRulePropertyGlobal_clr.html
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
  void UserRulePropertyGlobal_clr(TP_UserRuleProperty property, String_imp ruleName = "");




 /*!
 initialize the grammar object

 @param grammar               [in]  script-text written in the notation of spirit 1.8.5
 @param rootRule              [in]  name of the rule to start parsing with
 @param skipRule              [in]  name of the rule that defines content to ignore in phrased rules
 @param lineRule              [in]  name of the rule that defines a line-change
 @param listOfNonPhrased      [in]  comma separated list of rules which are not phrased
 @param grammarTextIdentifier [in]  name of the text-file that contains the syntax definition
 @param logOutput             [in]  name and path of a log-file that contains the user-grammar as analysed
 @param debugMode             [in]  forces the grammar to store debug-data if set to true
 @param limitCallingTree      [in]  maximum number of calling-levels to analyse
 @param limitCallingNode      [in]  maximum number of calling rules  to analyse
 @param limitCallerTree       [in]  maximum number of caller-levels  to analyse
 @param limitCallerNode       [in]  maximum number of caller rules   to analyse






 <br><br>
 @htmlinclude ./des/Spirit185_External_grammar_init.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    08.12.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
    19.06.2016   @I  Eckard Klotz
 @I enabling debug-outputs
 @I definition of log output-file
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  void grammar_init(const char* grammar,
                    const char* rootRule,
                    const char* skipRule,
                    const char* lineRule,
                    const char* listOfNonPhrased,
                    const char* grammarTextIdentifier,
                    const char* logOutputFile,
                    bool        debugMode/*        = false*/,
                    int         limitCallingTree = 5,
                    int         limitCallingNode = 30,
                    int         limitCallerTree  = 5,
                    int         limitCallerNode  = 30);





/*!
 calculate for a given text the number of lines and the number of characters
 in the longest line.


 @param [in]  begin   first character of string to analyse
 @param [in]  end     behind last character of string to analyse

 @return number of lines and number of characters in the longest line


 <br><br>
 @htmlinclude ./des/Prcs_Transformation_getTextSize.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    31.08.2010   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  TP_TextSize getTextSize(const char* begin, const char* end);



 set<String_imp>* getSymbols(String_imp key);

 protected:




/*!
 replace tabs with spaces due to the rules defined for python 2.5

 @param [in] text    original text with tabs inside
 @param [in] tabSize maximal numbers of spaces for a tab

 @return text without tabs

 @htmlinclude ./des/Prcs_Transformation_replaceTabs.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    13.09.2009      @I  Eckard Klotz
 @I help-function
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  String_imp replaceTabs(String_imp* text, int tabSize);












///memory-location of parser-stuff
  TP_GrammmarStuff Grm;


  struct TextMakeup
  {
   int                   StartLine;
   int                   StartColumn;
   map<const char*, int> LineChange;

   /*!
    @brief initializing constructor
   */
   TextMakeup(void):
    StartLine(0),
    StartColumn(0)
   {};

   /*!
    @brief copy constructor
    @param [in] src object to copy
   */
   TextMakeup(const TextMakeup& src):
    StartLine(src.StartLine),
    StartColumn(src.StartColumn),
    LineChange(src.LineChange)
   {};

   /*!
    @brief assignment operator
    @param [in] src object to copy
    @return copied object
   */
   TextMakeup& operator = (const TextMakeup& src)
   {
    StartLine = src.StartLine;
    StartColumn = src.StartColumn;
    LineChange = src.LineChange;
    return(*this);
   };

   /// @brief destructor
   ~TextMakeup(void)
   {
    LineChange.clear();
   };

  }TextMakeup;


/*!
 file that should store the parser-log
*/
  String_imp                     ParserLogFile;

  Spirit185_External*            Grammar_Spirit185;

  Spirit185_Filter               ResultFilter;

  TiPa_DataModel                 ContextModel;      ///< manages the analysed data

 private:

};


#ifndef DOXYGEN
#define USING_NAMESPACE using namespace
//}; USING_NAMESPACE CL_TRANSFORM;
//}; USING_NAMESPACE CL_PROCESS;
#endif //DOXYGEN
#undef  USING_NAMESPACE







#endif //TRANSFORM_H
