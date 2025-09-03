/*
 * WeightedGraph.h
 *
 *  Created on: 29 Apr 2024
 *      Author: Dongmo
 */
#ifndef H_weightedGraph
#define H_weightedGraph

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cfloat>
#include <stack>

using namespace std;

class WeightedGraph {
protected:
    int gSize;        // number of vertices
    list<int> *graph; // Store adjacency list
    double **weights; // Store weights of edges
    int *edges;
    double *edgeWeights;
    int source;
    double *minDist;
    double *heuristic;
    double *pathHeuristic;
    int *previousIndexDistance;
    int *previousIndexHeuristic;
    int *previousIndexPathHeuristic;
    double **totalHeuristic;

public:
    WeightedGraph(int size = 0);

    ~WeightedGraph();

    void minimumSpanningTree(int sVertex);

    void shortestPath(int sVertex);

    int nearestStation(int sVertex, map<int, Station> locations);

    void stationHeuristics(int sVertex, map<int, Station> locations);

    void chargingPathHeuristics(int sVertex, int eVertex, map<int, Station> locations);

    int cheapestStation(int sVertex, map<int, Station> locations);

    stack<int> optimalPath(int sVertex, int eVertex, map<int, Station> locations);

    stack<int> optimalPath2(int sVertex, int eVertex, map<int, Station> locations);

    list<int> getAdjancencyList(int index) {
        return graph[index];
    }

    double getWeight(int i, int j) {
        return weights[i][j];
    }

    int getEdge(int i) {
        return edges[i];
    }

    double getSmallestWeight(int i) {
        return minDist[i];
    }

    void printAdjacencyList();

    void printAdjacencyMatrix();

    stack<int> getPath(int source, int end);
};

WeightedGraph::WeightedGraph(int size) {
    gSize = 0;
    ifstream infile;
    char fileName[100] = "/Users/thomashtay/CLionProjects/Data Structures and Algorithms/Assignment 2/BaseCode/Distance.txt";

//	cout << "Enter graph adjacency matrix file name: ";
//	cin >> fileName;
//	cout << endl;

    infile.open(fileName);

    if (!infile) {
        cout << "Cannot open input file." << endl;
        return;
    }

    gSize = size;
    graph = new list<int>[gSize];                                  // adjacency list
    weights = new double *[gSize];                                 // 2D array of doubles
    edges = new int[gSize];
    edgeWeights = new double[gSize];
    minDist = new double[gSize];
    heuristic = new double[gSize];
    pathHeuristic = new double[gSize];
    previousIndexDistance = new int[gSize];
    previousIndexHeuristic = new int[gSize];
    previousIndexPathHeuristic = new int[gSize];
    totalHeuristic = new double *[gSize];

    for (int i = 0; i < gSize; i++) {
        weights[i] = new double[gSize];
        totalHeuristic[i] = new double[gSize];
    }

    for (int i = 0; i < gSize; i++) {
        for (int j = 0; j < gSize; j++) {
            double value;
            infile >> value;
            if (value == 0)
                weights[i][j] = DBL_MAX;
            else {
                weights[i][j] = value;
                graph[i].push_back(j);
            }
            totalHeuristic[i][j] = DBL_MAX;
        }
    }
    infile.close();
}

void WeightedGraph::minimumSpanningTree(int sVertex) {
    source = sVertex;

    bool *mstv = new bool[gSize];

    for (int i = 0; i < gSize; i++) {
        mstv[i] = false;
        edges[i] = source;
        edgeWeights[i] = weights[source][i];
    }

    mstv[source] = true;
    edgeWeights[source] = 0;

    for (int i = 0; i < gSize - 1; i++) {
        double minWeight = DBL_MAX;
        int startVertex, endVertex;

        for (int j = 0; j < gSize; j++) {
            if (mstv[j]) {
                for (int k = 0; k < gSize; k++) {
                    if (!mstv[k] && weights[j][k] < minWeight) {
                        startVertex = j;
                        endVertex = k;
                        minWeight = weights[j][k];
                    }
                }
            }
        }
        mstv[endVertex] = true;
        edges[endVertex] = startVertex;
        edgeWeights[endVertex] = minWeight;
    }
// Int, station task 3
    delete[] mstv;
}

