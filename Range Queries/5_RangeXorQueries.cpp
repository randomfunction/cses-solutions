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
        tree[node]= tree[2*node+1]^ tree[2*node+2];
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
        return lm^rm;
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
        tree[node]=tree[2*node+1]^ tree[2*node+2];
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

    vector<pair<ll,ll>> mp;
    for(int i = 0; i < q; i++){
        ll a, b;
        cin >> a >> b;
        mp.push_back({a-1, b-1});
    }

    SegmentTree xorst(x);

    for(auto it: mp){
        cout << xorst.query(it.first, it.second) << endl;
    }
    return 0;
}
