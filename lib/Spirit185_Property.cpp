
/*!

 @file
 @brief search for a association with specific data

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
    09.09.2015     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    09.09.2015...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/



//#define DEBUG_OUTPUT_LOG
#include "LogOutput.h"




#include <stdio.h>
#include <cstdlib>
#include <list>


#include "Spirit185_Filter.h"
#include "Spirit185_Store.h"

#include "Spirit185_Internal.h"


#include "Spirit185_Property.h"
#include "TiPa_Search.h"


using namespace std;


#ifndef DOXYGEN
//namespace TXTDIASM {
//namespace TDA_Grammar {
//namespace DATA {
#endif //DOXYGEN



/* @MRTZ_describe Spirit185_Property

*/
Spirit185_Property::Spirit185_Property(void)
{
 Att.DataBase = nullptr;
}



/* @MRTZ_describe Spirit185_Property
  just call init
*/
Spirit185_Property::Spirit185_Property(TiPa_Concrete::DataAssociation*     source,
//                                       TiPa_Concrete::DataAssociation*     sponsor,
                                       const char* notPhrased, char separator,
                                       const char*                  grammarTextIdentifier,
                                       int limitCallingTree,   int  limitCallingNode,
                                       int limitCallerTree,    int  limitCallerNode)
{

 Att.ContextModel.init();                                 // set up Context of database-content


 Att.DataBase = Att.ContextModel.fellow_create();         // create data-base root
 Spirit185_Data* Data = Att.ContextModel.data_create();   // create new data-object
 Data->SourceData = source;                               // use source as core-data
 Att.DataBase->data_set(Data);                            // connect new data-object with data-base root

 evaluate_Rule(source);

 evaluate_isUsedBy();                                     // add to every rule detail-information about other rules which use them

 evaluate_Collaboration(notPhrased,       separator,
                        limitCallingTree, limitCallingNode,
                        limitCallerTree,  limitCallerNode);
 storeDataBaseAsXML(grammarTextIdentifier) ;              // store result in an xml-file
}





/* @MRTZ_describe ~Spirit185_Property

*/
Spirit185_Property::~Spirit185_Property(void)
{
 Att.ContextModel.init();
 Att.Rule.clear();
}


/* @MRTZ_describe evaluate_isUsing

*/
void Spirit185_Property::evaluate_Rule(TiPa_Concrete::DataAssociation* source)
{
 TiPa_Search Search;                                                                             // visitor to search special associations

 TiPa_Concrete::DataAssociation* Contractor = source->contractorFirst_get(Search(TiPa_Search::UserName,"RootContent/RootElement"));
                                                                                                 // search for first sub-node with fellows to iterate over
 while(Contractor != nullptr)                                                                    // first iteration over all sub nodes found to define rule-roots
 {
  TiPa_Concrete::DataAssociation* Rule = Contractor->contractorFirst_get(Search(TiPa_Search::UserName,"Rule"));
                                                                                                 // search for a sub-sub node that contains a rule description
  if(Rule != nullptr)                                                                            // rule found
  {
   TiPa_Concrete::DataAssociation* Identifier         = Rule->contractorFirst_get(Search(TiPa_Search::UserName,"RuleContent/Identifier"));
                                                                                                 // sub-sub-sub node that contains the rule-identifier
   Spirit185_Data*          RuleData           = Att.ContextModel.data_create();                 // data object for rule node

   RuleData->SourceData                        = Rule;                                           //Identifier;                                                           // connect core data
   RuleData->Detail[Spirit185_Data::attName]   = "Rule";                                         // standard node identifier
   RuleData->Detail[Spirit185_Data::attValue]  = Identifier->data_get()->getContent();           // individual identifier defined by user


   const char* OldKey = getRuleKey(Identifier->data_get()->getContent());
   if(OldKey != nullptr)                                                                         // a rule with the same identifier is already defined
    Att.Rule.erase(OldKey);

   Att.Rule[Identifier->data_get()->getContent()]   = Att.ContextModel.fellow_create();
   Att.Rule[Identifier->data_get()->getContent()]->data_set(RuleData);                           // add new node to the list of rules
  }
  Contractor = Contractor->fellowBehind_get();                                                   // next fellow to analyse
 }
 if(getRuleKey("reserved") == nullptr)                                                           // a rule with the same identifier is already defined
  createReserved(source);


 Contractor = source->contractorFirst_get(Search(TiPa_Search::UserName,"RootContent/RootElement"));
                                                                                                 // search for first sub-node with fellows to iterate over
 while(Contractor != nullptr)                                                                    // second iteration over all sub nodes found to analyse rule expressions
 {
  TiPa_Concrete::DataAssociation* Rule = Contractor->contractorFirst_get(Search(TiPa_Search::UserName,"Rule"));
                                                                                                 // search for a sub-sub node that contains a rule description
  if(Rule != nullptr)                                                                            // rule found
  {
   TiPa_Concrete::DataAssociation* Identifier = Rule->contractorFirst_get(Search(TiPa_Search::UserName,"RuleContent/Identifier"));
                                                                                                 // sub-sub-sub node that contains the rule-identifier
   TiPa_Concrete::DataAssociation* Expression = Identifier->fellowBehind_get();                         // sub-sub-sub node that contains the rule-expression
   if(Att.Rule.find(Identifier->data_get()->getContent())!= Att.Rule.end())                      // current rule was not overwritten by newer definition
    Att.DataBase->contractorLast_add(evaluate_isUsing(Identifier,Expression));                   // add new node to data-base that contains the first analysed rule-data
  }
  Contractor = Contractor->fellowBehind_get();                                                   // next fellow to analyse
 }
 expressionReserved(source);

}



/* @MRTZ_describe createReserved
  create just a root node and insert insert a valid node into the rule dictionary
*/
void Spirit185_Property::createReserved(TiPa_Concrete::DataAssociation* source)
{

 const char* Key = getRuleKey("reserved");
 if(Key == nullptr)                                                                         // a rule with the same identifier is already defined
  Att.Rule.erase(Key);

 Att.Rule["reserved"] = Att.ContextModel.fellow_create();
                                                                                              // root-node of reserved-rule description
 Spirit185_Data*          RuleData           = Att.ContextModel.data_create();                // data object for rule node
 RuleData->Detail[Spirit185_Data::attName]   = "Rule";                                        // standard node identifier
 RuleData->Detail[Spirit185_Data::attValue]  = "reserved";                                    // individual identifier defined by user
 RuleData->SourceData                        = source;                                        // connect root of all rules as core data not a specific rule

 Att.Rule["reserved"]->data_set(RuleData);                                                    // add new node to the list of rules
}



