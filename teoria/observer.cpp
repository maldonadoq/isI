#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

class bidder{
private:
	unsigned mn;
public:
	string name;
	bidder(string _name, unsigned m_){
		this->name = _name;
		this->mn = m_;
	}

	unsigned set_mon(unsigned a){
		if(this->mn < a){
			cout << "Without Money [Raioz]" << endl << endl;
			return 0;
		}
		unsigned i;
		bool t = true;
		while(t){
			cout << "  " << this->name << "	[money]	"; cin >> i;
			cout << endl;
			if((i>a and i<this->mn) or i==0)	break;
		}
		return i;
	}
};

class actioneer{
public:
	vector<bidder *> observers;
	string object;
	unsigned pr, cm;
	actioneer(){
		this->object = "";
		this->pr = 0;
	}

	void add_bidders(bidder *a){
		observers.push_back(a);
	}

	void set_object(string a, unsigned b){
		this->object = a;
		this->pr = b;
	}

	unsigned menu(){
		unsigned t;
		cout << "╔════════════════════════════╗" << endl;
		cout << "║        DOWN   UNDER        ║" << endl;
		cout << "╠════════════════════════════╣" << endl;
		cout << "║\t     " << this->object << "	     ║" << endl;
		cout << "║ PA: " << this->pr << "     ║   PP: " << this->pr+20 << "    ║" << endl;
		cout << "╚════════════════════════════╝" << endl;
		for(unsigned i=0; i<this->observers.size(); i++){
			if(i==this->cm)	cout << "	[" << i+1 << "]	" << this->observers[i]->name << " [P]" << endl;
			else	cout << "	[" << i+1 << "]	" << this->observers[i]->name << endl;
		}
		cout << "	[" << this->observers.size()+1 << "]	Exit" << endl;
		cout << "	[T]:	"; cin >> t;
		return t;
	}

	void notify(){
		bool t = true;
		unsigned tm, m;
		while(t){
			m = this->menu()-1;
			if(m>=0 and m<=this->observers.size()-1){
				tm = this->observers[m]->set_mon(this->pr);
				if(tm!=0){
					this->pr = tm;
					this->cm = m;
				}
			}
			else if(m == this->observers.size())	break;
		}
		cout << "╔════════════════════════════╗" << endl;
		cout << "║\t     " << this->observers[this->cm]->name << "	     ║" << endl;
		cout << "╚════════════════════════════╝" << endl;
	}

	~actioneer(){};
};

int main(int argc, char const *argv[]){
	actioneer *a = new actioneer();
	bidder *b = new bidder("Percy",1000);
	bidder *c = new bidder("Tobey",2342);
	bidder *d = new bidder("Rick",8723);
	bidder *e = new bidder("Cara",987);
	bidder *f = new bidder("Marcos",1232);

	a->set_object("CARRO",150);
	a->add_bidders(b);	a->add_bidders(c);
	a->add_bidders(d);	a->add_bidders(e);
	a->add_bidders(f);

	a->notify();
	return 0;
}