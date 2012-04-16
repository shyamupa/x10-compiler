public class myclass()
{
	def static main():void
	{	
		var i,j:int;
		var temp,c,d:float;
		var a = new Array[float](8);
	
		a[0]= 34.3f;
		a[1] = 1.6f;
		a[2] = 555.555f;
		a[3] = 6.2443f;
		a[4] = 100.743f;
		a[5] = 233.342f;
		a[6] = 123.234f;
		a[7] = 222.234f;
	
	/*	a[0] = true;
		a[1] = false;
		a[2] = true;
		a[3] = false;
		a[4] = true;
		a[5] = false;
		a[6] = true;
		a[7] = false;
	*/	
		for ( i = 0; i <= 6 ; i = i + 1 )
		{
			for ( j = 0 ; j <= 6 - i ; j = j + 1 )
			{
				//println(j);
				c = a[j];
				d = a[j+1];
				if ( c < d )
				{
					temp = a[j] ;
					a[j] = a[j + 1] ;
					a[j + 1] = temp ;
				}
			}
		}
		for ( i = 0 ; i <= 7 ; i++ )
		{
			println(a[i]) ;
		}
		
		
	return;
	}
};


