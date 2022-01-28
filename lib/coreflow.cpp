/*!

 @file
 @brief    encapsulate the main process-sequence for all user-languages

 This file contains the definition of a class to encapsulate the work of
 the base-process to evaluate comments, line-changes and the source as well
 as the process to merge their results


 Copyright (C) 2008-2020 by Eckard Klotz.

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
    14.11.2011     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    14.11.2011...  @I Eckard Klotz
 @I Changes are documented in the comment of the changed element
 @TabEnd

*/

#include "coreflow.h"





#include <fstream>
#include <sys/stat.h>
#include <ctime>


#include "Spirit185_Store.h"
#include "Spirit185_Xml.h"




#ifndef DOXYGEN
 //namespace CL_COREFLOW {
#endif //DOXYGEN


/* @MRTZ_describe CoreFlow

*/
CoreFlow::CoreFlow(XML_Node                    configuration,
                   String_imp&                 usedPathSeparator,
                   String_imp&                 osPathSeparator,
                   map<String_imp,String_imp>& rootStrings)
{

 Att.UsedPathSeparator = usedPathSeparator;
 Att.OsPathSeparator   = osPathSeparator;
 Att.RootStrings       = rootStrings;

 Att.CntxtAttachment   = "_cntx_.xml";
 Att.CmntAttachment    = "_cmnt_.xml";
 Att.LineAttachment    = "_line_.xml";
 Att.CodeAttachment    = "_code_.xml";

 Att.SaveContextPart   = true;
 Att.SaveCommentPart   = true;
 Att.SaveLinePart      = true;
 Att.SaveSourcePart    = true;

 clock_t  Time         = 0;


// cout << "configure context-parser" << endl ;
// Time = clock()/CLOCKS_PER_SEC;
// Att.Context_prcs = _createContextProcess(configuration,
//                                          "Context",
//                                          &(Att.SaveContextPart),
//                                          &(Att.CntxtAttachment));
//
// cout << "context process set-up (" << ((clock()/CLOCKS_PER_SEC)-Time) << " sec)" << endl;
// cout << "-------------------------------------------------" << endl;




 XML_Node UseConfiguration = configuration.firstGet(XML_Node::Element(XML_Search::Value,"Process/Merge/UseComment"));
 if(lowCaseString(UseConfiguration.attributeGet("value")) == String_imp("no"))
 {
  cout <<  "skip configuration of context-parser" << endl ;
  Att.Context_prcs = nullptr;
  cout << "-------------------------------------------------" << endl;
  cout <<  "skip configuration of comment-parser" << endl ;
  Att.Comment_prcs = nullptr;
 }
 else
 {
  cout << "configure context-parser" << endl ;
  Time = clock()/CLOCKS_PER_SEC;
  Att.Context_prcs = _createContextProcess(configuration,
                                           "Context",
                                           &(Att.SaveContextPart),
                                           &(Att.CntxtAttachment));
  cout << "context process set-up (" << ((clock()/CLOCKS_PER_SEC)-Time) << " sec)" << endl;

  cout << "-------------------------------------------------" << endl;

  cout <<  "configure comment-parser" << endl ;
  Time = clock()/CLOCKS_PER_SEC;
  Att.Comment_prcs = _createCommentProcess(configuration,
                                           &(Att.SaveCommentPart),
                                           &(Att.CmntAttachment));

  cout << "comment process set-up (" << ((clock()/CLOCKS_PER_SEC)-Time) << " sec)" << endl;
 }

 cout << "-------------------------------------------------" << endl;

 UseConfiguration = configuration.firstGet(XML_Node::Element(XML_Search::Value,"Process/Merge/UseLine"));
 if(lowCaseString(UseConfiguration.attributeGet("value")) == String_imp("no"))
 {
  cout <<  "skip configuration of line-parser" << endl ;
  Att.Line_prcs = nullptr;
 }
 else
 {
  cout << "configure line-parser" << endl ;

  Time = clock()/CLOCKS_PER_SEC;
  Att.Line_prcs = _createLineProcess(configuration,
                                     &(Att.SaveLinePart),
                                     &(Att.LineAttachment));

 cout << "line process set-up (" << ((clock()/CLOCKS_PER_SEC)-Time) << " sec)" << endl;
 }
 cout << "-------------------------------------------------"  << endl;


// UseConfiguration     = configuration.firstGet(XML_Node::Element(XML_Search::Value,"Process/Merge/UseCommand"));
// if(lowCaseString(UseConfiguration.attributeGet("value")) == String_imp("no"))
// {
//  cout <<  "skip configuration of source-parser" << endl ;
//  Att.Source_prcs = nullptr;
// }
// else
// {
// }
 cout << "configure source-parser" << endl ;

 Time = clock()/CLOCKS_PER_SEC;
 Att.Source_prcs = _createSourceProcess(configuration,
                                        "Source",
                                        &(Att.SaveSourcePart),
                                        &(Att.CodeAttachment));

 cout << "source process set-up (" << ((clock()/CLOCKS_PER_SEC)-Time) << " sec)" << endl;

 cout << "-------------------------------------------------"  << endl;

 cout << "configure merge-process" << endl ;
 Time = clock()/CLOCKS_PER_SEC;
 Att.Merge_prcs = _createMergeProcess(configuration);

 cout << "merge process set-up (" << ((clock()/CLOCKS_PER_SEC)-Time) << " sec)" << endl;
 cout << "-------------------------------------------------" << endl;

}



/* @MRTZ_describe ~CoreFlow

*/
CoreFlow::~CoreFlow()
{
 delete Att.Context_prcs;
 delete Att.Comment_prcs;
 delete Att.Line_prcs;
 delete Att.Source_prcs;
 delete Att.Merge_prcs;

}






/* @MRTZ_describe analyse

*/
void CoreFlow::analyse(      XML_Node    configuration,
                       const String_imp& destinationPath,
                       const String_imp& sourceID,
                       const String_imp& sourceRelativePath,
                       const String_imp& sourceAbsolutePath,
                       const String_imp& variant)
{
 String_imp DoNotSkip  = configuration.attributeGet("doNotSkip");
 String_imp SourceName = configuration.attributeGet("value");

 if(Att.UsedPathSeparator != Att.OsPathSeparator) //do it only if it has to be done
  SourceName = replacePartString(SourceName,Att.UsedPathSeparator,Att.OsPathSeparator);

 String_imp FileText   = "";       //content of source-file
 if(  (lowCaseString(DoNotSkip)                           == "yes")
    ||(checkNewSource(destinationPath,SourceName+variant) == true )
   )
 {
  FileText = readTextFile(SourceName, Att.UsedPathSeparator, Att.OsPathSeparator);
  cout << endl << "SourceName: " << SourceName << endl;
 }
 else
 {
  FileText = "";
  cout << endl << "SourceName: " << SourceName
       << "\n -> skiped since souce has not changed " << endl;
 }

 if(FileText != "")
 {
  cout << endl << "Save as: "    << SourceName << endl;
  while(SourceName.find("\\")<SourceName.size())
  {
   SourceName = SourceName.replace(0,SourceName.find("\\")+1,"");
  }
  while(SourceName.find("/")<SourceName.size())
  {
   SourceName = SourceName.replace(0,SourceName.find("/")+1,"");
  }
  SourceName = replacePartString(SourceName,".","_");
  SourceName = replacePartString(SourceName,".","_");

  TiPa_DataModel DataModel;
  bool ProcessOK = doSequence(&DataModel,
                              &FileText,
                               destinationPath,
                               SourceName+variant,
                               ".xml",
                               sourceID,
                               sourceRelativePath,
                               sourceAbsolutePath);

  if(ProcessOK == true)
  {
   cout << "passed to parse or merge : " << SourceName << endl;
  }
  else
  {
   cout << "failed to parse or merge : " << SourceName << endl;
  }
 }
}




