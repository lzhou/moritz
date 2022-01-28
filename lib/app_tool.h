/*!

 @file
 @brief    diverse tool-functions for a main-application

 This file contains the declaration of common functions used in main-applications

 Copyright (C) 2012-2020 by Eckard Klotz.

 Permission to use, copy, modify, and distribute this software and its
 documentation under the terms of the GNU General Public License is hereby
 granted. No representations are made about the suitability of this software
 for any purpose. It is provided "as is" without express or implied warranty.
 See the GNU General Public License for more details.

 Documents produced by the binary of this source are derivative works derived from the
 input used in their production; they are not affected by this license.

 <b> History </b>

 @TabBegin
    date           @I author          @I implementation/change
 @I____________________________________________________________
    12.02.2012     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    12.02.2012...  @I Eckard Klotz
 @I Changes are documented in the comment of the changed element
 @TabEnd

*/
#ifndef APP_TOOL_H
#define APP_TOOL_H



#include "xml_DataModel.h"



#include "String_imp.h"


#include<map>



#ifndef DOXYGEN
 //namespace F_APP_TOOL{
#endif //DOXYGEN




typedef struct App_Info_TP
{
 String_imp Name;
 String_imp Content;
} App_Info_TP;


/*
#if defined(WINDOWS)
 const String_imp EndOfLine = "\x0D\x0A";
#elif defined(LINUX)
 const String_imp EndOfLine = "\x0A";
#else // no WINDOWS or LINUX
 const String_imp EndOfLine = "\x0D";
#endif // WINDOWS LINUX or ???
*/






/*!
 output of help-text off application due to the argumnts
 given to the application by the operation-system

 @param [in] argc             number of arguments given to the application
 @param [in] argv             array of arguments given to the application
 @param [in] kind             name argument that schould be returnd
 @param [in] application_Info container of help-output

 @htmlinclude ./des/app_tool_cpp_F_info.html

 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    31.12.2006      @I  Eckard Klotz
 @I give more helpoutput
 @I first implementation
 @I_______________________________________________________
    12.08.2007      @I  Eckard Klotz
 @I warning-message of the compiler because Info was a global
    variable
 @I Info is now a local variable of this function now
 @I_______________________________________________________
    15.12.2007      @I  Eckard Klotz
 @I implement an additional configuration path
 @I help-output about the additional configuration-path added
 @I_______________________________________________________
    24.12.2007      @I  Eckard Klotz
 @I re-factoring
 @I using of string-makros for argument-identifiers
 @I_______________________________________________________
    11.10.2009      @I  Eckard Klotz
 @I re-factoring
 @I Info renamed in Application-Info and replaced into
    an own header-file
 @I_______________________________________________________
    12.02.2012      @I  Eckard Klotz
 @I re-factoring
 @I moved function from main-files into a library-file that
    contains common application-tools
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
void info(int   argc, char* argv[],
          const String_imp& kind,
          App_Info_TP       application_Info[]);




/*!
  @brief test if the application is a 64 application

  @return true  if the application is built as a 64 application or more
  @return false if the application is built as an application smaller as 64 bit
*/
bool this_is_at_least_a_64_bit_application(void);





