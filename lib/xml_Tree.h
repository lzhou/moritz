/*!

 @file
 @brief create an xml-tree from xml-parser data

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
    27.12.2019     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    27.12.2019...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/

#ifndef XML_TREE_H
#define XML_TREE_H

#include <stdio.h>
#include <list>
#include <map>
#include "ASS_Visitor.hpp"
#include "TiPa_Data.h"
#include "TDA_GrmConcrete.h"

using namespace std;




/*!
 @brief concrete visitor to create a reduced association-tree

 Nodes with specified data will be treated as leaf-nodes and their contractors will be ignored.
 Depending on the work-mode other nodes with specified data will be skipped or they will be part
 of the new association while in both cases their contractors will still evaluated.
 The currently used filter criteria is the user-id
*/
class XML_Tree//:public AssociationVisitor<TiPa_Data*,nullptr>
{
 public:


 /// filter mode of this visitor
 typedef enum FilterMode_TP
 {
  KeepUndefined,                 ///< deliver a reduced association tree where undefined nodes are kept
  SkipUndefined,                 ///< deliver a reduced association tree where undefined nodes are skipped
  FilterMode_DF = KeepUndefined, ///< for initialisation purposes => valid
  FilterMode_NV,                 ///< for initialisation purposes => not valid
 }FilterMode_TP;

// /// data clone mode
// typedef enum CloneMode_TP
// {
//  ReuseData,                     ///< do not clone the data but reference the original data
//  CloneData,                     ///< do not reference the original data but clone the data
//  CloneMode_DF = ReuseData,      ///< for initialisation purposes => valid
//  CloneMode_NV,                  ///< for initialisation purposes => not valid
// }CloneMode_TP;
//


 typedef AssociationVisitor<TiPa_Data*,nullptr>  TiPa_Visitor;

 typedef Association<TiPa_Data*,nullptr>           DataAssociation;
 typedef AssociationFellowship<TiPa_Data*,nullptr> DataFellow;



/*!
 default constructor

 <br><br>

 @htmlinclude ./des/XML_Tree_XML_Tree.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    15.11.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 XML_Tree();



/*!
  constructor setting the context-model

 <br><br>

 @htmlinclude ./des/XML_Tree_XML_Tree.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    15.11.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 explicit XML_Tree(TiPa_Concrete::DataModel* contextModel,
                   TiPa_Concrete*            rootParser);


/*!
 specifying constructor

 @param [in] mode         kind of search
 @param [in]  cloneMode    control if original data should be referenced (ReuseData)
 <br>                      or the data should be cloned (CloneData)
 @param [in] keepNodes    nodes to keep
 @param [in] skipNodes    nodes to skip
 @param [in] leafNodes    nodes to leave
 @param [in] hideNodes    nodes to hide

 @htmlinclude ./des/XML_Tree_XML_Tree.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    15.11.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
    19.03.2017   @I  Eckard Klotz
 @I implementation of data cloning
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  XML_Tree(FilterMode_TP                           mode,
//           CloneMode_TP                            cloneMode,
map<TiPa_Concrete*, TDA_GrmConcrete::Property_TP>* parserProperty,
           TiPa_Concrete::DataModel*               contextModel,
           TiPa_Concrete*                          rootParser,
           set<int>*                               keepNodes = nullptr,
           set<int>*                               skipNodes = nullptr,
           set<int>*                               leafNodes = nullptr,
           set<int>*                               hideNodes = nullptr);

/*!
 default destructor



 @htmlinclude ./des/XML_Tree__XML_Tree.html

 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    15.11.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/

 virtual  ~XML_Tree(void);



/*!
 initialize this visitor

 @param [in] mode         kind of search
 @param [in] cloneMode    control if original data should be referenced (ReuseData)
 <br>                     or the data should be cloned (CloneData)
 @param [in] keepNodes    nodes to keep
 @param [in] skipNodes    nodes to skip
 @param [in] leafNodes    leaf-nodes
 @param [in] hideNodes    nodes to hide

 @htmlinclude ./des/XML_Tree_init.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    15.11.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
    19.03.2017   @I  Eckard Klotz
 @I implementation of data cloning
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void init(FilterMode_TP mode,
//           CloneMode_TP  cloneMode,
//           const char*   text,
           set<int>*     keepNodes,
           set<int>*     skipNodes,
           set<int>*     leafNodes,
           set<int>*     hideNodes);




/*!
 @brief define the context-model

 @param [in] contextModel management-object that creates and deletes associations and data-objects

 @htmlinclude ./des/XML_Tree_contextModel_set.html

 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    04.05.2016   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
void contextModel_set(TiPa_Concrete::DataModel* contextModel);



/*!
 initialize this visitor

 @param [in]  mode         kind of filter-algorithm
 @param [out] destination  root node of the new association tree to create
 @param [in]  cloneMode    control if original data should be referenced (ReuseData)
 <br>                      or the data should be cloned                  (CloneData)

 @return pointer to initialized class-object

 @htmlinclude ./des/XML_Tree_operator().html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    15.11.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
    19.03.2017   @I  Eckard Klotz
 @I implementation of data cloning
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
// XML_Tree* operator()(FilterMode_TP                   mode,
//                      DataFellow* destination,
//                      const char*                     text/*,
//                      CloneMode_TP                    cloneMode= CloneMode_DF*/);










