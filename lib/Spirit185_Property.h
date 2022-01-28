/*!

 @file
 @brief search for a association with specific data

 Copyright (C) 2015-2020 by Eckard Klotz.

 Permission to use, copy, modify, and distribute this software and its
 documentation under the terms of the GNU General Public License is hereby
 granted. No representations are made about the suitability of this software
 for any purpose. It is provided "as is" without express or implied warranty.
 See the GNU General Public License for more details.

 Documents produced by this add-on functions are derivative works derived from
 the input used in their production; they are not affected by this license.

 <b> History </b>

 @TabBegin
    date           @I author          @I implementation/change
 @I____________________________________________________________
    02.07.2016     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    02.07.2016...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/

#ifndef SPIRIT185_PROPERTY_H
#define SPIRIT185_PROPERTY_H

#include <stdio.h>
#include <map>
#include <string>

#include "TiPa_Data.h"

#include "ASS_Model.hpp"
#include "Spirit185_Data.h"


 #include "xml_DataModel.h"


using namespace std;


#ifndef DOXYGEN
//namespace TXTDIASM {
//namespace TDA_Grammar {
//namespace DATA {
#endif //DOXYGEN



/*!
 @brief concrete visitor to search for a tree-node defined by an index-path
*/
class Spirit185_Property
{
 public:
 typedef AssociationModel<Spirit185_Data, nullptr> Spirit185_DataModel;
 typedef Spirit185_Data::Spirit185_DataAssociation Spirit185_DataAssociation;

/*!
 default constructor

 <br><br>

 @htmlinclude ./des/Spirit185_Property_Spirit185_Property.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    02.07.2016   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  Spirit185_Property(void);

// @param [in]  sponsor                the sponsor of the association to analyse

/*!
 specifying constructor

 @param [in]  source                 the association to analyse
 @param [in]  notPhrased             set of rules which have the property to be not phrased
 @param [in]  separator              character used to separate single rule-names in the given list
 @param [in]  grammarTextIdentifier  user defined name of a file used to store the analysed data
 @param [in]  limitCallingTree       maximum number of calling-levels to analyse
 @param [in]  limitCallingNode       maximum number of calling rules  to analyse
 @param [in]  limitCallerTree        maximum number of caller-levels  to analyse
 @param [in]  limitCallerNode        maximum number of caller rules   to analyse


 @htmlinclude ./des/Spirit185_Property_Spirit185_Property.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    02.07.2016   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  Spirit185_Property(TiPa_Concrete::DataAssociation*       source,
//                     TiPa_Concrete::DataAssociation*       sponsor,
                     const char* notPhrased,   char separator,
                     const char*                    grammarTextIdentifier,
                     int limitCallingTree = 5, int  limitCallingNode = 30,
                     int limitCallerTree = 5,  int  limitCallerNode = 30);

/*!
 default destructor



 @htmlinclude ./des/Spirit185_Property__Spirit185_Property.html

 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    02.07.2016   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/

 virtual  ~Spirit185_Property(void);










 protected:

 private:


/*!
 @brief create the map of rules and start the basic analysis of the rules

 @param [in]  source   data-object that describes the rule-expression

 @htmlinclude ./des/Spirit185_Property_evaluate_Rule.html

 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    07.08.2016   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void evaluate_Rule(TiPa_Concrete::DataAssociation* source);






/*!
 @brief add a root node for the reserved-rule to the rule dictionary @ref Att::Rule

 The reserved rule will not be defined by user but by while the grammar-analysis.
 It contains as an alternative-condition all key-words used in all other rules.
 Usually this key-words are not reusable as an ID, thus the the rule <b> reserved</b>
 will be used to define NON-IDs.

 @param [in]  source   data-object used as core object for the new node-data

 @post the rule-dictionary contains a rudimentary reserved-rule definition usable
 while analysing the used rules of all grammar rules.

 @htmlinclude ./des/Spirit185_Property_createReserved.html

 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    30.08.2016   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
void createReserved(TiPa_Concrete::DataAssociation* source);


/*!
 @brief add the expression node to the reserved-rule by analysing the dictionary @ref Att::ReservedWords

 The reserved rule will not be defined by user but by while the grammar-analysis.
 It contains as an alternative-condition all key-words used in all other rules.
 Usually this key-words are not reusable as an ID, thus the the rule <b> reserved</b>
 will be used to define NON-IDs.

 @param [in]  source   data-object used as core object for the new node-data

 @pre all grammar rules have to be analysed at least to fill the dictionary @ref ReservedWords
 @post the dictionary @ref Rule contains now a reserved rule definition complete
       enough to define its properties and callers. Callings have not to be analysed.


 @htmlinclude ./des/Spirit185_Property_fillReserved.html

 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    03.09.2016   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
void expressionReserved(TiPa_Concrete::DataAssociation* source);












/*!
 create rule associated data-base part

 @param [in]  identifier   data-object that describes the rule-identifier
 @param [in]  expression   data-object that describes the rule-expression

 @return root of new data-tree  if creation was successful
 <br>    nullptr                if given source could not be analysed

 @htmlinclude ./des/Spirit185_Property_evaluate_Expression.html

 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    17.07.2016   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
Spirit185_Data::Spirit185_DataAssociation* evaluate_isUsing(TiPa_Concrete::DataAssociation*             identifier,
                                                            TiPa_Concrete::DataAssociation*             expression);







// @param [in]  sponsor     the sponsor of the association to analyse

/*!
 create data-base from external association

 @param [out] usedRules   list of rule identifiers called by the current rule
 @param [out] destination the association that should keep the result
 @param [in]  source      the association to analyse

 @return root of new data-tree  if creation was successful
 <br>    nullptr                if given source could not be analysed

 @htmlinclude ./des/Spirit185_Property_evaluate_Expression.html

 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    04.07.2016   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
Spirit185_Data::Spirit185_DataAssociation* evaluate_Expression(set<Spirit185_Data::Spirit185_DataAssociation*>* usedRules,
                                                    Spirit185_Data::Spirit185_DataAssociation*       destination,
                                                    TiPa_Concrete::DataAssociation*       source/*,
                                                    TiPa_Concrete::DataAssociation*       sponsor*/);





