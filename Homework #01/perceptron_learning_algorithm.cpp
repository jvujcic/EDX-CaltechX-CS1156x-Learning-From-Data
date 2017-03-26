#include <iostream>
#include <vector>
#include <utility>
#include <tuple>
#include <random>
#include <ctime>

using namespace std;

class Point {
public:
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

class LinearFunction {
public:
    double w0, w1, w2;

    LinearFunction(double w0=0, double w1=0, double w2=0) : w0(w0), w1(w1), w2(w2) {}

    LinearFunction(const Point & p1, const Point & p2) {
        w1 = p2.y - p1.y;
        w2 = p1.x - p2.y;
        w0 = -w1 * p1.x - w2 * p1.y;
    }

    double operator()(const Point & p) const{
        return w0 + w1 * p.x + w2 * p.y; 
    }

    int sign(const Point & p) const {
        double sgn =(*this)(p);
        if (sgn > 0) return 1;
        else if (sgn < 0) return -1;
        return 0;
    }

    LinearFunction operator+(const LinearFunction & f) {
        return LinearFunction(w0 + f.w0, w1 + f.w1, w2 + f.w2);
    }
};

tuple<LinearFunction, int> perceptron_algorithm(vector<pair<Point, int>> sample) {
    LinearFunction h(0, 0, 0);
    int n = sample.size();
    int i = 0, j = 0, num_it = 0;
    while (j <= n) {
        Point p = sample[i].first;
        int d = sample[i].second;
        int sgn = h.sign(p);
        if (sgn == d) {
            i++; 
            i%=n; 
            j++;
        }
        else {
            h = h + LinearFunction(d, d*p.x, d*p.y);
            i++; 
            i%=n; 
            j=0;
            num_it++;
        }
    }

    return make_tuple(h, num_it);
}

void run_experiment(int data_set_size) {
    default_random_engine generator;
    generator.seed(time(NULL));
    uniform_real_distribution<double> distribution(-1.0, 1.0);

    double avarage_it = 0;
    double average_prob = 0;
    int num_exp = 10000;

    for (int i = 0; i < num_exp; i++) {
        Point p1(distribution(generator), distribution(generator));
        Point p2(distribution(generator), distribution(generator));
        LinearFunction line(p1, p2);
        vector<pair<Point, int>> sample(data_set_size);

        for (auto &s : sample) {
            s.first.x = distribution(generator);
            s.first.y = distribution(generator);
            s.second = line.sign(s.first);
        }

        LinearFunction solution;
        int num_it;
        tie(solution, num_it) = perceptron_algorithm(sample);

        int num_points = 10000, diff = 0;
        for (int j = 0; j < num_points; ++j) {
            Point p(distribution(generator), distribution(generator));
            if (solution.sign(p) != line.sign(p)) ++diff;
        }

        avarage_it += num_it;
        average_prob += (double) diff / num_points;
    }
    cout << "Data set size: " << data_set_size << endl;
    cout << "Average number of iterations: " << avarage_it/num_exp << endl;
    cout << "Average probability: " << average_prob/num_exp << endl;
}

int main() {
    run_experiment(10);
    run_experiment(100);
    return 0;
}