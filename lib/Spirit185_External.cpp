/*!

 @file
 @brief definitions of an concrete grammar-class for scanning a2x-scripts
        written in the notation of the old spirit 1.8.5

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
    08.03.2015     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    08.03.2015...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/

//#define DEBUG_OUTPUT_LOG
#include "LogOutput.h"


#include "Spirit185_External.h"
#include "Spirit185_Internal.h"
#include "TiPa_Search.h"

#include "Spirit185_Property.h"



#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#include <limits.h>



#include <fstream>



using namespace std;

#ifndef DOXYGEN
//namespace TXTDIASM {
//namespace TDA_Grammar {
////namespace CL_TDA_GRMCONCRETE {
//namespace CL_SPIRIT185 {
#endif //DOXYGEN






/* @MRTZ_describe Spirit185_External
 no initialization of nearly all attributes since already done in declaration
*/
 Spirit185_External::Spirit185_External(TiPa_Concrete::DataModel* contextModel,
                                        bool                      debugMode)
                    :TDA_GrmConcrete(contextModel, debugMode),
                     Mbr(),
                     Log()
 {
//  Mbr.GrammarTextIdentifier = nullptr;
//  Mbr.LocalParserID         = LocalParserID_Min;

//  Log.Indent     = 0;
//  Log.IndentOffset.clear();
//  Log.File       = nullptr;                          // initialize as not existing
//  Log.Path       = nullptr;                          // initialize as not existing
//  Log.Name       = nullptr;                          // initialize as not existing
//  Log.Attachment = nullptr;                          // initialize as not existing
//  Log.Path_end   = nullptr;                          // initialize as not existing
//  Log.Name_end   = nullptr;                          // initialize as not existing

  Mbr.DebugReaction.setProperty(&TDA_GrmConcrete::Att.Property);
 }






/* @MRTZ_describe Spirit185_External

*/
 Spirit185_External::Spirit185_External(TiPa_Concrete::DataAssociation* association,
                                        const char*                     rootRule,
                                        const char*                     skipRule,
                                        const char*                     lineRule,
                                        const char*                     listOfNonPhrased,
                                        const char*                     grammarTextIdentifier,
                                        TiPa_Concrete::DataModel*       contextModel,
                                        bool                            debugMode)
                    :TDA_GrmConcrete(contextModel, debugMode),
                     Mbr(),
                     Log()
 {
//  Mbr.LocalParserID = LocalParserID_Min;
//  Log.Indent        = 0;
//  Log.IndentOffset.clear();
//  Log.File       = nullptr;                          // initialize as not existing
//  Log.Path       = nullptr;                          // initialize as not existing
//  Log.Name       = nullptr;                          // initialize as not existing
//  Log.Attachment = nullptr;                          // initialize as not existing
//  Log.Path_end   = nullptr;                          // initialize as not existing
//  Log.Name_end   = nullptr;                          // initialize as not existing

  init(association,
       rootRule,
       skipRule,
       lineRule,
       listOfNonPhrased,
       grammarTextIdentifier,
       debugMode);

  Mbr.DebugReaction.setProperty(&TDA_GrmConcrete::Att.Property);

 }







/* @MRTZ_describe ~Spirit185_External

*/
 Spirit185_External::~Spirit185_External(void)
 {
  LOG_OUTPUT(LOG_OFF,"~Spirit185_External start");

  if(Mbr.GrammarTextIdentifier != nullptr)
    delete(Mbr.GrammarTextIdentifier);

  Log.IndentOffset.clear();
  Log.Text.clear();

  if(Log.File != nullptr)
   delete[](Log.File);
  Log.File       = nullptr;                          // initialize as not existing

  if(Log.Path != nullptr)
   delete[](Log.Path);                               // delete old file-path
  Log.Path       = nullptr;                          // initialize as not existing

  if(Log.Name != nullptr)
   delete[](Log.Name);                               // delete old file-name
  Log.Name       = nullptr;                          // initialize as not existing

  if(Log.Attachment != nullptr)
   delete[](Log.Attachment);                         // delete old file-name
  Log.Attachment = nullptr;                          // initialize as not existing


  LOG_OUTPUT(LOG_OFF,"~Spirit185_External end");
 }

/* @MRTZ_describe init

*/
void Spirit185_External::init(TiPa_Concrete::DataAssociation* association,
                              const char*                     rootRule,
                              const char*                     skipRule,
                              const char*                     lineRule,
                              const char*                     listOfNonPhrased,
                              const char*                     grammarTextIdentifier,
                              bool                            debugMode,
                              int                             limitCallingTree,
                              int                             limitCallingNode,
                              int                             limitCallerTree,
                              int                             limitCallerNode
                             )
 {
  TDA_GrmConcrete::Att.DebugMode = debugMode;
  Mbr.LocalParserID              = LocalParserID_Min;
  Log.Indent                     = 0;
  Log.IndentOffset.clear();


  char*  CopyOfName = new char[strlen(grammarTextIdentifier)+1];
  strcpy(CopyOfName,grammarTextIdentifier);        // create an independent copy
  CopyOfName[strlen(grammarTextIdentifier)] = 0;   // ensure termination
  Mbr.GrammarTextIdentifier = CopyOfName;          // store as attribute

//  TiPa_Data* Data = association->data_get();

  TiPa_Concrete::DataAssociation* KeyContent = collectKeyData(association);
  //reduce parser-tree to avoid methods to process bridge nodes which contain no relevant information

  if(Log.File != nullptr)
  {
   Spirit185_Property  RuleProperty(KeyContent,/*nullptr,*/
                                    listOfNonPhrased,',',
                                    Log.File,
                                    limitCallingTree, limitCallingNode,
                                    limitCallerTree, limitCallerNode
                                    );   // used to create extended log-output
  }


  set<string>         NotPhrased;
  string2set(&NotPhrased,listOfNonPhrased,',');


  LOG_OUTPUT(LOG_OFF, string("List of not phrased : ") << listOfNonPhrased);
  LOG_OUTPUT(LOG_OFF, string("Size of not phrased : ") << NotPhrased.size());

  CREATE_PARSER(TiPa_Rule, Skip, Spirit185_Internal::Skip_rid, "text content to ignore");
  TDA_GrmConcrete::Att.SkipParser = Skip;

  unsigned int Rule_ID = 0;

  TiPa_Search  Search;
  TiPa_Concrete::DataAssociation* RootElement = KeyContent->contractorFirst_get(Search(TiPa_Search::UserName,"RootContent/RootElement"));
  while(RootElement!=nullptr)
  {

   TiPa_Concrete::DataAssociation* Contractor = RootElement->contractorFirst_get();
   if(Contractor != nullptr)
   {
    TiPa_Data* Data = Contractor->data_get();

    LOG_OUTPUT(LOG_OFF, string("Spirit185_External::init Rule(") << Rule_ID << "): " << Data->getContent());

    if(Data->UserID == Spirit185_Internal::Rule_rid)
    {
     create_Rule(Contractor, &NotPhrased, Rule_ID);
     ++ Rule_ID;
    }
    else if(Data->UserID == Spirit185_Internal::Comment_rid)
    {
     LOG_OUTPUT(LOG_OFF, string("comment content : ") << Data->getContent());
    }
    else
    {
     LOG_OUTPUT(LOG_OFF, "root element is empty");
    }

    RootElement = RootElement->fellowBehind_get();
   }
   else
   {
    RootElement = nullptr;
    LOG_OUTPUT(LOG_OFF, "root element not found");
   }
  }

  TDA_GrmConcrete::Att.MainParser = defineRootRule(rootRule, Mbr.LocalParserID);
  TDA_GrmConcrete::Att.SkipParser = defineSkipRule(skipRule, Mbr.LocalParserID);
  TDA_GrmConcrete::Att.LineParser = defineLineRule(lineRule, Mbr.LocalParserID);

  defineReservedRule(/*TDA_GrmConcrete::Att.SkipParser,*/ Rule_ID);

  while(! NotPhrased.empty())
  {
   NotPhrased.erase(*NotPhrased.rbegin());
  }

  if(Log.File != nullptr)
  {
   ofstream  File(Log.File);
   if(File.good()) // file successfully opened
   {
    File << Log.Text.str();
    File.close();
   }
   else
   {
    File.clear();
    printf("file \"%s\" not found \n",Log.File);
   };

  }
 }




/* @MRTZ_describe Spirit185_External_parse

*/
 const char* Spirit185_External::parse(const char* begin,
                                       const char* end,
                                       const char* rule)
{

  pre_parse( begin, end);                       // call the pre parser process to collect common attributes of the give text

  return(TDA_GrmConcrete::parse(begin, end, rule));   // call the main parsing process and return its result
}



#define LOG_DOCXYGEN_CUTOUT_LINE(content)      logRawResult("/*! [Snipet__",-1);    \
                                               logRawResult(Log.Name,-1);           \
                                               logRawResult("__",-1);               \
                                               logRawResult(content,-1);            \
                                               logRawResult("__] */",-1,NEWLOGLINE)



