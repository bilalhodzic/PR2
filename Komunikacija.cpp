#include <iostream>
#include <vector>
#include <sstream>
#include <thread>
#include <mutex>
using namespace std;

#pragma warning(disable:4996)
const char* crt = "\n-------------------------------------------\n";
enum eRazred { PRVI = 1, DRUGI, TRECI, CETVRTI };
const char* razredString[] = { "PRVI" , "DRUGI", "TRECI", "CETVRTI" };
const float minimalan_prosjek = 4.5;

char* AlocirajNizKaraktera(const char* sadrzaj) {
	if (sadrzaj == nullptr)
		return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}
mutex m;

template<class T1, class T2>
class Kolekcija {
	T1* _elementi1;
	T2* _elementi2;
	int* _trenutno;
public:
	Kolekcija() {
		_elementi1 = nullptr;
		_elementi2 = nullptr;
		_trenutno = new int(0);
	}
	Kolekcija(const Kolekcija& obj) {
		_trenutno = new int(*obj._trenutno);
		_elementi1 = new T1[*_trenutno];
		_elementi2 = new T2[*_trenutno];
		for (size_t i = 0; i < *_trenutno; i++)
		{
			_elementi1[i] = obj._elementi1[i];
			_elementi2[i] = obj._elementi2[i];

		}

	}
	Kolekcija& operator=(const Kolekcija& obj) {
		if (this == &obj)
			return*this;
		//delete _trenutno;
		delete[]_elementi1;
		delete[]_elementi2;

		*_trenutno = (*obj._trenutno);
		_elementi1 = new T1[*_trenutno];
		_elementi2 = new T2[*_trenutno];
		for (size_t i = 0; i < *_trenutno; i++)
		{
			_elementi1[i] = obj._elementi1[i];
			_elementi2[i] = obj._elementi2[i];

		}
		return *this;

	}
	~Kolekcija() {
		delete[]_elementi1; _elementi1 = nullptr;
		delete[]_elementi2; _elementi2 = nullptr;
		delete _trenutno; _trenutno = nullptr;
	}
	T1& getElement1(int lokacija) { return _elementi1[lokacija]; }
	T2& getElement2(int lokacija) { return _elementi2[lokacija]; }
	int getTrenutno() { return *_trenutno; }
	void AddElement(const T1& el1, const T2& el2) {
		T1* temp1 = new T1[*_trenutno + 1];
		T2* temp2 = new T2[*_trenutno + 1];
		for (size_t i = 0; i < *_trenutno; i++)
		{
			temp1[i] = _elementi1[i];
			temp2[i] = _elementi2[i];

		}
		temp1[*_trenutno] = el1;
		temp2[*_trenutno] = el2;
		(*_trenutno)++;
		delete[]_elementi1;
		delete[]_elementi2;
		_elementi1 = temp1;
		_elementi2 = temp2;


	}
	//kolekcija3.SortOpadajuciByT2(); //od najvece prema najmanjoj vrijednosti
	void SortOpadajuciByT2() {
		for (size_t i = 0; i < *_trenutno; i++)
		{
			for (size_t j = i+1; j < *_trenutno; j++)
			{
				if (_elementi2[j] > _elementi2[i]) {
					T2 temp1 = _elementi2[j];
					_elementi2[j] = _elementi2[i];
					_elementi2[i] = temp1;
					T1 temp2 = _elementi1[j];
					_elementi1[j] = _elementi1[i];
					_elementi1[i] = temp2;
				}
			}
		}
	}
	friend ostream& operator<< (ostream& COUT, Kolekcija& obj) {
		for (size_t i = 0; i < *obj._trenutno; i++)
			COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
		return COUT;
	}
};

