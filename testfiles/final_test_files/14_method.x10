public class newclass(a:int,e:int)
{
	
	def myfun(x:int,y:int):void
	{
		println(x+y);		
		return; 
	}
};
public class myclass()
{
	def static main():void
	{
		val obj:newclass=new newclass();
		obj.myfun(12,1);
		return;
	}
};
