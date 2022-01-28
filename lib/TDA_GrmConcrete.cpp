/*!

 @file
 @brief definitions of an concrete grammar-class as template
         to manage tiny parser classes and their extensions

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
    10.05.2015     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    10.05.2015...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/

#define DEBUG_OUTPUT_LOG
#include "TDA_GrmConcrete.h"


 #include <ctime>





/* @MRTZ_describe TDA_GrmConcrete

*/
 TDA_GrmConcrete::TDA_GrmConcrete(TiPa_Concrete::DataModel* contextModel, bool debugMode)
 {
  Att.MainParser     = nullptr;                                          // parser used to start main parsing process with
  Att.SkipParser     = nullptr;                                          // parser used to define those text-parts to ignore while parsing
  Att.LineParser     = nullptr;                                          // parser used to identify the begin of a new line

  Att.DebugMode      = debugMode;
  Att.LineCurrent    = Att.LineBegin.begin();

  Att.LineBegin.clear();                                                 // all positions of line-begins
  Att.LineNumber.clear();                                                // contains the number of the newline begins
  Att.TextBegin  = nullptr;                                              // store text-begin
  Att.TextEnd    = nullptr;                                              // store text-end

  Att.ContextModel = contextModel;

//  LOG_OUTPUT(LOG_OFF, "TDA_GrmConcrete(bool debugMode)");

 }







/* @MRTZ_describe ~TDA_GrmConcrete

*/
 TDA_GrmConcrete::~TDA_GrmConcrete(void)
 {

  LOG_OUTPUT(LOG_OFF, "~TDA_GrmConcrete(void) start");
  init();

  map<string,TiPa_Character*>::iterator CurrentCharacter = Att.ParserCharacter.begin();
  while(CurrentCharacter != Att.ParserCharacter.end())
  {
   LOG_OUTPUT(LOG_OFF, string("del ") + CurrentCharacter->first);
   delete(CurrentCharacter->second);
   CurrentCharacter->second = nullptr;
   ++ CurrentCharacter;
  }
  Att.ParserCharacter.clear();
  LOG_OUTPUT(LOG_OFF, "~TDA_GrmConcrete(void) CurrentCharacter ready");

  map<string,TiPa_String*>::iterator CurrentString = Att.ParserString.begin();
  while(CurrentString != Att.ParserString.end())
  {
   LOG_OUTPUT(LOG_OFF, string("del ") + CurrentString->first);
   delete(CurrentString->second);
   CurrentString->second = nullptr;
   ++ CurrentString;
  }
  Att.ParserString.clear();
  LOG_OUTPUT(LOG_OFF, "~TDA_GrmConcrete(void) CurrentString ready");

  map<string,TiPa_Counter*>::iterator CurrentCounter = Att.ParserCounter.begin();
  while(CurrentCounter != Att.ParserCounter.end())
  {
   LOG_OUTPUT(LOG_OFF, string("del ") + CurrentCounter->first);
   delete(CurrentCounter->second);
   CurrentCounter->second = nullptr;
   ++ CurrentCounter;
  }
  Att.ParserCounter.clear();
  LOG_OUTPUT(LOG_OFF, "~TDA_GrmConcrete(void) CurrentCounter ready");

  map<string,TiPa_Sequence*>::iterator CurrentSequence = Att.ParserSequence.begin();
  while(CurrentSequence != Att.ParserSequence.end())
  {
   LOG_OUTPUT(LOG_OFF, string("del ") + CurrentSequence->first);
   delete(CurrentSequence->second);
   CurrentSequence->second = nullptr;
   ++ CurrentSequence;
  }
  Att.ParserSequence.clear();
  LOG_OUTPUT(LOG_OFF, "~TDA_GrmConcrete(void) CurrentSequence ready");

  map<string,TiPa_Condition*>::iterator CurrentCondition = Att.ParserCondition.begin();
  while(CurrentCondition != Att.ParserCondition.end())
  {
   LOG_OUTPUT(LOG_OFF, string("del ") + CurrentCondition->first);
   delete(CurrentCondition->second);
   CurrentCondition->second = nullptr;
   ++ CurrentCondition;
  }
  Att.ParserCondition.clear();
  LOG_OUTPUT(LOG_OFF, "~TDA_GrmConcrete(void) CurrentCondition ready");

  map<string,TiPa_Rule*>::iterator CurrentRule = Att.ParserRule.begin();
  while(CurrentRule != Att.ParserRule.end())
  {
   LOG_OUTPUT(LOG_OFF, string("del ") + CurrentRule->first);

   delete(CurrentRule->second);
   CurrentRule->second = nullptr;

   ++ CurrentRule;
  }
  Att.ParserRule.clear();
  LOG_OUTPUT(LOG_OFF, "~TDA_GrmConcrete(void) CurrentRule ready");


  Att.MainParser   = nullptr;                                            // parser used to start main parsing process with
  Att.SkipParser   = nullptr;                                            // parser used to define those text-parts to ignore while parsing
  Att.LineParser   = nullptr;                                            // parser used to identify the begin of a new line
  Att.Property.clear();


  Att.LineCurrent  = Att.LineBegin.begin();

  Att.LineBegin.clear();                                                 // all positions of line-begins
  Att.LineNumber.clear();                                                // contains the number of the newline begins
  Att.TextBegin  = nullptr;                                              // store text-begin
  Att.TextEnd    = nullptr;                                              // store text-end




  LOG_OUTPUT(LOG_OFF, "~TDA_GrmConcrete(void) end");
 }





