#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetBackgroundAuto(true);
    ofSetBackgroundColor(255);
    bLoad = false;
    
    imageCnt = 0;
    colorCnt = 0;
}

//--------------------------------------------------------------
void testApp::update(){
    if (bLoad) {
        ImageLoad();
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(0);
    
    ofDrawBitmapString("Image Counter : " + ofToString(imageCnt), 10, 50);
    ofDrawBitmapString("color Counter : " + ofToString(colorCnt), 10, 70);
    
    if (colorTable.size() > 0) {
        ofDrawBitmapString("Used Color : " + ofToString(colorTable.size()), 10, 90);
    }else{
        ofDrawBitmapString("Used Color : 0", 10, 90);
    }
    
    ofDrawBitmapString("press '1' : Load Images\nPress '2' : Analysis\nPress '3' : make file", 10, 120);
    
    
}

//--------------------------------------------------------------
void testApp::ImageLoad(){
    ofColor color;
    dir.listDir("images");
    imageCnt = 0;
    colorCnt = 0;
    
    colorArray.clear();
    colorInfomationArray.clear();
    
    int imgCnt = dir.size();
    
    for (int i = 0; i < imgCnt; i++) {
        string tmpstr = dir[i].path();
        img.loadImage(tmpstr);
        imageCnt++;
        
        for(int i=0; i < img.width; i++){
            for(int j=0; j<img.height; j++){
                colorArray.push_back(color);
                color = img.getColor(i,j);
                colorCnt++;
                
                string tmp
                = ofToString(colorCnt)
                + " "
                + ofToString(imageCnt)
                + " "
                + ofToString(i)
                + " "
                + ofToString(j)
                + " "
                + ofToString(int(color.r))
                + ","
                + ofToString(int(color.g))
                + ","
                + ofToString(int(color.b));
                /*
                 + ","
                 + ofToHex(color.r)
                 + ofToHex(color.g)
                 + ofToHex(color.b);
                 */
                
                colorInfomationArray.push_back(tmp);
            }
        }
    }
    toast.addText("Loaded");
    bLoad = false;
}

//--------------------------------------------------------------
void testApp::printColor(){
    if(colorInfomationArray.size()>0){
        ofstream file;
        file.open ("result.txt", ios::out);
        for (int i=0; i< colorInfomationArray.size() ; i++) {
            file << colorInfomationArray[i] << " " << colorNumber[i] << endl;
        }
        file.close();
        toast.addText("Done");
    }
    
    if(colorTable.size()>0){
        ofstream file;
        file.open ("colorTable.txt", ios::out);
        for (int i=0; i< colorTable.size() ; i++) {
            file << i << " " << ofToString((int)colorTable[i].r) << "," << ofToString((int)colorTable[i].g) << "," << ofToString((int)colorTable[i].b) << endl;
        }
        file.close();
        toast.addText("Done");
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    switch (key) {
        case '1':
            bLoad = true;
            break;
            
        case '3':
            printColor();
            break;
            
        case '2':
            ColorTable();
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------------------
int testApp::palette(ofColor c){
    ofColor tmpColor;
    tmpColor = c;
    
    if(colorTable.size() == 0)
    {
        colorTable.push_back(tmpColor);
    }
    else if(colorTable.size() > 0)
    {
        bool bCheck = true;
        for (int i=0; i<colorTable.size(); i++)
        {
            if(colorTable[i] == tmpColor)
            {
                bCheck = false;
                return colorTable.size();
            }
        }
        if(bCheck){
            colorTable.push_back(tmpColor);
        }
    }
    return colorTable.size();
}

//--------------------------------------------------------------
void testApp::ColorTable(){
    for (int i=0; i<colorArray.size(); i++) {
        palette(colorArray[i]);
    }
    
    for (int i=0; i<colorArray.size(); i++) {
        for (int j=0; j< colorTable.size(); j++) {
            if(colorArray[i] == colorTable[j]){
                colorNumber.push_back(j);
                break;
            }
        }
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
    
}
