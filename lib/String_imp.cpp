/*!

 @file
 @brief implementation of a string-class

 First I started with the string-class of wxWidgets. But then I decided to
 design the tool moritz as terminal- or shell- application. So I also decided to
 use only standard libs of c/c++. But I wanted also be able to use othe libs
 again. <br>
 This file provides a generic definition of a string-type and functions or
 methods to deal with it.
 <br><br>
 At the moment it contains only a definition as standard-string of c++ and there
 are a lot of todo's to implement a real bridge-pattern to use several
 string-types;

 Copyright (C) 2004-2020 by Eckard Klotz.

 Permission to use, copy, modify, and distribute this software and its
 documentation under the terms of the GNU General Public License is hereby
 granted. No representations are made about the suitability of this software
 for any purpose. It is provided "as is" without express or implied warranty.
 See the GNU General Public License for more details.

 Documents produced by Moritz are derivative works derived from the
 input used in their production; they are not affected by this license.

 <b> History </b>

 @TabBegin
    date           @I author          @I implementation/change
 @I____________________________________________________________
    2004-05.2005   @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    06.2006 -      @I Eckard Klotz
 @I Changes are documented in the comment of the changed element
 @TabEnd

*/



#include "String_imp.h"




#ifdef ORIGINAL_STRING



// ***************************************************************************** /
// ***************************************************************************** /
// ***************************************************************************** /
#else //ORIGINAL_STRING


#endif //ORIGINAL_STRING

#ifndef DOXYGEN
 //namespace F_STRING_IMP{
#endif //DOXYGEN

/* @MRTZ_describe lowCaseString

*/
 String_imp lowCaseString(String_imp text)
 {
  String_imp ReturnValue = "";
  size_t     Index       =0;

  for(Index = 0; Index < text.size() ; Index++)
   ReturnValue.append(1,(char)tolower(text.at(Index)));

  return(ReturnValue);
 }



/* @MRTZ_describe replacePartString

   @MRTZ_describe mask_oldParts

*/
 String_imp replacePartString(const String_imp& text,
                              const String_imp& oldPart,
                              const String_imp& newPart,
                              bool              ReplaceInNewPart)
 {
//  String_imp ReturnValue = "";
//  ReturnValue = text;
  String_imp ReturnValue = text;
  String_imp TemporaryReplacement = "@_@";


  if(  (oldPart != "")
     &&(oldPart != newPart)
     &&(ReturnValue.find(oldPart) < ReturnValue.size())
    )
    //old part is not empty and not the same as the new part and part of the main-string
  {
   String_imp OldPart = oldPart;
   if(!ReplaceInNewPart)
   {
// @MRTZ_exclude mask_oldParts
// @MRTZ_beginBlock
    while(  (ReturnValue.find(TemporaryReplacement) < ReturnValue.size())
          ||(newPart.find(TemporaryReplacement)     < newPart.size())
         )//temporary replacement is part of main- or new string
    {
     TemporaryReplacement[0]=TemporaryReplacement[0]+1;
     TemporaryReplacement[1]=TemporaryReplacement[1]+1;
     TemporaryReplacement[2]=TemporaryReplacement[2]+1;
    }
    TemporaryReplacement = TemporaryReplacement + TemporaryReplacement;
    ReturnValue=replacePartString(ReturnValue, OldPart,TemporaryReplacement); //temporary replacement
    OldPart = TemporaryReplacement;
// @MRTZ_endBlock
   }


   if(newPart.size()>OldPart.size())
    ReturnValue.reserve(ReturnValue.size()+(5*(newPart.size()-OldPart.size())));
    // allocate the needed place in one step


   while(ReturnValue.find(OldPart) < ReturnValue.size())
                                       //as long as the old part will be found
   {
#if defined(DEBUG_OUTPUT)
    printf("Text: \n %s\n Old: \n %s\n New: \n %s\n",
             ReturnValue.c_str(),OldPart.c_str(),newPart.c_str());
#endif
    ReturnValue.replace(ReturnValue.find(OldPart),OldPart.size(),newPart);
   };

#if defined(DEBUG_OUTPUT)
   printf("Text: \n %s\n Old: \n %s\n New: \n %s\n",
           ReturnValue.c_str(),OldPart.c_str(),newPart.c_str());
#endif
  }
#if defined(DEBUG_BREAK)
   system("PAUSE");
#endif

  return(ReturnValue);
 }



/* @MRTZ_describe numberToString

*/
String_imp numberToString(long number)
{
// String_imp ReturnValue = "";

 ostringstream  Con_Num2Str ;
 Con_Num2Str << number;
 String_imp ReturnValue = Con_Num2Str.str();

 return(ReturnValue);
}



/*String_imp newLine(String_imp text)
{
 static String_imp ReturnValue = "";

 if(ReturnValue == "")
 {
  //@MRTZ_ifElseChain
  if     (text.find("\r\n") < text.size())
  {
   ReturnValue = "\n";
  }
  else if(text.find("\n\r") < text.size())
  {
   ReturnValue = "\n\r";
  }
  else if(text.find("\r")   < text.size())
  {
   ReturnValue = "\r";
  }
  else if(text.find("\n")   < text.size())
  {
    ReturnValue = "\n";
  }
  else
  {
  }

 }
 return(ReturnValue);
}
*/