/* @MRTZ_describe Spirit185_External_create_Rule

*/
void Spirit185_External::create_Rule(TiPa_Concrete::DataAssociation* association,
                                     //bool                phrased,
                                     set<string>*          notPhrased,
                                     int                 id)
{
 bool        Phrased  = true;
 TiPa_Search Search;

 TiPa_Concrete::DataAssociation* RuleContent = association->contractorFirst_get(Search(TiPa_Search::UserName,"RuleContent"));
 if(RuleContent != nullptr)
 {
  TiPa_Concrete::DataAssociation* RulePart    = RuleContent->contractorFirst_get();
  TiPa_Rule*          Parser                  = nullptr;

  bool        FoundID  = false;
  const char* RuleName = nullptr;
  while(RulePart != nullptr)
  {
   TiPa_Data*  Data    = RulePart->data_get();
   const char* Content = Data->getContent();

   LOG_OUTPUT(LOG_OFF, string("rule content : ")<<Content);

   if(  (FoundID      == false)
      &&(Data->UserID == Spirit185_Internal::Identifier_rid)
     )
   {
    if(notPhrased->find(Content)!= notPhrased->end())
    {
     Phrased = TiPa_Concrete::NOTPHRASED;
     LOG_OUTPUT(LOG_OFF, string("NotPhrased : ") + Content);
    }
    else
    {
     Phrased = TiPa_Concrete::PHRASED;
     LOG_OUTPUT(LOG_OFF, string("Phrased : ") + Content);
    }

    LOG_OUTPUT(LOG_OFF, string("Identifier content : ")<<Content);
    RuleName = Content;
    LOG_DOCXYGEN_CUTOUT_LINE(RuleName);

    logRawResult(Content);
    logRawResult(" = ",strlen(Content) + 3);

    Parser = dynamic_cast<TiPa_Rule*>(createParser(TiPa_Rule::id_Class(),
                                                   Content,
                                                   Content,
                                                   id,
                                                   "a rule",
                                                   Mbr.GrammarTextIdentifier,
                                                   atoi(Data->lineGet()))
                                      );
    if(TDA_GrmConcrete::Att.DebugMode == true)
      Parser->reactionHit_set(&Mbr.DebugReaction);

    if(Parser->contractor_ParserCounter() != 0)
    {
     cout << "recreation of existing rule : " << Content << endl;
     if( TDA_GrmConcrete::Att.Property.find(Parser)!= TDA_GrmConcrete::Att.Property.end())
      cout << "  order number (existing/new): " << TDA_GrmConcrete::Att.Property[Parser].User_ID
                                         << "/" << id << endl;
     if( TDA_GrmConcrete::Att.ParserDebugData.find(Parser)!= TDA_GrmConcrete::Att.ParserDebugData.end())
      cout << "  source line  (existing/new): " << TDA_GrmConcrete::Att.ParserDebugData[Parser].LineNumber
                                         << "/" << Data->lineGet() << endl;
    }
    FoundID = true;
   }
   else if(Parser != nullptr)
   {
    LOG_OUTPUT(LOG_OFF, "call other parser creation in create_Rule ");
    TiPa_Concrete* ParserContent = call_ParserCreation(Data->UserID,RulePart,Phrased);
    logRawResult(" ;",-1,NEWLOGLINE);

    LOG_DOCXYGEN_CUTOUT_LINE(RuleName);

    logRawResult(EMPTYLOG,0,NEWLOGLINE);

    Parser->init(ParserContent);
   }
   else
   {
    LOG_OUTPUT(LOG_ON, string("failure in rule definition : ")<<Content);
   }
   RulePart = RulePart->fellowBehind_get();
  }
 }
 else
 {
   LOG_OUTPUT(LOG_OFF, "rule content not valid valid ");
 }

 if(Phrased == true)
 {
  LOG_OUTPUT(LOG_OFF, "phrased Rule");
 }
 else
 {
  LOG_OUTPUT(LOG_OFF, "not phrased Rule");
 }



}





/* @MRTZ_describe get_Rule

*/
TiPa_Rule* Spirit185_External::get_Rule(TiPa_Concrete::DataAssociation* association/*,
                                        bool                            phrased*/)
{
 TiPa_Data*  Data    = association->data_get();
 const char* Content = Data->getContent();
 LOG_OUTPUT(LOG_OFF, string("identifier : ")<<Content);
 logRawResult(Content);

 TiPa_Rule* Returnvalue = dynamic_cast<TiPa_Rule*>(createParser(TiPa_Rule::id_Class(),
                                                                Content,
                                                                Content,
                                                                -1,
                                                                "a rule",
                                                                Mbr.GrammarTextIdentifier,
                                                                -1)
                                                   );
 return(Returnvalue);
}





