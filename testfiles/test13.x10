public class myclass
{
	def main():void
	{	
		var i,a:int;
		var t = Array[int](5);
		a = 3;
		for(i = 0;i<5;i=i+1)
		{
			t[i] = a;
			a = a + 1;
		}
		for(i = 0;i<5;i=i+1)
		{
			t[i] += a;
		}
		for(i = 0;i<5;i=i+1)
		{
			println(t[i]);
		}
		a -= t[2];
		println(a); 
		return;
	}
};


