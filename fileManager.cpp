#include "fileManager.h"
#include <dirent.h>  
#include <stdio.h>
#include <cerrno>
using namespace std;
//std: 98


/*10.1
*have changed error problem BUT haven't
*/
FileManager::FileManager(const char* filename) {
    struct stat buf;
    int result;
    string ptr;
    char modeval[10] = "---------";

    result = stat(filename, &buf);
    //use stat() function to get information of the file;
    // first check return value and exit if there is an error
    if (result != 0) {
        printf("Failed to use stat function!");
        exit(1);
    }

    /*-----name----------*/
	name = filename;
    /*-----size----------*/
    size = buf.st_size;
    /*-----owner ID----------*/
    ownerID = buf.st_uid;
    /*-----owner name----------*/
    passwd* pw = getpwuid(buf.st_uid);
    if (pw != 0) {
        ownernm = pw->pw_name;
    }
    else {
        printf("Couldn't get the username");
        exit(1);
    }
    /*-----group ID----------*/
    groupID = buf.st_gid;
    /*-----group name----------*/
    group* gr = getgrgid(buf.st_gid);
    if (gr != 0) { groupnm = gr->gr_name; }
    else {
        printf("Couldn't get the group name!");
        exit(1);
    }

    /*-------file type----------*/
    if (S_ISREG(buf.st_mode)) {
        ptr = "regular";
    }
    else if (S_ISDIR(buf.st_mode)) {
        ptr = "directory";
    }
    else if (S_ISCHR(buf.st_mode)) {
        ptr = "character special";
    }
    else if (S_ISBLK(buf.st_mode)) {
        ptr = "block special";
    }
    else if (S_ISFIFO(buf.st_mode)) {
        ptr = "fifo";
    }
    else if (S_ISLNK(buf.st_mode)) {
        ptr = "symbolic link";
    }
    else if (S_ISSOCK(buf.st_mode)) {
        ptr = "socket";
    }
    else {
        ptr = "** nuknown mode **";
    }
    type = ptr;

    /*-----file permission----------*/
    mode_t perm = buf.st_mode;
    modeval[0] = (perm & S_IRUSR) ? 'r' : '-';
    modeval[1] = (perm & S_IWUSR) ? 'w' : '-';
    modeval[2] = (perm & S_IXUSR) ? 'x' : '-';
    modeval[3] = (perm & S_IRGRP) ? 'r' : '-';
    modeval[4] = (perm & S_IWGRP) ? 'w' : '-';
    modeval[5] = (perm & S_IXGRP) ? 'x' : '-';
    modeval[6] = (perm & S_IROTH) ? 'r' : '-';
    modeval[7] = (perm & S_IWOTH) ? 'w' : '-';
    modeval[8] = (perm & S_IXOTH) ? 'x' : '-';
    permission = modeval;
    /*-----Access time----------*/
    accessTime = buf.st_atime;
    /*-----modify time----------*/
    modifyTime = buf.st_mtime;
    /*-----status change time----------*/
    statusChangeTime = buf.st_ctime;
    /*-----block size----------*/
    blockSize = buf.st_blksize;

    /*-----children for directory----------*/
    if (S_ISDIR(buf.st_mode)) {
        Expand();
    }
    /*-----error number----------*/
    errnum = 0;

}

FileManager::~FileManager() { }

string FileManager::getname() {
    return name;
}

string FileManager::gettype() {
    return type;
}
off_t FileManager::getsize() {
    return size;
}
uid_t FileManager::getownerID() {
    return ownerID;
}
string FileManager::getownernm() {
    return ownernm;
}
gid_t FileManager::getgroupID() {
    return groupID;
}
string FileManager::getgroupnm() {
    return groupnm;
}
string FileManager::getpermission() {
    return permission;
}
static char * helper_ctime(long t){
	char* ct = ctime(&t);
	ct[strlen(ct)-1] = '\0';
    return ct;
}
char* FileManager::getaccessTime() {
    return helper_ctime(accessTime);
}
char* FileManager::getmodifyTime() {
	return helper_ctime(modifyTime);
}
char* FileManager::getstatusChangeTime() {
	return helper_ctime(statusChangeTime);
}

