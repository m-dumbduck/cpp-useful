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
    Line() {}
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
    bool IsParallel(Line other) const {
        return a * other.b == b * other.a;
    }
    double DistToLine(Line other) const {
        if (this->IsParallel(other)) {
            pt point;
            if (b != 0) {
                point = pt(1, (-a - c) / b);
            } else {
                point = pt((-b - c) / a, 1);
            }
            return other.DistToPoint(point);
        }
        return 0;
    }
};

struct Ray {
    pt f, s;
    Line line;
    Ray() {}
    Ray(pt first, pt second) {
        f = first, s = second, line = Line(first, second);
    }
    double DistToPoint(pt point) const {
        Line perpLineF = line.PerpendicularLine(f);
        pt cross = line.LineIntersect(line.PerpendicularLine(point));
        if (perpLineF.PointHalfPlain(s) == perpLineF.PointHalfPlain(cross) ||
            perpLineF.PointHalfPlain(f) == perpLineF.PointHalfPlain(cross)) {
            return pt(cross, point).Len();
        } else {
            return pt(f, point).Len();
        }
    }
    bool HasRayIntersection(Ray other) const {
        pt cross = line.LineIntersect(other.line);
        Line thisPerpLineF = line.PerpendicularLine(f),
                otherPerpLineF = other.line.PerpendicularLine(other.f);
        return ((thisPerpLineF.PointHalfPlain(cross) == thisPerpLineF.PointHalfPlain(s) ||
                thisPerpLineF.PointHalfPlain(cross) == thisPerpLineF.PointHalfPlain(f)) &&
                (otherPerpLineF.PointHalfPlain(cross) == otherPerpLineF.PointHalfPlain(other.s) ||
                 otherPerpLineF.PointHalfPlain(cross) == otherPerpLineF.PointHalfPlain(other.f)));
    }
    bool HasLineIntersection(Line l) const {
        pt cross = line.LineIntersect(l);
        Line thisPerpLineF = line.PerpendicularLine(f);
        return (thisPerpLineF.PointHalfPlain(cross) == thisPerpLineF.PointHalfPlain(s) ||
                thisPerpLineF.PointHalfPlain(cross) == thisPerpLineF.PointHalfPlain(f));
    }
    double DistToRay(Ray other) const {
        if (this->HasRayIntersection(other)) {
            return 0;
        }
        return min(this->DistToPoint(other.f), other.DistToPoint(f));
    }
    double DistToLine(Line l) const {
        if (this->HasLineIntersection(l)) {
            return 0;
        }
        return l.DistToPoint(f);
    }
};

struct Segment {
    pt f, s;
    Line line;
    Segment() {}
    Segment(pt f1, pt s1) {
        f = f1, s = s1, line = Line(f1, s1);
    }
    double DistToPoint(pt point) const {
        pt cross = line.LineIntersect(line.PerpendicularLine(point));
        if (pt(cross, f).Len() <= pt(f, s).Len() &&
            pt(cross, s).Len() <= pt(f, s).Len()) {
            return pt(cross, point).Len();
        } else {
            return min(pt(point, f).Len(), pt(point, s).Len());
        }
    }
    bool HasSegmentIntersection(Segment other) const {
        Ray r1 = Ray(f, s), r2 = Ray(s, f), r3 = Ray(other.f, other.s),
                    r4 = Ray(other.s, other.f);
        return r1.HasRayIntersection(r3) && r1.HasRayIntersection(r4) &&
                r2.HasRayIntersection(r3) && r2.HasRayIntersection(r4);
    }
    bool HasRayIntersection(Ray ray) const {
        Ray r1 = Ray(f, s), r2 = Ray(s, f);
        return r1.HasRayIntersection(ray) && r2.HasRayIntersection(ray);
    }
    bool HasLineIntersection(Line l) const {
        Ray r1 = Ray(f, s), r2 = Ray(s, f);
        return r1.HasLineIntersection(l) && r2.HasLineIntersection(l);
    }
    double DistToSegment(Segment other) const {
        if (this->HasSegmentIntersection(other)) {
            return 0;
        }
        return min(min(this->DistToPoint(other.f), this->DistToPoint(other.s)),
                    min(other.DistToPoint(f), other.DistToPoint(s)));
    }
    double DistToRay(Ray ray) const {
        if (this->HasRayIntersection(ray)) {
            return 0;
        }
        return min(min(ray.DistToPoint(f), ray.DistToPoint(s)), this->DistToPoint(ray.f));
    }
    double DistToLine(Line l) const {
        if (this->HasLineIntersection(l)) {
            return 0;
        }
        return min(l.DistToPoint(f), l.DistToPoint(s));
    }
};
 
int main() {
    
}
