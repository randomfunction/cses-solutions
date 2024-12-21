#include <bits/stdc++.h>
using namespace std;

using ll = long long;

class SegmentTree {
private:
    vector<ll> tree, lazy;
    ll n;
    void pushdown(ll node, ll s, ll e) {
        if (lazy[node] != 0) {
            tree[node] += (e - s + 1) * lazy[node];  
            if (s != e) {  
                lazy[node * 2 + 1] += lazy[node];
                lazy[node * 2 + 2] += lazy[node];
            }
            lazy[node] = 0;  
        }
    }
    void buildTree(vector<ll> &arr, ll s, ll e, ll node) {
        if (s == e) {
            tree[node] = arr[s];
            return;
        }
        ll mid = (s + e) / 2;
        buildTree(arr, s, mid, 2 * node + 1);
        buildTree(arr, mid + 1, e, 2 * node + 2);
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }

    void updateRange(ll node, ll s, ll e, ll l, ll r, ll value) {
        pushdown(node, s, e); 
        if (s > r || e < l)  
            return;
        if (s >= l && e <= r) {  
            lazy[node] += value;
            pushdown(node, s, e);
            return;
        }
        ll mid = (s + e) / 2;
        updateRange(2 * node + 1, s, mid, l, r, value);
        updateRange(2 * node + 2, mid + 1, e, l, r, value);
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }

    ll ValueAtK(ll node, ll s, ll e, ll k) {
        pushdown(node, s, e); 
        if (s == e)  
            return tree[node];

        ll mid = (s + e) / 2;
        if (k <= mid)
            return ValueAtK(2 * node + 1, s, mid, k);
        else
            return ValueAtK(2 * node + 2, mid + 1, e, k);
    }

public:
    SegmentTree(vector<ll> &arr) {
        n = arr.size();
        tree.resize(4 * n, 0);
        lazy.resize(4 * n, 0);
        buildTree(arr, 0, n - 1, 0);
    }

    void updaterange(ll l, ll r, ll value) {
        updateRange(0, 0, n - 1, l, r, value);
    }

    ll query(ll idx) {
        return ValueAtK(0, 0, n - 1, idx);
    }
};

int main() {
    ll n, q;
    cin >> n >> q;
    vector<ll> x(n);
    for (int i = 0; i < n; i++)
        cin >> x[i];

    SegmentTree sumst(x);
    for (int i = 0; i < q; i++) {
        ll c;
        cin >> c;
        if (c == 1) {
            ll a, b, u;
            cin >> a >> b >> u;
            a--; b--; 
            sumst.updaterange(a, b, u);
        } else {
            ll k;
            cin >> k;
            k--; 
            cout << sumst.query(k) << endl;
        }
    }

    return 0;
}
