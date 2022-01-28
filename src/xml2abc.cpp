/*!

 @file
 @brief test-application of the new version of xml2abc

 This file contains the main-function of xml2abc and its help-functions only.
 Most of the detail-operations are done by classes contained in the included
 sources.

 Copyright (C) 2009-2020 by Eckard Klotz.

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
    04.12.2009     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    04.12.2009...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/

#include <iostream>
#include <dirent.h>
#include <list>

#include <fstream>
#include <sys/stat.h>

#include "StringC_help.h"



#include "xml_DataModel.h"
#include "xml_Replace.h"

#include "String_imp.h"
#include "app_tool.h"

#include "gen_nsd.h"

#include "cmnd_dict_xml.h"
#include "cmnd_parser.h"

#include "Spirit185_Xml.h"

#include "moritz_2.h"



#ifndef DOXYGEN
//namespace F_XML2ABC_MAIN {
#endif //DOXYGEN






/* @MRTZ_describe create_Gen_NDG

   @MRTZ_describe scan_Snipets

   @MRTZ_describe scan_grammar

   @MRTZ_describe scan_UserRuleProperties

   @MRTZ_describe setup_the_process

   @MRTZ_describe setup_Snipets

   @MRTZ_describe  setup_stack

*/
Generator_Nsd* create_Gen_NDG(XML_Node       configuration,
                        const String_imp&    usedPathSeparator,
                        const String_imp&    osPathSeparator,
                  map<String_imp,String_imp> rootStrings)
{
 Generator_Nsd* ReturnValue = nullptr;

// String_imp  Grammar             = "";

 char* Buffer  = nullptr;
 String_imp Generate =  XMLNODE_GET_SUBCHILD_TEXT(configuration,"Process/Generate",&Buffer);
 if(Buffer != nullptr)
   delete[](Buffer);

#if defined(DEBUG_OUTPUT)
 cout << endl;
 SubConfiguration->Print(stdout,1);
 cout << endl;
#endif

// @MRTZ_exclude scan_Snipets
// @MRTZ_beginBlock
 String_imp  Snipet = "";
 XML_Node Node = configuration.firstGet(XML_Node::Element(XML_Search::Value,"Process/SnipetParser/Snipet/File"));
 while(Node.valid() == true)
 {
  String_imp Text = Node.attributeGet("value");
  String_imp Root = Node.attributeGet("root");
  Root = rootStrings[Root];
  if(  (Root                        != "")
     &&(Root.rfind(osPathSeparator) <  Root.size()-1)
    )
   Root = Root + osPathSeparator;
  if(Text != "")
   Snipet = Snipet +  readTextFile(Root + Text, usedPathSeparator, osPathSeparator);
#if defined(DEBUG_OUTPUT)
  cout << endl;
  cout << "Snipet:" << Snipet << endl;
  cout << endl;
#endif
  Node = Node.behindGet(XML_Node::Element(XML_Search::Value,"File"));
 }
 Buffer  = nullptr;
  Snipet = Snipet + XMLNODE_GET_SUBCHILD_TEXT(configuration,"Process/SnipetParser/Snipet",&Buffer);
 if(Buffer != nullptr)
   delete[](Buffer);

// if(Snipet == "")
// {
//  Snipet = "";
// }
#if defined(DEBUG_OUTPUT)
  cout << endl;
  cout << Snipet << endl;
  cout << endl;
#endif
// @MRTZ_endBlock



// @MRTZ_exclude scan_grammar
// @MRTZ_beginBlock
 String_imp  Grammar = "";
 Node = configuration.firstGet(XML_Node::Element(XML_Search::Value,"Process/SnipetParser/Grammar/File"));
 while(Node.valid() == true)// != nullptr)
 {
  String_imp Text = Node.attributeGet("value");
  String_imp Root = Node.attributeGet("root");
  Root = rootStrings[Root];
  if(  (Root                        != "")
     &&(Root.rfind(osPathSeparator) <  Root.size()-1)
    )
   Root = Root + osPathSeparator;

  if(Text != "")
   Grammar = Grammar + readTextFile(Root + Text, usedPathSeparator, osPathSeparator);
  Node = Node.behindGet(XML_Node::Element(XML_Search::Value,"File"));
 }
 Buffer  = nullptr;
 Grammar = Grammar +  XMLNODE_GET_SUBCHILD_TEXT(configuration,"Process/SnipetParser/Grammar",&Buffer);
 if(Buffer != nullptr)
   delete[](Buffer);

 if(Grammar == "")
 {
  Grammar = " fail = (anychar_p ^ '#'); \n\
              pass = ('#' >> *(anychar_p - eol_p) >> eol_p);";
 }
#if defined(DEBUG_OUTPUT)
  cout << endl;
  cout << Grammar << endl;
  cout << endl;
#endif
// @MRTZ_endBlock

 int DebugLevel = stringToNumber(XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                                "Process/SnipetParser/DebugLevel",
                                                                "value",
                                                                 numberToString(0).c_str()));
