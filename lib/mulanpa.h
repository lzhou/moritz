/*!

 @file
 @brief definitions for the abc2xml-application a bnf-based parser-tool

 This file contains several definitions for the abc2xml main-source.

 Copyright (C) 2008-2020 by Eckard Klotz.

 Permission to use, copy, modify, and distribute this software and its
 documentation under the terms of the GNU General Public License is hereby
 granted. No representations are made about the suitability of this software
 for any purpose. It is provided "as is" without express or implied warranty.
 See the GNU General Public License for more details.

 Documents produced by abc2xml are derivative works derived from the
 input used in their production; they are not affected by this license.

 <b> History </b>

 @TabBegin
    date           @I author          @I implementation/change
 @I____________________________________________________________
    31.08.2009     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    31.08.2009...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/
#ifndef MULANPA_H
#define MULANPA_H

#include "app_tool.h"
#include "trn_directive.h"



/*!
 @defgroup ABC2XML_SOURCE Diverse Source-elements
 brief Collection of non class-assosiatet elements inside the
 source-code of Moritz

*/



/*!
 @brief creating and configuration of an directive-process object

 @ingroup ABC2XML_SOURCE

 @param [in] configuration     xml-part that contains the
                               user-defined configuration
 @param [in] process           name of the root-tag to use
 @param [out] savePartResult   user-configuration to save part-result
 <br>                          true ==> part-result should be saved as file
 <br>                          false==> part-result should not be saved
 @param [out] attachment       file attachment for the file to save the
                               part-result in
 @param [in] usedPathSeparator character or character-sequence used as
                               separator of folder-path definitions in
                               user-configuration
 @param [in] osPathSeparator   character or character-sequence to be used
                               as separator of folder-path definitions in
                               current operation system of the computer
 @param [in] rootStrings       container of root-strings to be used for
                               file-paths if defined by user

 @return configured object ready to use


 <br><br>
 @htmlinclude ./des/MuLanPa_TiPa/main_cpp_F_createDirectiveProcess.html

 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    25.09.2011   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
Prcs_Trn_Directive* createDirectiveProcess(      XML_Node       configuration,
                                           const String_imp&    process,
                                                 bool*          savePartResult,
                                                 String_imp*    attachment,
                                           const String_imp&    usedPathSeparator,
                                           const String_imp&    osPathSeparator,
                                     map<String_imp,String_imp> rootStrings);




/*!
 @brief get user defined set of pre-processor constants

 @ingroup ABC2XML_SOURCE

 search for a special variant of constant-definitions to initialize
 the evaluation switches-directives due to the user-configuration

 @param [in] directiveDefinition xml-node that hods the all variants
                                 of constant-definition sets
 @param [in] variant             name of the variant to use

 @return xml-node that holds the defined constant-values to use
         with the given variant-name

 @htmlinclude ./des/MuLanPa_TiPa/main_cpp_F_getUserVariant.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    02.11.2011   @I  Eckard Klotz
 @I part of base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
XML_Node  getUserVariant(XML_Node    directiveDefinition,
                         const char* variant);

















/// @defgroup ARGUMENTXML xml-names of arguments
/// @ingroup ABC2XML_SOURCE
/// @{
const String_imp XML_PATH              = "Path";
const String_imp XML_USERPATH          = "User";
//const String_imp XML_RESOURCEPATH      = "ResourcePath";
//const String_imp XML_SOURCEPATH        = "SourcePath";
//const String_imp XML_SOURCEFILE        = "SourceFile";
const String_imp XML_DESTINATIONPATH   = "DestinationPath";
//const String_imp XML_DESCRIPTIONPATH   = "DescriptionPath";
const String_imp XML_CONFIGURATIONPATH = "ConfigurationPath";
/// @}

/// @defgroup ARGUMENTPREFIX Argument-Prefix
/// @ingroup ABC2XML_SOURCE
/// @{
const String_imp ARG_CONFIGURATIONFILE = "CF";
//const String_imp ARG_CONFIGURATIONPATH = "CP";
//const String_imp ARG_RESOURCEPATH      = "RP";
//const String_imp ARG_SOURCEPATH        = "SP";
//const String_imp ARG_SOURCEFILE        = "SF";
const String_imp ARG_DESTINATIONPATH   = "DP";


const String_imp ARG_UsedPathSeparator = "UPS";
const String_imp ARG_OsPathSeparator   = "OPS";
//const char*      ARG_RootPath          = "RootPath";
//const String_imp ARG_DESCRIPTIONPATH   = "DscP";
/// @}



/// @defgroup ARGUMENTDEFAULT argument-defaults
/// @ingroup ABC2XML_SOURCE
/// @{
//const String_imp SOURCEFILE_DF = "index.xml";
//#define CONFIGURATIONFILE_DF "abc2xml_cfg.xml"
const String_imp CONFIGURATIONFILE_DF = "abc2xml_cfg.xml";

//#define SOURCEPATH_DF        "C:\\abc2xml\\src\\"
//const String_imp SOURCEPATH_DF       = "";
//const String_imp RESOURCEPATH_DF     = "C:\\abc2xml\\res\\";
const String_imp DESTINATIONPATH_DF  = "C:\\abc2xml\\xml\\";
//const String_imp DESCRIPTIONPATH_DF  = "C:\\abc2xml\\des\\";



#if defined(WINDOWS)
 const String_imp UsedPathSeparator_DF = "/";
 const String_imp OsPathSeparator_DF   =  "\\";
#elif defined(LINUX)
 const String_imp UsedPathSeparator_DF = "\\";
 const String_imp OsPathSeparator_DF   =  "/";
#else // no WINDOWS or LINUX
 const String_imp UsedPathSeparator_DF = "\\";
 const String_imp OsPathSeparator_DF   =  "/";
#endif // WINDOWS LINUX or ???


/// @}


App_Info_TP Application_Info[] = {
{ "StartOutput" , "\
                        abc2xml Version 2.0.0  \n \
      multi-language-parser to translate sourc-codes into xml-structures \n \
               Copyright (C) 2008-"+String_imp(__DATE__).substr(String_imp(__DATE__).size()-4,4)+" by Eckard Klotz \n \
              Build date: "+String_imp(__DATE__)+" , time: "+String_imp(__TIME__)+" \n \
              Build as : _TARGET_POINTER_SIZE_ application  \n \
\n \
Permission to use, copy, modify, and distribute this software and its \n \
documentation under the terms of the GNU General Public License is hereby \n \
granted. No representations are made about the suitability of this software \n \
for any purpose. It is provided \"as is\" without express or implied warranty. \n \
See the GNU General Public License for more details. \n \
\n \
Documents produced by abc2xml are derivative works derived from the \n \
input used in their production; they are not affected by this license. \n \
\n \
To get first help use the command \" abc2xml help\" \n \
You can find more information under www.mulanpa.sourceforge.net or \n \
www.sourceforge.net/projects/mulanpa/ .\n \
Here you may download the manual or use the forum.\
\n"
},
{ "Help" , "\n \
                        Using the help Argument of abc2xml \n \
\n \
abc2xml                 -> general program-information \n \
abc2xml help            -> shows this text \n \
abc2xml help All        -> shows all help-information (reroute it into a file!) \n \
abc2xml help Resources  -> general overview about the needed resource-files \n \
abc2xml help Arguments  -> general overview about the command-line arguments \n \
abc2xml help "+String_imp(ARG_DESTINATIONPATH)+"         -> describes the destination-path argument \n \
abc2xml help "+String_imp(ARG_CONFIGURATIONFILE)+"         -> describes the configuration-file argument \n \
\n"
},
/*
abc2xml help "+String_imp(ARG_RESOURCEPATH)+"         -> describes the resource-path argument \n \
abc2xml help "+String_imp(ARG_SOURCEPATH)+"         -> describes the source-path argument \n \
abc2xml help "+String_imp(ARG_DESCRIPTIONPATH)+"       -> describes the description-path argument \n \

abc2xml help "+String_imp(ARG_SOURCEFILE)+"         -> describes the source-file argument \n \
abc2xml help "+String_imp(ARG_CONFIGURATIONPATH)+"         -> describes the additional configuration-path argument \n \
*/

