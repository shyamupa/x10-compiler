public class myclass()
{	
	def static fun1():void
	{
		var x:int;
		x=10;
		println(x);
		return;
	}
	def static main():void
	{	
		var x:int;
		x=12;
		println(x);
		fun1();
		{
			var x:int;
			x=13;
			println(x);
		}
		return ;
	}
};


