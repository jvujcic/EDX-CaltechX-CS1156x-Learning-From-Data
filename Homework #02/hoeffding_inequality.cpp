#include <iostream>
#include <tuple>
#include <random>
#include <ctime>

using namespace std;   

mt19937 generator;

tuple<double, double, double> run_experiment() {
    uniform_int_distribution<int> unif_dist(1, 1000);
    binomial_distribution<int> bin_dist(10, 0.5);

    double v1 = 0;
    int c_rand = unif_dist(generator);
    double v_rand = 0;
    double v_min = 11;

    for (int i = 1; i <= 1000; ++i) {
        int v = bin_dist(generator);
        if (v < v_min) v_min = v;
        if (i == 1) v1 = v;
        else if (i == c_rand) v_rand = v;
    }

    return {v1/10, v_rand/10, v_min/10};
}

int main() {
    generator.seed(time(NULL));
    int num_exp = 100000;

    double v1_sum, v_min_sum, v_rand_sum;
    v1_sum = v_min_sum = v_rand_sum = 0;

    for (int i = 0; i < num_exp; ++i) {
        double v1, v_rand, v_min;
        tie(v1, v_rand, v_min) = run_experiment();
        v1_sum += v1;
        v_rand_sum += v_rand;
        v_min_sum += v_min;
    }

    cout << "v1: " << v1_sum / num_exp << endl;
    cout << "v_rand: " << v_rand_sum / num_exp << endl;
    cout << "v_min: " << v_min_sum / num_exp << endl;
}