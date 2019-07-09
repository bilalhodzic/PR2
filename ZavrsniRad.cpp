﻿#include<iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
using namespace std;

/****************************************************************************
1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR ĆE BITI OZNACENO KAO "RE"
3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJEČILO GUBLJENJE URAĐENOG ZADATKA
4. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIČNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U, OSIM U SLUČAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOĆNE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
5. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNAČENO.
****************************************************************************/
mutex m;
const char* nedozvoljena_operacija = "Nedozvoljena operacija";
const char* not_set = "NOT_SET";
const int min_polgavlja = 3;
const int min_karaktera_po_poglavlju = 30;

char* AlocirajNizKaraktera(const char* sadrzaj) {
	if (sadrzaj == nullptr)
		return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}

template<class T1, class T2>
class Kolekcija {
	T1* _elementi1;
	T2* _elementi2;
	int _trenutno;
public:
	Kolekcija() :_trenutno(0), _elementi1(nullptr), _elementi2(nullptr) { }
	Kolekcija(const Kolekcija& obj) {
		_trenutno = obj._trenutno;
		_elementi1 = new T1[_trenutno];
		_elementi2 = new T2[_trenutno];
		for (size_t i = 0; i < _trenutno; i++)
		{
			_elementi1[i] = obj._elementi1[i];
			_elementi2[i] = obj._elementi2[i];

		}

	}
	Kolekcija& operator=(const Kolekcija& obj) {
		if (this != &obj) {
			_trenutno = obj._trenutno;
			delete[]_elementi1;
			delete[]_elementi2;
			_elementi1 = new T1[_trenutno];
			_elementi2 = new T2[_trenutno];
			for (size_t i = 0; i < _trenutno; i++)
			{
				_elementi1[i] = obj._elementi1[i];
				_elementi2[i] = obj._elementi2[i];

			}
		}return*this;

	}

	void AddElement(const T1& elem1, const T2& elem2) {

		for (int i = 0; i < _trenutno; i++)
			if (_elementi1[i] == elem1 || _elementi2[i] == elem2)
				throw exception(nedozvoljena_operacija);

		T1 * temp1 = new T1[_trenutno + 1];
		T2 * temp2 = new T2[_trenutno + 1];
		for (int i = 0; i < _trenutno; i++) {
			temp1[i] = _elementi1[i];
			temp2[i] = _elementi2[i];
		}
		delete[] _elementi1; _elementi1 = nullptr;
		delete[] _elementi2; _elementi2 = nullptr;
		_elementi1 = temp1;
		_elementi2 = temp2;

		_elementi1[_trenutno] = elem1;
		_elementi2[_trenutno++] = elem2;

	}

	T1* getElementi1Pok() { return _elementi1; }
	T2* getElementi2Pok() { return _elementi2; }
	T1& getElement1(int lokacija) { return _elementi1[lokacija]; }
	T2& getElement2(int lokacija) { return _elementi2[lokacija]; }
	int getTrenutno() { return _trenutno; }