/* @MRTZ_describe Spirit185_External_create_ParserPrimitive

*/
TiPa_Concrete* Spirit185_External::create_ParserPrimitive(TiPa_Concrete::DataAssociation* association,
                                                           bool                phrased)
{
 TiPa_Concrete*      ReturnValue   = nullptr;

 TiPa_Concrete::DataAssociation* CharacterPart = association->contractorFirst_get();
 while(CharacterPart != nullptr )
 {
  TiPa_Data*  Data    = CharacterPart->data_get();

  LOG_OUTPUT(LOG_OFF, string("primitive content : ")<<Data->getContent());
  logRawResult(Data->getContent());

  switch(Data->UserID)
  {
   case Spirit185_Internal::PrmAlnum_rid:                 // primitive parser: alpha numeric characters
   {
    LOG_OUTPUT(LOG_OFF, "creation of alpha numeric characters ");
    CREATE_USER_PARSER(TiPa_Character, PrmAlnum, "__Prm_Alnum__", Mbr.LocalParserID++,
                       "primitive : alpha numeric characters",
                       Mbr.GrammarTextIdentifier,atoi(Data->lineGet()));
    PrmAlnum->init(TiPa_Character::Alnum);            // alpha numeric characters

    ReturnValue = PrmAlnum;
   }break;
   case Spirit185_Internal::PrmAlpha_rid:                 // primitive parser: alphabetic characters
   {
    LOG_OUTPUT(LOG_OFF, "creation of alphabetic characters ");
    CREATE_USER_PARSER(TiPa_Character, PrmAlpha, "__Prm_Alpha__", Mbr.LocalParserID++,
                       "primitive : alphabetic characters",
                       Mbr.GrammarTextIdentifier,atoi(Data->lineGet()));
    PrmAlpha->init(TiPa_Character::Alpha);            // alphabetic characters

    ReturnValue = PrmAlpha;
   }break;
   case Spirit185_Internal::PrmAnychar_rid:               // primitive parser: any character
   {
    LOG_OUTPUT(LOG_OFF, "creation of any character ");
    CREATE_USER_PARSER(TiPa_Character, PrmAnychar, "__Prm_Anychar__", Mbr.LocalParserID++,
                       "primitive : any character",
                       Mbr.GrammarTextIdentifier,atoi(Data->lineGet()));


    PrmAnychar->init(TiPa_Character::Anychar);           // all characters with an ordinal number between 1 and 255

    ReturnValue = PrmAnychar;
   }break;
   case Spirit185_Internal::PrmBlank_rid:                 // primitive parser: blank
   {
    LOG_OUTPUT(LOG_OFF, "creation of blank ");
    CREATE_USER_PARSER(TiPa_Character, PrmBlank, "__Prm_Blank__", Mbr.LocalParserID++,
                       "primitive : blank",
                       Mbr.GrammarTextIdentifier,atoi(Data->lineGet()));
    PrmBlank->init(TiPa_Character::Blank);            // blank

    ReturnValue = PrmBlank;
   }break;
   case Spirit185_Internal::PrmCntrl_rid:                 // primitive parser: control characters
   {
    LOG_OUTPUT(LOG_OFF, "creation of control characters ");
    CREATE_USER_PARSER(TiPa_Character, PrmCntrl, "__Prm_Cntrl__", Mbr.LocalParserID++,
                       "primitive : control characters",
                       Mbr.GrammarTextIdentifier,atoi(Data->lineGet()));
    PrmCntrl->init(TiPa_Character::Cntrl);            // blank

    ReturnValue = PrmCntrl;
   }break;
   case Spirit185_Internal::PrmDigit_rid:                 // primitive parser: digits
   {
    LOG_OUTPUT(LOG_OFF, "creation of digits ");
    CREATE_USER_PARSER(TiPa_Character, PrmDigit, "__Prm_Digit__", Mbr.LocalParserID++,
                       "primitive : digits",
                       Mbr.GrammarTextIdentifier,atoi(Data->lineGet()));
    PrmDigit->init(TiPa_Character::Digit);            // digits

    ReturnValue = PrmDigit;
   }break;
   case Spirit185_Internal::PrmGraph_rid:                 // primitive parser: graphs
   {
    LOG_OUTPUT(LOG_OFF, "creation of graphs ");
    CREATE_USER_PARSER(TiPa_Character, PrmGraph, "__Prm_Graph__", Mbr.LocalParserID++,
                       "primitive : graphs",
                       Mbr.GrammarTextIdentifier,atoi(Data->lineGet()));
    PrmGraph->init(TiPa_Character::Graph);            // graphs

    ReturnValue = PrmGraph;
   }break;
   case Spirit185_Internal::PrmLower_rid:                 // primitive parser: lower case characters
   {
    LOG_OUTPUT(LOG_OFF, "creation of lower case characters ");
    CREATE_USER_PARSER(TiPa_Character, PrmLower, "__Prm_Lower__", Mbr.LocalParserID++,
                       "primitive : lower case characters",
                       Mbr.GrammarTextIdentifier,atoi(Data->lineGet()));
    PrmLower->init(TiPa_Character::Lower);             // lower

    ReturnValue = PrmLower;
   }break;
   case Spirit185_Internal::PrmPrint_rid:                 // primitive parser: printable characters
   {
    LOG_OUTPUT(LOG_OFF, "creation of printable characters ");
    CREATE_USER_PARSER(TiPa_Character, PrmPrint, "__Prm_Print__", Mbr.LocalParserID++,
                       "primitive : printable characters",
                       Mbr.GrammarTextIdentifier,atoi(Data->lineGet()));
    PrmPrint->init(TiPa_Character::Print);            // print

    ReturnValue = PrmPrint;
   }break;
   case Spirit185_Internal::PrmPunct_rid:                 // primitive parser: punctuation
   {
    LOG_OUTPUT(LOG_OFF, "creation of punctuation ");
    CREATE_USER_PARSER(TiPa_Character, PrmPunct, "__Prm_Punct__", Mbr.LocalParserID++,
                       "primitive : punctuation",
                       Mbr.GrammarTextIdentifier,atoi(Data->lineGet()));
    PrmPunct->init(TiPa_Character::Punct);             // punctuation

    ReturnValue = PrmPunct;
   }break;
   case Spirit185_Internal::PrmSign_rid:                  // primitive parser: sign
   {
    LOG_OUTPUT(LOG_OFF, "creation of sign ");
    CREATE_USER_PARSER(TiPa_Character, PrmSign, "__Prm_Sign__", Mbr.LocalParserID++,
                       "primitive : sign",
                       Mbr.GrammarTextIdentifier,atoi(Data->lineGet()));
    PrmSign->init(TiPa_Character::Sign);             // sign

    ReturnValue = PrmSign;
   }break;
   case Spirit185_Internal::PrmSpace_rid:                 // primitive parser: space
   {
    LOG_OUTPUT(LOG_OFF, "creation of space ");
    CREATE_USER_PARSER(TiPa_Character, PrmSpace, "__Prm_Space__", Mbr.LocalParserID++,
                       "primitive : space",
                       Mbr.GrammarTextIdentifier,atoi(Data->lineGet()));
    PrmSpace->init(TiPa_Character::Space);           // space

    ReturnValue = PrmSpace;
   }break;
   case Spirit185_Internal::PrmUpper_rid:                 // primitive parser: upper case characters
   {
    LOG_OUTPUT(LOG_OFF, "creation of upper case characters ");
    CREATE_USER_PARSER(TiPa_Character, PrmUpper, "__Prm_Upper__", Mbr.LocalParserID++,
                       "primitive : upper case characters",
                       Mbr.GrammarTextIdentifier,atoi(Data->lineGet()));
    PrmUpper->init(TiPa_Character::Upper);// upper

    ReturnValue = PrmUpper;
   }break;
   case Spirit185_Internal::PrmXdigit_rid:                // primitive parser: hexadecimal digits
   {
    LOG_OUTPUT(LOG_OFF, "creation of hexadecimal digits ");
    CREATE_USER_PARSER(TiPa_Character, PrmXdigit, "__Prm_Xdigit__", Mbr.LocalParserID++,
                       "primitive : hexadecimal digits",
                       Mbr.GrammarTextIdentifier,atoi(Data->lineGet()));
    PrmXdigit->init(TiPa_Character::HexDigit);// hex-digit

    ReturnValue = PrmXdigit;
   }break;
   case Spirit185_Internal::PrmBin_rid:                   // primitive parser: binary digits
   {
    LOG_OUTPUT(LOG_OFF, "creation of binary digits ");
    CREATE_USER_PARSER(TiPa_Character, PrmBin, "__Prm_Bin__", Mbr.LocalParserID++,
                       "primitive : binary digits",
                       Mbr.GrammarTextIdentifier,atoi(Data->lineGet()));
    PrmBin->init(TiPa_Character::BinDigit);          // bin digit

    ReturnValue = PrmBin;
   }break;
   case Spirit185_Internal::PrmHex_rid:                   // primitive parser: hexadecimal numbers
   {
    LOG_OUTPUT(LOG_OFF, "creation of hexadecimal digits ");
    CREATE_USER_PARSER(TiPa_Character, Zero, "__Prm_Zero__", Mbr.LocalParserID++,
                       "character : hexadecimal leading 0",
                       Mbr.GrammarTextIdentifier,atoi(Data->lineGet()));
    Zero->init('0');                                 // leading 0

    CREATE_USER_PARSER(TiPa_Character, Xx, "__Prm_Xx__", Mbr.LocalParserID++,
                       "character : hexadecimal X or x",
                       Mbr.GrammarTextIdentifier,atoi(Data->lineGet()));
    Xx->init("Xx",2);                                // x in between

    CREATE_USER_PARSER(TiPa_Character, PrmXdigit, "__Prm_Xdigit__", Mbr.LocalParserID++,
                       "character : hexadecimal digits",
                       Mbr.GrammarTextIdentifier,atoi(Data->lineGet()));
    PrmXdigit->init(TiPa_Character::HexDigit);       // hex-digit

    CREATE_USER_PARSER(TiPa_Counter, HexSequence, "__Prm_HexSequence__", Mbr.LocalParserID++,
                       "character-sequence : hexadecimal numbers",
                       Mbr.GrammarTextIdentifier,atoi(Data->lineGet()));
    HexSequence->init(TiPa_Counter::Cnt_OneOrMore,PrmXdigit); // hex digit sequence

    CREATE_USER_PARSER(TiPa_Sequence, PrmHex, "__Prm_Hex__", Mbr.LocalParserID++,
                       "primitive : hexadecimal numbers",
                       Mbr.GrammarTextIdentifier,atoi(Data->lineGet()));
    PrmHex->init(TiPa_Sequence::Seq_HrdSq, Zero, Xx);  //hex header
    PrmHex->contractor_ParserInsert(HexSequence,2);  //hexadecimal numbers

    ReturnValue = PrmHex;
   }break;
   case Spirit185_Internal::PrmOct_rid:                   // primitive parser: octal numbers
   {
    LOG_OUTPUT(LOG_OFF, "creation of octal numbers ");
    CREATE_USER_PARSER(TiPa_Character, Octal, "__Prm_Octal__", Mbr.LocalParserID++,
                       "primitive : blank",
                       Mbr.GrammarTextIdentifier,atoi(Data->lineGet()));
    Octal->init(TiPa_Character::OctDigit);            // hex-digit

    CREATE_USER_PARSER(TiPa_Counter, PrmOct, "__Prm_Oct__", Mbr.LocalParserID++,
                       "character : hexadecimal numbers",
                       Mbr.GrammarTextIdentifier,atoi(Data->lineGet()));
    PrmOct->init(TiPa_Counter::Cnt_OneOrMore,Octal);  // new line for Apple-Macintosh

    ReturnValue = PrmOct;
   }break;
   case Spirit185_Internal::PrmEscape_rid:                // primitive parser: escape characters
   {
    LOG_OUTPUT(LOG_OFF, "creation of escape characters ");

    CREATE_USER_PARSER(TiPa_Character, BackSlash, "__Prm_BackSlash__", Mbr.LocalParserID++,
                       "character : backslash",
                       Mbr.GrammarTextIdentifier,atoi(Data->lineGet()));
    BackSlash->init('\\'); //backslash

    CREATE_USER_PARSER(TiPa_Character, Anychar, "__Prm_Anychar__", Mbr.LocalParserID++,
                       "primitive : any character",
                       Mbr.GrammarTextIdentifier,atoi(Data->lineGet()));
    Anychar->init(TiPa_Character::Anychar);           // all characters with an ordinal number between 1 and 255

    CREATE_USER_PARSER(TiPa_Sequence, Escape, "__Prm_Escape__", Mbr.LocalParserID++,
                       "primitive : escape characters",
                       Mbr.GrammarTextIdentifier,atoi(Data->lineGet()));
    Escape->init(TiPa_Sequence::Seq_HrdSq, BackSlash, Anychar);
    ReturnValue = Escape;
   }break;
   case Spirit185_Internal::PrmEol_rid:                   // primitive parser: end-of-line
   {
    LOG_OUTPUT(LOG_OFF, "creation of end-of-line ");
    CREATE_USER_PARSER(TiPa_Character, CR, "__Prm_CR__", Mbr.LocalParserID++,
                       "character : carriage return",
                       Mbr.GrammarTextIdentifier,atoi(Data->lineGet()));
    CR->init(13);                                     // carriage return

    CREATE_USER_PARSER(TiPa_Character, LF, "__Prm_LF__", Mbr.LocalParserID++,
                       "character : line feed",
                       Mbr.GrammarTextIdentifier,atoi(Data->lineGet()));
    LF->init(10);                                     // line feed

    CREATE_USER_PARSER(TiPa_Sequence, NL_MS, "__Prm_NL_MS__", Mbr.LocalParserID++,
                       "character-sequence : new line for Microsoft",
                       Mbr.GrammarTextIdentifier,atoi(Data->lineGet()));
    NL_MS->init(TiPa_Sequence::Seq_HrdSq,CR, LF);     // new line for Microsoft

    CREATE_USER_PARSER(TiPa_Rule, NL_UNIX, "__Prm_NL_UNIX__", Mbr.LocalParserID++,
                       "character : new line for Linux",
                       Mbr.GrammarTextIdentifier,atoi(Data->lineGet()));
    NL_UNIX->init(LF);    // new line for Unix or Linux


    CREATE_USER_PARSER(TiPa_Condition, NL_MAC, "__Prm_NL_MAC__", Mbr.LocalParserID++,
                       "character : new line for Apple-Macintosh",
                       Mbr.GrammarTextIdentifier,atoi(Data->lineGet()));
    NL_MAC->init(TiPa_Condition::Cnd_WthOt,CR,NL_MS);     // new line for Apple-Macintosh

    CREATE_USER_PARSER(TiPa_Condition, PrmEol, "__Prm_PrmEol__", Mbr.LocalParserID++,
                       "primitive : new line for Microsoft ex-or Unix/Linux ex-or Apple-Macintosh",
                       Mbr.GrammarTextIdentifier,atoi(Data->lineGet()));
    PrmEol->init(TiPa_Condition::Cnd_OrExc, NL_MS, NL_UNIX);    // new line for Microsoft ex-or Unix/Linux

    PrmEol->contractor_ParserInsert(NL_MAC,2);                  // new line for Microsoft ex-or Unix/Linux ex-or Apple-Macintosh

    ReturnValue = PrmEol;
   }break;
   case Spirit185_Internal::PrmEnd_rid:                   // primitive parser end-of-input
   {
    LOG_OUTPUT(LOG_OFF, "creation of end-of-input ");

    CREATE_USER_PARSER(TiPa_Character, Anychar, "__Prm_Anychar__", Mbr.LocalParserID++,
                       "primitive : any character",
                       Mbr.GrammarTextIdentifier,atoi(Data->lineGet()));
    Anychar->init(TiPa_Character::Anychar);           // all characters with an ordinal number between 1 and 255

    CREATE_USER_PARSER(TiPa_Counter, PrmEnd, "__Prm_PrmEnd__", Mbr.LocalParserID++,
                       "primitive : end of input",
                       Mbr.GrammarTextIdentifier,atoi(Data->lineGet()));
    PrmEnd->init(TiPa_Counter::Cnt_AllButNot,Anychar);  //end of text to parse

    ReturnValue = PrmEnd;
   }break;

   default:
   {
    LOG_OUTPUT(LOG_OFF, "invalid primitive content ");

    CREATE_USER_PARSER(TiPa_Character, Anychar, "__Prm_Anychar__", Mbr.LocalParserID++,
                       "primitive : any character",
                       Mbr.GrammarTextIdentifier,atoi(Data->lineGet()));
    Anychar->init(TiPa_Character::Anychar);           // all characters with an ordinal number between 1 and 255

    CREATE_USER_PARSER(TiPa_Counter, PrmEnd, "__Prm_PrmEnd__", Mbr.LocalParserID++,
                       "primitive : end of input",
                       Mbr.GrammarTextIdentifier,atoi(Data->lineGet()));
    PrmEnd->init(TiPa_Counter::Cnt_AllButNot,Anychar);  //end of text to parse

    ReturnValue = PrmEnd;

   }break;
  }
  CharacterPart = CharacterPart->fellowBehind_get();
 }



 if(phrased == true)
 {
// LOG_OUTPUT(LOG_OFF, "phrased Character");
 }
 else
 {
//  LOG_OUTPUT(LOG_OFF, "not phrased Character");
 }


 return(ReturnValue);
}




