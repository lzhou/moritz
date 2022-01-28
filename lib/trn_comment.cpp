/*!

 @file
 @brief    definition of an comment parser-process defined by the user

 This file contains the definition of a user parser-process to analyse the comments.

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
    28.08.2009     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    28.08.2009...  @I Eckard Klotz
 @I Changes are documented in the comment of the changed element
 @TabEnd

*/

#include "trn_comment.h"

//#include "TiXml_ao.h"

//#include "TiPa_Filter.h"
#include "Spirit185_Internal.h"
#include "Spirit185_Store.h"

#ifndef DOXYGEN
//namespace CL_PROCESS {
//namespace CL_TRANSFORM {
//namespace CL_TRN_COMMENT {
#endif //DOXYGEN




const String_imp  COMMAND = "__command__";
const String_imp  COMMENT = "Comment";



/* @MRTZ_describe Prcs_Trn_Comment

*/
Prcs_Trn_Comment::Prcs_Trn_Comment(map<String_imp, SpecialCommentToken > speclComntToken,
                                   int                                   startLine,
                                   int                                   startColumn,
                                   bool                                  showTextToParse)
{
  map<String_imp, SpecialCommentToken >::iterator ComntToken;

  TextMakeup.StartLine    = startLine;
  TextMakeup.StartColumn  = startColumn;
  Att.ShowTextToParse     = showTextToParse;

  ComntToken = speclComntToken.begin();
  while(ComntToken != speclComntToken.end())
  {
   if((ComntToken->first).find("Comment") == 0)
   {
    Att.NormlComntToken[(ComntToken->first)]= (ComntToken->second);
   }
   else
   {
    Att.SpeclComntToken[(ComntToken->first)]= (ComntToken->second);
   }
   ++ComntToken ;
  }


}

/* @MRTZ_describe ~Prcs_Trn_Comment

*/
Prcs_Trn_Comment::~Prcs_Trn_Comment()
{
 Att.SpeclComntToken.clear();
 Att.NormlComntToken.clear();
}



/* @MRTZ_describe analyse

*/
TiPa_Concrete::DataFellow*  Prcs_Trn_Comment::analyse(String_imp*     text,
                                                      TiPa_DataModel* model/*,
                                                      const String_imp& rule*/)
{
 TiPa_Concrete::DataFellow*  ReturnValue = nullptr;

 if(Att.ShowTextToParse == true)
  printf("\n\nText to parse for comments:\n%s\n",text->c_str());

 ContextModel.init();
 Grammar_Spirit185->pre_parse(text->c_str(),text->c_str()+text->size());
 Grammar_Spirit185->scan(text->c_str(),text->c_str()+text->size(),"pass");

 TiPa_Concrete::DataFellow* GrammarTree = Grammar_Spirit185->scanData("pass");
 if(GrammarTree != nullptr)
 {
  ResultFilter.contextModel_set(model);
  GrammarTree->welcome(ResultFilter(Spirit185_Filter::KeepUndefined, model->focus_Fellow(), Spirit185_Filter::CloneData),IterateDownwards);
                                            // reduce to level of intrest

#if defined(DEBUG_OUTPUT)
  Spirit185_Store  ResultStore;
  cout << __FILE__ << "|Prcs_Trn_Comment::analyse|" << __LINE__ << endl;
  char*           ParsedText = nullptr;    // xml-text
  model->focus_Fellow()->welcome(ResultStore(Spirit185_Store::Content2XML,&ParsedText),IterateDownwards);
  cout << ParsedText << endl;
  delete[]ParsedText;
#endif

  postAnalysis(model);
  ReturnValue = model->focus_Fellow();
  TiPa_Data* ReturnData = ReturnValue->data_get();
             ReturnData->userName_set("Content");
             ReturnData->lineSet(1);
             ReturnData->columnSet(1);

  LOG_OUTPUT(LOG_ON,"...................... Grammar Tree created ...................");
 }
 else
 {
  LOG_OUTPUT(LOG_ON,"!!!!!!!!!!!!!!!!!!!!No Grammar Tree created!!!!!!!!!!!!!!!!!!!!");
 }

 Grammar_Spirit185->TDA_GrmConcrete::init();
 ContextModel.init();

 return(ReturnValue);
}







