/*!

 @file
 @brief    definition of an expression evaluation

 This file contains the definition of a class to evaluate source expressions
 to force internal decisions


 Copyright (C) 2011-2020 by Eckard Klotz.

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
    25.09.2011     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    25.09.2011...  @I Eckard Klotz
 @I Changes are documented in the comment of the changed element
 @TabEnd

*/






#include "trn_directive.h"
#include "TiPa_Search.h"


//#include "TiXml_ao.h"
#include "StringC_help.h"


#ifndef DOXYGEN
//namespace CL_PROCESS {
//namespace CL_TRANSFORM {
//namespace CL_TRN_DIRECTIVE {
#endif //DOXYGEN

//const String_imp  COMMAND = "__command__";
//const String_imp  BLOCK   = "__block__";
//const String_imp  COMMENT = "Comment";
const String_imp  YES    = "Yes";
const String_imp  NO     = "No";
const String_imp  SP     = "SP";
//const String_imp  CODE   = "CODE";
//const String_imp  LINE   = "LINE";



/* @MRTZ_describe Prcs_Trn_Directive

*/
Prcs_Trn_Directive::Prcs_Trn_Directive(int            positionOutput,
                                       bool           normlzKwrdsOfSource,
                                       bool           showTextToParse,
                                       bool           parseTolerant,
                                       int            startLine ,
                                       int            startColumn,
                                 const String_imp&    tokenIndent,
                                 const String_imp&    tokenDedent,
                                 const String_imp&    tokenNewLine,
                                 const String_imp&    commentBegin,
                                 const String_imp&    commentEnd
                                      ):Prcs_Trn_Source(positionOutput,
                                                        normlzKwrdsOfSource,
                                                        showTextToParse,
                                                        parseTolerant,
                                                        startLine ,
                                                        startColumn,
                                                        tokenIndent,
                                                        tokenDedent,
                                                        tokenNewLine)
{
 Att.Replacement["\n"]       = " ";
 Att.Replacement["\r"]       = " ";
 Att.Replacement["\t"]       = " ";
 Att.Replacement["  "]       = " ";
 Att.Replacement[EMPTYSTRING]= "";
// Att.ParsedSource            = nullptr;
 Att.ExpressionCheck         = new Prsd_Expression;

 Att.CommentBegin            = commentBegin;
 Att.CommentEnd              = commentEnd;
 Att.TestParser              = nullptr;
 Att.AbleToParseDirectives   = true;
// Att.CodeTree                = nullptr;
 Att.CodeRoot                = nullptr;
 Att.DataModel               = nullptr;
}

/* @MRTZ_describe ~Prcs_Trn_Directive

*/
Prcs_Trn_Directive::~Prcs_Trn_Directive()
{
 Att.Replacement.clear();
}


/* @MRTZ_describe configureConstants

*/
void Prcs_Trn_Directive::configureConstants(XML_Node  variant)
{
 if(Att.ExpressionCheck != nullptr)
  delete(Att.ExpressionCheck);
 Att.ExpressionCheck = new Prsd_Expression;

 XML_Node  Child = variant.firstGet(XML_Node::Element(XML_Search::Value,"ConstantSet"));
 while (Child.valid() == true)// != nullptr)
 {
  String_imp  Value = Child.attributeGet("value");
  const char* Text  = Child.attributeGet("name");
  if(Text != nullptr)
  {
   String_imp Constant = String_imp(Text);
#if defined(DEBUG_OUTPUT)
   cout << Constant << "=|" << Value << "|" << endl;
#endif //DEBUG_OUTPUT
   if(Constant != "")
    Att.ExpressionCheck->constant_Set(Constant, Value);
  }
  else
  {
   Text = Child.attributeGet("term");
   if(Text != nullptr)
   {
    String_imp Constant = String_imp(Text);
#if defined(DEBUG_OUTPUT)
    cout << Constant << "=|" << Value << "|" << endl;
#endif //DEBUG_OUTPUT
    if(Constant != "")
     Att.ExpressionCheck->userResult_Set(Constant, Value);
   }
   else
   {
    cout << "unknown type of user-constant for value: " << Value << endl;
   }
  }
  Child = Child.behindGet(XML_Node::Element(XML_Search::Value,"ConstantSet"));
 }


}

/* @MRTZ_describe setTestParser

*/
void Prcs_Trn_Directive::setTestParser(CoreFlow* testParser)
{
 Att.TestParser = testParser;
}

/* @MRTZ_describe setMergeLevel

*/
void Prcs_Trn_Directive::setMergeLevel(String_imp& mergeLevel, String_imp& variantID)
{
 Att.MergeLevel = stringToSet(mergeLevel);
 Att.VariantID  = variantID;
}


/* @MRTZ_describe analyse

*/
TiPa_Concrete::DataFellow* Prcs_Trn_Directive::analyse(String_imp*     text,
                                                       TiPa_DataModel* model,
                                                       String_imp      rule)
{
 TiPa_Concrete::DataFellow*  ReturnValue = nullptr;

 if ((text != nullptr)&&((*text)!=""))
 {
  Att.DataModel = model;

  Prcs_Trn_Source::analyse( text, model, rule);
  Att.SplitedSource.clear();
  splitSource( model->focus_Fellow(),
               model,
              &Att.SplitedSource);
  ReturnValue  = model->focus_Fellow();
  Att.CodeRoot = model->focus_Fellow();
 }

 return(ReturnValue);
}


/* @MRTZ_describe getSourceParts

*/
map<int,String_imp>Prcs_Trn_Directive::getSourceParts(DataAssociation*             rootNew,
                                                      TiPa_DataModel* context)
{
 map<int,String_imp>           ReturnValue;
 static int          Recursion        = 0;
 static int          MaxLine          = 0;

 if(Recursion == 0)
  MaxLine = 0;

 ++ Recursion;
 DataAssociation* Node  = rootNew->contractorFirst_get();

 while(Node  != nullptr)
 {
  TiPa_Data* Data = Node->data_get();

  if(Data != nullptr)
  {
   if(  (STRINGS_ARE_EQUAL(Data->userName_get(), "p_if_expr"))
      ||(STRINGS_ARE_EQUAL(Data->userName_get(), "p_ifdef_expr"))
      ||(STRINGS_ARE_EQUAL(Data->userName_get(), "p_ifndef_expr"))
      ||(STRINGS_ARE_EQUAL(Data->userName_get(), "p_elif_expr"))
      ||(STRINGS_ARE_EQUAL(Data->userName_get(), "p_else_expr"))
      ||(STRINGS_ARE_EQUAL(Data->userName_get(), "p_endif"))
      ||(STRINGS_ARE_EQUAL(Data->userName_get(), "p_define"))
      ||(STRINGS_ARE_EQUAL(Data->userName_get(), "p_undefine"))
      ||(STRINGS_ARE_EQUAL(Data->userName_get(), "p_include"))
      ||(STRINGS_ARE_EQUAL(Data->userName_get(), "p_pragma"))
      ||(STRINGS_ARE_EQUAL(Data->userName_get(), "p_line"))
      ||(STRINGS_ARE_EQUAL(Data->userName_get(), "p_error"))
      ||(STRINGS_ARE_EQUAL(Data->userName_get(), "p_warning"))
      ||(STRINGS_ARE_EQUAL(Data->userName_get(), "text_line"))
      )
   {
    int LineNumber = stringToNumber(String_imp(Data->lineGet())) ;
    ReturnValue[LineNumber] = _reconstructSource(Node,context);
    if(MaxLine < LineNumber)
    {
     MaxLine = LineNumber;
    }
   }
   else
   {
    map<int,String_imp>           ChildContent = getSourceParts(/*Child,*/Node,context);
    map<int,String_imp>::iterator Line         = ChildContent.begin();
    while(Line != ChildContent.end())
    {
     ReturnValue[Line->first] = Line->second;
     ++Line ;
    }
   }
  }
  Node  = Node->fellowBehind_get();
 }

 -- Recursion;

 if(Recursion == 0)
 {
  map<int,String_imp>::iterator Line             = ReturnValue.begin();
  int                           LineNumberBefore = 0;
  int                           LineNumber       = 0;
  list<int>                     EmptyLines;

  while(LineNumber <= MaxLine)
  {
   while(ReturnValue.find(LineNumber) == ReturnValue.end())
    ++LineNumber;

   while((LineNumber-LineNumberBefore) > 1)
   {
    ++LineNumberBefore;
    EmptyLines.push_back(LineNumberBefore);
   }
   TP_TextSize Size = getTextSize((Line->second).c_str(),
                                  (Line->second).c_str() + (Line->second).size()
                                 );
   LineNumberBefore = LineNumberBefore + Size.Height;

   ++LineNumber;
  }

  list<int>::iterator EmptyLine = EmptyLines.begin();
  while(EmptyLine != EmptyLines.end())
  {
   ReturnValue[*EmptyLine] = "";
   ++EmptyLine;
  }
 }


 return(ReturnValue);
}