/* @MRTZ_describe Spirit185_External_create_ParserCharacter

*/
TiPa_Character* Spirit185_External::create_ParserCharacter(TiPa_Concrete::DataAssociation* association,
                                                           bool                phrased)
{
 TiPa_Character*     ReturnValue   = nullptr;

 TiPa_Concrete::DataAssociation* CharacterPart = association->contractorFirst_get();
 while(CharacterPart != nullptr )
 {
  TiPa_Data*  CharacterData    = CharacterPart->data_get();

  LOG_OUTPUT(LOG_OFF, string("character content : ") << CharacterData->UserDescription << " > " << CharacterData->getContent());
  logRawResult(CharacterData->getContent());

  char* ParserNumber = nullptr;
  TiPa_Data::itoa(&ParserNumber,Mbr.LocalParserID) ;
  char ParserName[30] = "__Character__";
  strcat(ParserName,ParserNumber);

  switch(CharacterData->UserID)
  {
   case Spirit185_Internal::CharacterSingle_rid:          // character parser for one single character
   {
    LOG_OUTPUT(LOG_OFF, "creation of single character ");
    TiPa_Concrete::DataAssociation* Parameter1 = CharacterPart->contractorFirst_get();
    if(Parameter1 != nullptr)
    {
     TiPa_Data*  Data       = Parameter1->data_get();
     const char* Content    = Data->getContent();
     char        Character1 = getPureCharacter(Content);

     ReturnValue =  dynamic_cast<TiPa_Character*>(createParser(TiPa_Character::id_Class(),
                                                               ParserName,
                                                               "Chr",
                                                               Mbr.LocalParserID++,
                                                               "a single character",
                                                               Mbr.GrammarTextIdentifier,
                                                               atoi(Data->lineGet())));
     ReturnValue->init(Character1);
    }
    else
    {
     LOG_OUTPUT(LOG_OFF, "parameter 1 is not valid");
     ReturnValue = new TiPa_Character(nullptr);
    }
   }break;
   case Spirit185_Internal::CharacterRange_rid:           // parser function for a character range
   {
    LOG_OUTPUT(LOG_OFF, "creation of character range ");
    TiPa_Concrete::DataAssociation* Parameter1 = CharacterPart->contractorFirst_get();
    TiPa_Concrete::DataAssociation* Parameter2 = CharacterPart->contractorLast_get();
    if(  (Parameter1 != nullptr)
       &&(Parameter2 != nullptr)
      )
    {
     TiPa_Data*  Data        = Parameter1->data_get();
     const char* Content     = Data->getContent();
     char        Character1  = getPureCharacter(Content);

                 Data        = Parameter2->data_get();
                 Content     = Data->getContent();
     char Character2         = getPureCharacter(Content);

     ReturnValue =  dynamic_cast<TiPa_Character*>(createParser(TiPa_Character::id_Class(),
                                                               ParserName,
                                                               "Chr",
                                                               Mbr.LocalParserID++,
                                                               "a character range",
                                                               Mbr.GrammarTextIdentifier,
                                                               atoi(Data->lineGet())));
     ReturnValue->init(Character1,Character2);
    }
    else
    {
     LOG_OUTPUT(LOG_OFF, "parameter 1 or parameter 2 is not valid");
     ReturnValue = new TiPa_Character(nullptr);
    }

   }break;
   default:
   {
    LOG_OUTPUT(LOG_OFF, "invalid character content ");
   }break;
  }

  CharacterPart = CharacterPart->fellowBehind_get();
 }


/*
*/
 if(phrased == true)
 {
  LOG_OUTPUT(LOG_OFF, "phrased Character");
//  ReturnValue->skip_ParserSet(TDA_GrmConcrete::Att.SkipParser);
 }
 else
 {
  LOG_OUTPUT(LOG_OFF, "not phrased Character");
 }

 return(ReturnValue);
}



/* @MRTZ_describe getPureCharacter

*/
char Spirit185_External::getPureCharacter(const char* symbol)
{
 char ReturnValue = 0;

 if(symbol[0] != '\\')
 {
  ReturnValue = symbol[0];
 }
 else
 {
  switch(symbol[1])
  {
   case'\''/*single quote*/ 	          : ReturnValue = 0x27; break;
   case'\"'/*double quote*/ 	          : ReturnValue = 0x22; break;
   case'?'/*question mark*/ 	          : ReturnValue = 0x3f; break;
   case'\\'/*backslash*/ 	              : ReturnValue = 0x5c; break;
   case'a'/*audible bell*/                : ReturnValue = 0x07; break;
   case'b'/*backspace*/                   : ReturnValue = 0x08; break;
   case'f'/*form feed - new page*/        : ReturnValue = 0x0c; break;
   case'n'/*line feed - new line*/        : ReturnValue = 0x0a; break;
   case'r'/*carriage return*/             : ReturnValue = 0x0d; break;
   case't'/*horizontal tab*/              : ReturnValue = 0x09; break;
   case'v'/*vertical tab*/                : ReturnValue = 0x0b; break;

   case'0':
   case'1':
   case'2':
   case'3':
   case'4':
   case'5':
   case'6':
   case'7':
/*
\nnn 	arbitrary octal value 	byte nnn
Of the octal escape sequences, \0 is the most useful because it represents the terminating nullptr character in
   case'0' terminating nullptr character  : ReturnValue = 0x00; break;
*/
   {
    ReturnValue = 0;
    int Index = 1;             //without leading back-slash
    while(  (symbol[Index]>='0')
          &&(symbol[Index]<='7')
         )                 // as long as characters a octal digits
    {
      ReturnValue = ReturnValue*8 +(symbol[Index]-'0');
                           // shift by one octal digit and add numerical value of character
      ++Index;             // next character
    }
   } break;
/*
   case'x'
\xnn 	arbitrary hexadecimal value 	byte nn
*/
   case'u':
/*
\unnnn 	universal character name
(arbitrary Unicode value);
may result in several characters 	code point U+nnnn
*/
   {
    ReturnValue = 0;
    int Index = 1;             //without leading back-slash
    while((   (symbol[Index]>='0')
            &&(symbol[Index]<='9')
           )
         ||(  (symbol[Index]>='A')
            &&(symbol[Index]<='F')
            )
         ||(  (symbol[Index]>='a')
            &&(symbol[Index]<='f')
            )
         )                 // as long as characters a hexadecimal digits
    {
      if      (symbol[Index]<='9')
       ReturnValue = ReturnValue*16 +(symbol[Index]-'0');
                           // shift by one hexadecimal digit and add deci-numerical value of character
      else if (symbol[Index]<='F')
       ReturnValue = ReturnValue*16 +(symbol[Index]-'A' + 10);
                           // shift by one hexadecimal digit and add hexa-numerical value of character
      else  //(symbol[Index]<='f')
       ReturnValue = ReturnValue*16 +(symbol[Index]-'a' + 10);
                           // shift by one hexadecimal digit and add hexa-numerical value of character
      ++Index;             // next character
    }
   } break;
   case'U':
/*
   case'U'
\Unnnnnnnn 	universal character name
(arbitrary Unicode value);
may result in several characters 	code point U+nnnnnnnn
*/
   {
    LOG_OUTPUT(LOG_OFF, "Unicode character definition not supported");
    ReturnValue = (char)0xFF;
   } break; // no Unicode support

   default: LOG_OUTPUT(LOG_OFF, "invalid escape-sequence found");ReturnValue = 0 ; break;
  }
 }

 return(ReturnValue);
}



/* @MRTZ_describe Spirit185_External_create_ParserString

*/
TiPa_String* Spirit185_External::create_ParserString(TiPa_Concrete::DataAssociation* association,
                                                     bool                phrased)
{
 TiPa_String*        ReturnValue = nullptr;

 TiPa_Condition* ConditionReserved = dynamic_cast<TiPa_Condition*>(createParser(TiPa_Condition::id_Class(),
                                                                                "ConditionReserved",
                                                                                "ConditionReserved",
                                                                                -1,
                                                                                "a collection of reserved words",
                                                                                Mbr.GrammarTextIdentifier,
                                                                                -1));

 TiPa_Concrete::DataAssociation*  StringPart = association->contractorFirst_get();
 while(StringPart != nullptr )
 {
  TiPa_Data* StringData = StringPart->data_get();
  LOG_OUTPUT(LOG_OFF, string("combination content : ") << StringData->UserDescription << " > " << StringData->getContent());
  logRawResult(StringData->getContent());

  char* ParserNumber  = nullptr;
  TiPa_Data::itoa(&ParserNumber,Mbr.LocalParserID) ;
  char ParserName[30] = "__String__";
  strcat(ParserName,ParserNumber);

  switch(StringData->UserID)
  {
   case Spirit185_Internal::KeyWordCommentSingle_rid:     // parser function for a single line commenting string
   {
    LOG_OUTPUT(LOG_OFF, "creation of single line commenting string");
    TiPa_Concrete::DataAssociation* Parameter1 = StringPart->contractorFirst_get();
    if(Parameter1 != nullptr)
    {
     TiPa_Data*  Data    = Parameter1->data_get();
     const char* Content = Data->getContent();
     char*       String1 = nullptr;
     LOG_OUTPUT(LOG_OFF, string("Line : ") << Data->lineGet());
     getPureString(Content,&String1);

     ReturnValue =  dynamic_cast<TiPa_String*>(createParser(TiPa_String::id_Class(),
                                                            ParserName,
                                                            "Str",
                                                            Mbr.LocalParserID++,
                                                            "a single line commenting string",
                                                            Mbr.GrammarTextIdentifier,
                                                            atoi(Data->lineGet())));
     ReturnValue->init(String1);//????????????????????

     ConditionReserved->contractor_ParserInsert(ReturnValue, TiPa_Concrete::InsertNext);

     delete[](String1); // already copied in the parser

    }
   }break;
   case Spirit185_Internal::KeyWordCommentDouble_rid:     // parser function for a block commenting string
   {
    LOG_OUTPUT(LOG_OFF, "creation of block commenting string ");
    TiPa_Concrete::DataAssociation* Parameter1 = StringPart->contractorFirst_get();
    TiPa_Concrete::DataAssociation* Parameter2 = StringPart->contractorLast_get();
    if(  (Parameter1 != nullptr)
       &&(Parameter2 != nullptr)
      )
    {
     TiPa_Data*  Data    = Parameter1->data_get();
     const char* Content = Data->getContent();
     char*       String1 = nullptr;
     char*       String2 = nullptr;
     LOG_OUTPUT(LOG_OFF, string("Line : ") << Data->lineGet());
     getPureString(Content,&String1);
     Data    = Parameter2->data_get();
     Content = Data->getContent();
     getPureString(Content,&String2);

     ReturnValue =  dynamic_cast<TiPa_String*>(createParser(TiPa_String::id_Class(),
                                                            ParserName,
                                                            "Str",
                                                            Mbr.LocalParserID++,
                                                            "a block commenting string",
                                                            Mbr.GrammarTextIdentifier,
                                                            atoi(Data->lineGet())));
     ReturnValue->init(String1);      //???????????????????
     ReturnValue->include(String2);   //???????????????????

     ConditionReserved->contractor_ParserInsert(ReturnValue, TiPa_Concrete::InsertNext);

     delete[](String1); // already copied in the parser
     delete[](String2); // already copied in the parser

    }
   }break;
   case Spirit185_Internal::KeyWordString_rid:             // parser for a real string
   {
    LOG_OUTPUT(LOG_OFF, "creation of real string ");
    TiPa_Concrete::DataAssociation* Parameter1 = StringPart->contractorFirst_get();
    if(Parameter1 != nullptr)
    {
     TiPa_Data*  Data    = Parameter1->data_get();
     const char* Content = Data->getContent();
     char*       String1 = nullptr;
     LOG_OUTPUT(LOG_OFF, string("Line : ") << Data->lineGet());
     getPureString(Content,&String1);

     ReturnValue =  dynamic_cast<TiPa_String*>(createParser(TiPa_String::id_Class(),
                                                            ParserName,
                                                            "Str",
                                                            Mbr.LocalParserID++,
                                                            "a real string",
                                                            Mbr.GrammarTextIdentifier,
                                                            atoi(Data->lineGet())));
     ReturnValue->init(String1);

     ConditionReserved->contractor_ParserInsert(ReturnValue, TiPa_Concrete::InsertNext);

     delete[](String1); // already copied in the parser

    }
   }break;
   case Spirit185_Internal::KeyWordCharSequence_rid:      // parser function for a character sequence
   {
    LOG_OUTPUT(LOG_OFF, "creation of character sequence ");
    TiPa_Concrete::DataAssociation* Parameter1 = StringPart->contractorFirst_get();
    if(Parameter1 != nullptr)
    {

     TiPa_Data*  Data    = Parameter1->data_get();
     const char* Content = Data->getContent();
     char*       String1 = nullptr;
     LOG_OUTPUT(LOG_OFF, string("Line : ") << Data->lineGet());
     getPureString(Content,&String1);

     ReturnValue =  dynamic_cast<TiPa_String*>(createParser(TiPa_String::id_Class(),
                                                            ParserName,
                                                            "Str",
                                                            Mbr.LocalParserID++,
                                                            "a character sequence",
                                                            Mbr.GrammarTextIdentifier,
                                                            atoi(Data->lineGet())));
     ReturnValue->init(String1);

     ConditionReserved->contractor_ParserInsert(ReturnValue, TiPa_Concrete::InsertNext);

     delete[](String1);                                  // already copied in the parser
    }
   }break;
   default:
   {
    LOG_OUTPUT(LOG_OFF, "invalid string content ");

   }break;
  }

  StringPart = StringPart->fellowBehind_get();
 }

/*
 */
 if(phrased == true)
 {
  LOG_OUTPUT(LOG_OFF, "phrased String");
 }
 else
 {
  LOG_OUTPUT(LOG_OFF, "not phrased String");
 }

 return(ReturnValue);
}




