/*!
 @file
 @brief grammar used to parse xml replacement-definitions used with configuration-files

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
    02.03.2019     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    02.03.2019...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/
#ifndef XML_REPLACE_GRM_H
 #define XML_REPLACE_GRM_H

#include "TDA_GrmConcrete.h"
#include "Debug_Reaction.h"





class XML_Replace_Grm:public TDA_GrmConcrete
{
 public:

/*!
  initializing constructor

 @htmlinclude ./des/XML_Replace_Grm_XML_Replace_Grm.html
*/
 explicit XML_Replace_Grm(TiPa_Concrete::DataModel* contextModel);

/*!
  destructor

 @htmlinclude ./des/XML_Replace_Grm__XML_Replace_Grm.html
*/
  ~XML_Replace_Grm(void);




/*!
 test the given string described with its begin and end to
 decide if it starts with a construction defined by the parser,
 a hit will be stored inside the parser and reused to save time.

 @param [in] begin points to the first character of the given string
 @param [in] end   points behind the last  character of the given string
 @param [in] rule  name of the rule if not the main-parser rule should be used

 @return a pointer directly behind the found match if the given string starts
         with the construction defined by the parser.
 @return nullptr if the given string starts not
         with the construction defined by the parser

 @htmlinclude ./des/XML_Replace_Grm_parse.html

*/
const char * parse(const char* begin, const char* end, const char* rule = nullptr) override;




 /*!
 test the given string described with its begin and end to
 decide if it contains one or more constructions defined by the parser,
 all hits will be stored inside the parser and reused to save time.

 @param  begin points to the first character of the given string
         <br> once the first fitting part-string was found this parameter points
              to its first character
 @param [in] end   points behind the last character of the given string
 @param [in] rule  name of the rule if not the main-parser rule should be used

 @return a value behind the given <b>begin</b>  and before the given <b>end</b> that
         points directly to the last part of the given string that hits the
         construction of the parser.
 @return the value of the given <b>end</b> if the given string contains no
         with the construction defined by the parser
 @return nullptr in the case of an error or special event

 @htmlinclude ./des/XML_Replace_Grm_scan.html


*/
const char * scan(const char* begin, const char* end, const char* rule = nullptr);





/*!
 @brief return a reduced tree containing only simple xml data

 @param node xml-root node with more complex content

 @return root-node of a new tree with reduced content


 @htmlinclude ./des/XML_Replace_Grm_filter_simple.html
*/
TiPa_Concrete::DataFellow* filter_simple(TiPa_Concrete::DataFellow* node);




 protected:

 private:
/*!
  default constructor forbidden to use

 @htmlinclude ./des/XML_Replace_Grm_XML_Replace_Grm.html
*/
  XML_Replace_Grm(void);



//   [?(#Configuration/UserArgument/RootPath)!({value})]


/*!
    name =  (     ( range_p('a','z') | range_p('A','Z')                      | '_' )
             >>  *( range_p('a','z') | range_p('A','Z') |  range_p('0','9')  | '_' )
            );

 @htmlinclude ./des/XML_Replace_Grm_defineRules_Name.html
*/
 void defineRules_Name(void);


/*!
    path = +((up | here | name) >> "/");
    up   = ".." ;
    here = ".";

 @htmlinclude ./des/XML_Replace_Grm_defineRules_Path.html
*/
 void defineRules_Path(void);



/*!

    xmlPath = !"%/" >> !path >> node;
    node    = name

 @htmlinclude ./des/XML_Replace_Grm_defineRules_PathXML.html
*/
 void defineRules_PathXML(void);



/*!
    filePath = !volume >> !path >> file;

    volume    = character >> ":/" ;
    character = range_p('a','z') | range_p('A','Z');

    file      = name >> "." >> name;

 @htmlinclude ./des/XML_Replace_Grm_defineRules_PathFile.html
*/
 void defineRules_PathFile(void);



/*!
    data      = "!(" >> (attribute | text ) >> ")";
    attribute = "{" >> name >> "}" ;
    text      = "{" >> "-TEXT-" >> "}" ;

 @htmlinclude ./des/XML_Replace_Grm_defineRules_Data.html
*/
 void defineRules_Data(void);



/*!

    search  = "?(" >> location >> ")";

    location = !filePath >> "#" >> xmlPath ;

 @htmlinclude ./des/XML_Replace_Grm_defineRules_Search.html
*/
 void defineRules_Search(void);



/*!
    replacement = "[" >> search >> data >> "]";

 @htmlinclude ./des/XML_Replace_Grm_defineRules_Replacement.html
*/
 void defineRules_Replacement(void);


/*!


 @htmlinclude ./des/XML_Replace_Grm_defineRules_RawText.html
*/
void defineRules_RawText(void);

/*!


 @htmlinclude ./des/XML_Replace_Grm_defineMainParser.html
*/
void defineMainParser(void);




void skipNonRuleResults(void);

  struct ID
  {
    int Character{0};
    int String{300};
    int Counter{600};
    int Condition{1000};
    int Sequence{2000};
    int Rule{5000};

    /// @brief default initialization
    ID(void):
        Character(0),
        String(300),
        Counter(600),
        Condition(1000),
        Sequence(2000),
        Rule(5000)
        {};

    ID( const ID& id):
     Character(id.Character),
     String   (id.String   ),
     Counter  (id.Counter  ),
     Condition(id.Condition),
     Sequence (id.Sequence ),
     Rule     (id.Rule     ){};


    ID& operator=( const ID& id)
    {
     Character = id.Character;
     String    = id.String   ;
     Counter   = id.Counter  ;
     Condition = id.Condition;
     Sequence  = id.Sequence ;
     Rule      = id.Rule     ;
     return(*this);
    };

    ~ID(void){};

  }ID;

  Debug_Reaction      DebugReaction;



};














#endif // XML_REPLACE_GRM_H
