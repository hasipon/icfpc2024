
extern crate serde_json;
extern crate serde;
extern crate rand;
extern crate chrono;

mod data;
use data::*;
use rand::Rng;
use std::{fs};

fn main() -> Result<(), Box<dyn std::error::Error>> {
    for i in 20..21 {
        println!("start: {}", i + 1);
        match solve(i + 1) 
        {
            Ok(()) => {
                println!("finish: {}", i + 1);
            },
            Err (error) => {
                println!("error: {} : {:?}", i + 1 , error);
            }
        }
    }
    Ok(())
}

fn solve(number:u32) -> Result<(), Box<dyn std::error::Error>> {
    let path = format!("../../../problems/lambdaman/{}.txt", number);
    let data:String = fs::read_to_string(path)?; 
    let problem:Problem = parse_problem(&data)?;
    let mut answer_string = String::new();
    let mut state = Vec::new();
    for block in problem.blocks 
    {
        if block 
        {
            state.push(Block::Fill)
        }
        else 
        {
            state.push(Block::Empty)
        }
    }

    // ランダム移動フェーズ
    let mut current = problem.start.clone();
    let dirs = [Dir::L, Dir::R, Dir::D, Dir::U];
    let mut rng = rand::thread_rng();
    let mut prev_dir: Dir = dirs[rng.gen_range(0..4)];
    let mut index = 0;
    'outside: loop {
        {
            let dir = prev_dir.clone();
            let pair = dir.to_pair();
            let next = (current.0 + pair.0, current.1 + pair.1);
            if 
                0 <= next.0 && next.0 < problem.width &&
                0 <= next.1 && next.1 < problem.height &&
                state[(next.0 + next.1 * problem.width) as usize] == Block::Empty
            {
                let arrow = Arrow{ dir: dir.clone(), index };
                let mut vec = Vec::new();
                vec.push(arrow);
                state[(current.0 + current.1 * problem.width) as usize] = Block::R(false, vec, index);
                current = next;
                index += 50000;
                prev_dir = dir;
                continue;
            }
        }
        for dir in &dirs
        {
            let pair = dir.to_pair();
            let next = (current.0 + pair.0, current.1 + pair.1);
            if 
                0 <= next.0 && next.0 < problem.width &&
                0 <= next.1 && next.1 < problem.height &&
                state[(next.0 + next.1 * problem.width) as usize] == Block::Empty
            {
                let arrow = Arrow{ dir: dir.clone(), index };
                let mut vec = Vec::new();
                vec.push(arrow);
                state[(current.0 + current.1 * problem.width) as usize] = Block::R(false, vec, index);
                current = next;
                index += 50000;
                prev_dir = dir.clone();
                continue 'outside;
            }
        }
        state[(current.0 + current.1 * problem.width) as usize] = Block::R(false, Vec::new(), index);
        break;
    }
    current = problem.start.clone();
    index = 0;
    let mut dir_current = 0;
    let mut history:Vec<usize> = Vec::new();
    'outside: loop {
        let dir = dirs[dir_current];
        let pair = dir.to_pair();
        let next = (current.0 + pair.0, current.1 + pair.1);
        if 
            0 <= next.0 && next.0 < problem.width &&
            0 <= next.1 && next.1 < problem.height &&
            state[(next.0 + next.1 * problem.width) as usize] == Block::Empty
        {
            if let Block::R(even, arrows, index) = &mut state[(current.0 + current.1 * problem.width) as usize]
            {
                arrows.push(Arrow{ dir, index:*index });
                history.push(dir_current);
                state[(next.0 + next.1 * problem.width) as usize] = Block::R(true, Vec::new(), *index);
                current = next;
                dir_current = 0;
            }
            continue;
        }
        else 
        {
            dir_current += 1;
            while dir_current >= 4
            {
                if let Option::Some(last) =  history.pop()
                {
                    dir_current = last;
                    let pair = dirs[dir_current].to_pair();
                    current = (current.0 - pair.0, current.1 - pair.1);
                    dir_current += 1;
                }
                else 
                {
                    if let Block::R(even, arrows, index) = &state[(current.0 + current.1 * problem.width) as usize]
                    {
                        if arrows.len() > 0
                        {
                            let pair = arrows[0].dir.to_pair();
                            current = (current.0 + pair.0, current.1 + pair.1);
                            dir_current = 0;
                        }
                        else 
                        {
                            break 'outside;
                        }
                    }
                    else
                    {
                        break 'outside;
                    }
                }
            }
        }
    }
    
    current = problem.start.clone();
    index = 0;
    let mut history:Vec<Dir> = Vec::new();
    loop {
        if let Block::R(even, arrows, index) = &mut state[(current.0 + current.1 * problem.width) as usize]
        {
            if let Option::Some(arrow) = arrows.pop()
            {
                let pair = arrow.dir.to_pair();
                current = (current.0 + pair.0, current.1 + pair.1);
                if *even || arrows.len() > 0
                {
                    history.push(arrow.dir);
                }
                answer_string.push(arrow.dir.char());
            }
            else if let Option::Some(dir) =  history.pop()
            {
                let pair = dir.to_pair();
                current = (current.0 - pair.0, current.1 - pair.1);
                answer_string.push(dir.invert().char());
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }

    println!("{}", answer_string);
    fs::write(
        format!("../../../solutions/lambdaman/{}-shohei1.txt", number), 
        &answer_string
    )?;
    Ok(())
}

fn parse_problem(problem:&String) -> Result<Problem, Box<dyn std::error::Error>>
{
    let mut width = 0;
    let mut height = 0;
    let mut start = (0, 0);
    let mut blocks = Vec::new();
    let mut i = 0;

    for char in problem.chars()
    {
        match char
        {
            '#' => {
                blocks.push(true);
                i += 1;
            },
            '.' => {
                blocks.push(false);
                i += 1;
            },
            'L' => {
                start = (i, height);
                blocks.push(false);
                i += 1;
            },
            '\n' | '\r' => {
                if i != 0
                {
                    width = i;
                    height += 1;
                    i = 0;
                }
            },
            _ => {}
        }
    }
    Ok(Problem{ width, height, start, blocks })
}
