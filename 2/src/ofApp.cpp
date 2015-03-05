#include "ofApp.h"
#include "myGL.h"


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

    canvas.drawPixel (100, 400, 255, 255, 0);
    canvas.drawPixel (100, 401, 255, 255, 0);
    
    static int cnt=0;
//    if (cnt++ < 100)
        {
        //drawLine (random()%width, random()%height, random()%width, random()%height);
    
//        drawTriangleFill (random()%width, random()%height,
//                          random()%width, random()%height,
//                          random()%width, random()%height,
//                          randomColor(), randomColor(), randomColor());
        
        //    canvas.drawPixel (100, 400, 255, 255, 0);
//        canvas.drawCircle(random()%500, random()%600, 30 + random()%300, canvas.randomColor());
        canvas.drawCircleFilled(random()%1000, random()%700, 30 + random()%300,
                         canvas.randomColor(), 3 + random()%10);
        
        }

    canvas.setWorldWindow (-2.5, 2.5, -0.5, 1.4);
    canvas.setViewport(0, canvas.width, canvas.height, 0);

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