/* @MRTZ_describe context2xml

*/
XML_DataModel* CoreFlow::context2xml(TiPa_DataModel* context,
                                     set<String_imp>* keyWord,
                                     set<String_imp>* keyChar)
{
 XML_DataModel* ReturnValue = new XML_DataModel();

 Spirit185_Xml Converter;
               Converter.contextModel_set(ReturnValue);
               Converter.setSpcialTag(keyWord,keyChar);
 XML_Node Root = ReturnValue->rootNode();
 context->focus_Fellow()->welcome(Converter(Spirit185_Xml::Content2XML,&Root),IterateDownwards);

 return(ReturnValue);
}





bool CoreFlow::storeContext(TiPa_DataModel*  context,
                            set<String_imp>* keyWord,
                            set<String_imp>* keyChar,
                            const char*      destination)
{
 bool  ReturnValue = false;

 XML_DataModel* XML_Model = context2xml(context,
                                        keyWord,//Att.Source_prcs->getSymbols("Keyword"),
                                        keyChar //Att.Source_prcs->getSymbols("KeyChr")
                                       );

 char* ParsedText  = nullptr;    // xml-text
 XML_Model->rootNode().xmlText(&ParsedText);

 XML_Model->init(true);

 delete(XML_Model);


 if(  (destination != nullptr)
    &&(ParsedText  != nullptr)
   )
 {
  ofstream  File(destination,ios_base::binary|ios_base::out);

  if(File.good()) // file successfully opened
  {
   File << ParsedText;
   File.close();
   ReturnValue = true;
  }
 }

 delete[]ParsedText;

 return(ReturnValue);
}



/* @MRTZ_describe doSequence

*/
bool CoreFlow::doSequence(      TiPa_DataModel* dataModel,
                                String_imp*     sourceText,
                          const String_imp&     destinationPath,
                          const String_imp&     destinationName,
                          const String_imp&     destinationAttachment,
                          const String_imp&     sourceID,
                                String_imp      sourceRelativePath,
                                String_imp      sourceAbsolutePath)
{
 bool     ReturnValue = true;
 dataModel->init();

 clock_t  Time = clock()/CLOCKS_PER_SEC;
 if(Att.Context_prcs != nullptr)
 {
  cout << "  processing contexts (";
  dataModel->focus_Set("Context");
  Att.Context_prcs->analyse(sourceText, dataModel);
  if(Att.SaveContextPart == true)
    storeContext(dataModel,
                 Att.Context_prcs->getSymbols("Keyword"),
                 Att.Context_prcs->getSymbols("KeyChr"),
                 (destinationPath + destinationName + Att.CntxtAttachment).c_str());
  cout << ((clock()/CLOCKS_PER_SEC)-Time) << " sec)" << endl;
 }
 else
 {
  cout << " skip processing contexts !" << endl;
  // keep comment-content empty
 }


 String_imp CommentContent = "";
 if(Att.Comment_prcs != nullptr)
 {
  if(Att.Context_prcs != nullptr)
  {
   Time           = clock()/CLOCKS_PER_SEC;
   cout << "  get comment-context (";
   CommentContent = Att.Context_prcs->getContext("Comment", sourceText);
   cout << ((clock()/CLOCKS_PER_SEC)-Time) << " sec)" << endl;
  }
  else
  {
   cout << " use original source as comment-context " << endl;
   CommentContent = *sourceText;
  }

  Time = clock()/CLOCKS_PER_SEC;
  cout << "  processing comments (";
  dataModel->focus_Set("Comment");
  Att.Comment_prcs->analyse( &CommentContent, dataModel);
  if(Att.SaveCommentPart == true)
    storeContext(dataModel,
                 Att.Comment_prcs->getSymbols("Keyword"),
                 Att.Comment_prcs->getSymbols("KeyChr"),
                 (destinationPath + destinationName + Att.CmntAttachment).c_str());
  cout << ((clock()/CLOCKS_PER_SEC)-Time) << " sec)" << endl;
 }
 else
 {
  cout << " skip processing comments !" << endl;
  // keep comment-content empty
 }

 String_imp CodeContent = "";
 if(Att.Context_prcs != nullptr)
 {
  Time        = clock()/CLOCKS_PER_SEC;
  cout << "  get code-context (";
  CodeContent = Att.Context_prcs->getContext("Code", sourceText);
  cout << ((clock()/CLOCKS_PER_SEC)-Time) << " sec)" << endl;
 }
 else
 {
  cout << " use original source as code-context " << endl;
  CodeContent = *sourceText;
 }

 if(Att.Line_prcs != nullptr)
 {
  Time = clock()/CLOCKS_PER_SEC;
  cout << "  processing logical line-breaks (";
  dataModel->focus_Set("Line");
  Att.Line_prcs   ->analyse(&CodeContent, dataModel );
  if(Att.SaveLinePart == true)
    storeContext(dataModel,
                 Att.Line_prcs->getSymbols("Keyword"),
                 Att.Line_prcs->getSymbols("KeyChr"),
                 (destinationPath + destinationName + Att.LineAttachment).c_str());
  cout << ((clock()/CLOCKS_PER_SEC)-Time) << " sec)" << endl;
 }
 else
 {
  cout << " skip processing line-breaks !" << endl;
 }

// if(Att.Source_prcs != nullptr)
// {
// }
// else
// {
//  cout << " skip processing source-code !" << endl;
// }
  Time = clock()/CLOCKS_PER_SEC;
  cout << "  processing source-code (";
  dataModel->focus_Set("Code");
  Att.Source_prcs ->analyse(&CodeContent, dataModel);
  if(Att.SaveSourcePart == true)
    storeContext(dataModel,
                 Att.Source_prcs->getSymbols("Keyword"),
                 Att.Source_prcs->getSymbols("KeyChr"),
                 (destinationPath + destinationName + Att.CodeAttachment).c_str());
  cout << ((clock()/CLOCKS_PER_SEC)-Time) << " sec)" << endl;

 Time = clock()/CLOCKS_PER_SEC;
 cout << "  merge part-results (";
 Att.Merge_prcs  ->merge(dataModel, "Code", "Line", "Comment");

 TiPa_Concrete::DataAssociation* MergeDocContenet = dataModel->focus_Fellow();
 MergeDocContenet->data_get()->secondaryData_add("sourceFile", sourceID.c_str());

 sourceRelativePath = replacePartString(sourceRelativePath,"\\","/");
 sourceRelativePath = replacePartString(sourceRelativePath,"././","./");
 sourceRelativePath = replacePartString(sourceRelativePath,"./../","../");
 sourceRelativePath = replacePartString(sourceRelativePath,".././","../");
 MergeDocContenet->data_get()->secondaryData_add("relativeSourcePath",sourceRelativePath.c_str());

 sourceAbsolutePath = replacePartString(sourceAbsolutePath,"\\","/");
 MergeDocContenet->data_get()->secondaryData_add("absoluteSourcePath",sourceAbsolutePath.c_str());

 storeContext(dataModel,
              Att.Source_prcs->getSymbols("Keyword"),
              Att.Source_prcs->getSymbols("KeyChr"),
              (destinationPath + destinationName + destinationAttachment).c_str());

 cout << ((clock()/CLOCKS_PER_SEC)-Time) << " sec)" << endl;

 XML_DataModel* XML_Model = context2xml(dataModel,
                                        Att.Source_prcs->getSymbols("Keyword"),
                                        Att.Source_prcs->getSymbols("KeyChr")
                                        );

 delete(XML_Model);

 return(ReturnValue);
}




