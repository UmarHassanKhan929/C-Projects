#include <iostream>
using namespace std;
#define MAX 10

// task 1


class AdjacencyMatrix{

    char weighted;
    bool wc;
    char directed;
    bool dc;
    int vertices;
    bool vc;
    bool invalid;
    bool invalid2;
    int AdjMatrix[MAX][MAX]={0};



public:
    AdjacencyMatrix(){
        wc=false;
        dc=false;
        vc=false;
    }

    void InputStuff(){
        while(!(vc && invalid && invalid2)){
            cout<<"Weighted or Unweighted ?(y/n)"<<endl;
            cin>>weighted;
            if(weighted=='y' || weighted=='Y' ){
                wc=true;
            }else if(weighted=='N' || weighted=='n'){
                wc = false;
            }else{
                cout<<"Invalid"<<endl;
                invalid=true;
            }

            cout<<"Directed or UnDirected ?(y/n)"<<endl;
            cin>>directed;
            if(directed=='y' || directed=='Y' ){
                dc=true;
            }else if(directed=='N' || directed=='n'){
                dc=false;
            }else{
                cout<<"Invalid"<<endl;
                invalid2=true;
            }

            cout<<"Enter the numbers of vertices you want"<<endl;
            cin>>vertices;
            if(vertices>0){
                vc=true;
            }else{
                cout<<"Invalid"<<endl;
            }
        }
    }

    void InsertEdge( int u, int v, int weight){
        if(wc && !dc){ //just the weighted
            AdjMatrix[u][v]=weight;
        }
        if(dc && !wc){ //just the directed
            AdjMatrix[u][v]=1;
        }
        if(dc && wc){ //weighted and directed
            AdjMatrix[u][v]=weight;
            AdjMatrix[v][u]=weight;
        }
        if(!(dc && wc)){ //not weighted and directed
            AdjMatrix[u][v]=1;
            AdjMatrix[v][u]=1;
        }
    }

    void PopulateMatrix(){
        cout<<"Possible vertices from 0 to "<<vertices-1<<endl;
        int x=vertices;
        int u,v,weight;
        if(wc){
            while(x>1){
                cout<<"\nEnter source(u), destination(v),weight(w) ";
                cin>>u;
                cin>>v;
                cin>>weight;
                InsertEdge(u,v,weight);
                x--;
            }
        }else{
            while(x>0){
                cout<<"\nEnter source(u), destination(v) ";
                cin>>u;
                cin>>v;
                InsertEdge(u,v,1);
                x--;
            }
        }

    }
    void DisplayMatrix(){
        for(int i=0;i<vertices;i++){
            for(int j=0;j<vertices;j++){
                cout<<AdjMatrix[i][j]<<" ";
            }
            cout<<endl;
        }
    }
    bool IsConnected(int u, int v){
        return AdjMatrix[u][v]>=1;
    }
};

int main(){
    AdjacencyMatrix am;
    am.InputStuff();
    am.PopulateMatrix();
    am.DisplayMatrix();
    am.IsConnected(1,2);
}