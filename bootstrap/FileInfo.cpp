#include "FileInfo.h"
#include "Util.h"

#include <iostream>
#include <fstream>

std::shared_ptr<FileInfo> FileInfo::create(std::string absolutePath)
{
  static FileInfo s;
  std::shared_ptr<FileInfo> rtn(new FileInfo(s));
  rtn->FileInfo::init(absolutePath);

  return rtn;
}

std::string FileInfo::getAbsolutePath()
{
  return absolutePath;
}

void FileInfo::init(std::string absolutePath)
{
  this->absolutePath = absolutePath;
}

std::string FileInfo::getSuffix(std::string absolutePath)
{
  return Util::cropRight(absolutePath, '.');
}

std::string FileInfo::getFolderPath(std::string absolutePath)
{
  return Util::trimRight(absolutePath, '/');
}

std::shared_ptr<SourceFileInfo> SourceFileInfo::create(std::string absolutePath)
{
  static SourceFileInfo s;
  std::shared_ptr<SourceFileInfo> rtn(new SourceFileInfo(s));
  rtn->FileInfo::init(absolutePath);

  std::cout << "Source: " << absolutePath << std::endl;
  rtn->processInclude(absolutePath);

  for(int i = 0; i < rtn->dependencies.size(); i++)
  {
    std::cout << "Dep: " << rtn->dependencies.at(i)->getAbsolutePath() << std::endl;
  }

  return rtn;
}

void SourceFileInfo::processInclude(std::string absolutePath)
{
  // Dont want to reprocess file if already in list
  for(int i = 0; i < dependencies.size(); i++)
  {
    if(absolutePath == dependencies.at(i)->getAbsolutePath())
    {
      return;
    }
  }

  // Dont add initial cpp unit to list of depends
  if(absolutePath != this->absolutePath)
  {
    dependencies.push_back(FileInfo::create(absolutePath));
  }

  //std::cout << "Processing: " << absolutePath << std::endl;

  std::ifstream file(absolutePath.c_str());

  if(file.is_open() == false)
  {
    throw std::exception();
  }

  while(file.eof() == false)
  {
    std::string token;
    file >> token;

    if(token == "") continue;

    if(token.substr(0, 1) == "#")
    {
      if(token == "#")
      {
        std::string tmp;
        file >> tmp;
        token = token + tmp;
      }

      if(token.substr(0, 8) == "#include")
      {
        if(token == "#include")
        {
          std::string tmp;
          file >> tmp;
          token = token + tmp;
        }

        std::string dep = token.substr(8);

        if(dep.at(0) == '"')
        {
          dep = Util::trimLeft(dep, '"');
          dep = Util::trimRight(dep, '"');
          dep = getFolderPath(absolutePath) + "/" + dep;
          processInclude(dep);
        }
      }
    }
  }
}