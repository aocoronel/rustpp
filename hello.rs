use std::ffi::c_void;
use std::fmt;
use std::ops::{Add, Div, Mul, Sub};

struct MyClass {
    my_num: i32,
    my_string: &'static str,
}

impl MyClass {
    fn my_method(&self) {
        println!("Hello World!");
    }
}

fn add<T: std::ops::Add<Output = T>>(x: T, y: T) -> T {
    x + y
}

#[no_mangle]
pub extern "C" fn add_int(x: i32, y: i32) -> i32 {
    add(x, y)
}

#[no_mangle]
pub extern "C" fn add_float(x: f32, y: f32) -> f32 {
    add(x, y)
}

const fn fib(n: usize) -> usize {
    if n <= 1 {
        n
    } else {
        fib(n - 1) + fib(n - 2)
    }
}

#[derive(Debug, Copy, Clone)]
struct Vec2 {
    x: f32,
    y: f32,
}

impl fmt::Display for Vec2 {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "Vec2({}, {})", self.x, self.y)
    }
}

impl Add for Vec2 {
    type Output = Vec2;
    fn add(self, other: Vec2) -> Vec2 {
        Vec2 {
            x: self.x + other.x,
            y: self.y + other.y,
        }
    }
}

impl Sub for Vec2 {
    type Output = Vec2;
    fn sub(self, other: Vec2) -> Vec2 {
        Vec2 {
            x: self.x - other.x,
            y: self.y - other.y,
        }
    }
}

impl Mul for Vec2 {
    type Output = Vec2;
    fn mul(self, other: Vec2) -> Vec2 {
        Vec2 {
            x: self.x * other.x,
            y: self.y * other.y,
        }
    }
}

impl Div for Vec2 {
    type Output = Vec2;
    fn div(self, other: Vec2) -> Vec2 {
        Vec2 {
            x: self.x / other.x,
            y: self.y / other.y,
        }
    }
}

struct Defer<F: FnOnce()> {
    f: Option<F>,
}

impl<F: FnOnce()> Defer<F> {
    fn new(f: F) -> Self {
        Defer { f: Some(f) }
    }
}

impl<F: FnOnce()> Drop for Defer<F> {
    fn drop(&mut self) {
        if let Some(f) = self.f.take() {
            f();
        }
    }
}

extern "C" {
    fn malloc(size: usize) -> *mut c_void;
    fn free(ptr: *mut c_void);
}

unsafe fn c() {
    let ptr: *mut c_void = malloc(100);

    if ptr.is_null() {
        panic!("malloc failed!");
    }

    let _d = Defer::new(move || {
        println!("Memory freed!");
        free(ptr);
    });

    println!("Allocated 100 bytes at {:p}", ptr);

    let u8_ptr = ptr as *mut u8;
    *u8_ptr = 42;
}

unsafe fn add2() -> () {
    println!("23");
    c();
}

fn main() {
    let my_obj = MyClass {
        my_num: 15,
        my_string: "Some text",
    };

    println!("{}", add(my_obj.my_num, 20));
    println!("{}", my_obj.my_string);
    my_obj.my_method();

    const X: usize = fib(20);
    println!("{X}");

    let z: usize = 10;
    let f = |x: usize| x + z;
    println!("{}", f(20));

    let a = Vec2 { x: 1.0, y: 2.0 };
    let b = Vec2 { x: 3.0, y: 4.0 };
    let c = a / b;
    println!("{c}");

    unsafe {
        add2();
    };
}
