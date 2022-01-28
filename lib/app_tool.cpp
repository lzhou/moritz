/*!

 @file
 @brief    diverse tool-functions for a main-application

 This file contains the definition of common functions used in main-applications


 Copyright (C) 2012-2020 by Eckard Klotz.

 Permission to use, copy, modify, and distribute this software and its
 documentation under the terms of the GNU General Public License is hereby
 granted. No representations are made about the suitability of this software
 for any purpose. It is provided "as is" without express or implied warranty.
 See the GNU General Public License for more details.

 Documents produced by the binary of this source are derivative works derived from the
 input used in their production; they are not affected by this license.

 <b> History </b>

 @TabBegin
    date           @I author          @I implementation/change
 @I____________________________________________________________
    12.02.2012     @I Eckard Klotz    @I first implementation
 @I____________________________________________________________
    12.02.2012...  @I Eckard Klotz
 @I Changes are documented in the comment of the changed element
 @TabEnd

*/
#include "app_tool.h"

#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>





#ifndef DOXYGEN
 //namespace F_APP_TOOL{
#endif //DOXYGEN


/* @MRTZ_describe info

   @MRTZ_describe define_SearchWord

   @MRTZ_describe create_help_output

*/
void info(int argc,   char* argv[],
          const String_imp& kind,
          App_Info_TP       application_Info[])
{

 String_imp ReturnValue = "";
 String_imp SearchWord  = "";

// @MRTZ_exclude define_SearchWord
// @MRTZ_beginBlock
// @MRTZ_ifElseChain
 if((argc == 2)&&(argv[1] == kind))                // general help
 {
  SearchWord = lowCaseString(String_imp(argv[1]));
 }
 else if((argc >2)&&(argv[1] == kind))             // special help
 {
  SearchWord = lowCaseString(String_imp(argv[2]));
 }
 else                                              // program-info
 {
  SearchWord = lowCaseString("StartOutput");
 }
// @MRTZ_endBlock

 int Index = 0;
// @MRTZ_exclude create_help_output
 while(application_Info[Index].Name != "")      //until termination-element found
 {
  if( SearchWord == lowCaseString("All"))       //all Information wanted
  {
   ReturnValue =   ReturnValue
                 + "\n\n"
                 + application_Info[Index].Content;         //collecting all help-info
  }
  else if( lowCaseString(application_Info[Index].Name) == SearchWord)  //wanted help found
  {
   ReturnValue = application_Info[Index].Content;           //special help-info
   break;
  }
  Index ++;
 }

 String_imp TargetPointerSize = "_TARGET_POINTER_SIZE_" ;

 if(this_is_at_least_a_64_bit_application() == true)
  ReturnValue.replace(ReturnValue.find(TargetPointerSize), TargetPointerSize.size(),"64 bit");
 else
  ReturnValue.replace(ReturnValue.find(TargetPointerSize), TargetPointerSize.size(),"32 bit");

 printf("%s",ReturnValue.c_str());

 if(SearchWord != lowCaseString("StartOutput")) //only output of help info
  exit(0);                                      //terminate
}


/*
 @MRTZ_describe this_is_at_least_a_64_bit_application
*/
bool this_is_at_least_a_64_bit_application(void)
{
 int* TestPointer = (int*)0xFFFFFFFF;   // maximum value for a 32 bit pointer
      TestPointer ++;                   // try to increase pointer value
 if(TestPointer > (int*)0xFFFFFFFF)     // pointer value is really incresed
  return(true);
 else                                   // pointer value is smaller due to an value overflow
  return(false);
}


/* @MRTZ_describe getAgument

*/
String_imp getAgument(int argc, char* argv[], const String_imp& kind)
{
 String_imp ReturnValue = "";

 int ArgumentCounter    = 0;                          //index of arguments
 String_imp Argument = argv[0];                       //read first argument

 if(argc != -1)
  while(  (argv[ArgumentCounter+1]     != nullptr)
//        &&(Argument.find(kind.c_str(),0)>0)
        &&(starts_with(Argument, kind) == false )
       )                                              //until end of argument-array or argument is found
  {
   ArgumentCounter ++;
   Argument = argv[ArgumentCounter];                   //read next argument
  };

// if(Argument.find(kind.c_str(),0)==0)                 //argument is found
 if(starts_with(Argument, kind) == true)              //argument is found
 {
  ReturnValue = Argument.substr(kind.size());         //store argument
  (argv[ArgumentCounter])[0]='?';                     //delete argument in array
 };

 return(ReturnValue);
}



