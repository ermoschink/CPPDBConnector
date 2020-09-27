#include "stdafx.h"
#include "SqlLiteDatabase.h"

#include <sstream>

template<class T>
std::string to_str(const T& val) {
	std::stringstream ss;
	ss << val;
	return ss.str();
}


CSqlLiteDatabase::CSqlLiteDatabase(std::string p)
{
	int rc = sqlite3_open(p.c_str(), &this->db);
	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		throw std::exception("Can't open database");
	}
}


CSqlLiteDatabase::~CSqlLiteDatabase()
{
	sqlite3_close(this->db);
}

std::vector<TRow> CSqlLiteDatabase::getData(const TRow& r)
{
	std::string statement = "Select * from " + r.tableName;
	return this->executeStatement(statement);
}

TRow CSqlLiteDatabase::saveData(const TRow& r)
{
	/// - - - - 
	std::string columnsName, data;

	std::map<std::string, std::string> values = r.getValues();
	for (auto i = values.cbegin(); i != values.cend(); ++i) {
		if (i->first == r.idColumn) continue;
		columnsName += i->first;
		data += i->second;
		if (std::next(i) != values.cend()) {
			columnsName += ", ";
			data += ", ";
		}
	}
	std::string total = "insert into " + r.tableName + " (" + columnsName + ")" + "VALUES (" + data + ")";
	/// - - - - 
	return this->saveData(total, r.idColumn);
}

TRow CSqlLiteDatabase::saveData(std::string query, std::string idColumn) {
	sqlite3_stmt *stmt = NULL;
	int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		fprintf(stderr, ": %s\n", sqlite3_errmsg(db));
		return TRow();
	}

	if (sqlite3_step(stmt) != SQLITE_DONE) {
		fprintf(stderr, ": %s\n", sqlite3_errmsg(db));
		return TRow();
	}

	std::vector<TRow> res = this->executeStatement("SELECT last_insert_rowid() as " + idColumn);
	if (res.empty()) return TRow();
	return res.front();
}



bool CSqlLiteDatabase::updateData(const TRow& r)
{
	std::string data;
	std::map<std::string, std::string> values = r.getValues();
	for (auto i = values.cbegin(); i != values.cend(); ++i) {
		if (i->first == r.idColumn) continue;
		data += i->first + " = " + i->second + "";
		if (std::next(i) != values.cend())
			data += ",";
	}
	std::string statement = "update " + r.tableName + " Set " + data + " where " + r.idColumn + "=" + r.getValueByColumn(r.idColumn);
	return executeStatement(statement).empty();
}
std::vector<TRow> CSqlLiteDatabase::executeStatement(std::string query) {
	sqlite3_stmt *stmt = NULL;
	int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		fprintf(stderr, ": %s\n", sqlite3_errmsg(db));
		return std::vector<TRow>();
	}
	std::vector<TRow> result;
	int rowCount = 0;
	rc = sqlite3_step(stmt);
	while (rc != SQLITE_DONE && rc != SQLITE_OK)
	{
		rowCount++;
		TRow currentRow;
		int colCount = sqlite3_column_count(stmt);
		for (int colIndex = 0; colIndex < colCount; colIndex++)
		{
			int type = sqlite3_column_type(stmt, colIndex);
			const char * columnName = sqlite3_column_name(stmt, colIndex);
			std::string  colName = std::string(columnName);
			std::string  cellData = std::string();
			if (type == SQLITE_INTEGER)
			{
				int valInt = sqlite3_column_int(stmt, colIndex);
			//	printf("columnName = %s, Integer val = %d", columnName, valInt);
				cellData = to_str(valInt);

			}
			else if (type == SQLITE_FLOAT)
			{
				double valDouble = sqlite3_column_double(stmt, colIndex);
			//	printf("columnName = %s,Double val = %f", columnName, valDouble);
				cellData = to_str(valDouble);
			}
			else if (type == SQLITE_TEXT)
			{
				const unsigned char * valChar = sqlite3_column_text(stmt, colIndex);
			//	printf("columnName = %s,Text val = %s", columnName, valChar);
				cellData = std::string((const char*)valChar);
				
			}
			else if (type == SQLITE_BLOB)
			{
			//	printf("columnName = %s,BLOB", columnName);
			}
			else if (type == SQLITE_NULL)
			{
			//	printf("columnName = %s,NULL", columnName);
			}
			currentRow.setValueByColumn(colName, cellData);
		}
		result.push_back(currentRow);
		rc = sqlite3_step(stmt);
	}

	rc = sqlite3_finalize(stmt);

	return result;

}
