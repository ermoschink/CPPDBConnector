#pragma once

#include <map>

class TRow
{
public:
	TRow(std::string, std::string);
	TRow();
	~TRow();

	std::string getValueByColumn(const std::string&) const;
	void setValueByColumn(const std::string&, const std::string&);
	std::map<std::string, std::string> getValues() const { return this->values; }

	std::string idColumn;

	std::string tableName;
private:
	std::map<std::string, std::string> values;
};

