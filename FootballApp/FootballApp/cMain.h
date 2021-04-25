#pragma once
#include "wx/wx.h"
#include <memory>
#include <array>
#include "Liga.h"

using namespace std;
class cMain : public wxFrame
{
public:
	cMain();
	~cMain();
	
private:
	//LIGI
	Liga* ligaAngielska = nullptr;
	Liga* ligaHiszpanska = nullptr;
	Liga* ligaWloska = nullptr;
	bool czyLigaAngielska = false;
	bool czyLigaHiszpanska = false;
	bool czyLigaWloska = false;
	//�EBY WIEDZIE� KT�RA LIGA AKTUALNIE JEST WYBRANA
	int wybranaLiga;
	// DO OBS�UGI OBRAZ�W
	wxPNGHandler* handler = nullptr;
	// TU S� OBIEKTY POTRZEBNE DO EKRANU WYBORU LIGI
	wxStaticBitmap* logoPremierLeague = nullptr;
	wxStaticBitmap* logoLaLiga = nullptr;
	wxStaticBitmap* logoSerieA = nullptr;
	wxButton* przyciskLigaAngielska = nullptr;
	wxButton* przyciskLigaHiszpanska = nullptr;
	wxButton* przyciskLigaWloska = nullptr;
	wxStaticText* polecenieWyboruLigi = nullptr;
	// TU S� OBIEKTY POTRZEBNE DO EKRANU WYBORU STATYSTYK
	wxStaticBitmap* logoTabela = nullptr;
	wxStaticBitmap* logoOstatnieMecze = nullptr;
	wxStaticBitmap* logoTerminarz = nullptr;
	wxStaticBitmap* logoNajlepsiZawodnicy = nullptr;
	wxStaticText* informacjaKtoraLiga;
	wxStaticText* polecenieWyboruStatystyk = nullptr;
	wxButton* przyciskTabelaLigowa = nullptr;
	wxButton* przyciskTerminarz = nullptr;
	wxButton* przyciskOstatnieMecze = nullptr;
	wxButton* przyciskNajlepsiZawodnicy = nullptr;
	wxButton* przyciskWyborInnejLigi = nullptr;
	// UNIWERSALNY PRZYCISK POWROTU DO WYBORU STATYSTYK
	wxButton* przyciskPowrotuDoStatystyk = nullptr;
	// AKCJE WY�WIETLANIA MENU G��WNEGO
	void pokazMenuWyboruStatystyki(wxCommandEvent &evt);
	void pokazMenuWyboruLigi(wxCommandEvent &evt);
	void schowajMenuWyboruStatystyk();
	void pokazTabele(wxCommandEvent& evt);
	void pokazTerminarz(wxCommandEvent& evt);
	void pokazOstatnieMecze(wxCommandEvent& evt);
	void pokazNajlepszychZawodnikow(wxCommandEvent& evt);
	
	// ZARARTO�� EKRANU TABELI
	array<wxStaticText*, 21> kolumnaMiejsca; //Te tablice rezerwuj� miejsce dla obiekt�w GUI
	array<wxStaticText*, 21> kolumnaDruzyny;
	array<wxStaticText*, 21> kolumnaBramki;
	array<wxStaticText*, 21> kolumnaPunkty;
	void inicjalizujTabele();
	void pokazElementyTabeli();
	void ukryjElementyTabeli();
	// TABELA DONE
	// ZAWARTO�� TERMINARZA
	array<wxStaticText*, 10> kolumnaGospodarze; //Te tablice rezerwuj� miejsce dla obiekt�w GUI
	array<wxStaticText*, 10> kolumnaGoscie;
	array<wxStaticText*, 10> kolumnaMyslnik; 
	array<wxStaticText*, 10> kolumnaDataIGodzina;
	void inicjalizujTerminarz();
	void pokazElementyTerminarza();
	void ukryjElementyTerminarza();
	// TERMINARZ DONE
	// ZAWARTO�� OSTATNICH MECZY
	array<wxStaticText*, 10> oKolumnaGospodarze; //Te tablice rezerwuj� miejsce dla obiekt�w GUI
	array<wxStaticText*, 10> oKolumnaGoscie;
	array<wxStaticText*, 10> kolumnaDwukropek;
	array<wxStaticText*, 10> kolumnaBramkiGospodarzy;
	array<wxStaticText*, 10> kolumnaBramkiGosci;
	void inicjalizujOstatnieMecze();
	void pokazElementyOstatnichMeczy();
	void ukryjElementyOstatnichMeczy();
	// OSTATNIE MECZE DONE
	// ZAWARTO�� NAJLEPSI ZAWODNICY
	array<wxStaticText*, 11> najlepsiAsystenci; //Te tablice rezerwuj� miejsce dla obiekt�w GUI
	array<wxStaticText*, 11> najlepsiStrzelcy;
	array<wxStaticText*, 10> ileBramek;
	array<wxStaticText*, 10> ileAsyst;
	
	void inicjalizujNajlepszychZawodnikow();
	void pokazElementyNajlepszychZawodnikow();
	void ukryjElementyNajlepszychZawodnikow();

	// FUNKCJE ODPOWIADAJ�CE ZA SAMO WPISYWANIE ODPOWIEDNICH DANYCH DO OBIEKT�W WXWIDGETS
	void wpiszDoTabeli(array<string, 20>& druzyny, array<int, 20>& bramki, array<int, 20>& punkty); // stosowna tabela b�dzie dostarczana z API poprzez klasy Liga->Tabela
	void wpiszDoTerminarza(array<string, 10>& gosp, array<string, 10>& gosc, array<string, 10>& data);
	void wpiszDoOstatnichMeczy(array<string, 10>& gosp, array<string, 10>& gosc, array<int, 10>& bramkiGosp, array<int, 10>& bramkiGosc);
	void wpiszDoNajlepszychZawodnikow(array<string, 10>& strzelcy, array<string, 10>& asystenci, array<int, 10>& ileGoli, array<int, 10>& ileAsyst);
	wxDECLARE_EVENT_TABLE();
};

