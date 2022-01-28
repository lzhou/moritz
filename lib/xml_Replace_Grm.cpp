/*!
 @file
 @brief grammar used to parse xml replacement-definitions used with configuration-files

 Copyright (C) 2019-2020 by Eckard Klotz.

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
    02.03.2019     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    02.03.2019...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/

#include "xml_Replace_Grm.h"

#include "TiPa_Concrete.h"
#include "TiPa_Combination.h"
#include "TiPa_Counter.h"
#include "TiPa_String.h"
#include "TiPa_Character.h"

#include "Spirit185_Filter.h"

//#define XML_DEBUG


/* @MRTZ_describe XML_Replace_Grm

*/
XML_Replace_Grm::XML_Replace_Grm(TiPa_Concrete::DataModel* contextModel)
#ifdef  XML_DEBUG
              :TDA_GrmConcrete(contextModel, true),
               ID(),
               DebugReaction()
#else //XML_DEBUG
              :TDA_GrmConcrete(contextModel, false),
               ID(),
               DebugReaction()
#endif //XML_DEBUG
{
// ID.Character   =    0;
// ID.String      =  300;
// ID.Counter     =  600;
// ID.Condition   = 1000;
// ID.Sequence    = 2000;
// ID.Rule        = 5000;

 defineRules_Name();
 defineRules_Path();
 defineRules_PathXML();
 defineRules_PathFile();
 defineRules_Data();
 defineRules_Search();
 defineRules_Replacement();
 defineRules_RawText();
 defineMainParser();

 skipNonRuleResults();

 GET_PARSER(TiPa_Rule,        MainParser);

 TDA_GrmConcrete::Att.MainParser = MainParser;
 TDA_GrmConcrete::Att.SkipParser = nullptr;
 TDA_GrmConcrete::Att.LineParser = nullptr;

 DebugReaction.setProperty(&TDA_GrmConcrete::Att.Property);
}


/* @MRTZ_describe XML_Replace_Grm

*/
XML_Replace_Grm::XML_Replace_Grm(void)
#ifdef  XML_DEBUG
              :TDA_GrmConcrete(nullptr, true),
               ID(),
               DebugReaction()
#else //XML_DEBUG
              :TDA_GrmConcrete(nullptr, false),
               ID(),
               DebugReaction()
#endif //XML_DEBUG
{
// ID.Character   =    0;
// ID.String      =  300;
// ID.Counter     =  600;
// ID.Condition   = 1000;
// ID.Sequence    = 2000;
// ID.Rule        = 5000;

 defineRules_Name();
 defineRules_Path();
 defineRules_PathXML();
 defineRules_PathFile();
 defineRules_Data();
 defineRules_Search();
 defineRules_Replacement();
 defineRules_RawText();
 defineMainParser();
 skipNonRuleResults();

 GET_PARSER(TiPa_Rule,        MainParser);

 TDA_GrmConcrete::Att.MainParser = MainParser;
 TDA_GrmConcrete::Att.SkipParser = nullptr;
 TDA_GrmConcrete::Att.LineParser = nullptr;

 DebugReaction.setProperty(&TDA_GrmConcrete::Att.Property);
}





/* @MRTZ_describe ~XML_Replace_Grm

*/
XML_Replace_Grm::~XML_Replace_Grm(void)
{

}





/* @MRTZ_describe parse

*/
const char * XML_Replace_Grm::parse(const char* begin, const char* end, const char* rule)
{
 return(TDA_GrmConcrete::parse(begin, end, rule));  // call the main parsing process and return its result
}





/* @MRTZ_describe scan

*/
const char * XML_Replace_Grm::scan(const char* begin, const char* end, const char* rule)
{
 return(TDA_GrmConcrete::scan(begin, end, rule));   // call the main parsing process and return its result
}







/* @MRTZ_describe filter_simple

*/
TiPa_Concrete::DataFellow* XML_Replace_Grm::filter_simple(TiPa_Concrete::DataFellow* node)
{
 TiPa_Concrete::DataFellow* ReturnValue = Att.ContextModel->fellow_create();

 Spirit185_Filter Filter(Att.ContextModel);
                  Filter.specialNodes_set(Spirit185_Filter::NodesToKeep,4999);

 node->welcome(Filter(Spirit185_Filter::SkipUndefined, ReturnValue),IterateDownwards);
 ReturnValue->data_set(Att.ContextModel->data_create(node->data_get()));

 return(ReturnValue);
}






