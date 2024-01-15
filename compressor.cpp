#include <iostream>
#include <filesystem>

#include "compressor.h"
#include <bitset>
#define buffer_size 1024000

void Compressor::readfile()
{
    unsigned long long filesize=0,op=0;
    char buffer[buffer_size];
    memset(weight, 0, sizeof(weight));
    while (!feof(fin))
    {
        int k=fread(buffer,1,buffer_size,fin);
        for (int i=0;i<k;i++)
        {
           weight[(unsigned char)buffer[i]]++;
        }
        filesize+=k;
    }
    for (int i=0;i<256;i++) op+=weight[i];
    tree=new HuffmanTree(weight);
}
void Compressor::writeinformation()
{
    short size = tree->GetSize();
    unsigned char namesize=infile.size();
    fwrite(&namesize,1,1,fout);
    fwrite(&infile[0],sizeof(char),namesize,fout);
    fwrite(&size, sizeof(size), 1, fout);
    for (unsigned char i=0;i<=255;i++)
    {
        if (weight[i]!=0)
        {
            fwrite(&i, sizeof(i), 1, fout);
            fwrite(&weight[i], sizeof(weight[i]), 1, fout);
        }
        if (i==255) break;
    }
    unsigned long long tempsize=0;
    unsigned char c=0;
    fwrite(&tempsize,sizeof(unsigned long long),1,fout);
    fwrite(&c,sizeof(unsigned char),1,fout);
}
void Compressor::writecompressed()
{
    double u=0;
    unsigned long long outfilesize=0;
    auto transmap = tree->Encodemap();
    int nowbit = 0;
    std::bitset<256> outbuffer[10240];
    int outbuffersize=0;
    std::bitset<256> temp;
    char buffer[buffer_size];
    rewind(fin); 
    while (!feof(fin))
    {
        int k=fread(buffer,1,buffer_size,fin);
        for (int i=0;i<k;i++)
        {
            auto p = transmap[(unsigned char)buffer[i]];
            std::bitset<256> nowcode =p.first;
            int nowlength = p.second;  
            if (nowbit+nowlength<=256)
            {
                nowcode<<=nowbit;
                temp|=nowcode;
                nowbit+=nowlength;
            }
            else
            {
                temp|=(nowcode<<nowbit);
                outbuffer[outbuffersize]=temp;
                outbuffersize++;
                temp=nowcode>>(256-nowbit); 
                nowbit=nowbit+nowlength-256; 
                if (outbuffersize==10240) {
                    fwrite(&outbuffer,32,10240,fout);
                    outbuffersize=0;
                    outfilesize+=10240;
                }
            }
        }
    }
    fwrite(&outbuffer,32,outbuffersize,fout);
    outfilesize+=outbuffersize;
    fseek(fout,-9-32*outfilesize,SEEK_CUR);
    fwrite(&outfilesize,sizeof(unsigned long long),1,fout);
    fwrite(&nowbit,sizeof(unsigned char),1,fout);
    fseek(fout,0,SEEK_END);
}


void Compressor::compress(){
    this->readfile();
    this->writeinformation();
    this->writecompressed();
}


void FolderCompressor::compress(){
    double t=0;
    std::vector<std::filesystem::path> files=folder->getFiles();
    std::filesystem::path lastpath;
    this->writefolder(folderpath);
    for (auto &it:files){
        if (is_directory(it)){
          lastpath=it; 
          this->writefolder(it); continue;
        }
        if (it.parent_path()!=lastpath){
           this->writefolder(it.parent_path());
        }
        lastpath=it.parent_path(); 
        std::string filename=it.filename().string();
        FILE *fin=fopen(it.string().c_str(),"rb");
        Compressor c(filename,fin,fout);double t1=clock();
        c.compress();
        fclose(fin);
    }
}

void FolderCompressor::writefolder(const std::filesystem::path &nowpath){  
    std::string foldername=nowpath.string().substr(pathlength);
    unsigned char namesize=foldername.size();
    fwrite(&namesize,1,1,fout);
    fwrite(&foldername[0],sizeof(char),namesize,fout);
    short size=-1;
    fwrite(&size, sizeof(size), 1, fout);
}
