#pragma once

class Vect3 {
    public:
        double x, y, z;

        Vect3(): x(0), y(0), z(0) {
        }

        Vect3(int x, int y, int z): x(x), y(y), z(z) {
        }

        Vect3 operator+(const Vect3& v) {
            return Vect3(x + v.x,
                         y + v.y,
                         z + v.z);
        }

        Vect3 operator*(const Vect3& v) {
            return Vect3(x * v.x,
                         y * v.y,
                         z * v.z);
        }

        Vect3 operator-(const Vect3& v) {
            return Vect3(x - v.x,
                         y - v.y,
                         z - v.z);
        }

};

