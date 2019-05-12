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
        if (gp[i][col] != 0) {
            gp[i][col] = 0;
        }
    }
    return gp;
}

vector<vector<int>> percoNodes(vector<vector<int>> gp, int n, float prov) {
    vector<vector<int>> ngp = gp;
    for (int i = 0; i < n; i++) {
        float pi = (float) rand()/RAND_MAX;
        if (pi < prov) {
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
    if ((d-e) <= error) {
        return e; // POINT FOUND
    }
    
    float point = ((d - e)/2) + e;
    vector<vector<int>> result;

    if (type == 1) {
        result = percoNodes(gr, n*n, point);
    } else {
        result = percoEdges(gr, n*n, point);
    }
    
    vector<int> res = unFind(result, n);
    bool perco = hasPercolocated(res, n);

    if (perco) {
        return dicotomicPerco(gr, n, point, d, type, error);
    } else {
        return dicotomicPerco(gr, n, e, point, type, error);
    }
}

void studyB() {
    const clock_t begin_time = clock();
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

	    cout << "FINISHED NODE PERCOLOCATION SEARCH WITH TIME: ";
	    std::cout << float( clock () - begin_time ) /  CLOCKS_PER_SEC <<  " SINCE BEGIN" << endl;

        cout << endl;
        cout << "Starting study with Percolocation on Edges " << endl;
        r = dicotomicPerco(graella, nreal, 0, 1, 1, error); 
        cout << "Percolocation found at point: " << r << " With an error threshold of: " << error << endl;

	    cout << "FINISHED EDGE PERCOLOCATION SEARCH WITH TIME: ";
	    std::cout << float( clock () - begin_time ) /  CLOCKS_PER_SEC <<  " SINCE BEGIN" << endl;
        cout << endl;
        cout << endl;
    }
}



int main() 
{
	cout << "ESTUDI GRAELLES N X N" << endl;
    studyB();

    return 0;
}