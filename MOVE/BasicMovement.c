#include "BasicMovement.h"

struct wheel WheelsSpeed;//保留各轮毂电机最新速度

/*
 * 函数名: InitWheelsSpeed(void)
 * 描  述: 初始化变量WheelsSpeed[2]。
 * 输  入：向量P
 * 输  出: 向量P与车身坐标系y轴正方向夹角
 */
void InitWheelsSpeed(void)
{
		struct wheel Wheelsangle={{0,0},{0,0},{0,0},{0,0}};
}

/*
 * 函数名: GetVectorRadian(Position P)
 * 描  述: 求向量P与车身坐标系y轴正方向夹角，顺时针为正,采用弧度制。
 * 输  入：向量P
 * 输  出: 向量P与车身坐标系y轴正方向夹角
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
 * 函数名: GetVectorLength(Position P)
 * 描  述: 求向量P的模
 * 输  入：向量P
 * 输  出: 向量P的模
 */
double GetVectorLength(Position P)
{
	return sqrt(P.x * P.x + P.y * P.y);
}

/*
 * 函数名: WheelsSpeed_Cycle(struct Point M, double w0)
 * 描  述: 求绕M点以角速度w0(顺时针为正，弧度制）旋转时四个轮子的速度大小和以及速度与车身坐标系y轴正方向夹角，顺时针为正.

 * 输  入：点P绝对空间坐标以及角速度w0，车身GPS坐标b变量GPS
 * 输  出: 四个轮子的速度大小和以及速度与车身坐标系y轴夹角变量WheelsSpeed[0]
 */
void GetWheelsSpeed_Cycle(struct Point M, double w0)
{
	if (w0 == 0)
	{
		WheelsSpeed.fl.wheelvel = WheelsSpeed.fr.wheelvel= WheelsSpeed.bl.wheelvel = WheelsSpeed.br.wheelvel=0;
    }
	else
	{
		struct Point TempPosition, TempPosition1;
		//TempPosition存储轮子到转圈的向量
		TempPosition1.x = w0*(GPS.position.y - M.y - LENGTH_LR / 2 * sin(GPS.radian) + LENGTH_FB / 2 * cos(GPS.radian));
		TempPosition1.y = w0*(-GPS.position.x + M.x - LENGTH_FB / 2 * sin(GPS.radian) - LENGTH_LR / 2 * cos(GPS.radian));
		TempPosition.x = -TempPosition1.y/w0;
		TempPosition.y = TempPosition1.x/w0;
		WheelsSpeed.fr.wheelvel = GetVectorLength( TempPosition) * fabs(w0);
		WheelsSpeed.fr.wheelangle = GetVectorRadian(TempPosition1) - GPS.radian;
		if (WheelsSpeed.fr.wheelangle > pi / 2)
		{
			WheelsSpeed.fr.wheelangle -= pi;
			WheelsSpeed.fr.wheelvel = -WheelsSpeed.fr.wheelvel;
		}
		if (WheelsSpeed.fr.wheelangle < -pi / 2)
		{
			WheelsSpeed.fr.wheelangle += pi;
			WheelsSpeed.fr.wheelvel = -WheelsSpeed.fr.wheelvel;
		}
		
		/**********************************/

		TempPosition1.x = w0*(GPS.position.y - M.y + LENGTH_LR / 2 * sin(GPS.radian) + LENGTH_FB / 2 * cos(GPS.radian));
		TempPosition1.y = w0*(-GPS.position.x + M.x - LENGTH_FB / 2 * sin(GPS.radian) + LENGTH_LR / 2 * cos(GPS.radian));
		TempPosition.x = -TempPosition1.y/w0;
		TempPosition.y = TempPosition1.x/w0;

		WheelsSpeed.fl.wheelvel = GetVectorLength( TempPosition) * fabs(w0);
		WheelsSpeed.fl.wheelangle = GetVectorRadian(TempPosition1) - GPS.radian;

		if (WheelsSpeed.fl.wheelangle > pi / 2)
		{
			WheelsSpeed.fl.wheelangle -= pi;
			WheelsSpeed.fl.wheelvel = -WheelsSpeed.fl.wheelvel;
		}
		if (WheelsSpeed.fl.wheelangle < -pi / 2)
		{
			WheelsSpeed.fl.wheelangle += pi;
			WheelsSpeed.fl.wheelvel = -WheelsSpeed.fl.wheelvel;
		}
	
		/**********************************/

		TempPosition1.x = w0*(GPS.position.y - M.y + LENGTH_LR / 2 * sin(GPS.radian) - LENGTH_FB / 2 * cos(GPS.radian));
		TempPosition1.y = w0*(-GPS.position.x + M.x + LENGTH_FB / 2 * sin(GPS.radian) + LENGTH_LR / 2 * cos(GPS.radian));
		TempPosition.x = -TempPosition1.y/w0;
		TempPosition.y = TempPosition1.x/w0;

		WheelsSpeed.bl.wheelvel = GetVectorLength(TempPosition) * fabs(w0);
		WheelsSpeed.bl.wheelangle = GetVectorRadian(TempPosition1) - GPS.radian;

		if (WheelsSpeed.bl.wheelangle > pi / 2)
		{
			WheelsSpeed.bl.wheelangle -= pi;
			WheelsSpeed.bl.wheelvel = -WheelsSpeed.bl.wheelvel;
		}
		if (WheelsSpeed.bl.wheelangle < -pi / 2)
		{
			WheelsSpeed.bl.wheelangle += pi;
			WheelsSpeed.bl.wheelvel = -WheelsSpeed.bl.wheelvel;
		}
		
		/**********************************/

		TempPosition1.x = w0*(GPS.position.y - M.y - LENGTH_LR / 2 * sin(GPS.radian) - LENGTH_FB / 2 * cos(GPS.radian));
		TempPosition1.y = w0*(-GPS.position.x + M.x + LENGTH_FB / 2 * sin(GPS.radian) - LENGTH_LR / 2 * cos(GPS.radian));
		TempPosition.x = -TempPosition1.y/w0;
		TempPosition.y = TempPosition1.x/w0;

		WheelsSpeed.br.wheelvel = GetVectorLength( TempPosition) * fabs(w0);
		WheelsSpeed.br.wheelangle = GetVectorRadian(TempPosition1) - GPS.radian;

		if (WheelsSpeed.br.wheelangle > pi / 2)
		{
			WheelsSpeed.br.wheelangle -= pi;
			WheelsSpeed.br.wheelvel = -WheelsSpeed.br.wheelvel;
		}
		if (WheelsSpeed.br.wheelangle < -pi / 2)
		{
			WheelsSpeed.br.wheelangle += pi;
			WheelsSpeed.br.wheelvel = -WheelsSpeed.br.wheelvel;
		}
		
	}
}

