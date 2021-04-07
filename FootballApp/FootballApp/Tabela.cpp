#include "Tabela.h"

using namespace std;
Tabela::Tabela()
{
	druzyny = make_shared<array<string, 20>>();
	punkty = make_shared<array<int, 20>>();
	bramki = make_shared<array<int, 20>>();
}

Tabela::~Tabela()
{

}

array<string, 20>& Tabela::getDruzyny()
{
	return *druzyny;
}
array<int, 20>& Tabela::getPunkty()
{
	return *punkty;
}
array<int, 20>& Tabela::getBramki()
{
	return *bramki;
}
