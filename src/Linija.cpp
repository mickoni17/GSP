#include "Linija.h"
#include "Stajaliste.h"
using namespace std;

//Operatori
bool operator<(const Linija &l1, const Linija &l2) { return l1.oznaka < l2.oznaka; }
ostream& operator<<(ostream &ot, const Linija &l) {
	ot << "Linija " << l.getOznaka() << " smer A:" << endl;
	for (Stajaliste* s : l.smerA) ot << (*s);
	ot << endl << endl;
	ot << "Linija " << l.getOznaka() << " smer B:" << endl;
	for (Stajaliste* s : l.smerB) ot << (*s);
	ot << endl << endl;
	return ot;
}
bool operator==(const Linija& l1, const Linija&l2) {
	return l1.getOznaka() == l2.getOznaka();
}

//Setters & Getters
void Linija::setZona(int k) { zona = k; }
int Linija::getZona() const { return zona; }
string Linija::getOznaka()const { return oznaka; }
int Linija::getBrStajalista() const {
	int sum = 0;
	if (smerA.size() != 0) sum += smerA.size();
	if (smerB.size() != 0) sum += smerB.size();
	return sum;
}
vector<Stajaliste*> Linija::getSmerA() const { return smerA; }
vector<Stajaliste*> Linija::getSmerB() const { return smerB; }

//Razne funkcije
void Linija::dodaj(string c, Stajaliste* s) { (c == "A" || c == "a" ? smerA.push_back(s) : smerB.push_back(s)); }
void Linija::pisiKrace() const {
	cout << setw(6) << oznaka << "   " << (smerA.size() ? smerA.front()->getNaziv() : "") << " / " << (smerA.size() ? smerA.back()->getNaziv() : "");
}
Linija& Linija::dodajNaPoziciju(Stajaliste* s, int i, string smer) {
	if (i > smerA.size() && (smer == "A" || smer == "a"))
		smerA.push_back(s);
	if (i > smerB.size() && (smer == "B" || smer == "b"))
		smerB.push_back(s);
	else
	(smer == "A" ? smerA.insert(smerA.begin() + i, s) : smerB.insert(smerB.begin() + i, s));
	return *this;
}
Linija& Linija::brisiStajaliste(int br, string c) {
	int i = 0;
	if (c == "A") {
		for (Stajaliste* s : smerA)
		if (s->getBroj() == br)
		{
			smerA.erase(smerA.begin() + i);
			break;
		}
		else 
			i++;
	}
	else {
		for (Stajaliste* s : smerB)
			if (s->getBroj() == br)
			{
				smerB.erase(smerB.begin() + i);
				break;
			}
			else
				i++;
	}

	return *this;
}
