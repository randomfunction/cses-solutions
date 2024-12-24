// BIPARTITE GRAPH
#include<bits/stdc++.h>
using namespace std;
using ll= long long;

int main(){
    ll n,m; cin>>n>>m;
    vector<vector<ll>> G(n+1);
    for(int i=0;i<m;i++){
        ll a,b; cin>>a>>b;
        G[a].push_back(b);
        G[b].push_back(a); 
    }
    vector<ll> T(n+1,0); // 0-> unvis, 1-> TEAM1, 2-> TEAM2
    for(int i=1;i<=n;i++){
        if(T[i]==0){
            queue<ll> q;
            q.push(i);
            T[i]=1;
            while(!q.empty()){
                ll node= q.front();
                q.pop();
                for(auto it:G[node]){
                    if(T[it]==0){
                    T[it]= 3-T[node];
                    q.push(it);
                    }
                    else if(T[it]== T[node]){
                        cout<<"IMPOSSIBLE"<<endl;
                        return 0;
                    }
                }

            }
        }
    }
    for(int i=1;i<=n;i++){
        cout<<T[i]<<" ";
    }
    cout<<endl;
    return 0;
}