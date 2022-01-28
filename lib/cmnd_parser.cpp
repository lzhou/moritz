/*!

 @file
 @brief  definition of a collection of snippet-commands to parse text

 This file contains special snippet-commands to parse tag-identifiers,
 attribute-values or the content of xml text-elements to transfer
 it into a new detailed xml-tree

 Copyright (C) 2008-2020 by Eckard Klotz.

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
    01.08.2013     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    01.08.2013...  @I Eckard Klotz
 @I Changes are documented in the comment of the changed element
 @TabEnd

*/



#include "cmnd_parser.h"
#include "app_tool.h"
#include "Spirit185_Xml.h"




#ifndef DOXYGEN
//namespace CL_COMMAND {
//namespace CL_CMND_PARSER {
#endif //DOXYGEN


String_imp                 Cmnd_Parser::UsedPathSeparator = "";
String_imp                 Cmnd_Parser::OsPathSeparator   = "";
map<String_imp,String_imp> Cmnd_Parser::RootStrings;
String_imp                 Cmnd_Parser::NotationCfg       = "";
Prcs_Trn_Source*           Cmnd_Parser::Parser            = nullptr;




/* @MRTZ_describe Cmnd_Parser

*/
Cmnd_Parser::Cmnd_Parser(void)
{



}





/* @MRTZ_describe ~Cmnd_Parser

*/
Cmnd_Parser::~Cmnd_Parser(void)
{
}



/* @MRTZ_describe setParser

*/
void Cmnd_Parser::setParser(XML_Node          configuration,
                            const String_imp& grammar)
{
 if(Parser !=nullptr)
 {
  delete Parser;
 }
 Parser = _createSourceProcess(configuration, grammar);
}




/* @MRTZ_describe useParser

*/
void Cmnd_Parser::useParser(const String_imp& text,
                            const String_imp& rule,
                            XML_Node*         result)
{
//cout<<__FILE__<<"|Cmnd_Parser::useParser|"<<"("<<__LINE__<<") enter"<<endl;
 if(Parser != nullptr)
 {
  TiPa_DataModel CodeTree;
  CodeTree.focus_Set("Code");

  String_imp Text = text;
  Parser->analyse(&Text, &CodeTree, rule);

  Spirit185_Xml Converter;
                Converter.contextModel_set(result->associationContextGet());
                Converter.setSpcialTag(Parser->getSymbols("Keyword"),
                                       Parser->getSymbols("KeyChr")
                                      );
  CodeTree.focus_Fellow()->welcome(Converter(Spirit185_Xml::Content2XML,result),IterateDownwards);
  if(  (result->valid()            == true)// != nullptr)
     &&(result->firstGet().valid() == true)// != nullptr)
    )
  {
   result->valueSet("Content");
   result->firstGet().valueSet(rule.c_str());
  }
 }
 else
 {
  cout << "no valid parser defined with rule \""
       << rule
       << "\" for : \n \""
       << text
       <<"\" \n " << endl;

 }
//cout<<__FILE__<<"|Cmnd_Parser::useParser|"<<"("<<__LINE__<<") leave"<<endl;
}









/* @MRTZ_describe setFolderRoots

*/
 void Cmnd_Parser::setFolderRoots(const String_imp&                 usedPathSeparator,
                                  const String_imp&                 osPathSeparator,
                                  const map<String_imp,String_imp>& rootStrings)
{
  UsedPathSeparator = usedPathSeparator;
  OsPathSeparator   = osPathSeparator;
  RootStrings       = rootStrings;
}




/* @MRTZ_describe _createSourceProcess

   @MRTZ_describe scan_grammar

   @MRTZ_describe scan_diverse_values

   @MRTZ_describe scan_UserRuleProperties

   @MRTZ_describe scan_lineprocess_information

   @MRTZ_describe setup_the_process

*/
Prcs_Trn_Source* Cmnd_Parser::_createSourceProcess(XML_Node          configuration,
                                                   const String_imp& grammar)
{
// cout<<__FILE__<<"|Cmnd_Parser::_createSourceProcess|"<<"("<<__LINE__<<") enter"<<endl;
 Prcs_Trn_Source* ReturnValue = nullptr;

 bool NormlzKwrdsOfSource        = false;
 if(lowCaseString(XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                 "Parser/NormalizeKeywordsOfSource",
                                                 "value",
                                                 "")) == String_imp("yes"))
 {
  NormlzKwrdsOfSource = true;
 }

 bool ShowTextToParse            = false;
 if(lowCaseString(XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                 "Parser/ShowTextToParse",
                                                 "value",
                                                 "")) == String_imp("yes"))
 {
  ShowTextToParse = true;
 }

 bool ParseTolerant              = false;
 if(lowCaseString(XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                             "Parser/ParseTolerant",
                                             "value",
                                             "")) == String_imp("yes"))
 {
  ParseTolerant = true;
 }

 String_imp Grammar = grammar;
 char*      Buffer  = nullptr;
 Grammar = Grammar +  XMLNODE_GET_SUBCHILD_TEXT(configuration,"Parser/Grammar", &Buffer);
 if(Buffer != nullptr)
   delete[](Buffer);


 int DebugLevel = stringToNumber(XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                                "Parser/DebugLevel",
                                                                "value",
                                                                 numberToString(0).c_str()));
 String_imp PaserLogFile = "ParserSnippetLog";
            PaserLogFile = XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                          "Parser/DebugLevel",
                                                          "file",
                                                          PaserLogFile.c_str());

 String_imp Root = XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                  "Parser/DebugLevel",
                                                  "root",
                                                  "");
 Root = RootStrings[Root];
 if(  (Root                        != "")
    &&(Root.rfind(OsPathSeparator) <  Root.size()-1)
   )
  Root = Root + OsPathSeparator;

 if(UsedPathSeparator != OsPathSeparator) //do it only if it has to be done
  PaserLogFile = replacePartString(Root + PaserLogFile,
                                   UsedPathSeparator,
                                   OsPathSeparator);

 int PositionOutput = stringToNumber(XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                                    "Parser/PositionOutput",
                                                                    "value",
                                                                    "2"));


