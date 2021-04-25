#include "cMain.h"
#include <windows.h>
#include <typeinfo> 
#include <string>
#include "Liga.h"
#include "LigaID.h"
wxBEGIN_EVENT_TABLE(cMain, wxFrame) // INICJALIZACJA TABELI EVENTÓW
	EVT_BUTTON(10001, pokazMenuWyboruStatystyki) //<- przycisk Liga Angielska
	EVT_BUTTON(10002, pokazMenuWyboruStatystyki) //<- przycisk Liga Hiszpanska
	EVT_BUTTON(10003, pokazMenuWyboruStatystyki) //<- przycisk Liga Wloska
	EVT_BUTTON(10004, pokazTabele) //<- przycisk Tabela
	EVT_BUTTON(10005, pokazTerminarz) //<- przycisk Terminarz
	EVT_BUTTON(10006, pokazOstatnieMecze) //<- przycisk Ostatnie mecze
	EVT_BUTTON(10007, pokazNajlepszychZawodnikow) //<- przycisk Najlepsi Zawodnicy
	EVT_BUTTON(10008,pokazMenuWyboruLigi) //<- przycisk powrotu do wyboru ligi
	EVT_BUTTON(10009, pokazMenuWyboruStatystyki) //<- przycisk powrotu do wyboru statystyki
wxEND_EVENT_TABLE()

// jest funkcja lambda,RTTI, kontenery STL oraz wyj¹tki(throw) w switchach

