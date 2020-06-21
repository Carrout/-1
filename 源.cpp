#pragma warning(disable:4996)
#include<graphics.h>
#include<conio.h>
#include<time.h>
#pragma comment(lib,"Winmm.lib")

void initial();
void human_move(int x, int y, int r);
void updateWithoutInput(int r);
void updateWithInput(int r);
void show(int r);

IMAGE boll, cloud, cloud1, bkg, run[6], run1[6];
POINT boll_1, cloud_1, cloud_2, bkg_0;
int k = 6, z = 0;
/*
void transparentimage(int x, int y, IMAGE* srcimg, IMAGE* maskimg)  //无背景图实现透明贴图
{
	putimage(x, y, maskimg, SRCAND);
	putimage(x, y, srcimg, SRCPAINT);

*/
int main()
{
	double t = 0;
	int r;
	initial();
	srand((unsigned)time(NULL));
	while (true)
	{
		r = int(t * 10) % 5;
		cleardevice();
		show(r);
		updateWithoutInput(r);
		updateWithInput(r);
		FlushMouseMsgBuffer();
		t += 0.1;
		Sleep(50);
	}
	getch();
	closegraph();
	return 0;
}
void initial()
{
	initgraph(1280, 720);

	loadimage(&bkg, _T("F:\\C语言课程设计\\GD\\bkg.png"));
	loadimage(&boll, _T("F:\\C语言课程设计\\GD\\boll.png"));
	loadimage(&run[0], _T("F:\\C语言课程设计\\GD\\run_0.png"));
	loadimage(&run1[0], _T("F:\\C语言课程设计\\GD\\run_0_0.png"));
	loadimage(&run[1], _T("F:\\C语言课程设计\\GD\\run_1.png"));
	loadimage(&run1[1], _T("F:\\C语言课程设计\\GD\\run_1_0.png"));
	loadimage(&run[2], _T("F:\\C语言课程设计\\GD\\run_2.png"));
	loadimage(&run1[2], _T("F:\\C语言课程设计\\GD\\run_2_0.png"));
	loadimage(&run[3], _T("F:\\C语言课程设计\\GD\\run_3.png"));
	loadimage(&run1[3], _T("F:\\C语言课程设计\\GD\\run_3_0.png"));
	loadimage(&run[4], _T("F:\\C语言课程设计\\GD\\run_4.png"));
	loadimage(&run1[4], _T("F:\\C语言课程设计\\GD\\run_4_0.png"));
	loadimage(&run[5], _T("F:\\C语言课程设计\\GD\\run_5.png"));
	loadimage(&run1[5], _T("F:\\C语言课程设计\\GD\\run_5_0.png"));
	loadimage(&cloud, _T("F:\\C语言课程设计\\GD\\cloud.png"));
	loadimage(&cloud1, _T("F:\\C语言课程设计\\GD\\cloud_0.png"));
	mciSendString(_T("open \"E:\\Music\\Tanchiky - COME ON! DISCO THE SOULS.mp3\" alias mymusic"), NULL, 0, NULL);
	mciSendString(_T("play mymusic"), NULL, 0, NULL);
	boll_1.x = 0, cloud_1.x = 1200, cloud_2.x = 500, bkg_0.x = 0;
	boll_1.y = 600, cloud_1.y = 300, cloud_2.x = 400, bkg_0.y = 0;
	BeginBatchDraw();
}
void show(int r)
{
	putimage(bkg_0.x, bkg_0.y, &bkg);
	putimage(1280 - z, 0, &bkg);

	putimage(cloud_1.x, cloud_1.y, &cloud1, NOTSRCERASE);
	putimage(cloud_1.x, cloud_1.y, &cloud, SRCINVERT);
	putimage(cloud_2.x, cloud_2.y, &cloud1, NOTSRCERASE);
	putimage(cloud_2.x, cloud_2.y, &cloud, SRCINVERT);
	/*
	transparentimage(320, 0, &run[1], &run1[1]);
	*/
	bkg_0.x -= 1;
	z += 1;
	if (z == 1280)
		z = 0;
	if (bkg_0.x == -1280)
		bkg_0.x = 0;
	if (cloud_1.x <= 0)
	{
		cloud_1.y = rand() % 400;
		cloud_1.x = 1210;
	}
	if (cloud_2.x <= 0)
	{
		cloud_2.y = rand() % 400;
		cloud_2.x = 1280;
	}
	cloud_1.x -= 10;
	cloud_2.x -= 10;
	human_move(boll_1.x, boll_1.y, r);
	if (boll_1.x <= 300)
	{
		boll_1.x += 10;
	}
	FlushBatchDraw();
	Sleep(30);
}
void updateWithoutInput(int r)
{
	if (boll_1.y < 600)
	{
		for (boll_1.y;boll_1.y < 600;boll_1.y += 20)
		{
			show(r);
			Sleep(30);
		}
	}
}
void updateWithInput(int r)
{
	int jump_real = 0;
	char input, jump_high = 55;   //一次性起跳高度
	const int jump_lim = 420;    //增加起跳动画帧率
	MOUSEMSG m;
	if (MouseHit())
	{
		POINT pt;
		m = GetMouseMsg();
		if (GetKeyState(0x1) < 0)
		{
			for (jump_real;jump_real < jump_lim;jump_real += 70)
			{
				cleardevice();
				boll_1.y -= jump_high;
				jump_real += jump_high;
				show(r);
				Sleep(30);
			}
		}
	}
}
void human_move(int x, int y, int r)
{
	static IMAGE oldimg;

	putimage(x, y, &run1[r], NOTSRCERASE);
	putimage(x, y, &run[r], SRCINVERT);
	FlushBatchDraw();
}