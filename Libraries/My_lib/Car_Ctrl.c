#include "Car_Ctrl.h"


Task_Ctr_Strcuct Task;
Carry_Obj_Struct Carry;
Carry_Obj_Struct Carry2;

/******************************模式选择*****************************/
//#define MODE 0        ////初赛
#define MODE 1        ////决赛
//#define MODE 2        ////堆垛
 
/*-----------------------------------
|              成品区(744)          |
|                                   |
|                                   |
|                | \                |
|                 \ DIR:2           |
| 加              \               物|
| 工              \               料|
| 区      <-------*------->       区|
|(1050)    DIR:1  \    DIR:3   (426)|
|                 \                 |
|                 \                 |
|           DIR:0 \                 |
|                \ /         ////////
|                            /  发  |
|                            /  车  |
|                            /  区  |
-----------------------------------*/
char Scan2_Complete = 0;
unsigned char colour_rec=0,colour_rec1=0,colour_rec2=0;


//由于决赛地图较大，此处为添加的三个校准点
float Check_Point_X[3],Check_Point_Y[3];

/**********************以下状态在预赛模式下确定后不需要再调整************************/
/**********************以下状态在决赛模式下需要根据模式不同进行切换******************/

float  Pos_Accuracy;
short int id=0,flag=-1;
short int step,step_flag,step2,step_flag2;
char Round;

/******************************************************************************/
//参数设置
/******************************************************************************/
void Parament_Init()//参数初始化
{

    //定位精度(<n毫米)
    Pos_Accuracy=3.0f;
    
    //电机最大输出(最大10000)
    Duty_MAX =  8000;
    Duty_MIN = -8000;    
    Duty_MAX =  8000;
    Duty_MIN = -8000;
    
    //PID参数
    //位置环
    Position.Pid[X].Kp=1.0f;//X方向P
    Position.Pid[X].Ki=0.0f; //X方向I
    Position.Pid[X].Kd=0.0f; //X方向D
    
    Position.Pid[Y].Kp=1.0f;//Y方向P
    Position.Pid[Y].Ki=0.0f; //Y方向I
    Position.Pid[Y].Kd=0.0f; //Y方向D
    
    Position.Pid[W].Kp=1100.0f;//偏航角P
    Position.Pid[W].Ki=0.0f;   //偏航角I
    Position.Pid[W].Kd=7000.0f; //偏航角D 
    
    //速度环
    Speed_Kp = 5.0f;
    Speed_Kd = 0.0f;
    
    
    Area_Init();//区域位置初始化
    Servo_Position_Init();//舵机姿态初始化
    Colour_Position_Init();//颜色顺序初始化

}

void Task_Init()//任务初始化
{   
    /*以下参数默认状态下禁止修改！！！！！！！！！！！！！！！！！！！！！！！*/
    /*以下参数默认状态下禁止修改！！！！！！！！！！！！！！！！！！！！！！！*/
    /*以下参数默认状态下禁止修改！！！！！！！！！！！！！！！！！！！！！！！*/
    Task.ID=0;//初始任务ID号为0，从任务0开始执行
    Task.Status=-1;//初始任务状态总线为空闲状态
    
    //任务完成标志位
    Task.Flag[0]=-1;//任务0初始状态为未完成
    Task.Flag[1]=-1;//任务1初始状态为未完成
    Task.Flag[2]=-1;//任务2初始状态为未完成
    Task.Flag[3]=-1;//任务3初始状态为未完成
    
    //搬运步数标志位（共6步）（物料区到加工区）
    Carry.Step=0;
    //搬运步骤完成标志位
    Carry.Step_Flag[0]=-1;//（物料区到加工区）第一个色块抓取，初始状态为未完成
    Carry.Step_Flag[1]=-1;//（物料区到加工区）第一个色块放置，初始状态为未完成
    Carry.Step_Flag[2]=-1;//（物料区到加工区）第二个色块抓取，初始状态为未完成
    Carry.Step_Flag[3]=-1;//（物料区到加工区）第二个色块放置，初始状态为未完成
    Carry.Step_Flag[4]=-1;//（物料区到加工区）第三个色块抓取，初始状态为未完成
    Carry.Step_Flag[5]=-1;//（物料区到加工区）第三个色块放置，初始状态为未完成
    
    //搬运步数标志位（共6步）（加工区到成品区）
    Carry2.Step=0;
    //搬运步骤完成标志位
    Carry2.Step_Flag[0]=-1;//（加工区到成品区）第一个色块抓取，初始状态为未完成
    Carry2.Step_Flag[1]=-1;//（加工区到成品区）第一个色块放置，初始状态为未完成
    Carry2.Step_Flag[2]=-1;//（加工区到成品区）第二个色块抓取，初始状态为未完成
    Carry2.Step_Flag[3]=-1;//（加工区到成品区）第二个色块放置，初始状态为未完成
    Carry2.Step_Flag[4]=-1;//（加工区到成品区）第三个色块抓取，初始状态为未完成
    Carry2.Step_Flag[5]=-1;//（加工区到成品区）第三个色块放置，初始状态为未完成
    
    Task.Pos_X=0.0f;
    Task.Pos_Y=0.0f;
    if(Round == 0)Task.Pos_W=0.0f;
    else if(Round == 1)Task.Pos_W=0.0f; //第二圈会有角度漂移，现已修复
    
    
    Task.Pos_Hold_X=0.0f;
    Task.Pos_Hold_Y=0.0f;
    
    Task.STOP=0;
    
    Task.Pos_Acu=0;
    Task.Pos_Hold=0;

    Scan2_Complete = 0;
    
    //决赛地图需要校准点
    Check_Point_X[0] = 1500;    //校准点1
    Check_Point_Y[0] = 1800;
    
    Check_Point_X[1] = 3300;    //校准点2
    Check_Point_Y[2] = 1000;
    
    Check_Point_X[2] = 1000;    //校准点3
    Check_Point_Y[1] = 1800;
}

