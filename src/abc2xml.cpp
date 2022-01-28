/*!

 @file
 @brief test-application of a bnf-based parser-process

 This file contains a test-application of a bnf-based parser-process.

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
    07.12.2008     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    07.12.2008...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/

#include <iostream>
#include <dirent.h>
#include <limits.h>
#include <list>
#include <ctime>

#include <fstream>
#include <sys/stat.h>




#include "xml_DataModel.h"
#include "xml_Replace.h"
#include "String_imp.h"
#include "StringC_help.h"
#include "app_tool.h"

#include "coreflow.h"
#include "merge.h"
#include "mulanpa.h"



using namespace std;






/* @MRTZ_describe createDirectiveProcess

   @MRTZ_describe scan_grammar

   @MRTZ_describe scan_diverse_values

   @MRTZ_describe scan_UserRuleProperties

   @MRTZ_describe scan_lineprocess_information

   @MRTZ_describe setup_the_process

*/
Prcs_Trn_Directive* createDirectiveProcess(      XML_Node       configuration,
                                           const String_imp&    process,
                                                 bool*          savePartResult,
                                                 String_imp*    attachment,
                                           const String_imp&    usedPathSeparator,
                                           const String_imp&    osPathSeparator,
                                     map<String_imp,String_imp> rootStrings)
{
 Prcs_Trn_Directive* ReturnValue    = nullptr;

 XML_Node  Detail = configuration.firstGet(XML_Node::Element(XML_Search::Value,(string("Process/") + process + "/SavePartResult").c_str()));
 if(lowCaseString(Detail.attributeGet("value")) == String_imp("no"))
 {
  (*savePartResult) = false;
 }

 String_imp Attachment = Detail.attributeGet("attachment");
 if(Attachment != "")
  (*attachment) = Attachment;

 bool ShowTextToParse            = false;
 if(lowCaseString(XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                 (string("Process/") + process + "/ShowTextToParse").c_str(),
                                                 "value",
                                                 ""
                                                )) == String_imp("yes"))
 {
  ShowTextToParse = true;
 }

 bool ParseTolerant              = false;
 if(lowCaseString(XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                             (string("Process/") + process + "/ParseTolerant").c_str(),
                                             "value",
                                             "")) == String_imp("yes"))
 {
  ParseTolerant = true;
 }

// @MRTZ_exclude scan_grammar
// @MRTZ_beginBlock
 String_imp  Grammar             = "";
 String_imp  GrammarText         = "";
 XML_Node  Node = configuration.firstGet(XML_Node::Element(XML_Search::Value,(string("Process/") + process + "/Grammar/File").c_str()));
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
  {
   Grammar = Grammar + readTextFile(Root + Text, usedPathSeparator, osPathSeparator);
   GrammarText = Root + Text;
  }
  else
  {
   GrammarText = "Source Process Grammar";
  }
  Node = Node.behindGet(XML_Node::Element(XML_Search::Value,"File"));
 }
 char* Buffer  = nullptr;
 Grammar = Grammar +  XMLNODE_GET_SUBCHILD_TEXT(configuration,(string("Process/") + process + "/Grammar").c_str(),&Buffer);
 if(Buffer != nullptr)
   delete[](Buffer);
// @MRTZ_endBlock


 int DebugLevel = stringToNumber(XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                                (string("Process/") + process + "/DebugLevel").c_str(),
                                                                 "value",
                                                                 numberToString(0).c_str()));
 String_imp PaserLogFile = "DirectiveLog";
 PaserLogFile = XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                               (string("Process/") + process + "/DebugLevel").c_str(),
                                               "file",
                                               PaserLogFile.c_str());
 String_imp Root = XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                  (string("Process/") + process + "/DebugLevel").c_str(),
                                                  "root",
                                                  "");
 Root = rootStrings[Root];
 if(  (Root                        != "")
    &&(Root.rfind(osPathSeparator) <  Root.size()-1)
   )
  Root = Root + osPathSeparator;

 if(usedPathSeparator != osPathSeparator) //do it only if it has to be done
 {
  PaserLogFile = replacePartString(Root + PaserLogFile, usedPathSeparator, osPathSeparator);
  createFolder(Root, osPathSeparator[0]); // create destination-folder
 }