/* @MRTZ_describe getConfigValue
 A <a href="group___a_r_g_u_m_e_n_t_p_r_e_f_i_x.html#">special prefix</a>
 is used to mark the config-value in the argument-stringsand is given with the
 parameter argName.<br>
 The <a href="group___a_r_g_u_m_e_n_t_x_m_l.html#">xml-names of arguments</a>
 are used to mark the same values in the configuration-file and are given with
 the parameter xmlName.<br>
 The <a href="group___a_r_g_u_m_e_n_t_d_e_f_a_u_l_t.html#">argument-defaults</a>
 are  used as fail-save values only and are given with the parameter
 defaultValue. Since the user-placement of the xml2abc-files may differ from the
 default-values they will lead to error-messages.
*/
String_imp getConfigValue(XML_Node configuration,
                          const String_imp& xmlName,
                          int argc, char* argv[],
                          const String_imp& argName,
                          const String_imp& defaultValue)
{
  String_imp ReturnValue    = "";

  String_imp ArgumentBuffer = getAgument(argc, argv, argName);
  if(  (ArgumentBuffer == "")
     &&(configuration.valid() == true)
    )
  {
   XML_Node SubChild = configuration.firstGet(XML_Node::Element(XML_Search::Value,xmlName.c_str()));
   cout << "argName " << argName << endl;
   if(SubChild.attributeGet(argName.c_str(),nullptr) != nullptr)
        // given argName is used as attribute
    ArgumentBuffer = SubChild.attributeGet(argName.c_str());
   else if(SubChild.attributeGet("value",nullptr) != nullptr)
        // default attribute "value exists"
    ArgumentBuffer = SubChild.attributeGet("value");
   else // no definition in xml-configuration available
    { /* nothing to do */}
  };

  if(ArgumentBuffer != "")
   ReturnValue = ArgumentBuffer;
  else
   ReturnValue = defaultValue;

  return(ReturnValue);
 }















/* @MRTZ_describe getUserDefinitions

*/
XML_Node getUserDefinitions(XML_Node    root,
                            int         argc,
                            char*       argv[],
                            char        frame,
                            char        splitter,
//                            char        charStart,
//                            char        charEnd,
                            const char* argName)
{
 XML_Node      ReturnValue = root.lastAdd(XML_Data::NT_Element);
               ReturnValue.valueSet("UserArgument");

 if(argc != -1)
 {
  int   ArgumentCounter  = 0;                                      // index of arguments
  char* Argument         = argv[0];                                // read first argument

  while(  (argv[ArgumentCounter+1] != nullptr)
        &&(Argument[0]!=0)
       )                                                           // until end of argument-array or argument is found
 {
  ArgumentCounter ++;
  Argument = argv[ArgumentCounter];                                // read next argument

  if(Argument[0] == frame)                                         // argument starts not with argument-name
   ++Argument;                                                     // begin of  argument-name

  if(  (Argument[0]               != 0)
     &&(strstr(Argument,argName)  == Argument)
     &&(strchr(Argument,splitter) != nullptr)
    )                                                              // argument is not empty, starts with the given argument-name
                                                                   // and contains the given splitter-character
  {
   int MaxSize =strlen(Argument);

   char* Identifier = new char[MaxSize];                           // prepare identifier-buffer with enough memory
   memset(Identifier,0,MaxSize);
   strcpy(Identifier,Argument+strlen(argName));                    // copy argument
   Identifier[strchr(Identifier,splitter)-Identifier] = 0;         // cut identifier at splitter position


   char* Value = new char[MaxSize];                                // prepare value-buffer with enough memory
   memset(Value,0,MaxSize);
   strcpy(Value,strchr(Argument,splitter)+1);                      // copy argument after splitter

   strRestoreCharacters(&Value,Value);                             // restore special characters

   if(strlen(Identifier)>0)                                        // valid identifier
   {
    XML_Node NewChild = ReturnValue.lastAdd(XML_Data::NT_Element); // create buffer
             NewChild.valueSet(Identifier);                        // returned buffer of single user definition
             NewChild.attributeSet("value",Value);                 // store value

   }

   delete[](Identifier);                                           // clear identifier-buffer again
   Identifier = nullptr;
   delete[](Value);                                                // clear value-buffer again
   Value      = nullptr;
  }
 };

 }
 return(ReturnValue);
}





