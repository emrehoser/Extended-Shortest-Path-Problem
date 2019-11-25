#include <iostream>
#include <fstream>
#include <queue>
#include <list>
#include <limits>

using namespace std;
class graph {
public:
    int v;
    vector<vector<int>> adj;

    graph(int v) {
        this->v = v;
        adj.resize(v+1);

    }




};
struct compare{
    bool operator () (const pair<int,int> a,const pair<int,int> b){
        return a.second>b.second;
    }
};


int main(int argc, char* argv[]) {
    int n;
    int m;
   ofstream write(argv[2]);
    ifstream read;
    read.open(argv[1]);


    read >> n;
    read >> m;
    int mtx[n+1][m+1];
    graph g(n*m);
    vector<int> height;
    height.resize(g.v +1);
    for(int i =1 ;i<=n;i++){
        for(int j =1;j<=m;j++){
            int temp;
            read >> temp;
            mtx[i][j] = temp;
            height[m*(i-1)+j] = temp;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (j + 1 <= m) {
                g.adj.at(m * (i - 1) + j).push_back(m * (i - 1) + j + 1);
                g.adj.at(m * (i - 1) + j + 1).push_back(m * (i - 1) + j);
            }
            if (i + 1 <= n) {
                g.adj.at(m * (i - 1) + j).push_back(m * (i) + j);
                g.adj.at(m * (i) + j).push_back(m * (i - 1) + j);
            }
        }
    }


    int fn = 1;
    vector<int> cost;
    vector<int> path;
    vector<bool> known;
    vector<int> depth;

    cost.resize(g.v +1);
    path.resize(g.v +1);
    known.resize(g.v +1);
    depth.resize(g.v +1);

    for (int i = 0; i < known.size(); i++) {
        known[i] = false;
        cost[i] = numeric_limits<int>::max();
        path[i] = -1;
    }
    cost[0] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, compare> finished;
    cost[fn] = 0;
    depth[fn] = 0;
    pair<int, int> pair1;
    pair1.first = fn;
    pair1.second = cost[fn];
    finished.push(pair1);
    while (!finished.empty()) {
        pair<int, int> finishedpair = finished.top();
        finished.pop();
        if (known.at(finishedpair.first) == false) {
            known.at(finishedpair.first) = true;
            for (int i = 0; i < g.adj.at(finishedpair.first).size(); i++) {
                if (known[g.adj.at(finishedpair.first).at(i)] == false) {
                    int adjacent = g.adj.at(finishedpair.first).at(i);
                    int weight = abs(height.at(finishedpair.first) - height.at(adjacent));
                    if (weight < cost[adjacent]) {
                        cost[adjacent] = weight;
                        path[adjacent] = finishedpair.first;
                        depth[adjacent] = depth[finishedpair.first] + 1;
                        pair<int, int> toQueue;
                        toQueue.first = adjacent;
                        toQueue.second = cost[adjacent];
                        finished.push(toQueue);
                    }
                }
            }
        }
    }

    int bon;
    read>>bon;

    int x;
    int y;
    int x1;
    int y1;
    read>>x;
    read>>y;
    read>>x1;
    read>>y1;
    int indexOfSource = m * (x - 1) + y;
    int indexOfDest = m * (x1 - 1) + y1;
    int mindep;
    int minindex;
    int maxdep;
    int maxindex;
    if (depth[indexOfDest] > depth[indexOfSource]) {

        mindep = depth[indexOfDest];

        minindex = indexOfDest;
        maxdep = depth[indexOfSource];

        maxindex = indexOfSource;

    } else {

        mindep = depth[indexOfSource];

        minindex = indexOfSource;
        maxdep = depth[indexOfDest];

        maxindex = indexOfDest;


    }

    int ladder = 0;
    while (mindep != maxdep) {
        ladder = max(ladder, cost[minindex]);
        minindex = path[minindex];
        mindep--;
    }
    while (maxindex != minindex) {
        int tempMax = max(cost[maxindex], cost[minindex]);
        ladder = max(ladder, tempMax);
        maxindex = path[maxindex];
        minindex = path[minindex];
    }
    write<<ladder<<" ";





}