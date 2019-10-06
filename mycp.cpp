#include<iostream>
#include<string>
#include<cstring>
#include "fileManager.h"

using namespace std;

int main(int argc, char * argv[]) {
	
	if(argc != 3){
		cout << "Usage: " << argv[0] << " <src> <dist>" << endl;
		return 1;
	}

	FileManager manager(argv[1]);
	fstream dist(argv[2], ios::binary|ios::out);
	if(!dist.is_open()){
		cout << "open failed" << endl;
	}
	int result = manager.Dump(dist);
	if(result != 0){
		cout << manager.geterrnomsg() << endl;
	}
	dist.close();
    return 0;
}
