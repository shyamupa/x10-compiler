public class myclass
{
	def main():void
	{	
		var i,j,temp,c,d:int;
		var a = Array[int](8);
		a[0]= 34;
		a[1] = 1;
		a[2] = 12;
		a[3] = 6;
		a[4] = 100;
		a[5] = 233;
		a[6] = 123;
		
		for ( i = 0; i <= 3 ; i = i + 1 )
		{
			//println(i);
			for ( j = 0 ; j <= 3 - i ; j = j + 1 )
			{
				//println(j);
				c = a[j];
				d = a[j+1];
				if ( c > d )
				{
					temp = a[j] ;
					a[j] = a[j + 1] ;
					a[j + 1] = temp ;
				}
				temp = 1;
			}
		}
		for ( i = 0 ; i <= 4 ; i++ )
		{
			println(a[i]) ;
		}
	return;
	}
};


