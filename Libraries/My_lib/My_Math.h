#ifndef _MY_MATH_
#define _MY_MATH_

#include "headfile.h"

#define my_3_norm(x,y,z) (my_sqrt(my_pow((x)) + my_pow((y)) + my_pow((z))))
#define my_2_norm(x,y) (my_sqrt(my_pow((x)) + my_pow((y))))

#define my_pow(a) ((a)*(a))
#define safe_div(numerator,denominator,safe_value) ( (denominator == 0) ? (safe_value) : ((numerator)/(denominator)) )
#define ABS(x) ( (x)>0?(x):-(x) )
#define LIMIT( x,min,max ) ( (x) < (min)  ? (min) : ( (x) > (max) ? (max) : (x) ) )
#define _MIN(a, b) ((a) < (b) ? (a) : (b))
#define _MAX(a, b) ((a) > (b) ? (a) : (b))

#define my_pow_2_curve(in,a,max) (((1.0f - (a)) + (a) *ABS((in) / (max))) * in)

float my_sqrt(float number);
float fast_invSqrt(float x);
float my_abs(float f);

float my_avge_i(int a[], int size);
float my_avge_f(float a[], int size);
void bubble_sort(uint8 a[], int n);
float my_avge_i_0(int a[], int size);
float my_avge_f_0(float a[], int size);
double mx_sin(double rad);
double my_sin(double rad);
double my_cos(double rad);

extern float angle_to_radian;

#endif