#include "Car_Ctrl.h"


Task_Ctr_Strcuct Task;
Carry_Obj_Struct Carry;
Carry_Obj_Struct Carry2;

/******************************ģʽѡ��*****************************/
//#define MODE 0        ////����
#define MODE 1        ////����
//#define MODE 2        ////�Ѷ�
 
/*-----------------------------------
|              ��Ʒ��(744)          |
|                                   |
|                                   |
|                | \                |
|                 \ DIR:2           |
| ��              \               ��|
| ��              \               ��|
| ��      <-------*------->       ��|
|(1050)    DIR:1  \    DIR:3   (426)|
|                 \                 |
|                 \                 |
|           DIR:0 \                 |
|                \ /         ////////
|                            /  ��  |
|                            /  ��  |
|                            /  ��  |
-----------------------------------*/
char Scan2_Complete = 0;
unsigned char colour_rec=0,colour_rec1=0,colour_rec2=0;


//���ھ�����ͼ�ϴ󣬴˴�Ϊ��ӵ�����У׼��
float Check_Point_X[3],Check_Point_Y[3];

/**********************����״̬��Ԥ��ģʽ��ȷ������Ҫ�ٵ���************************/
/**********************����״̬�ھ���ģʽ����Ҫ����ģʽ��ͬ�����л�******************/

float  Pos_Accuracy;
short int id=0,flag=-1;
short int step,step_flag,step2,step_flag2;
char Round;

/******************************************************************************/
//��������
/******************************************************************************/
void Parament_Init()//������ʼ��
{

    //��λ����(<n����)
    Pos_Accuracy=3.0f;
    
    //���������(���10000)
    Duty_MAX =  8000;
    Duty_MIN = -8000;    
    Duty_MAX =  8000;
    Duty_MIN = -8000;
    
    //PID����
    //λ�û�
    Position.Pid[X].Kp=1.0f;//X����P
    Position.Pid[X].Ki=0.0f; //X����I
    Position.Pid[X].Kd=0.0f; //X����D
    
    Position.Pid[Y].Kp=1.0f;//Y����P
    Position.Pid[Y].Ki=0.0f; //Y����I
    Position.Pid[Y].Kd=0.0f; //Y����D
    
    Position.Pid[W].Kp=1100.0f;//ƫ����P
    Position.Pid[W].Ki=0.0f;   //ƫ����I
    Position.Pid[W].Kd=7000.0f; //ƫ����D 
    
    //�ٶȻ�
    Speed_Kp = 5.0f;
    Speed_Kd = 0.0f;
    
    
    Area_Init();//����λ�ó�ʼ��
    Servo_Position_Init();//�����̬��ʼ��
    Colour_Position_Init();//��ɫ˳���ʼ��

}

void Task_Init()//�����ʼ��
{   
    /*���²���Ĭ��״̬�½�ֹ�޸ģ���������������������������������������������*/
    /*���²���Ĭ��״̬�½�ֹ�޸ģ���������������������������������������������*/
    /*���²���Ĭ��״̬�½�ֹ�޸ģ���������������������������������������������*/
    Task.ID=0;//��ʼ����ID��Ϊ0��������0��ʼִ��
    Task.Status=-1;//��ʼ����״̬����Ϊ����״̬
    
    //������ɱ�־λ
    Task.Flag[0]=-1;//����0��ʼ״̬Ϊδ���
    Task.Flag[1]=-1;//����1��ʼ״̬Ϊδ���
    Task.Flag[2]=-1;//����2��ʼ״̬Ϊδ���
    Task.Flag[3]=-1;//����3��ʼ״̬Ϊδ���
    
    //���˲�����־λ����6���������������ӹ�����
    Carry.Step=0;
    //���˲�����ɱ�־λ
    Carry.Step_Flag[0]=-1;//�����������ӹ�������һ��ɫ��ץȡ����ʼ״̬Ϊδ���
    Carry.Step_Flag[1]=-1;//�����������ӹ�������һ��ɫ����ã���ʼ״̬Ϊδ���
    Carry.Step_Flag[2]=-1;//�����������ӹ������ڶ���ɫ��ץȡ����ʼ״̬Ϊδ���
    Carry.Step_Flag[3]=-1;//�����������ӹ������ڶ���ɫ����ã���ʼ״̬Ϊδ���
    Carry.Step_Flag[4]=-1;//�����������ӹ�����������ɫ��ץȡ����ʼ״̬Ϊδ���
    Carry.Step_Flag[5]=-1;//�����������ӹ�����������ɫ����ã���ʼ״̬Ϊδ���
    
    //���˲�����־λ����6�������ӹ�������Ʒ����
    Carry2.Step=0;
    //���˲�����ɱ�־λ
    Carry2.Step_Flag[0]=-1;//���ӹ�������Ʒ������һ��ɫ��ץȡ����ʼ״̬Ϊδ���
    Carry2.Step_Flag[1]=-1;//���ӹ�������Ʒ������һ��ɫ����ã���ʼ״̬Ϊδ���
    Carry2.Step_Flag[2]=-1;//���ӹ�������Ʒ�����ڶ���ɫ��ץȡ����ʼ״̬Ϊδ���
    Carry2.Step_Flag[3]=-1;//���ӹ�������Ʒ�����ڶ���ɫ����ã���ʼ״̬Ϊδ���
    Carry2.Step_Flag[4]=-1;//���ӹ�������Ʒ����������ɫ��ץȡ����ʼ״̬Ϊδ���
    Carry2.Step_Flag[5]=-1;//���ӹ�������Ʒ����������ɫ����ã���ʼ״̬Ϊδ���
    
    Task.Pos_X=0.0f;
    Task.Pos_Y=0.0f;
    if(Round == 0)Task.Pos_W=0.0f;
    else if(Round == 1)Task.Pos_W=0.0f; //�ڶ�Ȧ���нǶ�Ư�ƣ������޸�
    
    
    Task.Pos_Hold_X=0.0f;
    Task.Pos_Hold_Y=0.0f;
    
    Task.STOP=0;
    
    Task.Pos_Acu=0;
    Task.Pos_Hold=0;

    Scan2_Complete = 0;
    
    //������ͼ��ҪУ׼��
    Check_Point_X[0] = 1500;    //У׼��1
    Check_Point_Y[0] = 1800;
    
    Check_Point_X[1] = 3300;    //У׼��2
    Check_Point_Y[2] = 1000;
    
    Check_Point_X[2] = 1000;    //У׼��3
    Check_Point_Y[1] = 1800;
}

