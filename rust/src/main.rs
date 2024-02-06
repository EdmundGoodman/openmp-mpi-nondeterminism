// use mpi::collective::SystemOperation;
// use mpi::traits::*;
use rayon::prelude::*;
use std::env;

fn main() {
    // let universe = mpi::initialize().unwrap();
    // let world = universe.world();
    let args: Vec<String> = env::args().collect();
    if args.len() != 2 {
        panic!("Provide the array sizes as an input!")
    }
    let length = args[1].parse::<usize>().unwrap();

    let mut x: Vec<f64> = vec![0.0; length];
    let mut y: Vec<f64> = vec![0.0; length];
    for i in 0..length {
        x[i] = (i as f64) / 3.0;
        y[i] = ((length - i) as f64) / 3.0;
    }

    // if world.rank() == 0 {
    let result_serial = ddot_serial(&x, &y);
    println!("Serial: {result_serial}");
    // }

    // if world.rank() == 0 {
    let result_rayon = ddot_rayon(&x, &y);
    println!("Rayon: {result_rayon}");
    // }

    // ===== //

    // let offset = (length / world.size() as usize) * rank;
    // let split_length = if (world.rank() != world.size() - 1) {
    //     length / world.size() as usize
    // } else {
    //     length - offset
    // };
    // let mut split_x: Vec<f64> = vec![0.0; split_length];
    // let mut split_y: Vec<f64> = vec![0.0; split_length];
    // for i in 0..split_length {
    //     split_x[i] = ((i + offset) as f64) / 3.0;
    //     split_y[i] = ((length - (i + offset)) as f64) / 3.0;
    // }
}

pub fn ddot_serial(lhs: &[f64], rhs: &[f64]) -> f64 {
    lhs.iter().zip(rhs.iter()).map(|(x, y)| x * y).sum()
}

pub fn ddot_rayon(lhs: &[f64], rhs: &[f64]) -> f64 {
    lhs.par_iter().zip(rhs.par_iter()).map(|(x, y)| x * y).sum()
}

// pub fn ddot_mpi(lhs: &[f64], rhs: &[f64]) -> f64 {
//     let local_result: f64 = lhs.iter().zip(rhs.iter()).map(|(x, y)| x * y).sum();
//     let mut global_result = 0.0;
//     world.all_reduce_into(&local_result, &mut global_result, SystemOperation::sum());
//     global_result
// }

// pub fn ddot_hybrid(lhs: &[f64], rhs: &[f64]) -> f64 {
//     let local_result: f64 = lhs.par_iter().zip(rhs.par_iter()).map(|(x, y)| x * y).sum();
//     let mut global_result = 0.0;
//     world.all_reduce_into(&local_result, &mut global_result, SystemOperation::sum());
//     global_result
// }
