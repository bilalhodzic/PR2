#include <iostream>
#include <vector>
#include<future>
#include<string>
#include<cstring>
#include<cctype>
#include<ctime>
#include<chrono>
#include <regex>
#include <thread>
#include <mutex>
using namespace std;
const char* crt = "\n-----------------------------------------------\n";
char* AlocirajNizKaraktera(const char* sadrzaj) {
	if (sadrzaj == nullptr) return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}
mutex m;
enum Status { ZAHTJEV_ZAPRIMLJEN, ODUSTAO, ODBIJENA, IZDATA, ISTEKLA, PONISTENA };
enum Sortiranje { RASTUCI, OPADAJUCI };
enum Drzava { SAD, AUSTRALIJA, ENGLESKA };
const char* DrzavaChar[] = { "SAD", "AUSTRALIJA", "ENGLESKA" };

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
	Datum(const Datum& obj) {
		_dan = new int(*obj._dan);
		_mjesec = new int(*obj._mjesec);
		_godina = new int(*obj._godina);
	}
	Datum & operator=(const Datum& obj) {
		if (this != &obj) {
			delete _dan;
			delete _mjesec;
			delete _godina;

			_dan = new int(*obj._dan);
			_mjesec = new int(*obj._mjesec);
			_godina = new int(*obj._godina);
		}
		return *this;
	}
	~Datum()
	{
		delete _dan; _dan = nullptr;
		delete _mjesec; _mjesec = nullptr;
		delete _godina; _godina = nullptr;
	}
	friend ostream& operator<< (ostream& COUT, Datum& obj)
	{
		COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina;
		return COUT;
	}

	bool operator==(const Datum& obj) {
		return *this->_dan == *obj._dan && *this->_mjesec == *obj._mjesec && *this->_godina == *obj._godina;
	}
	Datum operator++() {
		Datum temp = *this;
		*temp._dan += 1;
		return temp;
	}
	int getYear() {
		return*_godina;
	}
	bool operator>(const Datum& obj) {
		return (*_dan + *_mjesec * 30 + *_godina * 365) > (*obj._dan + *obj._mjesec * 30 + *obj._godina * 365);
	}
};

template<class T1, class T2, int max>
class FITKolekcija
{
	T1* _elementi1[max];
	T2* _elementi2[max];
	int _trenutno;
public:
	FITKolekcija()
	{
		for (size_t i = 0; i < max; i++)
		{
			_elementi1[i] = nullptr;
			_elementi2[i] = nullptr;
		}
		_trenutno = 0;
	}
	~FITKolekcija()
	{
		for (size_t i = 0; i < _trenutno; i++)
		{
			delete _elementi1[i]; _elementi1[i] = nullptr;
			delete _elementi2[i]; _elementi2[i] = nullptr;
		}
	}
	FITKolekcija(const FITKolekcija& obj) {
		_trenutno = obj._trenutno;

		for (size_t i = 0; i < _trenutno; i++)
		{
			_elementi1[i] = new T1(*obj._elementi1[i]);
			_elementi2[i] = new T2(*obj._elementi2[i]);

		}
	}
	FITKolekcija & operator=(const FITKolekcija& obj) {
		if (this == &obj)
			return*this;
		_trenutno = obj._trenutno;
	

		for (size_t i = 0; i < _trenutno; i++)
		{
			_elementi1[i] = new T1(*obj._elementi1[i]);
			_elementi2[i] = new T2(*obj._elementi2[i]);


		}
		return*this;
	}
	void Dodaj( T1& el1,  T2& el2) {
		

		if (_trenutno == max) {
			throw exception("dostigli ste maximum");
		}
		else{
			_elementi1[_trenutno] = new T1(el1);
			_elementi2[_trenutno++] = new T2(el2);
		}
	}
	void Sortiraj(Sortiranje sortiranje) {
		if (_trenutno <= 1)
			return;

		for (int i = 0; i < _trenutno - 1; i++) {
			int flag = i;

			if (sortiranje == RASTUCI)
				for (int j = i + 1; j < _trenutno; j++)
					if (*_elementi1[j] < *_elementi1[flag])
						flag = j;

			if (sortiranje == OPADAJUCI)
				for (int j = i + 1; j < _trenutno; j++)
					if (*_elementi1[j] > * _elementi1[flag])
						flag = j;

			if (flag != i) {
				swap(*_elementi1[i], *_elementi1[flag]);
				swap(*_elementi2[i], *_elementi2[flag]);
			}
		}
	}
	
