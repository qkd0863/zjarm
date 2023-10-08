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
char shape = 'a';


GLfloat lineShape1[2][3] = { { -0.1, -0.1, 0.0 }, { 0, 0.1, 0.0 } };
GLfloat lineShape2[2][3] = { { 0, 0.1, 0.0 }, { 0.1, -0.1, 0.0} };

GLfloat lineShape3[2][3] = { { -0.1, -0.1, 0.0 }, { 0, 0.1, 0.0 } };
GLfloat lineShape4[2][3] = { { 0, 0.1, 0.0 }, { 0.1, -0.1, 0.0} };

GLfloat lineShape5[2][3] = { { -0.1, -0.1, 0.0 }, { 0, 0.1, 0.0 } };
GLfloat lineShape6[2][3] = { { 0, 0.1, 0.0 }, { 0.1, -0.1, 0.0} };

GLfloat lineShape7[2][3] = { { -0.1, -0.1, 0.0 }, { 0, 0.1, 0.0 } };
GLfloat lineShape8[2][3] = { { 0, 0.1, 0.0 }, { 0.1, -0.1, 0.0} };

const GLfloat lineShape[2][3] = { { 0.1, -0.1, 0.0},{ -0.1, -0.1, 0.0 } };

GLfloat triShape1[3][3] = { { -0.1, -0.1, 0.0 }, { 0, 0.1, 0.0 }, { 0.1, -0.1, 0.0} };
GLfloat triShape2[3][3] = { { -0.1, -0.1, 0.0 }, { 0, 0.1, 0.0 }, { 0.1, -0.1, 0.0} };
GLfloat triShape3[3][3] = { { -0.1, -0.1, 0.0 }, { 0, 0.1, 0.0 }, { 0.1, -0.1, 0.0} };
GLfloat triShape4[3][3] = { { -0.1, -0.1, 0.0 }, { 0, 0.1, 0.0 }, { 0.1, -0.1, 0.0} };

const GLfloat RectShape[6][3] = { { -0.2, -0.2, 0.0 }, { -0.2, 0.2, 0.0 }, { 0.2, -0.2, 0.0},
{ -0.2, 0.2, 0.0 },{0.2,0.2,0.0},{0.2,-0.2,0.0}
};

const GLfloat colors1[6][3] = { { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 1.0 } };
const GLfloat colors2[6][3] = { { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 1.0, 0.0, 0.0 } };
const GLfloat colors3[6][3] = { { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 1.0, 0.0 } };
const GLfloat colors4[6][3] = { { 1.0, 1.0, 0.0 }, { 0.0, 1.0, 1.0 }, { 1.0, 0.0, 1.0 } };

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
	glutMainLoop();
}

