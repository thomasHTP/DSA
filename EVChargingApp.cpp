/*
I hereby certify that no other part of this submission has
been copied from any other sources, including the Internet,
books, or other student’s work, or generated from generative
AI tools, such as ChatGPT except the ones I have listed below:
// Professor Dongmo's BaseCode.zip
I hold a copy of this assignment that I can produce if the
original is lost or damaged.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <queue>
#include <map>

using namespace std;

const double travelCostpkm = 0.08;
const double maxPrice = 1.00;
const int maxFreeCharge = 30;
const int chargeAmountMin = 10;
const int chargeAmountMax = 60;

#include "Station.h"
#include "WeightedGraph.h"
#include "EVCharging.h"

int main() {
    srand(time(0));

    EVCharging charging;
    WeightedGraph mst(27);
    int selection = -1;
    int amoutToBeCharged = rand() % 51 + 10;

    charging.askForSelection(selection);

    while(selection != -1) {
        if (selection == 1) {
            charging.printLocations();
            charging.printAdjacencyMatrix();
        }
        else if (selection == 2) {
            double price = charging.askForPrice();
            string location = charging.askForLocation();
            charging.changeLocationDetails(location, price);
        }
        else if (selection == 3) {
            bool option = charging.askForBool();
            string location = charging.askForLocation();
            charging.changeLocationDetails(location, option);
        }
        else if (selection == 4) {
            string location;
            location = charging.askForLocation();
            charging.printMinimumSpanningTree(location);
        }
        else if (selection == 5) {
            charging.listLocationDetails();
        }
        else if (selection == 6) {
            string location = charging.askForLocation();
            charging.printNearestStation(location);
        }
        else if (selection == 7) {
            string location = charging.askForLocation();
            charging.printCheapestStation(location);
        }
        else if (selection == 8) {
            string location = charging.askForLocation();
            string destination = charging.askForLocation();

            charging.printCheapestTrip(location, destination);
        }
        else if (selection == 9) {
            string location = charging.askForLocation();
            string destination = charging.askForLocation();

            charging.printCheapestTrip2(location, destination);
        }
        cout << endl;
        cout << endl;
        charging.askForSelection(selection);
    }

//
//    charging.printMinimumSpanningTree("Parramatta"); // Make it so its an input done by the user instead of in the code
//    charging.changeLocationDetails(0, 0.99);
//    charging.listLocationDetails();
//    charging.printNearestStation("Campbelltown");
//    charging.printCheapestStation("Campbelltown");
//    charging.printCheapestTrip("Wahroonga", "Campbelltown");
//    return 0;
}