/* @MRTZ_describe init

*/
 void TDA_GrmConcrete::init(void)
 {
  map<string,TiPa_Character*>::iterator   CurrentCharacter;   ///< character parser
  map<string,TiPa_String*>::iterator      CurrentString;      ///< string parser
  map<string,TiPa_Counter*>::iterator     CurrentCounter;     ///< counter parser
  map<string,TiPa_Sequence*>::iterator    CurrentSequence;    ///< conditional parser
  map<string,TiPa_Condition*>::iterator   CurrentCondition;   ///< sequence parser
  map<string,TiPa_Rule*>::iterator        CurrentRule;        ///< language specific rules defined by user

  map<TiPa_Concrete*, ParserDebugData_TP>::iterator CurrentParserDebugData;   ///< data-base used to store debug data around a parser



  LOG_OUTPUT(LOG_OFF, "TDA_GrmConcrete::init(void) start");


  CurrentCharacter = Att.ParserCharacter.begin();
  while(CurrentCharacter != Att.ParserCharacter.end())
  {
   LOG_OUTPUT(LOG_OFF, string("result_clear ") + CurrentCharacter->first);
   CurrentCharacter->second->result_clear();

   ++ CurrentCharacter;
  }
  LOG_OUTPUT(LOG_OFF, "TDA_GrmConcrete::init(void) CurrentCharacter ready");

  CurrentString = Att.ParserString.begin();
  while(CurrentString != Att.ParserString.end())
  {
   LOG_OUTPUT(LOG_OFF, string("result_clear ") + CurrentString->first);
   CurrentString->second->result_clear();
   ++ CurrentString;
  }
  LOG_OUTPUT(LOG_OFF, "TDA_GrmConcrete::init(void) CurrentString ready");

  CurrentCounter = Att.ParserCounter.begin();
  while(CurrentCounter != Att.ParserCounter.end())
  {
   LOG_OUTPUT(LOG_OFF, string("result_clear ") + CurrentCounter->first);
   CurrentCounter->second->result_clear();
   ++ CurrentCounter;
  }
  LOG_OUTPUT(LOG_OFF, "TDA_GrmConcrete::init(void) CurrentCounter ready");

  CurrentSequence = Att.ParserSequence.begin();
  while(CurrentSequence != Att.ParserSequence.end())
  {
   LOG_OUTPUT(LOG_OFF, string("result_clear ") + CurrentSequence->first);
   CurrentSequence->second->result_clear();
   ++ CurrentSequence;
  }
  LOG_OUTPUT(LOG_OFF, "TDA_GrmConcrete::init(void) CurrentSequence ready");

  CurrentCondition = Att.ParserCondition.begin();
  while(CurrentCondition != Att.ParserCondition.end())
  {
   LOG_OUTPUT(LOG_OFF, string("result_clear ") + CurrentCondition->first);
   CurrentCondition->second->result_clear();
   ++ CurrentCondition;
  }
  LOG_OUTPUT(LOG_OFF, "TDA_GrmConcrete::init(void) CurrentCondition ready");

  CurrentRule = Att.ParserRule.begin();
  while(CurrentRule != Att.ParserRule.end())
  {
   LOG_OUTPUT(LOG_OFF, string("result_clear ") + CurrentRule->first);
   CurrentRule->second->result_clear();
   ++ CurrentRule;
  }
  LOG_OUTPUT(LOG_OFF, "TDA_GrmConcrete::init(void) CurrentRule ready");


  CurrentParserDebugData = Att.ParserDebugData.begin();
  while(CurrentParserDebugData != Att.ParserDebugData.end())
  {
   delete[](CurrentParserDebugData->second.FileName);
   ++ CurrentParserDebugData;
  }
  Att.ParserDebugData.clear();
  LOG_OUTPUT(LOG_OFF, "TDA_GrmConcrete::init(void) CurrentParserDebugData ready");

  Att.LineCurrent  = Att.LineBegin.begin();
 }







