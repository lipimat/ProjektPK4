#ifndef API_H
#define API_H

#include <cpr/cpr.h>
#include <string>

#include "LigaID.h"

class ApiKonektor
{
private:
	const std::string URL = "https://api-football-v1.p.rapidapi.com/v3/";
	const cpr::Header HEADERS = {{ "x-rapidapi-host" , "api-football-v1.p.rapidapi.com"},
								 {"x-rapidapi-key", "RAPIDAPI_KEY"}};
	
	cpr::Response wyslijGET(std::string requestURL);
	int getRok();
	int sprawdzStatusOdpowiedzi(cpr::Response odpowiedz);
public:
	void getTabela(NazwaLigi liga);
	void getPrzyszleMecze(NazwaLigi liga);
	void getOstatnieMecze(NazwaLigi liga);
	void getNajlepsiStrzelcy(NazwaLigi liga);
};

#endif
