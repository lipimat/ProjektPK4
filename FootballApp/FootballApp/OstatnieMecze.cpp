#include "OstatnieMecze.h"

using namespace std;

OstatnieMecze::OstatnieMecze()
{
	oGospodarze = make_shared<array<string, 10>>();
	oGoscie = make_shared<array<string, 10>>();
	bramkiGospodarzy = make_shared<array<int, 10>>();
	bramkiGosci = make_shared<array<int, 10>>();
}
OstatnieMecze::~OstatnieMecze()
{

}
array<string, 10>& OstatnieMecze::getOGospodarze()
{
	return *oGospodarze;
}
array<string, 10>& OstatnieMecze::getOGoscie()
{
	return *oGoscie;
}
array<int, 10>& OstatnieMecze::getBramkiGospodarzy()
{
	return *bramkiGospodarzy;
}
array<int, 10>& OstatnieMecze::getBramkiGosci()
{
	return *bramkiGosci;
}