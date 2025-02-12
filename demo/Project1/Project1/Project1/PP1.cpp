#include<iostream>
#include<string>
#include<vector>
#include<graphics.h>
using namespace std;

#pragma comment(lib, "MSIMG32.LIB")
#pragma comment(lib, "Winmm.lib")

inline void putimage_a(int x, int y, IMAGE* img) {
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(NULL), x, y, w, h, 
		GetImageHDC(img), 0, 0, w, h,{AC_SRC_OVER,0,255,AC_SRC_ALPHA});
}

class Animation
{
public:
	Animation(LPCTSTR path, int num, int interval)
	{
		ms = interval;

		TCHAR path_file[256];
		for (size_t i = 0; i < num; i++)
		{
			_stprintf_s(path_file, path, i);

			IMAGE* img = new IMAGE();
			loadimage(img, path_file);
			c_list.push_back(img);
		}

	}
	~Animation()
	{
		for (size_t i = 0; i < c_list.size(); i++)delete c_list[i];
	}

	void play(int x, int y, int delta)
	{
		timer += delta;
		if (timer >= ms)
		{
			idx = (idx + 1) % c_list.size();
			timer = 0;
		}
		putimage_a(x, y, c_list[idx]);
	}
private:

	int idx = 0;
	int ms = 0;
	int timer = 0;

	vector<IMAGE*>c_list;
};

class player {
public:	

	POINT pos = { 300,300 };

	player()
	{
		player_l = new Animation(_T("player/player_l%d.png"), 4, 45);
		player_r = new Animation(_T("player/player_r%d.png"), 4, 45);
		player_dn = new Animation(_T("player/player_d%d.png"), 4, 45);
		player_up = new Animation(_T("player/player_up%d.png"), 4, 45);
	}
	~player()
	{
		delete player_l;
		delete player_r;
		delete player_dn;
		delete player_up;
	}