/* @MRTZ_describe createParser

   @MRTZ_describe store_properties

*/
TiPa_Concrete* TDA_GrmConcrete::createParser(TiPa_Concrete::TDA_TiPa_CLASS_TP classType,
                                             const char*                      internName,
                                             const char*                      userName,
                                             int                              id,
                                             const char*                      description,
                                             const char*                      fileName,
                                             int                              lineNumber)
{
 TiPa_Concrete*    ReturnValue = nullptr;
 bool              AlreadyExisting = false; // will be set true if the parser-type specific

 switch(classType)
 {
  case TiPa_Concrete::TDA_TiPa_Character:
  {
   if(Att.ParserCharacter.find(internName) == Att.ParserCharacter.end())
   {
    Att.ParserCharacter[internName] = new TiPa_Character(Att.ContextModel);
   }
   else
   {
    AlreadyExisting = true;
   }
    ReturnValue     = Att.ParserCharacter[internName];
  }break;
  case TiPa_Concrete::TDA_TiPa_String:
  {
   if(Att.ParserString.find(internName) == Att.ParserString.end())
   {
    Att.ParserString[internName] = new TiPa_String(Att.ContextModel);
   }
   else
   {
    AlreadyExisting = true;
   }
    ReturnValue     = Att.ParserString[internName];
  }break;
  case TiPa_Concrete::TDA_TiPa_Counter:
  {
   if(Att.ParserCounter.find(internName) == Att.ParserCounter.end())
   {
    Att.ParserCounter[internName] = new TiPa_Counter(Att.ContextModel);
   }
   else
   {
    AlreadyExisting = true;
   }
    ReturnValue     = Att.ParserCounter[internName];
  }break;
  case TiPa_Concrete::TDA_TiPa_Sequence:
  {
   if(Att.ParserSequence.find(internName) == Att.ParserSequence.end())
   {
    Att.ParserSequence[internName] = new TiPa_Sequence(Att.ContextModel);
   }
   else
   {
    AlreadyExisting = true;
   }
    ReturnValue     = Att.ParserSequence[internName];
  }break;
  case TiPa_Concrete::TDA_TiPa_Condition:
  {
   if(Att.ParserCondition.find(internName) == Att.ParserCondition.end())
   {
    Att.ParserCondition[internName] = new TiPa_Condition(Att.ContextModel);
   }
   else
   {
    AlreadyExisting = true;
   }
    ReturnValue     = Att.ParserCondition[internName];
  }break;
  case TiPa_Concrete::TDA_TiPa_Rule:
  {
   if(Att.ParserRule.find(internName) == Att.ParserRule.end())
   {
    Att.ParserRule[internName] = new TiPa_Rule(internName,Att.ContextModel);
   }
   else
   {
    AlreadyExisting = true;
   }
    ReturnValue     = Att.ParserRule[internName];
  }break;
  case TiPa_Concrete::TDA_TiPa_Concrete:
  default:
  {
   ReturnValue = nullptr;
  }break;
 }

 if(AlreadyExisting == false)                              // parser is new
 {
  if(ReturnValue != nullptr)                               // parser is valid
  {
// @MRTZ_exclude store_properties
// @MRTZ_beginBlock
   Property_TP Property;

   Property.Name = new char[strlen(userName)+1];           // prepare new memory
   strcpy(Property.Name, userName);                        // copy user-name
   Property.Name[strlen(userName)] = 0;                    // ensure definition on string end

   Property.Description = new char[strlen(description)+1]; // prepare new memory
   strcpy(Property.Description, description);              // copy description
   Property.Description[strlen(description)] = 0;          // ensure definition on string end

   Property.User_ID = id;                                  // copy id
   Property.User_ID_String = nullptr;                      // prepare new memory
   TiPa_Data::itoa(&Property.User_ID_String,id);           // convert id to string

   Att.Property[ReturnValue]      = Property;
// @MRTZ_endBlock

   if(Att.DebugMode != false)                             // grammar should be debugged
   {
    Att.ParserDebugData[ReturnValue].FileName = new char[strlen(fileName)+1];
    strcpy(Att.ParserDebugData[ReturnValue].FileName,fileName);
    Att.ParserDebugData[ReturnValue].FileName[strlen(fileName)] = 0;

    Att.ParserDebugData[ReturnValue].LineNumber = lineNumber;

   }
   else // grammar should not be debugged
   {
    // without debug-mode storing some source information makes no sense
   }
  }
  else // parser was not defined correctly
  {
   // here an error-message may be outputted later since the required parser-type is not existing
  }
 }
 else // parser with the same name was already existing in the parser-type specific data-base
 {
  if(  (Att.DebugMode                               != false)
     &&(Att.ParserDebugData[ReturnValue].LineNumber == -1)
    )                                                                        // occurs if parser was used before its definition
  {
   Att.ParserDebugData[ReturnValue].LineNumber = lineNumber;                 // lineNumber should be positive while parser-definition
  }

  if(  (Att.Property[ReturnValue].User_ID == -1)
     &&(                               id != -1)
    )                                                                        // occurs if parser was used before its definition
  {
   if(Att.Property[ReturnValue].Description != nullptr)
    delete[](Att.Property[ReturnValue].Description);
   Att.Property[ReturnValue].Description = new char[strlen(description)+1]; // prepare new memory
   strcpy(Att.Property[ReturnValue].Description, description);              // copy description
   Att.Property[ReturnValue].Description[strlen(description)] = 0;          // ensure definition on string end

   Att.Property[ReturnValue].User_ID = id;                                  // copy id
   if(Att.Property[ReturnValue].User_ID_String!=nullptr)
    delete[](Att.Property[ReturnValue].User_ID_String);
   Att.Property[ReturnValue].User_ID_String = nullptr;                      // prepare new memory
   TiPa_Data::itoa(&Att.Property[ReturnValue].User_ID_String,id);           // convert id to string
  }


  // here an warning-message may be outputted later since the parser-name was already existing in the data-base
 }

 return(ReturnValue);
}













/* @MRTZ_describe parse

*/
const char * TDA_GrmConcrete::parse(const char* begin,
                                    const char* end,
                                    const char* rule)
{
 init();              // clear old results


 if(rule == nullptr)  // main-parser should ne used
 {
  return(Att.MainParser->parser_Test(begin,end));
 }
 else if (Att.ParserRule.find(rule)!=Att.ParserRule.end())
                      // special rule should be used
 {
  return(Att.ParserRule[rule]->parser_Test(begin,end));
 }
 else                 // special rule to use is not defined
 {
  return(nullptr);
 }

}





