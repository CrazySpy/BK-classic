#include <iostream>
#include "Types.h"
#include "CSVReader/CSVReader.h"
#include "EventClock/EventClock.hpp"
#include "BK.h"
using namespace std;

int main(int argc, char **argv) {
    if(argc != 3) {
        printf("Argument Error: %s <dataset> <distance threshold>\n", argv[0]);
        return 0;
    }
    string dataset = argv[1];
    double distanceThreshold = atof(argv[2]);

    CSVReader csvReader(dataset);

    std::vector<InstanceType> instances;
    while(csvReader.hasNext()) {
        auto line = csvReader.getNextRecord();
        FeatureType feature = line[0];
        InstanceIdType id = line[1];
        double x = stod(line[2]);
        double y = stod(line[3]);

        instances.push_back({feature, id, {x, y}});
    }

    EventClock<TimeTicks::Microseconds> clock;

    clock.startClock("bk");
    BK bk(instances, distanceThreshold);
    auto cliques = bk.execute();
    clock.stopClock("bk");

    for(auto &clique : cliques) {
        for(auto &instance : clique) {
            cout << instance.first << '.' << instance.second << ' ';
        }
        cout << endl;
    }

    clock.printEvent("bk");
    return 0;
}
