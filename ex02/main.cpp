
#include <iostream>
#include <string>
#include <climits> 
#include <vector>
#include <deque>
#include <algorithm>
#include <sstream>
#include <windows.h>
#include <iomanip>



template <typename T>
void display(const T& container)
{
    typename T::const_iterator it;
    for (it = container.begin(); it != container.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

int isDigitsOnly(const std::string& str) 
{
    for (size_t i = 0; i < str.length(); ++i) {
        if (!isdigit(str[i]))
            return 1; 
    }
    return 0;
}

int fake_atoi(const std::string &str) {
    unsigned int nbr = 0;
    size_t i = 0;

    while (str[i]) 
    {
	if (nbr > INT_MAX) 
	{
            std::cerr << "Error: invalid argument (overflow) INT > INT_MAX '" << str << "'!" << std::endl;
           return -1;
	}
	nbr = nbr * 10 + (str[i] - '0');
        ++i;
    }
    return nbr;
}

std::vector<size_t> getJacobsthalIndices(size_t n) 
{
	std::vector<size_t> jacob;
	jacob.push_back(0);
	jacob.push_back(1);
	jacob.push_back(3);

    while (jacob.back() < n) 
    {
        size_t next = jacob[jacob.size() - 1] + 2 * jacob[jacob.size() - 2];
	if (next >= n)
            break;
        jacob.push_back(next);
    }
    return jacob;
}


void fusion(std::vector<int> &vec, std::vector<int> &small_storage, std::vector<int> &big_storage)
{
	std::sort(big_storage.begin(), big_storage.end());
	std::vector<size_t> jacob = getJacobsthalIndices(small_storage.size());
	
	for (size_t i = 0; i < jacob.size() - 1; ++i)
	{
   		size_t idx = jacob[i];   
		int val = small_storage[idx];
		std::vector<int>::iterator it = std::lower_bound(big_storage.begin(), big_storage.end(), val);
		big_storage.insert(it, val);
	}
	std::cout << jacob.size() << std::endl;
	
	size_t idx = 0;
	size_t j = 0;
	for (size_t i = 0; i < small_storage.size(); ++i)
	{
		int val = small_storage[i];
		if (j < jacob.size())
		{
			idx = jacob[j];
		}
		if (idx != i)
		{
			std::vector<int>::iterator it = std::lower_bound(big_storage.begin(), big_storage.end(), val);
			big_storage.insert(it,val);
		}
		else {
			++j;
		}
		
	}
	std::cout << big_storage.size() << std::endl;
	vec = big_storage;	
}

void vec_algo(std::vector<int> &vec)
{
	std::vector<int>::iterator it = vec.begin();
	std::vector<int> big_storage, small_storage;
	
	while (it != vec.end() && (it + 1) != vec.end())
	{
		int first = *it;
		int second = *(it + 1);
		if (first > second)
		{
			big_storage.push_back(*it);
			small_storage.push_back(*(it + 1));
		}
		else {
			big_storage.push_back(*(it + 1));
			small_storage.push_back(*it);
		}
		it += 2;
	}
	if (it != vec.end())
		small_storage.push_back(*it);
	
	fusion(vec, small_storage, big_storage);
}

int check_doublon(std::vector<int> &vec)
{
	std::vector<int>::iterator it = vec.begin();

	int i = 0;
	while (it != vec.end())
	{
		int value = *it;
		while (it + i != vec.end())
		{
			if (value == *(it + i + 1))
			{
				std::cerr << "Error: Doublon !" << std::endl;
				return -1;
			}
			++i;
		}
		i = 0;
		++it;
	}
	return 0;
	
}

int verif(std::vector<std::string> &vec, char** argv, int argc)
{
	if (argc == 2)
	{
		std::istringstream iss(argv[1]);
		std::string token;
		
		while (iss >> token) 
		{
			vec.push_back(token);
		}
	}
	if (argc < 5 && vec.size() < 4) 
	{
        	std::cerr << "Error: not enough arguments !" << std::endl;
        	return 1;
	}
	return 0;
}

int main(int argc, char** argv) 
{
	srand(time(NULL));
	clock_t start1 = clock();
	std::vector<std::string> tokens;
	if (verif(tokens, argv, argc))
		return 1;
	std::vector<int> vec;
	std::deque<int> dec;

	int i = 1;
	if (argc == 2)
		i = 0;
	while (i < argc || i < static_cast<int>(tokens.size())) 
	{
		std::string arg;
		if (argc == 2)
			arg = tokens[i];
		else (arg = argv[i]);
		if (isDigitsOnly(arg)) 
		{
			std::cerr << "Error: invalid argument '" << arg << "'!" << std::endl;
			return 1;
		}
		int value = fake_atoi(arg);

		if (value == -1)
			return 1;

		vec.push_back(value); 
		dec.push_back(value); 
		++i;
	}
    	if (check_doublon(vec) == -1)
    		return 1;

	
	if (vec.size() < 4)
	{
		std::cout << vec.size() << std::endl;
		std::cerr << "Error: not enough arguments !" << std::endl;
        		return 1;
	}
    
    	std::cout << "Befor: ";
		for (int i = 0; i <= 6 && i < static_cast<int>(vec.size()); ++i)
			std::cout << vec[i] << " ";
	std::cout << std::endl;
	std::cout << vec.size() << std::endl;
	vec_algo(vec);
	std::cout << vec.size() << std::endl;

	// Sleep(450);

 	clock_t end1 = clock();
	double time1 = static_cast<double>(end1 - start1) / CLOCKS_PER_SEC * 1000;
	std::cout << "After: ";
		for (int i = 0; i <= 6 && i < static_cast<int>(vec.size()); ++i)
			std::cout << vec[i] << " ";
	std::cout << std::endl;
    std::cout << std::fixed << std::setprecision(5);
    std::cout << "Time to process a range of " << vec.size()
              << " elements with std::vector container: "
              << time1 << " us" << std::endl;
    return 0;
}

