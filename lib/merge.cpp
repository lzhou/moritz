/*!

 @file
 @brief  definition of backus-naur-form

 This file contains the definition of a container that stores
 the result of a parser.

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
    08.02.2009     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    08.02.2009...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/

#include <limits.h>
#include <stdlib.h>
#include "merge.h"
#include "TiPa_Search.h"


#include "Spirit185_Store.h"



#ifndef DOXYGEN
//namespace CL_PROCESS {
//namespace CL_TRN_MERGE {
#endif //DOXYGEN
//#define DEBUG_OUTPUT

/* @MRTZ_describe Prcs_Trn_Merge

*/
Prcs_Trn_Merge::Prcs_Trn_Merge()
{
  Att.Comment.Use                 = true;
  Att.Comment.LimitToImportBehind = -1;
  Att.Comment.LimitToImportBefore = -1;
  Att.Line.Use                    = true;
  Att.Line.LimitToImportBehind    = -1;
  Att.Line.LimitToImportBefore    = -1;
}



/* @MRTZ_describe Prcs_Trn_Merge

*/
Prcs_Trn_Merge::Prcs_Trn_Merge(
            bool            useComment,
            int             limitToImportBeforeComment,
            int             limitToImportBehindComment,
            String_imp&     importLevelComment,
            bool            useLine,
            int             limitToImportBeforeLine,
            int             limitToImportBehindLine,
            String_imp&     importLevelLine,

            bool            useCommand,
            int             limitToImportBeforeCommand,
            int             limitToImportBehindCommand,
            map<String_imp,String_imp>  importLevelCommand)
{

 map<String_imp,String_imp>::iterator LevelCommand;

 Att.Comment.Use                 = useComment;
 Att.Comment.LimitToImportBefore = limitToImportBeforeComment;
 Att.Comment.LimitToImportBehind = limitToImportBehindComment;
 Att.Comment.ImportLevel["Cmnt"] = stringToSet(importLevelComment);
 Att.Line.Use                    = useLine;
 Att.Line.LimitToImportBefore    = limitToImportBeforeLine;
 Att.Line.LimitToImportBehind    = limitToImportBehindLine;
 Att.Line.ImportLevel["Line"]    = stringToSet(importLevelLine);

 Att.Command.Use                 = useCommand;
 Att.Command.LimitToImportBefore = limitToImportBeforeCommand;
 Att.Command.LimitToImportBehind = limitToImportBehindCommand;


 LevelCommand = importLevelCommand.begin();
 while( LevelCommand != importLevelCommand.end())
 {
  Att.Command.ImportLevel[LevelCommand->first]
            = stringToSet(LevelCommand->second);
  ++LevelCommand ;
 }

}




/* @MRTZ_describe ~Prcs_Trn_Merge

*/
Prcs_Trn_Merge::~Prcs_Trn_Merge()
{
}