/* @MRTZ_describe parse

*/
const char * TDA_GrmConcrete::scan(const char* begin,
                                   const char* end,
                                   const char* rule)
{
 init();              // clear old results

 if(rule == nullptr)  // main-parser should ne used
 {
  return(Att.MainParser->parser_Scan(begin, end, TiPa_Concrete::SequentialScan));
 }
 else if (Att.ParserRule.find(rule)!=Att.ParserRule.end())
                      // special rule should be used
 {
  return(Att.ParserRule[rule]->parser_Scan(begin, end, TiPa_Concrete::SequentialScan));
 }
 else                 // special rule to use is not defined
 {
  cout << endl << "TDA_GrmConcrete::scan rule (" << rule << ") not found!" << endl << string(begin,end) << endl;
  return(nullptr);
 }
}

/* @MRTZ_describe text

*/
char* TDA_GrmConcrete::text(char*       textBuffer,
                            int         size,
                            const char* begin,
                            const char* rule)
{
 if(rule == nullptr)  // main-parser should ne used
  return(Att.MainParser->result_Text(textBuffer, size, begin));
 else if (Att.ParserRule.find(rule)!=Att.ParserRule.end())
                      // special rule should be used
  return(Att.ParserRule[rule]->result_Text(textBuffer, size, begin));
 else                 // special rule to use is not defined
  return(nullptr);
}





/* @MRTZ_describe scanData

*/
TiPa_Concrete::DataFellow* TDA_GrmConcrete::scanData(const char* rule)
{
 TiPa_Concrete::DataFellow*                          ReturnValue = nullptr;

 map<const char*, TiPa_Concrete::Hit_TP >* ScanResult  = nullptr;
 if(rule == nullptr)  // main-parser should ne used
  ScanResult = Att.MainParser->result_Dictionary();

 else if (Att.ParserRule.find(rule)!=Att.ParserRule.end())
                      // special rule should be used
  ScanResult = Att.ParserRule[rule]->result_Dictionary();
 else                 // special rule to use is not defined
  ScanResult = nullptr;


 if(ScanResult != nullptr)
 {
  TiPa_Data* ParserData = TDA_GrmConcrete::Att.ContextModel->data_create();
             ParserData->Begin        = nullptr;
             ParserData->End          = nullptr;
             ParserData->UserID       = -1;
             ParserData->ParserClass  = TiPa_Concrete::TDA_TiPa_Concrete;
  ReturnValue = TDA_GrmConcrete::Att.ContextModel->fellow_create(ParserData);

  map<const char*, TiPa_Concrete::Hit_TP >::iterator Hit = ScanResult->begin();

  while(Hit != ScanResult->end())
  {
   ReturnValue->contractorLast_add(treeData(Hit->first,rule) );
   ++Hit;
  }

 }

 return(ReturnValue);
}





