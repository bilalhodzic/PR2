#include <iostream>
#include <vector>
#include <regex>
using namespace std;
const char* crt = "\n---------------------------------------\n";
 char* alociraj(const char* s) {
	if (s != nullptr) {
		int vel = strlen(s) + 1;
		char* temp = new char[vel];
		strcpy_s(temp, vel, s);
		return temp;
	}
	return nullptr;
}
class Datum {
	int* _dan, * _mjesec, * _godina;
public:
	Datum(int dan = 1, int mjesec = 1, int godina = 2000) {
		_dan = new int(dan);
		_mjesec = new int(mjesec);
		_godina = new int(godina);
	}
	Datum(const Datum& obj) :Datum(*obj._dan, *obj._mjesec, *obj._godina) {};
	Datum& operator=(const Datum& obj) {
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
	~Datum() {
		delete _dan; _dan = nullptr;
		delete _mjesec; _mjesec = nullptr;
		delete _godina; _godina = nullptr;
	}
	friend ostream& operator<< (ostream& COUT, Datum& obj) {
		COUT << *obj._dan << " " << *obj._mjesec << " " << *obj._godina;
		return COUT;
	}
	bool operator==(const Datum& obj) {
		return *_dan == *obj._dan && *_mjesec == *obj._mjesec && *_godina == *obj._godina;
	}
	Datum& operator++() {
		*_dan += 1;
		return *this;
	}
	int GetDatumInDani() {
		return (*_dan + *_mjesec * 30 + *_godina * 365);
	}
};
class Izuzetak :public exception {
	Datum _datum;//KORISTITE DANASNJI DATUM
	string _funkcija;//FUNKCIJA U KOJOJ JE NASTAO IZUZETAK
	int _linija;//LINIJA CODE-A U KOJOJ JE NASTAO IZUZETAK
public:
	Izuzetak(const char* napomena, string funkcija, int linija) :exception(napomena) {
		_funkcija = funkcija;
		_linija = linija;
		//_datum = datum;
	}
	friend ostream& operator<<(ostream& cout, Izuzetak& obj) {
		cout << obj.what() << endl;
		cout << obj._funkcija << " " << obj._linija << endl;
		//cout << obj._datum << endl;
		return cout;
	}
};

template<class T1, class T2, int max>
class Kolekcija {
	T1 _elementi1[max];
	T2 _elementi2[max];
	int* _trenutno;
public:
	Kolekcija() {
		_trenutno = new int(0);
	}
	~Kolekcija()
	{
		delete _trenutno;
	}
	Kolekcija(const Kolekcija& obj) {
		_trenutno = new int(*obj._trenutno);
		for (size_t i = 0; i < *_trenutno; i++)
		{
			_elementi1[i] = obj._elementi1[i];
			_elementi2[i] = obj._elementi2[i];

		}
	}
	Kolekcija& operator=(const Kolekcija& obj) {
		if (this != &obj) {
			delete _trenutno;
			_trenutno = new int(*obj._trenutno);
			for (size_t i = 0; i < *_trenutno; i++)
			{
				_elementi1[i] = obj._elementi1[i];
				_elementi2[i] = obj._elementi2[i];

			}
		}
		return *this;
	}
	void AddElement(const T1& el1, const T2& el2) {
		if (*_trenutno == max) {
			throw Izuzetak("Dostigli ste maksimum", __FUNCTION__, __LINE__);
		}
		_elementi1[*_trenutno] = el1;
		_elementi2[*_trenutno] = el2;
		(*_trenutno)++;
	}
	T1 &GetElement1(int i) {
		if (i<0 || i> * _trenutno)
			throw Izuzetak("Ne postoji ta lokacija", __FUNCTION__, __LINE__);
		return _elementi1[i];
	}
	T2 &GetElement2(int i) {
		if (i<0 || i> * _trenutno)
			throw Izuzetak("Ne postoji ta lokacija", __FUNCTION__, __LINE__);
		return _elementi2[i];
	}
	int GetMax() { return max; }
	int GetTrenutno() { return *_trenutno; }
	friend ostream& operator<<(ostream& cout, Kolekcija& obj) {
		for (size_t i = 0; i < *obj._trenutno; i++)
		{
			cout << obj._elementi1[i] << " " << obj._elementi2[i] << endl;
		}
		return cout;
	}
	bool operator==(const Kolekcija& obj) {
		return _elementi1 == obj._elementi1 && _elementi2 == obj._elementi2;
	}
	T1& operator[](int i) {
		if (i<0 || i> * _trenutno)
			throw Izuzetak("Ne postoji ta lokacija", __FUNCTION__, __LINE__);
		return _elementi1[i];
	}
};


enum enumKursevi { HtmlCSSJavaScript, SoftwareEngeneeringFundamentals, MasteringSQL, WindowsSecurity };
const char* enumKurseviChar[]= {" HtmlCSSJavaScript", "SoftwareEngeneeringFundamentals", "MasteringSQL", "WindowsSecurity "};

class Kurs {
	enumKursevi _kurs;
	Datum _pocetak;
	Datum _kraj;
	char* _imePredavaca;
public:
	Kurs(enumKursevi kurs=HtmlCSSJavaScript, const char* ime=" ", Datum pocetak=Datum(), Datum kraj=Datum()) :_pocetak(), _kraj() {
		_kurs = kurs;
		_imePredavaca = alociraj(ime);
	}
	Kurs(const Kurs& obj) {
		_kurs = obj._kurs;
		_pocetak = obj._pocetak;
		_kraj = obj._kraj;
		_imePredavaca = alociraj(obj._imePredavaca);
	}
	Kurs& operator=(const Kurs& obj) {
		if (this != &obj) {
			_kurs = obj._kurs;
			_pocetak = obj._pocetak;
			_kraj = obj._kraj;
			delete[]_imePredavaca;
			_imePredavaca = alociraj(obj._imePredavaca);
		}
		return *this;
	}
	~Kurs()
	{
		delete[]_imePredavaca;
		_imePredavaca = nullptr;
	}
	friend ostream& operator<<(ostream& cout, Kurs& obj) {
		cout << "KURS" << endl;
		cout << enumKurseviChar[obj._kurs] << endl;
		cout << "Trajanje: " << obj._pocetak << obj._kraj << endl;
		cout << "Predavac: " << obj._imePredavaca << endl;
		return cout;
	}
	bool operator==(const Kurs& obj) {
		return _kurs == obj._kurs && _pocetak == obj._pocetak && strcmp(_imePredavaca, obj._imePredavaca) == 0;
	}
	enumKursevi GetKurs() { return _kurs; }
	Datum getPocetak() { return _pocetak; }
	Datum getKraj() { return _kraj; }
	char* GetIme() { return _imePredavaca; }

};
bool ProvjeriFormatTelefona(string telefon) {
	return regex_match(telefon, regex("\\((06.)\\)\\d{3}\\-\\d{3}"));
}
class Polaznik {
	static int ID;
	const int _polaznikID;
	//SVAKOM NOVOM POLAZNIKU AUTOMATSKI DODIJELITI NOVI ID (AUTOINCREMENT) POCEVSI OD BROJA 1
	char* _imePrezime;
	string _kontaktTelefon; //BROJ TELEFONA TREBA BITI U FORMATU (06X)XXX-XXX 
	Kolekcija<Kurs*, int, 10> _uspjesnoOkoncaniKursevi;
	//INT PREDSTAVLJA OSTVARENI PROCENAT NA ISPITU, A JEDAN POLAZNIK MOZE POLOZITI NAJVISE 10 KURSEVA
public:
	Polaznik(const char* imePrezime, string telefon) :_polaznikID(ID++) {
		_imePrezime = alociraj(imePrezime);
		_kontaktTelefon = telefon;
	}
	Polaznik(Polaznik& obj):_polaznikID(ID++),_uspjesnoOkoncaniKursevi(obj._uspjesnoOkoncaniKursevi) {
		_imePrezime = alociraj(obj._imePrezime);
		_kontaktTelefon = obj._kontaktTelefon;
		//for (size_t i = 0; i < obj._uspjesnoOkoncaniKursevi.GetTrenutno(); i++)
		//{
		//	//*_uspjesnoOkoncaniKursevi.GetElement1(i) = *obj._uspjesnoOkoncaniKursevi.GetElement1(i);
		//	_uspjesnoOkoncaniKursevi.AddElement(new Kurs(*obj._uspjesnoOkoncaniKursevi.GetElement1(i)), obj._uspjesnoOkoncaniKursevi.GetElement2(i));

		//}
		
		//_uspjesnoOkoncaniKursevi = obj._uspjesnoOkoncaniKursevi;
	}
	Polaznik& operator=( Polaznik& obj) {
		if (this != &obj) {
			//delete[] _imePrezime;
			_imePrezime = alociraj(obj._imePrezime);
			_kontaktTelefon = obj._kontaktTelefon;
	
			for (size_t i = 0; i < obj._uspjesnoOkoncaniKursevi.GetTrenutno(); i++)
			{
				//*_uspjesnoOkoncaniKursevi.GetElement1(i) = *obj._uspjesnoOkoncaniKursevi.GetElement1(i);
				_uspjesnoOkoncaniKursevi.AddElement(new Kurs(*obj._uspjesnoOkoncaniKursevi.GetElement1(i)), obj._uspjesnoOkoncaniKursevi.GetElement2(i));
			}
			//_uspjesnoOkoncaniKursevi = obj._uspjesnoOkoncaniKursevi;
		}
		return *this;
	}
	~Polaznik() {
		delete[] _imePrezime; _imePrezime = nullptr;
		for (size_t i = 0; i < _uspjesnoOkoncaniKursevi.GetTrenutno(); i++)
		{
			delete _uspjesnoOkoncaniKursevi[i];
		}
	}
	void AddKurs(Kurs &k, int procenat) {
		_uspjesnoOkoncaniKursevi.AddElement( new Kurs(k), procenat);
	}
	int GetID() { return _polaznikID; }
	friend ostream& operator<<(ostream& cout, Polaznik& obj) {
		cout << "POLAZNIK" << endl;
		cout << "ID: " << obj._polaznikID<<endl;
		cout << "Ime: " << obj._imePrezime << " " << obj._kontaktTelefon << endl;
		for (size_t i = 0; i < obj._uspjesnoOkoncaniKursevi.GetTrenutno(); i++)
		{
			if (obj._uspjesnoOkoncaniKursevi.GetElement1(i) != nullptr) {
				cout << obj._uspjesnoOkoncaniKursevi.GetElement1(i) << " " << obj._uspjesnoOkoncaniKursevi.GetElement2(i) << endl;
			}
		}
		return cout;
	}
	bool operator==(const Polaznik& obj) {
		return strcmp(_imePrezime, obj._imePrezime) == 0 && _uspjesnoOkoncaniKursevi == obj._uspjesnoOkoncaniKursevi;
	}
};
int Polaznik::ID = 1;

class SkillsCentar {
	string _nazivCentra;
	vector<Kurs> _kursevi;//KURSEVI KOJE NUDI ODREDJENI CENTAR
	Kolekcija<Kurs, Polaznik*, 150> _aplikanti;
public:
	SkillsCentar(string naziv) { _nazivCentra = naziv; }
	SkillsCentar(const SkillsCentar& obj) :_kursevi(obj._kursevi), _aplikanti(obj._aplikanti) {
		_nazivCentra = obj._nazivCentra;
	}
	void operator =(const SkillsCentar& obj) 
	{
		_nazivCentra = obj._nazivCentra;
		_kursevi = obj._kursevi;
		_aplikanti = obj._aplikanti;
	}
	bool ProvjeriKoliziju(Kurs& kurs) {
		for (size_t i = 0; i < _kursevi.size(); i++)
		{
			if (_kursevi[i].getKraj().GetDatumInDani() < kurs.getPocetak().GetDatumInDani()) {
				return false;
			}
		}
		return true;
		
	}
	void AddKurs(Kurs& k) {
		if(ProvjeriKoliziju(k)==false)
			throw Izuzetak("Ne moze poceti kurs dok traje drugi kurs", __FUNCTION__, __LINE__);
		for (size_t i = 0; i < _kursevi.size(); i++)
		{
			if(_kursevi[i]==k)
				throw Izuzetak("\nkurs vec postoji", __FUNCTION__, __LINE__);

		}
		_kursevi.push_back(k);
	}
	void AddAplikaciju(Kurs& k, Polaznik& p) {
		bool flag = false;
		for (size_t i = 0; i < _kursevi.size(); i++)
		{
			if (_kursevi[i] == k) {
				flag = true;
				break;
			}
		}
		if(!flag)
			throw Izuzetak("Nemoguce aplicirati za kurs koji nije registrovan", __FUNCTION__, __LINE__);
		for (size_t i = 0; i < _aplikanti.GetTrenutno(); i++)
		{
			if (_aplikanti.GetElement1(i) == k) {
				if (*_aplikanti.GetElement2(i) == p) {
					throw Izuzetak("Nemoguce aplicirati za isti kurs", __FUNCTION__, __LINE__);
				}
			}
		}
			_aplikanti.AddElement(k, &p);
	
	}
	