/* @MRTZ_describe getPureString

*/
void Spirit185_External::getPureString(const char* symbol, char** destination)
{
 int   Read        = 0;                                   // index of reading
 int   Write       = 0;                                   // index of writing
 int   Size        = strlen(symbol);                      // size of strings

 if(*destination == nullptr)                              // user has not prepared the destination memory
  (*destination) = new char[Size+1];                      // allocate enough memory to create a terminated string

 while(  (Read < Size)
       &&(Write < Size)
      )                                                   // iterate over strings
 {
  if(symbol[Read] != '\\')                                // normal character
  {
   (*destination)[Write] = symbol[Read];                  // simple copy
   ++Read;                                                // jump over character
  }
  else                                                    // escape-sequence
  {
   (*destination)[Write] = getPureCharacter(symbol+Read); // transform to character
   ++Read;                                                // jump over backslash
   ++Read;                                                // jump over character
  }
   ++Write;                                               // next position to write in
 }
 (*destination)[Write] = 0;                               // terminate string


}







/* @MRTZ_describe Spirit185_External_create_ParserCounter

*/
TiPa_Counter* Spirit185_External::create_ParserCounter(TiPa_Concrete::DataAssociation* association,
                                                       bool                phrased)
{
 TiPa_Counter*                   ReturnValue   = nullptr;

 TiPa_Counter::Parser_id Operation       = TiPa_Counter::Cnt_Default;
 char                    LogString[5][4] ={" § ", " ! ", " * ", " + ", " ~ "} ;
 list<TiPa_Concrete*>    Parser;

 TiPa_Concrete::DataAssociation* CounterPart = association->contractorFirst_get();
 while(CounterPart != nullptr )
 {
  TiPa_Data*  Data     = CounterPart->data_get();
  int         LogIndex = 0;

  LOG_OUTPUT(LOG_OFF, string("counter content : ")<<Data->getContent());

  int CounterPartID =Data->UserID;
  switch(CounterPartID)                            //store kind of unary operation
  {
   case Spirit185_Internal::UniOperand_OptionOne_rid : // operation  one match or nothing
    Operation = TiPa_Counter::Cnt_OptionOne;           // operator to find nothing or one
    LogIndex   = 1;
   break;
   case Spirit185_Internal::UniOperand_OptionMore_rid: // operation zero or more matches
    Operation = TiPa_Counter::Cnt_OptionMore;      // operator to find nothing or more
    LogIndex   = 2;
   break;
   case Spirit185_Internal::UniOperand_OneOrMore_rid : // operation one or more matches
    Operation = TiPa_Counter::Cnt_OneOrMore;       // operator to find one or more
    LogIndex   = 3;
   break;
   case Spirit185_Internal::UniOperand_AllButNot_rid : // operation every character without
    Operation = TiPa_Counter::Cnt_AllButNot;       // operator to find every character except the defined
    LogIndex   = 4;
   break;
   default:                                        // user id is not defined for a counter-operation
    Operation = TiPa_Counter::Cnt_Default;         // not specified counting operator
    logRawResult(Data->getContent());
   break;
  }

  switch(CounterPartID)
  {
   case Spirit185_Internal::UniOperand_OptionOne_rid : // operation  one match or nothing
   case Spirit185_Internal::UniOperand_OptionMore_rid: // operation zero or more matches
   case Spirit185_Internal::UniOperand_OneOrMore_rid : // operation one or more matches
   case Spirit185_Internal::UniOperand_AllButNot_rid : // operation every character without
   {
    TiPa_Concrete::DataAssociation* SubParser = CounterPart->contractorFirst_get();
    while(SubParser != nullptr)
    {
         Data        = SubParser->data_get();
     int SubParserID = Data->UserID;
     LOG_OUTPUT(LOG_OFF, "call spirit like parser creation in create_ParserCounter ");

     logRawResult(LogString[LogIndex],3);
     Parser.push_back(call_ParserCreation(SubParserID,SubParser,phrased));
     logRawResult(EMPTYLOG,-3);

     SubParser = SubParser->fellowBehind_get();
    }
   }break;
   default:
   {
    LOG_OUTPUT(LOG_OFF, "call default parser creation in create_ParserCounter ");
    Parser.push_back(call_ParserCreation(Data->UserID,CounterPart,phrased));
   }break;
  }
  CounterPart = CounterPart->fellowBehind_get();
 }

 if(Parser.size() == 1)    // exactly 1 sub-parser found
 {

  char* ParserNumber = nullptr;
  TiPa_Data::itoa(&ParserNumber,Mbr.LocalParserID) ;
  char ParserName[30] = "__Counter__";
  strcat(ParserName,ParserNumber);

  TiPa_Data*  Data    = association->data_get();

  ReturnValue =  dynamic_cast<TiPa_Counter*>(createParser(TiPa_Counter::id_Class(),
                                                          ParserName,
                                                          "Counter",
                                                          Mbr.LocalParserID++,
                                                          "a counter",
                                                          Mbr.GrammarTextIdentifier,
                                                          atoi(Data->lineGet())));
  ReturnValue->init( Operation, *Parser.begin());

 }
 else if(Parser.size()>1)    // at least 2 sub-parsers found
 {
  LOG_OUTPUT(LOG_OFF, "counter parser has to much operands");
 }
 else                        // no sub-parser found
 {
  LOG_OUTPUT(LOG_OFF, "counter parser has no operands");
 }

 if(phrased == true)
 {
  LOG_OUTPUT(LOG_OFF, "phrased counter");
  ReturnValue->skip_ParserSet(TDA_GrmConcrete::Att.SkipParser);
 }
 else
 {
  LOG_OUTPUT(LOG_OFF, "not phrased counter");

 }

 return(ReturnValue);
}