GLvoid drawScene() //--- 콜백 함수: 그리기 콜백 함수
{
	GLfloat rColor, gColor, bColor;
	rColor = gColor = 0.0;
	bColor = 0.0;
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(shaderProgramID);
	glBindVertexArray(vao);

	



	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position"); //	: 0  Shader의 'layout (location = 0)' 부분
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color"); //	: 1

	glEnableVertexAttribArray(PosLocation); // Enable 필수! 사용하겠단 의미
	glEnableVertexAttribArray(ColorLocation);

	GLuint changePos = glGetUniformLocation(shaderProgramID, "Pos");





	if (shape == 'a')
	{
		for (int i = 0; i < 4; ++i)
		{
			if (Rect[i] == 1)
			{
				glUniform2f(changePos, triPos[i][0], triPos[i][1]);
				glBindBuffer(GL_ARRAY_BUFFER, triPosVbo[i]); // VBO Bind
				glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
				{
					glBindBuffer(GL_ARRAY_BUFFER, triColor[i]); // VBO Bind
					glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
				}
				glDrawArrays(GL_TRIANGLES, 0, 3);
			}
		}
	}
	else
	{
		for (int i = 0; i < 4; ++i)
		{
			if (Rect[i] == 1)
			{
				glUniform2f(changePos, LinePos1[i][0], LinePos1[i][1]);
				glBindBuffer(GL_ARRAY_BUFFER, linePosVbo1[i]); // VBO Bind
				glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
				{
					glBindBuffer(GL_ARRAY_BUFFER, triColor[0]); // VBO Bind
					glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
				}
				glDrawArrays(GL_LINES, 0, 2);
			}
		}
		for (int i = 0; i < 4; ++i)
		{
			if (Rect[i] == 1)
			{
				glUniform2f(changePos, LinePos2[i][0], LinePos2[i][1]);
				glBindBuffer(GL_ARRAY_BUFFER, linePosVbo2[i]); // VBO Bind
				glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
				{
					glBindBuffer(GL_ARRAY_BUFFER, triColor[1]); // VBO Bind
					glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
				}
				glDrawArrays(GL_LINES, 0, 2);
			}
		}
		for (int i = 0; i < 4; ++i)
		{
			if (Rect[i] == 1)
			{
				glUniform2f(changePos, LinePos3[i][0], LinePos3[i][1]);
				glBindBuffer(GL_ARRAY_BUFFER, linePosVbo3[i]); // VBO Bind
				glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
				{
					glBindBuffer(GL_ARRAY_BUFFER, triColor[2]); // VBO Bind
					glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
				}
				glDrawArrays(GL_LINES, 0, 2);
			}
		}
	}
	


	glDisableVertexAttribArray(PosLocation); // Disable 필수!
	glDisableVertexAttribArray(ColorLocation);


	glUniform2f(changePos, 0, 0);
	glColor3f(0, 0, 0);
	glRectf(-1.0, 0.0 + 0.01, 1.0, 0.0 - 0.01);
	glRectf(0.0 + 0.01, 1.0, 0.0 - 0.01, -1.0);

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
	
	int n = rand() % 3 - 1;

	while (n == 0)
	{
		n = rand() % 3 - 1;
	}
		

	convert(x, y, &Wx, &Wy);
	convert(x, y, &Rx, &Ry);


	ry = (rand() % 10) / 500.0 * n;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (Wx > 0 && Wy > 0) //1사분면
		{
			x1[0] = Wx;
			Y1[0] = Wy;
			std::cout << std::endl << x1[0] << Y1[0] << '\t' << rx;
			triPos[0][0] = x1[0];
			triPos[0][1] = Y1[0];
			Rect[0] = 1;
			triShape1[1][1] += ry;



			LinePos1[0][0] = x1[0];
			LinePos1[0][1] = Y1[0];
			LinePos2[0][0] = x1[0];
			LinePos2[0][1] = Y1[0];
			LinePos3[0][0] = x1[0];
			LinePos3[0][1] = Y1[0];

			lineShape1[1][1] += ry;
			lineShape2[0][1] += ry;
		}
		if (Wx <= 0 && Wy > 0)//2사분면
		{
			x1[1] = Wx;
			Y1[1] = Wy;
			std::cout << std::endl << x1[1] << Y1[1];
			triPos[1][0] = x1[1];
			triPos[1][1] = Y1[1];
			Rect[1] = 1;
			triShape2[1][1] += ry;


			LinePos1[1][0] = x1[1];
			LinePos1[1][1] = Y1[1];
			LinePos2[1][0] = x1[1];
			LinePos2[1][1] = Y1[1];
			LinePos3[1][0] = x1[1];
			LinePos3[1][1] = Y1[1];

			lineShape3[1][1] += ry;
			lineShape4[0][1] += ry;
		}
		if (Wx <= 0 && Wy <= 0)//3사분면
		{
			x1[2] = Wx;
			Y1[2] = Wy;
			std::cout << std::endl << x1[2] << Y1[2];
			triPos[2][0] = x1[2];
			triPos[2][1] = Y1[2];
			Rect[2] = 1;
			triShape3[1][1] += ry;


			LinePos1[2][0] = x1[2];
			LinePos1[2][1] = Y1[2];
			LinePos2[2][0] = x1[2];
			LinePos2[2][1] = Y1[2];
			LinePos3[2][0] = x1[2];
			LinePos3[2][1] = Y1[2];

			lineShape5[1][1] += ry;
			lineShape6[0][1] += ry;
		}
		if (Wx > 0 && Wy <= 0)//4사분면
		{
			x1[3] = Wx;
			Y1[3] = Wy;
			std::cout << std::endl << x1[3] << Y1[3];
			triPos[3][0] = x1[3];
			triPos[3][1] = Y1[3];
			Rect[3] = 1;
			triShape4[1][1] += ry;


			LinePos1[3][0] = x1[3];
			LinePos1[3][1] = Y1[3];
			LinePos2[3][0] = x1[3];
			LinePos2[3][1] = Y1[3];
			LinePos3[3][0] = x1[3];
			LinePos3[3][1] = Y1[3];

			lineShape7[1][1] += ry;
			lineShape8[0][1] += ry;
		}
	}
	
	InitBuffer();
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


	glutPostRedisplay(); // 화면 재 출력
	glutTimerFunc(100, TimerFunction, 1); // 타이머함수 재 설정
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
	glGenBuffers(1, &triPosVbo[0]);
	glBindBuffer(GL_ARRAY_BUFFER, triPosVbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triShape1), triShape1, GL_DYNAMIC_DRAW);
	glGenBuffers(1, &triColor[0]);
	glBindBuffer(GL_ARRAY_BUFFER, triColor[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors1), colors1, GL_STATIC_DRAW);

	glGenBuffers(1, &triPosVbo[1]);
	glBindBuffer(GL_ARRAY_BUFFER, triPosVbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triShape2), triShape2, GL_DYNAMIC_DRAW);
	glGenBuffers(1, &triColor[1]);
	glBindBuffer(GL_ARRAY_BUFFER, triColor[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors2), colors2, GL_STATIC_DRAW);

	glGenBuffers(1, &triPosVbo[2]);
	glBindBuffer(GL_ARRAY_BUFFER, triPosVbo[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triShape3), triShape3, GL_DYNAMIC_DRAW);
	glGenBuffers(1, &triColor[2]);
	glBindBuffer(GL_ARRAY_BUFFER, triColor[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors3), colors3, GL_STATIC_DRAW);

	glGenBuffers(1, &triPosVbo[3]);
	glBindBuffer(GL_ARRAY_BUFFER, triPosVbo[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triShape4), triShape4, GL_DYNAMIC_DRAW);
	glGenBuffers(1, &triColor[3]);
	glBindBuffer(GL_ARRAY_BUFFER, triColor[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors4), colors4, GL_STATIC_DRAW);








	glGenBuffers(1, &linePosVbo1[0]);
	glBindBuffer(GL_ARRAY_BUFFER, linePosVbo1[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lineShape1), lineShape1, GL_DYNAMIC_DRAW);
	glGenBuffers(1, &triColor[0]);
	glBindBuffer(GL_ARRAY_BUFFER, triColor[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors1), colors1, GL_STATIC_DRAW);

	glGenBuffers(1, &linePosVbo2[0]);
	glBindBuffer(GL_ARRAY_BUFFER, linePosVbo2[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lineShape2), lineShape2, GL_DYNAMIC_DRAW);
	glGenBuffers(1, &triColor[0]);
	glBindBuffer(GL_ARRAY_BUFFER, triColor[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors1), colors1, GL_STATIC_DRAW);



	glGenBuffers(1, &linePosVbo1[1]);
	glBindBuffer(GL_ARRAY_BUFFER, linePosVbo1[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lineShape3), lineShape3, GL_DYNAMIC_DRAW);
	glGenBuffers(1, &triColor[0]);
	glBindBuffer(GL_ARRAY_BUFFER, triColor[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors1), colors1, GL_STATIC_DRAW);

	glGenBuffers(1, &linePosVbo2[1]);
	glBindBuffer(GL_ARRAY_BUFFER, linePosVbo2[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lineShape4), lineShape4, GL_DYNAMIC_DRAW);
	glGenBuffers(1, &triColor[0]);
	glBindBuffer(GL_ARRAY_BUFFER, triColor[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors1), colors1, GL_STATIC_DRAW);



	glGenBuffers(1, &linePosVbo1[2]);
	glBindBuffer(GL_ARRAY_BUFFER, linePosVbo1[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lineShape5), lineShape5, GL_DYNAMIC_DRAW);
	glGenBuffers(1, &triColor[0]);
	glBindBuffer(GL_ARRAY_BUFFER, triColor[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors1), colors1, GL_STATIC_DRAW);

	glGenBuffers(1, &linePosVbo2[2]);
	glBindBuffer(GL_ARRAY_BUFFER, linePosVbo2[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lineShape6), lineShape6, GL_DYNAMIC_DRAW);
	glGenBuffers(1, &triColor[0]);
	glBindBuffer(GL_ARRAY_BUFFER, triColor[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors1), colors1, GL_STATIC_DRAW);



	glGenBuffers(1, &linePosVbo1[3]);
	glBindBuffer(GL_ARRAY_BUFFER, linePosVbo1[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lineShape7), lineShape7, GL_DYNAMIC_DRAW);
	glGenBuffers(1, &triColor[0]);
	glBindBuffer(GL_ARRAY_BUFFER, triColor[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors1), colors1, GL_STATIC_DRAW);

	glGenBuffers(1, &linePosVbo2[3]);
	glBindBuffer(GL_ARRAY_BUFFER, linePosVbo2[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lineShape8), lineShape8, GL_DYNAMIC_DRAW);
	glGenBuffers(1, &triColor[0]);
	glBindBuffer(GL_ARRAY_BUFFER, triColor[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors1), colors1, GL_STATIC_DRAW);





	for (int i = 0;i < 4;i++)
	{
		glGenBuffers(1, &linePosVbo3[i]);
		glBindBuffer(GL_ARRAY_BUFFER, linePosVbo3[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(lineShape), lineShape, GL_DYNAMIC_DRAW);
		glGenBuffers(1, &triColor[2]);
		glBindBuffer(GL_ARRAY_BUFFER, triColor[2]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors2), colors2, GL_STATIC_DRAW);
	}
}