#include <vector>

#include "ParserDanych.h"
#include "nlohmann/json.hpp"

using namespace std;
using nlohmann::json;

vector<json> ParserDanych::parsujTabele(json odpowiedz) {
	vector<json> dane;
	for (auto teamInfo: odpowiedz["response"][0]["league"]["standings"][0]) {
		dane.push_back(teamInfo);
	}
	return dane;
}