	friend ostream& operator<<(ostream& COUT, Kolekcija<T1, T2>& obj) {
		for (size_t i = 0; i < obj._trenutno; i++)
			COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
		return COUT;
	}
};
class Poglavlje {
	char* _naslov;
	char* _sadrzaj;
	bool _prihvaceno;
	int _ocjena;//da bi se poglavlje smatralo prihvacenim ocjena mora biti u opsegu od 6 - 10
public:
	Poglavlje(const char* naslov = nullptr, const char* sadrzaj = nullptr)
		:_ocjena(0), _prihvaceno(false) {
		_naslov = AlocirajNizKaraktera(naslov);
		_sadrzaj = AlocirajNizKaraktera(sadrzaj);
	}
	Poglavlje(const Poglavlje& obj) {
		_naslov = AlocirajNizKaraktera(obj._naslov);
		_sadrzaj = AlocirajNizKaraktera(obj._sadrzaj);
		_prihvaceno = obj._prihvaceno;
		_ocjena = obj._ocjena;
	}
	Poglavlje& operator=(const Poglavlje& obj) {
		if (this != &obj) {
			delete[]_naslov;
			delete[]_sadrzaj;
			_naslov = AlocirajNizKaraktera(obj._naslov);
			_sadrzaj = AlocirajNizKaraktera(obj._sadrzaj);
			_prihvaceno = obj._prihvaceno;
			_ocjena = obj._ocjena;
		}
		return*this;
	}
	Poglavlje() {
		delete[] _naslov; _naslov = nullptr;
		delete[] _sadrzaj; _sadrzaj = nullptr;
	}
	friend ostream& operator<<(ostream& COUT, Poglavlje& obj) {
		if (obj._naslov == nullptr || obj._sadrzaj == nullptr)
			return COUT;
		COUT << endl << obj._naslov << endl << obj._sadrzaj << endl;
		if (obj._prihvaceno)
			COUT << "Ocjena: " << obj._ocjena << endl;;
		return COUT;
	}
	char* GetNaslov() { return _naslov; }
	char* GetSadrzaj() { return _sadrzaj; }
	int BrojKaraktera() {
		int brojac = 0;
		
		for (size_t i = 0; i < strlen(_sadrzaj) - 1; i++)
		{
			brojac++;
		}
		return brojac;
		
	}
	bool GetPrihvaceno() { return _prihvaceno; }
	int GetOcjena() { return _ocjena; }
	bool operator==(const Poglavlje& obj) {
		return strcmp(_naslov, obj._naslov) == 0;
	}
	void SetSadrzaj(const char* s) {
		string string = _sadrzaj;
		string += " ";
		string += s;
		delete[]_sadrzaj;
		_sadrzaj = AlocirajNizKaraktera(string.c_str());
	}

	void OcijeniPoglavlje(int ocjena) {
		_ocjena = ocjena;
		if (_ocjena > 5 && ocjena <= 10)
			_prihvaceno = true;
	}
};

class ZavrsniRad {
	char* _tema;
	vector<Poglavlje> _poglavljaRada;
	string _datumOdbrane;
	float _konacnaOcjena; //prosjek ocjena svih poglavlja u zavrsnom radu koja se izracunava u momentu zakazivanja odbrane
public:
	ZavrsniRad(const char* nazivTeme = nullptr) : _konacnaOcjena(0), _datumOdbrane(not_set) {
		_tema = AlocirajNizKaraktera(nazivTeme);
	}

	ZavrsniRad(const ZavrsniRad& org) : _poglavljaRada(org._poglavljaRada), _konacnaOcjena(org._konacnaOcjena), _datumOdbrane(org._datumOdbrane) {
		_tema = AlocirajNizKaraktera(org._tema);
	}
	ZavrsniRad& operator=(const ZavrsniRad& org) {
		if (this != &org) {
			delete[]_tema;
			_tema = AlocirajNizKaraktera(org._tema);
			_poglavljaRada = (org._poglavljaRada);
			_konacnaOcjena = (org._konacnaOcjena);
			_datumOdbrane = (org._datumOdbrane);
		}
		return *this;
	}
	~ZavrsniRad() {
		delete[] _tema; _tema = nullptr;
	}
	char* GetNazivTeme()const { return _tema; }
	vector<Poglavlje>& GetPoglavlja() { return _poglavljaRada; };
	string GetDatumOdbrane()const { return _datumOdbrane; }
	void setDatumOdbrane(string d){
		_datumOdbrane = d;
	}
	void setKonacnu(float d) {
		_konacnaOcjena= d;
	}

	float GetOcjena() { return _konacnaOcjena; }
	friend ostream& operator<<(ostream& COUT, ZavrsniRad& obj) {
		COUT << "Tema rada: " << obj._tema << endl;
		COUT << "Sadrzaj: " << endl;
		for (size_t i = 0; i < obj._poglavljaRada.size(); i++)
			COUT << obj._poglavljaRada[i] << endl;
		COUT << "Datum odbrane rada: " << obj._datumOdbrane << endl << " Ocjena: " << obj._konacnaOcjena << endl;
		return COUT;
	}
	
