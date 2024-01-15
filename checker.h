#ifndef Checker_H
#define Checker_H
#include<string>
#include<io.h>
enum SkipState {undefined,always_skip,always_overwrite};
class ObserverChecker{
   public:
     bool isSkipped(const std::string &filename){ return true; };
};
class OutFileChecker:public ObserverChecker{
   private:
     SkipState state;
   public:
     OutFileChecker(){
        state=undefined;
     }
     bool isSkipped(const std::string &filename);
};
class InFileChecker:public ObserverChecker{
   private:
   public:
     bool isSkipped(const std::string &filename);
};
class InFolderChecker:public ObserverChecker{
   public:
     bool isSkipped(const std::string &foldername);
};
class TimFileChecker:public ObserverChecker{
   public:
     bool isSkipped(const std::string &filename);
};
#endif