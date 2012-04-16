public class myclass()
{
	
	def static myfun(x:boolean,y:int):int
	{
		while(true)
		{		
		println(1);
		y=y+1;
		if(y == 6)
		{
		break;
		}
		}
		//return(6+7); 
	}
	
	def static main():void
	{	
		myfun(true,2);
		return;
	}
};

