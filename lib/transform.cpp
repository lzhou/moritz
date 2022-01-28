/*!

 @file
 @brief  definition of an parser-process defined by the user

 This file contains the definition of a user parser-process.

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
    12.07.2009     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    12.07.2009...  @I Eckard Klotz
 @I changed design for spirit
 @I____________________________________________________________
    12.07.2009...  @I Eckard Klotz
 @I Changes are documented in the comment of the changed element
 @TabEnd

*/


#include "String_imp.h"
#include "Spirit185_Internal.h"



#include "transform.h"


#ifndef DOXYGEN
//namespace CL_PROCESS {
//namespace CL_TRANSFORM {
#endif //DOXYGEN



/* @MRTZ_describe Prcs_Transformation

*/
Prcs_Transformation::Prcs_Transformation(void)
{
 Grammar_Spirit185 = new   Spirit185_External(&ContextModel);
// ResultFilter.contextModel_set(&ContextModel);
 ResultFilter.contextModel_set(nullptr);

 TextMakeup.StartLine   = 0;
 TextMakeup.StartColumn = 0;

}



/* @MRTZ_describe Prcs_Transformation

Prcs_Transformation::Prcs_Transformation(const Prcs_Transformation& src):
 TextMakeup       (src.TextMakeup       ),
 ParserLogFile    (src.ParserLogFile    ),
 Grammar_Spirit185(src.Grammar_Spirit185)
// ResultFilter     (src.ResultFilter     ),
// ContextModel     (src.ContextModel     )
{
}
*/

/* @MRTZ_describe operator=

Prcs_Transformation& Prcs_Transformation::operator= (const Prcs_Transformation& src)
{
 TextMakeup        = src.TextMakeup       ;
 ParserLogFile     = src.ParserLogFile    ;
 Grammar_Spirit185 = src.Grammar_Spirit185;
// ResultFilter      = src.ResultFilter     ;
// ContextModel      = src.ContextModel     ;
 return(*this);
}
*/




/* @MRTZ_describe ~Prcs_Transformation

*/
Prcs_Transformation::~Prcs_Transformation(void)
{
 delete(Grammar_Spirit185);
}


/* @MRTZ_describe Grammar_get

*/
Prcs_Transformation::TP_GrammmarStuff* Prcs_Transformation::Grammar_get(void)
{
 return(&Grm);
}


/* @MRTZ_describe ParserLogFile_set

*/
void Prcs_Transformation::ParserLogFile_set(const String_imp& parserLogFile)
{
 ParserLogFile = parserLogFile;
}


