// ConsoleApplication1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include "SqlLiteDatabase.h"
#include "TInformation.h"

#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>

template<class T>
std::string to_str(const T& val) {
	std::stringstream ss;
	ss << val;
	return ss.str();
}

TRow createRow(TInformation* inf) {
	TRow  r = TInformation::getEmpty();
	r.setValueByColumn("id",    to_str(inf->id_order));
	r.setValueByColumn("caption", "'" + (inf->caption) + "'");;
	r.setValueByColumn("valueF", to_str(inf->valueF));;
	r.setValueByColumn("valueB", to_str(inf->valueB));
	r.setValueByColumn("valueI", to_str(inf->valueI));
	return r;
}

int main()
{
	IDatabase *db = new CSqlLiteDatabase(std::string("D:\\db.db"));
	
	for (unsigned int i = 55; i < 40; ++i) {
		TInformation *inf0 = new TInformation();
		inf0->caption = "inf0 - " + to_str(i);
		inf0->valueB = false;
		inf0->valueF = 0.42f;
		inf0->valueI = 255;
		TRow r = createRow(inf0);
		TRow res = db->saveData(r);
		inf0->id_order = std::stoi( res.getValueByColumn(r.idColumn));
	}


	std::vector<TRow> vRows = db->getData(TInformation::getEmpty());
	std::vector<TInformation*> newV;
	newV.reserve(vRows.size());   
	std::transform(vRows.begin(), vRows.end(),
		std::back_inserter(newV), [](auto r) {
		return new TInformation(r.getValues());
	});

	for (unsigned int i = 0; i < newV.size(); ++i) {
		newV.at(i)->caption += (std::to_string(i));
		TRow r = createRow(newV.at(i));
		db->updateData(r);		
	}
    return 0;
}

