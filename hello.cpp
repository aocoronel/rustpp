#include <cstdio>
#include <stdio.h>

struct MyClass {
    int myNum;
    bool err;
    const char *myString;
    void myMethod() {
        printf("%s\n", "Hello World!");
        return;
    }
    void myMethod2() {
        printf("%s\n", "Hello World!");
        return;
    }
    template <typename T> T add(T x, T y) {
        if (x > y) {
            err = true;
            return 0;
        }
        return x + y;
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

    Vec2 operator+(const Vec2 other) const {
        return { x + other.x, y + other.y };
    }

    Vec2 operator-(const Vec2 other) const {
        return { x - other.x, y - other.y };
    }

    Vec2 operator/(const Vec2 other) const {
        return { x / other.x, y / other.y };
    }

    Vec2 operator*(const Vec2 other) const {
        return { x * other.x, y * other.y };
    }

    void operator=(const Vec2 other) {
        x = other.x;
        y = other.y;
    }

    float operator[](size_t idx) const {
        return x + y + idx;
    }

    void print(void) {
        printf("[%f, %f]\n", x, y);
    }
};
} // namespace vec

#define lambda auto

template <typename F> struct scoped_defer {
    F f;
    explicit scoped_defer(F f)
            : f(f) {
    }
    ~scoped_defer() {
        f();
    }
};

#define CAT(a, b) CAT_IMPL(a, b)
#define CAT_IMPL(a, b) a##b
#define defer(code) auto CAT(defer_t, __LINE__) = scoped_defer([&]() { code; })

// Usage
void f2() {
    // FILE *fp = fopen("file.txt", "r");
    // if (!fp) return;
    // DEFER(fclose(fp)); // fclose runs when f() exits
    defer({
        printf("=i\n");
        printf("=i\n");
        printf("=i\n");
    });
    printf("hello\n");
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

    lambda f = [z](int x) { return x + z; };

    printf("%d\n", f(20));

    vec::Vec2 a{ 1, 2 }, b{ 3, 4 };
    vec::Vec2 c = a / b;
    c = a;
    c.print();
    f2();

    printf("%f\n", c[20]);

    vec::Vec2 za{ 1, 2 };
    vec::Vec2 *zw = &za;
    printf("%f\n", zw->x);
    return 0;
}
// clang++ hello.cpp -fno-exceptions -fno-rtti -nostdlib++