/* @MRTZ_describe UserSymbolMap_set

   @MRTZ_describe replace_special_characters

   @MRTZ_describe search_begin_of_name

   @MRTZ_describe search_end_of_name

   @MRTZ_describe save_name

   @MRTZ_describe restore_special_characters

*/
void Prcs_Transformation::UserSymbolMap_set(String_imp className,
                                            String_imp members)
{
#if defined(DEBUG_OUTPUT)
 cout << className << endl;
 cout << members << " : " << members.size() <<endl;
#endif //DEBUG_OUTPUT


 if(  (className != String_imp(""))
    &&(members   != String_imp(""))
   )
 {
// @MRTZ_exclude replace_special_characters
// @MRTZ_beginBlock
  members = replacePartString(members,"\\\\","°_°_°_BACKSLASH_°_°_°");
  members = replacePartString(members,"\\\"","°_°_°_QUOTATION_°_°_°");
  members = replacePartString(members,"\\\'","°_°_°_APOSTROPH_°_°_°");
//@MRTZ_endBlock

 size_t     Iterator  = 0;
  while(  (                 Iterator   < (members.size()-1))
        &&(members.find('"',Iterator) !=   string::npos    )
       )                   //until begin of tag name found or end of given text
  {
#if defined(DEBUG_OUTPUT)
   cout << "members.at("<< Iterator <<") : " <<members.at(Iterator) << endl;
#endif //DEBUG_OUTPUT

// @MRTZ_exclude search_begin_of_name
// @MRTZ_beginBlock
   char Character = members.at(Iterator);        //read next character
   char       ChrctrBfr = 0x00;                  //single character in given text
   while(  (  (Character != '"' )
            ||(ChrctrBfr == '\\' )
           )
         &&(Iterator  <  (members.size()-1))
        )                   //until begin of name found or end of given text
   {
    ChrctrBfr = members.at(Iterator);

    Iterator ++;                              //increment given character-index
#if defined(DEBUG_OUTPUT)
    printf("Getchar 1 starten \n");
#endif //DEBUG_OUTPUT
    Character = members.at(Iterator);        //read next character
#if defined(DEBUG_OUTPUT)
    printf("Getchar 1 fertig \n");
#endif //DEBUG_OUTPUT
#if defined(DEBUG_OUTPUT)
    cout << "members.at("<< Iterator <<") : " << Character << endl;
#endif //DEBUG_OUTPUT
   };
   size_t Pos0 = Iterator;
   Iterator ++;                              //increment given character-index
//@MRTZ_endBlock

// @MRTZ_exclude search_end_of_name
// @MRTZ_beginBlock
   Character = members.at(Iterator);         //read next character
   while(  (  (Character != '"' )
            ||(ChrctrBfr == '\\' )
           )
         &&(Iterator  <  (members.size()-1))
        )                   //until end of name found or end of given text
   {
    ChrctrBfr = members.at(Iterator);
    Iterator ++;                              //increment given character-index
    Character = members.at(Iterator);         //read next character
   };

   size_t Length = Iterator - Pos0 + 1;
   if(Iterator == (members.size()-1))        // no komma found but last character
    Length ++;
//@MRTZ_endBlock


// @MRTZ_exclude save_name
// @MRTZ_beginBlock
   String_imp Name   = members.substr(Pos0, Length);    //find part of member-name
   Length = Name.find('\"') + 1;             //locate opening '"'
   Name   = Name.erase(0,Length);            //delete not valid prefix
   Pos0   = Name.find_last_of('\"');         //locate terminating '"'
   Name   = Name.erase(Pos0);                //delete not valid postfix

// @MRTZ_exclude restore_special_characters
// @MRTZ_beginBlock
   Name = replacePartString(Name,"°_°_°_BACKSLASH_°_°_°","\\");
   Name = replacePartString(Name,"°_°_°_QUOTATION_°_°_°","\"");
   Name = replacePartString(Name,"°_°_°_APOSTROPH_°_°_°","\'");
//@MRTZ_endBlock

#if defined(DEBUG_OUTPUT)
    cout << "Name : -|" << Name << "|-" << Pos0 << endl;
#endif //DEBUG_OUTPUT

   if( Name != "")
   {
    Grm.SymbolMap[className].insert(Name);
#if defined(DEBUG_OUTPUT)
     cout << "add " << Name << " to keyword-class : " << className << endl;
#endif //DEBUG_OUTPUT
   }
//@MRTZ_endBlock

   Iterator ++;                              //increment current index behind comma
   Pos0 = Iterator;                          //first-index of new name
   if(Iterator  <  (members.size()-1))
    Character = members.at(Iterator);       //read next character
  }
 }
}