/* @MRTZ_describe strRestoreCharacters

*/
void strRestoreCharacters(char**      newStr,
                          const char* oldStr,
                          char        charStart,
                          char        charEnd)
{
 int  MaxSize =strlen(oldStr)+1;



 char* Buffer = nullptr;
 if(oldStr == (*newStr)) // original string should contain result
 {
  Buffer = new char[MaxSize];
  memset(Buffer,0,MaxSize);
  strcpy(Buffer,oldStr);
 }
 else
 {
  Buffer = (char*)oldStr;
 }

 if((*newStr) == nullptr)
 {
  (*newStr) = new char[MaxSize];
 }
 memset(*newStr,0,MaxSize);

#if defined(DEBUG_OUTPUT)
 cout << "Buffer: " << Buffer << endl;
#endif // DEBUG_OUTPUT

 int  readIndex  = 0;
 int  writeIndex = 0;
 for(readIndex = 0; readIndex< MaxSize; ++readIndex)
 {
  if(Buffer[readIndex]!=charStart)
  {
   (*newStr)[writeIndex] = Buffer[readIndex];
   ++writeIndex;
  }
  else
  {
   ++readIndex;
   int  Ordinal = 0;
   while(Buffer[readIndex] != charEnd)
   {
    Ordinal = Ordinal * 10 + (Buffer[readIndex] - '0');
    ++readIndex;
   }

   if((Ordinal>0) && (Ordinal<256))
   {
    (*newStr)[writeIndex] = (char) Ordinal;
    ++writeIndex;
   }

  }
#if defined(DEBUG_OUTPUT)
  cout << "newStr: " << newStr << endl;
#endif // DEBUG_OUTPUT
 }

 if(Buffer != oldStr) //buffer was temporary created
  delete[](Buffer);

}




/* @MRTZ_describe readTextFile

*/
String_imp readTextFile(const String_imp& fileName,
                        const String_imp& usedPathSeparator,
                        const String_imp& osPathSeparator)
/* @MRTZ_describe readTextFile

*/
{
 String_imp   ReturnValue = "";
 String_imp   FileName    = fileName;

 if(usedPathSeparator != osPathSeparator)         // do it only if it has to be done
  FileName = replacePartString(FileName,usedPathSeparator,osPathSeparator);

 ifstream  File((char*)(FileName.c_str()));

 if(File.good())                                  // file successfully opened
 {
  struct stat  FileInfo;
  stat((char*)(FileName.c_str()), &FileInfo);     // get information about file
  streamsize   Index  = 0;                        // character position

  char*  Content = new char[FileInfo.st_size +1]; // allocate memory for file content
  memset(Content,0,FileInfo.st_size +1);          // ensure string termination

  while(  (File.eof() == false             )
        &&(Index      <  (FileInfo.st_size))
       )                                          // iterate over file content
  {
   File.get(Content[Index]);                      // get next character
   ++ Index;                                      // next output position
  }
  File.close();

  ReturnValue = Content;
 }
 else
 {
  File.clear();
  printf("file \"%s\" not found \n",FileName.c_str());
 };

 return(ReturnValue);
}


