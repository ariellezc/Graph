#include <iostream>
#include <vector>
#include "linkedList.h"
#include <algorithm>
#include <string>
#include <queue>
#include <limits>
#include <fstream>

class graph {
public:
    int flag = false;
    std::vector<list> edges;
    std::vector<int> visited;
    std::queue<int> queue;
    std::vector<int> getAdjacent(int nodeValue);
    std::vector<node*> getNodes(int nodeValue);

    bool equalValue(std::vector<int> firstVec, std::vector<int> secVec);
    bool checkNodes(int nodeVal);
    //creating nodes and adding edges
    void addEdge(int nodeA, int nodeB, int weight);
    void createNode(int vertices);
    //is there a path from vertex(A) to vertex(B)?
    bool isPathCode(int srcNode, int dstNode);
    bool isPath(int srcNode, int dstNode);
    //bfs and dfs
    void depthFirstSearchCode(int srcNode, int dstNode);
    void depthFirstSearch(int srcNode, int dstNode);
    void breadthFirstSearchCode(int srcNode, int dstNode);
    void breadthFirstSearch(int srcNode, int dstNode);
    //is graph connected?
    bool isConnected(int srcNode, int dstNode);
    //dijkstras algorithm
    int minValue(std::vector<int> dist, std::vector<int> adjacentQueue);
    int dijkstraCode(int srcNode, int dstNode);
    int dijkstra(int srcNode, int dstNode);
    //filehandling
    std::string openContentsOfFile(std::string fileName);
    void writeToFile(std::string fileName, int data);
    void fileToClear(std::string fileName);
};

/*not needed (just for testing)
if the vector is not the same size it doesnt have the same value otherwise sort it and return true if it's the same*/
bool graph::equalValue(std::vector<int> firstVec, std::vector<int> secVec){
    if (firstVec.size()!=secVec.size()){
        return false;
    }
    std::sort(firstVec.begin(),firstVec.end());
    std::sort(secVec.begin(),secVec.end());
    return(firstVec == secVec);
}

/*function to add edges to the graph
edges is a vector of list
check if data is equivalent to 0 and above
call function to createNode (code found on linkedList.h)*/
void graph::addEdge(int nodeA, int nodeB, int weight){
    if (nodeA >= 0 && nodeB >= 0) {
        this->edges[nodeA].createNode(nodeB,weight);
        this->edges[nodeB].createNode(nodeA,weight);
    }
    else{
        std::cout << "Invalid Value" << std::endl;
    }
}

/*function to create nodes
create a list and push back to edges vector*/
void graph::createNode(int vertices){
    list newList;
    for(int i=0;i<vertices;i++){
        this->edges.push_back(newList);
    }
}

/*Implemented the code so it does not cout the data, returns a vector, and does not change the value implicitly
make tempNode equivalent to head, loop while it's not null, input data into getAdjacentVector*/
std::vector<int> graph::getAdjacent(int nodeValue){
    std::vector<int> getAdjacentVector;
    node* tempNode = this->edges[nodeValue].head;
    while (tempNode != nullptr){
        getAdjacentVector.emplace_back(tempNode->data);
        tempNode = tempNode->next;
    }
    return getAdjacentVector;
}

//change getAdjacent so it gets the nodes instead (removed ->data and leave it as tempNode)
std::vector<node*> graph::getNodes(int nodeValue){
    std::vector<node*> getAdjacentVector;
    node* tempNode = this->edges[nodeValue].head;
    while (tempNode != nullptr){
        getAdjacentVector.emplace_back(tempNode);
        tempNode = tempNode->next;
    }
    return getAdjacentVector;
}

/*function to check if nodes are viable
check if nodes is in edges by looping over edges and checking if value passed is equivalent*/
bool graph::checkNodes(int nodeVal){
    for (int i=0;i<edges.size();i++){
        if (i == nodeVal){
            return true;
        }
    }
    return false;
}

//All functions relating to file calls by other function to write, clear and open contents of file
void graph::writeToFile(std::string fileName, int data){
    std::ofstream out(fileName, std::ios::app);
    out << data << " ";
    out.close();
}

