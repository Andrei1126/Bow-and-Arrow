/*
	Micut Andrei-Ion
	Grupa 331CB
*/

#include "Tema1.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"

using namespace std;

Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}

// initializez obiectele si toate coordonatele pentru centru cercului, translatie, scalare
// de care voi avea nevoie

void Tema1::Init()
{

	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	glm::vec3 corner = glm::vec3(0, 0, 0);

	// compute coordinates of square center
	cx_square = corner.x + squareSide / 2;
	cy_square = corner.y + squareSide / 2;

	cx_arrow = corner.x + arrow_side / 2;
	cy_arrow = corner.y + arrow_side / 2;

	cx_bow = corner.x;
	cy_bow = corner.y ;

	cx_ballon = corner.x + radius_ballon / 2;
	cy_ballon = corner.y + radius_ballon / 2;

	cx_polyline = corner.x + polyline_side / 2;
	cy_polyline = corner.y + polyline_side / 2;

	cx_shuriken = corner.x;
	cy_shuriken = corner.y;

	cx_heart = corner.x + heart_side / 2;
	cy_heart = corner.y + heart_side / 2;

	// initialize tx and ty (the translation steps)

	translateX_bow = 65;
	translateY_bow = resolution.y - 470;

	translateX_powerbar = resolution.x - 1220;
	translateY_powerbar = resolution.y - 640;

	translateX_shuriken = 0;
	translateY_shuriken = resolution.y - 470;

	translateX_fireball = resolution.x - 630;
	translateY_fireball = resolution.y - 270;

	translateX_red_ballon = resolution.x - 630;
	translateY_red_ballon = 0;

	translateX_red_ballon1 = resolution.x - 330;
	translateY_red_ballon1 = resolution.y - 360;


	translateX_yellow_ballon = resolution.x - 530;
	translateY_yellow_ballon = 0;


	translateX_yellow_ballon1 = resolution.x - 230;
	translateY_yellow_ballon1 = resolution.y - 180;


	translateX_arrow = resolution.x - 1230;
	translateY_arrow = resolution.y - 470;

	translateX_arrow_cos = resolution.x - 1230;
	translateY_arrow_sin = resolution.y - 470;

	translateX_point = 0;
	translateY_point = 0;


	// initialize sx and sy (the scale factors)
	scaleX_red = 1;
	scaleY_red = 1.5;

	scaleX_red1 = 1;
	scaleY_red1 = 1.5;

	scaleX_yellow = 1;
	scaleY_yellow = 1.5;

	scaleX_yellow1 = 1;
	scaleY_yellow1 = 1.5;

	scaleX_powerbar = 1;
	scaleY_powerbar = 1.5;

	// initialize angularStep
	angularStep = 0;


	Mesh* arrow = Object2D::CreateArrow("arrow", corner, arrow_side, glm::vec3(0, 0, 0), false);
	AddMeshToList(arrow);

	Mesh* shuriken = Object2D::CreateShuriken("shuriken", corner, shuriken_side, glm::vec3(0, 0, 0), false);
	AddMeshToList(shuriken);

	Mesh* bow = Object2D::CreateBow("bow", glm::vec3(0, 0, 0), radius_bow, glm::vec3(0, 0, 0));
	AddMeshToList(bow);

	Mesh* red_ballon = Object2D::CreateBallon("red_ballon", glm::vec3(0, 0, 0), radius_ballon, glm::vec3(1, 0, 0));
	AddMeshToList(red_ballon);

	Mesh* yellow_ballon = Object2D::CreateBallon("yellow_ballon", glm::vec3(0, 0, 0), radius_ballon, glm::vec3(1, 1, 0));
	AddMeshToList(yellow_ballon);

	Mesh* polyline = Object2D::CreatePolyLine("polyline", glm::vec3(0, 0, 0), polyline_side, glm::vec3(0, 0, 0), false);
	AddMeshToList(polyline);

	Mesh* point = Object2D::CreatePoint("point", glm::vec3(1, 1, 0), radius_point, glm::vec3(0, 0, 0));
	AddMeshToList(point);

	Mesh* heart = Object2D::CreateHeart("heart", glm::vec3(0, 0, 0), heart_side, glm::vec3(1, 0, 0), true);
	AddMeshToList(heart);

	Mesh* powerbar = Object2D::CreateSquare("powerbar", glm::vec3(0, 0, 0), squareSide, glm::vec3(1.0, 0.5, 0.0), true);
	AddMeshToList(powerbar);

	Mesh* fireball1 = Object2D::CreateBallon("fireball1", glm::vec3(0, 0, 0), radius_ballon, glm::vec3(1, 0, 0));
	AddMeshToList(fireball1);

	Mesh* triangle = Object2D::CreateTriangle("triangle", glm::vec3(0, 0, 0), radius_ballon /1.5 , glm::vec3(1, 0, 0), false);
	AddMeshToList(triangle);

}