/* @MRTZ_describe getLogicTerms

*/
void Prcs_Trn_Directive::getLogicTerms(DataAssociation*                root,
                                       map<String_imp,SwitchState_TP>* term,
                                       bool                            treatAsDefined)
{
// String_imp     Statement       = "";

 map<String_imp,SwitchState_TP>*          Term = nullptr;
 map<String_imp,SwitchState_TP>::iterator NewTerm;

 DataAssociation* Node  = root->contractorFirst_get();

 while(Node  != nullptr)
 {
  TiPa_Data* Data = Node->data_get();

  if     (  (ASSOCIATION_IS_NOT_LEAF(Node))
          &&(STRINGS_ARE_NOT_EQUAL(Data->userName_get(), "expression"))
         )
  {
   if(  (STRINGS_ARE_EQUAL(Data->userName_get(), "p_ifdef"))
      ||(STRINGS_ARE_EQUAL(Data->userName_get(), "p_ifndef"))
     )
    getLogicTerms(Node,term,true);
   else
    getLogicTerms(Node,term,false);

  }
  else if(  (ASSOCIATION_IS_NOT_LEAF(Node))
          &&(STRINGS_ARE_EQUAL(Data->userName_get(), "expression"))
         )
  {

    Term = Att.ExpressionCheck->getLogicTerms(Node);
    NewTerm = Term->begin();
    while(NewTerm != Term->end())
    {
// @MRTZ_ifElseChain
     if     ((treatAsDefined == true) && ((NewTerm->second) == TRI_UNDEFINED))
      (*term)[NewTerm->first] =TRI_UNDEFINED;
     else if((treatAsDefined == true) && ((NewTerm->second) != TRI_UNDEFINED))
      (*term)[NewTerm->first] =TRI_DEFINED;
     else
      (*term)[NewTerm->first] =NewTerm->second;
#if defined(DEBUG_OUTPUT)
     cout << "Term(" << NewTerm->first << ") = " << NewTerm->second << endl;
#endif //DEBUG_OUTPUT
     ++NewTerm ;
    }

    delete(Term);
  }
  else
  {}
  Node  = Node->fellowBehind_get();
 }


}

/* @MRTZ_describe analyze_SwitchedText

*/
bool  Prcs_Trn_Directive::analyze_SwitchedText(KEEP_VALIDE_CODE_TP keepValideCode,
                                               DataAssociation*             rootNew,
                                               TiPa_DataModel* context,
                                               Prsd_Expression*             expressionCheck)
{
 bool       ReturnValue     = false;
// bool       ParentOn        = true;

#if defined(DEBUG_OUTPUT)
 cout << "analyze_SwitchedText" << endl;
#endif //DEBUG_OUTPUT


 if(rootNew == nullptr)
  rootNew = Att.CodeRoot;//Att.CodeTree->focus_Fellow();
 if(context == nullptr)
  context = Att.DataModel;//Att.CodeTree;
 if(expressionCheck == nullptr)
  expressionCheck = Att.ExpressionCheck;

 if(rootNew != nullptr)
 {
  Att.CommentOut.clear();
  Att.AbleToParseDirectives = true;
  bool AbleToParseCode      = true;                       // will be set to false if a code snipet is not parse-able

  DataAssociation* Node = rootNew->contractorFirst_get();
  while(Node != nullptr)
  {
   TiPa_Data* Data = Node->data_get();
   if(Data != nullptr)
   {
    bool ParentOn = true;
// @MRTZ_ifElseChain
    if     (STRINGS_ARE_EQUAL(Data->userName_get(), "p_Block"))
    {
     if(   _analyze_P_Block(keepValideCode, Node, context, ParentOn, expressionCheck, &(Att.CommentOut))
        == false)
      AbleToParseCode = false;
     else
      {/* no reset of AbleToParseCode from false to true allowed here*/}
    }
    else if(STRINGS_ARE_EQUAL(Data->userName_get(), "preprocedure"))
    {
     if(   _analyze_Preprocedure(keepValideCode, Node, context, ParentOn, expressionCheck, &(Att.CommentOut))
        == false)
      AbleToParseCode = false;
     else
      {/* no reset of AbleToParseCode from false to true allowed here*/}
    }
    else
    {
#if defined(DEBUG_OUTPUT)
     cout << "else -> getSwitchedText" << endl;
#endif //DEBUG_OUTPUT
    }
   }
   Node  = Node->fellowBehind_get();
  }

#if defined(DEBUG_OUTPUT)
  cout << "\nAbleToParseCode: " << AbleToParseCode << " AbleToParseDirectives: " << Att.AbleToParseDirectives << endl;
#endif //DEBUG_OUTPUT

  if(  (    AbleToParseCode       == false)
     &&(Att.AbleToParseDirectives == false)
    )
   ReturnValue = false;
  else
   ReturnValue = true;
 }

 return(ReturnValue);
}



/* @MRTZ_describe _analyze_P_Block

*/
bool Prcs_Trn_Directive::_analyze_P_Block(KEEP_VALIDE_CODE_TP          keepValideCode,
                                          DataAssociation*             rootNew,
                                          TiPa_DataModel* context,
                                          bool                         parentOn,
                                          Prsd_Expression*             expressionCheck,
                                          map<int,bool>*               commentOut)
{
 bool        ReturnValue    = true;
 bool        AbleToParse    = true;
// int         LineNumber     = 0;
// bool        ParentOn       = true;

#if defined(DEBUG_OUTPUT)
 cout << "_get_P_Block" << endl;
#endif //DEBUG_OUTPUT

 DataAssociation* Node  = rootNew->contractorFirst_get();

 while(Node  != nullptr)
 {
  TiPa_Data* Data = Node->data_get();

  if(Data != nullptr)
  {
   bool ParentOn = parentOn;

   if (STRINGS_ARE_EQUAL(Data->userName_get(), "text_line"))
   {
    int LineNumber = stringToNumber(String_imp(Data->lineGet())) ;
    if(parentOn == true)
    {
     //@MRTZ_ifElseChain
     if(commentOut->find(LineNumber)==commentOut->end())
     //due to some parsing-limitations comments of endifs will be managed as independently text-line
     //even if they are located in the same line. this test should ensure that a deactivated endif-line
     //could not be activated again. thus the endif-comments are deactivated also but only those in the
     //same line.
     {
      Data->secondaryData_add("activeCode", YES.c_str());
      (*commentOut)[LineNumber] = false;
     }
     else if((*commentOut)[LineNumber] == false)
     {
      Data->secondaryData_add("activeCode", YES.c_str());
     }
     else
     {
      Data->secondaryData_add("activeCode", NO.c_str());
     }
    }
    else
    {
     Data->secondaryData_add("activeCode", NO.c_str());
     (*commentOut)[LineNumber] = true;
    }


   }
   else  if(STRINGS_ARE_EQUAL(Data->userName_get(), "preprocedure"))
   {
    if(   _analyze_Preprocedure(keepValideCode, Node, context, ParentOn, expressionCheck, commentOut)
       == false
      )//trial to parse the directive content failed
     AbleToParse = false;
    else//content of directive can be parsed
     {/* no reset of AbleToParse to true allowed*/}
   }
   else
   {
#if defined(DEBUG_OUTPUT)
    cout << "else -> _get_P_Block" << endl;
#endif //DEBUG_OUTPUT
   }
  }
  Node  = Node->fellowBehind_get();
 }


 TiPa_Data* RootData     = rootNew->data_get();
 DataAssociation* Parent = rootNew->sponsor_get();
 if(  (Parent             != nullptr)
    &&(Parent->data_get() != nullptr)
    &&(RootData           != nullptr)
    &&(AbleToParse        == true   )
   )
 {
  TiPa_Data* ParentData = Parent->data_get();

  if(  (STRINGS_ARE_EQUAL(ParentData->userName_get(),"p_if"))
     ||(STRINGS_ARE_EQUAL(ParentData->userName_get(),"p_ifdef"))
     ||(STRINGS_ARE_EQUAL(ParentData->userName_get(),"p_ifndef"))
     ||(STRINGS_ARE_EQUAL(ParentData->userName_get(),"p_elif"))
     ||(STRINGS_ARE_EQUAL(ParentData->userName_get(),"p_else"))
    )//only inside of compiler-switches
  {
// @MRTZ_ifElseChain
   if(RootData->secondaryData_get("ableToParse",nullptr) == nullptr)
   {
    ReturnValue = _tryToParse(/*root,*/ rootNew, context);
    if(ReturnValue == true)
     RootData->secondaryData_add("ableToParse", YES.c_str()) ;
    else
     RootData->secondaryData_add("ableToParse", NO.c_str()) ;
   }
   else if(STRINGS_ARE_EQUAL(RootData->secondaryData_get("ableToParse",NO.c_str()),YES.c_str()))
   {
    ReturnValue = true;
   }
   else
   {
    ReturnValue = false;
   }
  }
  else
  {
   ReturnValue = true;
   RootData->secondaryData_add("ableToParse",YES.c_str()) ;
  }
 }
 else
 {
#if defined(DEBUG_OUTPUT)
  cout << " keepValideCode(" << keepValideCode << ") AbleToParse(" << AbleToParse << ") " << xmlToText(root) << endl;
#endif //DEBUG_OUTPUT
  ReturnValue = false;
  RootData->secondaryData_add("ableToParse",NO.c_str()) ;
 }

 return(ReturnValue);
}



