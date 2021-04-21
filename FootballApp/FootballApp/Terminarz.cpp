#include "Terminarz.h"

using namespace std;
Terminarz::Terminarz()
{
	gospodarze = make_shared<array<string, 10>>();
	goscie = make_shared<array<string, 10>>();
	dataIGodzinaMeczow = make_shared<array<string, 10>>();
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
array<string, 10>& Terminarz::getDatyIGodzinyMeczow()
{
	return *dataIGodzinaMeczow;
}