/*!
 parameter-type for the method @ref specialNodes_set
*/
typedef enum SpecialNodes_TP
{
 NodesToKeep,  ///< define the nodes which should be kept in the output
               ///< and which may contain contractor associations to evaluate
 NodesToSkip,  ///< define the nodes which should be skipped in the output
               ///< but which may still contain contractor associations to evaluate
 NodesAsLeaf,  ///< define the nodes which should be kept in the output
               ///< and which contain no contractor associations to evaluate
 NodesToHide,  ///< define the nodes which should not shown in the output
               ///< and which contain no contractor associations to evaluate
}SpecialNodes_TP;



/*!
 initialize a specific set of nodes that should be kept, skipped
 or should be treated as leaf-node

 @param [in] nodeType      node-set to initialize
 @param [in] separatedList list of numbers
 @param [in] separator     separator used in the separated list


 @htmlinclude ./des/XML_Tree_specialNodes_set().html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    03.12.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void specialNodes_set(SpecialNodes_TP nodeType,
                       const char*     separatedList,
                             char      separator = ',');



/*!
 initialize a specific set of nodes that should be kept, skipped
 or should be treated as leaf-node

 @param [in] nodeType      node-set to initialize
 @param [in] lowerLimit    nodes with a id equal or higher will be filtered


 @htmlinclude ./des/XML_Tree_specialNodes_set().html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    13.12.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void specialNodes_set(SpecialNodes_TP nodeType,
                       int             lowerLimit);






/*!
 @brief extend a specific set of nodes that should be kept, skipped
 or should be treated as leaf-node

 @param [in] nodeType      node-set to initialize
 @param [in] idToInsert    additional id to filter


 @htmlinclude ./des/XML_Tree_specialNodes_insert().html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    19.11.2017   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void specialNodes_insert(SpecialNodes_TP nodeType,
                       int             idToInsert);







/*!
 initialize a specific set of nodes that should be kept, skipped
 or should be treated as leaf-node by searching the ids in the
 @ref ParserProperty object

 @param [in] nodeType      node-set to initialize
 @param [in] separatedList list of parser-names
 @param [in] separator     separator used in the separated list


 @htmlinclude ./des/XML_Tree_specialNodes_search().html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    16.12.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void specialNodes_search(SpecialNodes_TP nodeType,
                          const char*     separatedList,
                                char      separator = ',');



/*!
 initialize a specific set of nodes that should be kept, skipped
 or should be treated as leaf-node by searching the ids in the
 @ref ParserProperty object

 @param [in] nodeType   node-set to initialize
 @param [in] parserName name of the parser used as part of set of nodes


 @htmlinclude ./des/XML_Tree_specialNode_search().html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    16.12.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void specialNode_search(SpecialNodes_TP nodeType,
                         const char*     parserName);




 /*!
 set the data-base used by the grammar-generator to store normal data
 around a parser by


 @param [in] parserProperties reference to the data base

 <br><br>
 @htmlinclude "XML_Tree_parserProperties_set.html"
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    16.12.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 void parserProperties_set(map<TiPa_Concrete*, TDA_GrmConcrete::Property_TP>* parserProperties);







// @param sponsor the sponsor of the association to analyse

/*!
 start to evaluate an association

 @param node    the association to analyse


 @htmlinclude ./des/XML_Tree_evaluate.html

 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    15.11.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
/*DirectionOfIteration TiPa_Concrete::DataAssociation* node
                              ,TiPa_Concrete::DataAssociation* sponsor*/



DataFellow* evaluate(const char*   text,
                                         FilterMode_TP mode = SkipUndefined);