	void DodajPoglavlje(const char* naziv, const char* sadrzaj) {
		Poglavlje temp(naziv, sadrzaj);
		bool flag = false;
		for (vector<Poglavlje>::iterator i = _poglavljaRada.begin(); i !=_poglavljaRada.end(); i++)
		{
			if (*i == temp) {
				
				i->SetSadrzaj(sadrzaj);
				flag = true;
			}
		}
		if (!flag) {
			_poglavljaRada.push_back(temp);
		}
	}
	const int BrojPoglavlja() const{
		return _poglavljaRada.size() ;
	}
	const int BrojKaraktera(int i) {
		return _poglavljaRada[i].BrojKaraktera();
	}
	void OcijeniPoglavlje(const char* naziv, int ocjena) {
		for (size_t i = 0; i < _poglavljaRada.size(); i++)
		{
			if (strcmp(_poglavljaRada[i].GetNaslov(),naziv)==0) {
				_poglavljaRada[i].OcijeniPoglavlje(ocjena);
			}
		}
	}
	bool operator==(const ZavrsniRad& obj) {
		if (_tema != nullptr)
			return strcmp(_tema, obj._tema) == 0;
		else
			return false;
	}
	float IzracunajKonacnu() {
		float suma = 0;
		for (size_t i = 0; i < _poglavljaRada.size(); i++)
		{
			suma += _poglavljaRada[i].GetOcjena();
		}
		return suma / (_poglavljaRada.size() - 1);
	}

};

class Osoba {
protected:
	string _imePrezime;
public:
	Osoba(string imePrezime) : _imePrezime(imePrezime) {}
	string GetImePrezime() { return _imePrezime; }
	virtual void Info() = 0 {
		cout << _imePrezime << endl;
	}
};

class Nastavnik: public Osoba{
	//Parametar string predstavlja broj indeksa studenta koji prijavljuje zavrsni rad kod odredjenog nastavnika
	Kolekcija<string, ZavrsniRad> _teme;
public:
	void sendMail(Nastavnik n, int i) {
		m.lock();
		cout << "FROM::  brojIndeksa@edu.fit.ba " << endl;
		cout << "Postovani " << _teme.getElement1(i) << ", uzimajuci u obzir cinjenicu da" <<
			" ste kod mentora " << n._imePrezime << " uspjesno odbranili rad sa ocjenom " << n._teme.getElement2(i).GetOcjena() <<
			"cast nam je pozvati vas na dodjelu nagrada za najbolje studente koja ce se " <<
			"odrzatu u na FIT - u 20.09.2018.godine." << endl;
		m.unlock();
	}
	Nastavnik(string ime) :Osoba(ime) {};
	Kolekcija<string, ZavrsniRad>& GetTeme() { return _teme; };
	void Info() {
		cout << endl << "    NASTAVNIK    " << endl;
		Osoba::Info();
		for (size_t i = 0; i < _teme.getTrenutno(); i++)
		{
			cout << _teme.getElement1(i) << " " << _teme.getElement2(i) << endl;
		}
	}
	
	bool DodajZavrsniRad(string s,const  ZavrsniRad &rad) {
		for (size_t i = 0; i < _teme.getTrenutno(); i++)
		{
			if (_teme.getElement1(i)==s || _teme.getElement2(i)== rad) {
			
				return false;
			}
		}
		_teme.AddElement(s, rad);
		return true;
	}
	
