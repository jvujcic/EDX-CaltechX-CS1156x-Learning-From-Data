import numpy as np
import matplotlib.pyplot as plt

def calculate_implicit(f, start, error):
    N = start
    while (np.abs(f(N) - N) > error):
        N = f(N)
    return N


def f(epsilon, delta, dvc):
    def g(N):
        return (8/epsilon**2) * (np.log(4) + dvc*np.log(2*N) - np.log(delta))
    return calculate_implicit(g, 1, 0.1)


def original_bound(delta, dvc, N):
    return np.sqrt((8/N) * (np.log(4) + dvc*np.log(2*N) -np.log(delta)))


def rademacher(delta, dvc, N):
    return np.sqrt(2 * (np.log(2*N) + dvc*np.log(N)) / N) + np.sqrt(2 * np.log(1/delta) / N) + 1/N


def parrondo(delta, dvc, N):
    def g(epsilon):
        return np.sqrt((1/N) * (2*epsilon + np.log(6) + dvc*np.log(2*N) - np.log(delta)))
    return calculate_implicit(g, 1, 0.01)


def devroye(delta, dvc, N):
    def g(epsilon):
        return np.sqrt((1/(2*N)) * (4*epsilon*(1+epsilon) + np.log(4) + 2*dvc*np.log(N) - np.log(delta)))
    return calculate_implicit(g, 1, 0.01)


def compare_all(delta, dvc, N):
    print("original: ", original_bound(delta, dvc, N))
    print("rademacher: ", rademacher(delta, dvc, N))
    print("parrondo: ", parrondo(delta, dvc, N))
    print("devroye: ", devroye(delta, dvc, N))


print("1 ::")
print(f(0.05, 0.05, 10))


delta = 0.05
dvc = 50
print("\n2 ::")
compare_all(delta, dvc, 10000)
print("\n3 ::")
compare_all(delta, dvc, 5)


x = np.arange(1, 10000, 10)
plt.plot(x, original_bound(delta, dvc, x), color="blue", label="original")
plt.plot(x, np.vectorize(rademacher)(delta, dvc, x), color="red", label="rademacher")
plt.plot(x, np.vectorize(parrondo)(delta, dvc, x), color="green", label="parrondo")
plt.plot(x, np.vectorize(devroye)(delta, dvc, x), color="purple", label="devroye")
plt.legend(loc='upper left')
plt.show
