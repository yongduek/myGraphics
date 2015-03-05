#include <vector>
#include <math.h>
#include <iostream>
using namespace std;

typedef unsigned char uchar;

struct mPointf {
    float x, y;
    mPointf(float xx=0, float yy=0) : x(xx), y(yy) {}
};

struct mPointi {
    int x, y;
    mPointi(int xx=0, int yy=0) : x(xx), y(yy) {}
};
struct mColor {
    uchar r, g, b;
    mColor (uchar rr=0, uchar gg=0, uchar bb=0) : r(rr), g(gg), b(bb) { }
};
//struct PointColor : public Pointi, public mColor {};
struct PointColor {
    mPointi p;
    mColor c;
    PointColor(mPointi pp=mPointi(0,0), mColor cc=mColor(0,0,0)) { p=pp; c=cc; }
};

struct mWindow {
    float l, r, b, t;
    void set(float ll, float rr, float bb, float tt) {l=ll, r=rr, b=bb, t=tt;}
};

const mColor mR(255,0,0), mG(0,255,0), mB(0,0,255);

#define myPOINTS 0
#define myLINE_LOOP 1
#define myLINE_STRIP 2

struct myCanvas {
    uchar *pixels; // RGB
    const int width=800, height=600;
    const int bpp = 3;

    mWindow viewport;
    bool flagViewport = false;

    mWindow worldWindow;
    bool flagWorldWindow = false;

    float A, B, C, D; // window2viewport transform
    void init ()
    {
    pixels = new uchar[width*height*3];
    for (int i=0; i<height; i++)
        for (int j=0; j<width; j++)
            for (int k=0; k<bpp; k++)
                pixels[bpp*(width*i + j) + k] = 0;

    viewport.set (0, width, 0, height);
    worldWindow.set (0, width, 0, height);
    computeABCD();
    }
    
    void setViewport(float ll, float rr, float bb, float tt) {
        viewport.set (ll,rr,bb,tt);
        computeABCD();
    }
    void setWorldWindow(float ll, float rr, float bb, float tt) {
        worldWindow.set (ll,rr,bb,tt);
        computeABCD();
    }
    
    void computeABCD() {
        A = (viewport.r - viewport.l)/(worldWindow.r-worldWindow.l);
        B = viewport.l - A * worldWindow.l;
        C = (viewport.t - viewport.b)/(worldWindow.t-worldWindow.b);
        D = viewport.b - C * worldWindow.b;
    }
    
    vector<mPointi> getPixelCoordinates(vector<mPointf>& vec) {
        vector<mPointi> vi;
        for (int i=0; i<vec.size(); i++)
            vi.push_back( mPointi(roundf(A*vec[i].x+B), roundf(C*vec[i].y+D) ) );
        return vi;
    }
    
    void draw (int type, vector<mPointf>& vec) {
        vector<mPointi> vi = getPixelCoordinates(vec);       
        if (type==myLINE_STRIP) {
            //std::cerr << "drawing myLINE_STRIP" << std::endl;
            for (int i=1; i<vec.size(); i++)
                drawLine (vi[i-1], vi[i]);
        }
    }

    void draw (int type, vector<mPointf>& vec, vector<mColor>& vcolor) {
        vector<mPointi> vi = getPixelCoordinates(vec);
        if (type==myLINE_STRIP) {
            for (int i=1; i<vec.size(); i++)
                drawLine (vi[i-1], vi[i], vcolor[i-1], vcolor[i]);
        }
    }
    
    mColor randomColor();
    void drawPixel(int x0, int y0, uchar r, uchar g, uchar b);
    void drawPixel(int x0, int y0, mColor c);
    void drawLineX (int x1, int y1, int x2, int y2, mColor c1, mColor c2);
    void drawLineY (int x1, int y1, int x2, int y2, mColor c1, mColor c2);
    void drawLine (int x1, int y1, int x2, int y2, mColor c1=mR, mColor c2=mB);
    void drawLine (mPointi p1, mPointi p2, mColor c1=mR, mColor c2=mB);
    
    void drawLineX (vector<PointColor>& pcv,
                    int x1, int y1, int x2, int y2, mColor c1, mColor c2);
    void drawLineY (vector<PointColor>& pcv,
                    int x1, int y1, int x2, int y2, mColor c1, mColor c2);
    void drawLine (vector<PointColor>& pcv,
                   int x1, int y1, int x2, int y2, mColor c1=mR, mColor c2=mB);
    
    void drawTriangle (int x1, int y1, int x2, int y2, int x3, int y3,
                       mColor c1=mR, mColor c2=mG, mColor c3=mB);
    void drawTriangle (mPointi p1, mPointi p2, mPointi p3,
                       mColor c1=mR, mColor c2=mG, mColor c3=mB);
        
    void drawTriangleFill (int x1, int y1, int x2, int y2, int x3, int y3,
                           mColor c1=mR, mColor c2=mG, mColor c3=mB);
    void drawTriangleFill (mPointi p1, mPointi p2, mPointi p3,
                           mColor c1=mR, mColor c2=mG, mColor c3=mB);
    void drawCircle (int x0, int y0, int r, mColor c1, int nSplit);
    void drawCircleFilled (int x0, int y0, int r, mColor c1=mR, int nSplit=30);
    
};

float  lip (int x, int r1, int r2, int x1, int x2);
mColor lip (int x, mColor c1, mColor c2, int x1, int x2);

// EOF //