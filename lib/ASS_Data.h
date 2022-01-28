/*!

 @file
 @brief abstract manager of tree_data

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
    08.08.2015     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    08.08.2015...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/

#ifndef ASS_DATA_H
#define ASS_DATA_H

#include <stdio.h>
#include <map>
#include <list>
#include <cstring>

using namespace std;





/*!
 @brief  abstract manager of tree_data

 this class describes an common interface between the data of a tree node and its
 node that is managing the tree-associations
*/
class AssociationData
{
 public:

/// @brief data-format for secondary data not decelerated by derived class
 typedef struct SecondaryData_TP
 {
  char* Key;  ///< identifier
  char* Val;  ///< value
 }SecondaryData_TP;



/*!
 @brief default constructor

 <br><br>

 @htmlinclude ./des/AssociationData_AssociationData.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    08.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 AssociationData(void);






/*!
 @brief default destructor

 <br><br>

 @htmlinclude ./des/AssociationData__AssociationData.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    08.08.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/

 virtual  ~AssociationData(void);


/*!
 @brief clear the secondary data
*/
 void init(void);



 /*!
 @brief convert a long integer number into a c-string

 @param [out] numberString   pointer of the c-string to return
 @param [in]  numberValue    number to convert

 @note in the case that the given string-pointer is not nullptr it will be
       assumed that the string already contains data what can be deleted
       to prepare a new fresh and empty string

 <br><br>
 @htmlinclude ./des/AssociationData_itoa.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    28.10.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
static void itoa(char** numberString, long numberValue);







/*!
 @brief return an xml compatible symbol for the given character

 @param [in] character   should be analysed and perhaps replaced

 @return character itself or xml-replacement


 <br><br>
 @htmlinclude ./des/AssociationData_char2xml.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    20.10.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  static const char* char2xml(char character);

/*!
 @brief convert into xml-compatible string
 replace in the given source string not xml compatible symbols by compatible one
 and return the result as the given destination string


 @param [in]  source        should be analysed for correction
 @param [out] destination   return value that has to be NULL

 @return character itself or xml-replacement


 <br><br>
 @htmlinclude ./des/AssociationData_string2xml.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    10.12.2015   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  static void string2xml(const char* source, char** destination);







/*!
 @brief add secondary text data that is not part of the specific core data

 @param [in] key  reference name used to identify the data
 @param [in] data text used to represent the data

 @return added data as new string (stored and maintained as secondary data)

 <br><br>
 @htmlinclude ./des/AssociationData_secondaryData_add.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    18.02.2017   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  const char* secondaryData_add(const char* key, const char* data);


/*!
 @brief add secondary integer data that is not part of the specific core data

 @param [in] key  reference name used to identify the data
 @param [in] data text used to represent the data

 @return added data as new string (stored and maintained as secondary data)

 <br><br>
 @htmlinclude ./des/AssociationData_secondaryData_add.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    18.02.2017   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  const char* secondaryData_add(const char* key, int data);

/*!
 @brief add secondary floating point data that is not part of the specific core data

 @param [in] key  reference name used to identify the data
 @param [in] data text used to represent the data

 @return added data as new string (stored and maintained as secondary data)

 <br><br>
 @htmlinclude ./des/AssociationData_secondaryData_add.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    18.02.2017   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  const char* secondaryData_add(const char* key, double data);



/*!
 @brief return secondary data that is not part of the specific core data

 @param [in] key  reference name used to identify the data
 @param [in] defaultData return value used if the searched data is not existing or not convertible

 @return text used to represent the data

 <br><br>
 @htmlinclude ./des/AssociationData_secondaryData_get.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    18.02.2017   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  const char* secondaryData_get(const char* key, const char* defaultData = "");


/*!
 @brief return secondary data that is not part of the specific core data

 @param [in] key         reference name used to identify the data
 @param [in] defaultData return value used if the searched data is not existing or not convertible

 @return numerical content if data could be transferred into an integer number
 <br>    given default value if the searched data is not existing or not convertible

 <br><br>
 @htmlinclude ./des/AssociationData_secondaryData_get.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    18.02.2017   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  int secondaryData_get(const char* key, int defaultData);


/*!
 @brief return secondary data that is not part of the specific core data

 @param [in] key         reference name used to identify the data
 @param [in] defaultData return value used if the searched data is not existing or not convertible

 @return numerical content if data could be transferred into an integer number
 <br>    given default value if the searched data is not existing or not convertible

 <br><br>
 @htmlinclude ./des/AssociationData_secondaryData_get.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    18.02.2017   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  double secondaryData_get(const char* key, double defaultData);



/*!
 @brief return the dictionary of secondary data that is not part of the specific core data

 @return text based dictionary used to represent the data

 <br><br>
 @htmlinclude ./des/AssociationData_secondaryData_get_2.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    18.02.2017   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 list<SecondaryData_TP*>* secondaryData_get(void);



/*!
 @brief check if data-pointer points to primary-data declared by concrete class

 If the concrete class implements string-pointers it may be that this strings have to be stored
 as secondary data even they are actually primary data. Once the data should be used this
 method could be used to differ between real secondary data and data that is already known by
 the concrete class.

 @return false if given data is no primary data just stored as secondary data
 <br>    true if given data is not used with a primary pointer of the concrete class

 <br><br>
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    09.04.2017   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
 virtual bool isRealSecondaryData(const char* data) =0;







/*!
 @brief return secondary data defined by the given key text

 @param [in] text  reference name used to identify the data

 @return  pointer used in the secondary data dictionary
 <br>    or nullptr if referenced data is not existing

 <br><br>
 @htmlinclude ./des/AssociationData_secondaryData_key.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    18.02.2017   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  SecondaryData_TP* secondaryData_key(const char* text);





/*!
 @brief return secondary data defined by the given data text

 @param [in] text data

 @return pointer used in the secondary data dictionary
 <br>    or nullptr if referenced data is not existing

 <br><br>
 @htmlinclude ./des/AssociationData_secondaryData_data.html
 @TabBegin
  <b>date</b>    @I <b>author</b> @I <b>cause</b> @I <b>change</b>
 @I_______________________________________________________
    18.02.2017   @I  Eckard Klotz
 @I base-design
 @I first implementation
 @I_______________________________________________________
                 @I               @I              @I
 @TabEnd
*/
  SecondaryData_TP* secondaryData_data(const char* text);






/*!
 @brief copy a given string to an attribute

 @param destination  attribute to define
 @param source       string to copy

 @return number as string

 @htmlinclude ./des/TiPa_Data_copyString.html
*/
void copyString(char** destination, const char* source);







//#define SORT_SECONDARY_DATA

#ifdef SORT_SECONDARY_DATA
   list<char*>       Keys;
#endif