void Colour_Position_Init()
{
    /*********************************************************************/
    /*��������ɫ��վ�ڱ�����������λ����Ը�����ʱ�������ң�λ������Ϊ0��1��2����������ɫ�ֱ��Ӧ1��2��3��*/
    /*********************************************************************/
    //��������OpenMV��ɫʶ���ã����¶���Task.ColourΪ�����ã�ÿ��ֻ����һ�鸳ֵ
    Task.Colour1[0]=1;//λ�ã���-��ɫ���죩
    Task.Colour1[1]=2;//λ�ã��У�-��ɫ���̣�
    Task.Colour1[2]=3;//λ�ã��ң�-��ɫ������
    
    //�ӹ���
    Task.Colour2[0]=3;//��
    Task.Colour2[1]=2;//��
    Task.Colour2[2]=1;//��
    
    //��Ʒ��
    Task.Colour3[0]=3;//��
    Task.Colour3[1]=2;//��
    Task.Colour3[2]=1;//��  
    
    /*********************************************************************/
    /*�����ά��*/
    /*********************************************************************/
    Task.Code1[0]=1;
    Task.Code1[1]=2;
    Task.Code1[2]=3;
    
    Task.Code2[0]=1;
    Task.Code2[1]=2;
    Task.Code2[2]=3; 
}

/******************************************************************************/
//�������
/******************************************************************************/
void Task_Ctrl()//ȫ�ֿ���
{
  Task_Switch();
  switch(Task.ID)
  {
  case 0: Task_Departure();             break;
  case 1: Task_Pattern_Recognition();   break;
  case 2: Task_MH1();                   break;
  case 3: Task_MH2();                   break;
  }
}

void Task_Switch()//�����л������
{ 
  /*-----------------------------��ǰû���������----------------------------*/
  if(Task.Status==-1)
  {
    //��ȡ��һ��δ��������Լ�״̬
    for(int16 i=3;i>-1;i--)
    {
      if(Task.Flag[i]!=1) 
      {
        id=i;               //��ȡ�¸�����������ID��ֻҪ��δ��ɾͼ����ö���
        flag=Task.Flag[i];  //��ȡ������״̬
      }
    }
    
    if(flag!=-1)
    {
      while(1);//��ǰ��ִ������״̬����δִ�У���ѭ�������ԣ�
    }
    
    //����滮����һ�μ������е�����
    Task.ID=id;         //����ID
    Task.Enable[id]=1;  //����ʹ��
    
    //��¼��ʹ������
    Task.ID_MEM[id]=1;
  }
  /*-----------------------------��ǰ���������ڽ���--------------------------*/
  else if(Task.Status==0)
  {
    //����У����ɱ�־λ����������Ϊ0
    Task.Bingo=0;
    
    //��ȡ��ǰ����ID
    id=Task.ID;
    
    //�жϵ�ǰ����״̬
    if(Task.Flag[id]==-1)while(1);//����δ��ʼ�������д�
    
    if(Task.Flag[id]==0)//���������
    {
      //���ݲ�ͬ���񣬶���������������У�飬�Լ�ʵʱ�������
      //�ص㣬ȫ�ֿ���
      if(id==0)//ǰ������׼����
      { 
        // ��������Ҫ����ָ��������׼������ͨ��Ϊ����ȫ���뿪���������������������̬��λ
      }
      else if(id==1)//��������Ϣ��ȡ
      {
        //��������Ҫ������ɫʶ�����ά��ʶ������������ɫʶ�����ά��ɨ�裬�����������ɫ���ά��������滮����˳��
      }
      else if(id==2)//���������������˵��ӹ���
      {
        
        //��������Ҫ���ݰ���˳�����ϴ����������˵��ӹ������˴�Ϊ��¼��ǰ�İ���״̬����ȡ��Ҫ���еİ��ˣ�����״̬�����֣�ǰ��������ץȡ��ǰ���ӹ�������
        for(int16 i=5;i>-1;i--)
        {
          if(Carry.Step_Flag[i]!=1) 
          {
            step=i;               //��ȡ�¸����˶�����ֻҪ��δ��ɾͼ����ö���
            step_flag=Carry.Step_Flag[i];  //��ȡ������״̬
          }
        }
        
        Carry.Step=step;//���˲���
        Carry.Step_Enable[step]=1;//����ʹ��               
        //�����������ݼ�MH1����
        
      }
      else if(id==3)//�����Ӽӹ������˵���Ʒ��
      {
        //��ִ�а��˶���ǰ����Ҫ�ٴ�ɨ���ά��
        //��������Ҫ���ݰ���˳�����ϴӼӹ������˵���Ʒ�����˴�Ϊ��¼��ǰ�İ���״̬����ȡ��Ҫ���еİ��ˣ�����״̬�����֣�ǰ���ӹ���ץȡ��ǰ����Ʒ������
        for(int16 i=5;i>-1;i--)
        {
          if(Carry2.Step_Flag[i]!=1) 
          {
            step2=i;               //��ȡ�¸����˶�����ֻҪ��δ��ɾͼ����ö���
            step_flag2=Carry2.Step_Flag[i];  //��ȡ������״̬
          }
        }
        Carry2.Step=step2;//���˲���
        Carry2.Step_Enable[step2]=1;//����ʹ��
        //�����������ݼ�MH2����
      }
    }
    if (Task.Flag[id]==1)//��ǰ���������
    {
      if(id==0)
      {
        Task.Bingo=1;
      }
      else if(id==1)
      {
        Task.Bingo=1;
      }
      else if(id==2)
      {
        Task.Bingo=1; 
      }
      else if(id==3)
      {
        Task.Bingo=1;
      }  
      if(Task.Bingo)    Task.Status=1;  //������,����������״̬��Ϊ��������� 
      else              Task.Status=0; //���û�����   
    }
  }
  /*-----------------------------��ǰ���������------------------------------*/
  else if(Task.Status==1)
  {
    //�ж���������������
    //����ǰ�����Ѿ���ɣ����������������ͷ���������
    if(id<3)
    {
      Task.Status=-1;
    }
    else
    {
      Task.ID=5;//ID5�����ڣ����һ�κ󷵻�
      Task.Status=1;
      CYS_Transfer_Without_Corr(Area.Home[0].X,Area.Home[0].Y);
      Task.Pos_Hold=0;
      Robot_Position(POSItion.first.Start,POSItion.second.START,POSItion.third.START,POSItion.fourth.open,0);  
      //�ص�������ͣ��
      if(my_abs(Ops9.Pos_X-Task.Pos_X)<5&&my_abs(Ops9.Pos_Y-Task.Pos_Y)<5)
      {
        Task.STOP=1; 
        Task.STOP=0; 
        CYS_Transfer_Without_Corr(Area.Home[1].X,Area.Home[1].Y);
        systick_delay_ms(2000);
        Task.STOP=1; 
        Task.Pos_Hold=0;
      }
      //��Ҫ����������Ҫ�ڷ��س�����֮�������ʼ����������Task_Init(),ͬʱ��Ҫ��ȡ���е���ʱ�䣬ȷ��������֮����ɲ����ص�������
    }
    //�����������Ѿ���ɣ��ص�������
  }
}