void Tema1::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0.5, 1, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->GetResolution();


	// cu cat tin apasat mai mult mouse-ul, cu atat factorul de scalare pe OX
	// pentru powerbar va creste, la fel si viteza sagetii
	if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)) {
		scaleX_powerbar += speed * deltaTimeSeconds;
		speed_arrow += scaleX_powerbar;
	}

	// daca jocul inca nu a inceput, afisez un mesaj friendly si imi pregatesc player-ul si sageata
	if (start_Game == false) {

		if (show == 0) {
			cout << "\n>>>>>>> LET'S PLAY BOW AND ARROW <<<<<<< \n";
			cout << "     >>>> PRESS P TO START <<<< \n";
			show = 1;
		}

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(resolution.x - 1230, resolution.y - 470);
		RenderMesh2D(meshes["arrow"], shaders["VertexColor"], modelMatrix);


		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(resolution.x - 1210, resolution.y - 470);
		modelMatrix *= Transform2D::Rotate(14.15);
		RenderMesh2D(meshes["bow"], shaders["VertexColor"], modelMatrix);

		return;
	}

	// daca mouse-ul este apasat si i-am dat drumul, atunci mi se va deplasa sageata
	// altfel va ramane unde este si arcul si mi se va deplasa cu unghiul calculat mai devreme dupa mouse
	if (click_Left == true && shoot == true) {
		modelMatrix = glm::mat3(1);

		translateX_arrow_cos += deltaTimeSeconds * speed_arrow * cos(theta1);
		translateY_arrow_sin += deltaTimeSeconds * speed_arrow * sin(theta1);


		translateX_arrow += deltaTimeSeconds * speed_arrow;

		modelMatrix *= Transform2D::Rotate(95.29 - theta1);
		modelMatrix *= Transform2D::Translate(translateX_arrow_cos, translateY_arrow);
		
		RenderMesh2D(meshes["arrow"], shaders["VertexColor"], modelMatrix);


		if (translateX_arrow_cos > 1280 || translateY_arrow > 720 || translateY_arrow < 0) {

			shoot = false;
			translateX_arrow = translateX_bow;
			translateY_arrow = translateY_bow;

			translateX_arrow_cos = translateX_bow;
			translateY_arrow_sin = translateY_bow;
			speed_arrow = speed_arrow1;
		}
	}
	else{

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(translateX_arrow, translateY_arrow);

		modelMatrix *= Transform2D::Translate(cy_bow, cx_bow);
		modelMatrix *= Transform2D::Rotate(95.29 - theta);
		modelMatrix *= Transform2D::Translate(-( cy_bow), -cx_bow);


		RenderMesh2D(meshes["arrow"], shaders["VertexColor"], modelMatrix);

	}

	if (translateX_arrow == translateX_bow && translateY_arrow == translateY_bow && shoot == false) {
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(translateX_bow, translateY_bow);

		modelMatrix *= Transform2D::Translate(cy_bow, cx_bow);
		modelMatrix *= Transform2D::Rotate(95.29 - theta);
		modelMatrix *= Transform2D::Translate(-(cy_bow), -cx_bow);


		RenderMesh2D(meshes["arrow"], shaders["VertexColor"], modelMatrix);
	}


	// arcul se va deplasa dupa cursorul mouse-ului in functie de unghiul 
	// dintre mouse si arc
	modelMatrix = glm::mat3(1);

	modelMatrix *= Transform2D::Translate(translateX_bow, translateY_bow);
	modelMatrix *= Transform2D::Translate(cx_bow, cy_bow);
	modelMatrix *= Transform2D::Rotate(84.3 - theta);
	modelMatrix *= Transform2D::Translate(-cx_bow, -cy_bow);

	RenderMesh2D(meshes["bow"], shaders["VertexColor"], modelMatrix);



	// powerbar-ul mi se va duce pana la o valoare setata de programator,
	// iar daca acea valoare este depasita revine la scalarea initiala pe OX
	modelMatrix = glm::mat3(1);

	modelMatrix *= Transform2D::Translate(translateX_powerbar, translateY_powerbar);

	if (ok == 0)
		modelMatrix *= Transform2D::Scale(scaleX_powerbar, 1);
	else
	{
		ok = 0;
		scaleX_powerbar = 1;
	}

	modelMatrix *= Transform2D::Scale(0.25, 0.5);

	RenderMesh2D(meshes["powerbar"], shaders["VertexColor"], modelMatrix);

	// shuriken-ul va face, mai intai, o rotatie in jurul propriului centru(asemanator ca in laborator),
	// iar apoi se va translata pe OX cu o viteza prestabilita
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(translateX_shuriken, translateY_shuriken);

	if (translateX_shuriken <= 0) {
		translateX_shuriken = resolution.x;
	}
	translateX_shuriken -= deltaTimeSeconds * speed_shuriken;

	angularStep += deltaTimeSeconds * 0.5;
	modelMatrix *= Transform2D::Translate(cx_shuriken + shuriken_side, cy_shuriken );
	modelMatrix *= Transform2D::Rotate(6 * angularStep);
	modelMatrix *= Transform2D::Translate(-cx_shuriken - shuriken_side, -cy_shuriken);


	RenderMesh2D(meshes["shuriken"], shaders["VertexColor"], modelMatrix);


	// fireball-ul va fi un obiect asemanator cu shuriken-ul ce ii poate scadea vietile player-ului
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(translateX_fireball, translateY_fireball);

	if (translateX_fireball <= 0) {
		translateX_fireball = resolution.x;
	}

	translateX_fireball -= deltaTimeSeconds * speed_shuriken;
	RenderMesh2D(meshes["fireball1"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(translateX_fireball + 35, translateY_fireball);
	RenderMesh2D(meshes["triangle"], shaders["VertexColor"], modelMatrix);



	// in cazul in care balonul este atins de varful sagetii, atunci balonul(impreuna cu polilinia)
	// vor disparea priintr-o translatie pana la 0 in functie de deltaTimeSeconds
	// in cazul in care varful sagetii nu atinge balonul, atunci, acesta, isi continua translatia pe OY
	if (shoot_ballon_red) {

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(resolution.x - 630, resolution.y - 470);


		if (scaleX_red >= 0 && scaleY_red >= 0)
		{
			scaleX_red -= deltaTimeSeconds * 2.25;
			scaleY_red -= deltaTimeSeconds * 2.25;

			modelMatrix = glm::mat3(1);

			modelMatrix *= Transform2D::Translate(translateX_red_ballon, translateY_red_ballon);

			modelMatrix *= Transform2D::Translate(-cx_ballon, -cy_ballon);
			modelMatrix *= Transform2D::Scale(scaleX_red, scaleY_red);
			modelMatrix *= Transform2D::Translate(-cx_ballon, -cy_ballon);

			RenderMesh2D(meshes["red_ballon"], shaders["VertexColor"], modelMatrix);



			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(resolution.x - 615, resolution.y - 512);

			modelMatrix *= Transform2D::Translate(translateX_red_ballon, translateY_red_ballon);

			modelMatrix *= Transform2D::Translate(-cx_polyline, -cy_polyline);
			modelMatrix *= Transform2D::Scale(scaleX_red, scaleY_red);
			modelMatrix *= Transform2D::Translate(-cx_polyline, -cy_polyline);


			RenderMesh2D(meshes["polyline"], shaders["VertexColor"], modelMatrix);
		}


		if (scaleX_red == 0) {
			shoot_ballon_red = false;
			scaleX_red = 1;
			scaleY_red = 1.5;
		}
		

	}
	else {

		modelMatrix = glm::mat3(1);

		if (translateY_red_ballon > resolution.y)
			translateY_red_ballon = 0;


		int speed_red_ballon = 150;

		translateY_red_ballon += deltaTimeSeconds * speed_red_ballon;

		modelMatrix *= Transform2D::Translate(translateX_red_ballon, translateY_red_ballon);

		modelMatrix *= Transform2D::Translate(-cx_ballon, -cy_ballon);
		modelMatrix *= Transform2D::Scale(scaleX_red, scaleY_red);
		modelMatrix *= Transform2D::Translate(-cx_ballon, -cy_ballon);

		RenderMesh2D(meshes["red_ballon"], shaders["VertexColor"], modelMatrix);



		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(20, resolution.y - 762);

		modelMatrix *= Transform2D::Translate(translateX_red_ballon, translateY_red_ballon);

		modelMatrix *= Transform2D::Translate(-cx_polyline, -cy_polyline);
		modelMatrix *= Transform2D::Scale(scaleX_red, scaleY_red);
		modelMatrix *= Transform2D::Translate(-cx_polyline, -cy_polyline);


		RenderMesh2D(meshes["polyline"], shaders["VertexColor"], modelMatrix);
	}



	// mai adaug un balon rosu
	// in cazul in care balonul este atins de varful sagetii, atunci balonul(impreuna cu polilinia)
	// vor disparea priintr-o translatie pana la 0 in functie de deltaTimeSeconds
	// in cazul in care varful sagetii nu atinge balonul, atunci, acesta, isi continua translatia pe OY

	if (shoot_ballon_red1) {

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(resolution.x - 630, resolution.y - 470);


		if (scaleX_red1 >= 0 && scaleY_red1 >= 0)
		{
			scaleX_red1 -= deltaTimeSeconds * 2.25;
			scaleY_red1 -= deltaTimeSeconds * 2.25;

			modelMatrix = glm::mat3(1);


			modelMatrix *= Transform2D::Translate(translateX_red_ballon1, translateY_red_ballon1);

			modelMatrix *= Transform2D::Translate(-cx_ballon, -cy_ballon);
			modelMatrix *= Transform2D::Scale(scaleX_red1, scaleY_red1);
			modelMatrix *= Transform2D::Translate(-cx_ballon, -cy_ballon);

			RenderMesh2D(meshes["red_ballon"], shaders["VertexColor"], modelMatrix);



			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(resolution.x - 515, resolution.y - 512);

			modelMatrix *= Transform2D::Translate(translateX_red_ballon1, translateY_red_ballon1);

			modelMatrix *= Transform2D::Translate(-cx_polyline, -cy_polyline);
			modelMatrix *= Transform2D::Scale(scaleX_red1, scaleY_red1);
			modelMatrix *= Transform2D::Translate(-cx_polyline, -cy_polyline);


			RenderMesh2D(meshes["polyline"], shaders["VertexColor"], modelMatrix);
		}


		if (scaleX_red1 == 0) {
			shoot_ballon_red1 = false;
			scaleX_red1 = 1;
			scaleY_red1 = 1.5;
		}


	}
	else {

		modelMatrix = glm::mat3(1);

		if (translateY_red_ballon1 > resolution.y)
			translateY_red_ballon1 = 0;


		int speed_red_ballon = 150;
		translateY_red_ballon1 += deltaTimeSeconds * speed_red_ballon;

		modelMatrix *= Transform2D::Translate(translateX_red_ballon1, translateY_red_ballon1);

		modelMatrix *= Transform2D::Translate(-cx_ballon, -cy_ballon);
		modelMatrix *= Transform2D::Scale(scaleX_red1, scaleY_red1);
		modelMatrix *= Transform2D::Translate(-cx_ballon, -cy_ballon);

		RenderMesh2D(meshes["red_ballon"], shaders["VertexColor"], modelMatrix);



		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(20, resolution.y - 762);

		modelMatrix *= Transform2D::Translate(translateX_red_ballon1, translateY_red_ballon1);

		modelMatrix *= Transform2D::Translate(-cx_polyline, -cy_polyline);
		modelMatrix *= Transform2D::Scale(scaleX_red1, scaleY_red1);
		modelMatrix *= Transform2D::Translate(-cx_polyline, -cy_polyline);


		RenderMesh2D(meshes["polyline"], shaders["VertexColor"], modelMatrix);
	}






	// in cazul in care balonul este atins de varful sagetii, atunci balonul(impreuna cu polilinia)
	// vor disparea priintr-o translatie pana la 0 in functie de deltaTimeSeconds
	// in cazul in care varful sagetii nu atinge balonul, atunci, acesta, isi continua translatia pe OY
	if (shoot_ballon_yellow) {

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(resolution.x - 530, resolution.y - 470);

		if (scaleX_yellow >= 0 && scaleY_yellow >= 0)
		{
			scaleX_yellow -= deltaTimeSeconds * 2.25;
			scaleY_yellow -= deltaTimeSeconds * 2.25;

			modelMatrix *= Transform2D::Translate(translateX_yellow_ballon, translateY_yellow_ballon);

			modelMatrix *= Transform2D::Translate(-cx_ballon, -cy_ballon);
			modelMatrix *= Transform2D::Scale(scaleX_yellow, scaleY_yellow);
			modelMatrix *= Transform2D::Translate(-cx_ballon, -cy_ballon);

			RenderMesh2D(meshes["yellow_ballon"], shaders["VertexColor"], modelMatrix);



			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(resolution.x - 515, resolution.y - 512);

			modelMatrix *= Transform2D::Translate(translateX_yellow_ballon, translateY_yellow_ballon);

			modelMatrix *= Transform2D::Translate(-cx_polyline, -cy_polyline);
			modelMatrix *= Transform2D::Scale(scaleX_yellow, scaleY_yellow);
			modelMatrix *= Transform2D::Translate(-cx_polyline, -cy_polyline);

			RenderMesh2D(meshes["polyline"], shaders["VertexColor"], modelMatrix);
		}

		if (scaleX_yellow == 0) {
			shoot_ballon_yellow = false;
			scaleX_yellow = 1;
			scaleY_yellow = 1.5;
		}
	}
	else {

		modelMatrix = glm::mat3(1);

		if (translateY_yellow_ballon > resolution.y)
			translateY_yellow_ballon = 0;

		int speed_yellow_ballon = 100;
		translateY_yellow_ballon += deltaTimeSeconds * speed_yellow_ballon;

		modelMatrix *= Transform2D::Translate(translateX_yellow_ballon, translateY_yellow_ballon);

		modelMatrix *= Transform2D::Translate(-cx_ballon, -cy_ballon);
		modelMatrix *= Transform2D::Scale(scaleX_yellow, scaleY_yellow);
		modelMatrix *= Transform2D::Translate(-cx_ballon, -cy_ballon);

		RenderMesh2D(meshes["yellow_ballon"], shaders["VertexColor"], modelMatrix);



		modelMatrix = glm::mat3(1);

		modelMatrix *= Transform2D::Translate(translateX_yellow_ballon + 10, translateY_yellow_ballon - 45);

		modelMatrix *= Transform2D::Translate(-cx_polyline, -cy_polyline);
		modelMatrix *= Transform2D::Scale(scaleX_yellow, scaleY_yellow);
		modelMatrix *= Transform2D::Translate(-cx_polyline, -cy_polyline);

		RenderMesh2D(meshes["polyline"], shaders["VertexColor"], modelMatrix);

	}


	// mai adaug un balon galben
	// in cazul in care balonul este atins de varful sagetii, atunci balonul(impreuna cu polilinia)
	// vor disparea priintr-o translatie pana la 0 in functie de deltaTimeSeconds
	// in cazul in care varful sagetii nu atinge balonul, atunci, acesta, isi continua translatia pe OY
	if (shoot_ballon_yellow1) {

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(resolution.x - 630, resolution.y - 470);


		if (scaleX_yellow1 >= 0 && scaleY_yellow1 >= 0)
		{
			scaleX_yellow1 -= deltaTimeSeconds * 2.25;
			scaleY_yellow1 -= deltaTimeSeconds * 2.25;

			modelMatrix = glm::mat3(1);

			modelMatrix *= Transform2D::Translate(translateX_yellow_ballon1, translateY_yellow_ballon1);

			modelMatrix *= Transform2D::Translate(-cx_ballon, -cy_ballon);
			modelMatrix *= Transform2D::Scale(scaleX_yellow1, scaleY_yellow1);
			modelMatrix *= Transform2D::Translate(-cx_ballon, -cy_ballon);

			RenderMesh2D(meshes["yellow_ballon"], shaders["VertexColor"], modelMatrix);



			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(resolution.x - 615, resolution.y - 512);

			modelMatrix *= Transform2D::Translate(translateX_yellow_ballon1, translateY_yellow_ballon1);

			modelMatrix *= Transform2D::Translate(-cx_polyline, -cy_polyline);
			modelMatrix *= Transform2D::Scale(scaleX_yellow1, scaleY_yellow1);
			modelMatrix *= Transform2D::Translate(-cx_polyline, -cy_polyline);


			RenderMesh2D(meshes["polyline"], shaders["VertexColor"], modelMatrix);
		}


		if (scaleX_yellow1 == 0) {
			shoot_ballon_yellow1 = false;
			scaleX_yellow1 = 1;
			scaleY_yellow1 = 1.5;
		}


	}
	else {

		modelMatrix = glm::mat3(1);

		if (translateY_yellow_ballon1 > resolution.y)
			translateY_yellow_ballon1 = 0;


		int speed_yellow_ballon = 100;

		translateY_yellow_ballon1 += deltaTimeSeconds * speed_yellow_ballon;

		modelMatrix *= Transform2D::Translate(translateX_yellow_ballon1, translateY_yellow_ballon1);

		modelMatrix *= Transform2D::Translate(-cx_ballon, -cy_ballon);
		modelMatrix *= Transform2D::Scale(scaleX_yellow1, scaleY_yellow1);
		modelMatrix *= Transform2D::Translate(-cx_ballon, -cy_ballon);

		RenderMesh2D(meshes["yellow_ballon"], shaders["VertexColor"], modelMatrix);



		modelMatrix = glm::mat3(1);

		modelMatrix *= Transform2D::Translate(translateX_yellow_ballon1 + 15, translateY_yellow_ballon1 - 43);

		modelMatrix *= Transform2D::Translate(-cx_polyline, -cy_polyline);
		modelMatrix *= Transform2D::Scale(scaleX_yellow1, scaleY_yellow1);
		modelMatrix *= Transform2D::Translate(-cx_polyline, -cy_polyline);


		RenderMesh2D(meshes["polyline"], shaders["VertexColor"], modelMatrix);
	}

	


	// prin acest punct ne vom da seama unde se afla cursorul mouse-ului si vom putea
	// aprecia mai bine unde se afla tintele
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(translateX_point, translateY_point);

	RenderMesh2D(meshes["point"], shaders["VertexColor"], modelMatrix);


	// in cazul in care shuriken-ul imi va atinge player-ul, atunci ii va scadea din viata(scalare ca la baloane)
	// valorile intre care se situeaza shoot_player sunt date, deoarece
	// shuriken-ul atinge arcul un interval de timp 
	// daca nu este atins player-ul de shuriken, atunci inimile nu imi vor disparea
	if (shoot_player > 0 && shoot_player  < 62) {


		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(resolution.x - 120, resolution.y - 20);

		if (scaleX_heart >= 0 && scaleY_heart >= 0){

			scaleX_heart = 0;
			scaleY_heart = 0;

			modelMatrix *= Transform2D::Scale(scaleX_heart, scaleY_heart);

			
		}

		RenderMesh2D(meshes["heart"], shaders["VertexColor"], modelMatrix);

		
	}
	else if(shoot_player == 0){

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(resolution.x - 120, resolution.y - 20);

		RenderMesh2D(meshes["heart"], shaders["VertexColor"], modelMatrix);

	}


	if (shoot_player > 61 && shoot_player < 123) {

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(resolution.x - 80, resolution.y - 20);


		if (scaleX_heart >= 0 && scaleY_heart >= 0) {

			scaleX_heart = 0;
			scaleY_heart = 0;

			modelMatrix *= Transform2D::Scale(scaleX_heart, scaleY_heart);

		}

		RenderMesh2D(meshes["heart"], shaders["VertexColor"], modelMatrix);

	}
	else{

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(resolution.x - 80, resolution.y - 20);

		RenderMesh2D(meshes["heart"], shaders["VertexColor"], modelMatrix);
	}
		
	if (shoot_player > 122)
		gameEnd = true;

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(resolution.x - 40, resolution.y - 20);

	RenderMesh2D(meshes["heart"], shaders["VertexColor"], modelMatrix);
	

	// coliziunea dintre arc si shuriken (cerc la cerc)
	dx1 = translateX_bow - translateX_shuriken;
	dy1 = translateY_bow - translateY_shuriken;
	distance1 = sqrt(dx1 * dx1 + dy1 * dy1);

	if (distance1 < radius_bow + shuriken_side) {
		shoot_player++;
	}


	// coliziunea dintre arc si fireball (cerc la cerc)
	dx2 = translateX_bow - translateX_fireball;
	dy2 = translateY_bow - translateY_fireball;
	distance2 = sqrt(dx2 * dx2 + dy2 * dy2);
	
	if(distance2 < radius_bow + radius_ballon){
		shoot_player++;
	}
	

	if (score < CollisionRedBallon(translateX_arrow_cos, translateY_arrow_sin, translateX_red_ballon, translateY_red_ballon, score)) {
		score = CollisionRedBallon(translateX_arrow_cos, translateY_arrow_sin, translateX_red_ballon, translateY_red_ballon, score);
		shoot_ballon_red = true;
	}

	
	if (score < CollisionRedBallon(translateX_arrow_cos, translateY_arrow_sin, translateX_red_ballon1, translateY_red_ballon1, score)) {
		score = CollisionRedBallon(translateX_arrow_cos, translateY_arrow_sin, translateX_red_ballon1, translateY_red_ballon1, score);
		shoot_ballon_red1 = true;
	}
	
	if (score > CollisionYellowBallon(translateX_arrow_cos, translateY_arrow_sin, translateX_yellow_ballon, translateY_yellow_ballon, score)) {
		score = CollisionYellowBallon(translateX_arrow_cos, translateY_arrow_sin, translateX_yellow_ballon, translateY_yellow_ballon, score);
		shoot_ballon_yellow = true;
	}

	

	
	if (score > CollisionYellowBallon1(translateX_arrow_cos, translateY_arrow_sin, translateX_yellow_ballon1, translateY_yellow_ballon1, score)) {
		score = CollisionYellowBallon1(translateX_arrow_cos, translateY_arrow_sin, translateX_yellow_ballon1, translateY_yellow_ballon1, score);
		shoot_ballon_yellow1 = true;
	}
	



	// in cazul in care player-ul a ramas fara vieti(l-a atins shuriken-ul de 3 ori)
	// jocul se termina, ecranul devine negru si mi se va afisa un mesaj friendly 
	// alaturi de scorul obtinut
	if (gameEnd) {
		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (show == 1) {
			cout << "\n>>>>>>> GAME OVER <<<<<<<\n";
			cout << "Your Score is:  " << score << "\n";
			show = 2;
		}

		return;
	}


}


int Tema1::CollisionRedBallon(float X_arrow, float Y_arrow, float X_red_ballon, float Y_red_ballon, int sc) {

	// coliziunea dintre varful sagetii si balonul rosu (punct la cerc)
	int dx3 = X_arrow - X_red_ballon;
	int dy3 = Y_arrow - Y_red_ballon;
	float distance3 = sqrt(dx3 * dx3 + dy3 * dy3);


	if (distance3 < 325) {
		sc += 100;
	}

	return sc;
}

int Tema1::CollisionYellowBallon(float X_arrow, float Y_arrow, float X_yellow_ballon, float Y_yellow_ballon, int sc) {
	
	// coliziunea dintre varful sagetii si balonul galben (punct la cerc)
	int dx4 = X_arrow - X_yellow_ballon;
	int dy4 = Y_arrow- Y_yellow_ballon;
	float distance4 = sqrt(dx4 * dx4 + dy4 * dy4);

	if (distance4 < 250) {
		sc -= 100;
	}
	return sc;
}

int Tema1::CollisionYellowBallon1(float X_arrow, float Y_arrow, float X_yellow_ballon, float Y_yellow_ballon, int sc) {

	// coliziunea dintre varful sagetii si balonul galben (punct la cerc)
	int dx4 = X_arrow - X_yellow_ballon;
	int dy4 = Y_arrow - Y_yellow_ballon;
	float distance4 = sqrt(dx4 * dx4 + dy4 * dy4);

	if (distance4 < 500) {
		sc -= 100;
	}
	return sc;
}

void Tema1::FrameEnd()
{

}

// in aceasta functie verific ce taste sunt apasate pentru a face o translatie in functie de deltaTime
// si impun niste limite translatiilor pentru a nu iesi din scena
void Tema1::OnInputUpdate(float deltaTime, int mods)
{

	glm::ivec2 resolution = window->GetResolution();

	

	if (window->KeyHold(GLFW_KEY_W) && translateY_bow < resolution.y - radius_bow - 2) {
		translateY_bow += deltaTime * 100;
		translateY_powerbar += deltaTime * 100;
	}

	if (window->KeyHold(GLFW_KEY_S) && translateY_bow > 0 + radius_bow && translateY_powerbar > 0) {
		translateY_bow -= deltaTime * 100;
		translateY_powerbar -= deltaTime * 100;
	}

	if (window->KeyHold(GLFW_KEY_W) && translateY_arrow < resolution.y - radius_bow - 2 && shoot == false) {
		translateY_arrow += deltaTime * 100;
	}

	if (window->KeyHold(GLFW_KEY_S) && translateY_powerbar > 0 && shoot == false) {
		translateY_arrow -= deltaTime * 100;
	}

}

void Tema1::OnKeyPress(int key, int mods)
{
	// add key press event

	if (key == GLFW_KEY_P) {
		start_Game = true;
	}
}

void Tema1::OnKeyRelease(int key, int mods)
{
	// add key release event
}

// retin coordonatele unde se situeaza mouse-ul
// mouseOY a trebuit sa il calculez, deoarece se pozitiona invers pe OY fata de cursor
void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
	glm::ivec2 resolution = window->GetResolution(); 

	translateX_point = mouseX;
	translateY_point = resolution.y - mouseY;

	// imi calculez unghiul pe care il face mouse-ul cu arcul
	double len_point = sqrt(translateX_point * translateX_point + translateY_point * translateY_point);
	double len_bow = sqrt(translateX_bow * translateX_bow + translateY_bow * translateY_bow);


	theta = acos((translateX_point * translateX_bow + translateY_point * translateY_bow) / (len_point * len_bow));


}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
	if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT))
		click_Left = true;
	else click_Left = false;
}

// in aceasta functie incerc sa limitez scalarea powerbar-ului
// verific daca mouse-ul este apasat pentru a trage
void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event

	glm::ivec2 resolution = window->GetResolution();

	if (scaleX_powerbar < resolution.x - 1080)
		ok = 1;

	if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT) == false) {
		shoot = true;
		theta1 = theta;
	}
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}

//functia pentru terminarea jocului
void Tema1::GameEnd() {
	gameEnd = true;
}
