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
    13.09.2011     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    13.09.2011...  @I Eckard Klotz
 @I Changes are documented in the comment of the changed element
 @TabEnd

*/


#include "expression.h"
//#include "AssociationFellowship.hpp"
//#include "AssociationSponsor.hpp"
//#include "ASS_Model.hpp"
#include "TiPa_DataModel.h"

#include "StringC_help.h"


#if !defined( DOXYGEN)
//namespace CL_EXPRESSION {
#endif //DOXYGEN

 const String_imp EMPTYSTRING = "__EMPTYSTRING__";

/* @MRTZ_describe Prsd_Expression

*/
Prsd_Expression::Prsd_Expression(void)
{
 Att.Replacement["\n"]       ="";
 Att.Replacement["\t"]       ="";
 Att.Replacement["\r"]       ="";
 Att.Replacement[" "]        ="";
 Att.Replacement[EMPTYSTRING]="";
}


/* @MRTZ_describe ~Prsd_Expression

*/
Prsd_Expression::~Prsd_Expression(void)
{
 Att.UserResult.clear();
 Att.Constant.clear();
 Att.Replacement.clear();
}










/* @MRTZ_describe constant_Set

*/
bool Prsd_Expression::constant_Set(String_imp& name, String_imp& value)
{
 bool ReturnValue = (Att.Constant.find(name) != Att.Constant.end());
 Att.Constant[name] = value;

 return(ReturnValue);
}

/* @MRTZ_describe constant_Get

*/
bool Prsd_Expression::constant_Get(String_imp name, String_imp* value)
{
 bool ReturnValue = (Att.Constant.find(name) != Att.Constant.end());
 if(ReturnValue == true)
  (*value) = (Att.Constant[name]);
 else
  (*value) = "";
 return(ReturnValue);
}

/* @MRTZ_describe constant_Clear


*/
bool Prsd_Expression::constant_Clear(String_imp name)
{
 bool ReturnValue = (Att.Constant.find(name) != Att.Constant.end());
 if(ReturnValue == true)
  Att.Constant.erase(name);

 return(ReturnValue);
}




/* @MRTZ_describe userResult_Set

*/
bool Prsd_Expression::userResult_Set(const String_imp& check,
                                     const String_imp& value)
{
#if defined(DEBUG_OUTPUT)
 cout << "given term: |" << check << "|" << endl;
#endif //DEBUG_OUTPUT
 String_imp Name = check;

 map<String_imp, String_imp>::iterator Current = Att.Replacement.begin();
 while(Current != Att.Replacement.end())
 {
  Name = replacePartString(Name,Current->first,Current->second);
#if defined(DEBUG_OUTPUT)
  cout << "|" << Current->first << "|" << Current->second << "|";
#endif //DEBUG_OUTPUT
  ++Current  ;
 }

#if defined(DEBUG_OUTPUT)
 cout << "used term: |" << Name << "|" << endl;
#endif //DEBUG_OUTPUT

 bool ReturnValue = (Att.UserResult.find(Name) != Att.UserResult.end());
 Att.UserResult[Name] = value;

 return(ReturnValue);
}

/* @MRTZ_describe userResult_Get

*/
bool Prsd_Expression::userResult_Get(String_imp check, String_imp* value)
{
 map<String_imp, String_imp>::iterator Current;

#if defined(DEBUG_OUTPUT)
 cout << "given term: |" << check << "|" << endl;
#endif //DEBUG_OUTPUT

 Current = Att.Replacement.begin();
 while(Current != Att.Replacement.end())
 {
  check = replacePartString(check,Current->first,Current->second);
  ++Current  ;
 }

#if defined(DEBUG_OUTPUT)
 cout << "used term: |" << check << "|" << endl;
#endif //DEBUG_OUTPUT

#if defined(DEBUG_OUTPUT)
 Current = Att.UserResult.begin();
 while(Current != Att.UserResult.end())
 {
  cout << "term: |" << Current->first << "| value: |" << Current->second << "|" << endl;
  ++Current;
 }
#endif //DEBUG_OUTPUT

 bool ReturnValue = (Att.UserResult.find(check) != Att.UserResult.end());
 if(ReturnValue == true)
  (*value) = (Att.UserResult[check]);
 else
  (*value) = "";

#if defined(DEBUG_OUTPUT)
 cout << "Result(" << ReturnValue << ") " << (*value) << endl;
#endif //DEBUG_OUTPUT

 return(ReturnValue);
}


/* @MRTZ_describe userResultXML_Get

*/
bool Prsd_Expression::userResultXML_Get(DataAssociation* check, String_imp* value)
{
 String_imp Check       = xmlToText(check, &Att.Replacement);
 bool       ReturnValue = userResult_Get(Check, value);
#if defined(DEBUG_OUTPUT)
 cout << "term to check: |" << Check << "| value: |" << (*value) << "|" << endl;
#endif //DEBUG_OUTPUT

 return(ReturnValue);
}




/* @MRTZ_describe userResultClear

*/
bool Prsd_Expression::userResult_Clear(String_imp check)
{
 bool ReturnValue = false;
 map<String_imp, String_imp>::iterator Current;

 Current = Att.Replacement.begin();
 while(Current != Att.Replacement.end())
 {
  check = replacePartString(check,Current->first,Current->second);
  ++Current  ;
 }

 ReturnValue = (Att.UserResult.find(check) != Att.UserResult.end());
 if(ReturnValue == true)
  Att.UserResult.erase(check);

 return(ReturnValue);
}





/* @MRTZ_describe testExpression

*/
_s_TestRet Prsd_Expression::testExpression(DataAssociation* expression,
                                           bool*            unknown)
{
 _s_TestRet     ReturnValue = {"",VOID};

 (*unknown) = false;
 TiPa_Data* Data = expression->data_get();
 if(Data != nullptr)
 {
// @MRTZ_ifElseChain
  if(STRINGS_ARE_EQUAL(Data->userName_get(), "expression"))
  {

   DataAssociation* Child = expression->contractorFirst_get();
   while(Child != nullptr)
   {
    bool Unknown     = false;
    ReturnValue = _testLogicalOr(Child,&Unknown);
    if(Unknown == true)
     (*unknown) = true;

    Child  = Child->fellowBehind_get();
    while(Child != nullptr)
     Child = Child->fellowBehind_get();
   }
  }
  else if(STRINGS_ARE_EQUAL(Data->userName_get(), "logical_or_expression"))
  {
   ReturnValue = _testLogicalOr(expression,unknown);
  }
  else if(STRINGS_ARE_EQUAL(Data->userName_get(), "logical_and_expression"))
  {
   ReturnValue = _testLogicalAnd(expression,unknown);
  }
  else if(STRINGS_ARE_EQUAL(Data->userName_get(), "inclusive_or_expression"))
  {
   ReturnValue = _calcInclusiveOr(expression,unknown);
  }
  else if(STRINGS_ARE_EQUAL(Data->userName_get(), "exclusive_or_expression"))
  {
   ReturnValue = _calcExclusiveOr(expression,unknown);
  }
  else if(STRINGS_ARE_EQUAL(Data->userName_get(), "and_expression"))
  {
   ReturnValue = _calcAnd(expression,unknown);
  }
  else if(STRINGS_ARE_EQUAL(Data->userName_get(), "equality_expression"))
  {
   ReturnValue = _testEquality(expression,unknown);
  }
  else if(STRINGS_ARE_EQUAL(Data->userName_get(), "relational_expression"))
  {
   ReturnValue = _testRelational(expression,unknown);
  }
  else if(STRINGS_ARE_EQUAL(Data->userName_get(), "shift_expression"))
  {
   ReturnValue = _calcShift(expression,unknown);
  }
  else if(STRINGS_ARE_EQUAL(Data->userName_get(), "additive_expression"))
  {
   ReturnValue = _calcAdditive(expression,unknown);
  }
  else if(STRINGS_ARE_EQUAL(Data->userName_get(), "multiplicative_expression"))
  {
   ReturnValue = _calcMultiplicative(expression,unknown);
  }
  else if(STRINGS_ARE_EQUAL(Data->userName_get(), "unary_expression"))
  {
   ReturnValue = _testUnary(expression,unknown);
  }
  else
  {
   TiPa_DataModel  ContextModel;       ///< manages the analysed data
   TiPa_Data*      HelpData           = ContextModel.data_create();   // just used for creating help expression
   DataFellow*     HelpExpression     = ContextModel.fellow_create(HelpData);

   HelpExpression->contractorFirst_add(ContextModel.fellow_create(expression));
   ReturnValue = _testUnary(HelpExpression,unknown);
  }
 }
 return(ReturnValue);
}


