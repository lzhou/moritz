/*!

 @file
 @brief definitions of very simple parser-functions just to create an
 parser-tree

 Copyright (C) 2014-2018 by Eckard Klotz.

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
    27.07.2014     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    27.07.2014...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/
#ifndef TXTDIASM_H
 #define TXTDIASM_H


#include <stdio.h>
#include <list>

using namespace std;




#ifndef DOXYGEN
//namespace TXTDIASM{
#endif //DOXYGEN




typedef struct ParserNode_TP
{
 const char*          Identifier;
 const char*          Begin;
 const char*          End;
 unsigned int         Length;
 list<ParserNode_TP*> SubContent;

}ParserNode_TP;






typedef struct TerminatedResult_TP
{
 const char*                Identifier;
 const char*                StartToken;
 const char*                EndToken;
 const char*                ContentBegin;
 const char*                ContentEnd;
 unsigned int               ContentLength;
 list<TerminatedResult_TP*> SubContent;
}TerminatedResult_TP;







list<TerminatedResult_TP*> TerminatedRule_parse(const char* textBegin,
                                                const char* textEnd,
                                                const char* identifier,
                                                const char* startToken,
                                                const char* endToken);





list<TerminatedResult_TP*> SpliterRule_parse(const char* textBegin,
                                             const char* textEnd,
                                             const char* splitToken);






bool ParserNode_getText(char** text, ParserNode_TP* parsernode);














#ifndef DOXYGEN
#define USING_NAMESPACE using namespace
//}; USING_NAMESPACE TXTDIASM;
#undef  USING_NAMESPACE
#endif //DOXYGEN

#endif // TXTDIASM_H
