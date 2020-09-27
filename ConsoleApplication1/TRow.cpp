#include "stdafx.h"
#include "TRow.h"

TRow::TRow(std::string t, std::string id)
{
	this->tableName = t;
	this->idColumn = id;
}


TRow::TRow()
{
}
TRow::~TRow()
{
}


std::string TRow::getValueByColumn(const std::string& col) const{
	if(this->values.find(col) == this->values.end()) 
		throw std::runtime_error(std::string("Columns with this name do not exist"));
	return this->values.at(col);
}

void TRow::setValueByColumn(const std::string& col, const std::string& data){
	this->values[col] = data;
}