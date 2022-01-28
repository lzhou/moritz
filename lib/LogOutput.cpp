/*!

 @file
 @brief provides preprocessor-macros and data to create log-outputs

 This log-outputs contain information about the source-file and the
 location of the log-command inside the source in a formatted stile.
 Thus they are treated from an integrated development environment
 like compiler-outputs and may be transferred into linked build-messages

 @note This header file contains no main compiler-switch since it may be included
       in template header-files also as well as in c/cpp files which include this
       template headers. As long this log-header must not include project-headers
       this will not result in preprocessor problems like endless include loops.

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
    06.10.2015     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    06.10.2015...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/

#include "LogOutput.h"

////namespace LogOutput
//{
// bool Active = false;
//}

 bool LogOutput_Active = false;

