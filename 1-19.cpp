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



GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void Drag(int x, int y);
void TimerFunction(int value);
GLvoid Special(int key, int x, int y);
void convert(int x, int y, float* ox, float* oy);
void InitBuffer();
void make_vertexShaders();
void make_fragmentShaders();
void make_shaderProgram();
GLvoid drawScene();
GLvoid Reshape(int w, int h);
char* filetobuf(const char* file);
void set();


float Y = 0, Z = 0, ry = 0;
float mx = 0, my = 0, mz = 0;

bool left_button;
bool select = true, c1 = true, c2 = true;
bool rot = false;
bool zrot = false;
bool solid = true;

bool grain = true;


GLfloat HexahedronShape[36][3];
GLfloat HexahedronColors[36][3];
GLfloat TetrahedronShape[18][3];
GLfloat TetrahedronColors[18][3];



GLuint HexPosVbo, TetPosVbo;
GLuint HexColor, TetColor;


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
	glutSpecialFunc(Special);
	glutTimerFunc(10, TimerFunction, 1);

	glutMainLoop();
}

GLUquadricObj* qobj;
GLUquadricObj* qobj2;
GLUquadricObj* qobj3;
GLUquadricObj* qobj4;
GLUquadricObj* qobj5;
GLUquadricObj* qobj6;