 protected:




 private:




 /*!
  @brief data added while using and analysing the specific core data
 */
  struct SecondaryData
  {
   list<SecondaryData_TP*>Dictionary;

   SecondaryData(){};

   SecondaryData(const SecondaryData& source)
   {
    list<SecondaryData_TP*>::const_iterator Source = source.Dictionary.begin();
    while(Source != source.Dictionary.end())       // iterate over given data dictionary
    {
     SecondaryData_TP* Data = new SecondaryData_TP;

     int Size  = strlen((*Source)->Key);           // size of key to copy
     Data->Key = new char[Size+1];                 // create fresh key
     memcpy(Data->Key,(*Source)->Key,Size);        // set up content
     Data->Key[Size] = 0;                          // ensure string termination

         Size  = strlen((*Source)->Val);           // size of data to copy
     Data->Val = new char[Size+1];                 // create new data location
     memcpy(Data->Val,(*Source)->Val,Size);        // set up content
     Data->Val[Size] = 0;                          // ensure string termination

     Dictionary.push_back(Data);                   // insert new entry

     ++ Source;
    }
   };

   const SecondaryData& operator = (const SecondaryData& source)
   {
    list<SecondaryData_TP*>::const_iterator Source = source.Dictionary.begin();
    while(Source != source.Dictionary.end())       // iterate over given data dictionary
    {
     SecondaryData_TP* Data = new SecondaryData_TP;

     int Size  = strlen((*Source)->Key);           // size of key to copy
     Data->Key = new char[Size+1];                 // create fresh key
     memcpy(Data->Key,(*Source)->Key,Size);        // set up content
     Data->Key[Size] = 0;                          // ensure string termination

         Size  = strlen((*Source)->Val);           // size of data to copy
     Data->Val = new char[Size+1];                 // create new data location
     memcpy(Data->Val,(*Source)->Val,Size);        // set up content
     Data->Val[Size] = 0;                          // ensure string termination

     Dictionary.push_back(Data);                   // insert new entry

     ++ Source;
    }
    return(*this);
   };

   ~SecondaryData()
   {
    list<SecondaryData_TP*>::iterator Source = Dictionary.begin();
    while(Source != Dictionary.end())   //iterate over given data dictionary
    {
     delete[]((*Source)->Key);
     delete[]((*Source)->Val);
     ++ Source;
    }
    Dictionary.clear();
   }

  }SecondaryData;

};





#endif // ASS_DATA_H