#define INCED_ID(id) ++(id)



/*  @MRTZ_describe defineRules_Name
    name =  (     ( range_p('a','z') | range_p('A','Z')                      | '_' )
             >>  *( range_p('a','z') | range_p('A','Z') |  range_p('0','9')  | '_' )
            );
*/
void XML_Replace_Grm::defineRules_Name(void)
{
 CREATE_CHARACTER_PARSER( NameStartChar,   INCED_ID(ID.Character), "start of a name");
 CREATE_CHARACTER_PARSER( NameChar,        INCED_ID(ID.Character), "continue of a name");

 CREATE_COUNTER_PARSER(   NameBody,        INCED_ID(ID.Counter),   "continue of a name");
 CREATE_SEQUENCE_PARSER(  Name_seq,        INCED_ID(ID.Sequence),  "name (parser)");

 CREATE_RULE_PARSER(      Name,            INCED_ID(ID.Rule),      "identifying name ");



 NameStartChar->init('_')->include('a','z')->include('A','Z');
 NameChar->init('_')->include('a','z')->include('A','Z')->include('0','9');

 NameBody->zeroOrMore(NameChar);

 Name_seq->hard(NameStartChar, NameBody);

 Name->init(Name_seq);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  Name->reactionHit_set(&DebugReaction);

}



/*   @MRTZ_describe defineRules_Path

    path = +((up | here | name) >> "/");
    up   = ".." ;
    here = ".";

*/
void XML_Replace_Grm::defineRules_Path(void)
{
 CREATE_CHARACTER_PARSER( Separator, INCED_ID(ID.Character), "path-level separator");

 CREATE_STRING_PARSER( Up_Str,       INCED_ID(ID.String),    "jump one path-level up");
 CREATE_RULE_PARSER(   Up,           INCED_ID(ID.Rule),      "path-string");

 CREATE_STRING_PARSER( Here_Str,     INCED_ID(ID.String),    "current path-level");
 CREATE_RULE_PARSER(  Here,          INCED_ID(ID.Rule),      "path-string");

 CREATE_CONDITION_PARSER( Level,     INCED_ID(ID.Condition),  "level name in path");

 CREATE_SEQUENCE_PARSER( Level_seq,  INCED_ID(ID.Sequence),   "level-name and separator");
 CREATE_COUNTER_PARSER(  Path_cnt,   INCED_ID(ID.Counter),    "sequence of path-parts");

 CREATE_RULE_PARSER(     Path,       INCED_ID(ID.Rule),       "path-string");


 GET_PARSER(TiPa_Rule, Name);

 Separator->init('/');

 Up_Str->init("..");
 Up->init(Up_Str);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  Up->reactionHit_set(&DebugReaction);

 Here_Str->init(".");
 Here->init(Here_Str);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  Here->reactionHit_set(&DebugReaction);

 Level->incOr(Up,Here)->incOr(Name);
 Level_seq->hard(Level,Separator);

 Path_cnt->init(TiPa_Counter::Cnt_OneOrMore,Level_seq);

 Path->init(Path_cnt);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  Path->reactionHit_set(&DebugReaction);
}