/* @MRTZ_describe merge

   @MRTZ_describe assemble_comments

   @MRTZ_describe assemble_line_ends

*/
void Prcs_Trn_Merge::merge(TiPa_DataModel* dataModel,
                           const char*     code,
                           const char*     line,
                           const char*     comment)
{
 int CommentLimImpBef_Def = Att.Comment.LimitToImportBefore;
 int CommentLimImpBeH_Def = Att.Comment.LimitToImportBehind;

 if(  (Att.Comment.Use == true)
    &&(code            != nullptr)
    &&(comment         != nullptr)
   )
 {
// @MRTZ_exclude assemble_comments
// @MRTZ_beginBlock
  dataModel->focus_Set(comment);
  TiPa_Concrete::DataAssociation* ImportRoot = dataModel->focus_Fellow();
  if(ImportRoot != nullptr)
  {
   TiPa_Concrete::DataAssociation* Import = ImportRoot->contractorFirst_get();
   while(Import != nullptr)
   {
    TiPa_Concrete::DataAssociation* NextChild = Import->fellowBehind_get();

    Import = ImportRoot->contractorFirst_cut();
    TiPa_Data* ImportData = Import->data_get();
 // @MRTZ_ifElseChain


    if(String_imp(ImportData->userName_get()) == COMMENT)
    {
     dataModel->focus_Set(code);
     if(dataModel->focus_Fellow()->contractorFirst_get() == nullptr)
      dataModel->focus_Fellow()->contractorLast_add(Import);
     else
      _assemble(dataModel->focus_Fellow(), Import,
                Att.Comment.LimitToImportBefore,
                Att.Comment.LimitToImportBehind,
                &(Att.Comment.ImportLevel.begin()->second));
    }
    else if(String_imp(ImportData->userName_get()) == COMMAND)
    {

     NextChild =_assembleCommentsToCommands(Import, NextChild, dataModel);
     TiPa_Concrete::DataAssociation* SubImport = Import->contractorFirst_get();
     if(SubImport != nullptr)
     {
      TiPa_Data* SubImportData = SubImport->data_get();
      String_imp Command = String_imp(SubImportData->userName_get());
      if(Att.Command.ImportLevel.find(Command)!=Att.Command.ImportLevel.end())
      {
       if((Command == "mrtz_commentModel")) // user redefines the location of the comment relative to the commented part
       {
        String_imp  ModelCommentAttribute  = "";

        const char*  Text = SubImportData->secondaryData_get("modelComment",nullptr);
        if(Text != nullptr)
         ModelCommentAttribute  =  String_imp(Text);
        else
         ModelCommentAttribute  =  "";

        if(ModelCommentAttribute == "CommentBehind")
        {
         Att.Comment.LimitToImportBefore = CommentLimImpBef_Def;
         Att.Comment.LimitToImportBehind = CommentLimImpBeH_Def;
        }
        else if(ModelCommentAttribute == "CommentBefore")
        {
         Att.Comment.LimitToImportBefore = INT_MAX;
         Att.Comment.LimitToImportBehind = 0;
        }
        else if(ModelCommentAttribute == "CommentDefault")
        {
         Att.Comment.LimitToImportBefore = 0;
         Att.Comment.LimitToImportBehind = INT_MAX;
        }
        else
        {
        }
       }
       else //normal moritz command
       {
        // nothing to do
       }
       dataModel->focus_Set(code);
       if(dataModel->focus_Fellow()->contractorFirst_get() == nullptr)
        dataModel->focus_Fellow()->contractorLast_add(Import);
       else
        _assemble(dataModel->focus_Fellow(), Import,
                  Att.Command.LimitToImportBefore,
                  Att.Command.LimitToImportBehind,
                  &(Att.Command.ImportLevel[Command]));
      }
     }
    }
    else
    {
     dataModel->focus_Set(code);
     if(dataModel->focus_Fellow()->contractorFirst_get() == nullptr)
      dataModel->focus_Fellow()->contractorLast_add(Import);
     else
      _assemble(dataModel->focus_Fellow(), Import,
                Att.Command.LimitToImportBefore,
                Att.Command.LimitToImportBehind,
                &(Att.Command.ImportLevel["mrtz_independent"]));
    }
    Import = NextChild;
   }

  }
// @MRTZ_endBlock
 }


 if(  (Att.Line.Use == true)
    &&(code     != nullptr)
    &&(line     != nullptr)
   )
 {
// @MRTZ_exclude assemble_line_ends
// @MRTZ_beginBlock
  dataModel->focus_Set(line);
  TiPa_Concrete::DataAssociation* ImportRoot = dataModel->focus_Fellow();
  if(ImportRoot != nullptr)
  {
   TiPa_Concrete::DataAssociation* Import = ImportRoot->contractorFirst_get();
   while(Import != nullptr)
   {
    TiPa_Concrete::DataAssociation* NextChild = Import->fellowBehind_get();
    Import = ImportRoot->contractorFirst_cut();

    dataModel->focus_Set(code);
    if(dataModel->focus_Fellow()->contractorFirst_get() == nullptr)
     dataModel->focus_Fellow()->contractorLast_add(Import);
    else
     _assemble(dataModel->focus_Fellow(), Import,
               Att.Line.LimitToImportBefore,
               Att.Line.LimitToImportBehind,
               &(Att.Line.ImportLevel.begin()->second));
    Import = NextChild;
   }
  }
// @MRTZ_endBlock
 }
  dataModel->focus_Set(code);
  if(dataModel->focus_Fellow()->contractorFirst_get() != nullptr)
   _moveCodePart(dataModel->focus_Fellow(), dataModel);

 Att.Comment.LimitToImportBefore = CommentLimImpBef_Def;
 Att.Comment.LimitToImportBehind = CommentLimImpBeH_Def;
}














