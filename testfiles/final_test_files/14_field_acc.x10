public class newclass(a:int,e:int)
{
	
	def newclass(i:int,j:int):void
	{
		this.a=i*100;
		this.e=j;
	}
	def myfun(x:int,y:int):void
	{
		var b:boolean;
		b = false;
		println(6);
		return;		
	}
};
public class myclass()
{
	def myclass(w:int,t:int):void
	{
		println(10);
	}
	def static main():void
	{
		var i:int;
		println(6);
		val obj:newclass=new newclass(1,2);
		obj.myfun(12,1);
		
		i=obj.a+obj.e;
		
		println(obj.a);
		println(obj.e);
		println(i);
		return;
	}
};
