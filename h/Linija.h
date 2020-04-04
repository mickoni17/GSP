#pragma once
#include <cstdlib>
#include <iostream>
#include <set>
#include <fstream>
#include <string>
#include <regex>
#include <iomanip>
using namespace std;

class Stajaliste;

class Linija {
	string oznaka;
	vector<Stajaliste*> smerA,smerB;
	int zona=0;
public:
	Linija(string oznaka) { this->oznaka = oznaka; }
	
	//Setters & Getters
	void setZona(int k);
	void setOznaka(string i) { oznaka = i; }
	int getZona() const;
	string getOznaka()const;
	int getBrStajalista() const;
	vector<Stajaliste*> getSmerA() const;
	vector<Stajaliste*> getSmerB() const;
	
	//Razne funkcije
	void dodaj(string c, Stajaliste* s);
	void pisiKrace() const;
	Linija& dodajNaPoziciju(Stajaliste* s, int i, string smer);
	Linija& brisiStajaliste(int br, string c);

	//Operatori
	friend ostream& operator<<(ostream &ot, const Linija &l);
	friend bool operator<(const Linija &l1, const Linija &l2);
	friend bool operator==(const Linija& l1, const Linija&l2);
};