/* @MRTZ_describe _analyze_Preprocedure

*/
bool Prcs_Trn_Directive::_analyze_Preprocedure(KEEP_VALIDE_CODE_TP keepValideCode,
                                               DataAssociation*    rootNew,
                                               TiPa_DataModel*     context,
                                               bool                parentOn,
                                               Prsd_Expression*    expressionCheck,
                                               map<int,bool>*      commentOut)
{
 bool          ReturnValue    = true;
// int           LineNumber     = 0;
// map<int,bool>::iterator Line;
// bool          KeepValideCode = true;

#if defined(DEBUG_OUTPUT)
 cout << "_get_Preprocedure" << endl;
#endif //DEBUG_OUTPUT

 DataAssociation* Node     = rootNew->contractorFirst_get();
 TiPa_Data*       RootData = rootNew->data_get();

 while(  (Node     != nullptr)
       &&(RootData != nullptr)
      )
 {
  TiPa_Data* Data = Node->data_get();
  if(Data != nullptr)
  {
   if(STRINGS_ARE_EQUAL(Data->userName_get(), "compilerSwitch"))
   {
    map<int,bool> TempCommentOut;
    if(   _analyze_compilerSwitch(keepValideCode, Node, context, parentOn, expressionCheck, &TempCommentOut)
       == false)
    {
     ReturnValue = false;
     Data->secondaryData_add("ableToParse",NO.c_str());
     RootData->secondaryData_add("ableToParse",NO.c_str());

     if(STRINGS_ARE_EQUAL(Data->secondaryData_get("solved","implicit"),"implicit"))
     {
      Att.AbleToParseDirectives = false;
      Data->secondaryData_add("problem","1");
     }
     map<int,bool>::iterator Line = TempCommentOut.begin();
     while(Line != TempCommentOut.end())
     {
      (*commentOut)[Line->first] = Line->second;
      ++ Line;
     }
    }
    else
    {/* no reset of ReturnValue to true allowed*/
     Data->secondaryData_add("ableToParse",YES.c_str());
     RootData->secondaryData_add("ableToParse",YES.c_str());

     if(  (keepValideCode==KVC_NEVER)
        &&STRINGS_ARE_EQUAL(Data->secondaryData_get("solved",""),"implicit")
       )
     {
      Att.AbleToParseDirectives = false;
      Data->secondaryData_add("problem","2");
     }
     bool KeepValideCode = (  (   keepValideCode==KVC_ALLWAYS)
                            ||(  (keepValideCode==KVC_IMPLICIT)
                               && STRINGS_ARE_EQUAL(Data->secondaryData_get("solved",""),"implicit")
                              )
                           );
     map<int,bool>::iterator Line = TempCommentOut.begin();
     while(Line != TempCommentOut.end())
     {
      if(KeepValideCode == true)
      {
       (*commentOut)[Line->first] = false;
      }
      else
      {
       (*commentOut)[Line->first] = Line->second;
      }
      ++ Line;
     }
    }
   }
   else if(  (STRINGS_ARE_EQUAL(Data->userName_get(), "p_define"))
           ||(STRINGS_ARE_EQUAL(Data->userName_get(), "p_undefine"))
           ||(STRINGS_ARE_EQUAL(Data->userName_get(), "p_include"))
           ||(STRINGS_ARE_EQUAL(Data->userName_get(), "p_pragma"))
           ||(STRINGS_ARE_EQUAL(Data->userName_get(), "p_line"))
           ||(STRINGS_ARE_EQUAL(Data->userName_get(), "p_error"))
           ||(STRINGS_ARE_EQUAL(Data->userName_get(), "p_warning"))
           ||(STRINGS_ARE_EQUAL(Data->userName_get(), "text_line"))
          )
   {
    int LineNumber = stringToNumber(String_imp(Data->lineGet())) ;

    if(parentOn == true)
    {
     Data->secondaryData_add("activeCode", YES.c_str());
     (*commentOut)[LineNumber] = false;
    }
    else
    {
     Data->secondaryData_add("activeCode", NO.c_str());
     (*commentOut)[LineNumber] = true;
    }
    Data->secondaryData_add("ableToParse",YES.c_str());
    RootData->secondaryData_add("ableToParse",YES.c_str());
   }
   else
   {
   }
  }
  Node  = Node->fellowBehind_get();
 }
 return(ReturnValue);
}


/* @MRTZ_describe _analyze_compilerSwitch

*/
bool Prcs_Trn_Directive::_analyze_compilerSwitch(KEEP_VALIDE_CODE_TP          keepValideCode,
                                                 DataAssociation*             rootNew,
                                                 TiPa_DataModel* context,
                                                 bool                         parentOn,
                                                 Prsd_Expression*             expressionCheck,
                                                 map<int,bool>*               commentOut)
{
 bool          ReturnValue     = true;
// int           LineNumber      = 0;

#if defined(DEBUG_OUTPUT)
 cout << "_get_compilerSwitch" << endl;
#endif //DEBUG_OUTPUT

 bool             OnFound  = false;// init for the search in switch-pathes
 bool             Dummi    = true;
 DataAssociation* Node     = rootNew->contractorFirst_get();
 TiPa_Data*       RootData = rootNew->data_get();

 while(  (Node     != nullptr)
       &&(RootData != nullptr)
      )
 {
  TiPa_Data* Data = Node->data_get();
  if(Data != nullptr)
  {
   int LineNumber = stringToNumber(String_imp(Data->lineGet()));
   (*commentOut)[LineNumber] = true;

   if     (STRINGS_ARE_EQUAL(Data->userName_get(), "p_if"))
   {
    if(   _analyze_SwitchContent(keepValideCode, Node, context, parentOn, expressionCheck, commentOut, TRI_TRUE, &OnFound)
       == false)
     ReturnValue = false;
    else
     {/* no reset of ReturnValue to true allowed*/}
   }
   else if(STRINGS_ARE_EQUAL(Data->userName_get(), "p_ifdef"))
   {
    if(   _analyze_SwitchContent(keepValideCode, Node, context, parentOn, expressionCheck, commentOut, TRI_DEFINED, &OnFound)
       == false)
     ReturnValue = false;
    else
     {/* no reset of ReturnValue to true allowed*/}
#if defined(DEBUG_OUTPUT)
    cout << endl << "onFound: "<< OnFound << endl;
#endif //DEBUG_OUTPUT

   }
   else if(STRINGS_ARE_EQUAL(Data->userName_get(), "p_ifndef"))
   {
    if(   _analyze_SwitchContent(keepValideCode, Node, context, parentOn, expressionCheck, commentOut, TRI_UNDEFINED, &OnFound)
       == false)
     ReturnValue = false;
    else
     {/* no reset of ReturnValue to true allowed*/}
   }
   else if(STRINGS_ARE_EQUAL(Data->userName_get(), "p_elif"))
   {
    if(OnFound == true)
     if(   _analyze_SwitchContent(keepValideCode, Node, context, parentOn, expressionCheck, commentOut, TRI_FALSE, &Dummi)
        == false)
      ReturnValue = false;
     else
      {/* no reset of ReturnValue to true allowed*/}
    else
     if(   _analyze_SwitchContent(keepValideCode, Node, context, parentOn, expressionCheck, commentOut, TRI_TRUE, &OnFound)
        == false)
      ReturnValue = false;
     else
      {/* no reset of ReturnValue to true allowed*/}
   }
   else if(STRINGS_ARE_EQUAL(Data->userName_get(), "p_else"))
   {
    if(OnFound == true)
     if(   _analyze_SwitchContent(keepValideCode, Node, context, parentOn, expressionCheck, commentOut, TRI_FALSE, &Dummi)
        == false)
      ReturnValue = false;
     else
      {/* no reset of ReturnValue to true allowed*/}
    else
     if(   _analyze_SwitchContent(keepValideCode, Node, context, parentOn, expressionCheck, commentOut, TRI_TRUE, &OnFound)
        == false)
      ReturnValue = false;
     else
      {/* no reset of ReturnValue to true allowed*/}
   }
   else if(STRINGS_ARE_EQUAL(Data->userName_get(), "p_endif"))
   {
   }
   else
   {
   }

   if(STRINGS_ARE_EQUAL(Data->secondaryData_get("solved",""),"implicit"))
    RootData->secondaryData_add("solved","implicit");
  }
  Node  = Node->fellowBehind_get();
 }

 return(ReturnValue);
}