/******************************************************************************/
//������
/******************************************************************************/
/******************************************************************************/
//��������ǰ������ִ��׼����
//�����ܣ�
//���������
//�������ָ�꣺OPS����������Ϊ����������
/******************************************************************************/
void Task_Departure()//����
{
  if(Task.Status==-1)     //�ж����������Ƿ�������������
  {
    if(Task.Enable[0]==1&& Task.Flag[0]==-1)//�ж������Ƿ�ʹ��
    {
      Task.Pos_X=Area.Departure[0].X;
      Task.Pos_Y=Area.Departure[0].Y;    
      Task.Pos_Hold=0;
      Grasp_flag = 1;
      Task.Status=0;        //����������״̬�л�Ϊ��������ִ�У�
      Task.Flag[0]=0;      // ��������״̬��־λ�л�Ϊ����ִ�У�
    }
  }
  //�жϵ�ǰ����������
  if(Task.Flag[0]==0)
  {
    if(Task.Pos_Hold==1)
    {
      Grasp_flag = 0;
      CYS_Transfer(Area.Departure[1].X,Area.Departure[1].Y,Area.Departure[1].X,Area.Departure[1].Y);
      Scan_QR_Code1();
      //��ʾ��ά��
      oled_printf_int32(60,1,Task.Code1[0],1);
      oled_printf_int32(80,1,Task.Code1[1],1);
      oled_printf_int32(100,1,Task.Code1[2],1);
      Robot_Position(POSItion.first.Material,POSItion.second.Color_Recognition[0],POSItion.third.Color_Recognition[0],POSItion.fourth.open,0);     
      Task.Flag[0]=1;
    }
  }
  //�����ɽ�������״̬��־λ�л�Ϊ����ɣ���ʱ���ͷ��������ߣ����������л����ͷ�
}

/******************************************************************************/
//��������ɨ���ά������ɫʶ��
//�����ܣ������ά��ɨ�����򣬲������ȷ��ά������
//���������1.��ά��ɨ��λ�ã�2.��ά��ģ��ɨ��ָ��
//�������ָ�꣺tof����������Ϊ��ά��ɨ���λ�ã������翪�ؾ�ȷ���㺯�������õ����ظ�У������ȷ��ά������
/******************************************************************************/
void Task_Pattern_Recognition()//ɨ���ά����ʶ�������ɫ
{ 
  if(Task.Status==-1)     //�ж����������Ƿ�������������
  {
    if(Task.Enable[1]==1&& Task.Flag[1]==-1)//�ж������Ƿ�ʹ��
    {
      CYS_Transfer(Area.Departure[1].X,Area.Departure[1].Y,Check_Point_X[0],Check_Point_Y[0]);
      while(!Task.Pos_Hold);
      CYS_Transfer(Check_Point_X[0],Check_Point_Y[0],Check_Point_X[1],Check_Point_Y[1]);
      while(!Task.Pos_Hold);
      CYS_Transfer(Check_Point_X[1],Check_Point_Y[1],Area.Recognition.X,Area.Recognition.Y);
      
      Task.Pos_Hold=0;
      Task.Pos_Acu=0;
      Task.Pos_Check_Flag=0;
      
      Task.Status=0;        //����������״̬�л�Ϊ��������ִ�У�
      Task.Flag[1]=0;      // ��������״̬��־λ�л�Ϊ����ִ�У�
    }
  }
  
  if(Task.Flag[1]==0)
  {
    if(Task.Pos_Hold)//�ж��Ƿ��Ѿ������ά��ʶ����
    {     
      systick_delay_ms(100);
      //������ɫʶ��   
      Colour_Recognition();
      
      //      oled_printf_int32(8,7,Task.Colour1[0],1);
      //      oled_printf_int32(48,7,Task.Colour1[1],1);
      //      oled_printf_int32(96,7,Task.Colour1[2],1);  
      
      //��Ϣƥ��
      if(MODE == 0)
      {
        Information_Match_Grasp1();
        if(Round == 1)Information_Match_Place1();
      }
      else if(MODE == 1)
      {
        Information_Match_Grasp1();
        Information_Match_Place1();
      }

      Task.STOP=0;
      
      Task.Flag[1]=1;
    }
  }
}

