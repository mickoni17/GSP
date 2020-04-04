#pragma once
#include <cstdlib>
#include <iostream>
#include <set>
#include <fstream>
#include <string>
#include <regex>
#include <iomanip>
using namespace std;

class Linija;

class Stajaliste {
	static vector<Stajaliste*> svaStajalista;
	
	int broj;
	int zona;
	string naziv;
	double x, y;
	set<Linija*> linije;
public:
	
	Stajaliste(int broj, string naziv, double x, double y,int z) {
		this->broj = broj;
		this->naziv = naziv;
		this->x = x;
		this->y = y;
		zona = z;
	}
	
	//Setterg & Getters
	void setNaziv(string ime) { naziv = ime; }
	void setLinije(set<Linija*>l);
	string getNaziv()const;
	static vector<Stajaliste*> getSvaStajalista();
	int getBroj() const;
	set<Linija*> getLinije() const;
	double getX()const { return x; }
	double getY()const { return y; }

	//Razne funkcije
	static void dodajUSvaStajalista(Stajaliste* s);
	static Stajaliste* pokNaStanicu(Stajaliste*s1);
	Stajaliste dodajLiniju(Linija* l);
	static set<Stajaliste*> voznjaStanicu7(int br);
	static void brisiStajaliste(int br);
	void brisiLiniju(Linija*l);

	//Operatori
	friend bool operator<(const Stajaliste &s1, const Stajaliste &s2);
	friend bool operator>(const Stajaliste &s1, const Stajaliste &s2);
	friend ostream& operator<<(ostream &ot, const Stajaliste &s);
	friend bool operator==(const Stajaliste& s1, const Stajaliste& s2);

	friend class Linija;
};