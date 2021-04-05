#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cpr/cpr.h>
#include <string>
#include <ctime>

#include "ApiKonektor.h"
#include "ParserDanych.h"
#include "LigaID.h"
#include "nlohmann/json.hpp"

using nlohmann::json;
using namespace std;

cpr::Response ApiKonektor::wyslijGET(std::string requestURL) {
	return cpr::Get(cpr::Url(requestURL), HEADERS);
}

int ApiKonektor::getRok() {
	time_t t = time(NULL);
	tm* timePtr = localtime(&t);

	//Rozgrywki zaczynaja sie w sierpniu, jesli jeszcze nie ma sierpnia to wez rozgrywki zeszloroczne
	if ((timePtr->tm_mon) + 1 >= 8) {
		return 1900 + timePtr->tm_year;
	}
	else {
		return 1900 + timePtr->tm_year - 1;
	}
}

int ApiKonektor::sprawdzStatusOdpowiedzi(cpr::Response odpowiedz) {
	if (odpowiedz.status_code == 200) return 1;
	else if (odpowiedz.status_code == 204) return 2;
	else return -1;
}

void ApiKonektor::getTabela(NazwaLigi liga) {
	cpr::Response odpowiedz = wyslijGET(URL 
		+ "standings?season=" + to_string(getRok()) 
		+ "&league="+ to_string(liga));
	
	if (sprawdzStatusOdpowiedzi(odpowiedz) == 2) throw("Wystapil bug po stronie serwera, przepraszamy sprobuj pozniej");
	else if (sprawdzStatusOdpowiedzi(odpowiedz) == -1) throw("Wystapil problem, sprobuj ponownie pozniej");

	//parsowanie
	json jOdpowiedz;
	stringstream(odpowiedz.text) >> jOdpowiedz;
	vector<json> jTabela = ParserDanych::parsujTabele(jOdpowiedz);
}

void ApiKonektor::getPrzyszleMecze(NazwaLigi liga) {
	cpr::Response odpowiedz = wyslijGET(URL
		+ "fixtures?league=" + to_string(liga)
		+ "&next=10");

	if (sprawdzStatusOdpowiedzi(odpowiedz) == 2) throw("Wystapil bug po stronie serwera, przepraszamy sprobuj pozniej");
	else if (sprawdzStatusOdpowiedzi(odpowiedz) == -1) throw("Wystapil problem, sprobuj ponownie pozniej");

	//parsowanie
	json jOdpowiedz;
	stringstream(odpowiedz.text) >> jOdpowiedz;
	vector<json> jPrzyszleMeczeInfo = ParserDanych::parsujMecze(jOdpowiedz);
}

void ApiKonektor::getOstatnieMecze(NazwaLigi liga) {
	cpr::Response odpowiedz = wyslijGET(URL
		+ "fixtures?league=" + to_string(liga)
		+ "&last=10");

	if (sprawdzStatusOdpowiedzi(odpowiedz) == 2) throw("Wystapil bug po stronie serwera, przepraszamy sprobuj pozniej");
	else if (sprawdzStatusOdpowiedzi(odpowiedz) == -1) throw("Wystapil problem, sprobuj ponownie pozniej");

	//parsowanie
	json jOdpowiedz;
	stringstream(odpowiedz.text) >> jOdpowiedz;
	vector<json> jOstatnieMeczeInfo = ParserDanych::parsujMecze(jOdpowiedz);
}
