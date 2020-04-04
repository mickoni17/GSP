#include "Mreza.h"
#include "Stajaliste.h"
#include "LModel.h"


int minDistance(int *d, int n,int *ispitani) {
	int min=INT_MAX;
	for (int i = 0; i < n; i++)
		if (d[i] <= min && ispitani[i] == 0)
			min = i;
	return min;
}

//Operatori
ostream& operator<<(ostream& ot, const Mreza& m) {
	for (Linija* l : m.gsp)
		ot << *l << endl;
	return ot;
}

//Razne funkcije
void Mreza::ucitaj(string fileName) {
	ifstream file(fileName);//Otvaranje _lines
	if (file.is_open()) {
		string s;
		regex reg("([^!]*)!([^!]*)!([^!]*).");
		while (getline(file, s)) { //Citanje linija iz datoteke _lines
			smatch res;
			if (regex_match(s, res, reg)) {
				string fName, c = res.str(1);
				Linija *novaLinija=new Linija(c);

				for (int i = 0; i < 2; i++) { //Ucitavanje datoteka linije A i B
					(i == 0 ? fName = "data//" + c + "_dirA.txt" : fName = "data//" + c + "_dirB.txt");
					ifstream f(fName);
					if (f.is_open()) {
						string t;
						regex ex("([^!]*)!([^!]*)!([^!]*)!([^!]*)!(.)");
						while (getline(f, t)) {
							smatch result;
							if (regex_match(t, result, ex)) {  //Kreiraj stajaliste
								string naziv = result.str(2);
								int br = atoi(result.str(1).c_str());
								double x = atof(result.str(3).c_str());
								double y = atof(result.str(4).c_str());
								int z = atoi(result.str(5).c_str());
								Stajaliste *novoSt = new Stajaliste(br, naziv, x, y, z);
								
								if (z > novaLinija->getZona()) novaLinija->setZona(z);

								if (novoSt->pokNaStanicu(novoSt) == nullptr) { //Ukoliko stajaliste ne postoji, dodaj u sva stajalista
									novoSt->dodajLiniju(novaLinija);
									novoSt->dodajUSvaStajalista(novoSt);
								}
								else {                                      //Ukoliko vec postoji stajaliste, dodaj mu novu liniju
									novoSt = novoSt->pokNaStanicu(novoSt);
									novoSt->dodajLiniju(novaLinija);
								}
								
								novaLinija->dodaj((i == 0 ? "A" : "B"), novoSt); //Dodaj stajaliste na putanju linije
								
							}

						}

					}
					else
						cout << "Datoteka nije pronadjena.." << endl;

				}
				gsp.push_back(novaLinija);
			}


		}
	}
	else
		cout << "Greska u otvaranju datoteke.." << endl;
	file.close();
}

void Mreza::pisiStanicu(string i) const {
	bool flag=false;
	for (Stajaliste* s : Stajaliste::getSvaStajalista())
		if (s->getNaziv() == i) {
			cout << *s << endl;
			flag = true;
		}
	if (flag == false)
	cout << "Takva stanica ne postoji." << endl;
	return;
}
void Mreza::pisiStanicu(int br) const{
	bool flag = false;
	for (Stajaliste* s : Stajaliste::getSvaStajalista())
		if (s->getBroj() == br) {
			cout << *s << endl;
			flag = true;
		}
	if (flag == false)
		cout << "Takva stanica ne postoji." << endl;
	return;
}
void Mreza::pisiLiniju(string i) const {
	for (Linija* l : gsp) 
		if (l->getOznaka() == i) {
			cout << *l << endl;
			return;
		}
	cout << "Takva linija ne postoji." << endl;
	return;
}
void Mreza::pisiSveLinije() const {
	for(Linija *l:gsp)
	{
		l->pisiKrace(); cout << endl;
	}
}