GLvoid drawScene() //--- �ݹ� �Լ�: �׸��� �ݹ� �Լ�
{
	GLfloat rColor, gColor, bColor;
	rColor = gColor = 0.0;
	bColor = 0.0;
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	if (grain)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);

	glUseProgram(shaderProgramID);




	GLuint changePos = glGetUniformLocation(shaderProgramID, "Pos");
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position"); //	: 0  Shader�� 'layout (location = 0)' �κ�
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color"); //	: 1

	glEnableVertexAttribArray(PosLocation); // Enable �ʼ�! ����ϰڴ� �ǹ�
	glEnableVertexAttribArray(ColorLocation);

	glm::vec3 cameraPos = glm::vec3(0.0f, 1.0f, 5.0f); //--- ī�޶� ��ġ
	glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f); //--- ī�޶� �ٶ󺸴� ����
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); //--- ī�޶� ���� ����



	


	glm::mat4 model;
	model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 view;
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), 800.0f / 800.0f, 0.1f, 100.0f);

	int modelLocation = glGetUniformLocation(shaderProgramID, "transform"); //--- ���ؽ� ���̴����� �𵨸� ��ȯ ��� �������� �޾ƿ´�.
	int viewLoc = glGetUniformLocation(shaderProgramID, "viewTransform"); //--- ���ؽ� ���̴����� ���� ��ȯ ��� �������� �޾ƿ´�.
	int projLoc = glGetUniformLocation(shaderProgramID, "projectionTransform");





	glm::mat4 mTransform = glm::mat4(1.0f);
	mTransform = glm::rotate(mTransform, glm::radians(Y), glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &mTransform[0][0]);
	glm::mat4 vTransform = glm::mat4(1.0f);
	vTransform = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &vTransform[0][0]);
	glm::mat4 pTransform = glm::mat4(1.0f);
	pTransform = glm::perspective(glm::radians(60.0f), 800.0f / 800.0f, 0.1f, 200.0f);
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, &pTransform[0][0]);




	

	

	qobj = gluNewQuadric();
	qobj2 = gluNewQuadric();
	

	gluQuadricDrawStyle(qobj, GLU_LINE);
	gluQuadricDrawStyle(qobj2, GLU_FILL);

	


	
	
	{
		glm::mat4 xyz = glm::mat4(1.0f);
		glm::mat4 rot = glm::mat4(1.0f);
		glm::mat4 x = glm::mat4(1.0f);
		x = glm::rotate(x, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0));
		rot = glm::rotate(rot, glm::radians(ry), glm::vec3(0.0, 1.0, 0.0));
		xyz = glm::translate(xyz, glm::vec3(mx, my, mz));


		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(xyz * rot));
		if (solid)
			gluSphere(qobj, 0.8, 20, 20);
		else
			gluSphere(qobj2, 0.8, 20, 20);
	}


	{
		glm::mat4 x = glm::mat4(1.0f);
		glm::mat4 y = glm::mat4(1.0f);
		glm::mat4 z = glm::mat4(1.0f);
		glm::mat4 xyz = glm::mat4(1.0f);
		glm::mat4 rot = glm::mat4(1.0f);
		glm::mat4 zrot = glm::mat4(1.0f);
		glm::mat4 movez = glm::mat4(1.0f);

		zrot = glm::rotate(zrot, glm::radians(Z), glm::vec3(0.0, 0.0, 1.0));
		y = glm::rotate(y, glm::radians(Y), glm::vec3(0.0, 1.0, 0.0));
		movez = glm::translate(movez, glm::vec3(0.0, 0, -2.0f));
		xyz = glm::translate(xyz, glm::vec3(mx, my, mz));

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(xyz*zrot*rot*y * movez));
		if (solid)
			gluSphere(qobj, 0.3, 20, 20);
		else
			gluSphere(qobj2, 0.3, 20, 20);


		x = glm::rotate(x, glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0));
		y = glm::rotate(y, glm::radians(0.0f), glm::vec3(0.0, 1.0, 0.0));
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(xyz* zrot* rot* x));
		
			gluDisk(qobj, 2.0, 2.0, 50, 1);
		
	}
	{
		glm::mat4 x = glm::mat4(1.0f);
		glm::mat4 y = glm::mat4(1.0f);
		glm::mat4 z = glm::mat4(1.0f);
		glm::mat4 y2 = glm::mat4(1.0f);
		glm::mat4 movez = glm::mat4(1.0f);
		glm::mat4 movez2 = glm::mat4(1.0f);
		glm::mat4 rot = glm::mat4(1.0f);
		glm::mat4 zrot = glm::mat4(1.0f);
		glm::mat4 xyz = glm::mat4(1.0f);


		xyz = glm::translate(xyz, glm::vec3(mx, my, mz));
		zrot = glm::rotate(zrot, glm::radians(Z), glm::vec3(0.0, 0.0, 1.0));
		rot = glm::rotate(rot, glm::radians(ry), glm::vec3(0.0, 1.0, 0.0));
		x = glm::rotate(x, glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0));
		y = glm::rotate(y, glm::radians(Y), glm::vec3(0.0, 1.0, 0.0));
		y2 = glm::rotate(y2, glm::radians(Y * 0.5f), glm::vec3(0.0, 1.0, 0.0));
		movez = glm::translate(movez, glm::vec3(0.0, 0, -2.0f));
		movez2 = glm::translate(movez2, glm::vec3(0.0, 0, -0.5f));


		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(xyz* zrot* y* movez* y2* movez2));
		if (solid)
			gluSphere(qobj, 0.1, 20, 20);
		else
			gluSphere(qobj2, 0.1, 20, 20);



		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(xyz* zrot* y* movez* x));

		gluDisk(qobj, 0.5, 0.5, 50, 1);
	
	}





	{
		glm::mat4 x = glm::mat4(1.0f);
		glm::mat4 y = glm::mat4(1.0f);
		glm::mat4 z = glm::mat4(1.0f);
		glm::mat4 y2 = glm::mat4(1.0f);
		glm::mat4 movez = glm::mat4(1.0f);
		glm::mat4 rot = glm::mat4(1.0f);
		glm::mat4 zrot = glm::mat4(1.0f);
		glm::mat4 xyz = glm::mat4(1.0f);

		xyz = glm::translate(xyz, glm::vec3(mx, my, mz));
		zrot = glm::rotate(zrot, glm::radians(Z), glm::vec3(0.0, 0.0, 1.0));
		rot = glm::rotate(rot, glm::radians(ry), glm::vec3(0.0, 1.0, 0.0));
		y = glm::rotate(y, glm::radians(Y), glm::vec3(1.0, 1.0, 0.0));
		movez = glm::translate(movez, glm::vec3(0.0, 0, 2.0f));

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(xyz* zrot* rot* y*  movez));
		if (solid)
			gluSphere(qobj, 0.3, 20, 20);
		else
			gluSphere(qobj2, 0.3, 20, 20);


		x = glm::rotate(x, glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0));
		y2 = glm::rotate(y2, glm::radians(45.0f), glm::vec3(0.0, 1.0, 0.0));
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(xyz* zrot* rot* x* y2));
	
		gluDisk(qobj, 2.0, 2.0, 50, 1);
		
	}
	{
		glm::mat4 x = glm::mat4(1.0f);
		glm::mat4 x2 = glm::mat4(1.0f);
		glm::mat4 z = glm::mat4(1.0f);
		glm::mat4 rot = glm::mat4(1.0f);
		glm::mat4 y = glm::mat4(1.0f);
		glm::mat4 y2 = glm::mat4(1.0f);
		glm::mat4 movez = glm::mat4(1.0f);
		glm::mat4 movez2 = glm::mat4(1.0f);
		glm::mat4 zrot = glm::mat4(1.0f);
		glm::mat4 xyz = glm::mat4(1.0f);

		xyz = glm::translate(xyz, glm::vec3(mx, my, mz));
		zrot = glm::rotate(zrot, glm::radians(Z), glm::vec3(0.0, 0.0, 1.0));
		rot = glm::rotate(rot, glm::radians(ry), glm::vec3(0.0, 1.0, 0.0));
		y = glm::rotate(y, glm::radians(Y), glm::vec3(1.0, 1.0, 0.0));
		y2 = glm::rotate(y2, glm::radians(Y * 0.5f), glm::vec3(1.0, 1.0, 0.0));
		x = glm::rotate(x, glm::radians(-90.0f), glm::vec3(1.0, -1.0, 0.0));
		x2 = glm::rotate(x2, glm::radians(45.0f), glm::vec3(1.0, 0.0, 0.0));
		z = glm::rotate(z, glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0));

		movez = glm::translate(movez, glm::vec3(0.0, 0, 2.0f));
		movez2 = glm::translate(movez2, glm::vec3(0.0, 0, -0.5f));

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(xyz* zrot* rot* y* movez* y2* movez2));
		if (solid)
			gluSphere(qobj, 0.1, 20, 20);
		else
			gluSphere(qobj2, 0.1, 20, 20);

		
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(xyz* zrot* rot* y*movez*x));
	
		gluDisk(qobj, 0.5, 0.5, 50, 1);
		
	}

	
	{
		glm::mat4 z = glm::mat4(1.0f);
		glm::mat4 x = glm::mat4(1.0f); 
		glm::mat4 y = glm::mat4(1.0f);
		glm::mat4 y2 = glm::mat4(1.0f);
		glm::mat4 movez = glm::mat4(1.0f);
		glm::mat4 rot = glm::mat4(1.0f);
		glm::mat4 zrot = glm::mat4(1.0f);
		glm::mat4 xyz = glm::mat4(1.0f);

		xyz = glm::translate(xyz, glm::vec3(mx, my, mz));
		zrot = glm::rotate(zrot, glm::radians(Z), glm::vec3(0.0, 0.0, 1.0));
		rot = glm::rotate(rot, glm::radians(ry), glm::vec3(0.0, 1.0, 0.0));
		y = glm::rotate(y, glm::radians(Y), glm::vec3(-1.0, 1.0, 0.0));
		movez = glm::translate(movez, glm::vec3(0.0, 0, 2.0f));

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(xyz* zrot* rot*y * movez));
		if (solid)
			gluSphere(qobj, 0.3, 20, 20);
		else
			gluSphere(qobj2, 0.3, 20, 20);



		x = glm::rotate(x, glm::radians(90.0f), glm::vec3(-1.0, 0.0, 0.0));
		y2 = glm::rotate(y2, glm::radians(45.0f), glm::vec3(0.0, 1.0, 0.0));
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(xyz* zrot* rot* x* y2));
		gluDisk(qobj, 2.0, 2.0, 50, 1);
	}
	{
		glm::mat4 x = glm::mat4(1.0f);
		glm::mat4 y = glm::mat4(1.0f);
		glm::mat4 y2 = glm::mat4(1.0f);
		glm::mat4 movez = glm::mat4(1.0f);
		glm::mat4 movez2 = glm::mat4(1.0f);
		glm::mat4 rot = glm::mat4(1.0f);
		glm::mat4 zrot = glm::mat4(1.0f);
		glm::mat4 xyz = glm::mat4(1.0f);

		xyz = glm::translate(xyz, glm::vec3(mx, my, mz));
		zrot = glm::rotate(zrot, glm::radians(Z), glm::vec3(0.0, 0.0, 1.0));
		y = glm::rotate(y, glm::radians(Y), glm::vec3(-1.0, 1.0, 0.0));
		y2 = glm::rotate(y2, glm::radians(Y * 0.5f), glm::vec3(-1.0, 1.0, 0.0));
		rot = glm::rotate(rot, glm::radians(ry), glm::vec3(0.0, 1.0, 0.0));

		x = glm::rotate(x, glm::radians(90.0f), glm::vec3(1.0, 1.0, 0.0));
		movez = glm::translate(movez, glm::vec3(0.0, 0, 2.0f));
		movez2 = glm::translate(movez2, glm::vec3(0.0, 0, -0.5f));

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(xyz* zrot* rot* y * movez * y2 * movez2));
		if (solid)
			gluSphere(qobj, 0.1, 20, 20);
		else
			gluSphere(qobj2, 0.1, 20, 20);




		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(xyz* zrot* rot* y* movez* x));
		gluDisk(qobj, 0.5, 0.5, 50, 1);
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
	case '+':
		mz += 0.1;
		break;
	case '-':
		mz -= 0.1;
		break;
	case 'd':
		mx += 0.1;
		break;
	case 'a':
		mx -= 0.1;
		break;
	case 'w':
		my += 0.1;
		break;
	case 's':
		my -= 0.1;
		break;
	case 'y':
		if (rot)
			rot = false;
		else
			rot = true;
		break;
	case 'z':
		if (zrot)
			zrot = false;
		else
			zrot = true;
		break;
	case 'm':
		if (solid)
			solid = false;
		else
			solid = true;
		break;
	case 'q':
		exit(1);
		break;
	}


	glutPostRedisplay();
}
GLvoid Special(int key, int x, int y)
{
	switch (key)
	{
	
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
	Y += 3;

	if (rot)
		ry++;
	if (zrot)
		Z++;


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
	glGenBuffers(1, &HexPosVbo);
	glBindBuffer(GL_ARRAY_BUFFER, HexPosVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(HexahedronShape), HexahedronShape, GL_DYNAMIC_DRAW);
	glGenBuffers(1, &HexColor);
	glBindBuffer(GL_ARRAY_BUFFER, HexColor);
	glBufferData(GL_ARRAY_BUFFER, sizeof(HexahedronColors), HexahedronColors, GL_STATIC_DRAW);

	glGenBuffers(1, &TetPosVbo);
	glBindBuffer(GL_ARRAY_BUFFER, TetPosVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(TetrahedronShape), TetrahedronShape, GL_DYNAMIC_DRAW);
	glGenBuffers(1, &TetColor);
	glBindBuffer(GL_ARRAY_BUFFER, TetColor);
	glBufferData(GL_ARRAY_BUFFER, sizeof(TetrahedronColors), TetrahedronColors, GL_STATIC_DRAW);

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
	for (int i = 12;i < 15;i++)
	{
		TetrahedronColors[i][0] = 1;
		TetrahedronColors[i][1] = 0;
		TetrahedronColors[i][2] = 1;
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
	TetrahedronShape[2][0] = 0.0;TetrahedronShape[2][1] = 0.0;TetrahedronShape[2][2] = 0.5;

	TetrahedronShape[3][0] = 0.5;TetrahedronShape[3][1] = 0.0;TetrahedronShape[3][2] = 0.5;
	TetrahedronShape[4][0] = 0.5;TetrahedronShape[4][1] = 0.0;TetrahedronShape[4][2] = 0.0;
	TetrahedronShape[5][0] = 0.0;TetrahedronShape[5][1] = 0.0;TetrahedronShape[5][2] = 0.5;

	TetrahedronShape[6][0] = 0.5;TetrahedronShape[6][1] = 0.0;TetrahedronShape[6][2] = 0.0;
	TetrahedronShape[7][0] = 0.0;TetrahedronShape[7][1] = 0.0;TetrahedronShape[7][2] = 0.0;
	TetrahedronShape[8][0] = 0.25;TetrahedronShape[8][1] = 0.4;TetrahedronShape[8][2] = 0.25;

	TetrahedronShape[9][0] = 0.0;TetrahedronShape[9][1] = 0.0;TetrahedronShape[9][2] = 0.5;
	TetrahedronShape[10][0] = 0.0;TetrahedronShape[10][1] = 0.0;TetrahedronShape[10][2] = 0.0;
	TetrahedronShape[11][0] = 0.25;TetrahedronShape[11][1] = 0.4;TetrahedronShape[11][2] = 0.25;

	TetrahedronShape[12][0] = 0.5;TetrahedronShape[12][1] = 0.0;TetrahedronShape[12][2] = 0.0;
	TetrahedronShape[13][0] = 0.5;TetrahedronShape[13][1] = 0.0;TetrahedronShape[13][2] = 0.5;
	TetrahedronShape[14][0] = 0.25;TetrahedronShape[14][1] = 0.4;TetrahedronShape[14][2] = 0.25;

	TetrahedronShape[15][0] = 0.0;TetrahedronShape[15][1] = 0.0;TetrahedronShape[15][2] = 0.5;
	TetrahedronShape[16][0] = 0.5;TetrahedronShape[16][1] = 0.0;TetrahedronShape[16][2] = 0.5;
	TetrahedronShape[17][0] = 0.25;TetrahedronShape[17][1] = 0.4;TetrahedronShape[17][2] = 0.25;



}