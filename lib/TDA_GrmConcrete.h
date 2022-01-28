/*!

 @file
 @brief definitions of an concrete grammar-class as template
         to manage tiny parser classes and their extensions

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
    10.05.2015     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    10.05.2015...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/
#ifndef TIPAGRM_CONCRETE_H
 #define TIPAGRM_CONCRETE_H



#include "TDA_GrmAbstract.h"

#include "ASS_Model.hpp"


#include "TiPa_Counter.h"
#include "TiPa_Combination.h"
#include "TiPa_Character.h"
#include "TiPa_String.h"
#include "TiPa_Rule.h"




#include<map>
#include<vector>

#include<string>

#include <stdio.h>
#include <cstring>
#include <limits.h>


using namespace std;


class TDA_GrmConcrete:public TDA_GrmAbstract
{

 public:


 /// data stored for optimize or debug the grammar
 typedef struct ParserDebugData_TP
 {
  char* FileName;                       ///< @brief source-file name where the parser was defined
  int   LineNumber;                     ///< @brief source-file location where the parser was defined

  /// @brief default constructor
  ParserDebugData_TP(void):
   FileName  (nullptr),
   LineNumber(-1)
  {};

  /*!
   @brief copy constructor
   @param [in] src object to copy
  */
  ParserDebugData_TP(const ParserDebugData_TP& src):
   FileName  (src.FileName  ),
   LineNumber(src.LineNumber)
  {};
  /*!
   @brief assignment operator
   @param [in] src object to copy
   @return copied object
  */
  ParserDebugData_TP& operator = (const ParserDebugData_TP& src)
  {
   FileName   = src.FileName  ;
   LineNumber = src.LineNumber;
   return(*this);
  };
  /// @brief destructor
  ~ParserDebugData_TP(void)
  {
  };

 }ParserDebugData_TP;

 /// store of meta data defined by the user to identify and to describe a parser
 typedef struct Property_TP
  {
   char* Name;                 ///< used defined name of the parser
   char* Description;          ///< user defined description of the parser
   int   User_ID;              ///< user defined numerical identifier of the parser
   char* User_ID_String;       ///< string of user defined numerical identifier of the parser

  /// @brief default constructor
  Property_TP(void):
   Name          (nullptr),
   Description   (nullptr),
   User_ID       (-1),
   User_ID_String(nullptr)
  {};

  /*!
   @brief copy constructor
   @param [in] src object to copy
  */
  Property_TP(const Property_TP& src):
   Name          (src.Name          ),
   Description   (src.Description   ),
   User_ID       (src.User_ID       ),
   User_ID_String(src.User_ID_String)
  {};
  /*!
   @brief assignment operator
   @param [in] src object to copy
   @return copied object
  */
  Property_TP& operator = (const Property_TP& src)
  {
   Name           = src.Name          ;
   Description    = src.Description   ;
   User_ID        = src.User_ID       ;
   User_ID_String = src.User_ID_String;
   return(*this);
  };
  /// @brief destructor
  ~Property_TP(void)
  {
  };

  }Property_TP;

 /// define part-texts found by a parser
 typedef struct PartText_TP
 {
  const char* Begin;          ///< first character of text-part
  const char* End;            ///< first character behind text-part

  /// @brief default constructor
  PartText_TP(void):
   Begin(nullptr),
   End  (nullptr)
  {};

  /*!
   @brief copy constructor
   @param [in] src object to copy
  */
  PartText_TP(const PartText_TP& src):
   Begin(src.Begin),
   End  (src.End  )
  {};
  /*!
   @brief assignment operator
   @param [in] src object to copy
   @return copied object
  */
  PartText_TP& operator = (const PartText_TP& src)
  {
   Begin = src.Begin;
   End   = src.End  ;
   return(*this);
  };
  /// @brief destructor
  ~PartText_TP(void)
  {
  };

 } PartText_TP;

 /*!
 default constructor

 @param debugMode  forces the grammar to store debug-data if set to true


 <br><br>
 @htmlinclude TDA_GrmConcrete_TDA_GrmConcrete.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    10.05.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
TDA_GrmConcrete(TiPa_Concrete::DataModel* contextModel, bool debugMode = false);









/*!
 @brief  destructor

 <br><br>
 @htmlinclude TDA_GrmConcrete__TDA_GrmConcrete.html

  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    10.05.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  virtual ~TDA_GrmConcrete(void);






/*!
 @brief  initialize the parser

 @param type        identifier of parser-type



<br><br>
 @htmlinclude ./des/TDA_GrmConcrete_init.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    10.05.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void init(void);
























/*!
 @brief  create a parser, store its user data and depending on the debug-mode some debug-data

 @param [in]  classType   parser class to use
 @param [in]  internName  internal name of the new parser
 @param [in]  userName    user-name of the new parser
 @param [in]  id          user identifier of the new parser
 @param [in]  description user description of the new parser
 @param [in]  fileName    file-name of creation for debugging purpose
 @param [in]  lineNumber  file line-number of creation for debugging purpose

 @return  parser to create


 <br><br>
 @htmlinclude ./des/TDA_GrmConcrete_createParser.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    04.07.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
TiPa_Concrete* createParser(TiPa_Concrete::TDA_TiPa_CLASS_TP classType,
                            const char*                      internName,
                            const char*                      userName,
                            int                              id,
                            const char*                      description,
                            const char*                      fileName,
                            int                              lineNumber);


/*!
 @brief convenience macro for calling the method @ref TDA_GrmConcrete::createParser
 to create and insert a new parser

 @param [in]  classType   parser class to use
 @param [out] destination parser to create
 @param [in]  id          user identifier of the new parser
 @param [in]  description user description of the new parser

 following parameters will be defined inside the macro by using __FILE__ and __LINE__
 <br>  fileName    file-name of creation for debugging purpose
 <br>  lineNumber  file line-number of creation for debugging purpose


 <br><br>
 @htmlinclude ./nsd/TDA_GrmConcrete_h_M_CREATE_PARSER.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    04.07.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
#define CREATE_PARSER(classType, destination, id, description)                    \
  classType * destination = dynamic_cast<classType *>(this->createParser(classType::id_Class(),\
                                                      #destination,                      \
                                                      #destination,                      \
                                                      id,                                \
                                                      description,                       \
                                                      __FILE__,                          \
                                                      __LINE__))





/*!
 @defgroup PARSER_SHORT_CUTS Parser Short Cuts

 @brief for a more convenient parser definition

 @{
*/
/// @brief create a character parser
#define CREATE_CHARACTER_PARSER(destination, id, description)                                                 \
  TiPa_Character * destination = dynamic_cast<TiPa_Character *>(this->createParser(TiPa_Character::id_Class(),\
                                                                #destination,                                 \
                                                                #destination,                                 \
                                                                id,                                           \
                                                                description,                                  \
                                                                __FILE__,                                     \
                                                                __LINE__))

