#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Undirected_graph/undirectedGraph.h"
//used catch2 for unit testing
//https://github.com/catchorg/Catch2

//graph testing

TEST_CASE("Graph is working correctly"){
    std::cout<<std::endl;
    std::cout << "Graph testing" << std::endl;

    auto graph1 = new graph();

    graph1->createNode(8);
    graph1->addEdge(0,4,4);
    graph1->addEdge(0,5,3);
    graph1->addEdge(1,4,2);
    graph1->addEdge(1,6,3);
    graph1->addEdge(1,3,5);
    graph1->addEdge(2,6,4);
    graph1->addEdge(2,5,1);
    graph1->addEdge(3,4,1);
    graph1->addEdge(5,6,7);

    auto graph2 = new graph();
    graph2->createNode(7);
    graph2->addEdge(0,4,4);
    graph2->addEdge(0,5,3);
    graph2->addEdge(1,4,2);
    graph2->addEdge(1,6,3);
    graph2->addEdge(1,3,5);
    graph2->addEdge(2,6,4);
    graph2->addEdge(2,5,1);
    graph2->addEdge(3,4,1);
    graph2->addEdge(5,6,7);

    SECTION("Testing if the addEdge does not accept negative integers"){
        std::cout<<std::endl;
        graph1->addEdge(-2,6,8);
        graph1->addEdge(-1,-3,4);
        graph1->addEdge(-9,2,1);
    }

    SECTION("Testing adjacent nodes"){

        std::vector<int> adjacentTo0 = graph1->getAdjacent(0);
        std::vector<int> connectedTo0 = {5,4};
        REQUIRE(graph1->equalValue(adjacentTo0,connectedTo0));

        std::vector<int> adjacentTo1 = graph1->getAdjacent(1);
        std::vector<int> connectedTo1 = {4,6,3};
        REQUIRE(graph1->equalValue(adjacentTo1,connectedTo1));

        std::vector<int> adjacentTo2 = graph1->getAdjacent(2);
        std::vector<int> connectedTo2 = {4,6,5};
        REQUIRE(!graph1->equalValue(adjacentTo2,connectedTo2));
    }

    SECTION("Testing isPath"){
        REQUIRE(graph1->isPath(0,1));
        REQUIRE(graph1->isPath(2,3));
        REQUIRE(!(graph1->isPath(0,7)));
        REQUIRE(!(graph1->isPath(0,8)));
    }

    SECTION("Testing isConnected"){
        REQUIRE(!(graph1->isConnected(0,graph1->edges.size())));
        REQUIRE(graph2->isConnected(0,graph2->edges.size()));
    }

    SECTION("Testing dijkstra"){
        int shortestDist1 = graph2->dijkstra(0,6);
        REQUIRE(shortestDist1 == 8);
        int shortestDist2 = graph2->dijkstra(0,2);
        REQUIRE(shortestDist2 == 4);
        int shortestDist3 = graph2->dijkstra(1,5);
        REQUIRE(shortestDist3 == 8);
        int shortestDist4 = graph2->dijkstra(1,4);
        REQUIRE(shortestDist4 == 2);
    }

    SECTION("Testing bfs"){
        graph2->breadthFirstSearch(0,1);
        std::string bfs1 = graph2->openContentsOfFile("bfs.txt");
        REQUIRE(bfs1 == "0 4 5 1 ");

        graph2->breadthFirstSearch(0,2);
        std::string bfs2 = graph2->openContentsOfFile("bfs.txt");
        REQUIRE(bfs2 == "0 4 5 1 3 2 ");
    }

    SECTION("Testing dfs"){
        graph2->depthFirstSearch(0,6);
        std::string dfs1 = graph2->openContentsOfFile("dfs.txt");
        REQUIRE(dfs1 == "0 4 1 6 ");

        graph2->depthFirstSearch(5,4);
        std::string dfs2 = graph2->openContentsOfFile("dfs.txt");
        REQUIRE(dfs2 == "5 0 4 ");
    }
}
