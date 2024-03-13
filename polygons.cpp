#include <iostream>
#include <random>
#include <list>
#include <vector>
#include <algorithm>
#define border 1000
#define eps 1E-8

struct Point2d
{
	double x, y;

    bool operator== (Point2d b)
    {
        return (this->x == b.x && this->y == b.y);
    }
};
struct Line
{
	double a, b, c;
};
struct Segment
{
	Point2d start, finish;
};
//it is also necessary to check that 3 points do not belong to one line
std::vector <std::vector <Point2d>> GenerateTriangles(uint32_t numOfTriangles)
{
	std::srand(0);
	std::vector <std::vector <Point2d>> Triangles;
	for (int i = 0; i < numOfTriangles; ++i)
	{
		std::vector <Point2d> tempList;
		uint32_t vertexes = 3;
		for (int k = 1; k <= vertexes; ++k)
		{
			Point2d temp;
			temp.x = rand() % (10 - 0 + 1) - 10;
			temp.y = rand() % (10 - 0 + 1) - 10;
			tempList.push_back(temp);
		}
		Triangles.push_back(tempList);
	}
	return Triangles;
}
// check that start < finish for segments
void IntersectionOfSegments(Segment s1, Segment s2, std::vector <Point2d>& vertex)
{
	Line l1 = { s1.start.y - s1.finish.y, s1.finish.x - s1.start.x, l1.a * s1.start.x + l1.b * s1.start.y };
	Line l2 = { s2.start.y - s2.finish.y, s2.finish.x - s2.start.x, l2.a * s2.start.x + l2.b * s2.start.y };
	double check = l1.a * l2.b - l1.b * l2.a;
	if (abs(check) < eps)
	{
		return;
	}
	Point2d commonPoint = { (l1.c * l2.b  - l2.c * l1.b ) / check, (l1.a * l2.c  - l1.c * l2.a ) / check };
	if (commonPoint.x >= s1.start.x and commonPoint.x <= s1.finish.x and commonPoint.x >= s2.start.x and commonPoint.x <= s2.finish.x)
	{
		vertex.push_back(commonPoint);
	};
}
double polar_angle(Point2d p0, Point2d p1) {
    int x_span = p0.x - p1.x;
    int y_span = p0.y - p1.y;
    return atan2(y_span, x_span);
}

int distance(Point2d p0, Point2d p1) {
    int x_span = p0.x - p1.x;
    int y_span = p0.y - p1.y;
    return y_span * y_span + x_span * x_span;
}

int det(Point2d p1, Point2d p2, Point2d p3) {
    return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
}

std::vector<Point2d> quicksort(std::vector<Point2d>& a) {
    if (a.size() <= 1) {
        return a;
    }
    Point2d originPoint;
    originPoint.x = 0;
    originPoint.y = 0;
    std::vector<Point2d> smaller, equal, larger;
    double piv_ang = polar_angle(a[0], originPoint);
    for (auto pt : a) {
        double pt_ang = polar_angle(pt, originPoint);
        if (pt_ang < piv_ang) {
            smaller.push_back(pt);
        }
        else if (pt_ang == piv_ang) {
            equal.push_back(pt);
        }
        else {
            larger.push_back(pt);
        }
    }
    smaller = quicksort(smaller);
    larger = quicksort(larger);
    std::vector<Point2d> sorted_pts;
    sorted_pts.insert(sorted_pts.end(), smaller.begin(), smaller.end());
    sorted_pts.insert(sorted_pts.end(), equal.begin(), equal.end());
    sorted_pts.insert(sorted_pts.end(), larger.begin(), larger.end());
    return sorted_pts;
}

std::vector<Point2d> scan(std::vector<Point2d>& points) {
    Point2d anchor;
    int min_idx = -1;
    for (int i = 0; i < points.size(); i++) {
        int x = points[i].x;
        int y = points[i].y;
        if (min_idx == -1 || y < points[min_idx].y) {
            min_idx = i;
        }
        if (y == points[min_idx].y && x < points[min_idx].x) {
            min_idx = i;
        }
    }
    anchor = points[min_idx];
    std::vector<Point2d> sorted_pts = quicksort(points);
    sorted_pts.erase(std::find(sorted_pts.begin(), sorted_pts.end(), anchor));
    std::vector<Point2d> hull;
    hull.push_back(anchor);
    hull.push_back(sorted_pts[0]);
    for (int i = 1; i < sorted_pts.size(); i++) {
        while (det(hull[hull.size() - 2], hull[hull.size() - 1], sorted_pts[i]) <= 0) {
            hull.pop_back();
            if (hull.size() < 2) {
                break;
            }
        }
        hull.push_back(sorted_pts[i]);
    }
    return hull;
}

int main()
{
    int numOfTriangles;
    std::cin >> numOfTriangles;
    std::vector<Point2d> ans;
    std::vector <std::vector <Point2d>> triangles = GenerateTriangles(numOfTriangles);
    for (auto triangle : triangles)
    {
        Segment firstSeg, secondSeg;
        firstSeg.start = triangle.at(0); 
        firstSeg.finish = triangle.at(1);
        secondSeg.finish = triangle.at(1);
        secondSeg.start = triangle.at(2);
        IntersectionOfSegments(firstSeg, secondSeg, ans);
    }
    std::cout << "ans = " << ans.at(0).x << " " << ans.at(0).y << "\n";
    std::cout << "vertex = " << triangles.at(0).at(1).x << " " << triangles.at(0).at(1).y << "\n";
    /*std::vector<Point2d> res_pts = scan();
    res_pts.push_back(res_pts[0]);
    int p1 = 0;
    int p2 = 0;
    for (int i = 0; i < res_pts.size() - 1; i++) {
        p1 += res_pts[i].x * res_pts[i + 1].y;
        p2 += res_pts[i].x * res_pts[i + 1].y;
    }
    double a = 0.5 * (p1 - p2);
    std::cout << a << std::endl;*/
    return 0;
}