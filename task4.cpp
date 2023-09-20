#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <chrono>
#include <iomanip> 
#include <ctime>


std::ofstream logFile("c:\\test\\app.log");

// Function for finding connected components with DFS
void findConnectedComponents(std::vector<std::vector<int>>& adjacencyList, std::vector<int>& component, std::vector<bool>& visited, int node, int componentNumber) {
    visited[node] = true;
    component[node] = componentNumber;

    for (int neighbor : adjacencyList[node]) {
        if (!visited[neighbor]) {
            findConnectedComponents(adjacencyList, component, visited, neighbor, componentNumber);
        }
    }
}

void log(std::string message) {
    // Add time information to log
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::tm localTime;
    localtime_s(&localTime, &time);

    // Write the log message to the file
    logFile << "[" << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S") << "] " << message << std::endl;
}

int main() {
  
   
    log("Application started.");
    std::ifstream input("c:\\test\\graf.txt");

    int numNodes;
    input >> numNodes;

    std::vector<std::vector<int>> adjacencyList(numNodes);

    for (int i = 0; i < numNodes; ++i) {
        int node;
        input >> node;

        int neighbor;
        while (input >> neighbor && neighbor != -1) {
            adjacencyList[node].push_back(neighbor);
        }
    }

    std::vector<int> component(numNodes, -1);  
    std::vector<bool> visited(numNodes, false);  
    int componentNumber = 0;  // Component counter

   // finding connected components with DFS
    for (int i = 0; i < numNodes; ++i) {
        if (!visited[i]) {
            findConnectedComponents(adjacencyList, component, visited, i, componentNumber);
            componentNumber++;
        }
    }

    //Write the results to the file
    std::ofstream output("c:\\test\\connected_components.txt");

    for (int i = 0; i < numNodes; ++i) {
        output << "Node  " << i << " connected component " << component[i] << std::endl;
    }

    log("Application ended.");
    input.close();
    output.close();
    logFile.close();

    return 0;
}