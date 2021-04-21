#pragma once
#include <array>
#include <memory>
#include <string>
/* Wszystkie klasy maj¹ tablice z STL Array(¿eby by³o fajne indeksowanie) , u¿y³em smart pointerów ¿eby
   unikn¹æ wycieków pamiêci, pamiêtaj ¿e te tablice to tak naprawdê pointery i ¿eby u¿ywaæ * odwo³uj¹c siê do nich            */
using namespace std;
class Terminarz
{
private:
	shared_ptr<array<string, 10>> gospodarze; // dru¿yny graj¹ce u siebie(po kolei)
	shared_ptr<array<string, 10>> goscie; //dru¿yny graj¹ce na wyjeŸdzie(po kolei)
	shared_ptr<array<string, 10>> dataIGodzinaMeczow; // daty meczów (jako string) (dzieñ i miesi¹c albo dzieñ, miesi¹c, rok) 
public:
	Terminarz();
	~Terminarz();
	//gettery
	array<string, 10>& getGospodarze();
	array<string, 10>& getGoscie();
	array<string, 10>& getDatyIGodzinyMeczow();
};

