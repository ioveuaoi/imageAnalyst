#pragma once

#include "ofMain.h"
#include <fstream>

//Valid date until...
#define YEAR    2014
#define MON     2
#define DAY     28
#define HOUR    3
#define MINUTE  30

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
    
    
    bool License(int year, int month, int day, int hour, int minute);
    void ImageLoad();
    void printColor();
    int  palette(ofColor c);
    void ColorTable();
    void saveImage(vector<int> selectNum, ofColor color);
    void stringCutter(string str, vector<int> &ch, char knife);
    
    ofImage         img;
    ofDirectory     dir;
    bool            bLoad;
    bool            bPushLoad;
    bool            bAnal;
    bool            bPushAnal;
    bool            bCreate;
    bool            bFileDone;
    bool            bPushCreate;
    bool            bImageMakePush;
    bool            bImageMakeStart;
    string          folderPath;
    string          tmpPath;
    
    vector<string>  colorInfomationArray;
    vector<string>  colorInfomationHTML;
    vector<ofColor> colorArray;
    vector<int>     colorNumber;
    vector<ofColor> colorTable;
    
    int             imageCnt;
    int             colorCnt;
    
    ofFileDialogResult openFileResult;
    
    int             imgWidth;
    int             imgHeight;
    
    //input text
    string          chgColorNumStr;
    int             pos; // key position
    
    vector<int>     chgColorNum;
    vector<int>     cutterInt;
    ofColor         wantColor;
    int             wr;
    int             wg;
    int             wb;
    bool            bStartRgb;
};
