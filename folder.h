#ifndef Folder_H
#define Folder_H
#include<vector>
#include<string>
#include<filesystem>

class Folder{
     private: 
       std::vector<std::filesystem::path> files;
       std::string foldername; 
     public:
       inline const std::vector<std::filesystem::path>& getFiles() const { return files; }
       Folder(const std::string& _foldername);
};
#endif

