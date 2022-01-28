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
    18.11.2017     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    18.11.2017...  @I Eckard Klotz
 @I changes are documented in the comment of the changed element
 @TabEnd

*/
#include "xml_DataModel.h"

//#include "AssociationSponsor.hpp"
#include "AssociationFellowship.hpp"

#include "xml_Parser.h"

#include <fstream>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <ctime>

#include "Spirit185_Store.h"



/* @MRTZ_describe XML_DataModel

*/
XML_DataModel::XML_DataModel(void)
{

}

/* @MRTZ_describe XML_DataModel

*/
XML_DataModel::XML_DataModel(const char* srcPath)
{
  load(srcPath);
}



/* @MRTZ_describe ~XML_DataModel

*/
XML_DataModel::~XML_DataModel(void)
{
}

/* @MRTZ_describe load

*/
bool XML_DataModel::load(const char* srcPath)
{
 bool ReturnValue = false;

 if(srcPath != nullptr)
 {
#if defined(DEBUG_OUTPUT)
  cout << "load file"  << endl; ;
  clock_t Time = clock()/CLOCKS_PER_SEC;
#endif
  const char* Text = readTextFile(srcPath);
#if defined(DEBUG_OUTPUT)
  cout << ((clock()/CLOCKS_PER_SEC)-Time) << " sec  : ";
  Time = clock()/CLOCKS_PER_SEC;
  cout << "file loaded"  << endl;
#endif


  ReturnValue = parse(Text, srcPath);
  delete[](Text);
 }

 return(ReturnValue);
}



/* @MRTZ_describe parse

*/
bool XML_DataModel::parse(const char* text, const char* rootContent)
{
 bool ReturnValue = false;

 if (text != nullptr)
 {
#if defined(DEBUG_OUTPUT)
  clock_t Time = clock()/CLOCKS_PER_SEC;
#endif
  TiPa_Concrete::DataModel SourceModel;
  XML_Parser Source(& SourceModel);

  const char* EndOffResult = Source.parse(text,text+strlen(text));

#if defined(DEBUG_OUTPUT)
  cout << ((clock()/CLOCKS_PER_SEC)-Time) << " sec  : ";
  Time = clock()/CLOCKS_PER_SEC;
  cout << "parser ready : " ;
  cout << strlen(text) << "|" << EndOffResult-text << endl;
#endif


// cout<<__FILE__<<":"<<__LINE__<<":0: XML_DataModel::parse" << endl;
//  TiPa_Concrete::DataFellow* SourceTree = Source.treeData(text,nullptr);
// cout<<__FILE__<<":"<<__LINE__<<":0: XML_DataModel::parse" << endl;
//
//#if defined(DEBUG_OUTPUT)
//  cout << ((clock()/CLOCKS_PER_SEC)-Time) << " sec  : ";
//  Time = clock()/CLOCKS_PER_SEC;
//  cout << "tree ready : " ;
//#endif

  if(  /*(text         != nullptr)
     &&*/(EndOffResult != nullptr)
    )
  {
#if defined(DEBUG_OUTPUT)
  cout << "start filtering." << endl;
#endif
  TiPa_Concrete::DataFellow*  ReducedTree = Source.filter_simple_XML(text);
#if defined(DEBUG_OUTPUT)
  cout << ((clock()/CLOCKS_PER_SEC)-Time) << " sec  : ";
  Time = clock()/CLOCKS_PER_SEC;
  cout << "tree ready : " ;
#endif
  if(rootContent != nullptr)
  {
   ReducedTree->data_get()->Begin = rootContent;
   ReducedTree->data_get()->End   = ReducedTree->data_get()->Begin +strlen(rootContent);
  }
  else
  {
   ReducedTree->data_get()->Begin = text;
   ReducedTree->data_get()->End   = ReducedTree->data_get()->Begin + strlen(text);
  }

#if defined(DEBUG_OUTPUT)
  cout << ((clock()/CLOCKS_PER_SEC)-Time) << " sec  : ";
  Time = clock()/CLOCKS_PER_SEC;
  cout << "filtering done" << endl;
#endif

#if defined(DEBUG_OUTPUT)
   Spirit185_Store ResultStore;
   char*           ParsedText = nullptr;    // xml-text
   ReducedTree->welcome(ResultStore(Spirit185_Store::Content2XML,&ParsedText),IterateDownwards);
   cout << ParsedText << endl;
   delete[]ParsedText;
#endif

   XML_Load SourceDocument;
   SourceDocument.contextModel_set(this);
   while(this->focus_Fellow()->contractorFirst_get() != nullptr)
   {
    this->focus_Fellow()->contractorFirst_cut();
   }

   ReducedTree->welcome(SourceDocument( this->focus_Fellow(),ReducedTree),IterateDownwards);

#if defined(DEBUG_OUTPUT)
   cout << ((clock()/CLOCKS_PER_SEC)-Time) << " sec  : " ;
   Time = clock()/CLOCKS_PER_SEC;//   if(  (strstr(rootContent,".\\.\\xml\\samples_cpp.xml") == rootContent)
   cout << "xml-tree created" << endl;
#endif

   ReturnValue = true;
   LOG_OUTPUT(LOG_ON,"...................... Source Tree created ...................");
  }
  else
  {
  cout << "parsing failed" << endl;

   LOG_OUTPUT(LOG_ON,"!!!!!!!!!!!!!!!!!!!!No Source Tree created!!!!!!!!!!!!!!!!!!!!");
  }

  Source.TDA_GrmConcrete::init();
  SourceModel.init();
//  cout << "Parser End: SourceModel.outputSize()" ;
//  SourceModel.outputSize();
//  cout << endl;

#if defined(DEBUG_OUTPUT)
  cout << ((clock()/CLOCKS_PER_SEC)-Time) << " sec  : ";
  Time = clock()/CLOCKS_PER_SEC;
  cout << "TDA_GrmConcrete reinitialized : " ;
  cout << strlen(text) << "|" << EndOffResult-text << endl;
#endif

 }
 return(ReturnValue);
}













