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
// @MRTZ_skip
#ifndef ASS_MODEL_HPP
 #define ASS_MODEL_HPP

#include "AssociationFellowship.hpp"


#include "ASS_Model.h"





/* @MRTZ_describe AssociationModel

*/
template <class DataType, DataType* defaultData>
 AssociationModel<DataType, defaultData>::AssociationModel(void)
                                         :Att(),
                                          Perspective()
{
//#ifdef ASSOCIATIONMODEL_DEBUG
//  outputSize();
//#endif // ASSOCIATIONMODEL_DEBUG
 init();
}





/* @MRTZ_describe ~AssociationModel

*/
template <class DataType, DataType* defaultData>
 AssociationModel<DataType, defaultData>::~AssociationModel(void)
{
 init(true);  // shutDown == true
}




/* @MRTZ_describe init

*/
template <class DataType, DataType* defaultData>
 void AssociationModel<DataType, defaultData>::init(bool shutDown)
{

 while(!Att.Fellow.empty())
 {
//  cout << "/";
  delete(*(Att.Fellow.begin()));
//  cout << "-";
  Att.Fellow.erase(Att.Fellow.begin());
//  cout << "\\";
 }

 while(!Att.Data.empty())
 {
//  cout << "+";
  delete(*(Att.Data.begin()));
  Att.Data.erase(Att.Data.begin());
 }

 Perspective.Data    = nullptr;
 Perspective.Fellow  = nullptr;


 Perspective.Focus.clear();


 map<int, const char*>::iterator Key = Perspective.Key.begin();
 while(Key !=  Perspective.Key.end())
 {
  delete[](Key->second);
  ++ Key;
 }
 Perspective.Key.clear();


 if(shutDown == false)
 {
  Perspective.Data    = this->data_create();
  Perspective.Fellow  = this->fellow_create(Perspective.Data);
 }

}


/* @MRTZ_describe data_create

*/
template <class DataType, DataType* defaultData>
 DataType* AssociationModel<DataType, defaultData>::data_create(void)
{
 DataType* Data = new DataType;

 Att.Data.insert(Data);
 return(Data);
}

/* @MRTZ_describe data_create

*/
template <class DataType, DataType* defaultData>
 DataType* AssociationModel<DataType, defaultData>::data_create(DataType* data)
{
 DataType* Data = new DataType(*data);

 Att.Data.insert(Data);
 return(Data);

}

/* @MRTZ_describe data_insert

*/
template <class DataType, DataType* defaultData>
 void AssociationModel<DataType, defaultData>::data_insert(DataType* data)
{
 Att.Data.insert(data);
}

/* @MRTZ_describe data_known

*/
template <class DataType, DataType* defaultData>
 bool AssociationModel<DataType, defaultData>::data_known(DataType* data)
{
 if(Att.Data.find(data)!=Att.Data.end())
    return(true);
 else
    return(false);
}

/* @MRTZ_describe data_delete

*/
template <class DataType, DataType* defaultData>
 void AssociationModel<DataType, defaultData>::data_delete(DataType* data)
{
 if(Att.Data.find(data)!=Att.Data.end())
    Att.Data.erase(data);
 else
 {
 // do nothing
 }
}


/* @MRTZ_describe fellow_create

*/
template <class DataType, DataType* defaultData>
 AssociationFellowship<DataType*, defaultData>* AssociationModel<DataType, defaultData>::fellow_create(void)
{
 AssociationFellowship<DataType*, defaultData>* Fellow = new AssociationFellowship<DataType*, defaultData>;
 //Fellow->data_set(& AssociationModel<DataType, defaultData>::DataDefault);
 Att.Fellow.insert(Fellow);
 return(Fellow);
}

/* @MRTZ_describe fellow_create

*/
template <class DataType, DataType* defaultData>
 AssociationFellowship<DataType*, defaultData>* AssociationModel<DataType, defaultData>::fellow_create(DataType* data)
{
// cout <<__FILE__ << "  #  " << __LINE__ << endl;

 AssociationFellowship<DataType*, defaultData>* Fellow = new AssociationFellowship<DataType*, defaultData>(data);

 Att.Fellow.insert(Fellow);
 return(Fellow);
}

/* @MRTZ_describe fellow_create

*/
template <class DataType, DataType* defaultData>
 AssociationFellowship<DataType*, defaultData>* AssociationModel<DataType, defaultData>::fellow_create(Association<DataType*, defaultData>* association, CloneData_TP cloneData)
{
// cout <<__FILE__ << "  #  " << __LINE__ << endl;
 AssociationFellowship<DataType*, defaultData>* Fellow = nullptr;
 if(cloneData == DataClone) // create a real independent data-tree
 {
  Fellow = new AssociationFellowship<DataType*, defaultData>();
  Fellow->data_set(data_create(association->data_get()));
 }
 else                       // create just an independent association-tree
 {
  Fellow = new AssociationFellowship<DataType*, defaultData>(association->data_get());
 }

 Association<DataType*, defaultData>* Contractor = association->contractorFirst_get();
 while(Contractor != nullptr)
 {
  Fellow->contractorLast_add(fellow_create(Contractor, cloneData));
  Contractor = association->contractorBehind_get(Contractor);
 }


 Att.Fellow.insert(Fellow);
// cout <<__FILE__ << "  #  " << __LINE__ << endl;
 return(Fellow);
}