#if defined(DEBUG_OUTPUT)
  cout << endl;
  cout << DebugLevel << endl;
  cout << endl;
#endif

 String_imp PaserLogFile = XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                          "Process/SnipetParser/DebugLevel",
                                                          "file",
                                                          "SnippetLog");

 String_imp Root = XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                  "Process/SnipetParser/DebugLevel",
                                                  "root",
                                                  "");
 Root = rootStrings[Root];
 if(  (Root                        != "")
    &&(Root.rfind(osPathSeparator) <  Root.size()-1)
   )
  Root = Root + osPathSeparator;

 if(usedPathSeparator != osPathSeparator) //do it only if it has to be done
 {
  PaserLogFile = replacePartString(Root + PaserLogFile,
                                   usedPathSeparator,
                                   osPathSeparator);
  createFolder(Root, osPathSeparator[0]); // create destination-folder
 }

// String_imp         GlobalToken         = "";
 Buffer           = nullptr;// (char*)GlobalToken.c_str();
 String_imp  GlobalToken      = XMLNODE_GET_SUBCHILD_TEXT(configuration, "Process/SnipetParser/GlobalToken",      &Buffer);
 delete[](Buffer);

// String_imp         GlobalNotPhrased    = "";
 Buffer           = nullptr;// (char*)GlobalNotPhrased.c_str();
 String_imp  GlobalNotPhrased = XMLNODE_GET_SUBCHILD_TEXT(configuration, "Process/SnipetParser/GlobalNotPhrased", &Buffer);
 delete[](Buffer);

// String_imp         GlobalHide          = "";
 Buffer           = nullptr;// (char*)GlobalHide.c_str();
 String_imp  GlobalHide       = XMLNODE_GET_SUBCHILD_TEXT(configuration, "Process/SnipetParser/GlobalHide",       &Buffer);
 delete[](Buffer);

// String_imp         GlobalSkipLevel     = "";
 Buffer           = nullptr;// (char*)GlobalSkipLevel.c_str();
 String_imp  GlobalSkipLevel  = XMLNODE_GET_SUBCHILD_TEXT(configuration, "Process/SnipetParser/GlobalSkipLevel",  &Buffer);
 delete[](Buffer);

// @MRTZ_endBlock


// @MRTZ_exclude  setup_the_process
// @MRTZ_beginBlock
  ReturnValue = new Generator_Nsd(Generate);


  ReturnValue->UserRulePropertyGlobal_set(Prcs_Transformation::URP_NOTPHRASED,
                                          GlobalNotPhrased);
  ReturnValue->UserRulePropertyGlobal_set(Prcs_Transformation::URP_TOKEN,
                                          GlobalToken);
  ReturnValue->UserRulePropertyGlobal_set(Prcs_Transformation::URP_HIDE,
                                          GlobalHide);
  ReturnValue->UserRulePropertyGlobal_set(Prcs_Transformation::URP_SKIPLEVEL,
                                          GlobalSkipLevel);
