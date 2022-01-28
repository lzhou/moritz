/*!

 @file
 @brief concrete reaction-class for a parser-hit event to create debug-outputs


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
    15.10.2017     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    15.10.2017...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/

#ifndef DEBUG_REACTION
  #define DEBUG_REACTION

#include "TiPa_Reaction_Concrete.h"
#include "TDA_GrmConcrete.h"



/// @brief concrete reaction-class for a parser-hit event to create debug-outputs
class Debug_Reaction : public TiPa_Reaction_Concrete
{
 public:
/*!
  @brief default constructor

 @htmlinclude ./des/Debug_Reaction_Debug_Reaction.html
*/
 Debug_Reaction(void);




/*!
  @brief copy constructor

  @param [in] debug_Reaction object to copy

  @htmlinclude ./des/Debug_Reaction_Debug_Reaction.html
*/
 explicit Debug_Reaction(const Debug_Reaction& debug_Reaction);




/*!
  @brief assignment operator=

  @param [in] debug_Reaction object to assign

  @htmlinclude ./des/Debug_Reaction_operator=.html

*/
Debug_Reaction& operator= (const Debug_Reaction& debug_Reaction);





/*!
 @brief destructor

 @htmlinclude ./des/Debug_Reaction__Debug_Reaction.html
*/
 ~Debug_Reaction(void);


/*!
 @brief set parser property data-base

 @param property [in] data-base used to store normal data around a parser

 @htmlinclude ./des/Debug_Reaction_setProperty.html
*/
 void setProperty(map<TiPa_Concrete*, TDA_GrmConcrete::Property_TP>* property);


/*!
 @brief process a parser hit

 @param data [in] data associated with the parser hit-event

 @htmlinclude ./des/Debug_Reaction_processHit.html
*/
 virtual void processHit(TiPa_Abstract* owner, TiPa_Result::Data_TP& data) override;



 protected:


 private:


  map<TiPa_Concrete*, TDA_GrmConcrete::Property_TP>*  Property{nullptr};          ///< data-base used to store normal data around a parser




};



#endif // DEBUG_REACTION