/* @MRTZ_describe treeData

*/
TiPa_Concrete::DataFellow* TDA_GrmConcrete::treeData(const char* begin,
                                                     const char* rule)
{
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"TDA_GrmConcrete::treeData : enter" <<endl;
 TiPa_Concrete::DataFellow*            ReturnValue = nullptr;
 TiPa_Concrete::Hit_TP*                ParserTree  = nullptr;

#if defined(DEBUG_OUTPUT)
 clock_t             Time            =  clock()/CLOCKS_PER_SEC;
 clock_t             SubTime         =  0;
#endif //DEBUG_OUTPUT

// LOG_OUTPUT(LOG_OFF, "read Att.MainParser->result_Tree");

#if defined(DEBUG_OUTPUT)
   SubTime         = clock()/CLOCKS_PER_SEC;
#endif //DEBUG_OUTPUT

 if(rule == nullptr)  // main-parser should ne used
 {
 // cout << "Att.MainParser" << endl;
  ParserTree = Att.MainParser->result_Tree(begin);
 }
 else if (Att.ParserRule.find(rule)!=Att.ParserRule.end())      // special rule should be used
 {
//  cout << "rule : " << rule << endl;
  ParserTree = Att.ParserRule[rule]->result_Tree(begin);
 }
 else                 // special rule to use is not defined
 {
//  cout << "rule : " << rule << " not found" << endl;
  ParserTree = nullptr;
 }
#if defined(DEBUG_OUTPUT)
  cout << "-result_Tree(" << ((clock()/CLOCKS_PER_SEC)-SubTime) << " sec)-" << endl;
#endif //DEBUG_OUTPUT


 if(ParserTree != nullptr)
 {
#if defined(DEBUG_OUTPUT)
  SubTime         = clock()/CLOCKS_PER_SEC;
#endif //DEBUG_OUTPUT
  TiPa_Data* ParserData = TDA_GrmConcrete::Att.ContextModel->data_create();
             ParserData->Begin        = ParserTree->Begin;
             ParserData->End          = ParserTree->End;
             ParserData->Parser       = ParserTree->Parser;

  ReturnValue = Att.ContextModel->fellow_create(ParserData);

#if defined(DEBUG_OUTPUT)
  cout << "-new TiPa_Concrete::DataFellow(" << ((clock()/CLOCKS_PER_SEC)-SubTime) << " sec)-" << endl;
#endif //DEBUG_OUTPUT


#if defined(DEBUG_OUTPUT)
  SubTime         = clock()/CLOCKS_PER_SEC;
#endif //DEBUG_OUTPUT

  TiPa_Concrete* Parser   = ParserData->Parser->as_TiPa_Concrete();
  ParserData->UserID      = Att.Property[Parser].User_ID;
  ParserData->ParserClass = Parser->id_Type();

  attributes(ParserData, Parser, ParserData->Begin);

  map<const char*, TiPa_Abstract*>::iterator SubResult = ParserTree->SubParser.begin();               //dictionary of the sub-parsers which were used to identify the found text-part
  while(SubResult != ParserTree->SubParser.end())
  {
   TiPa_Abstract*         SupParser     = SubResult->second;
   const char*            SupSnippet    = SubResult->first;

   TiPa_Concrete::Hit_TP* SubParserTree = SupParser->as_TiPa_Concrete()->result_Tree(SupSnippet);

   TiPa_Concrete::DataAssociation*  Contractor = Att.ContextModel->fellow_create();
   if(SubParserTree != nullptr)
    treeDataSub(Contractor, SubParserTree);

   ReturnValue->contractorLast_add(Contractor);
   ++ SubResult;
  }
#if defined(DEBUG_OUTPUT)
  cout << "-treeDataSub(" << ((clock()/CLOCKS_PER_SEC)-SubTime) << " sec)-" << endl;
#endif //DEBUG_OUTPUT
 }
 else
 {
  LOG_OUTPUT(LOG_OFF, "no main result found");
  TiPa_Data*  ParserData  = TDA_GrmConcrete::Att.ContextModel->data_create();
  ParserData->Begin       = nullptr;
  ParserData->End         = nullptr;
  ParserData->UserID      = -1;
  ParserData->ParserClass = TiPa_Concrete::TDA_TiPa_Concrete;

  ReturnValue = TDA_GrmConcrete::Att.ContextModel->fellow_create(ParserData);
 }

#if defined(DEBUG_OUTPUT)
 cout << "-treeData(" << ((clock()/CLOCKS_PER_SEC)-Time) << " sec)-" << endl;
#endif //DEBUG_OUTPUT

//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"TDA_GrmConcrete::treeData : leave" <<endl;
 return(ReturnValue);
}









/* @MRTZ_describe treeDataSub

*/
void TDA_GrmConcrete::treeDataSub(TiPa_Concrete::DataAssociation* sponsor,
                                  TiPa_Concrete::Hit_TP*          parserTree)
{
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"TDA_GrmConcrete::treeDataSub : enter" <<endl;

#if defined(DEBUG_OUTPUT)
 static int Counter = 0;

 ++ Counter;
 cout << "Counter(treeDataSub) : " << Counter << endl;
#endif //DEBUG_OUTPUT

// try
// {
  TiPa_Data* ParserData         = TDA_GrmConcrete::Att.ContextModel->data_create();
  sponsor->data_set(ParserData);
  ParserData->Begin  = parserTree->Begin;
  ParserData->End    = parserTree->End;
  ParserData->Parser = parserTree->Parser;

  if((ParserData->Parser != nullptr) &&(ParserData->Begin != nullptr))
  {
   ParserData->UserID      = Att.Property[ParserData->Parser->as_TiPa_Concrete()].User_ID;
   ParserData->ParserClass = (ParserData->Parser)->id_Type();

   attributes(ParserData, ParserData->Parser->as_TiPa_Concrete(), ParserData->Begin);

   map<const char*, TiPa_Abstract*>::iterator SubResult = parserTree->SubParser.begin();               //dictionary of the sub-parsers which were used to identify the found text-part
   while(SubResult != parserTree->SubParser.end())
   {
    TiPa_Abstract*         SupParser     = SubResult->second;
    const char*            SupSnippet    = SubResult->first;
    if((SupParser != nullptr) &&(SupSnippet != nullptr))
    {
//     try
//     {
        TiPa_Concrete::DataAssociation*  Contractor    = Att.ContextModel->fellow_create();
        TiPa_Concrete::Hit_TP*           SubParserTree = SupParser->as_TiPa_Concrete()->result_Tree(SupSnippet);

        if(SubParserTree != nullptr)
         treeDataSub(Contractor,SubParserTree);

        sponsor->contractorLast_add(Contractor);
//     }
//     catch (const std::bad_alloc& e)
//     {
//      cout<<__FILE__<<":"<<__LINE__<<":0: "<<"TDA_GrmConcrete::treeDataSub :" <<endl;
//      cout<<  "failed to create new contractor" <<endl<<endl;
////      Att.ContextModel->outputSize();
//      cout<<endl<<endl;
//     }
    }
    ++ SubResult;
   }
  }
// }
// catch (const std::bad_alloc& e)
// {
//  cout<<__FILE__<<":"<<__LINE__<<":0: "<<"TDA_GrmConcrete::treeDataSub :" <<endl;
//  cout<<  "failed to create new data" <<endl<<endl;
////  Att.ContextModel->outputSize();
//  cout<<endl<<endl;
// }
#if defined(DEBUG_OUTPUT)
 --Counter;
#endif //DEBUG_OUTPUT
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"TDA_GrmConcrete::treeDataSub : leave" <<endl;
}






