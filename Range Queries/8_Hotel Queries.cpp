#include <bits/stdc++.h>
using namespace std;

struct Vertex {
    int value;
    int index;
};

class SegmentTree {
private:
    vector<Vertex> tree;
    int size;

    void build(vector<int>& a, int v, int tl, int tr) {
        if (tl == tr) {
            tree[v].value = a[tl];
            tree[v].index = tl + 1;
            return;
        }
        int mid = (tl + tr) / 2;
        build(a, 2 * v, tl, mid);
        build(a, 2 * v + 1, mid + 1, tr);
        if (tree[2 * v].value >= tree[2 * v + 1].value) {
            tree[v] = tree[2 * v];
        } else {
            tree[v] = tree[2 * v + 1];
        }
    }

    int query(int v, int tl, int tr, int num) {
        if (tree[v].value < num)
            return 0;

        if (tl == tr) {
            tree[v].value -= num;
            return tree[v].index;
        }

        int mid = (tl + tr) / 2;
        int idx;
        if (tree[2 * v].value >= num) {
            idx = query(2 * v, tl, mid, num);
        } else {
            idx = query(2 * v + 1, mid + 1, tr, num);
        }

        if (tree[2 * v].value >= tree[2 * v + 1].value) {
            tree[v] = tree[2 * v];
        } else {
            tree[v] = tree[2 * v + 1];
        }

        return idx;
    }

public:
    SegmentTree(vector<int>& a) {
        size = a.size();
        tree.resize(4 * size);
        build(a, 1, 0, size - 1);
    }

    int query(int num) {
        return query(1, 0, size - 1, num);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector<int> h(n), r(m);
    for (int i = 0; i < n; i++) cin >> h[i];
    for (int i = 0; i < m; i++) cin >> r[i];

    SegmentTree segmentTree(h);

    for (int i = 0; i < m; i++) {
        cout << segmentTree.query(r[i]) << " ";
    }
    return 0;
}
