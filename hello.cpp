#include <stdio.h>

struct MyClass {
    int myNum;
    const char *myString;
    void myMethod() {
        printf("%s\n", "Hello World!");
        return;
    }
};

template <typename T> T add(T x, T y) {
    return x + y;
}

template int add<int>(int, int);
template float add<float>(float, float);

extern "C" {
int add_int(int x, int y) {
    return add<int>(x, y);
}

float add_float(float x, float y) {
    return add<float>(x, y);
}
}

constexpr int fib(int n) {
    if (n <= 1) return n;
    return fib(n - 1) + fib(n - 2);
}

namespace vec {
struct Vec2 {
    float x, y;

    Vec2 operator+(const Vec2 &other) const {
        return { x + other.x, y + other.y };
    }

    Vec2 operator-(const Vec2 &other) const {
        return { x - other.x, y - other.y };
    }

    Vec2 operator/(const Vec2 &other) const {
        return { x / other.x, y / other.y };
    }

    Vec2 operator*(const Vec2 &other) const {
        return { x * other.x, y * other.y };
    }
};
}

int main() {
    MyClass myObj;

    myObj.myNum = 15;
    myObj.myString = "Some text";

    printf("%d\n", add(myObj.myNum, 20));
    printf("%s\n", myObj.myString);
    myObj.myMethod();

    constexpr int x = fib(20);
    printf("%d\n", x);

    int z = 10;

    auto f = [z](int x) { return x + z; };

    printf("%d\n", f(20));

    vec::Vec2 a{ 1, 2 }, b{ 3, 4 };
    vec::Vec2 c = a / b;
    printf("%f %f\n", c.x, c.y);

    return 0;
}
// clang++ hello.cpp -fno-exceptions -fno-rtti -nostdlib++