// @MRTZ_exclude scan_diverse_values
// @MRTZ_beginBlock
 Detail = configuration.firstGet(XML_Node::Element(XML_Search::Value,"Process/Merge/UseComment"));
 bool DontMerge = true;
 if(lowCaseString(Detail.attributeGet( "value","no")) == String_imp("yes"))
 {
  DontMerge = false;
 }
 Detail = configuration.firstGet(XML_Node::Element(XML_Search::Value,"Process/Merge/UseLine"));
 if(lowCaseString(Detail.attributeGet("value","no")) == String_imp("yes"))
 {
  DontMerge = false;
 }

 int PositionOutput = 2;
 if(DontMerge == true)
 {
  PositionOutput = stringToNumber(XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                                 (string("Process/") + process + "/PositionOutput").c_str(),
                                                                 "value",
                                                                 "2"));
 }
 else
 {
  PositionOutput = 2;
 }
// @MRTZ_endBlock


// @MRTZ_exclude  scan_UserRuleProperties
// @MRTZ_beginBlock

// String_imp         GlobalToken         = "";
 Buffer           = nullptr;// (char*)GlobalToken.c_str();
 String_imp  GlobalToken      = XMLNODE_GET_SUBCHILD_TEXT(configuration, (string("Process/") + process + "/GlobalToken").c_str(),      &Buffer);
 delete[](Buffer);

// String_imp         GlobalNotPhrased    = "";
 Buffer           = nullptr;// (char*)GlobalNotPhrased.c_str();
 String_imp  GlobalNotPhrased = XMLNODE_GET_SUBCHILD_TEXT(configuration, (string("Process/") + process + "/GlobalNotPhrased").c_str(), &Buffer);
 delete[](Buffer);

// String_imp         GlobalHide          = "";
 Buffer           = nullptr;// (char*)GlobalHide.c_str();
 String_imp  GlobalHide       = XMLNODE_GET_SUBCHILD_TEXT(configuration, (string("Process/") + process + "/GlobalHide").c_str(),       &Buffer);
 delete[](Buffer);

// String_imp         GlobalSkipLevel     = "";
 Buffer           = nullptr;// (char*)GlobalSkipLevel.c_str();
 String_imp  GlobalSkipLevel  = XMLNODE_GET_SUBCHILD_TEXT(configuration, (string("Process/") + process + "/GlobalSkipLevel").c_str(),  &Buffer);
 delete[](Buffer);
// @MRTZ_endBlock


// @MRTZ_exclude scan_lineprocess_information
// @MRTZ_beginBlock
 int StartLine = stringToNumber(XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                       "Process/Line/StartLine",
                                                       "value",
                                                       numberToString(1).c_str()));

 int StartColumn = stringToNumber(XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                         "Process/Line/StartColumn",
                                                         "value",
                                                         numberToString(1).c_str()));

 String_imp Indent = XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                    "Process/Line/Indent",
                                                    "value",
                                                    Indent.c_str());

 String_imp Dedent = XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                    "Process/Line/Dedent",
                                                    "value",
                                                    Dedent.c_str());

 String_imp NewLine = XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                     "Process/Line/NewLine",
                                                     "value",
                                                     NewLine.c_str());

// @MRTZ_endBlock

 String_imp  CommentBegin = "//- ";
 CommentBegin = XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                               (string("Process/") + process + "/CommentBegin").c_str(),
                                               "value",
                                               CommentBegin.c_str());
 String_imp  CommentEnd  = "";
 CommentEnd = XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                             (string("Process/") + process + "/CommentEnd").c_str(),
                                             "value",
                                             CommentEnd.c_str());

// String_imp  GlobalMergeLevel = "";
 Buffer           = nullptr;// (char*)GlobalMergeLevel.c_str();
 String_imp   GlobalMergeLevel = XMLNODE_GET_SUBCHILD_TEXT(configuration,
                                             (string("Process/") + process + "/GlobalMergeLevel").c_str(),
                                             &Buffer);
 delete[](Buffer);

 String_imp  VariantID = "Variant";
 VariantID = XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                            (string("Process/") + process + "/GlobalMergeLevel").c_str(),
                                            "variantID",
                                            VariantID.c_str());

