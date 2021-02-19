/*
	Micut Andrei-Ion
	Grupa 331CB
*/

#include "Object2D.h"

#include <Core/Engine.h>
#include <math.h>

#define TAU 2*3.141592


// am folosit acest mesh pentru a-mi crea powerbar-ul pe care l-am scalat diferit

Mesh* Object2D::CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(length, 0, 0), color),
		VertexFormat(glm::vec3(length, length, 0), color),
		VertexFormat(glm::vec3(0, length, 0), color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };
	
	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}


// folosit pentru a crea sageata

Mesh* Object2D::CreateArrow(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{

	Mesh* arrow = new Mesh(name);
	float line_width = 4;

	std::vector<VertexFormat> vertices;
	std::vector<unsigned short> indices;


	vertices =
	{
		VertexFormat(glm::vec3(0, line_width / 2,  0), color), //0
		VertexFormat(glm::vec3(length, line_width / 2,  0), color),  //1
		VertexFormat(glm::vec3(length, 3 / 2 * line_width,  0), color), //2
		VertexFormat(glm::vec3(length + length / 6, 0, 0), color), //3
		VertexFormat(glm::vec3(length, -3 / 2 * line_width,  0), color), //4
		VertexFormat(glm::vec3(length, -line_width / 2,  0), color), //5
		VertexFormat(glm::vec3(0, -line_width / 2,  0), color) //6
	};
	indices = { 0, 1, 5,
				0, 5, 6,
				2, 3, 4 };

	arrow->SetDrawMode(GL_TRIANGLES);
	arrow->InitFromData(vertices, indices);
	return arrow;
}

// folosit pentru codita baloanelor(creat din mai multe linii)

Mesh* Object2D::CreatePolyLine(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	float length_polyline = length;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner + glm::vec3(0, 0, 0), color), //0
		VertexFormat(corner + glm::vec3(-length / 3, -length / 10, 0), color), //1 
		VertexFormat(glm::vec3(0, -length / 5, 0), color), //2
		VertexFormat(glm::vec3(-length / 3.5, -length / 2.5, 0), color), //3
		VertexFormat(glm::vec3(0, -length / 2, 0), color) //4
		

	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1,
											1, 2, 
											2, 3,
											3, 4};

	if (!fill) {
		square->SetDrawMode(GL_LINES);
	}

	square->InitFromData(vertices, indices);
	return square;
}

// functia de creare a inimilor ce reprezinta vietile player-ului

Mesh* Object2D::CreateHeart(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	float length_polyline = length;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner + glm::vec3(0, 0, 0), color), //0
		VertexFormat(corner + glm::vec3(-length / 4, -length / 4, 0), color), //1 
		VertexFormat(corner + glm::vec3(length / 2.7, -length , 0), color), //2 
		VertexFormat(corner + glm::vec3(length, - length/4 , 0), color), //3 
		VertexFormat(corner + glm::vec3(( 3 * length / 4), 0 , 0), color), //4 
		VertexFormat(corner + glm::vec3((length / 2), 0, 0), color), //5 
		VertexFormat(corner + glm::vec3((length / 2.7), -(length / 4.5), 0), color), //6
		VertexFormat(corner + glm::vec3((length / 4), 0, 0), color) //7


	};

	Mesh* heart = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 7,
											1, 7, 6,
											3, 5, 4,
											3, 6, 5,
											2, 1, 0,
											2, 0, 7,
											2, 7, 6,
											2, 6, 5,
											2, 5, 4,
											2, 4, 3};

	if (!fill) {
		heart->SetDrawMode(GL_TRIANGLE_FAN);
	}

	heart->InitFromData(vertices, indices);
	return heart;
}


// shuriken-ul l-am creat din 4 triunghiuri
Mesh* Object2D::CreateShuriken(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;


	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(0, 0, 0), color), //0
		VertexFormat(glm::vec3(length/2, length/2, 0), color), //1
		VertexFormat(glm::vec3(length, 0, 0), color), //2
		VertexFormat(glm::vec3(length, length, 0), color), //3
		VertexFormat(glm::vec3(1.5 * length, length/2, 0), color), //4
		VertexFormat(glm::vec3(2 * length, 0, 0), color), //5
		VertexFormat(glm::vec3(1.5 * length, -length/2, 0), color), //6
		VertexFormat(glm::vec3(length, -length, 0), color), //7
		VertexFormat(glm::vec3(length/2, -length/2, 0), color) //8


	};

	Mesh* shuriken = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2,
											2, 3, 4,
											2, 5, 6,
											2, 7, 8};

	if (!fill) {
		shuriken->SetDrawMode(GL_TRIANGLES);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
	}

	shuriken->InitFromData(vertices, indices);
	return shuriken;
}


