#ifndef _TIME_H_
#define _TIME_H_

#include <time.h>
#include <iostream>

using namespace std;

void menu(void){
	cout << "1.- red_light" << endl;
	cout << "2.- yellow_light" << endl;
	cout << "3.- green_light" << endl << endl;
}

void wait(int seg){
 	time_t t1;
 	time_t t2;

  	(void)time(&t1);
	do
 		(void)time(&t2);
  	while (int(t2-t1) < seg);
}

#endif