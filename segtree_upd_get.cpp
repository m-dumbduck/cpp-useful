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
typedef pair<int, int> pii;

struct base {
    int val = 0;
    int push = -1;
    base(int val1) {
        val = val1;
    }
};

vector<base> tree;

base NEUTRAL = {0};

base merge(base a, base b) {
    return {a.val + b.val};
}

void build(int v, int l, int r, vector<int>& a) {
    if (l == r - 1) {
        tree[v] = {a[l]};
        return;
    }
    int m = (l + r) / 2;
    build(2 * v + 1, l, m, a);
    build(2 * v + 2, m, r, a);
    tree[v] = merge(tree[2 * v + 1], tree[2 * v + 2]);
}

void push(int v, int tl, int tr) {
    if (tree[v].push == -1) {
        return;
    }
    if (tl + 1 == tr) {
        tree[v].val = tree[v].push;
    }
    else {
        tree[v].val = (tr - tl) * tree[v].push;
        tree[2 * v + 1].push = tree[v].push;
        tree[2 * v + 2].push = tree[v].push;
    }
    tree[v].push = -1;
}

void upd(int v, int tl, int tr, int ql, int qr, int x) {
    push(v, tl, tr);
    if (tl >= qr || ql >= tr) {
        return;
    }
    if (ql <= tl && tr <= qr) {
        tree[v].push = x;
        push(v, tl, tr);
        return;
    }
    int tm = (tl + tr) / 2;
    upd(2 * v + 1, tl, tm, ql, qr, x);
    upd(2 * v + 2, tm, tr, ql, qr, x);
    tree[v] = merge(tree[2 * v + 1], tree[2 * v + 2]);
}

base getOne(int v, int tl, int tr, int pos) {
    push(v, tl, tr);
    if (tl + 1 == tr) {
        return tree[v];
    }
    int tm = (tl + tr) / 2;
    if (pos <= tm) {
        return getOne(2 * v + 1, tl, tm, pos);
    }
    else {
        return getOne(2 * v + 2, tm, tr, pos);
    }
}

base get(int v, int l, int r, int ql, int qr) {
    push(v, l, r);
    if (ql <= l && qr >= r) {
        return tree[v];
    }
    if (l > qr || r < ql) {
        return NEUTRAL;
    }
    int m = (l + r) / 2;
    return merge(get( 2 * v + 1, l, m, ql, qr), get(2 * v + 2, m, r, ql, qr));
}