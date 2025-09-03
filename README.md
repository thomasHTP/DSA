Electric Vehicle Charging:
Complexity Analysis
**Introduction:**
Demonstrate your understanding of the problem. (2 marks)
Assignment 2 requires students to demonstrate their understanding of fundamental
path finding algorithms, utilising graphs, and other data structures. We are presented
with a given adjacency matrix of the Sydney metropolitan area, indicating the distance
between each station. Additionally, we are given the cost, name, and availability of each
station.

Tasks 1-3: Asks students to demonstrate a basic understanding of the data structures
involved. I.e. EV Charging class.

Task 4: Demonstrates an understanding of Prim’s algorithm, or any other minimum
spanning tree algorithm. Create a minimum spanning tree from parramatta to all other
vertices using Prim’s algorithm.

Task 5 – 9: Highlights an understanding of Dijkstra’s algorithm and its implementation in
relation to the EV charging stations. Find the shortest path using Dijkstra’s algorithm to
all other vertices. Then calculate heuristics and use that to calculate the cheapest path
to all other vertices. Then create a function to use the two algorithms to calculate the
cheapest station to stop at and record the paths from the source, to station, then end
vertex.

**Data Structures:**
List all the major data structures that have been used in the whole program
including the ones in the base code and the code you implemented. (3 marks)
1. Priority Queue – Minheap
2. 2D Array – Array of Arrays
3. Array
4. Linked List of Arrays – Adjacency Matrix / Graph
5. Stack
6. Map - Balanced Binary Search Tree
Algorithms:
Choose three algorithms you have implemented for Tasks 3-9 in your program to
explain your idea of implementation using pseudocode or simplified source code
(list the major operations only). You should choose the most significant algorithms
to demonstrate your skill of programming and the depth of your understanding. (3
marks)
Shortest Path Algorithm
Create a bool, visited, containing all vertices;
Set all visited values to false;
Initialise minDist from source to all other verticies as infinity;
Add source to the visited bool;
Set the minDist of source to 0;
For each vertex
{
Set the minimumWeight to infinity
For each vertex j, if it has not been visited:
{
Check if minDist[j] < minWeight
if it is smaller than MinWeight
Record j as minIndex
}
Record minIndex as visited
For each vertex, x, if weight has not been found
{
If the recorded minDist[vertex] is larger than
the new minWeight + the weight of minIndex to x
Update the minDist of x to the new found minDist
}
}
Minimum Spanning Tree
Create a bool, visited, containing all vertices;
Set all visited values to false;
Initialise the edgeWeights from source to all other verticies as
infinity;
Add source to the visited bool;
Set the edgeWeight of source to 0;
For each vertex {
Set the minimumWeight to infinity
For each vertex j, if It has not been visited
{
For each vertex k, if it has not been visited
{
Compare weights[j][k] minWeight
If it is smaller:
let minWeight be the weight of the current vertex
let startVertex = j
let endVertex = k
}
}
Add endVertex to to visited
}
Charging Path Algorithm
Create a bool, visited, containing all vertices;
Set all visited values to false;
Initialise heuristic from source to neighbouring verticies as:
minDist[source][vertex] * 0.08 + charge * price +
minDist[vertex][endVertex] * 0.08
(distance to cheapest station + from cheapest to end)
if source and vertex are not neighbours
let heuristic = infinity;
Add source to the visited bool;
Set the heuristic of source to 0;
For each vertex
{
Let minHeuristic = infinity
For each vertex j, if it has not been visited:
{
Check if heuristic[j] < minHeuristic
if it is smaller than minHeuristic
Record j as minIndex
}
Record minIndex as visited
For each vertex, x, if weight has not been found
{
If the recorded heurisitc[x] is larger than
the new minHeuristic + weight[minIndex][x]:
Update the minDist of x to the new found minDist
Record minIndex as previousIndex[x]
}
For the most optimal path:
Find the lowest heuristic station:
(I.e. the station with lowest cost to travel to and charge at and the
the lowest cost to travel to the end station.)
Set it as chargingStation
Get the path of chargingStation to source as 1;
Get the path of chargingStation to end as 2;
Print 1 and 2;
Bubble Sort Algorithm
For every station, i, in locations - 1
{
For every station, j, in locations – i - 2
If station j > station j+1
{
Swap station[j] name with station[j+1]
swap station[j] with station[j+1];
}
}

**Complexity analysis:**
Estimate either worst-case or average complexity of the three algorithms you have
chosen above. Assume that the total number of locations is n and total number of
edges in the graph is m. You do not have to give both worst-case and average-case
complexity. (6 marks)
Kruskal’s Algorithm:
Worst-case time complexity: O(n^2)
Prim's Algorithm:
Worst-case time complexity: O(n^3)
Charging Path Algorithm
Worst-case time complexity: O(n^4)
(More complex because it is repeating the shortest path algorithm inside to find the
minimum distance and cost of each charging station using heuristics)
Bubble Sort Algorithm
Worst-case time complexity: O(n^2)

**Conclusion:**
For this assignment I used Prim’s algorithm to calculate the powerlines and a minimum
spanning tree to all vertices. Then I used Dijkstra’s algorithm to calculate the shortest
path to all vertices. I also created a heuristic value by modifying Dijkstra’s algorithm to
record the cheapest heuristic from source to all vertices. which allowed me to calculate
the minimum costing path, and which stations are most optimal to stop at when
travelling from a source to end. Then, I got the minimum heuristics from source to every
vertex, then from the current vertex to every other vertex, then to the destination, for all
vertices. Using these 3 algorithms, I was able to complete all Tasks.