/* @MRTZ_describe _analyze_SwitchContent

*/
bool Prcs_Trn_Directive::_analyze_SwitchContent(KEEP_VALIDE_CODE_TP          keepValideCode,
                                                DataAssociation*             rootNew,
                                                TiPa_DataModel* context,
                                                bool                         parentOn,
                                                Prsd_Expression*             expressionCheck,
                                                map<int,bool>*               commentOut,
                                                SwitchState_TP               wantedResult,
                                                bool*                        onFound)
{
 bool          ReturnValue      = true;

#if defined(DEBUG_OUTPUT)
 cout << "_get_SwitchContent" << endl;
#endif //DEBUG_OUTPUT


 DataAssociation* Switch     = rootNew->sponsor_get();
 TiPa_Data*       SwitchData = Switch->data_get();
 DataAssociation* Node       = rootNew->contractorFirst_get();
 bool ParentOn = parentOn;

 while(  (Switch     != nullptr)
       &&(SwitchData != nullptr)
       &&(Node       != nullptr)
      )
 {
  TiPa_Data* Data = Node->data_get();

  if(Data != nullptr)
  {
   if(  (STRINGS_ARE_EQUAL(Data->userName_get(), "p_if_expr"))
      ||(STRINGS_ARE_EQUAL(Data->userName_get(), "p_ifdef_expr"))
      ||(STRINGS_ARE_EQUAL(Data->userName_get(), "p_ifndef_expr"))
      ||(STRINGS_ARE_EQUAL(Data->userName_get(), "p_elif_expr"))
     )
   {
    TiPa_Search      Search;
    DataAssociation* ExpressionNew  = Node->contractorFirst_get(Search(TiPa_Search::UserName,"expression"));
    TiPa_Data*       ExpressionData = ExpressionNew->data_get();
    if(  (ExpressionNew  != nullptr)
       &&(ExpressionData != nullptr)
      )
    {
#if defined(DEBUG_OUTPUT)
     cout << "Expression: " << xmlToText(Expression) <<endl;
#endif //DEBUG_OUTPUT
      bool        NotFullDefined   = false;
      _s_TestRet  ExpressionResult = expressionCheck->testExpression(ExpressionNew, &NotFullDefined);
     if(NotFullDefined == true)
     {
      ExpressionData->secondaryData_add("solved","implicit");
      Data->secondaryData_add("solved","implicit");
      if(STRINGS_ARE_NOT_EQUAL(SwitchData->secondaryData_get("solved",""),"explicit"))
       SwitchData->secondaryData_add("solved","implicit");
#if defined(DEBUG_OUTPUT)
      cout << "unknown part found in Expression" << endl;
      cout << xmlToText(Expression);
      cout << "ExpressionResult("<<ExpressionResult.Type<<") |" <<ExpressionResult.Value<<"|\n";
      cout << endl;
#endif //DEBUG_OUTPUT
     }
     else
     {
      ExpressionData->secondaryData_add("solved","explicit");
      Data->secondaryData_add("solved","explicit");
      /* no reset of Att.AbleToParseDirectivese from false to true allowed here*/
#if defined(DEBUG_OUTPUT)
      cout << "all parts found in Expression" << endl;
      cout << xmlToText(Expression);
      cout << "ExpressionResult("<<ExpressionResult.Type<<") |" <<ExpressionResult.Value<<"|\n";
      cout << endl;
#endif //DEBUG_OUTPUT
     }

     if(  (  (wantedResult           == TRI_TRUE)
           &&(ExpressionResult.Value == "true")
          )
        ||(  (wantedResult           == TRI_DEFINED)
           &&(  (ExpressionResult.Type  == STRING)
              ||(ExpressionResult.Value != "")
             )
          )
        ||(  (wantedResult           == TRI_UNDEFINED)
           &&(  (ExpressionResult.Type  != STRING)
              &&(ExpressionResult.Value == "")
             )
          )
       )
     {
      (*onFound) = true;
      if(STRINGS_ARE_NOT_EQUAL(SwitchData->secondaryData_get("solved",nullptr),"implicit"))
       SwitchData->secondaryData_add("solved","explicit");
#if defined(DEBUG_OUTPUT)
     if     (wantedResult == TRI_TRUE)
      cout << "if is on" << endl;
     else if(wantedResult == TRI_DEFINED)
      cout << "ifdef is on" << endl;
     else if(wantedResult == TRI_UNDEFINED)
      cout << "ifndef is on" << endl;
#endif //DEBUG_OUTPUT
     }
     else
     {
      ParentOn    = false;
#if defined(DEBUG_OUTPUT)
      cout << "if-error wanted Result(" << wantedResult <<") Type("<< ExpressionResult.Type << ") Value("<< ExpressionResult.Value << ")" << endl;
#endif //DEBUG_OUTPUT
     }
    }
   }
   else if(STRINGS_ARE_EQUAL(Data->userName_get(), "p_else_expr"))
   {
    if(STRINGS_ARE_NOT_EQUAL(SwitchData->secondaryData_get("solved","implicit"),"implicit"))
    {
     SwitchData->secondaryData_add("solved","explicit");
     Data->secondaryData_add("solved","explicit");
    }
    else
    {
     Data->secondaryData_add("solved","implicit");
    }

    if(wantedResult == TRI_TRUE)
    {
     (*onFound) = true;
      ParentOn  = true;
    }
    else
    {
     // no reset of onFound from true to false allowed here
      ParentOn  = false;
    }
   }
   else if(STRINGS_ARE_EQUAL(Data->userName_get(), "p_Block"))
   {
    if(parentOn == false) // if given parent of at higher switch level is off than parent
                          // of the local text-block is also off
     ParentOn = false;
    if(   _analyze_P_Block(keepValideCode, Node, context, ParentOn, expressionCheck, commentOut)
        == false)
     ReturnValue = false;
    else
      {/* no reset of ReturnValue to true allowed*/}
   }
   else
   {
   }
  }
  Node  = Node->fellowBehind_get();
 }

#if defined(DEBUG_OUTPUT)
 cout<< "SwitchLine: " << SwitchLine << endl;
#endif //DEBUG_OUTPUT

 return(ReturnValue);
}








/* @MRTZ_describe splitSource

   @MRTZ_describe collect_switching_parts

   @MRTZ_describe collect_switched_parts

*/
void Prcs_Trn_Directive::splitSource(DataAssociation*   rootNew,
                                     TiPa_DataModel*    context,
                                     list<_s_TextLine>* analysedText)
{
 list<String_imp>           Text;
 list<String_imp>::iterator Line;
 _s_TextLine                ResultLine;
// int                        Offset = 0;

 DataAssociation* Node  = rootNew->contractorFirst_get();


 while(Node  != nullptr)
 {
  TiPa_Data* Data = Node->data_get();
  if(/*  (ASSOCIATION_IS_NOT_LEAF(Node))
     &&*/(Data                 != nullptr)
     &&  (Data->userName_get() != nullptr)
    )
  {
   if(  (STRINGS_ARE_EQUAL(Data->userName_get(), "p_if_expr"))
      ||(STRINGS_ARE_EQUAL(Data->userName_get(), "p_ifdef_expr"))
      ||(STRINGS_ARE_EQUAL(Data->userName_get(), "p_ifndef_expr"))
      ||(STRINGS_ARE_EQUAL(Data->userName_get(), "p_elif_expr"))
      ||(STRINGS_ARE_EQUAL(Data->userName_get(), "p_else_expr"))
     )
   {
    Text.clear();
    Text.push_back(_reconstructSource(Node, context));
    int Offset = 0;
    Line = Text.begin();
    while(Line != Text.end())
    {
     ResultLine.Content    = String_imp(*Line);
     ResultLine.LineNumber = Offset + stringToNumber(String_imp(Data->lineGet()));
     analysedText->push_back(ResultLine);
     ++ Offset;
     ++ Line;
    }
   }
   else
// @MRTZ_exclude collect_switched_parts
        if(  (STRINGS_ARE_EQUAL(Data->userName_get(), "p_endif"))
           ||(STRINGS_ARE_EQUAL(Data->userName_get(), "p_define"))
           ||(STRINGS_ARE_EQUAL(Data->userName_get(), "p_undefine"))
           ||(STRINGS_ARE_EQUAL(Data->userName_get(), "p_include"))
           ||(STRINGS_ARE_EQUAL(Data->userName_get(), "p_pragma"))
           ||(STRINGS_ARE_EQUAL(Data->userName_get(), "p_line"))
           ||(STRINGS_ARE_EQUAL(Data->userName_get(), "p_error"))
           ||(STRINGS_ARE_EQUAL(Data->userName_get(), "p_warning"))
           ||(STRINGS_ARE_EQUAL(Data->userName_get(), "text_line"))
          )
   {
    Text.clear();
    Text.push_back(_reconstructSource(Node, context));
    int Offset = 0;
    Line = Text.begin();
    while(Line != Text.end())
    {
     ResultLine.Content    = String_imp(*Line);
     ResultLine.LineNumber = Offset + stringToNumber(String_imp(Data->lineGet()));
     analysedText->push_back(ResultLine);
     ++ Offset;
     ++ Line;
    }
   }
   else
   {
    splitSource(Node, context, analysedText);
   }
  }
  Node  = Node->fellowBehind_get();
 }
}