/* @MRTZ_describe _assemble

*/
TiPa_Concrete::DataAssociation* Prcs_Trn_Merge::_assemble(TiPa_Concrete::DataAssociation* destination,
                                                          TiPa_Concrete::DataAssociation* import,
                                                          int                             limitToImportBehind,
                                                          int                             limitToImportBefore,
                                                          set<String_imp>*                importLevel)
{
 TiPa_Concrete::DataAssociation* ChildBefore      = _searchLastLeafChild(destination);
 TiPa_Concrete::DataAssociation* DestChild        = destination->fellowBehind_get();
 TiPa_Concrete::DataAssociation* ChildBehind      = nullptr;

 if(DestChild != nullptr)
 {
  ChildBehind = _searchFirstLeafChild(DestChild);//->ToElement();
 }
 else
 {
 }

// @MRTZ_ifElseChain
 if  (_compare(import, destination) == 0)
 {
  import = _assembleDownwards(destination,         import,
                              limitToImportBehind, limitToImportBefore,
                              importLevel);
 }
 else if(_compare(import, destination) < 0)
 {
  import = _assembleBefore(destination, import, importLevel);
 }
 else if(  (ChildBehind!= nullptr)
         &&(  (_compare(import, destination) > 0)
            &&(_compare(import, ChildBehind) < 0)
           )
        )
 {
  TiPa_Data* ChildBeforeData = ChildBefore->data_get();
  int        LineBefore      = stringToNumber(ChildBeforeData->lineGet());

  if(ChildBeforeData->secondaryData_get("H",nullptr) != nullptr)
   LineBefore   =  LineBefore
                 + stringToNumber(ChildBeforeData->secondaryData_get("H",nullptr))-1;

  TiPa_Data* ImportData = import->data_get();

  int LineImportBegin = stringToNumber(ImportData->lineGet());
  int LineImportEnd   = LineImportBegin;

  if(ImportData->secondaryData_get("H",nullptr) != nullptr)
   LineImportEnd   =  LineImportEnd
                     + stringToNumber(ImportData->secondaryData_get("H",nullptr))-1;

  TiPa_Data* ChildBehindData  = ChildBehind->data_get();
  int        LineBehind       = stringToNumber(ChildBehindData->lineGet());
  int        DifferenceBehind = LineBehind-LineImportEnd;
  int        DifferenceBefore = LineImportBegin-LineBefore;

  import = _assembleBetween(destination,         import,
                            limitToImportBehind, limitToImportBefore,
                            DifferenceBehind,    DifferenceBefore,
                            importLevel);
 }
 else if(  (_compare(import, destination)    > 0      )
         &&(destination->fellowBehind_get() == nullptr)
        )
 {
  import = _assembleBehind(destination, import, importLevel);
 }
 else
 {
 }

 return(import);
}





/* @MRTZ_describe _assembleDownwards

*/
TiPa_Concrete::DataAssociation* Prcs_Trn_Merge::_assembleDownwards(TiPa_Concrete::DataAssociation* destination,
                                                            TiPa_Concrete::DataAssociation* import,
                                                            int                      limitToImportBehind,
                                                            int                      limitToImportBefore,
                                                            set<String_imp>*         importLevel)
{
 TiPa_Concrete::DataAssociation* DestChild = destination->contractorFirst_get();
 while(  (DestChild != nullptr)
       &&(import    != nullptr)
      )
 {
   import = _assemble(DestChild, import, /*config,*/
                      limitToImportBehind,
                      limitToImportBefore,
                      importLevel);

  DestChild = DestChild->fellowBehind_get();
 }

 if(import != nullptr)
 {
  destination->contractorBehind_add(DestChild,import);
  import = nullptr;
 }

 return(import);
}



/* @MRTZ_describe _assembleBefore

*/
TiPa_Concrete::DataAssociation* Prcs_Trn_Merge::_assembleBefore(TiPa_Concrete::DataAssociation* destination,
                                                         TiPa_Concrete::DataAssociation* import,
                                                         set<String_imp>*         importLevel)
{
 TiPa_Concrete::DataAssociation* DestChild = _searchFirstImportChild(destination,importLevel,import);
                          DestChild->fellowBefore_add(import);
 TiPa_Data* ImportData = import->data_get();

 if(String_imp(ImportData->userName_get()) == COMMAND)
   _assembleBlock(import, DestChild->fellowBefore_get());

 import = nullptr;

 return(import);

}







