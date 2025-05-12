#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

void find(std::map<std::string, float> &cont, float &value, std::string &date)
{
	std::map<std::string, float>::iterator it = cont.find(date);

	if (it != cont.end())
		std::cout << date << " => " << value << " = " << value * it->second << std::endl;
	else {
		it = cont.lower_bound(date);
		if (it != cont.begin())
		{
			it--;
			std::cout << date << " => " << value << " = " << value * it->second << std::endl;
		}
		else ( std::cerr << "Error: no data available for this date or earlier." << std::endl, 1);
	}


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
			std::cerr << " Error: Wrong format" << std::endl;
		ss >> value;
		if (value < 0.0f || value > 1000)
			std::cerr << "Error: value not allowed" << std::endl;
		find(cont, value, date);
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
		
	int i = 0;
		while (std::getline(file, line) && i < 10)
		{
			std::string date;
			float value = 1;
			++i;
			std::stringstream ss(line);
			std::getline(ss, date, ',');
			std::cout << "value = " << value << "date = " << date << std::endl;
			ss >> value;
			// break;
			if (ss.fail())
			{
				std::cerr << " Error: Wrong format 1" << std::endl;
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
				cont[date] = value;
			}
			else (std::cerr << " Error: Wrong format 2" << std::endl);
		}
		
		// recherche(cont, txt);
		
	}