	ZavrsniRad* ZakaziOdbranuRada(string index, string datum) {
		for (size_t i = 0; i < _teme.getTrenutno(); i++)
		{
			if (_teme.getElement1(i) == index) {
				if (int(_teme.getElement2(i).BrojPoglavlja()) >= min_polgavlja) {
					float suma = 0;
					for (size_t j = 0; j < _teme.getElement2(i).GetPoglavlja().size(); j++)
					{
						if (_teme.getElement2(i).BrojKaraktera(j)<min_karaktera_po_poglavlju
							||!(_teme.getElement2(i).GetPoglavlja()[j].GetPrihvaceno())) {
							return nullptr;
						}
						suma += _teme.getElement2(i).GetPoglavlja()[j].GetOcjena();
					}
					suma = suma / _teme.getElement2(i).GetPoglavlja().size();
					_teme.getElement2(i).setKonacnu(suma);
					_teme.getElement2(i).setDatumOdbrane(datum);
					return &_teme.getElement2(i);
				}
				
			}
		}
		return nullptr;
	}
	friend ostream& operator<<(ostream& COUT, Nastavnik& obj) {
		COUT << obj._imePrezime << endl;
		
		cout << obj._teme;
		return COUT;
	}

};
/*Funkcija PronadjiNajStudenta ima zadatak da svim studentima koji su uspjesno okoncali svoj zavrsni
	rad kod nastavnika/mentora sa najnizom prosjecnom ocjenom
	i tom prilikom ostvarili ocjenu vecu od proslijedjene, u zasebnom thread.u, posalje email poruku
	(mail adresa: brojIndeksa@edu.fit.ba) sa sadrzajem, "Postovani {brojIndeksa}, uzimajuci u obzir cinjenicu da
	ste kod mentora {imePrezimeMentora} uspjesno odbranili rad sa ocjenom {ocjena} cast nam je pozvati vas na
	dodjelu nagrada za najbolje studente koja ce se odrzatu u na FIT-u 20.09.2018. godine."
	da su svoj zavrsni rad uspjesno odbranili sa vecom ili manjom ocjenom od prosjecne.
	funkcija treba da vrati sadrzaj svih poslatih email poruka, a ukoliko niti jedan od nastavnika ne posjeduje
	evidentirano mentorstvo na zavrsnom radu, funkcija vraca not_set*/
