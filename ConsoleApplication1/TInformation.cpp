#include "stdafx.h"
#include "TInformation.h"


TInformation::TInformation()
{
}

TInformation::TInformation(std::map<std::string, std::string> _map)
{
	if (_map.find("id") != _map.end())
		this->id_order = std::stoi(_map["id"]);
	if (_map.find("valueI") != _map.end())
		this->valueI = std::stoi(_map["valueI"]);
	if (_map.find("valueF") != _map.end())
		this->valueF =  atof(_map["valueF"].c_str());
	if (_map.find("valueB") != _map.end())
		this->valueB = std::stoi(_map["valueB"]);
	if (_map.find("caption") != _map.end())
		this->caption =(_map["caption"]);

}


TInformation::~TInformation()
{
}
