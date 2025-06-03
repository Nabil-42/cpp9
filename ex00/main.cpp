#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

void find(std::map<std::string, float> &cont, float &value, std::string &date)
{
	std::map<std::string, float>::iterator it = cont.find(date);

	if (it != cont.end())
	{
		std::cout << date << " => " << value << " = " << value * it->second << std::endl;
	}
	else
	{
		it = cont.lower_bound(date);

		if (it == cont.begin())
		{
			std::cerr << "Error: no earlier date found for " << date << std::endl;
			return;
		}
		if (it == cont.end() || it->first != date)
			--it;

		std::cout << date << " => " << value << " = " << value * it->second << std::endl;
	}
}

std::string trim(const std::string& str)
{
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos)
        return "";

    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, last - first + 1);
}


void recherche(std::map<std::string, float> &cont, std::ifstream &txt)
{
	std::string line;

	while(std::getline(txt, line))
	{
		std::string date;
		float value; 
		std::stringstream ss(line);
		std::getline(ss, date, '|');
		if (ss.fail())
		{
			std::cerr << " Error: Wrong format" << std::endl;
			continue;
		}
		ss >> value;
		date = trim(date);
		if (!date.empty() && (std::isdigit(date[0]) 
			&& std::isdigit(date[1]) 
			&& std::isdigit(date[2])
			&& std::isdigit(date[3])
			&& date[4] == '-'
			&& (std::isdigit(date[5])
			&& std::isdigit(date[6])
			&& date[7] == '-' 
			&& std::isdigit(date[8])
			&& std::isdigit(date[9]))))
		{
			if ((date[5] >= '1' && date[6] > '2') || (date[5] > '1')
					|| (date[8] >= '3' && date[9] > '1') || date[8] > '3'
					|| (date[5] == '0' && date[6] == '0') || (date[8] == '0' && date[9] == '0'))
				{
					std::cerr << "Error: bad input => " << date << std::endl;
					continue;
				}
			if (value < 0.0f )
				std::cerr << "Error: not a positive number." << std::endl;
			else if (value > 1000)
				std::cerr << "Error: too large a number." << std::endl;
			else (find(cont, value, date));
		}
		
	}
}

int main (int argc, char** argv)
{
	if (argc != 2)
		return std::cerr << "Error: could not open file" << std::endl, 1;
	
	std::ifstream txt (argv[1]);
	std::ifstream file ("data.csv");
	
	if (!txt)
	{
			return std::cerr << "Error: could not open file" << std::endl, 1;
	}

	if (!file)
	{
		return std::cerr << "Error: couldn't open the file data.csv" << std::endl, 1;
	}	
		std::map<std::string, float> cont;
		std::string line;
		
		while (std::getline(file, line))
		{
			std::string date;
			float value = 1;
			std::stringstream ss(line);
			std::getline(ss, date, ',');
			ss >> value;
			if (ss.fail())
			{
				continue;
			}
			if (!date.empty() && (std::isdigit(date[0]) 
			&& std::isdigit(date[1]) 
			&& std::isdigit(date[2])
			&& std::isdigit(date[3])
			&& date[4] == '-'
			&& (std::isdigit(date[5])
			&& std::isdigit(date[6])
			&& date[7] == '-' 
			&& std::isdigit(date[8])
			&& std::isdigit(date[9]))))
			{
				if ((date[5] >= '1' && date[6] > '2') || (date[5] > '1')
					|| (date[8] >= '3' && date[9] > '1') || date[8] > '3'
					|| (date[5] == '0' && date[6] == '0') || (date[8] == '0' && date[9] == '0'))
				{
					std::cerr << "Error: bad input => " << date << std::endl;
					continue;
				}
				cont[date] = value;

			}
			else (std::cerr << " Error: Wrong format 2" << std::endl);
		}
		recherche(cont, txt);
	}