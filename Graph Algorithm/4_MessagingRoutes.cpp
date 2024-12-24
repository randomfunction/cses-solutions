#include<bits/stdc++.h>
using namespace std;

int main(){
    long long n,m;
    cin>>n>>m;
    vector<vector<long long>> G(n+1);
    for(long long i=0;i<m;i++){
        long long a,b;
        cin>>a>>b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    vector<long long> parent(n+1,-1);
    vector<bool> vis(n+1,false);
    queue<long long> q;
    vis[1]=true;
    q.push(1);
    while(!q.empty()){
        long long node= q.front();
        q.pop();
        for(auto it:G[node]){
            if(vis[it]==0){
                vis[it]=true;
                parent[it]=node;
                q.push(it);
            }
        }
    }
    if(!vis[n]){ cout<<"IMPOSSIBLE"; return 0;}
    //reconstruct path
    vector<long long> path;
    for(long long i=n;i!=-1;i=parent[i]){
        path.push_back(i);
    }
    reverse(path.begin(),path.end());
    cout<<path.size()<<endl;
    for(auto it:path){
        cout<<it<<" ";
    }
    cout<<endl;
    return 0;
}