/* @MRTZ_describe create_ParserSequence

*/
TiPa_Sequence* Spirit185_External::create_ParserSequence(TiPa_Concrete::DataAssociation* association,
                                                         bool                            phrased)
{
 TiPa_Sequence*           ReturnValue       = nullptr;

 TiPa_Sequence::Parser_id Operation       = TiPa_Sequence::Seq_Default;
 char                     LogString[4][5] ={"    ", " >> ", "  % ", " || "};
 list<TiPa_Concrete*>     Parser;

 logRawResult("(",1);

 TiPa_Concrete::DataAssociation* SequencePart = association->contractorFirst_get();
 while(SequencePart != nullptr )
 {
  TiPa_Data* Data     = SequencePart->data_get();
  int        LogIndex = 0;

  int SequencePartID  = Data->UserID;

  switch(SequencePartID)                      //store kind of binary operation
  {
   case Spirit185_Internal::BinOperand_HrdSeq_rid: // multi part of operation for serial sequence
    Operation = TiPa_Sequence::Seq_HrdSq;          // next part detection of sequence-part (&&) or (>>)
    LogIndex   = 1;
   break;
   case Spirit185_Internal::BinOperand_Seprt_rid:  // multi part of operation for table sequence
    Operation = TiPa_Sequence::Seq_Seprt;          // next part detection of table-part (%)
    LogIndex   = 2;
   break;
   case Spirit185_Internal::BinOperand_SftSq_rid:  // multi part of operation for inclusive-or sequence
    Operation = TiPa_Sequence::Seq_SftSq;          // next part detection of sequence-part (||)
    LogIndex   = 3;
   break;
   default:                                    // first operand ->
                                               // operation not known
                                               // operand in between ->
                                               // user id is not defined for a counter-operation
                                               // keep the current value for the case that it already contain valid content
   break;
  }

  switch(SequencePartID)
  {
   case Spirit185_Internal::BinOperand_HrdSeq_rid:// multi part of operation for serial sequence
   case Spirit185_Internal::BinOperand_Seprt_rid: // multi part of operation for table sequence
   case Spirit185_Internal::BinOperand_SftSq_rid: // multi part of operation for inclusive-or sequence
   {
    TiPa_Concrete::DataAssociation* SubParser = SequencePart->contractorFirst_get();
    while(SubParser != nullptr)
    {
         Data        = SubParser->data_get();
     int SubParserID = Data->UserID;
     LOG_OUTPUT(LOG_OFF, string("call parser creation in create_ParserSequence "));

     logRawResult(LogString[LogIndex],4);
     Parser.push_back(call_ParserCreation(SubParserID,SubParser,phrased));
     SubParser = SubParser->fellowBehind_get();
     if(SubParser != nullptr)
      logRawResult(EMPTYLOG,-4,NEWLOGLINE);
     else
      logRawResult(EMPTYLOG,-4);

    }
   }break;
   default:                                  // first operand
   {
    Data = SequencePart->data_get();

    LOG_OUTPUT(LOG_OFF, string("first sequence content : ")<< Data->UserID << " : " /*<< Content*/);

    logRawResult(LogString[LogIndex],4);
    Parser.push_back(call_ParserCreation(SequencePartID,SequencePart,phrased));
    logRawResult(EMPTYLOG,-4,NEWLOGLINE);

   }break;
  }
  SequencePart = SequencePart->fellowBehind_get();
 }

 logRawResult(EMPTYLOG,-1,NEWLOGLINE);
 logRawResult(")");

 if(Parser.size()>1)    // at least 2 sub-parsers found
 {
  char* ParserNumber = nullptr;
  TiPa_Data::itoa(&ParserNumber,Mbr.LocalParserID) ;
  char ParserName[30] = "__Sequence__";
  strcat(ParserName,ParserNumber);

   TiPa_Data*  Data    = association->data_get();

   list<TiPa_Concrete*>::iterator Current = Parser.begin();
   ++ Current;
   ReturnValue =  dynamic_cast<TiPa_Sequence*>(createParser(TiPa_Sequence::id_Class(),
                                                            ParserName,
                                                            "Sequence",
                                                            Mbr.LocalParserID++,
                                                            "a sequence",
                                                            Mbr.GrammarTextIdentifier,
                                                            atoi(Data->lineGet())));
   ReturnValue->init( Operation,
                     *Parser.begin(),
                     *Current,
                      TiPa_Sequence::PrDr_Default); ///< @todo last argument the directive has to be correctly defined

   int Counter = 2;                         //sub-parser index
     ++Current;
   while(Current != Parser.end())
   {
    ReturnValue->contractor_ParserInsert(*Current, Counter); // add next sub-parser
    ++Counter;
    ++Current;
   }
 }
 else     // less than 2 operands found
 {
  LOG_OUTPUT(LOG_OFF, "sequence parser has not enough operands");
 }



/*
 */
 if(phrased == true)
 {
  LOG_OUTPUT(LOG_OFF, "phrased Sequence");
  ReturnValue->skip_ParserSet(TDA_GrmConcrete::Att.SkipParser);
 }
 else
 {
  LOG_OUTPUT(LOG_OFF, "not phrased Sequence");
 }

 return(ReturnValue);
}







/* @MRTZ_describe create_ParserCondition

*/
TiPa_Condition* Spirit185_External::create_ParserCondition(TiPa_Concrete::DataAssociation* association,
                                                           bool                            phrased)
{
 TiPa_Condition*           ReturnValue       = nullptr;

 TiPa_Condition::Parser_id Operation       = TiPa_Condition::Cnd_Default;
 char                      LogString[5][4] ={"   ", " - ", " & ", " | ", " ^ "};
 list<TiPa_Concrete*>      Parser;

 logRawResult("(",1);

 TiPa_Concrete::DataAssociation* ConditionPart = association->contractorFirst_get();
 while(ConditionPart != nullptr )
 {
  TiPa_Data* Data     = ConditionPart->data_get();
  int        LogIndex = 0;
  int ConditionPartID = Data->UserID;

  switch(ConditionPartID)                    //store kind of binary operation
  {
   case Spirit185_Internal::BinOperand_WthOt_rid:  // multi part of operation for without operation
    Operation = TiPa_Condition::Cnd_WthOt;         // next part detection of without (-)
    LogIndex  = 1;
   break;
   case Spirit185_Internal::BinOperand_And_rid:    // multi part of operation for and operation character
    Operation = TiPa_Condition::Cnd_And ;          // next part detection of and (&)
    LogIndex  = 2;
   break;
   case Spirit185_Internal::BinOperand_OrInc_rid:  // multi part of operation for inclusive-or operation character
    Operation = TiPa_Condition::Cnd_OrInc;         // next part detection of inclusive-or (|)
    LogIndex  = 3;
   break;
   case Spirit185_Internal::BinOperand_OrExc_rid:  // multi part of operation for exclusive-or operation
    Operation = TiPa_Condition::Cnd_OrExc;         // next part detection of exclude-or (^)
    LogIndex  = 4;
   break;
   default:                                    // first operand ->
                                               // operation not known
                                               // operand in between ->
                                               // user id is not defined for a counter-operation
                                               // keep the current value for the case that it already contain valid content
   break;
  }


  switch(ConditionPartID)
  {
   case Spirit185_Internal::BinOperand_WthOt_rid: // multi part of operation for without operation
   case Spirit185_Internal::BinOperand_And_rid:   // multi part of operation for and operation character
   case Spirit185_Internal::BinOperand_OrInc_rid: // multi part of operation for inclusive-or operation character
   case Spirit185_Internal::BinOperand_OrExc_rid: // multi part of operation for exclusive-or operation
   {
    TiPa_Concrete::DataAssociation* SubParser = ConditionPart->contractorFirst_get();

    while(SubParser != nullptr)
    {
         Data        = SubParser->data_get();
     int SubParserID = Data->UserID;
     LOG_OUTPUT(LOG_OFF, "call other parser creation in create_ParserCombination ");

     logRawResult(LogString[LogIndex],3);
     Parser.push_back(call_ParserCreation(SubParserID,SubParser,phrased));

     SubParser = SubParser->fellowBehind_get();
     if(SubParser != nullptr)
      logRawResult(EMPTYLOG,-3,NEWLOGLINE);
     else
      logRawResult(EMPTYLOG,-3);
    }
   }break;
   default:                                  // first operand
   {
    Data = ConditionPart->data_get();
    LOG_OUTPUT(LOG_OFF, string("first condition content : ")<< Data->UserID << " : " /*<< Content*/);

    logRawResult(LogString[LogIndex],3);
    Parser.push_back(call_ParserCreation(ConditionPartID,ConditionPart,phrased));
    logRawResult(EMPTYLOG,-3,NEWLOGLINE);

   }break;
  }
  ConditionPart = ConditionPart->fellowBehind_get();
 }

 logRawResult(EMPTYLOG,-1,NEWLOGLINE);
 logRawResult(")");

 if(Parser.size()>1)    // at least 2 sub-parsers found
 {
  char* ParserNumber = nullptr;
  TiPa_Data::itoa(&ParserNumber,Mbr.LocalParserID) ;
  char ParserName[30] = "__Condition__";
  strcat(ParserName,ParserNumber);

  TiPa_Data*  Data    = association->data_get();

  list<TiPa_Concrete*>::iterator Current = Parser.begin();
  ++ Current;
  ReturnValue =  dynamic_cast<TiPa_Condition*>(createParser(TiPa_Condition::id_Class(),
                                                              ParserName,
                                                              "Condition",
                                                              Mbr.LocalParserID++,
                                                              "a condition",
                                                              Mbr.GrammarTextIdentifier,
                                                              atoi(Data->lineGet())));
  ReturnValue->init( Operation,
                    *Parser.begin(),
                    *Current,
                     TiPa_Condition::PrDr_Default); ///< @todo last argument the directive has to be correctly defined

  int Counter = 2;                         //sub-parser index
    ++Current;
  while(Current != Parser.end())
  {
   ReturnValue->contractor_ParserInsert(*Current, Counter); // add next sub-parser
   ++Counter;
   ++Current;
  }
 }
 else     // less than 2 operands found
 {
  LOG_OUTPUT(LOG_OFF, "condition parser has not enough operands");
 }



/*
 */
 if(phrased == true)
 {
  LOG_OUTPUT(LOG_OFF, "phrased Condition");
  ReturnValue->skip_ParserSet(TDA_GrmConcrete::Att.SkipParser);
 }
 else
 {
  LOG_OUTPUT(LOG_OFF, "not phrased Condition");
 }

 return(ReturnValue);
}


/* @MRTZ_describe call_ParserCreation

*/
TiPa_Concrete*  Spirit185_External::call_ParserCreation(int                             kind,
                                                        TiPa_Concrete::DataAssociation* association,
                                                        bool                            phrased)
{
 TiPa_Concrete* ReturnValue = nullptr;

 switch(kind)
 {
  case Spirit185_Internal::Identifier_rid :
  {
   LOG_OUTPUT(LOG_OFF, string("Identifier content : ")<<association->data_get()->getContent());
   ReturnValue = get_Rule(association/*,phrased*/);

  }break;
  case Spirit185_Internal::Primitive_rid :
  {
   LOG_OUTPUT(LOG_OFF, string("Primitive content : ")<<association->data_get()->getContent());
   ReturnValue = create_ParserPrimitive(association,phrased);

  }break;
  case Spirit185_Internal::Character_rid :
  {
   ReturnValue = create_ParserCharacter(association,phrased);
   LOG_OUTPUT(LOG_OFF, string("Character content : ")<<association->data_get()->getContent());

  }break;
  case Spirit185_Internal::KeyWord_rid :
  {
   ReturnValue = create_ParserString(association,phrased);
   LOG_OUTPUT(LOG_OFF, string("KeyWord content : ")<<association->data_get()->getContent());

  }break;
  case Spirit185_Internal::BinSequence_rid :
  {
   LOG_OUTPUT(LOG_OFF, string("BinOperation content : ")<<association->data_get()->getContent());
   ReturnValue = create_ParserSequence(association,phrased);
  }break;
  case Spirit185_Internal::BinCondition_rid :
  {
   LOG_OUTPUT(LOG_OFF, string("BinOperation content : ")<<association->data_get()->getContent());
   ReturnValue = create_ParserCondition(association,phrased);
  }break;
  case Spirit185_Internal::UniOperation_rid :
  {
   LOG_OUTPUT(LOG_OFF, string("UniOperation content : ")<<association->data_get()->getContent());
   ReturnValue = create_ParserCounter(association,phrased);

  }break;
  default:
  {
   LOG_OUTPUT(LOG_OFF, "rule part not valid  ");

  }break;
 }

 return(ReturnValue);
}




