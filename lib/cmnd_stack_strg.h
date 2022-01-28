/*!

 @file
 @brief  definition of a collection of snippet-commands to organize a stack

 This file contains special snippet-commands used to manage a stack
 used as tmporary lifo-memory for part-results

 Copyright (C) 2008-2018 by Eckard Klotz.

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
    11.06.2011     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    11.06.2011...  @I Eckard Klotz
 @I Changes are documented in the comment of the changed element
 @TabEnd

*/
#ifndef CMND_STACK_STRG_H
#define CMND_STACK_STRG_H


#include <map>

using namespace std;



#include "snippet.h"
#include "command.h"





#ifndef DOXYGEN
//namespace CL_COMMAND {
//namespace CL_CMND_STACK_STRG {
#endif //DOXYGEN



/*!
 @brief Concrete command to construct snipet content by temporary buffering.

 @history
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    27.8.2008   @I  Eckard Klotz @I First Implementation @I
 @I_______________________________________________________
    26.02.2012   @I  Eckard Klotz
 @I implementation of stack for xml-data
 @I renaming the class from Cmnd_Stack to Cmnd_Stack_Strg
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/

class Cmnd_Stack_Strg:public Cmnd_Common
{
 public:



/*!
 construktor
 <br><br>
 @htmlinclude Cmnd_Stack_Strg_Cmnd_Stack_Strg.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    11.06.2011   @I  Eckard Klotz
 @I refactoring of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  Cmnd_Stack_Strg(void);











/*!
 destruktor
 <br><br>
 @htmlinclude "Cmnd_Stack_Strg__Cmnd_Stack_Strg.html"
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    11.05.2011   @I  Eckard Klotz
 @I refactoring of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  ~Cmnd_Stack_Strg(void);


/*!
 write a value into a stack

 @param [in] name  identifier of the stack to write in
 @param [in] value value to push on the stack


 <br><br>
 @htmlinclude Cmnd_Stack_Strg_addStackValue.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    28.08.2010   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
    21.12.2011   @I  Eckard Klotz
 @I refactoring elimination of include-circle problems
 @I copy function from class Generator_Nsd
                     to class SnippetExecution
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  void addStackValue(String_imp name,
                     String_imp value);




/*!
 push the content of a ready evaluated Snipet on a stack stored
 under a key-name in a map-container


 @param [in]  source         xml-tree of the source to analyse
 @param [in]  startTag       name of the searched sub-tree
 @param [in]  replacement    contains replacement-information to tailore
                             tags, attributes, texts and so on
 @param [in]  keyName        name to save the Snipet-content under
 @param [in]  owner          snipet that has called this function


 <br><br>
 @htmlinclude Cmnd_Stack_Strg_stackPush.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    30.06.2010   @I  Eckard Klotz
 @I refactoring of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void stackPush(XML_Node                     source,
                String_imp                   startTag,
                map<String_imp, String_imp>* replacement,
                String_imp                   keyName,
                SnippetExecution*            owner);




/*!
 saves the size of a stack as string on a destination-stack

 @param [in]   source      name the stack to measure
 @param [in]   destination name the stack to save the result

 <br><br>
 @htmlinclude Cmnd_Stack_Strg_stackPushSize.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    14.08.2010   @I  Eckard Klotz
 @I refactoring of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void stackPushSize(String_imp  destination,
                    String_imp  source);







/*!
 saves a diagram stored in the stack stored in a file with a name
 stored in the stack also


 @param [in]  keyDiagram  name the Snippet-content used as file-content
 @param [in]  keyFile     name the Snippet-content used as file-name
 @param [in]  replacement contains replacement-information to tailor
                          tags, attributes, texts and so on
 @param [in]  diagram     directory to save the file in
 @param [in]  owner       snippet that has called this function if user-message
                          should be displayed in shell-window if an error was found
              <br>        or NULL if no message should be displayed

 <br><br>
 @htmlinclude Cmnd_Stack_Strg_stackSave.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    11.07.2010   @I  Eckard Klotz
 @I re-factoring of base-design
 @I first implementation
 @I_______________________________________________________
    15.08.2012   @I  Eckard Klotz
 @I re-factoring of design
 @I error-messages will only generated if the givven owner is not NULL
 @I_______________________________________________________
    25.12.2014   @I  Eckard Klotz
 @I re-factoring of design for better maintenance
 @I moved reverse save actions for the whole stack to an own method
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void stackSave(String_imp                   keyDiagram,
                String_imp                   keyFile,
                map<String_imp, String_imp>* replacement,
                list<String_imp>*            diagram,
                SnippetExecution*            owner);



/*!
 saves the whole stack content beginning with the last element


 @param [in]  keyDiagram  name the Snippet-content used as file-content
 @param [in]  keyFile     name the Snippet-content used as file-name
 @param [in]  replacement contains replacement-information to tailor
                          tags, attributes, texts and so on
 @param [in]  diagram     directory to save the file in
 @param [in]  owner       snippet that has called this function if user-message
                          should be displayed in shell-window if an error was found
              <br>        or NULL if no message should be displayed

 <br><br>
 @htmlinclude Cmnd_Stack_Strg_stackSave.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    25.12.2014   @I  Eckard Klotz
 @I re-factoring of design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void stackSaveAllReverse(String_imp                   keyDiagram,
                          String_imp                   keyFile,
                          map<String_imp, String_imp>* replacement,
                          list<String_imp>*            diagram,
                          SnippetExecution*            owner);




/*!
 delete the Snippet-stack with the given key-name.


 @param [in]  keyName    name the Snippet-content was saved under


 <br><br>
 @htmlinclude Cmnd_Stack_Strg_stackClear.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    30.06.2010   @I  Eckard Klotz
 @I refactoring of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void stackClear(String_imp keyName);






/*!
 compare if content of the current stack-element is equal to a ref-content

 @param [in]   stcName  name the stack to compare in
 @param [in]   refValue value to compare with
 @param [out]  result   will be set to false if compare-result is unequal

 <br><br>
 @htmlinclude Cmnd_Stack_Strg_ifStackEqual.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    14.08.2010   @I  Eckard Klotz
 @I refactoring of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void ifStackEqual(String_imp  stcName,
                   String_imp  refValue,
                   bool*       result);



/*!
 compare if content of the current stack-element is unequal to a ref-content

 @param [in]   stcName  name the stack to compare in
 @param [in]   refValue value to compare with
 @param [out]  result   will be set to false if compare-result is unequal

 <br><br>
 @htmlinclude Cmnd_Stack_Strg_ifStackUnequal.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    14.08.2010   @I  Eckard Klotz
 @I re factoring of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void ifStackUnequal(String_imp  stcName,
                     String_imp  refValue,
                     bool*       result);


/*!
 exchnage the given stack-name with its top-value or return itself

 @param [in]  stackName   possible stack-name
 @param [in]  replacement contains replacement-information to tailor
                          tags, attributes, texts and so on

 @return      the top-value of the stack if it exists or
              the given stack-name if it does not exist
 <br><br>
 @htmlinclude Cmnd_Stack_Strg_exchange.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    21.08.2012   @I  Eckard Klotz
 @I expanding of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
String_imp exchange(const String_imp&            stackName,
                    map<String_imp, String_imp>* replacement = nullptr);


 private:



/*!
 @brief common object-attributes


 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    06.12.2009   @I  Eckard Klotz
 @I re-factoring of base-design <br>
 to put the attributes into a structure makes it possible to
 set them apart from local variables and parameters of a method
 in the source-code by using the struct-name as prefix.
 @I first implementation
 @I_______________________________________________________
 @I re-factoring elimination of include-circle problems
 @I erasing knowledge to owners (attribute-struct)
    and implementation of a stack as class attribute
    not as object-example attribute
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
static map<String_imp, list<String_imp>* >Att_Stack;

};


#ifndef DOXYGEN
#define USING_NAMESPACE  using namespace
//}; USING_NAMESPACE CL_CMND_STACK_STRG;
//}; USING_NAMESPACE CL_COMMAND;
#undef  USING_NAMESPACE
#endif //DOXYGEN



#endif //CMND_STACK_STRG_H