void WeightedGraph::shortestPath(int sVertex) {
    bool *weightFound;
    weightFound = new bool[gSize];

    for (int i = 0; i < gSize; i++) {
        weightFound[i] = false;
        minDist[i] = weights[sVertex][i];
        if (weights[sVertex][i] < DBL_MAX) {
            previousIndexDistance[i] = sVertex;
        } else previousIndexDistance[i] = -1;
    }
    weightFound[sVertex] = true;
    minDist[sVertex] = 0;
    previousIndexDistance[sVertex] = -1;

    for (int i = 0; i < gSize - 1; i++) {
        double minWeight = DBL_MAX;
        int minIndex;

        for (int j = 0; j < gSize; j++) {
            if (!weightFound[j]) {
                if (minDist[j] < minWeight) {
                    minIndex = j;
                    minWeight = minDist[j];
                }
            }
        }
        weightFound[minIndex] = true;

        for (int x = 0; x < gSize; x++) {
            if (!weightFound[x]) {
                if (minDist[x] > minWeight + weights[minIndex][x]) {
                    minDist[x] = minWeight + weights[minIndex][x];
                    previousIndexDistance[x] = minIndex;
                }
            }
        }
    }

    previousIndexDistance[sVertex] = -1;

    cout << "Source Vertex: " << sVertex << endl;
    cout << "Shortest distance from source to each vertex."
         << endl;
    cout << setw(12) << "Vertex" << setw(21) << "Shortest Distance" << setw(19) << "Previous Vertex" << endl;

    for (int j = 0; j < gSize; j++) {
        cout << setw(10) << j + 1 << setw(16) << minDist[j] << setw(20) << previousIndexDistance[j] + 1
             << endl;
    }
    cout << endl;

    delete[] weightFound;
}

int WeightedGraph::nearestStation(int sVertex, map<int, Station> locations) {
    shortestPath(sVertex);              //I think i broke this
    int nearest;
    double minWeight = DBL_MAX;

    for (int j = 0; j < gSize; j++) {
        if (locations[j].available) {
            if (minDist[j] <= minWeight && minDist[j] != 0) {
                minWeight = minDist[j];
                nearest = j;
            }
        }
    }

    return nearest;
}

void WeightedGraph::stationHeuristics(int sVertex, map<int, Station> locations) {
    bool *heuristicFound;
    heuristicFound = new bool[gSize];

    for (int i = 0; i < gSize; i++) {
        heuristicFound[i] = false;
        heuristic[i] = weights[sVertex][i] * 2 * 0.08 + 45 * locations[i].chargingPrice;
        if (weights[sVertex][i] < DBL_MAX && locations[i].available) {
            previousIndexHeuristic[i] = sVertex;
        } else previousIndexHeuristic[i] = -1;
    }

    heuristicFound[sVertex] = true;
    heuristic[sVertex] = 0;

    for (int i = 0; i < gSize - 1; i++) {
        double minHeuristic = DBL_MAX;
        int minIndex = -1;

        for (int j = 0; j < gSize; j++) {
            if (!heuristicFound[j]) {
                if (heuristic[j] < minHeuristic) {
                    minIndex = j;
                    minHeuristic = heuristic[j];
                }
            }
        }
        heuristicFound[minIndex] = true;

        for (int x = 0; x < gSize; x++) {
            if (!heuristicFound[x]) {
                double newHeuristic = minHeuristic + weights[minIndex][x] * 2 * 0.08 + 45 * locations[x].chargingPrice;
                if (heuristic[x] > newHeuristic) {
                    heuristic[x] = newHeuristic;
                    previousIndexHeuristic[x] = minIndex;
                }
            }
        }
    }

    previousIndexHeuristic[sVertex] = -5;

    cout << "Source Vertex: " << sVertex + 1 << endl;
    cout << "Heuristic from source to each vertex."
         << endl;
    cout << setw(12) << "Vertex" << setw(18) << "Heuristic" << setw(23) << "Previous Vertex" << endl;

    for (int j = 0; j < gSize; j++) {
        cout << setw(10) << j + 1 << setw(16) << heuristic[j] << setw(20) << previousIndexHeuristic[j] + 1
             << endl;
    }
    cout << endl;

    delete[] heuristicFound;
}

void WeightedGraph::chargingPathHeuristics(int sVertex, int eVertex, map<int, Station> locations) {
    stationHeuristics(sVertex, locations);

    for (int i = 0; i < gSize; i++) {
        shortestPath(i);
        pathHeuristic[i] = (heuristic[i] / 2) + 0.08 * minDist[eVertex];
    }

    cout << "Source Vertex: " << sVertex << endl;
    cout << "Destination Vertex " << eVertex << endl;
    cout << "Heuristic from source to destination vertex."
         << endl;
    cout << setw(12) << "Vertex" << setw(18) << "Heuristic" << setw(23) << "Previous Vertex" << endl;

    for (int j = 0; j < gSize; j++) {
        cout << setw(10) << j + 1 << setw(16) << pathHeuristic[j] << setw(20) << previousIndexHeuristic[j] + 1
             << endl;
    }
    cout << endl;
}

