#include <iostream>
#include<graphics.h>
#define wind_width 800
#define wind_height 400
#define size 50
int num = 0;
void getandsave();
struct dm
{
    char buff[size];
    int x, y;
    COLORREF color;
    int movespace;//控制移动速率
}; 
struct dm DM[1024];
int main()
{
     HWND hwnd = initgraph(wind_width, wind_height, SHOWCONSOLE);//初始化绘图窗口
     SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) - WS_CAPTION);// 去除窗口边框
     RECT rect;
     SystemParametersInfo(SPI_GETWORKAREA, 0, &rect,0); //获取主显示器的工作区矩形
     int width = rect.right / 2;
     int height = rect.bottom / 2;
     SetWindowPos(hwnd, NULL, rect.left, rect.top, width, height,0);// 设置窗口位置为屏幕左上角1/4区域
     SetWindowLong(hwnd,GWL_EXSTYLE,GetWindowLong(hwnd,GWL_EXSTYLE)|WS_EX_LAYERED);//设置窗口样式为透明
     BYTE alpha = 0; // 设置窗口透明度（取值范围0-255，0为完全透明，255为不透明）
     SetLayeredWindowAttributes(hwnd, 0, alpha, LWA_COLORKEY);
     // 刷新窗口
     InvalidateRect(hwnd, NULL, TRUE);
     UpdateWindow(hwnd);
     CreateThread(
        NULL,//线程的安全属性
        NULL,//
        (LPTHREAD_START_ROUTINE)getandsave,//线程函数的地址，指定了线程开始的地方
        NULL,
        NULL,
        NULL
    );
    while (1)
    {
        cleardevice();//清屏
        for (int i = 0; i < num; i++)
        {
            settextcolor(DM[i].color);
            outtextxy(DM[i].x, DM[i].y, DM[i].buff);
        }
        Sleep(30);//控制帧率，sleep值越小，帧率越高
        for (int i = 0; i < num; i++)
        {
            DM[i].x -= DM[i].movespace;
        }
    }
}
void getandsave()
{   
    while (1) 
    {
        std::cout << "请输入弹幕:";
        std::cin.getline(DM[num].buff, size);
        DM[num].x = wind_width;
        DM[num].y = wind_height / 4 + rand() % (wind_height / 2 + 1);
        DM[num].color = RGB(rand() % 256, rand() % 256, rand() % 256);
        DM[num].movespace = 1+rand()%4;
        num++;
    }
}