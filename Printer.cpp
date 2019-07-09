#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <thread>

using namespace std;

const char* crt = "\n---------------------------------------\n";

class DatumVrijeme
{
	int* _dan, * _mjesec, * _godina, * _sati, * _minuti;
public:
	DatumVrijeme(int dan = 1, int mjesec = 1, int godina = 2000, int sati = 0, int minuti = 0)
	{
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
	DatumVrijeme & operator=(const DatumVrijeme& obj) {
		if (this == &obj)
			return *this;
		_dan = new int(*obj._dan);
		_mjesec = new int(*obj._mjesec);
		_godina = new int(*obj._godina);
		_sati = new int(*obj._sati);
		_minuti = new int(*obj._minuti);
		return *this;
	}
	~DatumVrijeme()
	{
		delete _dan; _dan = nullptr;
		delete _mjesec; _mjesec = nullptr;
		delete _godina; _godina = nullptr;
		delete _sati; _sati = nullptr;
		delete _minuti; _minuti = nullptr;
	}
	friend ostream& operator<< (ostream& COUT, DatumVrijeme& obj)
	{
		COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina << " " << *obj._sati << ":" << *obj._minuti;
		return COUT;
	}
	bool operator==(DatumVrijeme& d) {
		return *_dan == *d._dan && *_mjesec == *d._mjesec && *_godina == *d._godina;
	}
};

template<class T1, class T2 = int>
class FITKolekcija
{
	T1* _elementi1;
	T2* _elementi2;
	int _trenutno;
public:
	FITKolekcija()
	{
		_elementi1 = nullptr;
		_elementi2 = nullptr;
		_trenutno = 0;
	}
	FITKolekcija(const FITKolekcija& obj) {
		_trenutno = obj._trenutno;
		_elementi1 = new T1[_trenutno];
		_elementi2 = new T2[_trenutno];
		for (size_t i = 0; i < _trenutno; i++)
		{
			_elementi1[i] = obj._elementi1[i];
			_elementi2[i] = obj._elementi2[i];
		}
	}
	FITKolekcija& operator=(const FITKolekcija& obj) {
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
		return *this;
	}
	~FITKolekcija()
	{
		delete[] _elementi1; _elementi1 = nullptr;
		delete[] _elementi2; _elementi2 = nullptr;
	}
	T1* GetT1() { return _elementi1; }
	T2* GetT2() { return _elementi2; }
	int GetTrenutno() { return _trenutno; }
	