/* @MRTZ_describe getLogicTerms

*/
map<String_imp,SwitchState_TP>* Prsd_Expression::getLogicTerms(DataAssociation*                expression,
                                                               map<String_imp,SwitchState_TP>* returnValue)
{
 map<String_imp,SwitchState_TP>* ReturnValue = nullptr;
// String_imp                      Term = "";
// bool                            Unknown     = false;
// _s_TestRet                      Result      = {"",VOID};

 if(returnValue == nullptr)
  ReturnValue = new map<String_imp,SwitchState_TP>;
 else
  ReturnValue = returnValue;

 DataAssociation* Child = expression->contractorFirst_get();
 while(Child != nullptr)
 {
  TiPa_Data* Data = Child->data_get();
  if(Data != nullptr)
  {
   if(   STRINGS_ARE_EQUAL(Data->userName_get(), "logical_or_expression")
      || STRINGS_ARE_EQUAL(Data->userName_get(), "logical_and_expression")
      || STRINGS_ARE_EQUAL(Data->userName_get(), "unary_expression")
      || STRINGS_ARE_EQUAL(Data->userName_get(), "subexpression")
      ||(/*   ASSOCIATION_IS_NOT_LEAF(Child)
         &&*/(Child->contractorFirst_get() == Child->contractorLast_get())
         && STRINGS_ARE_NOT_EQUAL(Data->userName_get(), "ID")
         && STRINGS_ARE_NOT_EQUAL(Data->userName_get(), "Number")
         && STRINGS_ARE_NOT_EQUAL(Data->userName_get(), "String")
         &&(strstr(Data->userName_get(),"o_") != Data->userName_get())
        )
     )
   {
    getLogicTerms(Child,ReturnValue);
   }
   else if(  ASSOCIATION_IS_NOT_LEAF(Child)
           &&(strstr(Data->userName_get(),"o_") != Data->userName_get())
          )
   {
    String_imp Term    = xmlToText(Child);
    bool       Unknown = false;
    _s_TestRet Result  = testExpression(Child,&Unknown);
 #if defined(DEBUG_OUTPUT)
    cout<< "Type: " << Result.Type << "  Value: " << Result.Value << "  Unknown=" << Unknown << endl;
 #endif //DEBUG_OUTPUT
 // @MRTZ_ifElseChain
   if     (Result.Value == "true")
    (*ReturnValue)[Term] = TRI_TRUE;
   else if(Result.Value == "false")
    (*ReturnValue)[Term] = TRI_FALSE;
   else if(Unknown == false)
    (*ReturnValue)[Term] = TRI_DEFINED;
   else
    (*ReturnValue)[Term] = TRI_UNDEFINED;
   }
   else
   {}
  }
  Child  = Child->fellowBehind_get();
 }


 return(ReturnValue);
}




/* @MRTZ_describe xmlToText

   @MRTZ_describe evaluate_Childes

   @MRTZ_describe replacements
*/
String_imp Prsd_Expression::xmlToText(DataAssociation*              source,
                                      map<String_imp ,String_imp >* replacement,
                                      list<String_imp>*             returnValue)
{
 String_imp                            ReturnValue = "";
 list<String_imp>                      TempReturn;

 if(source != nullptr)
 {
// @MRTZ_exclude evaluate_Childes
// @MRTZ_beginBlock
   DataAssociation* Child = source->contractorFirst_get();
   while(Child != nullptr)
   {
// @MRTZ_ifElseChain
    if     (  (Child->contractorFirst_get()== nullptr)
            &&(Child->contractorLast_get( )== nullptr)
           )  //child is a leaf node
    {
     String_imp Text = "";
     TiPa_Data* Data = Child->data_get();
     if(Data != nullptr)
      Text = String_imp(Data->getContent());
     else
      Text = "";
     if(replacement != nullptr)
     {
// @MRTZ_exclude replacements
// @MRTZ_beginBlock
      map<String_imp, String_imp>::iterator Current = replacement->begin();
      while(Current != replacement->end())
      {
       Text = replacePartString(Text,Current->first,Current->second);
       ++Current  ;
      }
      if(Text == "" )//use default-value since tailored value is empty
       Text = (*replacement)[EMPTYSTRING];
// @MRTZ_endBlock
     }

     if(returnValue == nullptr)
      TempReturn.push_back(Text);
     else
      returnValue->push_back(Text);
    }
    else  // child has childes
    {
     if(returnValue == nullptr)
      xmlToText(Child, replacement, &TempReturn);
     else
      xmlToText(Child, replacement, returnValue);
    }
    Child = Child->fellowBehind_get();
   }
// @MRTZ_endBlock

 }
 else
 {
  cout << "invalid xml-node found";
 }

 if(returnValue == nullptr)
 {
  list<String_imp>::iterator ReturnPart = TempReturn.begin();
  while(ReturnPart!= TempReturn.end())
  {
   ReturnValue = ReturnValue + (*ReturnPart).c_str();
   ++ReturnPart ;
  }
 }
 else
  ReturnValue = "";

 return(ReturnValue);
}





