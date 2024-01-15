#include"command.h"
#include<iostream>
void CompressCommand::execute(){
    FILE *fin=fopen(inname.c_str(),"rb");
    FILE *fout=fopen(outname.c_str(),"wb");
    int index=inname.rfind("\\")+1;
    std::string singlefile_name=(index==std::string::npos)?inname:inname.substr(index);
    c=new Compressor(singlefile_name,fin,fout);
    c->compress(); 
    fclose(fin);
    fclose(fout);
}

void FolderCompressCommand::execute(){
    FILE *fout=fopen(outname.c_str(),"wb");
    int pathlength=inname.rfind("\\")+1;
    f=new FolderCompressor(inname,pathlength,fout);
    f->compress();
    fclose(fout);
}

void DecompressCommand::execute(){
    FILE *fin=fopen(inname.c_str(),"rb");
    d=new Decompressor(fin,outname);
    d->decompress();
    fclose(fin);
}

void DecompressCommand::display(){
    FILE *fin=fopen(inname.c_str(),"rb");
    d=new Decompressor(fin,outname);
    auto file=d->getFileNames();
    fclose(fin);
    int level=0;
    std::filesystem::path nowpath;
    for (int i=0;i<file.size();i++){
        std::filesystem::path p=file[i];
        if (!file[i].extension().empty()){
            for (int i=0;i<level-1;i++) std::cout<<"|   ";
            std::cout<<"|---";
            std::cout<<file[i].string()<<std::endl;
        }
        else{
            auto its=file[i].begin(),ite=file[i].end();
            level=0;
            for (auto &it:nowpath){
               if (it.string()==its->string()) level++;
               else break;
               its++;
               if (its==ite) break; 
            }
            for (auto itd=its;itd!=ite;itd++){
               for (int i=0;i<level-1;i++) std::cout<<"|   ";
               if (level) std::cout<<"|---";
               std::cout<<itd->string()<<std::endl;
               level++;
            }
            nowpath=file[i];
        }
    }
}