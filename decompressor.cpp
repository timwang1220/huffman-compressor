#include<bitset>
#include"decompressor.h"
#define buffer_size 800000
#include<iostream>


const std::string& Decompressor::GetName(){
    unsigned char namesize;
    fread(&namesize,1,1,fin);
    if (feof(fin)) {outfile="";return outfile;}
    outfile.resize(namesize);
    fread(&outfile[0],1,(int)namesize,fin);
    return outfile;
}
void Decompressor::readweight(){
    isFolder=false;
    short size;
    fread(&size, sizeof(size), 1, fin); 
    if (size==-1) {isFolder=true; return;}
    memset(weight,0,sizeof(weight));  
    for (int i=0;i<size;i++)
    {
        unsigned char c;
        unsigned long long w;
        fread(&c, sizeof(c), 1, fin);
        fread(&w, sizeof(w), 1, fin);
        weight[c] = w;
    }
    fread(&filesize,sizeof(filesize),1,fin);
}

void Decompressor::writedecompressed()
{
    unsigned char lastbit;
    fread(&lastbit,sizeof(unsigned char),1,fin);
    tree = new HuffmanTree(weight);  
    if (!tree->GetSize()) {std::bitset<256> null; fread(&null,32,1,fin); return;}
    Node *root=tree->GetRoot();
    Node *now=root;
    char outbuffer[buffer_size];
    int now_buffersize=0;
    double t=0;
    while (filesize>0)
    {
        std::bitset<256> buffer;
        fread(&buffer,32,1,fin); 
        int k=256;
        if (filesize==1) k=(lastbit)?lastbit:256;
        for (int i=0;i<k;i++){
            if (buffer.test(i)) now=now->right;
            else now=now->left;
            if (now->c!=-1){
               char temp=(unsigned char)now->c;
               outbuffer[now_buffersize]=temp;
               now_buffersize++;
               if (now_buffersize==buffer_size) {
                  fwrite(&outbuffer,sizeof(char),buffer_size,fout); 
                  now_buffersize=0;
               }
               now=root;
            }
        }
      filesize--;
    }
    fwrite(&outbuffer,sizeof(char),now_buffersize,fout);
}

void Decompressor::decompress(){
    if (!outfolder.empty()) std::filesystem::create_directories(outfolder);
    while (!feof(fin)){
       std::string outname=this->GetName();
       if (outname.empty()) break;
       this->readweight();
       if (isFolder){
          nowfolder=outname+"\\";
          std::filesystem::create_directories(outfolder+outname);
          continue;
       } 
       outname=outfolder+nowfolder+outname;
       if (outfileChecker.isSkipped(outname)) {
          fseek(fin,filesize*32+1,SEEK_CUR); 
          continue;
       }  
       fout=fopen(outname.c_str(),"wb");
       this->writedecompressed();
       fclose(fout); 
    }
}

const std::vector<std::filesystem::path>& Decompressor::getFileNames(){
    if (!files.empty()) return files;
    while (!feof(fin)){
       std::string nowfile=this->GetName();
       if (nowfile.empty()) break;
       files.push_back(nowfile);
       this->readweight();
       if (isFolder) continue; 
       fseek(fin,filesize*32+1,SEEK_CUR);
    }
    return files;
}
// 
// min = (condition)? true value:false value;