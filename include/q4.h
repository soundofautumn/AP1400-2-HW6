#ifndef Q4_H
#define Q4_H

#include <vector>

namespace q4 {
    struct Vector2D {
        double x{};
        double y{};
    };

    struct Sensor {
        Vector2D pos;
        double accuracy;
    };

    inline Vector2D kalman_filter(const std::vector<Sensor> &sensors) {
        double weighted_sum_x = 0.0;
        double weighted_sum_y = 0.0;
        double total_accuracy = 0.0;

        for (const auto &sensor: sensors) {
            weighted_sum_x += sensor.pos.x * sensor.accuracy;
            weighted_sum_y += sensor.pos.y * sensor.accuracy;
            total_accuracy += sensor.accuracy;
        }

        Vector2D result;
        if (total_accuracy != 0) {
            result.x = weighted_sum_x / total_accuracy;
            result.y = weighted_sum_y / total_accuracy;
        }

        return result;
    }
}

#endif //Q4_H