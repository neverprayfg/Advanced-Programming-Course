#ifndef Q1_H
#define Q1_H
#include <functional>
#include <cmath>
namespace q1{
    double gradient_descent(double init, double step, std::function<double(double)> func)
    {
        for(int i = 0; i < 1e6; i++){
            double grad = (func(init + 1e-4) - func(init - 1e-4)) / (2 * 1e-4);
            double cur_init = init - step * grad;
            if(std::abs(init - cur_init) / std::abs(cur_init) < 1e-6) break;
            init = cur_init;
        }
        return init;
    }
}
#endif //Q1_H