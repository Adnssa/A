#include <iostream>
#include <sstream>
#include <string>

#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

/* vector<vector<int>> graph; */

void fillRow(int** gp, int n, int row) {
    for (int i = 0; i < n; i++) {
    	gp[row][i] = 0;
    }
}

void fillCol(int** gp, int n, int col) {
    for (int i = 0; i < n; i++) {
    	gp[i][col] = 0;
    }
}

int** getNewGraph(int* gp, int n, float prov) {
    for (int i = 0; i < n; i++) {
		float pi = (float) rand()/RAND_MAX;
        if (pi < prov) {
        	cout << "DELETED VERTEX" << i << endl;
            fillRow(gp, n, i);
            fillCol(gp, n, i);
        } else {
            for (int j = 0; j < n; j++) {
                float pj = (float) rand()/RAND_MAX;
                if (pj < prov) {
                	cout << "DELETED EDGE I: " << i << " J: " << j << endl;
                    /* int aux = gp[i][j]; */
                    gp[i][j] = 0;
                    gp[j][i] = 0;
                }
            }
        }
    }
    return gp;
}

int main() 
{
	cout << "Hello, World!";

	std::ifstream infile("adj.txt");
	// int n = 3;
    int n = std::count(std::istreambuf_iterator<char>(infile), 
             std::istreambuf_iterator<char>(), '\n');

    // CLEAR THE STREAM
   	infile.close();
   	infile.clear();
   	infile.open("adj.txt");
	// std::ifstream infile("adj.txt");
   	 

	std::string line;
 //    cout << "N: " << n << endl;
    
    int graph[n][n] = {};
    fill(*graph, *graph + n*n , 0);
    int i = 0;

    

    cout << "HOLA 1"<< endl;

	while (std::getline(infile, line))
	{
	    cout << "E1" << endl;
	    std::istringstream iss(line);
	    int a, b, num;
	    /* if (!(iss >> a >> b)) { break; } // error */
        bool first = true;
        int index;
        while (iss >> num) {
		    cout << "E2" << endl;
        	if (first)
        	 {
        	 	index = num;
        	 	first = false;
        	 } else {
        	 	graph[index][num] = 1;
        	 } 
            cout << index;
            cout << " - ";
            cout << num;
            cout << " ";
        }
        cout << " " << endl;

	    // process pair (a,b)
		/* cout << a << " " << b << endl; */

         // graph.push_back(edges); 
	}

    /* cout << graph.size(); */

    cout << "HOLA 2"<< endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "(I, J): (" << i << "," << j << ") = " << graph[i][j] << endl;
        }
    }

    graph = getNewGraph(&graph, n, 0.5); 
    return 0;
}



