public class myclass
{
	
	def myfun(x:boolean,y:int):int
	{
		switch(y)
		{
		case 1 :  println(1);
		case 2 : println(2);
		default : println(8);
		}		 
	}
	
	def main():void
	{	
		myfun(true,1);
		return ;
	}
};

