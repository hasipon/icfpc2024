
extern crate serde_json;
extern crate serde;
extern crate rand;
extern crate chrono;

mod data;
use data::*;
use rand::{thread_rng, Rng};
use std::{fs::{self, File}, mem::{self}};
use std::io::Write;

fn main() -> Result<(), Box<dyn std::error::Error>> {
    
    for i in 17..21 {
        let number = i + 1;
        let id = "shohei6";
        let path = format!("../../../solutions/lambdaman/{}-{}.rand", number, id);
        let path2 = format!("../../../solutions/lambdaman/{}-{}.randr", number, id);
        match solve(number, path.clone(), path2.clone())
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

fn solve(number:i64, mut output:String, mut output2:String) -> Result<(), Box<dyn std::error::Error>> {
    let path = format!("../../../problems/lambdaman/{}.txt", number);
    let data:String = fs::read_to_string(path)?; 
    let dirs = [Dir::R, Dir::D, Dir::L, Dir::U];
    let problem:Problem = parse_problem(&data, &dirs)?;
    let mut states = Vec::new();
    let start = 9i64;
    let base_a = 799155963i64;
    let base_m = 1000000007i64;
    let b = 1951i64;
    let segment = 200;
    let max_a = 93;
    
    let dir_len;
    let dir_seq;
    let dir_interval;
    
    if 11 <= number && number <= 16
    {
        dir_len = 2;
        dir_interval = 2;
        dir_seq = vec![Dir::R, Dir::R, Dir::D, Dir::D, Dir::L, Dir::L, Dir::U, Dir::U];
    }
    else
    {
        dir_len = 1;
        dir_interval = 1;
        dir_seq = vec![Dir::R, Dir::D, Dir::L, Dir::U];
    }
    for _ in 0..30
    {
        let mut state = State {
            history: Vec::new(),
            current: start,
            position: problem.start.clone(),
            remains: problem.roads.clone(),
            score: 999999999999999999f64,
        };
        state.remains[problem.pos(&state.position)] = false;
        states.push(state);
    }

    let mut cleared_states:Vec<State> = Vec::new();
    let mut best_state:Option<State> = Option::None;

    let mut rng = thread_rng();
    for phase in 0..250
    {
        println!("{} - score:{}", phase, states[0].score);
        let mut next_states:Vec<State> = Vec::new();
        let mut cleared = 0;
        for state in &states
        {
            let mut a = 0;
            loop 
            {
                a += rng.gen_range(1..11);
                if a > max_a { break; }

                let mut s = state.clone();
                let seed = Seed { a, };
                s.history.push(seed);
                for _ in 0..segment
                {
                    let mut offset = (s.current * dir_interval) as usize;
                    offset %= dir_seq.len();
                    for dir in &dir_seq[offset..(offset + dir_len)]
                    {
                        let next = dir.move_cursor(&s.position);
                        if problem.is_road(&next)
                        {
                            s.position = next;
                            if s.remains[problem.pos(&next)]
                            {
                                cleared += 1;
                                s.remains[problem.pos(&next)] = false;
                            }
                        }
                    }
                    s.current = ((base_a * seed.a) * s.current + b) % (base_m);
                }
                next_states.push(s);
            }
        }

        for state in &mut next_states
        {
            let mut count = 0;
            let mut score = 0.0;
            for i in 0..problem.roads.len()
            {
                if !state.remains[i] { continue; }

                score += problem.heat_map[i];
                count += 1;
            }

            // クリア
            if count == 0
            {
                cleared_states.push(state.clone());
                continue;
            }
            
            {
                // 最も近い点を求める
                let mut values = vec![state.position];
                let mut next_values = Vec::new();
                let mut i = 0;
                let mut moved = vec![false; problem.roads.len()];
                'out: while values.len() > 0 
                {
                    i += 1;
                    for current in &values
                    {
                        for dir in dirs
                        {
                            let next = dir.move_cursor(current);
                            let pos = problem.pos(&next);
                            if problem.is_road(&next) && !moved[pos]
                            {
                                moved[pos] = true;
                                next_values.push(next);

                                if state.remains[pos]
                                {
                                    score -= problem.heat_map[pos] / (i + 1) as f64;
                                    break 'out;
                                }
                            }
                        }
                    }
                    mem::swap(&mut values, &mut next_values);
                    next_values.clear();
                }
            }
            state.score = score;
        }

        if cleared_states.len() > 0
        {
            let mut min = max_a + 1;
            for state in cleared_states
            {
                let mut a = 0;
                for seed in &state.history
                {
                    if seed.a > a { a = seed.a; }
                }
                if a < min
                {
                    best_state = Option::Some(state);
                    min = a;
                }
            }
            break;
        }
        let len = next_states.len();
        next_states.sort_by(|a, b| a.score.partial_cmp(&b.score).unwrap());
        if 2000 < len
        {
            next_states.drain(2000..len);
        }
        states = next_states;
    }

    if let Option::None = best_state
    {
        best_state = Option::Some(states[0].clone());
        output += "failed";
        output2 += "failed";
    }
    if let Option::Some(state) = best_state
    {
        let mut file1 = File::create(output)?;
        let mut file2 = File::create(output2)?;
        let mut dir_string = String::new();
        for d in &dir_seq
        {
            dir_string.push_str(&format!("{:?}", d));
        }
        writeln!(file1, "{} {} {}", dir_string, dir_len, dir_interval)?;
        writeln!(file1, "{} {} {} {} {}", start, segment, base_a, base_m, b)?;
        let mut current = start;
        for seed in &state.history
        {
            writeln!(file1, "{}", seed.a)?;
            for _ in 0..segment
            {
                let mut offset = (current * dir_interval) as usize;
                offset %= dir_seq.len();
                for dir in &dir_seq[offset..(offset + dir_len)]
                {
                    write!(file2, "{:?}", dir)?;
                }
                current = ((base_a + seed.a) * current + b) % base_m;
            }
        }
        file2.flush()?;
    }
    Ok(())
}

fn parse_problem(problem:&String, dirs:&[Dir; 4]) -> Result<Problem, Box<dyn std::error::Error>>
{
    let mut width = 0;
    let mut height = 0;
    let mut start = (0, 0);
    let mut roads = Vec::new();
    let mut i = 0;

    for char in problem.chars()
    {
        match char
        {
            '#' => {
                roads.push(false);
                i += 1;
            },
            '.' => {
                roads.push(true);
                i += 1;
            },
            'L' => {
                start = (i, height);
                roads.push(true);
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
    let heat_map = vec![0.0; roads.len()];
    let mut problem = Problem{ width, height, start, roads, heat_map };
    let mut distances = vec![i64::MAX; problem.roads.len()];
    let mut states = vec![start.clone()];
    let mut next_states = vec![];
    let mut last = states[0];

    // 端点を探す
    let mut i = 0;
    while states.len() > 0 {
        i += 1;
        for state in &states
        {
            for dir in dirs
            {
                let next = dir.move_cursor(state);
                let pos = problem.pos(&next);
                if problem.is_road(&next) && distances[pos] > i
                {
                    distances[pos] = i;
                    last = next;
                    next_states.push(next);
                }
            }
        }
        mem::swap(&mut states, &mut next_states);
        next_states.clear();
    }
    let mut distances = vec![i64::MAX; problem.roads.len()];
    let mut states = vec![last];
    let mut next_states = vec![];
    let mut last = states[0];

    // 逆の端点を探す
    let mut i = 0;
    while states.len() > 0 {
        i += 1;
        for state in &states
        {
            for dir in dirs
            {
                let next = dir.move_cursor(state);
                let pos = problem.pos(&next);
                if problem.is_road(&next) && distances[pos] > i
                {
                    distances[pos] = i;
                    last = next;
                    next_states.push(next);
                }
            }
        }
        mem::swap(&mut states, &mut next_states);
        next_states.clear();
    }
    let distances1 = distances.clone();

    // 逆端点からの距離を算出
    let mut distances = vec![i64::MAX; problem.roads.len()];
    let mut states = vec![last];
    let mut next_states = vec![];
    let mut i = 0;
    while states.len() > 0 {
        i += 1;
        for state in &states
        {
            for dir in dirs
            {
                let next = dir.move_cursor(state);
                let pos = problem.pos(&next);
                if problem.is_road(&next) && distances[pos] > i
                {
                    distances[pos] = i;
                    next_states.push(next);
                }
            }
        }
        mem::swap(&mut states, &mut next_states);
        next_states.clear();
    }
    let distances2 = distances.clone();

    // 中心点を算出
    let mut min = i64::MAX;
    let mut center = (0, 0);
    for i in 0..problem.roads.len()
    {
        if !problem.roads[i] { continue; }
        let score = (distances1[i] - distances2[i]).abs() * 100 + distances1[i] + distances2[i];
        if min > score
        {
            min = score;
            center = (i as i64 % problem.width, i as i64 / problem.width);
        }
    }
    
    // 中心点からの距離をヒートマップに反映
    let mut distances = vec![i64::MAX; problem.roads.len()];
    let mut states = vec![center];
    let mut next_states = vec![];
    let mut i = 0;
    while states.len() > 0 {
        i += 1;
        for state in &states
        {
            for dir in dirs
            {
                let next = dir.move_cursor(state);
                let pos = problem.pos(&next);
                if problem.is_road(&next) && distances[pos] > i
                {
                    distances[pos] = i;
                    let value = i as f64;
                    problem.heat_map[pos] = 0.0001 * 1.1_f64.powf(value);
                    next_states.push(next);
                }
            }
        }
        mem::swap(&mut states, &mut next_states);
        next_states.clear();
    }
    Ok(problem)
}
