
extern crate serde_json;
extern crate serde;
extern crate rand;
extern crate chrono;

mod data;
use data::*;
use std::{fs, os::windows::process};

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let id = "shohei2";
    let dirss = [
        [Dir::L, Dir::R, Dir::D, Dir::U],
        [Dir::L, Dir::R, Dir::U, Dir::D],
        [Dir::L, Dir::D, Dir::R, Dir::U],
        [Dir::L, Dir::D, Dir::U, Dir::R],
        [Dir::L, Dir::U, Dir::R, Dir::D],
        [Dir::L, Dir::U, Dir::D, Dir::R],
        [Dir::R, Dir::L, Dir::D, Dir::U],
        [Dir::R, Dir::L, Dir::U, Dir::D],
        [Dir::R, Dir::D, Dir::L, Dir::U],
        [Dir::R, Dir::D, Dir::U, Dir::L],
        [Dir::R, Dir::U, Dir::L, Dir::D],
        [Dir::R, Dir::U, Dir::D, Dir::L],
        [Dir::D, Dir::R, Dir::L, Dir::U],
        [Dir::D, Dir::R, Dir::U, Dir::L],
        [Dir::D, Dir::L, Dir::R, Dir::U],
        [Dir::D, Dir::L, Dir::U, Dir::R],
        [Dir::D, Dir::U, Dir::R, Dir::L],
        [Dir::D, Dir::U, Dir::L, Dir::R],
        [Dir::U, Dir::R, Dir::D, Dir::L],
        [Dir::U, Dir::R, Dir::L, Dir::D],
        [Dir::U, Dir::D, Dir::R, Dir::L],
        [Dir::U, Dir::D, Dir::L, Dir::R],
        [Dir::U, Dir::L, Dir::R, Dir::D],
        [Dir::U, Dir::L, Dir::D, Dir::R],
    ];
    for i in 0..21 {
        let number = i + 1;
        let path = format!("../../../solutions/lambdaman/{}-{}.txt", number, id);
        fs::remove_file(path.clone());
        for dirs in dirss
        {
            match solve(number, path.clone(), &dirs)
            {
                Ok(()) => {
                    println!("finish: {}", i + 1);
                },
                Err (error) => {
                    println!("error: {} : {:?}", i + 1 , error);
                }
            }
        }
    }
    Ok(())
}

fn solve(number:i64, output:String, dirs:&[Dir; 4]) -> Result<(), Box<dyn std::error::Error>> {
    let path = format!("../../../problems/lambdaman/{}.txt", number);
    let data:String = fs::read_to_string(path)?; 
    let problem:Problem = parse_problem(&data)?;
    let mut answer_string = String::new();
    let mut state = Vec::new();
    let mut size = 0;
    for block in &problem.blocks
    {
        if *block 
        {
            state.push(Block::Fill)
        }
        else 
        {
            size += 1;
            state.push(Block::Empty)
        }
    }
    let mut current = problem.start.clone();
    let mut dir_index = 0;
    let mut stack = Vec::new();
    let mut index = 0;
    state[problem.pos(&current)] = Block::R(Vec::new(), index, 0);
    size -= 1;
    while size > 0 {
        let dir = dirs[dir_index];
        let next = dir.move_cursor(&current);
        let pos = problem.pos(&next);
        if problem.contains(&next) && state[pos] == Block::Empty
        {
            if let Block::R(arrows, _, _) = &mut state[problem.pos(&current)]
            {
                arrows.push(dir);
            }
            state[pos] = Block::R(Vec::new(), index, 0);
            current = next;
            stack.push(dir_index);
            index += 1;
            size -= 1;
            dir_index = 0;
        }
        else {
            dir_index += 1;    
        }
        while dir_index >= 4
        {
            dir_index = stack.pop().unwrap();
            let dir = dirs[dir_index].invert();
            if let Block::R(arrows, _, _) = &mut state[problem.pos(&current)]
            {
                arrows.push(dir)
            }
            current = dir.move_cursor(&current);
            index -= 1;
            dir_index += 1;
        }
    }

    // 回答作成フェーズ
    let mut current = problem.start.clone();
    loop {
        if let Block::R(arrows, _, processed) = &mut state[(current.0 + current.1 * problem.width) as usize]
        {
            if *processed < arrows.len()
            {
                let arrow = arrows[*processed];
                let pair = arrow.to_pair();
                current = (current.0 + pair.0, current.1 + pair.1);
                answer_string.push(arrow.char());
                *processed += 1;
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

    let prev = fs::read_to_string(output.clone()); 
    if prev.is_err() || prev.unwrap().len() > answer_string.len()
    {
        println!("{}", answer_string);
        fs::write(
            output, 
            &answer_string
        )?;
    }
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