/* @MRTZ_describe fellow_insert

*/
template <class DataType, DataType* defaultData>
 void AssociationModel<DataType, defaultData>::fellow_insert(AssociationFellowship<DataType*, defaultData>* association)
{
 Att.Fellow.insert(association);
}

/* @MRTZ_describe fellow_known

*/
template <class DataType, DataType* defaultData>
 bool AssociationModel<DataType, defaultData>::fellow_known(AssociationFellowship<DataType*, defaultData>* association)
{
 if(Att.Fellow.find(association)!=Att.Fellow.end())
    return(true);
 else
    return(false);
}

/* @MRTZ_describe fellow_delete

*/
template <class DataType, DataType* defaultData>
 void AssociationModel<DataType, defaultData>::fellow_delete(AssociationFellowship<DataType*, defaultData>* association)
{
 if(Att.Fellow.find(association)!=Att.Fellow.end())
    Att.Fellow.erase(association);
 else
  {
   // do nothing
  }
}









/* @MRTZ_describe focus_Fellow

*/
template <class DataType, DataType* defaultData>
 AssociationFellowship<DataType*, defaultData>* AssociationModel<DataType, defaultData>::focus_Fellow(void)
{
 return(Perspective.Fellow);
}



/* @MRTZ_describe focus_Sponsor

*/
template <class DataType, DataType* defaultData>
 DataType* AssociationModel<DataType, defaultData>::focus_Data(void)
{
 return(Perspective.Data);
}




/* @MRTZ_describe

*/
template <class DataType, DataType* defaultData>
void AssociationModel<DataType, defaultData>::focus_Set(const char* key, bool fellowNode)
{
 Association<DataType*, defaultData>* FocusAssociation = focus_Get(key);

 if(FocusAssociation == nullptr)
 {
  if(fellowNode == true)
  {
   Perspective.Fellow                        = this->fellow_create(Perspective.Data);
   Perspective.Focus[Perspective.Key.size()] = Perspective.Fellow;
  }
  else
  {
   Perspective.Focus[Perspective.Key.size()] = nullptr;
  }

  char*  Key = new char[strlen(key)+1];
  memset(Key,0,strlen(key)+1);
  strcpy(Key,key);
  int Index =  Perspective.Key.size();
  Perspective.Key[Index] = Key;

 }
 else
 {
  if(fellowNode == true)
   Perspective.Fellow  = FocusAssociation->as_AssociationFellowship();
  else
   Perspective.Fellow  = nullptr;
 }
}



/* @MRTZ_describe

*/
template <class DataType, DataType* defaultData>
Association<DataType*, defaultData>* AssociationModel<DataType, defaultData>::focus_Get(const char* key, bool fellowNode)
{
 map<int, const char*>::iterator Node = Perspective.Key.begin();

 while(Node !=  Perspective.Key.end())
 {
  if(  (strstr(Node->second,key) ==        Node->second )
     &&(strlen(key)              == strlen(Node->second))
    )
  {
   break;
  }
  else
  {
   ++ Node;
  }
 }

 if(Node ==  Perspective.Key.end())
 {
  return(nullptr);
 }
 else if(fellowNode == true)
 {
  return(Perspective.Focus[Node->first]->as_AssociationFellowship());
 }
 else
 {
  return(nullptr);
 }
}



#ifdef ASSOCIATIONMODEL_DEBUG
 template <class DataType, DataType* defaultData>
 void AssociationModel<DataType, defaultData>::outputSize(void)
 {
  cout << "AssociationModel : " << (int)this << endl;

//  cout << "size of sponsor : " << sizeof(AssociationSponsor<DataType*, defaultData>) << endl;
//  cout << Att.Sponsor.size() << " sponsors of maximal " << Att.Sponsor.max_size() <<endl;

  cout << "size of fellow  : " << sizeof(AssociationFellowship<DataType*, defaultData>) << endl;
  cout << Att.Fellow.size()<< " fellows of maximal " << Att.Fellow.max_size() << endl;

  cout << "size of data  : " << sizeof(DataType) << endl;
  cout << Att.Data.size()<< " data-objects of maximal " << Att.Data.max_size() << endl;

 }
#endif // ASSOCIATIONMODEL_DEBUG








#endif // ASS_MODEL_HPP

