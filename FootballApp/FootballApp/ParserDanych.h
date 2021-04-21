#ifndef PARDA_H
#define PARDA_H

#include <vector>
#include "nlohmann/json.hpp"
#include "Tabela.h"
#include "Terminarz.h"
#include "OstatnieMecze.h"
#include "NajlepsiZawodnicy.h"

using nlohmann::json;

class ParserDanych
{
public:
	static Tabela* parsujTabele(json odpowiedz);
	static Terminarz* parsujPrzyszleMecze(json odpowiedz);
	static OstatnieMecze* parsujOstatnieMecze(json odpowiedz);
	static NajlepsiZawodnicy* parsujDaneOStrzelcach(json odpowiedz);
	static void parsujDaneOAsystentach(json odpowiedz,NajlepsiZawodnicy*& topZawodnicy);
};

#endif

