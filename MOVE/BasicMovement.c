#include "BasicMovement.h"

struct wheel WheelsSpeed[2];//WheelsSpeed[0]�������������ٶ�,WheelsSpeed[1]��һ���ٶ�

/*
 * ������: InitWheelsSpeed
 * ��  ��: ��ʼ������WheelsSpeed[2]��
 * ��  �룺����P
 * ��  ��: ����P�복������ϵy��������н�
 * ��  ��: �ⲿ����
 */
void InitWheelsSpeed(void)
{
	int i = 0;
	for (; i < 2; i++)
	{
		WheelsSpeed[i].bl.wheelangle = 0;
		WheelsSpeed[i].bl.wheelvel = 0;
		WheelsSpeed[i].fl.wheelangle = 0;
		WheelsSpeed[i].fl.wheelvel = 0;
		WheelsSpeed[i].br.wheelangle = 0;
		WheelsSpeed[i].br.wheelvel = 0;
		WheelsSpeed[i].fr.wheelangle = 0;
		WheelsSpeed[i].fr.wheelvel = 0;
	}
}

/*
 * ������: GetVectorRadian
 * ��  ��: ������P�복������ϵy��������нǣ�˳ʱ��Ϊ��,���û����ơ�
 * ��  �룺����P
 * ��  ��: ����P�복������ϵy��������н�
 * ��  ��: �ⲿ����
 */
double GetVectorRadian(Position P)
{
	double radian = 0;
	if (P.x > 0)
		radian = pi / 2 - atan(P.y / P.x);
	else if (P.x < 0)
		radian = -pi / 2 - atan(P.y / P.x);
	else
	{
		if (P.y > 0)
			radian = 0;
		else if (P.y < 0)
			radian = pi;
	}
	return radian;
}

/*
 * ������: WheelsSpeed_Cycle
 * ��  ��: ����M���Խ��ٶ�w0(˳ʱ��Ϊ���������ƣ���תʱ�ĸ����ӵ��ٶȴ�С���Լ��ٶ��복������ϵy��������нǣ�˳ʱ��Ϊ��
           �н�λ��-pi/2~pi/2,���û����ơ�
 * ��  �룺��P���Կռ������Լ����ٶ�w0������GPS����b����GPS
 * ��  ��: �ĸ����ӵ��ٶȴ�С���Լ��ٶ��복������ϵy��нǱ���WheelsSpeed[0]
 * ��  ��: �ⲿ����
 */