void Mreza::filtrirajPoZoni(int i)const {
	for (Linija* l : gsp) {
		if (l->getZona() <= i && l->getZona()!=0) {
			l->pisiKrace();
			cout << endl;
		}
	}
}
void Mreza::filtrirajPoOznaci(int i) const {
		for (Linija* l : gsp) {
		regex ex("([A-Z]*|[a-z]*)([0-9]*).*");
		string s = l->getOznaka();
		smatch res;
		if (regex_match(s, res, ex)) {
			int br = atoi(res.str(2).c_str());
			if (br <= i) {
				l->pisiKrace(); cout << endl;
			}
		}
	}
}
void Mreza::filtrirajPoBrSt(int i) const {
	for (Linija* l : gsp) 
		if (l->getBrStajalista() <= i) { l->pisiKrace(); cout << endl; }
}

set<Linija*> Mreza::zajednickaStajalista1(string ime) const {
	set<Linija*> skup;
	for (Linija* l : gsp) if (l->getOznaka() == ime) {
		for (int i = 0; i < 2; i++) {
			for (Stajaliste* s : (i == 0 ? l->getSmerA() : l->getSmerB())) {
				for (Linija *l: s->getLinije())
					if (l->getOznaka()!=ime)skup.insert(l);
			}
		}
		return skup;
	}
		cout << "Greska! Data linija nije pronadjena." << endl;
		return skup;
}
bool Mreza::dvaStajalista2(string ime,int s1, int s2) const {
	pair<bool, bool> par;
	for (Linija* l : gsp) if (l->getOznaka()==ime){
		for (int i = 0; i < 2; i++) {
			par.first = false; par.second = false;
			for (Stajaliste * s : (i == 0 ? l->getSmerA() : l->getSmerB()))
			{
				if (s->getBroj() == s1) par.first = true;
				if (s->getBroj() == s2) par.second = true;
				if (par.first == true && par.second == true) return true;
			}
		}
		return false;
	}
	cout << "Linija nije pronadjena" << endl;
	return false;
}
void Mreza::linijaSaLinijom3(string ime) const {
	for (Linija* l : gsp) if (l->getOznaka() == ime) {
		map<Linija, int> m;
		for (int i = 0; i < 2; i++) {
			for (Stajaliste * s : (i == 0 ? l->getSmerA() : l->getSmerB()))
				for (Linija *l : s->getLinije()) {
					if (l->getOznaka() == ime)continue;
					auto it = m.find(*l);
					if (it == m.end()) 
						m[*l] = 1;			
					else 
						m[*l] = m[*l] + 1;					
				}
		}
		using pt = pair<Linija, int>;
		pt ret=*max_element(m.begin(), m.end(), [](pt a, pt b)->bool {return a.second < b.second; });
		cout << "Linija " << ime << " ima najvise zajednickih stajalsita sa linijom " << ret.first.getOznaka() << " i to " << ret.second;
		return;
	}
	cout << "Linija nije pronadjena" << endl;
}
Stajaliste* Mreza::najblizeStajalsite4(double geox,double geoy) const {
	vector<Stajaliste*> myCopy = Stajaliste::getSvaStajalista();
	return *min_element(myCopy.begin(), myCopy.end(), [&](Stajaliste* s1, Stajaliste* s2)->bool { return sqrt(pow((s1->getX() - geox), 2.0) + pow(abs(s1->getY() - geoy), 2.0)) < sqrt(pow(abs(s2->getX() - geox), 2.0) + pow(abs(s2->getY() - geoy), 2.0)); });
}
Stajaliste* Mreza::najblizeStajalsite4(double geox,double geoy, string ime) const {
vector<Stajaliste*> myCopy = Stajaliste::getSvaStajalista();
sort(myCopy.begin(), myCopy.end(), [&](Stajaliste* s1, Stajaliste* s2)->bool { return sqrt(pow((s1->getX() - geox), 2.0) + pow(abs(s1->getY() - geoy), 2.0)) < sqrt(pow(abs(s2->getX() - geox), 2.0) + pow(abs(s2->getY() - geoy), 2.0)); });
for (Stajaliste* s : myCopy) {
	for (Linija* l : s->getLinije())
		if (l->getOznaka() == ime)
			return s;
}
cout << "Dato stajaliste ne postoji" << endl;
return nullptr;
}
void Mreza::brZajednickih5(string ime) const{
	for (Linija* l : gsp) if (l->getOznaka() == ime) {
		map<Linija, int> m;
		for (int i = 0; i < 2; i++) {
			for (Stajaliste * s : (i == 0 ? l->getSmerA() : l->getSmerB()))
				for (Linija *l : s->getLinije()) {
					if (l->getOznaka() == ime)continue;
					auto it = m.find(*l);
					if (it == m.end())
						m[*l] = 1;
					else
						m[*l] = m[*l] + 1;
				}
		}
		for_each(m.begin(), m.end(), [](pair<Linija, int> l)->void { l.first.pisiKrace();cout << " , " << l.second << " zajednickih"<<endl; });
		return;
	}
	cout << "Linija nije pronadjena" << endl;
}
void Mreza::brZajednickih5(string ime,int br) const {
	for (Linija* l : gsp) if (l->getOznaka() == ime) {
		map<Linija, int> m;
		for (int i = 0; i < 2; i++) {
			for (Stajaliste * s : (i == 0 ? l->getSmerA() : l->getSmerB()))
				for (Linija *l : s->getLinije()) {
					if (l->getOznaka() == ime)continue;
					auto it = m.find(*l);
					if (it == m.end())
						m[*l] = 1;
					else
						m[*l] = m[*l] + 1;
				}
		}
		for_each(m.begin(), m.end(), [=](pair<Linija, int> l) {if (l.second >= br) { l.first.pisiKrace(); cout << " , " << l.second << " zajednickih"<<endl; } });
		return;
	}
	cout << "Linija nije pronadjena" << endl;
}
void Mreza::linijeKrozStanicu6(string ime) const{
	for (Stajaliste* s : Stajaliste::getSvaStajalista())
		if (s->getNaziv() == ime) {
			for (Linija* l : s->getLinije()) { l->pisiKrace(); cout << endl; }
			return;
		}
		cout << "Takva stanica ne postoji." << endl;
}
void Mreza::linijeKrozStanicu6(int br) const {
	for (Stajaliste* s : Stajaliste::getSvaStajalista())
		if (s->getBroj() == br) {
			for (Linija* l:s->getLinije()){l->pisiKrace();cout << endl;}
			return;
		}
	cout << "Takva stanica ne postoji." << endl;
}
void Mreza::voznjaStanicu7(int br)const {
	for (Stajaliste* s : Stajaliste::voznjaStanicu7(br))
		cout << *s << endl;
}
int Mreza::najmanjiBrPresed8(int b1, int b2) const {
	int ret = 0;
	vector<Stajaliste*> myCopy = Stajaliste::getSvaStajalista();
	auto it = find_if(myCopy.begin(), myCopy.end(), [=](Stajaliste*s)->bool {return s->getBroj() == b1; });
	set<Linija*> skup;
	for (Linija*l : (*it)->getLinije()) {
		vector<Stajaliste*> myCopyA = l->getSmerA();
		vector<Stajaliste*> myCopyB = l->getSmerB();

		auto it1 = find_if(myCopyA.begin(), myCopyA.end(), [=](Stajaliste*s)->bool {return s->getBroj() == b2; });
		if (it1 != myCopyA.end()) return ret;
		auto it2 = find_if(myCopyB.begin(), myCopyB.end(), [=](Stajaliste*s)->bool {return s->getBroj() == b2; });
		if (it2 != myCopyB.end()) return ret;

		skup.insert(l);
	}   
	set<Linija*> skup2;
	while (ret != 5) {
		ret++;
		for (Linija*l : skup) {
			for (Linija*l2:zajednickaStajalista1(l->getOznaka()))
				skup2.insert(l2);
		}
		for (Linija*l : skup2) {
			vector<Stajaliste*> myCopyA = l->getSmerA();
			vector<Stajaliste*> myCopyB = l->getSmerB();

			auto it1 = find_if(myCopyA.begin(), myCopyA.end(), [=](Stajaliste*s)->bool {return s->getBroj() == b2; });
			if (it1 != myCopyA.end()) return ret;
			auto it2 = find_if(myCopyB.begin(), myCopyB.end(), [=](Stajaliste*s)->bool {return s->getBroj() == b2; });
			if (it2 != myCopyB.end()) return ret;
		}
		skup = skup2;
	}
}
void Mreza::najkraciPut9(int s1, int s2)const {
	LModel *lm = new LModel();
	int src = 0;
	for (Stajaliste*s : lm->getS())
		if (s->getBroj() == s1) {
			lm->zameniSaPocetkom(src);
			break;
		}
		else
			src++;

	int n = lm->getN();
	int *d; //Stajaliste **t; 
	int *ispitani;
	d = new int[n]; //t = new Stajaliste*[n]; 
	ispitani = new int[n];

	for (int i = 0; i < n; i++)
	{
		ispitani[i] = 0; d[i] = INT_MAX - 1;
	}
	d[0] = 0;
	ispitani[0] = 1;

	for (int i = 1; i < n; i++) {
		if (lm->dalPostojiPut(0, lm->getS()[i]) == true)
			d[i] = 1;
		/*if (lm->dalPostojiPut(0,lm->getS()[i]) == false)
		t[i] = lm->getS()[0];
		else
		t[i] = nullptr;*/
	}

	for (int k = 0; k < n - 1; k++) {

		int i = minDistance(d, n, ispitani);
		ispitani[i] = 1;

		for (int v = 0; v < n; v++) {
			if (lm->dalPostojiPut(i, lm->getSodI(v)) && d[i] + 1 < d[v]) {
				d[v] = d[i] + 1;
				//t[v] = t[i];
			}
		}
	}
	cout << "Najkraci put izmedju stanice " << s1 << " i " << s2 << " je ";
	int i = 0;
	for (Stajaliste *s : lm->getS())
		if (s->getBroj() == s2) {
			cout << d[i];
			return;
		}
		else
			i++;
}

