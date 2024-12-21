#include <iostream>
#include <vector>
using namespace std;

class SegmentTree2D {
private:
    vector<vector<int>> tree;
    int n;

    void buildY(const vector<vector<int>>& matrix, int x1, int x2, int y1, int y2, int nodeX, int nodeY) {
        if (y1 == y2) {
            if (x1 == x2) {
                tree[nodeX][nodeY] = matrix[x1][y1];
            } else {
                tree[nodeX][nodeY] = tree[2 * nodeX + 1][nodeY] + tree[2 * nodeX + 2][nodeY];
            }
            return;
        }

        int midY = (y1 + y2) / 2;
        buildY(matrix, x1, x2, y1, midY, nodeX, 2 * nodeY + 1);
        buildY(matrix, x1, x2, midY + 1, y2, nodeX, 2 * nodeY + 2);

        tree[nodeX][nodeY] = tree[nodeX][2 * nodeY + 1] + tree[nodeX][2 * nodeY + 2];
    }

    void buildX(const vector<vector<int>>& matrix, int x1, int x2, int y1, int y2, int nodeX) {
        if (x1 == x2) {
            buildY(matrix, x1, x2, y1, y2, nodeX, 0);
            return;
        }

        int midX = (x1 + x2) / 2;
        buildX(matrix, x1, midX, y1, y2, 2 * nodeX + 1);
        buildX(matrix, midX + 1, x2, y1, y2, 2 * nodeX + 2);

        for (int j = 0; j < 4 * n; ++j) {
            tree[nodeX][j] = tree[2 * nodeX + 1][j] + tree[2 * nodeX + 2][j];
        }
    }

    int queryY(int x1, int x2, int y1, int y2, int qy1, int qy2, int nodeX, int nodeY) {
        if (y1 > qy2 || y2 < qy1) return 0;
        if (y1 >= qy1 && y2 <= qy2) return tree[nodeX][nodeY];

        int midY = (y1 + y2) / 2;
        return queryY(x1, x2, y1, midY, qy1, qy2, nodeX, 2 * nodeY + 1) +
               queryY(x1, x2, midY + 1, y2, qy1, qy2, nodeX, 2 * nodeY + 2);
    }

    int queryX(int x1, int x2, int y1, int y2, int qx1, int qx2, int qy1, int qy2, int nodeX) {
        if (x1 > qx2 || x2 < qx1) return 0;
        if (x1 >= qx1 && x2 <= qx2) return queryY(x1, x2, y1, y2, qy1, qy2, nodeX, 0);

        int midX = (x1 + x2) / 2;
        return queryX(x1, midX, y1, y2, qx1, qx2, qy1, qy2, 2 * nodeX + 1) +
               queryX(midX + 1, x2, y1, y2, qx1, qx2, qy1, qy2, 2 * nodeX + 2);
    }

public:
    SegmentTree2D(const vector<vector<int>>& matrix) {
        n = matrix.size();
        tree.resize(4 * n, vector<int>(4 * n, 0));
        buildX(matrix, 0, n - 1, 0, n - 1, 0);
    }

    int query(int x1, int x2, int y1, int y2) {
        return queryX(0, n - 1, 0, n - 1, x1, x2, y1, y2, 0);
    }
};

int main() {
    int n, q;
    cin >> n >> q;
    vector<vector<int>> matrix(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        string row;
        cin >> row;
        for (int j = 0; j < n; j++) {
            matrix[i][j] = (row[j] == '*') ? 1 : 0;
        }
    }
    SegmentTree2D segTree(matrix);
    while (q--) {
        int y1, x1, y2, x2;
        cin >> y1 >> x1 >> y2 >> x2;
        y1--; x1--; y2--; x2--;
        cout << segTree.query(y1, y2, x1, x2) << endl;
    }

    return 0;
}
