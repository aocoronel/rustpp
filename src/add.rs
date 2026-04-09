pub mod add {
    pub fn add<T: std::ops::Add<Output = T>>(x: T, y: T) -> T {
        x + y
    }

    #[unsafe(no_mangle)]
    pub extern "C" fn add_int(x: i32, y: i32) -> i32 {
        add(x, y)
    }

    #[unsafe(no_mangle)]
    pub extern "C" fn add_float(x: f32, y: f32) -> f32 {
        add(x, y)
    }
}