/* @MRTZ_describe _createContextProcess

   @MRTZ_describe scan_grammar

   @MRTZ_describe scan_context_values

   @MRTZ_describe scan_UserRuleProperties

   @MRTZ_describe scan_lineProcess_information

   @MRTZ_describe setup_the_process

*/
Prcs_Trn_Context* CoreFlow::_createContextProcess(      XML_Node    configuration,
                                                  const String_imp& process,
                                                        bool*       savePartResult,
                                                        String_imp* attachment)
{
 Prcs_Trn_Context*  ReturnValue = nullptr;
 XML_Node           Detail      = configuration.firstGet(XML_Node::Element(XML_Search::Value,(string("Process/") + process + "/SavePartResult").c_str()));


 if(lowCaseString(Detail.attributeGet("value")) == String_imp("no"))
 {
  (*savePartResult) = false;
 }

 String_imp Attachment = Detail.attributeGet("attachment");
 if(Attachment != "")
  (*attachment) = Attachment;


 bool ShowTextToParse = false;
 if(lowCaseString(XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                 (string("Process/") + process + "/ShowTextToParse").c_str(),
                                                 "value",
                                                 ""
                                                )) == String_imp("yes"))
 {
  ShowTextToParse = true;
 }

 bool ParseTolerant = false;
 if(lowCaseString(XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                             (string("Process/") + process + "/ParseTolerant").c_str(),
                                             "value",
                                             "")) == String_imp("yes"))
 {
  ParseTolerant = true;
 }

 int PositionOutput = stringToNumber(XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                                    (string("Process/") + process + "/PositionOutput").c_str(),
                                                                    "value",
                                                                    "2"));

// @MRTZ_exclude scan_grammar
// @MRTZ_beginBlock
 XML_Node  Node = configuration.firstGet(XML_Node::Element(XML_Search::Value,(string("Process/") + process + "/Grammar/File").c_str()));
 String_imp  Grammar     = "";
 String_imp  GrammarText = "";
 while(Node.valid() == true)
 {
  String_imp Text = Node.attributeGet("value");
  String_imp Root = Node.attributeGet("root");

  Root = Att.RootStrings[Root];
  if(  (Root                        != "")
     &&(Root.rfind(Att.OsPathSeparator) <  Root.size()-1)
    )
   Root = Root + Att.OsPathSeparator;

  if(Text != "")
  {
   Grammar = Grammar + readTextFile(Root + Text,
                                    Att.UsedPathSeparator,
                                    Att.OsPathSeparator);
   GrammarText = Root + Text;
  }
  else
  {
   GrammarText = "Context Process Grammar";
  }
  Node = Node.behindGet(XML_Node::Element(XML_Search::Value,"File"));
 }
 char* Buffer  = nullptr;
 Grammar = Grammar +  XMLNODE_GET_SUBCHILD_TEXT(configuration,(string("Process/") + process + "/Grammar").c_str(),&Buffer);
 if(Buffer != nullptr)
   delete[](Buffer);
// @MRTZ_endBlock

 String_imp PaserLogFile  = "ContextLog";
 int DebugLevel = stringToNumber(XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                                (string("Process/") + process + "/DebugLevel").c_str(),
                                                                "value",
                                                                numberToString(0).c_str()));

 PaserLogFile = XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                               (string("Process/") + process + "/DebugLevel").c_str(),
                                               "file",
                                               PaserLogFile.c_str());

 String_imp Root = XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                  (string("Process/") + process + "/DebugLevel").c_str(),
                                                  "root",
                                                  "");
 Root = Att.RootStrings[Root];
 if(  (Root                        != "")
    &&(Root.rfind(Att.OsPathSeparator) <  Root.size()-1)
   )
  Root = Root + Att.OsPathSeparator;

 if(Att.UsedPathSeparator != Att.OsPathSeparator)             // do it only if it has to be done
 {
  PaserLogFile = replacePartString(Root + PaserLogFile,
                                   Att.UsedPathSeparator,
                                   Att.OsPathSeparator);
  createFolder(PaserLogFile+ ".xml", Att.OsPathSeparator[0]); // create destination-folder
 }

// @MRTZ_exclude scan_context_values
// @MRTZ_beginBlock
 map<String_imp, Prcs_Trn_Context::_s_ContextType> ContextContainer;
 Detail = configuration.firstGet(XML_Node::Element(XML_Search::Value,(string("Process/") + process + "/Type").c_str()));
 if(Detail.valid() == true)
 {
  XML_Node  Context = Detail.firstGet(XML_Node::Element());
  while(Context.valid() == true)
  {
   String_imp Name      = Context.valueGet();
   bool       IsDefault = false;

   if(lowCaseString(Context.attributeGet("isDefault","no")) == String_imp("yes"))
   {
    IsDefault = true;
   }
   else
   {
    IsDefault = false;
   }

   String_imp ReplacementStr = Context.attributeGet("replacement");
   char       Replacement    = ' ';

   if(ReplacementStr != "")
   {
    Replacement = ReplacementStr.at(0);
   }
   else
   {
    Replacement = ' ';
   }

   Prcs_Trn_Context::_s_ContextType                  ContextType;
   Prcs_Trn_Context::_s_Sequence                     Sequence;
   XML_Node  SubDetail = Context.firstGet(XML_Node::Element(XML_Search::Value,"Sequence"));
   while(SubDetail.valid() == true)
   {
    Sequence.Name       = SubDetail.attributeGet("name");
    Sequence.StartToken = SubDetail.attributeGet("startToken");
    Sequence.EndToken   = SubDetail.attributeGet("endToken");
    ContextType.Sequence.push_back(Sequence);

    SubDetail = SubDetail.behindGet(XML_Node::Element());
   }

   ContextType.IsDefault    = IsDefault;
   ContextType.Replacement  = Replacement;
   ContextContainer[Name]   = ContextType;
   ContextType.Sequence.clear();
   Context = Context.behindGet(XML_Node::Element());
  }
 }