// baloanele le-am creat cu ajutorul functiilor sin si cos pentru a-mi forma
// un cerc pe care l-am scalat diferit

Mesh* Object2D::CreateBallon(std::string name, glm::vec3 center, float radius, glm::vec3 color)
{
	Mesh* ballon = new Mesh(name);
	glm::vec3 clr(color);
	std::vector<VertexFormat> vertices;
	std::vector<unsigned short> indices;

	vertices.push_back(VertexFormat(center, color));
	indices.push_back(0);
	for (float i = 0; i <= 50; i++) {
		glm::vec3 border_point(radius * cos((double)i * (TAU) / (double)50),
			radius * sin((double)i * TAU / (double)50),
			0);
		vertices.push_back(VertexFormat(center + border_point, clr));
		indices.push_back(i + 1);
	}

	ballon->SetDrawMode(GL_TRIANGLE_FAN);
	ballon->InitFromData(vertices, indices);
	return ballon;
}


// punctul ce reprezinta cursorul mouse-ului pentru o mai buna apreciere a tintelor

Mesh* Object2D::CreatePoint(std::string name, glm::vec3 center, float radius, glm::vec3 color)
{
	Mesh* point = new Mesh(name);
	glm::vec3 clr(color);
	std::vector<VertexFormat> vertices;
	std::vector<unsigned short> indices;

	vertices.push_back(VertexFormat(center, color));
	indices.push_back(0);
	for (float i = 0; i <= 50; i++) {
		glm::vec3 border_point(radius * cos((double)i * (TAU) / (double)50),
			radius * sin((double)i * TAU / (double)50),
			0);
		vertices.push_back(VertexFormat(center + border_point, clr));
		indices.push_back(i + 1);
	}

	point->SetDrawMode(GL_TRIANGLE_FAN);
	point->InitFromData(vertices, indices);
	return point;
}


// arcul ce reprezinta player-ul l-am format din semicerul unui cerc

Mesh* Object2D::CreateBow(std::string name, glm::vec3 center, float radius, glm::vec3 color) {
	Mesh* bow = new Mesh(name);
	glm::vec3 clr(color);
	std::vector<VertexFormat> vertices;
	std::vector<unsigned short> indices;

	vertices.push_back(VertexFormat(center, color));
	indices.push_back(0);
	for (float i = 12.95; i <= 50; ++i) {
		glm::vec3 border_point(radius * cos((double)i * (TAU) / (double)50),
			radius * sin((double)i * TAU / (double)50),
			0);
		vertices.push_back(VertexFormat(center + border_point, clr));
		indices.push_back(i + 1);
	}
	
	bow->SetDrawMode(GL_LINE_STRIP);
	bow->InitFromData(vertices, indices);
	return bow;
}


Mesh* Object2D::CreateFireBall(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	float length_polyline = length;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner + glm::vec3(0, 0, 0), color), //0
		VertexFormat(corner + glm::vec3(-3 * length, length / 2, 0), color), //2
		VertexFormat(corner + glm::vec3(0, length / 2, 0), color), //3
		VertexFormat(corner + glm::vec3(0, length, 0), color), //4
		VertexFormat(corner + glm::vec3(length, length / 2, 0), color), //4


	};

	Mesh* heart = new Mesh(name);
	std::vector<unsigned short> indices = { 1, 2, 3, 4, 0};

	if (!fill) {
		heart->SetDrawMode(GL_TRIANGLE_FAN);
	}

	heart->InitFromData(vertices, indices);
	return heart;
}

Mesh* Object2D::CreateTriangle(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	float length_polyline = length;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner + glm::vec3(0, -length, 0), color), //0
		VertexFormat(corner + glm::vec3(0, length, 0), color), //1
		VertexFormat(corner + glm::vec3(length, 0, 0), color) //2


	};

	Mesh* heart = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2 };

	if (!fill) {
		heart->SetDrawMode(GL_TRIANGLES);
	}

	heart->InitFromData(vertices, indices);
	return heart;
}