/*  @MRTZ_describe defineRules_PathXML

    xmlPath = !"%/" >> !path >> node;
    node    = name
*/
void XML_Replace_Grm::defineRules_PathXML(void)
{
 CREATE_STRING_PARSER(  Root_Begin,    INCED_ID(ID.String),    "string of xml-root token");
 CREATE_SEQUENCE_PARSER(Root_seq,      INCED_ID(ID.Sequence),  "complete root-node token");
 CREATE_COUNTER_PARSER( Separator_cnt, INCED_ID(ID.Counter),   "optional separator");

 CREATE_RULE_PARSER(   Root,           INCED_ID(ID.Rule),      "rule of xml-root token");

 CREATE_COUNTER_PARSER( Root_cnt,      INCED_ID(ID.Counter),   "optional xml-root token");
 CREATE_COUNTER_PARSER( PathXML_cnt,   INCED_ID(ID.Counter),   "optional xml-path");

 CREATE_RULE_PARSER(   Node,           INCED_ID(ID.Rule),      "rule of xml-node");

 CREATE_SEQUENCE_PARSER( PathXML_seq,  INCED_ID(ID.Sequence),  "complete xml-path");
 CREATE_CONDITION_PARSER(PathXML_con,  INCED_ID(ID.Condition), "xml-path options");
 CREATE_RULE_PARSER(   PathXML,        INCED_ID(ID.Rule),      "rule of complete xml-path");

 GET_PARSER(TiPa_Character, Separator);
 GET_PARSER(TiPa_Sequence, Name_seq);
 GET_PARSER(TiPa_Rule, Name);
 GET_PARSER(TiPa_Rule, Path);


 Root_Begin->init("%");
 Separator_cnt->init(TiPa_Counter::Cnt_OptionOne,Separator);
 Root_seq->hard(Root_Begin,Name)->hard(Separator_cnt);
 Root->init(Root_seq);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  Root->reactionHit_set(&DebugReaction);

 Root_cnt->init(TiPa_Counter::Cnt_OptionOne,Root);

 PathXML_cnt->init(TiPa_Counter::Cnt_OptionOne,Path);

 Node->init(Name_seq);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  Node->reactionHit_set(&DebugReaction);

 PathXML_seq->hard(Root_cnt,PathXML_cnt)->hard(Node);
 PathXML_con->incOr(PathXML_seq,Root);
 PathXML->init(PathXML_con);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  PathXML->reactionHit_set(&DebugReaction);
}



/*  @MRTZ_describe defineRules_PathFile
    filePath = !volume >> !path >> file;

    volume    = character >> ":/" ;
    character = range_p('a','z') | range_p('A','Z');

    file      = name >> "." >> name;
*/
void XML_Replace_Grm::defineRules_PathFile(void)
{
 CREATE_CHARACTER_PARSER( Volume_Chr,    INCED_ID(ID.Character), "character of hard-disc volume");
 CREATE_STRING_PARSER( Volume_Str,       INCED_ID(ID.String),    "string of hard-disc volume");
 CREATE_SEQUENCE_PARSER(   Volume_seq,   INCED_ID(ID.Sequence),  "sequence of hard-disc volume");
 CREATE_RULE_PARSER(   Volume,           INCED_ID(ID.Rule),      "rule of hard-disc volume");
 CREATE_COUNTER_PARSER( Volume_cnt,      INCED_ID(ID.Counter),   "optional hard-disc volume");

 CREATE_COUNTER_PARSER( PathFile_cnt,    INCED_ID(ID.Counter),   "optional file-path");


 CREATE_CHARACTER_PARSER( File_Chr,      INCED_ID(ID.Character), "separator between fine-name and attachment");
 CREATE_SEQUENCE_PARSER(  File_seq,      INCED_ID(ID.Sequence),  "sequence of file-name");
 CREATE_RULE_PARSER(      File,          INCED_ID(ID.Rule),      "rule of file-name");

 CREATE_SEQUENCE_PARSER( PathFile_seq,   INCED_ID(ID.Sequence),  "sequence of file-path");
 CREATE_RULE_PARSER(     PathFile,       INCED_ID(ID.Rule),      "rule of file-path");


 GET_PARSER(TiPa_Rule, Path);
 GET_PARSER(TiPa_Rule, Name);



 Volume_Chr->init('a','z')->include('A','Z');
 Volume_Str->init(":/");
 Volume_seq->hard(Volume_Chr,Volume_Str);

 Volume->init(Volume_seq);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  Volume->reactionHit_set(&DebugReaction);
 Volume_cnt->init(TiPa_Counter::Cnt_OptionOne,Volume);

 PathFile_cnt->init(TiPa_Counter::Cnt_OptionOne,Path);

 File_Chr->init('.');
 File_seq->hard(Name,File_Chr)->hard(Name);
 File->init(File_seq);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  File->reactionHit_set(&DebugReaction);

 PathFile_seq->hard(Volume_cnt,PathFile_cnt)->hard(File);
 PathFile->init(PathFile_seq);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  PathFile->reactionHit_set(&DebugReaction);
}