	T1** GetT1() { return _elementi1; }
	T2** GetT2() { return _elementi2; }
	int GetTrenutno() { return _trenutno; }

	friend ostream& operator<< (ostream& COUT, FITKolekcija& obj)
	{
		for (size_t i = 0; i < obj._trenutno; i++)
			COUT << *obj._elementi1[i] << " " << *obj._elementi2[i] << endl;
		return COUT;
	}
	
};


class Viza abstract
{
protected:
	Drzava _drzava;
	Datum _vazenjeOD;
	Datum _vazenjeDO;
	char* _napomena;
	// string se odnosi na razlog promjene statusa, a moguæe je samo 10 izmjena statusa
	FITKolekcija<Status, string, 10> _statusi;
public:
	Viza() :_napomena(AlocirajNizKaraktera(" ")) {}
	Viza(Drzava drzava, Datum _OD, Datum _DO, const char* napomena = nullptr) :_vazenjeDO(_DO), _vazenjeOD(_OD)
	{
		if (napomena != nullptr)
		{
			_napomena = AlocirajNizKaraktera(napomena);
		}
		else
			_napomena = nullptr;
		_drzava = drzava;
	}
	Viza(const Viza& obj):_vazenjeOD(obj._vazenjeOD), _vazenjeDO(obj._vazenjeDO), _drzava(obj._drzava) {
		_napomena = AlocirajNizKaraktera(obj._napomena);
		_statusi = obj._statusi;
	}
	Viza& operator=(const Viza& obj) {
		if (this != &obj) {
			delete[]_napomena;
			_napomena = AlocirajNizKaraktera(obj._napomena);
			_statusi = obj._statusi;
			_vazenjeDO = obj._vazenjeDO;
			_vazenjeOD = obj._vazenjeOD;
			_drzava = obj._drzava;
		}
		return *this;
	}
	virtual ~Viza() { delete[] _napomena; _napomena = nullptr; }
	Drzava GetDrzava() { return _drzava; }
	Datum GetVazenjeOD() { return _vazenjeOD; }
	Datum GetVazenjeDO() { return _vazenjeDO; }
	char* GetNapomena() { return _napomena; }
	FITKolekcija<Status, string, 10>& GetStatuse() { return _statusi; }
	virtual void Info() = 0 {
		cout << " INFO " << crt;
		cout << "Drzava: " << DrzavaChar[_drzava]<<endl;
		cout << "Vazenje: " << _vazenjeOD << " DO: " << _vazenjeDO << endl;
		if(_napomena!=nullptr)
		cout << " Napomena: " << _napomena << endl;
	}
	void DodajStatus(Status status, string s) {
		_statusi.Dodaj(status, s);
	}
	bool operator==(const Viza& obj) {
		return _drzava == obj._drzava && _vazenjeOD == obj._vazenjeOD;
	}
	friend ostream& operator << (ostream& COUT, Viza& obj) {
		cout << DrzavaChar[ obj._drzava] << endl;
		cout << "Vazenje: " << obj._vazenjeOD << " " << obj._vazenjeDO << endl;
		if(obj._napomena!=nullptr)
		cout << "Napomena: " << obj._napomena << endl;

		return COUT;
	}
	void SetNapomena(const char* s) {
		delete[]_napomena;
		_napomena = AlocirajNizKaraktera(s);
	}

};

class PoslovnaViza :virtual public Viza
{
	string _kompanija; //naziv kompanije koja potvrðuje da posluje sa aplikantom
public:
	PoslovnaViza() :_kompanija("") {};
	