/* @MRTZ_describe reassembleSource

*/
String_imp Prcs_Trn_Directive::reassembleSource(map<int,bool>*     commentOut,
                                                list<_s_TextLine>* splitSource,
                                                bool               restoreEmtyLines)
{
 String_imp  ReturnValue   = "";

 if(commentOut  == nullptr)
  commentOut    = &(Att.CommentOut);
 if(splitSource == nullptr)
  splitSource = &(Att.SplitedSource);

 bool CommentMode    = true;
 bool UseLineComment = true;

 if(Att.CommentEnd == "")
  UseLineComment = true;
 else
  UseLineComment = false;

 int                         Offset     = TextMakeup.StartLine;
 list<_s_TextLine>::iterator Line       = splitSource->begin();
 list<_s_TextLine>::iterator LineBefore = splitSource->end();
 while(Line != splitSource->end())
 {
  while( (restoreEmtyLines == true)
        &&(Offset < ((*Line).LineNumber -1))
       )
  {
   if((CommentMode == true)&&(UseLineComment == false))
   {
    ReturnValue =   ReturnValue
                 + Att.CommentEnd;
    CommentMode = false;
   }
   ReturnValue = ReturnValue + "\n";
   ++ Offset;
  }
  if(   ((commentOut->find((*Line).LineNumber)) != commentOut->end())
      &&((*commentOut)[(*Line).LineNumber]      != true)
    )
  {
   if((CommentMode == true)&&(UseLineComment == false))
   {
    ReturnValue =   ReturnValue
                 + Att.CommentEnd + "\n";
    CommentMode = false;
    ++ Offset;
   }
   else if (ReturnValue != "")
   {
    ReturnValue = ReturnValue + "\n";
    ++ Offset;
   }
  }
  else if(UseLineComment == false)
  {
   if(CommentMode == false)
   {
    ReturnValue =   ReturnValue + "\n"
                 + Att.CommentBegin;
    CommentMode = true;
    ++ Offset;
   }
   else
   {
    ReturnValue = ReturnValue + "\n";
    ++ Offset;
   }
#if defined(DEBUG_OUTPUT)
   cout << "Line(" << (*Line).LineNumber << ") "<< (*Line).Content << endl;
#endif //DEBUG_OUTPUT

  }
  else // UseLineComment is true
  {
   if(   (LineBefore              == splitSource->end())
      ||((LineBefore->LineNumber) <  (Line->LineNumber)  )
     )
   {
    ReturnValue =   ReturnValue + "\n"
                 + Att.CommentBegin;
    (*Line).Content = replacePartString((*Line).Content,
                                        "\n",
                                        "\n"+ Att.CommentBegin,false);
    ++ Offset;
   }

  }

#if defined(DEBUG_OUTPUT)
   cout << "Line(" << (*Line).LineNumber << ") "<< (*Line).Content << endl;
#endif //DEBUG_OUTPUT

  ReturnValue =   ReturnValue
               + (*Line).Content;

  size_t Pos  = 0;
  while(((*Line).Content).find("\n",Pos)<((*Line).Content).size())
  {
   Pos = (*Line).Content.find("\n",Pos) + 1;
   ++ Offset;
  }
  LineBefore = Line;
  ++ Line ;
 }
 if((CommentMode == true)&&(UseLineComment == false))
 {
  ReturnValue =   ReturnValue
               + Att.CommentEnd;
 // CommentMode = false;
 }

 return(ReturnValue);
}




/* @MRTZ_describe remerge

*/
void Prcs_Trn_Directive::remerge(const char* common,
                                 const char* variant,
                                 const char* variantName)
{
 XML_DataModel* CommonDoc = new XML_DataModel();
 if(CommonDoc->load(common) == true)//common result exists
 {
  XML_DataModel* VariantDoc = new XML_DataModel();
  if(VariantDoc->load(variant) == true)//common result exists
  {
   DataAssociation*                      CommonDocNew     = nullptr;
   DataAssociation*                      VariantDocNew    = nullptr;
   map<int, map<int ,XML_Node > >        VariantTable;
   map<int, map<int ,DataAssociation*> > VariantTableNew;

   _getLeaveTable(VariantDoc->rootNode().firstGet(XML_Node::Element()), VariantDocNew, &VariantTable, &VariantTableNew);
#if defined(DEBUG_OUTPUT)
   cout << "VariantTable.size(): " << VariantTable.size() << endl;
#endif
   _merge(CommonDoc->rootNode().firstGet(XML_Node::Element()), CommonDocNew, &VariantTable, &VariantTableNew, variantName);
   _add(CommonDoc->rootNode().firstGet(XML_Node::Element()), CommonDocNew, &VariantTable, &VariantTableNew, variantName);
   CommonDoc->save(common);
  }
  else
  {
   cout << "the variant-result is not existing: " << variant << endl;
  }
  delete VariantDoc;
 }
 else // no common result was found
 {
  if(CommonDoc->load(variant) == true) // special result exits
  {
   CommonDoc->save(common); // save a copy of the special result as common result
   cout << "the common result is not existing   : " << common  << endl;
   cout << "a variant will be used as substitude: " << variant << endl;
  }
  else // the special result exist not also
  {
   cout << "neither common-result is existing: " << common  << endl;
   cout << "   nor variant-result is existing: " << variant << endl;
  }
 }
 delete CommonDoc;

}





/* @MRTZ_describe _reconstructSource

   @MRTZ_describe local_declarations

   @MRTZ_describe  iterate_over_lines

   @MRTZ_describe iterate_over_line_parts

   @MRTZ_describe build_code_lines

   @MRTZ_describe define_MinCol

*/
String_imp Prcs_Trn_Directive::_reconstructSource(DataAssociation*             root,
                                                  TiPa_DataModel* context)
{
 String_imp       ReturnValue  = "";

#if defined(DEBUG_OUTPUT)
 cout << "assemble Code-Lines : Code with spaces" << endl;
 ReturnValue->Print(stdout,1);
 cout << endl;
#endif //DEBUG_OUTPUT
 DataAssociation* Line = nullptr;
 DataAssociation* Code = _getCodeFragments(root, context, TextMakeup.StartColumn);
 if(Code != nullptr)
 {
   Line = Code->contractorFirst_get();
 }
 else
 {
//  cout<< code is not defined"<<endl;
 }

 TiPa_Data* RootData = root->data_get();

 if(RootData != nullptr)
 {
  while(  (Line     != nullptr)
       )
  {
   DataAssociation* Fragment = Line->contractorFirst_get();
   while(Fragment != nullptr)
   {
    TiPa_Data* FragmentData = Fragment->data_get();
    if(  (FragmentData != nullptr)
       && STRINGS_ARE_EQUAL(FragmentData->userName_get(),"SP")
      )
     ReturnValue = ReturnValue + " ";
    else
     ReturnValue = ReturnValue + FragmentData->getContent();
    Fragment = Fragment->fellowBehind_get();
   }
   Line = Line->fellowBehind_get();
   if(Line != nullptr)
    ReturnValue = ReturnValue + "\n";
  }

  if(  (STRINGS_ARE_EQUAL(RootData->userName_get(), "p_define"))
     ||(STRINGS_ARE_EQUAL(RootData->userName_get(), "p_undefine"))
     ||(STRINGS_ARE_EQUAL(RootData->userName_get(), "p_include"))
     ||(STRINGS_ARE_EQUAL(RootData->userName_get(), "p_pragma"))
     ||(STRINGS_ARE_EQUAL(RootData->userName_get(), "p_line"))
     ||(STRINGS_ARE_EQUAL(RootData->userName_get(), "p_error"))
     ||(STRINGS_ARE_EQUAL(RootData->userName_get(), "p_warning"))
     ||(STRINGS_ARE_EQUAL(RootData->userName_get(), "p_endif"))
    )
  {
   if(ReturnValue.find("//") != String_imp::npos)
   {
    ReturnValue = replacePartString(ReturnValue,"//","/*");
    ReturnValue = ReturnValue + "*/";
   }
   if(STRINGS_ARE_EQUAL(RootData->userName_get(), "p_define"))
    ReturnValue = ReturnValue + " #;";
   ReturnValue = ReturnValue + " #preproend";
   ReturnValue = replacePartString(ReturnValue,"\\"," ");
  }
 }

 return(ReturnValue);
}

