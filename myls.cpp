#include<iostream>
#include<string>
#include<cstring>
#include "fileManager.h"

using namespace std;

static void print(FileManager &manager, bool use_l, bool is_last){
	if(use_l){
		if(manager.gettype() == "regular")
			cout << "-";
		else if(manager.gettype() == "directory")
			cout << "d";
		else if(manager.gettype() == "character special")
			cout << "c";
		else if(manager.gettype() == "block special")
			cout << "b";
		else if(manager.gettype() == "fifo")
			cout << "f";
		else if(manager.gettype() == "symbolic link")
			cout << "l";
		else if(manager.gettype() == "socket")
			cout << "s";
		else
			cout << "[unknown]";
		cout << manager.getpermission() << "\t";
		cout << manager.getownernm() << "\t";
		cout << manager.getgroupnm() << "\t";
		cout << manager.getsize() << "\t";
		cout << manager.getstatusChangeTime() << "\t";
	}
	char fname[BUFSIZ];
	sprintf(fname, "%s", manager.getname().c_str());
	fname[strlen(fname)] = '\0';
	char * name = strrchr(fname, '/');
    name = (name == NULL) ? fname : name + 1;
	cout << name;
	if(is_last || use_l){
		cout << endl;
	}else{
		cout << "    ";
	}
}
int main(int argc, char * argv[]) {
	char filename[BUFSIZ] = ".";
	bool use_l = false;
	if(argc > 1){
		for(int i = 1; i < argc && i <= 2; i++ ){
			if(strcmp(argv[i], "-l") == 0){
				use_l = true;
			}else{
				strcpy(filename, argv[i]);
			}
		}
	}
	FileManager manager(filename);
	if(manager.gettype() != "directory"){
		print(manager, use_l, true);
	}else{
		vector<FileManager> v = manager.getchildren();
		vector<FileManager>::const_iterator it;
		for(it = v.begin(); it != v.end(); ++it)
		{	
			FileManager child = *it;
			print(child, use_l, it == v.end() - 1);
		}
	}
    return 0;

}