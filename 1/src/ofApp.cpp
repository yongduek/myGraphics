#include "ofApp.h"

typedef unsigned char uchar;
uchar *pixels; // RGB
int width, height;

void imshow()
{
    ofImage ofImg;
    ofImg.setFromPixels(pixels, width, height, OF_IMAGE_COLOR);
    // ofImageType: OF_IMAGE_GRAYSCALE, OF_IMAGE_COLOR, OF_IMAGE_COLOR_ALPHA
    
    ofImg.setColor(100, 100, ofColor(255,0,0));
    ofImg.update(); // don't forget to update after changing ofImage, or it won't come up.
    ofImg.draw(0,0);
}

void drawPixel(int x0, int y0, uchar r, uchar g, uchar b)
{
    for (int i=-2; i<=2; i++)
        for (int j=-2; j<=2; j++) {
            int x = x0 + j;
            int y = y0 + i;
            int index = width*3*y + 3*x;
            pixels [index + 0] = r;
            pixels [index + 1] = g;
            pixels [index + 2] = b;
        }
}

//--------------------------------------------------------------
void ofApp::setup(){

    width = 800;
    height = 600;
    pixels = new uchar[width*height*3];
    for (int i=0; i<height; i++)
        for (int j=0; j<width; j++)
            for (int k=0; k<3; k++)
                pixels[3*(width*i + j) + k] = 0;
}

//--------------------------------------------------------------
void ofApp::update(){

    drawPixel (100, 400, 255, 0, 0);
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