/* @MRTZ_describe save

*/
bool XML_DataModel::save(const char* dstPath, XML_Node childNode)
{
 bool ReturnValue = false;

 XML_Save OutputGenerator;

 char*  Text = nullptr;    // xml-text

#if defined(DEBUG_OUTPUT)
// clock_t Time = clock()/CLOCKS_PER_SEC;
#endif

 if(childNode.valid() == false)
  this->focus_Fellow()->welcome(OutputGenerator(&Text),IterateDownwards);
 else
  childNode.associationNodeGet()->welcome(OutputGenerator(&Text),IterateDownwards);

#if defined(DEBUG_OUTPUT)
// cout << ((clock()/CLOCKS_PER_SEC)-Time) << " sec  : ";
// cout << "xml file-text created"  << endl; ;
#endif

#if defined(DEBUG_OUTPUT)
// cout << endl << endl << Text << endl << endl;
#endif

 if(dstPath != nullptr)
 {
  ofstream  File(dstPath,ios_base::binary|ios_base::out);

  if(File.good()) // file successfully opened
  {
   File << Text;
   File.close();
   ReturnValue = true;
  }
 }
 delete[]Text;

 return(ReturnValue);
}





XML_Node XML_DataModel::rootNode(void)
{
 return(XML_Node(this,focus_Fellow()));
}






/* @MRTZ_describe readTextFile

*/
const char*  XML_DataModel::readTextFile(const char* srcPath/*,
                        String_imp usedPathSeparator,
                        String_imp osPathSeparator*/)
{
// cout<<__FILE__<<":"<<__LINE__<<":0: XML_DataModel::readTextFile enter" << endl;
 char*  ReturnValue = nullptr;


 ifstream  File(srcPath,ios_base::binary|ios_base::in );


 if(File.good())                                      // file successfully opened
 {
  struct stat  FileInfo;
  stat(srcPath, &FileInfo);                           // get information about file
  streamsize   Index  = 0;                            // character position
  int TextSize = FileInfo.st_size ;
//  while(ReturnValue == nullptr)
//  {
//   try
//   {
    ReturnValue = new char[TextSize+1];        // allocate memory for file content
//   }
//   catch (const std::bad_alloc& e)
//   {
//    cout << "memory allocation failed for loading xml-file : " << srcPath << endl;
//    ReturnValue = nullptr;
//    cout << " -> requested text-size " << TextSize << "characters";
//    TextSize = TextSize - (FileInfo.st_size) / 100;
//    cout << " will be reduced to "  << TextSize << "characters." << endl;
//   }
//  }
  memset(ReturnValue, 0, TextSize+1);          // ensure string termination


  char Character = 0;
  while(  (File.eof() == false           )
        &&(Index      <  TextSize)
       )                                              // iterate over file content
  {
   File.get(Character);                               // get next character

   if(Character == '<')                               // new tag starts
   {
    while(  (ReturnValue[Index-1] == ' ')
           )                // character before tag is a space
    {
     ReturnValue[Index-1] = 0;                        // delete and reinitialize place of space
     -- Index;                                        // prepare the overwriting of space-position
    }
   }
   else                                               // no tag start
   {/* keep character*/ }

   ReturnValue[Index] = Character;                    // store character
   ++ Index;                                          // next output position
  }
  File.close();


 }
 else
 {
  File.clear();
  printf("file \"%s\" not found \n",srcPath);
 };

// cout<<__FILE__<<":"<<__LINE__<<":0: XML_DataModel::readTextFile leave" << endl;
 return(ReturnValue);
}










