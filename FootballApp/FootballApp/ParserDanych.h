#ifndef PARDA_H
#define PARDA_H

#include <vector>
#include "nlohmann/json.hpp"

using nlohmann::json;

class ParserDanych
{
public:
	static std::vector<json> parsujTabele(json odpowiedz);
	static std::vector<json> parsujMecze(json odpowiedz);
	static std::vector<json> parsujDaneOStrzelcach(json odpowiedz);
};

#endif

