package;
import haxe.DynamicAccess;
import haxe.Http;
import haxe.Json;
import haxe.Resource;
import js.Browser;
import js.html.CanvasElement;
import js.html.Element;
import js.html.InputElement;
import js.html.TextAreaElement;
import pixi.core.Application;
import pixi.core.graphics.Graphics;
import data.Data;

class Main
{
	private static var problems       :Array<Problem> = [];
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
			var blocks = [];
			var x = 0;
			var y = 0;
			var startX = 0;
			var startY = 0;
			for (i in 0...source.length)
			{
				var char = source.charAt(i);
				if (char == "#")
				{
					blocks.push(true);
					x += 1;
				}
				else if (char == ".")
				{
					blocks.push(false);
					x += 1;
				}
				else if (char == "L")
				{
					blocks.push(false);
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
				blocks: blocks,
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
		refresh();
	}
	
	private static function refresh():Void 
	{
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
		for (x in 0...problem.width)
		{
			for (y in 0...problem.height)
			{
				problemGraphics.beginFill(
					if (problem.blocks[x + y * problem.width]) 0x111111 else 0x888888,
					1
				);
				problemGraphics.drawRect(
					x * scale,
					y * scale,
					scale,
					scale,
				);
			}
		}
	}
}
