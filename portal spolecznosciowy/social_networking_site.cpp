#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
#include "social_networking_site.h"

int main(){
    ios::sync_with_stdio(false);
    
    int Z;
    cin>>Z;
    while(Z--){
        int n,m;
        cin>>n>>m;
        
        vector <int> site[n+1];
        while(m--){
            int a,b;
            cin>>a>>b;
            site[a].push_back(b);
            site[b].push_back(a);
        }
        
        int my_number;
        cin>>my_number;
        
        int distance[n+1];
        memset(distance,-1,sizeof(distance));
        distance[my_number]=0;
        
        queue <int> vertices;
        vertices.push(my_number);
        while(!vertices.empty()){
            int k=vertices.front();
            vertices.pop();
            for(unsigned i=0; i<site[k].size(); ++i){
                int x=site[k][i];
                if(distance[x]==-1){
                    distance[x]=distance[k]+1;
                    vertices.push(x);
                }
            }
        }
        
        bool visited[n+1];
        queue <int> to_visit;
        visited[0]=1;
        for(int i=1; i<=n; ++i){
            if(distance[i]==-1){
                visited[i]=0;
                to_visit.push(i);
            }
            else visited[i]=1;
        }
        
        int groups=1;
        while(!to_visit.empty()){
            if(!visited[to_visit.front()]){
                vertices.push(to_visit.front());
                to_visit.pop();
                
                while(!vertices.empty()){
                    int k=vertices.front();
                    vertices.pop();
                    visited[k]=1;
                    for(unsigned i=0; i<site[k].size(); ++i){
                        int x=site[k][i];
                        if(!visited[x]) vertices.push(x);
                    }
                }
                
                ++groups;
            }
            else to_visit.pop();
        }
        
        cout<<"Znajomi numeru "<<my_number<<":\n";
        for(int i=1; i<=n; ++i){
            if(i!=my_number && distance[i]!=-1)
                cout<<i<<": "<<distance[i]<<"\n";
        }
        
        cout<<"Grup znajomych jest "<<groups<<".\n";
    }
    
    return 0;
}
