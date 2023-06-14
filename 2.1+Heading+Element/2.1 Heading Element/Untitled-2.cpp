#include<GL/glut.h>
#include <time.h>
double w=1280,h=720;
double view[3]={2,2,12.9};
double look[3]={2,2,2};
int flag=-1;
void steps(void);
void window(void);
void sgate(void);
void gate(void);
double angle=0,speed=5,maino=0,romo=0,tro=0,mgo=0,sgo=0;
//declarating quadric objects
GLUquadricObj *Cylinder;
GLUquadricObj *Disk;
struct tm *newtime;
time_t ltime;
GLfloat angle1;
//initialisation
void myinit(void)
{
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glFrustum(-1.0,1.0,-1*w/h,1*w/h,1,200.0);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
//defining new quadric object
 Cylinder = gluNewQuadric();
//to set drawing style
 gluQuadricDrawStyle( Cylinder, GLU_FILL);
//to set automatic normals
 gluQuadricNormals( Cylinder,GLU_SMOOTH);
 Disk = gluNewQuadric();
 gluQuadricDrawStyle( Disk, GLU_FILL);
 gluQuadricNormals( Disk, GLU_SMOOTH);
GLfloat gam[]={0.2,.2,.2,1};
glLightModelfv(GL_LIGHT_MODEL_AMBIENT,gam);
}
//set material property
void matprop(GLfloat amb[],GLfloat dif[],GLfloat spec[],GLfloat shi[])
{
glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,amb);
glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,dif);
glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,spec);
glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shi);
}
//to create wall
void wall(double thickness)
{
glPushMatrix();
glTranslated(2,.5*thickness,2);
glScaled(4.0,thickness,4.0);
glutSolidCube(1.0);
glPopMatrix();
}
//to create compound wall
void wall2(double thickness)
{
glPushMatrix();
glTranslated(.8,.5*thickness*4,3.5);
glScaled(1.6,thickness*4,7.0);
glutSolidCube(1.0);
glPopMatrix();
}
//to create earth
void earth(void)
{
GLfloat ambient[]={1,0,0,1};
GLfloat specular[]={0,1,1,1};
GLfloat diffuse[]={.5,.5,.5,1};
GLfloat shininess[]={50};
matprop(ambient,diffuse,specular,shininess);
GLfloat lightIntensity[]={.7,.7,.7,1};
GLfloat light_position[]={2,5,-3,0};
glLightfv(GL_LIGHT0,GL_POSITION,light_position);
glLightfv(GL_LIGHT0,GL_DIFFUSE,lightIntensity);
glPushMatrix();
glTranslated(0,-.25,0);
glScaled(10000,.5,1000000);
glutSolidCube(1.0);
glPopMatrix();
glFlush();
}
void compound(void)
{
GLfloat ambient[]={1,0,0,1};
GLfloat specular[]={0,1,1,1};
GLfloat diffuse[]={.7,1,.7,1};
GLfloat shininess[]={50};
matprop(ambient,diffuse,specular,shininess);
GLfloat lightIntensity[]={.7,.7,.7,1};
GLfloat light_position[]={2,6,1.5,0};
glLightfv(GL_LIGHT0,GL_POSITION,light_position);
glLightfv(GL_LIGHT0,GL_DIFFUSE,lightIntensity);
//left wall of compound
glPushMatrix();
glPushMatrix();
glTranslated(-4,0,-1-.04);
glRotated(90.0,0,0,1);
wall2(0.08);
glPopMatrix();
//right wall of compound
glPushMatrix();
glTranslated(8,0,-1-.02);
glRotated(90.0,0,0,1);
wall2(0.08);
glPopMatrix();
//back wall of compound
glPushMatrix();
glTranslated(2,.8,-1);
glRotated(-90,1,0,0);
glScaled(12,.02*4,1.6);
glutSolidCube(1.0);
glPopMatrix();
//front left wall of compound
glPushMatrix();
glTranslated(-3,.8,6-.08);
glRotated(-90,1,0,0);
glScaled(2,.02*4,1.6);
glutSolidCube(1.0);
glPopMatrix();
//front middle wall of compound
glPushMatrix();
glTranslated(2.5,.8,6-.08);
glRotated(-90,1,0,0);
glScaled(6,.02*4,1.6);
glutSolidCube(1.0);
glPopMatrix();
//front right wall of compound
glPushMatrix();
glTranslated(7,.8,6-.08);
glRotated(-90,1,0,0);
glScaled(2,.02*4,1.6);
glutSolidCube(1.0);
glPopMatrix();
glPopMatrix();
GLfloat ambient2[]={0,1,0,1};
GLfloat specular2[]={1,1,1,1};
GLfloat diffuse2[]={.2,.6,0.1,1};
GLfloat shininess2[]={50};
matprop(ambient2,diffuse2,specular2,shininess2);
//floor
glPushMatrix();
glTranslated(-4,-0.05,-1);
glScaled(3,3,1.7);
wall(0.08);
glPopMatrix();
gate();
 sgate();
 glFlush();
}
void room()
{
GLfloat ambient1[]={1,0,1,1};
GLfloat specular1[]={1,1,1,1};
GLfloat diffuse1[]={0.5,0.5,0.5,1};
GLfloat mat_shininess[]={50};
 matprop(ambient1,diffuse1,specular1,mat_shininess);
glPushMatrix();
glTranslated(.5,4,.5);
//roof
glPushMatrix();
glTranslated(-.02*4,.7*3.9,-.02*4);
glScaled(.6+.02,1.5,.5+.02+.1);
wall(0.08);
glPopMatrix();
GLfloat ambient2[]={1,0,0,1};
GLfloat specular2[]={1,1,1,1};
GLfloat diffuse2[]={1,1,.7,1};
GLfloat shininess1[]={50};
matprop(ambient2,diffuse2,specular2,shininess1);
//left wall
glPushMatrix();
glTranslated(0,0,-.02);
glScaled(1,.7,.5);
glRotated(90.0,0,0,1);
wall(0.08);
glPopMatrix();
//right wall
glPushMatrix();
glTranslated(2.4,0,-.02);
glScaled(1,.7,.5);
glRotated(90.0,0,0,1);
wall(0.08);
glPopMatrix();
//back wall
glPushMatrix();
glTranslated(-.08,0,0);
glScaled(.62,.7,1);
glRotated(-90.0,1,0,0);
wall(0.08);
glPopMatrix();
//front wall
glPushMatrix();
glTranslated(-0.08,0,2);
glScaled(.5,.7,1);
glRotated(-90.0,1,0,0);
wall(0.08);
glPopMatrix();
//wall above the room door
glPushMatrix();
glTranslated(1.9,.7*3,2);
glScaled(.11,.7*.25,1);
glRotated(-90.0,1,0,0);
wall(0.08);
glPopMatrix();
GLfloat ambient[]={1,0.5,.5,1};
GLfloat specular[]={1,1,1,1};
GLfloat diffuse[]={1,0.5,0.5,1};
 matprop(ambient,diffuse,specular,mat_shininess);
//door
glPushMatrix();
glTranslated(2.3,0,(2-.05));
glRotated(-tro,0,1,0);
glTranslated(-2.3,0,-(2-.05));
glPushMatrix();
glTranslated(1.927,0,2);
glScaled(.09,.525,1);
glRotated(-90.0,1,0,0);
wall(0.02);
glPopMatrix();
glPushMatrix();
glTranslated(2.3,0,2-.05);
glScaled(.6,.7,.8);
glRotated(-90,1,0,0);
gluCylinder(Cylinder, 0.05, 0.05, 3, 16, 16);
glPopMatrix();
glPopMatrix();
glPopMatrix();
}
void tankwall(float thk)
{
glTranslated(.5,.5*thk,.5);
glScaled(1,thk,1);
glutSolidCube(1);
}
void watertank(void)
{
float thk=.04,hght=1,wdth=1,bdth=1;
GLfloat ambient1[]={.5,0,1,1};
GLfloat specular1[]={1,1,1,1};
GLfloat diffuse1[]={.5,.8,1,1};
GLfloat mat_shininess[]={50};
 matprop(ambient1,diffuse1,specular1,mat_shininess);
glPushMatrix();
glTranslated(1.5,4+4*.7,1.5);
glScaled(.8,.8,.8);
//tank floor
glPushMatrix();
glScaled(wdth,1,bdth);
tankwall(thk);
glPopMatrix();
//tank left wall
glPushMatrix();
glScaled(1,hght,bdth);
glRotated(90.0,0,0,1);
tankwall(thk);
glPopMatrix();
//tank right wall
glPushMatrix();
glTranslated(wdth,0,0);
glScaled(1,hght,bdth);
glRotated(90.0,0,0,1);
tankwall(thk);
glPopMatrix();
//tank back wall
glPushMatrix();
glScaled(wdth,hght,1);
glRotated(-90.0,1,0,0);
tankwall(0.04);
glPopMatrix();
//tank front wall
glPushMatrix();
glTranslated(0,0,bdth);
glScaled(wdth,hght,1);
glRotated(-90.0,1,0,0);
tankwall(0.04);
glPopMatrix();
//tank roof
glPushMatrix();
glTranslated(-thk,hght,0);
glScaled(wdth*.8,1,bdth);
tankwall(0.04);
glPopMatrix();
glPushMatrix();
glTranslated(wdth*.8-thk,hght,0);
glScaled(wdth*.2+thk,1,bdth*.6);
tankwall(0.04);
glPopMatrix();
glPopMatrix();
}
void terece(void)
{
GLfloat ambient1[]={1,0,1,1};
GLfloat specular1[]={1,1,1,1};
GLfloat diffuse1[]={0.5,0.5,0.5,1};
GLfloat mat_shininess[]={50};
 matprop(ambient1,diffuse1,specular1,mat_shininess);
glPushMatrix();
glTranslated(0,4,0);
glScaled(1,.1,1);
//left wall
glPushMatrix();
glTranslated(0,0,-.02-.25);
glScaled(1,1,.95);
glRotated(90.0,0,0,1);
wall(0.08);
glPopMatrix();
//right wall
glPushMatrix();
glTranslated(6+.12,0,-.02-.27);
glScaled(1,1,1.1);
glRotated(90.0,0,0,1);
wall(0.08);
glPopMatrix();
//back wall
glPushMatrix();
glTranslated(-.08,0,-.21);
glScaled(1.5+.05,1,1);
glRotated(-90.0,1,0,0);
wall(0.08);
glPopMatrix();
//front wall
glPushMatrix();
glTranslated(-.08,0,4+.11);
glScaled(1.5+.05,1,1);
glRotated(-90.0,1,0,0);
wall(0.08);
glPopMatrix();
glPushMatrix();
glTranslated(-.04,2,4);
glScaled(.08,4,.1);
glutSolidCube(1);
glPopMatrix();
 glPopMatrix();
}
void fanwing(float winglen)
{
 glPushMatrix();
glRotated(90,1,0,0);
glRotated(90,0,1,0);
glScaled(1,15,1);
gluCylinder(Cylinder,.01,.01,1,4,1);
glPopMatrix();
}
void fanbottom()
{
glPushMatrix();
glTranslated(1,3.2,1);
glPushMatrix();
glRotated(90,1,0,0);
gluCylinder(Cylinder, .2, .2,.05, 128, 16);
glPopMatrix();
glPushMatrix();
glTranslated(0,0.00025,0);
glRotated(90,1,0,0);
gluDisk(Disk,0,.2,32,16);
glPopMatrix();
glPushMatrix();
glTranslated(0,-.05,0);
glRotated(90,1,0,0);
gluCylinder(Cylinder,.2,.15,.1,128,16);
glPopMatrix();
glPushMatrix();
glTranslated(0,-.1,0);
glRotated(90,1,0,0);
gluDisk(Disk,0,.15,32,16);
glPopMatrix();
glPushMatrix();
glTranslated(0.1,0.0,0);
fanwing(.6);
glPopMatrix();
glPushMatrix();
glRotated(120,0,1,0);
glTranslated(.1,0,0);
fanwing(.6);
glPopMatrix();
glPushMatrix();
glRotated(240,0,1,0);
glTranslated(0.1,0.0,0);
fanwing(.6);
glPopMatrix();
glPopMatrix();
}
void fan(void)
{ glPushMatrix();
glTranslated(2.5,1.9,0);
glScaled(.5,.5,.5);
GLfloat mat_ambient[]={.5,0,0,1};
GLfloat mat_specular[]={0,1,1,0};
GLfloat mat_diffuse[]={.8,1,.8,1};
GLfloat mat_shininess[]={50};
glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
if(flag==-1)
{
glPushMatrix();
fanbottom();
glPopMatrix();
}
else
{
angle+=speed;
glPushMatrix();
glTranslated(1,0,1);
glRotated(angle,0,1,0);
glTranslated(-1,0,-1);
fanbottom();
glPopMatrix();
}
glPushMatrix();
glTranslatef(1,3.3,1);
glRotated(-90,1,0,0);
gluCylinder(Cylinder, .1, 0.005, .25, 16, 16);
glPopMatrix();
glPushMatrix();
glTranslatef(1,4,1);
glRotated(90,1,0,0);
gluCylinder(Cylinder, .006, 0.006, .6, 16, 16);
glPopMatrix();
glPushMatrix();
glTranslatef(1,3.96,1);
glRotated(90,1,0,0);
gluCylinder(Cylinder, .1, 0.005, .25, 16, 16);
glPopMatrix();
glPopMatrix();
if(flag==1)
glutPostRedisplay();
}
void tableg(float llen,float lthk)
{
glPushMatrix();
glRotated(-90,1,0,0);
gluCylinder(Cylinder,lthk,lthk,llen,32,32);
glPopMatrix();
}
void table(float tabwid,float tablen,float tabthk,float llen,float lthk)
{
glPushMatrix();
glPushMatrix();
glTranslated(0,llen,0);
glScaled(tabwid,tabthk,tablen);
glutSolidCube(1);
glPopMatrix();
float dist1=.95*tablen/2-lthk/