// @MRTZ_exclude  scan_UserRuleProperties
// @MRTZ_beginBlock
// String_imp         GlobalToken         = "";
 Buffer           = nullptr;// (char*)GlobalToken.c_str();
 String_imp  GlobalToken      = XMLNODE_GET_SUBCHILD_TEXT(configuration, "Parser/GlobalToken",      &Buffer);
 delete[](Buffer);

// String_imp         GlobalNotPhrased    = "";
 Buffer           = nullptr;// (char*)GlobalNotPhrased.c_str();
 String_imp  GlobalNotPhrased = XMLNODE_GET_SUBCHILD_TEXT(configuration, "Parser/GlobalNotPhrased", &Buffer);
 delete[](Buffer);

// String_imp         GlobalHide          = "";
 Buffer           = nullptr;// (char*)GlobalHide.c_str();
 String_imp  GlobalHide       = XMLNODE_GET_SUBCHILD_TEXT(configuration, "Parser/GlobalHide",       &Buffer);
 delete[](Buffer);

// String_imp         GlobalSkipLevel     = "";
 Buffer           = nullptr;// (char*)GlobalSkipLevel.c_str();
 String_imp  GlobalSkipLevel  = XMLNODE_GET_SUBCHILD_TEXT(configuration, "Parser/GlobalSkipLevel",  &Buffer);
 delete[](Buffer);
// @MRTZ_endBlock

// @MRTZ_exclude scan_lineprocess_information
// @MRTZ_beginBlock


 int StartLine = stringToNumber(XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                               "Parser/StartLine",
                                                               "value",
                                                               "1"));

 int StartColumn = stringToNumber(XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                                 "Parser/StartColumn",
                                                                 "value",
                                                                 "1"));

 String_imp Indent = XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                    "Parser/Indent",
                                                    "value",
                                                    Indent.c_str());

 String_imp Dedent = XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                    "Parser/Dedent",
                                                    "value",
                                                    Dedent.c_str());

 String_imp NewLine = XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                     "Parser/NewLine",
                                                     "value",
                                                     NewLine.c_str());

// @MRTZ_endBlock

// @MRTZ_exclude  setup_the_process
// @MRTZ_beginBlock
  ReturnValue    = new Prcs_Trn_Source(PositionOutput,
                                       NormlzKwrdsOfSource,
                                       ShowTextToParse,
                                       ParseTolerant,
                                       StartLine,
                                       StartColumn,
                                       Indent,
                                       Dedent,
                                       NewLine);

  ReturnValue->UserRulePropertyGlobal_set(Prcs_Transformation::URP_NOTPHRASED,
                                          GlobalNotPhrased);
  ReturnValue->UserRulePropertyGlobal_set(Prcs_Transformation::URP_TOKEN,
                                          GlobalToken);
  ReturnValue->UserRulePropertyGlobal_set(Prcs_Transformation::URP_HIDE,
                                          GlobalHide);
  ReturnValue->UserRulePropertyGlobal_set(Prcs_Transformation::URP_SKIPLEVEL,
                                          GlobalSkipLevel);

  XML_Node Detail = configuration.firstGet(XML_Node::Element(XML_Search::Value,"Parser/Symbol"));
  if(Detail.valid() == true)
  {
   XML_Node SubDetail = Detail.firstGet(XML_Node::Element(XML_Search::Value,"Class"));
   while(SubDetail.valid() == true)
   {
    String_imp SymbolClass = SubDetail.attributeGet("value");

    /*char* */ Buffer  = nullptr;
    String_imp Symbol =  SubDetail.textCollect(&Buffer);

    if(Buffer != nullptr)
      delete[](Buffer);

#if defined(DEBUG_OUTPUT)
    cout << endl;
    cout << "SymbolClass : " << SymbolClass << endl;
    cout << "Symbol : "      << Symbol      << endl;
    cout << endl;
#endif

    ReturnValue->UserSymbolMap_set(SymbolClass, Symbol);
    SubDetail = SubDetail.behindGet(XML_Node::Element(XML_Search::Value,"Class"));
   }
  }
// @MRTZ_endBlock


 String_imp  LogOutputFile       = "";
 Detail = configuration.firstGet(XML_Node::Element(XML_Search::Value,"Process/Notation/OutputRule"));
 if(lowCaseString(Detail.attributeGet("value")) == String_imp("yes")) // rules should be outputted
 {
  LogOutputFile = replacePartString(Detail.attributeGet("folder"),
                                    UsedPathSeparator,
                                    OsPathSeparator)+"Source.txt";
  createFolder(LogOutputFile, OsPathSeparator[0]); // create destination-folder
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

  ReturnValue->grammar_init(grammar.c_str(),
                            "pass","skip","line",
                            GlobalNotPhrased.c_str(),
                            "CommandGrammar",
                            LogOutInfo,
                           (DebugLevel != 0),
                            LimitCallingTree,
                            LimitCallingNode,
                            LimitCallerTree,
                            LimitCallerNode);
// cout<<__FILE__<<"|Cmnd_Parser::_createSourceProcess|"<<"("<<__LINE__<<") leave"<<endl;
 return(ReturnValue);
}





#ifndef DOXYGEN
//};
//};// using namespace CL_COMMAND ;
#endif //DOXYGEN





