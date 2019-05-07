#include <iostream>
#include <sstream>
#include <string>

#include <fstream>

using namespace std;

int main() 
{
	cout << "Hello, World!";
	
	std::ifstream infile("adj.txt");
	std::string line;
	while (std::getline(infile, line))
	{
	    std::istringstream iss(line);
	    int a, b;
	    if (!(iss >> a >> b)) { break; } // error

	    // process pair (a,b)
		cout << a << " " << b << endl;
	}
    	return 0;
}