/******************************************************************************/
//�����������ϰ���
//�����ܣ�
//���������
//�������ָ�꣺
/******************************************************************************/

void Task_MH1()
{
    if(Task.Status==-1)     //�ж����������Ƿ�������������
    {
        if(Task.Enable[2]==1&& Task.Flag[2]==-1)//�ж������Ƿ�ʹ��
        {
            Task.Status=0;        //����������״̬�л�Ϊ��������ִ�У�
            Task.Flag[2]=0;      // ��������״̬��־λ�л�Ϊ����ִ�У�
            Task.Pos_Hold=0;
        }
    }
    
    if(Task.Flag[2]==0) Path_Planer(Carry);
}

/******************************************************************************/
//�����������ϰ���
//�����ܣ�1.��˳�����ָ������
//���������1.Ŀ��λ�ã�2.��е��ָ�ץȡ������//ץȡ������ɺ���ת��ʣ�ද���ɻ�е��������ɣ���е��ֻ�践��״̬��־λ����������Ⱥ�������
//�������ָ�꣺1.tof����������Ϊ������Ⱥ���ָ����λ��2.����ָ����λ��Ļ�е��ָ�����������Ⱥ�����ɣ�
/******************************************************************************/
uint8 PP_FLAG=0;
void Task_MH2()//��������
{  
  if(Task.Status==-1)     //�ж����������Ƿ�������������
  {
    if(Task.Enable[3]==1&& Task.Flag[3]==-1)//�ж������Ƿ�ʹ��
    {
      CYS_Transfer_Without_Corr(Check_Point_X[1],Check_Point_Y[1]);
      while(!Task.Pos_Hold);
      CYS_Transfer(Check_Point_X[1],Check_Point_Y[1],Check_Point_X[0],Check_Point_Y[0]);
      while(!Task.Pos_Hold);
      CYS_Transfer(Check_Point_X[0],Check_Point_Y[0],Area.Departure[2].X,Area.Departure[2].Y);
      
      Task.Status=0;        //����������״̬�л�Ϊ��������ִ�У�
      Task.Flag[3]=0;      // ��������״̬��־λ�л�Ϊ����ִ�У�
      Task.Pos_Hold=0;
    }
  }
  
  if(Task.Pos_Hold&&!Scan2_Complete)
  {
    Scan_QR_Code2(); 
    
    oled_printf_int32(60,3,Task.Code2[0],1);
    oled_printf_int32(80,3,Task.Code2[1],1);
    oled_printf_int32(100,3,Task.Code2[2],1);  
    
    if(MODE == 0){
      Information_Match_Grasp2();
      if(Round == 1)Information_Match_Place2();
    }
    else if(MODE == 1)
    {
      Information_Match_Grasp2();
      Information_Match_Place2();
    }
    
  }
  if(Scan2_Complete&&Task.Flag[3]==0) 
  {
    Path_Planer(Carry2);
  }
}

/******************************************************************************/
//���ݴ��������
/******************************************************************************/
//��Ϣƥ�䣨��һ��ɨ��Ķ�ά����������ɫ�飩
void Information_Match_Grasp1()
{
  uint8 i,j;
  for(i=0;i<3;i++)
  {
    for(j=0;j<3;j++)
    {
      if(Task.Code1[i]==Task.Colour1[j])//������ɫ�����˳����ɫ��ʵ��λ��ƥ��
      {
        Task.Target1[i]=j;//jΪ0��1��2�ֱ��Ӧ���У���
      }
    }
  }
}
//��Ϣƥ�䣨��һ��ɨ��Ķ�ά����ӹ���ɫ�飩
void Information_Match_Place1()
{
  uint8 i,j;
  for(i=0;i<3;i++)
  {
    for(j=0;j<3;j++)
    {
      if(Task.Code1[i]==Task.Colour2[j])//������ɫ�����˳����ɫ��ʵ��λ��ƥ��
      {
        Task.Target2[i]=j;//jΪ0��1��2�ֱ��Ӧ���У���
      }
    }
  }   
}
//��Ϣƥ�䣨�ڶ���ɨ��Ķ�ά����ӹ���ɫ�飩
void Information_Match_Grasp2()
{
  uint8 i,j;
  for(i=0;i<3;i++)
  {
    for(j=0;j<3;j++)
    {
      if(Task.Code2[i]==Task.Colour2[j])//������ɫ�����˳����ɫ��ʵ��λ��ƥ��
      {
        Task.Target2[i]=j;//jΪ0��1��2�ֱ��Ӧ���У���
      }
    }
  }   
}
//��Ϣƥ�䣨�ڶ���ɨ��Ķ�ά�����Ʒ��ɫ�飩
void Information_Match_Place2()
{
  uint8 i,j;
  for(i=0;i<3;i++)
  {
    for(j=0;j<3;j++)
    {
      if(Task.Code2[i]==Task.Colour3[j])//������ɫ�����˳����ɫ��ʵ��λ��ƥ��
      {
        Task.Target3[i]=j;//jΪ0��1��2�ֱ��Ӧ���У���
      }
    }
  }   
}

