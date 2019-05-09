#include <iostream>
#include <sstream>
#include <string>

#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

/* vector<vector<int>> graph; */

vector<vector<int>> getNewGraph(vector<vector<int>> gp, float prov) {
    vector<int> deletedV;
    vector<int> deletedE;
    for (int i = 0; i < gp.size(); i++) {
		float pi = (float) rand()/RAND_MAX;
        if (pi < prov) {
            deletedV.push_back(i+1);
        } else {
            for (int j = 0; j < gp[i].size(); j++) {
                float pj = (float) rand()/RAND_MAX;
                if (pj < prov) {
                    /* int aux = gp[i][j]; */
                    deletedE.push_back(j+1);
                }
            }
        }
        
    }

    for (int i = 0; i < deletedV.size(); i++) {
        cout << "V" << i << endl;
        cout << "VERTEX" << deletedV[i] << endl;
    }
    
    for (int i = 0; i < deletedE.size(); i++) {
        cout << "V" << i << endl;
        cout << "EDGE" << deletedE[i] << endl;
    }
    
}

int main() 
{
	cout << "Hello, World!";

	std::ifstream infile("adj.txt");
    int n = std::count(std::istreambuf_iterator<char>(infile), 
             std::istreambuf_iterator<char>(), '\n');

	std::string line;
    cout << "N: " << n << endl;
    
    int graph[n][n];
    fill(graph.begin(), graph.end(), -1);
    int i = 0;


	while (std::getline(infile, line))
	{
	    std::istringstream iss(line);
	    int a, b, num;
	    /* if (!(iss >> a >> b)) { break; } // error */
        int j = 0;
        while (iss >> num) {
            graph[i][j] = num;
            j++;
            cout << num;
            cout << " ";
        }
        cout << " " << endl;

	    // process pair (a,b)
		/* cout << a << " " << b << endl; */

        /* graph.push_back(edges); */
        i++;
	}

    /* cout << graph.size(); */

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "(I, J): (" << i << "," << j << ") = " << graph[i][j] << endl;
        }
    }

    /* graph = getNewGraph(graph, 0.5); */
    return 0;
}