/* @MRTZ_describe postAnalysis

*/
void  Prcs_Trn_Comment::postAnalysis(TiPa_DataModel* result)
{
 TiPa_Concrete::DataAssociation* Node   = result->focus_Fellow()->contractorFirst_get();

 while(Node   != nullptr)// parsing-result and document are OK
 {
  TiPa_Data*   Data = Node->data_get();    // a single parsing-data
  if(Data != nullptr)
  {
   TP_TextSize  Size = {0,0};

   const char* Kind = detectSpecialComment(Data->Begin);
   if(Kind != nullptr)
   {
    Data->userName_set((char*)Kind);                                                // replace tag name by the same with a capital letter at the begin
   }
   else
   {
    Data->userName_set("Comment") ;

    Size = getTextSize(Data->Begin, Data->End);
    Data->secondaryData_add("H",Size.Height);
    Data->secondaryData_add("W",Size.Width );

    Grammar_Spirit185->scan(Data->Begin, Data->End,"command");
    TiPa_Concrete::DataFellow* CommentTree = Grammar_Spirit185->scanData("command");

    if(CommentTree != nullptr)
    {
     TiPa_Concrete::DataFellow ReducedComment;                                   // filtered parsing-result
     Spirit185_Filter      CommandFilter(&ContextModel);
     CommandFilter.specialNodes_set(Spirit185_Filter::NodesToSkip,1000);         // skip all none rules
     CommentTree->welcome(CommandFilter(Spirit185_Filter::KeepUndefined, &ReducedComment),IterateDownwards);
                                                                                 // reduce to level of intrest
     const char* CommentBegin = Data->Begin;
     TiPa_Concrete::DataAssociation* ToDelete = Node;
     TiPa_Concrete::DataAssociation* CommentHit = ReducedComment.contractorFirst_get();
     while(CommentHit != nullptr)
     {
      TiPa_Data*   CommentData = CommentHit->data_get();                          // a single parsing-data
      if(CommentData->Begin !=  CommentBegin)
      {
       string NewContent = deleteNormalCommentTokens(string(CommentBegin,CommentData->Begin));
       if(NewContent != "")
       {
        TiPa_Data*       NewCommentData = result->data_create();
        DataAssociation* NewComment     = result->fellow_create(NewCommentData);
        NewCommentData->userName_set(COMMENT.c_str());

        int   Line    = 0;
        int   Column  = 0;
        Grammar_Spirit185->getPosition(&Line, &Column, CommentBegin);

        NewCommentData->lineSet(Line);
        NewCommentData->columnSet(Column);

        const char* CommentKind = detectSpecialComment(CommentBegin);
        if(CommentKind != nullptr)
         NewCommentData->userName_set(CommentKind);
        else
        {
         /*TP_TextSize*/  Size = getTextSize(CommentBegin,CommentData->Begin);
         NewCommentData->secondaryData_add("H", Size.Height);
         NewCommentData->secondaryData_add("W", Size.Width );
        }
        NewCommentData->Begin = NewCommentData->secondaryData_add("TextContent",NewContent.c_str());
        NewCommentData->End   = NewCommentData->Begin + strlen(NewContent.c_str());
        Node->sponsor_get()->contractorBehind_add(Node,NewComment);
        Node = NewComment;
       }
      }
      TiPa_Data*       NewCommandData = result->data_create();
      DataAssociation* NewCommand     = result->fellow_create(NewCommandData);
      NewCommandData->userName_set(COMMAND.c_str());

      int   Line    = 0;
      int   Column  = 0;
      Grammar_Spirit185->getPosition(&Line, &Column, CommentData->Begin);

      NewCommandData->lineSet(Line);
      NewCommandData->columnSet(Column);
      /*TP_TextSize*/  Size = getTextSize(CommentData->Begin,CommentData->End);
      NewCommandData->secondaryData_add("H", Size.Height);
      NewCommandData->secondaryData_add("W", Size.Width );
      TiPa_Concrete::DataAssociation* Detail = CommentHit->contractorFirst_get();
      if(Detail != nullptr)
      {
       Detail = Detail->contractorFirst_get();
       if(Detail != nullptr)
       {
        TiPa_Data* DetailData = Detail->data_get();    // a single parsing-data
        TiPa_Data*       NewLeafData = result->data_create();
        DataAssociation* NewLeaf     = result->fellow_create(NewLeafData);
        NewLeafData->userName_set( DetailData->userName_get());

        NewLeafData->lineSet(Line);
        NewLeafData->columnSet(Column);

        TiPa_Concrete::DataAssociation* Attribute = Detail->contractorFirst_get();
        while(Attribute != nullptr)
        {
         TiPa_Data* AttributeData = Attribute->data_get();    // a single parsing-data
         NewLeafData->secondaryData_add(AttributeData->userName_get(),
                                        string(AttributeData->Begin, AttributeData->End).c_str());
         Attribute = Attribute->fellowBehind_get(Detail);
        }
        NewCommand->contractorLast_add(NewLeaf);
       }
      }
      Node->sponsor_get()->contractorBehind_add(Node,NewCommand);
      Node = NewCommand ;
      CommentBegin = CommentData->End;
      while(  ((*CommentBegin) <= 32)
            &&(  CommentBegin  != Data->End)
           )
       ++CommentBegin;

      if(ToDelete != nullptr)
      {
       ToDelete = ToDelete->sponsor_get()->cutNode(ToDelete);
       ToDelete = nullptr;
      }
      CommentHit = CommentHit->fellowBehind_get(&ReducedComment);
     }
     if(  (CommentBegin > Data->Begin)
        &&(CommentBegin < Data->End)
       )
     {
      string NewContent = deleteNormalCommentTokens(string(CommentBegin,Data->End));
      if(NewContent != "")
      {
       TiPa_Data*       NewCommentData = result->data_create();
       DataAssociation* NewComment     = result->fellow_create(NewCommentData);
       NewCommentData->userName_set(COMMENT.c_str());
       const char* CommentKind = detectSpecialComment(CommentBegin);
       if(CommentKind != nullptr)
        NewCommentData->userName_set(CommentKind);
                                                // replace tag name by the same with a capital letter at the begin
       else
       {
       }

       int   Line    = 0;
       int   Column  = 0;
       Grammar_Spirit185->getPosition(&Line, &Column, CommentBegin);

       NewCommentData->lineSet(Line);
       NewCommentData->columnSet(Column);

       /*TP_TextSize*/  Size = getTextSize(CommentBegin, Data->End);
       NewCommentData->secondaryData_add("H", Size.Height);
       NewCommentData->secondaryData_add("W", Size.Width );
       NewCommentData->Begin = NewCommentData->secondaryData_add("TextContent",NewContent.c_str());
       NewCommentData->End   = NewCommentData->Begin + strlen(NewContent.c_str());
       Node->sponsor_get()->contractorBehind_add(Node,NewComment);
       Node = NewComment ;
      }
     }
    }
   }
  }
  Node = Node->fellowBehind_get(result->focus_Fellow());  // next parser-result
 }
}





