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

typedef int64_t ll;
typedef uint64_t ull;
typedef __int128_t bll;

const double EPS = 1e-8;
const double PI = acos(-1);

bool IsEqual(double x, double y) {
    return abs(x - y) < EPS;
}
bool IsMore(double x, double y) {
    return x - y > EPS;
}
bool IsLess(double x, double y) {
    return y - x > EPS;
}

struct pt {
    double x = 0;
    double y = 0;
    pt() {
    }
    pt(double x1, double y1) {
        x = x1, y = y1;
    }
    pt(pt pt1, pt pt2) {
        x = pt2.x - pt1.x, y = pt2.y - pt1.y;
    }
    bool operator==(pt other) const {
        return x == other.x && y == other.y;
    }
    pt operator+(pt other) const {
        return {x + other.x, y + other.y};
    }
    pt operator-(pt other) const {
        return {x - other.x, y - other.y};
    }
    pt operator*(double d) const {
        return {x * d, y * d};
    }
    double operator^(pt other) const {
        return x * other.y - y * other.x;
    }
    double operator*(pt other) const {
        return x * other.x + y * other.y;
    }
    double LenSquared() const {
        return x * x + y * y;
    }
    double Len() const {
        return sqrt(LenSquared());
    }
};

istream &operator>>(istream &in, pt &p) {
    in >> p.x >> p.y;
    return in;
}
ostream &operator<<(ostream &out, pt p) {
    out << setprecision(15) << p.x << " " << p.y;
    return out;
}

struct Line {
    double a;
    double b;
    double c;
    Line(double a1, double b1, double c1) {
        a = a1;
        b = b1;
        c = c1;
    }
    Line(pt p1, pt p2) {
        a = p2.y - p1.y, b = p1.x - p2.x, c = p2.x * p1.y - p1.x * p2.y;
    }
    Line(double k1, double b1) {
        a = k1, b = -1, c = b1;
    }
    Line PerpendicularLine(pt point) const {
        return {-b, a, b * point.x - a * point.y};
    }
    int PointHalfPlain(pt point) const {
        if (IsEqual(a * point.x + b * point.y + c, 0)) {
            return 0;
        } else if (a * point.x + b * point.y + c > 0) {
            return 1;
        } else {
            return -1;
        }
    }
    double DistToPoint(pt p) const {
        return abs(a * p.x + b * p.y + c) / sqrt(a * a + b * b);
    }
    pt LineIntersect(Line other) const {
        return {(b * other.c - other.b * c) / (a * other.b - b * other.a),
                (other.c * a - c * other.a) / (b * other.a - other.b * a)};
    }
};
 
int main() {
    
}
