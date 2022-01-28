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
    09.09.2015     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    09.09.2015...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/

#ifndef TIPA_SEARCH_H
#define TIPA_SEARCH_H

#include <stdio.h>

#include "ASS_Visitor.hpp"
#include "TiPa_Data.h"

using namespace std;


#ifndef DOXYGEN
//namespace TXTDIASM {
//namespace TDA_TinyParser {
//namespace DATA {
#endif //DOXYGEN



/*!
 @brief concrete visitor to search for a tree-node defined by an index-path
*/
class TiPa_Search:public AssociationVisitor<TiPa_Data*, nullptr>
{
 public:


 /// search mode of this visitor
 typedef enum SearchMode_TP
 {
  Index,                   ///< evaluate the position inside a fellow-ship chain
//  Operand,                 ///< evaluate the operand number
  UserName,                ///< evaluate the parser-name given by the user
  UserID,                  ///< evaluate the parser id-number given by the user
  Content,                 ///< evaluate the string between Begin and End
  SearchMode_DF = Content, ///< for initialisation purposes => valid
  SearchMode_NV,           ///< for initialisation purposes => not valid
 }SearchMode_TP;


 typedef Association<TiPa_Data*, nullptr>        DataAssociation;
 typedef AssociationVisitor<TiPa_Data*,nullptr>  TiPa_Visitor;



/*!
 default constructor

 <br><br>

 @htmlinclude ./des/TiPa_Search_TiPa_Search.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    09.09.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  TiPa_Search(void);


/*!
 specifying constructor

 @param [in] mode         kind of search
 @param [in] path         filter data used to evaluate the data
 @param [in] separator    character used to split between the names in the
                          given type-path
 @param [in] indexStart   to initialize the call counter with the fellowship-index
                          of current association


 @htmlinclude ./des/TiPa_Search_TiPa_Search.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    09.09.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  TiPa_Search(SearchMode_TP mode, const char* path, char separator ='/', int indexStart = 0);


/*!
  @brief copy constructor

  @param [in] visitor object to assign

*/
 TiPa_Search(const TiPa_Search& visitor);



/*!
 default destructor
 @htmlinclude ./des/TiPa_SearchTiPa_Search.html

 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    09.09.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/

 virtual  ~TiPa_Search(void);



/*!
  @brief assignment operator

  @param [in] visitor object to assign

*/
TiPa_Search& operator= (const TiPa_Search& visitor);



/*!
 initialize this visitor

 @param [in] mode         kind of search
 @param [in] path         filter data used to evaluate the data
 @param [in] separator    character used to split between the names in the
                          given type-path
 @param [in] indexStart   to initialize the call counter with the fellowship-index
                          of current association

 @htmlinclude ./des/TiPa_Search_init.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    09.09.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void init(SearchMode_TP mode, const char* path, char separator ='/', int indexStart = 0);







/*!
 initialize this visitor

 @param [in] mode         kind of search
 @param [in] path         filter data used to evaluate the data
 @param [in] separator    character used to split between the names in the
                          given type-path
 @param [in] indexStart   to initialize the call counter with the fellowship-index
                          of current association

 @return pointer to initialized class-object

 @htmlinclude ./des/TiPa_Search_operator().html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    27.09.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 TiPa_Search* operator()(SearchMode_TP mode, const char* path, char separator ='/', int indexStart = 0);



/*!
 initialize this visitor

 @param [in] mode         kind of search
 @param [in] number       filter data used to evaluate the data

 @return pointer to initialized class-object

 @htmlinclude ./des/TiPa_Search_operator().html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    10.10.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
 TiPa_Search* operator()(SearchMode_TP mode, long number);
*/










/*!
 reinitialize the call-counter

 @param [in] indexStart   to initialize the call counter with the fellowship-index
                          of current association

 @htmlinclude ./des/TiPa_Search_setCallCounter.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    09.09.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void setCallCounter(int indexStart);








// @param sponsor the sponsor of the association to analyse


/*!
 start to evaluate an association

 @param node    the association to analyse


 @htmlinclude ./des/TiPa_Search_evaluate.html

 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    09.09.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
DirectionOfIteration evaluate(DataAssociation* node/*, DataAssociation* sponsor*/);





 protected:

 private:


/*!
 implements details of index evaluation

 @param [in] node the tree-node to analyse
 @param [in] word reference-value to search for

 @return true  if node hits search criteria
 <br>    false if not

 @htmlinclude ./des/TiPa_Search_evaluateIndex.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    09.09.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 bool evaluateIndex(DataAssociation* node, const char* word);

/* !
 implements details of operand evaluation

 @param [in] node the tree-node to analyse
 @param [in] word reference-value to search for

 @return true  if node hits search criteria
 <br>    false if not

 @htmlinclude ./des/TiPa_Search_welcome.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    09.09.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
bool evaluateOperand(DataAssociation* node, const char* word);
*/

/*!
 implements details of content evaluation

 @param [in] node the tree-node to analyse
 @param [in] word reference-value to search for

 @return true  if node hits search criteria
 <br>    false if not

 @htmlinclude ./des/TiPa_Search_evaluateContent.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    09.09.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 bool evaluateContent(DataAssociation* node, const char* word);



/*!
 implements details of user-name evaluation

 @param [in] node the tree-node to analyse
 @param [in] word reference-value to search for

 @return true  if node hits search criteria
 <br>    false if not

 @htmlinclude ./des/TiPa_Search_evaluateUserName.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    27.09.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 bool evaluateUserName(DataAssociation* node, const char* word);




/*!
 implements details of user id evaluation

 @param [in] node the tree-node to analyse
 @param [in] word reference-value to search for

 @return true  if node hits search criteria
 <br>    false if not

 @htmlinclude ./des/TiPa_Search_welcome.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    10.10.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
bool evaluateUserID(DataAssociation* node, const char* word);











 struct Att
 {
  SearchMode_TP               Mode;            ///< mode of search and evaluation
  list<const char*>           Path;            ///< reference data used for content-search
  list<const char*>::iterator Word;            ///< current part of the path
  DirectionOfIteration        CommonDirection; ///< stores the direction to iterate while temporary changes
  int                         CallCounter;     ///< counts how many times the evaluation was called,
                                               ///< will be used for index evaluation
//  long                        FilterNumber;    ///< reference data used for numerical search

  /// @brief default constructor
  Att(void):
      Mode(SearchMode_DF),
      Path(),
      Word(),
      CommonDirection(IterateAsBefore),
      CallCounter(0)
      {};
  /*!
   @brief copy constructor
   @param [in] src object to copy
  */
  Att(const Att& src):
   Mode           (src.Mode           ),
   Path           (src.Path           ),
   Word           (src.Word           ),
   CommonDirection(src.CommonDirection),
   CallCounter    (src.CallCounter    )
  {};
  /*!
   @brief assignment operator
   @param [in] src object to copy
   @return copied object
  */
  Att& operator = (const Att& src)
  {
   Mode            = src.Mode           ;
   Path            = src.Path           ;
   Word            = src.Word           ;
   CommonDirection = src.CommonDirection;
   CallCounter     = src.CallCounter    ;
   return(*this);
  };
  /// @brief destructor
  ~Att(void)
  {
   Path.clear();
  };

 }Att;


};



#ifndef DOXYGEN
#define USING_NAMESPACE using namespace
//}; USING_NAMESPACE DATA;
//}; USING_NAMESPACE TDA_TinyParser;
//}; USING_NAMESPACE TXTDIASM;
#undef  USING_NAMESPACE
#endif //DOXYGEN


#endif // TIPA_SEARCH_H

