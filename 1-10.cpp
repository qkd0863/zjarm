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
float rx = 0, ry = 0;
float t = 0.0, rad = 0.0;
float r = 0, g = 0, b = 0;
int n = 6; float pie = 3.141592;
float cycle = pie * n;
bool clockc = true;
char shape = 'a';


const GLfloat RectShape[6][3] = { { -0.2, -0.2, 0.0 }, { -0.2, 0.2, 0.0 }, { 0.2, -0.2, 0.0},
{ -0.2, 0.2, 0.0 },{0.2,0.2,0.0},{0.2,-0.2,0.0}
};

const GLfloat colors1[6][3] = { { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 1.0 } };


const GLfloat rectcolors[6][3] = {
{ 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 1.0 },
{ 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 1.0 } };
const GLfloat Poscolor[3] = { 1.0,0.0,1.0 };
const GLfloat linecolor[2][3] = { {1.0,0.0,1.0},{1.0,0.0,1.0 } };

GLfloat Pos[5][3] = { 0, };
GLfloat triPos[5][3] = { 0, };
GLfloat rectPos[5][3] = { 0, };
GLfloat LinePos1[5][3] = { 0, };
GLfloat LinePos2[5][3] = { 0, };
GLfloat LinePos3[5][3] = { 0, };

GLuint vao, vbo[2], TriPosVbo, TriColorVbo, PosVbo[5], ColorVbo, triPosVbo[5], triColor[4], rectPosVbo[5], rectColor,
linePosVbo1[5], linePosVbo2[5], linePosVbo3[5], lineColorVbo;


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
	glutTimerFunc(10, TimerFunction, 1);
	glutMainLoop();
}

GLvoid drawScene() //--- �ݹ� �Լ�: �׸��� �ݹ� �Լ�
{
	GLfloat rColor, gColor, bColor;
	rColor = gColor = 0.0;
	bColor = 0.0;
	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(shaderProgramID);
	glBindVertexArray(vao);





	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position"); //	: 0  Shader�� 'layout (location = 0)' �κ�
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color"); //	: 1

	glEnableVertexAttribArray(PosLocation); // Enable �ʼ�! ����ϰڴ� �ǹ�
	glEnableVertexAttribArray(ColorLocation);

	GLuint changePos = glGetUniformLocation(shaderProgramID, "Pos");




	

	
	glBindBuffer(GL_ARRAY_BUFFER, PosVbo[0]); // VBO Bind
	glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	{
		glBindBuffer(GL_ARRAY_BUFFER, ColorVbo); // VBO Bind
		glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	}
	
	
	if (clockc)
	{
		for (float i = 0;i < t;i += 0.1)
		{
			glUniform2f(changePos, Pos[0][0] + cos(i * -1) / 100.0 * i, Pos[0][1] + sin(i * -1) / 100.0 * i);
			glPointSize(5.0);
			glDrawArrays(GL_POINTS, 0, 1);
		}
	}
	else
	{
		for (float i = 0;i < cycle;i += 0.1)
		{
			glUniform2f(changePos, Pos[0][0] + cos(i * -1) / 100.0 * i, Pos[0][1] + sin(i * -1) / 100.0 * i);
			glPointSize(5.0);
			glDrawArrays(GL_POINTS, 0, 1);
		}

		for (float i = 0;i < cycle - t;i += 0.1)
		{
			glUniform2f(changePos, Pos[0][0] + cos(cycle * -1) / 100.0 * cycle*2 - cos(i * 1) / 100.0 * (cycle - i), Pos[0][1] + sin(cycle * -1) / 100.0 * cycle - sin(i * 1) / 100.0 * (cycle - i));
			glPointSize(5.0);
			glDrawArrays(GL_POINTS, 0, 1);
		}
	}

	/*
	if (clockc)
	{
		for (float i = 0;i < t;i += 0.1)
		{
			glUniform2f(changePos, Pos[0][0] + cos(i * 1) / 100.0 * i, Pos[0][1] + sin(i * 1) / 100.0 * i);
			glPointSize(5.0);
			glDrawArrays(GL_POINTS, 0, 1);
		}
	}
	else
	{
		for (float i = 0;i < cycle;i += 0.1)
		{
			glUniform2f(changePos, Pos[0][0] + cos(i * 1) / 100.0 * i, Pos[0][1] + sin(i * 1) / 100.0 * i);
			glPointSize(5.0);
			glDrawArrays(GL_POINTS, 0, 1);
		}

		for (float i = 0;i < cycle - t;i += 0.1)
		{
			glUniform2f(changePos, Pos[0][0] + cos(cycle * 1) / 100.0 * cycle + Pos[0][0] + cos(cycle * 1) / 100.0 * cycle - cos(i * -1) / 100.0 * (cycle - i), Pos[0][1] + sin(cycle * 1) / 100.0 * cycle - sin(i * -1) / 100.0 * (cycle - i));
			glPointSize(5.0);
			glDrawArrays(GL_POINTS, 0, 1);
		}
	}

	*/
	
	
	


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
	case '1':
		cycle = pie * 2;
		break;
	case '2':
		cycle = pie * 4;
		break;
	case '3':
		cycle = pie * 6;
		break;
	case '4':
		cycle = pie * 8;
		break;
	case '5':
		cycle = pie * 10;
		break;
	case 'a':
		shape = 'a';
		break;
	case 'b':
		shape = 'b';
		break;
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

	r = rand() % 255 / 255.0, g = rand() % 255 / 255.0, b = rand() % 255 / 255.0;

	convert(x, y, &Wx, &Wy);
	convert(x, y, &Rx, &Ry);



	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		x1[0] = Wx;
		Y1[0] = Wy;
		std::cout << std::endl << x1[0] << Y1[0];
		z1[0] = 0;
		Pos[0][0] = x1[0];
		Pos[0][1] = Y1[0];
		Pos[0][2] = z1[0];
		Rect[0] = 0;
		t = 0;
		rad = 0;
		clockc = true;
	}
	glClearColor(r, g, b, 1.0f);
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
	

	if (t <= cycle  && clockc)
	{
		t += 0.05;
		if (t > cycle )
			clockc = false;
	}
	if (t >= 0 && !clockc)
	{
		t -= 0.05;
	}


	if(rad<=20)
		rad += 0.01;
	cout << t << endl;

	glutPostRedisplay(); // ȭ�� �� ���
	glutTimerFunc(10, TimerFunction, 1); // Ÿ�̸��Լ� �� ����
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
	glGenBuffers(1, &PosVbo[0]);
	glBindBuffer(GL_ARRAY_BUFFER, PosVbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Pos), Pos, GL_DYNAMIC_DRAW);
	glGenBuffers(1, &ColorVbo);
	glBindBuffer(GL_ARRAY_BUFFER, ColorVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Poscolor), Poscolor, GL_STATIC_DRAW);
}