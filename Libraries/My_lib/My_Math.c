//#include "common.h"
#include "My_Math.h"


#define ONE_PI   (3.14159265)

float angle_to_radian = 0.01745f;//�Ƕ�ת����

//����ƽ�����㷨
float my_sqrt(float number)
{
	long i;
	float x, y;
	const float f = 1.5F;
	x = number * 0.5F;
	y = number;
	i = * ( long * ) &y;
	i = 0x5f3759df - ( i >> 1 );

	y = * ( float * ) &i;
	y = y * ( f - ( x * y * y ) );
	y = y * ( f - ( x * y * y ) );
	return number * y;
}

//����ƽ���������㷨
float fast_invSqrt(float x)
{
  float half_x = 0.5 * x;
  int i = *((int *)&x); // ��������ʽ��ȡX
  i = 0x5f3759df - (i>>1); // ����Ĳ���,�����һ�����Ƹ�
  x = *((float *)&i); // ���Ը��㷽ʽ��ȡi
  x = x*(1.5 - (half_x * x * x)); // ţ�ٵ���һ����߾���
  return x;
}


double mx_sin(double rad)
{   
  double sine;
  if (rad < 0)
    sine = rad * (1.27323954f + 0.405284735f * rad);
  else
    sine = rad * (1.27323954f - 0.405284735f * rad);
  if (sine < 0)
    sine = sine*(-0.225f * (sine + 1) + 1);
  else
    sine = sine * (0.225f *( sine - 1) + 1);
  return sine;
}

double my_sin(double rad)
{
  int8 flag = 1;
  
  while(rad > 2*ONE_PI)
  {
    rad = rad -  2*ONE_PI;
  }
  if (rad >= ONE_PI)
  {
    rad -= ONE_PI;
    flag = -1;
  }
  
  return mx_sin(rad) * flag;
}

double my_cos(double rad)
{
  int8 flag = 1;
  rad += ONE_PI/2.0;
  
  while(rad > 2*ONE_PI)
  {
    rad = rad -  2*ONE_PI;
  }
  if (rad >= ONE_PI)
  {
    flag = -1;
    rad -= ONE_PI;
  }
  return my_sin(rad)*flag;
}

//�����ֵ
float my_abs(float f)
{
	if (f >= 0.0f)
	{
		return f;
	}

	return -f;
}


float my_avge_i(int a[], int size)
{
	uint8 i, sum;
	float avge;
	sum = 0;
	for (i = 0; i < size; i++)
        {
		sum += a[i];
        }
	avge = sum / (float)size;
	return avge;
}

float my_avge_i_0(int a[], int size)
{
  uint8 i, sum;
	float avge, dele;
	sum = 0;
	for (i = 0; i < size; i++)
        {
          if(a[i] != 0)
          {
		sum += a[i];
                dele++;
          }
        }
	avge = sum / dele;
	return avge;
}

float my_avge_f(float a[], int size)
{
	uint8 i, sum;
	float avge;
	sum = 0;
	for (i = 0; i < size; i++)
		sum += a[i];
	avge = sum / (float)size;
	return avge;
}

float my_avge_f_0(float a[], int size)
{
  uint8 i, sum;
	float avge, dele;
	sum = 0;
	for (i = 0; i < size; i++)
        {
          if(a[i] != 0)
          {
		sum += a[i];
                dele++;
          }
        }
	avge = sum / dele;
	return avge;
}

void bubble_sort(uint8 a[], int n)    //�����Ǻ���bubble_sort�ĳ��� 
{
    uint8 i,j,temp;    //�����������ͱ��� 
    for (j=0;j<n-1;j++)    //��һ��Ƕ��ѭ��������һ��ÿһ������Ԫ�� ������ð�ݺ������ʱ�临�Ӷȸߣ�  
    {                           
        for (i=0;i<n-1-j;i++)
        {
            if(a[i]<a[i+1])  //�Ӵ�С�žͰ���ߵ�">"��Ϊ"<" ������
            {
                temp=a[i];      //a[i]��a[i+1](��a[i]�����Ǹ�) ����
                a[i]=a[i+1];    //�����Ľ���ԭ��"c=a;a=b;b=c" 
                a[i+1]=temp;
            }
        }
    }    
}
