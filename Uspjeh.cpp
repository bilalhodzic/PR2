#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <regex>
#include <thread>
#include <mutex>
using namespace std;

const char* crt = "\n-------------------------------------------\n";
enum GodinaStudija { PRVA = 1, DRUGA, TRECA };
const char* GodinaStudijaChar[]={ "PRVA "," DRUGA", "TRECA" };


char* Alociraj(const char* sadrzaj) {
	if (sadrzaj == nullptr)return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}

template<class T1, class T2>
class Dictionary {
	T1* _elementi1;
	T2* _elementi2;
	int* _trenutno;
public:
	Dictionary() {
		_elementi1 = nullptr;
		_elementi2 = nullptr;
		_trenutno = new int(0);
	}
	~Dictionary() {
		delete[]_elementi1; _elementi1 = nullptr;
		delete[]_elementi2; _elementi2 = nullptr;
		delete _trenutno; _trenutno = nullptr;
	}
	Dictionary(const Dictionary & obj)
	{
		_trenutno = new int(*obj._trenutno);
		_elementi1 = new T1[*_trenutno];
		_elementi2 = new T2[*_trenutno];
			for (size_t i = 0; i < *_trenutno; i++)
			{
				_elementi1[i] = obj._elementi1[i];
				_elementi2[i] = obj._elementi2[i];

			}

	}
	Dictionary& operator=(const Dictionary& obj)
	{
		if (this != &obj) {
			delete[]_elementi1;
			delete[]_elementi2;
			delete _trenutno;
			_trenutno = new int(*obj._trenutno);
			_elementi1 = new T1[*_trenutno];
			_elementi2 = new T2[*_trenutno];
			for (size_t i = 0; i < *_trenutno; i++)
			{
				_elementi1[i] = obj._elementi1[i];
				_elementi2[i] = obj._elementi2[i];

			}
		}
		return *this;
	}
	T1& getElement1(int lokacija)const { return _elementi1[lokacija]; }
	T2& getElement2(int lokacija)const { return _elementi2[lokacija]; }
	int getTrenutno() { return *_trenutno; }
	void AddElement(const T1& el1, const T2 & el2) {
		T1* temp1=nullptr;
		T2* temp2=nullptr;
		try {
			temp1 = new T1[*_trenutno + 1];
			temp2 = new T2[*_trenutno + 1];
			for (size_t i = 0; i < *_trenutno; i++)
			{
				temp1[i] = _elementi1[i];
				temp2[i] = _elementi2[i];

			}
			temp1[*_trenutno] = el1;
			temp2[*_trenutno] = el2;
			delete[]_elementi1;
			delete[]_elementi2;
			_elementi1 = temp1;
			_elementi2 = temp2;
			(*_trenutno)++;
		}
		catch (bad_alloc e) {
			cout << "nema dovoljno memorije" << endl;
			delete[]temp1;
			delete[]temp2;
		}
	}
	Dictionary<T1, T2> getRange(int i, int i2) {
		if (i<0 ||  i2<0 || i2> * _trenutno) {
			throw exception("Ne postoji lokacija");
		}
		if (i2 < i)
			throw exception("Posljedna lokacija ne moze biti manja od prve");
		else {
			Dictionary<T1, T2>temp;
			for (size_t j = i; j < i2; j++)
			{
				temp.AddElement(_elementi1[j], _elementi2[j]);
			}
			return  temp;
		}
	}
	friend ostream& operator<< (ostream& COUT, const Dictionary& obj) {
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
	~DatumVrijeme() {
		delete _dan; _dan = nullptr;
		delete _mjesec; _mjesec = nullptr;
		delete _godina; _godina = nullptr;
		delete _sati; _sati = nullptr;
		delete _minuti; _minuti = nullptr;
	}
	DatumVrijeme(const DatumVrijeme & obj)
	{
		_dan = new int(*obj._dan);
		_mjesec = new int(*obj._mjesec);
		_godina = new int(*obj._godina);
		_sati = new int(*obj._sati);
		_minuti = new int(*obj._minuti);
	}
	DatumVrijeme& operator=(const DatumVrijeme& obj)
	{
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
		return *this;
	}
	friend ostream& operator<< (ostream& COUT, const DatumVrijeme& obj) {
		COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina << " " << *obj._sati << ":" << *obj._minuti << endl;
		return COUT;
	}
	char* ToCharArray() {
		ostringstream vrijeme;
		vrijeme << setw(2) << setfill('0') << *_dan << "/" << setw(2) << setfill('0') << *_mjesec <<
			"/" << *_godina << " " << *_sati << ":" << *_minuti << endl;
		return Alociraj(vrijeme.str().c_str());

	}
	int GetDateInHours() {
		return (*_sati + *_dan * 24 + *_mjesec * 720 + *_godina * 8640);
	}
};

class Predmet {
	char* _naziv;
	int _ocjena;
	string _napomena;
public:
	Predmet(const char* naziv = "", int ocjena = 0, string napomena = "") {
		_naziv = Alociraj(naziv);
		_ocjena = ocjena;
		_napomena = napomena;
	}
	~Predmet() {
		delete[] _naziv; _naziv = nullptr;
	}
	Predmet(const Predmet & obj)
	{
		_naziv = Alociraj(obj._naziv);
		_ocjena = obj._ocjena;
		_napomena = obj._napomena;
	}
	Predmet & operator=(const Predmet& obj)
	{
		if (this != &obj) {
			delete[]_naziv;
			_naziv = Alociraj(obj._naziv);
			_ocjena = obj._ocjena;
			_napomena = obj._napomena;
		}
		return *this;
	}
	friend ostream& operator<< (ostream& COUT, Predmet& obj) {
		COUT << obj._naziv << " (" << obj._ocjena << ") " << obj._napomena << endl;
		return COUT;
	}
	string GetNapomena() { return _napomena; }
	char* GetNaziv() { return _naziv; }
	int GetOcjena() { return _ocjena; }

