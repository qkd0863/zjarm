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
void ReformatPenta(float h);
void ReformatLine(float h);
void ReformatTri(float h);
void ReformatRect(float h);


bool Line = true, Tri = true, Rect = true, Penta = true;
double x1[5], Y1[5], z1[5];
float rad = 3.141592 / 180.0;
float rx = 0, ry = 0;
char shape = 'a';


GLfloat lineShape[2][3] = { { 0.1, 0.1, 0.0},{ -0.1, -0.1, 0.0 } };

GLfloat triShape[3][3] = { { -0.1, -0.1, 0.0 }, { 0.0, 0.1, 0.0 }, { 0.1, -0.1, 0.0} };
GLfloat changetriShape[3][3] = { { 0.1, 0.1, 0.0 }, { -0.1, -0.1, 0.0 }, { 0.0, 0.01, 0.0} };









GLfloat RectShape[6][3] = {
{ -0.1, -0.1, 0.0 }, { -0.1, 0.1, 0.0 }, { 0.1, -0.1, 0.0},
{ -0.1, 0.1, 0.0 }, { 0.1, 0.1, 0.0}, { 0.1, -0.1, 0.0}
};
GLfloat changeRectShape[6][3] = {
{ -0.1, -0.1, 0.0 }, { 0.0, 0.1, 0.0 }, { 0.1, -0.1, 0.0},
{ 0.0, 0.1, 0.0 }, { 0.1, -0.1, 0.0}, { 0.01, 0.1, 0.0 }
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
GLfloat changePentagonShape[9][3] = {

	{ 0.0, 0.1, 0.0},
	{ -0.1, 0.1, 0.0},
	{ -0.1, -0.1, 0.0},

	{0.0, 0.1, 0.0},
	{-0.1, -0.1, 0.0},
	{0.1, -0.1, 0.0},

	{0.0, 0.1, 0.0},
	{0.1, -0.1, 0.0},
	{0.1, 0.1, 0.0}
};



const GLfloat colors1[6][3] = { { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 1.0 } };




const GLfloat Poscolor[3] = { 1.0,0.0,1.0 };
const GLfloat linecolor[2][3] = { {0.0,0.0,0.0},{0.0,0.0,0.0 } };
const GLfloat tricolor[6][3] = { {0.0,1.0,0.0},{0.0,1.0,0.0 } ,{0.0,1.0,0.0 } ,{0.0,1.0,0.0},{0.0,1.0,0.0 } ,{0.0,1.0,0.0 } };
const GLfloat rectcolors[9][3] = {
{ 1.0, 1.0, 0.0 }, { 1.0, 1.0, 0.0 }, { 1.0, 1.0, 0.0 },
{ 1.0, 1.0, 0.0 }, { 1.0, 1.0, 0.0 }, { 1.0, 1.0, 0.0 },
{ 1.0, 1.0, 0.0 }, { 1.0, 1.0, 0.0 }, { 1.0, 1.0, 0.0 }};
const GLfloat PenColors[9][3] = {
{ 1.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 },
{ 1.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 },
{ 1.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 } };



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
	glutTimerFunc(100, TimerFunction, 1);
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





	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position"); //	: 0  Shader의 'layout (location = 0)' 부분
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color"); //	: 1

	glEnableVertexAttribArray(PosLocation); // Enable 필수! 사용하겠단 의미
	glEnableVertexAttribArray(ColorLocation);

	GLuint changePos = glGetUniformLocation(shaderProgramID, "Pos");




	glUniform2f(changePos, LinePos[0][0], LinePos[0][1]);
	glBindBuffer(GL_ARRAY_BUFFER, linePosVbo); // VBO Bind
	glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	{
		glBindBuffer(GL_ARRAY_BUFFER, lineColorVbo); // VBO Bind
		glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	}
	if(Line)
		glDrawArrays(GL_LINES, 0, 3);
	else
		glDrawArrays(GL_TRIANGLES, 0, 3);
	
	




	glUniform2f(changePos, triPos[0][0], triPos[0][1]);
	glBindBuffer(GL_ARRAY_BUFFER, triPosVbo); // VBO Bind
	glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	{
		glBindBuffer(GL_ARRAY_BUFFER, triColor); // VBO Bind
		glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	}
	if(Tri)
		glDrawArrays(GL_TRIANGLES, 0, 3);
	else
		glDrawArrays(GL_TRIANGLES, 0, 6);





	glUniform2f(changePos, rectPos[0][0], rectPos[0][1]);
	glBindBuffer(GL_ARRAY_BUFFER, rectPosVbo); // VBO Bind
	glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	{
		glBindBuffer(GL_ARRAY_BUFFER, rectColor); // VBO Bind
		glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	}
	if (Rect)
		glDrawArrays(GL_TRIANGLES, 0, 6);
	else
		glDrawArrays(GL_TRIANGLES, 0, 9);




	glUniform2f(changePos, PentaPos[0][0], PentaPos[0][1]);
	glBindBuffer(GL_ARRAY_BUFFER, PenPosVbo); // VBO Bind
	glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	{
		glBindBuffer(GL_ARRAY_BUFFER, PenColor); // VBO Bind
		glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	}
	glDrawArrays(GL_TRIANGLES, 0, 9);



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
	case 'l':
		Line = false;
		break;
	case 't':
		Tri = false;
		break;
	case 'r':
		Rect = false;
		break;
	case 'p':
		Penta = false;
		break;
	case 'a':
		Line = true;
		Tri = true;
		Rect = true;
		Penta = true;
		ReformatPenta(0.2);
		break;
	case 'q':
		exit(1);
		break;
	}

	InitBuffer();
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
		x1[0] = Wx;
		Y1[0] = Wy;
		z1[0] = 0;
		PentaPos[0][0] = Wx;
		PentaPos[0][1] = Wy;
		PentaPos[0][2] = 0;
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
	cout << sin(rad*90) << endl;
	static float h = 0.2;




	
	
	if(!Line)
		ReformatLine(0.01);
	if (!Tri)
		ReformatTri(0.01);
	if (!Rect)
		ReformatRect(0.01);


	if (!Penta)
	{
		if (h > 0.01)
		{
			ReformatPenta(h);
			h -= 0.005;
		}
	}
	InitBuffer();
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
	if (Line)
	{
		glGenBuffers(1, &linePosVbo);
		glBindBuffer(GL_ARRAY_BUFFER, linePosVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(lineShape), lineShape, GL_DYNAMIC_DRAW);
		glGenBuffers(1, &lineColorVbo);
		glBindBuffer(GL_ARRAY_BUFFER, lineColorVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(linecolor), linecolor, GL_STATIC_DRAW);
	}
	else
	{
		glGenBuffers(1, &linePosVbo);
		glBindBuffer(GL_ARRAY_BUFFER, linePosVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(changetriShape), changetriShape, GL_DYNAMIC_DRAW);
		glGenBuffers(1, &lineColorVbo);
		glBindBuffer(GL_ARRAY_BUFFER, lineColorVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(linecolor), linecolor, GL_STATIC_DRAW);
	}
	


	if (Tri)
	{
		glGenBuffers(1, &triPosVbo);
		glBindBuffer(GL_ARRAY_BUFFER, triPosVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(triShape), triShape, GL_DYNAMIC_DRAW);
		glGenBuffers(1, &triColor);
		glBindBuffer(GL_ARRAY_BUFFER, triColor);
		glBufferData(GL_ARRAY_BUFFER, sizeof(tricolor), tricolor, GL_STATIC_DRAW);
	}
	else
	{
		glGenBuffers(1, &triPosVbo);
		glBindBuffer(GL_ARRAY_BUFFER, triPosVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(changeRectShape), changeRectShape, GL_DYNAMIC_DRAW);
		glGenBuffers(1, &triColor);
		glBindBuffer(GL_ARRAY_BUFFER, triColor);
		glBufferData(GL_ARRAY_BUFFER, sizeof(tricolor), tricolor, GL_STATIC_DRAW);
	}
	


	if (Rect)
	{
		glGenBuffers(1, &rectPosVbo);
		glBindBuffer(GL_ARRAY_BUFFER, rectPosVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(RectShape), RectShape, GL_DYNAMIC_DRAW);
		glGenBuffers(1, &rectColor);
		glBindBuffer(GL_ARRAY_BUFFER, rectColor);
		glBufferData(GL_ARRAY_BUFFER, sizeof(rectcolors), rectcolors, GL_STATIC_DRAW);
	}
	else
	{
		glGenBuffers(1, &rectPosVbo);
		glBindBuffer(GL_ARRAY_BUFFER, rectPosVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(changePentagonShape), changePentagonShape, GL_DYNAMIC_DRAW);
		glGenBuffers(1, &rectColor);
		glBindBuffer(GL_ARRAY_BUFFER, rectColor);
		glBufferData(GL_ARRAY_BUFFER, sizeof(rectcolors), rectcolors, GL_STATIC_DRAW);
	}
	





	glGenBuffers(1, &PenPosVbo);
	glBindBuffer(GL_ARRAY_BUFFER, PenPosVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(PentagonShape), PentagonShape, GL_DYNAMIC_DRAW);
	glGenBuffers(1, &PenColor);
	glBindBuffer(GL_ARRAY_BUFFER, PenColor);
	glBufferData(GL_ARRAY_BUFFER, sizeof(PenColors), PenColors, GL_STATIC_DRAW);
}






