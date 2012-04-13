public class myclass()
{
	def static myfun(x:boolean,y:int):int
	{
		var a:int;
		a = -1 * 7;		
		println(a);		
		return a; 
	}
	
	def static main():void
	{	
		var a:int;
		a = -myfun(true,2);
		println(a);
		return ;
	}
};
