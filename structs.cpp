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


// Queue supporting characteristic (function must not be overloaded)
template <typename T>
struct valCh {
    T val, ch;
    valCh(T v, T nch) {
        val = v, ch = nch;
    }
};

template <typename T>
struct ChQueue {
    stack<valCh<T>> s1, s2;
    function<T(T, T)> func;
    ChQueue<T>() = default;
    explicit ChQueue<T>(function<T(T, T)> f) {
        func = f;
    }
    bool empty() {
        return s1.size() + s2.size() == 0;
    }
    unsigned size() {
        return s1.size() + s2.size();
    }
    void push(T val) {
        if (s1.empty()) {
            s1.push(valCh<T>(val, val));
        } else {
            s1.push(valCh<T>(val, func(val, s1.top().ch)));
        }
    }
    void relocate() {
        while (!s1.empty()) {
            auto elem = s1.top();
            s1.pop();
            if (s2.empty()) {
                s2.push(valCh<T>(elem.val, elem.val));
            } else {
                s2.push(valCh<T>(elem.val, func(elem.val, s2.top().ch)));
            }
        }
    }
    void pop() {
        if (s2.empty()) {
            relocate();
        }
        s2.pop();
    }
    T front() {
        if (s2.empty()) {
            relocate();
        }
        return s2.top().val;
    }
    T funcRes() {
        if (s2.empty()) {
            return s1.top().ch;
        } else if (s1.empty()) {
            return s2.top().ch;
        } else {
            return func(s1.top().ch, s2.top().ch);
        }
    }
};




int main() {
    ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
    

    return 0;
}
