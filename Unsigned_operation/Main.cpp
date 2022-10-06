#include <iostream>
#include "Operation.h"
using namespace std;
int main()
{
	long long a = 999;
	int b = 100;

	Operation c(a);
	Operation d(b);
	

	cout << (c == d) << endl << endl;
	cout << (c != d) << endl << endl;
	cout << (c + d) << endl << endl;
	cout << (c * d) << endl << endl;

	string aa = "999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999";
	string bb = "9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999";

	Operation cc(aa);
	Operation dd(bb);


	cout << (cc == dd) << endl << endl;
	cout << (cc != dd) << endl << endl;
	cout << (cc + dd) << endl << endl;
	cout << (cc * dd) << endl << endl;
}