#include<iostream>
#include<string>
#include<cstring>
#include "fileManager.h"

using namespace std;

int main(int argc, char * argv[]) {
	if(argc != 3){
		cout << "Usage: " << argv[0] << " <file1> <file2>" << endl;
		return 1;
	}

	FileManager manager(argv[1]);
	int result = manager.Rename(argv[2]);
	if(result != 0){
		cout << manager.geterrnomsg() << endl;
	}
	
    return 0;
}