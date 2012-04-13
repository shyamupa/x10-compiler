public class myclass()
{
	def static main():void
	{	
		var i,j,k:int;
		for(i = 2; i<=20; i++)
		{
			k = 0;
			j = 2;
			while(j<i)
			{
				if((i % j) == 0)
				{
					k = 1;
					break;
				}
				j++;
			}
			if(k!=1)
			{
				println(i);
			}
		}
		return;
	}
};



