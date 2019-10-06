#include<iostream>
#include<string>
#include<cstring>
#include "fileManager.h"

using namespace std;

int main(int argc, char * argv[]) {
	
	if(argc < 2){
		cout << "Usage: " << argv[0] << " <file1> [file2...]" << endl;
		return 1;
	}
	for(int i = 1; i < argc; i++){
		char filename[BUFSIZ];
		strcpy(filename, argv[i]);
		FileManager manager(filename);
		manager.Dump(cout);
	}
	
    return 0;
}
