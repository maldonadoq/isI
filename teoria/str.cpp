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

	void cifrar(FILE *t_pl, ZZ c_pu, ZZ N){
		ZZ t_cif, c1 = ZZ(0);
		string tb = to_string(alfa.size());
		int bq1 = tb.size(), p, c;
		ZZ bq3 = ZZ(zz_to_str(N).size());

		string sms = "", temp, aux, str;
		bool tr = true;

		t_c = fopen("sws/t_ci.dat", "w");
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

	void descifrar(FILE *t_c){
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

		t_dc = fopen("sws/t_dc.dat", "w");
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

	ZZ resto_chino_rsa(ZZ w){
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
	
	void cifrar(FILE *t_pl, ZZ pb, ZZ gb, ZZ eb){
		int bl = zz_to_str(pb).size(), po;
		ZZ ra = modulo(RandomPrime_ZZ(bl), pb-4)+2;
		ZZ c1 = exp_mod(gb, ra, pb);
		cout << endl << "c1:   " << c1 << endl;
		ZZ k = exp_mod(eb, ra, pb);
		
		char c;
		string asd="", sms="", aux;
		ZZ temp;

		while((c=getc(t_pl))!=EOF){
			po = alfa.find(c);
			aux = to_string(po);
			sms += con_zero(aux,ZZ(2));
		}

		t_c = fopen("sws/t_ci.dat", "w");
		for(int i=0; i<sms.size(); i++){
			asd += sms[i];
			if(asd.size()==bl-1){
				ZZ num(INIT_VAL, asd.c_str());
				temp = modulo(num*k,pb);
				load_bq_(t_c, zz_to_str(temp), ZZ(bl));
				asd = "";
			}
		}

		if(asd.size()!=bl-1){
			while(asd.size()!=bl-1) asd+="0";
			ZZ num(INIT_VAL, asd.c_str());
			temp = modulo(num*k,pb);
			load_bq_(t_c, zz_to_str(temp), ZZ(bl));
		}
		fclose(t_c);
	}

	void descifrar(FILE *t_ci, ZZ c){
		char aux;
		string num = "", te = "", aux1, wq = "", ms="";
		ZZ rt, w = euc_ext(exp_mod(c,this->d,this->p),p);
		int n;
		bool t = true;
		while((aux=getc(t_ci))!=EOF){
			num += aux;
			if(num.size() == this->mb){
				ZZ temp(INIT_VAL, num.c_str());
				rt = modulo(w*temp, this->p);
				aux1 = zz_to_str(rt);
				te += con_zero(aux1, (ZZ)this->mb-1);
				num = "";
			}
		}

		t_dc = fopen("sws/t_dc.dat", "w");
		for(int i=0; i<te.size(); i++){
			wq+=te[i];
			if(wq.size()==2){
				int b = atoi(wq.c_str());
				ms += alfa[b];
				wq = "";
			}
		}
		load_bq(t_dc,ms);
		fclose(t_dc);
	}

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
	while(t){
		d = menu();
		switch(d){
			case 1:{
				gammal_ *gam  = new gammal_(r);
				cont->set_strategy(gam);
				cont->do_it();
				delete gam;
				break;
			}
			case 2:{
				rsa *rs = new rsa(r);
				cont->set_strategy(rs);
				cont->do_it();
				delete rs;
				break;
			}
			case 3:
				t = false;
				break;
		}
	}
	delete cont;
	return 0;
}