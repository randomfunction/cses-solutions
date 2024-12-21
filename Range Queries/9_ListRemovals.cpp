#include <bits/stdc++.h>
using namespace std;

using ll = long long;

class FenwickTree {
private:
    vector<ll> tree;
    ll n;

public:
    FenwickTree(ll size) {
        n = size;
        tree.resize(n + 1, 0);
    }

    void update(ll idx, ll delta) {
        while (idx <= n) {
            tree[idx] += delta;
            idx += idx & -idx;
        }
    }

    ll sum(ll idx) {
        ll r = 0;
        while (idx > 0) {
            r += tree[idx];
            idx -= idx & -idx;
        }
        return r;
    }

    ll find(ll k) {
        ll idx = 0, bitMask = 1;
        while (bitMask <= n) bitMask <<= 1;
        for (ll i = bitMask >> 1; i > 0; i >>= 1) {
            if (idx + i <= n && tree[idx + i] < k) {
                k -= tree[idx + i];
                idx += i;
            }
        }
        return idx + 1;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll n;
    cin >> n;
    vector<ll> x(n), p(n);

    for (ll i = 0; i < n; i++) cin >> x[i];
    for (ll i = 0; i < n; i++) cin >> p[i];

    FenwickTree fenwick(n);
    for (ll i = 1; i <= n; i++) fenwick.update(i, 1);

    vector<ll> r;
    for (ll i = 0; i < n; i++) {
        ll pos = fenwick.find(p[i]);
        r.push_back(x[pos - 1]);
        fenwick.update(pos, -1);
    }

    for (ll num : r) cout << num << " ";
    return 0;
}