void Colour_Position_Init()
{
    /*********************************************************************/
    /*任务区颜色（站在比赛区域中心位置面对各区域时从左往右，位置依次为0，1，2，红绿蓝颜色分别对应1，2，3）*/
    /*********************************************************************/
    //物料区（OpenMV颜色识别获得）以下多组Task.Colour为测试用，每次只能有一组赋值
    Task.Colour1[0]=1;//位置（左）-颜色（红）
    Task.Colour1[1]=2;//位置（中）-颜色（绿）
    Task.Colour1[2]=3;//位置（右）-颜色（蓝）
    
    //加工区
    Task.Colour2[0]=3;//左
    Task.Colour2[1]=2;//中
    Task.Colour2[2]=1;//右
    
    //成品区
    Task.Colour3[0]=3;//左
    Task.Colour3[1]=2;//中
    Task.Colour3[2]=1;//右  
    
    /*********************************************************************/
    /*任务二维码*/
    /*********************************************************************/
    Task.Code1[0]=1;
    Task.Code1[1]=2;
    Task.Code1[2]=3;
    
    Task.Code2[0]=1;
    Task.Code2[1]=2;
    Task.Code2[2]=3; 
}

/******************************************************************************/
//任务管理
/******************************************************************************/
void Task_Ctrl()//全局控制
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

