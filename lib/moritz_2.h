/*!

 @file
 @brief definitions for the xml2abc-application a bnf-based parser-tool

 This file contains several definitions for the xml2abc main-source.

 Copyright (C) 2008-2020 by Eckard Klotz.

 Permission to use, copy, modify, and distribute this software and its
 documentation under the terms of the GNU General Public License is hereby
 granted. No representations are made about the suitability of this software
 for any purpose. It is provided "as is" without express or implied warranty.
 See the GNU General Public License for more details.

 Documents produced by xml2abc are derivative works derived from the
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
#ifndef MORITZ_2_H
#define MORITZ_2_H

#include "app_tool.h"
#include "gen_nsd.h"




#ifndef DOXYGEN
//namespace F_XML2ABC_MAIN {
#endif //DOXYGEN


/*!
 @defgroup XML2ABC_SOURCE Diverse Source-elements
 brief Collection of non class-associated elements inside the
 source-code of xml2abc

*/



/*!
 @brief creating and configuration of an generator-process object
 @ingroup XML2ABC_SOURCE


 @param [in] configuration     xml-part that contains the
                               user-defined configuration
 @param [in] usedPathSeparator character or character-sequence used as
                               separator of folder-path definitions in
                               user-configuration
 @param [in] osPathSeparator   character or character-sequence to be used
                               as separator of folder-path definitions in
                               current operation system of the computer
 @param [in] rootStrings       container of root-strings to be used for
                               file-paths if defined by user

 @return configured object ready to use


 @htmlinclude main_cpp_F_create_Gen_NDG.html
*/
Generator_Nsd* create_Gen_NDG(XML_Node       configuration,
                        const String_imp&    usedPathSeparator,
                        const String_imp&    osPathSeparator,
                  map<String_imp,String_imp> rootStrings);















/// @defgroup ARGUMENTXML xml-names of arguments
/// @ingroup XML2ABC_SOURCE
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
/// @ingroup XML2ABC_SOURCE
/// @{
const String_imp ARG_CONFIGURATIONFILE = "CF";
//const String_imp ARG_CONFIGURATIONPATH = "CP";
//const String_imp ARG_RESOURCEPATH      = "RP";
//const String_imp ARG_SOURCEPATH        = "SP";
const String_imp ARG_SOURCEFILE        = "SF";
const String_imp ARG_DESTINATIONPATH   = "DP";


const String_imp ARG_UsedPathSeparator = "UPS";
const String_imp ARG_OsPathSeparator   = "OPS";


//const String_imp ARG_DESCRIPTIONPATH   = "DscP";
/// @}



/// @defgroup ARGUMENTDEFAULT argument-defaults
/// @ingroup XML2ABC_SOURCE
/// @{
//const String_imp SOURCEFILE_DF        = "index.xml";
const String_imp CONFIGURATIONFILE_DF = "xml2abc_cfg.xml";

//const String_imp SOURCEPATH_DF        = "C:\\xml2abc\\xml\\";
//const String_imp RESOURCEPATH_DF      = "C:\\xml2abc\\res\\";
const String_imp DESTINATIONPATH_DF   = "C:\\xml2abc\\nsd\\";
//const String_imp DESCRIPTIONPATH_DF   = "C:\\xml2abc\\des\\";


#if defined(WINDOWS)
 const String_imp UsedPathSeparator_DF = "/";
 const String_imp OsPathSeparator_DF   = "\\";
#elif defined(LINUX)
 const String_imp UsedPathSeparator_DF = "\\";
 const String_imp OsPathSeparator_DF   = "/";
#else // no WINDOWS or LINUX
 const String_imp UsedPathSeparator_DF = "\\";
 const String_imp OsPathSeparator_DF   = "/";
#endif // WINDOWS LINUX or ???


/// @}