/* @MRTZ_describe expressionReserved
 create the complete reserved expression by evaluating the reserved keywords found while analysing the user grammar,
 all keywords will be sorted and inserted to the expression only one times
*/
void Spirit185_Property::expressionReserved(TiPa_Concrete::DataAssociation* source)
{
 Spirit185_Data* RuleData  = Att.Rule[getRuleKey("reserved")]->data_get();
 RuleData->CalledRule.clear();  // may be filled by dummy-rule in user-grammar
 RuleData->CallingRule.clear(); // may be filled by dummy-rule in user-grammar

 if(RuleData->Detail[Spirit185_Data::attUsing] != nullptr)
 {
  delete[](RuleData->Detail[Spirit185_Data::attUsing]);
  RuleData->Detail[Spirit185_Data::attUsing] = nullptr;
 }


 char* Attribute = new char[1];
 Attribute[0] = 0 ;  // string becomes empty since reserved is not using other rules
                     // and not itself
 RuleData->Detail[Spirit185_Data::attUsing] = Attribute; // store new empty attribute


 Spirit185_DataAssociation*    Expression         = Att.ContextModel.fellow_create();         // create new expression node
 Spirit185_Data*               ExpressionData     = Att.ContextModel.data_create();           // data object of expression-node
 ExpressionData->SourceData                       = source;                                   // connect root of all rules as core data not a specific rule
 ExpressionData->Detail[Spirit185_Data::attName]  = "Expression" ;                            // standard node identifier
 Expression->data_set(ExpressionData);                                                        // connect expression node and expression data

 Att.Rule[getRuleKey("reserved")]->contractorLast_add(Expression);                                        // connect expression to rule



 Spirit185_DataAssociation* Alternative      = Att.ContextModel.fellow_create();           // create new note
 Spirit185_Data*               AlternativeData  = Att.ContextModel.data_create();             // create data-object
 AlternativeData->Detail[Spirit185_Data::attName]  = "BinOperand_OrInc";                      // default-name given in spirit-185 internal
 AlternativeData->SourceData = source;                                                        // connect root of all rules as core data not a specific rule
 Alternative->data_set(AlternativeData);                                                      // connect alternative node and alternative data

 Expression->contractorLast_add(Alternative);                                                 // connect alternative-node to expression


 list<const char*> KeyWords;                                                                  // lists of strings to sort
 map<const char*,Spirit185_DataAssociation*>::iterator ReservedWord = Att.ReservedWords.begin();
                                                                                              // key-word found while exploring grammar-rules
 while (ReservedWord  != Att.ReservedWords.end())                                             // iterate over all key words of grammar
 {
  KeyWords.push_back(ReservedWord->first);                                                    // store keyword in sorting-list
  ++ReservedWord;                                                                             // next keyword
 }
 KeyWords.sort(Spirit185_Property::compareIdentifier);                                        // alpha-numeric sorting

 list<const char*>::iterator Key       = KeyWords.begin();                                    // keyword of current iteration loop
 list<const char*>::iterator KeyBefore = KeyWords.begin();                                    // keyword of iteration loop before
 while(Key != KeyWords.end())
 {
  if(  (Key                     == KeyWords.begin())
     ||(strstr(*Key,*KeyBefore) != *Key        )
     ||(strlen(*KeyBefore)      != strlen(*Key))

    )                                                                                         // first iteration loop or key-string is new
  {
   Spirit185_DataAssociation* KeyWord      = Att.ContextModel.fellow_create();             // create new node
   KeyWord->data_set(Att.ReservedWords[*Key]->data_get());                                    // copy node data reference of key-word
   Alternative->contractorLast_add(KeyWord);                                                  // add new keyword node to alternative
  }
  else                                                                                        // key-string already added
  {
                                                                                              // do nothing
  }
  KeyBefore = Key;                                                                            // store current key as key before
  ++ Key;                                                                                     // continue iteration
 }

}















/* @MRTZ_describe evaluate_isUsing

*/
Spirit185_Data::Spirit185_DataAssociation* Spirit185_Property::evaluate_isUsing(TiPa_Concrete::DataAssociation* identifier,
                                                                                TiPa_Concrete::DataAssociation* expression)
{

 Spirit185_DataAssociation* Rule               = Att.Rule[identifier->data_get()->getContent()];            // create new rule-node
 Spirit185_Data*               RuleData           = Rule->data_get();

 Spirit185_DataAssociation* Expression         = Att.ContextModel.fellow_create();                          // create new expression node
 Spirit185_Data*               ExpressionData     = Att.ContextModel.data_create();                            // data object of expression-node
 ExpressionData->SourceData                       = expression;                                                // connect core data
 ExpressionData->Detail[Spirit185_Data::attName]  = "Expression" ;                                             // standard node identifier
 Expression->data_set(ExpressionData);                                                                         // connect expression node and expression data

 Rule->contractorLast_add(Expression);                                                                         // connect expression to rule



 Spirit185_DataAssociation* ExpressionContent  = Att.ContextModel.fellow_create();                          // create node for expression-details
 ExpressionContent = this->evaluate_Expression(&(RuleData->CalledRule),ExpressionContent,expression/*,nullptr*/);
                                                                                                               // fill new expression-details
 Expression->contractorLast_add(ExpressionContent);                                                            // connect expression-node and its details

 int AttributeSize = 0;                                                                                        // size of new attribute
 set<Spirit185_DataAssociation*>::iterator RuleName = RuleData->CalledRule.begin();                         // name of called rules
 while(RuleName != RuleData->CalledRule.end())                                                                 // over all collected rule names
 {
  Spirit185_Data* Data = (*RuleName)->data_get();

  AttributeSize = AttributeSize + strlen(Data->Detail[Spirit185_Data::attValue]) + 1;                          // rule name and split character like comma
  ++RuleName;                                                                                                  // next rule name
 }
 char* RuleNameAttribute = new char[AttributeSize+1];                                                          // create new attribute-string
 memset(RuleNameAttribute,0,AttributeSize+1);                                                                  // initialize with terminators



 list<const char*> KeyWords;
 RuleName = RuleData->CalledRule.begin();                                                                      // name of rule to add in new attribute
 while(RuleName != RuleData->CalledRule.end())                                                                 // over all collected rule names
 {
  KeyWords.push_back((*RuleName)->data_get()->Detail[Spirit185_Data::attValue]);
  ++RuleName;
 }

 KeyWords.sort(Spirit185_Property::compareIdentifier);

 list<const char*>::iterator KeyWord = KeyWords.begin();                                                       // rule-identifier to analyse
 while(KeyWord != KeyWords.end())                                                                              // over all collected rule names
 {
  strcat(RuleNameAttribute, *KeyWord);                                                                         // add rule name
  strcat(RuleNameAttribute, ",");                                                                              // add split character
  ++KeyWord;
 }


 RuleNameAttribute[AttributeSize-1] = 0;                                                                       // replace last split character by string termination

 RuleData->Detail[Spirit185_Data::attUsing] = RuleNameAttribute;                                               // store new attribute

 return(Rule);
}






