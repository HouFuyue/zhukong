#include "all.h"


typedef struct
	{
		double x;
		double y;
	}Positio;
double car_para[3]={300.0f,365.0f,0.8828330147f};//�� ���� ��y���복�Խ��߽Ƕȣ�����
double r=236.2334650;
//�涨˳ʱ��omegaΪ����direction��1��4����Ϊ����2��3����Ϊ��
double factor=1.0f;// �������ת����

double aatan(double x,double y) 
{
	double a;
	if(x==0)
		{
		if(y>0)
			a=PI/2;
		else
			a=-PI/2;
		}
	else
		{a=atan(y/x);
	   if(y<0&&x<0)
		{
		a=a;
		factor=-1.0;
		} 
	   if(y<0&&x>0)
		{a=a+PI;
		factor=-1.0; 
		} 
	   if(y>0&&x>0)
		{
		a=a;
		factor=1.0;
		} 
	   if(y>0&&x<0)
		{a=a+PI;
		factor=1.0;
		} 
        }
 
		return a;
}
 
 
/*
����������������ϵ���ٶȣ���ת�ֽ�Ϊ�ĸ�ֱ�ֵ��ٶȷ���
���룺��������ϵ��Ŀ���ٶȣ�Ŀ���ٶȷ���Ŀ����ٶȣ�������ھ�������ϵ����Ŀǰ�ģ�
�����ÿ�����ӵ��ٶȼ��ٶȷ��򣨳�������ϵ��
*/
void Wheel_Vel(double vel,double direction,double omega,double pose_angle) //�Ƕ����Ϊ������
{
	Positio p,p1;
 struct wheel WHEEL;
	double v;
	double d;
	double w;
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
 
	
	WHEEL.fl.wheelangle=-90.0+aatan((p1.x+p.x),(p1.y+p.y))/PI*180.0;
  WHEEL.fl.wheelvel=factor*sqrtf((p1.x+p.x)*(p1.x+p.x)+(p1.y+p.y)*(p1.y+p.y));
		
	p.x=w*r*sin(car_para[2]);
	p.y=-w*r*cos(car_para[2]);
	
	WHEEL.fr.wheelangle=-90.0+aatan((p1.x+p.x),(p1.y+p.y))/PI*180.0;
	WHEEL.fr.wheelvel=factor*sqrtf((p1.x+p.x)*(p1.x+p.x)+(p1.y+p.y)*(p1.y+p.y));
	
	p.x=-w*r*sin(car_para[2]);
	p.y=w*r*cos(car_para[2]);
	
	WHEEL.bl.wheelangle=-90.0+aatan((p1.x+p.x),(p1.y+p.y))/PI*180.0;
	WHEEL.bl.wheelvel=factor*sqrtf((p1.x+p.x)*(p1.x+p.x)+(p1.y+p.y)*(p1.y+p.y));
	
	p.x=-w*r*sin(car_para[2]);
	p.y=-w*r*cos(car_para[2]);
	
	
	WHEEL.br.wheelangle=-90.0+aatan((p1.x+p.x),(p1.y+p.y))/PI*180.0;
	WHEEL.br.wheelvel=factor*sqrtf((p1.x+p.x)*(p1.x+p.x)+(p1.y+p.y)*(p1.y+p.y));
	
	set_motor(WHEEL);
}


/*
�������������ٶȼ����򸳸����
���룺���ַ��ٶȼ�����
�������
*/
void set_motor(struct wheel Wheel)
{
	Set_WheelLoc(0,Wheel.fl.wheelangle);
	Set_WheelLoc(1,Wheel.fr.wheelangle);
	Set_WheelLoc(2,Wheel.bl.wheelangle);
	Set_WheelLoc(3,Wheel.br.wheelangle);
	
	Set_OdriveSpd(0,Wheel.fl.wheelvel);
	Set_OdriveSpd(1,Wheel.fr.wheelvel);
	Set_OdriveSpd(2,Wheel.bl.wheelvel);
	Set_OdriveSpd(3,Wheel.br.wheelvel);
}
