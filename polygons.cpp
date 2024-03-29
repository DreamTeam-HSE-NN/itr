#include <iostream>
#include <random>
#include <list>
#include <vector>
#include <algorithm>
#include <time.h>
#include <set>
#include <cstdlib>
#include <ctime>
#define _USE_MATH_DEFINES
#include <math.h>
#define border 1000
#define eps 1E-8

struct Point2d
{
    double x, y;

    bool operator== (const Point2d b) const
    {
        return (abs(this->x - b.x) < eps && abs(this->y - b.y) < eps);
    }
    bool operator<(const Point2d& rhs) const
    {
        return this->x < rhs.x;
    }
};

struct Line
{
    double a, b, c;
};

struct Segment
{
    Point2d start, finish;
    bool operator==(const Segment& ref) const
    {
        return (this->start == ref.start) && (this->finish == ref.finish);
    }
    bool operator<(const Segment& rhs) const
    {
        return this->start < rhs.start ;  
    }
};

double polar_angle(Point2d p0, Point2d p1) 
{
    int x_span = p0.x - p1.x;
    int y_span = p0.y - p1.y;
    return atan2(y_span, x_span);
}

int det(Point2d p1, Point2d p2, Point2d p3) 
{
    return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
}

double distance(Point2d p0, Point2d p1)
{
    double x_span = p0.x - p1.x;
    double y_span = p0.y - p1.y;
    return y_span * y_span + x_span * x_span;
}

