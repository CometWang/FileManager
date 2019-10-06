
#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H
#include <iostream>
#include <string.h>
#include <cstdlib>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <fstream>
#include <time.h>
#include <cmath>

#include <clocale>


using namespace std;
//std: 98
class FileManager{

private:
    const char* name;
    string type;
    off_t size;
    uid_t ownerID;
    string ownernm;
    gid_t groupID;
    string groupnm;
    string permission;
    long accessTime;
    long modifyTime;
    long statusChangeTime;
    unsigned long blockSize;
    vector<FileManager> children;
    int errnum;

public:
    FileManager(const char *filename);
    ~FileManager();

    string getname();


    string gettype();
    off_t getsize();
    uid_t getownerID();
    string getownernm();
    gid_t getgroupID();
    string getgroupnm();
    string getpermission();
    char* getaccessTime();
    char* getmodifyTime();
    char* getstatusChangeTime();
    unsigned long getblockSize();
    vector<FileManager> getchildren();

    void seterrnum(int newerr);

    int geterrInt();

    string geterrnomsg();
/*
     * @param: file stream; (filename?
     * @return: error code
     * This function will take the filestream as an argument and dump the named file to that stream
     * (used to copy file and display contents...);use block_size to determine how much data will be read or written AT A TIME
     * should return error code if the operation not finished store the number in to a variable
* */
    int Dump(ostream& infile);

    int Rename(const char* newname);

    void setname(const char* newname);

    int Remove();

    int Compare(FileManager &other);

    int Expand();

};
// int main();

#endif