/* @MRTZ_describe _tryToParse

*/
bool Prcs_Trn_Directive::_tryToParse(DataAssociation*             root,
                                     TiPa_DataModel* context)
{
 bool              ReturnValue = false;
// list<_s_TextLine>::iterator Line;
// String_imp        SourcePart;

 if(Att.TestParser != nullptr)
 {
  list<_s_TextLine> AnalysedText;
  map<int,bool>     CommentOut;
  splitSource(root, context, &AnalysedText);
  list<_s_TextLine>::iterator Line = AnalysedText.begin();
  while(Line != AnalysedText.end())
  {
   CommentOut[Line->LineNumber] = false;
   ++ Line;
  }
  String_imp SourcePart = reassembleSource(&CommentOut, &AnalysedText, false);

  if(SourcePart != "")
   ReturnValue = Att.TestParser->checkTextToParse(SourcePart);
 }
 return(ReturnValue);
}





/* @MRTZ_describe _merge

*/
void Prcs_Trn_Directive::_merge(XML_Node                               common,
                                DataAssociation*                       commonNew,
                                map<int, map<int ,XML_Node > >*        variantTable,
                                map<int, map<int ,DataAssociation*> >* variantTableNew,
                                String_imp                             variantName)
{

 if(  (common.typeGet()  == XML_Data::NT_Element)
    &&(!(variantTable->empty()))
   )
  {
//   DataAssociation*                   CommonNodeNew       = nullptr;
//   const char*                        Text                = nullptr;

   XML_Node  CommonNode    = common.firstGet(XML_Node::Element());
   DataAssociation* CommonNodeNew = commonNew->contractorFirst_get();
   while(  (CommonNode.valid() == true)//    != nullptr)
         &&(CommonNodeNew      != nullptr)
        )
   {
    if(Att.MergeLevel.find(CommonNode.valueGet()) != Att.MergeLevel.end())
    {
     XML_Node  Node = CommonNode.lastGet(XML_Node::Element(XML_Search::Value,Att.VariantID.c_str()));
     if(Node.valid() == false)// == nullptr)
     {
      Node = CommonNode.lastAdd(XML_Data::NT_Element);
      Node.valueSet(Att.VariantID.c_str());
      Node.attributeSet("name","Common");
      XML_Node  Child = CommonNode.firstGet(XML_Node::Element());
      while(Child.valid() == true)// != NULL)
      {
       XML_Node  NextChild = Child.behindGet(XML_Node::Element());
       Child = CommonNode.nodeCut(Child);
       Node.lastAdd(Child);
       Child = NextChild;
      }
     }

     int         SourceLine = 0;
     const char* Text       = CommonNode.attributeGet("L");
     if(Text != nullptr)
      SourceLine = stringToNumber(String_imp(Text));
     else
      SourceLine = -1;

     if(variantTable->find(SourceLine) != variantTable->end())
     {
      int SourceColl = 0;
      Text = CommonNode.attributeGet("C");
      if(Text != nullptr)
       SourceColl = stringToNumber(String_imp(Text));
      else
       SourceColl = -1;

      map<int ,XML_Node > VariantLine = (*variantTable)[SourceLine];
      if(VariantLine.find(SourceColl) != VariantLine.end())
      {
       Node = CommonNode.lastAdd(XML_Data::NT_Element);
       XML_Node  VariantNode = VariantLine[SourceColl];
       Node.valueSet(Att.VariantID.c_str());
       Node.attributeSet("name",variantName.c_str());
       XML_Node  Child = VariantNode.firstGet(XML_Node::Element());
       while(Child.valid() == true)// != NULL)
       {
        XML_Node  NextChild = Child.behindGet(XML_Node::Element());
        Child = VariantNode.nodeCut(Child);
        Node.lastAdd(Child);
        Child = NextChild;
       }
      }
     }
    }
    else
    {
     _merge(CommonNode, CommonNodeNew, variantTable, variantTableNew, variantName);
    }
    CommonNode    = CommonNode.behindGet(XML_Node::Element());
    CommonNodeNew = CommonNodeNew->fellowBehind_get();
   }
  }
}


/* @MRTZ_describe _getLeaveTable

*/
void Prcs_Trn_Directive::_getLeaveTable(XML_Node                               source,
                                        DataAssociation*                       rootNew,
                                        map<int, map<int ,XML_Node > >*        table,
                                        map<int, map<int ,DataAssociation*> >* tableNew)
{
// map<int ,XML_Node >  Line;
// const char*          L = nullptr;
// const char*          C = nullptr;

 if(  (source.valid() == true)//  != nullptr)
    &&(rootNew        != nullptr)
   )
 {
  XML_Node         Child = source.firstGet(XML_Node::Element());
  DataAssociation* Node  = rootNew->contractorFirst_get();
  while(  (Child.valid() == true)// != nullptr)
        &&(Node          != nullptr)
       )
  {

#if defined(DEBUG_OUTPUT)
   cout << endl << Child->ValueStr() << endl;
#endif

// @MRTZ_ifElseChain
   if(Att.MergeLevel.find(Child.valueGet()) != Att.MergeLevel.end())
   {
    const char* L  = Child.attributeGet("L");
    if(L != nullptr)
    {
#if defined(DEBUG_OUTPUT)
     cout <<"L"<<L;
#endif
     map<int ,XML_Node > Line = (*table)[stringToNumber(String_imp(L))];
     const char*         C    = Child.attributeGet("C");
     if(C != nullptr)
     {
#if defined(DEBUG_OUTPUT)
      cout <<"C"<<C;
#endif
      Line[stringToNumber(String_imp(C))]     = Child;
      (*table)[stringToNumber(String_imp(L))] = Line;
     }
    }
   }
   else
   {
    _getLeaveTable(Child, Node, table, tableNew);
   }
#if defined(DEBUG_OUTPUT)
   cout << endl;
#endif
   Child = Child.behindGet(XML_Node::Element());
   Node  = Node->fellowBehind_get();
  }
 }
 else
 {
  cout << "invalid xml-node found";
 }

}

/* @MRTZ_describe _add

*/
void Prcs_Trn_Directive::_add(XML_Node                               common,
                              DataAssociation*                       commonNew,
                              map<int, map<int ,XML_Node > >*        variantTable,
                              map<int, map<int ,DataAssociation*> >* variantTableNew,
                              String_imp                             variantName)
{
 map<int, map<int ,XML_Node > >::iterator        Line    = variantTable->begin();
 map<int, map<int ,DataAssociation*> >::iterator LineNew = variantTableNew->begin();
 while(Line != variantTable->end())
 {
  map<int ,XML_Node >::iterator         Coll    = Line->second.begin();
  map<int ,DataAssociation*>::iterator  CollNew = LineNew->second.begin();
  while(Coll != Line->second.end())
  {
   XML_Node         Element    = Coll->second;
   DataAssociation* ElementNew = CollNew->second;

   if(  (Element.firstGet().valid()              == true)// != nullptr)
      &&(Element.lastGet().valid()               == true)// != nullptr)
      &&(ElementNew->contractorFirst_get()       != nullptr)
      &&(ElementNew->contractorLast_get()        != nullptr)
      &&(Att.MergeLevel.find(Element.valueGet()) != Att.MergeLevel.end())
///  @todo replace    &&(Att.MergeLevel.find(ElementNew->ValueStr()) != Att.MergeLevel.end())
     )
   {
    list<XML_Node > Ansisters;
                    Ansisters.clear();  /// @todo check if deletable
    XML_Node        Ansister = Element.preGet();

    list<DataAssociation*> AnsistersNew;
    DataAssociation*       AnsisterNew = ElementNew->sponsor_get();

    while(  (Ansister.typeGet() == XML_Data::NT_Element)
          &&(AnsisterNew        != nullptr)
         )
    {
#if defined(DEBUG_OUTPUT)
    cout << "Ansister: " << Ansister->ValueStr() <<endl;
#endif

     Ansisters.push_back(Ansister);
     Ansister = Ansister.preGet();

     AnsistersNew.push_back(AnsisterNew);
     AnsisterNew = AnsisterNew->sponsor_get();
    }

    Ansister    = Ansisters.back();
    AnsisterNew = AnsistersNew.back();

    Ansisters.pop_back();
    AnsistersNew.pop_back();
    if(  (common.valueGet()                    == Ansister.valueGet())
       &&(_compareNodes(common,   Ansister)    == 0                   )
       &&(_compareNodes(commonNew,AnsisterNew) == 0                   )
      )
    {
     XML_Node  CommonParent = _lastCommonAnsister(&Ansisters,common);
     XML_Node  CommonChild  = CommonParent.firstGet(XML_Node::Element());

     DataAssociation* CommonParentNew = _lastCommonAnsister(&AnsistersNew,commonNew);
     DataAssociation* CommonChildNew  = CommonParentNew->contractorFirst_get();

     while((CommonChild.valid() == true)/* != nullptr)*/&&(CommonChildNew != nullptr))

     {
      if(  (_compareNodes(CommonChild,   Element)    == 1)
         &&(_compareNodes(CommonChildNew,ElementNew) == 1)
        )
      {

       /// @todo change sequence for use of association
       XML_Node  Node = Element.lastAdd(XML_Data::NT_Element);
                 Node.attributeSet("name",variantName.c_str());
       XML_Node  Child = Element.firstGet(XML_Node::Element());
       while(Child.valid())// != NULL)
       {
        XML_Node  NextChild = Child.behindGet(XML_Node::Element());
        Child = Element.nodeCut(Child);
        Node.lastAdd(Child);
        Child = NextChild;
       }
       Node = CommonParent.beforeAdd(CommonChild,XML_Data::NT_Element);
       Node.attributeSet("L",Element.attributeGet("L"));
       Node.attributeSet("C",Element.attributeGet("C"));
       Child = Element.firstGet(XML_Node::Element());
       while(Child.valid())// != NULL)
       {
        XML_Node  NextChild = Child.behindGet(XML_Node::Element());
        Child = Element.nodeCut(Child);
        Node.lastAdd(Child);
        Child = NextChild;
       }
       break;
      }
      CommonChild = CommonChild.behindGet(XML_Node::Element());
      CommonChildNew = CommonChildNew->fellowBehind_get();
     }
    }
    else
    {
    }
   }
   ++Coll;
  }
  ++Line;
 }

}



