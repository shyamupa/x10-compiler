public class myclass()
{
	def static myfun(b:int):void
	{	
		var a:int;
		a = b + 1;
		if(a>20)
		{
			return;
		}
		println(a);
		a++;
		myfun(a);
		return;
	}

	def static main():void
	{	
		var i:int;
		i = 1;
		val objref: someclass=new someclass();
		var x:int
		var y:int;
		objref.myfun();
		return;
	}
};



