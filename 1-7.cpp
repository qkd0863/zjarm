#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include<cstdlib>
#include<ctime>
#include <gl/glew.h> //--- �ʿ��� ������� include
#include<gl/freeglut.h>
#include <gl/freeglut_ext.h>

using namespace std;

struct rect
{
	float x1, x2, y1, y2;
	float r, g, b;
	bool draw = false;
	bool animation = false;
	float size = 0.001;
	int ani = -1;
};

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void Drag(int x, int y);
void TimerFunction(int value);
void convert(int x, int y, float* ox, float* oy);
void InitBuffer();
void make_vertexShaders();
void make_fragmentShaders();
void make_shaderProgram();
GLvoid drawScene();
GLvoid Reshape(int w, int h);
char* filetobuf(const char* file);


int Rect[5]{ -1,-1,-1,-1,-1 };
bool Point, Line, Triangle, Rectt{ false };
double x1[5], Y1[5], z1[5];
int k = 0;



const GLfloat triShape[3][3] = { { -0.2, -0.2, 0.0 }, { -0.2, 0.2, 0.0 }, { 0.2, -0.2, 0.0} };
const GLfloat RectShape[6][3] = {{ -0.2, -0.2, 0.0 }, { -0.2, 0.2, 0.0 }, { 0.2, -0.2, 0.0},
{ -0.2, 0.2, 0.0 },{0.2,0.2,0.0},{0.2,-0.2,0.0}
};
const GLfloat lineShape[2][3] = {{0.0,-0.2,0.0},{-0.2,0.0,0.0}};
const GLfloat colors[6][3] = {{ 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 1.0 } };
const GLfloat rectcolors[6][3] = { 
{ 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 1.0 },
{ 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 1.0 } };
const GLfloat Poscolor[3] = { 1.0,0.0,1.0 };
const GLfloat linecolor[2][3] = { {1.0,0.0,1.0},{1.0,0.0,1.0 } };

GLfloat Pos[5][3] = { 0, };
GLfloat triPos[5][3] = { 0, };
GLfloat rectPos[5][3] = { 0, };
GLfloat LinePos[5][3] = { 0, };
GLuint vao, vbo[2], TriPosVbo, TriColorVbo, PosVbo[5], ColorVbo, triPosVbo[5], triColor, rectPosVbo[5], rectColor,
linePosVbo[5], lineColorVbo;


GLint width, height;
GLuint shaderProgramID; //--- ���̴� ���α׷� �̸�
GLuint vertexShader; //--- ���ؽ� ���̴� ��ü
GLuint fragmentShader; //--- �����׸�Ʈ ���̴� ��ü







