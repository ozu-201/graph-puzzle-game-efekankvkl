
#include <fstream>
#include <iostream>
#include "Graph.h"
#include "../../Array/DisjointSet.h"
#include "../Queue.h"
#include "../../Array/Heap/MinHeap.h"

namespace list {

    Graph::Graph(int _vertexCount) : AbstractGraph(_vertexCount){
        edges = new EdgeList[vertexCount];
        words = new std::string[vertexCount];
        numberOfWords = 0;
        for (int i = 0; i < vertexCount; i++) {
            edges[i] = EdgeList();
        }
    }

    void Graph::addEdge(int from, int to) {
        Edge* edge = new Edge(from, to, 1);
        edges[from].insert(edge);
    }

    void Graph::addEdge(int from, int to, int weight) {
        Edge* edge = new Edge(from, to, weight);
        edges[from].insert(edge);
    }

    Graph::~Graph() {
        delete[] edges;
        delete[] words;
    }

    void Graph::connectedComponentsDisjointSet() {
        Edge* edge;
        int toNode;
        DisjointSet sets = DisjointSet(vertexCount);
        for (int fromNode = 0; fromNode < vertexCount; fromNode++){
            edge = edges[fromNode].getHead();
            while (edge != nullptr){
                toNode = edge->getTo();
                if (sets.findSetRecursive(fromNode) != sets.findSetRecursive(toNode)){
                    sets.unionOfSets(fromNode, toNode);
                }
                edge = edge->getNext();
            }
        }
    }

    void Graph::depthFirstSearch(bool *visited, int fromNode) {
        Edge* edge;
        int toNode;
        edge = edges[fromNode].getHead();
        while (edge != nullptr){
            toNode = edge->getTo();
            if (!visited[toNode]){
                visited[toNode] = true;
                depthFirstSearch(visited, toNode);
            }
            edge = edge->getNext();
        }
    }

    void Graph::breadthFirstSearch(bool *visited, int startNode) {
        Edge* edge;
        int fromNode, toNode;
        Queue queue = Queue();
        queue.enqueue(new Node(startNode));
        while (!queue.isEmpty()){
            fromNode = queue.dequeue()->getData();
            edge = edges[fromNode].getHead();
            while (edge != nullptr) {
                toNode = edge->getTo();
                if (!visited[toNode]){
                    visited[toNode] = true;
                    queue.enqueue(new Node(toNode));
                }
                edge = edge->getNext();
            }
        }
    }

    Path *Graph::bellmanFord(int source) {
        Edge* edge;
        Path* shortestPaths = initializePaths(source);
        for (int i = 0; i < vertexCount - 1; i++){
            for (int fromNode = 0; fromNode < vertexCount; fromNode++){
                edge = edges[fromNode].getHead();
                while (edge != nullptr){
                    int toNode = edge->getTo();
                    int newDistance = shortestPaths[fromNode].getDistance() + edge->getWeight();
                    if (newDistance < shortestPaths[toNode].getDistance()){
                        shortestPaths[toNode].setDistance(newDistance);
                        shortestPaths[toNode].setPrevious(fromNode);
                    }
                    edge = edge->getNext();
                }
            }
        }
        return shortestPaths;
    }

    Path *Graph::dijkstra(int source) {
        Edge* edge;
        Path* shortestPaths = initializePaths(source);
        MinHeap heap = MinHeap(vertexCount);
        for (int i = 0; i < vertexCount; i++){
            heap.insert(HeapNode(shortestPaths[i].getDistance(), i));
        }
        while (!heap.isEmpty()){
            HeapNode node = heap.deleteTop();
            int fromNode = node.getName();
            edge = edges[fromNode].getHead();
            while (edge != nullptr){
                int toNode = edge->getTo();
                int newDistance = shortestPaths[fromNode].getDistance() + edge->getWeight();
                if (newDistance < shortestPaths[toNode].getDistance()){
                    int position = heap.search(toNode);
                    heap.update(position, newDistance);
                    shortestPaths[toNode].setDistance(newDistance);
                    shortestPaths[toNode].setPrevious(fromNode);
                }
                edge = edge->getNext();
            }
        }
        return shortestPaths;
    }

    Edge *Graph::edgeList(int& edgeCount) {
        Edge* list;
        edgeCount = 0;
        for (int i = 0; i < vertexCount; i++){
            Edge* edge = edges[i].getHead();
            while (edge != nullptr){
                edgeCount++;
                edge = edge->getNext();
            }
        }
        list = new Edge[edgeCount];
        int index = 0;
        for (int i = 0; i < vertexCount; i++){
            Edge* edge = edges[i].getHead();
            while (edge != nullptr){
                list[index] = Edge(edge->getFrom(), edge->getTo(), edge->getWeight());
                index++;
                edge = edge->getNext();
            }
        }
        return list;
    }