class DatumVrijeme {
	int* _dan, * _mjesec, * _godina, * _sati, * _minuti;
public:
	DatumVrijeme(int dan = 1, int mjesec = 1, int godina = 2000, int sati = 0, int minuti = 0) {
		_dan = new int(dan);
		_mjesec = new int(mjesec);
		_godina = new int(godina);
		_sati = new int(sati);
		_minuti = new int(minuti);
	}
	DatumVrijeme(const DatumVrijeme& obj) {
		_dan = new int(*obj._dan);
		_mjesec = new int(*obj._mjesec);
		_godina = new int(*obj._godina);
		_sati = new int(*obj._sati);
		_minuti = new int(*obj._minuti);
	}
	DatumVrijeme& operator=(const DatumVrijeme& obj) {
		if (this != &obj) {
			delete _dan; 
			delete _mjesec; 
			delete _godina;
			delete _sati; 
			delete _minuti; 
			_dan = new int(*obj._dan);
			_mjesec = new int(*obj._mjesec);
			_godina = new int(*obj._godina);
			_sati = new int(*obj._sati);
			_minuti = new int(*obj._minuti);
		}
		return*this;
	}
	~DatumVrijeme() {
		delete _dan; _dan = nullptr;
		delete _mjesec; _mjesec = nullptr;
		delete _godina; _godina = nullptr;
		delete _sati; _sati = nullptr;
		delete _minuti; _minuti = nullptr;
	}
	friend ostream& operator<< (ostream& COUT, DatumVrijeme& obj) {
		COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina << " " << *obj._sati << ":" << *obj._minuti << endl;
		return COUT;
	}
	char* ToCharArray() {
		stringstream s;
		s << *_dan << "." << *_mjesec<<"." << *_godina << " " << *_sati << ":" << *_minuti;
		return AlocirajNizKaraktera(s.str().c_str());
	}
	bool operator==(const DatumVrijeme& d) {
		return *_dan == *d._dan && *_mjesec == *d._mjesec && *_godina == *d._godina;
	}
};

class Predmet {
	char* _naziv;
	int _ocjena;
	string _napomena;
public:
	Predmet(const char* naziv, int ocjena, string napomena = "") :_ocjena(ocjena), _napomena(napomena) {
		_naziv = AlocirajNizKaraktera(naziv);
	}
	~Predmet() {
		delete[] _naziv; _naziv = nullptr;
	}
	Predmet(const Predmet& obj) {
		_naziv = AlocirajNizKaraktera(obj._naziv);
		_ocjena = obj._ocjena;
		_napomena = obj._napomena;
	}
	Predmet& operator=(const Predmet& obj) {
		delete[]_naziv;
		_naziv = AlocirajNizKaraktera(obj._naziv);
		_ocjena = obj._ocjena;
		_napomena = obj._napomena;
	}
	friend ostream& operator<< (ostream& COUT, Predmet& obj) {
		COUT << obj._naziv << " (" << obj._ocjena << ") " << obj._napomena << endl;
		return COUT;
	}
	int GetOcjena() { return _ocjena; }
	char* GetNaziv() { return _naziv; }
	string GetNapomena() { return _napomena; }
	void DodajNapomenu(string napomena) {
		_napomena += " " + napomena;
	}
	bool operator==(const Predmet& p) {
		return strcmp(_naziv, p._naziv) == 0;
	}
};
struct Uspjeh {
	eRazred _razred;
	//datumvrijeme se odnosi na vrijeme evidentiranja polozenog predmeta
	Kolekcija<Predmet*, DatumVrijeme>* _predmeti;
public:
	Uspjeh(eRazred razred) :_razred(razred), _predmeti(nullptr) {
	}
	~Uspjeh() {
		for (size_t i = 0; i < _predmeti->getTrenutno(); i++)
		{
			delete _predmeti->getElement1(i);
		}
		delete _predmeti; _predmeti = nullptr;
	}
	Uspjeh(Uspjeh& u) {
		_razred = u._razred;
		//_predmeti = obj._predmeti;
		_predmeti = new Kolekcija<Predmet*, DatumVrijeme>;
		if (u.GetPredmeti() != nullptr) {
			for (size_t i = 0; i < u.GetPredmeti()->getTrenutno(); i++)
			{
				_predmeti->AddElement(new Predmet(*u.GetPredmeti()->getElement1(i)), u.GetPredmeti()->getElement2(i));
			}
		}
		
	}
	Uspjeh & operator=( Uspjeh& u) {
		if (this != &u) {
			_razred = u._razred;
			//_predmeti = obj._predmeti;
			delete[]_predmeti;
			_predmeti = new Kolekcija<Predmet*, DatumVrijeme>;
			if (u.GetPredmeti() != nullptr) {
				for (size_t i = 0; i < u.GetPredmeti()->getTrenutno(); i++)
				{
					_predmeti->AddElement(new Predmet(*u.GetPredmeti()->getElement1(i)), u.GetPredmeti()->getElement2(i));
				}
			}

		}
		return *this;
	}
	double GetProsjek() {
		double suma = 0;
		for (size_t i = 0; i < _predmeti->getTrenutno(); i++)
		{
			suma += _predmeti->getElement1(i)->GetOcjena();
		}
		return (double) suma / _predmeti->getTrenutno();
	}
	
