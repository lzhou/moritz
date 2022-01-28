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
#include "TiPa_Result_Abstract.h"


/* @MRTZ_describe TiPa_Result

*/
TiPa_Result_Abstract::TiPa_Result_Abstract(void)
{
}



/* @MRTZ_describe ~TiPa_Result

*/
TiPa_Result_Abstract::~TiPa_Result_Abstract(void)
{
}

/* @MRTZ_describe
  return nullptr since class does not support cast-destination
*/
TiPa_Result* TiPa_Result_Abstract::as_TiPa_Result(void)
{
 return(nullptr);
}

/* @MRTZ_describe as_TiPa_Result_Collector
  return nullptr since class does not support cast-destination
*/
TiPa_Result_Collector* TiPa_Result_Abstract::as_TiPa_Result_Collector(void)
{
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"TiPa_Result_Abstract::as_TiPa_Result_Collector"<<endl;
 return(nullptr);
}

/* @MRTZ_describe as_TiPa_Result_Terminate
  return nullptr since class does not support cast-destination
*/
TiPa_Result_Terminate* TiPa_Result_Abstract::as_TiPa_Result_Terminate(void)
{
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"TiPa_Result_Abstract::as_TiPa_Result_Terminate"<<endl;
 return(nullptr);
}

/* @MRTZ_describe as_TiPa_Result_Skip
  return nullptr since class does not support cast-destination
*/
TiPa_Result_Skip*      TiPa_Result_Abstract::as_TiPa_Result_Skip(void)
{
//cout<<__FILE__<<":"<<__LINE__<<":0: "<<"TiPa_Result_Abstract::as_TiPa_Result_Skip"<<endl;
 return(nullptr);
}