/// @brief create a string parser
#define CREATE_STRING_PARSER(destination, id, description)                                           \
  TiPa_String * destination = dynamic_cast<TiPa_String *>(this->createParser(TiPa_String::id_Class(),\
                                                          #destination,                              \
                                                          #destination,                              \
                                                          id,                                        \
                                                          description,                               \
                                                          __FILE__,                                  \
                                                          __LINE__))


/// @brief create a sequence parser
#define CREATE_SEQUENCE_PARSER(destination, id, description)                                               \
  TiPa_Sequence * destination = dynamic_cast<TiPa_Sequence *>(this->createParser(TiPa_Sequence::id_Class(),\
                                                              #destination,                                \
                                                              #destination,                                \
                                                              id,                                          \
                                                              description,                                 \
                                                              __FILE__,                                    \
                                                              __LINE__))


/// @brief create a condition parser
#define CREATE_CONDITION_PARSER(destination, id, description)                                                 \
  TiPa_Condition * destination = dynamic_cast<TiPa_Condition *>(this->createParser(TiPa_Condition::id_Class(),\
                                                                #destination,                                 \
                                                                #destination,                                 \
                                                                id,                                           \
                                                                description,                                  \
                                                                __FILE__,                                     \
                                                                __LINE__))


/// @brief create a counter parser
#define CREATE_COUNTER_PARSER(destination, id, description)                                             \
  TiPa_Counter * destination = dynamic_cast<TiPa_Counter *>(this->createParser(TiPa_Counter::id_Class(),\
                                                            #destination,                               \
                                                            #destination,                               \
                                                            id,                                         \
                                                            description,                                \
                                                            __FILE__,                                   \
                                                            __LINE__))


