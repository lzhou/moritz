/*!

 @file
 @brief    definition of an expression evaluation

 This file contains the definition of a class to evaluate source expressions
 to force internal decisions


 Copyright (C) 2011-2020 by Eckard Klotz.

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
    13.09.2011     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    13.09.2011...  @I Eckard Klotz
 @I Changes are documented in the comment of the changed element
 @TabEnd

*/
#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "AssociationFellowship.h"
#include "TiPa_Data.h"

 typedef Association<TiPa_Data*, nullptr>                                 DataAssociation;
 typedef AssociationFellowship<TiPa_Data*, nullptr>                       DataFellow;
// typedef AssociationSponsor<TiPa_Data*, nullptr>                          DataSponsor;


using namespace std;


#include <iostream>
#include <list>
#include <map>
#include <set>


#include"String_imp.h"

//#include "trn_source.h"

#ifndef DOXYGEN
//namespace CL_EXPRESSION {
#endif //DOXYGEN

typedef enum ReturnType
{
 VOID    = 0,
 BOOL    = 1,
 INTEGER = 2,
 FLOAT   = 3,
 STRING  = 4
} ReturnType;

typedef struct _s_TestRet
{
 String_imp Value;
 ReturnType Type;

 _s_TestRet(void)                                           :Value(""),              Type(VOID){                         }; ///< @brief default constructor
 _s_TestRet(const String_imp& value, const ReturnType& type):Value(value),           Type(type){                         }; ///< @brief initializing constructor
 _s_TestRet(const _s_TestRet& original)                     :Value(original.Value),  Type(original.Type){                }; ///< @brief copy constructor
 _s_TestRet& operator = (const _s_TestRet& original)        {Value = original.Value; Type = original.Type; return(*this);}; ///< @brief assignment operator
 ~_s_TestRet(void)                                          {Value.clear();          Type = VOID;                        }; ///< @brief destructor
} _s_TestRet;


typedef enum SwitchState_TP
{
 TRI_FALSE     = 0,
 TRI_TRUE      = 1,
 TRI_UNKOWN    = 2,
 TRI_DEFINED   = 3,
 TRI_UNDEFINED = 4,
}SwitchState_TP;
/*
typedef struct _s_LogTerm
{
 String_imp  Expression;
 SwitchState_TP Value;
}__LogTerm;*/












