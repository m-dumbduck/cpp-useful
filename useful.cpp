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
#include <chrono>

using namespace std;

typedef int64_t ll;
typedef uint64_t ull;
typedef __int128_t bll;

using TimePoint = chrono::time_point<chrono::system_clock>;

class Timer {
    private:
        TimePoint begin;
        string hint;
    public:
        Timer() {
            begin = chrono::system_clock::now();
        }
        Timer(string hint) {
            this->hint = hint;
            begin = chrono::system_clock::now();
        }
        ~Timer() {
            cout << hint << " " << (chrono::system_clock::now() - begin) / 1ms;
        }
};


int main() {

    return 0;
}