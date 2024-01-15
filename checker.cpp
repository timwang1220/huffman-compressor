#include"checker.h"
#include<iostream>
#include<filesystem>

bool OutFileChecker::isSkipped(const std::string &filename){
    if (state==always_skip) return true;
    if (state==always_overwrite) return false;
    if (access(filename.c_str(),0)==0){
        std::cout<<"The \""<<filename<<"\" has already existed, how do you want to process?"<<std::endl;
        std::cout<<"Press [s] for skip, Press [o] for overwrite."<<std::endl;
        std::cout<<"Press [sa] for always skip, Press [oa] for always overwrite.(Default for skip once)"<<std::endl;
        char c=getchar(); char a=getchar();
        if (a=='a'){
            if (c=='s') {state=always_skip; return true;}
            if (c=='o') {state=always_overwrite; return false;}
        }
        if (c=='o') return false;
        return true;
    }
    return false;
}
bool InFileChecker::isSkipped(const std::string& filename){
    if (access(filename.c_str(),0)==0&&!is_directory(std::filesystem::path(filename))) return false;
    std::cout<<"Cannot Find File \""<<filename<<"\""<<std::endl;
    return true;
}
bool InFolderChecker::isSkipped(const std::string& foldername){
    if (is_directory(std::filesystem::path(foldername))) return false;
    std::cout<<"Cannot Find Folder \""<<foldername<<"\""<<std::endl;
    return true;
}
bool TimFileChecker::isSkipped(const std::string& filename){
    if (std::filesystem::path(filename).extension()!=".tim"){
        std::cout<<"\""<<filename<<"\" is not a \".tim\" compressed file."<<std::endl;
        std::cout<<"You cannot decompress/display it."<<std::endl;
        return true;
    }
    return false;
}
