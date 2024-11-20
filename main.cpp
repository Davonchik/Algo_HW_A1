#include <iostream>
#include <cmath>
#include <cstdlib>
#include <random>
#include <fstream>

static constexpr double correct_S = 0.25 * M_PI + 1.25 * std::asin(0.8) - 1.0;

struct TestResult {
    int n;
    double intersection_area;
    double relative_error;
    TestResult(int n, double intersection_area)
        : n(n), intersection_area(intersection_area) {
        relative_error = std::abs(intersection_area - correct_S) / correct_S;
    }
};

std::ostream& operator <<(std::ofstream& out, const TestResult& res) {
    out << res.n << " " << res.intersection_area  << " " << res.relative_error;
    return out;
}

struct Point {
    double x;
    double y;
};

struct Circle {
    Point center;
    double r;
    bool in_circle(Point p) {
        return (p.x - center.x) * (p.x - center.x) +
            (p.y - center.y) * (p.y - center.y) <= r * r;
    }
};

struct Square {
    Point from;
    Point to;
    double area() {
        return std::abs(from.x - to.x) * std::abs(from.y - to.y);
    }
};

Point generate_point(Square area) {
    static std::mt19937 gen(42);
    std::uniform_real_distribution<> x_dis(area.from.x, area.to.x);
    std::uniform_real_distribution<> y_dis(area.from.y, area.to.y);
    Point result {
        .x = x_dis(gen),
        .y = y_dis(gen)
    };
    return result;
}

double get_intersection_area(Circle c_1, Circle c_2, Circle c_3, Square cover, int n) {
    int intersect_cnt = 0;

    for (int i = 0; i < n; ++i) {
        Point p = generate_point(cover);
        if (c_1.in_circle(p) && c_2.in_circle(p) && c_3.in_circle(p)) {
            ++intersect_cnt;
        }
    }

    return double(intersect_cnt) / n * cover.area();
}

void write_into_file(std::string file_name, const std::vector<TestResult>& data) {
    std::ofstream out(file_name);
    for (const auto& res: data) {
        out << res << std::endl;
    }
}


int main() {
    Circle c1 {
        .center = {1, 1},
        .r = 1
    };
    Circle c2 {
        .center = {1.5, 2},
        .r = std::sqrt(5) / 2
    };
    Circle c3 {
        .center = {2, 1.5},
        .r = std::sqrt(5) / 2
    };
    Square sq1 {
        .from = {0, 0},
        .to = {2+c3.r, 2+c2.r}
    };
    Square sq2 {
        .from = {0.85, 0.85},
        .to = {2.1, 2.1}
    };

    std::vector<TestResult> res_sq_1;
    std::vector<TestResult> res_sq_2;

    for (int i = 100; i <= 100000; i += 500) {
        res_sq_1.emplace_back(i, get_intersection_area(c1, c2, c3, sq1, i));
        res_sq_2.emplace_back(i, get_intersection_area(c1, c2, c3, sq2, i));
    }

    write_into_file("big_square.txt", res_sq_1);
    write_into_file("small_square.txt", res_sq_2);

    return 0;
}
