public class myclass()
{
	
	def static myfun(x:boolean,y:int):void
	{
		var i,j:int;
		var a,b,c,d:boolean;
		a = true;
		b = false;
		i = 1;
		j = 2;
		
	    //assignment of boolean expression
		c = a == b;
		if(c)
		{
		println(95);
		}
		else
		{
		println(96);
		}
		
		//assignment of bool and
		d = a && b;
		if(d)
		{
		println(95);
		}
		else
		{
		println(96);
		}
		
		d = a || b;
		if(d)
		{
		println(95);
		}
		else
		{
		println(96);
		}
		
		
		d = a != b;
		if(d)
		{
		println(95);
		}
		else
		{
		println(96);
		}
		
		//control flow using boolean or
		if(a||b)
		{
		println(95);
		}
		else
		{
		println(96);
		}
		
		//control flow using boolean and
		if(a && b)
		{
		println(95);
		}
		else
		{
		println(96);
		}
		
		//control flow using boolean eq
		if(i==j)
		{
		println(95);
		}
		else
		{
		println(96);
		}
		
		//control flow using comparison between constant values
		if(2==3)
		{
		println(95);
		}
		else
		{
		println(96);
		}
			
		//control flow using inequality operator
		if(a!=b)
		{
		println(95);
		}
		else
		{
		println(96);
		}	
		
		a = true;	
		if(2!=3 && (a && b) || 4==5 || a)
		{
		println(95);
		}
		else
		{
		println(96);
		}
			
	return;  
	}
	
	def static main():void
	{	
		myfun(true,2);
		return;
	}
};
