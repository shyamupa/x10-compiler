public class newclass(a:int,e:int)
{
	def newclass(i:int,j:int):void
	{
		a=i;
		e=j+a;
	}
	def private fun2():void
	{
		println(17);
		return;
	}
};
public class myclass()
{
	def static main():void
	{
		var i:int;
		println(6);
		val obj:newclass=new newclass(1,2);
		obj.fun2();
	}
};