// @MRTZ_endBlock

// @MRTZ_exclude  scan_UserRuleProperties
// @MRTZ_beginBlock
// String_imp         GlobalToken         = " ";
 Buffer           = nullptr;// nullptr;//(char*)GlobalToken.c_str();
 String_imp  GlobalToken      = XMLNODE_GET_SUBCHILD_TEXT(configuration, (string("Process/") + process + "/GlobalToken").c_str(),      &Buffer);
 delete[](Buffer);

// String_imp         GlobalNotPhrased    = " ";
 Buffer           = nullptr;// nullptr;//(char*)GlobalNotPhrased.c_str();
 String_imp  GlobalNotPhrased = XMLNODE_GET_SUBCHILD_TEXT(configuration, (string("Process/") + process + "/GlobalNotPhrased").c_str(), &Buffer);
 delete[](Buffer);

// String_imp         GlobalHide          = " ";
 Buffer           = nullptr;// nullptr;//(char*)GlobalHide.c_str();
 String_imp  GlobalHide       = XMLNODE_GET_SUBCHILD_TEXT(configuration, (string("Process/") + process + "/GlobalHide").c_str(),       &Buffer);
 delete[](Buffer);

// String_imp         GlobalSkipLevel     = " ";
 Buffer           = nullptr;// nullptr;//(char*)GlobalSkipLevel.c_str();
 String_imp  GlobalSkipLevel  = XMLNODE_GET_SUBCHILD_TEXT(configuration, (string("Process/") + process + "/GlobalSkipLevel").c_str(),  &Buffer);
 delete[](Buffer);

// @MRTZ_endBlock

// @MRTZ_exclude scan_lineProcess_information
// @MRTZ_beginBlock

 int StartLine = stringToNumber(XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                       "Process/Line/StartLine",
                                                       "value",
                                                       numberToString(1).c_str()));

 int StartColumn = stringToNumber(XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                         "Process/Line/StartColumn",
                                                         "value",
                                                         numberToString(1).c_str()));

// @MRTZ_endBlock

// @MRTZ_exclude  setup_the_process
// @MRTZ_beginBlock
  ReturnValue    = new Prcs_Trn_Context(ContextContainer,
                                        PositionOutput,
                                        ShowTextToParse,
                                        ParseTolerant,
                                        StartLine,
                                        StartColumn);

  ReturnValue->UserRulePropertyGlobal_set(Prcs_Transformation::URP_NOTPHRASED,
                                          GlobalNotPhrased);
  ReturnValue->UserRulePropertyGlobal_set(Prcs_Transformation::URP_TOKEN,
                                          GlobalToken);
  ReturnValue->UserRulePropertyGlobal_set(Prcs_Transformation::URP_HIDE,
                                          GlobalHide);
  ReturnValue->UserRulePropertyGlobal_set(Prcs_Transformation::URP_SKIPLEVEL,
                                          GlobalSkipLevel);
// @MRTZ_endBlock

 String_imp  LogOutputFile     = "";
 Detail = configuration.firstGet(XML_Node::Element(XML_Search::Value,"Process/Notation/OutputRule"));
 if(lowCaseString(Detail.attributeGet("value")) == String_imp("yes"))
 {
  LogOutputFile = replacePartString(string(Detail.attributeGet("folder")),
                                      Att.UsedPathSeparator,
                                      Att.OsPathSeparator)+"Context.txt";
  createFolder(LogOutputFile, Att.OsPathSeparator[0]); // create destination-folder
 }
 else                                                  // rules should not be outputted
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

 return(ReturnValue);
}



/* @MRTZ_describe _createCommentProcess

   @MRTZ_describe scan_grammar

   @MRTZ_describe scan_diverse_values

   @MRTZ_describe scan_UserRuleProperties

   @MRTZ_describe setup_the_process

*/
Prcs_Trn_Comment* CoreFlow::_createCommentProcess(XML_Node    configuration,
                                                  bool*       savePartResult,
                                                  String_imp* attachment)
{
 Prcs_Trn_Comment* ReturnValue   = nullptr;

 if(lowCaseString(XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                 "Process/Comment/SavePartResult",
                                                 "value",
                                                 "")) == String_imp("no"))
 {
  (*savePartResult) = false;
 }
 String_imp Attachment = XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                        "Process/Comment/SavePartResult",
                                                        "attachment",
                                                        "");
 if(Attachment != "")
  (*attachment) = Attachment;

 bool ShowTextToParse            = false;
 if(lowCaseString(XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                 "Process/Comment/ShowTextToParse",
                                                 "value",
                                                 "")) == String_imp("yes"))
 {
  ShowTextToParse = true;
 }

 map<String_imp, Prcs_Trn_Comment::SpecialCommentToken > SpeclComntToken;
 XML_Node  Detail = configuration.firstGet(XML_Node::Element(XML_Search::Value,"Process/Comment/SpecialComment"));
 if(Detail.valid() == true)
 {
  XML_Node  SubDetail = Detail.firstGet(XML_Node::Element());
  while(SubDetail.valid() == true)
  {
   String_imp                             SpecialName = SubDetail.valueGet();
   String_imp                             StartsWith  = SubDetail.attributeGet("startsWith");
   String_imp                             EndsWith    = SubDetail.attributeGet("endsWith");
   Prcs_Trn_Comment::SpecialCommentToken  TokenPair;
   TokenPair.Start = StartsWith;
   TokenPair.End   = EndsWith;
   SpeclComntToken[SpecialName] = TokenPair;
   SubDetail = SubDetail.behindGet(XML_Node::Element());
  }
 }