// @MRTZ_endBlock



  String_imp     LogOutputFile    = "";
  XML_Node Detail = configuration.firstGet(XML_Node::Element(XML_Search::Value,"Process/Notation/OutputRule"));
  if(lowCaseString(Detail.attributeGet("value")) == String_imp("yes"))
  {
   LogOutputFile = replacePartString(Detail.attributeGet("folder"),
                                     usedPathSeparator,
                                     osPathSeparator) + "Snippet.txt";
   createFolder(LogOutputFile, osPathSeparator[0]); // create destination-folder
  }
  else // rules should not be outputted
  {
   LogOutputFile = "";
  }

  int LimitCallingTree = 5;
  int LimitCallingNode = 30;
  Detail = configuration.firstGet(XML_Node::Element(XML_Search::Value,"Process/Notation/OutputCalled"));
  if(  (lowCaseString(Detail.attributeGet("value"))        == String_imp("yes"))
     &&(lowCaseString(Detail.attributeGet("minimumEdges")) == String_imp("yes"))
    )
  {
   LimitCallingTree = stringToNumber(XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                                    "Process/Notation/OutputCalled",
                                                                    "limitTree",
                                                                     numberToString(LimitCallingTree).c_str()));

   LimitCallingNode = stringToNumber(XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                                    "Process/Notation/OutputCalled",
                                                                    "limitNode",
                                                                    numberToString(LimitCallingNode).c_str()));

  }
  else  if(  (lowCaseString(Detail.attributeGet("value"))        == String_imp("yes"))
           &&(lowCaseString(Detail.attributeGet("minimumEdges")) == String_imp("no"))
          )
  {
   LimitCallingTree = INT_MAX;
   LimitCallingNode = INT_MAX;
  }
  else
  {
   LimitCallingTree = -1;
   LimitCallingNode = -1;
  }

  int LimitCallerTree = 5;
  int LimitCallerNode = 30;
  Detail = configuration.firstGet(XML_Node::Element(XML_Search::Value,"Process/Notation/OutputCaller"));
  if(  (lowCaseString(Detail.attributeGet("value"))        == String_imp("yes"))
     &&(lowCaseString(Detail.attributeGet("minimumEdges")) == String_imp("yes"))
    )
  {
   LimitCallerTree = stringToNumber(XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                                   "Process/Notation/OutputCaller",
                                                                   "limitTree",
                                                                   numberToString(LimitCallerTree).c_str()));

   LimitCallerNode = stringToNumber(XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                                   "Process/Notation/OutputCaller",
                                                                   "limitNode",
                                                                   numberToString(LimitCallerNode).c_str()));
  }
  else  if(  (lowCaseString(Detail.attributeGet("value"))        == String_imp("yes"))
           &&(lowCaseString(Detail.attributeGet("minimumEdges")) == String_imp("no"))
          )
  {
   LimitCallerTree = INT_MAX;
   LimitCallerNode = INT_MAX;
  }
  else
  {
   LimitCallerTree = -1;
   LimitCallerNode = -1;
  }

 const char* LogOutInfo = nullptr;
 if(LogOutputFile != "")
  LogOutInfo = LogOutputFile.c_str();

 ReturnValue->grammar_init(Grammar.c_str(),
                           "pass","skip","line",
                           GlobalNotPhrased.c_str(),
                           (replacePartString(Root + "*.a2x", usedPathSeparator, osPathSeparator)).c_str(),
                           LogOutInfo,
                          (DebugLevel != 0),
                           LimitCallingTree,
                           LimitCallingNode,
                           LimitCallerTree,
                           LimitCallerNode);

