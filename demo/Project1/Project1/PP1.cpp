#include<iostream>
#include<string>
#include<vector>
#include<graphics.h>
using namespace std;
const int player_time = 4;

#pragma comment(lib, "MSIMG32.LIB")

inline void putimage_a(int x, int y, IMAGE* img) {
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(NULL), x, y, w, h, 
		GetImageHDC(img), 0, 0, w, h,{AC_SRC_OVER,0,255,AC_SRC_ALPHA});
}

class player {
public:
	int Hp = 10;
	int Speed = 8;
	int attack_value = 5;
	int Lv = 1;
	int pos_x = 300;
	int pos_y = 300;
	
	IMAGE player_left[player_time];
	IMAGE player_right[player_time];

	int current_idx = 0;

	void loadAnimation_LR() {
		//向右
		for (size_t i = 0; i < 4; i++) 
		{
			wstring path = L"player/player_r" + to_wstring(i) + L".png";
			loadimage(&player_r[i], path.c_str());
		}
		//向左
		for (size_t i = 0; i < 4; i++)
		{
			wstring path = L"player/player_l" + to_wstring(i) + L".png";
			loadimage(&player_l[i], path.c_str());
		}
		//向下
		for (size_t i = 0; i < 4; i++)
		{
			wstring path = L"player/player_d" + to_wstring(i) + L".png";
			loadimage(&player_dn[i], path.c_str());
		}
		//向上
		for (size_t i = 0; i < 4; i++)
		{
			wstring path = L"player/player_up" + to_wstring(i) + L".png";
			loadimage(&player_up[i], path.c_str());
		}
	}
	//角色移动
	void move(ExMessage &msg) {
		if (msg.message == WM_KEYDOWN)
		{
			switch (msg.vkcode)
			{
			case VK_UP:
				move_up = true;
				break;
			case VK_DOWN:
				move_down = true;
				break;
			case VK_LEFT:
				move_left = true;
				break;
			case VK_RIGHT:
				move_right = true;
				break;
			}
		}
		else if (msg.message == WM_KEYUP)
		{
			switch (msg.vkcode)
			{
			case VK_UP:
				p1 = 1, p2 = 0, p3 = 0, p4 = 0;
				move_up = false;
				break;
			case VK_DOWN:
				p1 = 0, p2 = 1, p3 = 0, p4 = 0;
				move_down = false;
				break;
			case VK_LEFT:
				p1 = 0, p2 = 0, p3 = 1, p4 = 0;
				move_left = false;
				break;
			case VK_RIGHT:
				p1 = 0, p2 = 0, p3 = 0, p4 = 1;
				move_right = false;
				break;
			}
		}
	}
	//角色绘制
	void Draw() {
		if (move_up)putimage_a(pos_x, pos_y, &player_up[current_idx]);
		else if (move_down)putimage_a(pos_x, pos_y, &player_dn[current_idx]);
		else if (move_left)putimage_a(pos_x, pos_y, &player_l[current_idx]);
		else if (move_right)putimage_a(pos_x, pos_y, &player_r[current_idx]);
		else if (!move_up && p1 == 1)putimage_a(pos_x, pos_y, &player_up[current_idx]);
		else if (!move_down && p2 == 1)putimage_a(pos_x, pos_y, &player_dn[current_idx]);
		else if (!move_left && p3 == 1)putimage_a(pos_x, pos_y, &player_l[current_idx]);
		else if (!move_right && p4 == 1)putimage_a(pos_x, pos_y, &player_r[current_idx]);
	}
	void Speed_change() {
		if (move_up)pos_y -= Speed;
		else if (move_down)pos_y += Speed;
		else if (move_left)pos_x -= Speed;
		else if (move_right)pos_x += Speed;
	}

	int timer = 0;
	int idx_player = 0;
	int interval_ms = 0;
	IMAGE player_r[4];
	IMAGE player_l[4];
	IMAGE player_dn[4];
	IMAGE player_up[4];
	bool move_up = false;
	bool move_down = false;
	bool move_left = false;
	bool move_right = false;
	int p1 = 0, p2 = 0, p3 = 0, p4 = 1;
};

class Monster {
public:
	int Hp;
	int Speed; 
};

class bullet {
public:
	POINT pos = { 0,0 };
public:
	bullet() = default;
	~bullet() = default;

	void draw() const
	{
		setlinecolor(RGB(255, 155, 50));
		setfillcolor(RGB(200, 70, 10));
		fillcircle(pos.x, pos.y, N);
	}
private:
	const int N = 10;
};

int main()
{
	initgraph(1400, 600);

	player pp;
	bullet dd;

	IMAGE background;
	
	loadimage(&background, _T("background.jpg"));

	bool IsRunning = true;

	ExMessage msg;
	pp.loadAnimation_LR();
	BeginBatchDraw();
	while (IsRunning)
	{
		DWORD start_time = GetTickCount();
		
		while (peekmessage(&msg))pp.move(msg);
		
		pp.Speed_change();
		dd.pos = { pp.pos_x,pp.pos_y };
	
		static int counter = 0;
		if ( ++ counter % 4 == 0) {
			pp.current_idx++;
		}
		//使动画循环播放
		pp.current_idx %= player_time;

		cleardevice();
		putimage(0, 0, &background);
		pp.Draw();
		dd.draw();

		FlushBatchDraw();

		DWORD end_time = GetTickCount();

		DWORD delta_time = end_time - start_time;
		if (delta_time < 1000 / 60)
		{
			Sleep(1000 / 60 - delta_time);
		}
	}
	 
	EndBatchDraw();

	return 0;
}