//·���滮
void Path_Planer(Carry_Obj_Struct struct_carry)
{
  if(struct_carry.Step==0&&struct_carry.Step_Enable[0]==1)//ץȡ���1
  {
    Grasping(struct_carry);//ץȡ����      
  }
  else if(struct_carry.Step==1)//�������1
  {
    if(MODE ==0){
      if(!colour_rec1&&Task.ID==2)PlaceArea_Colour_Rec(struct_carry);
      else if(colour_rec1&&!colour_rec2&&Task.ID==3)PlaceArea_Colour_Rec(struct_carry);
      if(colour_rec1&&Task.ID==2)  Placing(struct_carry);
      else if(colour_rec1&&colour_rec2&&Task.ID==3) Placing(struct_carry);
    }
    else if(MODE ==1)Placing(struct_carry);
  }
  else if(struct_carry.Step==2)//ץȡ���2
  {
    Grasping(struct_carry);//ץȡ����       
  }
  else if(struct_carry.Step==3)//�������2
  {
    Placing(struct_carry);
  }
  else if(struct_carry.Step==4)//ץȡ���3
  {       
    Grasping(struct_carry);//ץȡ����      
  }
  else if(struct_carry.Step==5&&struct_carry.Step_Flag[struct_carry.Step]!=1)//�������3
  {
    Placing(struct_carry);
  }
}

//ץȡ����
void Grasping(Carry_Obj_Struct struct_carry)//ץȡ����
{
  if(struct_carry.Step_Flag[struct_carry.Step]==-1&&struct_carry.Step_Enable[struct_carry.Step]==1)//�ж϶�����־λ�Ƿ�Ϊδ��ɣ�-1������ʹ�ܣ�1��
  {   
    if(Task.ID==2)//�жϵ�ǰ����ID��2�����������ӹ�����
    {   
      Carry.Step_Flag[struct_carry.Step]=0;//��������־λ��0���������ڽ���
      
      if(struct_carry.Step/2 == 0 )
      {
        CYS_Transfer(Area.Recognition.X,Area.Recognition.Y,Area.Material[Task.Target1[0]].X,Area.Material[Task.Target1[0]].Y-20);
      }
      else
      {
        CYS_Transfer_Without_Corr(Area.Material[Task.Target1[struct_carry.Step/2]].X,Area.Material[Task.Target1[struct_carry.Step/2]].Y);
      }
      if(struct_carry.Step/2 != 0 )
      {
        Robot_Position(POSItion.first.Material,POSItion.second.Material.Grasp[1],POSItion.third.Material.Grasp[1],POSItion.fourth.open,0);
      }
      
      Task.Pos_Hold=0;
      
    }
    else if(Task.ID==3)//�жϵ�ǰ����ID��3���ӹ�������Ʒ����
    {       
      Robot_Position(POSItion.first.Process,POSItion.second.Process.Grasp[2],POSItion.third.Process.Grasp[2],POSItion.fourth.open,0);
      Carry2.Step_Flag[struct_carry.Step]=0;//��������־λ��0���������ڽ���
      
      if(struct_carry.Step/2 ==0)
      {
        CYS_Transfer(Area.Departure[2].X,Area.Departure[2].Y,Check_Point_X[0],Check_Point_Y[0]);
        while(!Task.Pos_Hold);
        CYS_Transfer(Check_Point_X[0],Check_Point_Y[0],Check_Point_X[1],Check_Point_Y[1]);
        while(!Task.Pos_Hold);
      }
      else 
      {
        CYS_Transfer_Without_Corr(Check_Point_X[0],Check_Point_Y[0]);
        while(!Task.Pos_Hold);
        CYS_Transfer(Check_Point_X[0],Check_Point_Y[0],Check_Point_X[1],Check_Point_Y[1]);
        while(!Task.Pos_Hold);
      }
      
      switch(Process_Dir)
      {
      case 0:
        Task.Pos_X=Area.Process_B[Task.Target2[struct_carry.Step/2]].X;//��Ŀ��λ������Ϊ�ӹ���
        Task.Pos_Y=Area.Process_B[Task.Target2[struct_carry.Step/2]].Y + 5;
        break;
      case 1:
        Task.Pos_X=Area.Process_B[Task.Target2[struct_carry.Step/2]].X - 5;//��Ŀ��λ������Ϊ�ӹ���
        Task.Pos_Y=Area.Process_B[Task.Target2[struct_carry.Step/2]].Y;
        break;
      case 2:
        Task.Pos_X=Area.Process_B[Task.Target2[struct_carry.Step/2]].X;//��Ŀ��λ������Ϊ�ӹ���
        Task.Pos_Y=Area.Process_B[Task.Target2[struct_carry.Step/2]].Y - 5;
        break;
      case 3:
        Task.Pos_X=Area.Process_B[Task.Target2[struct_carry.Step/2]].X + 5;//��Ŀ��λ������Ϊ�ӹ���
        Task.Pos_Y=Area.Process_B[Task.Target2[struct_carry.Step/2]].Y;
        break;
      }
      Task.Pos_Hold=0;
      Grasp_flag = 1;
    }
  }
  if(Task.Pos_Hold)//�ж��Ƿ��Ѿ�����ץȡ����
  {
    //����Ŀ�������ͣ��
    Task.STOP=1;
    Grasp_flag = 0;
    if(Task.ID==2)//�жϵ�ǰ����ID��2�����������ӹ�����
    {
      Robot_Position(0,POSItion.second.Material.Grasp[0],POSItion.third.Material.Grasp[0],POSItion.fourth.open,1200);
      Robot_Position(0,POSItion.second.Material.Grasp[0],POSItion.third.Material.Grasp[0],POSItion.fourth.close,1200);
    }
    else if(Task.ID==3)//�жϵ�ǰ����ID��3���ӹ�������Ʒ����
    {
      Robot_Position(POSItion.first.Process,POSItion.second.Process.Grasp[0],POSItion.third.Process.Grasp[0],POSItion.fourth.open,1000);
      Robot_Position(POSItion.first.Process,POSItion.second.Process.Grasp[1],POSItion.third.Process.Grasp[1],POSItion.fourth.open,500);
      Robot_Position(POSItion.first.Process,POSItion.second.Process.Grasp[1],POSItion.third.Process.Grasp[1],POSItion.fourth.close,500);
    }
    Task.STOP=0;
    
    if(Task.ID==2)  Carry.Step_Flag[struct_carry.Step]=1;
    else if(Task.ID==3)  Carry2.Step_Flag[struct_carry.Step]=1;
  }
}

