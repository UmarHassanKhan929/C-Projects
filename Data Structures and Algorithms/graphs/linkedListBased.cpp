#include <iostream>
#include "linkedList.h"

void addEdgeUndirected(SingleLinkedList<int> list[], int u, int v,int w){
    list[u].InsertAtEnd(v,w);
    list[v].InsertAtEnd(u,w);
}

void addEdgeDirected(SingleLinkedList<int> list[], int u, int v,int w){
    list[u].InsertAtEnd(v,w);
}

void addEdgeDirectedUnWeighted(SingleLinkedList<int> list[], int u, int v,int w){
    list[u].InsertAtEnd(v,1);
}

void addEdgeUnDirectedUnWeighted(SingleLinkedList<int> list[], int u, int v,int w){
    list[u].InsertAtEnd(v,1);
    list[v].InsertAtEnd(u,1);
}

void printGraph(SingleLinkedList<int> list[], int V){
    for (int v = 0; v < V; ++v){
        cout << "\n Adjacency list of vertex:     "<< v << " ";
        list[v].PrintList();
        printf("\n");
    }
}

int main(){
    int numbers;
    cout<<"for 5 vertices"<<endl;
//    cin>>numbers;
    SingleLinkedList<int> AdjList[5];

//    addEdgeDirected(AdjList, 0, 1,32);
//    addEdgeDirected(AdjList, 0, 4,65);
//    addEdgeDirected(AdjList, 1, 2,17);
//    addEdgeDirected(AdjList, 1, 3,43);
//    addEdgeDirected(AdjList, 1, 4,83);
//    addEdgeDirected(AdjList, 2, 3,61);

//    addEdgeDirected(AdjList, 3, 4,59);
    addEdgeUnDirectedUnWeighted(AdjList, 0, 1,32);
    addEdgeUnDirectedUnWeighted(AdjList, 0, 4,32);
    addEdgeUnDirectedUnWeighted(AdjList, 1, 2,32);
    addEdgeUnDirectedUnWeighted(AdjList,  1, 3,32);
    addEdgeUnDirectedUnWeighted(AdjList,  1, 4,32);
    addEdgeUnDirectedUnWeighted(AdjList,  2, 3,32);
    addEdgeUnDirectedUnWeighted(AdjList, 3, 4,32);

    printGraph(AdjList, 5);
}
