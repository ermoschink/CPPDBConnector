#pragma once
#include <string>
#include <map>

#include "TRow.h"
class TInformation
{
public:
	TInformation();
	TInformation(std::map<std::string, std::string>);
	~TInformation();

	int id_order;
	std::string caption;
	float valueF;
	bool  valueB;
	int   valueI;

	static TRow getEmpty() {
		return TRow("information", "id" );
	}
};