void GetWheelsSpeed_Cycle(struct Point M, double w0)
{
	WheelsSpeed[1] = WheelsSpeed[0];
	
	struct Point TempPosition, TempPosition1;
//TempPosition�洢���ӵ�תȦ������
	TempPosition1.x = (GPS.position.y - M.y - LENGTH_LR / 2 * sin(GPS.radian) + LENGTH_FB / 2 * cos(GPS.radian));
	TempPosition1.y = (-GPS.position.x + M.x - LENGTH_FB / 2 * sin(GPS.radian) - LENGTH_LR / 2 * cos(GPS.radian));
	TempPosition.x = -TempPosition1.y;
	TempPosition.y = TempPosition1.x;
	WheelsSpeed[0].fr.wheelvel = GetLength(M, TempPosition) * fabs(w0);	
	WheelsSpeed[0].fr.wheelangle = GetVectorRadian(TempPosition1)-GPS.radian;	
	if (WheelsSpeed[0].fr.wheelangle > pi / 2)
	{
		WheelsSpeed[0].fr.wheelangle -= pi;
		WheelsSpeed[0].fr.wheelvel = -WheelsSpeed[0].fr.wheelvel;
	}
	if (WheelsSpeed[0].fr.wheelangle < -pi / 2)
	{
		WheelsSpeed[0].fr.wheelangle += pi;
		WheelsSpeed[0].fr.wheelvel = -WheelsSpeed[0].fr.wheelvel;
	}
	WheelsSpeed[0].fr.wheelangle = WheelsSpeed[0].fr.wheelangle / pi * 180;
	/**********************************/

	TempPosition1.x = (GPS.position.y - M.y + LENGTH_LR / 2 * sin(GPS.radian) + LENGTH_FB / 2 * cos(GPS.radian));
	TempPosition1.y = (-GPS.position.x + M.x - LENGTH_FB / 2 * sin(GPS.radian) + LENGTH_LR / 2 * cos(GPS.radian));
	TempPosition.x = -TempPosition1.y;
	TempPosition.y = TempPosition1.x;
	
	WheelsSpeed[0].fl.wheelvel = GetLength(M, TempPosition) * fabs(w0);
	WheelsSpeed[0].fl.wheelangle = GetVectorRadian(TempPosition1) - GPS.radian;

	if (WheelsSpeed[0].fl.wheelangle > pi / 2)
	{
		WheelsSpeed[0].fl.wheelangle -= pi;
		WheelsSpeed[0].fl.wheelvel = -WheelsSpeed[0].fl.wheelvel;
	}
	if (WheelsSpeed[0].fl.wheelangle < -pi / 2)
	{
		WheelsSpeed[0].fl.wheelangle += pi;
		WheelsSpeed[0].fl.wheelvel = -WheelsSpeed[0].fl.wheelvel;
	}

	/**********************************/

	TempPosition1.x = (GPS.position.y - M.y + LENGTH_LR / 2 * sin(GPS.radian) - LENGTH_FB / 2 * cos(GPS.radian));
	TempPosition1.y = (-GPS.position.x + M.x + LENGTH_FB / 2 * sin(GPS.radian) + LENGTH_LR / 2 * cos(GPS.radian));
	TempPosition.x = -TempPosition1.y;
	TempPosition.y = TempPosition1.x;
	
	WheelsSpeed[0].bl.wheelvel = GetLength(M, TempPosition) * fabs(w0);
	WheelsSpeed[0].bl.wheelangle = GetVectorRadian(TempPosition1) - GPS.radian;
	
	if (WheelsSpeed[0].bl.wheelangle > pi / 2)
	{
		WheelsSpeed[0].bl.wheelangle -= pi;
		WheelsSpeed[0].bl.wheelvel = -WheelsSpeed[0].bl.wheelvel;
	}
	if (WheelsSpeed[0].bl.wheelangle < -pi / 2)
	{
		WheelsSpeed[0].bl.wheelangle += pi;
		WheelsSpeed[0].bl.wheelvel = -WheelsSpeed[0].bl.wheelvel;
	}
	
	/**********************************/

	TempPosition1.x = (GPS.position.y - M.y - LENGTH_LR / 2 * sin(GPS.radian) - LENGTH_FB / 2 * cos(GPS.radian));
	TempPosition1.y = (-GPS.position.x + M.x + LENGTH_FB / 2 * sin(GPS.radian) - LENGTH_LR / 2 * cos(GPS.radian));
	TempPosition.x = -TempPosition1.y;
	TempPosition.y = TempPosition1.x;
	
	WheelsSpeed[0].br.wheelvel = GetLength(M, TempPosition) * fabs(w0);
	WheelsSpeed[0].br.wheelangle = GetVectorRadian(TempPosition1) - GPS.radian;
	
	if (WheelsSpeed[0].br.wheelangle > pi / 2)
	{
		WheelsSpeed[0].br.wheelangle -= pi;
		WheelsSpeed[0].br.wheelvel = -WheelsSpeed[0].br.wheelvel;
	}
	if (WheelsSpeed[0].br.wheelangle < -pi / 2)
	{
		WheelsSpeed[0].br.wheelangle += pi;
		WheelsSpeed[0].br.wheelvel = -WheelsSpeed[0].br.wheelvel;
	}

}

/*
 * ������: GetWheelsSpeed_Line
 * ��  ��: ����������v,�����������ϵy��������н�theta����ֱ��ʱ�ĸ����ӵ��ٶȴ�С���Լ��ٶ��복������ϵy��������нǣ�˳ʱ��Ϊ��
		   �н�λ��-90~90,���ýǶ��ơ�
 * ��  �룺����v���н�theta
 * ��  ��: �ĸ����ӵ��ٶȴ�С���Լ��ٶ��복������ϵy��нǱ���WheelsSpeed[0]
 * ��  ��: �ⲿ����
 */
void GetWheelsSpeed_Line(double v,double theta)
{
	WheelsSpeed[1] = WheelsSpeed[0];
	WheelsSpeed[0].bl.wheelvel = WheelsSpeed[0].br.wheelvel = WheelsSpeed[0].fl.wheelvel = WheelsSpeed[0].fl.wheelvel = v;
	theta = (theta - GPS.radian);
	if (theta> pi/2)
	{
		WheelsSpeed[0].br.wheelangle =theta- pi;
		WheelsSpeed[0].bl.wheelvel = WheelsSpeed[0].br.wheelvel = WheelsSpeed[0].fl.wheelvel = WheelsSpeed[0].fl.wheelvel = -v;
	}
	if (theta <- pi/2)
	{
		WheelsSpeed[0].br.wheelangle = theta + pi;
		WheelsSpeed[0].bl.wheelvel = WheelsSpeed[0].br.wheelvel = WheelsSpeed[0].fl.wheelvel = WheelsSpeed[0].fl.wheelvel = -v;
	}
}

void Set_WheelLoc (int WheelID , float WheelDiraction)
{
	Mode[WheelID] = Location_Mode ;
	set_loc[WheelID] = 8192.0 * 140.0 / 360.0 * WheelDiraction ;
}