uint8 final_flag=0;
//���ö���
void Placing(Carry_Obj_Struct struct_carry)
{
  if(struct_carry.Step_Flag[struct_carry.Step]==-1&&struct_carry.Step_Enable[struct_carry.Step]==1)//�ж϶�����־λ�Ƿ�Ϊδ��ɣ�-1������ʹ�ܣ�1��
  {        
    if(Task.ID==2)//�жϵ�ǰ����ID��2�����������ӹ�����
    {
      Carry.Step_Flag[struct_carry.Step]=0;//��������־λ��0���������ڽ���
      Robot_Position(0,POSItion.second.Material.Grasp[1],POSItion.third.Material.Grasp[1],POSItion.fourth.close,500);
      CYS_Transfer_Without_Corr(Area.Process[Task.Target2[struct_carry.Step/2]].X,Area.Process[Task.Target2[struct_carry.Step/2]].Y);
      Task.Pos_Hold=0;
      final_flag=0;
      
    }
    else if(Task.ID==3)//�жϵ�ǰ����ID��3���ӹ�������Ʒ����
    {  
      Carry2.Step_Flag[struct_carry.Step]=0;//��������־λ��0���������ڽ���
      Robot_Position(POSItion.first.Process,POSItion.second.Process.Grasp[2],POSItion.third.Process.Grasp[2],POSItion.fourth.close,500);
      
      CYS_Transfer_Without_Corr(Check_Point_X[1],Check_Point_Y[1]);
      while(!Task.Pos_Hold);
      CYS_Transfer(Check_Point_X[1],Check_Point_Y[1],Check_Point_X[0],Check_Point_Y[0]);
      while(!Task.Pos_Hold);
      
      CYS_Transfer_Without_Corr(Area.Final[Task.Target3[struct_carry.Step/2]].X,Area.Final[Task.Target3[struct_carry.Step/2]].Y);
      Task.Pos_Hold=0;
      final_flag=0;
    }
    while(Task.Pos_Hold==0)
    {
      if(Task.ID==2)//�жϵ�ǰ����ID��2�����������ӹ�����
      {
        Robot_Position(POSItion.first.Process,POSItion.second.Process.place[2],POSItion.third.Process.place[2],POSItion.fourth.close,0);
      }
      if(Task.ID==3)//�жϵ�ǰ����ID��2�����������ӹ�����
      {
        Robot_Position(POSItion.first.Final,POSItion.second.Final.place[2],POSItion.third.Final.place[2],POSItion.fourth.close,0);
      }
    }
    
    if(final_flag==0)///ʶ��ɫ��Բ��
    {
      if(Task.Pos_Hold)//�ж��Ƿ��Ѿ������������
      {
        Task.STOP=1;
        if(Task.ID==2)//�жϵ�ǰ����ID��2�����������ӹ�����
        {
          CYS_Transfer(Area.Process[Task.Target2[struct_carry.Step/2]].X,Area.Process[Task.Target2[struct_carry.Step/2]].Y,Area.Process[Task.Target2[struct_carry.Step/2]].X+ STEP1_X, Area.Process[Task.Target2[struct_carry.Step/2]].Y + STEP1_Y);
          Area.Process_B[Task.Target2[struct_carry.Step/2]].X = Task.Pos_X;
          Area.Process_B[Task.Target2[struct_carry.Step/2]].Y = Task.Pos_Y;
          Task.Pos_Hold=0;
          final_flag=1;
        }
        else if(Task.ID==3)//�жϵ�ǰ����ID��2�����������ӹ�����
        {
          CYS_Transfer(Area.Final[Task.Target3[struct_carry.Step/2]].X,Area.Final[Task.Target3[struct_carry.Step/2]].Y,Area.Final[Task.Target3[struct_carry.Step/2]].X + STEP2_X,Area.Final[Task.Target3[struct_carry.Step/2]].Y + STEP2_Y);  
          
          Task.Pos_Hold=0;
          final_flag=1;
        }
        Task.STOP=0;
      }
    }
    while(Task.Pos_Hold==0)
    {
      if(Task.ID==2)//�жϵ�ǰ����ID��2�����������ӹ�����
      {
        Robot_Position(POSItion.first.Process,POSItion.second.Process.place[2],POSItion.third.Process.place[2],POSItion.fourth.close,0);
      }
      if(Task.ID==3)//�жϵ�ǰ����ID��2�����������ӹ�����
      {
        Robot_Position(POSItion.first.Final,POSItion.second.Final.place[2],POSItion.third.Final.place[2],POSItion.fourth.close,0);
      }
    }
    
    if(final_flag==1)
    {
      
      if(Task.Pos_Hold)//�ж��Ƿ��Ѿ������������
      {
        //����Ŀ�������ͣ��
        Task.STOP=1;
        if(Task.ID==2)//�жϵ�ǰ����ID��2�����������ӹ�����
        {
          Robot_Position(0,0,POSItion.third.Process.place[0],0,150);
          Robot_Position(0,POSItion.second.Process.place[0],POSItion.third.Process.place[0],POSItion.fourth.close,1300);
          Robot_Position(0,POSItion.second.Process.place[0],POSItion.third.Process.place[0],POSItion.fourth.open,500);
          Robot_Position(0,POSItion.second.Process.place[1],POSItion.third.Process.place[1],POSItion.fourth.open,500);
          Robot_Position(0,POSItion.second.Process.place[2],POSItion.third.Process.place[2],POSItion.fourth.open,700);
        }
        else if(Task.ID==3)//�жϵ�ǰ����ID��3���ӹ�������Ʒ����
        {
          Robot_Position(0,0,POSItion.third.Final.place[0],0,150);
          Robot_Position(POSItion.first.Final,POSItion.second.Final.place[0],POSItion.third.Final.place[0],POSItion.fourth.close,1300);
          Robot_Position(POSItion.first.Final,POSItion.second.Final.place[0],POSItion.third.Final.place[0],POSItion.fourth.open,500);
          Robot_Position(POSItion.first.Final,POSItion.second.Final.place[1],POSItion.third.Final.place[1],POSItion.fourth.open,500);
          Robot_Position(POSItion.first.Final,POSItion.second.Final.place[2],POSItion.third.Final.place[2],POSItion.fourth.open,700);
        }
        Task.STOP=0;
        if(Task.ID==2)        Carry.Step_Flag[struct_carry.Step]=1;
        else if(Task.ID==3)   Carry2.Step_Flag[struct_carry.Step]=1;
        
        if(struct_carry.Step==5)
        {
          if(Task.ID==2)
          {
            Task.Flag[2]=1;//MH1�������
          }
          else if(Task.ID==3)
          {
            Task.Flag[3]=1;//MH2�������
          }
        }
      }
    }
  }
}

