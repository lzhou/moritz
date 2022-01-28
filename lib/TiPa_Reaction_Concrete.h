/*!

 @file
 @brief concrete reaction-class for a parser event


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
    14.10.2017     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    14.10.2017...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/

#ifndef TIPA_REACTION_CONCRETE
  #define TIPA_REACTION_CONCRETE

#include "TiPa_Reaction_Abstract.h"



/// @brief concrete reaction-class for a parser event
class TiPa_Reaction_Concrete : public TiPa_Reaction_Abstract
{
 public:
/*!
  @brief default constructor

 @htmlinclude ./des/TiPa_Reaction_Concrete_TiPa_Reaction_Concrete.html
*/
 TiPa_Reaction_Concrete(void);

/*!
 @brief destructor

 @htmlinclude ./des/TiPa_Reaction_Concrete__TiPa_Reaction_Concrete.html
*/
 ~TiPa_Reaction_Concrete(void);




/*!
 @brief cast this object to an object of the type TiPa_Reaction_Concrete


 @return a pointer to a real existing object if conversion is possible
 @return nullptr if object could not be converted

 @htmlinclude ./des/TiPa_Reaction_Concrete_asTiPa_Reaction_Concrete.html
*/
 virtual TiPa_Reaction_Concrete* asTiPa_Reaction_Concrete(void) override;




/*!
 @brief process a parser hit

 @param data [in] data associated with the parser hit-event

 @htmlinclude ./des/TiPa_Reaction_Concrete_processHit.html
*/
 virtual void processHit(TiPa_Abstract* owner, TiPa_Result::Data_TP& data)override =0 ;


 protected:


 private:

};



#endif // TIPA_REACTION_CONCRETE

