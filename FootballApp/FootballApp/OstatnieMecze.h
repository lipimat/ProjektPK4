#pragma once
#include <array>
#include <memory>
#include <string>
using namespace std;
/* Wszystkie klasy maj¹ tablice z STL Array(¿eby by³o fajne indeksowanie) , u¿y³em smart pointerów ¿eby
   unikn¹æ wycieków pamiêci, pamiêtaj ¿e te tablice to tak naprawdê pointery i ¿eby u¿ywaæ * odwo³uj¹c siê do nich            */
class OstatnieMecze
{
private:
	shared_ptr<array<string, 10>> oGospodarze; // dru¿yny graj¹ce u siebie(po kolei)
	shared_ptr<array<string, 10>> oGoscie; // dru¿yny graj¹ce na wyjeŸdzie(po kolei)
	shared_ptr<array<int, 10>> bramkiGospodarzy; // bramki dru¿yn gospodarzy
	shared_ptr<array<int, 10>> bramkiGosci; // bramki dru¿yn goœci
public:
	OstatnieMecze();
	~OstatnieMecze();
	//gettery
	array<string, 10>& getOGospodarze();
	array<string, 10>& getOGoscie();
	array<int, 10>& getBramkiGospodarzy();
	array<int, 10>& getBramkiGosci();
};

