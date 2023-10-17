#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include<cstdlib>
#include<ctime>
#include <gl/glew.h> //--- �ʿ��� ������� include
#include<gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>

using namespace std;



struct sel
{
	bool c0 = true;
	bool c1 = false;
	bool c2 = false;
	bool c3 = false;
	bool c4 = false;
	bool c5 = false;
	bool c6 = false;

	bool t0 = false;
	bool t1 = false;
	bool t2 = false;
	bool t3 = false;
	bool t4 = false;
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
void ReadObj(FILE* path);
void set();
void resetS(sel* S);


double x1[5], Y1[5], z1[5];
float mx = 0, my = 0;
float X = 20, Y = -20;
bool left_button;
bool c1 = false, c2 = false, c3 = false, c4 = false, rect = false;


GLfloat lineShape1[2][3] = { { -0.1, 0.1, 0.0},{ 0.1, 0.1, 0.0 } };
GLfloat lineShape2[2][3] = { { 0.1, 0.1, 0.0},{ 0.1, -0.1, 0.0 } };
GLfloat lineShape3[2][3] = { { 0.1, -0.1, 0.0},{ -0.1, -0.1, 0.0 } };
GLfloat lineShape4[2][3] = { { -0.1, -0.1, 0.0},{ -0.1, 0.1, 0.0 } };

GLfloat triShape[3][3] = { { -0.1, -0.1, 0.0 }, { 0.0, 0.1, 0.0 }, { 0.1, -0.1, 0.0} };

GLfloat RectShape[6][3] = {
{ -0.1, -0.1, 0.0 }, { -0.1, 0.1, 0.0 }, { 0.1, -0.1, 0.0},
{ -0.1, 0.1, 0.0 }, { 0.1, 0.1, 0.0}, { 0.1, -0.1, 0.0}
};
GLfloat HexahedronShape[36][3];
GLfloat HexahedronColors[36][3];
GLfloat TetrahedronShape[12][3];
GLfloat TetrahedronColors[12][3];

const GLfloat colors1[6][3] = { { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 1.0 } };




const GLfloat Poscolor[3] = { 1.0,0.0,1.0 };
const GLfloat linecolor[2][3] = { {1.0,0.0,0.0},{0.0,1.0,0.0 } };
const GLfloat tricolor[6][3] = { {0.0,1.0,0.0},{0.0,1.0,0.0 } ,{0.0,1.0,0.0 } ,{0.0,1.0,0.0},{0.0,1.0,0.0 } ,{0.0,1.0,0.0 } };
const GLfloat rectcolors[9][3] = {
{ 1.0, 1.0, 0.0 }, { 1.0, 1.0, 0.0 }, { 1.0, 1.0, 0.0 },
{ 1.0, 1.0, 0.0 }, { 1.0, 1.0, 0.0 }, { 1.0, 1.0, 0.0 },
{ 1.0, 1.0, 0.0 }, { 1.0, 1.0, 0.0 }, { 1.0, 1.0, 0.0 } };
const GLfloat PenColors[9][3] = {
{ 1.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 },
{ 1.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 },
{ 1.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 } };



GLfloat PentaPos[5][3] = { {0.5,-0.5,0.0} };
GLfloat Pos[5][3] = { 0, };
GLfloat TriPos[5][3] = { {0.5,0.5,0.0} };
GLfloat RectPos[5][3] = { {-0.5,-0.5,0.0} };
GLfloat LinePos[5][3] = { 0, };


GLuint linePosVbo[4], lineColorVbo[4];
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
	
	//--- ������ �����ϱ�
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
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
	FILE* ptr = fopen("diamond.obj", "r");
	ReadObj(ptr);
	set();
	glutMainLoop();
}

GLUquadricObj* qobj;
sel S;