/* @MRTZ_describe evaluate_Expression

*/
Spirit185_Data::Spirit185_DataAssociation*  Spirit185_Property::evaluate_Expression(set<Spirit185_Data::Spirit185_DataAssociation*>* usedRules,
                                                                                    Spirit185_Data::Spirit185_DataAssociation*       destination,
                                                                                    TiPa_Concrete::DataAssociation*                  source/*,
                                                                                    TiPa_Concrete::DataAssociation*                  sponsor*/)
{
 Spirit185_DataAssociation* ReturnValue = nullptr;

 if(source != nullptr)
 {
  if(destination != nullptr)                                                                  // destination defined
   ReturnValue = destination;                                                                 // return given destination
  else                                                                                        // destination undefined
   ReturnValue = Att.DataBase;                                                                // return root of database

  switch(source->data_get()->UserID)                                                          // differ between kind of source-parser
  {

   case Spirit185_Internal::Character_rid:                                                    // character or string parser
   case Spirit185_Internal::KeyWord_rid:
   {
    TiPa_Concrete::DataAssociation* Contractor = source->contractorFirst_get();               // next sub-node to analyse
    ReturnValue = evaluate_Expression(usedRules,destination,Contractor/*,source*/);               // analyse sub-node
   }break;

   case Spirit185_Internal::Identifier_rid:                                                   // identifier of other rule
   {
    Spirit185_Data* Data = Att.ContextModel.data_create();                                    // create data-object
    Data->SourceData = source;                                                                // connect data with source-node
    Data->Detail[Spirit185_Data::attName]  = source->data_get()->userName_get();                    // default-name given in spirit-185 internal
    Data->Detail[Spirit185_Data::attValue] = source->data_get()->getContent();

//    cout <<            source->data_get()->getContent()  << " -> "
//         << getRuleKey(source->data_get()->getContent()) << endl ;


    if(Att.Rule.find(getRuleKey(source->data_get()->getContent()))!=Att.Rule.end())           // store user-identifier in used-rules of calling rule
     usedRules->insert(Att.Rule[getRuleKey(source->data_get()->getContent())]);               // store user-identifier in used-rules of calling rule
    destination->data_set(Data);                                                              // connect data-object to destination-node

   }break;
   case Spirit185_Internal::CharacterSingle_rid:                                              // single character
   case Spirit185_Internal::KeyWordCommentSingle_rid:                                         // single comment-string
   case Spirit185_Internal::KeyWordString_rid:                                                // single string
   case Spirit185_Internal::KeyWordCharSequence_rid:                                          // character-sequence
   case Spirit185_Internal::Primitive_rid:                                                    // primitive
   {
    Spirit185_Data* Data = Att.ContextModel.data_create();                                    // create data-object
    Data->SourceData = source;                                                                // connect data with source-node

    TiPa_Concrete::DataAssociation* Contractor = source->contractorFirst_get();                      // next sub-node to analyse

    Data->Detail[Spirit185_Data::attName]  = source->data_get()->userName_get();                    // default-name given in spirit-185 internal
    Data->Detail[Spirit185_Data::attValue] = Contractor->data_get()->getContent();            // identifier given by the user
    destination->data_set(Data);                                                              // connect data-object to destination-node

    if(  (source->data_get()->UserID != Spirit185_Internal::CharacterSingle_rid)
       &&(source->data_get()->UserID != Spirit185_Internal::Primitive_rid      )
      )                                                                                       // its a string
     Att.ReservedWords[(Contractor->data_get()->getContent())] = destination;                 // prepare generation of pseudo-rule "reserved_rules"

   }break;
   case Spirit185_Internal::CharacterRange_rid:                                               // character-range
   case Spirit185_Internal::KeyWordCommentDouble_rid:                                         // pair of comment-strings
   {
    Spirit185_Data* Data = Att.ContextModel.data_create();                                    // create data-object
    Data->SourceData = source;                                                                // connect data with source-node

    TiPa_Concrete::DataAssociation* Contractor = source->contractorFirst_get();                      // next sub-node to analyse

    Data->Detail[Spirit185_Data::attName]   = source->data_get()->userName_get();                   // default-name given in spirit-185 internal
    Data->Detail[Spirit185_Data::attValue1] = Contractor->data_get()->getContent();           // identifier given by the user
    Contractor = source->contractorBehind_get(Contractor);                                    // next source-contractor
    Data->Detail[Spirit185_Data::attValue2] = Contractor->data_get()->getContent();           // identifier given by the user

    destination->data_set(Data);                                                              // connect data-object to destination-node

   }break;

   case Spirit185_Internal::BinSequence_rid:                                                  // sequence
   case Spirit185_Internal::BinCondition_rid:                                                 // condition
   {
    TiPa_Concrete::DataAssociation* Contractor1 = source->contractorFirst_get();              // first sub-node to analyse
    Spirit185_DataAssociation* NewAssociation1 = Att.ContextModel.fellow_create();            // create new note
    NewAssociation1 = evaluate_Expression(usedRules,NewAssociation1,Contractor1/*,source*/);      // fill new note with data and own contractors

    TiPa_Concrete::DataAssociation* Contractor2 = source->contractorBehind_get(Contractor1);  // second sub-node to analyse

    if(Contractor2->data_get()->UserID != Spirit185_Internal::BinOperand_WthOt_rid)
    {
     ReturnValue->contractorLast_add(NewAssociation1);                                         // add new node to destination tree

     TiPa_Concrete::DataAssociation* SubContractor = Contractor2->contractorFirst_get();              // sub-sub node to analyse
     while(SubContractor != nullptr)
     {
      Spirit185_DataAssociation* NewAssociation = Att.ContextModel.fellow_create();         // create new sub-destination node
      NewAssociation = evaluate_Expression(usedRules,NewAssociation,SubContractor/*,Contractor2*/);// analyse sub-sub node
      ReturnValue->contractorLast_add(NewAssociation);                                         // add new node to destination tree
      SubContractor = Contractor2->contractorBehind_get(SubContractor);                        // next sub-sub node
     }
    }
    else
    {
     Spirit185_DataAssociation* NewAssociation1a = Att.ContextModel.fellow_create();        // create new note
     Spirit185_Data* Data = Att.ContextModel.data_create();                                    // create data-object
     Data->SourceData = NewAssociation1->data_get()->SourceData;                                                             // connect data with source-node
     Data->Detail[Spirit185_Data::attName]  = "First";                                         // default-name given in spirit-185 internal
     NewAssociation1a->data_set(Data);
     NewAssociation1a->contractorLast_add(NewAssociation1);                                    // add new node to destination tree
     ReturnValue->contractorLast_add(NewAssociation1a);                                        // add new node to destination tree

     TiPa_Concrete::DataAssociation* SubContractor = Contractor2->contractorFirst_get();              // sub-sub node to analyse
     if(SubContractor != nullptr)
     {
      Spirit185_DataAssociation* NewAssociation = Att.ContextModel.fellow_create();         // create new sub-destination node
      NewAssociation = evaluate_Expression(usedRules,NewAssociation,SubContractor/*,Contractor2*/);// analyse sub-sub node

      Spirit185_DataAssociation* NewAssociation2a = Att.ContextModel.fellow_create();       // create new note
      Data = Att.ContextModel.data_create();
      Data->SourceData = NewAssociation->data_get()->SourceData;                                                             // connect data with source-node
      Data->Detail[Spirit185_Data::attName]  = "Second";                                       // default-name given in spirit-185 internal
      NewAssociation2a->data_set(Data);
      NewAssociation2a->contractorLast_add(NewAssociation);                                    // add new node to destination tree
      ReturnValue->contractorLast_add(NewAssociation2a);                                       // add new node to destination tree
     }
    }

    Spirit185_Data* Data = Att.ContextModel.data_create();                                     // create data-object
    Data->SourceData = source;                                                                 // connect data with source-node
    Data->Detail[Spirit185_Data::attName]  = Contractor2->data_get()->userName_get();                // default-name given in spirit-185 internal
    destination->data_set(Data);                                                               // connect data-object to destination-node

   }break;
   case Spirit185_Internal::UniOperation_rid:                                                  // unary parser
   {
    TiPa_Concrete::DataAssociation* Contractor = source->contractorFirst_get();                       // next sub-node to analyse
    TiPa_Concrete::DataAssociation* SubContractor = Contractor->contractorFirst_get();                // next sub-sub node to analyse

    Spirit185_DataAssociation* NewAssociation = Att.ContextModel.fellow_create();              // create new sub-destination node
    NewAssociation = evaluate_Expression(usedRules,NewAssociation, SubContractor/*, Contractor*/); // analyse sub-sub node
    ReturnValue->contractorLast_add(NewAssociation);                                           // add new node to destination tree

    Spirit185_Data* Data = Att.ContextModel.data_create();                                     // create data-object
    Data->SourceData = source;                                                                 // connect data with source-node
    Data->Detail[Spirit185_Data::attName]  = Contractor->data_get()->userName_get();                 // default-name given in spirit-185 internal
    destination->data_set(Data);

   }break;

   default:                                                                                    // all other sub-nodes of source-tree
   {

    Spirit185_Data* Data = Att.ContextModel.data_create();                                     // create data-object
    Data->SourceData = source;                                                                 // connect data with source-node

    Data->Detail[Spirit185_Data::attName]  = source->data_get()->userName_get();                     // default-name given in spirit-185 internal
    Data->Detail[Spirit185_Data::attValue] = source->data_get()->userName_get();                     // default-name given in spirit-185 internal
    destination->data_set(Data);                                                               // connect data-object to destination-node
    TiPa_Concrete::DataAssociation* Contractor = source->contractorFirst_get();                       // next sub-node to analyse
    while(Contractor != nullptr)                                                               // over all sub-nodes
    {
     Spirit185_DataAssociation* NewAssociation = Att.ContextModel.fellow_create();             // create new note
     NewAssociation = evaluate_Expression(usedRules,NewAssociation,Contractor/*,source*/);         // fill new note with data and own contractors
     ReturnValue->contractorLast_add(NewAssociation);                                          // add new node to destination tree
     Contractor = source->contractorBehind_get(Contractor);                                    // next sub-node
    }
   }break;
  }
 }

 return(ReturnValue);
}





