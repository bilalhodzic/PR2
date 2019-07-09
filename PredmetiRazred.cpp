#include <iostream>
#include <vector>
#include <regex>

using namespace std;

enum Predmeti { Matematika, Historija, Geografia, Hemija, Biologija, Engleski, Muzicko, Fizicko };
enum Razredi { I1, I2, I3, II1, II2, II3, III1, III2, III3, IV1, IV2, IV3 };
const char* ispisPredmeti[] = { "Matematika", "Historija", "Geografia", "Hemija", "Biologija", "Engleski", "Muzicko", "Fizicko" };
const char* ispisRazredi[] = { "I1", "I2", "I3", "II1", "II2", "II3", "III1", "III2", "III3", "IV1", "IV2", "IV3" };
const char* crt = "\n--------------------------------\n";
bool ProvjeriValidnostBrojaTelefona(string telefon)//globalna funkcija
{
	//broj telefona treba biti u formatu: +387(61)-222-333
	return regex_match(telefon, regex("\\+387\\(6.\\)\\-(\\d{3})\\-(\\d{3})"));
}
char* Alociraj(const char* sadrzaj) {
	int vel = strlen(sadrzaj) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}
class Datum
{
	int* _dan, * _mjesec, * _godina;
public:
	Datum(int dan = 1, int mjesec = 1, int godina = 2000)
	{
		_dan = new int(dan);
		_mjesec = new int(mjesec);
		_godina = new int(godina);
	}

	Datum(const Datum& obj)
	{
		_dan = new int(*obj._dan);
		_mjesec = new int(*obj._mjesec);
		_godina = new int(*obj._godina);
	}
	Datum& operator=(const Datum& obj)
	{
		if (this == &obj)
			return*this;
		delete _dan;
		delete _mjesec;
		delete _godina;

		_dan = new int(*obj._dan);
		_mjesec = new int(*obj._mjesec);
		_godina = new int(*obj._godina);
		return*this;
	}


	~Datum()
	{
		delete _dan; _dan = nullptr;
		delete _mjesec; _mjesec = nullptr;
		delete _godina; _godina = nullptr;
	}