std::vector<Point2d> quicksort(std::vector<Point2d>& a) 
{
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

std::vector <std::vector <Segment>> GeneratePolygons(uint32_t numOfPolygons)
{
    std::vector <std::vector <Segment>> Polygons;
    for (int i = 0; i < numOfPolygons; ++i)
    {
        std::vector <Point2d> tempList;
        uint32_t vertexes;
        vertexes = rand() % (5 - 4 + 1) + 4;
        //vertexes = 3;
        std::vector<Segment> segments;
        int x0 = 0;
        int y0 = 0;
        int radius = rand() % (30 - 20 + 1) + 20;
        for (int k = 1; k <= vertexes; ++k)
        {
            Point2d temp;
            //float phi = 2 * M_PI * rand();
            int phi = rand() % (180 - 45 + 1) + 45;
            temp.x = x0 + radius * cos(phi);
            temp.y = y0 + radius * sin(phi);
            tempList.push_back(temp);
        }
        std::vector <Point2d> sorted_tempList;
        sorted_tempList = quicksort(tempList);
        //sorted_tempList = tempList;
        for (int j = 0; j < sorted_tempList.size(); ++j)
        {
            Segment segment;
            segment.start = sorted_tempList.at(j);
            segment.finish = sorted_tempList.at((j + 1) % sorted_tempList.size());
            segments.push_back(segment);
        }
        Polygons.push_back(segments);
    }
    return Polygons;
}


bool IntersectionOfSegments(Segment s1, Segment s2, std::vector <Point2d>& vertex)
{
    Line l1 = { s1.start.y - s1.finish.y, s1.finish.x - s1.start.x, l1.a * s1.start.x + l1.b * s1.start.y };
    Line l2 = { s2.start.y - s2.finish.y, s2.finish.x - s2.start.x, l2.a * s2.start.x + l2.b * s2.start.y };
    double check = l1.a * l2.b - l1.b * l2.a;
    if (abs(check) < eps)
    {
        return false;
    }
    Point2d commonPoint = { (l1.c * l2.b - l2.c * l1.b) / check, (l1.a * l2.c - l1.c * l2.a) / check };
    if (sqrt(distance(commonPoint, s1.start)) + sqrt(distance(commonPoint, s1.finish)) - sqrt(distance(s1.start, s1.finish)) < eps
        && sqrt(distance(commonPoint, s2.start)) + sqrt(distance(commonPoint, s2.finish)) - sqrt(distance(s2.start, s2.finish)) < eps)
    {
        vertex.push_back(commonPoint);
        return true;
    }
    return false;
}

double triangle_square(double A, double B, double C)
{
    double p = 0.5 * (A + B + C);
    return sqrt(p * (p - A) * (p - B) * (p - C));
}


double calculatePolygonSquare(std::vector<Point2d> res_pts)// Nikolay's function
{
    res_pts.push_back(res_pts[0]);
    double p1 = 0;
    double p2 = 0;
    for (int i = 0; i < res_pts.size() - 1; i++) 
    {
        p1 += res_pts[i].x * res_pts[i + 1].y;
        p2 += res_pts[i].y * res_pts[i + 1].x;
    }
    double a = abs(0.5 * (p1 - p2));
    return a;
}

int main()
{
    std::srand(std::time(NULL));
    int numOfPolygons;
    std::cin >> numOfPolygons;
    std::vector<Point2d> tempAns;
    std::vector <std::vector <Segment>> polygons = GeneratePolygons(numOfPolygons);
    /*
    std::vector <std::vector<Segment>> polygons;
    for (int i = 0; i < numOfPolygons; ++i)
    {
        std::vector<Segment> sides;
        for (int j = 0; j < 4; ++j)
        {
            Segment side;
            std::cin >> side.start.x >> side.start.y >> side.finish.x >> side.finish.y;
            sides.push_back(side);
        }
        polygons.push_back(sides);
    }
    */
    int i = 0;
    std::set<Segment> InnerPoint;
    while (i < polygons.size())
    {
        for (int j = 0; j < polygons.at(i).size(); ++j)
        {
            bool checkPoint;
            int count = 0;
            int k = 0;
            while (k < polygons.size())
            {
                if (k != i)
                {
                    for (int l = 0; l < polygons.at(k).size(); ++l)
                    {
                        checkPoint = IntersectionOfSegments(polygons.at(i).at(j), polygons.at(k).at(l), tempAns);
                        if (checkPoint)
                        {
                            count++;
                        }
                    }
                    if (count == 1 || count == 0)
                    {
                        InnerPoint.insert(polygons.at(i).at(j));
                    }
                }
                k++;
            }
            //if (InnerPoint.size() == 2)
                //IntersectionOfSegments(InnerPoint.at(0), InnerPoint.at(1), ans);  
        }
        i++;
    }
    std::set<Point2d> ans(tempAns.begin(), tempAns.end());
    for (Segment const seg : InnerPoint)
    {
        int count_polygonsStart = 1;
        int count_polygonsFinish = 1;
        for (auto polygon : polygons)
        {
            if (std::find(polygon.begin(), polygon.end(), seg) == polygon.end())
            {
                double PolygonSquareStart = 0;
                double PolygonSquareFinish = 0;
                std::set<Point2d> coordinates;
                for (auto const edge : polygon)
                {
                    coordinates.insert(edge.start);
                    coordinates.insert(edge.finish);
                    double A = sqrt(distance(seg.start, edge.start));
                    double B = sqrt(distance(seg.start, edge.finish));
                    double C = sqrt(distance(edge.start, edge.finish));
                    PolygonSquareStart += triangle_square(A, B, C);
                    A = sqrt(distance(seg.finish, edge.start));
                    B = sqrt(distance(seg.finish, edge.finish));
                    PolygonSquareFinish += triangle_square(A, B, C);
                }
                std::vector<Point2d> unique_coordinates(coordinates.begin(), coordinates.end());
                unique_coordinates = quicksort(unique_coordinates);

                if (abs(calculatePolygonSquare(unique_coordinates) - PolygonSquareStart) < eps)
                {
                    count_polygonsStart++;
                }
                if (abs(calculatePolygonSquare(unique_coordinates) - PolygonSquareFinish) < eps)
                {
                    count_polygonsFinish++;
                }
            }   
        }
        if (count_polygonsFinish == numOfPolygons)
        {
            ans.insert(seg.finish);
        }
        if (count_polygonsStart == numOfPolygons)
        {
            ans.insert(seg.start);
        }
    }
    std::set<Point2d> final_ans;
    for (auto point : ans)
    {
        int count_polygons = 0;
        for (auto polygon : polygons)
        {
            double PolygonSquare = 0;
            std::set<Point2d> coordinates;
            for (auto const edge : polygon)
            {
                coordinates.insert(edge.start);
                coordinates.insert(edge.finish);
                double A = sqrt(distance(point, edge.start));
                double B = sqrt(distance(point, edge.finish));
                double C = sqrt(distance(edge.start, edge.finish));
                if (A + B - C < eps)
                {
                    PolygonSquare += 0;
                }
                else
                {
                    PolygonSquare += triangle_square(A, B, C);
                }
            }
            std::vector<Point2d> unique_coordinates(coordinates.begin(), coordinates.end());
            unique_coordinates = quicksort(unique_coordinates);

            if (abs(calculatePolygonSquare(unique_coordinates) - PolygonSquare) < eps)
            {
                count_polygons++;
            }
        }
        if (count_polygons == numOfPolygons)
        {
            final_ans.insert(point);
        }
    }

    std::cout << "Coordinates of vertecies of polygons: " << "\n";
    for (int i = 0; i < polygons.size(); ++i)
    {
        for (int j = 0; j < polygons.at(i).size(); ++j)
        {
            std::cout << polygons.at(i).at(j).start.x << ", " << polygons.at(i).at(j).start.y << "; " << polygons.at(i).at(j).finish.x << ", " << polygons.at(i).at(j).finish.y << "\n";
        }
        std::cout << "\n";
    };

    std::cout << "Coordinates of intersection area: " << "\n";
    for (auto pet: final_ans)
    {
        std::cout << "x: "<< pet.x << " " << "y: " << pet.y << "\n";
    };
    std::cout << "\n";
    
    if (final_ans.size() > 2)
    {
        std::vector<Point2d> vectorAns(final_ans.begin(), final_ans.end());
        std::vector<Point2d> res_pts = quicksort(vectorAns);
        double SQUARE = 0;
        SQUARE = calculatePolygonSquare(res_pts);
        std::cout << "Calculated area: " << SQUARE << "\n";
    }
    else
    {
        std::cout << "Error";
    }
    
    return 0;
}