/* @MRTZ_describe _assembleBetween

*/
TiPa_Concrete::DataAssociation* Prcs_Trn_Merge::_assembleBetween(TiPa_Concrete::DataAssociation* destination,
                                                          TiPa_Concrete::DataAssociation* import,
                                                          int                      limitToImportBehind,
                                                          int                      limitToImportBefore,
                                                          int                      differenceBehind,
                                                          int                      differenceBefore,
                                                          set<String_imp>*         importLevel)
{
 TiPa_Concrete::DataAssociation* DestChild = destination->fellowBehind_get();
 TiPa_Data* ImportData      = import->data_get();
 TiPa_Data* DestinationData = destination->data_get();

// @MRTZ_ifElseChain
  if(  (String_imp(ImportData->userName_get())    == COMMAND)
     &&(import->contractorFirst_get()       != nullptr)
     &&(String_imp(import->contractorFirst_get()->data_get()->userName_get()) == "mrtz_endBlock")
    )
  {
   _assembleBlock(import);
   import = nullptr;
  }
  else if(  (String_imp(ImportData->userName_get())      == COMMAND)
          &&(String_imp(DestinationData->userName_get()) == COMMAND)
         )
  {
   destination->fellowBehind_add(import);
   _assembleBlock(import, destination->fellowBehind_get());
   import = nullptr;
  }
  else if(  (  (limitToImportBefore < 0               )
             &&(differenceBefore    < differenceBehind)
            )
          ||(  (limitToImportBefore >= 0                  )
             &&(differenceBefore    <= limitToImportBefore)
            )
         )
  {
   TiPa_Concrete::DataAssociation* ImportBefore = _searchLastImportChild(destination, importLevel,import);//->ToElement();
   ImportBefore->fellowBehind_add(import);
   if(String_imp(ImportData->userName_get())    == COMMAND)
     _assembleBlock(import, ImportBefore->fellowBehind_get());

   import = nullptr;

  }
  else if(  (  (limitToImportBehind < 0               )
             &&(differenceBehind    < differenceBefore)
            )
          ||(  (limitToImportBehind >= 0                  )
             &&(differenceBehind    <= limitToImportBehind)
            )
         )
  {
   TiPa_Concrete::DataAssociation* ImportBehind = _searchFirstImportChild(DestChild, importLevel,import);//->ToElement();
   ImportBehind->fellowBefore_add(import);

   if(String_imp(ImportData->userName_get())    == COMMAND)
    _assembleBlock(import, ImportBehind->fellowBefore_get());

   import = nullptr;
  }
  else
  {
   TiPa_Concrete::DataAssociation* ImportBefore = _searchLastImportChild(destination, importLevel,import);//->ToElement();

   if(ImportBefore != destination)
   {
    ImportBefore->fellowBehind_add(import);

    if(String_imp(ImportData->userName_get())    == COMMAND)
     _assembleBlock(import, ImportBefore->fellowBehind_get());

   }
   else
   {

    TiPa_Concrete::DataAssociation* ImportBehind = _searchFirstImportChild(destination->fellowBehind_get(), importLevel,import);//->ToElement();
    ImportBehind->fellowBefore_add(import);

    if(String_imp(ImportData->userName_get())    == COMMAND)
     _assembleBlock(import, ImportBehind->fellowBefore_get());

   }
   import = nullptr;

  }

 return(import);
}











/* @MRTZ_describe _assembleBehind

*/
TiPa_Concrete::DataAssociation* Prcs_Trn_Merge::_assembleBehind(TiPa_Concrete::DataAssociation* destination,
                                                         TiPa_Concrete::DataAssociation* import,
                                                         set<String_imp>*         importLevel)
{

 TiPa_Concrete::DataAssociation* DestChild = _searchLastImportChild(destination, importLevel,import);
 TiPa_Data* DestChildData = DestChild->data_get();

 while(  (DestChild->fellowBehind_get()       != nullptr)
       &&(String_imp(DestChildData->userName_get()) == COMMENT)
      )
 {
   DestChild = DestChild->fellowBehind_get();
 }
 DestChild->fellowBehind_add(import);

 import = nullptr;

 return(import);
}