	friend ostream& operator<< (ostream& COUT, const Datum& obj)
	{
		COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina;
		return COUT;
	}
	bool operator==(const Datum& d) {
		return *_dan == *d._dan && *_mjesec == *d._mjesec && *_godina == *d._godina;
	}
};
template<class T1, class T2>
class Kolekcija
{
	T1* _elementi1;
	T2* _elementi2;
	int _trenutno;
public:
	Kolekcija()
	{
		_elementi1 = nullptr;
		_elementi2 = nullptr;
		_trenutno = 0;
	}
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
		if (this == &obj)
			return *this;
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
		return*this;
	}
	~Kolekcija()
	{
		delete[]_elementi1;
		delete[]_elementi2;
	}
	void AddElement(const T1& el1,const  T2& el2) {
		T1* temp1 = new T1[_trenutno + 1];
		T2* temp2 = new T2[_trenutno + 1];
		for (size_t i = 0; i < _trenutno; i++)
		{
			temp1[i] = _elementi1[i];
			temp2[i] = _elementi2[i];

		}
		temp1[_trenutno] = el1;
		temp2[_trenutno++] = el2;
		delete[]_elementi1;
		delete[]_elementi2;
		_elementi1 = temp1;
		_elementi2 = temp2;


	}
	void RemoveElement(int index) {
		for (size_t i = 0; i < _trenutno; i++)
		{
			if (i == index) {
				for (size_t j = i; j < _trenutno-1; j++)
				{
					_elementi1[j] = _elementi1[j + 1];
					_elementi2[j] = _elementi2[j + 1];

				}
				_trenutno--;
				return;
			}
		}
	}
	int GetTrenutno() { return _trenutno; }
	T1 GetElement1(int i) { return _elementi1[i]; }
	T2 GetElement2(int i) { return _elementi2[i]; }

	friend ostream& operator<<(ostream& cout, Kolekcija& obj) {
		for (size_t i = 0; i < obj._trenutno; i++)
		{
			cout << obj._elementi1[i] << " " << obj._elementi2[i] << endl;
		}
		return cout;
	}
};
class Osoba
{
protected:
	char* _imePrezime;
	Datum* _datumRodjenja;
	string _brojTelefona;
public:
	Osoba(const char* imePrezime, Datum datum)
	{
		_imePrezime = new char[strlen(imePrezime) + 1];
		strcpy_s(_imePrezime, strlen(imePrezime) + 1, imePrezime);
		_datumRodjenja = new Datum(datum);
		_brojTelefona = "";
	}
	Osoba(const Osoba& obj) :_brojTelefona(obj._brojTelefona)
	{
		_imePrezime = new char[strlen(obj._imePrezime) + 1];
		strcpy_s(_imePrezime, strlen(obj._imePrezime) + 1, obj._imePrezime);
		_datumRodjenja = new Datum(*obj._datumRodjenja);
	}
	Osoba & operator=(const Osoba& obj) 
	{
		if (this != &obj) {
			delete[]_imePrezime;
			_imePrezime = Alociraj(obj._imePrezime);
			_datumRodjenja = new Datum(*obj._datumRodjenja);
			_brojTelefona = (obj._brojTelefona);
		}
		return*this;
	}
	~Osoba() { delete[]_imePrezime; delete _datumRodjenja; }
	char* GetImePrezime() { return _imePrezime; }
	bool setBrojTelefona(string brojTelefona)
	{
		if (ProvjeriValidnostBrojaTelefona(brojTelefona))
		{
			_brojTelefona = brojTelefona;
			return true;
		}
		return false;
	}
	bool operator==(const Osoba& obj) {
		return strcmp(_imePrezime, obj._imePrezime) == 0 && 
			*_datumRodjenja == *obj._datumRodjenja && _brojTelefona == obj._brojTelefona;
	}
	friend ostream& operator<< (ostream& COUT, const Osoba& obj)
	{
		cout << crt << obj._imePrezime << endl;
		cout << *obj._datumRodjenja << endl;
		cout << obj._brojTelefona << endl;
		return COUT;
	}

};
class Nastavnik :public Osoba
{
	Kolekcija<Predmeti, Razredi>* _predmetiRazredi;
public:
	Nastavnik(const char* imePrezime, Datum datum):Osoba(imePrezime, datum)
	{
		_predmetiRazredi = new Kolekcija<Predmeti, Razredi>;
	}
	~Nastavnik()
	{
		delete _predmetiRazredi;
	}
	Nastavnik( const Nastavnik& obj) :Osoba(obj){
		if(obj._predmetiRazredi !=nullptr)
		_predmetiRazredi = new Kolekcija<Predmeti,Razredi>(*obj._predmetiRazredi);
		else {
			_predmetiRazredi = new Kolekcija<Predmeti, Razredi>;
		}
	}
	Nastavnik & operator=(const Nastavnik& obj) {
		if (this == &obj)
			return*this;
		Osoba::operator=(obj);
		delete _predmetiRazredi;
		if (obj._predmetiRazredi != nullptr)
			_predmetiRazredi = new Kolekcija<Predmeti, Razredi>(*obj._predmetiRazredi);
		else {
			_predmetiRazredi = new Kolekcija<Predmeti, Razredi>;
		}
		return *this;
	}
	bool AddPredmetRazred(const Predmeti& predmet, const Razredi& razred) {
		for (size_t i = 0; i < _predmetiRazredi->GetTrenutno(); i++)
		{
			if (_predmetiRazredi->GetElement2(i) == razred) {
				return false;
			}
		}
		_predmetiRazredi->AddElement(predmet, razred);
		return true;
	}
	bool RemovePredmetRazred(const Predmeti& predmet) {
		bool flag = false;
		int index = 0;
		for (size_t i = 0; i < _predmetiRazredi->GetTrenutno(); i++)
		{
			if (_predmetiRazredi->GetElement1(i) == predmet) {
				_predmetiRazredi->RemoveElement(i);
				return true;
			}
		}
		return false;
	}
	bool operator==(const Nastavnik& obj) {
		return Osoba::operator==(obj);
	}
	Kolekcija<Predmeti, Razredi>& getPredmetiRazredi() {
		return* _predmetiRazredi;
	}
};
class Ucenik : public Osoba
{
	int _brojUDnevniku;
	Razredi _razred;
	vector<Nastavnik*> _nastavnici;
	Kolekcija<Predmeti, int> _predmetiOcjene;
public:
	Ucenik(const char* imePrezime, Datum datum , int broj, Razredi razred):Osoba(imePrezime, datum)
	{
		_brojUDnevniku = broj;
		_razred = razred;
	}
	bool AddNastavnik(Nastavnik& n) {
		for (size_t i = 0; i < n.getPredmetiRazredi().GetTrenutno(); i++)
		{
			if (n.getPredmetiRazredi().GetElement2(i) == _razred) {
				_nastavnici.push_back(&n);
				return true;
			}
		}
		return false;
	}
	bool AddPredmetOcjenu(const Predmeti& p, int ocjena) {
		for (size_t i = 0; i < _nastavnici.size(); i++)
		{
			if (_nastavnici[i]->getPredmetiRazredi().GetElement1(i) == p) {
				_predmetiOcjene.AddElement(p, ocjena);
				return true;
			}
		}
		return false;
	}
	vector<Nastavnik*> &getNastavnici() {
		return _nastavnici;
	}
	Kolekcija<Predmeti, int> &getPredmetiOcjene() { return _predmetiOcjene; }
	float GetProsjekByNastavnik(const char* ime) {

		for (size_t i = 0; i < _nastavnici.size(); i++)
		{
			if (strcmp(_nastavnici[i]->GetImePrezime(), ime)==0) {

			}
		}
	}
	friend ostream& operator<< (ostream& COUT, const Ucenik& obj)
	{
		cout << crt << "UCENIK" << crt;
		cout << (Osoba&)obj;
		cout << "Br. u dnevniku: " << obj._brojUDnevniku <<"\nRazred: "<<ispisRazredi[obj._razred]<<endl;
		
		return COUT;
	}

};