	PoslovnaViza(Drzava drzava, Datum _OD, Datum _DO, string kompanija, char* napomena = nullptr)
		: Viza(drzava, _OD, _DO, napomena)
	{
		_kompanija = kompanija;
	}
	friend ostream& operator << (ostream& COUT, PoslovnaViza& obj)
	{
		COUT << obj._drzava << " " << obj._vazenjeOD << " " << obj._vazenjeDO << " " << obj._kompanija << endl;
		COUT << ((obj._napomena != nullptr) ? obj._napomena : "") << endl;
		COUT << "STATUSI -> " << obj._statusi << endl;
		return COUT;
	}
	void Info() {
		cout << crt << " POSLOVNA VIZA  " << crt;
		Viza::Info();
		cout << "Naziv kompanije: " << _kompanija << endl;
		
	}

};

class TuristickaViza : public Viza
{
	string _adresa; //adresa hotele ili drugog smještaja na kojoj æe aplikant boraviti
public:
	TuristickaViza(Drzava drzava, Datum _OD, Datum _DO, string adresa, char* napomena = nullptr) : Viza(drzava, _OD, _DO, napomena)
	{
		_adresa = adresa;
	}
	friend ostream& operator << (ostream& COUT, TuristickaViza& obj)
	{
		COUT << obj._drzava << " " << obj._vazenjeOD << " " << obj._vazenjeDO << " " << obj._adresa << endl;
		COUT << ((obj._napomena != nullptr) ? obj._napomena : "") << endl;
		COUT << "STATUSI -> " << obj._statusi << endl;
		return COUT;
	}
	void Info() {
		cout << crt << " TURISTICKA VIZA  " << crt;
		Viza::Info();
		cout << "Adresa Smjestaja: " << _adresa << endl;

	}
	
};

class Aplikant
{
	char* _imePrezime;
	Datum* _datumRodjenja;
	char* _brojPasosa;
	vector<Viza*> _vize;
public:
	Aplikant(const char* imePrezime, Datum datumRodjenja, const char* brPasosa)
	{
		int vel = strlen(imePrezime) + 1;
		_imePrezime = new char[vel];
		strcpy_s(_imePrezime, vel, imePrezime);
		vel = strlen(brPasosa) + 1;
		_brojPasosa = new char[vel];
		strcpy_s(_brojPasosa, vel, brPasosa);
		_datumRodjenja = new Datum(datumRodjenja);
	}
	~Aplikant()
	{
		delete[]_imePrezime; _imePrezime = nullptr;
		delete[]_brojPasosa; _brojPasosa = nullptr;
		delete _datumRodjenja; _datumRodjenja = nullptr;
		for (size_t i = 0; i < _vize.size(); i++)
		{
			delete _vize[i]; _vize[i] = nullptr;
		}
	}
	friend ostream& operator << (ostream& COUT, Aplikant& obj)
	{
		COUT <<crt<< obj._imePrezime << " " << *obj._datumRodjenja << " " << obj._brojPasosa << endl;
		COUT << "VIZE -> " << endl;
		for (size_t i = 0; i < obj._vize.size(); i++)
			COUT << *obj._vize[i] << endl;
		return COUT;
	}
	vector<Viza* > GetVize() { return _vize; }
	Aplikant(const Aplikant& obj) {
		_imePrezime = AlocirajNizKaraktera(obj._imePrezime);
		_datumRodjenja = new Datum(*obj._datumRodjenja);
		_brojPasosa = AlocirajNizKaraktera(obj._brojPasosa);
		for (size_t i = 0; i < obj._vize.size(); i++)
		{
			if (dynamic_cast<TuristickaViza*>(obj._vize[i]) != nullptr) {
				_vize.push_back(new TuristickaViza(*dynamic_cast<TuristickaViza*>(obj._vize[i])));
			}
			else {
				_vize.push_back(new PoslovnaViza(*dynamic_cast<PoslovnaViza*>(obj._vize[i])));

			}
		}
	}
	