void main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ���� 
{
	//--- ������ �����ϱ�
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Example1");
	//--- GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	glewInit();
	make_shaderProgram();
	InitBuffer();
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

GLvoid drawScene() //--- �ݹ� �Լ�: �׸��� �ݹ� �Լ�
{
	GLfloat rColor, gColor, bColor;
	rColor = gColor = 0.0;
	bColor = 0.0; 
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(shaderProgramID);
	glBindVertexArray(vao);
	

	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position"); //	: 0  Shader�� 'layout (location = 0)' �κ�
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color"); //	: 1

	glEnableVertexAttribArray(PosLocation); // Enable �ʼ�! ����ϰڴ� �ǹ�
	glEnableVertexAttribArray(ColorLocation);

	GLuint changePos = glGetUniformLocation(shaderProgramID, "Pos");


	for (int i = 0; i < 5; ++i) 
	{
		if (Rect[i] == 0) 
		{
			glUniform2f(changePos, Pos[i][0], Pos[i][1]);
			glBindBuffer(GL_ARRAY_BUFFER, PosVbo[i]); // VBO Bind
			glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			{
				glBindBuffer(GL_ARRAY_BUFFER, ColorVbo); // VBO Bind
				glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			}
			glPointSize(5.0);
			glDrawArrays(GL_POINTS, 0, 1);
		}
	}

	for (int i = 0; i < 5; ++i) 
	{
		if (Rect[i] == 1) 
		{
			glUniform2f(changePos, triPos[i][0], triPos[i][1]);
			glBindBuffer(GL_ARRAY_BUFFER, triPosVbo[i]); // VBO Bind
			glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			{
				glBindBuffer(GL_ARRAY_BUFFER, triColor); // VBO Bind
				glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			}
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
	}

	for (int i = 0; i < 5; ++i) 
	{
		if (Rect[i] == 2) 
		{
			glUniform2f(changePos, rectPos[i][0], rectPos[i][1]);
			glBindBuffer(GL_ARRAY_BUFFER, rectPosVbo[i]); // VBO Bind
			glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			{
				glBindBuffer(GL_ARRAY_BUFFER, rectColor); // VBO Bind
				glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			}
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
	}
	for (int i = 0; i < 5; ++i)
	{
		if (Rect[i] == 3)
		{
			glUniform2f(changePos, LinePos[i][0], LinePos[i][1]);
			glBindBuffer(GL_ARRAY_BUFFER, linePosVbo[i]); // VBO Bind
			glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			{
				glBindBuffer(GL_ARRAY_BUFFER, rectColor); // VBO Bind
				glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			}
			glDrawArrays(GL_LINES, 0, 2);
		}
	}


	glDisableVertexAttribArray(PosLocation); // Disable �ʼ�!
	glDisableVertexAttribArray(ColorLocation);

	glutSwapBuffers();
	glutPostRedisplay();
}


GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
{
	glViewport(0, 0, w, h);
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	srand(unsigned(time(NULL)));

	switch (key)
	{
	case 'p':
		std::cout << "Point:true";
		Point = true;
		Triangle = false;
		Rectt = false;
		Line = false;
		break;
	case 'l':
		Point = false;
		Triangle = false;
		Rectt = false;
		Line = true;
		break;
	case 't':
		Point = false;
		Triangle = true;
		Rectt = false;
		Line = false;
		break;
	case 'r':
		Point = false;
		Triangle = false;
		Rectt = true;
		Line = false;
		break;
	case 'c':
		k = 0;
		for (int i = 0; i < 5; ++i) 
		{
			Rect[i] = -1;
		}
		break;
	case 'w':
		for (int i = 0; i < 5; ++i) 
		{
			if (Rect[i] == 0) 
			{
				Pos[i][1] += 0.1f;
				glBindBuffer(GL_ARRAY_BUFFER, PosVbo[i]);
				glBufferData(GL_ARRAY_BUFFER, sizeof(Pos), Pos, GL_DYNAMIC_DRAW);
			}
			else if (Rect[i] == 1)
			{
				triPos[i][1] += 0.1f;
				glBindBuffer(GL_ARRAY_BUFFER, triPosVbo[i]);
				glBufferData(GL_ARRAY_BUFFER, sizeof(triShape), triShape, GL_DYNAMIC_DRAW);
			}
			else if (Rect[i] == 2) 
			{
				rectPos[i][1] += 0.1f;
				glBindBuffer(GL_ARRAY_BUFFER, rectPosVbo[i]);
				glBufferData(GL_ARRAY_BUFFER, sizeof(RectShape), RectShape, GL_DYNAMIC_DRAW);
			}
			else if (Rect[i] == 3) 
			{
				LinePos[i][1] += 0.1f;
				glBindBuffer(GL_ARRAY_BUFFER, linePosVbo[i]);
				glBufferData(GL_ARRAY_BUFFER, sizeof(lineShape), lineShape, GL_DYNAMIC_DRAW);
			}
		}
		break;
	case 'a':
		for (int i = 0; i < 5; ++i) 
		{
			if (Rect[i] == 0) 
			{
				Pos[i][0] -= 0.1f;
				glBindBuffer(GL_ARRAY_BUFFER, PosVbo[i]);
				glBufferData(GL_ARRAY_BUFFER, sizeof(Pos), Pos, GL_DYNAMIC_DRAW);
			}
			else if (Rect[i] == 1) 
			{
				triPos[i][0] -= 0.1f;
				glBindBuffer(GL_ARRAY_BUFFER, triPosVbo[i]);
				glBufferData(GL_ARRAY_BUFFER, sizeof(triShape), triShape, GL_DYNAMIC_DRAW);
			}
			else if (Rect[i] == 2) 
			{
				rectPos[i][0] -= 0.1f;
				glBindBuffer(GL_ARRAY_BUFFER, rectPosVbo[i]);
				glBufferData(GL_ARRAY_BUFFER, sizeof(RectShape), RectShape, GL_DYNAMIC_DRAW);
			}
			else if (Rect[i] == 3) 
			{
				LinePos[i][0] -= 0.1f;
				glBindBuffer(GL_ARRAY_BUFFER, linePosVbo[i]);
				glBufferData(GL_ARRAY_BUFFER, sizeof(lineShape), lineShape, GL_DYNAMIC_DRAW);
			}
		}
		break;
	case 's':
		for (int i = 0; i < 5; ++i) 
		{
			if (Rect[i] == 0) 
			{
				Pos[i][1] -= 0.1f;
				glBindBuffer(GL_ARRAY_BUFFER, PosVbo[i]);
				glBufferData(GL_ARRAY_BUFFER, sizeof(Pos), Pos, GL_DYNAMIC_DRAW);
			}

			else if (Rect[i] == 1) {
				triPos[i][1] -= 0.1f;
				glBindBuffer(GL_ARRAY_BUFFER, triPosVbo[i]);
				glBufferData(GL_ARRAY_BUFFER, sizeof(triShape), triShape, GL_DYNAMIC_DRAW);
			}
			else if (Rect[i] == 2)
			{
				rectPos[i][1] -= 0.1f;
				glBindBuffer(GL_ARRAY_BUFFER, rectPosVbo[i]);
				glBufferData(GL_ARRAY_BUFFER, sizeof(RectShape), RectShape, GL_DYNAMIC_DRAW);
			}
			else if (Rect[i] == 3) 
			{
				LinePos[i][1] -= 0.1f;
				glBindBuffer(GL_ARRAY_BUFFER, linePosVbo[i]);
				glBufferData(GL_ARRAY_BUFFER, sizeof(lineShape), lineShape, GL_DYNAMIC_DRAW);
			}
		}
		break;
	case 'd':
		for (int i = 0; i < 5; ++i) 
		{
			if (Rect[i] == 0) 
			{
				Pos[i][0] += 0.1f;
				glBindBuffer(GL_ARRAY_BUFFER, PosVbo[i]);
				glBufferData(GL_ARRAY_BUFFER, sizeof(Pos), Pos, GL_DYNAMIC_DRAW);
			}
			else if (Rect[i] == 1) 
			{
				triPos[i][0] += 0.1f;
				glBindBuffer(GL_ARRAY_BUFFER, triPosVbo[i]);
				glBufferData(GL_ARRAY_BUFFER, sizeof(triShape), triShape, GL_DYNAMIC_DRAW);
			}
			else if (Rect[i] == 2) 
			{
				rectPos[i][0] += 0.1f;
				glBindBuffer(GL_ARRAY_BUFFER, rectPosVbo[i]);
				glBufferData(GL_ARRAY_BUFFER, sizeof(RectShape), RectShape, GL_DYNAMIC_DRAW);	
			}
			else if (Rect[i] == 3) 
			{
				LinePos[i][0] += 0.1f;
				glBindBuffer(GL_ARRAY_BUFFER, linePosVbo[i]);
				glBufferData(GL_ARRAY_BUFFER, sizeof(lineShape), lineShape, GL_DYNAMIC_DRAW);
			}
		}
		break;
	case 'q':
		exit(1);
		break; //--- ������ ��������� ����
	}
	glutPostRedisplay(); //--- ������ �ٲ� ������ ��� �ݹ� �Լ��� ȣ���Ͽ� ȭ���� refresh �Ѵ�
}

void Mouse(int button, int state, int x, int y)
{
	float Rx, Ry, Wx, Wy;

	convert(x, y, &Wx, &Wy);
	convert(x, y, &Rx, &Ry);

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (k < 5)
		{
			if (Point) {
				x1[k] = Wx;
				Y1[k] = Wy;
				std::cout << std::endl << x1[k] << Y1[k];
				z1[k] = 0;
				Pos[k][0] = x1[k];
				Pos[k][1] = Y1[k];
				Pos[k][2] = z1[k];
				Rect[k] = 0;
				++k;
			}
			else if (Triangle) {
				x1[k] = Wx;
				Y1[k] = Wy;
				std::cout << std::endl << x1[k] << Y1[k];
				z1[k] = 0;
				triPos[k][0] = x1[k];
				triPos[k][1] = Y1[k];
				triPos[k][2] = z1[k];
				Rect[k] = 1;
				++k;
			}
			else if (Rectt) {
				x1[k] = Wx;
				Y1[k] = Wy;
				std::cout << std::endl << x1[k] << Y1[k];
				z1[k] = 0;
				rectPos[k][0] = x1[k];
				rectPos[k][1] = Y1[k];
				rectPos[k][2] = z1[k];
				Rect[k] = 2;
				++k;
			}
			else if (Line) {
				x1[k] = Wx;
				Y1[k] = Wy;
				std::cout << std::endl << x1[k] << Y1[k];
				z1[k] = 0;
				LinePos[k][0] = x1[k];
				LinePos[k][1] = Y1[k];
				LinePos[k][2] = z1[k];
				Rect[k] = 3;
				++k;
			}
			return;
		}
	}
}


void convert(int x, int y, float* ox, float* oy)
{
	int w = 800;
	int h = 600;
	*ox = (float)(x - (float)w / 2.0) * (float)(1.0 / (float)(w / 2.0));
	*oy = -(float)(y - (float)h / 2.0) * (float)(1.0 / (float)(h / 2.0));
}




void TimerFunction(int value)
{


	glutPostRedisplay(); // ȭ�� �� ���
	glutTimerFunc(100, TimerFunction, 1); // Ÿ�̸��Լ� �� ����
}


GLchar* vertexSource, * fragmentSource; //--- �ҽ��ڵ� ���� ����

void make_vertexShaders()
{
	vertexSource = filetobuf("vertex.glsl");
		//--- ���ؽ� ���̴� ��ü �����
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//--- ���̴� �ڵ带 ���̴� ��ü�� �ֱ�
	glShaderSource(vertexShader, 1, (const GLchar**)&vertexSource, 0);
	//--- ���ؽ� ���̴� �������ϱ�
	glCompileShader(vertexShader);
	//--- �������� ����� ���� ���� ���: ���� üũ
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if(!result)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		cerr << "ERROR: vertex shader ������ ����\n" << errorLog << endl;
		return;
	}
}

void make_fragmentShaders()
{
	fragmentSource = filetobuf("fragment.glsl");
	//--- �����׸�Ʈ ���̴� ��ü �����
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//--- ���̴� �ڵ带 ���̴� ��ü�� �ֱ�
	glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentSource, 0);
	//--- �����׸�Ʈ ���̴� ������
	glCompileShader(fragmentShader);
	//--- �������� ����� ���� ���� ���: ������ ���� üũ
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		cerr << "ERROR: fragment shader ������ ����\n" << errorLog << endl;
		return;
	}
}


