/*!

 @file
 @brief concrete manager of tree_data
        representing the data of a grammar associated parser-tree

 Copyright (C) 2015-2020 by Eckard Klotz.

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
    03.07.2016     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    03.07.2016...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/

#ifndef SPIRIT185_DATA_H
#define SPIRIT185_DATA_H

#include "ASS_Data.h"

#include "TiPa_Data.h"
#include "Association.h"

//#include "TiPa_Concrete.h"
#include "TiPa_Abstract.h"

#include <list>
#include <map>


using namespace std;


#ifndef DOXYGEN
//namespace TXTDIASM {
//namespace TDA_Grammar {
//namespace DATA {
#endif //DOXYGEN

//#define IGNORE_UNUSED __attribute__ ((unused))

/// @ingroup UNUSED_DATA
/// @brief avoid compiler warning since the object is not used
/// @{
#define CONST_CHAR_UNUSED __attribute__ ((unused)) const char
/// @}



/*!
 concrete manager of tree_data representing grammar-results

 this class describes the concrete data content and provides specific
 analysis methods used by the tree-node for actions like filtering
*/
class Spirit185_Data:public AssociationData
{

 public:


/// property of a single parser which describe the meaning of the parser
/// for the whole grammar


  typedef struct ParserAttribute_TP
  {
   const char* Identifier = nullptr; ///< name of the attribute
   const char* Value      = nullptr;      ///< content of the attribute


   /// @brief default constructor
   ParserAttribute_TP(void):
    Identifier(nullptr),
    Value     (nullptr)
   {};

   /*!
    @brief copy constructor
    @param [in] src object to copy
   */
   ParserAttribute_TP(const ParserAttribute_TP& src):
    Identifier(src.Identifier),
    Value     (src.Value     )
   {};
   /*!
    @brief assignment operator
    @param [in] src object to copy
    @return copied object
   */
   ParserAttribute_TP& operator = (const ParserAttribute_TP& src)
   {
    Identifier = src.Identifier;
    Value      = src.Value     ;
    return(*this);
   };
   /// @brief destructor
   ~ParserAttribute_TP(void)
   {
   };

  }ParserAttribute_TP;



 typedef Association<Spirit185_Data*, nullptr> Spirit185_DataAssociation;
 typedef Association<TiPa_Data*, nullptr>     TiPa_DataAssociation;




// static Spirit185_Data* Cast(AssociationData* data);

/*!
 default constructor

 <br><br>

 @htmlinclude ./des/Spirit185_Data_Spirit185_Data.html
 .html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    03.07.2016   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
    Spirit185_Data(void);




/*!
 @brief copy constructor

 @param [in] data object to copy

 @htmlinclude ./des/XML_Data_XML_Data.html
*/
 explicit Spirit185_Data(Spirit185_Data& data);





/*!
 destructor

 <br><br>

 @htmlinclude ./des/Spirit185_Data__Spirit185_Data.html
 .html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    03.07.2016   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
   ~Spirit185_Data(void);





/*!
  @brief assignment operator

  @param [in] data object to assign

*/
Spirit185_Data& operator= (Spirit185_Data& data);





/*!
 @brief check if data-pointer points to primary-data declared by concrete class

 If the concrete class implements string-pointers it may be that this strings have to be stored
 as secondary data even they are actually primary data. Once the data should be used this
 method could be used to differ between real secondary data and data that is already known by
 the concrete class.

 @return false if given data is no primary data just stored as secondary data
 <br>    true if given data is not used with a primary pointer of the concrete class

 <br><br>
 @htmlinclude ./des/Spirit185_Data_isRealSecondaryData.html
 @I_______________________________________________________
    09.04.2017   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
bool isRealSecondaryData(CONST_CHAR_UNUSED* data) override;







   typedef enum Attributes
   {
    attName        ,
    attValue       ,
    attValue1      ,
    attValue2      ,
    attUsing       ,
    attUsedBy      ,
    attLeafLevel   ,
    attRootLevel   ,
    attPhrased     ,
    attV           ,
    attC           ,
 //   attUserID          = 1,
 //   attUserDescription = 2,
 //   attLine            = 3,
 //   attColumn          = 4,
   }
   Attributes;


  // Association<TiPa_Data*>*            SourceData;              ///< original node-Data extended by this
   TiPa_DataAssociation*            SourceData{nullptr};        ///< original node-Data extended by this

   set<Spirit185_DataAssociation*>  CalledRule{};              ///< nodes used by this one
   set<Spirit185_DataAssociation*>  CallingRule{};             ///< nodes which use this one

   list<Spirit185_DataAssociation*> UsingTerminated{};         ///< nodes used by this one
   list<Spirit185_DataAssociation*> UsedByTerminated{};        ///< nodes which use this one
   list<Spirit185_DataAssociation*> UsingRecursive{};          ///< nodes used by this one
   list<Spirit185_DataAssociation*> UsedByRecursive{};         ///< nodes which use this one
   map <int, const char*>           Detail{};                  ///< detailed data found while analysis

   int                              LevelRoot{0};               ///< maximum number of terminated nested contractor-nodes
   int                              LevelLeaf{0};               ///< maximum number of  sponsor-nodes

   bool                             Phrased{true};              ///< white-space characters will be ignored if rule is phrased



 protected:
 private:




/*
 struct Constant
 {
 }Constant;
*/

};



#ifndef DOXYGEN
#define USING_NAMESPACE using namespace
//}; USING_NAMESPACE DATA;
//}; USING_NAMESPACE TDA_Grammar;
//}; USING_NAMESPACE TXTDIASM;
#undef  USING_NAMESPACE
#endif //DOXYGEN


#endif // SPIRIT185_DATA_H
