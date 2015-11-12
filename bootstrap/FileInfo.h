#ifndef FILEINFO_H
#define FILEINFO_H

#include <string>
#include <memory>
#include <vector>

class FileInfo
{
public:
  static std::shared_ptr<FileInfo> create(std::string absolutePath);
  static std::string getSuffix(std::string absolutePath);
  static std::string getFolderPath(std::string absolutePath);

  std::string getAbsolutePath();

protected:
  std::string absolutePath;

  void init(std::string absolutePath);

};

class SourceFileInfo : public FileInfo
{
public:
  static std::shared_ptr<SourceFileInfo> create(std::string absolutePath);

private:
  void processInclude(std::string absolutePath);
  std::vector<std::shared_ptr<FileInfo>> dependencies;

};

#endif