void make_shaderProgram()
{
	make_vertexShaders(); //--- ���ؽ� ���̴� �����
	make_fragmentShaders(); //--- �����׸�Ʈ ���̴� �����
	//-- shader Program
	shaderProgramID = glCreateProgram();
	glAttachShader(shaderProgramID, vertexShader);
	glAttachShader(shaderProgramID, fragmentShader);
	glLinkProgram(shaderProgramID);
	//--- ���̴� �����ϱ�
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	//--- Shader Program ����ϱ�
	glUseProgram(shaderProgramID);
}



char* filetobuf(const char* file)
{
	FILE* fptr;
	long length;
	char* buf;
	fptr = fopen(file, "rb"); // Open file for reading
	if (!fptr) // Return NULL on failure
		return NULL;
	fseek(fptr, 0, SEEK_END); // Seek to the end of the file
	length = ftell(fptr); // Find out how many bytes into the file we are
	buf = (char*)malloc(length + 1); // Allocate a buffer for the entire length of the file and a null terminator
	fseek(fptr, 0, SEEK_SET); // Go back to the beginning of the file
	fread(buf, length, 1, fptr); // Read the contents of the file in to the buffer
	fclose(fptr); // Close the file
	buf[length] = 0; // Null terminator
	return buf; // Return the buffer
}



