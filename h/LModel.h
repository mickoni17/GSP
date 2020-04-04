#pragma once
#include "Mreza.h"
#include "Stajaliste.h"
class LModel{
	struct Elem {
		Stajaliste *izvor;
		set<Stajaliste*> destinacije;
		Elem(Stajaliste *s,set<Stajaliste*> skup):destinacije(skup),izvor(s){}
	};
	vector<Elem*> niz;
	vector <Stajaliste*> s= Stajaliste::getSvaStajalista();
public:
	LModel();

	void praviGML();
	void praviCSV();

	int getN()const { return niz.size(); }
	LModel& zameniSaPocetkom(int i);
	vector<Stajaliste*> getS() const;
	Stajaliste* getSodI(int i) { return s[i]; }
	vector<Elem*> getNiz()const;
	bool dalPostojiPut(int k, Stajaliste* s)const;
};

