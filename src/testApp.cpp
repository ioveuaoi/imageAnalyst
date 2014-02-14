#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetBackgroundColor(255,255,255);
    ofSetVerticalSync(true);
    ofSetBackgroundAuto(true);
    
    bLoad = false;
    bPushLoad = false;
    bAnal = false;
    bPushAnal = false;
    bCreate = false;
    bPushCreate = false;
    bFileDone = false;
    
  	pos      = 0;
    imageCnt = 0;
    colorCnt = 0;
    folderPath = "";
}


//--------------------------------------------------------------
void testApp::update(){
    if(bLoad){
        ImageLoad();
    }
    
    if(bAnal){
        ColorTable();
        bAnal = false;
    }
    
    if(bCreate){
        printColor();
        bCreate = false;
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    if(folderPath == "")
        ofSetColor(100, 100, 100);
    else
        ofSetColor(100, 200, 100);
    ofRect(10, 10, 100, 40);
    
    if(!imageCnt)
        ofSetColor(100, 100, 100);
    else
        ofSetColor(100, 200, 100);
    ofRect(120, 10, 100, 40);
    
    if(!colorTable.size())
        ofSetColor(100, 100, 100);
    else
        ofSetColor(100, 200, 100);
    ofRect(230, 10, 100, 40);
    
    if(!bFileDone)
        ofSetColor(100, 100, 100);
    else
        ofSetColor(100, 200, 100);
    ofRect(340, 10, 100, 40);
    
    ofSetColor(0, 0, 0);
    ofDrawBitmapString(" Open(O)", 10, 35);
    ofDrawBitmapString(" Load(L)", 120, 35);
    ofDrawBitmapString(" Analysts(A)", 230, 35);
    ofDrawBitmapString(" Create(C)", 340, 35);
    
    if(bPushLoad){
        ofSetColor(100, 100, 100);
        ofRect(0, 0, 450, 200);
        ofSetColor(255, 255, 255);
        ofDrawBitmapString("Loading... ", 190, 100);
        bLoad = true;
    }
    
    if(bPushAnal){
        ofSetColor(100, 100, 100);
        ofRect(0, 0, 450, 200);
        ofSetColor(255, 255, 255);
        ofDrawBitmapString("Analyst... ", 190, 100);
        bAnal = true;
    }
    
    if(bPushCreate){
        ofSetColor(100, 100, 100);
        ofRect(0, 0, 450, 200);
        ofSetColor(255, 255, 255);
        ofDrawBitmapString("Create... ", 190, 100);
        bCreate = true;
    }
    
    ofSetColor(0);
    if(folderPath.length() >= 35)
    {
        tmpPath = folderPath;
        while (tmpPath.size() > 35) {
            tmpPath.erase(tmpPath.begin());
        }
        ofDrawBitmapString("Folder Path : ..." + tmpPath, 10, 120);
    }
    else
        ofDrawBitmapString("Folder Path : " + folderPath, 10, 120);
    
    ofDrawBitmapString("Loaded Image : " + ofToString(imageCnt), 10, 140);
    ofDrawBitmapString("Pixel : " + ofToString(colorCnt), 10, 160);
    
    if (colorTable.size() > 0) {
        ofDrawBitmapString("Used Color : " + ofToString(colorTable.size()), 10, 180);
    }else{
        ofDrawBitmapString("Used Color : 0", 10, 180);
    }
    
    
}

//--------------------------------------------------------------
void testApp::ImageLoad(){
    try{
        ofColor color;
        dir.listDir(openFileResult.getPath());
        imageCnt = 0;
        colorCnt = 0;
        
        colorArray.clear();
        colorInfomationArray.clear();
        colorInfomationHTML.clear();
        
        int imgCnt = dir.size();
        for (int i = 0; i < imgCnt; i++) {
            
            string tmpstr = dir[i].path();
            
            if(dir[i].getExtension() == "jpg"  ||
               dir[i].getExtension() == "JPG"  ||
               dir[i].getExtension() == "jpeg" ||
               dir[i].getExtension() == "JPEG" ||
               dir[i].getExtension() == "png"  ||
               dir[i].getExtension() == "PNG"  ||
               dir[i].getExtension() == "bmp"  ||
               dir[i].getExtension() == "BMP"  ||
               dir[i].getExtension() == "gif"  ||
               dir[i].getExtension() == "GIF"){
                img.loadImage(tmpstr);
                imageCnt++;
                
                int imgPixel = img.width*img.height;
                
                for(int i=0; i < img.width; i++){
                    for(int j=0; j<img.height; j++){
                        /*
                         string strColorCnt = "";
                         string strImageCnt = "";
                         string strWidthCnt = "";
                         string strHeightCnt = "";
                         string strColorR = "";
                         string strColorG = "";
                         string strColorB = "";
                         */
                        
                        color = img.getColor(i,j);
                        colorArray.push_back(color);
                        colorCnt++;
                        
                        string tmp
                        = ofToString(colorCnt)
                        + ","
                        + ofToString(imageCnt)
                        + ","
                        + ofToString(i+1)
                        + ","
                        + ofToString(j+1)
                        + ","
                        + ofToString(int(color.r))
                        + ","
                        + ofToString(int(color.g))
                        + ","
                        + ofToString(int(color.b))
                        + ",";
                        
                        string tmpHtml
                        = "<tr><td align =\"right\">" + ofToString(colorCnt)
                        + "</td>"
                        + "<td align =\"right\">" + ofToString(imageCnt)
                        + "</td>"
                        + "<td align =\"right\">" + ofToString(i+1)
                        + "</td>"
                        + "<td align =\"right\">" + ofToString(j+1)
                        + "</td>"
                        + "<td bgcolor =\"#" + ofToHex(color.r) + ofToHex(color.g) + ofToHex(color.b) + "\">" + ofToString(int(color.r))
                        + ","
                        + ofToString(int(color.g))
                        + ","
                        + ofToString(int(color.b))
                        + "</td>";
                        
                        colorInfomationArray.push_back(tmp);
                        colorInfomationHTML.push_back(tmpHtml);
                    }
                }
                
            }
        }
        
        if(imageCnt > 0)
            toast.addText("Loaded");
        bPushLoad = false;
    }catch(exception e){
        toast.addText("Load fail");
    }
    bLoad = false;
}

//--------------------------------------------------------------
void testApp::printColor(){
    try {
        
        //for TEXT
        if(colorInfomationArray.size()>0){
            ofstream file;
            file.open ("result.txt", ios::out);
            for (int i=0; i< colorInfomationArray.size() ; i++) {
                file << colorInfomationArray[i] << colorNumber[i]+1 << "/" << endl;
            }
            file.close();
            toast.addText("Done");
            bFileDone = true;
        }
        
        //for HTML
        if(colorInfomationHTML.size()>0){
            ofstream file;
            file.open ("result.html", ios::out);
            file << "<html><head><title>Result</title></head><body><table border =\"1\"><tr align =\"center\"><td>Pixel</td><td>Image</td><td>X</td><td>Y</td><td>Color</td><td>Match</td></tr>" << endl;
            for (int i=0; i< colorInfomationHTML.size() ; i++) {
                file << colorInfomationHTML[i] << "<td align =\"right\">" << colorNumber[i]+1 << "</td></tr>" << endl;
            }
            file << "</td></tr></table></body></html>" << endl;
            file.close();
            toast.addText("Done");
            bFileDone = true;
        }
        
        //for HTML
        if(colorTable.size()>0){
            ofstream file;
            file.open ("colorTable.html", ios::out);
            file << "<html><head><title>Color Table</title></head><body><table border =\"1\"><tr align =\"center\"><td>Number</td><td>Color</td><td>RGB</td></tr>" << endl;
            for (int i=0; i< colorTable.size() ; i++) {
                file << "<tr>" << endl;
                file << "<td align =\"right\">" << i+1 << "</td>" << endl;
                file << "<td bgcolor=\"#" << ofToHex(colorTable[i].r)+ofToHex(colorTable[i].g)+ofToHex(colorTable[i].b) << "\"/>" << endl;
                file << "<td align =\"center\">" << ofToString((int)colorTable[i].r) << "," << ofToString((int)colorTable[i].g) << "," << ofToString((int)colorTable[i].b) << "</td></tr>" << endl;
            }
            file << "</table></body></html>" << endl;
            file.close();
            toast.addText("Done");
            bFileDone = true;
        }
        bPushCreate = false;
    }catch(exception e){
        
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    /*
     if(key == 13)
     key = '\n';
     if(key == 8 || key == 127){
     if( pos != 0 ){
     pos--;
     chgColorNum = chgColorNum.substr(0,pos);
     }else
     chgColorNum = "";
     }else if((key >= 48 && key <= 57) || key == 44){
     chgColorNum.append(1, (char) key);
     pos++;
     }
     */
    
    switch (key) {
        case 'O':
        case 'o':
            bLoad = false;
            bAnal = false;
            bCreate = false;
            bFileDone = false;
            
            pos      = 0;
            imageCnt = 0;
            colorCnt = 0;
            folderPath = "";
            
            openFileResult = ofSystemLoadDialog("Select a Folder",true);
            folderPath = openFileResult.getPath();
            break;
            
        case 'L':
        case 'l':
            bPushLoad = true;
            break;
            
        case 'A':
        case 'a':
            bPushAnal = true;
            //ColorTable();
            break;
            
        case 'C':
        case 'c':
            bPushCreate = true;
            //printColor();
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
    if(colorArray.size() > 0){
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
    bPushAnal = false;
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
    if(mouseX >= 10 && mouseX <= (10 + 100) &&
       mouseY >= 10 && mouseY <= 50){
        bPushLoad = false;
        bCreate = false;
        
        pos      = 0;
        imageCnt = 0;
        colorCnt = 0;
        folderPath = "";
        
        openFileResult = ofSystemLoadDialog("Select a Folder",true);
        folderPath = openFileResult.getPath();
    }
    
    if(mouseX >= 120 && mouseX <= (120 + 100) &&
       mouseY >= 10 && mouseY <= 50){
        bPushLoad = true;
    }
    
    if(mouseX >= 230 && mouseX <= (230 + 100) &&
       mouseY >= 10 && mouseY <= 50){
        bPushAnal = true;
    }
    
    
    if(mouseX >= 340 && mouseX <= (340 + 100) &&
       mouseY >= 10 && mouseY <= 50){
        bPushCreate = true;
    }
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
