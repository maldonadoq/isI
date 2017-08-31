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

static string alfa = "0123456789,abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ-.";

class strategy{
public:
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
					enc();
					break;
				case 3:
					dec();
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
	FILE *t_c, *t_dc;
	vector<ZZ> _p, _q, P, dpq;
public:
	vector<ZZ> criba;
	double time;
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

	ZZ resto_chino_rsa(ZZ);
	void inf(){
		cout << endl << "c_pu:  " << this->c_pu << endl;
		cout << "N:  " << this->N << endl;
		cout << "size:  " << ZZ(zz_to_str(this->N).size()) << endl;
		//printf("time:  %.28f\n", alice->time/1000);
	}	
	void enc(){
		ZZ c_pu, N;
		cout << endl << "clave publica: "; cin >> c_pu;
		cout << "N: "; cin >> N;
		FILE *t_pl = fopen("sws/t_pl.txt", "r");
		cifrar(t_pl,c_pu,N);
		fclose(t_pl);
	}
	void dec(){
		FILE *t_c = fopen("sws/t_ci.txt", "r");
		decifrar(t_c);
		fclose(t_c);
	}

	void cifrar(FILE *t_pl, ZZ c_pu, ZZ N){
		ZZ t_cif, c1 = ZZ(0);
		string tb = to_string(alfa.size());
		int bq1 = tb.size(), p, c;
		ZZ bq3 = ZZ(zz_to_str(N).size());

		string sms = "", temp, aux, str;
		bool tr = true;

		t_c = fopen("sws/t_ci.txt", "w");
		while(tr){
			c=getc(t_pl);
			if(c!=EOF){
				p = alfa.find(c);
				aux = to_string(p);
				if(aux.size() != bq1) aux = con_zero(aux, ZZ(bq1));
			}
			temp = sms;
			sms += aux;
			ZZ num(INIT_VAL, sms.c_str());
			if(c==EOF){
				ZZ num_(INIT_VAL, temp.c_str());
				str = zz_to_str(exp_mod(num_, c_pu, N));
				load_bq_(t_c, str, bq3);
				tr = false;
			}
			else if(num>N){
				ZZ nu(INIT_VAL, temp.c_str());
				str = zz_to_str(exp_mod(nu, c_pu, N));
				load_bq_(t_c, str, bq3);
				sms = aux;
			}
		}
		fclose(t_c);
	}

	void decifrar(FILE *t_c){
		ZZ bq1 = ZZ((zz_to_str(ZZ(alfa.size()))).size());
		ZZ bq3 = ZZ(zz_to_str(this->N).size());
		ZZ temp = ZZ(0);

		char c;
		string num = "", sms = "", str;
		while((c=getc(t_c))!=EOF){
			temp++;
			num += c;
			if(temp == bq3){
				ZZ aux(INIT_VAL, num.c_str());
				str = zz_to_str(resto_chino_rsa(aux));
				sms += str;
				num = "";
				temp = ZZ(0);
			}
		}

		t_dc = fopen("sws/t_dc.txt", "w");
		string ind = "";
		for(unsigned i=0; sms[i]!='\0'; i++){
			ind += sms[i];
			if(ind.size() == bq1){
				int b = atoi(ind.c_str());
				fprintf(t_dc,"%c",alfa[b]);
				ind = "";
			}
		}
		fclose(t_dc);
	}

	ZZ rsa::resto_chino_rsa(ZZ w){
		ZZ x = ZZ(0), a, ad;
		for(long int j=0;j<_p.size();j++){
			ad = modulo(w, _p[j]); //saca modulo de t_cifr con p o q respe
			a = exp_mod(ad, dpq[j],_p[j]); //saca el a , para cada uno
			x+= a*P[j]*_q[j];
		}
		x = modulo(x, N);
		return x;
	}

	virtual ~rsa(){	};
};

class gammal_ : public strategy{
public:
	gammal_(){	};
	void inf(){	};
	void enc(){	};
	void dec(){	};
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
	rsa *rs = new rsa(10);
	gammal_ *gam  = new gammal_();
	bool t = true;
	int d;
	while(t){
		d = menu();
		switch(d){
			case 1:{
				cont->set_strategy(gam);
				cont->do_it();
				break;
			}
			case 2:{
				cont->set_strategy(rs);
				cont->do_it();
				break;
			}
			case 3:
				t = false;
				break;
		}
	}
	return 0;
}