#pragma once
#include "Mreza.h"
#include "Linija.h"
class CModel{
	struct Elem {
		Linija *izvor;
		set<Linija*> destinacije;
		Elem(Linija *s, set<Linija*> skup) :destinacije(skup), izvor(s) {}
	};
	vector<Elem*> niz;
	vector <Linija*> l;
public:
	CModel(Mreza m);

	void praviGML();
	void praviCSV();

	int getN() const { return niz.size(); }
	vector<Linija*> getL() const { return l; }
	vector<Elem*> getNiz()const { return niz; }
};

