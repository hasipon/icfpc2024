use serde::{Serialize, Deserialize};

#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct Problem {
	pub width:i64,
	pub height:i64,
	pub start:(i64, i64),
	pub blocks:Vec<bool>,
}
impl Problem {
	pub fn pos(&self, current:&(i64, i64)) -> usize
	{
		(current.0 + current.1 * self.width) as usize
	}
	pub fn contains(&self, current:&(i64, i64)) -> bool
	{
		0 <= current.0 && current.0 < self.width && 0 <= current.1 && current.1 < self.height
	}
}

#[derive(Serialize, Deserialize, Debug, Clone, PartialEq)]
pub enum Block
{
	Empty,
	Fill,
	R(Vec<Dir>, i64, usize),
}

#[derive(Serialize, Deserialize, Debug, Clone, PartialEq, Copy)]
pub enum Dir
{
	L,
	R,
	U,
	D
}

impl Dir
{
	pub fn to_pair(&self) -> (i64, i64) {
		match self
		{
			Dir::L => (-1,  0),
			Dir::R => ( 1,  0),
			Dir::D => ( 0,  1),
			Dir::U => ( 0, -1),
		}
	}
	pub fn invert(&self) -> Dir {
		match self
		{
			Dir::L => Dir::R,
			Dir::R => Dir::L,
			Dir::D => Dir::U,
			Dir::U => Dir::D,
		}
	}
	pub fn char(&self) -> char {
		match self
		{
			Dir::L => 'L',
			Dir::R => 'R',
			Dir::D => 'D',
			Dir::U => 'U',
		}
	}
	pub fn move_cursor(&self, current:&(i64, i64)) -> (i64, i64) {
		let pair = self.to_pair();
		(current.0 + pair.0, current.1 + pair.1)
	}
}
