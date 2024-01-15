#ifndef Command_H
#define Command_H
#include<string>
#include"compressor.h"
#include"decompressor.h"

class Command{
    protected:
      std::string inname,outname;
    public:
      virtual void execute()=0;
      virtual void display(){};
      Command(const std::string&_inname,const std::string&_outname):inname(_inname),outname(_outname){}; 
};
class CompressCommand:public Command{
    private:
      Compressor *c;
    public:
      using Command::Command;
      void execute() override;
};
class FolderCompressCommand:public Command{
    private:
       FolderCompressor *f;
    public:
        using Command::Command;
        void execute();
      
};
class DecompressCommand:public Command{
    private:
       Decompressor *d;
    public:
      using Command::Command;
      void execute();
      void display();
};

#endif