//��һ��ɨ���ά��
void Scan_QR_Code1()
{
  do{ Barcode_Scan_Command();systick_delay_ms(500);}
  while(!getQRCode.receiveComplete);//ɨ�벻�ɹ�
  Task.Code1[0]=getQRCode.first[0];       //�洢��ά������
  Task.Code1[1]=getQRCode.second[0];
  Task.Code1[2]=getQRCode.third[0]; 
}

//�ڶ���ɨ���ά��
//void Scan_QR_Code2()
//{
//  do{ Barcode_Scan_Command();systick_delay_ms(500);}
//  while(!getQRCode.receiveComplete);//ɨ�벻�ɹ�
//  Task.Code2[0]=getQRCode.first;       //�洢��ά������
//  Task.Code2[1]=getQRCode.second;
//  Task.Code2[2]=getQRCode.third; 
//  Scan2_Complete = 1;
//}

//��ɫʶ��
void Colour_Recognition()
{
  OpenMV_uart_init();
  if(Round == 0)
  {
  do{ OpenMV_Step1_Command();systick_delay_ms(50);}
  while(!myOpenMV.receiveComplete);//ע�����ɼ�5��ȡ�м�һ�κ�ͽ�
  Task.Colour1[0]=myOpenMV.Left_N;   //�洢ɫ����ɫ����������ɫ��
  Task.Colour1[1]=myOpenMV.Middle_N;
  Task.Colour1[2]=myOpenMV.Right_N;
  }
  else if(Round == 1)
  {
  int counter = 0;
  do{ OpenMV_Step1_Command();systick_delay_ms(50);counter ++;}
  while(!myOpenMV.receiveComplete && counter <= 100);//ע�����ɼ�5��ȡ�м�һ�κ�ͽ�
  Task.Colour1[0]=myOpenMV.Left_N;   //�洢ɫ����ɫ����������ɫ��
  Task.Colour1[1]=myOpenMV.Middle_N;
  Task.Colour1[2]=myOpenMV.Right_N;
  }
  
}

