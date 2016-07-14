#include "tank.h"

void calcNormal(GLdouble v0[3], GLdouble v1[3], GLdouble v2[3], GLdouble n[3])
{
    GLdouble v2v[2][3];
    GLdouble vt[3];
    double abs;
    int i;
    for (i = 0; i < 3; i++)
    {
        v2v[0][i] = v1[i] - v0[i];
        v2v[1][i] = v2[i] - v0[i];
    }
    vt[0] = v2v[0][1] * v2v[1][2] - v2v[0][2] * v2v[1][1];
    vt[1] = v2v[0][2] * v2v[1][0] - v2v[0][0] * v2v[1][2];
    vt[2] = v2v[0][0] * v2v[1][1] - v2v[0][1] * v2v[1][0];
    abs = sqrt(vt[0] * vt[0] + vt[1] * vt[1] + vt[2] * vt[2]);
    for (i = 0; i < 3; i++)
        n[i] = vt[i] / abs;
}
/*
 drawXXX
 -----------------------------------------*/
void drawString(char str[6], int w, int h, int x0, int y0)
{
    int i;
    glDisable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, w, h, 0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2f(x0, y0);
    for(i = 0; i < 6; ++i)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, str[i]);
    
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void drawGround(void)
{
    int i, j;
    GLdouble normal[3] = { 0.0, 0.0, 1.0 };
    
    glPushMatrix();
    
    glNormal3dv(normal);
    
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color[YELLOW]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
    glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
    glBegin(GL_QUADS);
    glVertex3d(-0.5*L, -0.5*L, 0.0); // start
    glVertex3d((X - 0.5)*L, -0.5*L, 0.0);
    glVertex3d((X - 0.5)*L, 0.5*L, 0.0);
    glVertex3d(-0.5*L, 0.5*L, 0.0);
    
    glVertex3d(-0.5*L, (Y - 0.5)*L, 0.0); // goal
    glVertex3d((X - 0.5)*L, (Y - 0.5)*L, 0.0);
    glVertex3d((X - 0.5)*L, (Y + 0.5)*L, 0.0);
    glVertex3d(-0.5*L, (Y + 0.5)*L, 0.0);
    glEnd();
    
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color[GRAY]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
    glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
    glBegin(GL_QUADS);
    for (i = 1; i < Y; i++)
        for (j = 0; j < X; j++)
        {
            GLdouble v[4][3];
            if (!((i^j) & 1))continue;
            v[0][0] = (j + 0 - 0.5)*L;
            v[0][1] = (i + 0 - 0.5)*L;
            v[0][2] = 0;
            v[1][0] = (j + 1 - 0.5)*L;
            v[1][1] = (i + 0 - 0.5)*L;
            v[1][2] = 0;
            v[2][0] = (j + 1 - 0.5)*L;
            v[2][1] = (i + 1 - 0.5)*L;
            v[2][2] = 0;
            v[3][0] = (j + 0 - 0.5)*L;
            v[3][1] = (i + 1 - 0.5)*L;
            v[3][2] = 0;
            glVertex3dv(v[0]);
            glVertex3dv(v[1]);
            glVertex3dv(v[2]);
            glVertex3dv(v[3]);
        }
    glEnd();
    
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color[BLACK]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
    glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
    glBegin(GL_QUADS);
    for (i = 0; i < Y; i++)
        for (j = 0; j < X; j++)
        {
            GLdouble v[4][3];
            if ((i^j) & 1)continue;
            v[0][0] = (j + 0 - 0.5)*L;
            v[0][1] = (i + 0 - 0.5)*L;
            v[0][2] = 0;
            v[1][0] = (j + 1 - 0.5)*L;
            v[1][1] = (i + 0 - 0.5)*L;
            v[1][2] = 0;
            v[2][0] = (j + 1 - 0.5)*L;
            v[2][1] = (i + 1 - 0.5)*L;
            v[2][2] = 0;
            v[3][0] = (j + 0 - 0.5)*L;
            v[3][1] = (i + 1 - 0.5)*L;
            v[3][2] = 0;
            glVertex3dv(v[0]);
            glVertex3dv(v[1]);
            glVertex3dv(v[2]);
            glVertex3dv(v[3]);
        }
    glEnd();
    
    glPopMatrix();
}

void drawJiki(void)
{
    glPushMatrix();
    
    glTranslatef(jiki.x, jiki.y, z);
    
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color[GREEN]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0);
    
    glutSolidCube(jiki.w);
    glPopMatrix();
}

void drawKabe(void)
{
    int i;
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color[RED]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
    glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
    
    for (i = 0; i < kabeIndex; i++)
    {
        if (flag_kabe[i])
        {
            glPushMatrix();
            glTranslatef(kabeList[i][0], kabeList[i][1], kabeList[i][2]);
            glutSolidCone(0.5, 1, 30, 30);
            glPopMatrix();
        }
    }
    glPopMatrix();
}

void drawJikiProj(int i)
{
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color[RED]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
    glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
    glTranslatef(jiki.tama[i].x, jiki.tama[i].y, z);
    glutSolidSphere(jiki.tama[i].r, 30, 30);
    glPopMatrix();
}

void drawTekiProj(int i, int j)
{
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color[MAGENTA]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
    glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
    glTranslatef(teki[i].tama[j].x, teki[i].tama[j].y, z);
    glutSolidSphere(teki[i].tama[j].r, 30, 30);
    glPopMatrix();
}

void drawTeki(int i)
{
    glPushMatrix();
    
    glTranslatef(teki[i].x, teki[i].y, z);
    
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color[BLUE]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, color[BLACK]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, color[WHITE]);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0);
    
    glutSolidCube(teki[i].w);
    glPopMatrix();
}

void aim(void)
{
    double aim_x, aim_y;
    glPushMatrix();
    glBegin(GL_LINES);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color[RED]);
    glVertex3d(jiki.x,jiki.y,z);
    aim_x = jiki.x + 50*cos(jiki.t);
    aim_y = jiki.y + 50*sin(jiki.t);
    glVertex3d(aim_x,aim_y,z);
    glEnd();
    glPopMatrix();
}
