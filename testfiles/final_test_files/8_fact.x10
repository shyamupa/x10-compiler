public class myclass()
{
	
	def static myfun(x:int):int
	{
		var a:int;
		if(x==1)
		{
			return 1;
		}
		else
		{
			return x*myfun(x-1);
		}
	}
	
	def static main():void
	{	
		var result:int;
		result=myfun(5);
		println(result);
		
		result=myfun(6);
		println(result);
		
		result=myfun(7);
		println(result);
		
		return ;
	}
};