//ɫ����ɫʶ��
void PlaceArea_Colour_Rec(Carry_Obj_Struct struct_carry)
{
  uint8 temp1[10],temp2[10],i,j;
  if(struct_carry.Step_Flag[struct_carry.Step]==-1&&struct_carry.Step_Enable[struct_carry.Step]==1)//�ж��Ƿ��Ѿ������ά��ʶ����    
  {
    colour_rec=0;
    if(Task.ID==2)//�жϵ�ǰ����ID��2�����������ӹ�����
    {
      Task.Pos_X=Area.Color_Recognition1[0].X;//Area.Color_Recognition1[0].X;//Area.Process[Task.Target2[struct_carry.Step/2]].X;//��Ŀ��λ������Ϊ�ӹ���
      Task.Pos_Y=Area.Color_Recognition1[0].Y;//Area.Color_Recognition1[0].Y;//Area.Process[Task.Target2[struct_carry.Step/2]].Y;   
      Task.Pos_Hold=0;
      
    }
    if(Task.ID==3)//�жϵ�ǰ����ID��2�����������ӹ�����
    {
      Task.Pos_X=Area.Color_Recognition2[0].X;//Area.Color_Recognition2[0].X;//Area.Process[Task.Target2[struct_carry.Step/2]].X;//��Ŀ��λ������Ϊ�ӹ���
      Task.Pos_Y=Area.Color_Recognition2[0].Y;//Area.Color_Recognition2[0].Y;//Area.Process[Task.Target2[struct_carry.Step/2]].Y;
      Task.Pos_Hold=0;
    }
  }
  while(Task.Pos_Hold==0){
    if(Task.ID==2)//�жϵ�ǰ����ID��2�����������ӹ�����
    {
      Robot_Position(POSItion.first.Process,POSItion.second.Process.place[2],POSItion.third.Process.place[2],POSItion.fourth.close,0);
    }
    if(Task.ID==3)//�жϵ�ǰ����ID��2�����������ӹ�����
    {
      Robot_Position(POSItion.first.Final,POSItion.second.Final.place[2],POSItion.third.Final.place[2],POSItion.fourth.close,0);
    }
  };
  if(Task.Pos_Hold)//�ж��Ƿ��Ѿ������ά��ʶ����
  {
    while(gpio_get(A13));
    Task.STOP=1;
    if(Task.ID==2)//�жϵ�ǰ����ID��2�����������ӹ�����
    {
      Robot_Position(0,POSItion.second.Color_Recognition[1],POSItion.third.Color_Recognition[1],POSItion.fourth.close,0);
      OpenMV_uart_init();
      systick_delay_ms(1000);
      for(uint8 cnt=0;cnt<10;cnt++)
      {
        do{OpenMV_Step2_Left_Command();systick_delay_ms(50);}//ʶ��λ��0��ɫ
        while(!myOpenMV.receiveComplete);
        
        temp1[cnt]=myOpenMV.Step2Left;    //�洢�ӹ��������ɫ��Task.Colour2[0] 
        
      }
      Robot_Position(0,POSItion.second.Color_Recognition[1],POSItion.third.Color_Recognition[1],POSItion.fourth.close,0);
      OpenMV_uart_init();
      systick_delay_ms(700);
      for(uint8 cnt=0;cnt<10;cnt++)
      {
        do{OpenMV_Step2_Left_Command();systick_delay_ms(50);}//ʶ��λ��0��ɫ
        while(!myOpenMV.receiveComplete);
        temp2[cnt]=myOpenMV.Step2Left;    //�洢�ӹ��������ɫ��Task.Colour2[0] 
      }
      systick_delay_ms(300);
      
      uint8 filter_temp1=0;
      for(j=0;j<9;j++)                      //����ֵ��С�������У�ð�ݷ���
      {
        for(i=0;i<9-j;i++)
        {
          if(temp1[i]>temp1[i+1])
          {
            filter_temp1 = temp1[i];         //��һά����
            temp1[i] = temp1[i+1];
            temp1[i+1] = filter_temp1;                          
          }
        }
      }
      Task.Colour2[0]=temp1[4];
      oled_uint16(8,3,Task.Colour2[0]);
      
      uint8 filter_temp2=0;
      for(j=0;j<9;j++)                      //����ֵ��С�������У�ð�ݷ���
      {
        for(i=0;i<9-j;i++)
        {
          if(temp2[i]>temp2[i+1])
          {
            filter_temp2 = temp2[i];         //��һά����
            temp2[i] = temp2[i+1];
            temp2[i+1] = filter_temp2;                          
          }
        }
      }
      
      Task.Colour2[1]=temp2[4]; //�洢�ӹ����м���ɫ��Task.Colour2[1]
      oled_uint16(48,3,Task.Colour2[1]);
      
      if(Task.Colour2[0]!=1&&Task.Colour2[1]!=1)Task.Colour2[2]=1;//����ǰ����������ɫ�жϵ�����������ɫ
      else if(Task.Colour2[0]!=2&&Task.Colour2[1]!=2)Task.Colour2[2]=2;//����ǰ����������ɫ�жϵ�����������ɫ
      else if(Task.Colour2[0]!=3&&Task.Colour2[1]!=3)Task.Colour2[2]=3;//����ǰ����������ɫ�жϵ�����������ɫ
      
      oled_uint16(96,3,Task.Colour2[2]);
      Information_Match_Place1();//����ǰ��ȡ�ļӹ�����ɫ���ά��1ƥ��
      
      colour_rec1=1;
      Task.STOP=0;
      
    }
    else if(Task.ID==3)//�жϵ�ǰ����ID��2�����������ӹ�����
    {
      //while(gpio_get(A13));
      Robot_Position(0,POSItion.second.Color_Recognition[1],POSItion.third.Color_Recognition[1],POSItion.fourth.close,0);
      //�ƶ�����Ʒ��ָ��λ��       
      OpenMV_uart_init();
      //while(gpio_get(A13));
      systick_delay_ms(1000);
      for(uint8 cnt=0;cnt<10;cnt++)
      {
        do{OpenMV_Step2_Left_Command();systick_delay_ms(50);}//ʶ��λ��0��ɫ
        while(!myOpenMV.receiveComplete);
        
        temp1[cnt]=myOpenMV.Step2Left;    //�洢�ӹ��������ɫ��Task.Colour3[0] 
        
      }
      
      Robot_Position(0,POSItion.second.Color_Recognition[1],POSItion.third.Color_Recognition[1],POSItion.fourth.close,0);
      OpenMV_uart_init();
      systick_delay_ms(700);
      
      for(uint8 cnt=0;cnt<10;cnt++)
      {
        do{OpenMV_Step2_Left_Command();systick_delay_ms(50);}//ʶ��λ��0��ɫ
        while(!myOpenMV.receiveComplete);
        
        temp2[cnt]=myOpenMV.Step2Left;    //�洢�ӹ��������ɫ��Task.Colour3[0] 
      }
      systick_delay_ms(300);
      uint8 filter_temp1=0;
      for(j=0;j<9;j++)                      //����ֵ��С�������У�ð�ݷ���
      {
        for(i=0;i<9-j;i++)
        {
          if(temp1[i]>temp1[i+1])
          {
            filter_temp1 = temp1[i];         //��һά����
            temp1[i] = temp1[i+1];
            temp1[i+1] = filter_temp1;                          
          }
        }
      }
      Task.Colour3[0]=temp1[4];
      oled_uint16(8,3,Task.Colour3[0]);
      
      uint8 filter_temp2=0;
      for(j=0;j<9;j++)                      //����ֵ��С�������У�ð�ݷ���
      {
        for(i=0;i<9-j;i++)
        {
          if(temp2[i]>temp2[i+1])
          {
            filter_temp2 = temp2[i];         //��һά����
            temp2[i] = temp2[i+1];
            temp2[i+1] = filter_temp2;                          
          }
        }
      }
      
      Task.Colour3[1]=temp2[4]; //�洢�ӹ����м���ɫ��Task.Colour3[1]
      oled_uint16(48,3,Task.Colour3[1]);
      
      if(Task.Colour3[0]!=1&&Task.Colour3[1]!=1)Task.Colour3[2]=1;//����ǰ����������ɫ�жϵ�����������ɫ
      else if(Task.Colour3[0]!=2&&Task.Colour3[1]!=2)Task.Colour3[2]=2;//����ǰ����������ɫ�жϵ�����������ɫ
      else if(Task.Colour3[0]!=3&&Task.Colour3[1]!=3)Task.Colour3[2]=3;//����ǰ����������ɫ�жϵ�����������ɫ
      
      oled_uint16(96,3,Task.Colour3[2]);
      
      Information_Match_Place2();//����ǰ��ȡ�ĳ�Ʒ����ɫ���ά��2ƥ��
      colour_rec2=1;
      Task.STOP=0;
    }
  }
}

