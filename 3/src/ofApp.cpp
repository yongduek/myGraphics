#include "ofApp.h"
#include "myGL.h"
#include <glm/gtx/string_cast.hpp>


myCanvas canvas;

//--------------------------------------------------------------
void imshow()
{
    ofImage ofImg;
    ofImg.setFromPixels(canvas.pixels, canvas.width, canvas.height, OF_IMAGE_COLOR);
    // ofImageType: OF_IMAGE_GRAYSCALE, OF_IMAGE_COLOR, OF_IMAGE_COLOR_ALPHA
    
    ofImg.setColor(100, 100, ofColor(255,0,0));
    ofImg.update(); // don't forget to update after changing ofImage, or it won't come up.
    ofImg.draw(0,0);
    
}

void ofApp::setup(){

    canvas.init();

}

//--------------------------------------------------------------
void ofApp::update(){
    canvas.Clear();
    canvas.drawPixel (100, 401, 255, 255, 0);
    
    static int cnt=0;

//    canvas.drawCircleFilled(random()%1000, random()%700, 30 + random()%300,
//                         canvas.randomColor(), 3 + random()%10);
    

    canvas.setWorldWindow (-1.9, 1.9, -1.9, 1.9);
    canvas.setViewport(0, canvas.height, canvas.height, 0);

    vector<mPointf> xaxis;
    vector<mColor> xaxisColor;
    xaxis.push_back ( mPointf(-2.2, 0) );
    xaxis.push_back ( mPointf(2.2, 0) );
    xaxisColor.push_back (mColor(255,255,200));
    xaxisColor.push_back (mColor(255,255,200));
    canvas.draw(myLINE_STRIP, xaxis, xaxisColor);

    vector<mPointf> vert;
    vector<mColor> vertColor;
    for (float x=-2.; x<=2.; x+=0.01) {
        float y = sin (2*M_PI*x) / (2*M_PI*x);
        vert.push_back (mPointf(x,y));
        vertColor.push_back (mColor(255,0,0));
    }
    canvas.draw(myLINE_STRIP, vert, vertColor);
    
    
    vector<mPointf> tri;
    tri.push_back(mPointf(0,0));
    tri.push_back(mPointf(1,0));
    tri.push_back(mPointf(1,1));
    canvas.enableFilledDraw();
    static float angle = 0;
    angle += DEG2RAD(1);
//    float angle = glutGet(GLUT_ELAPSED_TIME) / 1000.0 * 45;  // 45° per second
    glm::mat4 X=glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.f,0.f,1.f));
    cerr << "rotation angle=" << angle << endl;
    cerr << "R=" << glm::to_string (X) << endl;
    canvas.setModelingMatrix(X);
    canvas.draw(myTRIANGLES, tri, mColor(255,255,0));
    canvas.disableFilledDraw();
}

//--------------------------------------------------------------
void ofApp::draw(){

    imshow ();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    cerr << "mouseReleased: " << x << "  " << y << endl;
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
