#ifndef _FUNC_H_
#define _FUNC_H_

#include <iostream>

using namespace std;

int menu(){
	int a;
	cout << "|    Cifrar Texto" << endl;
	cout << "|[1]: Gammal" << endl;
	cout << "|[2]: RSA" << endl;
	cout << "|[3]: Exit" << endl;
	cout << "|[n]: "; cin >> a;
	return a;
}

#endif	