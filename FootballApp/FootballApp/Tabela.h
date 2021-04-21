#pragma once

#include <array>
#include <memory>
#include <string>
/* Wszystkie klasy maj¹ tablice z STL Array(¿eby by³o fajne indeksowanie) , u¿y³em smart pointerów ¿eby
   unikn¹æ wycieków pamiêci, pamiêtaj ¿e te tablice to tak naprawdê pointery i ¿eby u¿ywaæ * odwo³uj¹c siê do nich            */
using namespace std;
class Tabela
{
private:
	shared_ptr<array<string, 20>> druzyny; // nazwy dru¿yn w tabeli(po kolei)
	shared_ptr<array<int, 20>> punkty; // iloœæ punktów odpowiadaj¹ca danej dru¿ynie
	shared_ptr<array<int, 20>> bramki; // ró¿nica bramek odpowiadaj¹ca danej dru¿ynie
public:
	Tabela();
	~Tabela();
	//gettery
	array<string, 20>& getDruzyny();
	array<int, 20>& getPunkty();
	array<int, 20>& getBramki();
};

