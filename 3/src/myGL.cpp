#include "myGL.h"
#include <glm/gtx/string_cast.hpp>
#include <stdlib.h>
#include <math.h>
#include <algorithm>

//typedef unsigned char uchar;
//
//struct mPointi {
//    int x, y;
//    mPointi(int xx=0, int yy=0) : x(xx), y(yy) {}
//};
//struct mColor {
//    uchar r, g, b;
//    mColor (uchar rr=0, uchar gg=0, uchar bb=0) : r(rr), g(gg), b(bb) { }
//};
////struct PointColor : public Pointi, public mColor {};
//struct PointColor {
//    mPointi p;
//    mColor c;
//    PointColor(mPointi pp=mPointi(0,0), mColor cc=mColor(0,0,0)) { p=pp; c=cc; }
//};
//
//struct mWindow {
//    float l, r, b, t;
//    void set(float ll, float rr, float bb, float tt) {l=ll, r=rr, b=bb, t=tt;}
//};


//struct myCanvas {
//uchar *pixels; // RGB
//const int width=800, height=600;
//const int bpp = 3;
//
//mWindow viewport;
//bool flagViewport = false;
//
//mWindow worldWindow;
//bool flagWorldWindow = false;
//
//const mColor mR(255,0,0), mG(0,255,0), mB(0,0,255);

mColor myCanvas::randomColor() {
    return mColor(random()%256, random()%256, random()%256);
}

float lip (int x, int r1, int r2, int x1, int x2)
{
    float t = fabs( (x-x1)/(float)(x2-x1) );
    float r = (1. - t)*r1 + t*r2;
    return r;
}

mColor lip (int x, mColor c1, mColor c2, int x1, int x2)
{
    float t = fabs( (x-x1)/(float)(x2-x1) );
    mColor c;
    c.r = lip(x,c1.r, c2.r, x1, x2);
    c.g = lip(x,c1.g, c2.g, x1, x2);
    c.b = lip(x,c1.b, c2.b, x1, x2);
    return c;
}

void myCanvas::drawPixel(int x0, int y0, uchar r, uchar g, uchar b)
{
    if (x0<0 || x0>=width || y0<0 || y0>=height) return;
    int index = bpp*(width*y0 + x0);
    pixels [index + 0] = r;
    pixels [index + 1] = g;
    pixels [index + 2] = b;
}

void myCanvas::drawPixel(int x0, int y0, mColor c)
{
    drawPixel(x0, y0, c.r, c.g, c.b);
}

void myCanvas::drawLineX (int x1, int y1, int x2, int y2, mColor c1, mColor c2)
{
    int dx = x1<x2 ? 1 : -1;
    float m = (y2-y1)/(float)(x2-x1);
    float b = -m*x1 + y1;
    mColor c;
    for (int x=x1; x!=x2; x+=dx) {
        int y = (int)roundf(m*x+b);
        c = lip (x, c1, c2, x1, x2);
        drawPixel(x, y, c);
    }
    drawPixel(x2, y2, c2);
}

void myCanvas::drawLineY (int x1, int y1, int x2, int y2, mColor c1, mColor c2)
{
    int dy = y1<y2 ? +1 : -1;
    float m = (x2-x1)/(float)(y2-y1);
    float b = -m*y1 + x1;
    mColor c;
    for (int y=y1; y!=y2; y+=dy) {
        int x = (int)roundf(m*y+b);
        c = lip (y, c1, c2, y1, y2);
        drawPixel(x, y, c);
    }
    drawPixel(x2, y2, c2);
}

void myCanvas::drawLine (int x1, int y1, int x2, int y2, mColor c1, mColor c2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    if (fabs(dy) < fabs(dx))
        drawLineX(x1, y1, x2, y2, c1, c2);
    else
        drawLineY(x1, y1, x2, y2, c1, c2);
}

