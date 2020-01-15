#ifndef _BASICMOVEMENT_H
#define _BASICMOVEMENT_H

#include "all.h"

//��ṹ��
typedef struct Point Position;

typedef struct
{
    double wheelvel;  //����ٶȣ������ɸ���Ϊ�����ת��������
    double wheelangle; //���ƽ���복��������ǰ���нǣ�˳ʱ��Ϊ������Сλ��-pi/2��pi/2֮��
}wheelspeed_para;

struct wheel
{
    wheelspeed_para fl;//ǰ����
    wheelspeed_para fr;//ǰ����
    wheelspeed_para bl;//������
    wheelspeed_para br;//������
};


#define LENGTH_FB 4  //����ǰ���ֳ���
#define LENGTH_LR 4  //���������ֳ���
extern struct wheel WheelsSpeed[2];

void InitWheelsSpeed(void);
void InitGPS_List(void);
double GetVectorRadian(Position P);
void GetWheelsSpeed_Cycle(struct Point M, double w0);
void GetWheelsSpeed_Line(double v, double theta);
#endif 