/* @MRTZ_describe UserSymbolMap_clr

   @MRTZ_describe replace_special_characters

   @MRTZ_describe search_begin_of_name

   @MRTZ_describe search_end_of_name

   @MRTZ_describe delete_name

   @MRTZ_describe restore_special_characters

*/
void Prcs_Transformation::UserSymbolMap_clr(String_imp className,
                                            String_imp members)
{


#if defined(DEBUG_OUTPUT)
 cout << className << endl;
 cout << members << " : " << members.size() <<endl;
#endif //DEBUG_OUTPUT
 if(members != "")
 {
  if(  (className != String_imp(""))
     &&(members   != String_imp(""))
    )
  {
// @MRTZ_exclude replace_special_characters
// @MRTZ_beginBlock
   members = replacePartString(members,"\\\\","°_°_°_BACKSLASH_°_°_°");
   members = replacePartString(members,"\\\"","°_°_°_QUOTATION_°_°_°");
   members = replacePartString(members,"\\\'","°_°_°_APOSTROPH_°_°_°");
// @MRTZ_endBlock

   size_t     Iterator  = 0;
   while(Iterator  <  (members.size()-1)
        )                   //until begin of tag name found or end of given text
   {
#if defined(DEBUG_OUTPUT)
    cout << "members.at("<< Iterator <<") : " <<members.at(Iterator) << endl;
#endif //DEBUG_OUTPUT

// @MRTZ_exclude search_begin_of_name
// @MRTZ_beginBlock
    char Character = members.at(Iterator);        //read next character
    char ChrctrBfr = 0x00;                        //single character in given text
    while(  (  (Character != '"' )
             ||(ChrctrBfr == '\\' )
            )
          &&(Iterator  <  (members.size()-1))
         )                   //until begin of name found or end of given text
    {
     ChrctrBfr = members.at(Iterator);

     Iterator ++;                              //increment given character-index
#if defined(DEBUG_OUTPUT)
     printf("Getchar 1 starten \n");
#endif //DEBUG_OUTPUT
     Character = members.at(Iterator);        //read next character
#if defined(DEBUG_OUTPUT)
     printf("Getchar 1 fertig \n");
#endif //DEBUG_OUTPUT
#if defined(DEBUG_OUTPUT)
     cout << "members.at("<< Iterator <<") : " << Character << endl;
#endif //DEBUG_OUTPUT
    };
    size_t Pos0 = Iterator;
                  Iterator ++;                //increment given character-index
//@MRTZ_endBlock

// @MRTZ_exclude search_end_of_name
// @MRTZ_beginBlock
    Character = members.at(Iterator);         //read next character
    while(  (  (Character != '"' )
             ||(ChrctrBfr == '\\' )
            )
          &&(Iterator  <  (members.size()-1))
         )                   //until end of name found or end of given text
    {
     ChrctrBfr = members.at(Iterator);
     Iterator ++;                              //increment given character-index
     Character = members.at(Iterator);         //read next character
    };

    size_t Length = Iterator - Pos0 + 1;
    if(Iterator == (members.size()-1))        // no komma found but last character
     Length ++;
//@MRTZ_endBlock


// @MRTZ_exclude delete_name
// @MRTZ_beginBlock
    String_imp Name   = members.substr(Pos0, Length);    //find part of member-name
    Length = Name.find('\"') + 1;             //locate opening '"'
    Name   = Name.erase(0,Length);            //delete not valid prefix
    Pos0   = Name.find_last_of('\"');         //locate terminating '"'
    Name   = Name.erase(Pos0);                //delete not valid postfix

// @MRTZ_exclude restore_special_characters
// @MRTZ_beginBlock
    Name = replacePartString(Name,"°_°_°_BACKSLASH_°_°_°","\\");
    Name = replacePartString(Name,"°_°_°_QUOTATION_°_°_°","\"");
    Name = replacePartString(Name,"°_°_°_APOSTROPH_°_°_°","\'");
//@MRTZ_endBlock

#if defined(DEBUG_OUTPUT)
     cout << "Name : -|" << Name << "|-" << Pos0 << endl;
#endif //DEBUG_OUTPUT

    if( Name != "")
    {
     Grm.SymbolMap[className].erase(Name);
#if defined(DEBUG_OUTPUT)
      cout << "erase " << Name << " to keyword-class : " << className << endl;
#endif //DEBUG_OUTPUT
    }
//@MRTZ_endBlock

    Iterator ++;                              //increment current index behind comma
    Pos0 = Iterator;                          //first-index of new name
    if(Iterator  <  (members.size()-1))
     Character = members.at(Iterator);       //read next character
   }
  }
 }
 else
 {
  Grm.SymbolMap[className].clear();
#if defined(DEBUG_OUTPUT)
  cout << "erase to keyword-class : " << className << endl;
#endif //DEBUG_OUTPUT
 }
}




/* @MRTZ_describe UserRulePropertyGlobal_set

*/
void Prcs_Transformation::UserRulePropertyGlobal_set(TP_UserRuleProperty property,
                                              const  String_imp&         ruleName)
{
    switch(property)
    {
     case(URP_NOTPHRASED):
     {
      Grm.URPG.NotPhrased = stringToSet(ruleName);
#if defined(DEBUG_OUTPUT)
      cout << "add " << Name << " to property NotPhrased" << endl;
#endif //DEBUG_OUTPUT
     }break;
     case(URP_TOKEN):
     {
      Grm.URPG.Token = stringToSet(ruleName);
   #if defined(DEBUG_OUTPUT)
      cout << "add " << Name << " to property Token" << endl;
#endif //DEBUG_OUTPUT
     }break;
     case(URP_HIDE):
     {
      Grm.URPG.Hide = stringToSet(ruleName);
#if defined(DEBUG_OUTPUT)
      cout << "add " << Name << " to property Hide" << endl;
#endif //DEBUG_OUTPUT
     }break;
     case(URP_SKIPLEVEL):
     {
      Grm.URPG.SkipLevel = stringToSet(ruleName);
#if defined(DEBUG_OUTPUT)
      cout << "add " << Name << " to property SkipLevel" << endl;
#endif //DEBUG_OUTPUT
     }break;
     default:
     {
      cout << "unknown user-rule-property used" << endl;
     }break;
    }
}