/* @MRTZ_describe _testUnary

*/
_s_TestRet Prsd_Expression::_testUnary(DataAssociation* expression,
                                       bool*            unknown)
{
 _s_TestRet       ReturnValue   = {"",VOID};
 String_imp       UserResult    = "";

 (*unknown) = false;

#if defined(DEBUG_OUTPUT)
 cout << "_testUnary" << endl;
#endif //DEBUG_OUTPUT
 if(userResultXML_Get(expression,&UserResult) == false)
 {
// long             ChildValue    = 0;
// DataAssociation* Child         = nullptr;
// String_imp       Word          = "";
// long             Value         = 0;
// long             Nible         = 0;
// unsigned int     Pos           = 0;
  _s_TestRet       ChildResult   = {"",VOID};
  bool             Unknown       = false;
  DataAssociation* SubChild      = nullptr;
  String_imp       Operator      = "";
  String_imp       ID            = "";

  DataAssociation* Child = expression->contractorFirst_get();
  while(Child != nullptr)
  {
#if defined(DEBUG_OUTPUT)
   cout << endl << "<unary|" << Child->ToElement()->ValueStr() << "|unary>" << endl;
#endif //DEBUG_OUTPUT
 // @MRTZ_ifElseChain
   if     (STRINGS_ARE_EQUAL(Child->data_get()->userName_get(), "unary_operator"))
   {
    SubChild = Child->contractorFirst_get();
    Operator = SubChild->data_get()->userName_get();
   }
   else if(STRINGS_ARE_EQUAL(Child->data_get()->userName_get(), "p_defined"))
   {
    if(userResultXML_Get(Child,&UserResult) == false)
    {
     SubChild = Child->contractorFirst_get();
     while(SubChild != nullptr)
     {
      if(STRINGS_ARE_EQUAL(SubChild->data_get()->userName_get(), "ID"))
      {
#if defined(DEBUG_OUTPUT)
       SubChild->Print(stdout,1);
#endif //DEBUG_OUTPUT
       ID = xmlToText(SubChild);
      }
      SubChild = SubChild->fellowBehind_get();
     }
#if defined(DEBUG_OUTPUT)
     cout << endl << "<ID|" << ID << "|ID>" << endl;
#endif //DEBUG_OUTPUT
     if(constant_Get(ID,&(ChildResult.Value)) == true)
     {
      if(ChildResult.Value != "")
       ChildResult.Value  = "true";
      else
       ChildResult.Value  = "false";
     }
     else
     {
      ChildResult.Value  = "false";
      (*unknown) = true;
     }
     ChildResult.Type  = BOOL;
    }
    else
    {
     ChildResult.Value = UserResult;
     if((UserResult == "true")||(UserResult == "false"))
      ChildResult.Type = BOOL;
     else
      ChildResult.Type = STRING;
    }
   }
   else if(STRINGS_ARE_EQUAL(Child->data_get()->userName_get(), "ID"))
   {
    ID   = xmlToText(Child);
#if defined(DEBUG_OUTPUT)
   cout << endl << "<ID__|" << ID << "|__ID>" << endl;
#endif //DEBUG_OUTPUT
    if(userResultXML_Get(Child,&(ChildResult.Value)) == true)
    {
     ChildResult.Type  = STRING;
    }

    if(constant_Get(ID,&(ChildResult.Value)) == true)
    {
     ChildResult.Type  = STRING;
    }
    else
    {
     ChildResult.Type  = VOID;
     ChildResult.Value = "";
     (*unknown) = true;
    }
   }
   else if(STRINGS_ARE_EQUAL(Child->data_get()->userName_get(), "Number"))
   {
    SubChild = Child->contractorFirst_get();
 // @MRTZ_ifElseChain
    if     (STRINGS_ARE_EQUAL(SubChild->data_get()->userName_get(), "CONSTANT_CHAR"))
    {
     ChildResult.Value = xmlToText(Child);
    }
    else if(STRINGS_ARE_EQUAL(SubChild->data_get()->userName_get(), "CONSTANT_HEX"))
    {
     String_imp Word  = lowCaseString(xmlToText(SubChild));
#if defined(DEBUG_OUTPUT)
     cout << endl << Word << endl;
#endif //DEBUG_OUTPUT
     long Value = 0;
     for(unsigned int Pos = 0; Pos<Word.size(); Pos++)
     {
#if defined(DEBUG_OUTPUT)
      cout << Word[Pos] << " ";
#endif //DEBUG_OUTPUT
      long Nible = 0;

      switch(Word[Pos])
      {
       case '0': Nible =  0; break;
       case '1': Nible =  1; break;
       case '2': Nible =  2; break;
       case '3': Nible =  3; break;
       case '4': Nible =  4; break;
       case '5': Nible =  5; break;
       case '6': Nible =  6; break;
       case '7': Nible =  7; break;
       case '8': Nible =  8; break;
       case '9': Nible =  9; break;
       case 'a': Nible = 10; break;
       case 'b': Nible = 11; break;
       case 'c': Nible = 12; break;
       case 'd': Nible = 13; break;
       case 'e': Nible = 14; break;
       case 'f': Nible = 15; break;
       default : Nible =  0; break;
      }
      Value = (Value*16)+Nible;
#if defined(DEBUG_OUTPUT)
      cout<< Pos << " " << Nible << " " << Value << endl;
#endif //DEBUG_OUTPUT
     }
     ChildResult.Value = numberToString(Value);
    }
    else if (STRINGS_ARE_EQUAL(SubChild->data_get()->userName_get(), "CONSTANT_INT"))
    {
     ChildResult.Value = xmlToText(Child);
    }
    else if(STRINGS_ARE_EQUAL(SubChild->data_get()->userName_get(), "CONSTANT_FLT"))
    {
     ChildResult.Value = xmlToText(Child);
    }
    else
    {
     ChildResult.Value = "";
    }
    ChildResult.Type  = INTEGER;
   }
   else if(STRINGS_ARE_EQUAL(Child->data_get()->userName_get(), "String"))
   {
    ChildResult.Type  = STRING;
    ChildResult.Value = xmlToText(Child);
   }
   else if(STRINGS_ARE_EQUAL(Child->data_get()->userName_get(), "logical_or_expression"))
   {
    ChildResult = _testLogicalOr(Child,&Unknown);
    if(Unknown == true)
     (*unknown) = true;
   }
   else if(STRINGS_ARE_EQUAL(Child->data_get()->userName_get(), "subexpression"))
   {
    if(userResultXML_Get(Child,&UserResult) == false)
    {
     SubChild = Child->contractorFirst_get();
     while(SubChild != nullptr)
     {
      if(STRINGS_ARE_EQUAL(SubChild->data_get()->userName_get(), "logical_or_expression"))
      {
       ChildResult = _testLogicalOr(SubChild,&Unknown);
       if(Unknown == true)
        (*unknown) = true;
      }
      SubChild = SubChild->fellowBehind_get();
     }
    }
    else
    {
     ChildResult.Value = UserResult;
     if((UserResult == "true")||(UserResult == "false"))
      ChildResult.Type = BOOL;
     else
      ChildResult.Type = STRING;
    }
   }
   else
   {
   }
   Child = Child->fellowBehind_get();
    while(  (Child != nullptr)
          &&(ASSOCIATION_IS_LEAF(Child))
         )
     Child = Child->fellowBehind_get();

  }

#if defined(DEBUG_OUTPUT)
   cout << endl << "<Operator|" << Operator << "|Operator>" << endl;
#endif //DEBUG_OUTPUT

  if     (Operator == "o_plus")
  {
   long ChildValue = stringToNumber(ChildResult.Value);
   ReturnValue.Type  = INTEGER;
   ReturnValue.Value = numberToString( + ChildValue);
  }
  else if(Operator == "o_minus")
  {
   long ChildValue = stringToNumber(ChildResult.Value);
   ReturnValue.Type  = INTEGER;
   ReturnValue.Value = numberToString( - ChildValue);
  }
  else if(Operator == "o_invert")
  {
   long ChildValue = stringToNumber(ChildResult.Value);
   ReturnValue.Type  = INTEGER;
   ReturnValue.Value = numberToString( ~ ChildValue);
  }
  else if(Operator == "o_negate")
  {
   ReturnValue.Type  = BOOL;
   if(ChildResult.Value == "false")
    ReturnValue.Value = "true";
   else
    ReturnValue.Value = "false";
  }
  else
  {
   ReturnValue.Type  = ChildResult.Type;
   ReturnValue.Value = ChildResult.Value;
  }
 }
 else
 {
  ReturnValue.Value = UserResult;
  if((UserResult == "true")||(UserResult == "false"))
   ReturnValue.Type = BOOL;
  else
   ReturnValue.Type = STRING;
 }
#if defined(DEBUG_OUTPUT)
 cout << endl    <<"_testUnary("    << (*unknown)   << ") " << xmlToText(expression)  << endl;
 cout << "Type(" <<ReturnValue.Type << ") Value: |" << ReturnValue.Value << "|" << endl;
#endif //DEBUG_OUTPUT

 return(ReturnValue);
}