{ "Resources" , "\n \
                        Additional Resources\n \
\n \
If no user-configuration is defined abc2xml tries to load this out of his home\n \
directory : \n \
    abc2xml_cfg.xml     -> prototype for the abc2xml main-configuration\n\
\n \
inside of newer configuration-files lines like the following may be placed: \n \
    <[TAGNAME] includeFile=\"[FOLDER_PATH][SUB_CONFIG_FILE].xml\"/> \n \
This is a reference to the excluded configuration for TAGNAME that has to be\n \
provided in the folder FOLDER_PATH under the name SUB_CONFIG_FILE.xml\n\
\n \
Some lines in the configuration have the following formate:\n \
    <File value=\"[FOLDER_PATH][GRAMMAR_FILE].a2x\"/> \n \
This is a reference to the excluded grammar-description that has to be\n \
provided in the folder FOLDER_PATH under the name GRAMMAR_FILE.xml\n\n \
\n \
\n"
},
{ "Arguments" , "\n \
                        abc2xml Command-Line Arguments \n \
\n \
Command-Line arguments are used to give abc2xml some base-informations about \n \
the directories and file which should be used. \n \
 \n \
The following argument has to be used to locate the outputs: \n \
 "+String_imp(ARG_DESTINATIONPATH)+"[destination-path]  destination-path of the created xml-files \n \
\n \
The following argument tells abc2xml to use another configuration-file: \n \
 "+String_imp(ARG_CONFIGURATIONFILE)+"[configuration-file] file with detail-configurations default is abc2xml_cfg \n \
\n \
\n \
Here are some examples: \n \
     win32     abc2xml "+String_imp(ARG_DESTINATIONPATH)+"c:\\project\\xml\\ \n \
     linux     abc2xml "+String_imp(ARG_CONFIGURATIONFILE)+"home:/project/config/abc2xml_cfg.xml \
\n"
},
/*
The following arguments may be used to override the equal information in \n \
the used configuration-file: \n \
 "+String_imp(ARG_RESOURCEPATH)+"[resource-path]	path with additional work-files of Moritz  \n \
                       default-value : home-path of Moritz \n \
 "+String_imp(ARG_SOURCEPATH)+"[source-path] 	path of the sourcee or script \n \
 "+String_imp(ARG_DESCRIPTIONPATH)+"[description-path] 	destination-path of the created description-tables \n \
 "+String_imp(ARG_SOURCEFILE)+"[source-file] 	first xml-file default is index.xml \n \
 "+String_imp(ARG_CONFIGURATIONPATH)+"[configuration-path] alternative path with work-files of Moritz  \n \
                       default-value : \"invalid\" path \n \
*/
/*
{ String_imp(ARG_SOURCEPATH) , "\n \
                        Source-Path Argument \n \
 \n \
This argument specifies the input-folder for abc2xml, that contains the \n \
source-code or scripts to analyse. The format of this string depends on the \n \
operation-system. win32 needs \\ between the folder names linux / \n\n \
like this examples:  SP.abc2xml\\source\\   SP./abc2xml/source/ \n \
 \n \
If this argument is not used its information has to be defined in the \n \
config file which is specified by the argument CF like this example: \n\n \
           <Directories> \n \
            <SourcePath value=\".\\src\\\" /> \n \
           </Directories> \n \
 \n \
If this is also not done abc2xml tries to use this default-folder : \n\n \
          " + String_imp(SOURCEPATH_DF) +
" \n\n \
If all these information are not given or not valid abc2xml terminates. \n \
If more than one of these Information are given the argument has the highest \n \
priority and the default-folder the lowest. \
\n"
},
*/
{ String_imp(ARG_DESTINATIONPATH) , " \n \
                        Destination-Path Argument \n  \
 \n \
This argument specifies the output-folder for abc2xml, that contains the \n \
generated xm-files. The format of this string depends on the \n \
operation-system. win32 needs \\ between the folder names linux / \n \
like this examples:  DP.abc2xml\\destination\\   DP./abc2xml/destination/ \n \
 \n \
If this argument is not used its information has to be defined in the \n \
config file which is specified by the argument CF like this example: \n\n \
           <Directories> \n \
            <DestinationPath value=\".\\xml\\\" /> \n \
           </Directories> \n \
 \n \
If this is also not done abc2xml tries to use this default-folder : \n\n \
          " + String_imp(DESTINATIONPATH_DF) +
" \n\n \
If all these information are not given or not valid abc2xml terminates. \n \
If more than one of these Information are given the argument has the highest \n \
priority and the default-folder the lowest. \
\n"
},
/*
{ String_imp(ARG_DESCRIPTIONPATH) , " \n \
                        Description-Path Argument \n  \
 \n \
This argument specifies the output-folder for abc2xml, that contains the \n \
description tables. The format of this string depends on the \n \
operation-system. win32 needs \\ between the folder names linux / \n \
like this examples:  DscP.abc2xml\\description\\   DscP./abc2xml/description/ \n \
 \n \
If this argument is not used its information has to be defined in the \n \
config file which is specified by the argument CF like this example: \n\n \
           <Directories> \n \
            <<DescriptionPath value=\".\\des\\\" /> \n \
           </Directories> \n \
 \n \
If this is also not done abc2xml tries to use this default-folder : \n\n \
          " + String_imp(DESCRIPTIONPATH_DF) +
" \n\n \
If all these information are not given or not valid abc2xml terminates. \n \
If more than one of these Information are given the argument has the highest \n \
priority and the default-folder the lowest. \
\n "
},
*/
{ String_imp(ARG_CONFIGURATIONFILE) , " \n \
                        Configuration-File Argument \n \
This argument specifies the main configuration files for abc2xml\n \
which allows the user to control the process of xml-file generating. \n \
The format of this string depends on the operation-system. \n \
win32 needs \\ between the folder names linux / like this examples: \n\n \
   CF.abc2xml\\config\\abc2xml.xml   CF./abc2xml/config/abc2xml.xml \n \
 \n \
If this argument is not used its information has to be defined abc2xml tries \n \
to find in its own home directory this default-file : \n\n \
          " + String_imp(CONFIGURATIONFILE_DF) +
" \n\n \
If all these information are not given or not valid abc2xml terminates. \n \
If more than one of these Information are given the argument has the highest \n \
priority and the default-filer the lowest. \
\n "
},
/*
{ String_imp(ARG_SOURCEFILE) , " \n \
                        Source-File Argument \n  \
 \n \
This argument specifies the main input-file for abc2xml, that contains the \n \
first xml-output produced by doxygen.  Since this file is located in the \n \
source-folder the format of this string depends not on the operation-system. \n \
Until the behavior of Doxygen doesn't change the argument looks like this: \n\n \
          CFindex.xml\n\n \
If this argument is not used its information has to be defined abc2xml tries \n \
to find in the specified source directory this default-file : \n\n \
          " + String_imp(SOURCEFILE_DF) +
" \n\n \
If all these information are not given or not valid abc2xml terminates. \n \
If more than one of these Information are given the argument has the highest \n\n \
priority and the default-filer the lowest. \
\n "
},
*/
/*
{ String_imp(ARG_RESOURCEPATH) , " \n\n \
                        Resource-Path Argument \n  \
 \n \
This argument specifies the input-folder, that contains additional files\n \
which abc2xml needs to work. The format of this string depends on the \n \
operation-system. win32 needs \\ between the folder names linux / \n \
like this examples:  RP.abc2xml\\resources\\   RP./abc2xml/resources/ \n \
 \n \
If this argument is not used its information has to be defined in the \n \
config file which is specified by the argument CF like this example: \n\n \
           <Directories> \n \
            <ResourcePath value=\".\\res\\\" /> \n \
           </Directories> \n \
 \n \
If this is also not done abc2xml tries to use this default-folder : \n\n \
          " + String_imp(RESOURCEPATH_DF) +
" \n\n \
If all these information are not given or not valid abc2xml terminates. \n \
If more than one of these Information are given the argument has the highest \n \
priority and the default-folder the lowest. \
\n "
},
*/
/*
{ String_imp(ARG_CONFIGURATIONPATH) , " \n\n \
                        Configuration-Path Argument \n  \
 \n \
This argument specifies an alternative input-folder, that may contain files\n \
which abc2xml expects in other paths. The format of this string depends on the \n \
operation-system. win32 needs \\ between the folder names linux / \n \
like this examples:  CP.abc2xml\\resources\\   CP./abc2xml/resources/ \n \
 \n \
If this argument is not used its information has to be defined in the \n \
config file which is specified by the argument CF like this example: \n\n \
           <Directories> \n \
            <ConfigurationPath value=\".\\res\\\" /> \n \
           </Directories> \n \
 \n \
If more than one of these Information are given the argument has the highest \n \
priority and the content of the configuration-file the lowest. \
 \n \
If both are missing abc2xml does not use a alternative configuration-path. \n \
If the alternative configuration-path is found all resources found there will \n \
be used instead of those in the also configured resource-path. \n \
\n "
},
*/
{ "" , ""\
}
};



#endif // MULANPA_H
