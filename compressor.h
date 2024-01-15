#ifndef Compressor_H
#define Compressor_H
#include<string>
#include<vector>
#include<cstring>
#include<fstream>
#include"huffman.h"
#include"folder.h"

class Compressor{
    private:
       unsigned long long int weight[256];
       HuffmanTree *tree;
       std::string infile;
       FILE *fin,*fout;
       void readfile();
       void writeinformation();
       void writecompressed();
    public:
      Compressor(const std::string &inname,FILE *_fin,FILE *_fout):infile(inname),fin(_fin),fout(_fout){};
      void compress();
};
class FolderCompressor{
   private:
      Folder *folder;
      FILE *fout;
      std::string folderpath;
      int pathlength;  
   public:
      FolderCompressor(const std::string &_folderpath,const int &_pathlength,FILE *_fout):folderpath(_folderpath),fout(_fout),pathlength(_pathlength){
         folder=new Folder(folderpath);
      };
      void compress();
      void writefolder(const std::filesystem::path &path);
};

     


#endif             