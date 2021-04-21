#ifndef API_H
#define API_H

#include <cpr/cpr.h>
#include <string>

#include "LigaID.h"
#include "Tabela.h"
#include "Terminarz.h"
#include "OstatnieMecze.h"
#include "NajlepsiZawodnicy.h"

class ApiKonektor
{
private:
	const std::string URL = "https://api-football-v1.p.rapidapi.com/v3/";
	const cpr::Header HEADERS = {{ "x-rapidapi-host" , "api-football-v1.p.rapidapi.com"},
								 {"x-rapidapi-key", "RAPIDAPI-KEY"}};
	
	cpr::Response wyslijGET(std::string requestURL);
	int getRok();
	int sprawdzStatusOdpowiedzi(cpr::Response odpowiedz);

public:
	Tabela* getTabela(NazwaLigi liga);
	Terminarz* getPrzyszleMecze(NazwaLigi liga);
	OstatnieMecze* getOstatnieMecze(NazwaLigi liga);
	NajlepsiZawodnicy* getNajlepsiZawodnicy(NazwaLigi liga);
};

#endif
