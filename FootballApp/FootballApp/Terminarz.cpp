#include "Terminarz.h"

using namespace std;
Terminarz::Terminarz()
{
	gospodarze = make_shared<array<string, 10>>();
	goscie = make_shared<array<string, 10>>();
	datyMeczow = make_shared<array<string, 10>>();
	godzinyMeczow = make_shared<array<string, 10>>();
}

Terminarz::~Terminarz()
{

}

array<string, 10>& Terminarz::getGospodarze()
{
	return *gospodarze;
}
array<string, 10>& Terminarz::getGoscie()
{
	return *goscie;
}
array<string, 10>& Terminarz::getDatyMeczow()
{
	return *datyMeczow;
}
array<string, 10>& Terminarz::getGodzinyMeczow()
{
	return *godzinyMeczow;
}