unsigned long FileManager::getblockSize() {
    return blockSize;
}
vector<FileManager> FileManager::getchildren() {
    return children;
}
void FileManager::seterrnum(int newerr) {
    errnum = newerr;

}
int FileManager::geterrInt() {
    return errnum;
}

string FileManager::geterrnomsg() {

    return strerror(geterrInt());
}

int file_size(fstream &file){
	file.seekg (0, file.end);
	int length = file.tellg();
    file.seekg (0, file.beg);
	return length;
}
/*
     * @param: file stream; (filename?
     * @return: error code
     * This function will take the filestream as an argument and dump the named file to that stream
     * (used to copy file and display contents...);use block_size to determine how much data will be read or written AT A TIME
     * should return error code if the operation not finished store the number in to a variable
* */
int FileManager::Dump(ostream& infile) {
    unsigned long size = blockSize;
    string thistype = gettype();
    char* buffer = new char[blockSize];

    //if the file is not a regular file, it can't be read
    if (thistype != "regular") {
        printf("wrong type of file in dump function!");
        seterrnum(ENOTSUP);
        return errnum;
    }

    fstream file(name, ios::binary|ios::in);
    if (!file.is_open()) {
        printf("wrong when DUMP file!");
        seterrnum(EIO);
        return errnum;
    }
	int length = file_size(file);
    while (!file.eof() && length > 0) {
		size = blockSize >= length ? length : blockSize;
        file.read(buffer, size);
        infile.write(buffer, size);
		length -= size;
    }
	delete []buffer;
    return 0;

}

int FileManager::Rename(const char* newname) {
	cout << name << endl;
	cout << newname << endl;
    if (rename(name, newname)) {
        seterrnum(errno);
        printf("wrong CHANGENAME\n");
    }else{
		seterrnum(0);
	}
    return errnum;

}

void FileManager::setname(const char* newname) {
    name = newname;
    Rename(newname);
}

int FileManager::Remove() {
    if (unlink(name)) {
        seterrnum(errno);
        printf("wrong REMOVE\n");
    }else{
		seterrnum(0);
		delete this;
	}
    return errnum;
}

int FileManager::Compare(FileManager &other) {
	fstream thisfile = fstream(name, ios::in);
	fstream otherfile = fstream(other.getname(), ios::in);
	int length1 = file_size(thisfile);
	int length2 = file_size(otherfile);
	if(length1 != length2){
		return 1;
	}
	char *buffer1 = new char[blockSize + 1];
	char *buffer2 = new char[blockSize + 1];
	while (!thisfile.eof() && length1 > 0) {
		int size = blockSize >= length1 ? length1 : blockSize;
        thisfile.read(buffer1, size);
        otherfile.read(buffer2, size);
		buffer1[size] = '\0';
		buffer2[size] = '\0';
		if(strcmp(buffer1, buffer2) != 0){
			return 1;
		}
		length1 -= size;
    }
	
	delete [] buffer1;
	delete [] buffer2;
	return 0;
}

int FileManager::Expand() {
	struct dirent* ent = NULL;
    DIR *pDir;
    pDir = opendir(name);
	if(pDir){
		while(NULL != (ent = readdir(pDir))) {
			if((!strncmp(ent->d_name, ".", 1)) || (!strncmp(ent->d_name, "..", 2)))
				continue;
			char *buf = new char[BUFSIZ];
			sprintf(buf, "%s/%s",name,ent->d_name);
			children.push_back(FileManager(buf));
		}
		closedir(pDir);
		seterrnum(0);
	}else{
		seterrnum(errno);
	}
    
	return errnum;
}