	bool operator==(const Predmet& obj) {
		return strcmp(obj._naziv, _naziv) == 0;
	}
	void DodajNapomenu(string napomena) {
		_napomena += " " + napomena;
	}
};
class Uspjeh {
	GodinaStudija* _godina;
	//datumvrijeme se odnosi na vrijeme evidentiranja polozenog predmeta
	Dictionary<Predmet, DatumVrijeme> _predmeti;
public:
	Uspjeh(GodinaStudija godina) {
		_godina = new GodinaStudija(godina);
	}
	~Uspjeh() { delete _godina; _godina = nullptr; }
	Uspjeh(const Uspjeh& obj) {
		_godina = new GodinaStudija(*obj._godina);
		_predmeti = obj._predmeti;
	}
	Uspjeh& operator=(const Uspjeh& obj) {
		if (this != &obj) {
			delete _godina;
			_godina = new GodinaStudija(*obj._godina);
			_predmeti = obj._predmeti;
		}
		return *this;
	}

	Dictionary<Predmet, DatumVrijeme>* GetPredmeti() { return &_predmeti; }
	GodinaStudija* GetGodinaStudija() { return _godina; }
	friend ostream& operator<< (ostream& COUT, const Uspjeh& obj) {
		COUT << *obj._godina << " " << obj._predmeti << endl;
		return COUT;
	}
	void add(const Predmet& pr, const DatumVrijeme& d) {
		_predmeti.AddElement(pr, d);
	}
};
mutex m;
class Student {
	char* _imePrezime;
	string _emailAdresa;
	string _brojTelefona;
	vector<Uspjeh> _uspjeh;
	bool validanEmail(string mail) {
	
		return regex_match(mail, regex("\\w*[.|-]\\w*\\@(hotmail.com|outlook.com|fit.ba)"));
	}
	void sendMail( GodinaStudija g) {
		m.lock();

		cout << "   FROM:info@fit.ba" << endl;
		cout << "	TO : "<<_emailAdresa<< endl;
		//this_thread::sleep_for(chrono::seconds(1));
		cout << "	Postovani " << _imePrezime << ", evidentirali ste uspjeh za " << GodinaStudijaChar[g-1]<< " godinu studija." << endl;
		cout << "	Pozdrav." << endl << "	FIT Team." << crt;
		m.unlock();
	}
	void sendSMS(int prosjek, GodinaStudija g) {
		m.lock();
		this_thread::sleep_for(chrono::seconds(2));
		cout << "Svaka cast za uspjeh "<<prosjek<<" ostvaren u "<<GodinaStudijaChar[g-1]<<" godini studija" << endl;
		m.unlock();
	}
public:
	Student(const char* imePrezime, string emailAdresa, string brojTelefona) {
		_imePrezime = Alociraj(imePrezime);
		if(validanEmail(emailAdresa))
			_emailAdresa = emailAdresa;
		else {
			_emailAdresa = "notSet@fit.ba";
		}
		_brojTelefona = brojTelefona;
	}
	~Student() {
		delete[] _imePrezime; _imePrezime = nullptr;
	}
	Student(const Student & obj)
	{
		_imePrezime = Alociraj(obj._imePrezime);
		_emailAdresa = obj._emailAdresa;
		_brojTelefona = obj._brojTelefona;
		_uspjeh = obj._uspjeh;

	}
	Student & operator=(const Student& obj)
	{
		if (this != &obj) {
			delete[]_imePrezime;
			_imePrezime = Alociraj(obj._imePrezime);
			_emailAdresa = obj._emailAdresa;
			_brojTelefona = obj._brojTelefona;
			_uspjeh = obj._uspjeh;
		}
		return *this;
	}
	friend ostream& operator<< (ostream& COUT, Student& obj) {
		COUT << obj._imePrezime << " " << obj._emailAdresa << " " << obj._brojTelefona << endl;
		return COUT;
	}
	vector<Uspjeh>* GetUspjeh() { return &_uspjeh; }
	string GetEmail() { return _emailAdresa; }
	string GetBrojTelefona() { return _brojTelefona; }
	char* GetImePrezime() { return _imePrezime; }
	