/* @MRTZ_describe attributes
      to enable a consistent delete strategy
       attribute values individual are always individual data,
       while attribute identifiers are always central constants
   @MRTZ_describe Pre_Parsing_Results
    add character specific attributes here by using the content of the new line-parser

*/
void TDA_GrmConcrete::attributes(TiPa_Data* returnValue ,TiPa_Concrete* parser, const char* character)
{
// if ((character != nullptr)&&(strlen(character)>100000))
//  cout/*<<__FILE__<<":"*/<<__LINE__<<":-: ";

 if(Att.Property.find(parser) != Att.Property.end())
 {
  Property_TP Property = Att.Property[parser];
  returnValue->userName_set(Property.Name);
//  returnValue->userName_set((char*) returnValue->secondaryData_add("UserName", Property.Name));
  returnValue->user_ID_String_set(Property.User_ID_String);
  returnValue->userDescription_set(Property.Description);
 }

 // @MRTZ_exclude Pre_Parsing_Results
 if(!( Att.LineNumber.empty()))
 {
  int                          TextLine      = -1;
  int                          TextColumn    = -1;
//  char*                        StringL       = nullptr;
//  char*                        StringC       = nullptr;

  getPosition(&TextLine, &TextColumn, character);               // evaluate pre parser-results

//  TiPa_Data::itoa(&StringL, TextLine);                          // convert line-number of given character into a string
  returnValue->lineSet(TextLine);// = StringL;                                  // value  of the line-number attribute
//  TiPa_Data::itoa(&StringC, TextColumn);                        // convert column-number of given character into a string
  returnValue->columnSet(TextColumn);// = StringC;                                // value  of the column-number attribute
 }
// if ((character != nullptr)&&(strlen(character)>100000))
//  cout/*<<__FILE__<<":"*/<<__LINE__<<":-: ";

}
















/* @MRTZ_describe getPosition

    call the new-line parser to find all line-changes and evaluate its result to
    create a list of all new line locations inside the text defined by the given begin and end
*/
void TDA_GrmConcrete::pre_parse(const char* begin, const char* end)
{
// map<const char*,TiPa_Concrete::DataSponsor* >*          Result      = nullptr;  //whole parser-Result
// map<const char*,TiPa_Concrete::DataSponsor* >::iterator Current;                //single parser-result
 map<const char*,TiPa_Concrete::Hit_TP >*          Result      = nullptr;  //whole parser-Result
 map<const char*,TiPa_Concrete::Hit_TP >::iterator Current;                //single parser-result
 list<const char*>::iterator                       LineBegin;              //single line-begin
// int                                               LineNumber  = 0;        //counting index
 const char*                                       BeginBefore = nullptr;  //temporary store of line begin

 Att.LineBegin.clear();                                                 // ensure that the order is correct
 Att.LineCurrent = Att.LineBegin.begin();                               // initialise line to evaluate
 Att.LineNumber.clear();                                                // first character of text is first character of first line
 Att.TextBegin   = nullptr;                                             // store text-begin
 Att.TextEnd     = nullptr;                                             // store text-end

 if(Att.LineParser != nullptr)
 {
  Att.TextBegin     = begin;                                             // store text-begin
  Att.TextEnd       = end;
  Att.LineParser->result_clear();                                        // store text-end
  Att.LineParser->parser_Scan(Att.TextBegin,
                              Att.TextEnd,
                              TiPa_Concrete::SequentialScan);            // pre-parsing for later line-change analysis

  Att.LineBegin.push_back(begin);                                        // begin of text is begin of first line
  BeginBefore = begin;                                                   // to store later end of the first line
  Result  = Att.LineParser->result_Dictionary();                         // get parser result
  Current = Result->begin();                                             // first line-change
  while(Current != Result->end())                                        // until last line-change is processed
  {
   Att.LineEnd[BeginBefore] = Current->second.Begin;        // begin of line-change is end of line detected before
   Att.LineBegin.push_back(Current->second.End);            // store character behind line-change as first character in new line
   BeginBefore              = Current->second.End;          // to store later end of this line
   ++ Current;                                                           // next detected line-change
  }
  Att.LineEnd[BeginBefore] = end;                                        // end of parsed text is end of last line

  Att.LineBegin.sort();                                                  // ensure that the order is correct

  int LineNumber                = 0;                                     //counting index
  Att.LineNumber[Att.TextBegin] = LineNumber;                            // first character of text is first character of first line

  LineBegin = Att.LineBegin.begin();                                     // first line-change
  while(LineBegin != Att.LineBegin.end())                                // until last line-change is processed
  {
   ++ LineNumber;                                                         // define next line-number
   Att.LineNumber[*LineBegin] = LineNumber;                               // store line-number under its first character-position
//   cout << LineNumber << "|" << string(*LineBegin,*LineBegin+10) << "|" << endl;
   ++ LineBegin;                                                          // next detected line-change
  }
  Att.LineCurrent = Att.LineBegin.begin();                                    // initialise line to evaluate
 }
 else
 {
  cout << "line-parser is not defined !" << endl;
 }


}









