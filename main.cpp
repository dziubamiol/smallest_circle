#include <iostream>
#include <vector>
#include <cmath>

struct Point {
    double x;
    double y;
};

struct Circle {
    Point center;
    double radius;
};

double point_distance (Point &point_1, Point &point_2) {
    return std::sqrt(pow(point_1.x - point_2.x, 2) + pow(point_2.y - point_1.y, 2));
}

bool point_in_circle (Circle &circle, Point &point) {
    return pow(point.x - circle.center.x, 2) + pow(point.y - circle.center.y, 2) <= pow(circle.radius, 2);
}

Circle min_circle(Point &point_1, Point &point_2) {
    Point init_center = {
            (point_1.x + point_2.x) / 2,
            (point_1.y + point_2.y) / 2
    };
    double distance = point_distance(point_1, point_2);
    Circle circle = {
            init_center,
            distance / 2
    };

    return circle;
}

Circle circumcircle (Point &point_1, Point &point_2, Point &point_3) {
    double a = point_distance(point_1, point_2);
    double b = point_distance(point_2, point_3);
    double c = point_distance(point_3, point_1);

    double P = a + b + c;

    Point center = {
            (a * point_1.x + b * point_2.x + c * point_3.x) / P,
            (a * point_1.y + b * point_2.y + c * point_3.y) / P
    };
    double radius = point_distance(center, point_1);

    Circle circle = {
            center,
            radius
    };

    return circle;
}

Circle min_disc_with_two_points(std::vector<Point> &points, Point &point_1, Point &point_2) {
    Circle circle = min_circle(point_1, point_2);

    for (auto pnt : points) {
         if (!point_in_circle(circle, pnt)) {
            circle = circumcircle(pnt, point_1, point_2);
        }
    }
    return circle;
}

Circle min_disc_with_points (std::vector<Point> &points, Point &point) {
    Circle circle = min_circle(points[0], point);

    for (int i = 1; i < points.size(); i++) {
        Point pnt = points[i];

        if (!point_in_circle(circle, pnt)) {
            circle = min_disc_with_two_points(points, pnt, point);
        }
    }
    return circle;
}

Circle min_disc (std::vector<Point> &points) {
    if (points.size() < 2) {
        std::cout << "Minimal number of points to proceed is 2\n";
        throw;
    }

    // initialize first circle
    Circle circle = min_circle(points[0], points[1]);

    for (int i = 2; i < points.size(); i++) {
        Point point = points[i];

        if (!point_in_circle(circle, point)) {
            circle = min_disc_with_points(points, point);
        }
    }
    return circle;
}


int main() {
    std::vector<Point> points = {
            {2, 2},
            {3, 1},
            {4, 2},
            {5, 8},
            {8, 5}
    };

    Circle min_circle = min_disc(points);

    std::cout << "Minimal circle, x: " << min_circle.center.x << " y: " << min_circle.center.y << " radius: " << min_circle.radius << "\n";

    return 0;
}