/* @MRTZ_describe collectKeyData

*/
TiPa_Concrete::DataAssociation* Spirit185_External::collectKeyData(TiPa_Concrete::DataAssociation* source,
                                                                   TiPa_Concrete::DataAssociation* destination)
{

 if(destination == nullptr)
 {
  destination = TDA_GrmConcrete::Att.ContextModel->fellow_create();

  destination->data_set(source->data_get());
 }
 else
 {
  //nothing to do since destination was defined outside
 }

 TiPa_Concrete::DataAssociation* ContractorIn = source->contractorFirst_get();
 while(ContractorIn != nullptr)
 {
  TiPa_Data* Data = ContractorIn->data_get();

  if(Data != nullptr)
  {
   switch(Data->UserID)
   {
    case Spirit185_Internal::Root_rid:                     // valid text content
    case Spirit185_Internal::RootElement_rid:              // one MuLanPa grammar rule or comment
    case Spirit185_Internal::RootContent_rid:              // all grammar rules

    case Spirit185_Internal::Rule_rid:                     // single rule
    case Spirit185_Internal::RuleContent_rid:              // actual MuLanPa grammar rule

    case Spirit185_Internal::UniOperation_rid:             // unary parser
    case Spirit185_Internal::UniOperand_OptionOne_rid:     // operation  one match or nothing
    case Spirit185_Internal::UniOperand_OptionMore_rid:    // operation zero or more matches
    case Spirit185_Internal::UniOperand_OneOrMore_rid:     // operation one or more matches
    case Spirit185_Internal::UniOperand_AllButNot_rid:     // operation every character without

    case Spirit185_Internal::BinSequence_rid:              // sequence parser
    case Spirit185_Internal::BinCondition_rid:             // conditional parser
    case Spirit185_Internal::BinOperand_HrdSeq_rid:        // multi part of operation for serial sequence
    case Spirit185_Internal::BinOperand_Seprt_rid:         // multi part of operation for table sequence
    case Spirit185_Internal::BinOperand_SftSq_rid:         // multi part of operation for inclusive-or sequence
    case Spirit185_Internal::BinOperand_WthOt_rid:         // multi part of operation for without operation
    case Spirit185_Internal::BinOperand_And_rid:           // multi part of operation for and operation character
    case Spirit185_Internal::BinOperand_OrInc_rid:         // multi part of operation for inclusive-or operation character
    case Spirit185_Internal::BinOperand_OrExc_rid:         // multi part of operation for exclusive-or operation

    case Spirit185_Internal::Primitive_rid:                // primitive parser
    case Spirit185_Internal::Comment_rid:                  // comment inside the user-grammar

    case Spirit185_Internal::KeyWord_rid:                  // keyword parsers
    case Spirit185_Internal::KeyWordCommentSingle_rid:     // parser function for a single line commenting string
    case Spirit185_Internal::KeyWordCommentDouble_rid:     // parser function for a block commenting string
    case Spirit185_Internal::KeyWordString_rid:            // parser for a real string
    case Spirit185_Internal::KeyWordCharSequence_rid:      // parser function for a character sequence

    case Spirit185_Internal::Character_rid:                // character parsers
    case Spirit185_Internal::CharacterSingle_rid:          // character parser for one single character
    case Spirit185_Internal::CharacterRange_rid:           // parser function for a character range
    {
     //actions for associations which contain needed to create a parser
     //and which contain sub-associations with additional data
      TiPa_Concrete::DataFellow* NewAssociation = TDA_GrmConcrete::Att.ContextModel->fellow_create();
                                                           // create new node
      NewAssociation->data_set(Data);                      // and associate it with the data
      destination->contractorLast_add(NewAssociation);     // add new node to destination tree
      collectKeyData(ContractorIn,NewAssociation);         // recursive continue of analysis

    }break;

    case Spirit185_Internal::CharacterID_rid:              // identifier of a character

    case Spirit185_Internal::KeyWordCharacterCount_rid:    // character sequence of a string");

    case Spirit185_Internal::Identifier_rid:               // identifying name of a user-rule

    case Spirit185_Internal::PrmAlnum_rid:                 // primitive parser: alpha numeric characters
    case Spirit185_Internal::PrmAlpha_rid:                 // primitive parser: alphabetic characters
    case Spirit185_Internal::PrmAnychar_rid:               // primitive parser: any charcter
    case Spirit185_Internal::PrmBlank_rid:                 // primitive parser: blank
    case Spirit185_Internal::PrmCntrl_rid:                 // primitive parser: control characters
    case Spirit185_Internal::PrmDigit_rid:                 // primitive parser: digits
    case Spirit185_Internal::PrmGraph_rid:                 // primitive parser: graphs
    case Spirit185_Internal::PrmLower_rid:                 // primitive parser: lower case characters
    case Spirit185_Internal::PrmPrint_rid:                 // primitive parser: printable characters
    case Spirit185_Internal::PrmPunct_rid:                 // primitive parser: punctuation
    case Spirit185_Internal::PrmSign_rid:                  // primitive parser: sign
    case Spirit185_Internal::PrmSpace_rid:                 // primitive parser: space
    case Spirit185_Internal::PrmUpper_rid:                 // primitive parser: upper case characters
    case Spirit185_Internal::PrmXdigit_rid:                // primitive parser: hexadecimal digits
    case Spirit185_Internal::PrmBin_rid:                   // primitive parser: binary digits
    case Spirit185_Internal::PrmHex_rid:                   // primitive parser: hexadecimal numbers
    case Spirit185_Internal::PrmOct_rid:                   // primitive parser: octal numbers
    case Spirit185_Internal::PrmEscape_rid:                // primitive parser: escape characters
    case Spirit185_Internal::PrmEol_rid:                   // primitive parser: end-of-line
    {
     //actions for associations which contain needed to create a parser
     //but which contain no sub-associations with additional data
      TiPa_Concrete::DataFellow* NewAssociation = TDA_GrmConcrete::Att.ContextModel->fellow_create();
                                                       // create new node
      NewAssociation->data_set(Data);                  // and associate it with the data
      destination->contractorLast_add(NewAssociation); // add new node to destination tree
    }break;
    default:
    {
     //actions for associations which don't contain needed to create a parser
     //but which contain sub-associations with needed data

     collectKeyData(ContractorIn,destination);         // recursive continue of analysis
    }break;

   }


  }
  else
  {
   LOG_OUTPUT(LOG_OFF, "data content of association node is not valid");
  }
  ContractorIn = ContractorIn->fellowBehind_get();
 }




 return(destination);
}


/* @MRTZ_describe defineRootRule

*/
TiPa_Rule* Spirit185_External::defineRootRule(const char* ruleName, unsigned int& ruleID)
{
 CREATE_PARSER(TiPa_Rule, Root, Spirit185_Internal::Root_rid, "text content to parse for");

 if(TDA_GrmConcrete::Att.ParserRule.find(ruleName) != TDA_GrmConcrete::Att.ParserRule.end())
 {
  LOG_OUTPUT(LOG_ON, string("Main Rule found : ") << ruleName);
  Root->contractor_ParserInsert(TDA_GrmConcrete::Att.ParserRule[ruleName]) ;

 }
 else
 {
  LOG_OUTPUT(LOG_ON, string("Main Rule not found : ") << ruleName);

  CREATE_USER_PARSER(TiPa_Character, PrmAnychar,
                     "__Prm_Anychar__", ruleID++,
                     "primitive : any character",
                     Mbr.GrammarTextIdentifier,-1);
  PrmAnychar->init(TiPa_Character::Anychar);           // all characters with an ordinal number between 1 and 255
  Root->contractor_ParserInsert(PrmAnychar) ;
 }

 return(Root);
}



/* @MRTZ_describe defineSkipRule

*/
TiPa_Rule* Spirit185_External::defineSkipRule(const char* ruleName, unsigned int& ruleID)
{
 CREATE_PARSER(TiPa_Rule, Skip, Spirit185_Internal::Skip_rid, "text content to ignore");

 if(TDA_GrmConcrete::Att.ParserRule.find(ruleName) != TDA_GrmConcrete::Att.ParserRule.end())
 {
  LOG_OUTPUT(LOG_ON, string("Skip Rule found : ") << ruleName);
  Skip->contractor_ParserInsert(TDA_GrmConcrete::Att.ParserRule[ruleName]) ;
 }
 else
 {
  LOG_OUTPUT(LOG_ON, string("Skip Rule not found : ") << ruleName);
  CREATE_USER_PARSER(TiPa_Character, PrmCntrl,
                     "__Prm_Cntrl__", ruleID++,
                     "primitive : control characters",
                     Mbr.GrammarTextIdentifier,-1);
  PrmCntrl->init(TiPa_Character::Cntrl);            // control-characters
  Skip->contractor_ParserInsert(PrmCntrl);
 }

 return(Skip);
}

