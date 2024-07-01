package data ;

typedef Problem = 
{
	roads: Array<Bool>,
	startX: Int,
	startY: Int,
	width: Int,
	height: Int,
	problemSize:Int,
	stepSize:Int,
}

typedef State = 
{
	x:Int,
	y:Int,
	moves   : Array<Move>,
}

enum abstract Move(String)
{
	var R;
	var L;
	var U;
	var D;
	var r;
	var l;
	var u;
	var d;
}