/* @MRTZ_describe evaluate_isUsedBy

*/
void Spirit185_Property::evaluate_isUsedBy(void)
{
 map<const char*,Spirit185_DataAssociation*>::iterator  UsingRule1 = Att.Rule.begin();
 while(UsingRule1 != Att.Rule.end())                                                           // fill all rules in database
 {
  Spirit185_Data*                              DataUsing = UsingRule1->second->data_get();     // data container to fill
  set<Spirit185_DataAssociation*>::iterator UsedRule1 = DataUsing->CalledRule.begin();      // rule-identifier to analyse
  while(UsedRule1 != DataUsing->CalledRule.end())                                              // over all collected rule names
  {
   (*UsedRule1)->data_get()->CallingRule.insert(UsingRule1->second);                            // store rule-identifier as using one of used rule
   ++UsedRule1;                                                                                // continue search
  }
  ++ UsingRule1;                                                                               // next rule to fill
 }


 map<const char*,Spirit185_DataAssociation*>::iterator  UsedRule2 = Att.Rule.begin();
 while(UsedRule2 != Att.Rule.end())                                                           // fill all rules in database
 {
  Spirit185_Data* DataUsed      = UsedRule2->second->data_get();                              // data container to fill
  int             AttributeSize = 0;                                                         // size of new attribute string
  set<Spirit185_DataAssociation*>::iterator UsingRule2 = DataUsed->CallingRule.begin();    // rule-identifier to analyse
  while(UsingRule2 != DataUsed->CallingRule.end())                                            // over all collected rule names
  {
   Spirit185_Data* DataUsing  = (*UsingRule2)->data_get();                                    // data container to fill
   AttributeSize = AttributeSize + strlen(DataUsing->Detail[Spirit185_Data::attValue]) + 1;  // rule name and split character like comma
   ++UsingRule2;                                                                              // continue search
  }

  char* RuleNameAttribute = new char[AttributeSize+1];                                       // new attribute
  memset(RuleNameAttribute,0,AttributeSize+1);                                               // initialise string with terminators

  list<const char*> KeyWords;
  UsingRule2 = DataUsed->CallingRule.begin();                                                 // rule-identifier to analyse
  while(UsingRule2 != DataUsed->CallingRule.end())                                            // over all collected rule names
  {
   KeyWords.push_back((*UsingRule2)->data_get()->Detail[Spirit185_Data::attValue]);
   ++UsingRule2;
  }

  KeyWords.sort(Spirit185_Property::compareIdentifier);

  list<const char*>::iterator KeyWord = KeyWords.begin();                                    // rule-identifier to analyse
  while(KeyWord != KeyWords.end())                                                           // over all collected rule names
  {
   strcat(RuleNameAttribute, *KeyWord);                                                      // add rule name
   strcat(RuleNameAttribute, ",");                                                           // add split character
   ++KeyWord;
  }

  RuleNameAttribute[AttributeSize-1] = 0;                                                    // replace last split character by string termination

  DataUsed->Detail[Spirit185_Data::attUsedBy] = RuleNameAttribute;                           // store new attribute

  ++ UsedRule2;                                                                               // next rule to fill
 }



}










