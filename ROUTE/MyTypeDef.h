#ifndef __MYTYPEDEF_H
#define __MYTYPEDEF_H

#include "sys.h"

//��ṹ��
struct Point
{
    double x;
    double y;
};

struct Gyro_State
{
    int32_t  value;
    int32_t  count;
};

struct Encoder_State
{
    int32_t Now;
    int32_t Last;
    int32_t Total;
    double Convert1;        //��תϵ��
    double Convert2;        //��תϵ��
    double Distance;
    double Radius;          //������תʱ���̵���ת�뾶
    double radian;          //�����복������ϵY��������ļн�
    int8_t dir;             //�ı�����ת�����������Ҫ�ķ�������1��������-1��
};

struct GPS_State
{
    struct Point position; //��ǰ����    
    double distancestep1;  //����1����ǰ������
    double distancestep2;  //����2����ǰ������
    double distance1;      //����1ǰ������
    double distance2;      //����2ǰ������
    double angle;          //��ǰ�Ƕ�         
    double radian;         //��ǰ����
};

#endif 
