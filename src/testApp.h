#pragma once

#include "ofMain.h"
#include <fstream>
#include "ofxToast.h"

class testApp : public ofBaseApp, ofThread{
    
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
    bool            bPushLoad;
    bool            bAnal;
    bool            bPushAnal;
    bool            bCreate;
    bool            bFileDone;
    bool            bPushCreate;
    string          folderPath;
    string          tmpPath;
    
    vector<string>  colorInfomationArray;
    vector<string>  colorInfomationHTML;
    vector<ofColor> colorArray;
    vector<int>     colorNumber;
    vector<ofColor> colorTable;
    
    int             imageCnt;
    int             colorCnt;
    
    ofxToast        toast;
    ofFileDialogResult openFileResult;
    
    //input text
    string          chgColorNum;
    int             pos; // key position
};