/* @MRTZ_describe evaluate_Collaboration

*/
void Spirit185_Property::evaluate_Collaboration(const char* notPhrased, char separator,
                                                int limitCallingTree,   int  limitCallingNode,
                                                int limitCallerTree,    int  limitCallerNode)
{
 map<const char*,Spirit185_DataAssociation*>::iterator  Rule = Att.Rule.begin();
 while(Rule != Att.Rule.end())                                                           //  all rules in database
 {
  Spirit185_Data* RuleData                       = Rule->second->data_get();             // data container to analyse

  Spirit185_DataAssociation* Property         = Att.ContextModel.fellow_create();     // create new expression node
  Spirit185_Data*               PropertyData     = Att.ContextModel.data_create();       // data object of expression-node
  PropertyData->SourceData                       = RuleData->SourceData;                 // connect core data
  PropertyData->Detail[Spirit185_Data::attName]  = "Property" ;                          // standard node identifier
  Property->data_set(PropertyData);

  Rule->second->contractorLast_add(Property);                                            // connect expression node and expression data

  Spirit185_DataAssociation* Calling         = Att.ContextModel.fellow_create();      // create new expression node
  Spirit185_Data*               CallingData     = Att.ContextModel.data_create();        // data object of expression-node
  CallingData->SourceData                       = RuleData->SourceData;                  // connect core data
  CallingData->Detail[Spirit185_Data::attName]  = "Called" ;                             // standard node identifier
  Calling->data_set(CallingData);                                                        // connect expression node and expression data

  Rule->second->contractorLast_add(Calling);                                             // connect expression to rule

  Spirit185_DataAssociation* Caller         = Att.ContextModel.fellow_create();       // create new expression node
  Spirit185_Data*               CallerData     = Att.ContextModel.data_create();         // data object of expression-node
  CallerData->SourceData                       = RuleData->SourceData;                   // connect core data
  CallerData->Detail[Spirit185_Data::attName]  = "Caller" ;                              // standard node identifier
  Caller->data_set(CallerData);                                                          // connect expression node and expression data

  Rule->second->contractorLast_add(Caller);                                              // connect expression to rule

  const char * SearchedName = strstr(notPhrased,Rule->first);                            // name of the rule
  int          SearchLength = strlen(Rule->first);                                       // length of rule-name
  if(  (SearchedName != nullptr)
     &&(  (SearchedName[SearchLength] == separator)
        ||(SearchedName[SearchLength] == 0)
       )
    )                                                                                    // rule-name was found as separate word in side not-phrased list or at its end
   PropertyData->Detail[Spirit185_Data::attPhrased]  = "not phrased";                    // rule is ignoring white spaces
  else
   PropertyData->Detail[Spirit185_Data::attPhrased]  = "phrased";                        // rule consumes white spaces

  evaluate_Calling(Rule->second, Property, Calling, limitCallingTree, limitCallingNode);
  evaluate_Caller (Rule->second, Property, Caller,  limitCallerTree,  limitCallerNode);

  ++Rule;
 }

}



/* @MRTZ_describe evaluate_Calling

*/
void Spirit185_Property::evaluate_Calling(Spirit185_DataAssociation* rule,
                                          Spirit185_DataAssociation* property,
                                          Spirit185_DataAssociation* calling,
                                          int                           limitTree,
                                          int                           limitNode)
{
 set<Spirit185_DataAssociation*> AlreadyChecked;
 AlreadyChecked.insert(rule);
 set<Spirit185_DataAssociation*> AlreadyKnown;

 if(limitNode < 0)
  limitTree = -1;
 else
  -- limitTree;


 Spirit185_Data* PropertyData = property->data_get();           // data object of expression-node

 int   LeafLevel = 0;

 Spirit185_Data* RuleData    = rule->data_get();                // data container to analyse

 list<const char*> KeyWords;
 set<Spirit185_DataAssociation*>::iterator UsedRule  = RuleData->CalledRule.begin(); // rule-identifier to analyse
 while (UsedRule  != RuleData->CalledRule.end())
 {
  KeyWords.push_back((*UsedRule)->data_get()->Detail[Spirit185_Data::attValue]);
  ++UsedRule;

 }
 KeyWords.sort(Spirit185_Property::compareIdentifier);

 list<const char*>::iterator KeyWord = KeyWords.begin();
 while(  (KeyWord  != KeyWords.end())
       &&(limitTree >= 0)
      )
 {
  Spirit185_Data* DataUsed      = Att.Rule[*KeyWord] ->data_get();                                  // data container to fill
  int             SingleResult  = 0;

  if(Att.Rule[*KeyWord] == rule)
  {
   LeafLevel = -1;
  }

   -- limitNode;

   Spirit185_DataAssociation* SubCalling         = Att.ContextModel.fellow_create();         // create new expression node
   Spirit185_Data*               SubCallingData     = Att.ContextModel.data_create();           // data object of expression-node
   SubCalling->data_set(SubCallingData);
   calling->contractorLast_add(SubCalling);

   SingleResult  = check_Calling(&AlreadyChecked,
                                 &AlreadyKnown,
                                 rule,
                                 Att.Rule[*KeyWord],
                                 SubCalling,
                                 limitTree,
                                 limitNode);
   if (LeafLevel >= 0)
     LeafLevel = SingleResult;

  Spirit185_DataAssociation* SubProperty         = Att.ContextModel.fellow_create();         // create new expression node
  Spirit185_Data*               SubPropertyData     = Att.ContextModel.data_create();           // data object of expression-node
  SubPropertyData->SourceData                       = DataUsed->SourceData;                     // connect core data
  SubProperty->data_set(SubPropertyData);
  property->contractorLast_add(SubProperty);
                                                                                                // connect expression node and expression data
  if     (LeafLevel >= 0)
  {
   SubPropertyData->Detail[Spirit185_Data::attName]  = "Uses_Terminated" ;                      // parser with direct or indirect termination
  }
  else if(LeafLevel == -1 )
  {
   SubPropertyData->Detail[Spirit185_Data::attName]  = "Uses_Recursive" ;                      // parser with direct or indirect recursion back to the calling one
  }
  else
  {
   SubPropertyData->Detail[Spirit185_Data::attName]  = "Uses" ;                                // not known if terminated or recursive
  }

  SubPropertyData->Detail[Spirit185_Data::attValue]  = DataUsed->Detail[Spirit185_Data::attValue]; // standard node identifier

  ++ KeyWord;
 }

 PropertyData->LevelLeaf = LeafLevel;
 char* Leaf = nullptr;
 Spirit185_Data::itoa(&Leaf,PropertyData->LevelLeaf);
 PropertyData->Detail[Spirit185_Data::attLeafLevel]  = Leaf ;                            // standard node identifier

}