/* @MRTZ_describe collectFiles


   @MRTZ_describe scan_file

   @MRTZ_describe check_file_attachment

   @MRTZ_describe check_if_file_is_already_known

   @MRTZ_describe add_new_file_to_list_of_sources_to_analyse

   @MRTZ_describe scan_sub_folder

*/
void collectFiles(XML_Node         sourceContainer,
                  XML_Node         addBehind,
                  const String_imp& folderName,
                  const String_imp& sourcePath,
                  const String_imp& rootPath,
                  const String_imp& osPathSeparator,
                  const String_imp& fileAttachment,
                  bool              recursive,
                  const String_imp& doNotSkip,
                  XML_Node          variantContainer)
{

#if defined(DEBUG_OUTPUT)
    cout << "folderName: " << folderName << endl;
#endif //DEBUG_OUTPUT

 DIR* Directory = opendir(folderName.c_str());
 if(Directory != nullptr)
 {
  struct stat    FileInfo;
  struct dirent* Entry       = nullptr;
  String_imp     FoundSource = "";
  do
  {
   Entry = readdir(Directory);
   if(Entry)
   {
     String_imp Path = folderName ;
     if(Path.find(osPathSeparator) != (Path.size()-1))
      Path = Path + osPathSeparator;
     Path = Path + (Entry->d_name) ;


    fstream  File((char*)(folderName+Entry->d_name).c_str(),ios::binary|ios::in);
    if(  (opendir(Path.c_str()) == nullptr)
       &&(File.good())) // file successfully opened
    {
// @MRTZ_exclude scan_file
// @MRTZ_beginBlock
     stat((char*)(Entry->d_name), &FileInfo);
// @MRTZ_exclude check_file_attachment
// @MRTZ_beginBlock
     bool UseFile     = true;
     if( fileAttachment!="" )
     {
      String_imp FoundAttach = String_imp(Entry->d_name);
      if(FoundAttach.size()>=fileAttachment.size())
      {
       FoundAttach = FoundAttach.substr(FoundAttach.size()-fileAttachment.size());
       if(fileAttachment == FoundAttach)
        UseFile = true;
       else
        UseFile = false;
      }
      else
       UseFile = false;
     }

// @MRTZ_endBlock

// @MRTZ_exclude check_if_file_is_already_known
     if(UseFile == true)
     {
      FoundSource = (folderName+Entry->d_name);
      XML_Node   Child       = sourceContainer.firstGet(XML_Node::Element());
      while(Child.valid() == true)
      {
       const char* Value = Child.attributeGet("value",nullptr);
       if(  (Value                         != nullptr       )
          &&(String_imp(Child.valueGet()) == "FileName")
          &&(String_imp(Value)             == FoundSource)
         ) // source to analyse is already part of the list
       {
        UseFile = false;
        break;
       }
       Child = Child.behindGet(XML_Node::Element());
      }
     }
     if(UseFile == true)
     {
      // add new file to list of sources to analyse
      XML_Node FileName = sourceContainer.behindAdd(addBehind,XML_Data::NT_Element);
      FileName.valueSet("FileName");
      FileName.attributeSet("value", FoundSource.c_str()) ;
      FileName.attributeSet("root", rootPath.c_str()) ;
      FileName.attributeSet("doNotSkip", doNotSkip.c_str()) ;
      if(variantContainer.valid() == true)
      {
       XML_Node Child = variantContainer.firstGet(XML_Node::Element());
       while(Child.valid() == true)
       {
        if(  (String_imp(Child.valueGet()) == "Common")
           ||(String_imp(Child.valueGet()) == "Special")
          )
        {
         XML_Node Variant = FileName.lastAdd(XML_Data::NT_Element);
                  Variant.valueSet(Child.valueGet());
                  Variant.attributeSet("name",           Child.attributeGet("name"));
                  Variant.attributeSet("keepValideCode", Child.attributeGet("keepValideCode"));
        }
        Child = Child.behindGet(XML_Node::Element());
       }
      }
      addBehind = FileName;
     }
    }
    else if(  ( recursive     == true            )
            &&((Entry->d_name)!= String_imp(".."))
            &&((Entry->d_name)!= String_imp(".") )
            &&((Entry->d_name)!= String_imp("")  )
           )// file-information describes a sub-directory
     {

     collectFiles(sourceContainer, addBehind,
                  replacePartString(   folderName                + osPathSeparator
                                     + String_imp(Entry->d_name) + osPathSeparator,
                                    osPathSeparator+osPathSeparator,osPathSeparator),
                  sourcePath,
                  rootPath,
                  osPathSeparator,
                  fileAttachment,
                  recursive,
                  doNotSkip,
                  variantContainer);
     }
   }
   else
   {
   }
  }
  while(Entry);
 }
 else
 {
    cout << "folder not found: " << folderName << endl;
 }

 if(Directory != nullptr)
  closedir(Directory);
}





