/*!
 searches an argument given by the operation-system to the
 application that starts with the given string \"kind\"

 @param [in] argc number of arguments given to the application
 @param [in] argv array of arguments given to the application
 @param [in] kind name argument that should be returned

 @return content of argument


 <br><br>
 @htmlinclude ./des/app_tool_cpp_F_getAgument.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    ... 09.2009   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
    12.02.2012      @I  Eckard Klotz
 @I re-factoring
 @I moved function from main-files into a library-file that
    contains common application-tools
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
String_imp getAgument(int argc, char* argv[], const String_imp& kind);



/*!
 Reads a configuration-value out of the arg-array of the application
 or if not given out of the configuration file. If the value is not found
 the given default-value will be returned

 @param[in] configuration root block of the xml-configuration
 @param[in] xmlName       name of the searched configuration value
 @param[in] argc          number of values in the arg-array of the
                          application
 @param[in] argv          arg-array of the application
 @param[in] argName       Begin of the searched configuration value in the
                          arg-array of the application
 @param[in] defaultValue  default-value of the configuration-value

 @return configuration-value

 @htmlinclude ./des/app_tool_cpp_F_getConfigValue.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    ... 02.2012   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
    12.02.2012      @I  Eckard Klotz
 @I re-factoring
 @I moved function from main-files into a library-file that
    contains common application-tools
 @I_______________________________________________________
    12.02.2012      @I  Eckard Klotz
 @I use of replacement-mechanism for separators in path-strings
 @I don't use configuration if equal to NULL
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
String_imp getConfigValue(XML_Node          configuration,
                          const String_imp& xmlName,
                          int argc,   char* argv[],
                          const String_imp& argName,
                          const String_imp& defaultValue);



/// header of application-arguments used to define special user-definitions
#define ARG_UA "UA:"

// @param[in] charStart     starts the numerical definition of a character example [32] as space or [61] as =
// @param[in] charEnd       ends   the numerical definition of a character example [60] as < or [62] as >

/*!
 evaluate the arg-array of the application to create a dictionary
 of user-definitions

 @param[in] root          root node of xml-configuration (will be extended by the user-definitions as well)
 @param[in] argc          number of values in the arg-array of the
                          application
 @param[in] argv          arg-array of the application

 @param[in] frame         character used to mark an argument that contains
                          a white-space character to provide a split into separated
                          arguments
 @param[in] splitter      character used to split identifier of user-argument and
                          its value
 @param[in] argName       Begin of the searched configuration value in the
                          arg-array of the application


 @return dictionary of user definitions

 @htmlinclude ./des/app_tool_cpp_F_getUserDefinitions.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    20.12.2014   @I  Eckard Klotz
 @I re-factoring application arguments
 @I first implementation
  @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
XML_Node getUserDefinitions(XML_Node    root,
                            int         argc,
                            char*       argv[],
                            char        frame     = '\"',
                            char        splitter  = '=',
//                            char        charStart = '[',
//                            char        charEnd   = ']',
                            const char* argName   = ARG_UA);












/*!
 evaluate the arg-array of the application to create a dictionary
 of user-definitions

 @param[out] newStr        new string with place-holders replaced by characters.
             @note if this pointer points to NULL a new character-array will be created
             @note if this pointer points not to NULL it will be expected that the user provides a buffer big enough to contain the result

 @param[in]  oldStr        original string with place-holders for special characters

 @param[in]  charStart     starts the numerical definition of a character example [32] as space or [61] as =
 @param[in]  charEnd       ends   the numerical definition of a character example [91] as [ or [93] as ]



 @htmlinclude ./des/app_tool_cpp_F_strRestoreCharacters.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    20.12.2014   @I  Eckard Klotz
 @I re-factoring application arguments
 @I first implementation
  @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
void strRestoreCharacters(char**      newStr,
                          const char* oldStr,
                          char        charStart = '[',
                          char        charEnd   = ']');





/*!
 tries to open the file with the given name

 @param [in] fileName path and name of the text-file to read
 @param [in] usedPathSeparator character or character-sequence used as
                               separator of folder-path definitions in
                               user-configuration
 @param [in] osPathSeparator   character or character-sequence to be used
                               as separator of folder-path definitions in
                               current operation system of the computer

 @return content of file or empty string


 <br><br>
 @htmlinclude ./des/app_tool_cpp_F_readTextFile.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    ... 09.2009   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
     23.10.2011   @I  Eckard Klotz
 @I wrong display of line-changes by adding an additional carrage-return
 @I using ifstream now and ist getline-method to read line by line,
    line-change will be added while createing return-value
 @I_______________________________________________________
    12.02.2012      @I  Eckard Klotz
 @I re-factoring
 @I moved function from main-files into a library-file that
    contains common application-tools
 @I_______________________________________________________
    02.06.2013      @I  Eckard Klotz
 @I re-factoring
 @I use of replacement-mechanism for separators in path-strings
 @I_______________________________________________________
    12.10.2013      @I  Eckard Klotz
 @I bug: if a file contains only one line with out a line-brake
         at the end the read-loop is endless since end-of-file
         will not be detected.
 @I the loop reads now the file character for character and
    counts the readed characters. The loop ends if the number
    reaches the file-size or end-of-file will be detected.
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
String_imp readTextFile(const String_imp& fileName,
                        const String_imp& usedPathSeparator,
                        const String_imp& osPathSeparator);






/*!
 scans the given folder for additional source-files, sub-folder will
 be scanned also if defined by user.

 @param [out] sourceContainer  xml-node that holds all files to analyse
 @param [in]  addBehind        xml-node to insert behind
 @param [in]  folderName       sub-folder to search in
 @param [in]  sourcePath       local path of the sources
 @param [in]  rootPath         machine-depended path used as root of sourcePath
 @param [in]  osPathSeparator  character or character-sequence to be used
                               as separator of folder-path definitions in
                               current operation system of the computer
 @param [in]  fileAttachment   attachment of the files to search for
 @param [in]  recursive        control of recursive search in sub-folders
 <br>                          true  ==> scan all sub-folders also
 <br>                          false ==> scan no sub-folders
 @param [in] doNotSkip         decision of user if unchanged files should be analysed or not
 @param [in] variantContainer  user-configuration to manage variants of directive-switches

 @return content of file or empty string


 <br><br>
 @htmlinclude ./des/app_tool_cpp_F_collectFiles.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    14.02.2010   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
    09.04.2010   @I  Eckard Klotz
 @I bug: under linux pseudo-pathes <b>.</b> and  <b>..</b>
         produces pseudo-output by using tag  <b>FolderName</b>
 @I check of file-attactment changed
 @I_______________________________________________________
    02.06.2011   @I  Eckard Klotz
 @I re-factoring: split xml-configuration into language dependend and user-dependent parts
 @I added copc of doNotSkip-attribute in folder-configuration to the new file-tags
 @I_______________________________________________________
    12.02.2012      @I  Eckard Klotz
 @I re-factoring
 @I moved function from main-files into a library-file that
    contains common application-tools
 @I_______________________________________________________
    20.08.2012      @I  Eckard Klotz
 @I enable for the user to control the order of processing
 @I new files will be added directly after the folder and
    not at the end of the list any-more
 @I_______________________________________________________
    20.01.2013      @I  Eckard Klotz
 @I re-factoring
 @I use of a machine-depending root-path
 @I_______________________________________________________
    12.10.2013      @I  Eckard Klotz
 @I bug: xml-comments lead to crash
 @I no use of method ToElement for LinkEndChild
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
void collectFiles(XML_Node          sourceContainer,
                  XML_Node          addBehind,
                  const String_imp& folderName,
                  const String_imp& sourcePath,
                  const String_imp& rootPath,
                  const String_imp& osPathSeparator,
                  const String_imp& fileAttachment,
                  bool              recursive,
                  const String_imp& doNotSkip,
                  XML_Node          variantContainer);


/*!
 scans the folder-description in the given configuration for
 additional source-files and starts a search-process in this
 directory

 @param [in] configuration     xml-element that describes the
                               searched content
 @param [in] commonAttachment  default attachment of the file-name
 @param [in] usedPathSeparator character or character-sequence used as
                               separator of folder-path definitions in
                               user-configuration
 @param [in] osPathSeparator   character or character-sequence to be used
                               as separator of folder-path definitions in
                               current operation system of the computer

 @return content of file or empty string

 <br><br>
 @htmlinclude ./des/app_tool_cpp_F_searchFiles.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    14.02.2010   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
    02.06.2011   @I  Eckard Klotz
 @I re-factoring: split xml-configuration into language dependend and user-dependent parts
 @I added evaluation of doNotSkip-attribute in user-configuration
 @I_______________________________________________________
    12.02.2012      @I  Eckard Klotz
 @I re-factoring
 @I moved function from main-files into a library-file that
    contains common application-tools
 @I_______________________________________________________
    20.01.2013      @I  Eckard Klotz
 @I re-factoring
 @I use of a mashine-depending root-path container
 @I_______________________________________________________
    02.06.2013      @I  Eckard Klotz
 @I re-factoring
 @I use of replacement-mechanism for separators in path-strings
 @I_______________________________________________________
    18.08.2013      @I  Eckard Klotz
 @I bug: filles will be treated as folder if folder-string
         contains no separator at the end
 @I test if folder contains a separator at the end and
    add one if not
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
void searchFiles(XML_Node                   configuration,
                 const String_imp&          commonAttachment,
                 const String_imp&          usedPathSeparator,
                 const String_imp&          osPathSeparator);


/*!
 check if the xml-tree has to be completed by loading additional xml-files,
 load this additional file and do the competetion.

 @param [in] root              holds the xml-tree to check and complete
 @param [in] usedPathSeparator character or character-sequence used as
                               separator of folder-path definitions in
                               user-configuration
 @param [in] osPathSeparator   character or character-sequence to be used
                               as separator of folder-path definitions in
                               current operation system of the computer
 @param [in] rootStrings       container of root strings to be used for
                               file-paths if defined by user
 @param [in] subFileAttribute  defines the attribute that holds the information about the file to load

 @return content of file or empty string


 <br><br>
 @htmlinclude ./des/app_tool_cpp_F_completeXML.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    30.05.2011   @I  Eckard Klotz
 @I re-factoring: split xml-configuration into language dependend and user-dependent parts
 @I first implementation
 @I_______________________________________________________
    12.02.2012      @I  Eckard Klotz
 @I re-factoring
 @I moved function from main-files into a library-file that
    contains common application-tools
 @I_______________________________________________________
    02.06.2013      @I  Eckard Klotz
 @I re-factoring
 @I use of replacement-mechanism for separators in path-strings
 @I_______________________________________________________
    09.06.2013      @I  Eckard Klotz
 @I re-factoring
 @I use of root-definition for relative path-strings
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
void completeXML(XML_Node          root,
                 const String_imp& usedPathSeparator,
                 const String_imp& osPathSeparator,
    map<String_imp,String_imp>     rootStrings,
                 const String_imp& subFileAttribute = "includeFile");





/*!
 check if the xml-tree has to be completed by loading additional xml-files,
 load this additional file and do the completion.

 @param [in] source            path and file-name of source to analyse
 @param [in] destination       paths and file name of files to generate
 @param [in] usedPathSeparator character or character-sequence used as
                               separator of folder-path definitions in
                               user-configuration
 @param [in] osPathSeparator   character or character-sequence to be used
                               as separator of folder-path definitions in
                               current operation system of the computer

 @return content of file or empty string


 <br><br>
 @htmlinclude ./des/app_tool_cpp_F_checkNewSource.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    02.06.2011   @I  Eckard Klotz
 @I re-factoring: split xml-configuration into language depended and user-dependent parts
 @I first implementation
 @I_______________________________________________________
    26.06.2013   @I  Eckard Klotz
 @I re-factoring of source-structure
 @I moving of function from project main-file to global app-tools
    since it will be used in different projects
 @I_______________________________________________________
    26.06.2013   @I  Eckard Klotz
 @I re-factoring
 @I use of replacement-mechanism for separators in path-strings
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
bool checkNewSource(const String_imp& source,
                    list<String_imp>  destination,
                    const String_imp& usedPathSeparator,
                    const String_imp& osPathSeparator);






/*!
 return the absolute folder path including the file name as well as its attachment
 of the given file
 @param [in] file              path and name of file to analyse
 @param [in] osPathSeparator   character or character-sequence to be used
                               as separator of folder-path definitions in
                               current operation system of the computer

 @return absolute file-path


 <br><br>
 @htmlinclude ./des/app_tool_cpp_F_getAbsolutePath.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    12.10.2014   @I  Eckard Klotz
 @I new service function
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
String_imp getAbsolutePath(const String_imp& file,
                           const String_imp& osPathSeparator);


/*!
 create the given folder-path or not existing sub-folders
 @param [in] path              path and name of file to analyse
 @param [in] separator         character used to separate folder-names in the path

 @return 0 on windows or system-return-value on linux

 <br><br>
 @htmlinclude ./des/app_tool_cpp_F_createFolder.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    22.12.2014   @I  Eckard Klotz
 @I new service function
 @I first implementation
 @I_______________________________________________________
    24.07.2016   @I  Eckard Klotz
 @I avoid compiler-warnings
 @I define return-value to catch system-return on linux
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
int createFolder(const String_imp& path, char separator='/');



#ifndef DOXYGEN
//};
#endif //DOXYGEN


#endif//APP_TOOL_H
