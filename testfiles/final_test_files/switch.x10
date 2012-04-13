public class myclass()
{
	
	def static myfun(x:boolean,y:int):int
	{
		var i:int;
		switch(y)
		{
		case 1 :{
			switch(3)
				{
				case 3 : {
						 println(3);
						 
						 }
			 	case 4 : {
						 for(i=1;i<10;i=i+1)
							{
								println(23);
								if(i == 5)
								{
								break;
								}
							}	
						  }
									 	
				}
			 } 		 
		case 2 : {
			println(4);
			break;
			 }		
		default : println(8);
		}		 
	return 9;
	}
	
	def static main():void
	{	
		var i:int;
		i = myfun(true,1);
		return ;
	}
};