/// @brief create a rule parser
#define CREATE_RULE_PARSER(destination, id, description)                                       \
  TiPa_Rule * destination = dynamic_cast<TiPa_Rule *>(this->createParser(TiPa_Rule::id_Class(),\
                                                      #destination,                            \
                                                      #destination,                            \
                                                      id,                                      \
                                                      description,                             \
                                                      __FILE__,                                \
                                                      __LINE__))


/*!
 @}
*/







/*!
 @brief  convenience macro for calling the method @ref TDA_GrmConcrete::createParser

 create and insert a new parser without a local object to us it at once

 @param [in]  classType   parser class to use
 @param [out] destination parser to create
 @param [in]  id          user identifier of the new parser
 @param [in]  description user description of the new parser

 following parameters will be defined inside the macro by using __FILE__ and __LINE__
 <br>  fileName    file-name of creation for debugging purpose
 <br>  lineNumber  file line-number of creation for debugging purpose



 <br><br>
 @htmlinclude ./nsd/TDA_GrmConcrete_h_M_DECLEARE_PARSER.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    06.12.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
#define DECLEARE_PARSER(classType, destination, id, description)                    \
                dynamic_cast<classType *>(this->createParser(classType::id_Class(),\
                                               #destination,                      \
                                               #destination,                      \
                                               id,                                \
                                               description,                       \
                                               __FILE__,                          \
                                               __LINE__))






/*!
 @brief  convenience macro for calling the method @ref TDA_GrmConcrete::createParser

 create and insert a new parser defined over an external user-script

 @param [in]  classType   parser class to use
 @param [out] destination parser to create
 @param [in]  name        user-name of the new parser
 @param [in]  id          user identifier of the new parser
 @param [in]  description user description of the new parser
 @param [in]  file        file-name of creation for debugging purpose
 @param [in]  line        file line-number of creation for debugging purpose



 <br><br>
 @htmlinclude ./nsd/TDA_GrmConcrete_h_M_CREATE_USER_PARSER.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    16.10.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
#define CREATE_USER_PARSER(classType, destination, name, id, description,file,line)            \
  classType * destination = dynamic_cast<classType *>(this->createParser(classType::id_Class(),\
                                               name,                                           \
                                               name,                                           \
                                               id,                                             \
                                               description,                                    \
                                               file,                                           \
                                               line))










/*!
 @brief convenience macro for calling the method @ref TDA_GrmConcrete::createParser

 get an existing parser

 @param [in]  classType   parser class to use
 @param [out] destination parser to create
 @param [in]  name        user-name of the new parser

 following parameters will be defined inside the macro by using __FILE__ and __LINE__
 <br>  fileName    file-name of creation for debugging purpose
 <br>  lineNumber  file line-number of creation for debugging purpose



 <br><br>
 @htmlinclude ./nsd/TDA_GrmConcrete_h_M_CREATE_PARSER.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    04.07.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
#define GET_PARSER(classType, destination)                                        \
  classType * destination = dynamic_cast<classType *>(this->createParser(classType::id_Class(),\
                                               #destination,                      \
                                               #destination,                      \
                                               -1,                                \
                                               "",                                \
                                               __FILE__,                          \
                                               __LINE__))



/*!
 @brief  test the given string described with its begin and end

 decide if it starts with a construction defined by the parser,
 a hit will be stored inside the parser and reused to save time.

 @param [in] begin points to the first character of the given string
 @param [in] end   points behind the last  character of the given string
 @param [in] rule  name of the rule if not the main-parser rule should be used

 @return a pointer directly behind the found match if the given string starts
         with the construction defined by the parser.
 @return nullptr if the given string starts not
         with the construction defined by the parser

 @htmlinclude ./des/TDA_GrmConcrete_parse.html

 <br><br>
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    14.05.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
virtual const char * parse(const char* begin, const char* end, const char* rule = nullptr) = 0;



/*!
 @brief  test the given string described with its begin and end

 decide if it contains one or more constructions defined by the parser,
 all hits will be stored inside the parser and reused to save time.

 @param [out] begin points to the first character of the given string
         <br> once the first fitting part-string was found this parameter points
              to its first character
 @param [in]  end   points behind the last character of the given string
 @param [in]  rule  name of the rule if not the main-parser rule should be used

 @return a value behind the given <b>begin</b>  and before the given <b>end</b> that
         points directly to the last part of the given string that hits the
         construction of the parser.
 @return the value of the given <b>end</b> if the given string contains no
         with the construction defined by the parser
 @return nullptr in the case of an error or special event

 @htmlinclude ./des/TDA_GrmConcrete_scan.html

 <br><br>
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    21.12.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
const char * scan(const char* begin, const char* end, const char* rule = nullptr);




/*!

 @brief output a copy of the result-text

 @param [out] textBuffer  provided buffer array to copy the result-text in.
                          if text is a nullptr pointer the function allocates the needed buffer but
                          the user is responsible to delete it correctly to prevent runtime-errors
 @param [in]  size        length of the provided buffer array if given text is no nullptr pointer.
                          if given text is a nullptr pointer size will be ignored.
 @param [in]  begin       points to the first character of the result if known
 @param [in] rule  name of the rule if not the main-parser rule should be used

 @return pointer to result-text, in the case that the given text was just a pointer to nullptr
         the function return is the only possibility to access the result since the parameter text
         is after leaving the function again a pointer to nullptr
 <br><br>
 @htmlinclude ./des/TDA_GrmConcrete_text.html
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    14.05.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 char* text(char* textBuffer = nullptr, int size = -1, const char* begin = nullptr, const char* rule = nullptr);









/*!
 @brief return the parser-tree extended with attributes of the parsers known by
 the grammar that contains all results stored in the parser-dictionary

 @param [in] rule  name of the rule if not the main-parser rule should be used

 @return information about the  complete results of the parser together with
         valid data about the result of its sub-parsers and their sub-parsers
         extended by attributes defined while specifying the grammar


 <br><br>
 @htmlinclude ./des/TDA_GrmConcrete_scanData.html
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    22.12.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd

*/
 TiPa_Concrete::DataFellow* scanData(const char* rule = nullptr);









