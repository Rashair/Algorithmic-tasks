#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    
    int Z;
    cin>>Z;
    
    while(Z--){
        int m,n;
        cin>>m>>n;
        
        char dungeon[m][n];
        pair <int, int> sorc;
        pair <int, int> out;
        vector <pair <int, int> > input;
        
        for(int i=0; i<m; ++i){
            for(int j=0; j<n; ++j){
                cin>>dungeon[i][j];
                
                if(dungeon[i][j]=='@'){
                    sorc.first=i;
                    sorc.second=j;
                }
                else if(dungeon[i][j]=='>'){
                    out.first=i;
                    out.second=j;
                }
                
                if(dungeon[i][j]!='#'){
                    if(i>0)
                        if(dungeon[i-1][j]!='#') input.push_back(make_pair((i-1)*n+j , i*n+j));
                    if(j>0)
                        if(dungeon[i][j-1]!='#') input.push_back(make_pair(i*n+j-1 , i*n+j));
                }
            }
        }
        
        vector <int> way[n*m+n];
        for(const auto &ver : input){
           way[ver.first].push_back(ver.second);
           way[ver.second].push_back(ver.first);
        }

        int distance[n*m+n];
        memset(distance,-1,sizeof(distance));
        distance[sorc.first*n+sorc.second]=0;
        queue <int> vertices;
        vertices.push(sorc.first*n+sorc.second);

        int maze_exit=out.first*n+out.second;
        while(!vertices.empty() && vertices.front()!=maze_exit){
            int k=vertices.front();
            vertices.pop();
            for(unsigned i=0; i<way[k].size(); ++i){
                int x=way[k][i];
                if(distance[x]==-1){
                    distance[x]=distance[k]+1;
                    vertices.push(x);
                }
            }
        }
        
        int t=distance[maze_exit];
        if(t!=-1) cout<<t<<"\n";
        else cout<<"NIE"<<"\n";
    }
    
    return 0;
}