//cout << "Studenti za dodjelu nagrada: " << PosaljiPozivZaDodjeluNagrada(nastavnici, max, 9.5) << endl;
string PosaljiPozivZaDodjeluNagrada(Nastavnik** nastavnici, int max, float ocjena) {
	//string s="bilal";
	//string poruka;
	//for (size_t i = 0; i < max; i++)
	//{
	//	for (size_t j = 0; j < n[i]->GetTeme().getTrenutno(); j++)
	//	{
	//		if (n[i]->GetTeme().getElement2(j).IzracunajKonacnu() > ocjena) {
	//			/*thread mail(&Nastavnik::sendMail,n[i]->GetTeme().getElement2(i), n[i], j);
	//			mail.join();
	//			return s.c_str();*/
	//			string temp = "Postovani" + n->GetTeme().getElement1(i) + ", uzimajuci u obzir cinjenicu da ste kod mentora " + n->GetImePrezime() + " uspjesno odbranili rad sa ocjenom " + to_string(n->GetTeme().getElement2(i).GetKonacnaOcjena()) + " cast nam je pozvati vas na dodjelu nagrada za najbolje studente koja ce se odrzatu u na FIT - u 20.09.2018.godine.";
	//			poruka += "\n" + temp + "\n";
	//			thread t([temp](string email) {
	//				m.lock();
	//				cout << "Saljem mail -> " << email << endl;
	//				cout << temp << endl;
	//				this_thread::sleep_for(chrono::seconds(2));
	//				m.unlock();
	//				}, n->GetTeme().getElement1(i) + "@edu.fit.ba");
	//			t.join();
	//		}

	//	}
	//}
	//return not_set;
	string poruka = not_set;
	Nastavnik* n = nullptr;
	float prosjek = INT_MAX;
	for (size_t i = 0; i < max; i++)
	{
		float trenutniProsjek = 0;
		int brojac = 0;
		for (size_t j = 0; j < nastavnici[i]->GetTeme().getTrenutno(); j++)
		{
			if (nastavnici[i]->GetTeme().getElement2(j).GetOcjena() > 5) {
				trenutniProsjek += nastavnici[i]->GetTeme().getElement2(j).GetOcjena();
				brojac++;
			}
		}
		if (brojac != 0) {
			trenutniProsjek /= brojac;
			if (prosjek > trenutniProsjek) {
				prosjek = trenutniProsjek;
				n = nastavnici[i];
			}
		}
	}
	if (n != nullptr) {
		for (size_t i = 0; i < n->GetTeme().getTrenutno(); i++)
		{
			if (n->GetTeme().getElement2(i).IzracunajKonacnu() >= ocjena) {
				string temp = "Postovani" + n->GetTeme().getElement1(i) + ", uzimajuci u obzir cinjenicu da ste kod mentora " + n->GetImePrezime() + " uspjesno odbranili rad sa ocjenom " + to_string(n->GetTeme().getElement2(i).GetOcjena()) + " cast nam je pozvati vas na dodjelu nagrada za najbolje studente koja ce se odrzatu u na FIT - u 20.09.2018.godine.";
				poruka += "\n" + temp + "\n";
				thread t([temp](string email) {
					m.lock();
					cout << "Saljem mail -> " << email << endl;
					cout << temp << endl;
					this_thread::sleep_for(chrono::seconds(2));
					m.unlock();
					}, n->GetTeme().getElement1(i) + "@edu.fit.ba");
				t.join();
			}
		}
	}
	return poruka;
}
int main() {
	const int max = 4;
	
	Nastavnik* nastavnici[max];

	nastavnici[0] = new Nastavnik("Denis Music");
	nastavnici[1] = new Nastavnik("Zanin Vejzovic");
	nastavnici[2] = new Nastavnik("Jasmin Azemovic");
	nastavnici[3] = new Nastavnik("Emina Junuz");


	ZavrsniRad multimedijalni("Multimedijalni informacijski sistem za visoko - obrazovnu ustanovu");
	ZavrsniRad podrsa_operaterima("Sistem za podršku rada kablovskog operatera");
	ZavrsniRad analiza_sigurnosti("Prakticna analiza sigurnosti bežičnih računarskih mreža");
	ZavrsniRad kriptografija("Primjena teorije informacija u procesu generisanja kriptografskih ključeva");


	/*u zavrsni rad dodaje novo poglavlje i njegov sadrzaj. ukoliko poglavlje vec postoji u zavrsnom radu, 
	funkcija tom poglavlju treba dodati novi sadrzaj i pri tome zadrzi postojeci (izmedju postojeceg i novog 
	sadrzaja se dodaje prazan prostor). u slucaju da poglavlje ne postoji, ono se dodaje zajedno sa sadrzaje*/
	//nazivPoglavlja, sadrzajPoglavlja
	multimedijalni.DodajPoglavlje("Uvod", "U ovom poglavlju ce biti rijeci");
	multimedijalni.DodajPoglavlje("Uvod", "o multimedijalnim sistemima koji se danas koriste");
	multimedijalni.DodajPoglavlje("Uvod", "u savremenom poslovanju");
	multimedijalni.DodajPoglavlje("Vrste multimedijalnih sistema", "Danas se moze govoriti o nekoliko vrsta multimedijalnih sistema, a neke od najznacajnijih su ...");
	multimedijalni.DodajPoglavlje("Teorija multimedije", "Sadrzaj koji bi trebao stajati na pocetku treceg poglavlja zavrsnog rada o multimediji studenta IB130011");

	//nazivPoglavlja, ocjena
	multimedijalni.OcijeniPoglavlje("Uvod", 8);
	multimedijalni.OcijeniPoglavlje("Vrste multimedijalnih sistema", 8);
	multimedijalni.OcijeniPoglavlje("Teorija multimedije", 10);

	
	/*funkcija DodajZavrsniRad ima zadatak da odredjenom nastavniku dodijeli mentorstvo na zavrsnom radu.
	zavrsni rad se dodaje studentu sa brojem indeksa proslijedjenim kao prvi parametar.
	sprijeciti dodavanje zavrsnih radova sa istom temom*/
	//brojIndeksa, zavrsniRad
	try {
		if (nastavnici[0]->DodajZavrsniRad("IB130011", multimedijalni))
			cout << "Zavrsni rad uspjesno dodat!" << endl;
		if (nastavnici[0]->DodajZavrsniRad("IB120051", podrsa_operaterima))
			cout << "Zavrsni rad uspjesno dodat!" << endl;
		if (!nastavnici[0]->DodajZavrsniRad("IB120056", podrsa_operaterima))//dupliranje rada
			cout << "Zavrsni rad nije dodat!" << endl;
		if (!nastavnici[0]->DodajZavrsniRad("IB120051", kriptografija)) //studentu vec dodijeljen rad
			cout << "Zavrsni rad nije dodat!" << endl;
		if (nastavnici[1]->DodajZavrsniRad("IB140102", analiza_sigurnosti))
			cout << "Zavrsni rad uspjesno dodat!" << endl;
		if (nastavnici[2]->DodajZavrsniRad("IB140002", kriptografija))
			cout << "Zavrsni rad uspjesno dodat!" << endl;
	}
	catch (exception err) {
		cout << err.what();
	}
	/*funkcija ZakaziOdbranuRada ima zadatak da studentu sa proslijedjenim brojem indeksa zakaze odbranu zavrsnog rada sto podrazumijeva definisanje
	datuma odbrane. odbrana rada se moze zakazati samo studentu koji je rad prethodno prijavio.
	Za zakazivanje odbrane rada moraju biti zadovoljeni sljedeci uslovi:
				   1. zavrsni rad mora imati broj poglavlja veci od minimalnog
				   2. svako poglavlje mora imati broj karaktera veci od minimalnog
				   3. svako poglavlje mora biti prihvaceno/odobreno
	ukoliko su zadovoljeni prethodni kriteriji, izracunava se konacna ocjena rada (prosjek ocjena svih poglavlja), postavlja datum odbrane rada i vraca pokazivac na rad kome je zakazan odbrana.
	u slucaju da student sa primljenim brojem indeksa nije prijavio zavrsni rad ili neki od postavljenih kriterija nije zadovoljen, funkcija vraca nullptr.
*/

//brojIndeksa, datumOdbrane
	cout << endl;
	ZavrsniRad* zr1 = nastavnici[0]->ZakaziOdbranuRada("IB130011", "25.09.2018");
	if (zr1 != nullptr)
		cout << *zr1 << endl;

	zr1 = nastavnici[0]->ZakaziOdbranuRada("IB130111", "25.09.2018");//student sa brojem indeksa IB130111 jos uvijek nije prijavio rad
	if (zr1 != nullptr)
		cout << *zr1 << endl;

	//ispisuje sve podatke o nastavniku i njegovim mentorstvima
	cout << *nastavnici[0] << endl;

	/*Funkcija PronadjiNajStudenta ima zadatak da svim studentima koji su uspjesno okoncali svoj zavrsni 
	rad kod nastavnika/mentora sa najnizom prosjecnom ocjenom
	i tom prilikom ostvarili ocjenu vecu od proslijedjene, u zasebnom thread.u, posalje email poruku 
	(mail adresa: brojIndeksa@edu.fit.ba) sa sadrzajem, "Postovani {brojIndeksa}, uzimajuci u obzir cinjenicu da 
	ste kod mentora {imePrezimeMentora} uspjesno odbranili rad sa ocjenom {ocjena} cast nam je pozvati vas na 
	dodjelu nagrada za najbolje studente koja ce se odrzatu u na FIT-u 20.09.2018. godine."
	da su svoj zavrsni rad uspjesno odbranili sa vecom ili manjom ocjenom od prosjecne.
	funkcija treba da vrati sadrzaj svih poslatih email poruka, a ukoliko niti jedan od nastavnika ne posjeduje 
	evidentirano mentorstvo na zavrsnom radu, funkcija vraca not_set*/
	cout << "Studenti za dodjelu nagrada: " << PosaljiPozivZaDodjeluNagrada(nastavnici, max, 9.5) << endl;

	/*
	Koristeci postojeci programski code, demonstrirati i ukratko opisati polimorfizam.
	*/

	for (int i = 0; i < max; i++)
	{
		delete nastavnici[i];
		nastavnici[i] = nullptr;
	}
	system("pause>0");
	return 0;
}