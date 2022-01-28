/*!

 @file
 @brief store the result of a tiny parser classes

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
    07.02.2019     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    07.02.2019...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/
#include "TiPa_Result_Skip.h"




/* @MRTZ_describe TiPa_Result_Collector
  do not call the bas constructor but initialize everything in a specific way
*/
TiPa_Result_Skip::TiPa_Result_Skip(TiPa_Abstract*        owner,
                                   TiPa_Result_Abstract* sponsor)
                 :TiPa_Result(owner, sponsor)
{
// Att.Owner       = owner;
// Att.Sponsor     = sponsor->as_TiPa_Result();
// Att.Context     = new DataModel;
 Att.Destination = owner->as_TiPa_Concrete()->result_Dictionary();
}





/* @MRTZ_describe TiPa_Result_Skip

*/
TiPa_Result_Skip::TiPa_Result_Skip(void)
                 :TiPa_Result()

{
}

/* @MRTZ_describe TiPa_Result_Skip

*/
TiPa_Result_Skip::TiPa_Result_Skip(const TiPa_Result_Skip& original)
                 :TiPa_Result(original)
{
}



/* @MRTZ_describe operator=

*/
TiPa_Result_Skip& TiPa_Result_Skip::operator=(const TiPa_Result_Skip& original)
{
 TiPa_Result::Att = original.TiPa_Result::Att;
 return(*this);
}


/* @MRTZ_describe ~TiPa_Result_Skip

*/
TiPa_Result_Skip::~TiPa_Result_Skip(void)
{
}





/* @MRTZ_describe as_TiPa_Result_Collector
  return nullptr since class does not support cast-destination
*/
TiPa_Result_Collector* TiPa_Result_Skip::as_TiPa_Result_Collector(void)
{
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"TiPa_Result_Skip::as_TiPa_Result_Collector"<<endl;
 return(nullptr);
}

/* @MRTZ_describe as_TiPa_Result_Terminate
  return nullptr since class does not support cast-destination
*/
TiPa_Result_Terminate* TiPa_Result_Skip::as_TiPa_Result_Terminate(void)
{
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"TiPa_Result_Skip::as_TiPa_Result_Terminate"<<endl;
 return(nullptr);
}

/* @MRTZ_describe as_TiPa_Result_Skip
  return this since class supporty cast-destination
*/
TiPa_Result_Skip* TiPa_Result_Skip::as_TiPa_Result_Skip(void)
{
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"TiPa_Result_Skip::as_TiPa_Result_Skip"<<endl;
 return(this);
}









/* @MRTZ_describe storeDeep

*/
TiPa_Result_Skip::LastStorage_TP TiPa_Result_Skip::storeResult(CONST_CHAR_UNUSED* begin, CONST_CHAR_UNUSED* end)
{
  return(Att.Destination->end());
}


