public class myclass()
{
	
	def myfun(x:int):int
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
	
	def main():void
	{	
		var result:int;
		result=myfun(5);
		println(result);
		return ;
	}
};

