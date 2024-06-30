package;
import haxe.DynamicAccess;
import haxe.Http;
import haxe.Json;
import haxe.Resource;
import js.Browser;
import js.html.CanvasElement;
import js.html.Element;
import js.html.InputElement;
import js.html.InputEvent;
import js.html.KeyEvent;
import js.html.KeyboardEvent;
import js.html.TextAreaElement;
import pixi.core.Application;
import pixi.core.graphics.Graphics;
import data.Data;

class Main
{
	private static var problems       :Array<Problem> = [];
	private static var state          :State;
	private static var mainPixi       :Application;
	private static var problemGraphics:Graphics;
	
	static function main() 
	{
		var mainCanvas = cast Browser.document.getElementById("pixi");
		mainPixi = new Application({
			view  :mainCanvas,
			transparent: true,
			width: mainCanvas.width,
			height: mainCanvas.height,
			autoResize: true,
		});
		mainPixi.stage.addChild(problemGraphics = new Graphics());
		
		// 問題取得
		for (i in 0...21)
		{
			var num = i + 1;
			var name = num + ".txt";
			var skippable = 
				num == 4 || 
				(11 <= num && num <= 16);
			
			var width = 0;
			var height = 0;
			var source = Resource.getString(name);
			var roads = [];
			var x = 0;
			var y = 0;
			var startX = 0;
			var startY = 0;
			for (i in 0...source.length)
			{
				var char = source.charAt(i);
				if (char == "#")
				{
					roads.push(false);
					x += 1;
				}
				else if (char == ".")
				{
					roads.push(true);
					x += 1;
				}
				else if (char == "L")
				{
					roads.push(true);
					startX = x;
					startY = y;
					x += 1;
				}
				else
				{
					if (x != 0) {
						width = x; 
						y += 1;
					}
					x = 0;
				}
			}
			height = y;
			problems.push({
				roads: roads,
				startX: startX,
				startY: startY,
				width: width,
				height: height,
				problemSize: if (width > height) width else height,
				stepSize: if (skippable) 2 else 1,
			});
		}
		Browser.document.getElementById("problem").addEventListener(
			"change",
			refresh
		);
		Browser.document.getElementById("problem").addEventListener(
			"input",
			refresh
		);
		Browser.window.addEventListener(
			"keydown",
			keyDown
		);
		refresh();
	}
	
	private static function refresh():Void 
	{
		var form:InputElement = cast Browser.document.getElementById("problem");
		var problem = problems[Std.parseInt(form.value) - 1];
		state = {
			moves: [],
		}
		draw();
	}
	
	private static function draw():Void
	{
		var form:InputElement = cast Browser.document.getElementById("problem");
		var problem = problems[Std.parseInt(form.value) - 1];
		
		problemGraphics.clear();
		var scale = 500 / problem.problemSize;
		problemGraphics.beginFill(0x111111);
		problemGraphics.drawRect(
			0,
			0,
			500,
			500,
		);
		var remains = [for (b in problem.roads) b];
		var sx = problem.startX;
		var sy = problem.startY;
		remains[sx + sy * problem.width] = false;
		function move(dx:Int, dy:Int, len:Int)
		{
			for (_ in 0...len)
			{
				var nextX = sx + dx;
				var nextY = sy + dy;
				if (
					0 <= nextX && nextX < problem.width &&
					0 <= nextY && nextY < problem.height &&
					problem.roads[nextX + nextY * problem.width]
				)
				{
					remains[nextX + nextY * problem.width] = false;
					sx = nextX;
					sy = nextY;
				}
				else
				{
					break;
				}
			}
		}
		for (m in state.moves)
		{
			switch m
			{
				case R: move( 1,  0, problem.stepSize);
				case L: move(-1,  0, problem.stepSize);
				case U: move( 0, -1, problem.stepSize);
				case D: move( 0,  1, problem.stepSize);
				case r: move( 1,  0, problem.problemSize);
				case l: move(-1,  0, problem.problemSize);
				case u: move( 0, -1, problem.problemSize);
				case d: move( 0,  1, problem.problemSize);
			}
		}
		for (x in 0...problem.width)
		{
			for (y in 0...problem.height)
			{
				problemGraphics.beginFill(
					if (problem.roads[x + y * problem.width]) 0x888888 else 0x111111,
					1
				);
				problemGraphics.drawRect(
					x * scale,
					y * scale,
					scale,
					scale,
				);
				if (remains[x + y * problem.width])
				{
					problemGraphics.beginFill(
						0xFFFF00,
					);
					problemGraphics.drawCircle(
						(x + 0.5) * scale,
						(y + 0.5) * scale,
						scale / 5,
					);
				}
				if (sx == x && sy == y)
				{
					problemGraphics.beginFill(
						0xFF0000,
					);
					problemGraphics.drawCircle(
						(x + 0.5) * scale,
						(y + 0.5) * scale,
						scale / 3,
					);
				}
			}
		}
		var form:TextAreaElement = cast Browser.document.getElementById("solution");
		var result = problem.problemSize + "\n" + problem.stepSize + "\n";
		for (move in state.moves)
		{
			result += move;
		}
		form.innerHTML = result;
	}
	
	public static function keyDown(e:KeyboardEvent):Void
	{
		if (!e.ctrlKey)
		{
			switch e.keyCode
			{
				case KeyboardEvent.DOM_VK_W | KeyboardEvent.DOM_VK_COMMA: addMove(if (e.shiftKey) Move.U else Move.u); e.preventDefault();
				case KeyboardEvent.DOM_VK_S | KeyboardEvent.DOM_VK_O    : addMove(if (e.shiftKey) Move.D else Move.d); e.preventDefault();
				case KeyboardEvent.DOM_VK_A : addMove(if (e.shiftKey) Move.L else Move.l); e.preventDefault();
				case KeyboardEvent.DOM_VK_D | KeyboardEvent.DOM_VK_E    : addMove(if (e.shiftKey) Move.R else Move.r); e.preventDefault();
				case KeyboardEvent.DOM_VK_Z    : undo(); e.preventDefault();
				case KeyboardEvent.DOM_VK_R    : reset(); e.preventDefault();
			}
		}
	}
	
	public static function addMove(move:Move):Void
	{
		state.moves.push(move);
		draw();
	}
	
	public static function undo():Void
	{
		state.moves.pop();
		draw();
	}
	
	public static function reset():Void 
	{
		state.moves.resize(0);
		draw();
	}
}
