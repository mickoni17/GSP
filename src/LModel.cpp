#include "LModel.h"
#include "Stajaliste.h"

LModel::LModel() {
	for (int i = 0; i < s.size(); i++) 
		niz.push_back(new Elem(s[i], Stajaliste::voznjaStanicu7(s[i]->getBroj())));
}
LModel& LModel::zameniSaPocetkom(int i) {
	Elem *e = niz[i];
	Stajaliste*st = s[i];
	niz[i] = niz[0];
	niz[0] = e;
	s[i] = s[0];
	s[0] = st;
	return*this;
}
vector<LModel::Elem*> LModel::getNiz()const { return niz; }
vector<Stajaliste*> LModel::getS()const { return s; }
bool LModel::dalPostojiPut(int k, Stajaliste* s)const {
	if (niz[k]->destinacije.count(s)) return true;
	return false;
}

void LModel::praviCSV(){

    ofstream f("CSV_Cvorovi.csv");

    for (int i = 0; i < niz.size(); i++) {
	    f << niz[i]->izvor->getBroj();
	    for (Stajaliste*l : niz[i]->destinacije)
		   f << ";" << l->getBroj();
		if (i != niz.size() - 1)
			f << endl;
	    }

    f.close();
	
}
void LModel::praviGML(){
	ofstream f("GML_Cvorovi.gml");
	int i = 0;
	f << "graph" << endl << "[" << endl;

	for (i = 0; i < niz.size(); i++) {
		f << "\tnode" << endl << "\t[" << "\t id " << niz[i]->izvor->getBroj() << endl << "\t label \"" << niz[i]->izvor->getBroj() << "\"" << endl << "\t]" << endl;
	}

	for (i = 0; i < niz.size(); i++) {
		if (niz[i]->destinacije.size() != 0)
			for (Stajaliste* l : niz[i]->destinacije)
				f << (i == 0 ? "\t edge" : "\tedge") << endl << "\t[" << endl << "\t source " << niz[i]->izvor->getBroj() << endl << "\t target " << l->getBroj() << endl << "\t]" << endl;
	}

	f << "]";
	f.close();
}