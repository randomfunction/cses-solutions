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
        tree[node]= min(tree[2*node+1], tree[2*node+2]);
    }

    ll querymin(ll s, ll e, ll l ,ll r, ll node){
        if(s>r||e<l){
            return LLONG_MAX; 
        }
        if(s>=l&&e<=r){
            return tree[node];
        }

        ll m= (s+e)/2;
        ll lm= querymin(s,m,l,r,2*node+1);
        ll rm= querymin(m+1,e,l,r,2*node+2);
        return min(lm,rm);
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
        tree[node]= min(tree[2*node+1], tree[2*node+2]);
    }

    public:
    SegmentTree(vector<ll> &arr){
        n= arr.size();
        tree.resize(4*n, LLONG_MAX);
        buildTree(arr, 0, n-1, 0);
    }

    ll query(ll l,ll r){
        return querymin(0, n-1, l, r, 0);
    }

    void update(ll i, ll k){
        updateTree(0, n-1, i, k, 0);
    }
};

class MinSqrtDc{
    private:
    vector<ll> arr;
    vector<ll> block;
    ll blocksize;

    public:
    MinSqrtDc(vector<ll> arr){
        this->arr=arr;
        ll n=arr.size();
        blocksize = static_cast<ll>(sqrt(n)) + 1;
        block.assign(blocksize, LLONG_MAX);
        for (ll i = 0; i < n; ++i) {
            block[i / blocksize] = min(block[i / blocksize], arr[i]);
        }
    }

    void update(ll idx, ll value) {
        ll blockIdx = idx / blocksize;
        arr[idx] = value;
        block[blockIdx] = LLONG_MAX;
        ll start = blockIdx * blocksize;
        ll end = min(static_cast<ll>(arr.size()), (blockIdx + 1) * blocksize);
        for (ll i = start; i < end; ++i) {
            block[blockIdx] = min(block[blockIdx], arr[i]);
        }
    }

    ll query(ll l, ll r) {
        ll minVal = LLONG_MAX;
        while (l < r && l % blocksize != 0) {
            minVal = min(minVal, arr[l]);
            ++l;
        }
        while (l + blocksize <= r) {
            minVal = min(minVal, block[l / blocksize]);
            l += blocksize;
        }
        while (l <= r) {
            minVal = min(minVal, arr[l]);
            ++l;
        }
        return minVal;
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

    SegmentTree minst(x);
    MinSqrtDc sqrt(x);
    

    for(auto it: mp){
        cout << minst.query(it.first, it.second) << endl;
        // cout<<sqrt.query(it.first, it.second)<<endl; ->> TLE on 2nd test
    }
    return 0;
}