//���������ٶ� ��mm/s
void Set_OdriveSpd ( int WheelID , float OdriveSpeed )
{
	double n ; //�ﵽOdriveSpeed���踳��odrive�Ķ�Ӧ��ֵ
	n = OdriveSpeed * 8192.0 / 3.1415926 / 105.0 ;
	
 	if ( WheelID == 0 )
	{
		USART_printf( USART1 , " v 0 %lf 0\n ",n) ;
	}
	
	 	if ( WheelID == 1 )
	{
		USART_printf( USART3 , " v 0 %lf 0\n ",n) ;
	}

	 	if ( WheelID == 2 )
	{
		USART_printf( USART1 , " v 1 %lf 0\n ",n) ;
	}
	
	 	if ( WheelID == 3 )
	{
		USART_printf( USART3 , " v 1 %lf 0\n ",n) ;
	}
}


/*
�������������ٶȼ����򸳸����
���룺���ַ��ٶȼ�����
�������
*/
void set_motor(struct wheel Wheel)
{
	Set_WheelLoc(1,Wheel.fl.wheelangle);
	Set_WheelLoc(2,Wheel.fr.wheelangle);
	Set_WheelLoc(3,Wheel.bl.wheelangle);
	Set_WheelLoc(4,Wheel.br.wheelangle);
	
	Set_OdriveSpd(0,Wheel.fl.wheelvel);
	Set_OdriveSpd(1,Wheel.fr.wheelvel);
	Set_OdriveSpd(2,Wheel.bl.wheelvel);
	Set_OdriveSpd(3,Wheel.br.wheelvel);
}


double car_para[3]={300.0f,365.0f,0.8828330147f};//�� ���� ��y���복�Խ��߽Ƕȣ�����
float r=236.2334650;
//�涨˳ʱ��omegaΪ����direction��1��4����Ϊ����2��3����Ϊ��
float factor=1.0f;// 

float aatan(float x,float y) 
{
	double a;
	if(x==0)
		{
		if(y>0)
			a=pi/2;
		else
			a=-pi/2;
		}
	else
		{a=atan(y/x);
	   if(y<0&&x<0)
		{
		a=a;
		factor=-1.0;
		} 
	   if(y<0&&x>0)
		{a=a+pi;
		factor=-1.0; 
		} 
	   if(y>0&&x>0)
		{
		a=a;
		factor=1.0;
		} 
	   if(y>0&&x<0)
		{a=a+pi;
		factor=1.0;
		} 
        }
 
		return a;
}
 
struct wheel anotherWheelsSpeed;


/*
���룺��������ϵ��Ŀ���ٶȣ�Ŀ���ٶȷ���Ŀ����ٶȣ�������ھ�������ϵ����Ŀǰ�ģ�
�����ÿ�����ӵ��ٶȼ��ٶȷ��򣨳�������ϵ��
*/
struct wheel Wheel_vel(float vel,float direction,float omega,float pose_angle) //�Ƕ����Ϊ������
{
	Position p,p1;
 struct wheel WHEEL;
	float v;
	float d;
	float w;
 //ת������������ϵ
	v=vel;
	d=direction-pose_angle;
	w=omega;
	//���ַ��ٶ�
		v=vel;
	d=direction-pose_angle;
	w=omega;
 
	p1.x=v*sin(d);
	p1.y=v*cos(d);
 
	p.x=w*r*sin(car_para[2]);
	p.y=w*r*cos(car_para[2]);
 
	WHEEL.fl.wheelvel=factor*sqrtf((p1.x+p.x)*(p1.x+p.x)+(p1.y+p.y)*(p1.y+p.y));
	WHEEL.fl.wheelangle=90.0-aatan((p1.x+p.x),(p1.y+p.y))/PI*180.0;
 
		
	p.x=w*r*sin(car_para[2]);
	p.y=-w*r*cos(car_para[2]);
	WHEEL.fr.wheelvel=factor*sqrtf((p1.x+p.x)*(p1.x+p.x)+(p1.y+p.y)*(p1.y+p.y));
	WHEEL.fr.wheelangle=90.0f-aatan((p1.x+p.x),(p1.y+p.y))/PI*180;
	
	p.x=-w*r*sin(car_para[2]);
	p.y=w*r*cos(car_para[2]);
	WHEEL.bl.wheelvel=factor*sqrtf((p1.x+p.x)*(p1.x+p.x)+(p1.y+p.y)*(p1.y+p.y));
	WHEEL.bl.wheelangle=90.0f-aatan((p1.x+p.x),(p1.y+p.y))/PI*180;
	
	p.x=-w*r*sin(car_para[2]);
	p.y=-w*r*cos(car_para[2]);
	WHEEL.br.wheelvel=factor*sqrtf((p1.x+p.x)*(p1.x+p.x)+(p1.y+p.y)*(p1.y+p.y));
	WHEEL.br.wheelangle=90.0f-aatan((p1.x+p.x),(p1.y+p.y))/PI*180;
	
	return WHEEL;
}
