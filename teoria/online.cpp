#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

class user{
private:
	string name, lastname, email, cel, city, password;
	unsigned year_b;
public:
	bool t;
	string state;
	vector<user *> observers;
	user(string a, string b, string c, string d, string e, string f, unsigned g){
		this->name = a;		this->lastname = b; 
		this->email = c;	this->password = d;
		this->cel = e;		this->city = f;
		this->year_b = g;
		this->t = false;
	}

	void add(user *a){
		for(unsigned i=0; i<this->observers.size(); i++){
			if(this->observers[i] == a)	return;
		}
		this->observers.push_back(a);
	}

	void friends(user *a){
		add(a);
		a->add(this);
	}

	void online(string a){
		this->t = true;
		this->state = a;
	}

	void offline(){	
		this->t = false;
		this->state = "";
	}

	void check(){
		cout << "[" << this->name << "] look:" << endl;
		for(unsigned i=0, j=0; i<observers.size(); i++){
			if(observers[i]->t == true){
				cout << "\t" << j << ": " << observers[i]->name << "\t[" << observers[i]->state << "]" << endl;
				j++;
			}
		}
		cout << endl;
	}

	void info_perfil(){
		cout << "name:		" << this->name << endl;
		cout << "lastname:	" << this->lastname << endl;
		cout << "email:		" << this->email << endl;
		cout << "cel:		" << this->cel << endl;
		cout << "city:		" << this->city << endl;
		cout << "born:		" << this->year_b << endl;
	}
};

int main(int argc, char const *argv[]){

	user *a = new user("Percy","Maldonado Quispe","percy.maldonado@ucsp.edu.pe","maldonado","","",1997);
	user *b = new user("Marcos","Aldea Chicllasto","marcos.aldea@ucsp.edu.pe","aldea","","",1996);
	user *c = new user("Paolo","Justo Ugarte","paolo.justo@gmail.com","potter","","",1998);
	user *d = new user("Tobias","Vincent Maguire","tobey.maguire@marvel.com","tobey","","",1995);

	b->friends(a);
	b->friends(c);
	b->friends(d);
	c->friends(d);
	c->friends(a);

	b->online("Ohh");
	a->online("Sape");
	c->online("Baia");
	d->online("Pero Peter!");
	
	a->check();
	b->check();
	c->check();
	d->check();

	a->offline();
	b->offline();
	c->offline();

	cout << "╔════════════════════════════╗" << endl;
	cout << "╚════════════════════════════╝" << endl << endl;

	a->check();
	b->check();
	c->check();
	d->check();

	delete a;	delete b;	delete c;	delete d;
	return 0;
}