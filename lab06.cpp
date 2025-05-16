#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <iomanip>

class PointOutOfRange : public std::out_of_range {
private:
    double x, y, z;

public:
    PointOutOfRange(const std::string& what_arg, double x, double y, double z)
        : std::out_of_range(what_arg), x(x), y(y), z(z) {}

    void printInvalidPoint() const {
        std::cout << "Invalid point coordinates: ("
            << x << ", " << y << ", " << z << ")\n";
        std::cout << "Error message: " << what() << std::endl;
    }
};

class UnitCubePoint {
private:
    double x, y, z;

    static bool isValidCoordinate(double coord) {
        return coord >= 0.0 && coord <= 1.0;
    }

public:
    UnitCubePoint(double x, double y, double z) {
        if (!isValidCoordinate(x) || !isValidCoordinate(y) || !isValidCoordinate(z)) {
            std::ostringstream oss;
            oss << "All coordinates must be in range [0, 1]. Got ("
                << x << ", " << y << ", " << z << ")";
            throw PointOutOfRange(oss.str(), x, y, z);
        }

        this->x = x;
        this->y = y;
        this->z = z;
    }

    double getX() { return x; }
    double getY() { return y; }
    double getZ() { return z; }

    void print() const {
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Point in unit cube: (" << x << ", " << y << ", " << z << ")\n";
    }
};

int main() {
    try {
        UnitCubePoint p1(0.5, 0.3, 0.8);
        p1.print();
    }
    catch (const PointOutOfRange& e) {
        e.printInvalidPoint();
    }

    std::cout << "\n";

    try {
        UnitCubePoint p2(1.2, -0.1, 0.5);
        p2.print();
    }
    catch (const PointOutOfRange& e) {
        e.printInvalidPoint();
    }

    return 0;
}