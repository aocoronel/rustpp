use std::error::Error;
use std::ffi::c_void;
use std::fmt;
use std::io::{self, Write};
use std::ops::{Add, Div, Mul, Sub};

struct hello {
    msg: &'static str,
}

unsafe extern "C" {
    fn malloc(size: usize) -> *mut c_void;
    fn free(ptr: *mut c_void);
}

unsafe fn c() {
    unsafe {
        let ptr: *mut c_void = malloc(100);

        if ptr.is_null() {
            panic!("malloc failed!");
        }

        println!("Allocated 100 bytes at {:p}", ptr);

        let u8_ptr = ptr as *mut u8;
        *u8_ptr = 42;
    }
}

impl Drop for hello {
    fn drop(&mut self) {
        unsafe {
            c();
        }
    }
}

fn main() -> Result<(), Box<dyn Error>> {
    let my_obj = hello {
        msg: "Some text",
    };
    Ok(())
}
