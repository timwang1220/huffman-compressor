#include"folder.h"
#include<filesystem>

#include<iostream>


Folder::Folder(const std::string &_foldername){
    foldername = _foldername;
    for (auto &p: std::filesystem::recursive_directory_iterator(foldername)){
        files.push_back(p);
    }
}