int WeightedGraph::cheapestStation(int sVertex, map<int, Station> locations) {
    stationHeuristics(sVertex, locations);
    int cheapest;

    double minHeuristic = DBL_MAX;
    for (int j = 0; j <= gSize; j++) {
        if (heuristic[j] < minHeuristic && heuristic[j] != 0) {
            if (locations[j].available) {
                minHeuristic = heuristic[j];
                cheapest = j;
            }
        }
    }

    return cheapest;
}

stack<int> WeightedGraph::optimalPath(int sVertex, int eVertex, map<int, Station> locations) {
    chargingPathHeuristics(sVertex, eVertex, locations);
    stack<int> path;

    double minPathHeuristic = DBL_MAX;
    int minPathIndex;
    for (int i = 0; i < gSize; i++) {
        if (pathHeuristic[i] < minPathHeuristic && locations[i].available) {
            minPathIndex = i;
            minPathHeuristic = pathHeuristic[i];
        }
    }

    cout << "\nSTATION TO CHARGE AT: " << minPathIndex + 1 << endl;

    stack<int> path1 = getPath(sVertex, minPathIndex);
    stack<int> path2 = getPath(eVertex, minPathIndex);

    while (!path1.empty()) {
        path.push(path1.top());
        path1.pop();
    }
    while (!path2.empty()) {
        path.push(path2.top());
        path2.pop();
    }

    return path;
}

stack<int> WeightedGraph::optimalPath2(int sVertex, int eVertex, map<int, Station> locations) {
    chargingPathHeuristics(sVertex, eVertex, locations);
    stack<int> path;

    double heuristicToFirstStation;
    double heuristicToSecondStation;
    double heuristicToDestination;

    for (int i = 0; i < gSize; i++) {
        stationHeuristics(sVertex, locations);
        heuristicToFirstStation = heuristic[i] / 2;
        for (int j = 0; j < gSize; j++) {
            stationHeuristics(i, locations);
            heuristicToSecondStation = heuristic[j] / 2;
            for (int x = 0; x < gSize; x++) {
                shortestPath(j);
                heuristicToDestination = 0.08 * minDist[eVertex];
                totalHeuristic[i][j] = heuristicToFirstStation + heuristicToSecondStation + heuristicToDestination;
            }
        }
    }

    int minIndex1 = -1;
    int minIndex2 = -1;
    double minHeuristic = DBL_MAX;

    for (int i = 0; i < gSize; i++) {
        for (int j = 0; j < gSize; j++) {
            if (totalHeuristic[i][j] < minHeuristic && locations[j].available && locations[i].available && i != j) {
                minIndex1 = i;
                minIndex2 = j;
                minHeuristic = totalHeuristic[i][j];
            }
        }
    }

    cout << "\nSTATIONS TO CHARGE AT " << minIndex1 << " AND " << minIndex2 << endl;

    stack<int> path1 = getPath(sVertex, minIndex1);
    stack<int> path2 = getPath(minIndex1, minIndex2);
    stack<int> path3 = getPath(eVertex, minIndex2);

    while (!path1.empty()) {
        path.push(path1.top());
        path1.pop();
    }
    while (!path2.empty()) {
        path.push(path2.top());
        path2.pop();
    }
    while (!path3.empty()) {
        path.push(path3.top());
        path3.pop();
    }

    stack<int> tempInts = path;
    cout << "\nCurrent Paths" << endl;
    while (!tempInts.empty()) {
        cout << locations[tempInts.top()].stationLocation << "(" << tempInts.top() + 1 << ") --> ";
        tempInts.pop();
    }

    return path;
}

// OTHER STUFF

WeightedGraph::~WeightedGraph() {
    for (int i = 0; i < gSize; i++)
        delete[] weights[i];

    delete[] weights;

    for (int index = 0; index < gSize; index++)
        graph[index].clear();

    delete[] graph;
}

void WeightedGraph::printAdjacencyMatrix() {
    cout << "\nAdjacency Matrix" << endl;
    for (int i = 0; i < gSize; i++) {
        for (int j = 0; j < gSize; j++) {
            cout << setw(8) << (weights[i][j] == DBL_MAX ? 0.0 : weights[i][j]);
        }
        cout << endl;
    }
}

void WeightedGraph::printAdjacencyList() {
    cout << "\nAdjacency List" << endl;
    for (int index = 0; index < gSize; index++) {
        cout << index << ": ";
        for (int e: graph[index])
            cout << e << " ";
        cout << endl;
    }

    cout << endl;
}

stack<int> WeightedGraph::getPath(int source, int end) {
    stack<int> path;
    shortestPath(source);

    int currentVertex = end;
    path.push(currentVertex);

    while (currentVertex != source) {
        int prev = previousIndexDistance[currentVertex];
        currentVertex = prev;
        path.push(currentVertex);
    }

    return path;
}

#endif