/* @MRTZ_describe _assembleBlock

*/
void Prcs_Trn_Merge::_assembleBlock(TiPa_Concrete::DataAssociation* import,
                                    TiPa_Concrete::DataAssociation* blockBegin)
{
  TiPa_Data* SubImportData  = import->contractorFirst_get()->data_get();

 if     (String_imp(SubImportData->userName_get()) == "mrtz_beginBlock")
 {
  if(blockBegin != nullptr)
   Att.BlockStack.push_back(blockBegin);
  else
   cout << "invalid child-block for mrtz_beginBlock" << endl;
 }
 else if(String_imp(SubImportData->userName_get()) == "mrtz_endBlock")
 {
// @MRTZ_exclude create_sub_block
// @MRTZ_beginBlock
  if(!(Att.BlockStack.empty()))
  {
   TiPa_Concrete::DataAssociation* ImportBefore = Att.BlockStack.back();//->ToElement();
   while(  ( ImportBefore->fellowBehind_get()                   != nullptr)
         &&( _compare(import, ImportBefore->fellowBehind_get()) == 1      )
        )
   {
    ImportBefore = ImportBefore->fellowBehind_get();
   }
   TiPa_Search              Search;
   TiPa_Concrete::DataAssociation* DestOfMove  = Att.BlockStack.back();
                            DestOfMove -> contractorFirst_cut(Search(TiPa_Search::UserName,"mrtz_beginBlock"));
//                            DestOfMove -> data_get()->userName_set((char*)DestOfMove -> data_get()->secondaryData_add("UserName", BLOCK.c_str())) ;
                            DestOfMove -> data_get()->userName_set( BLOCK.c_str()) ;
   TiPa_Concrete::DataAssociation* ChildToMove = DestOfMove->fellowBehind_get();
   TiPa_Concrete::DataAssociation* DontMove    = ImportBefore->fellowBehind_get();
   while(  (ChildToMove != DontMove)
         &&(ChildToMove != nullptr)
        )
   {
    TiPa_Concrete::DataAssociation* NextChild = ChildToMove->fellowBehind_get();
    ChildToMove = (ChildToMove->sponsor_get())->cutNode(ChildToMove);

    if(ChildToMove != nullptr)
     DestOfMove->contractorLast_add(ChildToMove);
    ChildToMove = NextChild;
   }
   Att.BlockStack.pop_back();
  }
  else
   cout << "no child-blocks defined for mrtz_endBlock in Line "
        << SubImportData->lineGet()<< endl;
// @MRTZ_endBlock

  if(blockBegin != nullptr )
  {
   TiPa_Data* BlockBeginData    = blockBegin->data_get();
   TiPa_Data* SubBlockBeginData = blockBegin->contractorFirst_get()->data_get();
   if(  (blockBegin->sponsor_get()               != nullptr )
      &&(blockBegin->contractorFirst_get()       != nullptr )
      &&(String_imp(BlockBeginData->userName_get())    == COMMAND)
      &&(String_imp(SubBlockBeginData->userName_get()) == "mrtz_endBlock")
     )
   {
    blockBegin->sponsor_get()->cutNode(blockBegin);
   }
  }
 }
 else
 {
 }
}









/* @MRTZ_describe _compare

   @MRTZ_describe local_declarations

   @MRTZ_describe define_ColumnFixEnd

*/
int Prcs_Trn_Merge::_compare(TiPa_Concrete::DataAssociation* unknown, TiPa_Concrete::DataAssociation* fix)
{

// @MRTZ_exclude local_declarations
// @MRTZ_beginBlock
 int                      ReturnValue = 0;
 TiPa_Concrete::DataAssociation* Unknown     = unknown;
 TiPa_Concrete::DataAssociation* FixBegin    = fix;

// @MRTZ_endBlock



 if(  (Unknown != nullptr)
    &&(FixBegin!= nullptr)
   )
 {
  int                      LineUnknown     = stringToNumber(Unknown->data_get()->lineGet());
  int                      LineFixBegin    = stringToNumber(FixBegin->data_get()->lineGet());
  int                      CollumnUnknown  = stringToNumber(Unknown->data_get()->columnGet());
  int                      CollumnFixBegin = stringToNumber(FixBegin->data_get()->columnGet());
  TiPa_Concrete::DataAssociation* FixEnd          = _searchLastLeafChild(FixBegin);//->ToElement();

// @MRTZ_exclude define_ColumnFixEnd
// @MRTZ_beginBlock
  int LineFixEnd    = stringToNumber(FixEnd->data_get()->lineGet());
  int CollumnFixEnd = stringToNumber(FixEnd->data_get()->columnGet());
  TiPa_Data* FixEndData       = FixEnd->data_get();
  TiPa_Data* FixEndParentData = FixEnd->sponsor_get()->data_get();
// @MRTZ_ifElseChain
  if( FixEnd->contractorFirst_get() == nullptr)//leaf-node with text-atom
  {
   String_imp Text = FixEndData->getContent();
              Text = replacePartString(Text,"\r\n","\n");
              Text = replacePartString(Text,"\r","\n");
   size_t Pos  = 0;
   while(Text.find("\n", Pos) < Text.size())
   {
    Pos = Text.find("\n", Pos) + 1;
    LineFixEnd++;
   }
   CollumnFixEnd = Text.size() - Pos;
  }
  else if(String_imp(FixEndParentData->userName_get()) == COMMAND)
  {
   CollumnFixEnd = strlen(FixEndData->userName_get());
  }
  else
  {

  }
// @MRTZ_endBlock

// @MRTZ_ifElseChain
  if     (LineUnknown < LineFixBegin)
  {
   ReturnValue = -1;
  }
  else if(LineUnknown > LineFixEnd)
  {
   ReturnValue = +1;
  }

  else if(  (LineUnknown    == LineFixBegin)
          &&(CollumnUnknown <  CollumnFixBegin)
         )
  {
   ReturnValue = -1;
  }
  else if(  (LineUnknown    == LineFixEnd)
          &&(CollumnUnknown >  CollumnFixEnd))
  {
   ReturnValue = +1;
  }
  else
  {
   ReturnValue = 0;
  }
 }

 return(ReturnValue);
}