// @MRTZ_exclude  setup_the_process
// @MRTZ_beginBlock
  ReturnValue    = new Prcs_Trn_Directive(PositionOutput,
                                          false,
                                          ShowTextToParse,
                                          ParseTolerant,
                                          StartLine,
                                          StartColumn,
                                          Indent,
                                          Dedent,
                                          NewLine,
                                          CommentBegin,
                                          CommentEnd);


  ReturnValue->UserRulePropertyGlobal_set(Prcs_Transformation::URP_NOTPHRASED,
                                          GlobalNotPhrased);
  ReturnValue->UserRulePropertyGlobal_set(Prcs_Transformation::URP_TOKEN,
                                          GlobalToken);
  ReturnValue->UserRulePropertyGlobal_set(Prcs_Transformation::URP_HIDE,
                                          GlobalHide);
  ReturnValue->UserRulePropertyGlobal_set(Prcs_Transformation::URP_SKIPLEVEL,
                                          GlobalSkipLevel);

  ReturnValue->setMergeLevel(GlobalMergeLevel, VariantID);

  Detail = configuration.firstGet(XML_Node::Element(XML_Search::Value,(string("Process/") + process + "/Symbol").c_str()));
  if(Detail.valid() == true)// != nullptr)
  {
   XML_Node  SubDetail = Detail.firstGet(XML_Node::Element(XML_Search::Value,"Class"));
   while(SubDetail.valid() == true)// != nullptr)
   {
    String_imp SymbolClass = SubDetail.attributeGet("value");

    Buffer  = nullptr;
    String_imp Symbol =  SubDetail.textCollect(&Buffer);
    if(Buffer != nullptr)
      delete[](Buffer);

#if defined(DEBUG_OUTPUT)
    cout << endl;
    cout << "SymbolClass : |" << SymbolClass << "|" << endl;
    cout << "Symbol : |"      << Symbol      << "|" << endl;
    cout << endl;
#endif

    ReturnValue->UserSymbolMap_set(SymbolClass, Symbol);
    SubDetail = SubDetail.behindGet(XML_Node::Element(XML_Search::Value,"Class"));
   }
  }
// @MRTZ_endBlock

  String_imp  LogOutputFile = "";
  Detail = configuration.firstGet(XML_Node::Element(XML_Search::Value,"Process/Notation/OutputRule"));
  if(lowCaseString(Detail.attributeGet("value")) == String_imp("yes"))
  {
   LogOutputFile = replacePartString(Detail.attributeGet("folder"),
                                     usedPathSeparator,
                                     osPathSeparator) + "Directive.txt";
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
                           GrammarText.c_str(),
                           LogOutInfo,
                          (DebugLevel != 0),
                           LimitCallingTree,
                           LimitCallingNode,
                           LimitCallerTree,
                           LimitCallerNode);

#if defined(DEBUG_OUTPUT)
 cout << "source ready" << endl;
#endif

 return(ReturnValue);

}








/* @MRTZ_describe getUserVariant

*/
XML_Node  getUserVariant(XML_Node    directiveDefinition,
                         const char* variant)
{
 XML_Node   ReturnValue;

 XML_Node  Child = directiveDefinition.firstGet(XML_Node::Element(XML_Search::Value,"Variant"));
 while (Child.valid() == true)// != nullptr)
 {
  const char* Name  = Child.attributeGet("name");
  if(STRINGS_ARE_EQUAL(Name,variant))
  {
   ReturnValue = Child;
   break;
  }

  Child = Child.behindGet(XML_Node::Element(XML_Search::Value,"Variant"));
 }

 return(ReturnValue);
}






