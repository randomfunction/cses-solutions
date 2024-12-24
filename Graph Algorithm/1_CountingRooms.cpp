#include<bits/stdc++.h>

using namespace std;
using ll= long long;
void dfs(ll x,ll y, vector<vector<char>> &grid,vector<vector<bool>> &vis){
    ll n= grid.size(), m= grid[0].size();
    if(x<0||y<0||x>=n||y>=m||vis[x][y]||grid[x][y]=='#') return;
    vis[x][y]=true;
    dfs(x+1,y,grid,vis);
    dfs(x,y+1,grid,vis);
    dfs(x-1,y,grid,vis);
    dfs(x,y-1,grid,vis);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n,m;
    cin>>n>>m;
    vector<vector<char>> grid(n, vector<char>(m));
    vector<vector<bool>> vis(n, vector<bool>(m,false));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>grid[i][j];
        }
    }
    int c=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(grid[i][j]=='.'&&vis[i][j]==0){
                dfs(i,j,grid,vis);
                c++;
            }
        }
    }
    cout<<c<<endl;
    return 0;
}