/* @MRTZ_describe _searchFirstLeafChild

*/
TiPa_Concrete::DataAssociation* Prcs_Trn_Merge::_searchFirstLeafChild(TiPa_Concrete::DataAssociation* parent)
{
 TiPa_Concrete::DataAssociation* ReturnValue = nullptr;

 if(parent->contractorFirst_get() != nullptr)
 {
  ReturnValue = _searchFirstLeafChild(parent->contractorFirst_get());
 }
 else
 {
  ReturnValue = parent;
 }

 return(ReturnValue);
}





/* @MRTZ_describe _searchLastLeafChild

*/
TiPa_Concrete::DataAssociation* Prcs_Trn_Merge::_searchLastLeafChild(TiPa_Concrete::DataAssociation* parent)
{
 TiPa_Concrete::DataAssociation* ReturnValue = nullptr;

 if(parent->contractorLast_get() != nullptr)
 {
  ReturnValue = _searchLastLeafChild(parent->contractorLast_get());
 }
 else
 {
  ReturnValue = parent;
 }

 return(ReturnValue);
}




/* @MRTZ_describe _searchFirstImportChild

*/
TiPa_Concrete::DataAssociation* Prcs_Trn_Merge::_searchFirstImportChild(TiPa_Concrete::DataAssociation* parent,
                                                                 set<String_imp>*         importLevel,
                                                                 TiPa_Concrete::DataAssociation* import)
{
 TiPa_Concrete::DataAssociation* ReturnValue = nullptr;

 if(  (parent                        != nullptr)
    &&(parent->contractorFirst_get() != nullptr)
    )
 {
  TiPa_Concrete::DataAssociation* Child            = parent->contractorFirst_get();
  TiPa_Data*               ImportData       = import->data_get();

  String_imp               ParentParentName = "";
  if(parent->sponsor_get()  != nullptr)
   ParentParentName = parent->sponsor_get()->data_get()->userName_get();

  while(  (Child             != nullptr)
        &&(  (String_imp(Child->data_get()->userName_get()) == COMMAND)
           ||(  (String_imp(Child->data_get()->userName_get())  == COMMENT)
              &&(String_imp(ImportData->userName_get())         == COMMAND)
             )
           ||(_compare(import, Child) > 0)
          )
       )
   Child = Child->fellowBehind_get();

  if(  (Child                               != nullptr)
     &&(importLevel->find(ParentParentName) == importLevel->end())
    )
  {
   ReturnValue = _searchFirstImportChild(Child, importLevel,import);
  }
  else
  {
   ReturnValue = parent;
  }
 }
 else
 {
  ReturnValue = parent;
 }

 return(ReturnValue);
}