App_Info_TP Application_Info[] = {
{ "StartOutput" , "\
                        xml2abc Version 2.1.0  \n \
       generation of nassi shneiderman diagrams for source-codes \n \
               Copyright (C) 2004-"+String_imp(__DATE__).substr(String_imp(__DATE__).size()-4,4)+" by Eckard Klotz \n \
              Build date: "+String_imp(__DATE__)+" , time: "+String_imp(__TIME__)+" \n \
              Build as : _TARGET_POINTER_SIZE_ application  \n \
\n \
Permission to use, copy, modify, and distribute this software and its \n \
documentation under the terms of the GNU General Public License is hereby \n \
granted. No representations are made about the suitability of this software \n \
for any purpose. It is provided \"as is\" without express or implied warranty. \n \
See the GNU General Public License for more details. \n \
\n \
Documents produced by xml2abc are derivative works derived from the \n \
input used in their production; they are not affected by this license. \n \
\n \
To get first help use the command \" xml2abc help\" \n \
You can find more information under www.moritz.sourceforge.net or \n \
www.sourceforge.net/projects/moritz/ .\n \
Here you may download the manual or use the forum.\
\n"
},
{ "Help" , "\n \
                        Using the help Argument of xml2abc \n \
\n \
xml2abc                 -> general program-information \n \
xml2abc help            -> shows this text \n \
xml2abc help All        -> shows all help-information (reroute it into a file!) \n \
xml2abc help Resources  -> general overview about the needed resource-files \n \
xml2abc help Arguments  -> general overview about the command-line arguments \n \
xml2abc help "+String_imp(ARG_DESTINATIONPATH)+"         -> describes the destination-path argument \n \
xml2abc help "+String_imp(ARG_CONFIGURATIONFILE)+"         -> describes the configuration-file argument \n \
\n"
},

/*
xml2abc help "+String_imp(ARG_SOURCEFILE)+"         -> describes the source-file argument \n \
xml2abc help "+String_imp(ARG_CONFIGURATIONPATH)+"         -> describes the additional configuration-path argument \n \
xml2abc help "+String_imp(ARG_SOURCEPATH)+"         -> describes the source-path argument \n \
xml2abc help "+String_imp(ARG_RESOURCEPATH)+"         -> describes the resource-path argument \n \

*/

{ "Resources" , "\n \
                        Additional Resources\n \
\n \
xml2abc is configured by xml-files the main file includes some additional \n \
files. \n \
\n \
If no user-configuration is defined xml2abc tryes to load this out of his home\n \
directory : \n \
ansi_c_xml2abc_cfg.xml     -> prototype for the xml2abc main-configuration\n \
\n"
},
/*
PreProcessor.xml -> values of preprocessor values defined by the user\n \
adcmd_cfg.xml    -> declaration of the xml2abc commands (don't change)\n \
*/
{ "Arguments" , "\n \
                        xml2abc Command-Line Arguments \n \
\n \
Command-Line arguments are used to give xml2abc some base-informations about \n \
the directories and file which should be used. \n \
 \n \
The following argument tells xml2abc to use another configuration-file: \n \
 "+String_imp(ARG_CONFIGURATIONFILE)+"[configuration-file] file with detail-configurations default is mrtz_cfg.xml \n \
\
The following argument may be used to override the equal information in \n \
the used configuration-file: \n \
 "+String_imp(ARG_DESTINATIONPATH)+"[destination-path] destination-path of the created diagrams \n \
                       default-value : home-path of xml2abc \n \
\n \
Here are some examples: \n \
     win32     xml2abc "+String_imp(ARG_DESTINATIONPATH)+"c:\\docu\\nsd\\ \n \
     linux     xml2abc "+String_imp(ARG_CONFIGURATIONFILE)+"home:/project/config/xml2abc_cfg.xml \
\n"
},
/*
     win32     xml2abc "+String_imp(ARG_SOURCEPATH)+"c:\\docu\\xml\\ "+String_imp(ARG_DESTINATIONPATH)+"c:\\docu\\nsd\\ \n \
 "+String_imp(ARG_SOURCEPATH)+"[source-path] 	source-path of the xml-files \n \
 "+String_imp(ARG_RESOURCEPATH)+"[resource-path]	path with additional work-files of xml2abc  \n \

*/

/*
 "+String_imp(ARG_DESCRIPTIONPATH)+"[description-path] 	destination-path of the created description-tables \n \
 "+String_imp(ARG_CONFIGURATIONPATH)+"[configuration-path] alternative path with work-files of xml2abc  \n \
                       default-value : \"invalid\" path \n \
 "+String_imp(ARG_SOURCEFILE)+"[source-file] 	first xml-file default is index.xml \n \
*/
/*
{ String_imp(ARG_SOURCEPATH) , "\n \
                        Source-Path Argument \n \
 \n \
This argument specifies the input-folder for xml2abc, that contains the \n \
xml-output. The format of this string depends on the \n \
operation-system. win32 needs \\ between the folder names linux / \n\n \
like this examples:  SP.xml2abc\\source\\   SP./xml2abc/source/ \n \
 \n \
If this argument is not used its information has to be defined in the \n \
config file which is specified by the argument CF like this example: \n\n \
           <Directories> \n \
            <SourcePath value=\".\\xml\\\" /> \n \
           </Directories> \n \
 \n \
If this is also not done xml2abc tries to use this default-folder : \n\n \
          " + String_imp(SOURCEPATH_DF) +
" \n\n \
If all these information are not given or not valid xml2abc terminates. \n \
If more than one of these Information are given the argument has the highest \n \
priority and the default-folder the lowest. \
\n"
},*/
{ String_imp(ARG_DESTINATIONPATH) , " \n \
                        Destination-Path Argument \n  \
 \n \
This argument specifies the output-folder for xml2abc, that contains the \n \
nassi shneiderman diagrams. The format of this string depends on the \n \
operation-system. win32 needs \\ between the folder names linux / \n \
like this examples:  DP.xml2abc\\destination\\   DP./xml2abc/destination/ \n \
 \n \
If this argument is not used its information has to be defined in the \n \
config file which is specified by the argument CF like this example: \n\n \
           <Directories> \n \
            <DestinationPath value=\".\\nsd\\\" /> \n \
           </Directories> \n \
 \n \
If this is also not done xml2abc tries to use this default-folder : \n\n \
          " + String_imp(DESTINATIONPATH_DF) +
" \n\n \
If all these information are not given or not valid xml2abc terminates. \n \
If more than one of these Information are given the argument has the highest \n \
priority and the default-folder the lowest. \
\n"
},
/*
{ String_imp(ARG_DESCRIPTIONPATH) , " \n \
                        Description-Path Argument \n  \
 \n \
This argument specifies the output-folder for xml2abc, that contains the \n \
description tables. The format of this string depends on the \n \
operation-system. win32 needs \\ between the folder names linux / \n \
like this examples:  DscP.xml2abc\\description\\   DscP./xml2abc/description/ \n \
 \n \
If this argument is not used its information has to be defined in the \n \
config file which is specified by the argument CF like this example: \n\n \
           <Directories> \n \
            <<DescriptionPath value=\".\\des\\\" /> \n \
           </Directories> \n \
 \n \
If this is also not done xml2abc tries to use this default-folder : \n\n \
          " + String_imp(DESCRIPTIONPATH_DF) +
" \n\n \
If all these information are not given or not valid xml2abc terminates. \n \
If more than one of these Information are given the argument has the highest \n \
priority and the default-folder the lowest. \
\n "
},
*/
{ String_imp(ARG_CONFIGURATIONFILE) , " \n \
                        Configuration-File Argument \n  \
This argument specifies the main configuration files for xml2abc\n \
which allows the user to control the process of script generating. \n \
The format of this string depends on the operation-system. \n \
win32 needs \\ between the folder names linux / like this examples: \n\n \
   CF.xml2abc\\config\\xml2abc.xml   CF./xml2abc/config/xml2abc.xml \n \
 \n \
If this argument is not used its information has to be defined xml2abc tries \n \
to find in its own home directory this default-file : \n\n \
          " + String_imp(CONFIGURATIONFILE_DF) +
" \n\n \
If all these information are not given or not valid xml2abc terminates. \n \
If more than one of these Information are given the argument has the highest \n \
priority and the default-filer the lowest. \
\n "
},
/*
{ String_imp(ARG_SOURCEFILE) , " \n \
                        Source-File Argument \n  \
 \n \
This argument specifies the main input-file for xml2abc, that contains the \n \
first xml-output produced by doxygen.  Since this file is located in the \n \
source-folder the format of this string depends not on the operation-system. \n \
Until the behavior of Doxygen doesn't change the argument looks like this: \n\n \
          CFindex.xml\n\n \
If this argument is not used its information has to be defined xml2abc tries \n \
to find in the specified source directory this default-file : \n\n \
          " + String_imp(SOURCEFILE_DF) +
" \n\n \
If all these information are not given or not valid xml2abc terminates. \n \
If more than one of these Information are given the argument has the highest \n\n \
priority and the default-filer the lowest. \
\n "
},

{ String_imp(ARG_RESOURCEPATH) , " \n\n \
                        Resource-Path Argument \n  \
 \n \
This argument specifies the input-folder, that contains additional files\n \
which xml2abc needs to work. The format of this string depends on the \n \
operation-system. win32 needs \\ between the folder names linux / \n \
like this examples:  RP.xml2abc\\resources\\   RP./xml2abc/resources/ \n \
 \n \
If this argument is not used its information has to be defined in the \n \
config file which is specified by the argument CF like this example: \n\n \
           <Directories> \n \
            <ResourcePath value=\".\\res\\\" /> \n \
           </Directories> \n \
 \n \
If this is also not done xml2abc tries to use this default-folder : \n\n \
          " + String_imp(RESOURCEPATH_DF) +
" \n\n \
If all these information are not given or not valid xml2abc terminates. \n \
If more than one of these Information are given the argument has the highest \n \
priority and the default-folder the lowest. \
\n "
},

{ String_imp(ARG_CONFIGURATIONPATH) , " \n\n \
                        Configuration-Path Argument \n  \
 \n \
This argument specifies an alternative input-folder, that may contain files\n \
which xml2abc expects in other paths. The format of this string depends on the \n \
operation-system. win32 needs \\ between the folder names linux / \n \
like this examples:  CP.xml2abc\\resources\\   CP./xml2abc/resources/ \n \
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
If both are missing xml2abc does not use a alternative configuration-path. \n \
If the alternative configuration-path is found all resources found there will \n \
be used instead of those in the also configured resource-path. \n \
\n "
},
*/
{ "" , ""\
}
};


//};

#endif // MORITZ_2