/* @MRTZ_describe UserRulePropertyGlobal_clr

   @MRTZ_describe search_name

   @MRTZ_describe erase_name

   @MRTZ_describe erase_whole_property

*/
void Prcs_Transformation::UserRulePropertyGlobal_clr(TP_UserRuleProperty property,
                                                     String_imp          ruleName)
{

 if(ruleName != "")
 {
  char   Character = 0x00;               //single character in given text
  size_t Pos0      = 0;

  size_t Iterator  = 0;
  while(Iterator  <  (ruleName.size()-1)
       )                   //until begin of tag name found or end of given text
  {
// @MRTZ_exclude search_name
// @MRTZ_beginBlock
   while(  (Character != ',' )
         &&(Iterator  <  (ruleName.size()-1))
        )                   //until begin of tag name found or end of given text
   {
    Iterator ++;                              //increment given character-index
#if defined(DEBUG_OUTPUT)
    printf("Getchar 1 starten \n");
#endif //DEBUG_OUTPUT
    Character = ruleName.at(Iterator);        //read next character
#if defined(DEBUG_OUTPUT)
    printf("Getchar 1 fertig \n");
#endif //DEBUG_OUTPUT
   };
   size_t Length = Iterator - Pos0;
   if(Iterator == (ruleName.size()-1)) // no komma found but last character
    Length ++;

   String_imp Name = ruleName.substr(Pos0, Length);
              Name = replacePartString(Name," ",""); //delete space
              Name = replacePartString(Name,"\t","");//delete tab
              Name = replacePartString(Name,"\r","");//delete return
              Name = replacePartString(Name,"\n","");//delete newline
              Name = replacePartString(Name,",", "");//delete komma
// @MRTZ_endBlock

// @MRTZ_exclude erase_name
   if( Name != "")
    switch(property)
    {
     case(URP_NOTPHRASED):
     {
      Grm.URPG.NotPhrased.erase(Name);
#if defined(DEBUG_OUTPUT)
      cout << "erase " << Name << " from property NotPhrased" << endl;
#endif //DEBUG_OUTPUT
     }break;
     case(URP_TOKEN):
     {
      Grm.URPG.Token.erase(Name);
#if defined(DEBUG_OUTPUT)
      cout << "erase " << Name << " from property Token" << endl;
#endif //DEBUG_OUTPUT
     }break;
     case(URP_HIDE):
     {
      Grm.URPG.Hide.erase(Name);
#if defined(DEBUG_OUTPUT)
      cout << "erase " << Name << " from property Hide" << endl;
#endif //DEBUG_OUTPUT
     }break;
     case(URP_SKIPLEVEL):
     {
      Grm.URPG.SkipLevel.erase(Name);
#if defined(DEBUG_OUTPUT)
      cout << "erase " << Name << " from property SkipLevel" << endl;
#endif //DEBUG_OUTPUT
     }break;
     default:
     {
      cout << "unknown user-rule-property used" << endl;
     }break;
    }
    Iterator ++;                              //increment current index behind comma
    Pos0 = Iterator;                          //first-index of new name
    if(Iterator  <  (ruleName.size()-1))
     Character = ruleName.at(Iterator);       //read next character
  }
 }
 else
 {
// @MRTZ_exclude erase_whole_property
  switch(property)
  {
   case(URP_NOTPHRASED):
   {
    Grm.URPG.NotPhrased.clear();
#if defined(DEBUG_OUTPUT)
      cout << "erase property NotPhrased" << endl;
#endif //DEBUG_OUTPUT
   }break;
   case(URP_TOKEN):
   {
    Grm.URPG.Token.clear();
#if defined(DEBUG_OUTPUT)
      cout << "erase property Token" << endl;
#endif //DEBUG_OUTPUT
   }break;
   case(URP_HIDE):
   {
    Grm.URPG.Hide.clear();
#if defined(DEBUG_OUTPUT)
      cout << "erase property Hide" << endl;
#endif //DEBUG_OUTPUT
   }break;
   case(URP_SKIPLEVEL):
   {
    Grm.URPG.SkipLevel.clear();
#if defined(DEBUG_OUTPUT)
      cout << "erase property SkipLevel" << endl;
#endif //DEBUG_OUTPUT
   }break;
   default:
   {
    cout << "unknown user-rule-property used" << endl;
   }break;
  }
 }
}