/* @MRTZ_describe _lastCommonAnsister

*/
XML_Node  Prcs_Trn_Directive::_lastCommonAnsister(list<XML_Node >* variantAnsisters,
                                                  XML_Node         commonRoot)
{
 XML_Node   ReturnValue;

 if(!(variantAnsisters->empty()))
 {
  XML_Node  Ansister = variantAnsisters->back();
                       variantAnsisters->pop_back();

#if defined(DEBUG_OUTPUT)
  cout << "commonRoot: " << commonRoot->ValueStr() <<endl;
#endif

  XML_Node  CommonParent = commonRoot.firstGet(XML_Node::Element());
  while(CommonParent.valid() == true)// != nullptr)
  {
   if(  (CommonParent.valueGet()==Ansister.valueGet())
      &&(_compareNodes(CommonParent,Ansister) == 0)
     )
   {
    ReturnValue =_lastCommonAnsister(variantAnsisters, CommonParent);
    break;
   }
   CommonParent = CommonParent.behindGet(XML_Node::Element());
  }
 }

 if( ReturnValue.valid())// == nullptr)
  ReturnValue = commonRoot;

 return(ReturnValue);
}






/* @MRTZ_describe _lastCommonAnsister

*/
Prcs_Transformation::DataAssociation* Prcs_Trn_Directive::_lastCommonAnsister(list<DataAssociation*>* variantAnsisters,
                                                                              DataAssociation*        commonRoot)
{
 DataAssociation*  ReturnValue  = nullptr;


 if(!(variantAnsisters->empty()))
 {
  DataAssociation* Ansister     = variantAnsisters->back();
  variantAnsisters->pop_back();

#if defined(DEBUG_OUTPUT)
  cout << "commonRoot: " << commonRoot->ValueStr() <<endl;
#endif

  DataAssociation* CommonParent = commonRoot->contractorFirst_get();
  while(CommonParent != nullptr)
  {
   TiPa_Data* ParentData   = CommonParent->data_get();
   TiPa_Data* AnsisterData = Ansister->data_get();


   if(  ((ParentData                 != nullptr) && (AnsisterData                 != nullptr))
      &&((ParentData->userName_get() != nullptr) && (AnsisterData->userName_get() != nullptr))
      &&( strlen(ParentData->userName_get())     == strlen(AnsisterData->userName_get()))
      &&(  strstr(ParentData->userName_get(),AnsisterData->userName_get())
         ==ParentData->userName_get())
      &&(_compareNodes(CommonParent,Ansister) == 0)
     )
   {
    ReturnValue =_lastCommonAnsister(variantAnsisters, CommonParent);
    break;
   }
   CommonParent = CommonParent->fellowBehind_get();
  }
 }

 if( ReturnValue == nullptr)
  ReturnValue = commonRoot;

 return(ReturnValue);
}








/* @MRTZ_describe _compareNodes

*/
int Prcs_Trn_Directive::_compareNodes(XML_Node        node1,
                                      XML_Node        node2)
{
 int          ReturnValue = 0;


 const char* L_1    = node1.attributeGet("L");
 int         Line_1 = stringToNumber(String_imp(L_1));
 const char* C_1    = node1.attributeGet("C");
 int         Coll_1 = stringToNumber(String_imp(C_1));

 const char* L_2    = node2.attributeGet("L");
 int         Line_2 = stringToNumber(String_imp(L_2));
 const char* C_2    = node2.attributeGet("C");
 int         Coll_2 = stringToNumber(String_imp(C_2));

// @MRTZ_ifElseChain
 if     (  (Line_1  < Line_2)
         ||(  (Line_1 == Line_2)
            &&(Coll_1  < Coll_2)
           )
         )
  ReturnValue = -1;
 else if(  (Line_1 == Line_2)
         &&(Coll_1 == Coll_2)
        )
  ReturnValue = 0;
 else if(  (  (Line_1 == Line_2)
            &&(Coll_1  > Coll_2)
           )
         ||(Line_1  > Line_2)
        )
  ReturnValue = 1;


 return(ReturnValue);
}








/* @MRTZ_describe _compareNodes

*/
int Prcs_Trn_Directive::_compareNodes(DataAssociation* node1,
                                      DataAssociation* node2)
{
 int        ReturnValue = 0;
 TiPa_Data* Data1       = node1->data_get();

 int Line_1 = 0;
 if(  (Data1            != nullptr)
    &&(Data1->lineGet() != nullptr)
   )
  Line_1 = stringToNumber(String_imp(Data1->lineGet()));

 int Column_1 = 0;
 if(  (Data1              != nullptr)
    &&(Data1->columnGet() != nullptr)
   )
  Column_1 = stringToNumber(String_imp(Data1->columnGet()));

 TiPa_Data* Data2 = node2->data_get();

 int Line_2 = 0;
 if(  (Data2            != nullptr)
    &&(Data2->lineGet() != nullptr)
   )
  Line_2 = stringToNumber(String_imp(Data2->lineGet()));

 int Column_2 = 0;
 if(  (Data2              != nullptr)
    &&(Data2->columnGet() != nullptr)
   )
  Column_2 = stringToNumber(String_imp(Data2->columnGet()));

// @MRTZ_ifElseChain
 if     (  (Line_1  < Line_2)
         ||(  (Line_1   == Line_2)
            &&(Column_1  < Column_2)
           )
        )
  ReturnValue = -1;
 else if(  (Line_1   == Line_2)
         &&(Column_1 == Column_2)
        )
  ReturnValue = 0;
 else if(  (  (Line_1   == Line_2)
            &&(Column_1  > Column_2)
           )
         ||(Line_1  > Line_2)
        )
  ReturnValue = 1;


 return(ReturnValue);
}


/* @MRTZ_describe _getText

   @MRTZ_describe save_text

*/
void Prcs_Trn_Directive::_getText(DataAssociation*                   source,
                                  map<int, list<DataAssociation*> >* textNew,
                                  TiPa_DataModel*       context)
{
 if(  (source    !=  nullptr)
   )
 {
   String_imp       Text         = "";
   bool             CarierOfText = false;
// @MRTZ_ifElseChain
    if  (ASSOCIATION_IS_LEAF(source))
    {
     /// @todo change to use with association. what is a text element ?????
     TiPa_Data* Data = source->data_get();
     if(Data != nullptr)
      Text = Text + String_imp(Data->getContent());
     else
      cout<<"no data found!"<< endl;
     CarierOfText = true;
    }
    else if(ASSOCIATION_IS_NOT_LEAF(source))
    {
     DataAssociation* Child = source->contractorFirst_get();
     while(  (Child    != nullptr)
          )
     {
       _getText(Child, textNew, context);
      Child = Child->fellowBehind_get();
     }
    }
    else
    {
     TiPa_Data* Data = source->data_get();
     cout << "invalid type of xml-node found: " << (Data->userName_get());
    }

   if(CarierOfText == true)
   {
// @MRTZ_exclude save_text
// @MRTZ_beginBlock
    Text = replacePartString(Text,"\r","");
    Text = replacePartString(Text,"\n","");

    TiPa_Data* Data = source->data_get();
    TiPa_Data* FragmentData = context->data_create();
    DataAssociation* FragmentNew = context->fellow_create(FragmentData);
    FragmentData->userName_set(Data->userName_get()) ;

    FragmentData->lineSet(atoi(Data->lineGet()));
    FragmentData->columnSet(atoi(Data->columnGet()));

    FragmentData->Begin = FragmentData->secondaryData_add("TextContent",Text.c_str());
    FragmentData->End   = FragmentData->Begin + strlen(FragmentData->Begin);

    ((*textNew)[atoi(FragmentData->lineGet())]).push_back(FragmentNew);
// @MRTZ_endBlock
   }
 }
 else
 {
  cout << "invalid xml-node found";
 }

}






