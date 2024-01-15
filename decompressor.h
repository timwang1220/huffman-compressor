#ifndef Decompressor_H
#define Decompressor_H
#include<string>
#include<cstring>
#include<filesystem>
#include"huffman.h"
#include"checker.h"

class Decompressor{
   private:
     HuffmanTree *tree;
     std::string infile,outfile;
     std::string outfolder,nowfolder;
     FILE *fin,*fout;
     std::vector<std::filesystem::path> files;
     bool isFolder;
     OutFileChecker outfileChecker;
     unsigned long long int weight[256];
     unsigned long long int filesize;
   public: 
     Decompressor(FILE *_fin,std::string outname):fin(_fin),outfolder(outname){};
     const std::string& GetName(); 
     void readweight();
     void writedecompressed();
     void decompress();
     const std::vector<std::filesystem::path> &getFileNames();
};



#endif