	void DodajPredmet(Predmet predmet, DatumVrijeme datum) {
		if (_predmeti == nullptr) {
			_predmeti = new Kolekcija<Predmet*, DatumVrijeme>;

		}
		_predmeti->AddElement(new Predmet(predmet), datum);
	}
	eRazred GetRazred() { return _razred; }
	int GetbrojPredmeta() {
		return _predmeti->getTrenutno();
	}
	Kolekcija<Predmet*, DatumVrijeme>* GetPredmeti() { return _predmeti; }

	friend ostream& operator<< (ostream& COUT, const Uspjeh& obj) {
		COUT << razredString[obj._razred-1] << endl;
		if(obj._predmeti!=nullptr)
			for (size_t i = 0; i < obj._predmeti->getTrenutno(); i++)
			{
				cout << *obj._predmeti->getElement1(i) << " " << obj._predmeti->getElement2(i) << endl;
			}
		return COUT;
	}
};

class Kandidat {
	char* _imePrezime;
	string _emailAdresa;
	string _brojTelefona;
	vector<Uspjeh*> _uspjeh;
	void sendEmail(eRazred razred) {
		cout << crt << "Email sending..." << endl;
		this_thread::sleep_for(chrono::seconds(2));
		m.lock();
		cout << "Postovani " << _imePrezime << ", evidentirali ste uspjeh za " 
			<< razredString[razred - 1] << " razred!" << endl;
		m.unlock();
	}
	void sendSMS(int prosjek) {
		cout << crt << "SMS sending..." << endl;
		this_thread::sleep_for(chrono::seconds(2));
		m.lock();
		cout << "Postovani " << _imePrezime << ", svaka cast za uspjeh " << prosjek << endl;
		m.unlock();
	}
public:
	Kandidat(const char* imePrezime, string emailAdresa, string brojTelefona)
		:_emailAdresa(emailAdresa), _brojTelefona(brojTelefona) {
		_imePrezime = AlocirajNizKaraktera(imePrezime);
	}
	Kandidat(const Kandidat& obj) {
		_emailAdresa = obj._emailAdresa;
		_brojTelefona = (obj._brojTelefona);
		_imePrezime = AlocirajNizKaraktera(obj._imePrezime);
		for (size_t i = 0; i < _uspjeh.size(); i++)
		{
			_uspjeh[i] = obj._uspjeh[i];
		}
	}
	Kandidat& operator=(const Kandidat& obj) {
		if (this != &obj) {
			_emailAdresa = obj._emailAdresa;
			_brojTelefona = (obj._brojTelefona);
			delete[]_imePrezime;
			_imePrezime = AlocirajNizKaraktera(obj._imePrezime);
			for (size_t i = 0; i < _uspjeh.size(); i++)
			{
				_uspjeh[i] = obj._uspjeh[i];
			}
		}return *this;
	}
	~Kandidat() {
		delete[] _imePrezime; _imePrezime = nullptr;
		for (size_t i = 0; i < _uspjeh.size(); i++) {
			delete _uspjeh[i];
			_uspjeh[i] = nullptr;
		}
	}