	bool DodajVizu(Viza* obj) {
		TuristickaViza *tViza = dynamic_cast<TuristickaViza*>(obj);
		PoslovnaViza* pViza = nullptr;
		if (tViza == nullptr) {
			pViza = dynamic_cast<PoslovnaViza*>(obj);
		}

		if ((obj->GetVazenjeOD().getYear() - _datumRodjenja->getYear()) < 10)
			return false;

		for (size_t i = 0; i < _vize.size(); i++)
		{
			if (obj->GetDrzava() == _vize[i]->GetDrzava() &&  _vize[i]->GetVazenjeDO()>obj->GetVazenjeOD()) {
				for (size_t j = 0; j < _vize[i]->GetStatuse().GetTrenutno(); j++)
				{
					if (*_vize[i]->GetStatuse().GetT1()[j] == Status::IZDATA) {
						return false;
					}
				}
			}
			if (obj->GetDrzava() == Drzava::SAD && _vize[i]->GetDrzava() == Drzava::SAD) {
				for (size_t j = 0; j < _vize[i]->GetStatuse().GetTrenutno(); j++)
				{
					if (*_vize[i]->GetStatuse().GetT1()[j] == Status::PONISTENA) {
						return false;
					}
				}
			}
		}
		if (tViza != nullptr) {
			_vize.push_back(new TuristickaViza(*tViza));
		}
		else {
			_vize.push_back(new PoslovnaViza(*pViza));
		}
		return true;
	}
	// STATUSI SE MOGU DODAVATI SAMO U REDOSLIJEDU U KOJEM SE NALAZE U ENUMERACIJI NPR.
	// -	NIJE MOGUÆE ODBITI VIZU AKO PRETHODNO NIJE IMALA STATUS DA JE ZAHTJEV_ZAPRIMLJEN;
	// -	NIJE MOGUÆE PONIŠTITI VIZU KOJA PRETHODNO NIJE IZDATA

	//if (jasmin.DodajStatus(&poslovna, ZAHTJEV_ZAPRIMLJEN, "provjeriti navode sa predstavnicima kompanije Microsoft"))
	//	cout << "Status vize uspijesno promijenjen" << endl;
	bool DodajStatus(Viza* obj, Status status, string napomena="") {
		
		for (size_t i = 0; i < _vize.size(); i++)
		{
			if (*_vize[i] == *obj) {
				bool zaprimljeno = false;
				bool izdata = false;
				for (size_t j = 0; j < _vize[i]->GetStatuse().GetTrenutno(); j++)
				{
					if (*_vize[i]->GetStatuse().GetT1()[j] == Status::ZAHTJEV_ZAPRIMLJEN) {
						zaprimljeno = true;
					}
					if (*_vize[i]->GetStatuse().GetT1()[j] == Status::IZDATA) {
						izdata = true;
					}
				}

				if (status == Status::ZAHTJEV_ZAPRIMLJEN) {
					_vize[i]->DodajStatus(status, napomena);
					return true;
				}
				else if ((status == Status::ODUSTAO || status == Status::ODBIJENA || status == Status::IZDATA) && zaprimljeno) {
					_vize[i]->DodajStatus(status, napomena);
					return true;
				}
				else if ((status == Status::PONISTENA || status == Status::ISTEKLA) && izdata) {
					_vize[i]->DodajStatus(status, napomena);
					return true;
				}
			}
		}
		return false;
	}
	//U ZASEBNOJ NITI URADITI PRINTANJE VIZE...KORISTITI METODU SLEEP_FOR
	//	jasmin.PrintajVizu(&turisticka);
	void PrintajVizu(Viza* obj) {
		for (size_t i = 0; i < _vize.size(); i++)
		{
			if (*obj == *_vize[i]) {
				thread t([](Viza * obj) {
					m.lock();
					obj->Info();
					this_thread::sleep_for(chrono::seconds(2));
					m.unlock();
					}, _vize[i]);
				t.join();
			}
		}
	}
	//VRAÆA PODATKE O SVIM VIZAMA KOJE SU IZDATE ZA ODREÐENU DRŽAVU, A KOJE SU IMALE ODREÐENI STATUS
	//vector<Viza*> jasminVize = jasmin.GetVizeByDrzava(SAD, PONISTENA);