void Task_Switch()//任务切换与决策
{ 
  /*-----------------------------当前没有任务进行----------------------------*/
  if(Task.Status==-1)
  {
    //获取下一个未完成任务以及状态
    for(int16 i=3;i>-1;i--)
    {
      if(Task.Flag[i]!=1) 
      {
        id=i;               //获取下个待完成任务的ID，只要是未完成就继续该动作
        flag=Task.Flag[i];  //获取该任务状态
      }
    }
    
    if(flag!=-1)
    {
      while(1);//当前待执行任务状态不是未执行，死循环（调试）
    }
    
    //任务规划，下一次即将进行的任务
    Task.ID=id;         //任务ID
    Task.Enable[id]=1;  //任务使能
    
    //记录已使能任务
    Task.ID_MEM[id]=1;
  }
  /*-----------------------------当前有任务正在进行--------------------------*/
  else if(Task.Status==0)
  {
    //任务校验完成标志位，必须先置为0
    Task.Bingo=0;
    
    //获取当前任务ID
    id=Task.ID;
    
    //判断当前任务状态
    if(Task.Flag[id]==-1)while(1);//任务未开始，程序有错
    
    if(Task.Flag[id]==0)//任务进行中
    {
      //根据不同任务，对任务完成情况进行校验，以及实时任务调度
      //重点，全局控制
      if(id==0)//前往出发准备区
      { 
        // 该任务需要到达指定的任务准备区（通常为车身全部离开出发区），将各个舵机姿态置位
      }
      else if(id==1)//传感器信息读取
      {
        //该任务需要到达颜色识别与二维码识别区，开启颜色识别与二维码扫描，获得物料区颜色与二维码命令，并规划搬运顺序
      }
      else if(id==2)//将物块从物料区搬运到加工区
      {
        
        //该任务需要根据搬运顺序将物料从物料区搬运到加工区，此处为记录当前的搬运状态，获取将要进行的搬运，搬运状态有两种，前往物料区抓取和前往加工区放置
        for(int16 i=5;i>-1;i--)
        {
          if(Carry.Step_Flag[i]!=1) 
          {
            step=i;               //获取下个搬运动作，只要是未完成就继续该动作
            step_flag=Carry.Step_Flag[i];  //获取该任务状态
          }
        }
        
        Carry.Step=step;//搬运步骤
        Carry.Step_Enable[step]=1;//搬运使能               
        //具体任务内容见MH1函数
        
      }
      else if(id==3)//将物块从加工区搬运到成品区
      {
        //在执行搬运动作前，需要再次扫描二维码
        //该任务需要根据搬运顺序将物料从加工区搬运到成品区，此处为记录当前的搬运状态，获取将要进行的搬运，搬运状态有两种，前往加工区抓取和前往成品区放置
        for(int16 i=5;i>-1;i--)
        {
          if(Carry2.Step_Flag[i]!=1) 
          {
            step2=i;               //获取下个搬运动作，只要是未完成就继续该动作
            step_flag2=Carry2.Step_Flag[i];  //获取该任务状态
          }
        }
        Carry2.Step=step2;//搬运步骤
        Carry2.Step_Enable[step2]=1;//搬运使能
        //具体任务内容见MH2函数
      }
    }
    if (Task.Flag[id]==1)//当前任务已完成
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
      if(Task.Bingo)    Task.Status=1;  //如果完成,将任务总线状态置为任务已完成 
      else              Task.Status=0; //如果没有完成   
    }
  }
  /*-----------------------------当前任务已完成------------------------------*/
  else if(Task.Status==1)
  {
    //判断所有任务完成情况
    //若当前任务已经完成，但还有其他任务，释放任务总线
    if(id<3)
    {
      Task.Status=-1;
    }
    else
    {
      Task.ID=5;//ID5不存在，完成一次后返回
      Task.Status=1;
      CYS_Transfer_Without_Corr(Area.Home[0].X,Area.Home[0].Y);
      Task.Pos_Hold=0;
      Robot_Position(POSItion.first.Start,POSItion.second.START,POSItion.third.START,POSItion.fourth.open,0);  
      //回到出发点停车
      if(my_abs(Ops9.Pos_X-Task.Pos_X)<5&&my_abs(Ops9.Pos_Y-Task.Pos_Y)<5)
      {
        Task.STOP=1; 
        Task.STOP=0; 
        CYS_Transfer_Without_Corr(Area.Home[1].X,Area.Home[1].Y);
        systick_delay_ms(2000);
        Task.STOP=1; 
        Task.Pos_Hold=0;
      }
      //若要继续任务需要在返回出发点之后将任务初始化，即调用Task_Init(),同时需要获取运行的总时间，确保三分钟之内完成并返回到出发点
    }
    //若所有任务都已经完成，回到出发点
  }
}

/******************************************************************************/
//子任务
/******************************************************************************/
/******************************************************************************/
//任务名：前往任务执行准备区
//任务功能：
//任务参数：
//任务完成指标：OPS传感器数据为出发点数据
/******************************************************************************/
void Task_Departure()//出发
{
  if(Task.Status==-1)     //判断任务总线是否有任务在运行
  {
    if(Task.Enable[0]==1&& Task.Flag[0]==-1)//判断任务是否被使能
    {
      Task.Pos_X=Area.Departure[0].X;
      Task.Pos_Y=Area.Departure[0].Y;    
      Task.Pos_Hold=0;
      Grasp_flag = 1;
      Task.Status=0;        //将任务总线状态切换为任务正在执行；
      Task.Flag[0]=0;      // 将子任务状态标志位切换为正在执行；
    }
  }
  //判断当前任务完成情况
  if(Task.Flag[0]==0)
  {
    if(Task.Pos_Hold==1)
    {
      Grasp_flag = 0;
      CYS_Transfer(Area.Departure[1].X,Area.Departure[1].Y,Area.Departure[1].X,Area.Departure[1].Y);
      Scan_QR_Code1();
      //显示二维码
      oled_printf_int32(60,1,Task.Code1[0],1);
      oled_printf_int32(80,1,Task.Code1[1],1);
      oled_printf_int32(100,1,Task.Code1[2],1);
      Robot_Position(POSItion.first.Material,POSItion.second.Color_Recognition[0],POSItion.third.Color_Recognition[0],POSItion.fourth.open,0);     
      Task.Flag[0]=1;
    }
  }
  //如果完成将子任务状态标志位切换为已完成，此时不释放任务总线，交由任务切换器释放
}