void InitBuffer()
{
	glGenVertexArrays(1, &vao); //--- VAO �� �����ϰ� �Ҵ��ϱ�
	glBindVertexArray(vao); //--- VAO�� ���ε��ϱ�
	glGenBuffers(2, vbo); //--- 2���� VBO�� �����ϰ� �Ҵ��ϱ�
	//--- 1��° VBO�� Ȱ��ȭ�Ͽ� ���ε��ϰ�, ���ؽ� �Ӽ� (��ǥ��)�� ����
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	//--- ���� diamond ���� ���ؽ� ������ ���� ���ۿ� �����Ѵ�.
	//--- triShape �迭�� ������: 9 * float
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), triShape, GL_DYNAMIC_DRAW);
	//--- ��ǥ���� attribute �ε��� 0���� ����Ѵ�: ���ؽ� �� 3* float
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//--- attribute �ε��� 0���� ��밡���ϰ� ��
	glEnableVertexAttribArray(0);
	//--- 2��° VBO�� Ȱ��ȭ �Ͽ� ���ε� �ϰ�, ���ؽ� �Ӽ� (����)�� ����
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	//--- ���� colors���� ���ؽ� ������ �����Ѵ�.
	//--- colors �迭�� ������: 9 *float
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), colors, GL_DYNAMIC_DRAW);
	//--- ������ attribute �ε��� 1���� ����Ѵ�: ���ؽ� �� 3*float
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//--- attribute �ε��� 1���� ��� �����ϰ� ��.
	glEnableVertexAttribArray(1);


	for (int i = 0; i < 5; ++i)
	{
		glGenBuffers(1, &PosVbo[i]);
		glBindBuffer(GL_ARRAY_BUFFER, PosVbo[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Pos), Pos, GL_DYNAMIC_DRAW);
		glGenBuffers(1, &ColorVbo);
		glBindBuffer(GL_ARRAY_BUFFER, ColorVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Poscolor), Poscolor, GL_STATIC_DRAW);
	}


	for (int i = 0; i < 5; ++i)
	{
		glGenBuffers(1, &triPosVbo[i]);
		glBindBuffer(GL_ARRAY_BUFFER, triPosVbo[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(triShape), triShape, GL_DYNAMIC_DRAW);
		glGenBuffers(1, &triColor);
		glBindBuffer(GL_ARRAY_BUFFER, triColor);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	}


	for (int i = 0; i < 5; ++i)
	{
		glGenBuffers(1, &rectPosVbo[i]);
		glBindBuffer(GL_ARRAY_BUFFER, rectPosVbo[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(RectShape), RectShape, GL_DYNAMIC_DRAW);
		glGenBuffers(1, &rectColor);
		glBindBuffer(GL_ARRAY_BUFFER, rectColor);
		glBufferData(GL_ARRAY_BUFFER, sizeof(rectcolors), rectcolors, GL_STATIC_DRAW);
	}


	for (int i = 0; i < 5; ++i)
	{
		glGenBuffers(1, &linePosVbo[i]);
		glBindBuffer(GL_ARRAY_BUFFER, linePosVbo[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(lineShape), lineShape, GL_DYNAMIC_DRAW);
		glGenBuffers(1, &lineColorVbo);
		glBindBuffer(GL_ARRAY_BUFFER, lineColorVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(linecolor), linecolor, GL_STATIC_DRAW);
	}
}