/* @MRTZ_describe newLine

*/
String_imp newLine(void)
{
// String_imp ReturnValue = "";
 ostringstream  NewLineSymbol ;

 NewLineSymbol << endl;
 String_imp ReturnValue = NewLineSymbol.str();

 return(ReturnValue);
 }











/* @MRTZ_describe stringToNumber

*/
long stringToNumber(String_imp number)
 {
  long ReturnValue = 0 ;
  istringstream  Con_Str2Num(number);

  Con_Str2Num >> ReturnValue;

  return(ReturnValue);
 }





/* @MRTZ_describe stringToSet

   @MRTZ_describe split_text

   @MRTZ_describe search_for_next_splitter

   @MRTZ_describe delete_invalid_characters

*/
set<String_imp> stringToSet(String_imp text, char separator)
{
 set<String_imp> ReturnValue;

 if(text != "")
 {
//  String_imp Name      = "";
  size_t     Iterator  = 0;
  char       Character = 0x00;                  // single character in given text
  size_t     Pos0      = 0;

// @MRTZ_exclude split_text
    while(Iterator  <  (text.size()-1)
         )                                      // until begin of tag name found or end of given text
    {
// @MRTZ_exclude search_for_next_splitter
     while(  (Character != separator )
           &&(Iterator  <  (text.size()-1))
          )                                     // until begin of tag name found or end of given text
     {
      Iterator ++;                              // increment given character-index
#if defined(DEBUG_OUTPUT)
      printf("Getchar 1 starten \n");
#endif //DEBUG_OUTPUT
      Character = text.at(Iterator);            // read next character
#if defined(DEBUG_OUTPUT)
      printf("Getchar 1 fertig \n");
#endif //DEBUG_OUTPUT
     };
     size_t Length = Iterator - Pos0;
     if(Iterator == (text.size()-1))            // no comma found but last character
      Length ++;
     String_imp Name = text.substr(Pos0, Length);
// @MRTZ_exclude delete_invalid_characters
// @MRTZ_beginBlock
     Name = replacePartString(Name," ","");     // delete space
     Name = replacePartString(Name,"\t","");    // delete tab
     Name = replacePartString(Name,"\r","");    // delete return
     Name = replacePartString(Name,"\n","");    // delete newline
     Name = replacePartString(Name,",", "");    // delete comma
// @MRTZ_endBlock

     if(  (Name != "")
        &&(ReturnValue.find(Name)==ReturnValue.end())
        )
      ReturnValue.insert(Name);
#if defined(DEBUG_OUTPUT)
        cout << "add " << Name << " to ReturnValue" << endl;
#endif //DEBUG_OUTPUT
     Iterator ++;                               // increment current index behind comma
     Pos0 = Iterator;                           // first-index of new name
     if(Iterator  <  (text.size()-1))
      Character = text.at(Iterator);            // read next character
    }
 }
 return(ReturnValue);
}


/* @MRTZ_describe stringToList

   @MRTZ_describe split_text

   @MRTZ_describe search_for_next_splitter

   @MRTZ_describe delete_invalid_characters

*/
list<String_imp> stringToList(String_imp text, char separator)
{
 list<String_imp> ReturnValue;

 if(text != "")
 {
//  String_imp Name      = "";
  size_t     Iterator  = 0;
  char       Character = 0x00;                // single character in given text
  size_t     Pos0      = 0;

// @MRTZ_exclude split_text
    while(Iterator  <  (text.size()-1)
         )                                    // until begin of tag name found or end of given text
    {
// @MRTZ_exclude search_for_next_splitter
     while(  (Character != separator )
           &&(Iterator  <  (text.size()-1))
          )                                   // until begin of tag name found or end of given text
     {
      Iterator ++;                            // increment given character-index
#if defined(DEBUG_OUTPUT)
      printf("Getchar 1 starten \n");
#endif //DEBUG_OUTPUT
      Character = text.at(Iterator);          // read next character
#if defined(DEBUG_OUTPUT)
      printf("Getchar 1 fertig \n");
#endif //DEBUG_OUTPUT
     };
     size_t Length = Iterator - Pos0;
     if(  (Iterator  == (text.size()-1))
        &&(Character != separator ))          // no comma found but last character
      Length ++;
     String_imp Name = text.substr(Pos0, Length);
// @MRTZ_exclude delete_invalid_characters
// @MRTZ_beginBlock
     Name = replacePartString(Name," ","");   // delete space
     Name = replacePartString(Name,"\t","");  // delete tab
     Name = replacePartString(Name,"\r","");  // delete return
     Name = replacePartString(Name,"\n","");  // delete newline
     Name = replacePartString(Name,",", "");  // delete comma
// @MRTZ_endBlock

     if( Name != "")
      ReturnValue.push_back(Name);
#if defined(DEBUG_OUTPUT)
        cout << "add " << Name << " to ReturnValue" << endl;
#endif //DEBUG_OUTPUT
     Iterator ++;                             //increment current index behind comma
     Pos0 = Iterator;                         //first-index of new name
     if(Iterator  <  (text.size()-1))
      Character = text.at(Iterator);          //read next character
    }
   }
 return(ReturnValue);
}



// With C++20 you can use std::string::starts_with().
bool starts_with ( const std::string& str, const std::string& pre )
{
    std::size_t i = 0;
    for ( ; i < str.size() && i < pre.size(); ++i )
        if ( str[i] != pre[i] )
            return false;
    return i == pre.size();
}



#ifndef DOXYGEN
//};
#endif //DOXYGEN



