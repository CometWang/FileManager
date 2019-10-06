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
	FileManager manager1(argv[1]);
	FileManager manager2(argv[2]);
	int result = manager1.Compare(manager2);
	if(result){
		cout << "different" << endl;
	}else {
		cout << "same" << endl;
	}
    return 0;
}