void graph::fileToClear(std::string fileName){
    std::ofstream fileToClear;
    fileToClear.open(fileName);
    fileToClear.close();
}

std::string graph::openContentsOfFile(std::string fileName){
    std::ifstream myFile(fileName);
    std::string content((std::istreambuf_iterator<char>(myFile)),(std::istreambuf_iterator<char>()));
    return content;
}


/*implemented so it doesn't use boolean on visited nodes but vector
output node 1 to file once visited, breaks if node1 == dstNode, otherwise if it's not in visited do depthfirst again*/
void graph::depthFirstSearchCode(int srcNode, int dstNode){
    visited.emplace_back(srcNode);
    writeToFile("dfs.txt",srcNode);
    std::vector<int> adjacentVector = getAdjacent(srcNode);
    for (int i=0; i<adjacentVector.size(); i++){
        if (std::find(visited.begin(), visited.end(), dstNode) != visited.end()){
            break;
        }
        else if (std::find(visited.begin(), visited.end(), adjacentVector[i]) == visited.end()){
            depthFirstSearchCode(adjacentVector[i], dstNode);
        }
    }
}

/*function to clear file so it doesn't save the value from previous
clear visited
check if nodes actually exist before doing depthfirst otherwise doesnt do depthFirst*/
void graph::depthFirstSearch(int srcNode, int dstNode){
    fileToClear("dfs.txt");
    visited.clear();
    if (checkNodes(srcNode) && checkNodes(dstNode)){
        depthFirstSearchCode(srcNode,dstNode);
    }
    else{
        std::cout << "Cannot do depth first because one or both of the value does not belong to any nodes" << std::endl;
    }
}

/*function to do breadth first
Put node 1 in the visited and put in queue
make current as front
output to file and dequeue from queue
if current == dstNode stop the loop
loop and check if adjacent nodes are in visited, if it's not put it in the visited and push to the queue*/
void graph::breadthFirstSearchCode(int srcNode, int dstNode){
    visited.emplace_back(srcNode);
    queue.push(srcNode);

    while(!queue.empty()){
        int c = queue.front();
        writeToFile("bfs.txt",c);
        queue.pop();
        std::vector<int> adjacentVector = getAdjacent(c);
        if (c == dstNode){
            break;
        }
        for (int i=0; i<adjacentVector.size(); i++){
            if (std::find(visited.begin(), visited.end(), adjacentVector[i]) == visited.end()){
                visited.emplace_back(adjacentVector[i]);
                queue.push(adjacentVector[i]);
            }
        }
    }
}

/*clear file and visited
make sure queue is empty before going to the breadthfirstcode
check both nodes exist otherwise it would not do bfs*/
void graph::breadthFirstSearch(int srcNode, int dstNode){
    fileToClear("bfs.txt");
    visited.clear();
    while(!queue.empty()){
        queue.pop();
    }
    if (checkNodes(srcNode) && checkNodes(dstNode)){
        breadthFirstSearchCode(srcNode,dstNode);
    }
    else{
        std::cout << "Cannot do breadth first because one or both of the value does not belong to any nodes" << std::endl;
    }

}

/*check if node1 exist and dstNode is equivalent to the graph size so it goes through all the nodes
do a dfs
check if all nodes have been visited and put it in the vector
check if "no" exist in vector if it is, graph is not connected so return false otherwise return true*/
bool graph::isConnected(int srcNode, int dstNode){
    if ((checkNodes(srcNode)) && (dstNode == edges.size())){
        fileToClear("dfs.txt");
        visited.clear();
        depthFirstSearchCode(srcNode, dstNode);
    }
    std::vector<std::string> connected;
    for (int i = 0; i < this->edges.size(); i++) {
        if (std::find(visited.begin(), visited.end(), i) != visited.end()){
            connected.emplace_back("yes");
        } else {
            connected.emplace_back("no");
        }
    }

    if (std::find(connected.begin(), connected.end(), "no") != connected.end()){
        std::cout << "no" << std::endl;
        return false;
    }
    else{
        std::cout << "yes" << std::endl;
        return true;
    }
}

