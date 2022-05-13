#pragma once
#include <chrono>
#include <thread>
#include "MConsolUtil.hpp"
#include "Player.hpp"
#include "Monster.hpp"

using namespace std;

namespace MuSeoun_Engine
{
	class MGameLoop
	{
	private:
		bool _isGameRunning;
		MConsoleRenderer cRenderer;
		MConsoleRenderer MRenderer;
		chrono::system_clock::time_point startRenderTimePoint;
		chrono::duration<double> renderDuration;
		Player p;
		Monster m;

	public:
		MGameLoop() { _isGameRunning = false; }
		~MGameLoop() {}

		void Run()
		{
			_isGameRunning = true;
			Initialize();

			startRenderTimePoint = chrono::system_clock::now();
			while (_isGameRunning)
			{

				Input();
				Update();
				Render();

			}
			Release();
		}

		void Stop()
		{
			_isGameRunning = false;
		}

	private:
		void Initialize()
		{
			
		}
		void Release()
		{
		}

		void Input()
		{
			if (GetAsyncKeyState(VK_SPACE) & 0x8000 || GetAsyncKeyState(VK_SPACE) & 0x8001)
			{
				p.isKeyPressed();
			}
			else
			{
				p.isKeyUnpressed();
			}

		}
		void Update()
		{
			//m.x랑 p.x의 좌표가 같지 않거나 m.y랑 p.y 같지 않을 때 이동
			if (m.x != p.x || m.y != p.y) {
				m.x--;
			}

			if (m.x <= 0) {
				m.x = 100;
			}
		}
		void Render()
		{
			cRenderer.Clear();

			cRenderer.MoveCursor(p.x, p.y);
			cRenderer.DrawString("P");

			cRenderer.MoveCursor(m.x, m.y);
			cRenderer.DrawString("M");

			if (p.x == m.x && p.y == m.y) {
				cRenderer.MoveCursor(20, 15);
				cRenderer.DrawString("GameOver");
			}
			cRenderer.MoveCursor(10, 20);

			renderDuration = chrono::system_clock::now() - startRenderTimePoint;
			startRenderTimePoint = chrono::system_clock::now();
			string fps = "FPS : " + to_string(1.0 / renderDuration.count());
			cRenderer.DrawString(fps);

			this_thread::sleep_for(chrono::milliseconds(20));
		}
	};
}