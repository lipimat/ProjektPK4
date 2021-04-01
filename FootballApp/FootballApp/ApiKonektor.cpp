#include <iostream>
#include <cpr/cpr.h>
#include <string>

#include "ApiKonektor.h"
#include "LigaID.h"
#include "nlohmann/json.hpp"

using nlohmann::json;
using namespace std;

cpr::Response ApiKonektor::wyslijGET(std::string requestURL) {
	return cpr::Get(cpr::Url(requestURL), HEADERS);
}

void ApiKonektor::getTabela(NazwaLigi liga) {
	cpr::Response odpowiedz = wyslijGET(URL + "standings?season=2020&league=" + to_string(liga));
	if (odpowiedz.status_code != 200) {
		throw("Blad, sprobuj ponownie pozniej");
	}
	json jOdpowiedz;
	stringstream(odpowiedz.text) >> jOdpowiedz;
	cout << jOdpowiedz << endl;
}
