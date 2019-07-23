#include <iostream>
#include "directory.h"
using namespace std;
int main() {
	{
		Directory mydir;
		mydir.add();
		cout << mydir.data[0];
	}
	system("pause");
	return 0;
}