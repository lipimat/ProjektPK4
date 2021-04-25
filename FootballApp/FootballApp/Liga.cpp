#include "Liga.h"
#include "ApiKonektor.h"
#include <iostream>

Liga::Liga(NazwaLigi typ) {
	ApiKonektor konektor;
	try {
		tabela = konektor.getTabela(typ);
		zawodnicy = konektor.getNajlepsiZawodnicy(typ);
		ostatnieMecze = konektor.getOstatnieMecze(typ);
		przyszleMecze = konektor.getPrzyszleMecze(typ);
	}
	catch (const char* errorMSG) {
		std::cout << errorMSG << std::endl;
	}
}

Liga::~Liga() {
	delete tabela;
	delete zawodnicy;
	delete ostatnieMecze;
	delete przyszleMecze;
}

Tabela* Liga::getTabela() { return tabela; }

NajlepsiZawodnicy* Liga::getZawodnicy() { return zawodnicy; }

OstatnieMecze* Liga::getOstatnieMecze() { return ostatnieMecze; }

Terminarz* Liga::getPrzyszleMecze() { return przyszleMecze; }