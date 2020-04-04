#pragma once
#include <iostream>
#include <vector>
#include <regex>
#include <map>
#include "Linija.h"
using namespace std;

class Mreza {

	vector<Linija*> gsp;

public:

	//Getters & Setters
	int getBrLinija()const { return gsp.size(); }
	vector<Linija*> getGsp()const { return gsp; }

	//Razne funkcije
	void ucitaj(string fileName);//F-ja za ucitavanje svih linija

    void pisiLiniju(string i) const;
	void pisiStanicu(string i) const;
	void pisiStanicu(int br) const;
	void pisiSveLinije() const;

	void filtrirajPoZoni(int i) const;
	void filtrirajPoOznaci(int i) const;
	void filtrirajPoBrSt(int i) const;
	
	set<Linija*> zajednickaStajalista1(string ime) const;
	bool dvaStajalista2(string ime,int s1, int s2) const;
	void linijaSaLinijom3(string ime) const;
	Stajaliste* najblizeStajalsite4(double geoX,double geoY) const;
	Stajaliste* najblizeStajalsite4(double geoX,double geoY,string ime) const;
	void brZajednickih5(string ime) const;
	void brZajednickih5(string ime, int br) const;
	void linijeKrozStanicu6(string ime) const;
	void linijeKrozStanicu6(int br) const;
	void voznjaStanicu7(int br) const;
	int najmanjiBrPresed8(int b1, int b2) const;
	void najkraciPut9(int s1, int s2)const;

	void dodajNovuLiniju(string ime);
	bool jelPostojiLinija(string ime)const;
	bool jelPostojiStajaliste(int pom)const;
	Mreza& ubaciStajaliste(int pomint1,string ime,int pomint2,int pomint3);
	Mreza& brisiLiniju(string ime);
	Mreza& brisiStajaliste(int pomint1);
	void promeniLiniju(string ime, string ime2);
	void promeniStajaliste(int pomint1, string ime2);

	//Operatori
	friend ostream& operator<<(ostream& ot, const Mreza& m);
	
};