/* @MRTZ_describe searchFiles

*/
void searchFiles(XML_Node                   configuration,
                 const String_imp&          commonAttachment,
                 const String_imp&          usedPathSeparator,
                 const String_imp&          osPathSeparator)
{
 XML_Node   SourceContainer = configuration.preGet();
 String_imp FolderName      = configuration.attributeGet("value");

 String_imp    RootPath         = "";
 if(usedPathSeparator != osPathSeparator) //do it only if it has to be done
  RootPath = replacePartString(RootPath,usedPathSeparator,osPathSeparator);
 if( RootPath.rfind(osPathSeparator) < RootPath.size()-1)
  RootPath = RootPath + osPathSeparator;
 if( RootPath == "")
  RootPath = "." + osPathSeparator;


 FolderName = RootPath + FolderName;
 if(    FolderName.find_last_of(osPathSeparator)
    != (FolderName.size() - osPathSeparator.size()))
  FolderName = FolderName + osPathSeparator;

 String_imp DoNotSkip  = configuration.attributeGet("doNotSkip","");
 if(DoNotSkip == "")
  DoNotSkip = String_imp("No");

 String_imp  FileAttachment = configuration.attributeGet("fileAttachment",commonAttachment.c_str());

 String_imp  Text = configuration.attributeGet("recursive");

 bool Recursive = true;
// @MRTZ_ifElseChain
 if     (lowCaseString(Text)==String_imp("yes"))
  Recursive = true;
 else if(lowCaseString(Text)==String_imp("no"))
  Recursive = false;
 else
  Recursive = true;

 XML_Node VariantContainer;
 if(configuration.firstGet().valid() == true)
 {
  VariantContainer = configuration;
 }
 else
 {
 }

 collectFiles(SourceContainer,
              configuration,
              FolderName,
              FolderName,
              RootPath,
              osPathSeparator,
              FileAttachment,
              Recursive,
              DoNotSkip,
              VariantContainer);
}







/* @MRTZ_describe completeXML

*/
void completeXML(XML_Node          root,
                 const String_imp& usedPathSeparator,
                 const String_imp& osPathSeparator,
    map<String_imp,String_imp>     rootStrings,
                 const String_imp& subFileAttribute)
{
 const char* Text = root.attributeGet(subFileAttribute.c_str(),nullptr);
 if(Text != nullptr)
 {
  cout << "Text " << Text << endl;
  String_imp Root = root.attributeGet("root");
  cout << Root << ":";
  Root = rootStrings[Root];
  cout << Root << endl;
  if(  (Root                        != "")
     &&(Root.rfind(osPathSeparator) <  Root.size()-1)
    )
   Root = Root + osPathSeparator;

  String_imp SubFile =  Root + String_imp(Text);

  if(usedPathSeparator != osPathSeparator) // do it only if it has to be done
   SubFile = replacePartString(SubFile,usedPathSeparator,osPathSeparator);
  cout << "SubFile : " << SubFile << endl;
  XML_DataModel* IncludeFile    = new XML_DataModel(SubFile.c_str());
  XML_Node       IncludeContent = IncludeFile->rootNode();
  if(IncludeContent.firstGet(XML_Node::Element()).valid() == true)
  {
   printf("analyse configuration-file \n");
   XML_Node IncludeTree = IncludeContent.firstGet(XML_Node::Element());

   if(IncludeTree.valid() == true)
   {
    completeXML(IncludeTree, usedPathSeparator, osPathSeparator, rootStrings, subFileAttribute);
   }

   XML_Node Child = IncludeTree.firstGet(XML_Node::Element());
            Child = IncludeTree.nodeCut(Child);
   while(Child.valid() == true)
   {
    completeXML(Child, usedPathSeparator, osPathSeparator, rootStrings, subFileAttribute);
    root.lastAdd(Child);
    Child = IncludeTree.firstGet(XML_Node::Element());
    Child = IncludeTree.nodeCut(Child);
   }
  }
  else
  {
   printf("file \"%s\" not found !\n",SubFile.c_str());
   printf("or the file has xml-errors. \n");
   printf("abc2xml will terminate now. \n");
  }
 }
 else
 {
  XML_Node Child = root.firstGet(XML_Node::Element());
  while(Child.valid() == true)
  {
   completeXML(Child, usedPathSeparator, osPathSeparator, rootStrings, subFileAttribute);

   Child = Child.behindGet(XML_Node::Element());
  }
 }
}








