#include"command.h"
#include"checker.h"
#include<string>
#include<iostream>
#include<windows.h>

int main(int argc,char *argv[]){
    std::filesystem::path inpath,outpath;
    InFileChecker ifile; InFolderChecker ifolder; 
    TimFileChecker t; OutFileChecker o;
    Command *command;
    if (argc<3) goto Ilegal; 
   if (!strcmp(argv[1],"tim")){
      //  std::cout<<argv[1]<<std::endl;
       if (!strcmp(argv[2],"-r")){
          if (argc==3) goto Ilegal;
          inpath=argv[3];
          if (argc>4) outpath=argv[4];
          else outpath=std::filesystem::path(inpath.string()+".tim");
          if (ifolder.isSkipped(inpath.string())) return 0;
       }
       else{
          inpath=argv[2];
          if (argc>3) outpath=argv[3];
          else {outpath=inpath; outpath.replace_extension(".tim");} 
          if (ifile.isSkipped(inpath.string())) return 0;
       }
       if (o.isSkipped(outpath.string())) return 0;
       if (!strcmp(argv[2],"-r")) command=new FolderCompressCommand(inpath.string(),outpath.string());
                 else command=new CompressCommand(inpath.string(),outpath.string());          
        std::cout<<"Compressing..."<<std::endl; 
        command->execute(); delete command;
        std::cout<<"Compressing Succeed!"<<std::endl;
        return 0;
    }
    if (t.isSkipped(argv[2])) return 0;
    if (!strcmp(argv[1],"untim")){
       if (argc==3) command=new DecompressCommand(argv[2],"");
       else command=new DecompressCommand(argv[2],argv[3]);
       std::cout<<"Decompressing..."<<std::endl;
       command->execute();  delete command;
       std::cout<<"Decompressing Succeed!"<<std::endl;
       return 0; 
    }
    if (!strcmp(argv[1],"display")){
        command=new DecompressCommand(argv[2],"");
        command->display(); delete command;
        return 0;
    }
    Ilegal:
    std::cout<<"Ilegal Command.Please try again."<<std::endl;
}