enum liga{LIGA_ANGIELSKA = 1,LIGA_HISZPANSKA,LIGA_WLOSKA};

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Football App",wxPoint(30,30),wxSize(1000,700), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX)) //okno rodzica,id okna,nazwa,odleg³oœæ od lewego górnego rogu ekranu,rozmiar okna,style który nie pozwala na resize
{	
																		//wxSize - poziom,pion
	wxColourDatabase bazaKolorow; // USTALANIE KOLORU T£A
	//this->SetBackgroundColour(bazaKolorow.Find("FIREBRICK"));
	this->SetBackgroundColour(wxColor("#7cbfbf"));  //fajny zielony #76b577
	this->SetFocus();
	//OBRAZY
	handler = new wxPNGHandler;
	wxImage::AddHandler(handler);
	logoPremierLeague = new wxStaticBitmap(this, wxID_ANY, wxBitmap(".\\pictures\\PremierLeague.png", wxBITMAP_TYPE_PNG), wxPoint(115, 400));
	logoLaLiga = new wxStaticBitmap(this, wxID_ANY, wxBitmap(".\\pictures\\LaLiga.png", wxBITMAP_TYPE_PNG), wxPoint(435, 400));
	logoSerieA = new wxStaticBitmap(this, wxID_ANY, wxBitmap(".\\pictures\\SerieA.png", wxBITMAP_TYPE_PNG), wxPoint(774, 400));
	logoTabela = new wxStaticBitmap(this, wxID_ANY, wxBitmap(".\\pictures\\tabelaSymbol.png", wxBITMAP_TYPE_PNG), wxPoint(120, 400));
	logoOstatnieMecze = new wxStaticBitmap(this, wxID_ANY, wxBitmap(".\\pictures\\ostMeczeSymbol.png", wxBITMAP_TYPE_PNG), wxPoint(553, 400));
	logoTerminarz = new wxStaticBitmap(this, wxID_ANY, wxBitmap(".\\pictures\\terminarzSymbol.png", wxBITMAP_TYPE_PNG), wxPoint(335, 400));
	logoNajlepsiZawodnicy = new wxStaticBitmap(this, wxID_ANY, wxBitmap(".\\pictures\\najlepsiSymbol.png", wxBITMAP_TYPE_PNG), wxPoint(775, 400));
	//LIGI
	

	// TU S¥ OBIEKTY POTRZEBNE DO EKRANU WYBORU LIGI
	
	polecenieWyboruLigi = new wxStaticText(this, wxID_ANY, "Wybierz ligê", wxPoint(400, 100));
	przyciskLigaAngielska = new wxButton(this, 10001, "Angielska\n Premier League", wxPoint(100, 275), wxSize(150, 100));
	przyciskLigaHiszpanska = new wxButton(this, 10002, "Hiszpañska\n La Liga", wxPoint(425, 275), wxSize(150, 100));
	przyciskLigaWloska = new wxButton(this, 10003, "W³oska\n Serie A", wxPoint(750, 275), wxSize(150, 100));
	
	// TU S¥ OBIEKTY POTRZEBNE DO EKRANU WYBORU STATYSTYK
	polecenieWyboruStatystyk = new wxStaticText(this, wxID_ANY, "Wybierz statystykê", wxPoint(350, 100));
	przyciskTabelaLigowa = new wxButton(this, 10004, "Tabela ligowa", wxPoint(100, 275), wxSize(150, 100));
	przyciskTerminarz = new wxButton(this, 10005, "Terminarz", wxPoint(316, 275), wxSize(150, 100));
	przyciskOstatnieMecze = new wxButton(this, 10006, "Ostatnie mecze", wxPoint(532, 275), wxSize(150, 100));
	przyciskNajlepsiZawodnicy = new wxButton(this, 10007, "Statystyki\n zawodników", wxPoint(750, 275), wxSize(150, 100));
	przyciskWyborInnejLigi = new wxButton(this, 10008, "Wybierz inn¹ ligê", wxPoint(437, 550), wxSize(125, 85));
	informacjaKtoraLiga = new wxStaticText(this, wxID_ANY, "Aktualnie wybrano: Premier League", wxPoint(440, 170));
	// TU JEST OBIEKT UNIWERSALNEGO PRZYCISKU POWROTU DO WYBORU STATYSTYK
	przyciskPowrotuDoStatystyk = new wxButton(this, 10009, "Wybierz inn¹\nstatystykê", wxPoint(437, 550), wxSize(125, 85));

	// TU S¥ OBIEKTY DO INICJALIZACJI POSZCZEGÓLNYCH STATYSTYK
	// TABELA
	inicjalizujTabele();
	// TERMINARZ
	inicjalizujTerminarz();
	// OSTATNIE MECZE
	inicjalizujOstatnieMecze();
	// NAJLEPSI ZAWODNICY
	inicjalizujNajlepszychZawodnikow();

	// DEKLARACJE CZCIONEK DLA POSZCZEGÓLNYCH OBIEKTÓW
	wxFont czcionkaNapisow(30, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL); // rozmiar,rodzina,styl i waga czcionki
	wxFont czcionkaPrzyciskow(15, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	wxFont czcionkaPrzyciskowWyboruLigi(14, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	wxFont czcionkaDlaPrzyciskuWyborInnejLigi(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	wxFont czcionkaDlaInformacjiKtoraLiga(18, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL); 

	// INICJALIZACJE CZCIONEK
	polecenieWyboruLigi->SetFont(czcionkaNapisow); // ustawianie czcionki dla konkretnego wxObiektu
	przyciskLigaAngielska->SetFont(czcionkaPrzyciskowWyboruLigi);
	przyciskLigaHiszpanska->SetFont(czcionkaPrzyciskowWyboruLigi);
	przyciskLigaWloska->SetFont(czcionkaPrzyciskowWyboruLigi);
	polecenieWyboruStatystyk->SetFont(czcionkaNapisow);
	przyciskTabelaLigowa->SetFont(czcionkaPrzyciskow);
	przyciskTerminarz->SetFont(czcionkaPrzyciskow);
	przyciskOstatnieMecze->SetFont(czcionkaPrzyciskow);
	przyciskNajlepsiZawodnicy->SetFont(czcionkaPrzyciskow);
	przyciskWyborInnejLigi->SetFont(czcionkaDlaPrzyciskuWyborInnejLigi);
	informacjaKtoraLiga->SetFont(czcionkaDlaInformacjiKtoraLiga);
	przyciskPowrotuDoStatystyk->SetFont(czcionkaDlaPrzyciskuWyborInnejLigi);

	// NA POCZ¥TKU PROGRAMU NALE¯Y UKRYÆ NIEPOTRZEBNE ELEMENTY
	polecenieWyboruStatystyk->Hide();
	przyciskTabelaLigowa->Hide();
	przyciskOstatnieMecze->Hide();
	przyciskTerminarz->Hide();
	przyciskNajlepsiZawodnicy->Hide();
	przyciskWyborInnejLigi->Hide();
	informacjaKtoraLiga->Hide();
	przyciskPowrotuDoStatystyk->Hide();
	logoTabela->Hide();
	logoTerminarz->Hide();
	logoNajlepsiZawodnicy->Hide();
	logoOstatnieMecze->Hide();
	ukryjElementyTabeli();
	ukryjElementyTerminarza();
	ukryjElementyOstatnichMeczy();
	ukryjElementyNajlepszychZawodnikow();
}
cMain::~cMain()
{
	if (czyLigaAngielska)
		delete ligaAngielska;
	else if (czyLigaHiszpanska)
		delete ligaHiszpanska;
	else if (czyLigaWloska)
		delete ligaWloska;

}

void cMain::schowajMenuWyboruStatystyk()
{
	polecenieWyboruStatystyk->Hide();
	przyciskTabelaLigowa->Hide();
	przyciskOstatnieMecze->Hide();
	przyciskTerminarz->Hide();
	przyciskNajlepsiZawodnicy->Hide();
	przyciskWyborInnejLigi->Hide();
	informacjaKtoraLiga->Hide();
	logoTabela->Hide();
	logoTerminarz->Hide();
	logoNajlepsiZawodnicy->Hide();
	logoOstatnieMecze->Hide();
}

void cMain::pokazMenuWyboruStatystyki(wxCommandEvent &evt)
{
	Refresh(); //odœwie¿a rysowanie t³a ¿eby ³adnie siê zmienia³o
	switch (evt.GetId())
	{
	case 10001:
		ligaAngielska = new Liga(NazwaLigi::PREMIER_LEAGUE);
		
		czyLigaAngielska = true;
		wybranaLiga = 1;
		informacjaKtoraLiga->SetLabelText("Premier League");
		this->SetBackgroundColour(wxColor("#e69429"));
		break;
	case 10002:
		ligaHiszpanska = new Liga(NazwaLigi::LA_LIGA);
		czyLigaHiszpanska = true;
		wybranaLiga = 2;
		informacjaKtoraLiga->SetLabelText("La Liga");
		informacjaKtoraLiga->SetPosition(wxPoint(480, 170));
		this->SetBackgroundColour(wxColor("#e2ed40"));
		break;
	case 10003:
		ligaWloska = new Liga(NazwaLigi::SERIE_A);
		czyLigaWloska = true;
		wybranaLiga = 3;
		informacjaKtoraLiga->SetLabelText("Serie A");
		informacjaKtoraLiga->SetPosition(wxPoint(480, 170));
		this->SetBackgroundColour(wxColor("#76b577"));
		break;
	}
	
// POKAZYWANIE/UKRYWANIE ELEMENTÓW

polecenieWyboruLigi->Hide();
przyciskLigaAngielska->Hide();
przyciskLigaHiszpanska->Hide();
przyciskLigaWloska->Hide();
logoLaLiga->Hide();
logoPremierLeague->Hide();
logoSerieA->Hide();
polecenieWyboruStatystyk->Show();
przyciskTabelaLigowa->Show();
przyciskOstatnieMecze->Show();
przyciskTerminarz->Show();
przyciskNajlepsiZawodnicy->Show();
przyciskWyborInnejLigi->Show();
informacjaKtoraLiga->Show();
logoTabela->Show();
logoTerminarz->Show();
logoNajlepsiZawodnicy->Show();
logoOstatnieMecze->Show();

//chowanie z tabel
ukryjElementyTabeli();
//chowanie z terminarza
ukryjElementyTerminarza();
//chowanie z ostatnich meczy
ukryjElementyOstatnichMeczy();
//chowanie z najlepszych zawodników
ukryjElementyNajlepszychZawodnikow();
	evt.Skip();
}

void cMain::pokazMenuWyboruLigi(wxCommandEvent& evt)
{
	if (czyLigaAngielska)
		delete ligaAngielska;
	else if (czyLigaHiszpanska)
		delete ligaHiszpanska;
	else if (czyLigaWloska)
		delete ligaWloska;
	Refresh();
	this->SetBackgroundColour(wxColor("#7cbfbf"));
	// POKAZYWANIE/UKRYWANIE ELEMENTÓW
	polecenieWyboruLigi->Show();
	przyciskLigaAngielska->Show();
	przyciskLigaHiszpanska->Show();
	przyciskLigaWloska->Show();
	logoLaLiga->Show();
	logoPremierLeague->Show();
	logoSerieA->Show();
	polecenieWyboruStatystyk->Hide();
	przyciskTabelaLigowa->Hide();
	przyciskOstatnieMecze->Hide();
	przyciskTerminarz->Hide();
	przyciskNajlepsiZawodnicy->Hide();
	przyciskWyborInnejLigi->Hide();
	przyciskPowrotuDoStatystyk->Hide();
	logoTabela->Hide();
	logoTerminarz->Hide();
	logoNajlepsiZawodnicy->Hide();
	logoOstatnieMecze->Hide();
	informacjaKtoraLiga->Hide();
	informacjaKtoraLiga->SetPosition(wxPoint(440, 170));
	evt.Skip();
}

void cMain::pokazTabele(wxCommandEvent& evt)
{
	schowajMenuWyboruStatystyk();
	switch (wybranaLiga)
	{
		
	case LIGA_ANGIELSKA:
	
		wpiszDoTabeli(ligaAngielska->getTabela()->getDruzyny() ,
			ligaAngielska->getTabela()->getBramki(),
			ligaAngielska->getTabela()->getPunkty());

		break;
	case LIGA_HISZPANSKA:
		wpiszDoTabeli(ligaHiszpanska->getTabela()->getDruzyny(),
			ligaHiszpanska->getTabela()->getBramki(),
			ligaHiszpanska->getTabela()->getPunkty());
		break;
	case LIGA_WLOSKA:
		wpiszDoTabeli(ligaWloska->getTabela()->getDruzyny(),
			ligaWloska->getTabela()->getBramki(),
			ligaWloska->getTabela()->getPunkty());
		break;
	default:
		throw "Nie ma takiej ligi.";
	}
	przyciskPowrotuDoStatystyk->Show();
	pokazElementyTabeli();
	
}

void cMain::pokazTerminarz(wxCommandEvent& evt)
{
	// TODO: funkcja wyœwietlaj¹ca terminarz, w miarê mo¿liwoœci ju¿ z zewnêtrznej klasy
	schowajMenuWyboruStatystyk();
	switch (wybranaLiga)
	{
	case LIGA_ANGIELSKA:
		wpiszDoTerminarza(ligaAngielska->getPrzyszleMecze()->getGospodarze(),
			ligaAngielska->getPrzyszleMecze()->getGoscie(),
			ligaAngielska->getPrzyszleMecze()->getDatyIGodzinyMeczow());
		break;
	case LIGA_HISZPANSKA:
		wpiszDoTerminarza(ligaHiszpanska->getPrzyszleMecze()->getGospodarze(),
			ligaHiszpanska->getPrzyszleMecze()->getGoscie(),
			ligaHiszpanska->getPrzyszleMecze()->getDatyIGodzinyMeczow());
		break;
	case LIGA_WLOSKA:
		wpiszDoTerminarza(ligaWloska->getPrzyszleMecze()->getGospodarze(),
			ligaWloska->getPrzyszleMecze()->getGoscie(),
			ligaWloska->getPrzyszleMecze()->getDatyIGodzinyMeczow());
		break;
	default:
		throw "Nie ma takiej ligi.";
	}
	przyciskPowrotuDoStatystyk->Show();
	pokazElementyTerminarza();

}
	
void cMain::pokazOstatnieMecze(wxCommandEvent& evt)
{
	// TODO: funkcja wyœwietlaj¹ca ostatnie mecze, w miarê mo¿liwoœci ju¿ z zewnêtrznej klasy
	schowajMenuWyboruStatystyk();
	int ktoraLiga = [&]()->int {return wybranaLiga; }(); //lambda
	switch (ktoraLiga)
	{
	case LIGA_ANGIELSKA:
		wpiszDoOstatnichMeczy(ligaAngielska->getOstatnieMecze()->getOGospodarze(),
			ligaAngielska->getOstatnieMecze()->getOGoscie(),
			ligaAngielska->getOstatnieMecze()->getBramkiGospodarzy(),
			ligaAngielska->getOstatnieMecze()->getBramkiGosci());
		
		break;
	case LIGA_HISZPANSKA:
		wpiszDoOstatnichMeczy(ligaHiszpanska->getOstatnieMecze()->getOGospodarze(),
			ligaHiszpanska->getOstatnieMecze()->getOGoscie(),
			ligaHiszpanska->getOstatnieMecze()->getBramkiGospodarzy(),
			ligaHiszpanska->getOstatnieMecze()->getBramkiGosci());
		break;
	case LIGA_WLOSKA:
		wpiszDoOstatnichMeczy(ligaWloska->getOstatnieMecze()->getOGospodarze(),
			ligaWloska->getOstatnieMecze()->getOGoscie(),
			ligaWloska->getOstatnieMecze()->getBramkiGospodarzy(),
			ligaWloska->getOstatnieMecze()->getBramkiGosci());
		
		break;
	default:
		throw "Nie ma takiej ligi.";
	}
	przyciskPowrotuDoStatystyk->Show();
	pokazElementyOstatnichMeczy();
}

void cMain::pokazNajlepszychZawodnikow(wxCommandEvent& evt)
{
	// TODO: funkcja wyœwietlaj¹ca najlepszych zawodników, w miarê mo¿liwoœci ju¿ z zewnêtrznej klasy
	schowajMenuWyboruStatystyk();
	switch (wybranaLiga)
	{
	case LIGA_ANGIELSKA:
		wpiszDoNajlepszychZawodnikow(ligaAngielska->getZawodnicy()->getNajlepsiStrzelcy(),
			ligaAngielska->getZawodnicy()->getNajlepsiAsystenci(),
			ligaAngielska->getZawodnicy()->getIleStrzelili(),
			ligaAngielska->getZawodnicy()->getIleAsystowali());
		break;
	case LIGA_HISZPANSKA:
		wpiszDoNajlepszychZawodnikow(ligaHiszpanska->getZawodnicy()->getNajlepsiStrzelcy(),
			ligaHiszpanska->getZawodnicy()->getNajlepsiAsystenci(),
			ligaHiszpanska->getZawodnicy()->getIleStrzelili(),
			ligaHiszpanska->getZawodnicy()->getIleAsystowali());
		break;
	case LIGA_WLOSKA:
		wpiszDoNajlepszychZawodnikow(ligaWloska->getZawodnicy()->getNajlepsiStrzelcy(),
			ligaWloska->getZawodnicy()->getNajlepsiAsystenci(),
			ligaWloska->getZawodnicy()->getIleStrzelili(),
			ligaWloska->getZawodnicy()->getIleAsystowali());
		break;
	default:
		throw "Nie ma takiej ligi.";
	}
	przyciskPowrotuDoStatystyk->Show();
	pokazElementyNajlepszychZawodnikow();
}

void cMain::inicjalizujTabele()
{
	int wysokosc = 20;
	string nazwa_druzyny = "";
	wxFont czcionkaTabela(15, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	kolumnaMiejsca[0] = new wxStaticText(this, wxID_ANY, "R", wxPoint(245, wysokosc));
	kolumnaDruzyny[0] = new wxStaticText(this, wxID_ANY, "Dru¿yna", wxPoint(325, wysokosc));
	kolumnaBramki[0] = new wxStaticText(this, wxID_ANY, "RB", wxPoint(615, wysokosc));
	kolumnaPunkty[0] = new wxStaticText(this, wxID_ANY, "PKT", wxPoint(720, wysokosc));

	kolumnaMiejsca[0]->SetFont(czcionkaTabela);
	kolumnaDruzyny[0]->SetFont(czcionkaTabela);
	kolumnaBramki[0]->SetFont(czcionkaTabela);
	kolumnaPunkty[0]->SetFont(czcionkaTabela);
	wysokosc += 35;
	for (int i = 1; i < 21; i++)
	{
		
		if(i > 9)
			kolumnaMiejsca[i] = new wxStaticText(this, wxID_ANY, to_string(i), wxPoint(240, wysokosc));
		else
			kolumnaMiejsca[i] = new wxStaticText(this, wxID_ANY, to_string(i), wxPoint(245, wysokosc)); //¿eby numery tabeli ³adnie siê uk³ada³y

		kolumnaDruzyny[i] = new wxStaticText(this, wxID_ANY,"Druzyna w tabeli", wxPoint(290, wysokosc));
		kolumnaBramki[i] = new wxStaticText(this, wxID_ANY, "+100", wxPoint(610, wysokosc)); //+350
		kolumnaPunkty[i] = new wxStaticText(this, wxID_ANY, "100", wxPoint(727, wysokosc)); //jeszcze +100
		kolumnaMiejsca[i]->SetFont(czcionkaTabela);
		kolumnaBramki[i]->SetFont(czcionkaTabela);
		kolumnaDruzyny[i]->SetFont(czcionkaTabela);
		kolumnaPunkty[i]->SetFont(czcionkaTabela);
		wysokosc += 23;
	}
	
	
	
}

void cMain::pokazElementyTabeli()
{
	for (int i = 0; i < 21; i++)
	{
		kolumnaMiejsca[i]->Show();
		kolumnaDruzyny[i]->Show();
		kolumnaBramki[i]->Show();
		kolumnaPunkty[i]->Show();
	}
}

void cMain::ukryjElementyTabeli()
{
	for (int i = 0; i < 21; i++)
	{
		kolumnaMiejsca[i]->Hide();
		kolumnaDruzyny[i]->Hide();
		kolumnaBramki[i]->Hide();
		kolumnaPunkty[i]->Hide();
	}
}

void cMain::inicjalizujTerminarz()
{

	wxFont czcionkaTerminarz(15, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	int wysokosc = 100;
	if (typeid(int) != typeid(wysokosc)) //RTTI czy coœ posz³o nie tak z inicjalizacj¹
		throw "Zly typ";
	for (int i = 0; i < 10; i++)
	{

		kolumnaGospodarze[i] = new wxStaticText(this, wxID_ANY, "Druzyna gosp", wxPoint(200, wysokosc));
		kolumnaGoscie[i] = new wxStaticText(this, wxID_ANY, "Druzyna gosc", wxPoint(450, wysokosc)); //+350
		kolumnaMyslnik[i] = new wxStaticText(this, wxID_ANY, "-", wxPoint(379, wysokosc)); //+350
		kolumnaDataIGodzina[i] = new wxStaticText(this, wxID_ANY, "20.01.2021   19:00", wxPoint(650, wysokosc)); //jeszcze +100
		kolumnaGospodarze[i]->SetFont(czcionkaTerminarz);
		kolumnaGoscie[i]->SetFont(czcionkaTerminarz);
		kolumnaMyslnik[i]->SetFont(czcionkaTerminarz);
		kolumnaDataIGodzina[i]->SetFont(czcionkaTerminarz);
		wysokosc += 40;
	}
}

void cMain::pokazElementyTerminarza()
{
	for (int i = 0; i < 10; i++)
	{
		kolumnaGospodarze[i]->Show();
		kolumnaGoscie[i]->Show();
		kolumnaMyslnik[i]->Show();
		kolumnaDataIGodzina[i]->Show();
	}
}

void cMain::ukryjElementyTerminarza()
{
	for (int i = 0; i < 10; i++)
	{
		kolumnaGospodarze[i]->Hide();
		kolumnaGoscie[i]->Hide();
		kolumnaMyslnik[i]->Hide();
		kolumnaDataIGodzina[i]->Hide();
		
	}
}

void cMain::inicjalizujOstatnieMecze()
{
	wxFont czcionkaOstatnieMecze(15, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	int wysokosc = 100;
	
	if (typeid(int) != typeid(wysokosc)) //RTTI czy coœ posz³o nie tak z inicjalizacj¹
		throw "Zly typ";
	for (int i = 0; i < 10; i++)
	{

		oKolumnaGospodarze[i] = new wxStaticText(this, wxID_ANY, "Druzyna gosp", wxPoint(285, wysokosc));
		oKolumnaGoscie[i] = new wxStaticText(this, wxID_ANY, "Druzyna gosc", wxPoint(595, wysokosc)); //+350
		kolumnaDwukropek[i] = new wxStaticText(this, wxID_ANY, ":", wxPoint(494, wysokosc)); //+350
		kolumnaBramkiGospodarzy[i] = new wxStaticText(this, wxID_ANY, "0", wxPoint(473, wysokosc)); //jeszcze +100
		kolumnaBramkiGosci[i] = new wxStaticText(this, wxID_ANY, "0", wxPoint(511, wysokosc));
		oKolumnaGospodarze[i]->SetFont(czcionkaOstatnieMecze);
		oKolumnaGoscie[i]->SetFont(czcionkaOstatnieMecze);
		kolumnaDwukropek[i]->SetFont(czcionkaOstatnieMecze);
		kolumnaBramkiGospodarzy[i]->SetFont(czcionkaOstatnieMecze);
		kolumnaBramkiGosci[i]->SetFont(czcionkaOstatnieMecze);
		wysokosc += 40;
	}
}

void cMain::pokazElementyOstatnichMeczy()
{
	for (int i = 0; i < 10; i++)
	{
		oKolumnaGospodarze[i]->Show();
		oKolumnaGoscie[i]->Show();
		kolumnaDwukropek[i]->Show();
		kolumnaBramkiGospodarzy[i]->Show();
		kolumnaBramkiGosci[i]->Show();
	}
}

void cMain::ukryjElementyOstatnichMeczy()
{
	
	for (int i = 0; i < 10; i++)
	{
		oKolumnaGospodarze[i]->Hide();
		oKolumnaGoscie[i]->Hide();
		kolumnaDwukropek[i]->Hide();
		kolumnaBramkiGospodarzy[i]->Hide();
		kolumnaBramkiGosci[i]->Hide();
	}
}

void cMain::inicjalizujNajlepszychZawodnikow()
{
	wxFont czcionkaNajlepsiZawodnicy(15, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	wxFont czcionkaNajlepsiZawodnicyPodpisy(18, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	int wysokosc = 70; // +40
	najlepsiStrzelcy[10] = new wxStaticText(this, wxID_ANY, "Najlepsi strzelcy", wxPoint(220, wysokosc));
	najlepsiAsystenci[10] = new wxStaticText(this, wxID_ANY, "Najlepsi asystenci", wxPoint(590, wysokosc));
	najlepsiStrzelcy[10]->SetFont(czcionkaNajlepsiZawodnicyPodpisy);
	najlepsiAsystenci[10]->SetFont(czcionkaNajlepsiZawodnicyPodpisy);
	wysokosc = 100;
	for (int i = 0; i < 10; i++)
	{
		wysokosc += 40;
		najlepsiStrzelcy[i] = new wxStaticText(this, wxID_ANY, "Zawodnik Zawodnik", wxPoint(200, wysokosc));
		najlepsiAsystenci[i] = new wxStaticText(this, wxID_ANY, "Zawodnik Zawodnik", wxPoint(580, wysokosc));
		ileBramek[i] = new wxStaticText(this, wxID_ANY, "10", wxPoint(400, wysokosc));
		ileAsyst[i] = new wxStaticText(this, wxID_ANY, "10", wxPoint(780, wysokosc));

		najlepsiStrzelcy[i]->SetFont(czcionkaNajlepsiZawodnicy);
		najlepsiAsystenci[i]->SetFont(czcionkaNajlepsiZawodnicy);
		ileAsyst[i]->SetFont(czcionkaNajlepsiZawodnicy);
		ileBramek[i]->SetFont(czcionkaNajlepsiZawodnicy);
		
	}
}

void cMain::pokazElementyNajlepszychZawodnikow()
{
	for (int i = 0; i < 10; i++)
	{
		najlepsiAsystenci[i]->Show();
		najlepsiStrzelcy[i]->Show();
		ileBramek[i]->Show();
		ileAsyst[i]->Show();
	}
	najlepsiStrzelcy[10]->Show();
	najlepsiAsystenci[10]->Show();
}

void cMain::ukryjElementyNajlepszychZawodnikow()
{
	for (int i = 0; i < 10; i++)
	{
		najlepsiAsystenci[i]->Hide();
		najlepsiStrzelcy[i]->Hide();
		ileBramek[i]->Hide();
		ileAsyst[i]->Hide();
	}
	najlepsiStrzelcy[10]->Hide();
	najlepsiAsystenci[10]->Hide();
}

void cMain::wpiszDoTabeli(array<string, 20>& druzyny, array<int, 20>& bramki, array<int, 20>& punkty)
{
	string wpisywanaBramka = "";
	for (int i = 0; i < druzyny.size(); i++)
	{
		kolumnaDruzyny[i + 1]->SetLabel(druzyny[i]);
		string wpisywanaBramka = to_string(abs(bramki[i]));
		if (bramki[i] > 10)
			wpisywanaBramka = "+" + wpisywanaBramka;
		else if(bramki[i] == 0)
			wpisywanaBramka = "  " + wpisywanaBramka;
		else if(bramki[i] > -10 && bramki[i] < 0)
			wpisywanaBramka = "- " + wpisywanaBramka;
		else if (bramki[i] < 10 && bramki[i] > 0)
			wpisywanaBramka = "+ " + wpisywanaBramka;
		else
			wpisywanaBramka = "-" + wpisywanaBramka;
		kolumnaBramki[i + 1]->SetLabel(wpisywanaBramka);
		kolumnaPunkty[i + 1]->SetLabel(to_string(punkty[i]));
		
	}
}

void cMain::wpiszDoTerminarza(array<string, 10>& gosp, array<string, 10>& gosc, array<string, 10>& data)
{
	for (int i = 0; i < 10; i++)
	{
		kolumnaGospodarze[i]->SetLabel(gosp[i]);
		kolumnaGoscie[i]->SetLabel(gosc[i]);
		data[i][18] = ' ';
		data[i][19] = ' ';
		data[i][20] = ' ';
		data[i][21] = 'U';
		data[i][22] = 'T';
		data[i][23] = 'C';
		data[i][24] = ' ';
		data[i][25] = ' ';
		data[i][26] = ' ';
		data[i][27] = ' ';
		kolumnaDataIGodzina[i]->SetLabel(data[i]);
	}
}

void cMain::wpiszDoOstatnichMeczy(array<string, 10>& gosp, array<string, 10>& gosc, array<int, 10>& bramkiGosp, array<int, 10>& bramkiGosc)
{
	for (int i = 0; i < 10; i++)
	{
		oKolumnaGospodarze[i]->SetLabel(gosp[i]);
		oKolumnaGoscie[i]->SetLabel(gosc[i]);
		kolumnaBramkiGospodarzy[i]->SetLabel(to_string(bramkiGosp[i]));
		kolumnaBramkiGosci[i]->SetLabel(to_string(bramkiGosc[i]));
	}
}

void cMain::wpiszDoNajlepszychZawodnikow(array<string, 10>& strzelcy, array<string, 10>& asystenci, array<int, 10>& gole, array<int, 10>& asysty)
{
	for (int i = 0; i < 10; i++)
	{
		najlepsiStrzelcy[i]->SetLabel(strzelcy[i]);
		najlepsiAsystenci[i]->SetLabel(asystenci[i]);
		ileBramek[i]->SetLabel(to_string(gole[i]));
		ileAsyst[i]->SetLabel(to_string(asysty[i]));
	}
}