void myCanvas::drawLine (mPointi p1, mPointi p2, mColor c1, mColor c2)
{
    //    cerr << "drawLine(" << p1.x << " " << p1.y << " : " << p2.x << " " << p2.y << ") " << endl;
    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;
    if (fabs(dy) < fabs(dx))
        drawLineX(p1.x, p1.y, p2.x, p2.y, c1, c2);
    else
        drawLineY(p1.x, p1.y, p2.x, p2.y, c1, c2);
}

void myCanvas::drawLineX (vector<PointColor>& pcv,
                int x1, int y1, int x2, int y2, mColor c1, mColor c2)
{
    int dx = x1<x2 ? 1 : -1;
    float m = (y2-y1)/(float)(x2-x1);
    float b = -m*x1 + y1;
    mColor c;
    for (int x=x1; x!=x2; x+=dx) {
        int y = roundf(m*x+b);
        c = lip (x, c1, c2, x1, x2);
        //drawPixel(x, y, c);
        PointColor pc;
        pc.p = mPointi(x,y);
        pc.c = c;
        pcv.push_back(pc);
    }
}

void myCanvas::drawLineY (vector<PointColor>& pcv,
                int x1, int y1, int x2, int y2, mColor c1, mColor c2)
{
    int dy = y1<y2 ? +1 : -1;
    float m = (x2-x1)/(float)(y2-y1);
    float b = -m*y1 + x1;
    mColor c;
    for (int y=y1; y!=y2; y+=dy) {
        int x = roundf(m*y+b);
        c = lip (y, c1, c2, y1, y2);
        //drawPixel(x, y, c);
        PointColor pc;
        pc.p = mPointi(x,y);
        pc.c = c;
        //drawPixel(x, y, c);
        pcv.push_back(pc);
    }
}
void myCanvas::drawLine (vector<PointColor>& pcv,
                         int x1, int y1, int x2, int y2, mColor c1, mColor c2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    if (fabs(dy) < fabs(dx))
        drawLineX(pcv, x1, y1, x2, y2, c1, c2);
    else
        drawLineY(pcv, x1, y1, x2, y2, c1, c2);
}

void myCanvas::drawTriangle (int x1, int y1, int x2, int y2, int x3, int y3,
                             mColor c1, mColor c2, mColor c3)
{
    drawLine(x1,y1,x2,y2,c1,c2);
    drawLine(x1,y1,x3,y3,c1,c3);
    drawLine(x3,y3,x2,y2,c3,c2);
}
void myCanvas::drawTriangle (mPointi p1, mPointi p2, mPointi p3,
                             mColor c1, mColor c2, mColor c3)
{
    drawLine (p1, p2, c1, c2);
    drawLine (p2, p3, c2, c3);
    drawLine (p3, p1, c3, c1);
}

bool comparePointColor (PointColor a, PointColor b)
{
    //    return a.p.y < b.p.y;
    return a.p.y==b.p.y ? a.p.x < b.p.x : a.p.y < b.p.y;
}


void myCanvas::drawTriangleFill (int x1, int y1, int x2, int y2, int x3, int y3,
                       mColor c1, mColor c2, mColor c3)
{
    vector<PointColor> pcv;
    drawLine(pcv, x1,y1,x2,y2,c1,c2);
    drawLine(pcv, x1,y1,x3,y3,c1,c3);
    drawLine(pcv, x3,y3,x2,y2,c3,c2);
    
    pcv.push_back(PointColor(mPointi(x1,y1), c1));
    pcv.push_back(PointColor(mPointi(x2,y2), c2));
    pcv.push_back(PointColor(mPointi(x3,y3), c3));
    
    std::sort (pcv.begin(), pcv.end(), comparePointColor);
    
    vector<PointColor>::iterator it=pcv.begin();
    while (it != pcv.end()) {
        //        PointColor pc = *it;
        //        cerr << pc.p.x << ' ' << pc.p.y << endl;
        
        vector<PointColor> line;
        line.push_back(*it);
        while (it!=pcv.end() && it->p.y == line[0].p.y)
            line.push_back(*it++);
        
        //        if (line[0].p.y > 405 && line[0].p.y < 414) {
        //            for (int i=0; i<line.size(); i++)
        //                cerr << "(" << line[i].p.x << "," << line[i].p.y <<")";
        //            cerr << endl;
        //        }
        if ( (line.size()==1)
            || (line.size()==2 && line[0].p.x==line[1].p.x && line[0].p.y==line[1].p.y) ) {
            drawPixel(line[0].p.x, line[0].p.y, line[0].c.r, line[0].c.g, line[0].c.b);
            //            drawCircle(line[0].p.x, line[0].p.y, 5);
        }
        else {
            drawLine(line[0].p, line[line.size()-1].p, line[0].c, line[line.size()-1].c);
        }
    }
    return;
}
void myCanvas::drawTriangleFill (mPointi p1, mPointi p2, mPointi p3,
                                 mColor c1, mColor c2, mColor c3)
{
    drawTriangleFill(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, c1, c2, c3);
}

