#ifndef EVCHARGING_H_
#define EVCHARGING_H_

#include "Prices.h"//;

class EVCharging : public WeightedGraph {// you may also declare this class as an extension of WeightedGraph
private:
    map<int, Station> locations;// THIS IS A BINARY SEARCH TREE
    int numberOfLocations;
    WeightedGraph *weightedGraph;
    priority_queue<Prices> stationPrices;

public:
    EVCharging();

    ~EVCharging();

    void inputLocations();

    int lookForName(const string &locationName);

    void printLocations();

    void printAdjacencyMatrix();

    void printMinimumSpanningTree(string startLocation);

    void changeLocationDetails(string sLocation, bool option);

    void changeLocationDetails(string sLocation, double price);

    void listLocationDetails();

    void printNearestStation(string sLocation);

    void printCheapestStation(string sLocation);

    void printCheapestTrip(string sLocation, string eLocation);

    void printCheapestTrip2(string sLocation, string eLocation);

    void askForSelection(int &selection);

    string askForLocation();

    double askForPrice();

    bool askForBool();
};

EVCharging::EVCharging() {
    inputLocations();
    weightedGraph = new WeightedGraph(numberOfLocations);
}

EVCharging::~EVCharging() {
    delete weightedGraph;
}

void EVCharging::inputLocations() {
    ifstream infile;
    char fileName[100] = "/Users/thomashtay/CLionProjects/Data Structures and Algorithms/Assignment 2/BaseCode/Locations.txt";

//	cout << "Enter charging location file name: ";
//	cin >> fileName;
//	cout << endl;

    infile.open(fileName);

    if (!infile) {
        cout << "Cannot open input file." << endl;
        return;
    }

    int locationIndex = 0;

    while (!infile.eof()) {
        Station s;
        string charger;
        string price;
        while (!infile.eof()) {
            getline(infile, s.stationLocation, ',');        // Station name/location
            getline(infile, charger, ',');                  // number of chargers
            getline(infile, price);                              // price to charge
            s.available = (stoi(charger) == 1) ? true : false;     // if its available true
            s.chargingPrice = stod(price);                         // convert string to double, get price
            s.index = locationIndex;                                   // assigns a key to as the locationindex
            locations[locationIndex] = s;                              // assigns a key to the station
            locationIndex++;                                           // next location
        }
    }

    numberOfLocations = locationIndex;
}

int EVCharging::lookForName(const string &sLocation) {
    for (int i = 0; i < locations.size(); i++) {
        if (locations[i].stationLocation == sLocation) {
            return i;
        }
    }
    cout << endl << "*** Location " << sLocation << " was not found*** " << endl;
    return -1;
}

void EVCharging::printLocations() {
    cout << "List of locations and charging information " << endl;
    cout << setw(8) << "Index" << setw(20) << "Station Location" << setw(20) << "Availability" << setw(20)
         << "Charging price" << endl;

    map<int, Station>::iterator it = locations.begin();

    for (; it != locations.end(); it++) {
        it->second.printLocation();
    }

    cout << endl;
}

void EVCharging::printAdjacencyMatrix() {
    cout
            << "Adjacency matrix (0 means no direct connection, non-zero value represents the distance of adjacent locations)\n"
            << endl;
    cout << setw(13) << " ";
    for (int i = 0; i < numberOfLocations; i++) {
        cout << setw(13) << locations[i].stationLocation;
    }
    cout << endl;
    for (int i = 0; i < numberOfLocations; i++) {
        cout << setw(13) << locations[i].stationLocation;
        for (int j = 0; j < numberOfLocations; j++) {
            cout << setw(13) << (weightedGraph->getWeight(i, j) == DBL_MAX ? 0.0 : weightedGraph->getWeight(i, j));
        }
        cout << endl;
    }
}

void EVCharging::printMinimumSpanningTree(string startName) {
    int sVertex = lookForName(startName);

    weightedGraph->minimumSpanningTree(sVertex);

    cout << endl << "Coordinates of the Minimum Spanning Tree (MST):" << endl;
    for (int i = 0; i < numberOfLocations; ++i) {
        int startVertex = weightedGraph->getEdge(i);
        if (startVertex != i) {
            cout << locations[startVertex].stationLocation << "(" << startVertex + 1 << ")"
                 << " --> " << locations[i].stationLocation << "(" << i + 1 << ")" << endl;
        }
    }
    cout << endl;
}

void EVCharging::changeLocationDetails(string sLocation, bool option) {
    int index = lookForName(sLocation);

    if (locations.find(index) != locations.end()) {
        locations[index].available = option;
        cout << endl << "CHANGED " << locations[index].stationLocation
             << " AVAILABILITY TO " << locations[index].available << endl;
        cout << endl;
        return;
    }
    cout << endl << "*** Location is not in map ***" << endl;
}