/* @MRTZ_describe detectSpecialComment

*/
const char* Prcs_Trn_Comment::detectSpecialComment(const char* comment)
{
 const char* ReturnValue = nullptr;

 if(comment != nullptr)
 {
  map<String_imp, SpecialCommentToken >::iterator ComntToken;
  static map<String_imp, String_imp> StartToken;
  if(StartToken.begin()== StartToken.end())
  {
   ComntToken = Att.SpeclComntToken.begin();
   while(ComntToken != Att.SpeclComntToken.end())
   {
    StartToken[ComntToken->first] = (ComntToken->second).Start;
    ++ComntToken ;
   }
  }
  map<String_imp, String_imp>::iterator   Token = StartToken.begin();
  while(  (ReturnValue == nullptr)
        &&(Token != StartToken.end())
       )
  {
   if(strstr(comment,Token->second.c_str()) == comment)
   {
    ReturnValue = Token->first.c_str();
   }
   ++Token ;
  }

 }

 return(ReturnValue);

}






/* @MRTZ_describe detectSpecialComment

*/
String_imp Prcs_Trn_Comment::deleteNormalCommentTokens(String_imp text)
{
 map<String_imp, SpecialCommentToken >::iterator ComntToken;
 static list<String_imp > Replacement;
 if(Replacement.begin()== Replacement.end())
 {
  Replacement.push_back("\n");
  ComntToken = Att.NormlComntToken.begin();
  while(ComntToken != Att.NormlComntToken.end())
  {
   Replacement.push_back((ComntToken->second).Start);
   Replacement.push_back((ComntToken->second).End);
   ++ComntToken ;
  }
 }

 list<String_imp >::iterator   Token = Replacement.begin();
 while(Token != Replacement.end())
 {
  text = replacePartString(text,(*Token),"");
  ++Token  ;
 }

 while((text.size()>0)&&(text[0] <=32))
 {
  text.erase(0,1);
 }

 return(text);
}












#ifndef DOXYGEN
//};};};
#endif //DOXYGEN



