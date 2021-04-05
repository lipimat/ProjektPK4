#include <vector>

#include "ParserDanych.h"
#include "nlohmann/json.hpp"

using namespace std;
using nlohmann::json;

vector<json> ParserDanych::parsujTabele(json odpowiedz) {
	vector<json> jTabela;
	for (auto teamInfo: odpowiedz["response"][0]["league"]["standings"][0]) {
		jTabela.push_back(teamInfo);
	}
	return jTabela;
}

vector<json> ParserDanych::parsujPrzyszleMecze(json odpowiedz) {
	vector<json> jPrzyszleMecze;
	for (auto opisMeczu : odpowiedz["response"]) {
		jPrzyszleMecze.push_back(opisMeczu);
	}
	return jPrzyszleMecze;
}