/* @MRTZ_describe defineLineRule

*/
TiPa_Rule* Spirit185_External::defineLineRule(const char* ruleName, unsigned int& ruleID)
{
 CREATE_PARSER(TiPa_Rule, Line, 16, "text between two lines");

 if(TDA_GrmConcrete::Att.ParserRule.find(ruleName) != TDA_GrmConcrete::Att.ParserRule.end())
 {
  LOG_OUTPUT(LOG_OFF, string("Line Rule found : ") << ruleName);
  Line->contractor_ParserInsert(TDA_GrmConcrete::Att.ParserRule[ruleName]) ;
 }
 else
 {
  LOG_OUTPUT(LOG_OFF, string("Line Rule not found : ") << ruleName);

  CREATE_USER_PARSER(TiPa_Character, CR, "__Prm_CR__", ruleID++,
                      "character : carriage return",
                      Mbr.GrammarTextIdentifier,-1);
  CR->init(13);                                     // carriage return

  CREATE_USER_PARSER(TiPa_Character, LF, "__Prm_LF__", ruleID++,
                      "character : line feed",
                      Mbr.GrammarTextIdentifier,-1);
  LF->init(10);                                     // line feed

  CREATE_USER_PARSER(TiPa_Sequence, NL_MS, "__Prm_NL_MS__", ruleID++,
                      "character-sequence : new line for Microsoft",
                      Mbr.GrammarTextIdentifier,-1);
  NL_MS->init(TiPa_Sequence::Seq_HrdSq,CR, LF);     // new line for Microsoft

  CREATE_USER_PARSER(TiPa_Rule, NL_UNIX, "__Prm_NL_UNIX__", ruleID++,
                      "character : new line for Linux",
                      Mbr.GrammarTextIdentifier,-1);
  NL_UNIX->init(LF);    // new line for Unix or Linux

//  CREATE_USER_PARSER(TiPa_Counter, NL_MAC, "__Prm_NL_MAC__", ruleID++,
//                      "character : new line for Apple-Macintosh",
//                      Mbr.GrammarTextIdentifier,-1);
//  NL_MAC->init(TiPa_Counter::Cnt_OneOrMore,CR);     // new line for Apple-Macintosh
  CREATE_USER_PARSER(TiPa_Rule, NL_MAC, "__Prm_NL_MAC__", ruleID++,
                      "character : new line for Apple-Macintosh",
                      Mbr.GrammarTextIdentifier,-1);
  NL_MAC->init(CR);     // new line for Apple-Macintosh

  CREATE_USER_PARSER(TiPa_Condition, PrmEol, "__Prm_PrmEol__", ruleID++,
                      "primitive : new line for Microsoft ex-or Unix/Linux ex-or Apple-Macintosh",
                      Mbr.GrammarTextIdentifier,-1);
  PrmEol->init(TiPa_Condition::Cnd_OrExc, NL_MS, NL_UNIX);    // new line for Microsoft ex-or Unix/Linux
  PrmEol->contractor_ParserInsert(NL_MAC,2);                  // new line for Apple-Macintosh

  Line->contractor_ParserInsert(PrmEol);
 }

 return(Line);
}




/* @MRTZ_describe defineReservedRule

*/
TiPa_Rule* Spirit185_External::defineReservedRule(/*TiPa_Concrete* skip,*/ unsigned int& ruleID)
{
// TiPa_Rule* ReturnValue = nullptr;

 TiPa_Character*  AlnumReserved = dynamic_cast<TiPa_Character*>(createParser(TiPa_Character::id_Class(),
                                                                             "AlnumReserved",
                                                                             "AlnumReserved",
                                                                             ruleID++,
                                                                             "non-id character behind reserved word",
                                                                             Mbr.GrammarTextIdentifier,
                                                                             -1));
 AlnumReserved->init(TiPa_Character::Alnum);

 TiPa_Character*  UnderScoreReserved = dynamic_cast<TiPa_Character*>(createParser(TiPa_Character::id_Class(),
                                                                                  "UnderScoreReserved",
                                                                                  "UnderScoreReserved",
                                                                                  ruleID++,
                                                                                  "non-id character behind reserved word",
                                                                                  Mbr.GrammarTextIdentifier,
                                                                                  -1));
 UnderScoreReserved->init('_');

 TiPa_Condition* ConditionIdCharacter = dynamic_cast<TiPa_Condition*>(createParser(TiPa_Condition::id_Class(),
                                                                                   "ConditionIdCharacter",
                                                                                   "ConditionIdCharacter",
                                                                                   ruleID++,
                                                                                   "a collection of id characters",
                                                                                   Mbr.GrammarTextIdentifier,
                                                                                   -1));
 ConditionIdCharacter->init(TiPa_Condition::Cnd_OrInc, AlnumReserved, UnderScoreReserved);

 TiPa_Counter * NotIdCharacter = dynamic_cast<TiPa_Counter*>(createParser(TiPa_Counter::id_Class(),
                                                                                   "NonConditionIdCharacter",
                                                                                   "NonConditionIdCharacter",
                                                                                   ruleID++,
                                                                                   "a collection of non-id characters",
                                                                                   Mbr.GrammarTextIdentifier,
                                                                                   -1));
 NotIdCharacter->init(TiPa_Counter::Cnt_AllButNot,ConditionIdCharacter);


 TiPa_Condition* ConditionReserved = dynamic_cast<TiPa_Condition*>(createParser(TiPa_Condition::id_Class(),
                                                                                "ConditionReserved",
                                                                                "ConditionReserved",
                                                                                ruleID++,
                                                                                "a collection of reserved words",
                                                                                Mbr.GrammarTextIdentifier,
                                                                                -1));
 ConditionReserved->TiPa_Concrete::init((TiPa_Concrete::TiPa_ID)TiPa_Condition::Cnd_OrInc);

 TiPa_Sequence* SequenceReserved = dynamic_cast<TiPa_Sequence*>(createParser(TiPa_Sequence::id_Class(),
                                                                             "SequenceReserved",
                                                                             "SequenceReserved",
                                                                             ruleID++,
                                                                             "reserved word followed by a white space",
                                                                             Mbr.GrammarTextIdentifier,
                                                                             -1));

 SequenceReserved->init(TiPa_Sequence::Seq_HrdSq, ConditionReserved, NotIdCharacter);

 TiPa_Rule* ReturnValue = dynamic_cast<TiPa_Rule*>(createParser(TiPa_Rule::id_Class(),
                                                                "reserved",
                                                                "reserved",
                                                                ruleID++,
                                                                "a rule to detect reserved words",
                                                                Mbr.GrammarTextIdentifier,
                                                                -1));

 ReturnValue->init(SequenceReserved);


 return(ReturnValue);
}




/* @MRTZ_describe ogRawResult

*/
void Spirit185_External::setLogFile(const char* folder)
{
 if(Log.File != nullptr)
  delete[](Log.File);                               // delete old file-string
 if(Log.Path != nullptr)
  delete[](Log.Path);                               // delete old file-path
 if(Log.Name != nullptr)
  delete[](Log.Name);                               // delete old file-name
 if(Log.Attachment != nullptr)
  delete[](Log.Attachment);                         // delete old file-name



 if(folder != nullptr)                              // given folder is valid
 {
  Log.File = new char[strlen(folder)+1];            // allocate new memory
  strcpy(Log.File,folder);                          // copy given string
  Log.File[strlen(folder)] = 0;                     // ensure termination of string

  Log.Path_end = nullptr;                           // initialize as not existing
  char* Position = strchr(Log.File,'/');            // search for folder-separator used in Linux and MAC-OS
  while(Position != nullptr)                        // search for last one
  {
   Log.Path_end=Position;                           // store last positive search-result
   Position = strchr(Position+1 ,'/');              // new search may result in nullptr
  }

  if(Log.Path_end == nullptr)                        // no Linux or MAC-OS separator found
  {
   Position = strchr(Log.File,'\\');                // search for folder-separator used in Windows
   while(Position!=nullptr)                         // search for last one
   {
    Log.Path_end=Position;                          // store last positive search-result
    Position = strchr(Position +1 ,'\\');           // new search may result in nullptr
   }
  }

  Log.Name_end = nullptr;                            // initialize as not existing
  Position = strchr(Log.File,'.');                   // search for common attachment-separator
  while(Position!=nullptr)                           // search for last one
  {
   Log.Name_end=Position;                            // store last positive search-result
   Position = strchr(Position + 1,'.');              // new search may result in nullptr
  }

  if(Log.Path_end !=nullptr)                         // path separator found
  {
   int Size = Log.Path_end - Log.File +1;            // size of string to copy
   Log.Path = new char[Size + 1];                    // allocate new memory
   memcpy(Log.Path,Log.File,Size);                  // copy given string
   Log.Path[Size] = 0;                               // ensure termination of string
   Position = Log.Path_end + 1;                      // position of name-begin
 }
  else
  {
   Log.Path = nullptr;                               // initialize as not existing
   Position = Log.File;                              // position of name-begin
  }

  if(Log.Name_end !=nullptr)                         // attachment separator found
  {
   int Size = Log.Name_end - Position;               // size of string to copy
   Log.Name = new char[Size + 1];                    // allocate new memory
   memcpy(Log.Name,Position,Size);                  // copy given string
   Log.Name[Size] = 0;                               // ensure termination of string
  }
  else
  {
   int Size = strlen(Log.File)-(Position-Log.File);  // size of string to copy
   Log.Name = new char[Size + 1];                    // allocate new memory
   memcpy(Log.Name,Position,Size);                  // copy given string
   Log.Name[Size] = 0;                               // ensure termination of string
  }

//  cout << "Log.Name : " << Log.Name << endl;


  if(Log.Name_end !=nullptr)                         // attachment separator found
  {
   int Size = strlen(Log.Name_end + 1);              // size of string to copy
   Log.Attachment = new char[Size + 1];              // allocate new memory
   strcpy(Log.Attachment,Log.Name_end+1);            // copy given string
   Log.Attachment[Size] = 0;                         // ensure termination of string
 }
  else
  {
   Log.Attachment = nullptr;                         // initialize as not existing
  }

 }
 else
 {
  Log.File       = nullptr;                          // initialize as not existing
  Log.Path       = nullptr;                          // initialize as not existing
  Log.Name       = nullptr;                          // initialize as not existing
  Log.Attachment = nullptr;                          // initialize as not existing
  Log.Path_end   = nullptr;                          // initialize as not existing
  Log.Name_end   = nullptr;                          // initialize as not existing
 }

}


/* @MRTZ_describe logRawResult

*/
void Spirit185_External::logRawResult(const char* text, int indent, bool newLine)
{
 if(Log.File != nullptr)
 {
  if(text != EMPTYLOG)
   Log.Text << text;

  if     (indent > 0)               // increase indention
  {
   Log.IndentOffset.push_back(indent);
   Log.Indent = Log.Indent + (*(Log.IndentOffset.rbegin()));
  }
  else if(indent < 0)               // decrease indention
  {
   if(!(Log.IndentOffset.empty()))  // valid use
   {
    Log.Indent = Log.Indent - (*(Log.IndentOffset.rbegin()));
    Log.IndentOffset.pop_back();
   }
  }
  else //(indent == 0)                 keep indention
  {
   // keep current indention
  }


  if(newLine == true)
  {
   Log.Text << endl;
   for(int Count = 0; Count < Log.Indent; ++ Count)
     Log.Text << ' ';
  }
  else
  {
   // do nothing more
  }

 }
}





#ifndef DOXYGEN
#define USING_NAMESPACE using namespace
//}; USING_NAMESPACE CL_SPIRIT185;
//}; USING_NAMESPACE CL_TDA_GRMCONCRETE;
//}; USING_NAMESPACE TDA_Grammar;
//}; USING_NAMESPACE TXTDIASM;
#undef  USING_NAMESPACE
#endif //DOXYGEN