/*  @MRTZ_describe defineRules_Data
    data      = "!(" >> (attribute | text ) >> ")";
    attribute = "{" >> name >> "}" ;
    text      = "{" >> "-TEXT-" >> "}" ;
*/
void XML_Replace_Grm::defineRules_Data(void)
{
 CREATE_STRING_PARSER( Info_Start,       INCED_ID(ID.String),    "start of info");
 CREATE_STRING_PARSER( Info_End,         INCED_ID(ID.String),    "end of Info");

 CREATE_STRING_PARSER( Text_str,         INCED_ID(ID.String),    "symbol for text");

 CREATE_SEQUENCE_PARSER( Attribute_seq,  INCED_ID(ID.Sequence),  "sequence of attribute definition");
 CREATE_RULE_PARSER(     Attribute,      INCED_ID(ID.Rule),      "rule of attribute definition");

 CREATE_SEQUENCE_PARSER( Text_seq,       INCED_ID(ID.Sequence),  "sequence of text-definition");
 CREATE_RULE_PARSER(     Text,           INCED_ID(ID.Rule),      "rule of text-definition");

 CREATE_STRING_PARSER( Data_Start,       INCED_ID(ID.String),    "start of data");
 CREATE_STRING_PARSER( Data_End,         INCED_ID(ID.String),    "end of data");
 CREATE_CONDITION_PARSER( Data_con,      INCED_ID(ID.Condition), "condition of data");
 CREATE_SEQUENCE_PARSER( Data_seq,       INCED_ID(ID.Sequence),  "sequence of data");
 CREATE_RULE_PARSER(     Data,           INCED_ID(ID.Rule),      "rule of data");


 GET_PARSER(TiPa_Rule, Name);


 Info_Start->init("{");
 Info_End->init("}");

 Text_str->init("-TEXT-");


 Attribute_seq->hard(Info_Start,Name)->hard(Info_End);
 Attribute->init(Attribute_seq);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  Attribute->reactionHit_set(&DebugReaction);

 Text_seq->hard(Info_Start,Text_str)->hard(Info_End),
 Text->init(Text_seq);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  Text->reactionHit_set(&DebugReaction);

 Data_Start->init("!(");
 Data_End->init(")");
 Data_con->incOr(Attribute,Text);
 Data_seq->hard(Data_Start,Data_con)->hard(Data_End);
 Data->init(Data_seq);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  Data->reactionHit_set(&DebugReaction);

}



/*  @MRTZ_describe defineRules_Search
    search  = "?(" >> location >> ")";

    location = !filePath >> "#" >> xmlPath ;
*/
void XML_Replace_Grm::defineRules_Search(void)
{

 CREATE_COUNTER_PARSER( PathFile_opt,      INCED_ID(ID.Counter),   "optional file-path");
 CREATE_CHARACTER_PARSER( Location_Chr,    INCED_ID(ID.Character), "separator between fine-path and xml-path");
 CREATE_SEQUENCE_PARSER( Location_seq,     INCED_ID(ID.Sequence),  "sequence of location");
 CREATE_RULE_PARSER(     Location,         INCED_ID(ID.Rule),      "rule of location");

 CREATE_STRING_PARSER( Search_Start,       INCED_ID(ID.String),    "start of search");
 CREATE_STRING_PARSER( Search_End,         INCED_ID(ID.String),    "end of search");
 CREATE_SEQUENCE_PARSER( Search_seq,       INCED_ID(ID.Sequence),  "sequence of search");
 CREATE_RULE_PARSER(     Search,           INCED_ID(ID.Rule),      "rule of search");


 GET_PARSER(TiPa_Rule, PathFile);
 GET_PARSER(TiPa_Rule, PathXML);


 PathFile_opt->init(TiPa_Counter::Cnt_OptionOne,PathFile);
 Location_Chr->init('#');
 Location_seq->hard(PathFile_opt,Location_Chr)->hard(PathXML);
 Location->init(Location_seq);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  Location->reactionHit_set(&DebugReaction);

 Search_Start->init("?(");
 Search_End->init(")");
 Search_seq->hard(Search_Start,Location)->hard(Search_End);
 Search->init(Search_seq);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  Search->reactionHit_set(&DebugReaction);
}




