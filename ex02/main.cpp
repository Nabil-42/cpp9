
#include <iostream>
#include <string>
#include <climits> 
#include <vector>
#include <deque>
#include <algorithm>


int isDigitsOnly(const std::string& str) {
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

void fusion(std::vector<int> &vec, std::vector<int> &small_storage, std::vector<int> &big_storage)
{
	std::sort(small_storage.begin(), small_storage.end());
	std::sort(big_storage.begin(), big_storage.end());
	std::vector<int>::iterator it = small_storage.begin();

	int i = 0;	
	while (it != small_storage.end())
	{
		std::cout << "test s : " << *it << std::endl;
		vec[i] = *it;
		 ++it;
		 ++i;
	}
	it = big_storage.begin();
	while (it != big_storage.end())
	{
		std::cout << "test s : " << *it << std::endl;
		 vec[i] = *it;
		 ++it;
		 ++i;
	}

	

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

int main(int argc, char** argv) {
    if (argc < 5) {
        std::cerr << "Error: not enough arguments!" << std::endl;
        return 1;
    }

    std::vector<int> vec;
    std::deque<int> dec;

    for (int i = 1; i < argc; ++i) 
    {
        std::string arg = argv[i];
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
    }
    	if (check_doublon(vec) == -1)
    		return 1;
    
    	std::cout << "Befor: ";
		for (int i = 0; i <= 6 && i < static_cast<int>(vec.size()); ++i)
			std::cout << vec[i] << " ";
	std::cout << std::endl;

	vec_algo(vec);

	std::cout << "After: ";
		for (int i = 0; i <= 6 && i < static_cast<int>(vec.size()); ++i)
			std::cout << vec[i] << " ";
		std::cout << std::endl;

    return 0;
}

