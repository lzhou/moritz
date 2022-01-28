/*!

 @file
 @brief definitions of an abstract parser-class as template
        for tiny parser classes

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
    07.02.2015     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    07.02.2015...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/
#ifndef TIPA_ABSTRACT_H
 #define TIPA_ABSTRACT_H



#include <map>
#include <list>

#include <stdio.h>




using namespace std;

#ifndef DOXYGEN
//namespace TXTDIASM {
//namespace TDA_TinyParser {
#endif //DOXYGEN

class TiPa_Concrete;
class TiPa_Concrete;
class TiPa_Character;
class TiPa_String;
class TiPa_Rule;
class TiPa_Condition;
class TiPa_Sequence;
class TiPa_Counter;




class TiPa_Abstract
{
 friend class TiPa_Concrete;

 public:
  typedef int TiPa_ID;



/// possible parser-classes to create
 typedef enum TDA_TiPa_CLASS_TP
 {
  TDA_TiPa_Concrete    = 0,                ///< not valid parser
  TDA_TiPa_Character   = 1,                ///< character-parser
  TDA_TiPa_String      = 2,                ///< string-parser
  TDA_TiPa_Counter     = 3,                ///< counting parser operation
  TDA_TiPa_Sequence    = 4,                ///< sequence parser-operation
  TDA_TiPa_Condition   = 5,                ///< conditional parser-operation
  TDA_TiPa_Rule        = 6,                ///< call of an other parser or parser operation
 }TDA_TiPa_CLASS_TP;














 /*!
 constructor



 @htmlinclude ./des/TiPa_Abstract_TiPa_Abstract.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    07.02.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 TiPa_Abstract(void);


 /*!
 destructor


 @htmlinclude ./des/TiPa_Abstract__TiPa_Abstract.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    07.02.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  virtual ~TiPa_Abstract(void);






/*!
 @brief cast this object to an object of the type @ref TiPa_Concrete

 @return a pointer to a real existing object if conversion is possible
 @return nullptr if object could not be converted

*/
inline virtual TiPa_Concrete*  as_TiPa_Concrete(void){return(nullptr);};

/*!
 @brief cast this object to an object of the type @ref TiPa_Character

 @return a pointer to a real existing object if conversion is possible
 @return nullptr if object could not be converted

*/
inline virtual TiPa_Character* as_TiPa_Character(void){return(nullptr);};

/*!
 @brief cast this object to an object of the type @ref TiPa_String

 @return a pointer to a real existing object if conversion is possible
 @return nullptr if object could not be converted

*/
inline virtual TiPa_String*    as_TiPa_String   (void){return(nullptr);};

/*!
 @brief cast this object to an object of the type @ref TiPa_Rule

 @return a pointer to a real existing object if conversion is possible
 @return nullptr if object could not be converted

*/
inline virtual TiPa_Rule*      as_TiPa_Rule     (void){return(nullptr);};

/*!
 @brief cast this object to an object of the type @ref TiPa_Condition

 @return a pointer to a real existing object if conversion is possible
 @return nullptr if object could not be converted

*/
inline virtual TiPa_Condition* as_TiPa_Condition(void){return(nullptr);};

/*!
 @brief cast this object to an object of the type @ref TiPa_Sequence

 @return a pointer to a real existing object if conversion is possible
 @return nullptr if object could not be converted

*/
inline virtual TiPa_Sequence*  as_TiPa_Sequence (void){return(nullptr);};

/*!
 @brief cast this object to an object of the type @ref TiPa_Counter

 @return a pointer to a real existing object if conversion is possible
 @return nullptr if object could not be converted

*/
inline virtual TiPa_Counter*   as_TiPa_Counter  (void){return(nullptr);};



 /*!
 @brief return the kind of parser class identifier

 @return parser type identifying number

*/
virtual TDA_TiPa_CLASS_TP id_Type(void) = 0;



 /*!
 return the kind of parser type identifier

 @return parser type identifying number

<br><br>
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    03.12.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
virtual TiPa_ID id_SubType(void) = 0;





/*!
 @brief return type describing string defined for the parser that's part of the data set

 @return the describing string
         or a nullptr pointer if no valid parser is defined



 @htmlinclude ./des/TiPa_Data_typeString
 .html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    04.09.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
virtual const char* typeString(void) = 0;










/// @brief return user defined name of the parser that creates this data
 inline void userName_set(const char* userName){UserName = (char*)userName;};

/// @brief return string representation of user defined parser id
 inline void user_ID_String_set(const char* user_ID_String){User_ID_String = (char*)user_ID_String;};

/// @brief return user description of the parser
 inline void userDescription_set(const char* userDescription){UserDescription = (char*)userDescription;};

/// @brief return user defined name of the parser that creates this data
 inline const char* userName_get(void){return(UserName);};

/// @brief return string representation of user defined parser id
 inline const char* user_ID_String_get(void){return(User_ID_String);};

/// @brief return user description of the parser
 inline const char* userDescription_get(void){return(UserDescription);};

 protected:

 private:

  char*                                    UserName{nullptr};             ///< @brief user defined name of the parser that creates this data
  char*                                    User_ID_String{nullptr};       ///< @brief string representation of user defined parser id
  char*                                    UserDescription{nullptr};      ///< @brief user description of the parser


};



#ifndef DOXYGEN
#define USING_NAMESPACE using namespace
//}; USING_NAMESPACE TDA_TinyParser;
//}; USING_NAMESPACE TXTDIASM;
#undef  USING_NAMESPACE
#endif //DOXYGEN




#endif //TIPA_ABSTRACT_H