// @MRTZ_exclude scan_grammar
// @MRTZ_beginBlock
 String_imp  Grammar     = "";
 String_imp  GrammarText = "";
 XML_Node  Node = configuration.firstGet(XML_Node::Element(XML_Search::Value,"Process/Comment/Grammar/File"));
 while(Node.valid() == true)
 {
   String_imp Text = Node.attributeGet("value");
   String_imp Root = Node.attributeGet( "root");
              Root = Att.RootStrings[Root];
   if(  (Root                        != "")
      &&(Root.rfind(Att.OsPathSeparator) <  Root.size()-1)
     )
    Root = Root + Att.OsPathSeparator;

   if(Text != "")
   {
    Grammar = Grammar + readTextFile(Root + Text,
                                     Att.UsedPathSeparator,
                                     Att.OsPathSeparator);
    GrammarText = Root + Text;
   }
   else
   {
    GrammarText = "Comment Process Grammar";
   }

  Node = Node.behindGet(XML_Node::Element(XML_Search::Value,"File"));
 }
 char* Buffer  = nullptr;
 Grammar = Grammar +  XMLNODE_GET_SUBCHILD_TEXT(configuration, "Process/Comment/Grammar", &Buffer);
 if(Buffer != nullptr)
   delete[](Buffer);

 if(Grammar == "")
 {
  Grammar = " fail = (anychar_p ^ '#'); \n\
              pass = ('#' >> *(anychar_p - eol_p) >> eol_p);";
 }
// @MRTZ_endBlock

// @MRTZ_exclude scan_diverse_values
// @MRTZ_beginBlock
 int DebugLevel = stringToNumber(XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                                "Process/Comment/DebugLevel",
                                                                "value",
                                                                 numberToString(0).c_str()));

 String_imp PaserLogFile = XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                          "Process/Comment/DebugLevel",
                                                          "file",
                                                          PaserLogFile.c_str());
 String_imp Root = XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                  "Process/Comment/DebugLevel",
                                                  "root",
                                                  "");
 Root = Att.RootStrings[Root];
 if(  (Root                        != "")
    &&(Root.rfind(Att.OsPathSeparator) <  Root.size()-1)
   )
  Root = Root + Att.OsPathSeparator;

 if(Att.UsedPathSeparator != Att.OsPathSeparator)              //do it only if it has to be done
 {
  PaserLogFile = replacePartString(Root + PaserLogFile,
                                   Att.UsedPathSeparator,
                                   Att.OsPathSeparator);
  createFolder(PaserLogFile+ ".xml", Att.OsPathSeparator[0]); // create destination-folder
 }

 int StartLine = stringToNumber(XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                               "Process/Comment/StartLine",
                                                               "value",
                                                               numberToString(1).c_str()));

 int StartColumn = stringToNumber(XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                                 "Process/Comment/StartColumn",
                                                                 "value",
                                                                 numberToString(1).c_str()));
// @MRTZ_endBlock

// @MRTZ_exclude  scan_UserRuleProperties
// @MRTZ_beginBlock


// String_imp         GlobalToken         = "";
 Buffer           = nullptr;// (char*)GlobalToken.c_str();
 String_imp  GlobalToken      = XMLNODE_GET_SUBCHILD_TEXT(configuration, "Process/Comment/GlobalToken",      &Buffer);
 delete[](Buffer);

// String_imp         GlobalNotPhrased    = "";
 Buffer           = nullptr;// (char*)GlobalNotPhrased.c_str();
 String_imp  GlobalNotPhrased = XMLNODE_GET_SUBCHILD_TEXT(configuration, "Process/Comment/GlobalNotPhrased", &Buffer);
 delete[](Buffer);

// String_imp         GlobalHide          = "";
 Buffer           = nullptr;// (char*)GlobalHide.c_str();
 String_imp  GlobalHide       = XMLNODE_GET_SUBCHILD_TEXT(configuration, "Process/Comment/GlobalHide",       &Buffer);
 delete[](Buffer);

// String_imp         GlobalSkipLevel     = "";
 Buffer           = nullptr;// (char*)GlobalSkipLevel.c_str();
 String_imp  GlobalSkipLevel  = XMLNODE_GET_SUBCHILD_TEXT(configuration, "Process/Comment/GlobalSkipLevel",  &Buffer);
 delete[](Buffer);




// @MRTZ_endBlock

// @MRTZ_exclude  setup_the_process
// @MRTZ_beginBlock
 ReturnValue = new Prcs_Trn_Comment(SpeclComntToken,
                                    StartLine, StartColumn,
                                    ShowTextToParse);


 ReturnValue->UserRulePropertyGlobal_set(Prcs_Transformation::URP_NOTPHRASED,
                                         GlobalNotPhrased);
 ReturnValue->UserRulePropertyGlobal_set(Prcs_Transformation::URP_TOKEN,
                                         GlobalToken);
 ReturnValue->UserRulePropertyGlobal_set(Prcs_Transformation::URP_HIDE,
                                         GlobalHide);
 ReturnValue->UserRulePropertyGlobal_set(Prcs_Transformation::URP_SKIPLEVEL,
                                         GlobalSkipLevel);
// @MRTZ_endBlock


 String_imp  LogOutputFile     = "";
 Detail = configuration.firstGet(XML_Node::Element(XML_Search::Value,"Process/Notation/OutputRule"));
 if(lowCaseString(Detail.attributeGet("value","")) == String_imp("yes"))
 {
  LogOutputFile = replacePartString(Detail.attributeGet("folder"),
                                    Att.UsedPathSeparator,
                                    Att.OsPathSeparator)+"Comment.txt";
  createFolder(LogOutputFile, Att.OsPathSeparator[0]); // create destination-folder
 }
 else                                                  // rules should not be outputted
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



 return(ReturnValue);

}





/* @MRTZ_describe _createLineProcess

   @MRTZ_describe scan_grammar

   @MRTZ_describe scan_diverse_values

   @MRTZ_describe scan_special_tokens

   @MRTZ_describe scan_UserRuleProperties

   @MRTZ_describe setup_the_process

*/
Prcs_Trn_Line* CoreFlow::_createLineProcess(XML_Node    configuration,
                                            bool*       savePartResult,
                                            String_imp* attachment)
{
 Prcs_Trn_Line* ReturnValue      = nullptr;

 XML_Node  Detail = configuration.firstGet(XML_Node::Element(XML_Search::Value,"Process/Line/SavePartResult"));
 if(lowCaseString(Detail.attributeGet("value")) == String_imp("no"))
 {
  (*savePartResult) = false;
 }

 String_imp Attachment = XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                        "Process/Line/SavePartResult",
                                                        "attachment",
                                                        "");
 if(Attachment != "")
  (*attachment) = Attachment;

 bool ShowTextToParse            = false;
 if(lowCaseString(XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                 "Process/Line/ShowTextToParse",
                                                 "value",
                                                 "")) == String_imp("yes"))
 {
  ShowTextToParse = true;
 }

