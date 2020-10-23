#include "Map.h"

Area_Pos_Struct  Area;
float Correction_X,Correction_Y;
float Correction_W;
float A_,X_OPS,Y_OPS;
float X_Actual,Y_Actual;
float X_Exp_OPS,Y_Exp_OPS;
float CYS_Err_X,CYS_Err_Y;

void Area_Init()
{
  //��������OPS���꣩
    Area.Pos_Check.X=0.0f;
    Area.Pos_Check.Y=0.0f;
    
    Area.Original_Point.X=0.0f;
    Area.Original_Point.Y=0.0f;
    
  //���������������꣩
    Area.Home[0].X= 450.0f;
    Area.Home[0].Y= 350.0f;
    Area.Home[1].X= 120.0f;
    Area.Home[1].Y= 150.0f;
    
    //������׼��
    Area.Departure[0].X=405.0f;    //��OPS���꣩
    Area.Departure[0].Y=1642.0f;   //��OPS���꣩
    Area.Departure[1].X=600.0f;
    Area.Departure[1].Y=1800.0f;
    Area.Departure[2].X=600.0f;
    Area.Departure[2].Y=1800.0f;
    
    //������
    Area_Material_Init(Material_Pos_X, Material_Pos_Y, Material_Dir);
    
    //�ӹ���
    Area_Process_Init(Process_Pos_X, Process_Pos_Y, Process_Dir);
    
    //��Ʒ��
    Area_Final_Init(Final_Pos_X, Final_Pos_Y, Final_Dir);
}

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
//��������ɫλ�ó�ʼ��
//dir������ĳ���
void Area_Material_Init(float x,float y,int dir)
{
  //�����������������ɫʶ������
  Area.Recognition.X = x;
  Area.Recognition.Y = y;
  //���ݲ�ͬ���򣬼���ץȡ������
  switch(dir)
  {
    case 0:
      Area.Material[1].X = x;
      Area.Material[1].Y = y - Color_err;
      Area.Material[0].X = Area.Material[1].X - Material_err;
      Area.Material[0].Y = Area.Material[1].Y;
      Area.Material[2].X = Area.Material[1].X + Material_err;
      Area.Material[2].Y = Area.Material[1].Y;
      POSItion.first.Material = Material_Dir0;
      break;
    case 1:
      Area.Material[1].X = x + Color_err;
      Area.Material[1].Y = y;
      Area.Material[0].X = Area.Material[1].X;
      Area.Material[0].Y = Area.Material[1].Y - Material_err;
      Area.Material[2].X = Area.Material[1].X;
      Area.Material[2].Y = Area.Material[1].Y + Material_err;
      POSItion.first.Material = Material_Dir1;
      break;
    case 2:
      Area.Material[1].X = x;
      Area.Material[1].Y = y + Color_err;
      Area.Material[0].X = Area.Material[1].X + Material_err;
      Area.Material[0].Y = Area.Material[1].Y;
      Area.Material[2].X = Area.Material[1].X - Material_err;
      Area.Material[2].Y = Area.Material[1].Y;
      POSItion.first.Material = Material_Dir2;
      break;
    case 3:
      Area.Material[1].X = x - Color_err;
      Area.Material[1].Y = y;
      Area.Material[0].X = Area.Material[1].X;
      Area.Material[0].Y = Area.Material[1].Y + Material_err;
      Area.Material[2].X = Area.Material[1].X;
      Area.Material[2].Y = Area.Material[1].Y - Material_err;
      POSItion.first.Material = Material_Dir3;
      break;
  }
}