void Mreza::dodajNovuLiniju(string ime) {
	Linija* l=new Linija(ime);
	gsp.push_back(l);
}
bool Mreza::jelPostojiLinija(string ime)const {
	for (Linija* l : gsp)
		if (l->getOznaka() == ime) return true;
	return false;
}
bool Mreza::jelPostojiStajaliste(int pom)const {
	for (Stajaliste *s : Stajaliste::getSvaStajalista())
		if (pom == s->getBroj())return true;
	return false;
}
Mreza& Mreza::ubaciStajaliste(int pomint1, string ime, int pomint2, int pomint3) {
	for (Linija* l : gsp) if (l->getOznaka() == ime) {
		//Izuzetan slucaj
		if (pomint2 == 0 || pomint3 == 0) {
			for (Stajaliste* s : Stajaliste::getSvaStajalista())if (s->getBroj() == pomint1) {
					s->dodajLiniju(l);

				cout << "U koji smer zelite da ubacite stanicu: ";
				string smer; cin >> smer;
				if (smer != "a" && smer != "A" & smer != "b" && smer != "B")
				{cout << "Neispravan smer" << endl; return *this;}
				if (smer == "A" || smer == "a") {
					if (pomint2 == 0 && pomint3 == 0) {
						l->dodajNaPoziciju(s, 0, "A");
						return *this;
					}
					if (pomint2 == 0) l->dodajNaPoziciju(s, 0, "A");
					if (pomint3 == 0) l->dodajNaPoziciju(s, l->getSmerA().size(), "A");
					return *this;
				}
				else {
					if (pomint2 == 0 && pomint3 == 0) {
						l->dodajNaPoziciju(s, 0, "B");
						return *this;
					}
					if (pomint2 == 0) l->dodajNaPoziciju(s, 0, "B");
					if (pomint3 == 0) l->dodajNaPoziciju(s, l->getSmerA().size(), "B");
					return *this;
				}
			}
		}
		else {
			vector<Stajaliste*> myCopyA = l->getSmerA();
			vector<Stajaliste*> myCopyB = l->getSmerB();

			int br = 0;
			auto it1 = find_if(myCopyA.begin(), myCopyA.end(), [&](Stajaliste*s)->bool {br++; return s->getBroj() == pomint2 || s->getBroj() == pomint3; });
			if (it1 != myCopyA.end()) {
				for (Stajaliste* s : Stajaliste::getSvaStajalista())
					if (s->getBroj() == pomint1) {
						s->dodajLiniju(l);
						l->dodajNaPoziciju(s, br, "A");
						return *this;
					}
			}
			br = 0;
			auto it2 = find_if(myCopyB.begin(), myCopyB.end(), [&](Stajaliste*s)->bool {br++; return s->getBroj() == pomint2 || s->getBroj() == pomint3; });
			for (Stajaliste* s : Stajaliste::getSvaStajalista())
				if (s->getBroj() == pomint1) {
					s->dodajLiniju(l);
					l->dodajNaPoziciju(s, br, "B");
					return *this;
				}
		}
	}
}
Mreza& Mreza::brisiLiniju(string ime) {
	

	vector<Linija*> myCopy = gsp;
	int br = 0;
	auto it = find_if(myCopy.begin(), myCopy.end(), [&](Linija*l)->bool {br++; return l->getOznaka() == ime; });
	if (it != myCopy.end()) {

		for (Stajaliste* s : Stajaliste::getSvaStajalista()) if (s->getLinije().count((*it))){
			s->brisiLiniju(*it);
		}
		gsp.erase(gsp.begin() + br-1);
		return*this;
	}
	cout << "Takva linija ne postoji" << endl;
	return *this;
}
Mreza& Mreza::brisiStajaliste(int pomint1) {
	if (jelPostojiStajaliste(pomint1)) {
		for (Stajaliste*s : Stajaliste::getSvaStajalista())if (s->getBroj() == pomint1) {
			set<Linija*> lin = s->getLinije();
			while(!lin.empty()) {
				Linija*l = *lin.begin();

				for (Linija* l2 : gsp) if (l->getOznaka()==l2->getOznaka()){
					vector<Stajaliste*> myCopyA = l->getSmerA();
					vector<Stajaliste*> myCopyB = l->getSmerB();

					auto it1 = find_if(myCopyA.begin(), myCopyA.end(), [=](Stajaliste*s)->bool {return s->getBroj() == pomint1; });
					if (it1 != myCopyA.end()) { l->brisiStajaliste(pomint1,"A"); break; }
					auto it2 = find_if(myCopyB.begin(), myCopyB.end(), [=](Stajaliste*s)->bool {return s->getBroj() == pomint1; });
					if (it2 != myCopyB.end()) { l->brisiStajaliste(pomint1,"B"); break; }
				}
				lin.erase(l);
			}
			break;
		}
		Stajaliste::brisiStajaliste(pomint1);
		return *this;
	}
	cout << "Takvo stajaliste ne postoji" << endl;
	return *this;
}
void Mreza::promeniLiniju(string ime, string ime2){
	for (Linija*l : gsp) if (ime == l->getOznaka()) {
		l->setOznaka(ime2);
		return;
	}
	cout << "Linija nije pronadjena" << endl;
}
void Mreza::promeniStajaliste(int pomint1, string ime2) {
	for (Stajaliste*s : Stajaliste::getSvaStajalista()) if (s->getBroj() == pomint1){ s->setNaziv(ime2); return;
	}cout << "Stajaliste nije pronadjeno" << endl;
}
