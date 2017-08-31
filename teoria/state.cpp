#include <opencv2/core/core.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include "src/time.h"

using namespace cv;
using namespace std;

class state{
public:
	Mat src;
	int x, y, r, t, R, G, B;
	string name;
	virtual void ejecuta_accion() = 0;
	state(){
		this->src = Mat(400, 400, CV_8UC3, Scalar(0));
		this->x = this->y = 200;
		this->r = 150;
	}
	void on(){
		circle(src, Point(this->x,this->y),this->r, Scalar(R,G,B),CV_FILLED, 8,0);
		imshow(this->name, src);
		waitKey(this->t);
	}
	void off(){
		this->src = Mat(400, 400, CV_8UC3, Scalar(0));
		imshow(this->name, src);
	}
	virtual ~state(){	};
};

class red_light : public state{
public:
	red_light(int _t){	
		this->name = "Traffic Light [RED]";
		this->t = _t;
		this->R = 0;	this->G = 0;	this->B = 255;
	}
	void ejecuta_accion(){
		cout << this->name << ":                   time: 4s" << endl;
		on();	off();
	}
};

class green_light : public state{
public:
	green_light(int _t){	
		this->name = "Traffic Light [GREEN]";
		this->t = _t;
		this->R = 43;	this->G = 154;	this->B = 15;
	}
	void ejecuta_accion(){
		cout << this->name << ":                 time: 5s" << endl;
		on();	off();
	}
};

class yellow_light : public state{
public:
	yellow_light(int _t){	
		this->name = "Traffic Light [YELLOW]";
		this->t = _t;
		this->R = 0;	this->G = 255;	this->B = 255;
	}
	void ejecuta_accion(){
		cout << this->name << ":                time: 2s" << endl;
		on();	off();
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
	red_light *red = new red_light(4000);
	green_light *green = new green_light(5000);
	yellow_light *yellow = new yellow_light(2000);
	
	int asd[4] = {1,2,3,4};
	int n = 20;
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