//#include "common.h"
#include "My_Math.h"


#define ONE_PI   (3.14159265)

float angle_to_radian = 0.01745f;//角度转弧度

//快速平方根算法
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

//快速平方根倒数算法
float fast_invSqrt(float x)
{
  float half_x = 0.5 * x;
  int i = *((int *)&x); // 以整数方式读取X
  i = 0x5f3759df - (i>>1); // 神奇的步骤,计算第一个近似根
  x = *((float *)&i); // 再以浮点方式读取i
  x = x*(1.5 - (half_x * x * x)); // 牛顿迭代一遍提高精度
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

//求绝对值
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

void bubble_sort(uint8 a[], int n)    //下面是函数bubble_sort的程序 
{
    uint8 i,j,temp;    //定义三个整型变量 
    for (j=0;j<n-1;j++)    //用一个嵌套循环来遍历一遍每一对相邻元素 （所以冒泡函数慢嘛，时间复杂度高）  
    {                           
        for (i=0;i<n-1-j;i++)
        {
            if(a[i]<a[i+1])  //从大到小排就把左边的">"改为"<" ！！！
            {
                temp=a[i];      //a[i]与a[i+1](即a[i]后面那个) 交换
                a[i]=a[i+1];    //基本的交换原理"c=a;a=b;b=c" 
                a[i+1]=temp;
            }
        }
    }    
}
