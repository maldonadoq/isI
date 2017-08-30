#include <iostream>
#include "src/time.h"

using namespace std;

class state{
public:
	virtual void ejecuta_accion() = 0;
	virtual ~state(){	};
};

class red_light : public state{
public:
	void ejecuta_accion(){
		cout << "traffic_light: RED                   time: 5s" << endl;
		wait(5);
	}
};

class green_light : public state{
public:
	void ejecuta_accion(){
		cout << "traffic_light: GREEN                 time: 5s" << endl;
		wait(5);
	}
};

class yellow_light : public state{
public:
	void ejecuta_accion(){
		cout << "traffic_light: YELLOW                time: 2s" << endl;
		wait(2);
	}
};

class traffic_light{
private:
	static traffic_light *unico4;
	state *mi_state;
public:
	static traffic_light* get_instance(){
		if(unico4 == NULL)
			unico4 = new traffic_light();
		return unico4;
	}
	void set_state(state *e){
		this->mi_state = e;
	}
	void ejecutar_accion(){
		mi_state->ejecuta_accion();
	}
};

traffic_light *traffic_light::unico4 = NULL;


int main(int argc, char const *argv[]){
	traffic_light *traffic = traffic_light::get_instance();
	red_light *red = new red_light();
	green_light *green = new green_light();
	yellow_light *yellow = new yellow_light();
	
	int asd[4] = {1,2,3,4};
	int n = 10;
	int opcion;
	menu();
	int i = 0;
	do{
		opcion = asd[i];
		switch(opcion){
			case 1:
				traffic->set_state(red);
				break;
			case 2:
				traffic->set_state(yellow);
				break;
			case 3:
				traffic->set_state(green);
				break;
			case 4:
				traffic->set_state(yellow);
				break;
		}
		traffic->ejecutar_accion();

		i++;
		n--;
		if(i > 3) i = 0;
	}
	while(true and n>0);

	delete red;	delete yellow;	delete green;	delete traffic;
	return 0;
}