/* @MRTZ_describe _searchLastImportChild

*/
TiPa_Concrete::DataAssociation* Prcs_Trn_Merge::_searchLastImportChild(TiPa_Concrete::DataAssociation* parent,
                                                                set<String_imp>*         importLevel,
                                                                TiPa_Concrete::DataAssociation* import)
{
 TiPa_Concrete::DataAssociation* ReturnValue = nullptr;

 if(  (parent                        != nullptr)
    &&(parent->contractorFirst_get() != nullptr)
    )
 {
  TiPa_Concrete::DataAssociation* Child            = parent->contractorLast_get();
  TiPa_Data*               ImportData       = import->data_get();

  String_imp               ParentParentName = "";
  if(parent->sponsor_get()  != nullptr)
   ParentParentName = parent->sponsor_get()->data_get()->userName_get();

  while(  (Child             != nullptr)
        &&(  (String_imp(Child->data_get()->userName_get()) == COMMAND)
           ||(  (String_imp(Child->data_get()->userName_get())  == COMMENT)
              &&(String_imp(ImportData->userName_get())         == COMMAND)
             )
           ||(_compare(import, Child) < 0)
          )
       )
   Child = Child->fellowBefore_get();

  if(  (Child                               != nullptr)
     &&(importLevel->find(ParentParentName) == importLevel->end())
    )
  {
   ReturnValue = _searchLastImportChild(Child, importLevel,import);
  }
  else
  {
   ReturnValue = parent;
  }
 }
 else
 {
  ReturnValue = parent;
 }

 return(ReturnValue);
}





/* @MRTZ_describe _moveCodePart

   @MRTZ_describe local_declarations

   @MRTZ_describe move_block_content

*/
void Prcs_Trn_Merge::_moveCodePart(TiPa_Concrete::DataAssociation* codeTree, TiPa_DataModel* codeModel)
{

 list<TiPa_Concrete::DataAssociation*> EmptyExclude;
 TiPa_Concrete::DataAssociation*       SortIndex = codeTree->contractorFirst_get();

 while(SortIndex != nullptr)
 {
  TiPa_Concrete::DataAssociation* NextChild = SortIndex->fellowBehind_get();
  TiPa_Data* SortIndexData = SortIndex->data_get();

  if(String_imp(SortIndexData->userName_get()) != COMMAND)
  {
   if(SortIndex->contractorFirst_get() != nullptr) //
   {
   _moveCodePart(SortIndex, codeModel);
   }

   TiPa_Concrete::DataAssociation* ChildBefore = SortIndex->fellowBefore_get();

   TiPa_Search Search;
   if(  (ChildBefore                                   != nullptr)
      &&(String_imp(ChildBefore->data_get()->userName_get()) == COMMAND)
      &&(ChildBefore->contractorFirst_get()            != nullptr)
      &&(  (  (ChildBefore->contractorFirst_get(Search(TiPa_Search::UserName,"mrtz_describe"))    == nullptr)
            &&(ChildBefore->contractorFirst_get(Search(TiPa_Search::UserName,"mrtz_independent")) == nullptr)
            &&(ChildBefore->contractorFirst_get(Search(TiPa_Search::UserName,"mrtz_insertLink"))  == nullptr)
           )
        )
     )
   {
    ChildBefore = ChildBefore->contractorFirst_get();

    if(  (ChildBefore                        != nullptr)
       &&(ChildBefore->contractorFirst_get() == nullptr)
      )
    {
     SortIndex   =  SortIndex->sponsor_get()->cutNode(SortIndex);

     if(String_imp(SortIndexData->userName_get()) == BLOCK)
     {
      ChildBefore->contractorLast_add(SortIndex);
     }
     else
     {
      TiPa_Data*               DestinationData = codeModel->data_create();
      TiPa_Concrete::DataAssociation* Destination     = codeModel->fellow_create(DestinationData);
//      DestinationData->userName_set((char*)DestinationData->secondaryData_add("UserName", BLOCK.c_str())) ;
      DestinationData->userName_set(BLOCK.c_str()) ;

      DestinationData->lineSet(atoi(SortIndex->data_get()->lineGet()));
      DestinationData->columnSet(atoi(SortIndex->data_get()->columnGet()));


      Destination->contractorLast_add(SortIndex);
      ChildBefore->contractorLast_add(Destination);
     }
    }
   }
  }
  else  if(String_imp(SortIndexData->userName_get()) == COMMAND)
  {
   TiPa_Concrete::DataAssociation* ChildBefore     = SortIndex->contractorFirst_get();
   TiPa_Data*               ChildBeforeData = ChildBefore->data_get();

   if(  (ChildBefore                           != nullptr       )
      &&(String_imp(ChildBeforeData->userName_get()) == "mrtz_exclude")
     )
   {
    EmptyExclude.push_back(ChildBefore);
   }
   else
   {
    if(  (ChildBefore                           != nullptr       )
       &&(ChildBefore->contractorFirst_get()    != nullptr       )
       &&(String_imp(ChildBeforeData->userName_get()) == "mrtz_exclude")
     )
    {
     ChildBefore = ChildBefore -> contractorFirst_get();
     ChildBeforeData = ChildBefore->data_get();
     if(  (ChildBefore                           != nullptr    )
        &&(ChildBefore->contractorFirst_get()    != nullptr    )
        &&(String_imp(ChildBeforeData->userName_get()) == "__block__")
       )
      {
       ChildBefore = ChildBefore -> contractorFirst_get();
       ChildBeforeData = ChildBefore->data_get();

       if(  (ChildBefore                           != nullptr)
          &&(ChildBefore->contractorFirst_get()    != nullptr    )
          &&(String_imp(ChildBeforeData->userName_get()) == "BLOCK_OPEN")
         )
       {
//        cout << "wrong use of mrtz-exclude before blockopen in Line : " << ChildBefore->ToElement()->Attribute("L") <<  endl;
//        cout << "wrong use of mrtz-exclude before blockopen in Line : " << ChildBeforeData->Line <<  endl;
       }
      }
    }
   }
  }

  SortIndex = NextChild;
 }

 list<TiPa_Concrete::DataAssociation*>::iterator ToFill = EmptyExclude.begin();
 while(ToFill != EmptyExclude.end())
 {
  TiPa_Concrete::DataAssociation*  NextChild = (*ToFill)->fellowBehind_get();

  if(  (NextChild                                   != nullptr)
     &&(NextChild->contractorFirst_get()            != nullptr)
     &&(String_imp(NextChild->data_get()->userName_get()) == COMMAND)
    )
  {

   TiPa_Data*               DestinationData = codeModel->data_create();
   TiPa_Concrete::DataAssociation* Destination     = codeModel->fellow_create(DestinationData);
//   DestinationData->userName_set((char*)DestinationData->secondaryData_add("UserName", BLOCK.c_str())) ;
   DestinationData->userName_set(BLOCK.c_str()) ;


   DestinationData->lineSet(atoi(SortIndex->data_get()->lineGet()));
   DestinationData->columnSet(atoi(SortIndex->data_get()->columnGet()));

   NextChild = codeTree->cutNode(NextChild);
   Destination->contractorLast_add(NextChild);
   (*ToFill)->contractorLast_add(Destination);
 }
  ++ToFill;
 }
}




