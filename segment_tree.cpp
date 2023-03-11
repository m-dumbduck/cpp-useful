#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
#include <chrono>
#include <set>
#include <deque>
#include <stack>
#include <iomanip>
#include <cmath>

using namespace std;

#define setpr setprecision(15)

typedef int64_t ll;
typedef uint64_t ull;
typedef __int128_t bll;


int N;
vector<int> tree;
int NEUTRAL = 0;

int merge(int v1, int v2) {
    return v1 + v2;
}

void buildTree(int v, int l, int r, vector<int>& a) {
    if (l == r - 1) {
        tree[v] = a[l];
        return;
    }
    int m = (l + r) / 2;
    buildTree(2 * v + 1, l, m, a);
    buildTree(2 * v + 2, m, r, a);
    tree[v] = merge(tree[2 * v + 1], tree[2 * v + 2]);
}

int getOneTree(int v, int l, int r, int pos) {
    if (l == r - 1) {
        return tree[v];
    }
    int m = (l + r) / 2;
    if (m > pos) {
        return getOneTree(v * 2 + 1, l, m, pos);
    } else {
        return getOneTree(v * 2 + 2, m, r, pos);
    }
}

int getTree(int v, int l, int r, int ql, int qr) {
    if (ql <= l && qr >= r) {
        return tree[v];
    }
    if (l >= qr || r <= ql) {
        return NEUTRAL;
    }
    int m = (l + r) / 2;
    return merge(getTree( 2 * v + 1, l, m, ql, qr), getTree(2 * v + 2, m, r, ql, qr));
}

void updTree(int v, int l, int r, int pos, int val) {
    if (l == r - 1) {
        tree[v] += val;
        return;
    }
    int m = (l + r) / 2;
    if (m > pos) {
        updTree(v * 2 + 1, l, m, pos, val);
    } else {
        updTree(v * 2 + 2, m, r, pos, val);
    }
    tree[v] = merge(tree[2 * v + 1], tree[2 * v + 2]);
}

void build(vector<int>& vec) { N = vec.size(); tree.resize(4 * N, NEUTRAL); buildTree(0, 0, N, vec); }
int getOne(int pos) { return getOneTree(0, 0, N, pos); }
int get(int ql, int qr) { return getTree(0, 0, N, ql, qr); }
void upd(int pos, int val) { updTree(0, 0, N, pos, val); }



int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);


    return 0;
}
