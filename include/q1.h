#ifndef Q1_H
#define Q1_H

#include <functional>
#include <cmath>

namespace q1 {

    template<typename T=double, typename F>
    T gradient_descent(T init_value, T step, F f = F{}) {
        const T epsilon = std::numeric_limits<T>::epsilon();
        T current_value = init_value;
        T gradient;
        int max_iterations = 10000; // Prevent infinite loops
        int iteration = 0;

        do {
            // Compute the numerical gradient using central difference
            T delta = std::sqrt(epsilon);
            gradient = (f(current_value + delta) - f(current_value - delta)) / (2 * delta);

            // Update the current value
            current_value = current_value - step * gradient;

            iteration++;
        } while (std::abs(gradient) > epsilon && iteration < max_iterations);

        return current_value;
    }
}

#endif //Q1_H