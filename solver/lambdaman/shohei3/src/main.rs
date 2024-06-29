
extern crate serde_json;
extern crate serde;
extern crate rand;
extern crate chrono;

mod data;
use data::*;
use std::{fs, mem, os::windows::process};

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let id = "shohei3";
    let dirss = [
        [Dir::R, Dir::D, Dir::U, Dir::L],
    ];
    for i in 3..4 {
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
    
    // 一番遠い点を求める
    let mut distance = Vec::new();
    for block in &problem.blocks
    {
        if *block {
            distance.push(-1);
        } else {
            distance.push(99999999999i64);
        }
    }
    let mut current = problem.start.clone();
    let mut d = 0;
    distance[problem.pos(&current)] = 0;
    let mut vec0 = vec![current];
    let mut vec1 = Vec::new();
    let mut target = current.clone();
    while vec0.len() > 0 
    {
        d += 1;
        for current in &vec0
        {
            for dir in dirs
            {
                let next = dir.move_cursor(&current);
                if !problem.contains(&next) { continue; }
                let pos = problem.pos(&next);
                if distance[pos] > d
                {
                    distance[pos] = d;
                    vec1.push(next);
                    target = next.clone();
                }
            }
        }
        mem::swap(&mut vec0, &mut vec1);
        vec1.clear();
    }
    current = target;
    state[problem.pos(&current)] = Block::R(vec![], d, 0);
    for i in 0..d
    {
        let d2 = d - i - 1;
        for dir in dirs
        {
            let next = dir.move_cursor(&current);
            if !problem.contains(&next) { continue; }
            let pos = problem.pos(&next);
            if distance[pos] == d2
            {
                state[problem.pos(&next)] = Block::R(vec![dir.invert()], d2, 0);
                current = next;
                break;
            }
        }
    }
    
    let mut current = problem.start.clone();
    let mut dir_current = 0;
    let mut history:Vec<usize> = Vec::new();
    'outside: loop {
        let dir = dirs[dir_current];
        let next = dir.move_cursor(&current);
        if problem.contains(&next) && state[problem.pos(&next)] == Block::Empty
        {
            if let Block::R(arrows, index, processed) = &mut state[problem.pos(&current)]
            {
                arrows.push(dir);
                history.push(dir_current);
                state[problem.pos(&next)] = Block::R(vec![dir.invert()], *index, 0);
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
                    if let Block::R(arrows, index, processed) = &state[(current.0 + current.1 * problem.width) as usize]
                    {
                        if arrows.len() > 0
                        {
                            current = arrows[0].move_cursor(&current);
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
    // 回答作成フェーズ
    let mut current = problem.start.clone();
    loop {
        if let Block::R(arrows, _, processed) = &mut state[problem.pos(&current)]
        {
            if *processed < arrows.len()
            {
                let arrow = arrows[arrows.len() - *processed - 1];
                let pair = arrow.to_pair();
                current = (current.0 + pair.0, current.1 + pair.1);
                *processed += 1;
                answer_string.push(arrow.char());
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
