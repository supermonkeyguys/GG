#include<iostream>
#include<vector>
#include<graphics.h>
using namespace std;
const int player_time = 4;

class player {
public:
	int Hp = 10;
	int Speed = 10;
	int attack_value = 5;
	int Lv = 1;
	int pos_x = 300;
	int pos_y = 300;
	
	IMAGE player_left[player_time];
	IMAGE player_right[player_time];

	int current_idx = 0;


	void loadAnimation_LR(LPCTSTR path,int n,int interval) {
		interval_ms = interval;
		
		TCHAR path_file[256];
		for (size_t i = 0; i < n; i++) {
			_stprintf_s(path_file, path, i);

			IMAGE* p = new IMAGE();
			loadimage(p, path_file);
			player.push_back(p);
		}
	}

	void Animation() {
		for (size_t i = 0; i < player.size(); i++) {
			delete player[i];
		}
	}

	void play(int x, int y, int delta) {
		timer += delta;
		if (timer >= interval_ms) {
			idx_player = (idx_player + 1) % player.size();
			timer = 0;
		}

		putimage(x, y, player[idx_player]);
	}

	void Draw_player(int delta, int dir_x) {
		static bool face_left = false;
		if (dir_x < 0)face_left = true;
		else if (dir_x > 0)face_left = false;
	}

private:
	int timer = 0;
	int idx_player = 0;
	int interval_ms = 0;
	vector<IMAGE*>player;
};

class Monster {
public:
	int Hp;
	int Speed; 
};




int main()
{
	initgraph(1400, 600);

	player pp;

	IMAGE background;
	
	loadimage(&background, _T("background.jpg"));

	bool IsRunning = true;

	ExMessage msg;

	BeginBatchDraw();
	while (IsRunning) {
			DWORD start_time = GetTickCount();

			while (peekmessage(&msg)) {
				if (msg.message == WM_KEYDOWN)
					switch (msg.vkcode)
					{ 
					case VK_UP :
					pp.pos_y -= pp.Speed;
					break;
					case VK_DOWN :
					pp.pos_y += pp.Speed;
					break;
					case VK_LEFT :
					pp.pos_x -= pp.Speed;
					break;
					case VK_RIGHT :
					pp.pos_x += pp.Speed;
					break;
					}
			}
			static int counter = 0;

			if (counter % 4 == 0) {
				pp.current_idx++;
			}
			//使动画循环播放
			pp.current_idx %= player_time;

			cleardevice();
			putimage(0, 0, &background);
			putimage(20, 20, &pp.player_left[pp.current_idx]);
			FlushBatchDraw();

			DWORD end_time = GetTickCount();

			DWORD delta_time = end_time - start_time;
			if (delta_time < 1000 / 120)
			{
				Sleep(1000 / 120 - delta_time);
			}

	 }
	EndBatchDraw();

	return 0;
}