/* @MRTZ_describe _calcMultiplicative

*/
_s_TestRet Prsd_Expression::_calcMultiplicative(DataAssociation* expression,
                                                bool*            unknown)
{
 _s_TestRet        ReturnValue   = {"",VOID};
 String_imp        UserResult    = "";

 (*unknown) = false;

#if defined(DEBUG_OUTPUT)
 cout << "_calcMultiplicative" << endl;
#endif //DEBUG_OUTPUT

 if(userResultXML_Get(expression,&UserResult) == false)
 {
// long              ChildValue    = 0;
// DataAssociation*  Child         = nullptr;
  _s_TestRet       ChildResult   = {"",VOID};
  bool             Unknown       = false;
//  String_imp       Operator      = "";
  long             CurrentResult = 0;

  DataAssociation* Child = expression->contractorFirst_get();
  while(Child != nullptr)
  {
#if defined(DEBUG_OUTPUT)
   cout << endl << "<MulDiv|" << Child->data_get()->UserName << "|DivMul>" << endl;
#endif //DEBUG_OUTPUT

// @MRTZ_ifElseChain
   if(STRINGS_ARE_EQUAL(Child->data_get()->userName_get(), "unary_expression"))//sub-test
   {
    ChildResult   = _testUnary(Child, &Unknown);
    if(Unknown == true)
     (*unknown) = true;
    CurrentResult = stringToNumber(ChildResult.Value);
   }
   else if(STRINGS_ARE_EQUAL(Child->data_get()->userName_get(), "multiplicative_operator"))//do operation
   {
    String_imp Operator          = Child->contractorFirst_get()->data_get()->userName_get();
               ReturnValue.Value = ChildResult.Value;
               ReturnValue.Type  = ChildResult.Type;
               Child             = Child->fellowBehind_get();
               ChildResult       = _testUnary(Child, &Unknown);
    if(Unknown == true)
     (*unknown) = true;

// @MRTZ_ifElseChain
    if     (  (Operator == "o_mul") &&(Unknown  != true)
            &&(ReturnValue.Type == INTEGER)
            &&(ChildResult.Type == INTEGER)
           ) //valid test-data

    {
     long ChildValue = stringToNumber(ChildResult.Value);
       CurrentResult = CurrentResult * ChildValue;
    }
    else if(  (Operator == "o_div") &&(Unknown  != true)
            &&(ReturnValue.Type == INTEGER)
            &&(ChildResult.Type == INTEGER)
           ) //valid test-data
    {
     long ChildValue = stringToNumber(ChildResult.Value);
       CurrentResult = CurrentResult / ChildValue;
    }
    else if(  (Operator == "o_mod") &&(Unknown  != true)
            &&(ReturnValue.Type == INTEGER)
            &&(ChildResult.Type == INTEGER)
           ) //valid test-data
    {
     long ChildValue = stringToNumber(ChildResult.Value);
       CurrentResult = CurrentResult % ChildValue;
    }
    else                                         //invalid test-data or operator
    {
     (*unknown) = true;
    }
   }
   else
   {

   }

   Child = Child->fellowBehind_get();
    while(  (Child != nullptr)
          &&(ASSOCIATION_IS_LEAF(Child))
         )
     Child = Child->fellowBehind_get();
  }

  if(ReturnValue.Type == INTEGER)
  {
   ReturnValue.Value = numberToString(CurrentResult);
  }
  else
  {
   ReturnValue.Value = ChildResult.Value;
   ReturnValue.Type = ChildResult.Type;
  }
 }
 else
 {
  ReturnValue.Value = UserResult;
  if((UserResult == "true")||(UserResult == "false"))
   ReturnValue.Type = BOOL;
  else
   ReturnValue.Type = STRING;
 }

#if defined(DEBUG_OUTPUT)
 cout << endl    << "_calcMultiplicative(" << (*unknown)   << ") " << xmlToText(expression)     << endl;
 cout << "Type(" << ReturnValue.Type       << ") Value: |" << ReturnValue.Value << "|" << endl;
#endif //DEBUG_OUTPUT


 return(ReturnValue);
}



/* @MRTZ_describe _calcAdditive

*/
_s_TestRet Prsd_Expression::_calcAdditive(DataAssociation* expression,
                                          bool*            unknown)
{
 _s_TestRet        ReturnValue   = {"",VOID};
 String_imp        UserResult    = "";

 (*unknown) = false;

#if defined(DEBUG_OUTPUT)
 cout << "_calcAdditive" << endl;
#endif //DEBUG_OUTPUT
 if(userResultXML_Get(expression,&UserResult) == false)
 {
// long              ChildValue    = 0;
// DataAssociation*  Child         = nullptr;
  _s_TestRet       ChildResult   = {"",VOID};
  bool             Unknown       = false;
//  String_imp       Operator      = "";
  long             CurrentResult = 0;

  DataAssociation* Child = expression->contractorFirst_get();
  while(Child != nullptr)
  {
#if defined(DEBUG_OUTPUT)
   cout << endl << "<+-|" << Child->data_get()->UserName << "|-+>" << endl;
#endif //DEBUG_OUTPUT
// @MRTZ_ifElseChain
   if(STRINGS_ARE_EQUAL(Child->data_get()->userName_get(), "multiplicative_expression"))//sub-test
   {
    ChildResult = _calcMultiplicative(Child, &Unknown);
    if(Unknown == true)
     (*unknown) = true;
    CurrentResult = stringToNumber(ChildResult.Value);
   }
   else if(STRINGS_ARE_EQUAL(Child->data_get()->userName_get(), "additive_operator"))//do operation
   {
    String_imp Operator            = Child->contractorFirst_get()->data_get()->userName_get();
               ReturnValue.Value   = ChildResult.Value;
               ReturnValue.Type    = ChildResult.Type;
               Child               = Child->fellowBehind_get();
               ChildResult         = _calcMultiplicative(Child, &Unknown);
    if(Unknown == true)
     (*unknown) = true;

    if     (  (Operator == "o_plus") &&(Unknown  != true)
            &&(ReturnValue.Type == INTEGER)
            &&(ChildResult.Type == INTEGER)
           ) //valid test-data
    {
     long ChildValue = stringToNumber(ChildResult.Value);
       CurrentResult = CurrentResult + ChildValue;
    }
    else if(  (Operator == "o_minus") &&(Unknown  != true)
            &&(ReturnValue.Type == INTEGER)
            &&(ChildResult.Type == INTEGER)
           ) //valid test-data
    {
     long ChildValue = stringToNumber(ChildResult.Value);
       CurrentResult = CurrentResult - ChildValue;
    }
    else                                         //invalid test-data or operator
    {
     (*unknown) = true;
    }
   }
   else
   {}

   Child = Child->fellowBehind_get();
    while(  (Child != nullptr)
          &&(ASSOCIATION_IS_LEAF(Child))
         )
     Child = Child->fellowBehind_get();
  }

  if(ReturnValue.Type == INTEGER)
  {
   ReturnValue.Value = numberToString(CurrentResult);
  }
  else
  {
   ReturnValue.Value = ChildResult.Value;
   ReturnValue.Type = ChildResult.Type;
  }
 }
 else
 {
  ReturnValue.Value = UserResult;
  if((UserResult == "true")||(UserResult == "false"))
   ReturnValue.Type = BOOL;
  else
   ReturnValue.Type = STRING;
 }

#if defined(DEBUG_OUTPUT)
 cout << endl    << "_calcAdditive(" << (*unknown)   << ") " << xmlToText(expression)     << endl;
 cout << "Type(" << ReturnValue.Type << ") Value: |" << ReturnValue.Value << "|" << endl;
#endif //DEBUG_OUTPUT


 return(ReturnValue);
}




