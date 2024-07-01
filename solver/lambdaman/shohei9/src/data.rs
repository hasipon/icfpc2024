use serde::{Serialize, Deserialize};

#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct Problem {
	pub width:i64,
	pub height:i64,
	pub start:(i64, i64),
	pub roads:Vec<bool>,
	pub heat_map:Vec<f64>,
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
	pub fn is_road(&self, current:&(i64, i64)) -> bool
	{
		self.contains(current) && self.roads[self.pos(current)]
	}
}

#[derive(Serialize, Deserialize, Debug, Clone, PartialEq)]
pub struct State
{
	pub history:Vec<Seed>,
	pub rand_mod:i64,
	pub rand_offset:i64,
	pub position:(i64, i64),
	pub remains:Vec<bool>,
	pub score:f64,
	pub value:i64,
}

#[derive(Serialize, Deserialize, Debug, Clone, PartialEq, Copy)]
pub struct Seed
{
	pub a:i64,
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
