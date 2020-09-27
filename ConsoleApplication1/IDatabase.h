#pragma once

#include <vector>
#include "TRow.h"

class IDatabase
{
public:
	IDatabase();
	virtual ~IDatabase();

	virtual std::vector<TRow> getData(const TRow&) = 0;

	virtual TRow saveData(const TRow&) = 0;
	virtual bool updateData(const TRow&) = 0;
		
};