/* @MRTZ_describe _calcShift

*/
_s_TestRet Prsd_Expression::_calcShift(DataAssociation* expression,
                                       bool*            unknown)
{
 _s_TestRet        ReturnValue   = {"",VOID};
 String_imp        UserResult    = "";

 (*unknown) = false;

#if defined(DEBUG_OUTPUT)
 cout << "_calcShift" << endl;
#endif //DEBUG_OUTPUT
 if(userResultXML_Get(expression,&UserResult) == false)
 {
// DataAssociation*  Child         = nullptr;
//  long              ChildValue    = 0;
//  String_imp        Operator      = "";
  _s_TestRet        ChildResult   = {"",VOID};
  long              CurrentResult = 0;
  bool              Unknown       = false;

  DataAssociation* Child = expression->contractorFirst_get();
  while(Child != nullptr)
  {
#if defined(DEBUG_OUTPUT)
   cout << endl << "<shift|" << Child->data_get()->UserName << "|" << xmlToText(Child) << "|shift>" << endl;
#endif //DEBUG_OUTPUT
// @MRTZ_ifElseChain
   if     (STRINGS_ARE_EQUAL(Child->data_get()->userName_get(), "additive_expression"))//sub-test
   {
    ChildResult = _calcAdditive(Child, &Unknown);
    if(Unknown == true)
     (*unknown) = true;
    CurrentResult = stringToNumber(ChildResult.Value);
   }
   else if(STRINGS_ARE_EQUAL(Child->data_get()->userName_get(), "shift_operator"))//do operation
   {
    String_imp Operator            = Child->contractorFirst_get()->data_get()->userName_get();
               ReturnValue.Type    = ChildResult.Type;
               Child               = Child->fellowBehind_get();
               ChildResult         = _calcAdditive(Child, &Unknown);
    if(Unknown == true)
     (*unknown) = true;

    if     (  (Operator == "o_shift_left")&&(Unknown  != true)
            &&(ReturnValue.Type == INTEGER)
            &&(ChildResult.Type == INTEGER)
           ) //valid test-data
    {
     long ChildValue = stringToNumber(ChildResult.Value);
#if defined(DEBUG_OUTPUT)
     cout << endl << CurrentResult << "<<" << ChildValue;
#endif //DEBUG_OUTPUT
     CurrentResult = CurrentResult << ChildValue;
#if defined(DEBUG_OUTPUT)
     cout << "=" << CurrentResult << endl;
#endif //DEBUG_OUTPUT
    }
    else if(  (Operator == "o_shift_right")&&(Unknown  != true)
            &&(ReturnValue.Type == INTEGER)
            &&(ChildResult.Type == INTEGER)
           ) //valid test-data
    {
     long ChildValue = stringToNumber(ChildResult.Value);
#if defined(DEBUG_OUTPUT)
     cout << endl << CurrentResult << ">>" << ChildValue;
#endif //DEBUG_OUTPUT
     CurrentResult = CurrentResult >> ChildValue;
#if defined(DEBUG_OUTPUT)
     cout << "=" << CurrentResult << endl;
#endif //DEBUG_OUTPUT
    }
    else                                         //invalid test-data or operator
    {
     (*unknown) = true;
    }
   }
   else
   {}

   Child = Child->fellowBehind_get();
   while(  (Child != nullptr)
         &&(ASSOCIATION_IS_LEAF(Child))
        )
    Child = Child->fellowBehind_get();
  }

  if(ReturnValue.Type == INTEGER)
  {
    ReturnValue.Value = numberToString(CurrentResult);
  }
  else
  {
   ReturnValue.Value = ChildResult.Value;
   ReturnValue.Type = ChildResult.Type;
  }
 }
 else
 {
  ReturnValue.Value = UserResult;
  if((UserResult == "true")||(UserResult == "false"))
   ReturnValue.Type = BOOL;
  else
   ReturnValue.Type = STRING;
 }

#if defined(DEBUG_OUTPUT)
 cout << endl    << "_calcShift("    << (*unknown)   << ") " << xmlToText(expression)     << endl;
 cout << "Type(" << ReturnValue.Type << ") Value: |" << ReturnValue.Value << "|" << endl;
#endif //DEBUG_OUTPUT


 return(ReturnValue);
}




/* @MRTZ_describe _testRelational

*/
_s_TestRet Prsd_Expression::_testRelational(DataAssociation* expression,
                                            bool*            unknown)
{
 _s_TestRet        ReturnValue    = {"",VOID};
 String_imp        UserResult     = "";

 (*unknown) = false;

#if defined(DEBUG_OUTPUT)
 cout << "_testRelational" << endl;
#endif //DEBUG_OUTPUT
 if(userResultXML_Get(expression,&UserResult) == false)
 {
// DataAssociation*  Child          = nullptr;
//  String_imp        Operator       = "";
  _s_TestRet        ChildResult    = {"",VOID};
  bool              CurrentResult  = true;
  long              ChildValue_Old = 0;
//  long              ChildValue_New = 0;
  bool              Unknown        = false;

  DataAssociation* Child = expression->contractorFirst_get();
  while(Child != nullptr)
  {
#if defined(DEBUG_OUTPUT)
   cout << endl << "<rela|" << Child->data_get()->UserName << "|rela>" << endl;
#endif //DEBUG_OUTPUT
// @MRTZ_ifElseChain
   if(STRINGS_ARE_EQUAL(Child->data_get()->userName_get(), "shift_expression"))//sub-test
   {
    ChildResult    = _calcShift(Child, &Unknown);
    if(Unknown == true)
     (*unknown) = true;
    ChildValue_Old = stringToNumber(ChildResult.Value);
   }
   else if(STRINGS_ARE_EQUAL(Child->data_get()->userName_get(), "relational_operator"))//do operation
   {
    String_imp Operator          = Child->contractorFirst_get()->data_get()->userName_get();
               Child          = Child->fellowBehind_get();
               ChildResult    = _calcShift(Child, &Unknown);
    if(Unknown == true)
     (*unknown) = true;
    long ChildValue_New = stringToNumber(ChildResult.Value);

// @MRTZ_ifElseChain
    if     ((Operator == "o_less_equal") &&(Unknown  != true)) //valid equal test-data
    {
     CurrentResult = ChildValue_Old <= ChildValue_New;
     ReturnValue.Type = BOOL;
    }
    else if((Operator == "o_greater_equal") &&(Unknown  != true)) //valid unequal test-data
    {
     CurrentResult = ChildValue_Old >= ChildValue_New;
     ReturnValue.Type = BOOL;
    }
    else if((Operator == "o_less") &&(Unknown  != true)) //valid unequal test-data
    {
     CurrentResult = ChildValue_Old < ChildValue_New;
     ReturnValue.Type = BOOL;
    }
    else if((Operator == "o_greater") &&(Unknown  != true)) //valid unequal test-data
    {
     CurrentResult = ChildValue_Old > ChildValue_New;
     ReturnValue.Type = BOOL;
    }
    else                                         //invalid test-data or operator
    {
     (*unknown) = true;
    }
    ChildValue_Old = ChildValue_New;
   }
   else
   {}

   if(CurrentResult == false)//rest of check not necessary
   {
    Child = nullptr;
    (*unknown) = false;
   }
   else                   //continue to check
    Child = Child->fellowBehind_get();
   while(  (Child != nullptr)
         &&(ASSOCIATION_IS_LEAF(Child))
        )
    Child = Child->fellowBehind_get();
  }

  if(ReturnValue.Type == BOOL)
  {
   if(CurrentResult == true)
    ReturnValue.Value = "true";
   else
    ReturnValue.Value = "false";
  }
  else
  {
   ReturnValue.Value = ChildResult.Value;
   ReturnValue.Type  = ChildResult.Type;
  }
 }
 else
 {
  ReturnValue.Value = UserResult;
  if((UserResult == "true")||(UserResult == "false"))
   ReturnValue.Type = BOOL;
  else
   ReturnValue.Type = STRING;
 }

#if defined(DEBUG_OUTPUT)
 cout << endl    << "_testRelational(" << (*unknown)   << ") " << xmlToText(expression)     << endl;
 cout << "Type(" << ReturnValue.Type   << ") Value: |" << ReturnValue.Value << "|" << endl;
#endif //DEBUG_OUTPUT

 return(ReturnValue);
}



