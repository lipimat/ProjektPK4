#include "NajlepsiZawodnicy.h"

NajlepsiZawodnicy::NajlepsiZawodnicy()
{
	najlepsiStrzelcy = make_shared<array<string, 10>>();
	najlepsiAsystenci = make_shared<array<string, 10>>();
	ileStrzelili = make_shared<array<int, 10>>();
	ileAsystowali = make_shared<array<int, 10>>();
}
NajlepsiZawodnicy::~NajlepsiZawodnicy()
{

}

array<string, 10>& NajlepsiZawodnicy::getNajlepsiStrzelcy()
{
	return *najlepsiStrzelcy;
}
array<string, 10>& NajlepsiZawodnicy::getNajlepsiAsystenci()
{
	return *najlepsiAsystenci;
}
array<int, 10>& NajlepsiZawodnicy::getIleStrzelili()
{
	return *ileStrzelili;
}
array<int, 10>& NajlepsiZawodnicy::getIleAsystowali()
{
	return *ileAsystowali;
}