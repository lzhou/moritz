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


//#define DEBUG_OUTPUT_LOG  /*for test-purpose only*/


 #ifdef LOG_OUTPUT    //predefined in an included file before
  #undef LOG_OUTPUT
 #endif // LOG_OUTPUT

 #ifdef LOG_PRINTF    //predefined in an included file before
  #undef LOG_PRINTF
 #endif // LOG_PRINTF

 #ifdef LOG_ON        //predefined in an included file before
  #undef LOG_ON
 #endif // LOG_ON
 #ifdef LOG_OFF       //predefined in an included file before
  #undef LOG_OFF
 #endif // LOG_OFF

 #ifdef LOG_ACTIVE        //predefined in an included file before
  #undef LOG_ACTIVE
 #endif // LOG_ACTIVE

 #ifdef LOG_PASSIVE        //predefined in an included file before
  #undef LOG_PASSIVE
 #endif // LOG_PASSIVE

/*!
 @brief activate the log output locally

 parameter content for @ref LOG_OUTPUT and @ref LOG_PRINTF
*/
#define LOG_ON  true

/*!
 @brief deactivate the log output

 parameter content for @ref LOG_OUTPUT and @ref LOG_PRINTF
*/
#define LOG_OFF false

/*!
 @def DEBUG_OUTPUT_LOG
 @brief  activate the log output globally

 control of the compiler-switch that's defines  @ref  and @ref LOG_PRINTF
 with or without content
*/


/*!
 @def LOG_OUTPUT(onOff, comment)
 @brief cout based log-message that contains information about the source-location also

 Depending on the active definition of @ref DEBUG_OUTPUT_LOG  and the given parameter
 onOff this macro streams out a log-message defined in the source-code. The output-format
 depends  on the used build-environment to enable an analysis by the IDE. Since the macro
 is using the predefined constants __FILE__ and __LINE__ there is a chance that the IDE
 creates a linked build-message that can be clicked by the user to reach very easily the
 location of the log-command.

 @param onOff   locally activation or deactivation of the log-output
 @param comment log-output defined like a stream

*/


/*!
 @def LOG_PRINTF(onOff, comment)
 @brief printf based log-message that contains information about the source-location also
 Depending on the active definition of @ref DEBUG_OUTPUT_LOG  and the given parameter
 onOff this macro streams out a log-message defined in the source-code. The output-format
 depends  on the used build-environment to enable an analysis by the IDE. Since the macro
 is using the predefined constants __FILE__ and __LINE__ there is a chance that the IDE
 creates a linked build-message that can be clicked by the user to reach very easily the
 location of the log-command.

 @param onOff   locally activation or deactivation of the log-output
 @param comment log-output defined as printf content

*/


#if defined(DEBUG_OUTPUT_LOG)
              // global activation for the source-file that contains the log-commends
 #include <iostream>
 #include <string>
 #include <stdio.h>


 extern  bool LogOutput_Active;


 #define LOG_ACTIVE() LogOutput_Active = true

 #define LOG_PASSIVE() LogOutput_Active = false


 #if defined(__APPLE__) || defined(__GNUG__)

  #define LOG_OUTPUT(onOff, comment) if((onOff == true)&&(LogOutput_Active==true))\
                              {\
                               cout << __FILE__ << ":"<< __LINE__  <<  ": warning: user-note" <<  endl;\
                               cout << "note: " << comment << endl;\
                              }
  #define LOG_PRINTF(onOff, comment) if((onOff == true)&&(LogOutput::Active==true))\
                              {\
                               printf("%s:%d: warning: user-note\n", __FILE__ , __LINE__); \
                               printf("note: %s\n",(comment));\
                              }
 #else //defined(GNUG)
  #define LOG_OUTPUT(onOff, comment) if((onOff == true)&&(LogOutput_Active==true))\
                              {\
                               cout << __FILE__ << "("<< __LINE__  << "): warning: user-note" <<  endl;\
                               cout << "note: " << comment << endl;\
                              }
  #define LOG_PRINTF(onOff, comment) if((onOff == true)&&(LogOutput::Active==true))\
                              {\
                               printf("%s(%d): warning: user-note\n", __FILE__ , __LINE__); \
                               printf("note: %s\n",(comment));\
                              }
 #endif // defined(GNUG)

#else     // DEBUG_OUTPUT_LOG
          // global deactivation for the source-file that contains the log-commends

 #define LOG_ACTIVE()
 #define LOG_PASSIVE()
 #define LOG_OUTPUT(onOff, comment)
 #define LOG_PRINTF(onOff, comment)

#endif    //DEBUG_OUTPUT_LOG





//#endif // LOGOUTPUT_H

