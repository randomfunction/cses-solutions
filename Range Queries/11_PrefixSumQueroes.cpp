#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
class SegmentTree{ 
    private:
    vector<ll> tree;
    ll n;

    void buildTree(vector<ll> &arr, ll s, ll e, ll node){
        if(s==e){
            tree[node]=arr[s];
            return ;
        }

        ll m= (s+e)/2;
        buildTree(arr, s, m, 2*node+1);
        buildTree(arr, m+1, e, 2*node+2);
        ll l= tree[2*node+1];
        ll r= tree[2*node+2];
        tree[node]= max({l,r,l+r});
    }

    ll querysum(ll s, ll e, ll l ,ll r, ll node){
        if(s>r||e<l){
            return 0;
        }
        if(s>=l&&e<=r){
            return tree[node];
        }

        ll m= (s+e)/2;
        ll lm= querysum(s,m,l,r,2*node+1);
        ll rm= querysum(m+1,e,l,r,2*node+2);
        return max({lm,rm,lm+rm});
    }

    void updateTree(ll s, ll e, ll i, ll k, ll node){
        if(s==e){
            tree[node]=k;
            return;
        }
        ll m= (s+e)/2;
        if(i<=m){
            updateTree(s,m,i,k,2*node+1);
        }
        else{
            updateTree(m+1,e,i,k,2*node+2);
        }
        ll l= tree[2*node+1];
        ll r= tree[2*node+2];
        tree[node]= max({l,r,l+r});
    }

    void debug(){
        for(auto it:tree){
            cout<<it<<" ";
        }
        cout<<endl;
    }

    public:
    SegmentTree(vector<ll> &arr){
        n= arr.size();
        tree.resize(4*n,0);
        buildTree(arr,0,n-1,0);
    }

    ll query(ll l,ll r){
        return querysum(0,n-1,l,r,0);
    }

    void update(ll i, ll k){
        updateTree(0,n-1,i,k,0);
    }

    void Debug(){
        debug();
    }
};


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ll n, q;
    cin >> n >> q;

    vector<ll> x(n);
    for(int i = 0; i < n; i++){
        cin >> x[i];
    }

    SegmentTree tree(x);

    while(q--){
        ll c,a,b;
        cin>>c>>a>>b;

        if(c==1){
            tree.update(a--,b);
            // tree.Debug();
        }
        else{
            cout<<tree.query(a--,b--)<<endl;
            // tree.Debug();
        }
    }
}