/* @MRTZ_describe _testEquality

*/
_s_TestRet Prsd_Expression::_testEquality(DataAssociation* expression,
                                          bool*            unknown)
{
 _s_TestRet        ReturnValue    = {"",VOID};
 String_imp        UserResult     = "";

 (*unknown) = false;

#if defined(DEBUG_OUTPUT)
 cout << "_testEquality" << endl;
#endif //DEBUG_OUTPUT
 if(userResultXML_Get(expression,&UserResult) == false)
 {
//  DataAssociation*  Child          = nullptr;
//  String_imp        Operator       = "";
  _s_TestRet        ChildResult    = {"",VOID};
  bool              CurrentResult  = true;
  String_imp        ChildValue_Old = "";
//  String_imp        ChildValue_New = "";
  bool              Unknown        = false;

  DataAssociation* Child = expression->contractorFirst_get();
  while(Child != nullptr)
  {
#if defined(DEBUG_OUTPUT)
   cout << endl << "<!==|" << Child->data_get()->UserName << "|==!>" << endl;
#endif //DEBUG_OUTPUT
// @MRTZ_ifElseChain
   if     (STRINGS_ARE_EQUAL(Child->data_get()->userName_get(), "relational_expression"))//sub-test
   {
    ChildResult    = _testRelational(Child, &Unknown);
    if(Unknown == true)
     (*unknown) = true;
    ChildValue_Old = ChildResult.Value;
   }
   else if(STRINGS_ARE_EQUAL(Child->data_get()->userName_get(), "equality_operator"))//do operation
   {
    String_imp Operator         = Child->contractorFirst_get()->data_get()->userName_get();
#if defined(DEBUG_OUTPUT)
   cout << endl << "<Operator!==|" << Operator << "|==!Operator>" << endl;
#endif //DEBUG_OUTPUT
               Child            = Child->fellowBehind_get();
               ChildResult      = _testRelational(Child, &Unknown);
    if(Unknown == true)
     (*unknown) = true;
    String_imp ChildValue_New   = ChildResult.Value;

#if defined(DEBUG_OUTPUT)
 cout << "Old(" << ChildValue_Old << ")" << endl;
 cout << "New(" << ChildValue_New << ")" << endl;
#endif //DEBUG_OUTPUT

    if     ((Operator == "o_equal") &&(Unknown  != true)) //valid equal test-data
    {
     CurrentResult = ChildValue_Old == ChildValue_New;
     ReturnValue.Type = BOOL;
    }
    else if((Operator == "o_unequal") &&(Unknown  != true)) //valid unequal test-data
    {
     CurrentResult = ChildValue_Old != ChildValue_New;
     ReturnValue.Type = BOOL;
    }
    else                                         //invalid test-data or operator
    {
     (*unknown) = true;
    }
    ChildValue_Old = ChildValue_New;
   }
   else
   {}

   if(CurrentResult == false)//rest of check not necessary
   {
    Child = nullptr;
    (*unknown) = false;
   }
   else
   {
    Child = Child->fellowBehind_get();
     while(  (Child != nullptr)
          &&(ASSOCIATION_IS_LEAF(Child))
          )
      Child = Child->fellowBehind_get();
   }                  //continue to check
  }

  if(ReturnValue.Type == BOOL)
  {
   if(CurrentResult == true)
    ReturnValue.Value = "true";
   else
    ReturnValue.Value = "false";
  }
  else
  {
   ReturnValue.Value = ChildResult.Value;
   ReturnValue.Type = ChildResult.Type;
  }
 }
 else
 {
  ReturnValue.Value = UserResult;
  if((UserResult == "true")||(UserResult == "false"))
   ReturnValue.Type = BOOL;
  else
   ReturnValue.Type = STRING;
 }

#if defined(DEBUG_OUTPUT)
 cout << endl    << "_testEquality(" << (*unknown)   << ") " << xmlToText(expression)     << endl;
 cout << "Type(" << ReturnValue.Type << ") Value: |" << ReturnValue.Value << "|" << endl;
#endif //DEBUG_OUTPUT


 return(ReturnValue);
}




/* @MRTZ_describe _calcAnd

*/
_s_TestRet Prsd_Expression::_calcAnd(DataAssociation* expression,
                                     bool*            unknown)
{
 _s_TestRet        ReturnValue   = {"",VOID};
 String_imp        UserResult    = "";

 (*unknown) = false;

#if defined(DEBUG_OUTPUT)
 cout << "_calcAnd" << endl;
#endif //DEBUG_OUTPUT
 if(userResultXML_Get(expression,&UserResult) == false)
 {
// DataAssociation*  Child         = nullptr;
// String_imp        Operator      = "";
//  long             ChildValue    = 0;
  _s_TestRet        ChildResult   = {"",VOID};
  long              CurrentResult = 0;
  bool              Unknown       = false;

  DataAssociation* Child = expression->contractorFirst_get();
  while(Child != nullptr)
  {
#if defined(DEBUG_OUTPUT)
   cout << endl << "<|" << Child->data_get()->UserName << "|>" << endl;
#endif //DEBUG_OUTPUT
// @MRTZ_ifElseChain
   if     (STRINGS_ARE_EQUAL(Child->data_get()->userName_get(), "equality_expression"))//sub-test
   {
    ChildResult   = _testEquality(Child, &Unknown);
    if(Unknown == true)
     (*unknown) = true;
    CurrentResult = stringToNumber(ChildResult.Value);
   }
   else if(STRINGS_ARE_EQUAL(Child->data_get()->userName_get(), "bit_and_operator"))//do operation
   {
    String_imp Operator          = Child->contractorFirst_get()->data_get()->userName_get();
               ReturnValue.Value = ChildResult.Value;
               ReturnValue.Type  = ChildResult.Type;
               Child             = Child->fellowBehind_get();
               ChildResult       = _testEquality(Child, &Unknown);
    if(Unknown == true)
     (*unknown) = true;

    if(  (Operator == "o_bit_and")
       &&(Unknown  != true)
       &&(ReturnValue.Type == INTEGER)
       &&(ChildResult.Type == INTEGER)
      ) //valid test-data
    {
     long ChildValue = stringToNumber(ChildResult.Value);
       CurrentResult = CurrentResult & ChildValue;
    }
    else                                         //invalid test-data or operator
    {
     (*unknown) = true;
    }
   }
   else
   {}

   Child = Child->fellowBehind_get();
    while(  (Child != nullptr)
          &&(ASSOCIATION_IS_LEAF(Child))
         )
     Child = Child->fellowBehind_get();
  }

  if(ReturnValue.Type == INTEGER)
  {
   ReturnValue.Value = numberToString(CurrentResult);
  }
  else
  {
   ReturnValue.Value = ChildResult.Value;
   ReturnValue.Type = ChildResult.Type;
  }
 }
 else
 {
  ReturnValue.Value = UserResult;
  if((UserResult == "true")||(UserResult == "false"))
   ReturnValue.Type = BOOL;
  else
   ReturnValue.Type = STRING;
 }

#if defined(DEBUG_OUTPUT)
 cout << endl    << "_calcAnd("      << (*unknown)   << ") " << xmlToText(expression)     << endl;
 cout << "Type(" << ReturnValue.Type << ") Value: |" << ReturnValue.Value << "|" << endl;
#endif //DEBUG_OUTPUT


 return(ReturnValue);
}