/* @MRTZ_describe check_Calling

*/
int Spirit185_Property::check_Calling(set<Spirit185_DataAssociation*>* alreadyChecked,
                                      set<Spirit185_DataAssociation*>* alreadyKnown,
                                      Spirit185_DataAssociation* searchObject,
                                      Spirit185_DataAssociation* rule,
                                      Spirit185_DataAssociation* calling,
                                      int                           limitTree,
                                      int                           limitNode)
{
 int             ReturnValue               = alreadyChecked->size();

 Spirit185_Data* DataUsed                  = rule->data_get();                                  // data container to fill

 Spirit185_Data* CallingData               = calling->data_get();                               // data object of expression-node
 CallingData->SourceData                   = DataUsed->SourceData;                              // connect core data
 CallingData->Detail[Spirit185_Data::attV] = DataUsed->Detail[Spirit185_Data::attValue];        // standard node identifier
 char*           CallingLevel              = nullptr;
 Spirit185_Data::itoa(&CallingLevel,alreadyChecked->size());
 CallingData->Detail[Spirit185_Data::attC] = CallingLevel;                                      // standard node identifier

 if(limitNode < 0)
  limitTree = -1;
 else
  -- limitTree;

 if(limitTree<0)
  ReturnValue = -2;

 if     (rule == searchObject)
 {
  CallingData->Detail[Spirit185_Data::attName]  = "R" ;                                    // R == CallWithRecursion;
 }
 else if(DataUsed->CalledRule.empty())
 {
  CallingData->Detail[Spirit185_Data::attName]  = "T" ;                                    // T == TerminatingParser;
 }
 else if(limitTree < 0)
 {
  CallingData->Detail[Spirit185_Data::attName]  = "X" ;                                    // X == TerminationOfGraph_ButNo_TerminatingParser
 }
 else
 {
  CallingData->Detail[Spirit185_Data::attName]  = "C" ;                                    // C == CallWithoutRecursion;
 }

 if(  (alreadyChecked->find(rule) == alreadyChecked->end())
    &&(alreadyKnown->find(rule)   == alreadyKnown->end())
   )                                // avoid entering endless recursion-loops and double edges in caller-diagrams
 {
  alreadyChecked->insert(rule);

  list<const char*> KeyWords;
  set<Spirit185_DataAssociation*>::iterator UsedRule  = DataUsed->CalledRule.begin(); // rule-identifier to analyse
  while (UsedRule  != DataUsed->CalledRule.end())
  {
   KeyWords.push_back((*UsedRule)->data_get()->Detail[Spirit185_Data::attValue]);
   ++UsedRule;

  }
  KeyWords.sort(Spirit185_Property::compareIdentifier);

  list<const char*>::iterator KeyWord = KeyWords.begin();
  while(  (KeyWord  != KeyWords.end())
        &&(limitTree >= 0)
       )
  {
   int             SingleResult  = 0;

   if(Att.Rule[*KeyWord] == searchObject)
   {
    ReturnValue = -1;
   }

   -- limitNode;

   if(  (alreadyChecked->find(Att.Rule[*KeyWord]) == alreadyChecked->end())
      &&(alreadyKnown->find(Att.Rule[*KeyWord])   == alreadyKnown->end())
     )                                // avoid entering endless recursion-loops and double edges in caller-diagrams
   {
    Spirit185_DataAssociation* SubCalling         = Att.ContextModel.fellow_create();         // create new expression node
    Spirit185_Data*               SubCallingData     = Att.ContextModel.data_create();           // data object of expression-node
    SubCalling->data_set(SubCallingData);
    calling->contractorLast_add(SubCalling);

    SingleResult  = check_Calling(alreadyChecked,
                                  alreadyKnown,
                                  searchObject,
                                  Att.Rule[*KeyWord],
                                  SubCalling,
                                  limitTree,
                                  limitNode);

    alreadyKnown->insert(Att.Rule[*KeyWord]);
   }
   if (ReturnValue >= 0)
    ReturnValue = SingleResult;

   ++ KeyWord;
  }

  alreadyChecked->erase(rule);
 }



 return(ReturnValue);
}







/* @MRTZ_describe evaluate_Caller

*/
void Spirit185_Property::evaluate_Caller(Spirit185_DataAssociation* rule,
                                         Spirit185_DataAssociation* property,
                                         Spirit185_DataAssociation* caller,
                                         int                           limitTree,
                                         int                           limitNode)
{
 set<Spirit185_DataAssociation*> AlreadyChecked;
 AlreadyChecked.insert(rule);
 set<Spirit185_DataAssociation*> AlreadyKnown;

 if(limitNode < 0)
  limitTree = -1;
 else
  -- limitTree;

 Spirit185_Data* PropertyData = property->data_get();           // data object of expression-node

 int   RootLevel = 0;

 Spirit185_Data* RuleData                                = rule->data_get();                         // data container to analyse

 list<const char*> KeyWords;
 set<Spirit185_DataAssociation*>::iterator UsingRule  = RuleData->CallingRule.begin();      // rule-identifier to analyse
 while (UsingRule  != RuleData->CallingRule.end())
 {
  KeyWords.push_back((*UsingRule)->data_get()->Detail[Spirit185_Data::attValue]);
  ++UsingRule;

 }
 KeyWords.sort(Spirit185_Property::compareIdentifier);

 list<const char*>::iterator KeyWord = KeyWords.begin();
 while(  (KeyWord  != KeyWords.end())
       &&(limitTree >= 0)
      )
 {

  Spirit185_Data* DataUsing    = Att.Rule[*KeyWord]->data_get();
  if(Att.Rule[*KeyWord] == rule)
  {
   RootLevel = -1;
  }

  -- limitNode;

  Spirit185_DataAssociation* SubCaller         = Att.ContextModel.fellow_create();           // create new expression node
  Spirit185_Data*               SubCallerData     = Att.ContextModel.data_create();             // data object of expression-node
  SubCaller->data_set(SubCallerData);
  caller->contractorLast_add(SubCaller);


  int SingleResult = check_Caller(&AlreadyChecked,
                                  &AlreadyKnown,
                                  rule,
                                  Att.Rule[*KeyWord],
                                  SubCaller,
                                  limitTree,
                                  limitNode);
  if (RootLevel >= 0)
    RootLevel = SingleResult;


  Spirit185_DataAssociation* SubProperty         = Att.ContextModel.fellow_create();         // create new expression node
  Spirit185_Data*               SubPropertyData     = Att.ContextModel.data_create();           // data object of expression-node
  SubPropertyData->SourceData                       = DataUsing->SourceData;                    // connect core data
  SubProperty->data_set(SubPropertyData);
  property->contractorLast_add(SubProperty);                                                    // connect expression node and expression data

  if     (RootLevel >= 0)
  {
   SubPropertyData->Detail[Spirit185_Data::attName]  = "UsedBy_Terminated" ;                    // parser with direct or indirect termination
  }
  else if(RootLevel == -1)
  {
   SubPropertyData->Detail[Spirit185_Data::attName]  = "UsedBy_Recursive" ;                     // parser with direct or indirect recursion back to the calling one
  }
  else
  {
   SubPropertyData->Detail[Spirit185_Data::attName]  = "UsedBy" ;                               // not known if terminated or recursive
  }

  SubPropertyData->Detail[Spirit185_Data::attValue]  = DataUsing->Detail[Spirit185_Data::attValue]; // standard node identifier

  ++ KeyWord;

 }

 PropertyData->LevelRoot = RootLevel;
 char* Root = nullptr;
 Spirit185_Data::itoa(&Root,PropertyData->LevelRoot);
 PropertyData->Detail[Spirit185_Data::attRootLevel]  = Root ;                            // standard node identifier
}






