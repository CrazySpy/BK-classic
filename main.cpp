#include <iostream>
#include <fstream>
#include <sstream>
#include "Types.h"
#include "CSVReader/CSVReader.h"
#include "EventClock/EventClock.hpp"
#include "BK.h"
using namespace std;

int main(int argc, char **argv) {
    if(argc != 2) {
        printf("Argument Error: %s <dataset>\n", argv[0]);
        return 0;
    }
    string dataset = argv[1];

    std::vector<EdgeType> edges;
    unsigned int N = 0, M = 0;
    ifstream ifs(dataset);
    for(string line; getline(ifs, line);) {
        stringstream ss(line);
        if(ss.peek() == '%') continue;
        if(N == 0 && M == 0) {
            ss >> N >> N >> M;
        } else {
            VertexType u, v;
            ss >> u >> v;
            edges.push_back({u, v});
        }
    }

    EventClock<TimeTicks::Microseconds> clock;

    clock.startClock("bk");
    BK bk(N, edges);
    auto cliques = bk.execute();
    clock.stopClock("bk");

    for(auto &clique : cliques) {
        for(auto &vertex : clique) {
            cout << vertex << ' ';
        }
        cout << endl;
    }

    cout << "Size of result is " << cliques.size() << endl;
    clock.printEvent("bk");
    return 0;
}
