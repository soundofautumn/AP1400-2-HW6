#ifndef Q2_H
#define Q2_H

#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

namespace q2 {
    using std::string;
    using std::vector;
    using std::fstream;

    struct Patient {
        std::string name;
        size_t age;
        size_t smokes;
        size_t area_q;
        size_t alkhol;

        auto operator<=>(const Patient &other) const {
            auto this_ = 3 * age + 5 * smokes + 2 * area_q + 4 * alkhol;
            auto other_ = 3 * other.age + 5 * other.smokes + 2 * other.area_q + 4 * other.alkhol;
            return this_ <=> other_;
        }
    };

    inline vector<Patient> read_file(const string &filename) {
        vector<Patient> res;
        fstream file(filename);
        string line;
        std::getline(file, line);
        std::getline(file, line);

        auto trim = [](string &s) {
            s.erase(0, s.find_first_not_of(' '));
            s.erase(s.find_last_not_of(' ') + 1);
            return s;
        };

        while (!file.eof()) {
            std::string name;
            std::string surname;
            std::string age;
            std::string smokes;
            std::string area_q;
            std::string alkhol;
            std::getline(file, name, ',');
            std::getline(file, surname, ',');
            std::getline(file, age, ',');
            std::getline(file, smokes, ',');
            std::getline(file, area_q, ',');
            std::getline(file, alkhol, '\n');
            res.push_back({trim(name) + " " + trim(surname),
                           static_cast<size_t>(std::stoi(age)),
                           static_cast<size_t>(std::stoi(smokes)),
                           static_cast<size_t>(std::stoi(area_q)),
                           static_cast<size_t>(std::stoi(alkhol))});

        }
        return res;
    }

    inline void sort(vector<Patient> &v) {
        std::sort(v.begin(), v.end(), std::greater<>());
    }
}
#endif //Q2_H