	//½ÇÉ«ÒÆ¶¯
	void process_move(const ExMessage &msg) {
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

	void move() {
		int x = move_right - move_left;
		int y = move_down - move_up;
		double len_xy = sqrt(x * x + y * y);
		if (len_xy > 0)
		{
			double real_x = x / len_xy;
			double real_y = y / len_xy;
			pos.x += (int)(speed * real_x);
			pos.y += (int)(speed * real_y);
		}

		if (pos.x < 0)pos.x = 0;
		if (pos.x > 1400 - width)pos.x = 1400 - width;
		if (pos.y < 0)pos.y = 0;
		if(pos.y > 600 - height)pos.y = 600 - height;
	}

	void draw(int delta)
	{
		if (move_up)player_up->play(pos.x, pos.y, delta);
		else if (move_down)player_dn->play(pos.x, pos.y, delta);
		else if (move_left)player_l->play(pos.x, pos.y, delta);
		else if (move_right)player_r->play(pos.x, pos.y, delta);
		else if (!move_up && p1 == 1)player_up->play(pos.x, pos.y, delta);
		else if (!move_down && p2 == 1)player_dn->play(pos.x, pos.y, delta);
		else if (!move_left && p3 == 1)player_l->play(pos.x, pos.y, delta);
		else if (!move_right && p4 == 1)player_r->play(pos.x, pos.y, delta);
	}

	const POINT& get_pos() const
	{
		return pos;
	}

private:
	Animation* player_r;
	Animation* player_l;
	Animation* player_dn;
	Animation* player_up;

	bool move_up = false;
	bool move_down = false;
	bool move_left = false;
	bool move_right = false;
	int p1 = 0, p2 = 0, p3 = 0, p4 = 1;
	
public:
	int speed = 7;
	int width = 30;
	int height = 30;
    int damage = 40;
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

class Enemy {
public:
	Enemy()
	{
		enemy_l = new Animation(_T("enemy/e1_l%d.png"), 4, 45);
		enemy_r = new Animation(_T("enemy/e1_r%d.png"), 4, 45);
		enemy_dn = new Animation(_T("enemy/e1_d%d.png"), 4, 45);
		enemy_up = new Animation(_T("enemy/e1_up%d.png"), 4, 45);

		enum class edge
		{
			left = 0,
			right = 1,
			up = 2,
			down = 3
		};

		edge e = (edge)(rand() % 4);
		switch (e)
		{
		case edge::left:
			pos.x = -width;
			pos.y = rand() % height;
			break;
		case edge::right:
			pos.x = width;
			pos.y = rand() % height;
			break;
		case edge::up:
			pos.x = rand() % width;
			pos.y = -height;
			break;
		case edge::down:
			pos.x = rand() % width;
			pos.y = height;
			break;
		default:
			break;
		}
	}
	~Enemy()
	{
		delete enemy_l;
		delete enemy_r;
		delete enemy_dn;
		delete enemy_up;
	}

	bool checkbullet(const bullet& b)
	{
		if (b.pos.x >= pos.x && b.pos.x <= pos.x + width &&b.pos.y >= pos.y && b.pos.y <= pos.y + height)
		{
			return true;
		}
		return false;
	}

	bool checkplayer(const player& p)
	{
		if (p.pos.x >= pos.x && p.pos.x <= pos.x + width &&
			p.pos.y >= pos.y && p.pos.y <= pos.y + height)
		{
			return true;
		}
		return false;
	}

	void move(const player& p)
	{
		int x = p.pos.x - pos.x;
		int y = p.pos.y - pos.y;
		double len_xy = sqrt(x * x + y * y);
		if (len_xy > 0)
		{
			double real_x = x / len_xy;
			double real_y = y / len_xy;
			pos.x += (int)(speed * real_x);
			pos.y += (int)(speed * real_y);	
		}

		if (x < 0) {
			move_left = true;
			move_right = false;
			move_up = false;
			move_down = false;
			p1 = 0, p2 = 0, p3 = 1, p4 = 0;
		}
		else if (x > 0) {
			move_right = true;
			move_left = false;
			move_up = false;
			move_down = false;
			p1 = 0, p2 = 0, p3 = 0, p4 = 1;
		}
		else if (y < 0) {
			move_up = true;
			move_down = false;
			move_left = false;
			move_right = false;
			p1 = 1, p2 = 0, p3 = 0, p4 = 0;
		}
		else if (y > 0) {
			move_down = true;
			move_up = false;
			move_left = false;
			move_right = false;
			p1 = 0, p2 = 1, p3 = 0, p4 = 0;
		}
	}

	void get_speed()
	{
		speed = rand() % 10;
		if (speed <= 2)speed += 4;
	}

	void draw(int delta)
	{
		if (move_up)enemy_up->play(pos.x, pos.y, delta);
		else if (move_down)enemy_dn->play(pos.x, pos.y, delta);
		else if (move_left)enemy_l->play(pos.x, pos.y, delta);
		else if (move_right)enemy_r->play(pos.x, pos.y, delta);
		else if (!move_up && p1 == 1)enemy_up->play(pos.x, pos.y, delta);
		else if (!move_down && p2 == 1)enemy_dn->play(pos.x, pos.y, delta);
		else if (!move_left && p3 == 1)enemy_l->play(pos.x, pos.y, delta);
		else if (!move_right && p4 == 1)enemy_r->play(pos.x, pos.y, delta);
	}

	void hurt(int damage)
	{
		hp -= damage;
		if (hp <= 0)alive = false;
	}

	bool is_alive() const
	{
		return alive;
	}

private:
	Animation* enemy_r;
	Animation* enemy_l;
	Animation* enemy_up;
	Animation* enemy_dn;

	POINT pos = { 0,0 };
	int speed = 4;
	int width = 50;
	int height = 50;
	int hp = 100;

	bool alive = true;
	bool move_up = false;
	bool move_down = false;
	bool move_left = false;
	bool move_right = false;
	int p1 = 0, p2 = 0, p3 = 0, p4 = 1;
};


void trygenerate_enemy(vector<Enemy*>& e_list)
{
	const int interval = 100;
	static int timer = 0;
	if ((++timer) % interval == 0)
	{
		Enemy* e = new Enemy();
		e->get_speed();
		e_list.push_back(e);
	}
}

void updatebullet(vector<bullet>& bb, const player& pp)
{
	const double R_speed = 0.005;
	const double T_speed = 0.005;

	double R_interval = 2 * 3.14159 / bb.size();

	POINT p = pp.get_pos();

	double rad = 70 + 25 * sin(GetTickCount() * R_speed);

	for (size_t i = 0; i < bb.size(); i++)
	{
		double time = i * R_interval + GetTickCount() * T_speed;
		bb[i].pos.x = p.x + (int)(rad * sin(time)) + pp.width;
		bb[i].pos.y = p.y + (int)(rad * cos(time)) + pp.height;
	}
	
}

void draw_score(int score)
{
	TCHAR score_text[256];
	_stprintf_s(score_text, _T("Score: %d"), score);

	setbkmode(TRANSPARENT);
	settextcolor(RGB(255, 85, 255));
	outtextxy(0, 0, score_text);
}

int main()
{
	initgraph(1400, 600);

	mciSendString(_T("open player/bgmus.mp3 alias bgm"), NULL, 0, NULL);
	mciSendString(_T("open player/get_hit.mp3 alias hit"), NULL, 0, NULL);
	mciSendString(_T("play bgm repeat from 0"), NULL, 0, NULL);
	player pp;
	vector<Enemy*>e_list;
	vector<bullet>bb(3);
	IMAGE background;
	
	
	loadimage(&background, _T("background.jpg"));

	bool IsRunning = true;

	int s = 0;
	ExMessage msg;

	BeginBatchDraw();
	while (IsRunning)
	{
		DWORD start_time = GetTickCount();

		while (peekmessage(&msg))pp.process_move(msg);

		pp.move();
		trygenerate_enemy(e_list);
		for (Enemy* enemy : e_list)
		{
			enemy->move(pp);
		}

		for (Enemy* enemy : e_list)
		{
			if (enemy->checkplayer(pp))
			{
				MessageBox(GetHWnd(), _T("Game Over"), _T("Game Over"), MB_OK);
				IsRunning = false;
				break;
			}
		}

		cleardevice();

		putimage(0, 0, &background);
		pp.draw(1000 / 144);
		for (Enemy* enemy : e_list)
		{
			enemy->draw(1000 / 144);
		}
		for (bullet& b : bb)b.draw();
		updatebullet(bb, pp);

		for (Enemy* enemy : e_list)
		{
			for (bullet& b : bb)
			{
				if (enemy->checkbullet(b))
				{
					mciSendString(_T("play hit from 0"), NULL, 0, NULL);
					enemy->hurt(pp.damage);
				}
			}
		}

		for (size_t i = 0; i < e_list.size(); i++)
		{
			Enemy* e = e_list[i];
			if (!e->is_alive())
			{
				swap(e_list[i], e_list.back());
				e_list.pop_back();
				delete e;
				s++;
			}
		}

		draw_score(s);

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