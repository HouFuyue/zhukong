#include "all.h" 

/*���ڵ�����Ƶ���غ���*/




//�����ӵ��� WheelDiraction ���Ƕ���
void Set_WheelLoc (int WheelID , double WheelDiraction)
{
	Mode[WheelID] = Location_Mode ;
	set_loc[WheelID] = 8192.0f * 140.0f / 360.0f * WheelDiraction ;
}


//���������ٶ� ��mm/s
void Set_OdriveSpd ( int WheelID , double OdriveSpeed )
{
	double n ; //�ﵽOdriveSpeed���踳��odrive�Ķ�Ӧ��ֵ
	n = OdriveSpeed * 8192.0 /PI / 105.0 ;
	
 	if ( WheelID == 0 )
	{
		USART_printf( USART2 , "v 0 %lf 0\n",n) ;
	}
	
	 	if ( WheelID == 1 )
	{
		USART_printf( USART2 , "v 1 %lf 0\n",n) ;
	}

	 	if ( WheelID == 2 )
	{
		USART_printf( USART3 , "v 1 %lf 0\n",n) ;
	}
	
	 	if ( WheelID == 3 )
	{
		USART_printf( USART3 , "v 0 %lf 0\n",n) ;
	}
}