	bool AddPredmet(eRazred r, Predmet& p, DatumVrijeme d) {
		
		for (vector<Uspjeh*>::iterator i = _uspjeh.begin(); i != _uspjeh.end(); i++)
		{
			Uspjeh* u = *i;
			if (u->GetRazred() == r) {
				if (u->GetPredmeti() == nullptr) return false;
				if (u->GetPredmeti()->getTrenutno() >= 6) 	return false;
				for (size_t j = 0; j < u->GetPredmeti()->getTrenutno(); j++)
				{
					if (*u->GetPredmeti()->getElement1(j) == p/*|| u->GetPredmeti()->getElement2(j)==d*/) return false;
				}
				u->GetPredmeti()->AddElement(new Predmet(p), d);
				if (u->GetbrojPredmeta() == 6) {
					thread tEmail(&Kandidat::sendEmail, this, r);
					tEmail.join();
					double prosjek = u->GetProsjek();
					if (prosjek > minimalan_prosjek) {
						thread tSMS(&Kandidat::sendSMS, this, prosjek);
						tSMS.join();
					}
				}
				return true;
			}
			
		}
		Uspjeh* u = new Uspjeh(r);
			u->DodajPredmet(p, d);
			_uspjeh.push_back(u);
			return true;
		/*for (size_t i = 0; i < _uspjeh.size(); i++)
		{
			if (_uspjeh[i]->GetRazred() == r && _uspjeh[i]->GetbrojPredmeta() >= 6)
				return false;
			for (size_t j = 0; j < _uspjeh[i]->GetPredmeti()->getTrenutno(); j++)
			{
				if (_uspjeh[i]->GetRazred() == r && *_uspjeh[i]->GetPredmeti()->getElement1(j) == p)
					return false;
				if (_uspjeh[i]->GetRazred() == r && _uspjeh[i]->GetPredmeti()->getElement2(j) == d)
					return false;
			}
		}
		int index = -1;
		for (size_t i = 0; i < _uspjeh.size(); i++)
		{
			if (_uspjeh[i]->GetRazred() == r) {
				index = i;
			}
		}
		if (index==-1) {
			_uspjeh.push_back(new Uspjeh(r));
			_uspjeh[(int)_uspjeh.size() - 1]->DodajPredmet(p, d);
			
		}
		else {
			_uspjeh[index]->DodajPredmet(p, d);
			if (_uspjeh[index]->GetbrojPredmeta() == 6) {
				thread tEmail(&Kandidat::sendEmail, this, r);
				tEmail.join();
				double prosjek = _uspjeh[index]->GetProsjek();
				if (prosjek > minimalan_prosjek) {
					thread tSMS(&Kandidat::sendSMS, this, prosjek);
					tSMS.join();
				}
			}
		}
		return true;*/
	
	}

	friend ostream& operator<< (ostream& COUT, Kandidat& obj) {
		COUT << obj._imePrezime << " " << obj._emailAdresa << " " << obj._brojTelefona << endl;
		for (size_t i = 0; i < obj._uspjeh.size(); i++)
			COUT << *obj._uspjeh[i] << endl;
		return COUT;
	}
	vector<Uspjeh*> GetUspjeh() { return _uspjeh; }
	Uspjeh* operator()(eRazred r) {
		for (size_t i = 0; i < _uspjeh.size(); i++)
		{
			if (r == _uspjeh[i]->GetRazred()) {
				return _uspjeh[i];
			}
		}
		return nullptr;
	}
};