// @MRTZ_exclude scan_grammar
// @MRTZ_beginBlock
 String_imp  Grammar             = "";
 String_imp  GrammarText         = "";
 XML_Node  Node = configuration.firstGet(XML_Node::Element(XML_Search::Value,"Process/Line/Grammar/File"));
 while(Node.valid() == true)// != nullptr)
 {
  String_imp Text = Node.attributeGet("value");
  String_imp Root = Node.attributeGet( "root");
             Root = Att.RootStrings[Root];
  if(  (Root                        != "")
     &&(Root.rfind(Att.OsPathSeparator) <  Root.size()-1)
    )
   Root = Root + Att.OsPathSeparator;


  if(Text != "")
  {
   Grammar = Grammar + readTextFile(Root + Text,
                                    Att.UsedPathSeparator,
                                    Att.OsPathSeparator);
   GrammarText = Root + Text;
  }
  else
  {
   GrammarText = "Line Process Grammar";
  }
  Node = Node.behindGet(XML_Node::Element(XML_Search::Value,"File"));
 }
 char* Buffer  = nullptr;
 Grammar = Grammar +  XMLNODE_GET_SUBCHILD_TEXT(configuration, "Process/Line/Grammar", &Buffer);
 if(Buffer != nullptr)
   delete[](Buffer);

 if(Grammar == "")
 {
  Grammar = "fail = (anychar_p - eol_p); \n\
             pass = (eol_p >> *blank_p);";
 }
// @MRTZ_endBlock

// @MRTZ_exclude scan_diverse_values
// @MRTZ_beginBlock
 int DebugLevel = stringToNumber(XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                            "Process/Line/DebugLevel",
                                                            "value",
                                                             numberToString(0).c_str()));

 String_imp PaserLogFile         = "LineLog";
 PaserLogFile = XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                               "Process/Line/DebugLevel",
                                               "file",
                                               PaserLogFile.c_str());
 String_imp Root = XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                  "Process/Line/DebugLevel",
                                                  "root",
                                                  "");
 Root = Att.RootStrings[Root];
 if(  (Root                        != "")
    &&(Root.rfind(Att.OsPathSeparator) <  Root.size()-1)
   )
  Root = Root + Att.OsPathSeparator;

 if(Att.UsedPathSeparator != Att.OsPathSeparator)             // do it only if it has to be done
 {
  PaserLogFile = replacePartString(Root + PaserLogFile,
                                   Att.UsedPathSeparator,
                                   Att.OsPathSeparator);
  createFolder(PaserLogFile+ ".xml", Att.OsPathSeparator[0]); // create destination-folder
 }

 int StartLine = stringToNumber(XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                           "Process/Line/StartLine",
                                                           "value",
                                                           numberToString(1).c_str()));

 int StartColumn = stringToNumber(XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                             "Process/Line/StartColumn",
                                                             "value",
                                                             numberToString(1).c_str()));

 int TabSize = stringToNumber(XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                         "Process/Line/TabSize",
                                                         "value",
                                                         numberToString(1).c_str()));
// @MRTZ_endBlock


// @MRTZ_exclude scan_special_tokens
// @MRTZ_beginBlock
 String_imp  Indent              = "";
 Indent = XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                         "Process/Line/Indent",
                                         "value",
                                         Indent.c_str());

 String_imp  Dedent              = "";
 Dedent = XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                         "Process/Line/Dedent",
                                         "value",
                                         Dedent.c_str());

 String_imp  NewLine             = "";
 NewLine = XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                          "Process/Line/NewLine",
                                          "value",
                                          NewLine.c_str());

 String_imp  EndMarker           = "";
 EndMarker = XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                            "Process/Line/EndMarker",
                                            "value",
                                            EndMarker.c_str());
// @MRTZ_endBlock


// @MRTZ_exclude  scan_UserRuleProperties
// @MRTZ_beginBlock
// String_imp         GlobalToken         = "";
 Buffer           = nullptr;// (char*)GlobalToken.c_str();
 String_imp  GlobalToken      = XMLNODE_GET_SUBCHILD_TEXT(configuration, "Process/Line/GlobalToken",      &Buffer);
 delete[](Buffer);

// String_imp         GlobalNotPhrased    = "";
 Buffer           = nullptr;// (char*)GlobalNotPhrased.c_str();
 String_imp  GlobalNotPhrased = XMLNODE_GET_SUBCHILD_TEXT(configuration, "Process/Line/GlobalNotPhrased", &Buffer);
 delete[](Buffer);

// String_imp         GlobalHide          = "";
 Buffer           = nullptr;// (char*)GlobalHide.c_str();
 String_imp  GlobalHide       = XMLNODE_GET_SUBCHILD_TEXT(configuration, "Process/Line/GlobalHide",       &Buffer);
 delete[](Buffer);

// String_imp         GlobalSkipLevel     = "";
 Buffer           = nullptr;// (char*)GlobalSkipLevel.c_str();
 String_imp  GlobalSkipLevel  = XMLNODE_GET_SUBCHILD_TEXT(configuration, "Process/Line/GlobalSkipLevel",  &Buffer);
 delete[](Buffer);
// @MRTZ_endBlock


// @MRTZ_exclude  setup_the_process
// @MRTZ_beginBlock
 ReturnValue = new Prcs_Trn_Line(StartLine,
                                  StartColumn,
                                  TabSize,
                                  Indent,
                                  Dedent,
                                  NewLine,
                                  EndMarker,
                                  ShowTextToParse);


 ReturnValue->UserRulePropertyGlobal_set(Prcs_Transformation::URP_NOTPHRASED,
                                         GlobalNotPhrased);
 ReturnValue->UserRulePropertyGlobal_set(Prcs_Transformation::URP_TOKEN,
                                         GlobalToken);
 ReturnValue->UserRulePropertyGlobal_set(Prcs_Transformation::URP_HIDE,
                                         GlobalHide);
 ReturnValue->UserRulePropertyGlobal_set(Prcs_Transformation::URP_SKIPLEVEL,
                                         GlobalSkipLevel);
// @MRTZ_endBlock

 String_imp LogOutputFile     = "";
 Detail = configuration.firstGet(XML_Node::Element(XML_Search::Value,"Process/Notation/OutputRule"));
 if(lowCaseString(Detail.attributeGet("value")) == String_imp("yes"))
 {
  LogOutputFile = replacePartString(Detail.attributeGet("folder"),
                                    Att.UsedPathSeparator,
                                    Att.OsPathSeparator)+"Line.txt";
  createFolder(LogOutputFile, Att.OsPathSeparator[0]); // create destination-folder
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
 return(ReturnValue);

}