	bool AddPredmet( Predmet & predmet, const  GodinaStudija &godina, DatumVrijeme & datum) {
		//Uspjeh temp(godina);
		//temp.add(predmet, datum);
		//for (auto i = 0; i < _uspjeh.size(); i++)
		//{
		//	for (size_t j = i; j < _uspjeh[i].GetPredmeti()->getTrenutno(); j++)
		//	{
		//	if (predmet == _uspjeh[i].GetPredmeti()->getElement1(j)) {
		//		//_uspjeh.pop_back();
		//		return false;
		//	}
		//	}
		//}
		//_uspjeh.push_back(temp);
		////cout << _uspjeh[0].GetPredmeti()->getElement1(0) << crt;
		//return true;
		for (size_t i = 0; i < _uspjeh.size(); i++)
		{
			if (*_uspjeh[i].GetGodinaStudija() == godina) {

				for (size_t j = 0; j < _uspjeh[i].GetPredmeti()->getTrenutno(); j++)
				{
					if (predmet == _uspjeh[i].GetPredmeti()->getElement1(j)) {
						return false;
					}
					if (datum.GetDateInHours() <= _uspjeh[i].GetPredmeti()->getElement2(j).GetDateInHours()) {
						return false;
					}
				}
			}
		}
		Uspjeh temp(godina);
		temp.add(predmet, datum);
		_uspjeh.push_back(temp);

		thread mail(&Student::sendMail, this, godina);
		mail.join();
		float prosjek = 0, brojac=0;
		for (vector<Uspjeh>::iterator i = _uspjeh.begin(); i != _uspjeh.end(); i++)
		{
			if (*i->GetGodinaStudija() == godina) {
				for (size_t j = 0; j < i->GetPredmeti()->getTrenutno(); j++)
				{
					prosjek += i->GetPredmeti()->getElement1(j).GetOcjena();
					brojac++;
				}
			}
		}
		prosjek /= brojac;
		//thread sms;
		if (prosjek > 8.0) {
			thread sms(&Student::sendSMS, this, prosjek, godina);
		sms.join();
		}


	
		return true;
	}
	vector<Predmet>operator()(DatumVrijeme* od, DatumVrijeme* DO) {
		vector<Predmet>temp;
		for (size_t i = 0; i < _uspjeh.size(); i++)
		{
			for (size_t j = 0; j < _uspjeh[i].GetPredmeti()->getTrenutno(); j++)
			{
				if (od->GetDateInHours() <= _uspjeh[i].GetPredmeti()->getElement2(j).GetDateInHours() &&
					DO->GetDateInHours() >= _uspjeh[i].GetPredmeti()->getElement2(j).GetDateInHours()) {
					temp.push_back(_uspjeh[i].GetPredmeti()->getElement1(j));
				}
			}
		}
		return temp;
	}
	//Uspjeh * uspjeh_I_godina = jasmin["PRVA"];//vraca uspjeh Studenta ostvaren u prvoj godini studija
	Uspjeh* operator[](GodinaStudija g) {
		for (size_t i = 0; i < _uspjeh.size(); i++)
		{
			if (*_uspjeh[i].GetGodinaStudija() == g) {
				return &_uspjeh[i];
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
	5. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIÈNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U, OSIM U SLUÈAJU
	DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOÆNE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
	6. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNAÈENO.
	****************************************************************************/
#pragma region prva
	DatumVrijeme temp,
		datum19062019_1015(19, 6, 2019, 10, 15),
		datum20062019_1115(20, 6, 2019, 11, 15),
		datum30062019_1215(30, 6, 2019, 12, 15),
		datum05072019_1231(5, 7, 2019, 12, 31);

	//funkcija ToCharArray vraca datum i vrijeme kao char *. konverziju izvrsiti koristeci stringstream objekat.
	////voditi racuna o tome da se izmedju datuma i vremena nalazi samo jedan razmak, te da su vrijednosti dana i mjeseca 
	////iskazane kao dvije cifre
	cout << datum19062019_1015.ToCharArray() << endl;//treba ispisati: 19/06/2019 10:15
	temp = datum05072019_1231;
	cout << temp.ToCharArray() << endl;//treba ispisati: 05/07/2019 12:31

	const int DictionaryTestSize = 9;
	Dictionary<int, int> Dictionary1;
	for (size_t i = 0; i < DictionaryTestSize; i++)
		Dictionary1.AddElement(i + 1, i * i);
	cout << Dictionary1;

	try {
		//vraca elemente kolekcije koji se nalaze na lokacijama definisanim vrijednostima parametara (npr. 2 - 7). 
		//funkcija baca izuzetak u slucaju da se zahtijeva lokacija koja ne postoji ili je vrijednost posljednje lokacije manja od pocetne
		Dictionary<int, int> opseg = Dictionary1.getRange(2, 7);
		cout << opseg << endl;
		Dictionary1.getRange(7, 11);
	}
	catch (exception & err) {
		cout << err.what() << endl;
	}
	cout << Dictionary1 << endl;

	Dictionary<int, int> Dictionary2 = Dictionary1;
	cout << Dictionary2 << crt;

	Dictionary<int, int> Dictionary3;
	Dictionary3 = Dictionary1;
	cout << Dictionary3 << crt;
#pragma endregion zavrsena
	



	//napomena se moze dodati i prilikom kreiranja objekta
	Predmet MAT("Matematika", 7, "Ucesce na takmicenju"),
		UIT("Uvod u informacijske tehnologije", 9),
		RM("Racunarske mreze", 8),
		EN("Engleski jezik", 6);
	UIT.DodajNapomenu("Pohvala za ostvareni uspjeh");
	cout << MAT << endl;

	/*
	email adresa mora biti u formatu: text-text@ nakon cega slijedi neka od sljedecih domena: hotmail.com ili
	//outlook.com ili fit.ba. Pod text se podrazumijeva bilo koje slovo, malo ili veliko.
	u slucaju da email adresa nije validna, postaviti je na defaultnu: notSet@fit.ba
	za provjeru koristiti regex
	*/
	Student jasmin("Jasmin Azemovic", "jasmin.azemovic@hotmail.com", "033 281 172");
	Student adel("Adel Handzic", "adel.handzic@fit.ba", "033 281 170");
	Student emailNotValid("Ime Prezime", "korisnik@lazna.ba", "033 281 170");
	cout << jasmin << emailNotValid << endl;
	/*
	uspjeh se dodaje za svaki predmet na nivou godine studija.
	tom prilikom onemoguciti:
	- dodavanje istoimenih predmeta na nivou jedne godine,
	- dodavanje vise predmeta u kratkom vremenskom periodu (na nivou jedne godine, razmak izmedju dodavanja pojedinih predmeta 
	mora biti najmanje 1 sat).
	godine (predmeti ili uspjeh) ne moraju biti dodavani sortiranim redoslijedom (npr. prvo se moze dodati uspjeh za drugu
	godinu, pa onda za prvu godinu i sl.).
	Funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
	*/
	if (jasmin.AddPredmet(UIT, DRUGA, datum20062019_1115))
		cout << "Predmet uspjesno dodan!" << crt;
	if (jasmin.AddPredmet(RM, DRUGA, datum30062019_1215))
		cout << "Predmet uspjesno dodan!" << crt;
	if (jasmin.AddPredmet(EN, PRVA, datum19062019_1015))
		cout << "Predmet uspjesno dodan!" << crt;
	if (jasmin.AddPredmet(MAT, PRVA, datum20062019_1115))
		cout << "Predmet uspjesno dodan!" << crt;
	//ne treba dodati MAT jer je vec dodana u prvoj godini
	if (jasmin.AddPredmet(MAT, PRVA, datum05072019_1231))
		cout << "Predmet uspjesno dodan!" << crt;
	//ne treba dodati UIT jer nije prosao 1 sat od dodavanja posljednjeg predmeta
	if (jasmin.AddPredmet(UIT, PRVA, datum20062019_1115))
		cout << "Predmet uspjesno dodan!" << crt;
	/*nakon evidentiranja uspjeha na bilo kojem predmetu tj. prilikom uspjesno izvrsene funkcije AddPredmet, Studentu 
	se salje email sa sadrzajem:
	FROM:info@fit.ba
	TO: emailStudenta
	Postovani ime i prezime, evidentirali ste uspjeh za X godinu studija.
	Pozdrav.
	FIT Team.

	ukoliko je, nakon dodavanja predmeta, prosjek na nivou te godine veci od 8.0 Studentu se, pored email-a, salje i SMS 
	sa sadrzajem: "Svaka cast za uspjeh X.X       ostvaren u X godini studija".
	slanje poruka i emailova implemenitrati koristeci zasebne thread-ove.
	*/
	//cout << "USPJEH ISPISATI KORISTEÆI OSTREAM_ITERATOR" << endl;
	//cout << jasmin << endl;
	////vraca broj ponavljanja odredjene rijeci u napomenama, koristiti sregex_iterator
	//cout << "Rijec takmicenje se pojavljuje " << jasmin.BrojPonavljanjaRijeci("takmicenju") << " puta." << endl;

	//vraca niz predmeta koji su evidentiranih u periodu izmedju vrijednosti proslijedjenih parametara
	vector<Predmet> jasminUspjeh = jasmin(new DatumVrijeme(18, 06, 2019, 10, 15), new DatumVrijeme(21, 06, 2019, 10, 10));
	for (Predmet u : jasminUspjeh)
		cout << u << endl;

	Uspjeh * uspjeh_I_godina = jasmin[PRVA];//vraca uspjeh Studenta ostvaren u prvoj godini studija
	if (uspjeh_I_godina != nullptr)
		cout << *uspjeh_I_godina << endl;

	cin.get();
	system("pause>0");
}