/* @MRTZ_describe _assembleCommentsToCommands

*/
TiPa_Concrete::DataAssociation* Prcs_Trn_Merge::_assembleCommentsToCommands(TiPa_Concrete::DataAssociation* import,
                                                                     TiPa_Concrete::DataAssociation* nextChild,
                                                                     TiPa_DataModel* codeModel)
{
 if(nextChild != nullptr)
 {
  TiPa_Concrete::DataAssociation* ImportChild = import->contractorFirst_get();
  TiPa_Data* ImportChildData = ImportChild->data_get();
  TiPa_Data* NextChildData   = nextChild->data_get();

  if(  (  (String_imp(ImportChildData->userName_get()) == "mrtz_describe")
        ||(String_imp(ImportChildData->userName_get()) == "mrtz_independent")
        ||(String_imp(ImportChildData->userName_get()) == "mrtz_insertLink")
       )
     &&(String_imp(NextChildData->userName_get())   == "Comment")
     &&(  (  stringToNumber(NextChildData->lineGet())
           - stringToNumber(ImportChildData->lineGet())
          )
        <=1
       )
   )
  {
   TiPa_Concrete::DataAssociation*  FollowOfImport = nextChild;
                             nextChild      = nextChild->fellowBehind_get();
                             FollowOfImport = FollowOfImport->sponsor_get()->cutNode(FollowOfImport);

   TiPa_Data*               DestinationData = codeModel->data_create();
   TiPa_Concrete::DataAssociation* Destination     = codeModel->fellow_create(DestinationData);
//   DestinationData->userName_set((char*)DestinationData->secondaryData_add("UserName", BLOCK.c_str()));
   DestinationData->userName_set(BLOCK.c_str());


   DestinationData->lineSet(atoi(FollowOfImport->data_get()->lineGet()));
   DestinationData->columnSet(atoi(FollowOfImport->data_get()->columnGet()));

   Destination->contractorLast_add(FollowOfImport);
   ImportChild->contractorLast_add(Destination);
  }

 }
 return(nextChild);
}


#ifndef DOXYGEN
//};};
#endif //DOXYGEN