/*!
 main-function of the application

 @param [in] argc   number of values in the arg-array of the
                    application
 @param [in] argv   arg-array of the application

 @return EXIT_FAILURE == error occurred
 <br>    EXIT_SUCCESS == normal end off application without errors

 @htmlinclude main_cpp_F_main.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    07.12.2008   @I  Eckard Klotz @I First Implementation @I
 @I_______________________________________________________
    25.12.2009   @I  Eckard Klotz
 @I re-factoring for merging part xml-results
 @I added buffer for analysis-result and call of merge-method
 @I_______________________________________________________
    12.01.2010   @I  Eckard Klotz
 @I implementing new features
 @I configuration of saving part-results
 @I_______________________________________________________
    28.02.2010   @I  Eckard Klotz
 @I implementing new features
 @I define input as folder-content
  @I_______________________________________________________
    14.11.2011   @I  Eckard Klotz
 @I re-factoring to make main-file content smaller and better
    to maintain
 @I convert parts of the main-file into a methods of
    the class CoreFlow and use it in the main-function
 @I_______________________________________________________
    02.06.2013      @I  Eckard Klotz
 @I re-factoring
 @I use of replacement-mechanism for separators in path-strings
 @I_______________________________________________________
    19.02.2012   @I  Eckard Klotz
 @I re-factoring
 @I replaced called functions from main-files into calls of functions defined
    in library-file that contains common application-tools
 @I_______________________________________________________
    23.06.2013   @I  Eckard Klotz
 @I bug -> check of not changed source will not be done in every case
 @I check implemented for common variant of compiler-switch
    and re.merge of different variant results
 @I_______________________________________________________
    18.08.2013      @I  Eckard Klotz
 @I bug user-paths defined as empty-strings may result in
    invalid path-strings if relative path-definitions in other
    configurations don't contain a valid path-begin
 @I empty user-paths used as root of relative paths will be
    replaced by a point followed by a path-separator
 @I_______________________________________________________
    13.10.2013      @I  Eckard Klotz
 @I bug: xml-comments lead to crash
 @I xml-iterations will be done by using TixmlNode instead
    of TiXmlElement,
    as first action in the loop a macro checks if the
    current-element is a xml-comment and forces immediate
    the start of the next loop
 @I_______________________________________________________
    12.10.2014   @I  Eckard Klotz
 @I extending function to save source location in destination-file
 @I use of variables for relative and absolute folder-location
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

   @MRTZ_describe local_declarations

   @MRTZ_describe files_and_paths

   @MRTZ_describe define_configuration-file

   @MRTZ_describe load_configuration-file

   @MRTZ_describe define_resource-path

   @MRTZ_describe define_source-path

   @MRTZ_describe define_destination-path

   @MRTZ_describe init_process

   @MRTZ_describe do_process

   @MRTZ_describe shut_down_process

*/
{
//      cout<<__FILE__<<"|main|"<<"("<<__LINE__<<") enter"<<endl;
// @MRTZ_exclude local_declarations
// @MRTZ_beginBlock
 String_imp DrctAttachment   = "_drct.xml";
 String_imp CommonAttachment = ".xml";
// @MRTZ_endBlock


#if defined(DEBUG_OUTPUT)
 printf(START_OUTPUT);
#endif

 clock_t Time    = clock()/CLOCKS_PER_SEC;
 clock_t SubTime = clock()/CLOCKS_PER_SEC;

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
 String_imp  ArgumentBuffer    = getAgument(argc, argv, ARG_CONFIGURATIONFILE);
 String_imp  ConfigurationFile = "";
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

 String_imp OsPathSeparator   = getConfigValue(XML_Node(),//nullptr,
                                               XML_PATH,
                                               argc, argv,
                                               ARG_OsPathSeparator,
                                               OsPathSeparator_DF);
 printf("load configuration-file \n");

// String_imp FileText = readTextFile(ConfigurationFile, UsedPathSeparator, OsPathSeparator); //content of source-file

 map<String_imp,String_imp> RootStrings;
 XML_DataModel              ConfigurationModel;
 XML_Node                   ConfigurationContent;
 XML_Node                   Configuration;
// cout << FileText << endl;
 if(ConfigurationModel.load(ConfigurationFile.c_str()) == true)
 {
  ConfigurationContent    = ConfigurationModel.rootNode().firstGet(XML_Node::Element(XML_Search::Value,"Configuration"));
  XML_Node  UserArguments = getUserDefinitions(ConfigurationContent,argc, argv);

  cout << endl << "added under configuration root called \""
               << ConfigurationContent.valueGet()
               << "\" the new sub-node : "
               << endl;
  UserArguments.xmlText();
  cout << endl << "this sub node contains all application arguments which start with \""
               << ARG_UA
               << "\""
               << endl;

  XML_Replace ReplaceDataReference;
  ConfigurationContent.associationNodeGet()->welcome(ReplaceDataReference(ConfigurationContent.associationContextGet()),IterateDownwards);
                                                                                                  // insertion of user-arguments into xml-configuration
#if defined(DEBUG_OUTPUT)
  cout << endl;
  ConfigurationContent.xmlText();
  cout << endl;
#endif

  Configuration = ConfigurationContent.firstGet(XML_Node::Element(XML_Search::Value,XML_PATH.c_str()));
#if defined(DEBUG_OUTPUT)
  cout << endl;
  Configuration.xmlText();
  cout << endl;
#endif

  UsedPathSeparator = getConfigValue(ConfigurationContent,
                                     XML_PATH,
                                     argc, argv,
                                     ARG_UsedPathSeparator,
                                     UsedPathSeparator_DF);

  OsPathSeparator   = getConfigValue(ConfigurationContent,
                                     XML_PATH,
                                     argc, argv,
                                     ARG_OsPathSeparator,
                                     OsPathSeparator_DF);


//  @MRTZ_exclude define_user-path
//  @MRTZ_beginBlock

  XML_Node   UserPathes = Configuration.firstGet(XML_Node::Element(XML_Search::Value,XML_USERPATH.c_str()));
  if(UserPathes.valid() == true)// != nullptr)
  {
   XML_Node  UserElement = UserPathes.firstGet(XML_Node::Element());
   while(UserElement.valid() == true)// != nullptr)
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
#if defined(DEBUG_OUTPUT)
 cout << "------------------------" << endl;
 ConfigurationContent.xmlText();
 cout << "------------------------" << endl;
#endif
 }
 else
 {
  printf("file \"%s\" not found !\n",ConfigurationFile.c_str());
  printf("or the file has xml-errors. \n");
  printf("abc2xml will terminate now. \n");

  return EXIT_FAILURE;
 }

//  cout << "################################################################################################################" << endl;
  XML_Replace ReplaceDataReference;
  ConfigurationContent.associationNodeGet()->welcome(ReplaceDataReference(ConfigurationContent.associationContextGet()),IterateDownwards);
//  cout << endl << "################################################################################################################" << endl;
//  ConfigurationContent.xmlText();
//  cout << endl << "################################################################################################################" << endl;

#if defined(DEBUG_BREAK)
   system("PAUSE");
#endif
//  @MRTZ_endBlock


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
 printf("OsPathSeparator[0] : %c \n",OsPathSeparator[0]);

 createFolder(DestinationPath, OsPathSeparator[0]); // create destination-folder
#if defined(DEBUG_BREAK)
   system("PAUSE");
#endif
//  @MRTZ_endBlock


// @MRTZ_endBlock
 cout << " basic initialisation (" << ((clock()/CLOCKS_PER_SEC)-SubTime) << " sec)" << endl;

// @MRTZ_exclude init_process
// @MRTZ_beginBlock
 cout << endl << endl
      << "-------------------------------------------------" << endl;

  SubTime      = clock()/CLOCKS_PER_SEC;

  CoreFlow* CoreSequence = new CoreFlow(ConfigurationContent,//ConfigurationContent->RootElement(),
                                        UsedPathSeparator,
                                        OsPathSeparator,
                                        RootStrings);

 cout << "core-flow process set-up (" << ((clock()/CLOCKS_PER_SEC)-SubTime) << " sec)" << endl;
 cout << "-------------------------------------------------" << endl;

 bool                SaveDirectivePart = true;
 Prcs_Trn_Directive* Directive_prcs    = nullptr;
 if(ConfigurationContent.firstGet(XML_Node::Element(XML_Search::Value,"Process/Directive")).valid() == true)//!= nullptr)
 {
  cout << "configure directive-parser" << endl ;
  SubTime = clock()/CLOCKS_PER_SEC;

  Directive_prcs = createDirectiveProcess(ConfigurationContent,
                                          "Directive",
                                          &SaveDirectivePart,
                                          &DrctAttachment,
                                          UsedPathSeparator,
                                          OsPathSeparator,
                                          RootStrings);
  Directive_prcs->setTestParser(CoreSequence);
  cout << "directive process set-up (" << ((clock()/CLOCKS_PER_SEC)-SubTime) << " sec)" << endl;
 }
 else
 {
  cout << "no directive-parser defined" << endl ;
 }

// @MRTZ_endBlock
 cout << "initialisation finished(" << ((clock()/CLOCKS_PER_SEC)-Time) << " sec)" << endl;

 XML_Node  DirectiveDefinition = ConfigurationContent.firstGet(XML_Node::Element(XML_Search::Value, "DirectiveDefinition"));
 XML_Node  Source              = ConfigurationContent.firstGet(XML_Node::Element(XML_Search::Value, "Source"));

 if(Source.valid() == true)// != nullptr)
 {
#if defined(DEBUG_OUTPUT)
  cout << endl;
  Source->xmlText();//Print(stdout,1);
  cout << endl;
#endif
  TiPa_DataModel DataModel;

  Configuration = Source.firstGet(XML_Node::Element());
  while( Configuration.valid() == true)// != nullptr)
  {
   const char* Text = Configuration.attributeGet("value",nullptr);

   if(  (Text!=nullptr)
      &&(UsedPathSeparator != OsPathSeparator)
     ) //do it only if it has to be done
    Configuration.attributeSet("value",replacePartString(Text, UsedPathSeparator, OsPathSeparator).c_str());

// @MRTZ_ifElseChain
   if(STRINGS_ARE_EQUAL(Configuration.valueGet(),"FileName"))
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

     if(UsedPathSeparator != OsPathSeparator) //do it only if it has to be done
      SourceName = replacePartString(SourceName,UsedPathSeparator,OsPathSeparator);

     String_imp FileText = readTextFile(SourceName,UsedPathSeparator,OsPathSeparator); //content of source-file
     cout << endl << "SourceName: " << SourceName << endl;

     if(FileText != "")
     {
      DataModel.init();
      String_imp RelativePath = SourceName.substr(0,SourceName.find_last_of(OsPathSeparator));
      String_imp AbsolutePath = getAbsolutePath(SourceName,OsPathSeparator);

      while(SourceName.find("\\")<SourceName.size())
      {
       SourceName = SourceName.replace(0,SourceName.find("\\")+1,"");
      }
      while(SourceName.find("/")<SourceName.size())
      {
       SourceName = SourceName.replace(0,SourceName.find("/")+1,"");
      }
      String_imp SourceID   = SourceName;
                 SourceName = replacePartString(SourceName,".","_");
#if defined(DEBUG_OUTPUT)
      cout << endl << "Save as: "    << SourceName << endl;
#endif
      FileText   = FileText + String_imp("\n");
#if defined(DEBUG_OUTPUT)
      cout << endl << "FileText: "    << FileText << endl;
#endif
     if(  (Configuration.firstGet(XML_Node::Element(XML_Search::Value, "Common")).valid() == false)//  == nullptr)
        &&(Configuration.firstGet(XML_Node::Element(XML_Search::Value, "Special")).valid() == false)// == nullptr)
        )
      {
       CoreSequence->analyse(Configuration,
                             DestinationPath,
                             SourceID,
                             RelativePath,
                             AbsolutePath);
      }
      else if(Directive_prcs != nullptr)
      {
       Time = clock()/CLOCKS_PER_SEC;

       cout << "  processing directives (";
       TiPa_DataModel DirectiveTree;
       DirectiveTree.init();
       Directive_prcs ->analyse(&FileText, &DirectiveTree);
       if((SaveDirectivePart == true)/* && (DirectiveDoc!= nullptr)*/)
        CoreSequence->storeContext(&DirectiveTree,
                                   Directive_prcs->getSymbols("Keyword"),
                                   Directive_prcs->getSymbols("KeyChr"),
                                  (DestinationPath + SourceName + DrctAttachment).c_str());

       cout << ((clock()/CLOCKS_PER_SEC)-Time) << " sec)" << endl;
       bool      DirectiveOK = false;
       XML_Node  Node        = Configuration.firstGet(XML_Node::Element(XML_Search::Value, "Common"));

       KEEP_VALIDE_CODE_TP KeepValideCode = KVC_ALLWAYS;
       const char*         Name           = Node.attributeGet("name");
       if(  (Node.valid() == true)// != nullptr)
          &&(  (lowCaseString(Configuration.attributeGet("doNotSkip"))            == "yes")
             ||(CoreSequence->checkNewSource(DestinationPath,
                                             Configuration.attributeGet("value")) == true)
            )
         )
       {
        XML_Node    Variant = getUserVariant(DirectiveDefinition,Name);

// @MRTZ_ifElseChain
        if     (   lowCaseString(Node.attributeGet("keepValideCode"))
                == String_imp("allways"))
         KeepValideCode = KVC_ALLWAYS;
        else if(   lowCaseString(Node.attributeGet("keepValideCode","implicit"))
                == String_imp("never"))
         KeepValideCode = KVC_NEVER;
        else
         KeepValideCode = KVC_IMPLICIT;

        Time = clock()/CLOCKS_PER_SEC;
        cout << "  evaluating variant Common (";
        Directive_prcs->configureConstants(Variant);
      /*DirectiveOK =*/ Directive_prcs->analyze_SwitchedText(KeepValideCode);

        if((SaveDirectivePart == true))
         CoreSequence->storeContext(&DirectiveTree,
                                    Directive_prcs->getSymbols("Keyword"),
                                    Directive_prcs->getSymbols("KeyChr"),
                                   (DestinationPath + SourceName + DrctAttachment).c_str());

        cout << ((clock()/CLOCKS_PER_SEC)-Time) << " sec)" << endl;

        Time = clock()/CLOCKS_PER_SEC;
        cout << "  assembling variant Common (";
        String_imp FileText_Variant =  Directive_prcs->reassembleSource();
        cout << ((clock()/CLOCKS_PER_SEC)-Time) << " sec)" << endl;
#if defined(DEBUG_OUTPUT)
        cout << "---------------------------------------------------------------------------------" << endl;
        cout <<  FileText_Variant << endl;
#endif

        DirectiveOK = CoreSequence->doSequence(&DataModel,
                                               &FileText_Variant,
                                                DestinationPath,
                                                SourceName,
                                                CommonAttachment,
                                                SourceID,
                                                RelativePath,
                                                AbsolutePath);
        if(DirectiveOK == true)
        {
         cout << "passed to common merge : " << SourceName << endl;
        }
        else
        {
         cout << "failed to common merge : " << SourceName << endl;
        }
       }
       else
       {
        cout << endl <<"Variant(" << Name<< ") of Source: " << SourceName
             << "\n -> skipped since source has not changed or variant is not valid" << endl;
       }

       if(DirectiveOK == false)
       {
        Node = Configuration.firstGet(XML_Node::Element(XML_Search::Value, "Special"));
        if(   (Node.valid()            == true)//             != nullptr)
           && (Node.firstGet().valid() == true)// != nullptr)
           && (Node.lastGet().valid()  == true)//  != nullptr)
          )
        {
         bool RemergeVariants = true;
         if(lowCaseString(Node.attributeGet("remerge", "yes"))      == String_imp("no"))
          RemergeVariants = false;

         bool KeepVariants = true;
         if(lowCaseString(Node.attributeGet("keepVariants", "yes")) == String_imp("no"))
          KeepVariants = false;

         Node = Node.firstGet(XML_Node::Element());
         while(Node.valid() == true)// != nullptr)
         {
          if(STRINGS_ARE_EQUAL(Node.valueGet(), "UseVariant"))//variant with defined preprocessor constants defined
          {
                     Name    = Node.attributeGet( "name");
           XML_Node  Variant = getUserVariant(DirectiveDefinition,Name);

// @MRTZ_ifElseChain
           if     (   lowCaseString(Node.attributeGet( "keepValideCode"))
                   == String_imp("implicit"))
            KeepValideCode = KVC_IMPLICIT;
           else if(   lowCaseString(Node.attributeGet( "keepValideCode","allways"))
                   == String_imp("never"))
            KeepValideCode = KVC_NEVER;
           else
            KeepValideCode = KVC_ALLWAYS;

           if(  (Variant.valid() == true)// != nullptr)
              &&(  (lowCaseString(Configuration.attributeGet("doNotSkip"))            == "yes")
                 ||(CoreSequence->checkNewSource(DestinationPath,
                                                 Configuration.attributeGet("value")) == true)
                )
              )
           {
#if defined(DEBUG_OUTPUT)
            cout << "Variant: " << Name << endl;
            Variant.xmlText();
            cout << endl;
#endif
            Time = clock()/CLOCKS_PER_SEC;
            cout << "  evaluate variant "<< Name << " (";
            Directive_prcs->configureConstants(Variant);

            Directive_prcs   -> analyze_SwitchedText(KeepValideCode);

            if(SaveDirectivePart == true)
             CoreSequence->storeContext(&DirectiveTree,
                                        Directive_prcs->getSymbols("Keyword"),
                                        Directive_prcs->getSymbols("KeyChr"),
                                       (DestinationPath + SourceName + DrctAttachment).c_str());

            cout << ((clock()/CLOCKS_PER_SEC)-Time) << " sec)" << endl;

            Time = clock()/CLOCKS_PER_SEC;
            cout << "  assemble variant "<< Name << " (";
            String_imp FileText_Variant =  Directive_prcs->reassembleSource();
            cout << ((clock()/CLOCKS_PER_SEC)-Time) << " sec)" << endl;
#if defined(DEBUG_OUTPUT)
            cout <<  FileText_Variant << endl;
#endif

            DirectiveOK = CoreSequence->doSequence(&DataModel,
                                                   &FileText_Variant,
                                                    DestinationPath,
                                                    SourceName + Name,
                                                    CommonAttachment,
                                                    SourceID,
                                                    RelativePath,
                                                    AbsolutePath);

            if(DirectiveOK == true)
            {
             cout << "passed to sepcial merge : " << SourceName << endl;
            }
            else
            {
             cout << "failed to special merge : " << SourceName << endl;
            }

           }
           else
           {
            cout << endl <<"Variant(" << Name<< ") of Source: " << SourceName
                 << "\n -> skiped since souce has not changed or variant is not valid" << endl;
           }
          }
          else //  no variant definition
          {
            // no variant to process
          }
          if(  (RemergeVariants==true)
             &&(  (lowCaseString(Configuration.attributeGet("doNotSkip"))            == "yes")
                ||(CoreSequence->checkNewSource(DestinationPath,
                                                Configuration.attributeGet("value")) == true)
               )
            )
           Directive_prcs->remerge((DestinationPath + SourceName        + CommonAttachment).c_str(),
                                   (DestinationPath + SourceName + Name + CommonAttachment).c_str(),
                                    Name                                                            );
          if(KeepVariants == false)
           remove((DestinationPath + SourceName + Name + CommonAttachment).c_str());

          Node = Node.behindGet(XML_Node::Element());
         }
        }
        else
        {
         cout << "no valid special variants defined for :" << SourceName << endl;
           Directive_prcs->analyze_SwitchedText(KeepValideCode);
        }
       }
      }
     }
// @MRTZ_endBlock

   }
   else if(STRINGS_ARE_EQUAL(Configuration.valueGet(), "FolderName"))
   {
    searchFiles(Configuration,
                CommonAttachment, //RootStrings,
                UsedPathSeparator,
                OsPathSeparator);
#if defined(DEBUG_OUTPUT)
    cout << "----FolderName----" << endl;
    cout << Source.valueGet() << endl;
    Source->xmlText();
    cout << "----FolderName----" << endl;
#endif
   }
   else
   {
   }
   Configuration = Configuration.behindGet(XML_Node::Element());
  }

  cout << endl << "all files parsed." << endl << endl;
  XML_Node  Node = Source.firstGet();
  while(Node.valid() == true)// != nullptr)
  {
   XML_Node  NodeToEvaluate = Node;
   Node = Node.behindGet();
   if(STRINGS_ARE_NOT_EQUAL(NodeToEvaluate.valueGet(),"FileName") )
   {
    Source.nodeCut(NodeToEvaluate);
#if defined(DEBUG_OUTPUT)
    cout << endl << NodeToEvaluate.valueGet() << endl;
#endif //DEBUG_OUTPUT
   }
  }
  cout << "\ndirect configuration for analysed files:\n";
  Source.xmlText();

  ConfigurationModel.save("AnalysedSources.xml",Source);
 }

// @MRTZ_exclude shut_down_process
// @MRTZ_beginBlock

 delete Directive_prcs;
 delete CoreSequence;

// @MRTZ_endBlock


 return EXIT_SUCCESS;
}