GLvoid drawScene() //--- �ݹ� �Լ�: �׸��� �ݹ� �Լ�
{
	GLfloat rColor, gColor, bColor;
	rColor = gColor = 0.0;
	bColor = 0.0;
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glEnable(GL_DEPTH_TEST);

	glUseProgram(shaderProgramID);




	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position"); //	: 0  Shader�� 'layout (location = 0)' �κ�
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color"); //	: 1

	glEnableVertexAttribArray(PosLocation); // Enable �ʼ�! ����ϰڴ� �ǹ�
	glEnableVertexAttribArray(ColorLocation);


	glm::mat4 a = glm::mat4(1.0f);
	glm::mat4 model = glm::mat4(1.0f);	
	glm::mat4 model2 = glm::mat4(1.0f);
	glm::mat4 model3 = glm::mat4(1.0f);
	GLuint changePos = glGetUniformLocation(shaderProgramID, "Pos");

	a = glm::scale(a, glm::vec3(0.5, 2.0, 1.0));
	model = glm::rotate(model, glm::radians(X), glm::vec3(1.0, 0.0, 0.0));
	model2 = glm::rotate(model2, glm::radians(Y), glm::vec3(0.0, 1.0, 0.0));
	model3 = model * model2;
	
	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "transform");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model3));



	if (S.c0 || S.c1 || S.c2 || S.c3 || S.c4 || S.c5 || S.c6)
	{
		glBindBuffer(GL_ARRAY_BUFFER, TriPosVbo); // VBO Bind
		glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		{
			glBindBuffer(GL_ARRAY_BUFFER, TriColorVbo); // VBO Bind
			glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		}
	}
	
	
	if (S.t0 || S.t1 || S.t2 || S.t3 || S.t4)
	{
		glBindBuffer(GL_ARRAY_BUFFER, rectPosVbo); // VBO Bind
		glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		{
			glBindBuffer(GL_ARRAY_BUFFER, rectColor); // VBO Bind
			glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		}

		
	}




	
	if (S.c0)
	{
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	else
	{
		if (S.c1)
		{
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
		if (S.c2)
		{
			glDrawArrays(GL_TRIANGLES, 6, 6);
		}
		if (S.c3)
		{
			glDrawArrays(GL_TRIANGLES, 12, 6);
		}
		if (S.c4)
		{
			glDrawArrays(GL_TRIANGLES, 18, 6);
		}
		if (S.c5)
		{
			glDrawArrays(GL_TRIANGLES, 24, 6);
		}
		if (S.c6)
		{
			glDrawArrays(GL_TRIANGLES, 30, 6);
		}

	}
	

	if (S.t0)
	{
		glDrawArrays(GL_TRIANGLES, 0, 12);
	}
	else
	{
		if (S.t1)
		{
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
		if (S.t2)
		{
			glDrawArrays(GL_TRIANGLES, 3, 3);
		}
		if (S.t3)
		{
			glDrawArrays(GL_TRIANGLES, 6, 3);
		}
		if (S.t4)
		{
			glDrawArrays(GL_TRIANGLES, 9, 3);
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
	int a = -1, b = -1;
	

	switch (key)
	{
	case 'x':
		X+=3;
		break;
	case 'y':
		Y+=3;
		break;
	case 'r':
		S.c0 = true;
		break;
	case '1':
		resetS(&S);
		S.c1 = true;
		break;
	case '2':
		resetS(&S);
		S.c2 = true;
		break;
	case '3':
		resetS(&S);
		S.c3 = true;
		break;
	case '4':
		resetS(&S);
		S.c4 = true;
		break;
	case '5':
		resetS(&S);
		S.c5 = true;
		break;
	case '6':
		resetS(&S);
		S.c6 = true;
		break;
	case '7':
		resetS(&S);
		S.t1 = true;
		break;
	case '8':
		resetS(&S);
		S.t2 = true;
		break;
	case '9':
		resetS(&S);
		S.t3 = true;
		break;
	case '0':
		resetS(&S);
		S.t4 = true;
		break;
	case 'c':
		resetS(&S);
		a = rand() % 6 + 1;
		b = rand() % 6 + 1;
		while (a == b)
		{
			b = rand() % 6 + 1;
		}
		switch (a)
		{
		case 1:
			S.c1 = true;
			break;
		case 2:
			S.c2 = true;
			break;
		case 3:
			S.c3 = true;
			break;
		case 4:
			S.c4 = true;
			break;
		case 5:
			S.c5 = true;
			break;
		case 6:
			S.c6 = true;
			break;
		default:
			break;
		}
		switch (b)
		{
		case 1:
			S.c1 = true;
			break;
		case 2:
			S.c2 = true;
			break;
		case 3:
			S.c3 = true;
			break;
		case 4:
			S.c4 = true;
			break;
		case 5:
			S.c5 = true;
			break;
		case 6:
			S.c6 = true;
			break;
		default:
			break;
		}
		break;
	case 't':
		resetS(&S);
		a = rand() % 4 + 1;
		b = rand() % 4 + 1;
		while (a == b)
		{
			b = rand() % 4 + 1;
		}
		switch (a)
		{
		case 1:
			S.t1 = true;
			break;
		case 2:
			S.t2 = true;
			break;
		case 3:
			S.t3 = true;
			break;
		case 4:
			S.t4 = true;
			break;
		default:
			break;
		}
		switch (b)
		{
		case 1:
			S.t1 = true;
			break;
		case 2:
			S.t2 = true;
			break;
		case 3:
			S.t3 = true;
			break;
		case 4:
			S.t4 = true;
			break;
		default:
			break;
		}
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


	convert(x, y, &Wx, &Wy);
	convert(x, y, &Rx, &Ry);



	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
	
	}
}

void Drag(int x, int y)
{
	float Rx, Ry, Wx, Wy;

	convert(x, y, &Wx, &Wy);
	convert(x, y, &Rx, &Ry);

	mx = (lineShape1[0][0] + lineShape1[1][0]) / 2.0;my = (lineShape2[0][1] + lineShape2[1][1]) / 2.0;

	if (c1)
	{
		lineShape1[0][0] = Wx;lineShape1[0][1] = Wy;
		lineShape4[1][0] = Wx;lineShape4[1][1] = Wy;
	}
	if (c2)
	{
		lineShape1[1][0] = Wx;lineShape1[1][1] = Wy;
		lineShape2[0][0] = Wx;lineShape2[0][1] = Wy;
	}
	if (c3)
	{
		lineShape2[1][0] = Wx;lineShape2[1][1] = Wy;
		lineShape3[0][0] = Wx;lineShape3[0][1] = Wy;
	}
	if (c4)
	{
		lineShape3[1][0] = Wx;lineShape3[1][1] = Wy;
		lineShape4[0][0] = Wx;lineShape4[0][1] = Wy;
	}
	if (rect)
	{
		for (int i = 0;i < 2;i++)
		{
			lineShape1[i][0] += (Wx - mx) / 20.0;lineShape1[i][1] += (Wy - my) / 20.0;
			lineShape2[i][0] += (Wx - mx) / 20.0;lineShape2[i][1] += (Wy - my) / 20.0;
			lineShape3[i][0] += (Wx - mx) / 20.0;lineShape3[i][1] += (Wy - my) / 20.0;
			lineShape4[i][0] += (Wx - mx) / 20.0;lineShape4[i][1] += (Wy - my) / 20.0;
		}
	}
	InitBuffer();
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

	glm::mat4 transformMatrix(1.0f);
	transformMatrix = glm::translate(transformMatrix, glm::vec3(1.0f, 1.0f, 0.0f)); //--- �̵�
	//--- ��ȯ ��� ���� ���ؽ� ���̴��� ������
	unsigned int transformLocation = glGetUniformLocation(shaderProgramID, "transform");
	glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));

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
	glGenBuffers(1, &TriPosVbo);
	glBindBuffer(GL_ARRAY_BUFFER, TriPosVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(HexahedronShape), HexahedronShape, GL_DYNAMIC_DRAW);
	glGenBuffers(1, &TriColorVbo);
	glBindBuffer(GL_ARRAY_BUFFER, TriColorVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(HexahedronColors), HexahedronColors, GL_STATIC_DRAW);

	glGenBuffers(1, &rectPosVbo);
	glBindBuffer(GL_ARRAY_BUFFER, rectPosVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(TetrahedronShape), TetrahedronShape, GL_DYNAMIC_DRAW);
	glGenBuffers(1, &rectColor);
	glBindBuffer(GL_ARRAY_BUFFER, rectColor);
	glBufferData(GL_ARRAY_BUFFER, sizeof(TetrahedronColors), TetrahedronColors, GL_STATIC_DRAW);
}


void resetS(sel* S)
{
	S->c0 = false;
	S->c1 = false;
	S->c2 = false;
	S->c3 = false;
	S->c4 = false;
	S->c5 = false;
	S->c6 = false;
	S->t0 = false;
	S->t1 = false;
	S->t2 = false;
	S->t3 = false;
	S->t4 = false;
}
void set()
{
	for (int i = 0;i < 3;i++)
	{
		TetrahedronColors[i][0] = 1;
		TetrahedronColors[i][1] = 0;
		TetrahedronColors[i][2] = 0;
	}
	for (int i = 3;i < 6;i++)
	{
		TetrahedronColors[i][0] = 0;
		TetrahedronColors[i][1] = 1;
		TetrahedronColors[i][2] = 0;
	}
	for (int i = 6;i < 9;i++)
	{
		TetrahedronColors[i][0] = 0;
		TetrahedronColors[i][1] = 0;
		TetrahedronColors[i][2] = 1;
	}
	for (int i = 9;i < 12;i++)
	{
		TetrahedronColors[i][0] = 1;
		TetrahedronColors[i][1] = 1;
		TetrahedronColors[i][2] = 0;
	}


	for (int i = 0;i < 6;i++)
	{
		HexahedronColors[i][0] = 1;
		HexahedronColors[i][1] = 0;
		HexahedronColors[i][2] = 0;
	}
	for (int i = 6;i < 12;i++)
	{
		HexahedronColors[i][0] = 0;
		HexahedronColors[i][1] = 1;
		HexahedronColors[i][2] = 0;
	}
	for (int i = 12;i < 18;i++)
	{
		HexahedronColors[i][0] = 0;
		HexahedronColors[i][1] = 0;
		HexahedronColors[i][2] = 1;
	}
	for (int i = 18;i < 24;i++)
	{
		HexahedronColors[i][0] = 1;
		HexahedronColors[i][1] = 1;
		HexahedronColors[i][2] = 0;
	}
	for (int i = 24;i < 30;i++)
	{
		HexahedronColors[i][0] = 0;
		HexahedronColors[i][1] = 1;
		HexahedronColors[i][2] = 1;
	}
	for (int i = 30;i < 36;i++)
	{
		HexahedronColors[i][0] = 1;
		HexahedronColors[i][1] = 0;
		HexahedronColors[i][2] = 1;
	}
	HexahedronShape[0][0] = 0.0;HexahedronShape[0][1] = 0.0;HexahedronShape[0][2] = 0.0;
	HexahedronShape[1][0] = 0.5;HexahedronShape[1][1] = 0.5;HexahedronShape[1][2] = 0.0;
	HexahedronShape[2][0] = 0.5;HexahedronShape[2][1] = 0.0;HexahedronShape[2][2] = 0.0;

	HexahedronShape[3][0] = 0.0;HexahedronShape[3][1] = 0.0;HexahedronShape[3][2] = 0.0;
	HexahedronShape[4][0] = 0.0;HexahedronShape[4][1] = 0.5;HexahedronShape[4][2] = 0.0;
	HexahedronShape[5][0] = 0.5;HexahedronShape[5][1] = 0.5;HexahedronShape[5][2] = 0.0;

	HexahedronShape[6][0] = 0.0;HexahedronShape[6][1] = 0.0;HexahedronShape[6][2] = 0.0;
	HexahedronShape[7][0] = 0.0;HexahedronShape[7][1] = 0.5;HexahedronShape[7][2] = 0.5;
	HexahedronShape[8][0] = 0.0;HexahedronShape[8][1] = 0.5;HexahedronShape[8][2] = 0.0;

	HexahedronShape[9][0] = 0.0;HexahedronShape[9][1] = 0.0;HexahedronShape[9][2] = 0.0;
	HexahedronShape[10][0] = 0.0;HexahedronShape[10][1] = 0.0;HexahedronShape[10][2] = 0.5;
	HexahedronShape[11][0] = 0.0;HexahedronShape[11][1] = 0.5;HexahedronShape[11][2] = 0.5;

	HexahedronShape[12][0] = 0.0;HexahedronShape[12][1] = 0.5;HexahedronShape[12][2] = 0.0;
	HexahedronShape[13][0] = 0.5;HexahedronShape[13][1] = 0.5;HexahedronShape[13][2] = 0.5;
	HexahedronShape[14][0] = 0.5;HexahedronShape[14][1] = 0.5;HexahedronShape[14][2] = 0.0;

	HexahedronShape[15][0] = 0.0;HexahedronShape[15][1] = 0.5;HexahedronShape[15][2] = 0.0;
	HexahedronShape[16][0] = 0.0;HexahedronShape[16][1] = 0.5;HexahedronShape[16][2] = 0.5;
	HexahedronShape[17][0] = 0.5;HexahedronShape[17][1] = 0.5;HexahedronShape[17][2] = 0.5;

	HexahedronShape[18][0] = 0.5;HexahedronShape[18][1] = 0.0;HexahedronShape[18][2] = 0.0;
	HexahedronShape[19][0] = 0.5;HexahedronShape[19][1] = 0.5;HexahedronShape[19][2] = 0.0;
	HexahedronShape[20][0] = 0.5;HexahedronShape[20][1] = 0.5;HexahedronShape[20][2] = 0.5;

	HexahedronShape[21][0] = 0.5;HexahedronShape[21][1] = 0.0;HexahedronShape[21][2] = 0.0;
	HexahedronShape[22][0] = 0.5;HexahedronShape[22][1] = 0.5;HexahedronShape[22][2] = 0.5;
	HexahedronShape[23][0] = 0.5;HexahedronShape[23][1] = 0.0;HexahedronShape[23][2] = 0.5;

	HexahedronShape[24][0] = 0.0;HexahedronShape[24][1] = 0.0;HexahedronShape[24][2] = 0.0;
	HexahedronShape[25][0] = 0.5;HexahedronShape[25][1] = 0.0;HexahedronShape[25][2] = 0.0;
	HexahedronShape[26][0] = 0.5;HexahedronShape[26][1] = 0.0;HexahedronShape[26][2] = 0.5;

	HexahedronShape[27][0] = 0.0;HexahedronShape[27][1] = 0.0;HexahedronShape[27][2] = 0.0;
	HexahedronShape[28][0] = 0.5;HexahedronShape[28][1] = 0.0;HexahedronShape[28][2] = 0.5;
	HexahedronShape[29][0] = 0.0;HexahedronShape[29][1] = 0.0;HexahedronShape[29][2] = 0.5;

	HexahedronShape[30][0] = 0.0;HexahedronShape[30][1] = 0.0;HexahedronShape[30][2] = 0.5;
	HexahedronShape[31][0] = 0.5;HexahedronShape[31][1] = 0.0;HexahedronShape[31][2] = 0.5;
	HexahedronShape[32][0] = 0.5;HexahedronShape[32][1] = 0.5;HexahedronShape[32][2] = 0.5;

	HexahedronShape[33][0] = 0.0;HexahedronShape[33][1] = 0.0;HexahedronShape[33][2] = 0.5;
	HexahedronShape[34][0] = 0.5;HexahedronShape[34][1] = 0.5;HexahedronShape[34][2] = 0.5;
	HexahedronShape[35][0] = 0.0;HexahedronShape[35][1] = 0.5;HexahedronShape[35][2] = 0.5;


	TetrahedronShape[0][0] = 0.0;TetrahedronShape[0][1] = 0.0;TetrahedronShape[0][2] = 0.0;
	TetrahedronShape[1][0] = 0.5;TetrahedronShape[1][1] = 0.0;TetrahedronShape[1][2] = 0.0;
	TetrahedronShape[2][0] = 0.0;TetrahedronShape[2][1] = 0.5;TetrahedronShape[2][2] = 0.0;

	TetrahedronShape[3][0] = 0.0;TetrahedronShape[3][1] = 0.0;TetrahedronShape[3][2] = 0.0;
	TetrahedronShape[4][0] = 0.5;TetrahedronShape[4][1] = 0.0;TetrahedronShape[4][2] = 0.0;
	TetrahedronShape[5][0] = 0.0;TetrahedronShape[5][1] = 0.0;TetrahedronShape[5][2] = 0.5;

	TetrahedronShape[6][0] = 0.0;TetrahedronShape[6][1] = 0.0;TetrahedronShape[6][2] = 0.0;
	TetrahedronShape[7][0] = 0.0;TetrahedronShape[7][1] = 0.5;TetrahedronShape[7][2] = 0.0;
	TetrahedronShape[8][0] = 0.0;TetrahedronShape[8][1] = 0.0;TetrahedronShape[8][2] = 0.5;

	TetrahedronShape[9][0] = 0.5;TetrahedronShape[9][1] = 0.0;TetrahedronShape[9][2] = 0.0;
	TetrahedronShape[10][0] = 0.0;TetrahedronShape[10][1] = 0.5;TetrahedronShape[10][2] = 0.0;
	TetrahedronShape[11][0] = 0.0;TetrahedronShape[11][1] = 0.0;TetrahedronShape[11][2] = 0.5;
}
void ReadObj(FILE* path) 
{
	char count[128];
	int vertexnum = 0;
	int facenum = 0;
	int uvnum = 0;
	//--- 1. ��ü ���ؽ� ���� �� �ﰢ�� ���� ����
	while (!feof(path)) 
	{
		fscanf(path, "%s", count);
		if (count[0] == 'v' && count[1] == '\0')
			vertexnum++;
		else if (count[0] == 'f' && count[1] == '\0')
			facenum++;
		else if (count[0] == 'v' && count[1] == 'f' && count[3] == '\0')
			uvnum++;
		memset(count, '\0', sizeof(count));
	}
	rewind(path);
	int vertIndex = 0;
	int faceIndex = 0;
	int uvIndex = 0;
	//--- 2. �޸� �Ҵ�
	glm::vec3* vertex = new glm::vec3[vertexnum];
	glm::vec3* face = new glm::vec3[facenum];
	glm::vec3* uvdata = new glm::vec3[facenum];
	glm::vec2* uv = new glm::vec2[uvnum];
	char bind[128];

	while (!feof(path)) {
		fscanf(path, "%s", bind);
		if (bind[0] == 'v' && bind[1] == '\0') {
			fscanf(path, "%f %f %f\n",
				&vertex[vertIndex].x, &vertex[vertIndex].y, &vertex[vertIndex].z);
			vertIndex++;
		}
		else if (bind[0] == 'f' && bind[1] == '\0') {
			unsigned int temp_face[3], temp_uv[3], temp_normal[3];
			fscanf(path, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
				&temp_face[0], &temp_uv[0], &temp_normal[0],
				&temp_face[1], &temp_uv[1], &temp_normal[1],
				&temp_face[2], &temp_uv[2], &temp_normal[2]);
			face[faceIndex].x = temp_face[0];
			face[faceIndex].y = temp_face[1];
			face[faceIndex].z = temp_face[2];
			uvdata[faceIndex].x = temp_uv[0];
			uvdata[faceIndex].y = temp_uv[1];
			uvdata[faceIndex].z = temp_uv[2];
			faceIndex++;
		}
		else if (bind[0] == 'v' && bind[1] == 't' && bind[2] == '\0') {
			fscanf(path, "%f %f\n", &uv[uvIndex].x, &uv[uvIndex].y);
			uvIndex++;
		}
	}
	//--- �ʿ��� ��� �о�� ���� ���� ���� � ����


	for (int i = 0;i < faceIndex;i++)
	{
		HexahedronShape[0][0] = face[i].x;HexahedronShape[0][1] = face[i].t;HexahedronShape[0][2] = face[i].z;
		
	}
	printf("\n");



	for (int i = 0;i < 36;i++)
	{
		for (int j = 0;j < 3;j++)
		{
			printf("%f\t", HexahedronShape[i][j]);
		}
		printf("\n");
	}
}