// @MRTZ_exclude  setup_Snipets
 if(Snipet != "")
 {
  TiPa_DataModel CodeTree;

  ReturnValue->analyse( &Snipet, &CodeTree,  RAW_TEXT);

  XML_DataModel SnippetLogModel;
  Spirit185_Xml Converter;
                Converter.contextModel_set(&SnippetLogModel);
                Converter.setSpcialTag(ReturnValue->getSymbols("Keyword"),
                                       ReturnValue->getSymbols("KeyChr")
                                      );
  XML_Node SnippetLog = SnippetLogModel.rootNode();
  CodeTree.focus_Fellow()->welcome(Converter(Spirit185_Xml::Content2XML,&SnippetLog),IterateDownwards);

#if defined(DEBUG_OUTPUT)
  cout << "analyse ready" << endl;
#endif //DEBUG_OUTPUT


  String_imp     SnippetLogFile   = "SnippetLog";

  if(lowCaseString(XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                  "Process/SnipetParser/Snipet",
                                                  "outputLog","No"
                                                 )
                   ) == "yes"
    )
  {
   SnippetLogFile = XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                  "Process/SnipetParser/Snipet",
                                                  "file",
                                                   SnippetLogFile.c_str());

   Root = XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                         "Process/SnipetParser/Snipet",
                                         "root",
                                         SnippetLogFile.c_str());
   Root = rootStrings[Root];
   if(  (Root                        != "")
      &&(Root.rfind(osPathSeparator) <  Root.size()-1)
     )
    Root = Root + osPathSeparator;

   createFolder(replacePartString(Root + SnippetLogFile,
                                  usedPathSeparator,
                                  osPathSeparator),
                                  osPathSeparator[0]); // create destination-folder
   if(SnippetLog.valid() == true)
   {
    char* ParsedText  = nullptr;    // xml-text

    SnippetLog.xmlText(&ParsedText);

    if(ParsedText != nullptr)
    {
     ofstream  File((Root + SnippetLogFile).c_str(),ios_base::binary|ios_base::out);

     if(File.good()) // file successfully opened
     {
      File << ParsedText;
      File.close();
     }
    }

    delete[]ParsedText;
   }
   else
   {
    cout << "snippet-log was not defined" << endl;
   }


#if defined(DEBUG_OUTPUT)
   cout << " log is saveved under " << SnippetLogFile << endl;
#endif //DEBUG_OU  TPUT

  }
  CodeTree.init();
 }


// @MRTZ_exclude  setup_stack
// @MRTZ_beginBlock
 Node = configuration.firstGet(XML_Node::Element(XML_Search::Value,"Process/SnipetParser/Stack/Key"));
 while(Node.valid() == true)
 {
  String_imp Text = Node.attributeGet("name");
  if(Text != "")
   ReturnValue->addStackValue(Text,Node.attributeGet("content" ));
  Node = Node.behindGet(XML_Node::Element(XML_Search::Value,"Key"));
 }
// @MRTZ_endBlock

 return(ReturnValue);

}




#ifndef DOXYGEN
#define USING_NAMESPACE using namespace
//}; USING_NAMESPACE F_XML2ABC_MAIN;
#undef  USING_NAMESPACE
#endif //DOXYGEN



