use serde::{Serialize, Deserialize};

#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct Problem {
	pub width:i64,
	pub height:i64,
	pub start:(i64, i64),
	pub blocks:Vec<bool>,
}


#[derive(Serialize, Deserialize, Debug, Clone, PartialEq)]
pub enum Block
{
	Empty,
	Fill,
	R(bool, Vec<Arrow>, i64),
}

#[derive(Serialize, Deserialize, Debug, Clone, PartialEq)]
pub struct Arrow
{
	pub index:i64,
	pub dir:Dir,
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
}