	void DodajUspjesnoOkoncanKurs(int id, Kurs& k, int procenat) {
		for (size_t i = 0; i < _aplikanti.GetTrenutno(); i++)
		{
			if (_aplikanti.GetElement2(i)->GetID() == id && _aplikanti.GetElement1(i)==k &&procenat>=55) {
				_aplikanti.GetElement2(i)->AddKurs(k, procenat);
				return;
			}
		}
	}
	//	mostar.GetPolazniciByPredavac("Jasmin Azemovic", SoftwareEngeneeringFundamentals);
	//VRACA INFORMACIJE O POLAZNICIMA KOJI SU KOD ODREDJENOG PREDAVACA USPJESNO OKONCALI ODREDJENI KURS
	vector<Polaznik> GetPolazniciByPredavac(string ime, enumKursevi k) {
		vector<Polaznik>temp;
		for (size_t i = 0; i < _aplikanti.GetTrenutno(); i++)
		{
			
			
		}
		return temp;
	}

};
void main()
{
	/****************************************************************************
	1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
	2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR ĆE BITI OZNACENO KAO "RE"
	3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJEČILO GUBLJENJE URAĐENOG ZADATKA
	4. PROGRAMSKI CODE SE TAKOĐER NALAZI U FAJLU CODE.TXT
	5. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIČNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U, OSIM U SLUCAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOĆNE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
	6. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNAČENO.
	****************************************************************************/

#pragma region TestiranjeDatuma
	Datum danas(26, 11, 2015);
	Datum sutra(danas);
	Datum prekosutra;
	prekosutra = danas;
	cout << danas << endl << sutra << endl << prekosutra << crt;
#pragma endregion
#pragma region TestiranjeKolekcije
	Kolekcija<int, int, 10> kolekcija1;
	try
	{
		for (size_t i = 0; i < kolekcija1.GetMax(); i++)
			kolekcija1.AddElement(i, i + 2);
		//FUNKCIJA TREBA BACITI IZUZETAK U SLUCAJ DA NEMA VISE PROSTORA ZA DODAVANJE NOVIH ELEMENATA
		cout << kolekcija1.GetElement1(0) << " " << kolekcija1.GetElement2(0) << endl;
		cout << kolekcija1.GetElement1(20) << " " << kolekcija1.GetElement2(20) << endl;
		//FUNKCIJA TREBA DA BACI IZUZETAK UKOLIKO ELEMENT NA ZAHTIJEVANOJ LOKACIJI NE POSTOJI
	}
	catch (Izuzetak & err)
	{
		cout << "Greska -> " << err << endl;
	}

	cout << kolekcija1 << endl;
	Kolekcija<int, int, 10> kolekcija2;
	kolekcija2 = kolekcija1;
	cout << kolekcija2 << crt;
	if (kolekcija1.GetTrenutno() == kolekcija2.GetTrenutno())
		cout << "ISTI BROJ ELEMENATA" << endl;
	Kolekcija<int, int, 10> kolekcija3(kolekcija2);
	cout << kolekcija3 << crt;
#pragma endregion
#pragma region TestiranjeKursa
	Kurs sef(SoftwareEngeneeringFundamentals, "Jasmin Azemovic", Datum(28, 1, 2016), Datum(15, 2, 2016));
	cout << sef << endl;
	Kurs msql(MasteringSQL, "Adel Handzic", Datum(28, 2, 2016), Datum(15, 3, 2016));
	sef = msql;
	if (sef == msql)//KURSEVI SU ISTI AKO POSJEDUJU IDENTICNE VRIJEDNOSTI SVIH ATRIBUTA
		cout << "ISTI SU KURSEVI" << endl;
	Kurs msql2(msql);
	cout << msql2 << endl;
#pragma endregion
#pragma region TestiranjePolaznika
	string telefon1 = "(061)111-111";
	string telefon2 = "(061)111222";
	string telefon3 = "(061)111-333";

	if (!ProvjeriFormatTelefona(telefon1))
		cout << "Broj " << telefon1 << " nije validan" << endl;
	if (!ProvjeriFormatTelefona(telefon2))
		cout << "Broj " << telefon2 << " nije validan" << endl;
	if (!ProvjeriFormatTelefona(telefon3))
		cout << "Broj " << telefon3 << " nije validan" << endl;


	Polaznik denis("Denis Music", telefon1);
	Polaznik denis2("Denis2 Music2", telefon3);
	

#pragma endregion

#pragma region TestiranjeCentra
	try {
		SkillsCentar mostar("Skills Center Mostar");
		if (mostar.ProvjeriKoliziju(sef))
			//JEDAN KURS NE SMIJE POCETI DOK DRUGI TRAJE TJ. VRIJEME ODRZAVANJA KURSA SE NE SMIJE POKLAPATI
			mostar.AddKurs(sef);
		/*if (mostar.ProvjeriKoliziju(msql))
			mostar.AddKurs(msql);
		if (mostar.ProvjeriKoliziju(msql2))
			mostar.AddKurs(msql2);*/
		//ONEMOGUCITI DODAVANJE IDENTICNIH KURSEVA. FUNKCIJA TREBA DA BACI IZUZETAK UKOLIKO SE POKUSA DODATI IDENTICAN KURS
		mostar.AddAplikaciju(sef, denis);
		//ONEMOGUCITI APLICIRANJE ZA KURSEVE KOJI NISU REGISTROVANI U CENTRU
		//mostar.AddAplikaciju(msql, denis);
		//mostar.AddAplikaciju(msql, denis);
		//ONEMOGUCITI APLICIRANJE ZA ISTI KURS. FUNKCIJA BAZA IZUZETAK
		cout << denis2 << endl;
		denis2 = denis;
		if (denis == denis2)
			//POLAZNICI SU ISTI AKO POSJEDUJU ISTO IME I AKO SU POHADJALI ISTE KURSEVE
			cout << "ISTI SU" << endl;

		mostar.DodajUspjesnoOkoncanKurs(1, sef, 60);//BROJ 1 OZNACAVA ID POLAZNIKA. FUNKCIJA JE ZADUZENA DA POLAZNIKU DODA INFORMACIJU O USPJESNO POLOZENOM KURSU KOJI JE POSLAN KAO PARAMETAR. PREDUSLOV ZA DODAVANJE JE DA JE POLAZNIK PRETHODNO APLICIRAO ZA TAJ KURS, TE DA JE NA ISPITU OSTVARIO VISE OD 55%
		mostar.DodajUspjesnoOkoncanKurs(1, msql, 83);
		vector<Polaznik> listaPolaznika = mostar.GetPolazniciByPredavac("Jasmin Azemovic", SoftwareEngeneeringFundamentals);//VRACA INFORMACIJE O POLAZNICIMA KOJI SU KOD ODREDJENOG PREDAVACA USPJESNO OKONCALI ODREDJENI KURS
//
//		if (mostar.RemoveKurs(sef))//ONEMOGUCITI UKLANJANJE KURSA KOJI SU VEC PRIJAVILI NEKI OD POLAZNIKA
//			cout << "Kurs " << sef << " uspjesno uklonjen iz centra " << mostar << endl;
//
//		SkillsCentar sarajevo = mostar;
//		cout << sarajevo << endl;
	}
	catch (Izuzetak & err) {
		cout << err << endl;
	}
#pragma endregion
	system("pause>0");
}