	vector<Viza*> GetVizeByDrzava(Drzava d, Status s) {
		vector<Viza*> temp;
		for (size_t i = 0; i < _vize.size(); i++)
		{
			if (_vize[i]->GetDrzava() == d) {
				for (size_t j = 0; j < _vize[i]->GetStatuse().GetTrenutno(); j++)
				{
					if (*_vize[i]->GetStatuse().GetT1()[j] == s) {
						temp.push_back(_vize[i]);
					}
				}
			}
		}
		return temp;
	}
	////UNUTAR NAPOMENE MIJENJA SADRŽAJ "nemaju informaciju" SA "su upoznti sa" - KORISTITI REGEX
	//jasmin.ZamijeniRijec("nemaju informaciju", "su upoznti sa");
	void ZamijeniRijec(string rijec, string zam) {
		regex r("(" + rijec + ")");
		for (size_t i = 0; i < _vize.size(); i++)
		{
			if (_vize[i]->GetNapomena() != nullptr) {
				string a = regex_replace(string(_vize[i]->GetNapomena()),r, zam);
				_vize[i]->SetNapomena(a.c_str());
			}
		}
	}

};

void main()
{

	/****************************************************************************
	// 1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
	// 2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME
	//    ERROR ÆE BITI OZNACENO KAO "RE"
	// 3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJEÈILO GUBLJENJE URAÐENOG ZADATKA
	// 4. PROGRAMSKI CODE SE TAKOÐER NALAZI U FAJLU CODE.TXT
	// 5. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIÈNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U,
	//    OSIM U SLUÈAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOÆNE FUNKCIJE MOŽETE IMENOVATI
	//    I DODAVATI PO ŽELJI.
	// 6. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNAÈENO.
	****************************************************************************/

	Datum danas(15, 2, 2017);
	Datum sutra(++danas); // inkrementiranjem se uvecava dan za 1
	Datum prekosutra;
	Datum dat15022017(15, 2, 2017), dat18082017(18, 8, 2017), dat11052018(11, 5, 2018), dat11122017(11, 12, 2017);


	prekosutra = danas;
	if (prekosutra == danas)
		cout << "Datumi su jednaki" << endl;
	cout << danas << endl << sutra << endl << prekosutra << crt;

	int v6 = 6, v13 = 13, v32 = 32, v63 = 63, v98 = 98, v109 = 109, v196 = 196;

	FITKolekcija<int, int, 7> brojevi;

	brojevi.Dodaj(v196, v6);
	brojevi.Dodaj(v13, v32);
	brojevi.Dodaj(v98, v196);
	brojevi.Dodaj(v63, v13);
	brojevi.Dodaj(v98, v196);
	brojevi.Dodaj(v196, v6);

	cout << brojevi << crt;
	////NA KOJI NAÈIN ÆE SE VRŠITI SORTIRANJE PRVENSTVENO ZAVISI OD VRIJEDNOSTI PARAMETRA, A VRŠI SE NA OSNOVU VRIJEDNOSTI TIPA T1
	brojevi.Sortiraj(RASTUCI);
	cout << brojevi << crt;
	brojevi.Sortiraj(OPADAJUCI);
	cout << brojevi << crt;

	try
	{
		//U SLUÈAJU PREKORAÈENJA DEFINISANE VELIÈINE KOLEKCIJE, POTREBNO JE BACITI IZUZETAK
		brojevi.Dodaj(v13, v196);
		brojevi.Dodaj(v13, v196);

	}
	catch (exception & err)
	{
		cout << "Error -> " << err.what() << endl;
	}
	Aplikant jasmin("Jasmin Azemovic", Datum(15, 5, 1979), "BS6985645");
	PoslovnaViza poslovna(SAD, dat15022017, dat18082017, "Microsoft");



	// NOVA VIZA SE NE MOŽE DODATI UKOLIKO:
	// -	JE APLIKANT MLAÐI OD 10 GODINA
	// -	U TOM PERIODU (ODNOSI SE NA PERIOD VIZE OD - DO) NE POSTOJI VAŽEÆA (POJAM VAŽEÆA PODRAZUMIJEVA DA JE POSLJEDNJI STATUS VIZE BIO IZDATA TJ. DA VIZA NIJE 	PONIŠTENA ILI ISTEKLA) VIZA ZA TU DRŽAVU, BEZ OBZIRA NA NJENU VRSTU.	
	// -	JE NEKA OD RANIJIH VIZA PONIŠTENA (OVO SE ODNOSI SAMO NA VIZE ZA DRŽAVU: SAD)

	if (jasmin.DodajVizu(&poslovna))
		cout << "Podaci o vizi uspješno zaprimljeni" << endl;

	// STATUSI SE MOGU DODAVATI SAMO U REDOSLIJEDU U KOJEM SE NALAZE U ENUMERACIJI NPR.
	// -	NIJE MOGUÆE ODBITI VIZU AKO PRETHODNO NIJE IMALA STATUS DA JE ZAHTJEV_ZAPRIMLJEN;
	// -	NIJE MOGUÆE PONIŠTITI VIZU KOJA PRETHODNO NIJE IZDATA

	if (jasmin.DodajStatus(&poslovna, ZAHTJEV_ZAPRIMLJEN, "provjeriti navode sa predstavnicima kompanije Microsoft")) {
		cout << "Status vize uspijesno promijenjen" << endl;
	}

	else
		cout << "Aplikant " << jasmin << " ne posjeduje evidentiranu trazenu vizu ili status vize nema odgovarajucu vrijednost" << endl;


	if (jasmin.DodajStatus(&poslovna, PONISTENA, "predstavnicima kompanije Microsoft nemaju informaciju o posjeti navedenog aplikanta"))
		cout << "Status vize uspijesno promijenjen" << endl;
	else
		cout << "Aplikant " << jasmin << " ne posjeduje evidentiranu trazenu vizu ili status vize nema odgovarajucu vrijednost" << endl;

	TuristickaViza turisticka(ENGLESKA, dat18082017, dat11122017, "Whitehall Pl, London SW1A 2BD, UK");

	if (jasmin.DodajStatus(&turisticka, ZAHTJEV_ZAPRIMLJEN))
		cout << "Status vize uspijesno promijenjen" << endl;
	else
		cout << "Aplikant " << jasmin << " ne posjeduje evidentiranu trazenu vizu ili status vize nema odgovarajucu vrijednost" << endl;

	if (jasmin.DodajStatus(&turisticka, IZDATA))
	{
		cout << "Status vize uspijesno promijenjen" << endl;
		//U ZASEBNOJ NITI URADITI PRINTANJE VIZE...KORISTITI METODU SLEEP_FOR
		jasmin.PrintajVizu(&turisticka);
	}
	else
		cout << "Aplikant " << jasmin << " ne posjeduje evidentiranu trazenu vizu ili status vize nema odgovarajucu vrijednost" << endl;
	//VRAÆA PODATKE O SVIM VIZAMA KOJE SU IZDATE ZA ODREÐENU DRŽAVU, A KOJE SU IMALE ODREÐENI STATUS
	vector<Viza*> jasminVize = jasmin.GetVizeByDrzava(SAD, PONISTENA);
	for (size_t i = 0; i < jasminVize.size(); i++)
	{
		cout << crt << jasminVize[i] << crt;

	}
	//UNUTAR NAPOMENE MIJENJA SADRŽAJ "nemaju informaciju" SA "su upoznti sa" - KORISTITI REGEX
	jasmin.ZamijeniRijec("nemaju informaciju", "su upoznti sa");
	system("pause>0");
}