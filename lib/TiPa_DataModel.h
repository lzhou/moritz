/*!

 @file
 @brief central manager-class of parser-data and its associations

 Copyright (C) 2017-2020 by Eckard Klotz.

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
    15.07.2017     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    15.07.2017...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/
#ifndef TIPA_DATAMODEL_H
#define TIPA_DATAMODEL_H

#include "ASS_Model.h"
#include "TiPa_Data.h"



/*!
 @brief central manager-class of parser-data and its associations
*/
class TiPa_DataModel : public AssociationModel<TiPa_Data,nullptr>
{
 public:

/*!
 @brief default constructor
*/
  TiPa_DataModel(void);

/*!
 @brief default destructor
*/
  ~TiPa_DataModel(void);

 protected:

 private:

};



#endif // TIPA_DATAMODEL_H

