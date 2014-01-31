#pragma once

#include "ofMain.h"
#include <fstream>
#include "ofxToast.h"

class testApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void ImageLoad();
    void printColor();
    int  palette(ofColor c);
    void ColorTable();
    
    ofImage         img;
    ofDirectory     dir;
    bool            bLoad;
    
    vector<string>  colorInfomationArray;
    vector<ofColor> colorArray;
    vector<int>     colorNumber;
    vector<ofColor> colorTable;
    
    int             imageCnt;
    int             colorCnt;
    
    ofxToast        toast;
};
