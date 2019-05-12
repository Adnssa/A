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
    	gp[row][i] = 0;
    }
    return gp;
}

vector<vector<int>> fillCol(vector<vector<int>> gp, int n, int col) {
    for (int i = 0; i < n; i++) {
    	gp[i][col] = 0;
    }
    return gp;
}

vector<vector<int>> getNewGraph(vector<vector<int>> gp, int n, float prov) {
    vector<vector<int>> ngp = gp;
    for (int i = 0; i < n; i++) {
		float pi = (float) rand()/RAND_MAX;
        if (pi < prov) {
        	cout << "DELETED VERTEX" << i << endl;
            ngp = fillRow(ngp, n, i);
            ngp = fillCol(ngp, n, i);
        } else {
            for (int j = 0; j < n; j++) {
                if (ngp[i][j] == 0) continue;  
                float pj = (float) rand()/RAND_MAX;
                if (pj < prov) {
                	cout << "DELETED EDGE I: " << i << " J: " << j << endl;
                    /* int aux = gp[i][j]; */
                    ngp[i][j] = 0;
                    ngp[j][i] = 0;
                }
            }
        }
    }
    return ngp;
}

vector<vector<int>> percoNodes(vector<vector<int>> gp, int n, float prov) {
    vector<vector<int>> ngp = gp;
    for (int i = 0; i < n; i++) {
        float pi = (float) rand()/RAND_MAX;
        if (pi < prov) {
            cout << "DELETED VERTEX" << i << endl;
            ngp = fillRow(ngp, n, i);
            ngp = fillCol(ngp, n, i);
        } 
    }
    return ngp;
}


vector<vector<int>> percoEdges(vector<vector<int>> gp, int n, float prov) {
    vector<vector<int>> ngp = gp;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (ngp[i][j] == 0) continue;  
            float pj = (float) rand()/RAND_MAX;
            if (pj < prov) {
                cout << "DELETED EDGE I: " << i << " J: " << j << endl;
                /* int aux = gp[i][j]; */
                ngp[i][j] = 0;
                ngp[j][i] = 0;
            }
        }
    }
    return ngp;
}

// GENERATES GRAELLA N X N
vector<vector<int>> genGraellaN(int n) {
    int nr = n*n;
    int lastRow = (nr - n);
    vector<vector<int>> graella;
    graella.resize(nr, vector<int>(nr, 0));
    for (int i = 0; i < nr; i++) {
        if (i%n != (n-1)) {
            cout << i << " LAST COL" << endl; 
            graella[i][i+1] = 1;
            graella[i+1][i] = 1;
        }

        if (i < lastRow) {
            cout << i << " LAST ROW" << endl; 
            graella[i][i+n] = 1;
            graella[i+n][i] = 1;
        }
    }
    return graella;
}

int ufind(vector<int> result, int i) {
   if (result[i] == -1)
    {
        return i;
    } else {
        return ufind(result, result[i]);
    }
}

vector<int> uunion(vector<int> result, int i, int j) {
   int x = ufind(result, i); 
   int y = ufind(result, j); 
   result[x] = y;
   return result;
}

vector<int> unFind(vector<vector<int>> graella, int n) {
    int nr = n*n;
    vector<int> result;
    result.resize(nr, -1);

    cout << "NR: " << nr << endl;

    for (int i = 0; i < nr; i++) {
        for (int j = 0; j < nr; j++) {
            if (graella[i][j] != 0) {
                int fx = ufind(result, i); 
                int fy = ufind(result, j); 

                if (fx != fy) {
                    result = uunion(result, i, j);
                }
            }
        }
    }

    return result;
}

bool hasPercolocated(vector<int> unF, int n) {
    // FIRST ROW
    for (int i = 0; i < n; i++) {
        // LAST ROW
        for (int j = ((n*n) - n); j < n*n; j++) {
            // Check Connection between rows
            int fx = ufind(unF, i); 
            int fy = ufind(unF, j); 

            if (fx == fy) {
                return true;
            }
        }
    }
    return false;
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
    
    // int graph[n][n] = {};
    vector<vector<int>> graph;
    graph.resize(n, vector<int>(n, 0));

    //fill(*graph, *graph + n*n , 0);
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

    // cout << "ORIGINAL GRAPH"<< endl;
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         cout << "(I, J): (" << i << "," << j << ") = " << graph[i][j] << endl;
    //     }
    // }

    // vector<vector<int>> ngraph;

    // ngraph = getNewGraph(graph, n, 0.2); 

    // cout << "NEW GRAPH"<< endl;
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         cout << "(I, J): (" << i << "," << j << ") = " << ngraph[i][j] << endl;
    //     }
    // }

    vector<vector<int>> graella;
    int nreal = 5;
    graella = genGraellaN(nreal); 

    cout << "GRAELLA"<< endl;
    for (int i = 0; i < graella.size(); i++) {
        for (int j = 0; j < graella.size(); j++) {
            cout << "(I, J): (" << i << "," << j << ") = " << graella[i][j] << endl;
        }
    }


    vector<vector<int>> ngra;
    vector<vector<int>> ngraN;
    vector<vector<int>> ngraE;
    ngra = getNewGraph(graella, nreal*nreal, 0.5); 
    ngraN = percoNodes(graella, nreal*nreal, 0.5); 
    ngraE = percoEdges(graella, nreal*nreal, 0.5); 


    vector<int> res = unFind(ngra, nreal);
    vector<int> res2 = unFind(ngraN, nreal);
    vector<int> res3 = unFind(ngraE, nreal);


    cout << "Union Size: " << res.size() << endl;
    for (int i = 0; i < res.size(); i++) {
        cout << "(I): " << i << " Parent: " << res[i] << endl;
    }

    cout << "Percolocated: " << hasPercolocated(res, nreal) << endl;
    cout << "PercolocatedN: " << hasPercolocated(res2, nreal) << endl;
    cout << "PercolocatedE: " << hasPercolocated(res3, nreal) << endl;



    return 0;
}