/* @MRTZ_describe check_Caller

*/
int Spirit185_Property::check_Caller(set<Spirit185_DataAssociation*>* alreadyChecked,
                                     set<Spirit185_DataAssociation*>* alreadyKnown,
                                     Spirit185_DataAssociation*       searchObject,
                                     Spirit185_DataAssociation*       rule,
                                     Spirit185_DataAssociation*       caller,
                                     int                                 limitTree,
                                     int                                 limitNode)
{
 int             ReturnValue              = alreadyChecked->size();

 Spirit185_Data* DataUsing                = rule->data_get();

 Spirit185_Data* CallerData               = caller->data_get();                          // data object of expression-node
 CallerData->SourceData                   = DataUsing->SourceData;                       // connect core data
 CallerData->Detail[Spirit185_Data::attV] = DataUsing->Detail[Spirit185_Data::attValue]; // standard node identifier
 char*           CallerLevel              = nullptr;
 Spirit185_Data::itoa(&CallerLevel,alreadyChecked->size());
 CallerData->Detail[Spirit185_Data::attC] = CallerLevel;                                 // standard node identifier

 if(limitNode < 0)
  limitTree = -1;
 else
  -- limitTree;

 if(limitTree<0)
  ReturnValue = -2;

 if      (rule == searchObject)
 {
  CallerData->Detail[Spirit185_Data::attName]  = "R" ;                                    // R == CallWithRecursion;
 }
 else if(DataUsing->CallingRule.empty())
 {
  CallerData->Detail[Spirit185_Data::attName]  = "T" ;                                    // T == TerminatingParser;
 }
 else if(limitTree < 0 )
 {
  CallerData->Detail[Spirit185_Data::attName]  = "X" ;                                    // X == TerminationOfGraph_ButNo_TerminatingParser
 }
 else
 {
  CallerData->Detail[Spirit185_Data::attName]  = "C" ;                                    // C == CallWithoutRecursion;
 }

 if(  (alreadyChecked->find(rule) == alreadyChecked->end())
    &&(alreadyKnown->find(rule)   == alreadyKnown->end())
   )                                                                                      // avoid entering endless recursion-loops and double edges in caller-diagrams
 {
  alreadyChecked->insert(rule);
  list<const char*> KeyWords;
  set<Spirit185_DataAssociation*>::iterator UsingRule  = DataUsing->CallingRule.begin();      // rule-identifier to analyse
  while (UsingRule  != DataUsing->CallingRule.end())
  {
   KeyWords.push_back((*UsingRule)->data_get()->Detail[Spirit185_Data::attValue]);
   ++UsingRule;

  }
  KeyWords.sort(Spirit185_Property::compareIdentifier);

  list<const char*>::iterator KeyWord = KeyWords.begin();
  while(  (KeyWord  != KeyWords.end())
        &&(limitTree >= 0)
       )
  {
   int             SingleResult = 0;

   if(Att.Rule[*KeyWord] == searchObject)
   {
    ReturnValue = -1;
   }

   -- limitNode;

   if(  (alreadyChecked->find(Att.Rule[*KeyWord]) == alreadyChecked->end())
      &&(alreadyKnown->find(Att.Rule[*KeyWord])   == alreadyKnown->end())
     )                                // avoid entering endless recursion-loops and double edges in caller-diagrams
   {
    Spirit185_DataAssociation* SubCaller         = Att.ContextModel.fellow_create();           // create new expression node
    Spirit185_Data*               SubCallerData     = Att.ContextModel.data_create();             // data object of expression-node
    SubCaller->data_set(SubCallerData);
    caller->contractorLast_add(SubCaller);

    SingleResult = check_Caller(alreadyChecked,
                                alreadyKnown,
                                searchObject,
                                Att.Rule[*KeyWord],
                                SubCaller,
                                limitTree,
                                limitNode);
    alreadyKnown->insert(Att.Rule[*KeyWord]);
   }
   if (ReturnValue >= 0)
    ReturnValue = SingleResult;

   ++ KeyWord;
  }
  alreadyChecked->erase(rule);
 }

 return(ReturnValue);
}



bool Spirit185_Property::compareIdentifier(const char* String1, const char* String2)
{
 bool ReturnValue = true;               // will be the case if both strings do not differ

 int MaxIndex = 0;
 if(strlen(String1) < strlen(String2))  // first sting is the shorter one
  MaxIndex = strlen(String1);
 else                                   // second string is equal or shorter
  MaxIndex = strlen(String2);

 int Index = 0;
 while( Index <= MaxIndex)             // iterate until termination of shorter string
 {
  if     (  (String1[Index]          == 0)
          ||(tolower(String1[Index]) <  tolower(String2[Index]))
         )  // not case sensitive compare or end of string
  {
   ReturnValue = true;
   break;
  }
  else if(  (String2[Index]          == 0)
          ||(tolower(String2[Index]) < tolower(String1[Index]))
         )  // not case sensitive compare or end of string
  {
   ReturnValue = false;
   break;
  }
  else  // both characters are equal
  {
   ++Index;  // continue loop
  }
 }

 return(ReturnValue);
}