/* @MRTZ_describe _calcExclusiveOr

*/
_s_TestRet Prsd_Expression::_calcExclusiveOr(DataAssociation* expression,
                                             bool*            unknown)
{
 _s_TestRet        ReturnValue   = {"",VOID};
 String_imp        UserResult    = "";

 (*unknown) = false;

#if defined(DEBUG_OUTPUT)
 cout << "_calcExclusiveOr" << endl;
#endif //DEBUG_OUTPUT
 if(userResultXML_Get(expression,&UserResult) == false)
 {
// DataAssociation*  Child         = nullptr;
// String_imp        Operator      = "";
//  long             ChildValue    = 0;
  _s_TestRet        ChildResult   = {"",VOID};
  long              CurrentResult = 0;
  bool              Unknown       = false;

  DataAssociation* Child = expression->contractorFirst_get();
  while(Child != nullptr)
  {
#if defined(DEBUG_OUTPUT)
   cout << endl << "<|" << Child->data_get()->UserName << "|>" << endl;
#endif //DEBUG_OUTPUT
// @MRTZ_ifElseChain
   if     (STRINGS_ARE_EQUAL(Child->data_get()->userName_get(), "and_expression"))//sub-test
   {
    ChildResult   = _calcAnd(Child, &Unknown);
    if(Unknown == true)
     (*unknown) = true;

    CurrentResult = stringToNumber(ChildResult.Value);
   }
   else if(STRINGS_ARE_EQUAL(Child->data_get()->userName_get(), "bit_exor_opeartor"))//do operation
   {
    String_imp Operator          = Child->contractorFirst_get()->data_get()->userName_get();
               ReturnValue.Value = ChildResult.Value;
               ReturnValue.Type  = ChildResult.Type;
               Child             = Child->fellowBehind_get();
               ChildResult       = _calcAnd(Child, &Unknown);
    if(Unknown == true)
     (*unknown) = true;

    if(  (Operator == "o_bit_exor")
       &&(Unknown  != true)
       &&(ReturnValue.Type == INTEGER)
       &&(ChildResult.Type == INTEGER)
      ) //valid test-data
    {
     long ChildValue = stringToNumber(ChildResult.Value);
       CurrentResult = CurrentResult ^ ChildValue;
    }
    else                                         //invalid test-data or operator
    {
     (*unknown) = true;
    }
   }
   else
   {}

   Child = Child->fellowBehind_get();
   while(  (Child != nullptr)
          &&(ASSOCIATION_IS_LEAF(Child))
        )
    Child = Child->fellowBehind_get();
  }

  if(ReturnValue.Type == INTEGER)
  {
   ReturnValue.Value = numberToString(CurrentResult);
  }
  else
  {
   ReturnValue.Value = ChildResult.Value;
   ReturnValue.Type = ChildResult.Type;
  }
 }
 else
 {
  ReturnValue.Value = UserResult;
  if((UserResult == "true")||(UserResult == "false"))
   ReturnValue.Type = BOOL;
  else
   ReturnValue.Type = STRING;
 }

#if defined(DEBUG_OUTPUT)
 cout << endl    << "_calcExclusiveOr(" << (*unknown)   << ") " << xmlToText(expression)     << endl;
 cout << "Type(" << ReturnValue.Type    << ") Value: |" << ReturnValue.Value << "|" << endl;
#endif //DEBUG_OUTPUT


 return(ReturnValue);
}



/* @MRTZ_describe _calcInclusiveOr

*/
_s_TestRet Prsd_Expression::_calcInclusiveOr(DataAssociation* expression,
                                             bool*            unknown)
{
 _s_TestRet        ReturnValue   = {"",VOID};
 String_imp        UserResult    = "";

 (*unknown) = false;

#if defined(DEBUG_OUTPUT)
 cout << "_calcInclusiveOr" << endl;
#endif //DEBUG_OUTPUT
 if(userResultXML_Get(expression,&UserResult) == false)
 {
// DataAssociation*  Child         = nullptr;
// String_imp        Operator      = "";
// long              ChildValue    = 0;
  _s_TestRet        ChildResult   = {"",VOID};
  long              CurrentResult = 0;
  bool              Unknown       = false;

  DataAssociation* Child = expression->contractorFirst_get();
  while(Child != nullptr)
  {
#if defined(DEBUG_OUTPUT)
   cout << endl << "<|" << Child->data_get()->UserName << "|>" << endl;
#endif //DEBUG_OUTPUT
// @MRTZ_ifElseChain
   if     (STRINGS_ARE_EQUAL(Child->data_get()->userName_get(), "exclusive_or_expression"))//sub-test
   {
    ChildResult   = _calcExclusiveOr(Child, &Unknown);
    if(Unknown == true)
     (*unknown) = true;

    CurrentResult = stringToNumber(ReturnValue.Value);
   }
   else if(STRINGS_ARE_EQUAL(Child->data_get()->userName_get(), "bit_or_operator"))//do operation
   {
    String_imp Operator    = Child->contractorFirst_get()->data_get()->userName_get();
               Child       = Child->fellowBehind_get();
               ChildResult = _calcExclusiveOr(Child, &Unknown);
    if(Unknown == true)
     (*unknown) = true;
    if(  (Operator == "o_bit_or")
       &&(Unknown  != true)
       &&(ReturnValue.Type == INTEGER)
       &&(ChildResult.Type == INTEGER)
      ) //valid test-data
    {
     long ChildValue = stringToNumber(ChildResult.Value);
       CurrentResult = CurrentResult | ChildValue;

     ReturnValue.Type = INTEGER;
    }
    else                                         //invalid test-data or operator
    {
     (*unknown) = true;
    }
   }
   else
   {}

   Child = Child->fellowBehind_get();
   while(  (Child != nullptr)
         &&(ASSOCIATION_IS_LEAF(Child))
        )
    Child = Child->fellowBehind_get();
  }

  if(ReturnValue.Type == INTEGER)
  {
   ReturnValue.Value = numberToString(CurrentResult);
  }
  else
  {
   ReturnValue.Value = ChildResult.Value;
   ReturnValue.Type = ChildResult.Type;
  }
 }
 else
 {
  ReturnValue.Value = UserResult;
  if((UserResult == "true")||(UserResult == "false"))
   ReturnValue.Type = BOOL;
  else
   ReturnValue.Type = STRING;
 }

#if defined(DEBUG_OUTPUT)
 cout << endl    << "_calcInclusiveOr(" << (*unknown)   << ") " << xmlToText(expression)     << endl;
 cout << "Type(" << ReturnValue.Type    << ") Value: |" << ReturnValue.Value << "|" << endl;
#endif //DEBUG_OUTPUT


 return(ReturnValue);
}