void main() {
	/****************************************************************************
	1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
	2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR ÆE BITI OZNACENO KAO "RE"
	3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJEÈILO GUBLJENJE URAÐENOG ZADATKA
	4. PROGRAMSKI CODE SE TAKOÐER NALAZI U FAJLU CODE.TXT
	5. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIÈNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U, OSIM U SLUÈAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOÆNE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
	6. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNAÈENO.
	****************************************************************************/
#pragma region Testiranjedatuma
	DatumVrijeme temp,
		datum19062018_1015(19, 6, 2018, 10, 15),
		datum20062018_1115(20, 6, 2018, 11, 15),
		datum30062018_1215(30, 6, 2018, 12, 15),
		datum05072018_1231(5, 7, 2018, 12, 31),
		datum20062018_1115_Copy(datum20062018_1115);
	//funkcija ToCharArray vraca datum i vrijeme kao char *
	cout << datum19062018_1015.ToCharArray() << endl;//treba ispisati: 19.6.2018 10:15
	temp = datum05072018_1231;
	cout << temp.ToCharArray() << endl;//treba ispisati: 5.7.2018 12:31
	cout << datum20062018_1115_Copy.ToCharArray() << endl;//treba ispisati: 20.6.2018 11:15
#pragma endregion
#pragma region Kolekcija
	const int kolekcijaTestSize = 10;
	Kolekcija<int, int> kolekcija1;
	for (size_t i = 0; i < kolekcijaTestSize; i++)
		kolekcija1.AddElement(i + 1, i * i);
	cout << kolekcija1 << endl;

	Kolekcija<int, int> kolekcija2 = kolekcija1;
	cout << kolekcija2 << crt;
	Kolekcija<int, int> kolekcija3;
	kolekcija3 = kolekcija1;
	kolekcija3.SortOpadajuciByT2(); //od najvece prema najmanjoj vrijednosti
	cout << kolekcija3 << crt;
#pragma endregion
	//napomena se moze dodati i prilikom kreiranja objekta
	Predmet Matematika("Matematika", 5, "Ucesce na takmicenju"),
		Fizika("Fizika", 5),
		Hemija("Hemija", 2),
		Engleski("Engleski", 5),
	Ekonomija("Ekonomija", 4),
	Historija("Historija", 5),
	Bosanski("Bosanski", 5),

	Geografija("Geografija", 5);

	Fizika.DodajNapomenu("Pohvala za ostvareni uspjeh"); // dodaje novu napomenu zadrzavajuci ranije dodane
	cout << Matematika << endl;

	

	Kandidat jasmin("Jasmin Azemovic", "jasmin@gmail.com", "033 281 172");
	Kandidat adel("Adel Handzic", "adel@edu.fit.ba", "033 281 170");
	/*Kandidat bilal = jasmin;
	cout << bilal;*/

	/*
	uspjeh (tokom srednjoskolskog obrazovanja) se dodaje za svaki predmet na nivou razreda.
	tom prilikom onemoguciti:
	- dodavanje vise od 6 predmeta za jedan razred
	- dodavanje istoimenih predmeta na nivou jednog razreda,
	- dodavanje vise predmeta u kratkom vremenskom periodu (na nivou jednog razreda, razmak izmedju dodavanja pojedinih predmeta mora biti najmanje minut).
	razredi (predmeti ili uspjeh) ne moraju biti dodavani sortiranim redoslijedom (npr. prvo se moze dodati uspjeh za II
	razred, pa onda za I razred i sl.). Funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
	*/
	if (jasmin.AddPredmet(DRUGI, Fizika, datum20062018_1115))
		cout << "Predmet uspjesno dodan!" << crt;
	if (jasmin.AddPredmet(DRUGI, Hemija, datum30062018_1215))
		cout << "Predmet uspjesno dodan!" << crt;
	if (jasmin.AddPredmet(PRVI, Engleski, datum19062018_1015))
		cout << "Predmet uspjesno dodan!" << crt;
	if (jasmin.AddPredmet(PRVI, Matematika, datum20062018_1115))
		cout << "Predmet uspjesno dodan!" << crt;
	//ne treba dodati Matematiku jer je vec dodana u prvom razredu
	if (jasmin.AddPredmet(PRVI, Matematika, datum05072018_1231))
		cout << "Predmet uspjesno dodan!" << crt;
	//ne treba dodati Fiziku jer nije prosao minut od dodavanja posljednjeg predmeta
	if (jasmin.AddPredmet(PRVI, Fizika, datum05072018_1231))
		cout << "Predmet uspjesno dodan!" << crt;


	if (jasmin.AddPredmet(PRVI, Ekonomija, datum05072018_1231))
		cout << "Predmet uspjesno dodan!" << crt;
	if (jasmin.AddPredmet(PRVI, Historija, datum05072018_1231))
		cout << "Predmet uspjesno dodan!" << crt;
	if (jasmin.AddPredmet(PRVI, Geografija, datum05072018_1231))
		cout << "Predmet uspjesno dodan!" << crt;
	if (jasmin.AddPredmet(PRVI, Bosanski, datum05072018_1231))
		cout << "Predmet uspjesno dodan!" << crt;
	/*pretpostavka je da na nivou jednog razreda kandidati imaju 6 predmeta.
	upravo zbog toga, nakon evidentiranja 6 predmeta na nivou jednog razreda kandidatu se salje mail
	sa porukom: "evidentirali ste uspjeh za X razred". ukoliko je prosjek na nivou tog razreda veci od minimalan_prosjek
	kandidatu se salje SMS sa porukom: "svaka cast za uspjeh 4.X". slanje poruka i emailova implemenitrati koristeci
	zasebne thread-ove.
	*/
	cout << jasmin << endl;

	Uspjeh * u = jasmin(PRVI);//vraca uspjeh kandidata ostvaren u prvom razredu
	if (u != nullptr)
		cout << *u << endl;


	system("pause>0");
}