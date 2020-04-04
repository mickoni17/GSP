#include "CModel.h"

CModel::CModel(Mreza m) {
	l = m.getGsp();
	for (int i = 0; i < l.size(); i++)
		niz.push_back(new Elem(l[i], m.zajednickaStajalista1(l[i]->getOznaka())));
}
void CModel::praviGML() {
	ofstream f("GML_Linije.gml");
	int i = 0;
	f << "graph" << endl<<"["<<endl;

	for (i = 0; i < niz.size(); i++) {
       	f << "\tnode" << endl << "\t[" << "\t id " << niz[i]->izvor->getOznaka() << endl << "\t]" << endl;
	}

	set<pair<string, string>> skup;
	for (i=0; i < niz.size(); i++) {
		if (niz[i]->destinacije.size()!=0)
			for (Linija* l : niz[i]->destinacije) {
				skup.insert(pair<string,string>(niz[i]->izvor->getOznaka(), l->getOznaka()));
				pair<string, string> p2(l->getOznaka(), niz[i]->izvor->getOznaka());
				if (!skup.count(p2))
				f << (i == 0 ? "\t edge" : "\tedge") << endl << "\t[" << endl << "\t source " << niz[i]->izvor->getOznaka() << endl << "\t target " << l->getOznaka() << endl << "\t]" << endl;
			}
	}

	f << "]";
	f.close();
}
void CModel::praviCSV() {
	ofstream f("CSV_Linije.csv");
	
	set<pair<string, string>> skup;
	for (int i = 0; i < niz.size(); i++) {
		f << niz[i]->izvor->getOznaka(); 
		for (Linija*l : niz[i]->destinacije) {
			skup.insert(pair<string, string>(niz[i]->izvor->getOznaka(), l->getOznaka()));
			pair<string, string> p2(l->getOznaka(), niz[i]->izvor->getOznaka());
			if (!skup.count(p2))
			f << ";" << l->getOznaka();
		}
		if(i!=niz.size()-1)
		f << endl;
	}
	f.close();
}