/*!
 main-function of the application

 @param [in] argc  number of values in the arg-array of the
                   application
 @param [in] argv  arg-array of the application

 @return EXIT_FAILURE     == error occurred
 <br>    EXIT_SUCCESS == normal end off application without errors

 @htmlinclude main_cpp_F_main.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    04.12.2009   @I  Eckard Klotz @I First Implementation @I
 @I_______________________________________________________
    19.02.2012   @I  Eckard Klotz
 @I re-factoring
 @I replaced called functions from main-files into calls of functions defined
    in library-file that contains common application-tools
 @I_______________________________________________________
    02.06.2013      @I  Eckard Klotz
 @I re-factoring
 @I use of replacement-mechanism for separators in path-strings
 @I_______________________________________________________
    18.08.2013      @I  Eckard Klotz
 @I bug user-paths defined as empty-strings may result in
    invalid path-strings if relative path-definitions in other
    configurations don't contain a valid path-begin
 @I empty user-paths used as root of relative paths will be
    replaced by a point followed by a path-separator
 @I_______________________________________________________
    12.10.2013      @I  Eckard Klotz
 @I bug: xml-comments lead to crash
 @I xml-iterations will be done by using TixmlNode instead
    of TiXmlElement,
    as first action in the loop a macro checks if the
    current-element is a xml-comment and forces immediate
    the start of the next loop
 @I_______________________________________________________
    21.12.2014   @I  Eckard Klotz
 @I re-factoring application arguments
 @I use of new function and adding the arguments to the already
    loaded xml-configuration
@I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
int main(int argc, char* argv[])
/* @MRTZ_describe main

   @MRTZ_describe files_and_paths

   @MRTZ_describe define_configuration-file

   @MRTZ_describe load_configuration-file

   @MRTZ_describe define_destination-path

   @MRTZ_describe define_user-path

   @MRTZ_describe init_process

   @MRTZ_describe do_process

   @MRTZ_describe shut_down_process

*/
{
//cout<<__FILE__<<"|main|"<<"("<<__LINE__<<") enter"<<endl;
 String_imp        CommonAttachment    = ".xml";
 info(argc, argv, "help", Application_Info);

#if defined(DEBUG_OUTPUT)
 printf("Funktions-Start \n");
#endif
#if defined(DEBUG_BREAK)
   system("PAUSE");
#endif

// @MRTZ_exclude files_and_paths
// @MRTZ_beginBlock

//  @MRTZ_exclude define_configuration-file
//  @MRTZ_beginBlock
 String_imp ConfigurationFile = "";
 String_imp ArgumentBuffer    =  getAgument(argc, argv, ARG_CONFIGURATIONFILE);
 if(ArgumentBuffer != "")       // configuration-file found as argument
  ConfigurationFile = ArgumentBuffer;
 else                           // configuration-file not found as argument
 {
  ConfigurationFile = argv[0];  // read path and name of this application
// @MRTZ_ifElseChain
  if     (ConfigurationFile.rfind('\\') < ConfigurationFile.size()) //dos-path
   ConfigurationFile = ConfigurationFile.substr(0,ConfigurationFile.rfind('\\'))
                      + "\\" + CONFIGURATIONFILE_DF;
              // clear application-name from path and add default config-file
  else if(ConfigurationFile.rfind('/' ) < ConfigurationFile.size()) //linux-path
   ConfigurationFile = ConfigurationFile.substr(0,ConfigurationFile.rfind('/'))
                      + "/" + CONFIGURATIONFILE_DF;
              // clear application-name from path and add default config-file
  else        // operation-system not known
   ConfigurationFile = CONFIGURATIONFILE_DF;
              // set default konfig-file
 };
//  @MRTZ_endBlock



#if defined(DEBUG_OUTPUT)
 printf("ConfigurationFile : %s \n",ConfigurationFile.c_str());
#endif
#if defined(DEBUG_BREAK)
   system("PAUSE");
#endif


//  @MRTZ_exclude load_configuration-file
//  @MRTZ_beginBlock

  String_imp UsedPathSeparator = getConfigValue(XML_Node(),//nullptr,
                                                XML_PATH,
                                                argc, argv,
                                                ARG_UsedPathSeparator,
                                                UsedPathSeparator_DF);

  String_imp OsPathSeparator =  getConfigValue(XML_Node(),//nullptr,
                                               XML_PATH,
                                               argc, argv,
                                               ARG_OsPathSeparator,
                                               OsPathSeparator_DF);


 printf("load configuration-file \n");

 String_imp FileText = readTextFile(ConfigurationFile, UsedPathSeparator, OsPathSeparator);

 XML_DataModel                        ConfigurationModel;
 XML_Node                             ConfigurationContent;
 XML_Node                             Configuration;
 map<String_imp,String_imp>           RootStrings;
 map<String_imp,String_imp>::iterator RootString;

 if(ConfigurationModel.load(ConfigurationFile.c_str()) == true)
 {
  ConfigurationContent   = ConfigurationModel.rootNode().firstGet(XML_Node::Element(XML_Search::Value,"Configuration"));
  XML_Node UserArguments = getUserDefinitions(ConfigurationContent,argc, argv);
  cout << endl << "added under configuration root called \""
               << ConfigurationContent.valueGet()
               << "\" the new sub-node : "
               << endl;
  UserArguments.xmlText();
  cout << endl << "this sub node contains all application arguments which start with \""
               << ARG_UA
               << "\""
               << endl;
#if defined(DEBUG_OUTPUT)
  cout << endl;
  ConfigurationContent->Print(stdout,1);
  cout << endl;
#endif
  XML_Replace ReplaceDataReference;
  ConfigurationContent.associationNodeGet()->welcome(ReplaceDataReference(ConfigurationContent.associationContextGet()),IterateDownwards);
                                                                                                  // insertion of user-arguments into xml-configuration

  Configuration = ConfigurationContent.firstGet(XML_Node::Element(XML_Search::Value,XML_PATH.c_str()));

  UsedPathSeparator =  getConfigValue(ConfigurationContent,
                                      XML_PATH,
                                      argc, argv,
                                      ARG_UsedPathSeparator,
                                      UsedPathSeparator_DF);

  OsPathSeparator =  getConfigValue(ConfigurationContent,
                                    XML_PATH,
                                    argc, argv,
                                    ARG_OsPathSeparator,
                                    OsPathSeparator_DF);


//  @MRTZ_exclude define_user-path
//  @MRTZ_beginBlock
  XML_Node UserPathes = Configuration.firstGet(XML_Node::Element(XML_Search::Value,XML_USERPATH.c_str()));
  if(UserPathes.valid() == true)
  {
   XML_Node UserElement = UserPathes.firstGet(XML_Node::Element());
   while(UserElement.valid() == true)
   {
    String_imp PathString = replacePartString(UserElement.attributeGet("value"), UsedPathSeparator, OsPathSeparator);
    if(PathString == "")
     PathString = "." + OsPathSeparator;

    RootStrings[UserElement.valueGet()] = PathString;

    UserElement = UserElement.behindGet(XML_Node::Element());
   }
  }
  else
  {
   cout << "no user-paths defined." << endl;
  }

//  @MRTZ_endBlock

  printf("analyse configuration-file \n");
  completeXML(ConfigurationContent,UsedPathSeparator,OsPathSeparator,RootStrings);

  XML_Node ProcessConfiguration = ConfigurationContent.firstGet(XML_Node::Element(XML_Search::Value,"Process"));
  if(ProcessConfiguration.valid() == true)   // new tag-name in use
  {
    cout << endl << "You are already using a new and valid configuration to include the process-configuration." << endl;
    cout << "-> There is no need to change the associated tag-name." << endl << endl;
  }
  else
  {
   ProcessConfiguration = ConfigurationContent.firstGet(XML_Node::Element(XML_Search::Value,"GeneratorNSD"));
   if(ProcessConfiguration.valid() == true)  // old tag-name in use
   {
    ProcessConfiguration.valueSet("Process");
    // to ensure that old configurations which have still the tag  will be updated internally
    cout << endl << "warning: you are using an old configuration file!" << endl;
    cout << "->Please rename in your user-configuration the last tag, used to" << endl;
    cout << "  include the process-configuration, from \"GeneratorNSD\" into \"Process\"" << endl << endl;
   }
   else
   {
    ProcessConfiguration = ConfigurationContent.firstGet(XML_Node::Element());
    while(  (ProcessConfiguration.valid()                     == true   )
          &&(ProcessConfiguration.attributeGet("includeFile") == nullptr)
         )
     ProcessConfiguration = ProcessConfiguration.behindGet(XML_Node::Element());

    if(ProcessConfiguration.valid() == true)   // old tag-name in use
    {
     ProcessConfiguration.valueSet("Process");
     // to ensure that old configurations which have still the tag  will be updated internally
     cout << endl << "warning: you are using an unusual configuration file!" << endl;
     cout << "->Please rename in your user-configuration the last tag, used to" << endl;
     cout << "  include the process-configuration, into \"Process\"" << endl << endl;
    }
    else
    {
     cout << endl << "fatal error: you are using an invalid configuration file!" << endl;
     cout << "->Please ensure in your user-configuration the last tag, used to" << endl;
     cout << "  include the process-configuration, is called  \"Process\"" << endl << endl;
    }

   }
  }

 }
 else
 {
  printf("file \"%s\" not found !\n",ConfigurationFile.c_str());
  printf("or the file has xml-errors. \n");
  printf("xml2abc will terminate now. \n");

  return EXIT_FAILURE;
 }

#if defined(DEBUG_BREAK)
   system("PAUSE");
#endif
//  @MRTZ_endBlock

//  cout << "################################################################################################################" << endl;
  XML_Replace ReplaceDataReference;
  ConfigurationContent.associationNodeGet()->welcome(ReplaceDataReference(ConfigurationContent.associationContextGet()),IterateDownwards);
//  cout << endl << "################################################################################################################" << endl;
//  ConfigurationContent.xmlText();
//  cout << endl << "################################################################################################################" << endl;

//  @MRTZ_exclude define_destination-path
//  @MRTZ_beginBlock
 String_imp DestinationPath =  getConfigValue(Configuration,
                                              XML_DESTINATIONPATH,
                                              argc, argv,
                                              ARG_DESTINATIONPATH,
                                              DESTINATIONPATH_DF);

 if(UsedPathSeparator != OsPathSeparator) //do it only if it has to be done
  DestinationPath = replacePartString(DestinationPath,UsedPathSeparator,OsPathSeparator);
 if( DestinationPath.rfind(OsPathSeparator) < DestinationPath.size()-1)
  DestinationPath = DestinationPath + OsPathSeparator;
 if( DestinationPath == "")
  DestinationPath = "." + OsPathSeparator;

 RootStrings[XML_DESTINATIONPATH]=DestinationPath;

 printf("destination-path : %s \n",DestinationPath.c_str());
#if defined(DEBUG_BREAK)
   system("PAUSE");
#endif
//  @MRTZ_endBlock


// @MRTZ_endBlock


// @MRTZ_exclude init_process
// @MRTZ_beginBlock


 cout << endl << endl << "configure script-generator" << endl << endl;

 XML_DataModel SourceContent ;

 Cmnd_Dict_XML::xmlContext_init();
 Cmnd_Parser::setFolderRoots(UsedPathSeparator,
                             OsPathSeparator,
                             RootStrings);

 Generator_Nsd* Gen_NDG_prcs = create_Gen_NDG(ConfigurationContent,
                                              UsedPathSeparator,
                                              OsPathSeparator,
                                              RootStrings );

                Gen_NDG_prcs->xmlContext_set(&SourceContent);
// @MRTZ_endBlock

 XML_Node Source = ConfigurationContent.firstGet(XML_Node::Element(XML_Search::Value,"Source"));
 if(Source.valid() == true)// != nullptr)
 {

  Gen_NDG_prcs->addStackValue("__USEDPATHSEPARATOR__", UsedPathSeparator);
  Gen_NDG_prcs->addStackValue("__OSPATHSEPARATOR__",   OsPathSeparator);
  Gen_NDG_prcs->addStackValue("__SOURCENAME__",        "");
  Gen_NDG_prcs->addStackValue("__DESTINATIONPATH__",   DestinationPath);

  RootString = RootStrings.begin();
  while(RootString != RootStrings.end())
  {
    Gen_NDG_prcs->addStackValue("__"+RootString->first+"__",RootString->second);
   ++RootString;
  }

  list<String_imp>            Diagram;
  map<String_imp, String_imp> ReplacementDummi;
  Gen_NDG_prcs->snippet(XML_Node(), "__FirstSnippetOfAll__",
                        &ReplacementDummi,&Diagram, true);

  Configuration = Source.firstGet(XML_Node::Element());
  while(Configuration.valid() == true)// != nullptr)
  {
   const char* Text = Configuration.attributeGet("value");

   if(  (Text              != nullptr)
      &&(UsedPathSeparator != OsPathSeparator)
     ) //do it only if it has to be done
    Configuration.attributeSet("value",replacePartString(Text, UsedPathSeparator, OsPathSeparator).c_str());

// @MRTZ_ifElseChain
   if(STRINGS_ARE_EQUAL(Configuration.valueGet(), "FileName"))
   {
// @MRTZ_exclude do_process
// @MRTZ_beginBlock

     String_imp SourceName   = Configuration.attributeGet("root");
                SourceName   = RootStrings[SourceName];

     if(UsedPathSeparator != OsPathSeparator) //do it only if it has to be done
      SourceName = replacePartString(SourceName,UsedPathSeparator,OsPathSeparator);
     if( SourceName.rfind(OsPathSeparator) < SourceName.size()-1)
      SourceName = SourceName + OsPathSeparator;

     SourceName = SourceName + Configuration.attributeGet("value");
     String_imp DoNotSkip  = Configuration.attributeGet("doNotSkip");

     list<String_imp>  Destination;

     Destination.clear();
     if(lowCaseString(DoNotSkip)!="yes")
     {
      while(SourceName.find("\\")<SourceName.size())
      {
       SourceName = SourceName.replace(0,SourceName.find("\\")+1,"");
      }
      while(SourceName.find("/")<SourceName.size())
      {
       SourceName = SourceName.replace(0,SourceName.find("/")+1,"");
      }
      SourceName = SourceName.substr(0,SourceName.find_last_of('.'));
      Destination.push_back(DestinationPath + SourceName + ".html");
     }

     SourceName   = Configuration.attributeGet("root");
     SourceName   = RootStrings[SourceName];

     if(UsedPathSeparator != OsPathSeparator) //do it only if it has to be done
      SourceName = replacePartString(SourceName,UsedPathSeparator,OsPathSeparator);
     if( SourceName.rfind(OsPathSeparator) < SourceName.size()-1)
      SourceName = SourceName + OsPathSeparator;

     SourceName = SourceName + Configuration.attributeGet("value");

     if(UsedPathSeparator != OsPathSeparator) //do it only if it has to be done
      SourceName = replacePartString(SourceName,UsedPathSeparator,OsPathSeparator);

     if(checkNewSource(SourceName,Destination,
                                   UsedPathSeparator,
                                   OsPathSeparator) == true)

     {
      cout << endl<< "SourceName :" << SourceName << endl;
      SourceContent.init();
      if(SourceContent.load(SourceName.c_str()) == true)
      {
       Gen_NDG_prcs->addStackValue("__SOURCEFILE__",     SourceName);
       while(SourceName.find("\\")<SourceName.size())
       {
        SourceName = SourceName.replace(0,SourceName.find("\\")+1,"");
       }
       while(SourceName.find("/")<SourceName.size())
       {
        SourceName = SourceName.replace(0,SourceName.find("/")+1,"");
       }

       Gen_NDG_prcs->addStackValue("__SOURCENAME__",     SourceName);
       Gen_NDG_prcs->addStackValue("__DESTINATIONPATH__",DestinationPath);
       RootString = RootStrings.begin();
       while(RootString != RootStrings.end())
       {
         Gen_NDG_prcs->addStackValue("__"+RootString->first+"__",RootString->second);
        ++RootString;
       }
       XML_Node SourceRoot = SourceContent.rootNode();

       Gen_NDG_prcs->snippet(SourceRoot, "__FirstSnippetOfFile__",
                             &ReplacementDummi,&Diagram, true);
       Gen_NDG_prcs->generate(SourceRoot,DestinationPath+SourceName);
       Gen_NDG_prcs->snippet(SourceRoot, "__LastSnippetOfFile__",
                             &ReplacementDummi,&Diagram, true);
      }
      else
      {
       printf("file \"%s\" not found !\n",SourceName.c_str());
       printf("or the file has xml-errors. \n");
      }
     // delete(SourceContent);
     }
     else
     {
      FileText = "";
      cout << endl << "SourceName: " << SourceName
      << "\n -> skiped since has souce not changed " << endl;
     }

// @MRTZ_endBlock
   }
   else if(STRINGS_ARE_EQUAL(Configuration.valueGet(), "FolderName"))
   {
    searchFiles(Configuration,
                CommonAttachment,
                UsedPathSeparator,
                OsPathSeparator);
   }
   else
   {
   }
   Configuration = Configuration.behindGet(XML_Node::Element());
  }



  Gen_NDG_prcs->addStackValue("__SOURCENAME__",     "");
  Gen_NDG_prcs->addStackValue("__DESTINATIONPATH__",DestinationPath);

  Gen_NDG_prcs->snippet(XML_Node()/*nullptr*/, "__LastSnippetOfAll__",
                        &ReplacementDummi,&Diagram, true);
 }

// @MRTZ_exclude shut_down_process
// @MRTZ_beginBlock
 delete Gen_NDG_prcs;
// @MRTZ_endBlock

//cout<<__FILE__<<"|main|"<<"("<<__LINE__<<") leave"<<endl;
 return 0;
}
