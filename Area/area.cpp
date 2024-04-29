#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

struct Circle {
    double x, y, r;
};

struct Point {
    double x, y;
};

vector<Point> intersect(const Circle& c1, const Circle& c2) {
    vector<Point> points;
    double d = sqrt(pow(c1.x - c2.x, 2) + pow(c1.y - c2.y, 2));
    if (d > c1.r + c2.r || d < fabs(c1.r - c2.r) || d == 0) {
        return points; // No intersection or same circle
    }

    double a = (c1.r * c1.r - c2.r * c2.r + d * d) / (2 * d);
    double h = sqrt(c1.r * c1.r - a * a);
    double px = c1.x + a * (c2.x - c1.x) / d;
    double py = c1.y + a * (c2.y - c1.y) / d;

    // Intersection points
    double x1 = px + h * (c2.y - c1.y) / d;
    double y1 = py - h * (c2.x - c1.x) / d;
    double x2 = px - h * (c2.y - c1.y) / d;
    double y2 = py + h * (c2.x - c1.x) / d;

    points.push_back({x1, y1});
    if (x1 != x2 || y1 != y2) {
        points.push_back({x2, y2});
    }
    return points;
}

double triangle_area(const Point& p1, const Point& p2, const Point& p3) {
    return 0.5 * abs(p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y));
}

int main() {
    ifstream fin("1.inp");
    ofstream fout("1.txt");
    int T;
    fin >> T;
    fout << fixed << setprecision(2);

    while (T--) {
        Circle circles[3];
        for (int i = 0; i < 3; ++i) {
            fin >> circles[i].x >> circles[i].y >> circles[i].r;
        }

        vector<Point> points;
        for (int i = 0; i < 3; ++i) {
            for (int j = i + 1; j < 3; ++j) {
                vector<Point> pts = intersect(circles[i], circles[j]);
                points.insert(points.end(), pts.begin(), pts.end());
            }
        }

        // Assuming points form a valid triangle (for simplification)
        if (points.size() == 3) {
            double area = triangle_area(points[0], points[1], points[2]);
            fout << area << endl;
        } else {
            fout << "0.00" << endl;
        }
    }

    fin.close();
    fout.close();
    return 0;
}
