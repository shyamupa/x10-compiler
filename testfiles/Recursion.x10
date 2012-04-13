public class myclass()
{
	def myfun(b:int):void
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

	def main():void
	{	
		var i:int;
		i = 1;
		myfun(i);
		return;
	}
};



