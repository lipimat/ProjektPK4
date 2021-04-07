#pragma once
#include <array>
#include <memory>
/* Wszystkie klasy maj� tablice z STL Array(�eby by�o fajne indeksowanie) , u�y�em smart pointer�w �eby
   unikn�� wyciek�w pami�ci, pami�taj �e te tablice to tak naprawd� pointery i �eby u�ywa� * odwo�uj�c si� do nich            */
using namespace std;
class Terminarz
{
private:
	shared_ptr<array<string, 10>> gospodarze; // dru�yny graj�ce u siebie(po kolei)
	shared_ptr<array<string, 10>> goscie; //dru�yny graj�ce na wyje�dzie(po kolei)
	shared_ptr<array<string, 10>> datyMeczow; // daty mecz�w (jako string) (dzie� i miesi�c albo dzie�, miesi�c, rok) 
	shared_ptr<array<string, 10>> godzinyMeczow; // godziny mecz�w (jako string) 
public:
	Terminarz();
	~Terminarz();
	//gettery
	array<string, 10>& getGospodarze();
	array<string, 10>& getGoscie();
	array<string, 10>& getDatyMeczow();
	array<string, 10>& getGodzinyMeczow();
};

