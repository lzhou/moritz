/*!

 @file
 @brief definitions of an abstract grammar-class as template
         to manage tiny parser classes and their extensions

 Copyright (C) 2015-2017 by Eckard Klotz.

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
#ifndef TIPAGRM_ABSTRACT_H
 #define TIPAGRM_ABSTRACT_H

#include "TiPa_Concrete.h"


#include<map>
#include<list>

#include <stdio.h>



using namespace std;

#ifndef DOXYGEN
//namespace TXTDIASM {
//namespace TDA_Grammar {
#endif //DOXYGEN


class TDA_GrmAbstract
{
 friend class TDA_GrmConcrete;

 public:



//  /// property of a single parser which describe the meaning of the parser
//  /// for the whole grammar
//  typedef struct ParserAttribute_TP
//  {
//   const char* Identifier; ///< name of the attribute
//   const char* Value;      ///< content of the attribute
//  }ParserAttribute_TP;

//  /// extended parser-tree that contains the grammar specific properties of a
//  /// the parser responsible for detecting one node.
//  typedef struct GrammarResult
//  {
//   const char*                      Type;            ///< parser-type
//   int                              SubType;         ///< parser-type id
//   TiPa_Concrete::TDA_TiPa_CLASS_TP ParserClass;     ///< parser-class id
//   int                              UserID;          ///< user defined parser id
//   int                              ManagerOperand;  ///< order number of parser inside a parser operation
//   list<ParserAttribute_TP>         ParserAttribute; ///< grammar associated properties of the detecting parses
//   const char*                      Begin;           ///< first character of the detected text-part
//   const char*                      End;             ///< points directly behind the last character of the detected text-part
//   list<GrammarResult*>             Contractor;           ///< part-result of the contractor-parsers
//   GrammarResult*                   ManagerNode;       ///< manager-node in the grammar result tree
// }GrammarResult;






 /*!
 constructor
 <br><br>
 @htmlinclude TDA_GrmAbstract_TDA_GrmAbstract.html
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
 TDA_GrmAbstract(void);


 /*!
 destructor
 <br><br>
 @htmlinclude "TDA_GrmAbstract__TDA_GrmAbstract.html"
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
  virtual ~TDA_GrmAbstract(void);
























 protected:

 private:



};



#ifndef DOXYGEN
#define USING_NAMESPACE using namespace
//}; USING_NAMESPACE TDA_Grammar;
//}; USING_NAMESPACE TXTDIASM;
#undef  USING_NAMESPACE
#endif //DOXYGEN




#endif //TIPAGRM_ABSTRACT_H
