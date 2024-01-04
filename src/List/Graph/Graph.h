

#ifndef DATASTRUCTURES_CPP_GRAPH_H
#define DATASTRUCTURES_CPP_GRAPH_H

#include <windows.h>
#include <string>
#include "EdgeList.h"
#include "../../General/AbstractGraph.h"


namespace list {

    class Graph : public AbstractGraph{
    private:
    public:
        EdgeList *edges;
        std::string *words;
        int numberOfWords;
        explicit Graph(int vertexCount);
        ~Graph();
        void addEdge(int from, int to);
        void addEdge(int from, int to, int weight);
        void addWord(std::string word);
        void addEdge(std::string word1, std::string word2);
        int BFS(int startNode, int endNode);
        int BFS(std::string startWord, std::string endWord);
        void Dijkstra(std::string startWord, std::string endWord);
        void connectedComponentsDisjointSet();
        Path* bellmanFord(int source);
        Path* dijkstra(int source);
        void prim();
        int findIndex(std::string word);
        static list::Graph initializePuzzleGame(int wordLength);
        protected:
        void depthFirstSearch(bool* visited, int fromNode) override;
        void breadthFirstSearch(bool* visited, int startNode) override;

        Edge* edgeList(int& edgeCount) override;
    };

}
#endif //DATASTRUCTURES_CPP_GRAPH_H