/*!
 @brief  return the parser-tree extended with attributes of the parsers known by
 the grammar

 @param [in] begin points to the first character of the result if known
 @param [in] rule  name of the rule if not the main-parser rule should be used

 @return information about the result of the parser together with valid data
         about the result of its sub-parsers and their sub-parsers extended
         by attributes defined while specifying the grammar


 <br><br>
 @htmlinclude ./des/TDA_GrmConcrete_treeData.html
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    15.05.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd

*/
 TiPa_Concrete::DataFellow* treeData(const char* begin=nullptr, const char* rule = nullptr);










/*!
 @brief  return the attributes of a parser known by the grammar

 @param [out] returnValue data container to fill
 @param [in]  parser      source of parser describing attributes
 @param [in]  character   actual begin of parser-result

 @return a list of all attributes containing the identifiers as well as the values


 <br><br>
 @htmlinclude ./des/TDA_GrmConcrete_tree.html
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    15.05.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
void attributes(TiPa_Data*       returnValue ,
                TiPa_Concrete*   parser,
                const char*      character);







/*!
 @brief  start the pre parser process to collect common attributes of the give text

 @param [in] begin         points to the first character of the given string
 @param [in] end           points behind the last  character of the given string

 <br><br>
 @htmlinclude ./des/TDA_GrmConcrete_pre_parse.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    01.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
    16.12.2015   @I  Eckard Klotz
 @I base-design
 @I moved from  Spirit185_Internal to TDA_GrmConcrete
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  void pre_parse(const char* begin, const char* end);








/*!
 @brief  output line and column data of the given character if it is located
 in the analysed text.

 @param [out] line      line-number of the given character
 @param [out] column    column-number of the give character
 @param [in]  character character to output the position for
 @param [in]  tabSize   maximum number of spaces replaced by a tab-character

 <br><br>
 @htmlinclude ./des/TDA_GrmConcrete_type.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    01.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
    16.12.2015   @I  Eckard Klotz
 @I base-design
 @I moved from  Spirit185_Internal to TDA_GrmConcrete
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  void getPosition(int* line, int* column, const char* character, int tabSize = 8);






/*!
 @brief  return the data-base used to store normal data around a parser


 @return a reference to the data base

 <br><br>
 @htmlinclude ./des/TDA_GrmConcrete_getParserProperties.html
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    16.12.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
   map<TiPa_Concrete*, Property_TP>* getParserProperties(void);



/*27.04.2016*/
   void contextModel_set(TiPa_Concrete::DataModel* contextModel);




 protected:




/*!
 @brief  convert a string with separators inside into a list of strings

 @param [out] stringList       list to return
 @param [in]  userText         string to convert
 @param [in]  separator        character used to differ between the sub-strings in the text
 @param [in]  clearWhiteSpaces forces the methode to remove white-spaces in the character

 @note the returned list contains new strings which have to be deleted manually
       before the list is cleared and or destroyed.

 <br><br>
 @htmlinclude ./des/TDA_GrmConcrete_string2list.html
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    25.10.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
void string2list(list<string>* stringList ,
                 const char*   userText,
                 char          separator,
                 bool          clearWhiteSpaces=true);


/*!
 @brief convert a string with separators inside into a set of strings

 @param [out] stringSet        set to return
 @param [in]  userText         string to convert
 @param [in]  separator        character used to differ between the sub-strings in the text
 @param [in]  clearWhiteSpaces forces the method to remove white-spaces in the character

 @note the returned set contains new strings which have to be deleted manually
       before the set is cleared and or destroyed.

 <br><br>
 @htmlinclude ./des/TDA_GrmConcrete_string2set.html
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    25.10.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
void string2set(set<string>* stringSet ,
                const char*  userText,
                char         separator,
                bool         clearWhiteSpaces=true);


/*!
 @brief return the parser with the given name and type

 @param [in]  name      user defined parser-name
 @param [in]  classType type of parser

 @return a parser reference
 <br>    nullptr if parser is not existing
 <br><br>
 @htmlinclude ./des/TDA_GrmConcrete_parser_Get.html
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    26.11.2016   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 TiPa_Concrete* parser_Get(const string&                    name,
                           TiPa_Concrete::TDA_TiPa_CLASS_TP classType = TiPa_Concrete::TDA_TiPa_Rule);


/*!
 @brief return the user defined properties of the parser with the given name and type

 @param [in]  name      user defined parser-name
 @param [in]  classType type of parser

 @return user defined id-number if parser exists
 <br>    given default-id if parser is not existing
 <br><br>
 @htmlinclude ./des/TDA_GrmConcrete_property_UserID_Get.html
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    26.11.2016   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
Property_TP property_Get(const string&                    name,
                         TiPa_Concrete::TDA_TiPa_CLASS_TP classType = TiPa_Concrete::TDA_TiPa_Rule);




/*!
 @brief return the user defined id-number of the parser with the given name and type

 @param [in]  name      user defined parser-name
 @param [in]  defaultID return-value in the case that a parser with the given name is not existing
 @param [in]  classType type of parser

 @return user defined id-number if parser exists
 <br>    given default-id if parser is not existing
 <br><br>
 @htmlinclude ./des/TDA_GrmConcrete_property_UserID_Get.html
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    26.11.2016   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
int property_UserID_Get(const string&                    name,
                        int                              defaultID = INT_MIN,
                        TiPa_Concrete::TDA_TiPa_CLASS_TP classType = TiPa_Concrete::TDA_TiPa_Rule);




/*!
  @brief  attributes of class
*/
  struct Att
  {
   bool                                    DebugMode;         ///< @brief true forces to store additional data

   map<TiPa_Concrete*, ParserDebugData_TP> ParserDebugData;   ///< @brief data-base used to store debug data around a parser

   map<string,TiPa_Rule*>                  ParserRule;        ///< @brief language specific rules defined by user
   map<string,TiPa_Character*>             ParserCharacter;   ///< @brief takes care about created character parsers
   map<string,TiPa_String*>                ParserString;      ///< @brief takes care about created string parsers
   map<string,TiPa_Counter*>               ParserCounter;     ///< @brief takes care about created counter parsers
   map<string,TiPa_Sequence*>              ParserSequence;    ///< @brief takes care about created sequence parsers
   map<string,TiPa_Condition*>             ParserCondition;   ///< @brief takes care about created condition parsers

   map<TiPa_Concrete*, Property_TP>        Property;          ///< @brief data-base used to store normal data around a parser

   TiPa_Concrete*                          MainParser;        ///< @brief parser used to start main parsing process with
   TiPa_Concrete*                          SkipParser;        ///< @brief parser used to define those text-parts to ignore while parsing
   TiPa_Concrete*                          LineParser;        ///< @brief parser used to identify the begin of a new line

   list<const char*>                       LineBegin;         ///< @brief all positions of line-begins
   list<const char*>::iterator             LineCurrent;       ///< @brief current line to analyse

   map<const char*, const char*>           LineEnd;           ///< @brief corresponding lien-Ends
   map<const char*, int>                   LineNumber;        ///< @brief contains the number of the newline begins
   const char*                             TextBegin;         ///< @brief begin of the given text
   const char*                             TextEnd;           ///< @brief end of the given text

   TiPa_Concrete::DataModel*               ContextModel;      ///< @brief manages the analysed data

  /// @brief default constructor
  Att(void):
   DebugMode      (false  ),
   MainParser     (nullptr),
   SkipParser     (nullptr),
   LineParser     (nullptr),
   TextBegin      (nullptr),
   TextEnd        (nullptr),
   ContextModel   (nullptr)
  {};

  /*!
   @brief copy constructor
   @param [in] src object to copy
  */
  Att(const Att& src):
   DebugMode      (src.DebugMode      ),
   ParserDebugData(src.ParserDebugData),
   ParserRule     (src.ParserRule     ),
   ParserCharacter(src.ParserCharacter),
   ParserString   (src.ParserString   ),
   ParserCounter  (src.ParserCounter  ),
   ParserSequence (src.ParserSequence ),
   ParserCondition(src.ParserCondition),
   Property       (src.Property       ),
   MainParser     (src.MainParser     ),
   SkipParser     (src.SkipParser     ),
   LineParser     (src.LineParser     ),
   LineBegin      (src.LineBegin      ),
   LineCurrent    (src.LineCurrent    ),
   LineEnd        (src.LineEnd        ),
   LineNumber     (src.LineNumber     ),
   TextBegin      (src.TextBegin      ),
   TextEnd        (src.TextEnd        ),
   ContextModel   (src.ContextModel   )
  {};

  /*!
   @brief assignment operator
   @param [in] src object to copy
   @return copied object
  */
  Att& operator = (const Att& src)
  {
   DebugMode       = src.DebugMode      ;
   ParserDebugData = src.ParserDebugData;
   ParserRule      = src.ParserRule     ;
   ParserCharacter = src.ParserCharacter;
   ParserString    = src.ParserString   ;
   ParserCounter   = src.ParserCounter  ;
   ParserSequence  = src.ParserSequence ;
   ParserCondition = src.ParserCondition;
   Property        = src.Property       ;
   MainParser      = src.MainParser     ;
   SkipParser      = src.SkipParser     ;
   LineParser      = src.LineParser     ;
   LineBegin       = src.LineBegin      ;
   LineCurrent     = src.LineCurrent    ;
   LineEnd         = src.LineEnd        ;
   LineNumber      = src.LineNumber     ;
   TextBegin       = src.TextBegin      ;
   TextEnd         = src.TextEnd        ;
   ContextModel    = src.ContextModel   ;
   return(*this);
  };

  /// @brief destructor
  ~Att(void)
  {
   ParserDebugData.clear();
   ParserRule     .clear();
   ParserCharacter.clear();
   ParserString   .clear();
   ParserCounter  .clear();
   ParserSequence .clear();
   ParserCondition.clear();
   Property       .clear();
   LineBegin      .clear();
   LineEnd        .clear();
   LineNumber     .clear();
  };







 }Att;




 private:


 /*!
 extent the data-content of the given sponsor node by adding grammar associated knowledge
 and repeat this for its contractors

 @param [in] sponsor        parser result-tree of a


 <br><br>
 @htmlinclude ./des/TDA_GrmConcrete_treeDataSub.html
 @I_______________________________________________________
    17.05.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void treeDataSub(TiPa_Concrete::DataAssociation* sponsor,
                  TiPa_Concrete::Hit_TP*          parserTree);



};





#endif //TIPAGRM_CONCRETE_H