/*
 * 函数名: Run_Cycle(struct Point M, double w0)
  * 描  述: 让车子绕M点以角速度w0(顺时针为正，弧度制）旋转。
 * 输  入：点P绝对空间坐标以及角速度w0，车身GPS坐标b变量GPS
 * 输  出: 四个轮子的速度大小(m/s)和以及速度与车身坐标系y轴夹角变量WheelsSpeed[0]
 * 调  用: 外部调用
 */
void Run_Cycle(struct Point M, double w0)
{
	GetWheelsSpeed_Cycle( M, w0);
	set_motor(WheelsSpeed);	
}
/*
 * 函数名: GetWheelsSpeed_Line(double v,double theta)
 * 描  述: 求车子以速率v,沿与绝对坐标系y轴正方向夹角theta方向直行时四个轮子的速度大小和以及速度与车身坐标系y轴正方向夹角，顺时针为正
		       夹角位于-pi-pi,采用弧度制。
 * 输  入：速率v，夹角theta
 * 输  出: 四个轮子的速度大小和以及速度与车身坐标系y轴夹角变量WheelsSpeed[0]
 * 调  用: 外部调用
 */
void GetWheelsSpeed_Line(double v,double theta)
{
	
	WheelsSpeed.bl.wheelvel = WheelsSpeed.br.wheelvel = WheelsSpeed.fl.wheelvel = WheelsSpeed.fl.wheelvel = v;
	theta = (theta - GPS.radian);
	if (theta> pi/2)
	{
		WheelsSpeed.br.wheelangle =theta- pi;
		WheelsSpeed.bl.wheelvel = WheelsSpeed.br.wheelvel = WheelsSpeed.fl.wheelvel = WheelsSpeed.fl.wheelvel = -v;
	}
	if (theta <- pi/2)
	{
		WheelsSpeed.br.wheelangle = theta + pi;
		WheelsSpeed.bl.wheelvel = WheelsSpeed.br.wheelvel = WheelsSpeed.fl.wheelvel = WheelsSpeed.fl.wheelvel = -v;
	}
}

/*
 * 函数名: Run_Line(double v,double theta)
 * 描  述: 让车子以速率v,沿与绝对坐标系y轴正方向夹角theta（弧度制)方向直行,夹角位于-pi-pi.
 * 输  入：速率v，夹角theta
 * 输  出: 四个轮子的速度大小和以及速度与车身坐标系y轴夹角变量WheelsSpeed[0]
 * 调  用: 外部调用
 */

void Run_Line(double v,double theta)
{
	GetWheelsSpeed_Line( v,theta);
	set_motor(WheelsSpeed);
}