/* @MRTZ_describe grammar_init


*/
void Prcs_Transformation::grammar_init(const char* grammar,
                                       const char* rootRule,
                                       const char* skipRule,
                                       const char* lineRule,
                                       const char* listOfNonPhrased,
                                       const char* grammarTextIdentifier,
                                       const char* logOutputFile,
                                       bool        debugMode,
                                       int         limitCallingTree,
                                       int         limitCallingNode,
                                       int         limitCallerTree,
                                       int         limitCallerNode)
{
 Spirit185_Internal InternalGrammar(grammar,&ContextModel);

 TiPa_Concrete::DataFellow* GrammarTree = InternalGrammar.treeData();
 if(GrammarTree != nullptr)
 {

  Spirit185_Filter Filter(&ContextModel);

  Filter.specialNodes_set(Spirit185_Filter::NodesAsLeaf,
                          "101,102,103,104,105,106,107,108,109,110,111,\
                           112,113,114,115,116,117,118,119,126,200,300,400,500");
  Filter.specialNodes_set(Spirit185_Filter::NodesToKeep,
                          "100,600,601,700,1000,1100,1101,1102");


  Grammar_Spirit185->setLogFile(logOutputFile);
  Grammar_Spirit185->init(GrammarTree,
                          rootRule,
                          skipRule,
                          lineRule,
                          listOfNonPhrased,
                          grammarTextIdentifier,
                          debugMode,
                          limitCallingTree,
                          limitCallingNode,
                          limitCallerTree,
                          limitCallerNode);


  ResultFilter.parserProperties_set(Grammar_Spirit185->getParserProperties());
  ResultFilter.specialNodes_set(Spirit185_Filter::NodesToSkip,10000);


  set<String_imp>::iterator String = Grm.URPG.Token.begin();
  while(String != Grm.URPG.Token.end())
  {
   ResultFilter.specialNode_search(Spirit185_Filter::NodesAsLeaf,String->c_str());
   ++String;
  }
  String = Grm.URPG.Hide.begin();
  while(String != Grm.URPG.Hide.end())
  {
   ResultFilter.specialNode_search(Spirit185_Filter::NodesToHide,String->c_str());
   ++String;
  }
  String = Grm.URPG.SkipLevel.begin();
  while(String != Grm.URPG.SkipLevel.end())
  {
   ResultFilter.specialNode_search(Spirit185_Filter::NodesToSkip,String->c_str());
   ++String;
  }

//  ResultStore.setSpcialTag(&Grm.SymbolMap["Keyword"],&Grm.SymbolMap["KeyChr"]);


  LOG_OUTPUT(LOG_ON,"......................  ...................");
 }
 else
 {
  LOG_OUTPUT(LOG_ON,"!!!!!!!!!!!!!!!!!!!!  !!!!!!!!!!!!!!!!!!!!");
 }
/**/
 Grammar_Spirit185->TDA_GrmConcrete::init();

 ContextModel.init();


}




/* @MRTZ_describe replaceTabs

*/
 String_imp Prcs_Transformation::replaceTabs(String_imp* text, int tabSize)
 {
  String_imp ReturnValue = "";

  char OldPart = '\t';
  if(text->find(OldPart) < text->size())
    //old part is not empty and not the same as the new part and part of the main-string
  {
   ReturnValue.reserve(text->size()*4);
   for(size_t Character = 0; Character < (text->size()); Character++)
   {
    if((*text)[Character] != OldPart)
    {
     ReturnValue.append(1,(*text)[Character]);
    }
    else
    {
     char NewPart = ' ';
     while((ReturnValue.size()%tabSize) != 0)
     {
      ReturnValue.append(1,NewPart);
     }
    }
   }
  }
  else
  {
   ReturnValue = (*text);
  }
  return(ReturnValue);
 }






