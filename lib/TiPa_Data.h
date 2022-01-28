/*!

 @file
 @brief concrete manager of tree_data
        representing the data of a grammar associated parser-tree

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
    01.09.2015     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    01.09.2015...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/

#ifndef TIPA_DATA_H
#define TIPA_DATA_H

#include "ASS_Data.h"

//#include "TiPa_Concrete.h"
#include "TiPa_Abstract.h"

#include <vector>
#include <map>


using namespace std;


#ifndef DOXYGEN
//namespace TXTDIASM {
//namespace TDA_TinyParser {
//namespace DATA {
#endif //DOXYGEN




/*!
 concrete manager of tree_data representing grammar-results

 this class describes the concrete data content and provides specific
 analysis methods used by the tree-node for actions like filtering
*/
class TiPa_Data:public AssociationData
{

 public:


/// @brief property of a single parser which describe the meaning of the parser for the whole grammar
  typedef struct ParserAttribute_TP
  {
   const char* Identifier; ///< @brief name of the attribute
   const char* Value;      ///< @brief content of the attribute

   /// @brief default constructor
   ParserAttribute_TP(void):
    Identifier(nullptr),
    Value     (nullptr)
   {};
   /*!
    @brief initializing constructor
   */
   ParserAttribute_TP(const char* identifier, const char* value):
    Identifier(identifier),
    Value     (value     )
   {};
   /*!
    @brief copy constructor
    @param [in] src object to copy
   */
   ParserAttribute_TP(const ParserAttribute_TP& src):
    Identifier(src.Identifier),
    Value     (src.Value     )
   {};
   /*!
    @brief assignment operator
    @param [in] src object to copy
    @return copied object
   */
   ParserAttribute_TP& operator = (const ParserAttribute_TP& src)
   {
    Identifier = src.Identifier;
    Value      = src.Value     ;
    return(*this);
   };
   /// @brief destructor
   ~ParserAttribute_TP(void)
   {
   };

  }ParserAttribute_TP;











/*!
 default constructor

 <br><br>

 @htmlinclude ./des/TiPa_Data_TiPa_Data
 .html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    01.09.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  TiPa_Data(void);



/*!
 copy constructor

 <br><br>

 @htmlinclude ./des/TiPa_Data_TiPa_Data
 .html//   map<AssociationData*,int>        ContractorOperand; ///< @brief sub-parser numbers of called parsers

 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    19.03.2017   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 explicit TiPa_Data(TiPa_Data& data);







/*!
  @brief assignment operator

  @param [in] data object to assign

*/
TiPa_Data& operator= (TiPa_Data& data);






/*!
 destructor

 <br><br>

 @htmlinclude ./des/TiPa_Data_TiPa_Data
 .html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    01.09.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
   ~TiPa_Data(void);






/*!
 @brief check if data-pointer points to primary-data declared by concrete class

 If the concrete class implements string-pointers it may be that this strings have to be stored
 as secondary data even they are actually primary data. Once the data should be used this
 method could be used to differ between real secondary data and data that is already known by
 the concrete class.

 @return false if given data is no primary data just stored as secondary data
 <br>    true if given data is not used with a primary pointer of the concrete class

 <br><br>
 @htmlinclude "AssociationData_isRealSecondaryData.html"
 @I_______________________________________________________
    09.04.2017   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual bool isRealSecondaryData(const char* data) override;



/*!
 @brief output of detected text-part

 @return a c-string pointer that points to the data

 @note the user is not allowed to delete the content of the returned string

 @htmlinclude ./des/TiPa_Data_getContent.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    26.09.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
const char* getContent(void);



/*!
 @brief set text line data

 @param number [in] line number


 @htmlinclude ./des/TiPa_Data_lineSet.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    07.10.2017   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  void lineSet(int number);


/*!
 @brief get text line number

 @return number as string


 @htmlinclude ./des/TiPa_Data_lineGet.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    07.10.2017   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  const char* lineGet(void);

/*!
 @brief set text column number

 @param number [in] column number


 @htmlinclude ./des/TiPa_Data_columnSet.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    07.10.2017   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  void columnSet(int number);


/*!
 @brief get text column number

 @return number as string


 @htmlinclude ./des/TiPa_Data_columnGet.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    07.10.2017   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  const char* columnGet(void);


/// @brief return user defined name of the parser that creates this data
// inline void userName_set(const char* userName){if(Parser!=nullptr)Parser->userName_set(userName); else secondaryData_add("UserName", userName);};
// inline void userName_set(const char* userName){if(Parser!=nullptr)Parser->userName_set(userName); else copyString(&UserName, userName);};
 inline void userName_set(const char* userName){copyString(&UserName, userName);};

/// @brief return string representation of user defined parser id
// inline void user_ID_String_set(const char* user_ID_String){if(Parser!=nullptr)Parser->user_ID_String_set(user_ID_String); else secondaryData_add("User_ID_String", user_ID_String);};
// inline void user_ID_String_set(const char* user_ID_String){if(Parser!=nullptr)Parser->user_ID_String_set(user_ID_String); else copyString(&User_ID_String, user_ID_String);};
 inline void user_ID_String_set(const char* user_ID_String){copyString(&User_ID_String, user_ID_String);};

/// @brief return user description of the parser
// inline void userDescription_set(const char* userDescription){if(Parser!=nullptr)Parser->userDescription_set(userDescription); else secondaryData_add("UserDescription", userDescription);};
// inline void userDescription_set(const char* userDescription){if(Parser!=nullptr)Parser->userDescription_set(userDescription); else copyString(&UserDescription, userDescription);};
 inline void userDescription_set(const char* userDescription){copyString(&UserDescription, userDescription);};

/// @brief return user defined name of the parser that creates this data
// inline const char* userName_get(void){if(Parser!=nullptr)return(Parser->userName_get());else return(secondaryData_get("UserName"));};
// inline const char* userName_get(void){if(Parser!=nullptr)return(Parser->userName_get());else return(UserName);};
 inline const char* userName_get(void){if(UserName!=nullptr)return(UserName);else if(Parser!=nullptr)return(Parser->userName_get());else return(nullptr);};

/// @brief return string representation of user defined parser id
// inline const char* user_ID_String_get(void){if(Parser!=nullptr)return(Parser->user_ID_String_get());else return(secondaryData_get("User_ID_String"));};
// inline const char* user_ID_String_get(void){if(Parser!=nullptr)return(Parser->user_ID_String_get());else return(User_ID_String);};
 inline const char* user_ID_String_get(void){if(User_ID_String!=nullptr)return(User_ID_String);else if(Parser!=nullptr)return(Parser->user_ID_String_get());else return(nullptr);};

/// @brief return user description of the parser
// inline const char* userDescription_get(void){if(Parser!=nullptr)return(Parser->userDescription_get());else return(secondaryData_get("UserDescription"));};
 inline const char* userDescription_get(void){if(UserDescription!=nullptr)return(UserDescription);else if(Parser!=nullptr)return(Parser->userDescription_get());else return(nullptr);};

/// @brief return type describing string defined for the parser that's part of the data set
 inline const char* typeString(void){if(Parser!=nullptr)return(Parser->typeString());else return(nullptr);};


typedef enum Attributes
{
  attUserName        = 0,
  attUserID          = 1,
  attUserDescription = 2,
  attLine            = 3,
  attColumn          = 4,
}
Attributes;





   TiPa_Abstract*                   Parser{nullptr};                               ///< @brief parser that creates this data
//   int                              Operand;           ///< @brief sub-parser number inside the calling parser operation
//   map<AssociationData*,int>        ContractorOperand; ///< @brief sub-parser numbers of called parsers
//   map<AssociationData*,int>        ContractorData;    ///< @brief sub-parser numbers of called parsers
   const char*                      Begin{nullptr};                                ///< @brief first character of the detected text-part
   const char*                      End{nullptr};                                  ///< @brief points directly behind the last character of the detected text-part

   TiPa_Abstract::TDA_TiPa_CLASS_TP ParserClass{TiPa_Abstract::TDA_TiPa_Concrete}; ///< @brief parser-class id
   int                              UserID{-1};                                    ///< @brief user defined parser id


 protected:
 private:
  char*       Content{nullptr};                                                    ///< @brief buffer for getContent
  const char* Line{nullptr};                                                       ///< @brief line-number where detected text-part starts
  const char* Column{nullptr};                                                     ///< @brief column-number where detected text-part starts

        char* UserName{nullptr};                                                   ///< @brief user defined name of the parser that creates this data
        char* User_ID_String{nullptr};                                             ///< @brief string representation of user defined parser id
        char* UserDescription{nullptr};                                            ///< @brief user description of the parser

  static const char* Name[37];                                                     ///< @brief names and short descriptions of TiPa parsers
  static const char EmptyString[1];                                                ///< @brief default content of empty strings
  static map<int, const char*> NumberString;                                       ///< @brief container of strings representing integer numbers like lines and columns

 struct Constant
 {
  const char* Line            = "L";
  const char* Column          = "C";
  const char* UserName        = "UserName";
  const char* UserID          = "UserID";
  const char* UserDescription = "UserDescription";


   /// @brief default constructor
   Constant(void):
    Line           ("L"),
    Column         ("C"),
    UserName       ("UserName"),
    UserID         ("UserID"),
    UserDescription("UserDescription")
   {};
   /*!
    @brief copy constructor
    @param [in] src object to copy
   */
   Constant(const Constant& src):
    Line           (src.Line           ),
    Column         (src.Column         ),
    UserName       (src.UserName       ),
    UserID         (src.UserID         ),
    UserDescription(src.UserDescription)
   {};
   /*!
    @brief assignment operator
    @param [in] src object to copy
    @return copied object
   */
   Constant& operator = (const Constant& src)
   {
    Line            = src.Line           ;
    Column          = src.Column         ;
    UserName        = src.UserName       ;
    UserID          = src.UserID         ;
    UserDescription = src.UserDescription;
    return(*this);
   };
   /// @brief destructor
   ~Constant(void)
   {
   };

 }Constant;


};



#ifndef DOXYGEN
#define USING_NAMESPACE using namespace
//}; USING_NAMESPACE DATA;
//}; USING_NAMESPACE TDA_TinyParser;
//}; USING_NAMESPACE TXTDIASM;
#undef  USING_NAMESPACE
#endif //DOXYGEN


#endif // TIPA_DATA_H
