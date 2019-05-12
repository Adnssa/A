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
        	// cout << "DELETED VERTEX" << i << endl;
            ngp = fillRow(ngp, n, i);
            ngp = fillCol(ngp, n, i);
        } else {
            for (int j = 0; j < n; j++) {
                if (ngp[i][j] == 0) continue;  
                float pj = (float) rand()/RAND_MAX;
                if (pj < prov) {
                	// cout << "DELETED EDGE I: " << i << " J: " << j << endl;
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
            // cout << "DELETED VERTEX" << i << endl;
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
                // cout << "DELETED EDGE I: " << i << " J: " << j << endl;
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
            graella[i][i+1] = 1;
            graella[i+1][i] = 1;
        }

        if (i < lastRow) {
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

    // cout << "NR: " << nr << endl;

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

// STUDIES
float dicotomicPerco(vector<vector<int>> gr, int n, float e, float d, int type, float error) {
    const clock_t begin_time = clock();

    if ((d-e) <= error) {
        return e; // POINT FOUND
    }
    cout << "E: " << e << " D: " << d << endl;
    // TYPE: 1 - NODES ; 2 - EDGES
    float point = ((d - e)/2) + e;
    vector<vector<int>> result;

    if (type == 1) {
        result = percoNodes(gr, n*n, point);
    } else {
        result = percoEdges(gr, n*n, point);
    }
    cout << "PERCO: " << endl;
    std::cout << float( clock () - begin_time ) /  CLOCKS_PER_SEC << endl;
    
    vector<int> res = unFind(result, n);
    bool perco = hasPercolocated(res, n);
    cout << "Union: " << endl;
    std::cout << float( clock () - begin_time ) /  CLOCKS_PER_SEC << endl;

    if (perco) {
        cout << "PERCO " << endl;
        return dicotomicPerco(gr, n, point, d, type, error);
    } else {
        cout << " NO PERCO " << endl;
        return dicotomicPerco(gr, n, e, point, type, error);
    }
}

void studyB() {
    cout << "######## STARTIING STUDY B #########" << endl;
    vector<int> ennes = {5, 10, 15, 20};
    float error = 0.1;
    for (int i = 0; i < ennes.size(); ++i)
    {
        cout << "GENERATING GRID WITH N: " << ennes[i] << endl;
        vector<vector<int>> graella;
        int nreal = ennes[i];
        graella = genGraellaN(nreal); 
        cout << "Starting study with Percolocation on Nodes " << endl;
        float r = dicotomicPerco(graella, nreal, 0, 1, 1, error); 
        cout << "Percolocation found at point: " << r << " With an error threshold of: " << error << endl;
        cout << endl;
        cout << "Starting study with Percolocation on Edges " << endl;
        r = dicotomicPerco(graella, nreal, 0, 1, 1, error); 
        cout << "Percolocation found at point: " << r << " With an error threshold of: " << error << endl;
    }
}


vector<vector<int>> genRandomGraph(vector<vector<int>> gp, int n, float prov) {
    vector<vector<int>> ngp = gp;
    int nr = n*n;
    ngp.resize(nr, vector<int>(nr, 0));
    for (int i = 0; i < nr; i++) {
        for (int j = 0; j < nr; j++) {
            float pj = (float) rand()/RAND_MAX;
            if (pj < prov) {
                ngp[i][j] = 1;
                ngp[j][i] = 1;
            }
        }
    }
    return ngp;
}

int nComponents(vector<int> res) {
    int nParents = 0;
    for (int i = 0; i < res.size(); ++i) {
        if (res[i] == i) {
            nParents += 1;
        }
    }
    return nParents;
}

float dicotomicCC(vector<vector<int>> gr, int n, float e, float d, int goal, float error) {
    const clock_t begin_time = clock();

    if ((d-e) <= error) {
        return e; // POINT FOUND
    }
    cout << "E: " << e << " D: " << d << endl;
    float point = ((d - e)/2) + e;
    vector<vector<int>> result;

    result = percoEdges(gr, n*n, point);

    cout << "PERCO: " << endl;
    std::cout << float( clock () - begin_time ) /  CLOCKS_PER_SEC << endl;
    
    vector<int> res = unFind(result, n);
    int nCC = nComponents(res);
    cout << "Union: " << endl;
    std::cout << float( clock () - begin_time ) /  CLOCKS_PER_SEC << endl;

    if (nCC >= goal) {
        cout << "GOAL REACHED" << endl;
        return dicotomicCC(gr, n, e, point, goal, error);
    } else {
        cout << " GOAL NOT REACHED " << endl;
        return dicotomicCC(gr, n, point, d, goal, error);
    }
}

void studyC() {
    cout << "######## STARTIING STUDY C #########" << endl;
    vector<int> ennes = {5, 10, 15, 20};
    vector<float> provs = {0.5, 0.1, 0.3, 0.8};
    float error = 0.1;
    for (int i = 0; i < ennes.size(); ++i)
    {
        cout << "GENERATING GRID WITH N: " << ennes[i] << endl;
        vector<vector<int>> graella;
        int nreal = ennes[i];
        graella = genRandomGraph(graella, nreal, provs[i]); 
        cout << "Starting study with Percolocation on Edges " << endl;
        float r = dicotomicCC(graella, nreal, 0, 1, nreal/2, error); 
        cout << "Percolocation found at point: " << r << " With an error threshold of: " << error << endl;
    }
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

    // vector<vector<int>> graella;
    // int nreal = 5;
    // graella = genGraellaN(nreal); 

    // cout << "GRAELLA"<< endl;
    // for (int i = 0; i < graella.size(); i++) {
    //     for (int j = 0; j < graella.size(); j++) {
    //         cout << "(I, J): (" << i << "," << j << ") = " << graella[i][j] << endl;
    //     }
    // }


    // vector<vector<int>> ngra;
    // vector<vector<int>> ngraN;
    // vector<vector<int>> ngraE;
    // ngra = getNewGraph(graella, nreal*nreal, 0.5); 
    // ngraN = percoNodes(graella, nreal*nreal, 0.5); 
    // ngraE = percoEdges(graella, nreal*nreal, 0.5); 


    // vector<int> res = unFind(ngra, nreal);
    // vector<int> res2 = unFind(ngraN, nreal);
    // vector<int> res3 = unFind(ngraE, nreal);


    // cout << "Union Size: " << res.size() << endl;
    // for (int i = 0; i < res.size(); i++) {
    //     cout << "(I): " << i << " Parent: " << res[i] << endl;
    // }

    // cout << "Percolocated: " << hasPercolocated(res, nreal) << endl;
    // cout << "PercolocatedN: " << hasPercolocated(res2, nreal) << endl;
    // cout << "PercolocatedE: " << hasPercolocated(res3, nreal) << endl;

    
    // vector<vector<int>> graella;
    // int nreal = 100;
    // graella = genGraellaN(nreal); 

    // float r = dicotomicPerco(graella, nreal, 0, 1, 2, 0.1); 

    // cout << "Dico Perco: " << r << endl;
    // studyB();
    studyC();

    return 0;
}