/* @MRTZ_describe getRuleKey

*/
const char* Spirit185_Property::getRuleKey(const char* ruleName)
{
 const char* ReturnValue = nullptr;

 map<const char*,Spirit185_DataAssociation*>::iterator Rule = Att.Rule.begin();
 while(Rule != Att.Rule.end())
 {
  if(  (strstr(ruleName,Rule->first) == ruleName        )
     &&(strlen(Rule->first)          == strlen(ruleName))
    )
  {
   ReturnValue = Rule->first;
   break;
  }
  else
   ++ Rule;
 }

 return(ReturnValue);
}



/* @MRTZ_describe storeDataBaseAsXML

*/
void Spirit185_Property::storeDataBaseAsXML(const char* file)
{

 list<const char*> KeyWords;

 map<const char*,Spirit185_DataAssociation*>::iterator  Rule = Att.Rule.begin();
 while(Rule != Att.Rule.end())                                                       //  all rules in database
 {
  KeyWords.push_back(Rule->first);
  ++Rule;
 }

 KeyWords.sort(Spirit185_Property::compareIdentifier);

 XML_DataModel OutPut;                              // xml log-document
 XML_Node Root = OutPut.rootNode().lastAdd(XML_Data::NT_Element); // root note of xml-representation

 Root.valueSet("Content");
 int Counter = 1;
 list<const char*>::iterator KeyWord = KeyWords.begin();
 while(KeyWord != KeyWords.end())                                                       //  all rules in database
 {
  XML_Node Child = Root.lastAdd(XML_Data::NT_Element);
  Child.valueSet("Child");

  Child.attributeSet("number",Counter);
  ++ Counter;

  transformDataBaseToXML(Child,Att.Rule[*KeyWord]);         // transfer database-content into xml


  ++KeyWord;
 }


// OutPut.LinkEndChild(Root);                       // associate xml-tree with xml-document
 unsigned int Size = strlen(file) +4 +1;            // size of file + size of attachment + termination
 char* LogFile = new char[Size];                    // path and name of new xml-file plus new extension
 memset(LogFile,0,Size);                            // ensure termination
 strcpy(LogFile,file);                              // create an independent copy

 char* DotPosSearch  = strchr(LogFile,'.');         // next potential dot
 char* DotPos        = strchr(LogFile,'.');         // last dot found found
 while(DotPosSearch != nullptr)                     // as long next dot exists
 {
  DotPos       = DotPosSearch;                      // store last dot found
  DotPosSearch = strchr(DotPos+1,'.');              // search for next dot
 }


 if(DotPos != nullptr)                              // last dot found and exists
  DotPos[0] = 0;                                    // terminate file name before give extension
 strcat(LogFile,".xml");                            // add new extension


 OutPut.save(LogFile);                              // store xml log-file

 cout << "stored analysed grammar as: " << LogFile <<  endl;
 delete[](LogFile);

}









/* @MRTZ_describe transformDataBaseToXML

*/
void Spirit185_Property::transformDataBaseToXML(XML_Node                   destination,
                                                Spirit185_DataAssociation* source)
{
 TiPa_Data*      CoreData = nullptr;
 Spirit185_Data* ExtendedData = source->data_get();



 if(ExtendedData != nullptr)
 {
  TiPa_Concrete::DataAssociation*  SourceAssociation = ExtendedData->SourceData;
  if(SourceAssociation != nullptr)
  {
   CoreData = SourceAssociation->data_get();

  }
  else
  {
   cout << "no source association found" << endl;
  }
 }
 else
 {
  cout << "no extended data found" << endl;
 }

 if(  (CoreData     != nullptr)
    &&(ExtendedData != nullptr)
   )
 {
  if(ExtendedData->Detail.find(Spirit185_Data::attName) != ExtendedData->Detail.end())
   destination.valueSet(ExtendedData->Detail[Spirit185_Data::attName]);
  else
   destination.valueSet(CoreData->userName_get());

  if(ExtendedData->Detail.find(Spirit185_Data::attValue) != ExtendedData->Detail.end())
   destination.attributeSet("value",ExtendedData->Detail[Spirit185_Data::attValue]);

  if(ExtendedData->Detail.find(Spirit185_Data::attValue1) != ExtendedData->Detail.end())
   destination.attributeSet("value1",ExtendedData->Detail[Spirit185_Data::attValue1]);

  if(ExtendedData->Detail.find(Spirit185_Data::attValue2) != ExtendedData->Detail.end())
   destination.attributeSet("value2",ExtendedData->Detail[Spirit185_Data::attValue2]);

  if(ExtendedData->Detail.find(Spirit185_Data::attUsing) != ExtendedData->Detail.end())
   destination.attributeSet("uses",ExtendedData->Detail[Spirit185_Data::attUsing]);

  if(ExtendedData->Detail.find(Spirit185_Data::attUsedBy) != ExtendedData->Detail.end())
   destination.attributeSet("usedBy",ExtendedData->Detail[Spirit185_Data::attUsedBy]);

  if(ExtendedData->Detail.find(Spirit185_Data::attV) != ExtendedData->Detail.end())
   destination.attributeSet("v",ExtendedData->Detail[Spirit185_Data::attV]);

  if(ExtendedData->Detail.find(Spirit185_Data::attC) != ExtendedData->Detail.end())
   destination.attributeSet("c",ExtendedData->Detail[Spirit185_Data::attC]);

  if(ExtendedData->Detail.find(Spirit185_Data::attLeafLevel) != ExtendedData->Detail.end())
    destination.attributeSet("leafLevel",ExtendedData->Detail[Spirit185_Data::attLeafLevel]);

  if(ExtendedData->Detail.find(Spirit185_Data::attRootLevel) != ExtendedData->Detail.end())
    destination.attributeSet("rootLevel",ExtendedData->Detail[Spirit185_Data::attRootLevel]);

  if(ExtendedData->Detail.find(Spirit185_Data::attPhrased)   != ExtendedData->Detail.end())
    destination.attributeSet("characterLevel",ExtendedData->Detail[Spirit185_Data::attPhrased]);

  Spirit185_DataAssociation* Contractor = source->contractorFirst_get();

  while(Contractor != nullptr)
  {
   XML_Node Node =  destination.lastAdd(XML_Data::NT_Element);
            Node.valueSet("Child");
   this->transformDataBaseToXML(Node,Contractor);
   Contractor = source->contractorBehind_get(Contractor);                            // next source-contractor
  }
 }
}




#ifndef DOXYGEN
#define USING_NAMESPACE using namespace
//}; USING_NAMESPACE DATA;
//}; USING_NAMESPACE TDA_Grammar;
//}; USING_NAMESPACE TXTDIASM;
#undef  USING_NAMESPACE
#endif //DOXYGEN