/* @MRTZ_describe getPosition

*/
void TDA_GrmConcrete::getPosition(int* line, int* column, const char* character, int tabSize)
{
// static list<const char*>::iterator  LineBegin;             //single line-begin
 int                                 ColumnNumber   = 0;    //counting index
 const char*                         LineCharacter  = nullptr; //iterates through the line

 if(  (character <  Att.TextBegin)
    ||(character >= Att.TextEnd)
   )  //character is not part of the analysed Text
 {
  (*line)   = -1;                                               //invalid line-number
  (*column) = -1;                                               //invalid column-number
 }
 else if(Att.LineNumber.find(character)!=Att.LineNumber.end())
      //character matches directly the begin of a line
 {
  (*line)   = Att.LineNumber[character] ;                       //stored line-number
  (*column) = 1;                                                //first column

 }
 else //if(!(Att.LineBegin.empty()))//character is some where in the analysed text
 {
//  if     (Att.LineBegin.empty())                                //no evaluation possible
//   LineBegin = Att.LineBegin.end();                             // no line
//  else if((*line) == -1)                                        //first evaluation
//   LineBegin = Att.LineBegin.begin();                           //first line
//  else                                                          //evaluation inside
//   -- LineBegin;

                                                  //last evaluated line
  while(  (Att.LineCurrent != Att.LineBegin.begin())
        &&(character < (Att.LineEnd[*(Att.LineCurrent)]))
       )  // until last line-change reached or character is part of previous line
  {
   -- Att.LineCurrent;
  }
  while(  (Att.LineCurrent != Att.LineBegin.end())
        &&(character > (Att.LineEnd[*(Att.LineCurrent)]))
       )  // until last line-change reached or character is part of previous line
  {
   ++ Att.LineCurrent;                                                //next line
  }
                                             //actual line of character
  (*line)   = Att.LineNumber[*(Att.LineCurrent)] ;                      //stored line-number

  if(character>(*(Att.LineCurrent)))                                    // character inside real line
  {
   LineCharacter = (*(Att.LineCurrent));
   while(LineCharacter<character)                                //until given character reached
   {
    if((*LineCharacter == '\t'))                                 //tab-character found
     ColumnNumber = (ColumnNumber + tabSize)
                   -(ColumnNumber + tabSize)/tabSize;            //number of spaces until next tab-position
    else                                                         //normal character
     ++ColumnNumber;                                             //number of one normal character
    ++LineCharacter;                                             //next character
   }
   (*column) = ColumnNumber + 1;
  }
  else                                                           //character still inside line change
  {

   (*column) = - 1;                                              //define an unknown column
  }

 }
}










/* @MRTZ_describe getParserProperties

*/
map<TiPa_Concrete*, TDA_GrmConcrete::Property_TP>* TDA_GrmConcrete::getParserProperties(void)
{
 return(&Att.Property);
}





/* describe contextModel_set

*/
void TDA_GrmConcrete::contextModel_set(TiPa_Concrete::DataModel* contextModel)
{
 Att.ContextModel = contextModel;
}










/* @MRTZ_describe string2list

*/
void TDA_GrmConcrete::string2list(list<string>* stringList , const char* userText, char separator, bool clearWhiteSpaces)
{
 int          Size  = strlen(userText);           // length of  given text
 const char*  Begin = userText;                   // begin of first text-part
 const char*  End   = strchr(userText,separator); // end of first text-part

 while(  (End   != nullptr)
       &&(Begin <  userText + Size)
      )                                       // begin and end are inside of text
 {
  char*   Word = new char[Size+1];            // container for current text-part
  memcpy(Word,Begin,End-Begin);              // copy content of current text-part
  Word[End-Begin] = 0;                        // ensure the termination of the string

  LOG_OUTPUT(LOG_OFF, string("part text : |") << string(Word) << "|");

  if(clearWhiteSpaces == true)                // white spaces should be erased
  {
   char* Character = Word;                    // character of the original part-text
   char* WriteTo   = Word;                    // position to write a real character to (may be currently used by a white space)
   char* WordEnd   = Word + strlen(Word);     // end of the part-text

   while(Character != WordEnd)                // iterate over part-text
   {
    if(*Character > 32)                       // character is printable an no space
    {
     WriteTo = Character;                     // move character
     ++WriteTo;                               // next position to write to
  LOG_OUTPUT(LOG_OFF, string("part text : |")<< string(Word) << "|");
    }
    ++Character;                              // next character in part-text to evaluate
   }
   *WriteTo = 0;                               // terminate word at new position
  }
  else
  {
   // keep word as it is
  }

  stringList->push_back(Word);                // store result
  delete[](Word);                               // prepare next word
  Begin = End + 1;                            // begin of next text-part
  End   = strchr(Begin,separator);            // end of next text-part
  if(End==nullptr)                            // text contains no more separator
   End = userText + Size;                     // end of next text-part is end of text
 }

}