/******************************************************************************/
//任务名：扫描二维码与颜色识别
//任务功能：到达二维码扫描区域，并获得正确二维码数据
//任务参数：1.二维码扫描位置；2.二维码模块扫描指令
//任务完成指标：tof传感器数据为二维码扫描点位置（加入光电开关精确定点函数），得到经重复校验后的正确二维码数据
/******************************************************************************/
void Task_Pattern_Recognition()//扫描二维码与识别物块颜色
{ 
  if(Task.Status==-1)     //判断任务总线是否有任务在运行
  {
    if(Task.Enable[1]==1&& Task.Flag[1]==-1)//判断任务是否被使能
    {
      CYS_Transfer(Area.Departure[1].X,Area.Departure[1].Y,Check_Point_X[0],Check_Point_Y[0]);
      while(!Task.Pos_Hold);
      CYS_Transfer(Check_Point_X[0],Check_Point_Y[0],Check_Point_X[1],Check_Point_Y[1]);
      while(!Task.Pos_Hold);
      CYS_Transfer(Check_Point_X[1],Check_Point_Y[1],Area.Recognition.X,Area.Recognition.Y);
      
      Task.Pos_Hold=0;
      Task.Pos_Acu=0;
      Task.Pos_Check_Flag=0;
      
      Task.Status=0;        //将任务总线状态切换为任务正在执行；
      Task.Flag[1]=0;      // 将子任务状态标志位切换为正在执行；
    }
  }
  
  if(Task.Flag[1]==0)
  {
    if(Task.Pos_Hold)//判断是否已经到达二维码识别区
    {     
      systick_delay_ms(100);
      //开启颜色识别   
      Colour_Recognition();
      
      //      oled_printf_int32(8,7,Task.Colour1[0],1);
      //      oled_printf_int32(48,7,Task.Colour1[1],1);
      //      oled_printf_int32(96,7,Task.Colour1[2],1);  
      
      //信息匹配
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
//任务名：物料搬运
//任务功能：
//任务参数：
//任务完成指标：
/******************************************************************************/

void Task_MH1()
{
    if(Task.Status==-1)     //判断任务总线是否有任务在运行
    {
        if(Task.Enable[2]==1&& Task.Flag[2]==-1)//判断任务是否被使能
        {
            Task.Status=0;        //将任务总线状态切换为任务正在执行；
            Task.Flag[2]=0;      // 将子任务状态标志位切换为正在执行；
            Task.Pos_Hold=0;
        }
    }
    
    if(Task.Flag[2]==0) Path_Planer(Carry);
}

/******************************************************************************/
//任务名：物料搬运
//任务功能：1.按顺序搬运指定物料
//任务参数：1.目标位置；2.机械手指令（抓取，放置//抓取放置完成后，旋转等剩余动作由机械手自主完成，机械手只需返回状态标志位交由任务调度函数处理）
//任务完成指标：1.tof传感器数据为任务调度函数指定点位，2.到达指定点位后的机械手指令（或交由任务调度函数完成）
/******************************************************************************/
uint8 PP_FLAG=0;
void Task_MH2()//搬运物料
{  
  if(Task.Status==-1)     //判断任务总线是否有任务在运行
  {
    if(Task.Enable[3]==1&& Task.Flag[3]==-1)//判断任务是否被使能
    {
      CYS_Transfer_Without_Corr(Check_Point_X[1],Check_Point_Y[1]);
      while(!Task.Pos_Hold);
      CYS_Transfer(Check_Point_X[1],Check_Point_Y[1],Check_Point_X[0],Check_Point_Y[0]);
      while(!Task.Pos_Hold);
      CYS_Transfer(Check_Point_X[0],Check_Point_Y[0],Area.Departure[2].X,Area.Departure[2].Y);
      
      Task.Status=0;        //将任务总线状态切换为任务正在执行；
      Task.Flag[3]=0;      // 将子任务状态标志位切换为正在执行；
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
//数据处理与决策
/******************************************************************************/
//信息匹配（第一次扫描的二维码与物料区色块）
void Information_Match_Grasp1()
{
  uint8 i,j;
  for(i=0;i<3;i++)
  {
    for(j=0;j<3;j++)
    {
      if(Task.Code1[i]==Task.Colour1[j])//将命令色块搬运顺序与色块实际位置匹配
      {
        Task.Target1[i]=j;//j为0，1，2分别对应左，中，右
      }
    }
  }
}
//信息匹配（第一次扫描的二维码与加工区色块）
void Information_Match_Place1()
{
  uint8 i,j;
  for(i=0;i<3;i++)
  {
    for(j=0;j<3;j++)
    {
      if(Task.Code1[i]==Task.Colour2[j])//将命令色块搬运顺序与色块实际位置匹配
      {
        Task.Target2[i]=j;//j为0，1，2分别对应左，中，右
      }
    }
  }   
}
//信息匹配（第二次扫描的二维码与加工区色块）
void Information_Match_Grasp2()
{
  uint8 i,j;
  for(i=0;i<3;i++)
  {
    for(j=0;j<3;j++)
    {
      if(Task.Code2[i]==Task.Colour2[j])//将命令色块搬运顺序与色块实际位置匹配
      {
        Task.Target2[i]=j;//j为0，1，2分别对应左，中，右
      }
    }
  }   
}
//信息匹配（第二次扫描的二维码与成品区色块）
void Information_Match_Place2()
{
  uint8 i,j;
  for(i=0;i<3;i++)
  {
    for(j=0;j<3;j++)
    {
      if(Task.Code2[i]==Task.Colour3[j])//将命令色块搬运顺序与色块实际位置匹配
      {
        Task.Target3[i]=j;//j为0，1，2分别对应左，中，右
      }
    }
  }   
}

//路径规划
void Path_Planer(Carry_Obj_Struct struct_carry)
{
  if(struct_carry.Step==0&&struct_carry.Step_Enable[0]==1)//抓取物块1
  {
    Grasping(struct_carry);//抓取函数      
  }
  else if(struct_carry.Step==1)//放置物块1
  {
    if(MODE ==0){
      if(!colour_rec1&&Task.ID==2)PlaceArea_Colour_Rec(struct_carry);
      else if(colour_rec1&&!colour_rec2&&Task.ID==3)PlaceArea_Colour_Rec(struct_carry);
      if(colour_rec1&&Task.ID==2)  Placing(struct_carry);
      else if(colour_rec1&&colour_rec2&&Task.ID==3) Placing(struct_carry);
    }
    else if(MODE ==1)Placing(struct_carry);
  }
  else if(struct_carry.Step==2)//抓取物块2
  {
    Grasping(struct_carry);//抓取函数       
  }
  else if(struct_carry.Step==3)//放置物块2
  {
    Placing(struct_carry);
  }
  else if(struct_carry.Step==4)//抓取物块3
  {       
    Grasping(struct_carry);//抓取函数      
  }
  else if(struct_carry.Step==5&&struct_carry.Step_Flag[struct_carry.Step]!=1)//放置物块3
  {
    Placing(struct_carry);
  }
}

//抓取动作
void Grasping(Carry_Obj_Struct struct_carry)//抓取函数
{
  if(struct_carry.Step_Flag[struct_carry.Step]==-1&&struct_carry.Step_Enable[struct_carry.Step]==1)//判断动作标志位是否为未完成（-1）但已使能（1）
  {   
    if(Task.ID==2)//判断当前任务ID（2：物料区到加工区）
    {   
      Carry.Step_Flag[struct_carry.Step]=0;//将动作标志位置0，动作正在进行
      
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
    else if(Task.ID==3)//判断当前任务ID（3：加工区到成品区）
    {       
      Robot_Position(POSItion.first.Process,POSItion.second.Process.Grasp[2],POSItion.third.Process.Grasp[2],POSItion.fourth.open,0);
      Carry2.Step_Flag[struct_carry.Step]=0;//将动作标志位置0，动作正在进行
      
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
        Task.Pos_X=Area.Process_B[Task.Target2[struct_carry.Step/2]].X;//将目标位置设置为加工区
        Task.Pos_Y=Area.Process_B[Task.Target2[struct_carry.Step/2]].Y + 5;
        break;
      case 1:
        Task.Pos_X=Area.Process_B[Task.Target2[struct_carry.Step/2]].X - 5;//将目标位置设置为加工区
        Task.Pos_Y=Area.Process_B[Task.Target2[struct_carry.Step/2]].Y;
        break;
      case 2:
        Task.Pos_X=Area.Process_B[Task.Target2[struct_carry.Step/2]].X;//将目标位置设置为加工区
        Task.Pos_Y=Area.Process_B[Task.Target2[struct_carry.Step/2]].Y - 5;
        break;
      case 3:
        Task.Pos_X=Area.Process_B[Task.Target2[struct_carry.Step/2]].X + 5;//将目标位置设置为加工区
        Task.Pos_Y=Area.Process_B[Task.Target2[struct_carry.Step/2]].Y;
        break;
      }
      Task.Pos_Hold=0;
      Grasp_flag = 1;
    }
  }
  if(Task.Pos_Hold)//判断是否已经到达抓取区域
  {
    //到达目标区域后停车
    Task.STOP=1;
    Grasp_flag = 0;
    if(Task.ID==2)//判断当前任务ID（2：物料区到加工区）
    {
      Robot_Position(0,POSItion.second.Material.Grasp[0],POSItion.third.Material.Grasp[0],POSItion.fourth.open,1200);
      Robot_Position(0,POSItion.second.Material.Grasp[0],POSItion.third.Material.Grasp[0],POSItion.fourth.close,1200);
    }
    else if(Task.ID==3)//判断当前任务ID（3：加工区到成品区）
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
//放置动作
void Placing(Carry_Obj_Struct struct_carry)
{
  if(struct_carry.Step_Flag[struct_carry.Step]==-1&&struct_carry.Step_Enable[struct_carry.Step]==1)//判断动作标志位是否为未完成（-1）但已使能（1）
  {        
    if(Task.ID==2)//判断当前任务ID（2：物料区到加工区）
    {
      Carry.Step_Flag[struct_carry.Step]=0;//将动作标志位置0，动作正在进行
      Robot_Position(0,POSItion.second.Material.Grasp[1],POSItion.third.Material.Grasp[1],POSItion.fourth.close,500);
      CYS_Transfer_Without_Corr(Area.Process[Task.Target2[struct_carry.Step/2]].X,Area.Process[Task.Target2[struct_carry.Step/2]].Y);
      Task.Pos_Hold=0;
      final_flag=0;
      
    }
    else if(Task.ID==3)//判断当前任务ID（3：加工区到成品区）
    {  
      Carry2.Step_Flag[struct_carry.Step]=0;//将动作标志位置0，动作正在进行
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
      if(Task.ID==2)//判断当前任务ID（2：物料区到加工区）
      {
        Robot_Position(POSItion.first.Process,POSItion.second.Process.place[2],POSItion.third.Process.place[2],POSItion.fourth.close,0);
      }
      if(Task.ID==3)//判断当前任务ID（2：物料区到加工区）
      {
        Robot_Position(POSItion.first.Final,POSItion.second.Final.place[2],POSItion.third.Final.place[2],POSItion.fourth.close,0);
      }
    }
    
    if(final_flag==0)///识别色环圆心
    {
      if(Task.Pos_Hold)//判断是否已经到达放置区域
      {
        Task.STOP=1;
        if(Task.ID==2)//判断当前任务ID（2：物料区到加工区）
        {
          CYS_Transfer(Area.Process[Task.Target2[struct_carry.Step/2]].X,Area.Process[Task.Target2[struct_carry.Step/2]].Y,Area.Process[Task.Target2[struct_carry.Step/2]].X+ STEP1_X, Area.Process[Task.Target2[struct_carry.Step/2]].Y + STEP1_Y);
          Area.Process_B[Task.Target2[struct_carry.Step/2]].X = Task.Pos_X;
          Area.Process_B[Task.Target2[struct_carry.Step/2]].Y = Task.Pos_Y;
          Task.Pos_Hold=0;
          final_flag=1;
        }
        else if(Task.ID==3)//判断当前任务ID（2：物料区到加工区）
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
      if(Task.ID==2)//判断当前任务ID（2：物料区到加工区）
      {
        Robot_Position(POSItion.first.Process,POSItion.second.Process.place[2],POSItion.third.Process.place[2],POSItion.fourth.close,0);
      }
      if(Task.ID==3)//判断当前任务ID（2：物料区到加工区）
      {
        Robot_Position(POSItion.first.Final,POSItion.second.Final.place[2],POSItion.third.Final.place[2],POSItion.fourth.close,0);
      }
    }
    
    if(final_flag==1)
    {
      
      if(Task.Pos_Hold)//判断是否已经到达放置区域
      {
        //到达目标区域后停车
        Task.STOP=1;
        if(Task.ID==2)//判断当前任务ID（2：物料区到加工区）
        {
          Robot_Position(0,0,POSItion.third.Process.place[0],0,150);
          Robot_Position(0,POSItion.second.Process.place[0],POSItion.third.Process.place[0],POSItion.fourth.close,1300);
          Robot_Position(0,POSItion.second.Process.place[0],POSItion.third.Process.place[0],POSItion.fourth.open,500);
          Robot_Position(0,POSItion.second.Process.place[1],POSItion.third.Process.place[1],POSItion.fourth.open,500);
          Robot_Position(0,POSItion.second.Process.place[2],POSItion.third.Process.place[2],POSItion.fourth.open,700);
        }
        else if(Task.ID==3)//判断当前任务ID（3：加工区到成品区）
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
            Task.Flag[2]=1;//MH1任务结束
          }
          else if(Task.ID==3)
          {
            Task.Flag[3]=1;//MH2任务结束
          }
        }
      }
    }
  }
}

//第一次扫描二维码
void Scan_QR_Code1()
{
  do{ Barcode_Scan_Command();systick_delay_ms(500);}
  while(!getQRCode.receiveComplete);//扫码不成功
  Task.Code1[0]=getQRCode.first[0];       //存储二维码命令
  Task.Code1[1]=getQRCode.second[0];
  Task.Code1[2]=getQRCode.third[0]; 
}

//第二次扫描二维码
//void Scan_QR_Code2()
//{
//  do{ Barcode_Scan_Command();systick_delay_ms(500);}
//  while(!getQRCode.receiveComplete);//扫码不成功
//  Task.Code2[0]=getQRCode.first;       //存储二维码命令
//  Task.Code2[1]=getQRCode.second;
//  Task.Code2[2]=getQRCode.third; 
//  Scan2_Complete = 1;
//}

//颜色识别
void Colour_Recognition()
{
  OpenMV_uart_init();
  if(Round == 0)
  {
  do{ OpenMV_Step1_Command();systick_delay_ms(50);}
  while(!myOpenMV.receiveComplete);//注意程序采集5次取中间一次后就结
  Task.Colour1[0]=myOpenMV.Left_N;   //存储色块颜色（左中右颜色）
  Task.Colour1[1]=myOpenMV.Middle_N;
  Task.Colour1[2]=myOpenMV.Right_N;
  }
  else if(Round == 1)
  {
  int counter = 0;
  do{ OpenMV_Step1_Command();systick_delay_ms(50);counter ++;}
  while(!myOpenMV.receiveComplete && counter <= 100);//注意程序采集5次取中间一次后就结
  Task.Colour1[0]=myOpenMV.Left_N;   //存储色块颜色（左中右颜色）
  Task.Colour1[1]=myOpenMV.Middle_N;
  Task.Colour1[2]=myOpenMV.Right_N;
  }
  
}

//色环颜色识别
void PlaceArea_Colour_Rec(Carry_Obj_Struct struct_carry)
{
  uint8 temp1[10],temp2[10],i,j;
  if(struct_carry.Step_Flag[struct_carry.Step]==-1&&struct_carry.Step_Enable[struct_carry.Step]==1)//判断是否已经到达二维码识别区    
  {
    colour_rec=0;
    if(Task.ID==2)//判断当前任务ID（2：物料区到加工区）
    {
      Task.Pos_X=Area.Color_Recognition1[0].X;//Area.Color_Recognition1[0].X;//Area.Process[Task.Target2[struct_carry.Step/2]].X;//将目标位置设置为加工区
      Task.Pos_Y=Area.Color_Recognition1[0].Y;//Area.Color_Recognition1[0].Y;//Area.Process[Task.Target2[struct_carry.Step/2]].Y;   
      Task.Pos_Hold=0;
      
    }
    if(Task.ID==3)//判断当前任务ID（2：物料区到加工区）
    {
      Task.Pos_X=Area.Color_Recognition2[0].X;//Area.Color_Recognition2[0].X;//Area.Process[Task.Target2[struct_carry.Step/2]].X;//将目标位置设置为加工区
      Task.Pos_Y=Area.Color_Recognition2[0].Y;//Area.Color_Recognition2[0].Y;//Area.Process[Task.Target2[struct_carry.Step/2]].Y;
      Task.Pos_Hold=0;
    }
  }
  while(Task.Pos_Hold==0){
    if(Task.ID==2)//判断当前任务ID（2：物料区到加工区）
    {
      Robot_Position(POSItion.first.Process,POSItion.second.Process.place[2],POSItion.third.Process.place[2],POSItion.fourth.close,0);
    }
    if(Task.ID==3)//判断当前任务ID（2：物料区到加工区）
    {
      Robot_Position(POSItion.first.Final,POSItion.second.Final.place[2],POSItion.third.Final.place[2],POSItion.fourth.close,0);
    }
  };
  if(Task.Pos_Hold)//判断是否已经到达二维码识别区
  {
    while(gpio_get(A13));
    Task.STOP=1;
    if(Task.ID==2)//判断当前任务ID（2：物料区到加工区）
    {
      Robot_Position(0,POSItion.second.Color_Recognition[1],POSItion.third.Color_Recognition[1],POSItion.fourth.close,0);
      OpenMV_uart_init();
      systick_delay_ms(1000);
      for(uint8 cnt=0;cnt<10;cnt++)
      {
        do{OpenMV_Step2_Left_Command();systick_delay_ms(50);}//识别位置0颜色
        while(!myOpenMV.receiveComplete);
        
        temp1[cnt]=myOpenMV.Step2Left;    //存储加工区左边颜色到Task.Colour2[0] 
        
      }
      Robot_Position(0,POSItion.second.Color_Recognition[1],POSItion.third.Color_Recognition[1],POSItion.fourth.close,0);
      OpenMV_uart_init();
      systick_delay_ms(700);
      for(uint8 cnt=0;cnt<10;cnt++)
      {
        do{OpenMV_Step2_Left_Command();systick_delay_ms(50);}//识别位置0颜色
        while(!myOpenMV.receiveComplete);
        temp2[cnt]=myOpenMV.Step2Left;    //存储加工区左边颜色到Task.Colour2[0] 
      }
      systick_delay_ms(300);
      
      uint8 filter_temp1=0;
      for(j=0;j<9;j++)                      //采样值从小到大排列（冒泡法）
      {
        for(i=0;i<9-j;i++)
        {
          if(temp1[i]>temp1[i+1])
          {
            filter_temp1 = temp1[i];         //第一维调换
            temp1[i] = temp1[i+1];
            temp1[i+1] = filter_temp1;                          
          }
        }
      }
      Task.Colour2[0]=temp1[4];
      oled_uint16(8,3,Task.Colour2[0]);
      
      uint8 filter_temp2=0;
      for(j=0;j<9;j++)                      //采样值从小到大排列（冒泡法）
      {
        for(i=0;i<9-j;i++)
        {
          if(temp2[i]>temp2[i+1])
          {
            filter_temp2 = temp2[i];         //第一维调换
            temp2[i] = temp2[i+1];
            temp2[i+1] = filter_temp2;                          
          }
        }
      }
      
      Task.Colour2[1]=temp2[4]; //存储加工区中间颜色到Task.Colour2[1]
      oled_uint16(48,3,Task.Colour2[1]);
      
      if(Task.Colour2[0]!=1&&Task.Colour2[1]!=1)Task.Colour2[2]=1;//根据前两个区域颜色判断第三个区域颜色
      else if(Task.Colour2[0]!=2&&Task.Colour2[1]!=2)Task.Colour2[2]=2;//根据前两个区域颜色判断第三个区域颜色
      else if(Task.Colour2[0]!=3&&Task.Colour2[1]!=3)Task.Colour2[2]=3;//根据前两个区域颜色判断第三个区域颜色
      
      oled_uint16(96,3,Task.Colour2[2]);
      Information_Match_Place1();//将当前获取的加工区颜色与二维码1匹配
      
      colour_rec1=1;
      Task.STOP=0;
      
    }
    else if(Task.ID==3)//判断当前任务ID（2：物料区到加工区）
    {
      //while(gpio_get(A13));
      Robot_Position(0,POSItion.second.Color_Recognition[1],POSItion.third.Color_Recognition[1],POSItion.fourth.close,0);
      //移动到成品区指定位置       
      OpenMV_uart_init();
      //while(gpio_get(A13));
      systick_delay_ms(1000);
      for(uint8 cnt=0;cnt<10;cnt++)
      {
        do{OpenMV_Step2_Left_Command();systick_delay_ms(50);}//识别位置0颜色
        while(!myOpenMV.receiveComplete);
        
        temp1[cnt]=myOpenMV.Step2Left;    //存储加工区左边颜色到Task.Colour3[0] 
        
      }
      
      Robot_Position(0,POSItion.second.Color_Recognition[1],POSItion.third.Color_Recognition[1],POSItion.fourth.close,0);
      OpenMV_uart_init();
      systick_delay_ms(700);
      
      for(uint8 cnt=0;cnt<10;cnt++)
      {
        do{OpenMV_Step2_Left_Command();systick_delay_ms(50);}//识别位置0颜色
        while(!myOpenMV.receiveComplete);
        
        temp2[cnt]=myOpenMV.Step2Left;    //存储加工区左边颜色到Task.Colour3[0] 
      }
      systick_delay_ms(300);
      uint8 filter_temp1=0;
      for(j=0;j<9;j++)                      //采样值从小到大排列（冒泡法）
      {
        for(i=0;i<9-j;i++)
        {
          if(temp1[i]>temp1[i+1])
          {
            filter_temp1 = temp1[i];         //第一维调换
            temp1[i] = temp1[i+1];
            temp1[i+1] = filter_temp1;                          
          }
        }
      }
      Task.Colour3[0]=temp1[4];
      oled_uint16(8,3,Task.Colour3[0]);
      
      uint8 filter_temp2=0;
      for(j=0;j<9;j++)                      //采样值从小到大排列（冒泡法）
      {
        for(i=0;i<9-j;i++)
        {
          if(temp2[i]>temp2[i+1])
          {
            filter_temp2 = temp2[i];         //第一维调换
            temp2[i] = temp2[i+1];
            temp2[i+1] = filter_temp2;                          
          }
        }
      }
      
      Task.Colour3[1]=temp2[4]; //存储加工区中间颜色到Task.Colour3[1]
      oled_uint16(48,3,Task.Colour3[1]);
      
      if(Task.Colour3[0]!=1&&Task.Colour3[1]!=1)Task.Colour3[2]=1;//根据前两个区域颜色判断第三个区域颜色
      else if(Task.Colour3[0]!=2&&Task.Colour3[1]!=2)Task.Colour3[2]=2;//根据前两个区域颜色判断第三个区域颜色
      else if(Task.Colour3[0]!=3&&Task.Colour3[1]!=3)Task.Colour3[2]=3;//根据前两个区域颜色判断第三个区域颜色
      
      oled_uint16(96,3,Task.Colour3[2]);
      
      Information_Match_Place2();//将当前获取的成品区颜色与二维码2匹配
      colour_rec2=1;
      Task.STOP=0;
    }
  }
}

