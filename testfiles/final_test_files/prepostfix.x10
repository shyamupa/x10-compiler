public class myclass()
{
	def static main():void
	{	
		var i,j,k:int;
		i = 2;
		j = 0;
		//Here i is leaving its value on the stack
		j = i++ + i++ + ++i;	//Expected output is 10
		println(j);
		j = 1 < 2 ? i++ : --i ;	//Expected output is 5
		println(j);
		
		
		//i won't leave its value on the stack
		for(i = 3; i > 1 ; --i)	//Expected output is 3 & 2
		{
			println(i);
		}
		
		
		//Miscellaneous
		i=0;
		j=2;
		if(i++ == --j)			//Expected output is 0
		{
			println(1);
		}
		else
		{
			println(0);		
		}
		return;
	}
};



