#ifndef LIGA_H
#define LIGA_H

#include "LigaID.h"
#include "Tabela.h"
#include "NajlepsiZawodnicy.h"
#include "OstatnieMecze.h"
#include "Terminarz.h"

class Liga
{
private:
	Tabela* tabela;
	NajlepsiZawodnicy* zawodnicy;
	OstatnieMecze* ostatnieMecze;
	Terminarz* przyszleMecze;

public:
	Liga(NazwaLigi typ);
	~Liga();
	Tabela* getTabela();
	NajlepsiZawodnicy* getZawodnicy();
	OstatnieMecze* getOstatnieMecze();
	Terminarz* getPrzyszleMecze();
};

#endif

