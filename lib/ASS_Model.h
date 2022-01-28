/*!

 @file
 @brief central manager of associations and association_data

 Copyright (C) 2016-2020 by Eckard Klotz.

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
    26.04.2016     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    26.04.2015...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/

#ifndef ASS_MODEL_H
#define ASS_MODEL_H



#include "AssociationFellowship.h"
#include "ASS_Data.h"


#include <stdio.h>
#include <set>
#include <map>





using namespace std;




/*!
 abstract manager of tree_data

 this class describes an common interface between the data of a tree node and its
 node that is managing the tree-associations
*/
template <class DataType, DataType* defaultData> class AssociationModel
{
 public:

/*!
 @brief parameter for methods to create new fellow or sponsor trees to use for parameter cloneData
*/
typedef enum CloneData_TP
{
 DataReuse = 0,
 DataClone = 1,
}CloneData_TP;



/*!
 default constructor

 <br><br>

 @htmlinclude ./des/AssociationModel_AssociationModel.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    26.04.2016   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 AssociationModel(void);



/*!
 default destructor

 <br><br>

 @htmlinclude ./des/AssociationModel__AssociationModel.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    26.04.2016   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/

 ~AssociationModel(void);


 void init(bool shutDown = false);


 DataType* data_create(void);

 DataType* data_create(DataType* data);

 void data_insert(DataType* data);

 bool data_known(DataType* data);

 void data_delete(DataType* data);


 AssociationFellowship<DataType*, defaultData>* fellow_create(void);

 AssociationFellowship<DataType*, defaultData>* fellow_create(DataType* data);

 AssociationFellowship<DataType*, defaultData>* fellow_create(Association<DataType*, defaultData>* association, CloneData_TP cloneData = DataReuse);

 void fellow_insert(AssociationFellowship<DataType*, defaultData>* association);

 bool fellow_known(AssociationFellowship<DataType*, defaultData>* association);

 void fellow_delete(AssociationFellowship<DataType*, defaultData>* association);




 AssociationFellowship<DataType*, defaultData>* focus_Fellow(void);


 DataType*                         focus_Data(void);


 void                              focus_Set(const char* key, bool fellowNode = true);

 Association<DataType*, defaultData>*           focus_Get(const char* key, bool fellowNode = true);


// #define ASSOCIATIONMODEL_DEBUG

 #ifdef ASSOCIATIONMODEL_DEBUG
  void outputSize(void);
 #endif // ASSOCIATIONMODEL_DEBUG







 protected:


 private:







 /*!
  @brief Attributes of class
 */
 struct Att
 {
  set<AssociationFellowship<DataType*, defaultData>*>    Fellow{};  ///< @brief container of fellowship associations
  set<DataType*>                                         Data{};    ///< @brief container of data-objects

  Att(void):Fellow(),Data(){};                                      ///< @brief initialisation
  Att(AssociationModel::Att& att):Fellow(att.Fellow),Data(att.Data){};
                                                                    ///< @brief copy initialisation
  AssociationModel::Att& operator= (AssociationModel::Att& att)
                         {
                          Fellow  = att.Fellow;
                          Data    = att.Data;
                          return(*this);
                         };                                ///< @brief initialisation
 }Att;


 /*!
  @brief perspective and focus values
 */
 struct Perspective
 {
   map<int, Association<DataType*, defaultData>*> Focus{};              ///< @brief root nodes used while different perspectives of data collection or evaluation
   map<int, const char*>                          Key{};                ///< @brief identifier of perspective node

   AssociationFellowship<DataType*, defaultData>* Fellow{nullptr};      ///< @brief default fellow

   DataType*                                      Data{defaultData};    ///< @brief data

   Perspective(void):Focus(), Key(), Fellow(nullptr), Data(defaultData){};
   Perspective(AssociationModel::Perspective& perspective):Focus(perspective.Focus),
                                                           Key(perspective.Key),
                                                           Fellow(perspective.Fellow),
                                                           Data(perspective.Data){};
   AssociationModel::Perspective& operator = (AssociationModel::Perspective& perspective)
                                  {
                                   Focus   = perspective.Focus;
                                   Key     = perspective.Key;
                                   Fellow  = perspective.Fellow;
                                   Data    = perspective.Data;
                                   return(*this);
                                  };
 }Perspective;                                                          ///< @brief initialisation


};


#endif // ASS_MODEL_H

