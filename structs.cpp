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

using namespace std;

typedef int64_t ll;
typedef uint64_t ull;
typedef __int128_t bll;


// left + right in one object for vector<LR>
struct LR {
    int l, r;
	LR(int varL, int varR) {
		l = varL;
		r = varR;
	}
};


// value + two added characteristics used in minMaxQueue
struct valMinMax {
    int val, minV, maxV;
    valMinMax(int v, int mi, int ma) {
        val = v;
        minV = mi;
        maxV = ma;
    }
};

// queue with getting min and max for O(1)
struct minMaxQueue {
    stack<valMinMax> s1, s2;
    bool empty() {
        return s1.size() + s2.size() == 0;
    }
    unsigned size() {
        return s1.size() + s2.size();
    }
    void push(int val) {
        if (s1.empty()) {
            s1.push(valMinMax(val, val, val));
        } else {
            s1.push(valMinMax(val, min(val, s1.top().minV), max(val, s1.top().maxV)));
        }
    }
    void relocate() {
        while (!s1.empty()) {
            auto elem = s1.top();
            s1.pop();
            if (s2.empty()) {
                s2.push(valMinMax(elem.val, elem.val, elem.val));
            } else {
                s2.push(valMinMax(elem.val, min(elem.val, s2.top().minV), max(elem.val, s2.top().maxV)));
            }
        }
    }
    void pop() {
        if (s2.empty()) {
            relocate();
        }
        s2.pop();
    }
    int front() {
        if (s2.empty()) {
            relocate();
        }
        return s2.top().val;
    }
    int minElem() {
        if (s2.empty()) {
            return s1.top().minV;
        } else if (s1.empty()) {
            return s2.top().minV;
        } else {
            return min(s1.top().minV, s2.top().minV);
        }
    }
    int maxElem() {
        if (s2.empty()) {
            return s1.top().maxV;
        } else if (s1.empty()) {
            return s2.top().maxV;
        } else {
            return max(s1.top().maxV, s2.top().maxV);
        }
    }
};




int main() {
    ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
    

    return 0;
}