#if macro
package ;
import sys.io.File;
import haxe.macro.Context;
import haxe.Resource;
import sys.FileSystem;

class Macro 
{
	public static function init() 
	{
		for (file in FileSystem.readDirectory("../../problems/lambdaman"))
		{
			Context.addResource(file, File.getBytes("../../problems/lambdaman/" + file));
		}
	}
}
#end