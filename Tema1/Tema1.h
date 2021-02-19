/*
	Micut Andrei-Ion
	Grupa 331CB
*/

#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>

class Tema1 : public SimpleScene
{
	public:
		Tema1();
		~Tema1();

		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;
		int CollisionRedBallon(float translateX_arrow, float translateY_arrow, float translateX_red_ballon, float translateY_red_ballon, int score);
		int CollisionYellowBallon(float translateX_arrow, float translateY_arrow, float translateX_yellow_ballon, float translateY_yellow_ballon, int score);
		int CollisionYellowBallon1(float translateX_arrow, float translateY_arrow, float translateX_yellow_ballon, float translateY_yellow_ballon, int score);
		void GameEnd();

	protected:
		glm::mat3 modelMatrix;
		float translateX_shuriken, translateY_shuriken;
		float translateX_fireball, translateY_fireball;
		float translateX_red_ballon, translateY_red_ballon;
		float translateX_red_ballon1, translateY_red_ballon1;
		float translateX_yellow_ballon, translateY_yellow_ballon;
		float translateX_yellow_ballon1, translateY_yellow_ballon1;
		float translateX_arrow, translateY_arrow;
		float translateX_arrow_cos, translateY_arrow_sin;
		float translateX_bow, translateY_bow;
		float translateX_point, translateY_point;
		float translateX_powerbar, translateY_powerbar;
		float scaleX_red, scaleY_red;
		float scaleX_red1, scaleY_red1;
		float scaleX_yellow, scaleY_yellow;
		float scaleX_yellow1, scaleY_yellow1;
		float scaleX_heart, scaleY_heart;
		float scaleX_powerbar, scaleY_powerbar;
		float angularStep;


		float squareSide = 50;
		float arrow_side = 125;
		float shuriken_side = 35;
		float radius_bow = 100;
		float radius_ballon = 40;
		float radius_point = 5;
		float polyline_side = 50;
		float heart_side = 30;
		float dx1, dy1, distance1;
		float dx2, dy2, distance2;
		int dx3, dy3;
		float distance3;
		float dx4, dy4, distance4;


		float cx_square, cy_square;
		float cx_bow, cy_bow;
		float cx_ballon, cy_ballon;
		float cx_shuriken, cy_shuriken;
		float cx_arrow, cy_arrow;
		float cx_polyline, cy_polyline;
		float cx_heart, cy_heart;
		int ok;


		bool start_Game = false;
		bool gameEnd = false;
		int show = 0;
		bool click_Left = false;
		bool shoot = false;
		bool shoot_ballon_red = false;
		bool shoot_ballon_red1 = false;
		int red = 0;
		int shoot_player;
		bool shoot_ballon_yellow = false;
		bool shoot_ballon_yellow1 = false;
		int speed_arrow = 175;
		int speed_arrow1 = 175;
		int speed_shuriken = 200;
		int limit = 150;
		int speed = 4;
		int score = 0;
		double theta;
		double theta1;
		bool angle_arrow = false;
		bool respawn_arrow = true;
};