void myCanvas::drawCircle (int x0, int y0, int r, mColor c1, int nSplit)
{
    mPointi p(x0+r, y0 + 0);
    for (int i=1; i<=nSplit; i++) {
        mPointi q (round(x0 + r*cos(i*2*M_PI/nSplit)),
                   round(y0 + r*sin(i*2*M_PI/nSplit)));
        drawLine(p, q, c1, c1);
        p = q;
    }
}

void myCanvas::drawCircleFilled (int x0, int y0, int r, mColor c1, int nSplit)
{
    mPointi p0(x0, y0);
    vector<mPointi> p;
    for (int i=0; i<=nSplit; i++) {
        mPointi q (round(x0 + r*cos(i*2*M_PI/nSplit)),
                   round(y0 + r*sin(i*2*M_PI/nSplit)));
        p.push_back(q);
    }
    
    for (int i=1; i<p.size(); i++)
        drawTriangleFill(p0, p[i-1], p[i], c1, c1, c1);
    
}

void myCanvas::drawArrays(int type, vector<mPointf>& vert, vector<mColor>& color)
{
    
}
//glm::vec3
//
//void myCanvas::drawArrays(int type, float vert[], float color[], int nVert, int nDim)
//{
//    if (type == myLINE_STRIP) {
//        glm::vec4 v = glm::vec4(vert[0], vert[1], 0.f, 1.f);
//        v_proj = this->viewportM * this->MVP * v;
//        for (int i=nDim; i<nVert; i+= nDim) {
//            glm::vec4 v2 = glm::vec4(vert[i], vert[i+1], 0.f, 1.f);
//            v2 = this->viewportM * this->MVP * v2;
//            drawLine(round(v[0]), round(v[1]), round(v2[0]), round(v2[1]));
//            v = v2;
//        }
//    }
//}


void myCanvas::draw (int type, vector<mPointf>& vec_src, mColor vcolor)
{
    cerr << glm::to_string (modelingMatrix) << endl;
    
    vector<mPointf> vec;
    for (int i=0; i<vec_src.size(); i++) {
        glm::vec4 p2 = modelingMatrix * glm::vec4(vec_src[i].x, vec_src[i].y, 0.f, 1.f);
        cerr << i <<  ": " << p2.x << " " << p2.y << endl;
        vec.push_back( mPointf(p2.x, p2.y) );
    }
    cerr << "---" << endl;
    
    vector<mPointi> vi = getPixelCoordinates(vec);
    for (int i=0; i<vi.size(); i++) {
        cerr << i <<  ": " << vi[i].x << " " << vi[i].y << endl;
    }
    cerr << "---" << endl;
    
    if (type==myLINE_STRIP) {
        for (int i=1; i<vec.size(); i++)
            drawLine (vi[i-1], vi[i], vcolor, vcolor);
    }
    else if (type==myTRIANGLES) {
        if (flagDrawFilled) {
            for (int i=0; i<vi.size(); i+=3)
                drawTriangleFill(vi[i], vi[i+1], vi[i+2], vcolor, vcolor, vcolor);
        }
        else {
            for (int i=0; i<vi.size(); i+=3)
                drawTriangle(vi[i], vi[i+1], vi[i+2], vcolor, vcolor, vcolor);
        }
    }
}

// EOF //