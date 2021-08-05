#pragma once

class Vect2 {
    public:
        double x, y;

        Vect2(): x(0), y(0) {
        }

        Vect2(double x, double y): x(x), y(y) {
        }

        void operator+=(const Vect2& v) {
             x += v.x;
             y += v.y;
        }

        Vect2 operator+(const Vect2& v) {
            return Vect2(x + v.x,
                         y + v.y);
        }

        Vect2 operator+(const double w) {
            return Vect2(x + w,
                         y + w);
        }

        Vect2 operator*(const Vect2& v) {
            return Vect2(x * v.x,
                         y * v.y);
        }

        Vect2 operator*(const double w) {
            return Vect2(x * w,
                         y * w);
        }

        Vect2 operator-(const Vect2& v) {
            return Vect2(x - v.x,
                         y - v.y);
        }
};

