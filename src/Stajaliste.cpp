#include "Stajaliste.h"
#include "Linija.h"

//Operatori
ostream& operator<<(ostream &ot, const Stajaliste &s) {
	ot << setw(6) << s.broj << "   " <<
		setw(45) << left << s.naziv << right <<
		setw(4) << fixed << setprecision(4) << s.x << ", " <<
		setw(4) << fixed << setprecision(4) << s.y << "     ";
	ot << " { ";
	for (Linija *l : s.linije)
		ot << (*l).getOznaka() << " ";
	ot << "}" << endl;
	return ot;
}
bool operator<(const Stajaliste &s1, const Stajaliste &s2) { return s1.broj < s2.broj; }
bool operator>(const Stajaliste &s1, const Stajaliste &s2) { return s1.broj > s2.broj; }
bool operator==(const Stajaliste& s1, const Stajaliste& s2) {return s1.broj == s2.broj;}

//Setters & Getters
string Stajaliste::getNaziv()const { return naziv; }
int Stajaliste::getBroj() const { return broj; }
vector<Stajaliste*> Stajaliste::getSvaStajalista() {return svaStajalista;}
set<Linija*> Stajaliste::getLinije() const { return linije; }
void Stajaliste::setLinije(set<Linija*>l) { linije = l; }

//Razne funckije
Stajaliste Stajaliste::dodajLiniju(Linija* l) { 
	linije.insert(l); 
	return *this;
}
void Stajaliste::dodajUSvaStajalista(Stajaliste* s) {
	svaStajalista.push_back(s);
}
Stajaliste* Stajaliste::pokNaStanicu(Stajaliste *s1) {
	for (Stajaliste *s : svaStajalista)
		if (s->getBroj() == s1->getBroj()) 
			return s;

	return nullptr;
}
set<Stajaliste*> Stajaliste::voznjaStanicu7(int br) {
	set<Stajaliste*> skup;
	for (Stajaliste* s : Stajaliste::getSvaStajalista()) if (s->getBroj() == br) {
		for (Linija* l : s->getLinije())
			for (int i = 0; i < 2; i++) {
				vector<Stajaliste*> myCopy = (i == 0 ? l->getSmerA() : l->getSmerB());
				for (auto it = myCopy.begin(); it < myCopy.end(); it++)
					if ((*it)->getBroj() == br)
						if ((it + 1) == myCopy.end())
						{
							if (i == 0)
							{
								if (l->getSmerB().size() != 0)
									skup.insert(*l->getSmerB().begin());
							}
							else
								if (l->getSmerA().size() != 0)
									skup.insert(*l->getSmerA().begin());
						}
						else
							skup.insert(*(it + 1));
			}
		return skup;
	}
	cout << "Stanica nije pronadjena" << endl;
	return skup;
}
void Stajaliste::brisiStajaliste(int br) {
	int i = 0;
	for (Stajaliste* s : svaStajalista)
		if (s->getBroj() == br)
		{
			svaStajalista.erase(svaStajalista.begin() + i);
			break;
		}
		else
			i++;
}
void Stajaliste::brisiLiniju(Linija*l) {
	linije.erase(l);
}


vector<Stajaliste*> Stajaliste::svaStajalista;