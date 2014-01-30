#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetBackgroundAuto(true);
    ofSetBackgroundColor(0);
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
    
    ofDrawBitmapString("Image Counter : " + ofToString(imageCnt), 50, 50);
    ofDrawBitmapString("color Counter : " + ofToString(colorCnt), 50, 100);
    if (vectorColor.size() > 0) {
        ofDrawBitmapString("Vector Counter : " + ofToString(vectorColor.size()), 50, 200);
    }
}

//--------------------------------------------------------------
void testApp::ImageLoad(){
    dir.listDir("images");
    imageCnt = 0;
    colorCnt = 0;
    int imgCnt = dir.size();
    
    for (int i = 0; i < imgCnt; i++) {
        string tmpstr = dir[i].path();
        img.loadImage(tmpstr);
        
        imageCnt++;
        for(int i=0; i < img.width; i++){
            for(int j=0; j<img.height; j++){
                color = img.getColor(i,j);
                colorCnt++;
                string tmp = ofToString(colorCnt) + "   " + ofToString(imageCnt) + "    " + ofToString(i) + "   " + ofToString(j) + "   " + ofToHex(color.r) + "," + ofToHex(color.g) + "," + ofToHex(color.b);
                vectorColor.push_back(tmp);
            }
        }
    }
    toast.addText("Image Loaded.");
    bLoad = false;
}

//--------------------------------------------------------------
void testApp::printColor(){
    if(vectorColor.size()>0){
        ofstream file;
        file.open ("result.txt", ios::out);
        for (int i=0; i< vectorColor.size() ; i++) {
            file << vectorColor[i] << endl;
        }
        file.close();
            toast.addText("File is Written.");
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    switch (key) {
        case 'l':
            bLoad = true;
            break;
            
        case 'p':
            printColor();
            break;
            
        default:
            break;
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
