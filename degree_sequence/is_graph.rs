// (5,5,5,4,3,2,1,1)

use std::io;

fn main() {
    let mut seq = String::new();
    io::stdin()
        .read_line(&mut seq)
        .expect("Failed to read line");

    seq.truncate(seq.len() - 2);
    let seq = seq.split_off(1);
    let xs: Vec<&str> = seq.split(',').collect();

    let xs: Vec<i32> = xs
        .into_iter()
        .map(|x| x.trim().parse().expect("Enter a number!"))
        .collect();

    if is_graph(xs) {
        println!("Input sequence is the degree sequence for some graph");
    } else {
        println!("Input sequence is not a degree sequence.");
    }
}

fn is_graph(xs: Vec<i32>) -> bool {
    let mut s = 0;
    for x in &xs {
        if *x < 0 {
            return false;
        }
        s += *x;
    }
    if 0 == s {
        return true;
    }
    let x0 = &xs[0];
    let x0: usize = *x0 as usize;
    let mut ys: Vec<i32> = vec![];
    for i in 1..(xs.len()) {
        if i <= x0 {
            ys.push(xs[i] - 1);
        } else {
            ys.push(xs[i]);
        }
        ys.sort();
        ys.reverse();
    }
    is_graph(ys)
}
