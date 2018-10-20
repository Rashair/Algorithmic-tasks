#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    int n,m;
    cin>>n>>m;

    vector<int> tab[n+1];
    vector<int> cost[n+1];
    for(int i=0; i<m; ++i){
        int a,b,c;
        cin>>a>>b>>c;
        tab[a].push_back(b);
        cost[a].push_back(c);
    }

    int ex_cost[n+1];
    const int lim=100000001;
    memset(ex_cost, lim, sizeof ex_cost);
    ex_cost[1]=0;

    //Bellman-Ford algorithm
    for(int i=0; i<n-1; ++i){
        for(int j=1; j<=n; ++j){
            for(unsigned e=0; e<tab[j].size(); ++e){
                int v=tab[j][e];
                if(ex_cost[v]>ex_cost[j]+cost[j][e])
                    ex_cost[v]=ex_cost[j]+cost[j][e];
            }
        }
    }

    //saving values of after n-1 loop
    int val[n+1];
    for(int i=1; i<=n; ++i)
        val[i]=ex_cost[i];
    //nth loop of Bellman-Ford algorithm
    for(int j=1; j<=n; ++j){
        for(unsigned e=0; e<tab[j].size(); ++e){
            int v=tab[j][e];
            if(ex_cost[v]>ex_cost[j]+cost[j][e])
                ex_cost[v]=ex_cost[j]+cost[j][e];
        }
    }

    string an=(val[1]<0 ? "TAK" : "NIE");
    //check if values changed after nth loop
    for(int i=1; i<=n; ++i){
        if(ex_cost[i]<val[i]){
            an="TAK";
            break;
        }
    }
    cout<<an<<endl;
}