/*  @MRTZ_describe defineRules_Replacement
    replacement = "[" >> search >> data >> "]";

*/
void XML_Replace_Grm::defineRules_Replacement(void)
{
 CREATE_STRING_PARSER( Replacement_Start,       INCED_ID(ID.String),    "start of replacement");
 CREATE_STRING_PARSER( Replacement_End,         INCED_ID(ID.String),    "end of replacement");

 CREATE_SEQUENCE_PARSER( Replacement_seq,       INCED_ID(ID.Sequence),  "sequence of replacement");
 CREATE_RULE_PARSER(     Replacement,           INCED_ID(ID.Rule),      "rule of replacement");

 GET_PARSER(TiPa_Rule, Search);
 GET_PARSER(TiPa_Rule, Data);

 Replacement_Start->init("[");
 Replacement_End->init("]");

 Replacement_seq->hard(Replacement_Start,Search)->hard(Data)->hard(Replacement_End);
 Replacement->init(Replacement_seq);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  Replacement->reactionHit_set(&DebugReaction);
}





/*  @MRTZ_describe defineRules_RawText

*/
void XML_Replace_Grm::defineRules_RawText(void)
{
 CREATE_CHARACTER_PARSER( RawChar,        INCED_ID(ID.Character),    "raw character");

 CREATE_CONDITION_PARSER( Raw_Exclude,    INCED_ID(ID.Condition),    "non raw-character exception");
 CREATE_COUNTER_PARSER(   RawBody,        INCED_ID(ID.Counter),      "raw-text sequence");

 CREATE_RULE_PARSER(      RawText,        INCED_ID(ID.Rule),         "raw-text rule ");

 GET_PARSER(TiPa_Rule, Replacement);


 RawChar->init(TiPa_Character::Anychar);

 Raw_Exclude->init(TiPa_Condition::Cnd_WthOt,RawChar,Replacement);

 RawBody->oneOrMore(Raw_Exclude);

 RawText->init(RawBody);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  RawText->reactionHit_set(&DebugReaction);

}

/*  @MRTZ_describe defineMainParser

*/
void XML_Replace_Grm::defineMainParser(void)
{
 CREATE_CONDITION_PARSER( MainAlternative,    INCED_ID(ID.Condition),    "main-parser details");
 CREATE_COUNTER_PARSER(   MainBody,           INCED_ID(ID.Counter),      "main sequence");

 CREATE_RULE_PARSER(      MainParser,         INCED_ID(ID.Rule),         "main-parser rule ");

 GET_PARSER(TiPa_Rule, Replacement);
 GET_PARSER(TiPa_Rule, RawText);

 MainAlternative->init(TiPa_Condition::Cnd_OrExc,RawText,Replacement);
 MainBody->oneOrMore(MainAlternative);

 MainParser->init(MainBody);
 if(TDA_GrmConcrete::Att.DebugMode == true)
  MainParser->reactionHit_set(&DebugReaction);

}


















/*  @MRTZ_describe skipNonRuleResults

*/
void XML_Replace_Grm::skipNonRuleResults(void)
{
  map<string,TiPa_Character*>::iterator CurrentCharacter = Att.ParserCharacter.begin();
  while(CurrentCharacter != Att.ParserCharacter.end())
  {
   CurrentCharacter->second->resultStorage_Set(TiPa_Concrete::ResStore_Skip);
   ++ CurrentCharacter;
  }

  map<string,TiPa_String*>::iterator CurrentString = Att.ParserString.begin();
  while(CurrentString != Att.ParserString.end())
  {
   CurrentString->second->resultStorage_Set(TiPa_Concrete::ResStore_Skip);
   ++ CurrentString;
  }

//  map<string,TiPa_Counter*>::iterator CurrentCounter = Att.ParserCounter.begin();
//  while(CurrentCounter != Att.ParserCounter.end())
//  {
//   CurrentCounter->second->resultStorage_Set(TiPa_Concrete::ResStore_Skip);
//   ++ CurrentCounter;
//  }
//
//  map<string,TiPa_Sequence*>::iterator CurrentSequence = Att.ParserSequence.begin();
//  while(CurrentSequence != Att.ParserSequence.end())
//  {
//   CurrentSequence->second->resultStorage_Set(TiPa_Concrete::ResStore_Skip);
//   ++ CurrentSequence;
//  }
//
//  map<string,TiPa_Condition*>::iterator CurrentCondition = Att.ParserCondition.begin();
//  while(CurrentCondition != Att.ParserCondition.end())
//  {
//   CurrentCondition->second->resultStorage_Set(TiPa_Concrete::ResStore_Skip);
//   ++ CurrentCondition;
//  }

}

