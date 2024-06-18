#ifndef Q3_H
#define Q3_H

#include <queue>
#include <string>
#include <fstream>

namespace q3 {
    struct Flight {
        std::string flight_number;
        size_t duration;
        size_t connections;
        size_t connection_times;
        size_t price;

        auto operator<=>(const Flight &other) const {
            auto this_ = duration + connection_times + 3 * price;
            auto other_ = other.duration + other.connection_times + 3 * other.price;
            return this_ <=> other_;
        }
    };

    inline auto gather_flights(const std::string &filename) {
        // 1- flight_number:QR492 - duration:11h30m - connections:3 - connection_times:2h,1h30m,4h15m - price:250
        std::fstream file(filename);
        std::string line;
        std::priority_queue<Flight, std::vector<Flight>, std::greater<>> flights;
        auto trim = [](std::string &&s) {
            s.erase(0, s.find_first_not_of(' '));
            s.erase(s.find_last_not_of(' ') + 1);
            return s;
        };
        auto find_part = [=](const std::string &line, const std::string &part, size_t &begin) {
            auto part_begin = line.find(part, begin);
            auto part_end = line.find('-', part_begin);
            return trim(line.substr(part_begin + part.size(), part_end - part_begin - part.size()));
        };
        auto parse_duration = [](const std::string &duration) {
            size_t time = 0;
            size_t h_pos = duration.find('h');
            size_t m_pos = duration.find('m');
            if (h_pos != std::string::npos) {
                time += std::stoi(duration.substr(0, h_pos)) * 60;
            }
            if (m_pos != std::string::npos) {
                time += std::stoi(duration.substr(h_pos + 1, m_pos - h_pos - 1));
            }
            return time;
        };
        auto parse_connection_times = [=](const std::string &connection_times) {
            size_t begin = 0;
            size_t end = 0;
            size_t time = 0;
            while (end != std::string::npos) {
                end = connection_times.find(',', begin);
                time += parse_duration(connection_times.substr(begin, end - begin));
                begin = end + 1;
            }
            return time;
        };
        while (!file.eof()) {
            std::getline(file, line);
            size_t begin = 0;
            // QR492
            auto flight_number = find_part(line, "flight_number:", begin);
            // 11h30m
            auto duration = find_part(line, "duration:", begin);
            // 3
            auto connections = find_part(line, "connections:", begin);
            // 2h,1h30m,4h15m
            auto connection_times = find_part(line, "connection_times:", begin);
            // 250
            auto price = find_part(line, "price:", begin);
            flights.push({flight_number,
                          parse_duration(duration),
                          static_cast<size_t>(std::stoi(connections)),
                          parse_connection_times(connection_times),
                          static_cast<size_t>(std::stoi(price))});
        }
        return flights;
    }
}

#endif //Q3_H