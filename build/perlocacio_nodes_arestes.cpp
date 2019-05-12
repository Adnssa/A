#include <iostream>
#include <sstream>
#include <string>

#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;


/* vector<vector<int>> graph; */

 vector<vector<int>> fillRow(vector<vector<int>> gp, int n, int row) {
    for (int i = 0; i < n; i++) {
        if (gp[row][i] != 0) {
            gp[row][i] = 0;
        }
    }
    return gp;
}

vector<vector<int>> fillCol(vector<vector<int>> gp, int n, int col) {
    for (int i = 0; i < n; i++) {
    	// gp[i][col] = 0;

        if (gp[i][col] != 0) {
            gp[i][col] = 0;
        }
    }
    return gp;
}

vector<vector<int>> getNewGraph(vector<vector<int>> gp, int n, float prov) {
    vector<vector<int>> ngp = gp;
    for (int i = 0; i < n; i++) {
		float pi = (float) rand()/RAND_MAX;
        if (pi < prov) {
            ngp = fillRow(ngp, n, i);
            ngp = fillCol(ngp, n, i);
        } else {
            for (int j = 0; j < n; j++) {
                if (ngp[i][j] == 0) continue;  
                float pj = (float) rand()/RAND_MAX;
                if (pj < prov) {
                    ngp[i][j] = 0;
                    ngp[j][i] = 0;
                }
            }
        }
    }
    return ngp;
}


int main() 
{
    const clock_t begin_time = clock();
	cout << "PERCOLOCADOR DE GRAPHS PER NODES I ARESTES" << endl;
	cout << "Introdueix el nom del fitxer: ( Lineas: {NODE} {llistat de nodes conectats})" << endl;

	string filename;
	cin >> filename;

	std::ifstream infile(filename);
    int n = std::count(std::istreambuf_iterator<char>(infile), 
             std::istreambuf_iterator<char>(), '\n');

    // CLEAR THE STREAM
   	infile.close();
   	infile.clear();
   	infile.open(filename);
   	 

	std::string line;
    
    vector<vector<int>> graph;
    graph.resize(n, vector<int>(n, 0));

    int i = 0;

    cout << "START READING FILE" << endl;

	while (std::getline(infile, line))
	{
	    std::istringstream iss(line);
	    int a, b, num;
        bool first = true;
        int index;
        while (iss >> num) {
        	if (first)
        	 {
        	 	index = num;
        	 	first = false;
        	 } else {
        	 	graph[index][num] = 1;
        	 } 
        }
	}
    
    cout << "FINISHED READING FILE" << endl;

	// PERCOLOCATION
    cout << "START PERCOLOCATING" << endl;
    cout << "ENTER PROBABILITY P: " << endl;

    float p;
    cin >> p;
    vector<vector<int>> ngraph;
    ngraph = getNewGraph(graph, n, p); 
    
    cout << "FINISHED PERCOLOCATING" << endl;
    cout << "FINISHED PERCOLOCATING GRAPH WITH TIME: ";
    std::cout << float( clock () - begin_time ) /  CLOCKS_PER_SEC <<  " SINCE BEGIN" << endl;

    cout << "ENTER FILENAME TO EXPORT" << endl;

    cin >> filename;
	
	fstream myfile;

	myfile.open(filename, fstream::out);


    for (int i = 0; i < n; i++) {
    	myfile << i << "\t";
        for (int j = 0; j < n; j++) {
        	if (ngraph[i][j] == 1) {
		    	myfile << j << "\t";
        	}
        }
    	myfile << endl;
    }

	myfile.close();
    
    cout << "FINISHED EXPORTING" << endl;

    return 0;
}