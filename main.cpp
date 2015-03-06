//
// アプリ雛形
//

#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "lib/random.hpp"

enum Window {
	WIDTH = 512,
	HEIGHT = 512
};


struct Gun
{
	bool active;
	float x;
	float y;
	float r;
	float speed_x;
	float speed_y;
}gun;

struct Point
{
	bool snipe;
	float x;
	float y;
	float r;
}point;

struct Triangle
{
	float x;
	float y;
	float r;
	float angle;
}triangle;

void Init()
{
	gun.active = false;
	gun.x = 0;
	gun.y = 0;
	gun.r = 10;
	gun.speed_x = 4;
	gun.speed_y = 4;
	triangle.x = 0;
	triangle.y = 0;
	triangle.r = 50;
	triangle.angle = 0;
	point.snipe = false;
	point.x = 100;
	point.y = 0;
	point.r = 5;

}

void Gun_Create(AppEnv& env)
{
	if (env.isPushButton(Mouse::LEFT))
	{
		if (!gun.active)
		{
			gun.active = true;
		}
	}
}

void Gun_Move(AppEnv& env)
{
	//右真横

		if (gun.active)
		{
			gun.x += gun.speed_x;
		}
	}



void Aim(AppEnv& env)
{
	if (!point.snipe)
	{
		if (env.isPushKey('K'))
		{
			point.x = 100;
			point.y = 0;
		}
		if (env.isPushKey('I'))
		{
			point.x = 100;
			point.y = 100;
		}
		if (env.isPushKey('M'))
		{
			point.x = 100;
			point.y = -100;
		}
		if (env.isPushKey('H'))
		{
			point.x = -100;
			point.y = 0;
		}
		if (env.isPushKey('U'))
		{
			point.x = -100;
			point.y = 100;
		}
		if (env.isPushKey('N'))
		{
			point.x = -100;
			point.y = -100;
		}
		if (env.isPushKey('O'))
		{
			point.x = 0;
			point.y = 100;
		}
		if (env.isPushKey('L'))
		{
			point.x = 0;
			point.y = -100;
		}
	}
}

void Bound(int sign)
{
	if ((gun.x >= WIDTH / 2) || (gun.x <= -WIDTH / 2))
	{
		gun.speed_x *= sign;
	}
	if ((gun.y >= HEIGHT / 2) || (gun.y <= -HEIGHT / 2))
	{
		gun.speed_y *= sign;
	}
}


void Triangle_Move(AppEnv& env)
{
	if (env.isPressKey(GLFW_KEY_LEFT))
	{
		triangle.x -= 4;
	}
	if (env.isPressKey(GLFW_KEY_RIGHT))
	{
		triangle.x += 4;
	}
	if (env.isPressKey(GLFW_KEY_UP))
	{
		triangle.y += 4;
	}
	if (env.isPressKey(GLFW_KEY_DOWN))
	{
		triangle.y -= 4;
	}
	if (env.isPressKey('A'))
	{
		triangle.angle += 0.05f;
	}
	if (env.isPressKey('D'))
	{
		triangle.angle -= 0.05f;
	}
}

void Draw()
{
	if (gun.active){
		drawFillCircle(gun.x, gun.y, gun.r, gun.r, 100, Color(1, 1, 1));
	}
	if (!point.snipe)
	{
		drawPoint(point.x, point.y, point.r, Color(1, 0, 0));
	}

}
// 
// メインプログラム
// 
int main() {
	AppEnv env(Window::WIDTH, Window::HEIGHT, false, false);

	Init();
	const int sign = -1;
	while (env.isOpen()) {
		//Triangle_Move(env);
		if (env.isPushKey(GLFW_KEY_ESCAPE)) return 0;
		//生成処理
		Gun_Create(env);
		
		//移動処理
		Gun_Move(env);

		//跳ね返り処理
		Bound(sign);

		//照準処理
		Aim(env);

		env.setupDraw();
	
		Draw();


		//drawFillCircle(triangle.x, triangle.y, triangle.r  , triangle.r, 3, Color(1, 1, 1), triangle.angle, Vec2f(1, 1), Vec2f(0, 0));
		env.update();
	}
}