void Area_Process_Init(float x,float y,int dir)
{
  //����ӹ����м���õ�����
  Area.Process[1].X = x;
  Area.Process[1].Y = y;
  //���ݲ�ͬ���򣬼��������������õ�����
  switch(dir)
  {
    case 0:
      Area.Process[0].X = x - Process_err;
      Area.Process[0].Y = y;
      Area.Process[2].X = x + Process_err;
      Area.Process[2].Y = y;
      POSItion.first.Process = Process_Dir0;
      break;
    case 1:
      Area.Process[0].X = x;
      Area.Process[0].Y = y - Process_err;
      Area.Process[2].X = x;
      Area.Process[2].Y = y + Process_err;
      POSItion.first.Process = Process_Dir1;
      break;
    case 2:
      Area.Process[0].X = x + Process_err;
      Area.Process[0].Y = y;
      Area.Process[2].X = x - Process_err;
      Area.Process[2].Y = y;
      POSItion.first.Process = Process_Dir2;
      break;
  case 3:
      Area.Process[0].X = x;
      Area.Process[0].Y = y + Process_err;
      Area.Process[2].X = x;
      Area.Process[2].Y = y - Process_err;
      POSItion.first.Process = Process_Dir3;
      break;
  }
  //�˴�Ϊ�ӹ���ɫ����ɫʶ������꣨�ɲ��ã�
  Area.Color_Recognition1[0].X = (Area.Process[0].X + Area.Process[1].X)/2;
  Area.Color_Recognition1[0].Y = (Area.Process[0].Y + Area.Process[1].Y)/2;
}
void Area_Final_Init(float x,float y,int dir)
{
  //�����Ʒ���м���õ�����
  Area.Final[1].X = x;
  Area.Final[1].Y = y;
  //���ݲ�ͬ���򣬼��������������õ�����
  switch(dir)
  {
    case 0:
      Area.Final[0].X = x - Final_err;
      Area.Final[0].Y = y;
      Area.Final[2].X = x + Final_err;
      Area.Final[2].Y = y;
      POSItion.first.Final = Final_Dir0;
      break;
    case 1:
      Area.Final[0].X = x;
      Area.Final[0].Y = y - Final_err;
      Area.Final[2].X = x;
      Area.Final[2].Y = y + Final_err;
      POSItion.first.Final = Final_Dir1;
      break;
    case 2:
      Area.Final[0].X = x + Final_err;
      Area.Final[0].Y = y;
      Area.Final[2].X = x - Final_err;
      Area.Final[2].Y = y;
      POSItion.first.Final = Final_Dir2;
      break;
    case 3:
      Area.Final[0].X = x;
      Area.Final[0].Y = y + Final_err;
      Area.Final[2].X = x;
      Area.Final[2].Y = y - Final_err;
      POSItion.first.Final = Final_Dir3;
      break;
  }
  //�˴�Ϊ��Ʒ��ɫ����ɫʶ������꣨�ɲ��ã�
  Area.Color_Recognition2[0].X = (Area.Final[0].X + Area.Final[1].X)/2;
  Area.Color_Recognition2[0].Y = (Area.Final[0].Y + Area.Final[1].Y)/2;
}

//����任�� ��ǰ�� �� ��������� ʱʹ�ã�
//ÿ�ε��û����У׼
//���� ��ǰ�������� �� Ŀ���������
//����OpenMVУ׼
//�Զ�����OPS����
void CYS_Transfer(float X_I,float Y_I,float X_Exp,float Y_Exp)
{
  memset(&Connection_Data,0,sizeof(Connection_Data)); 
  Correction_X = DATAx + X_I;
  Correction_Y = DATAy + Y_I;
  Correction_W = DATAw;
  
  A_ = ((Correction_W - Ops9.Angle_Z)*3.1415926/180.0);
  
  X_OPS = (X_Exp - Correction_X)*cos(A_) - (Y_Exp - Correction_Y)*sin(A_) -  (Correction_X- Ops9.Pos_X)*cos(A_);
  Y_OPS = (X_Exp - Correction_X)*sin(A_) +(Y_Exp - Correction_Y)*cos(A_) - (Correction_Y- Ops9.Pos_Y)*cos(A_);
  
  CYS_Err_X = (Correction_X- Ops9.Pos_X)*cos(A_);
  CYS_Err_Y = (Correction_Y- Ops9.Pos_Y)*cos(A_);
  
  Task.Pos_X = Correction_X + X_OPS;
  Task.Pos_Y = Correction_Y + Y_OPS;
  Task.Pos_W = -(Correction_W - Ops9.Angle_Z);
  
  Task.Pos_Hold=0;
}

//����任�� ��ǰ�� ���� ��������� ʱʹ�ã�
//Ŀ���������
//�Զ�����OPS����
void CYS_Transfer_Without_Corr(float X_Exp,float Y_Exp)
{
  X_Actual = Ops9.Pos_Y*sin(A_)+Ops9.Pos_X*cos(A_) + CYS_Err_X;
  Y_Actual = Ops9.Pos_Y*cos(A_)-Ops9.Pos_X*sin(A_) + CYS_Err_Y;
  
  X_OPS = (X_Exp - X_Actual)*cos(A_) - (Y_Exp - Y_Actual)*sin(A_) -CYS_Err_X;
  Y_OPS = (X_Exp - X_Actual)*sin(A_) + (Y_Exp - Y_Actual)*cos(A_) -CYS_Err_Y;
  
  Task.Pos_X = X_Actual + X_OPS;
  Task.Pos_Y = Y_Actual + Y_OPS;
  
  Task.Pos_Hold=0;
}