/*
 @return true if a direct or indirect using was found
 <br>    false if no usage was found
*/
/*!
 evaluate if the rule given as ruleName is using the rule given as
 searchTag directly or indirectly(used by an directly used rule
 or used by a rule directly used by a used rule or...)

 @htmlinclude ./des/Spirit185_Property_evaluate_isUsedBy.html

 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    21.07.2016   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  void evaluate_isUsedBy(void);





/*!
 @brief analyse how rules will be called by other rules
        to create calling and caller rules

 @param notPhrased        list of not phrased rule-names
 @param separator         character used to separate single rule-names in the given list
 @param limitCallingTree  maximum number of calling-levels to analyse
 @param limitCallingNode  maximum number of calling rules to analyse
 @param limitCallerTree   maximum number of caller-levels to analys
 @param limitCallerNode   maximum number of caller rules to analyse


 @htmlinclude ./des/Spirit185_Property_evaluate_Collaboration.html

 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    13.08.2016   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
void evaluate_Collaboration(const char* notPhrased, char separator,
                            int limitCallingTree,   int  limitCallingNode ,
                            int limitCallerTree,    int  limitCallerNode) ;






/*!
 checks each parser-rule if it depends only on other rules without
 recursions to itself and defines for those a level-value that stands
 for the longest tree-path until basic-parsers are used only


 @param rule       root association of the tree to analyse
 @param property   association that should carry the level-result
 @param calling    root association of the calling-tree
 @param limitTree  maximum number of tree-levels which should be analysed
 @param limitNode  maximum number of called nodes which should be analysed


 @htmlinclude ./des/Spirit185_Property_evaluate_Calling.html

 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    13.08.2016   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
void evaluate_Calling(Spirit185_Data::Spirit185_DataAssociation* rule,
                      Spirit185_Data::Spirit185_DataAssociation* property,
                      Spirit185_Data::Spirit185_DataAssociation* calling,
                      int                                        limitTree,
                      int                                        limitNode);



/*!
 @brief recursive analysis of calling rules to create the calling-tree


 @param   alreadyChecked rules checked while the current recursive calling chain
          <br>           used to avoid endless-loops while recursive analysis
 @param   alreadyKnown   rules checked while traversing the whole calling-tree
          <br>           used to avoid double edges in calling-diagram
 @param   searchObject   root-rule that should be called direct or indirect
 @param   rule           current called rule
 @param   calling        local root of the sub calling-tree
 @param   limitTree      maximum number of tree-levels which should be analysed
 @param   limitNode      maximum number of called nodes which should be analysed

 @return  >=0 -> number of levels found while analysis
 <br>      -1 -> rule called by itself directly or indirectly
 <br>      -2 -> analysis reached given limits of analysis

 @htmlinclude ./des/Spirit185_Property_check_Calling.html

 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    07.08.2016   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
int check_Calling(set<Spirit185_Data::Spirit185_DataAssociation*>* alreadyChecked,
                  set<Spirit185_Data::Spirit185_DataAssociation*>* alreadyKnown,
                  Spirit185_Data::Spirit185_DataAssociation*       searchObject,
                  Spirit185_Data::Spirit185_DataAssociation*       rule,
                  Spirit185_Data::Spirit185_DataAssociation*       calling,
                  int                                              limitTree,
                  int                                              limitNode);




/*!
 checks each parser-rule if it depends only on other rules without
 recursions to itself and defines for those a level-value that stands
 for the longest tree-path until basic-parsers are used only



 @param rule       root association of the tree to analyse
 @param property   association that should carry the level-result
 @param called     root association of the called-tree
 @param limitTree  maximum number of tree-levels which should be analysed
 @param limitNode  maximum number of calling nodes which should be analysed


 @htmlinclude ./des/Spirit185_Property_evaluate_Called.html

 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    13.08.2016   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
void evaluate_Caller(Spirit185_Data::Spirit185_DataAssociation* rule,
                     Spirit185_Data::Spirit185_DataAssociation* property,
                     Spirit185_Data::Spirit185_DataAssociation* caller,
                     int                                        limitTree,
                     int                                        limitNode);

/*!
 @brief recursive analysis of calling rules to create the caller-tree


 @param   alreadyChecked rules checked while the current recursive caller chain
          <br>           used to avoid endless-loops while recursive analysis
 @param   alreadyKnown   rules checked while traversing the whole caller-tree
          <br>           used to avoid double edges in caller-diagram
 @param   searchObject   root-rule that should be called direct or indirect
 @param   dataUsing      data of current calling rule (may be deleted since rule is parameter also)
 @param   rule           current calling rule
 @param   property       (should be deleted since not used any more)
 @param   called         local root of the sub caller-tree
 @param   limitTree      maximum number of tree-levels which should be analysed
 @param   limitNode      maximum number of calling nodes which should be analysed

 @return  >=0 -> number of levels found while analysis
 <br>      -1 -> rule calls itself directly or indirectly
 <br>      -2 -> analysis reached given limits of analysis

 @htmlinclude ./des/Spirit185_Property_check_Caller.html

 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    07.08.2016   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
int check_Caller(set<Spirit185_Data::Spirit185_DataAssociation*>* alreadyChecked,
                 set<Spirit185_Data::Spirit185_DataAssociation*>* alreadyKnown,
                 Spirit185_Data::Spirit185_DataAssociation*       searchObject,
                 Spirit185_Data::Spirit185_DataAssociation*       rule,
                 Spirit185_Data::Spirit185_DataAssociation*       called,
                 int                                 limitTree,
                 int                                 limitNode);








/*!
  @brief alphanumeric  but not case-sensitive compare of two c-strings


 @param String1 first string
 @param String2 second string

 @return true  after a sequence of equivalent characters:
 <br>          the character of the first string comes
               before the character of the second string
 <br>          or the the first strings ends before the second string
 <br>          or both strings are the same.
 <br>    false in other cases

 @htmlinclude ./des/Spirit185_Property_.html

 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    14.08.2016   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
static bool compareIdentifier(const char* String1, const char* String2);






/*!
 return the symbol used in the rule-map as key-value

 Actually the key-value is the string-pointer itself thus other strings with the same
 content will not work as key. This method compares the given string-content with the
 content of all strings used as keys and returns the pointer of the found one.

 @param ruleName string of a grammar-rule name that has to be listed in the map  @ref Rule
 @return key-value of the given name if it is listed in the map  @ref Rule otherwise nullptr

 @htmlinclude ./des/Spirit185_Property_getRuleKey.html

 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    07.08.2016   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
const char*  getRuleKey(const char* ruleName);








/*!
 @brief stores current content of data-base object in an xml-file

 @param file name and its folder-path of destination file


 @htmlinclude ./des/Spirit185_Property_storeDataBaseAsXMLhtml

 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
   10.07.2016   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void storeDataBaseAsXML(const char* file);



/*!
 @brief transform data-base content to xml-format

 @param destination xml-node to fill with content
 @param source      data-base node to analyse

 @htmlinclude ./des/Spirit185_Property_transformDataBaseToXML.html

 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
   10.07.2016   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void transformDataBaseToXML(XML_Node destination, Spirit185_Data::Spirit185_DataAssociation* source);





 struct Att
 {
  Spirit185_DataModel                                         ContextModel;  ///< @brief manages the analysed data
  TiPa_Concrete::DataModel                                    TiPa_Context;  ///< @brief manages the analysed data
  Spirit185_Data::Spirit185_DataAssociation*                  DataBase;      ///< @brief reference-node for analysis or pointer to a node found

  map<const char*,Spirit185_Data::Spirit185_DataAssociation*> Rule;          ///< @brief dictionary of rule names identified by numbers

  map<const char*,Spirit185_Data::Spirit185_DataAssociation*> ReservedWords; ///< @brief collect key-words to create rule of reserved words


  /// @brief default constructor
  Att(void):
   DataBase(nullptr)
  {};

  /*!
   @brief copy constructor
   @param [in] src object to copy
  */
  Att(const Att& src):
//   ContextModel (src.ContextModel ),
//   TiPa_Context (src.TiPa_Context ),
   DataBase     (src.DataBase     ),
   Rule         (src.Rule         ),
   ReservedWords(src.ReservedWords)
  {};

  /*!
   @brief assignment operator
   @param [in] src object to copy
   @return copied object
  */
  Att& operator = (const Att& src)
  {
//   ContextModel  = src.ContextModel ;
//   TiPa_Context  = src.TiPa_Context ;
   DataBase      = src.DataBase     ;
   Rule          = src.Rule         ;
   ReservedWords = src.ReservedWords;
   return(*this);
  };

  /// @brief destructor
  ~Att(void)
  {
   Rule         .clear();
   ReservedWords.clear();
  };

 }Att;


};



#ifndef DOXYGEN
#define USING_NAMESPACE using namespace
//}; USING_NAMESPACE DATA;
//}; USING_NAMESPACE TDA_Grammar;
//}; USING_NAMESPACE TXTDIASM;
#undef  USING_NAMESPACE
#endif //DOXYGEN


#endif // SPIRIT185_PROPERTY_H

