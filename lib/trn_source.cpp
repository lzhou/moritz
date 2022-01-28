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

 Documents produced by Moritz are derivative works derived from the
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
#include <ctime>

#define DEBUG_OUTPUT_LOG
#include "LogOutput.h"

#include "String_imp.h"

//#include "action.h"

#include "Spirit185_Filter.h"
#include "Spirit185_Store.h"


#include "trn_source.h"


#ifndef DOXYGEN
//namespace CL_PROCESS {
//namespace CL_TRANSFORM {
//namespace CL_TRN_SOURCE {
#endif //DOXYGEN

const String_imp  CONTENT = "Content";

/* @MRTZ_describe Prcs_Trn_Source

*/
Prcs_Trn_Source::Prcs_Trn_Source(void)
{
// Att.TxtPos           = NULL;
 Att.PositionOutput   = 0;
 Att.ShowTextToParse  = false;
 Att.ParseTolerant    = false;
}


/* @MRTZ_describe Prcs_Trn_Source

*/
Prcs_Trn_Source::Prcs_Trn_Source(int            positionOutput,
                                 bool           normlzKwrdsOfSource,
                                 bool           showTextToParse,
                                 bool           parseTolerant,
                                 int            startLine ,
                                 int            startColumn,
                           const String_imp&    tokenIndent,
                           const String_imp&    tokenDedent,
                           const String_imp&    tokenNewLine)
{
 Att.PositionOutput        = positionOutput;
 Att.NormlzKwrdsOfSource   = normlzKwrdsOfSource;
 Att.ShowTextToParse       = showTextToParse;
 Att.ParseTolerant         = parseTolerant;

 TextMakeup.StartLine      = startLine;
 TextMakeup.StartColumn    = startColumn;

 if(tokenIndent != "")
  Att.TokenIndent = tokenIndent + " ";
 else
  Att.TokenIndent = "";
 Att.SkipString.push_back(Att.TokenIndent);

 if(tokenDedent != "")
  Att.TokenDedent = tokenDedent + " ";
 else
  Att.TokenDedent = "";
 Att.SkipString.push_back(Att.TokenDedent);

 if(tokenNewLine != "")
  Att.TokenNewLine = tokenNewLine + " ";
 else
  Att.TokenNewLine = "";
 Att.SkipString.push_back(Att.TokenNewLine);

}


/* @MRTZ_describe ~Prcs_Trn_Source

*/
Prcs_Trn_Source::~Prcs_Trn_Source(void)
{

}



/* @MRTZ_describe analyse

   @MRTZ_describe local_declarations

   @MRTZ_describe evaluate_hits

   @MRTZ_describe copy_part_results

*/
TiPa_Concrete::DataFellow*  Prcs_Trn_Source::analyse(String_imp*     text,
                                                     TiPa_DataModel* model,
                                                     String_imp      rule)
{
// @MRTZ_exclude local_declarations
// @MRTZ_beginBlock
 TiPa_Concrete::DataFellow*  ReturnValue = nullptr;


 clock_t             Time            = 0;
 clock_t             InputDuration   = 0;
 clock_t             OutputDuration  = 0;
// @MRTZ_endBlock





 if (Att.NormlzKwrdsOfSource == true)
  _normalizeKeyWords(text);

 if(Att.ShowTextToParse == true)
  printf("\n\nText to parse:\n%s\n",text->c_str());


 Time = clock()/CLOCKS_PER_SEC;

 ContextModel.init();
 const char* EndOffResult = Grammar_Spirit185->parse(text->c_str(),text->c_str()+text->size(),rule.c_str());
//  cout <<  InputDuration << endl;

 TiPa_Concrete::DataFellow* GrammarTree = Grammar_Spirit185->treeData(nullptr,rule.c_str());
 InputDuration = (clock()/CLOCKS_PER_SEC)-Time;

 Time = clock()/CLOCKS_PER_SEC;

 if(  (GrammarTree  != nullptr)
    &&(EndOffResult != nullptr)
   )
 {

  ResultFilter.contextModel_set(model);

  GrammarTree->welcome(ResultFilter(Spirit185_Filter::KeepUndefined, model->focus_Fellow(),Spirit185_Filter::CloneData),IterateDownwards);

  model->focus_Fellow()->data_set(model->data_create(GrammarTree->data_get()));

  ReturnValue = model->focus_Fellow();
  TiPa_Data* ReturnData = ReturnValue->data_get();
//             ReturnData->userName_set((char*) ReturnData->secondaryData_add("UserName", "Content"));
             ReturnData->userName_set(CONTENT.c_str());
             ReturnData->lineSet(1);
             ReturnData->columnSet(1);


  LOG_OUTPUT(LOG_ON,"...................... Grammar Tree created ...................");
 }
 else
 {
  LOG_OUTPUT(LOG_ON,"!!!!!!!!!!!!!!!!!!!!No Grammar Tree created!!!!!!!!!!!!!!!!!!!!");
 }



 OutputDuration = (clock()/CLOCKS_PER_SEC)-Time;

 if((InputDuration>1)||(OutputDuration>1))
  cout <<"["<<InputDuration <<"|"<<OutputDuration<<"] -> ";


 Grammar_Spirit185->TDA_GrmConcrete::init();

 return(ReturnValue);
}







/* @MRTZ_describe _normalizeKeyWords

*/
void Prcs_Trn_Source::_normalizeKeyWords(String_imp* text)
{

 size_t Index   = 0;
 char*  Current = (char*)text->c_str();

 while(Index < text->size())
 {
  while(  (Index < text->size())
        &&(!(  ((*(Current+Index) >='a')&&(*(Current+Index)  <='z'))
             ||((*(Current+Index) >='A')&&(*(Current+Index)  <='Z'))
             ||((*(Current+Index) =='_')                         )
            )
          )
       )
  {
   Index++;
  }

  size_t Pos0 = Index;
  String_imp Word = "";

  while( (Index < text->size())
        &&(  ((*(Current+Index)  >='a')&&(*(Current+Index)  <='z'))
           ||((*(Current+Index)  >='A')&&(*(Current+Index)  <='Z'))
           ||((*(Current+Index)  >='0')&&(*(Current+Index)  <='1'))
           ||((*(Current+Index)  =='_')                         )
          )
       )
  {
   Word.append(1,*(Current+Index) );
   Index++;
  }

  String_imp LowWord = lowCaseString(Word);

  if(   (Word != LowWord)
      &&(   Grm.SymbolMap["Keyword"].find(LowWord)
         != Grm.SymbolMap["Keyword"].end()
        )
    )
  {
   size_t PosWord  = 0;
   while(Pos0 < Index)
   {
    *((char*)(text->c_str()+Pos0)) = LowWord[PosWord];
    Pos0 ++;
    PosWord ++;
   }
  }
 }

}



#ifndef DOXYGEN
//};};};
#endif //DOXYGEN