/* @MRTZ_describe checkNewSource

*/
bool checkNewSource(const String_imp& source,
                    list<String_imp>  destination,
                    const String_imp& usedPathSeparator,
                    const String_imp& osPathSeparator)
{
 bool       ReturnValue = true;
 String_imp Source      = source;

 if(usedPathSeparator != osPathSeparator)                      // do it only if it has to be done
  Source = replacePartString(Source,usedPathSeparator,osPathSeparator);

 fstream  SourceFile((char*)Source.c_str(),ios::binary|ios::in);
 if(SourceFile.good())                                         // source file successfully opened
 {
  struct stat    SourceInfo;
  stat(Source.c_str(), &SourceInfo);
  SourceFile.close();
  list<String_imp>::iterator Destination = destination.begin();
  while(Destination != destination.end())
  {
   if(usedPathSeparator != osPathSeparator)                    // do it only if it has to be done
    (*Destination) = replacePartString(*Destination,usedPathSeparator,osPathSeparator);

   fstream  DestinationFile((char*)Destination->c_str(),ios::binary|ios::in);
   if(DestinationFile.good())                                  // destination-file found
   {
    struct stat    DestinationInfo;
    stat(Destination->c_str(), &DestinationInfo);
    DestinationFile.close();
    if(DestinationInfo.st_mtime > SourceInfo.st_mtime)         // destination-file is older than source-file
     ReturnValue = false;
   }
   else                                                        // destination-file does not exist
   {
    ReturnValue = true;
    break;                                                     // leave check since creation of destination is necessary
   }
   ++Destination;
  }
 }

 return(ReturnValue);
}

/* @MRTZ_describe getAbsolutePath

*/
String_imp getAbsolutePath(const String_imp& file,
                           const String_imp& osPathSeparator)
{
 String_imp     ReturnValue = "";

 String_imp Path = file.substr(0,file.find_last_of(osPathSeparator)+1);
 DIR* Directory = opendir(Path.c_str());
 if(Directory != nullptr)
 {
//  while(Path.find(String_imp(".") + osPathSeparator) == 0)
  while(starts_with(Path, String_imp(".") + osPathSeparator) == true)
  {
   Path.erase(0,osPathSeparator.size()+1);
  }
  ReturnValue = String_imp(getcwd(nullptr,1024)) + osPathSeparator + Path;
  ReturnValue = ReturnValue.substr(0,ReturnValue.find_last_of(osPathSeparator));

  closedir(Directory);
 }

 return(ReturnValue);
}


/* @MRTZ_describe createFolder

*/
int createFolder(const String_imp& path, char separator)
{
 int ReturnValue = 0;

 char             Splitter[2]   = {separator,0};
//#if !defined(NO_SYSTEM_FOR_FOLDERCREATE)
// String_imp       SystemCommand = "";
//#endif

 list<String_imp>           Folders       = stringToList(path, separator);
 list<String_imp>::iterator CurrentFolder = Folders.begin();
 String_imp                 PartFolder    = "";
 while(CurrentFolder != Folders.end())
 {
  if(   ((*CurrentFolder).find('.') >= (*CurrentFolder).size())
      ||((*CurrentFolder).find('.') == 0                      )
    )
   // no file name
  {
   PartFolder = PartFolder + (*CurrentFolder) + String_imp(Splitter);

    DIR* Directory  = opendir(PartFolder.c_str());
   if(Directory == nullptr)
   {
    cout<< "directory not found :\n" << PartFolder << endl;
#if defined(NO_SYSTEM_FOR_FOLDERCREATE)
  #ifdef WINDOWS
     mkdir(PartFolder.c_str());
  #elif defined(LINUX)
     mode_t FileAttributes = S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH;
     mkdir(PartFolder.c_str(),FileAttributes);
  #else
     mode_t FileAttributes = S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH;
     mkdir(PartFolder.c_str(),FileAttributes);
  #endif // WINDOWS
#else
    String_imp  SystemCommand = String_imp("mkdir ") + PartFolder;
                ReturnValue   = system(SystemCommand.c_str());
#endif
    Directory  = opendir(PartFolder.c_str());
    if(Directory == nullptr)
    {
     cout<< "faild to create directory :\n" << PartFolder << endl;
    }
    else
    {
     cout<< "new directory created:\n" << PartFolder << endl;
     closedir(Directory);
    }
   }
  }
  ++ CurrentFolder;
 }
 return(ReturnValue);
}



#ifndef DOXYGEN
//}; //using F_APP_TOOL;
#endif //DOXYGEN