/* @MRTZ_describe string2set

*/
void TDA_GrmConcrete::string2set(set<string>* stringSet , const char* userText, char separator, bool clearWhiteSpaces)
{
 int          Size  = strlen(userText);           // length of  given text
 const char*  Begin = userText;                   // begin of first text-part
 const char*  End   = strchr(userText,separator); // end of first text-part

 if(End == nullptr)                           // no separator found
  End = userText + strlen(userText);          // end is end of text

 while(  (End   != nullptr)
       &&(Begin <  userText + Size)
      )                                       // begin and end are inside of text
 {
  char*   Word = new char[Size+1];            // container for current text-part
  memcpy(Word,Begin,End-Begin);              // copy content of current text-part
  Word[End-Begin] = 0;                        // ensure the termination of the string

  LOG_OUTPUT(LOG_OFF, string("part text : |") << string(Word) << "|");

  if(clearWhiteSpaces == true)                // white spaces should be erased
  {
   char* Character = Word;                    // character of the original part-text
   char* WriteTo   = Word;                    // position to write a real character to (may be currently used by a white space)
   char* WordEnd   = Word + strlen(Word);     // end of the part-text

   while(Character != WordEnd)                // iterate over part-text
   {
    if(*Character > 32)                       // character is printable an no space
    {
     *WriteTo = *Character;                   // move character
     ++WriteTo;                               // next position to write to
     LOG_OUTPUT(LOG_OFF, string("part text short : |")<< string(Word) << "|");
    }
    ++Character;                              // next character in part-text to evaluate
   }
   *WriteTo = 0;                               // terminate word at new position
  }
  else
  {
   // keep word as it is
  }

  LOG_OUTPUT(LOG_OFF, string("word to save : |") << string(Word) << "|");
  stringSet->insert(Word);                    // store result
  delete[](Word);                               // prepare next word
  Begin = End + 1;                            // begin of next text-part
  End   = strchr(Begin,separator);            // end of next text-part
  if(End==nullptr)                            // text contains no more separator
   End = userText + Size;                     // end of next text-part is end of text
 }

}






/* @MRTZ_describe parser_Get

*/
 TiPa_Concrete* TDA_GrmConcrete::parser_Get(const string&                    name,
                                            TiPa_Concrete::TDA_TiPa_CLASS_TP classType)
{
 TiPa_Concrete* ReturnValue = nullptr;

 switch(classType)
 {
  case TiPa_Concrete::TDA_TiPa_Character : // character-parser
  {
   if(Att.ParserCharacter.find(name) != Att.ParserCharacter.end())
    ReturnValue = Att.ParserCharacter[name];
   else
    ReturnValue = nullptr;
  }break;
  case TiPa_Concrete::TDA_TiPa_String    : // string-parser
  {
   if(Att.ParserString.find(name) != Att.ParserString.end())
    ReturnValue = Att.ParserString[name];
   else
    ReturnValue = nullptr;
  }break;
  case TiPa_Concrete::TDA_TiPa_Counter   : // counting parser operation
  {
   if(Att.ParserCounter.find(name) != Att.ParserCounter.end())
    ReturnValue = Att.ParserCounter[name];
   else
    ReturnValue = nullptr;
  }break;
  case TiPa_Concrete::TDA_TiPa_Sequence  : // sequence parser-operation
  {
   if(Att.ParserSequence.find(name) != Att.ParserSequence.end())
    ReturnValue = Att.ParserSequence[name];
   else
    ReturnValue = nullptr;
  }break;
  case TiPa_Concrete::TDA_TiPa_Condition : // conditional parser-operation
  {
   if(Att.ParserCondition.find(name) != Att.ParserCondition.end())
    ReturnValue = Att.ParserCondition[name];
   else
    ReturnValue = nullptr;
  }break;
  case TiPa_Concrete::TDA_TiPa_Rule      : // call of an other parser or parser operation
  {
   if(Att.ParserRule.find(name) != Att.ParserRule.end())
    ReturnValue = Att.ParserRule[name];
   else
    ReturnValue = nullptr;
  }break;
  case TiPa_Concrete::TDA_TiPa_Concrete  : // not valid parser
  default                                : // not valid classType
  {
    ReturnValue = nullptr;
  }break;
 }

 return(ReturnValue);
}






/* @MRTZ_describe property_Get
*/
TDA_GrmConcrete::Property_TP TDA_GrmConcrete::property_Get(const string&                    name,
                                                           TiPa_Concrete::TDA_TiPa_CLASS_TP classType)
{
 TDA_GrmConcrete::Property_TP ReturnValue;
 TiPa_Concrete*               Parser      = parser_Get(name,classType);

 if(Att.Property.find(Parser) != Att.Property.end())
 {
  ReturnValue.Description    = Att.Property[Parser].Description;
  ReturnValue.Name           = Att.Property[Parser].Name;
  ReturnValue.User_ID        = Att.Property[Parser].User_ID;
  ReturnValue.User_ID_String = Att.Property[Parser].User_ID_String;
 }
 else
 {
  ReturnValue.Description    = nullptr;
  ReturnValue.Name           = nullptr;
  ReturnValue.User_ID        = INT_MIN;
  ReturnValue.User_ID_String = nullptr;
 }

 return(ReturnValue);
}



/* @MRTZ_describe property_UserID_Get

*/
int TDA_GrmConcrete::property_UserID_Get(const string&                    name,
                                         int                              defaultID,
                                         TiPa_Concrete::TDA_TiPa_CLASS_TP classType)
{
 int            ReturnValue;
 TDA_GrmConcrete::Property_TP Property      = property_Get(name,classType);

 if(Property.Name != nullptr)
  ReturnValue = Property.User_ID;
 else
  ReturnValue = defaultID;

 return(ReturnValue);
}




