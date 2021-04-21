#pragma once
#include <array>
#include <memory>
#include <string>
using namespace std;

/* Wszystkie klasy maj¹ tablice z STL Array(¿eby by³o fajne indeksowanie) , u¿y³em smart pointerów ¿eby
   unikn¹æ wycieków pamiêci, pamiêtaj ¿e te tablice to tak naprawdê pointery i ¿eby u¿ywaæ * odwo³uj¹c siê do nich           */

class NajlepsiZawodnicy
{
private:
	shared_ptr<array<string, 10>> najlepsiStrzelcy; //imiona i nazwiska strzelców
	shared_ptr<array<string, 10>> najlepsiAsystenci; //imiona i nazwiska asystentów
	shared_ptr<array<int, 10>> ileStrzelili; // tu trzeba wpisaæ ile bramek poszczególny strzelec strzeli³
	shared_ptr<array<int, 10>> ileAsystowali; // tu trzeba wpisaæ ile bramek poszczególny asystent asystowa³
public:
	NajlepsiZawodnicy();
	~NajlepsiZawodnicy();
	//gettery
	array<string, 10>& getNajlepsiStrzelcy();	
	array<string, 10>& getNajlepsiAsystenci();
	array<int, 10>& getIleStrzelili();
	array<int, 10>& getIleAsystowali();
	
};

