#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Linija.h"
#include "Stajaliste.h"
#include "Mreza.h"
#include "CModel.h"
#include "LModel.h"
using namespace std;

int main() {

	Mreza m;
	m.ucitaj("data//_lines.txt");

	bool gen = false;
	int izbor=-1,pomint1,pomint2,pomint3;
	double geoX,geoY;
	string ime,ime2;
	CModel * cm = new CModel(m);
	LModel *lm = new LModel();

	while (izbor != 0) {
		cout << "MENI" << endl;
		cout << "1.Filtriranje" << endl << "2.Ispisivanje" << endl << "3.Ostalo" << endl << "4.Dodavanja/brisanje" <<endl<<"5.Generisanje grafa"<<endl;
		cout << "0.Izlaz" << endl;
		cin >> izbor;
		switch (izbor) {
		case 1:
			cout << "1.Na zone" << endl << "2.Na osnovu oznake" << endl << "3.Broj stajalista" << endl;
			cin >> izbor;
			switch (izbor) {
			case 1:
				cout << "Unesite zonu: ";
				cin >> izbor;
				m.filtrirajPoZoni(izbor);
				getchar();
				break;
			case 2:
				cout << "Unesite maksimalan broj linije: ";
				cin >> izbor;
				m.filtrirajPoOznaci(izbor);
				getchar();
				break;
			case 3:
				cout << "Unesite maksimalan broj stajalista kroz koja linija prolazi: ";
				cin >> izbor;
				m.filtrirajPoBrSt(izbor);
				getchar();
				break;
			default:
				cout << "Nepoznata komanda.\n";
				getchar();
				break;
			}
			break;
		case 2:
			cout << "Sta zelite da ispisete?" << endl << "1.Liniju" << endl << "2.Stajaliste"<<endl<<"3.Sve linije"<<endl;
			cin >> izbor;
			switch (izbor) {
			case 1:
				cout << "Unesite ime linije koju zelite da ispisete: ";
				cin >> ime;
				m.pisiLiniju(ime);
				getchar();
				break;
			case 2:
				cout << "Sta zelite da unesete?" << endl << "1.Broj" << endl << "2.Naziv" << endl;
				cin >> izbor;
				switch (izbor) {
				case 2:
					cout << "Unesite ime stanice koju zelite da ispisete: ";
					getchar();
					getline(cin, ime);
					m.pisiStanicu(ime);
					break;
				case 1:
					cout << "Unesite broj stanice koju zelite da ispisete: ";
					cin >> izbor;
					m.pisiStanicu(izbor);
					getchar();
					break;
				default:cout << "Nepoznata komanda." << endl; getchar();  break;
				}
				break;
			case 3:
				m.pisiSveLinije();
				getchar();
				break;
			default: cout << "Nepoznata komanda." << endl; getchar(); break;
			}
			break;
		case 3:
		cout << "1.Skup linija sa kojim data linija ima zajednicka stajalista" << endl << 
				"2.Da li data linija prolazi kroz zadata 2 stajalista u istom smeru svog kretanja" << endl << 
				"3.Linija sa kojom data linija ima najvise zajednickih stajalsita" << endl << 
				"4.Najblize stajaliste po datom geografskom polozaju (generalno ili u datoj liniji)" << endl << 
				"5.Broj zajednickih stajalista za sve parove koji imaju zajednicko stajaliste (uz mogucnost filtriranja na parove linija koje imaju zajednickih stajalista vise od zadatog broja)" << endl << 
				"6.Sve linije koje prolaze kroz dato stajalsite" << endl << 
				"7.Sva stajalista do kojih je moguce stici iz zadatog stajalista uz voznju maksimalno jednu stanicu" << endl << 
				"8.Najmanji potreban broj presedanja izmedju 2 zadata stajalsita" << endl <<
				"9.Najrkaci put izmedju 2 stajalsita(najmanji broj stajalista)" << endl;
			cin >> izbor;
			switch (izbor) {
			case 1: 
				cout << "Unesite ime linije za koju zelite da pronadjete zajednicka stajalista: ";
				cin >> ime;
				if (m.zajednickaStajalista1(ime).size() == 0) { getchar(); break; }
				else
					for (Linija *l: m.zajednickaStajalista1(ime))
					{
						l->pisiKrace(); cout << endl;
					}
				getchar();
				break;
			case 2:
				cout << "Unesite oznaku linije: ";
				cin >> ime;
				cout << "Unesite brojeve prvog i drugog stajalista: ";
				cin >> izbor >> pomint1;
				cout << (m.dvaStajalista2(ime, izbor, pomint1) ? "Prolazi\n" : "Ne prolazi\n");
				getchar();
				break;
			case 3:
				cout << "Unesite oznaku linije: ";
				cin >> ime;
				m.linijaSaLinijom3(ime);
				getchar();
				break;
			case 4:
				cout << "Da li zelite" << endl << "1.Najblize stajaliste generalno" << endl << "2.Najblize stajaliste za datu liniju" << endl;
				cin >> izbor;
				switch (izbor) {
				case 1:
					cout << "Unesite geografski polozaj: "; cin >> geoX >> geoY;
					cout << "Najblize stajaliste je " << m.najblizeStajalsite4(geoX,geoY)->getNaziv() << " #" << m.najblizeStajalsite4(geoX,geoY)->getBroj();
					break;
				case 2:
					cout << "Unesite geografski polozaj: "; cin >> geoX>>geoY;
					cout << "Unesite oznaku linije: "; cin >> ime;
					cout << "Najblize stajaliste je " << m.najblizeStajalsite4(geoX,geoY,ime)->getNaziv() << " #" << m.najblizeStajalsite4(geoX,geoY,ime)->getBroj();
					break;
				default:cout << "Nepoznata komanda." << endl; getchar();  break;
				}
				getchar();
				break;
			case 5:
				cout << "Da li zelite" << endl << "1.Bez granice" << endl << "2.Sa granicom" << endl;
				cin >> izbor;
				switch (izbor) {
				case 1:
					cout << "Unesite zeljenu liniju: "; cin >> ime;
					m.brZajednickih5(ime);
					break;
				case 2:
					cout << "Unesite zeljenu liniju: "; cin >> ime;
					cout << "Unesite donju granicu: "; cin >> izbor;
					m.brZajednickih5(ime,izbor);
					break;
				default:cout << "Nepoznata komanda." << endl; getchar();  break;
				}
				getchar();
				break;
			case 6:
					cout << "Unesite broj stanice koju zelite da ispisete: ";
					cin >> izbor;
					m.linijeKrozStanicu6(izbor);
					getchar();
					break;
			case 7:
				cout << "Unesite broj stajalista sa koga polazite: "; cin >> izbor;
				m.voznjaStanicu7(izbor);
				getchar();
				break;
			case 8:
				cout << "Stajaliste sa kog polazite: "; cin >> pomint1;
				cout << "Stajaliste na koje zelite doci: "; cin >> pomint2;
			    cout<< "Za datu destinaciju bice vam potrebno "<<m.najmanjiBrPresed8(pomint1,pomint2)<<" presedanja\n";
				getchar();
				break;
			case 9:
				cout << "Unesite stajaliste sa kojeg krecemo: "; cin >> pomint1;
				cout << "Unesite odredisno stajaliste: "; cin >> pomint2;
				m.najkraciPut9(pomint1, pomint2);
				getchar();
				break;
			default: cout << "Nepoznata komanda." << endl; getchar();  break;
			}
			break;
		case 4:
			cout << "Sta zelite da uradite" << endl << "1.Dodati" << endl << "2.Obrisati" << endl << "3.Izmeniti" << endl;
			cin >> izbor;
			switch (izbor) {
			case 1:
				cout << "Sta zelite dodati" << endl << "1.Stajalsite" << endl << "2.Liniju" << endl<<"3.Dodati stajaliste na putanju linije"<<endl;
				cin >> izbor;
				switch(izbor){
				case 1:
					cout << "Ime stajalista: "; cin >> ime;
					cout << "Broj stajalista: "; cin >> pomint1;
					if (!m.jelPostojiStajaliste(pomint1)|| pomint1!=0) {
						cout << "Unesite x pa y kooridnatu: "; cin >> geoX >> geoY;
						cout << "Unesite zonu stajalista: "; cin >> pomint2;
						Stajaliste *s = new Stajaliste(pomint1, ime, geoX, geoY, pomint2);
						Stajaliste::dodajUSvaStajalista(s);
						gen = false;
					}
					else
						cout << "Takvo stajaliste vec postoji" << endl;
					break;
				case 2:
					cout << "Unesite oznaku nove linije: ";
					cin >> ime;
					if (!m.jelPostojiLinija(ime)) {
						m.dodajNovuLiniju(ime);
						gen = false;
					}
					else
						cout << "Linija sa tom oznakom vec postoji" << endl;
					break;
				case 3:
					cout << "U koju liniju zelite da ubacite stanicu: "; cin >> ime;
					if (!m.jelPostojiLinija(ime)) { cout << "Takva linija ne postoji" << endl; break; }
					cout << "Koji je broj stajalista koje zelite da ubacite: "; cin >> pomint1;
					if (!m.jelPostojiStajaliste(pomint1)) { cout << "Takvo stajaliste ne postoji" << endl; break; }
					m.pisiLiniju(ime);

					cout << "Izmedju koje dve stanice zelite da ubacite zadato stajaliste[0 za neposotjanu stanicu]: "; cin >> pomint2 >> pomint3;
					m.ubaciStajaliste(pomint1,ime,pomint2,pomint3);
					gen = false;
					break;
				default:cout << "Nepoznata komanda." << endl; getchar();  break;
				}
				break;
			case 2:
				cout << "Sta zelite obrisati" << endl << "1.Stajalsite" << endl << "2.Liniju" << endl;
				cin >> izbor;
				switch (izbor) {
				case 1:
					cout << "Broj stajalista koje zelite da obrisete: "; cin >> pomint1;
					m.brisiStajaliste(pomint1);
					gen = false;
					break;
				case 2:
					cout << "Koju liniju zelite da obrisete: "; cin >> ime;
					m.brisiLiniju(ime);
					gen = false;
					break;
				default:cout << "Nepoznata komanda." << endl; getchar();  break;
				}
				break;
			case 3:
				cout << "Sta zelite izmeniti" << endl << "1.Ime stajalsita" << endl << "2.Ime linije" << endl;
				cin >> izbor;
				switch (izbor) {
				case 1:
					cout << "Unesite broj stajalista koje zelite da izmenite: "; cin >> pomint1; getchar();
					cout << "Unesite novo ime: "; getline(cin, ime2);
					m.promeniStajaliste(pomint1, ime2);
					gen = false;
					break;
				case 2:
					cout << "Koju liniju zelite da izmenite: "; cin >> ime;
					cout << "Unesite novo ime: "; cin >> ime2;
					m.promeniLiniju(ime, ime2);
					gen = false;
					getchar();
					break;
				default:cout << "Nepoznata komanda." << endl; getchar();  break;
				}
				break;
			default:cout << "Nepoznata komanda." << endl; getchar();  break;
			}
			getchar();
			break;

		case 5:
			cout << "Pomocu kog formata zelite da generisete graf" << endl << "1.GML" << endl << "2.CSV" << endl;
			cin >> pomint1;
			switch (pomint1) {
			case 1:
				cout << "Sta zelite da budu cvorovi grafa" << endl << "1.Linije" << endl << "2.Stajalista" << endl;
				cin >> pomint2;
				switch (pomint2) {
				case 1:
					cm->praviGML();
					gen = true;
					break;
				case 2:
					lm->praviGML();
					gen = true;
					break;
				default:cout << "Nepoznata komanda" << endl; break;
				}
				break;
			case 2:
				cout << "Sta zelite da budu cvorovi grafa" << endl << "1.Linije" << endl << "2.Stajalista" << endl;
				cin >> pomint2;
				switch (pomint2) {
				case 1:
					cm->praviCSV();
					gen = true;
					break;
				case 2:
					lm->praviCSV();
					gen = true;
					break;
				default:cout << "Nepoznata komanda" << endl; break;
				}
				break;
			default:cout << "Nepoznata komanda" << endl; break;
			}
			getchar();
			break;
		case 0: 
			cout << "Da li ste sigurni da zelite da napustite program?" << endl << "1.Da" << endl << "2.Ne" << endl;
			cin >> pomint1;
			switch (pomint1) {
			case 1:		
				if (gen != true)
				{
					cout << "Niste generisali graf nakon poslednjih promena" << endl << "Da li zelite da ga izgenerisete pre naoustanja?" << endl << "1.Da" << endl << "2.Ne" << endl;
					cin >> pomint1;
					switch (pomint1) {
					case 1:
						break;
					case 2:
						exit(1);
					}
				}
				else
					exit(1);
			case 2:
				izbor = -1;
				break;
			default:cout << "Nepoznata komanda" << endl; break;
			}
			getchar();
			break;
		default: cout << "Nepoznata komanda." << endl; getchar();  break;
		}
		cout << endl << "[Enter]";
		getchar();
		system("CLS");
	}
	
	system("pause");
}