/* @MRTZ_describe _testLogicalAnd

*/
_s_TestRet Prsd_Expression::_testLogicalAnd(DataAssociation* expression,
                                            bool*            unknown)
{
 _s_TestRet        ReturnValue   = {"",VOID};
 String_imp        UserResult    = "";

 (*unknown) = false;//has to be modified from the first found sub-false

#if defined(DEBUG_OUTPUT)
 cout << "_testLogicalAnd" << endl;
#endif //DEBUG_OUTPUT
 if(userResultXML_Get(expression,&UserResult) == false)
 {
// DataAssociation*  Child         = nullptr;
// String_imp        Operator      = "";
  _s_TestRet        ChildResult   = {"",VOID};
  bool              CurrentResult = true;
  bool              Unknown       = false;

  DataAssociation* Child = expression->contractorFirst_get();
  while(Child != nullptr)
  {
#if defined(DEBUG_OUTPUT)
   cout << endl << "<&&|" << Child->data_get()->UserName << "|&&>" << endl;
#endif //DEBUG_OUTPUT
// @MRTZ_ifElseChain
   if     (STRINGS_ARE_EQUAL(Child->data_get()->userName_get(), "inclusive_or_expression"))//sub-test
   {
    ChildResult   = _calcInclusiveOr(Child, &Unknown);
    if(Unknown == true)
     (*unknown) = true;
    if(ChildResult.Value == "false")
      CurrentResult = false;
   }
   else if(STRINGS_ARE_EQUAL(Child->data_get()->userName_get(), "log_and_operator"))//do operation
   {
    String_imp Operator    = Child->contractorFirst_get()->data_get()->userName_get();
#if defined(DEBUG_OUTPUT)
   cout << endl << "<Operator|" << Operator << "|Operator>" << endl;
#endif //DEBUG_OUTPUT
               Child       = Child->fellowBehind_get();
               ChildResult = _calcInclusiveOr(Child, &Unknown);
    if(Unknown == true)
     (*unknown) = true;
    if(  (Operator == "o_log_and")
       &&(Unknown != true)
       &&(ChildResult.Type == BOOL)
      ) //valid test-data
    {
     if(ChildResult.Value == "false")
     {
      CurrentResult = false;
     }
     ReturnValue.Type = BOOL;
    }
    else                                         //invalid test-data or operator
    {
     (*unknown) = true;
    }
   }
   else // for example a comment
   {}

   if(  (CurrentResult == false)
      &&((*unknown)    == false)
     )  // if one input of log_and is false the whole log_and is false
        // but only if every evaluated input is known
   {
    Child = nullptr; //rest of check not necessary
   }
   else //continue to check
   {
    Child = Child->fellowBehind_get();
    while(  (Child != nullptr)
          &&(ASSOCIATION_IS_LEAF(Child))
         )
     Child = Child->fellowBehind_get();
   }
  }

  if(ReturnValue.Type == BOOL)
  {
   if(CurrentResult == true)
    ReturnValue.Value = "true";
   else
    ReturnValue.Value = "false";
  }
  else
  {
   ReturnValue.Value = ChildResult.Value;
   ReturnValue.Type = ChildResult.Type;
  }
 }
 else
 {
  ReturnValue.Value = UserResult;
  if((UserResult == "true")||(UserResult == "false"))
   ReturnValue.Type = BOOL;
  else
   ReturnValue.Type = STRING;
//  cout << "found user-result: " << ReturnValue.Type << endl;
 }

#if defined(DEBUG_OUTPUT)
 cout << endl    << "_testLogicalAnd(" << (*unknown)   << ") " << xmlToText(expression)     << endl;
 cout << "Type(" << ReturnValue.Type   << ") Value: |" << ReturnValue.Value << "|" << endl;
#endif //DEBUG_OUTPUT

 return(ReturnValue);
}



/* @MRTZ_describe _testLogicalOr

*/
_s_TestRet Prsd_Expression::_testLogicalOr(DataAssociation* expression,
                                           bool*            unknown)
{
 _s_TestRet        ReturnValue   = {"",VOID};
 String_imp        UserResult    = "";

 (*unknown) = false;//has to be modified from the first found sub-true
#if defined(DEBUG_OUTPUT)
 cout << "_testLogicalOr" << endl;
#endif //DEBUG_OUTPUT
 if(userResultXML_Get(expression,&UserResult) == false)
 {
// DataAssociation*  Child         = nullptr;
// String_imp        Operator      = "";
  _s_TestRet        ChildResult   = {"",VOID};
  bool              CurrentResult = false;
  bool              Unknown       = false;

  DataAssociation* Child = expression->contractorFirst_get();
  while(Child != nullptr)
  {
#if defined(DEBUG_OUTPUT)
   cout << endl << "<||-" << Child->data_get()->UserName << "-||>" << endl;
#endif //DEBUG_OUTPUT
// @MRTZ_ifElseChain
   if     (STRINGS_ARE_EQUAL(Child->data_get()->userName_get(), "logical_and_expression"))//sub-test
   {
    ChildResult = _testLogicalAnd(Child, &Unknown);
    if(Unknown == true)
     (*unknown) = true;
#if defined(DEBUG_OUTPUT)
    cout<<"unknown: " << (*unknown) << endl;
#endif //DEBUG_OUTPUT
   }
   else if(STRINGS_ARE_EQUAL(Child->data_get()->userName_get(), "log_or_operator"))//do operation
   {
    String_imp Operator = Child->contractorFirst_get()->data_get()->userName_get();
#if defined(DEBUG_OUTPUT)
   cout << endl << "<Operator|" << Operator << "|Operator>" << endl;
#endif //DEBUG_OUTPUT
    if(  (Operator == "o_log_or")
       &&(Unknown != true)
       &&(ChildResult.Type == BOOL)
      ) //valid test-data
    {
     if(ChildResult.Value == "true")
      CurrentResult = true;
     ReturnValue.Type = BOOL;
    }
    else                                         //invalid test-data or operator
    {
     (*unknown) = true;
    }
   }
   else
   {}

   if(  (CurrentResult == true)
      &&((*unknown)    == false)
     )  // if one input of log_or is true the whole log_or is true
        // but only if every evaluated input is known
   {
    Child = nullptr;// rest of check not necessary
   }
   else //continue to check
   {
    Child = Child->fellowBehind_get();
    while(  (Child != nullptr)
          &&(ASSOCIATION_IS_LEAF(Child))
         )
     Child = Child->fellowBehind_get();

   }
  }

  if(ReturnValue.Type == BOOL)
  {
   if(CurrentResult == true)
    ReturnValue.Value = "true";
   else
    ReturnValue.Value = "false";
  }
  else
  {
   ReturnValue.Value = ChildResult.Value;
   ReturnValue.Type = ChildResult.Type;
  }
 }
 else
 {
  ReturnValue.Value = UserResult;
  if((UserResult == "true")||(UserResult == "false"))
   ReturnValue.Type = BOOL;
  else
   ReturnValue.Type = STRING;
 }

#if defined(DEBUG_OUTPUT)
 cout << endl    <<"_testLogicalOr(" << (*unknown)   << ") " << xmlToText(expression)     << endl;
 cout << "Type(" <<ReturnValue.Type  <<") Value: |" << ReturnValue.Value << "|" << endl;
#endif //DEBUG_OUTPUT

 return(ReturnValue);
}



#ifndef DOXYGEN
//};
#endif //DOXYGEN
