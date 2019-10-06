#include<iostream>
#include<string>
#include<cstring>
#include "fileManager.h"

using namespace std;

int main(int argc, char * argv[]) {
	char filename[BUFSIZ] = ".";
	if(argc > 1){
		strcpy(filename, argv[1]);
	}
	FileManager manager(filename);
	cout << "Name: " << manager.getname() << endl;
	cout << "Type: " << manager.gettype() << endl;
	cout << "Size: " << manager.getsize() << "\t\tBlock size: " << manager.getblockSize() << endl;
	cout << "Owner: " << manager.getownernm() << "\t\tUid: " << manager.getownerID() << endl;
	cout << "Group: " << manager.getgroupnm() << "\t\tGid: " << manager.getgroupID() << endl;
	cout << "Permissions: " << manager.getpermission() << endl;
	cout << "Access time: " << manager.getaccessTime() << endl;
	cout << "Modification time: " << manager.getmodifyTime() << endl;
	cout << "Status change time: " << manager.getstatusChangeTime() << endl;
	
	// if(manager.gettype() != "directory"){
		// cout << "-";
		// cout << manager.getpermission() << "\t";
		// cout << manager.getgroupnm() << "\t";
		// cout << manager.getownernm() << "\t";
		// cout << manager.getsize() << "\t";
		// cout << manager.getstatusChangeTime() << "\t";
		// cout << manager.getname() << endl;
	// }else{
		
	// }
    return 0;
}