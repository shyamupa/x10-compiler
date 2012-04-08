public class myclass
{	
	def main():void
	{	
		var i,j:int;
		for(i = 1; i<=5; i=i+1)
		{
			for(j=1; j<=i; j=j+1)
			{
				println(j);
			}
			if(i == 3)
			{
				break;
			}	
		}
		return ;
	}
};