/*!
 @brief
 <br>
 @history
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    13.09.2011   @I  Eckard Klotz @I First Implementation @I
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
class Prsd_Expression
{
 public:



/*!
 constructor


 <br><br>
 @htmlinclude ./des/Prsd_Expression_Prsd_Expression.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    13.09.2011   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 Prsd_Expression(void);

/*!
 destructor
 <br><br>
 @htmlinclude ./des/Prsd_Expression__Prsd_Expression.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    13.09.2011   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  virtual ~Prsd_Expression(void);













/*!
 set the value of a string constant
 <br><br>

 @param name  [in] name of the constant
 @param value [in] new value of the constant

 @return true if the constant already exists and false if not

 @htmlinclude ./des/Prsd_Expression_constant_Set.html
@TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    13.09.2011   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  bool constant_Set(String_imp& name, String_imp& value);


/*!
 gset the value of a string constant
 <br><br>

 @param [in]  name  name of the constant
 @param [out] value user-container for value of the constant

 @return true if the constant exists and false if not

 @htmlinclude ./des/Prsd_Expression_constant_Get.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    13.09.2011   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  bool constant_Get(String_imp name, String_imp* value);


/*!
 delete a string constant
 <br><br>

 @param [in]  name  name of the constant

 @return true if the constant existed before and false if not

 @htmlinclude ./des/Prsd_Expression_constant_Clear.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    13.09.2011   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  bool constant_Clear(String_imp name);

/*!
 set the value of an user defined check-result

 @param check [in]   text of the check to define
 @param value [in] new value of the result

 @return true if the check-result was already defined and false if not

 <br><br>
 @htmlinclude ./des/Prsd_Expression_userResult_Set.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    13.09.2011   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  bool userResult_Set(const String_imp& check,
                      const String_imp& value);


/*!
 get the value of an user defined check-result given as string

 @param [in]  check  text of the check to read
 @param [out] value user-container for predefined result of the check

 @return true if the check-result is defined and false if not

 <br><br>
 @htmlinclude ./des/Prsd_Expression_userResult_Get.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    13.09.2011   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  bool userResult_Get(String_imp check, String_imp* value);

/*!
 get the value of an user defined check-result given as xml-tree

 @param [in]  check  text of the check to read
 @param [out] value user-container for predefined result of the check

 @return true if the check-result is defined and false if not

 <br><br>
 @htmlinclude ./des/Prsd_Expression_userResultXML_Get.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    13.09.2011   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  bool userResultXML_Get(DataAssociation* check, String_imp* value);


/*!
 delete an user defined check-result
 <br><br>

 @param [in]  check  text of the check to delete

 @return true if the check-result was defined before and false if not

 @htmlinclude ./des/Prsd_Expression_userResult_Clear.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    13.09.2011   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  bool userResult_Clear(String_imp check);





/*!
 evaluate the give expression
 <br><br>

 @param [in]  expression pre-parsed user expression to check
 @param [out] unknown    user-container for sub-result that
                         the real result is not testable

 @return the result of the analysis as string-structure that may
         symbolise a numeric, boolean, string or unknown result

 @htmlinclude ./des/Prsd_Expression_testExpression.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    13.09.2011   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
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
 _s_TestRet testExpression(DataAssociation* expression, bool* unknown);


/*!
 search in the give expression for all basic logical statements
 <br><br>

 @param [in]  expression  pre-parsed user expression to check
 @param [out] returnValue output-container for recursive call

 @return map of found statements that contain the analysed values

 @htmlinclude ./des/Prsd_Expression_getLogicTerms.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    19.09.2011   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  map<String_imp,SwitchState_TP>* getLogicTerms(DataAssociation*                expression,
                                                map<String_imp,SwitchState_TP>* returnValue = NULL);






/*!
 @ingroup ADVANCED_XML_SERVICE

 read out the text-content of the given xml-node and its childes
 @param [in]  source      root-node of the xml-tree to evaluate
 @param [in]  replacement replacements of special text-parts
 @param [out] returnValue alternative return-possibility

 @return text-content that was read-out

 <br><br>
 @htmlinclude ./des/Prsd_Expression_xmlToText.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    ... 09.2010   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
    28.09.2010   @I  Eckard Klotz
 @I re-factoring make it possible to define an empty-string replacement
 @I implemented the use of <b>replacement[EMPTYSTRING]</b>
 @I_______________________________________________________
    12.02.2017   @I  Eckard Klotz
 @I exchange tinyxml by data-associations
 @I copy function xmlToText from file TiXml_ao to class Prsd_Expression as method
    and exchanged parameter type TiXmlNode by DataAssociation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 String_imp xmlToText(DataAssociation*              source,
                      map<String_imp ,String_imp >* replacement = NULL,
                      list<String_imp>*             returnValue = NULL);







 protected:


 private:



/*!
 evaluate the give expression
 <br><br>
 expressions defined by this grammar will be evaluated directly in this method:
 @verbatim
 unary_expression =  (unary_operator >> primary_expression)
                   | ("++"           >> unary_expression)
                   | ("--"           >> unary_expression)
                   | primary_expression
                   | ("sizeof"       >> unary_expression);

 unary_operator =
    "&"
  | "*"
  | "+"
  | "-"
  | "~"
  | "!"
  ;

  primary_expression =  p_defined
                      | ID
                      | Number
                      | String
                      | subexpression
                      | logical_or_expression;

 subexpression = "(" >> logical_or_expression >>  ")" ;
 @endverbatim
 <br><br>
 others will be evaluated in called functions
 <br><br>


 @param [in]  expression pre-parsed user expression to check
 @param [out] unknown    user-container for sub-result that
                         the real result is not testable

 @return the result of the analysis as string-structure that may
         symbolise a numeric, boolean, string or unknown result

 @htmlinclude ./des/Prsd_Expression_testExpression.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    13.09.2011   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
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
 _s_TestRet _testUnary(DataAssociation* expression, bool* unknown);


/*!
 evaluate the give expression
 <br><br>
 expressions defined by this grammar will be evaluated directly in this method:
 @verbatim
 multiplicative_expression =                           unary_expression
                             >> *(("*" | "/" | "%") >> unary_expression) ;
 @endverbatim
 <br><br>
 others will be evaluated in called functions
 <br><br>


 @param [in]  expression pre-parsed user expression to check
 @param [out] unknown    user-container for sub-result that
                         the real result is not testable

 @return the result of the analysis as string-structure that may
         symbolise a numeric, boolean, string or unknown result

 @htmlinclude ./des/Prsd_Expression_testExpression.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    13.09.2011   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
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
 _s_TestRet _calcMultiplicative(DataAssociation* expression, bool* unknown);


/*!
 evaluate the give expression
 <br><br>
 expressions defined by this grammar will be evaluated directly in this method:
 @verbatim
 additive_expression =                     multiplicative_expression
                       >> *(("+" | "-") >> multiplicative_expression);
 @endverbatim
 <br><br>
 others will be evaluated in called functions
 <br><br>


 @param [in]  expression pre-parsed user expression to check
 @param [out] unknown    user-container for sub-result that
                         the real result is not testable

 @return the result of the analysis as string-structure that may
         symbolise a numeric, boolean, string or unknown result

 @htmlinclude ./des/Prsd_Expression_testExpression.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    13.09.2011   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
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
 _s_TestRet _calcAdditive(DataAssociation* expression, bool* unknown);


/*!
 evaluate the give expression
 <br><br>
 expressions defined by this grammar will be evaluated directly in this method:
 @verbatim
 shift_expression =                     additive_expression
                    >> *(("<<"|">>") >> additive_expression);
 @endverbatim
 <br><br>
 others will be evaluated in called functions
 <br><br>


 @param [in]  expression pre-parsed user expression to check
 @param [out] unknown    user-container for sub-result that
                         the real result is not testable

 @return the result of the analysis as string-structure that may
         symbolise a numeric, boolean, string or unknown result

 @htmlinclude ./des/Prsd_Expression_testExpression.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    13.09.2011   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
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
 _s_TestRet _calcShift(DataAssociation* expression, bool* unknown);


/*!
 evaluate the give expression
 <br><br>
 expressions defined by this grammar will be evaluated directly in this method:
 @verbatim
 relational_expression =                                    shift_expression
                         >> *( ("<=" | ">=" | "<" | ">") >> shift_expression);
 @endverbatim
 <br><br>
 others will be evaluated in called functions
 <br><br>


 @param [in]  expression pre-parsed user expression to check
 @param [out] unknown    user-container for sub-result that
                         the real result is not testable

 @return the result of the analysis as string-structure that may
         symbolise a numeric, boolean, string or unknown result

 @htmlinclude ./des/Prsd_Expression_testExpression.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    13.09.2011   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
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
 _s_TestRet _testRelational(DataAssociation* expression, bool* unknown);


/*!
 evaluate the give expression
 <br><br>
 expressions defined by this grammar will be evaluated directly in this method:
 @verbatim
 equality_expression =                     relational_expression
                       >> *(("=="|"!=") >> relational_expression);
 @endverbatim
 <br><br>
 others will be evaluated in called functions
 <br><br>


 @param [in]  expression pre-parsed user expression to check
 @param [out] unknown    user-container for sub-result that
                         the real result is not testable

 @return the result of the analysis as string-structure that may
         symbolise a numeric, boolean, string or unknown result

 @htmlinclude ./des/Prsd_Expression_testExpression.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    13.09.2011   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
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
 _s_TestRet _testEquality(DataAssociation* expression, bool* unknown);


/*!
 evaluate the give expression
 <br><br>
 expressions defined by this grammar will be evaluated directly in this method:
 @verbatim
 and_expression =                    equality_expression
                  >> *(("&"-"&&") >> equality_expression);
 @endverbatim
 <br><br>
 others will be evaluated in called functions
 <br><br>


 @param [in]  expression pre-parsed user expression to check
 @param [out] unknown    user-container for sub-result that
                         the real result is not testable

 @return the result of the analysis as string-structure that may
         symbolise a numeric, boolean, string or unknown result

 @htmlinclude ./des/Prsd_Expression_testExpression.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    13.09.2011   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
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
 _s_TestRet _calcAnd(DataAssociation* expression, bool* unknown);


/*!
 evaluate the give expression
 <br><br>
 expressions defined by this grammar will be evaluated directly in this method:
 @verbatim
 exclusive_or_expression =               and_expression
                           >> *(("^") >> and_expression);
 @endverbatim
 <br><br>
 others will be evaluated in called functions
 <br><br>


 @param [in]  expression pre-parsed user expression to check
 @param [out] unknown    user-container for sub-result that
                         the real result is not testable

 @return the result of the analysis as string-structure that may
         symbolise a numeric, boolean, string or unknown result

 @htmlinclude ./des/Prsd_Expression_testExpression.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    13.09.2011   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
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
 _s_TestRet _calcExclusiveOr(DataAssociation* expression, bool* unknown);


/*!
 evaluate the give expression
 <br><br>
 expressions defined by this grammar will be evaluated directly in this method:
 @verbatim
 inclusive_or_expression =                     exclusive_or_expression
                           >> *(("|" -"||") >> exclusive_or_expression);
 @endverbatim
 <br><br>
 others will be evaluated in called functions
 <br><br>


 @param [in]  expression pre-parsed user expression to check
 @param [out] unknown    user-container for sub-result that
                         the real result is not testable

 @return the result of the analysis as string-structure that may
         symbolise a numeric, boolean, string or unknown result

 @htmlinclude ./des/Prsd_Expression_testExpression.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    13.09.2011   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
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
 _s_TestRet _calcInclusiveOr(DataAssociation* expression, bool* unknown);


/*!
 evaluate the give expression
 <br><br>
 expressions defined by this grammar will be evaluated directly in this method:
 @verbatim
logical_and_expression =                      inclusive_or_expression
                         >> *(("&&" - "&") >> inclusive_or_expression);
 @endverbatim
 <br><br>
 others will be evaluated in called functions
 <br><br>


 @param [in]  expression pre-parsed user expression to check
 @param [out] unknown    user-container for sub-result that
                         the real result is not testable

 @return the result of the analysis as string-structure that may
         symbolise a numeric, boolean, string or unknown result

 @htmlinclude ./des/Prsd_Expression_testExpression.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    13.09.2011   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
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
 _s_TestRet _testLogicalAnd(DataAssociation* expression, bool* unknown);


/*!
 evaluate the give expression
 <br><br>
 expressions defined by this grammar will be evaluated directly in this method:
 @verbatim
 logical_or_expression =                     logical_and_expression
                        >> *(("||" - "|") >> logical_and_expression);
 @endverbatim
 <br><br>
 others will be evaluated in called functions
 <br><br>


 @param [in]  expression pre-parsed user expression to check
 @param [out] unknown    user-container for sub-result that
                         the real result is not testable

 @return the result of the analysis as string-structure that may
         symbolise a numeric, boolean, string or unknown result

 @htmlinclude ./des/Prsd_Expression_testExpression.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    13.09.2011   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
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
 _s_TestRet _testLogicalOr(DataAssociation* expression, bool* unknown);













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
                 @I               @I              @I
 @TabEnd
*/
 struct Att
 {
   map<String_imp, String_imp>UserResult;  ///< current user defined check-results
   map<String_imp, String_imp>Constant;    ///< current constants for evaluation
   map<String_imp, String_imp>Replacement; ///< to minimize the text of user-checks
 } Att;

};



#ifndef DOXYGEN
#define USING_NAMESPACE using namespace
//}; USING_NAMESPACE CL_EXPRESSION;
#undef  USING_NAMESPACE
#endif //DOXYGEN






#endif //EXPRESSION_H