	void Dodaj(const T1& el1, const T2& el2) {
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

	//	SORTIRANJE �LANOVA KOLEKCIJE SE VR�I U RASTU�EM REDOSLIJEDU NA OSNOVU VRIJEDNOSTI ELEMENTA TIPA T1
	void Sortiraj() {
		for (size_t i = 0; i < _trenutno; i++)
		{
			for (size_t j = i+1; j < _trenutno; j++)
			{
				if (_elementi1[i] > _elementi1[j]) {
					//T1 *temp1 = new T1(_elementi1[i]);
					T1 temp1 = _elementi1[i];
					_elementi1[i] = _elementi1[j];
					_elementi1[j] = temp1;
					//T2 *temp2 = new T2(_elementi2[i]);
					T2 temp2 = _elementi2[i];

					_elementi2[i] = _elementi2[j];
					_elementi2[j] = temp2;
				}
			}
		}
	}

	FITKolekcija<T1, T2>* GetJedinstveni() {
		FITKolekcija<T1, T2> *temp=new FITKolekcija<T1, T2>;
		for (size_t i = 0; i < _trenutno; i++)
		{
			bool flag = false;
			for (size_t j = 0; j < temp->GetTrenutno(); j++)
			{
				if (_elementi1[i] == temp->GetT1()[j]) {
					flag = true;

				}
				
				
			}
			if (!flag) {
				temp->Dodaj(_elementi1[i], _elementi2[i]);
			}
		}
		return temp;
	}
	//	BROJ 2 SE ODNOSI NA LOKACIJU/INDEKS UNUTAR LISTE NA KOJI JE POTREBNO DODATI NOVE ELEMENTE
//	brojevi.DodajNaLokaciju(v109, v6, 2);
	void DodajNaLokaciju(const T1& el1, const T2& el2, int index) {
		T1* temp1 = new T1[_trenutno + 1];
		T2* temp2 = new T2[_trenutno + 1];
		bool dodano = false;
		for (size_t i = 0; i < _trenutno; i++)
		{
			if (dodano) {
				temp1[i] = _elementi1[i+1];
				temp2[i] = _elementi2[i+1];

			}
			if (i == index - 1) {
				temp1[i] = el1;
				temp2[i] = el2;
				dodano = true;
			}
			else {
				temp1[i] = _elementi1[i];
				temp2[i] = _elementi2[i];
			}

		}
		
		delete[]_elementi1;
		delete[]_elementi2;
		_elementi1 = temp1;
		_elementi2 = temp2;
	}
	void Ukloni(T2& el) {
		for (size_t i = 0; i < _trenutno; i++)
		{
			if (el == _elementi2[i]) {
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
	friend ostream& operator<< (ostream& COUT, FITKolekcija& obj)
	{
		for (size_t i = 0; i < obj._trenutno; i++)
			COUT << obj._elementi1[i] << " " << obj._elementi2[i] << endl;
		return COUT;
	}
};

enum vrstaDokumenta { PDF, DOC, TXT, HTML };
// ostream& operator<<(ostream & cout,vrstaDokumenta & obj)
//{
//	 switch (obj) {
//	 case PDF:
//		 cout << "PDF"; break;
//	 case DOC:
//		 cout << "DOC"; break;
//	 case TXT:
//			 cout << "TXT"; break; 
//	 case HTML:
//				 cout << "HTML"; break;
//	 }
//	 return cout;
//}

class Dokument
{
	vrstaDokumenta _vrsta;
	string _naziv;
	string _sadrzaj;
	int _brojStranica;
public:
	Dokument() { _brojStranica = 0; }
	Dokument(vrstaDokumenta vrsta, string naziv)
	{
		_naziv = naziv; _vrsta = vrsta; _brojStranica = 0;
	}
	string GetNaziv() { return _naziv; };
	string GetSadrzaj() { return _sadrzaj; };
	vrstaDokumenta GetVrsta() { return _vrsta; };
	void UvecajBrojStranica() { _brojStranica++; }
	int GetBrojStranica() { return _brojStranica; }
	void DodajSadrzaj(string sadrzaj) {
		int vel = sadrzaj.length();
		_sadrzaj += sadrzaj;
		while (vel > 0) {
			if(vel>30)
			_brojStranica += 1;
			vel -= 30;
		}
	}
	friend ostream& operator<<(ostream& COUT, Dokument& obj)
	{
		COUT << obj._naziv << "." << obj._vrsta << " (" << obj._brojStranica << ")\n" << obj._sadrzaj << endl;
		return COUT;
	}
	bool operator==(Dokument& d) {
		return _vrsta == d._vrsta && _naziv == d._naziv && _sadrzaj == d._sadrzaj;
	}
};

class Uredjaj abstract
{
protected:
	char* _proizvodjac;
	char* _model;
public:
	Uredjaj(const char* proizvodjac, const char* model)
	{
		int vel = strlen(proizvodjac) + 1;
		_proizvodjac = new char[vel];
		strcpy_s(_proizvodjac, vel, proizvodjac);
		vel = strlen(model) + 1;
		_model = new char[vel];
		strcpy_s(_model, vel, model);
	}
	Uredjaj(const Uredjaj& obj) {
		int vel = strlen(obj._proizvodjac) + 1;
		_proizvodjac = new char[vel];
		strcpy_s(_proizvodjac, vel, obj._proizvodjac);
		vel = strlen(obj._model) + 1;
		_model = new char[vel];
		strcpy_s(_model, vel, obj._model);
	}
	Uredjaj& operator=(const Uredjaj& obj) {
		if (this == &obj)
			return*this;
		delete[]_proizvodjac;
		delete[]_model;

		int vel = strlen(obj._proizvodjac) + 1;
		_proizvodjac = new char[vel];
		strcpy_s(_proizvodjac, vel, obj._proizvodjac);
		vel = strlen(obj._model) + 1;
		_model = new char[vel];
		strcpy_s(_model, vel, obj._model);
		return *this;
	}
	~Uredjaj()
	{
		delete[] _proizvodjac; _proizvodjac = nullptr;
		delete[] _model; _model = nullptr;
	}
	friend ostream& operator<<(ostream& COUT, Uredjaj& obj)
	{
		COUT << obj._proizvodjac << "." << obj._model << endl;
		return COUT;
	}
};

class Printer: public Uredjaj
{
	FITKolekcija<DatumVrijeme, Dokument> _printaniDokumenti;
	vector<string> _zabranjeneRijeci;
public:
	Printer(const char* proizvodjac, const char* model):Uredjaj(proizvodjac, model){}
	
	void DodajZabranjenuRijec(string rijec){
		for (size_t i = 0; i < _zabranjeneRijeci.size(); i++)
		{
			if (_zabranjeneRijeci[i] == rijec) {
				throw exception("Ne moze dva puta ista rijec");
			}
		}
		_zabranjeneRijeci.push_back(rijec);
	}
	bool uslovPrintanja(Dokument& dokument) {
		if (!regex_match(dokument.GetNaziv(), regex("[a-zA-Z]{5,15}"))) {
			return false;
		}
		for (size_t i = 0; i < _zabranjeneRijeci.size(); i++)
		{
			if (regex_search(dokument.GetSadrzaj(), regex(" (" + _zabranjeneRijeci[i] + ")"))) {
				return false;
			}
		}
		return true;
	}
	void Printaj(DatumVrijeme& datum, Dokument& dokument) {
		_printaniDokumenti.Dodaj(datum, dokument);
		
		if (uslovPrintanja(dokument)) {
			cout << crt << "Printam dokument " << dokument.GetNaziv() << ".. (LOADING)" << crt;
			this_thread::sleep_for(chrono::seconds(2));
			cout << dokument.GetSadrzaj() << crt;
		}
		else
			throw exception("ERROR: Dokument nije validan!!");
	}
	float GetProsjecanBrojStranicaPoDatumu(DatumVrijeme& datum) {
		float suma = 0, brojac=0;
		for (size_t i = 0; i < _printaniDokumenti.GetTrenutno(); i++)
		{
			if (_printaniDokumenti.GetT1()[i] == datum) {
				suma += _printaniDokumenti.GetT2()->GetBrojStranica();
				brojac++;
			}
		}
		return suma/brojac ;
	}
	string GetTopZabranjenuRijec() {

		for (size_t i = 0; i < _zabranjeneRijeci.size(); i++)
		{

		}
		return "RE";
	}
	void UkloniDokumente() {
		for (size_t i = 0; i < _printaniDokumenti.GetTrenutno(); i++)
		{
			if (!uslovPrintanja(_printaniDokumenti.GetT2()[i])) {
				_printaniDokumenti.Ukloni(_printaniDokumenti.GetT2()[i]);
			}
		}
	}
	FITKolekcija<DatumVrijeme, Dokument>& GetPrintaniDokumenti() { return _printaniDokumenti; };
	vector<string>& GetZabranjeneRijeci() { return _zabranjeneRijeci; };
	friend ostream& operator<<(ostream& COUT, Printer& obj)
	{
		cout << " PRINTER " << endl;
		cout << (Uredjaj&)obj;
		cout << "Dokumenti:  " << endl;
		for (size_t i = 0; i < obj._printaniDokumenti.GetTrenutno(); i++)
		{
			cout << obj._printaniDokumenti.GetT1()[i] << obj._printaniDokumenti.GetT2()[i] << endl;
		}
		return COUT;
	}
};

void main()
{
	/****************************************************************************
	// 1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
	// 2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR
	//    �E BITI OZNACENO KAO "RE"
	// 3. SPA�AVAJTE PROJEKAT KAKO BI SE SPRIJE�ILO GUBLJENJE URA�ENOG ZADATKA
	// 4. PROGRAMSKI CODE SE TAKO�ER NALAZI U FAJLU CODE.TXT
	// 5. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTI�NI ONIMA KOJI SU KORI�TENI U TESTNOM CODE-U,
	//    OSIM U SLU�AJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMO�NE FUNKCIJE MO�ETE
	//    IMENOVATI I DODAVATI PO �ELJI.
	// 6. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNA�ENO.
	****************************************************************************/
#pragma region TestiranjeDatumVrijeme
	DatumVrijeme danas(1, 2, 2017, 10, 15);
	DatumVrijeme sutra(danas);
	DatumVrijeme prekosutra;
	prekosutra = danas;
	cout << danas << endl << sutra << endl << prekosutra << crt;
#pragma endregion
#pragma region FITKolekcija
	int v6 = 6, v13 = 13, v32 = 32, v63 = 63, v98 = 98, v109 = 109, v196 = 196;

	FITKolekcija<int, int> brojevi;
	FITKolekcija<int, int> brojevi2;
	

	brojevi.Dodaj(v196, v6);
	brojevi.Dodaj(v13, v32);
	brojevi.Dodaj(v98, v196);
	brojevi.Dodaj(v63, v13);
	brojevi.Dodaj(v98, v196);
	brojevi.Dodaj(v196, v6);

	cout << brojevi << crt;
//	SORTIRANJE �LANOVA KOLEKCIJE SE VR�I U RASTU�EM REDOSLIJEDU NA OSNOVU VRIJEDNOSTI ELEMENTA TIPA T1
	brojevi.Sortiraj();
	cout << brojevi << crt;
//	BROJ 2 SE ODNOSI NA LOKACIJU/INDEKS UNUTAR LISTE NA KOJI JE POTREBNO DODATI NOVE ELEMENTE
	brojevi.DodajNaLokaciju(v109, v6, 2);
	cout << brojevi << crt;
	brojevi.Sortiraj();
	cout << brojevi << crt;
//	 METODA GetJedinstveni VRA�A LISTU JEDINSTVENIH ELEMENATA TJ. ELEMENATA KOJI NE SADR�E DUPLIKATE 
//	 (POJAM DUPLIKAT SE ODNOSI NA ISTE VRIJEDNOSTI ELEMENATA T1 I T2). ELEMENTI KOJI SE DUPLIRAJU SE U 
//	 OVOJ LISTI TREBAJU POJAVITI SAMO JEDNOM.
	FITKolekcija<int, int> *jedinstveni = brojevi.GetJedinstveni();
	cout <<* jedinstveni << crt;
	*jedinstveni = brojevi;
	cout << *jedinstveni << crt;
#pragma endregion
#pragma region Dokument
	Dokument ispitPRIII(DOC, "ispitPRIII.doc");
//	BROJ STRANICA DOKUMENTA SE AUTOMATSKI ODRE�UJE PRILIKOM DODAVANJA SADR�AJA. ZA POTREBE ISPITA PRETPOSTAVLJAMO
//	DA NA JEDNU STRANICU MO�E STATI 30 ZNAKOVA UKLJU�UJU�I I RAZMAKE
	ispitPRIII.DodajSadrzaj("NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA	DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR �E BITI OZNACENO KAO RE");
	cout << "Broj stranica -> " << ispitPRIII.GetBrojStranica() << endl;
	Dokument ispitBaze(DOC, "ispitBaze.doc");
	ispitBaze.DodajSadrzaj("PROGRAMSKI CODE SE TAKO�ER NALAZI U FAJLU CODE.TXT");
	cout << ispitBaze << endl;//ISPISUJE SVE DOSTUPNE PODATKE O DOKUMENTU

	Printer hp3200("HP", "3200");
//	PRINTER NE�E DOZVOLITI PRINTANJE DOKUMENATA U �IJEM SADR�AJU SE NALAZI NEKA OD ZABRANJENIH RIJE�I
	try {
		hp3200.DodajZabranjenuRijec("RE");// :)
		hp3200.DodajZabranjenuRijec("RAT");
		hp3200.DodajZabranjenuRijec("UBITI");
		hp3200.DodajZabranjenuRijec("RE");// ONEMOGU�ITI PONAVLJANJE ZABRANJENIH RIJE�I, KORISTITI ITERATORE
		hp3200.DodajZabranjenuRijec("MRZITI");
	}
	catch (exception& err) {
		cout << "ERROR: " << err.what() << endl;
	}

	try
	{
	/*	 DA BI PRINTER ISPRINTAO NEKI DOKUMENT MORAJU BITI ZADOVOLJENA SLJEDE�A PRAVILA:
		 1. NAZIV DOKUMENTA MORA BITI U SLJEDE�EM FORMATU npr: ispitPRIII.doc
		 NAZIV DOKUMENTA MO�E SADR�AVATI SAMO SLOVA (NAJMANJE 5, NAJVI�E 15), A EKSTENZIJA MO�E 
		 BITI SAMO NEKA OD DOZVOLJENIH VRSTOMDOKUMENTA
		 2. SADR�AJ DOKUMENTA U SEBI NE SMIJE POSJEDOVATI NITI JEDNU ZABRANJENU RIJE�
		 UKOLIKO NEKI OD NAVEDENIH USLOVA NIJE ZADOVOLJEN FUNKCIJA TREBA DA BACI EXCEPTION SA 
		 ODGOVARAJU�OM PORUKOM, ALI �E DOKUMENT BITI POHRANJEN U KOLEKCIJU _printaniDokumenti. 
		 UKOLIKO DOKUMENT ISPUNJAVA SVE USLOVE ZA PRINTANJE POTREBNO JE NA KONZOLU ISPISATI 
		 SADR�AJ DOKUMENTA KOJI SE PRINTA*/

		hp3200.Printaj(danas, ispitPRIII);
		hp3200.Printaj(danas, ispitBaze);


		 /*IMPLEMENTIRATI PRINTANJE U ZASEBNIM NITIMA UZ KORI�TENJE sleep_for FUNKCIJE
		 VODITI RA�UNA O DIJELJENJU ZAJEDNI�KIH RESURSA*/
	}
	catch (exception & err)
	{
		cout << err.what() << endl;
	}

//	KOD PORE�ENJA DATUMA PRINTANJA NIJE POTREBNO POREDITI MINUTE, SAMO DATUM I SATE
	cout << "Prosjecan broj printanih stranica za " << danas << " je -> " << hp3200.GetProsjecanBrojStranicaPoDatumu(danas) << crt;
	cout << "Najcesce koristena zabranjena rijec je -> " << hp3200.GetTopZabranjenuRijec() << crt;

	Printer hp4000(hp3200);
	cout << "Prosjecan broj printanih stranica za " << danas << " je -> " << hp4000.GetProsjecanBrojStranicaPoDatumu(danas) << crt;
	cout << "Najcesce koristena zabranjena rijec je -> " << hp4000.GetTopZabranjenuRijec() << crt;
	hp4000.UkloniDokumente();//UKLANJA SVE DOKUMENTE KOJI NISU ZADOVOLJILI USLOVE ZA PRINTANJE
	cout << hp4000 << crt;

#pragma endregion
	system("pause>0");
}