    void Graph::prim() {
        Path* paths = initializePaths(0);
        MinHeap heap = MinHeap(vertexCount);
        for (int i = 0; i < vertexCount; i++){
            heap.insert(HeapNode(paths[i].getDistance(), i));
        }
        while (!heap.isEmpty()){
            HeapNode node = heap.deleteTop();
            int fromNode = node.getName();
            Edge* edge = edges[fromNode].getHead();
            while (edge != nullptr){
                int toNode = edge->getTo();
                if (paths[toNode].getDistance() > edge->getWeight()){
                    int position = heap.search(toNode);
                    heap.update(position, edge->getWeight());
                    paths[toNode].setDistance(edge->getWeight());
                    paths[toNode].setPrevious(fromNode);
                }
                edge = edge->getNext();
            }
        }
    }

    void Graph::addWord(std::string word) {
        words[numberOfWords] = std::move(word);
        numberOfWords++;
    }

    void Graph::addEdge(std::string word1, std::string word2) {
        int index1 = findIndex(word1);
        int index2 = findIndex(word2);

        addEdge(index1, index2);
        addEdge(index2, index1);
    }

    int Graph::findIndex(std::string word) {
        int index = 0;
        while(index < numberOfWords){
            if(word == words[index]){
                return index;
            }
            index++;
        }
        return -1;
    }

    int Graph::BFS(int startNode, int endNode) {
        bool* visited = new bool[vertexCount];

        if(startNode == endNode){
            std::cout << words[startNode] << " -> ";
            return 0;
        }

        for(int i = 0; i < vertexCount; i++){
            visited[i] = false;
        }

        Edge* edge;
        int fromNode, toNode;
        Queue queue = Queue();
        queue.enqueue(new Node(startNode));
        while (!queue.isEmpty()){
            fromNode = queue.dequeue()->getData();
            edge = edges[fromNode].getHead();
            while (edge != nullptr) {
                toNode = edge->getTo();
                if(toNode == endNode){

                    BFS(startNode, fromNode);
                    std::cout << words[toNode] << " -> ";
                    return 0;
                }
                if (!visited[toNode]){
                    visited[toNode] = true;
                    queue.enqueue(new Node(toNode));
                }
                edge = edge->getNext();
            }
        }

        return -1;
    }

    int Graph::BFS(std::string startWord, std::string endWord) {
        int startIndex = findIndex(startWord);
        int endIndex = findIndex(endWord);

        return BFS(startIndex, endIndex);
    }

    void Graph::Dijkstra(std::string startWord, std::string endWord) {
        int startIndex = findIndex(endWord);
        int endIndex = findIndex(startWord);

        Path* paths = dijkstra(startIndex);

        Path p = paths[endIndex];
        while(p.getDistance() != 0){
            std::cout << words[endIndex] << " -> ";
            endIndex = p.getPrevious();
            p = paths[endIndex];

        }
        std::cout << words[endIndex];
    }
   // ıt starts the puzzle game
    list::Graph Graph::initializePuzzleGame(int wordLength) {
        int count = 0;

        string myLine;
        ifstream myFile("C:\\Users\\TEMP\\CLionProjects\\graph-puzzle-game-efekankvkl\\Dictionary.txt", ifstream::in);

        while(getline(myFile, myLine)){
            if(myLine.length() == wordLength){
                count++;
            }
        }

        myFile.close();

        list::Graph graph(count);

        int i1 = 0;

        ifstream myFile2("C:\\Users\\TEMP\\CLionProjects\\graph-puzzle-game-efekankvkl\\Dictionary.txt", ifstream::in);

        while(getline(myFile2, myLine)){
            if(myLine.length() == wordLength){
                graph.addWord(myLine);
                i1++;
            }
        }

        myFile2.close();

        int diff = 0;
        for(int i = 0; i < count; i++){
            for(int j = i; j < count ; j++){
                diff = 0;
                for(int k = 0; k < wordLength; k++){
                    if(graph.words[i][k] != graph.words[j][k]){
                        diff++;
                    }
                }
                if(diff == 1){
                    graph.addEdge(i, j);
                    graph.addEdge(j, i);
                }
            }
        }

        return graph;
    }

}