/* @MRTZ_describe _createSourceProcess

   @MRTZ_describe scan_grammar

   @MRTZ_describe scan_diverse_values

   @MRTZ_describe scan_UserRuleProperties

   @MRTZ_describe scan_lineProcess_information

   @MRTZ_describe setup_the_process

*/
Prcs_Trn_Source* CoreFlow::_createSourceProcess(      XML_Node    configuration,
                                                const String_imp& process,
                                                      bool*       savePartResult,
                                                      String_imp* attachment)
{
 Prcs_Trn_Source* ReturnValue    = nullptr;

 XML_Node  Detail = configuration.firstGet(XML_Node::Element(XML_Search::Value,(string("Process/") + process + "/SavePartResult").c_str()));
 if(lowCaseString(Detail.attributeGet("value")) == String_imp("no"))
 {
  (*savePartResult) = false;
 }

 String_imp Attachment = XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                        (string("Process/") + process + "/SavePartResult").c_str(),
                                                        "attachment",
                                                        "");
 if(Attachment != "")
  (*attachment) = Attachment;

 bool NormlzKwrdsOfSource = false;
 if(lowCaseString(XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                 (string("Process/") + process + "/NormalizeKeywordsOfSource").c_str(),
                                                 "value",
                                                 "")) == String_imp("yes"))
 {
  NormlzKwrdsOfSource = true;
 }

 bool ShowTextToParse = false;
 if(lowCaseString(XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                 (string("Process/") + process + "/ShowTextToParse").c_str(),
                                                 "value",
                                                 "")) == String_imp("yes"))
 {
  ShowTextToParse = true;
 }

 bool ParseTolerant = false;
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
 while(Node.valid() == true)
 {
  String_imp Text = Node.attributeGet("value");
  String_imp Root = Node.attributeGet("root");
             Root = Att.RootStrings[Root];
  if(  (Root                            != "")
     &&(Root.rfind(Att.OsPathSeparator) <  Root.size()-1)
    )
   Root = Root + Att.OsPathSeparator;

  if(Text != "")
  {
   Grammar = Grammar + readTextFile(Root + Text,
                                    Att.UsedPathSeparator,
                                    Att.OsPathSeparator);
   GrammarText = Root + Text;
  }
  else
  {
   GrammarText = "Source Process Grammar";
  }
  Node = Node.behindGet(XML_Node::Element(XML_Search::Value,"File"));
 }

 char* Buffer  = nullptr;
 Grammar = Grammar +  XMLNODE_GET_SUBCHILD_TEXT(configuration, (string("Process/") + process + "/Grammar").c_str(), &Buffer);
 if(Buffer != nullptr)
   delete[](Buffer);
// @MRTZ_endBlock

 int DebugLevel = stringToNumber(XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                               (string("Process/") + process + "/DebugLevel").c_str(),
                                                               "value",
                                                               numberToString(0).c_str()));

 String_imp PaserLogFile = "SourceLog";
 PaserLogFile = XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                               (string("Process/") + process + "/DebugLevel").c_str(),
                                               "file",
                                               PaserLogFile.c_str());

 String_imp Root = XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                  (string("Process/") + process + "/DebugLevel").c_str(),
                                                  "root",
                                                  "");
 Root = Att.RootStrings[Root];
 if(  (Root                        != "")
    &&(Root.rfind(Att.OsPathSeparator) <  Root.size()-1)
   )
  Root = Root + Att.OsPathSeparator;

 if(Att.UsedPathSeparator != Att.OsPathSeparator)             // do it only if it has to be done
 {
  PaserLogFile = replacePartString(Root + PaserLogFile,
                                   Att.UsedPathSeparator,
                                   Att.OsPathSeparator);
  createFolder(PaserLogFile+ ".xml", Att.OsPathSeparator[0]); // create destination-folder
 }

// @MRTZ_exclude scan_diverse_values
// @MRTZ_beginBlock
 bool DontMerge = true;
 Detail = configuration.firstGet(XML_Node::Element(XML_Search::Value,"Process/Merge/UseComment"));
 if(lowCaseString(Detail.attributeGet("value")) == String_imp("yes"))
 {
  DontMerge = false;
 }
 Detail = configuration.firstGet(XML_Node::Element(XML_Search::Value,"Process/Merge/UseLine"));
 if(lowCaseString(Detail.attributeGet("value")) == String_imp("yes"))
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


// @MRTZ_exclude scan_lineProcess_information
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

 Detail = configuration.firstGet(XML_Node::Element(XML_Search::Value,(string("Process/") + process + "/Symbol").c_str()));
 if(Detail.valid() == true)
 {
  XML_Node  SubDetail = Detail.firstGet(XML_Node::Element(XML_Search::Value,"Class"));
  while(SubDetail.valid() == true)
  {
   String_imp SymbolClass = SubDetail.attributeGet("value");

   Buffer  = nullptr;
   String_imp Symbol =  SubDetail.textCollect(&Buffer);

   if(Buffer != nullptr)
     delete[](Buffer);

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
                                      Att.UsedPathSeparator,
                                      Att.OsPathSeparator)+"Source.txt";
  createFolder(LogOutputFile, Att.OsPathSeparator[0]); // create destination-folder
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

 return(ReturnValue);
}






/* @MRTZ_describe _createMergeProcess

   @MRTZ_describe scan_comment

   @MRTZ_describe scan_line

   @MRTZ_describe scan_command

   @MRTZ_describe setup_the_process

*/
Prcs_Trn_Merge* CoreFlow::_createMergeProcess(XML_Node   configuration)
{
 Prcs_Trn_Merge* ReturnValue      = nullptr;


// @MRTZ_exclude scan_comment
// @MRTZ_beginBlock
 XML_Node  Detail     = configuration.firstGet(XML_Node::Element(XML_Search::Value,"Process/Merge/UseComment"));
 bool      UseComment = true;
 if(lowCaseString(Detail.attributeGet("value")) == String_imp("no"))
 {
  UseComment = false;
 }

 int LimitToImportBeforeComment = -1;
 String_imp Text = XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                  "Process/Merge/UseComment/LimitToImportBefore",
                                                  "value",
                                                  numberToString(LimitToImportBeforeComment).c_str());

 if(lowCaseString(Text) == "max")
  LimitToImportBeforeComment = INT_MAX;
 else
  LimitToImportBeforeComment = stringToNumber(Text);


 int LimitToImportBehindComment = -1;
 Text = XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                       "Process/Merge/UseComment/LimitToImportBehind",
                                       "value",
                                       numberToString(LimitToImportBehindComment).c_str());
 if(lowCaseString(Text) == "max")
  LimitToImportBehindComment = INT_MAX;
 else
  LimitToImportBehindComment = stringToNumber(Text);

 String_imp ImportLevelComment = XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                                "Process/Merge/UseComment/Detail/ImportLevel",
                                                                "value",
                                                                "");
// @MRTZ_endBlock