/*Modified dfs to work with isPath by looking at adjacent nodes instead
check if dstNode is in the adjacent vector, if it is, output it and make flag equal to true to stop, otherwise return false*/
bool graph::isPathCode(int srcNode, int dstNode){
    visited.emplace_back(srcNode);
    writeToFile("isPath.txt",srcNode);
    std::vector<int> adjacentVector = getAdjacent(srcNode);

    if (std::find(adjacentVector.begin(),adjacentVector.end(), dstNode) != adjacentVector.end()){
        writeToFile("isPath.txt",dstNode);
        flag = true;
    }
    else {
        flag = false;
    }

    for (int i=0; i<adjacentVector.size(); i++){
        if (std::find(visited.begin(), visited.end(), adjacentVector[i]) == visited.end() && flag == false){
            isPathCode(adjacentVector[i], dstNode);
        }
    }
    return flag;
}

/*check if both node exist before going to ispathcode
doesnt go to ispathcode if it's not a node*/
bool graph::isPath(int srcNode, int dstNode){
    fileToClear("isPath.txt");
    visited.clear();
    if (checkNodes(srcNode) && checkNodes(dstNode)){
        isPathCode(srcNode,dstNode);
    }
    else{
        std::cout << "Cannot check path because one or both of the value does not belong to any nodes" << std::endl;
        return false;
    }
}
int graph::minValue(std::vector<int> dist, std::vector<int> adjacentQueue){
    int min = 0;
    int mindex = 0;
    int max = std::numeric_limits<int>::max();
    for (int i=0; i<adjacentQueue.size(); i++){
        if (dist[adjacentQueue[i]] < max){
            min = dist[adjacentQueue[i]];
            mindex = i;
        }
    }
    return mindex;
}
int graph::dijkstraCode(int srcNode, int dstNode){
    int max = std::numeric_limits<int>::max();
    std::vector<int> dist;
    std::vector<int> adjacentQueue;
    for (int i=0;i<edges.size();i++){
        if (i != srcNode){
            dist.emplace_back(max);
        }
        else{
            dist.emplace_back(0);
        }
        adjacentQueue.emplace_back(i);
    }
    while(!adjacentQueue.empty()){
        int min = minValue(dist,adjacentQueue);
        int x = adjacentQueue[min];
        std::vector<node*> adjacencyVector = getNodes(x);
        adjacentQueue.erase(adjacentQueue.begin()+min);
        for (int i=0; i<adjacencyVector.size(); i++){
            int newValue = dist[x] + adjacencyVector[i]->weight;
            if (newValue < dist[adjacencyVector[i]->data]){
                dist[adjacencyVector[i]->data] = newValue;
        }
        }
    }
    return dist[dstNode];
}
int graph::dijkstra(int srcNode, int dstNode){
    if (checkNodes(srcNode) && checkNodes(dstNode)){
        dijkstraCode(srcNode,dstNode);
    }
    else{
        std::cout << "Cannot do dijkstra because one or both of the value does not belong to any nodes" << std::endl;
    }
}
/*int main(){
    auto graph1 = new graph();
    graph1->createNode(7);
    graph1->addEdge(0,4,4);
    graph1->addEdge(0,5,3);
    graph1->addEdge(1,4,2);
    graph1->addEdge(1,6,3);
    graph1->addEdge(1,3,5);
    graph1->addEdge(2,6,4);
    graph1->addEdge(2,5,1);
    graph1->addEdge(3,4,1);
    graph1->addEdge(5,6,7);
    std::cout<< graph1->edges.size()<< std::endl;
    graph1->isConnected(0,graph1->edges.size());
    graph1->depthFirstSearch(0,2);
    graph1->breadthFirstSearch(0,2);
    graph1->isPath(0,2);
    int dijkstraDist = graph1->dijkstra(0,2);
    std::cout << dijkstraDist;
}*/