/* @MRTZ_describe _getCodeFragments

   @MRTZ_describe local_declarations

   @MRTZ_describe  iterate_over_lines

   @MRTZ_describe iterate_over_line_parts

   @MRTZ_describe build_code_lines

   @MRTZ_describe define_MinCol

*/
DataAssociation* Prcs_Trn_Directive::_getCodeFragments(DataAssociation*  sourceNew,
                                                       TiPa_DataModel*   context,
                                                       int               minCol)
{
// @MRTZ_exclude local_declarations
// @MRTZ_beginBlock
 DataAssociation*                         ReturnValueNew = nullptr;

// map<int, list<DataAssociation*> >           LinesNew;
// map<int, list<DataAssociation*> >::iterator LineNew;

// list <int>                                  Numbers;
// list <int>::iterator                        Number;

// list<DataAssociation*>                      FragmentsNew;
// list<DataAssociation*>::iterator            FragmentNew;


// int                                         Collumn      = 0;
// const char*                                 Text         = nullptr;
// @MRTZ_endBlock

 if(sourceNew != nullptr)
 {
  TiPa_Data* ReturnValueData = context->data_create();
  ReturnValueNew = context->fellow_create(ReturnValueData);
//  ReturnValueData->userName_set((char*) ReturnValueData->secondaryData_add("UserName", "CODE")) ;
  ReturnValueData->userName_set("CODE") ;

  map<int, list<DataAssociation*> > LinesNew;
  _getText(sourceNew, &LinesNew, context);

  list <int>  Numbers;
  map<int, list<DataAssociation*> >::iterator LineNew = LinesNew.begin();
  while(LineNew != LinesNew.end())
  {
     /// @todo change to use with association.
#if defined(DEBUG_OUTPUT)
   cout << "assemble Code-Lines : Line->first" << endl;
   cout << endl;
#endif //DEBUG_OUTPUT

   Numbers.push_back(LineNew->first);
   ++LineNew;
  }
  Numbers.sort();

  list <int>::iterator Number = Numbers.begin();
// @MRTZ_exclude iterate_over_lines
  while(Number != Numbers.end())
  {
     /// @todo change to use with association.
   TiPa_Data* CodeLineData = context->data_create();
   DataAssociation* CodeLineNew = context->fellow_create(CodeLineData);
//   CodeLineData->userName_set((char*) CodeLineData->secondaryData_add("UserName", "LINE"));
   CodeLineData->userName_set("LINE");

   CodeLineData->lineSet(*Number);
   CodeLineData->columnSet(0);

   list<DataAssociation*>           FragmentsNew = LinesNew[(*Number)];
   list<DataAssociation*>::iterator FragmentNew  = FragmentsNew.begin();

// @MRTZ_exclude iterate_over_line_parts
//   FragmentCol  = 0;
   int CodeCol      = 0;
   while(FragmentNew != FragmentsNew.end())
   {
    int FragmentCol  = stringToNumber((*FragmentNew)->data_get()->columnGet());
#if defined(DEBUG_OUTPUT)
    cout<<"FragmentCol:"<<FragmentCol<<endl;
#endif //DEBUG_OUTPUT

    DataAssociation* CodeFragmentNew = CodeLineNew->contractorLast_get();
    if(CodeFragmentNew != nullptr)
    {
     CodeCol = stringToNumber(CodeFragmentNew->data_get()->columnGet());
#if defined(DEBUG_OUTPUT)
     cout<<"CodeCol:"<<CodeCol<<endl;
#endif //DEBUG_OUTPUT
     while(  (CodeCol         >  FragmentCol)
           &&(CodeFragmentNew != nullptr)
          )
     {
      CodeFragmentNew = CodeFragmentNew->fellowBefore_get();
      if(CodeFragmentNew != nullptr)
       CodeCol = stringToNumber(CodeFragmentNew->data_get()->columnGet());
#if defined(DEBUG_OUTPUT)
      cout<<"CodeCol:"<<CodeCol<<endl;
#endif //DEBUG_OUTPUT
     }
     if(CodeFragmentNew != nullptr)
     {
      CodeLineNew->contractorBehind_add(CodeFragmentNew,(*FragmentNew)) ;
     }
     else
     {
      CodeFragmentNew = CodeLineNew->contractorFirst_get();
      CodeLineNew->contractorBefore_add(CodeFragmentNew,(*FragmentNew)) ;
     }
    }
    else
    {
     CodeLineNew->contractorLast_add((*FragmentNew));
    }
    ++FragmentNew ;
   }

   ReturnValueNew->contractorLast_add(CodeLineNew);
   ++Number ;
  }

#if defined(DEBUG_OUTPUT)
   cout << "assemble Code-Lines : Code A" << endl;
#endif //DEBUG_OUTPUT


// @MRTZ_exclude build_code_lines
// @MRTZ_beginBlock

// @MRTZ_exclude define_MinCol
// @MRTZ_beginBlock
   DataAssociation* SortedLineNew = ReturnValueNew->contractorFirst_get();
   while(  (SortedLineNew != nullptr)
         &&(minCol        >  0   )
        )
   {
    int CodeCol = stringToNumber(SortedLineNew->contractorFirst_get()->data_get()->columnGet());
    if(minCol > CodeCol)
     minCol = CodeCol;
    SortedLineNew = SortedLineNew->fellowBehind_get();
   }
// @MRTZ_endBlock

   SortedLineNew = ReturnValueNew->contractorFirst_get();
   while(SortedLineNew != nullptr)
   {
    TiPa_Data* SortedLineData = SortedLineNew->data_get();
    SortedLineData->columnSet(minCol);

    DataAssociation * CodeFragmentNew = SortedLineNew->contractorFirst_get();
    int CodeCol = stringToNumber(CodeFragmentNew->data_get()->columnGet());
//    for(int Collumn = minCol; Collumn != CodeCol; Collumn ++)
    int Collumn = minCol;
    while(Collumn != CodeCol)
    {
     TiPa_Data* SpaceData = context->data_create();
//     SpaceData->userName_set((char*) SpaceData->secondaryData_add("UserName",SP.c_str())) ;
     SpaceData->userName_set(SP.c_str()) ;
     DataAssociation* SpaceNew = context->fellow_create(SpaceData);
     SortedLineNew->contractorBefore_add(CodeFragmentNew,SpaceNew);
     ++ Collumn;
    }
    const char* Text = CodeFragmentNew->data_get()->getContent();
    if(Text != nullptr)
     Collumn = CodeCol + String_imp(Text).size();
    else
     Collumn = CodeCol;
    CodeFragmentNew = CodeFragmentNew->fellowBehind_get();

    while(CodeFragmentNew != nullptr)
    {
     CodeCol = stringToNumber(CodeFragmentNew->data_get()->columnGet());

//     for(Collumn = Collumn; Collumn < CodeCol; Collumn ++)
     while(Collumn < CodeCol)
     {
      TiPa_Data* SpaceData = context->data_create();
//      SpaceData->userName_set((char*) SpaceData->secondaryData_add("UserName",SP.c_str()));
      SpaceData->userName_set(SP.c_str());
      DataAssociation* SpaceNew = context->fellow_create(SpaceData);
      SortedLineNew->contractorBefore_add(CodeFragmentNew,SpaceNew);
      ++ Collumn;
     }
     Text = CodeFragmentNew->data_get()->getContent();
     if(Text != nullptr)
      Collumn = CodeCol + String_imp(Text).size();
     else
      Collumn = CodeCol;

     CodeFragmentNew = CodeFragmentNew->fellowBehind_get();
    }
    SortedLineNew = SortedLineNew->fellowBehind_get();
   }
// @MRTZ_endBlock
 }
 else
 {
 }
 return(ReturnValueNew);
}





#ifndef DOXYGEN
//};};};
#endif //DOXYGEN
