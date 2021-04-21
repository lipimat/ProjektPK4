#include <vector>
#include <iostream>
#include "ParserDanych.h"
#include "nlohmann/json.hpp"
#include "Tabela.h"
#include "Terminarz.h"
#include "OstatnieMecze.h"
#include "NajlepsiZawodnicy.h"

using namespace std;
using nlohmann::json;

Tabela* ParserDanych::parsujTabele(json odpowiedz) {
	Tabela* tabela = new Tabela();
	array<string, 20> nazwyDruzyn;
	array<int, 20> punktyDruzyn;
	array<int, 20> bramkiDruzyn;
	int licznik = 0;
	for (auto teamInfo: odpowiedz["response"][0]["league"]["standings"][0]) {
		nazwyDruzyn[licznik] = teamInfo["team"]["name"];
		punktyDruzyn[licznik] = teamInfo["points"];
		bramkiDruzyn[licznik] = teamInfo["goalsDiff"];
		licznik++;
	}
	tabela->getDruzyny() = nazwyDruzyn;
	tabela->getBramki() = bramkiDruzyn;
	tabela->getPunkty() = punktyDruzyn;
	return tabela;
}

Terminarz* ParserDanych::parsujPrzyszleMecze(json odpowiedz) {
	Terminarz* terminarz = new Terminarz();
	array<string, 10> nazwyGospodarzy;
	array<string, 10> nazwyGosci;
	array<string, 10> datyIGodzinyMeczow;
	int licznik = 0;
	for (auto opisMeczu : odpowiedz["response"]) {
		nazwyGospodarzy[licznik] = opisMeczu["teams"]["home"]["name"];
		nazwyGosci[licznik] = opisMeczu["teams"]["away"]["name"];
		string dataIGodzinaMeczu = opisMeczu["fixture"]["date"];
		dataIGodzinaMeczu.replace(10, 1, "   ");
		datyIGodzinyMeczow[licznik] = dataIGodzinaMeczu;
		licznik++;
	}
	terminarz->getGospodarze() = nazwyGospodarzy;
	terminarz->getGoscie() = nazwyGosci;
	terminarz->getDatyIGodzinyMeczow() = datyIGodzinyMeczow;

	return terminarz;
}

OstatnieMecze* ParserDanych::parsujOstatnieMecze(json odpowiedz) {
	OstatnieMecze* ostatnieMecze = new OstatnieMecze();
	array<string, 10> nazwyGospodarzy;
	array<string, 10> nazwyGosci;
	array<int, 10> bramkiGospodarzy;
	array<int, 10> bramkiGosci;
	int licznik = 0;
	for (auto opisMeczu : odpowiedz["response"]) {
		nazwyGospodarzy[licznik] = opisMeczu["teams"]["home"]["name"];
		nazwyGosci[licznik] = opisMeczu["teams"]["away"]["name"];
		
		//PRZELOZONY MECZ
		if (opisMeczu["fixture"]["status"]["long"] == "Match Postponed") {
			bramkiGospodarzy[licznik] = -1;
			bramkiGosci[licznik] = -1;
		}
		else {
			bramkiGospodarzy[licznik] = opisMeczu["goals"]["home"];
			bramkiGosci[licznik] = opisMeczu["goals"]["away"];
		}
		licznik++;
	}
	ostatnieMecze->getOGospodarze() = nazwyGospodarzy;
	ostatnieMecze->getOGoscie() = nazwyGosci;
	ostatnieMecze->getBramkiGospodarzy() = bramkiGospodarzy;
	ostatnieMecze->getBramkiGosci() = bramkiGosci;
	
	return ostatnieMecze;
}

NajlepsiZawodnicy* ParserDanych::parsujDaneOStrzelcach(json odpowiedz) {
	NajlepsiZawodnicy* strzelcy = new NajlepsiZawodnicy();
	array<string, 10> nazwiskaStrzelcow;
	array<int, 10> ileBramekKazdy;
	int licznik = 0;
	for (auto opisStrzelca : odpowiedz["response"]) {
		if (licznik == 10) break;
		else
		{
			nazwiskaStrzelcow[licznik] = opisStrzelca["player"]["name"];
			ileBramekKazdy[licznik] = opisStrzelca["statistics"][0]["goals"]["total"];
			licznik++;
		}
	}
	strzelcy->getNajlepsiStrzelcy() = nazwiskaStrzelcow;
	strzelcy->getIleStrzelili() = ileBramekKazdy;

	return strzelcy;
}

void ParserDanych::parsujDaneOAsystentach(json odpowiedz,NajlepsiZawodnicy*& topZawodnicy) {
	int licznik = 0;
	array<string, 10> nazwiskaAsystentow;
	array<int, 10> ileAsystKazdy;
	for (auto opisAsystenta : odpowiedz["response"]) {
		if (licznik == 10) break;
		else
		{
			nazwiskaAsystentow[licznik] = opisAsystenta["player"]["name"];
			ileAsystKazdy[licznik] = opisAsystenta["statistics"][0]["goals"]["assists"];
			licznik++;
		}
	}
	topZawodnicy->getNajlepsiAsystenci() = nazwiskaAsystentow;
	topZawodnicy->getIleAsystowali() = ileAsystKazdy;
}