void ReformatPenta(float h)
{
	PentagonShape[0][0] = h * cos(90 * rad);PentagonShape[0][1] = h * sin(90 * rad);
	PentagonShape[1][0] = h * cos(90 * rad + 72 * rad);PentagonShape[1][1] = h * sin(90 * rad + 72 * rad);
	PentagonShape[2][0] = h * cos(90 * rad + 72 * rad * 2);PentagonShape[2][1] = h * sin(90 * rad + 72 * rad * 2);

	PentagonShape[3][0] = h * cos(90 * rad);PentagonShape[3][1] = h * sin(90 * rad);
	PentagonShape[4][0] = h * cos(90 * rad + 72 * rad * 2);PentagonShape[4][1] = h * sin(90 * rad + 72 * rad * 2);
	PentagonShape[5][0] = h * cos(90 * rad + 72 * rad * 3);PentagonShape[5][1] = h * sin(90 * rad + 72 * rad * 3);

	PentagonShape[6][0] = h * cos(90 * rad);PentagonShape[6][1] = h * sin(90 * rad);
	PentagonShape[7][0] = h * cos(90 * rad + 72 * rad * 3);PentagonShape[7][1] = h * sin(90 * rad + 72 * rad * 3);
	PentagonShape[8][0] = h * cos(90 * rad + 72 * rad * 4);PentagonShape[8][1] = h * sin(90 * rad + 72 * rad * 4);
}
void ReformatLine(float h)
{
	if (changetriShape[0][1] > -0.1)
	{
		changetriShape[0][1] -= h;
	}
	if (changetriShape[0][1] < -0.1)
	{
		changetriShape[0][1] = -0.1;
	}

	
	if (changetriShape[2][1] < 0.1)
	{
		changetriShape[2][1] += h;
	}
}
void ReformatTri(float h)
{
	if (changeRectShape[1][0] > -0.1)
		changeRectShape[1][0] -= h;
	else
		changeRectShape[1][0] = -0.1;
	
	if (changeRectShape[3][0] > -0.1)
		changeRectShape[3][0] -= h;
	else
		changeRectShape[3][0] = -0.1;
	
	if (changeRectShape[5][0] < 0.1)
		changeRectShape[5][0] += h;
	else
		changeRectShape[5][0] = 0.1;
}
void ReformatRect(float h)
{
	if(changePentagonShape[0][1]< 0.2 * sin(90 * rad))
		changePentagonShape[0][1] += h;
	

	if (changePentagonShape[1][0] > 0.2 * cos(90 * rad + 72 * rad))
		changePentagonShape[1][0] -= h;
	if (changePentagonShape[1][1] > 0.2 * sin(90 * rad + 72 * rad))
		changePentagonShape[1][1] -= h;
	

	if (changePentagonShape[2][0] < 0.2 * cos(90 * rad + 72 * rad * 2))
		changePentagonShape[2][0] += h;
	if (changePentagonShape[2][1] > 0.2 * sin(90 * rad + 72 * rad * 2))
		changePentagonShape[2][1] -= h;






	if (changePentagonShape[3][1] < 0.2 * sin(90 * rad))
		changePentagonShape[3][1] += h;


	if (changePentagonShape[4][0] < 0.2 * cos(90 * rad + 72 * rad * 2))
		changePentagonShape[4][0] += h;
	if (changePentagonShape[4][1] > 0.2 * sin(90 * rad + 72 * rad * 2))
		changePentagonShape[4][1] -= h;


	if (changePentagonShape[5][0] > 0.2 * cos(90 * rad + 72 * rad * 3))
		changePentagonShape[5][0] -= h;
	if (changePentagonShape[5][1] > 0.2 * sin(90 * rad + 72 * rad * 3))
		changePentagonShape[5][1] -= h;




		
	if (changePentagonShape[6][1] < 0.2 * sin(90 * rad))
		changePentagonShape[6][1] += h;


	if (changePentagonShape[7][0] > 0.2 * cos(90 * rad + 72 * rad * 3))
		changePentagonShape[7][0] -= h;
	if (changePentagonShape[7][1] > 0.2 * sin(90 * rad + 72 * rad * 3))
		changePentagonShape[7][1] -= h;


	if (changePentagonShape[8][0] < 0.2 * cos(90 * rad + 72 * rad * 4))
		changePentagonShape[8][0] += h;
	if (changePentagonShape[8][1] > 0.2 * sin(90 * rad + 72 * rad * 4))
		changePentagonShape[8][1] -= h;
}	  