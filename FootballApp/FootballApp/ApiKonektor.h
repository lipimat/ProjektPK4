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
								 {"x-rapidapi-key", "cf3dcfa9d8msh4a6827aa7fa6556p1c7c63jsn39def2ee1fcd"}};
	
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
