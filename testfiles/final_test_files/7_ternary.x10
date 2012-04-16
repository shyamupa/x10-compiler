// Finding min using ternary
public class myclass()
{	
	def static main():void
	{	
		var a,b,c,min:int;
		a = 3;
		b = 2;
		c = 1;
		
		min=(a<b ? a : b);
		println(min); 
		
		println(a<b ? a : b); 

		min = (a<b ? a : b) + 2;
		println(min); 

		min = ((a<b) ? ( a<c ? a : c) : b) ;
		println(min);

		min = min < c ? min : c;
		println(min);
				
		return ;
	}
};