/* @MRTZ_describe getTextSize


   @MRTZ_describe evaluate_line_changer

   @MRTZ_describe calculate_Height_and_Size

   @MRTZ_describe substract_line_end_character_after_last_line

*/
Prcs_Transformation::TP_TextSize Prcs_Transformation::getTextSize(const char* begin, const char* end)
{
 TP_TextSize   ReturnValue = {0,0};

 if(  (begin != nullptr)
    &&(end   != nullptr)
   )
 {
// @MRTZ_exclude evaluate_line_changer
// @MRTZ_beginBlock
  bool        Found_0A     = false;
  bool        Found_0D     = false;
  int         Counter_0A0D = 0;
  const char* Current      = begin;
  while( Current != end)
  {
   if((*Current) == 0x0A)
   {
    Found_0A = true;
    Counter_0A0D ++;
   }
   if((*Current) == 0x0D)
   {
    Found_0D = true;
    Counter_0A0D ++;
   }
   if(Counter_0A0D == 2)// 1 ms-windows or 2 linux or 2 macintosh line-changer found
    Current = end;
   else
    Current ++;
  }
// @MRTZ_endBlock


  char LineChanger     = 0x00;
  bool DoubleCharacter = false;
//@MRTZ_ifElseChain
  if   (  (Found_0A == true)
        &&(Found_0D == true)
       )//ms-windows text with more than one line
  {
   LineChanger     = 0x0A;
   DoubleCharacter = true;
 #if defined(DEBUG_OUTPUT)
   cout<< "Linechanger : ms-windows text with more than one line" <<endl;
 #endif //DEBUG_OUTPUT
  }
  else if(Found_0A == true)
        //linux text with more than one line
  {
   LineChanger     = 0x0A;
   DoubleCharacter = false;
 #if defined(DEBUG_OUTPUT)
   cout<< "Linechanger : linux text with more than one line" <<endl;
 #endif //DEBUG_OUTPUT
  }
  else if(Found_0D == true)
        //macintosh text with more than one line
  {
   LineChanger     = 0x0D;
   DoubleCharacter = false;
 #if defined(DEBUG_OUTPUT)
   cout<< "Linechanger : macintosh text with more than one line" <<endl;
 #endif //DEBUG_OUTPUT
  }
  else
        //linux text without more than one line-end character
  {
   LineChanger     = 0x00;
   DoubleCharacter = false;
 #if defined(DEBUG_OUTPUT)
   cout<< "Linechanger : linux text without more than one line-end character" <<endl;
 #endif //DEBUG_OUTPUT
  }

  size_t       Height          = 1;
  size_t       Width           = 0;
  if(LineChanger == 0x00)// only 1 line without line-changer
  {
   Height = 1;
   Width  = end - begin; //size of whole text
 // @MRTZ_skip
 //  Width  = Size;
  }
  else // line-changer found
  {
 // @MRTZ_exclude calculate_Height_and_Size
 // @MRTZ_beginBlock
   Current = begin;
   size_t Length = 0;
   while( Current < end)        // iteration over the text
   {
    Length ++;                  // measure number of character in current line
    if((*Current)==LineChanger) // end of current line
    {
     Height ++;                 // measure number of lines
     if(Width < (Length - 1))   // current line is the longest currently found
      Width = Length - 1;       // length without line-changer
     Length = 0;                // prepare next measurement
     if(DoubleCharacter == true)//step over second line-changer-character for ms-windows text
      Current ++;
    }
    Current ++;
   }
 // @MRTZ_exclude substract_line_end_character_after_last_line
   if(  ((*(Current-1))==0x0A)
      ||((*(Current-1))==0x0D)
     )//last line ends with line-end character
    Height -- ;
 // @MRTZ_endBlock
  }
   ReturnValue.Height = Height;
   ReturnValue.Width  = Width;

 }

 return(ReturnValue);
}


/* @MRTZ_describe getSymbols

*/
 set<String_imp>* Prcs_Transformation::getSymbols(String_imp key)
 {
  if(Grm.SymbolMap.find(key) != Grm.SymbolMap.end())
   return(&Grm.SymbolMap[key]);
  else
   return(nullptr);
 }



#ifndef DOXYGEN
//};};
#endif //DOXYGEN

