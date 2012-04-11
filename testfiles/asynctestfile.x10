public class myclass
{
	
	def myfun():int
	{
		while(true)
		{
			println(1);		
		}	
		
		return (6+7); 
	}
	
	def main():void
	{	async {myfun();}
		while(true)
		{
			println(2);
		}
		return;
	}
};

