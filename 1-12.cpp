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

struct Poly
{
	int shape;
	bool sel = false;
	bool draw = true;
	bool ani = false;
	bool r = true, u = true;
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
void set();

bool Line = true, Tri = true, Rect = true, Penta = true;
double x1[5], Y1[5], z1[5];
float rad = 3.141592 / 180.0;
float rx = 0, ry = 0;
char shape = 'a';
Poly P[15];


GLfloat DotShape[1][3] = { { 0.0, 0.0, 0.0} };
GLfloat LineShape[2][3] = { { 0.1, 0.1, 0.0},{ -0.1, -0.1, 0.0 } };
GLfloat TriShape[3][3] = { { -0.1, -0.1, 0.0 }, { 0.0, 0.1, 0.0 }, { 0.1, -0.1, 0.0} };
GLfloat RectShape[6][3] = {
{ -0.1, -0.1, 0.0 }, { -0.1, 0.1, 0.0 }, { 0.1, -0.1, 0.0},
{ -0.1, 0.1, 0.0 }, { 0.1, 0.1, 0.0}, { 0.1, -0.1, 0.0}
};
GLfloat PentagonShape[9][3] = {
{ 0.2 * cos(90 * rad), 0.2 * sin(90 * rad), 0.0},
{ 0.2 * cos(90 * rad + 72 * rad), 0.2 * sin(90 * rad + 72 * rad), 0.0},
{ 0.2 * cos(90 * rad + 72 * rad * 2), 0.2 * sin(90 * rad + 72 * rad * 2), 0.0},

{ 0.2 * cos(90 * rad), 0.2 * sin(90 * rad), 0.0},
{ 0.2 * cos(90 * rad + 72 * rad * 2), 0.2 * sin(90 * rad + 72 * rad * 2), 0.0},
{ 0.2 * cos(90 * rad + 72 * rad * 3), 0.2 * sin(90 * rad + 72 * rad * 3), 0.0},

{ 0.2 * cos(90 * rad), 0.2 * sin(90 * rad), 0.0},
{ 0.2 * cos(90 * rad + 72 * rad * 3), 0.2 * sin(90 * rad + 72 * rad * 3), 0.0},
{ 0.2 * cos(90 * rad + 72 * rad * 4), 0.2 * sin(90 * rad + 72 * rad * 4), 0.0},
};



const GLfloat colors1[6][3] = { { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 1.0 } };




const GLfloat Poscolor[3] = { 1.0,0.0,1.0 };
const GLfloat linecolor[2][3] = { {0.0,0.0,0.0},{0.0,0.0,0.0 } };
const GLfloat tricolor[6][3] = { {0.0,1.0,0.0},{0.0,1.0,0.0 } ,{0.0,1.0,0.0 } ,{0.0,1.0,0.0},{0.0,1.0,0.0 } ,{0.0,1.0,0.0 } };
const GLfloat rectcolors[9][3] = {
{ 1.0, 1.0, 0.0 }, { 1.0, 1.0, 0.0 }, { 1.0, 1.0, 0.0 },
{ 1.0, 1.0, 0.0 }, { 1.0, 1.0, 0.0 }, { 1.0, 1.0, 0.0 },
{ 1.0, 1.0, 0.0 }, { 1.0, 1.0, 0.0 }, { 1.0, 1.0, 0.0 } };
const GLfloat PenColors[9][3] = {
{ 1.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 },
{ 1.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 },
{ 1.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 } };




GLfloat PolyPos[15][3] = {
	{-0.5,0.75,0.0}, {0.0,0.75,0.0},{0.5,0.75,0.0},
	{-0.5,0.5,0.0}, {0.0,0.5,0.0},{0.5,0.5,0.0},
	{-0.5,0.25,0.0}, {0.0,0.25,0.0},{0.5,0.25,0.0},
	{-0.5,-0.25,0.0}, {0.0,-0.25,0.0},{0.5,-0.25,0.0},
	{-0.5,-0.75,0.0}, {0.0,-0.75,0.0},{0.5,-0.75,0.0},
};
GLuint PolyPosVbo[15], PolyColorVbo[15];



GLfloat PentaPos[5][3] = { {0.5,-0.5,0.0} };
GLfloat Pos[5][3] = { 0, };
GLfloat triPos[5][3] = { {0.5,0.5,0.0} };
GLfloat rectPos[5][3] = { {-0.5,-0.5,0.0} };
GLfloat LinePos[5][3] = { {-0.5,0.5,0.0} };


GLuint linePosVbo, lineColorVbo;
GLuint TriPosVbo, TriColorVbo;
GLuint PosVbo, ColorVbo;
GLuint triPosVbo, triColor;
GLuint rectPosVbo, rectColor;
GLuint PenPosVbo, PenColor;


GLint width, height;
GLuint shaderProgramID; //--- ���̴� ���α׷� �̸�
GLuint vertexShader; //--- ���ؽ� ���̴� ��ü
GLuint fragmentShader; //--- �����׸�Ʈ ���̴� ��ü







void main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ���� 
{
	set();
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
	glutMotionFunc(Drag);
	glutKeyboardFunc(Keyboard);
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutTimerFunc(100, TimerFunction, 1);
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





	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position"); //	: 0  Shader�� 'layout (location = 0)' �κ�
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color"); //	: 1

	glEnableVertexAttribArray(PosLocation); // Enable �ʼ�! ����ϰڴ� �ǹ�
	glEnableVertexAttribArray(ColorLocation);

	GLuint changePos = glGetUniformLocation(shaderProgramID, "Pos");



	for (int i = 0;i < 15;i++)
	{
		if (P[i].draw)
		{
			switch (P[i].shape)
			{
			case 1:
				glUniform2f(changePos, PolyPos[i][0], PolyPos[i][1]);
				glBindBuffer(GL_ARRAY_BUFFER, PolyPosVbo[i]); // VBO Bind
				glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
				{
					glBindBuffer(GL_ARRAY_BUFFER, PolyColorVbo[i]); // VBO Bind
					glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
				}
				glPointSize(5.0);
				glDrawArrays(GL_POINTS, 0, 1);
				break;
			case 2:
				glUniform2f(changePos, PolyPos[i][0], PolyPos[i][1]);
				glBindBuffer(GL_ARRAY_BUFFER, PolyPosVbo[i]); // VBO Bind
				glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
				{
					glBindBuffer(GL_ARRAY_BUFFER, PolyColorVbo[i]); // VBO Bind
					glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
				}

				glDrawArrays(GL_LINES, 0, 2);
				break;
			case 3:
				glUniform2f(changePos, PolyPos[i][0], PolyPos[i][1]);
				glBindBuffer(GL_ARRAY_BUFFER, PolyPosVbo[i]); // VBO Bind
				glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
				{
					glBindBuffer(GL_ARRAY_BUFFER, PolyColorVbo[i]); // VBO Bind
					glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
				}
				glDrawArrays(GL_TRIANGLES, 0, 3);
				break;
			case 4:
				glUniform2f(changePos, PolyPos[i][0], PolyPos[i][1]);
				glBindBuffer(GL_ARRAY_BUFFER, PolyPosVbo[i]); // VBO Bind
				glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
				{
					glBindBuffer(GL_ARRAY_BUFFER, PolyColorVbo[i]); // VBO Bind
					glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
				}
				glDrawArrays(GL_TRIANGLES, 0, 6);
				break;
			case 5:
				glUniform2f(changePos, PolyPos[i][0], PolyPos[i][1]);
				glBindBuffer(GL_ARRAY_BUFFER, PolyPosVbo[i]); // VBO Bind
				glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
				{
					glBindBuffer(GL_ARRAY_BUFFER, PolyColorVbo[i]); // VBO Bind
					glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
				}
				glDrawArrays(GL_TRIANGLES, 0, 9);
				break;
			default:
				break;
			}
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
	case 'q':
		exit(1);
		break;
	}

	glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y)
{
	srand((unsigned int)time(NULL));

	float Rx, Ry, Wx, Wy;


	convert(x, y, &Wx, &Wy);
	convert(x, y, &Rx, &Ry);



	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		for (int i = 0;i < 15;i++)
		{
			if(abs(PolyPos[i][0] - Wx) < 0.05&& abs(PolyPos[i][1] - Wy) < 0.05)
			{
				P[i].sel = true;
				break;
			}
		}
		
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		for (int i = 0;i < 15;i++)
		{
			if (P[i].sel)
			{
				for (int j = 0;j < 15;j++)
				{
					if (abs(PolyPos[j][0] - PolyPos[i][0]) < 0.1 && abs(PolyPos[j][1] - PolyPos[i][1]) < 0.1)
					{
						if (i != j)
						{
							P[i].shape += P[j].shape;
							if (P[i].shape >= 6)
								P[i].shape = 1;
							P[j].draw = false;
							P[i].ani = true;
							InitBuffer();
						}
					}
				}
			}
			P[i].sel = false;
		}
	}
}

void Drag(int x, int y)
{
	float Rx, Ry, Wx, Wy;

	convert(x, y, &Wx, &Wy);
	convert(x, y, &Rx, &Ry);

	for (int i = 0;i < 15;i++)
	{
		if (P[i].sel)
		{
			PolyPos[i][0] = Wx;PolyPos[i][1] = Wy;
		}
	}

	glutPostRedisplay();
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
	for (int i = 0;i < 15;i++)
	{
		if (P[i].ani)
		{
			if (P[i].r)
			{
				if (P[i].u)
				{
					PolyPos[i][0] += 0.05;PolyPos[i][1] += 0.05;
					if (PolyPos[i][0] >= 1)
						P[i].r = false;
					if (PolyPos[i][1] >= 1)
						P[i].u = false;
				}
				else
				{
					PolyPos[i][0] += 0.05;PolyPos[i][1] -= 0.05;
					if (PolyPos[i][0] >= 1)
						P[i].r = false;
					if (PolyPos[i][1] <= -1)
						P[i].u = true;
				}
			}
			else
			{
				if (P[i].u)
				{
					PolyPos[i][0] -= 0.05;PolyPos[i][1] += 0.05;
					if (PolyPos[i][0] <= -1)
						P[i].r = true;
					if (PolyPos[i][1] >= 1)
						P[i].u = false;
				}
				else
				{
					PolyPos[i][0] -= 0.05;PolyPos[i][1] -= 0.05;
					if (PolyPos[i][0] <= -1)
						P[i].r = true;
					if (PolyPos[i][1] <= -1)
						P[i].u = true;
				}
			}
		}
	}


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
	if (!result)
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
	for (int i = 0;i < 15;i++)
	{
		switch (P[i].shape)
		{
		case 1:
			glGenBuffers(1, &PolyPosVbo[i]);
			glBindBuffer(GL_ARRAY_BUFFER, PolyPosVbo[i]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(DotShape), DotShape, GL_DYNAMIC_DRAW);
			glGenBuffers(1, &PolyColorVbo[i]);
			glBindBuffer(GL_ARRAY_BUFFER, PolyColorVbo[i]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(PolyColorVbo), PolyColorVbo, GL_STATIC_DRAW);
			break;
		case 2:
			glGenBuffers(1, &PolyPosVbo[i]);
			glBindBuffer(GL_ARRAY_BUFFER, PolyPosVbo[i]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(LineShape), LineShape, GL_DYNAMIC_DRAW);
			glGenBuffers(1, &PolyColorVbo[i]);
			glBindBuffer(GL_ARRAY_BUFFER, PolyColorVbo[i]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(PolyColorVbo), PolyColorVbo, GL_STATIC_DRAW);
			break;
		case 3:
			glGenBuffers(1, &PolyPosVbo[i]);
			glBindBuffer(GL_ARRAY_BUFFER, PolyPosVbo[i]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(TriShape), TriShape, GL_DYNAMIC_DRAW);
			glGenBuffers(1, &PolyColorVbo[i]);
			glBindBuffer(GL_ARRAY_BUFFER, PolyColorVbo[i]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(PolyColorVbo), PolyColorVbo, GL_STATIC_DRAW);
			break;
		case 4:
			glGenBuffers(1, &PolyPosVbo[i]);
			glBindBuffer(GL_ARRAY_BUFFER, PolyPosVbo[i]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(RectShape), RectShape, GL_DYNAMIC_DRAW);
			glGenBuffers(1, &PolyColorVbo[i]);
			glBindBuffer(GL_ARRAY_BUFFER, PolyColorVbo[i]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(PolyColorVbo), PolyColorVbo, GL_STATIC_DRAW);
			break;
		case 5:
			glGenBuffers(1, &PolyPosVbo[i]);
			glBindBuffer(GL_ARRAY_BUFFER, PolyPosVbo[i]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(PentagonShape), PentagonShape, GL_DYNAMIC_DRAW);
			glGenBuffers(1, &PolyColorVbo[i]);
			glBindBuffer(GL_ARRAY_BUFFER, PolyColorVbo[i]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(PolyColorVbo), PolyColorVbo, GL_STATIC_DRAW);
			break;
		default:
			break;
		}
	}
}



void set()
{
	for (int i = 0;i < 3;i++)
	{
		P[i].shape = 1;
	}
	for (int i = 3;i < 6;i++)
	{
		P[i].shape = 2;
	}
	for (int i = 6;i < 9;i++)
	{
		P[i].shape = 3;
	}
	for (int i = 9;i < 12;i++)
	{
		P[i].shape = 4;
	}
	for (int i = 12;i < 15;i++)
	{
		P[i].shape = 5;
	}
}