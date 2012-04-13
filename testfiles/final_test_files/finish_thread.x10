public class myclass()
{
	
	def static myfun():int
	{
		var i:int;
		for(i=0;i<100;i++)
		{
		println(1);		
		}		
		return (6+7); 
	}
	
	def static main():void
	{	
		var i:int;
		finish { 
			async {myfun();};
		        };
		for(i=0;i<100;i++)
		{
		println(6);		
		}		

		return;
	}
};

