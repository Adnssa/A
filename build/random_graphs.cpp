#include <iostream>
#include <sstream>
#include <string>

#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;


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
    int nr = n;
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



vector<vector<int>> genRandomGraph(vector<vector<int>> gp, int n, float prov) {
    vector<vector<int>> ngp = gp;
    int nr = n;
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
    if ((d-e) <= error) {
        return e; // POINT FOUND
    }
    float point = ((d - e)/2) + e;
    vector<vector<int>> result;

    result = percoEdges(gr, n, point);

    vector<int> res = unFind(result, n);
    int nCC = nComponents(res);

    if (nCC >= goal) {
        return dicotomicCC(gr, n, e, point, goal, error);
    } else {
        return dicotomicCC(gr, n, point, d, goal, error);
    }
}

void studyC() {
    const clock_t begin_time = clock();

    cout << "######## STARTIING STUDY C #########" << endl;
    vector<int> ennes = {100, 10, 15, 20};
    vector<float> provs = {0.8, 0.6, 0.3, 0.1};
    float error = 0.1;
    for (int i = 0; i < ennes.size(); ++i)
    {
        cout << "GENERATING GRID WITH N: " << ennes[i] << endl;
        vector<vector<int>> graella;
        int nreal = ennes[i];
        graella = genRandomGraph(graella, nreal, provs[i]); 

	    cout << "FINISHED GENERATING RANDOM GRAPH WITH TIME: ";
	    std::cout << float( clock () - begin_time ) /  CLOCKS_PER_SEC <<  " SINCE BEGIN" << endl;

        cout << "Starting study with Percolocation on Edges " << endl;
        float r = dicotomicCC(graella, nreal, 0, 1, nreal/2, error); 
        cout << "Goal found at point: " << r << " With an error threshold of: " << error << endl;

	    cout << "FINISHED SEARCHING FOR GOAL WITH TIME: ";
	    std::cout << float( clock () - begin_time ) /  CLOCKS_PER_SEC <<  " SINCE BEGIN" << endl;
	    cout << endl << endl;
    }
}

int main() 
{
	cout << "ESTUDI RANDOM GRAPHS" << endl;
    studyC();

    return 0;
}