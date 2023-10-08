#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include<cstdlib>
#include<ctime>
#include <gl/glew.h> //--- 필요한 헤더파일 include
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
GLuint shaderProgramID; //--- 세이더 프로그램 이름
GLuint vertexShader; //--- 버텍스 세이더 객체
GLuint fragmentShader; //--- 프래그먼트 세이더 객체







void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정 
{
	//--- 윈도우 생성하기
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Example1");
	//--- GLEW 초기화하기
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

GLvoid drawScene() //--- 콜백 함수: 그리기 콜백 함수
{
	GLfloat rColor, gColor, bColor;
	rColor = gColor = 0.0;
	bColor = 0.0;
	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(shaderProgramID);
	glBindVertexArray(vao);





	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position"); //	: 0  Shader의 'layout (location = 0)' 부분
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color"); //	: 1

	glEnableVertexAttribArray(PosLocation); // Enable 필수! 사용하겠단 의미
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
	
	
	


	glDisableVertexAttribArray(PosLocation); // Disable 필수!
	glDisableVertexAttribArray(ColorLocation);


	glutSwapBuffers();
	glutPostRedisplay();
}


GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수
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

	glutPostRedisplay(); // 화면 재 출력
	glutTimerFunc(10, TimerFunction, 1); // 타이머함수 재 설정
}


GLchar* vertexSource, * fragmentSource; //--- 소스코드 저장 변수

void make_vertexShaders()
{
	vertexSource = filetobuf("vertex.glsl");
	//--- 버텍스 세이더 객체 만들기
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//--- 세이더 코드를 세이더 객체에 넣기
	glShaderSource(vertexShader, 1, (const GLchar**)&vertexSource, 0);
	//--- 버텍스 세이더 컴파일하기
	glCompileShader(vertexShader);
	//--- 컴파일이 제대로 되지 않은 경우: 에러 체크
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		cerr << "ERROR: vertex shader 컴파일 실패\n" << errorLog << endl;
		return;
	}
}

void make_fragmentShaders()
{
	fragmentSource = filetobuf("fragment.glsl");
	//--- 프래그먼트 세이더 객체 만들기
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//--- 세이더 코드를 세이더 객체에 넣기
	glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentSource, 0);
	//--- 프래그먼트 세이더 컴파일
	glCompileShader(fragmentShader);
	//--- 컴파일이 제대로 되지 않은 경우: 컴파일 에러 체크
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		cerr << "ERROR: fragment shader 컴파일 실패\n" << errorLog << endl;
		return;
	}
}


void make_shaderProgram()
{
	make_vertexShaders(); //--- 버텍스 세이더 만들기
	make_fragmentShaders(); //--- 프래그먼트 세이더 만들기
	//-- shader Program
	shaderProgramID = glCreateProgram();
	glAttachShader(shaderProgramID, vertexShader);
	glAttachShader(shaderProgramID, fragmentShader);
	glLinkProgram(shaderProgramID);
	//--- 세이더 삭제하기
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	//--- Shader Program 사용하기
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