/*!
 @brief create a reduced association-tree while keeping nodes with specified data

 Nodes with specified data will be treated as leaf-nodes and their contractors will be ignored.
 Other nodes with specified data will be part of the new association and all others will be skipped,
 while in both cases their contractors will still evaluated.

 The currently used filter criteria is the user-id.


 @param [in]  source      root association of association tree to analyse
 @param [out] destination root association of association tree to create,
                          normally not for external use but for internal recursive calls

 @return a new association-tree that's associations point to data of the given association-tree

 <br><br>
 @htmlinclude ./des/XML_Tree_collectKeyData.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    15.11.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
DataFellow* evaluateKeep(TiPa_Concrete::Hit_TP*          result,
//                                             TiPa_Concrete::DataAssociation* source,
                                             DataFellow* destination);


/*!
 @brief create a reduced association-tree while skipping nodes with specified data

 Nodes with specified data will be treated as leaf-nodes and their contractors will be ignored.
 Other nodes with specified data will not be part of the new association and all others will be kept,
 while in both cases their contractors will still evaluated.

 The currently used filter criteria is the user-id.


 @param [in]  source      root association of association tree to analyse
 @param [out] destination root association of association tree to create,
                          normally not for external use but for internal recursive calls

 @return a new association-tree that's associations point to data of the given association-tree

 <br><br>
 @htmlinclude ./des/XML_Tree_collectKeyData.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    15.11.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
DataFellow* evaluateSkip(TiPa_Concrete::Hit_TP*          result,
//                                             TiPa_Concrete::DataAssociation* source,
                                             DataFellow* destination);




 protected:

 private:


 TiPa_Data* defineDataContent(TiPa_Concrete::Hit_TP* source);



 struct Att
 {

  FilterMode_TP                            Mode;            ///< @brief mode of search and evaluation

  DirectionOfIteration                     CommonDirection; ///< @brief stores the direction to iterate while temporary changes
  set<int>                                 KeepNodes;       ///< @brief nodes which should be kept in the output
                                                            ///<        and which may contain contractor associations to evaluate
  set<int>                                 SkipNodes;       ///< @brief nodes which should be skipped in the output
                                                            ///<        but which may still contain contractor associations to evaluate
  set<int>                                 LeafNodes;       ///< @brief nodes which should be kept in the output
                                                            ///<        and which contain no contractor associations to evaluate
  set<int>                                 HideNodes;       ///< @brief nodes which should be not shown in the output
                                                            ///<        and which contain no contractor associations to evaluate


  int KeepAboveID;                                          ///< @brief all nodes with an id higher than that should be kept
  int SkipAboveID;                                          ///< @brief all nodes with an id higher than that should be skipped
  int LeafAboveID;                                          ///< @brief all nodes with an id higher than that should be used as leaf
  int HideAboveID;                                          ///< @brief all nodes with an id higher than that should be hidden
  map<TiPa_Concrete*, TDA_GrmConcrete::Property_TP>* ParserProperty;
                                                            ///< @brief data-base used to store normal data around a parser

  TiPa_Concrete::DataModel*                ContextModel;    ///< @brief manages the analysed data

  TiPa_Concrete*                           RootParser;

  Att():Mode(FilterMode_NV),
        CommonDirection(IterateAsBefore),
        KeepAboveID(INT_MAX),
        SkipAboveID(INT_MAX),
        LeafAboveID(INT_MAX),
        HideAboveID(INT_MAX),
        ParserProperty(nullptr),
        ContextModel(nullptr),
        RootParser(nullptr){};

  Att(const Att& att):
   Mode           (att.Mode           ),
   CommonDirection(att.CommonDirection),
   KeepNodes      (att.KeepNodes      ),
   SkipNodes      (att.SkipNodes      ),
   LeafNodes      (att.LeafNodes      ),
   HideNodes      (att.HideNodes      ),
   KeepAboveID    (att.KeepAboveID    ),
   SkipAboveID    (att.SkipAboveID    ),
   LeafAboveID    (att.LeafAboveID    ),
   HideAboveID    (att.HideAboveID    ),
   ParserProperty (att.ParserProperty ),
   ContextModel   (att.ContextModel   ),
   RootParser     (att.RootParser     )
  {};


  Att& operator= (const Att& att)
  {
   Mode            = att.Mode           ;
   CommonDirection = att.CommonDirection;
   KeepNodes       = att.KeepNodes      ;
   SkipNodes       = att.SkipNodes      ;
   LeafNodes       = att.LeafNodes      ;
   HideNodes       = att.HideNodes      ;
   KeepAboveID     = att.KeepAboveID    ;
   SkipAboveID     = att.SkipAboveID    ;
   LeafAboveID     = att.LeafAboveID    ;
   HideAboveID     = att.HideAboveID    ;
   ParserProperty  = att.ParserProperty ;
   ContextModel    = att.ContextModel   ;
   RootParser      = att.RootParser     ;
   return(*this);
  };

  ~Att(void)
  {
   KeepNodes.clear();
   SkipNodes.clear();
   LeafNodes.clear();
   HideNodes.clear();
  }
 }Att;

};





#endif // XML_TREE_H