void EVCharging::changeLocationDetails(string sLocation, double price) {
    int index = lookForName(sLocation);

    if (locations.find(index) != locations.end()) {
        if (price <= 1.00) {
            locations[index].chargingPrice = price;
            cout << "CHANGED " << locations[index].stationLocation
                 << " PRICE TO $" << locations[index].chargingPrice << "/kWh" << endl;
            cout << endl;
            return;
        }
        cout << endl << "*** Maximum charging price is $1.00 ***" << endl;
    }
    cout << endl << "*** Location not in map ***" << endl;

}

void EVCharging::listLocationDetails() {
    // USE A PRIORITY QUEUE
    // AND A VECTOR
    map<int, Station> tempLocations = locations;

    for (int i = 0; i < locations.size() - 1; i++) {
        for (int j = 0; j < tempLocations.size() - i - 1; j++) {
            if (tempLocations[j].chargingPrice > tempLocations[j + 1].chargingPrice) {
                // Swaps names
                string tempName = tempLocations[j].stationLocation;
                tempLocations[j].stationLocation = tempLocations[j + 1].stationLocation;
                tempLocations[j + 1].stationLocation = tempName;

                // Swaps prices
                double tempPrice = tempLocations[j].chargingPrice;
                tempLocations[j].chargingPrice = tempLocations[j + 1].chargingPrice;
                tempLocations[j + 1].chargingPrice = tempPrice;
            }
        }
    }

    cout << "Stations sorted by ascending order: " << endl;
    cout << setw(8) << " " << "Station Location" << setw(21) << "Charging Price" << endl;

    for (int i = 0; i < tempLocations.size(); i++) {
        cout << setw(20) << tempLocations[i].stationLocation
             << setw(16) << "$" << tempLocations[i].chargingPrice << "/kWh" << endl;
    }
}

//void EVCharging::listLocationDetails() {
//    // USE A PRIORITY QUEUE
//    // AND A VECTOR
//    for (int i = 0; i < locations.size(); i++) {
//        locations()
//    }
//}
//

void EVCharging::printNearestStation(string sLocation) {
    int sVertex = lookForName(sLocation);

    string nearestStation = locations[weightedGraph->nearestStation(sVertex, locations)].stationLocation;

    cout << "Nearest station is " << nearestStation << endl;
}

void EVCharging::printCheapestStation(string sLocation){
    int sVertex = lookForName(sLocation);

    string cheapestStation = locations[weightedGraph->cheapestStation(sVertex, locations)].stationLocation;

    cout << "Cheapest station is " << cheapestStation << endl;
}

void EVCharging::printCheapestTrip(string sLocation, string eLocation) {
    int sVertex = lookForName(sLocation);
    int eVertex = lookForName(eLocation);

    stack<int> path;
    path = weightedGraph->optimalPath(sVertex, eVertex, locations);

    cout << "\nThe most optimal path from " << sLocation << " to " << eLocation << endl;
    while (!path.empty()) {
        cout << locations[path.top()].stationLocation << "(" << path.top() + 1 << ") --> ";
        path.pop();
    }
}

void EVCharging::askForSelection(int &selection) {
    cout << setw(50) << "===== Sydney EV Charging Optimiser =====\n";

    cout << "1. See station information\n";
    cout << "2. Change Price\n";
    cout << "3. Change Availability\n";
    cout << "4. Create Powerline\n";
    cout << "5. List Stations in Ascending Order\n";
    cout << "6. Nearest Station Available\n";
    cout << "7. Cheapest Station To Charge At\n";
    cout << "8. Most Optimal Charging Path to Destination\n";
    cout << "9. Most Optimal Charging Path 2 Stations\n";

    cout << endl << endl << "Enter your selection: " ;
    cin >> selection;
}

double EVCharging::askForPrice() {
    cin.clear();
    double price;
    cout << "Enter the price\n";
    cin >> price;
    return price;
}

string EVCharging::askForLocation() {
    cin.ignore();
    string sLocation;
    cout << "Enter the station\n";
    getline(cin, sLocation);
    return sLocation;
}

bool EVCharging::askForBool() {
    cin.ignore();
    int selection;
    cout << "Enter the Option\n";
    cin >> selection;

    if (selection == 1) {
        return true;
    }
    else return false;
}

void EVCharging::printCheapestTrip2(string sLocation, string eLocation) {
    int sVertex = lookForName(sLocation);
    int eVertex = lookForName(eLocation);

    stack<int> path;
    weightedGraph->optimalPath2(sVertex, eVertex, locations);

    cout << "\nThe most optimal path from " << sLocation << " to " << eLocation << endl;
    while (!path.empty()) {
        cout << locations[path.top()].stationLocation << "(" << path.top() + 1 << ") --> ";
        path.pop();
    }

    cout << eLocation << "(" << eVertex + 1 << ")";

}

#endif /* EVCHARGING_H_ */