void main()
{
	/****************************************************************************
	// 1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
	// 2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR
	// CE BITI OZNACENO KAO "RE"
	// 3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA
	// 4. PROGRAMSKI CODE SE TAKODJER NALAZI U FAJLU CODE_.TXT
	// 5. NAZIV I LISTA PARAMETARA FUNKCIJA MORAJU BITI IDENTIÈNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U.
	// 6. NIJE POTREBNO BACATI IZUZETKE. SVE FUNKCIJE VRACAJU TRUE ILI FALSE
	****************************************************************************/

#pragma region TestiranjeDatuma
	Datum danas(26, 11, 2015);
	Datum sutra(danas);
	Datum prekosutra;
	prekosutra = danas;
	cout << danas << endl << sutra << endl << prekosutra << crt;
#pragma endregion

#pragma region TestiranjeKolekcije
	Kolekcija<int, int> kolekcija1;
	int brojElemenata = 15;
	for (size_t i = 0; i < brojElemenata; i++)
		kolekcija1.AddElement(i, i);

	kolekcija1.RemoveElement(0);//uklanja element na osnovu lokacije
	cout << kolekcija1.GetElement1(0) << " " << kolekcija1.GetElement2(0) << endl;
	cout << kolekcija1 << endl;

	Kolekcija<int, int> kolekcija2;
	kolekcija2 = kolekcija1;
	cout << kolekcija2 << crt;
	if (kolekcija1.GetTrenutno() == kolekcija2.GetTrenutno())
		cout << "ISTI BROJ ELEMENATA" << endl;
	Kolekcija<int, int> kolekcija3(kolekcija2);
	cout << kolekcija3 << crt;
#pragma endregion

#pragma region TestiranjeNastavnika
	Nastavnik jasmin("Jasmin Azemovic", Datum(15, 2, 1980));
	Nastavnik adel("Adel Handzic", Datum(15, 10, 1981));
	/*NASTAVNIK MOZE PREDAVATI ISTI PREDMET, ALI TO MORA BITI U RAZLICITIM ODJELJENJIMA I NAJVISE U DVA
	RAZREDA (NA DVIJE RAZLICITE GODINE)*/
	if (jasmin.AddPredmetRazred(Matematika, I1))
		cout << "Predmeti dodan" << endl;
	if (jasmin.AddPredmetRazred(Historija, I1))
		cout << "Predmeti dodan" << endl;

	if (jasmin.AddPredmetRazred(Geografia, I1))
		cout << "Predmeti dodan" << endl;

	if (jasmin.AddPredmetRazred(Geografia, I2))
		cout << "Predmeti dodan" << endl;

	if (adel.AddPredmetRazred(Historija, III1))
		cout << "Predmeti dodan" << endl;

	if (adel.RemovePredmetRazred(Historija))
		cout << "Predmet uklonjen!" << endl;

	Nastavnik goran(adel);
	if (goran == adel)
		cout << "Nastavnici identicni" << endl;
	goran = jasmin;
	if (goran == jasmin)
		cout << "Nastavnici identicni" << endl;

	Kolekcija<Predmeti, Razredi> & predmetiRazredi = jasmin.getPredmetiRazredi();

	if (!jasmin.setBrojTelefona("+38761111222"))
		cout << "Broj telefona nije dodan!" << endl;
	if (!jasmin.setBrojTelefona("+387-61-111-222"))
		cout << "Broj telefona nije dodan!" << endl;
	if (jasmin.setBrojTelefona("+387(61)-111-222"))
		cout << "Broj telefona uspjesno dodan!" << endl;
#pragma endregion

#pragma region TestiranjeUcenika
	Ucenik denis("Denis Music", Datum(8, 10, 1990), 3, I1);
	Ucenik elmin("Elmin Sudic", Datum(15, 6, 1993), 1, I1);
	Ucenik adil("Adil Joldic", Datum(13, 8, 1992), 2, II1);
	/*VODITI RACUNA DA SE DODAJU REFERENCE NA NASTAVNIKE KAKO BI SVI UCENICI DIJELILI ISTE INFORMACIJE O
	NASTAVNICIMA U SLUCAJU DA SE NASTAVNIKU DODA NEKI PREDMET*/
	/*ZA USPJESNO DODAVANJE, NASTAVNIK MORA POSJEDOVATI (PREDAVATI) NAJMANJE JEDAN PREDMET U TOM RAZREDU */
	if (denis.AddNastavnik(jasmin))
		cout << "Nastavnik uspjesno dodan" << endl;
	/*ONEMOGUCITI DODAVANJE ISTIH NASTAVNIKA; POJAM ISTI PODRAZUMIJEVA IDENTICNE VRIJEDNOSTI SVIH ATRIBUTA*/
	if (denis.AddNastavnik(adel))
		cout << "Nastavnik uspjesno dodan" << endl;
	/*DA BI SE DODALA OCJENA ZA ODREDJENI PREDMET UCENIK MORA POSJEDOVATI NASTAVNIKA KOJI PREDAJE TAJ PREDMET*/
	if (denis.AddPredmetOcjenu(Matematika, 3))
		cout << "Ocjena uspjesno dodana" << endl;
	if (denis.AddPredmetOcjenu(Historija, 4))
		cout << "Ocjena uspjesno dodana" << endl;

	vector<Nastavnik*> & nastavnici = denis.getNastavnici();
	cout << "Ucenik Denis ima dodijeljena " << nastavnici.size() << " nastavnika" << endl;

	Kolekcija<Predmeti, int> & uspjeh = denis.getPredmetiOcjene();
	cout << "Denis ima " << uspjeh.GetTrenutno() << " polozenih predmeta" << endl;
//	cout << "Prosjecna ocjena kod nastavnika Jasmin Azemovic je " << denis.GetProsjekByNastavnik("Jasmin Azemovic") << endl;
//
	Ucenik denis2(denis);
	cout << denis2 << endl;

#pragma endregion
	system("pause>0");
}