#include <iostream>
#include <fstream>

using namespace std;

int main() {
	ofstream testFile;
	testFile.open("test.txt");
	testFile << "Testing, testing, 7 8 9\n";
	testFile << "Hello World!\n";
	testFile.close();
	string test;
	cout << getline(testFile, test);
}
