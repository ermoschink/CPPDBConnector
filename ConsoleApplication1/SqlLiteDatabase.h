#pragma once
#include "IDatabase.h"
#include "sqlite3.h"

/**
Begin Transaction;
Create  TABLE MAIN.[Temp_565117464](
[id] integer UNIQUE NOT NULL
,[caption] char(256)
,[valueF] float
,[valueB] binary
,[valueI] int
, Primary Key(id)
) ;
Insert Into MAIN.[Temp_565117464] ([id],[caption],[valueF],[valueB],[valueI])
Select [id],[caption],[valueF],[valueB],[valueI] From MAIN.[information];
Drop Table MAIN.[information];
Alter Table MAIN.[Temp_565117464] Rename To [information];
Commit Transaction;
 */

class CSqlLiteDatabase :
	public IDatabase
{
public:
	CSqlLiteDatabase(std::string);
	~CSqlLiteDatabase();

	std::vector<TRow> getData(const TRow&);

	TRow saveData(const TRow&);
	bool updateData(const TRow&) ;

private:
	sqlite3 * db;

	TRow saveData(std::string, std::string);

	std::vector<TRow> executeStatement(std::string);


};