// @MRTZ_exclude scan_line
// @MRTZ_beginBlock
      Detail  = configuration.firstGet(XML_Node::Element(XML_Search::Value,"Process/Merge/UseLine"));
 bool UseLine = true;
 if(lowCaseString(Detail.attributeGet("value")) == String_imp("no"))
 {
  UseLine = false;
 }

 int LimitToImportBeforeLine = -1;
 Text = XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                       "Process/Merge/UseLine/LimitToImportBefore",
                                       "value",
                                       numberToString(LimitToImportBeforeLine).c_str());
 if(lowCaseString(String_imp(Text)) == "max")
  LimitToImportBeforeLine = INT_MAX;
 else
  LimitToImportBeforeLine = stringToNumber(String_imp(Text));


 int LimitToImportBehindLine = -1;
 Text = XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                       "Process/Merge/UseLine/LimitToImportBehind",
                                       "value",
                                       numberToString(LimitToImportBehindLine).c_str());
 if(lowCaseString(String_imp(Text)) == "max")
  LimitToImportBehindLine = INT_MAX;
 else
  LimitToImportBehindLine = stringToNumber(String_imp(Text));


 String_imp ImportLevelLine = XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                                             "Process/Merge/UseLine/Detail/ImportLevel",
                                                             "value",
                                                             "");
// @MRTZ_endBlock


// @MRTZ_exclude scan_command
// @MRTZ_beginBlock
 Detail = configuration.firstGet(XML_Node::Element(XML_Search::Value,"Process/Merge/UseCommand"));
 bool UseCommand = true;
 if(lowCaseString(Detail.attributeGet("value")) == String_imp("no"))
 {
  UseCommand = false;
 }

  int LimitToImportBeforeCommand = -1;
  Text = XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                        "Process/Merge/UseCommand/LimitToImportBefore",
                                        "value",
                                        numberToString(LimitToImportBeforeCommand).c_str());
  if(lowCaseString(String_imp(Text)) == "max")
   LimitToImportBeforeCommand = INT_MAX;
  else
   LimitToImportBeforeCommand = stringToNumber(String_imp(Text));

  int LimitToImportBehindCommand = -1;
  Text = XMLNODE_GET_SUBCHILD_ATTRIBUTE(configuration,
                                        "Process/Merge/UseCommand/LimitToImportBehind",
                                        "value",
                                        numberToString(LimitToImportBehindCommand).c_str());
  if(lowCaseString(String_imp(Text)) == "max")
   LimitToImportBehindCommand = INT_MAX;
  else
   LimitToImportBehindCommand = stringToNumber(String_imp(Text));

  map <String_imp, String_imp>ImportLevelCommand;
  XML_Node  Node = configuration.firstGet(XML_Node::Element(XML_Search::Value,"Process/Merge/UseCommand/Detail"));
  while(Node.valid() == true)// != nullptr)
  {
   String_imp Command = Node.attributeGet("value");
   Detail = Node.firstGet(XML_Node::Element(XML_Search::Value,"ImportLevel"));
   ImportLevelCommand[Command] = Detail.attributeGet("value");
   Node = Node.behindGet(XML_Node::Element(XML_Search::Value,"Detail"));
  }
// @MRTZ_endBlock

// @MRTZ_exclude  setup_the_process
// @MRTZ_beginBlock
// @MRTZ_showSource
 ReturnValue = new Prcs_Trn_Merge(UseComment,
                                  LimitToImportBeforeComment,
                                  LimitToImportBehindComment,
                                  ImportLevelComment,
                                  UseLine,
                                  LimitToImportBeforeLine,
                                  LimitToImportBehindLine,
                                  ImportLevelLine,
                                  UseCommand,
                                  LimitToImportBeforeCommand,
                                  LimitToImportBehindCommand,
                                  ImportLevelCommand);
// @MRTZ_endBlock


 return(ReturnValue);
}








/* @MRTZ_describe checkNewSource

*/
bool CoreFlow::checkNewSource(const String_imp& destinationPath,
                              const String_imp& source)
{
 bool ReturnValue = true;

 String_imp   SourceName=source;
 while(SourceName.find("\\")<SourceName.size())
 {
  SourceName = SourceName.replace(0,SourceName.find("\\")+1,"");
 }
 while(SourceName.find("/")<SourceName.size())
 {
  SourceName = SourceName.replace(0,SourceName.find("/")+1,"");
 }
 SourceName = replacePartString(SourceName,".","_");

 list<String_imp>  DestinationList;
 if(Att.SaveCommentPart   == true)
  DestinationList.push_back(destinationPath + SourceName+ Att.CmntAttachment);
 if(Att.SaveLinePart      == true)
  DestinationList.push_back(destinationPath + SourceName + Att.LineAttachment);
 if(Att.SaveSourcePart    == true)
  DestinationList.push_back(destinationPath + SourceName+ Att.CodeAttachment);
 DestinationList.push_back(destinationPath + SourceName + ".xml");

 SourceName=source;
 fstream  SourceFile((char*)SourceName.c_str(),ios::binary|ios::in);
 if(SourceFile.good())   // source file successfully opened
 {
  struct stat SourceInfo;
  stat(SourceName.c_str(), &SourceInfo);
  SourceFile.close();

  list<String_imp>::iterator Destination = DestinationList.begin();
  while(Destination != DestinationList.end())
  {
   fstream  DestinationFile((char*)Destination->c_str(),ios::binary|ios::in);
   if(DestinationFile.good()) //destination-file found
   {
    struct stat  DestinationInfo;
    stat(Destination->c_str(), &DestinationInfo);
    DestinationFile.close();

    if(DestinationInfo.st_mtime > SourceInfo.st_mtime)
                   // destination-file is older than source-file
     ReturnValue = false;

   }
   else            // destination-file does not exist
   {
    ReturnValue = true;
    break;         // level check since creation of destination is necessary
   }

   ++Destination;
  }

 }

 return(ReturnValue);
}


/* @MRTZ_describe checkTextToParse

*/
bool CoreFlow::checkTextToParse(String_imp text)
{
 TiPa_DataModel DataModel;
                DataModel.focus_Set("Context");

 bool    ReturnValue =  true;
 if(Att.Context_prcs != nullptr)
 {
  TiPa_Concrete::DataFellow* ContextTree = Att.Context_prcs->analyse(&text, &DataModel);
                                    text = Att.Context_prcs->getContext("Code",&text);
  if(ContextTree    == nullptr)
   ReturnValue = false;
 }

 if(  (ReturnValue   != false  )
    &&(Att.Line_prcs != nullptr)
   )
 {
  DataModel.focus_Set("Line");
  TiPa_Concrete::DataFellow* LineTree    = Att.Line_prcs   ->analyse(&text, &DataModel);
  if(LineTree    == nullptr)
   ReturnValue = false;
 }

 if(  (ReturnValue     != false  )
    &&(Att.Source_prcs != nullptr)
   )
 {
  DataModel.focus_Set("Code");
  TiPa_Concrete::DataFellow* CodeTree    = Att.Source_prcs ->analyse(&text, &DataModel);
  if(CodeTree    == nullptr)
   ReturnValue = false;
 }

// if(    (ContextTree != nullptr)
//      &&(LineTree    != nullptr)
//      &&(CodeTree    != nullptr)
//    )
// {
//  ReturnValue = true;
// }
// else
// {
//  ReturnValue = false;
// }

 return(ReturnValue);
}

#ifndef DOXYGEN
//};
#endif //DOXYGEN


