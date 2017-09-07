#include <iostream>
#include <stdio.h>
#include "src/func.h"
#include <NTL/ZZ.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <unistd.h>
#include <sys/time.h>
#include <thread> 
#include <future>
#include "../../../Abstracta/func/func.cpp"
#include "../../../Abstracta/func/random.cpp"
#include "../../../Abstracta/func/rsa_fun.cpp"

using namespace std;
using namespace NTL;

static string alfa = "0123456789,abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ-.()";

class strategy{
public:
	FILE *t_c, *t_dc;
	strategy(){	};
	virtual void inf() = 0;
	virtual void enc() = 0;
	virtual void dec() = 0;

	void execute(){
		bool t = true;
		int d;
		while(t){
			cout << endl << "1: Información" << endl;
			cout << "2: Cifrar" << endl;
			cout << "3: Descifrar" << endl;
			cout << "4: Exit" << endl;
			cout << "x: "; cin >> d;
			switch(d){
				case 1:
					this->inf();
					break;
				case 2:
					this->enc();
					break;
				case 3:
					this->dec();
					break;
				case 4:
					t = false;
					cout << endl;
					break;
			}
		}
	}
	virtual ~strategy(){	};
};


class rsa: public strategy{
private:
	ZZ p, q ,c_pr;
	vector<ZZ> _p, _q, P, dpq;
public:
	vector<ZZ> criba;
	ZZ c_pu, N;
	rsa(long int t){
		this->p = RandomPrime_ZZ(t);
		this->q = RandomPrime_ZZ(t);
		this->c_pu = RandomPrime_ZZ(t);

		ZZ ps = (p-1)*(q-1);
		this->c_pr = euc_ext(c_pu, ps);
		this->N = p*q;

		_p.push_back(p);
		_p.push_back(q);

		_q.push_back(euc_ext(modulo(q,p),p));
		_q.push_back(euc_ext(modulo(p,q),q));
		
		P.push_back(q);
		P.push_back(p);

		dpq.push_back(modulo(c_pr, p-1));
		dpq.push_back(modulo(c_pr, q-1));
	}

	void inf(){
		cout << endl << "c_pu:  " << this->c_pu << endl;
		cout << "N:  " << this->N << endl;
	}	
	void enc(){
		ZZ c_pu, N;
		cout << endl << "clave publica: "; cin >> c_pu;
		cout << "N: "; cin >> N;
		FILE *t_pl = fopen("sws/t_pl.dat", "r");
		cifrar(t_pl,c_pu,N);
		fclose(t_pl);
	}
	void dec(){
		FILE *t_c = fopen("sws/t_ci.dat", "r");
		descifrar(t_c);
		fclose(t_c);
	}

	void cifrar(FILE *t_pl, ZZ c_pu, ZZ N);
	void descifrar(FILE *t_c);
	ZZ resto_chino_rsa(ZZ w);

	virtual ~rsa(){	};
};

class gammal_ : public strategy{
private:
	int mb, na;
	ZZ e, p, g, d, r;
public:
	gammal_(int t){
		this->p = RandomPrime_ZZ(t);
		this->g = generador(this->p);
		this->d = modulo(RandomPrime_ZZ(t), p-4)+2;
		this->e = exp_mod(this->g, this->d, this->p);

		this->mb = zz_to_str(this->p).size();
		this->na = alfa.size();
	}
	void inf(){
		cout << endl << "p:  " << this->p << endl;
		cout << "g:  " << this->g << endl;
		cout << "e:  " << this->e << endl;
	}
	void enc(){
		ZZ pb,gb,eb;
		cout << endl << "pb: "; cin >> pb;
		cout << "gb: "; cin >> gb;
		cout << "eb: "; cin >> eb;
		FILE *t_pl = fopen("sws/t_pl.dat", "r");
		cifrar(t_pl,pb, gb, eb);
		fclose(t_pl);
	}
	void dec(){
		FILE *t_c = fopen("sws/t_ci.dat", "r");
		ZZ b;
		cout << endl << "cb: ";	cin >> b;
		descifrar(t_c,b);
		fclose(t_c);
	}
	
	void cifrar(FILE *t_pl, ZZ pb, ZZ gb, ZZ eb);
	void descifrar(FILE *t_ci, ZZ c);
	~gammal_(){	};
};


class encrypted{
private:
	strategy *str;
public:
	encrypted(){	this->str = NULL;	}
	void set_strategy(strategy *_a){	this->str = _a;		}
	void do_it(){	this->str->execute();	}
	~encrypted(){	};
};


int main(int argc, char const *argv[]){
	encrypted *cont = new encrypted();
	bool t = true;
	int d, r=100;
	gammal_ *gam  = new gammal_(r);
	rsa *rs = new rsa(r);
	while(t){
		d = menu();
		switch(d){
			case 1:
				cont->set_strategy(gam);
				cont->do_it();
				break;
			case 2:
				cont->set_strategy(rs);
				cont->do_it();
				break;
			case 3:
				t = false;
				break;
		}
	}
	delete cont;
	return 0;
}