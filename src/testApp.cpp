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
    
    imgWidth = 64;
    imgHeight = 48;
}


//--------------------------------------------------------------
void testApp::update(){
    if(License(YEAR,MON,DAY,HOUR,MINUTE)){
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
}

//--------------------------------------------------------------
void testApp::draw(){
    if(License(YEAR,MON,DAY,HOUR,MINUTE)){
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
        
        ofSetColor(150,0,0);
        ofDrawBitmapString("set Image Width  : " + ofToString(imgWidth), 10, 70);
        ofDrawBitmapString("set Image Height : " + ofToString(imgHeight), 10, 90);
        
        ofSetColor(150,150,150);
        ofRect(204+36*0+4*0, 58, 36, 16);
        ofRect(204+36*1+4*1, 58, 36, 16);
        ofRect(204+36*2+4*2, 58, 36, 16);
        ofRect(204+36*3+4*3, 58, 36, 16);
        ofRect(204+36*4+4*4, 58, 36, 16);
        ofRect(204+36*5+4*5, 58, 36, 16);
        
        ofRect(204+36*0+4*0, 78, 36, 16);
        ofRect(204+36*1+4*1, 78, 36, 16);
        ofRect(204+36*2+4*2, 78, 36, 16);
        ofRect(204+36*3+4*3, 78, 36, 16);
        ofRect(204+36*4+4*4, 78, 36, 16);
        ofRect(204+36*5+4*5, 78, 36, 16);
        
        ofSetColor(150,0,0);
        ofDrawBitmapString("+100 -100  +10  -10   +1   -1", 206, 70);
        ofDrawBitmapString("+100 -100  +10  -10   +1   -1", 206, 90);
        
        
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
        
        if(bPushLoad){
            ofSetColor(100, 100, 100);
            ofRect(0, 0, 450, 200);
            ofSetColor(255, 255, 255);
            ofDrawBitmapString("Load... ", 190, 100);
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
    }else{
        ofSetColor(100, 100, 100);
        ofRect(0, 0, 450, 200);
        ofSetColor(255, 255, 255);
    }
}

bool testApp::License(int year, int month, int day, int hour, int minute){
    if(ofGetYear() <= year &&
       ofGetMonth() <= month &&
       ofGetDay() <= day)
        return true;
    else
        return false;
}

//--------------------------------------------------------------
void testApp::ImageLoad(){
    if(License(YEAR,MON,DAY,HOUR,MINUTE)){
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
                    if(img.width == imgWidth &&
                       img.height == imgHeight){
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
                    }else{
                        continue;
                    }
                    
                }
            }
            bPushLoad = false;
        }catch(exception e){
            
        }
        bLoad = false;
    }
}

//--------------------------------------------------------------
void testApp::printColor(){
    if(License(YEAR,MON,DAY,HOUR,MINUTE)){
        try {
            
            //for TEXT
            if(colorInfomationArray.size()>0){
                ofstream file;
                file.open ("result.txt", ios::out);
                for (int i=0; i< colorInfomationArray.size() ; i++) {
                    file << colorInfomationArray[i] << colorNumber[i]+1 << "/" << endl;
                }
                file.close();
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
                bFileDone = true;
            }
            bPushCreate = false;
        }catch(exception e){
            
        }
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if(License(YEAR,MON,DAY,HOUR,MINUTE)){
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
                colorTable.clear();
                
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
}

//--------------------------------------------------------------
int testApp::palette(ofColor c){
    if(License(YEAR,MON,DAY,HOUR,MINUTE)){
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
}

//--------------------------------------------------------------
void testApp::ColorTable(){
    if(License(YEAR,MON,DAY,HOUR,MINUTE)){
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
    if(License(YEAR,MON,DAY,HOUR,MINUTE)){
        if(mouseX >= 10 && mouseX <= (10 + 100) &&
           mouseY >= 10 && mouseY <= 50){
            bLoad = false;
            bAnal = false;
            bPushLoad = false;
            bCreate = false;
            bFileDone = false;
            pos      = 0;
            imageCnt = 0;
            colorCnt = 0;
            folderPath = "";
            colorTable.clear();
            
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
        
        
        if(mouseX >= 204+36*0+4*0 && mouseX <= (204+36*0+4*0 + 36) &&
           mouseY >= 58 && mouseY <= 74){
            imgWidth += 100;
        }
        
        if(mouseX >= 204+36*1+4*1 && mouseX <= (204+36*1+4*1 + 36) &&
           mouseY >= 58 && mouseY <= 74){
            imgWidth -= 100;
        }
        
        if(mouseX >= 204+36*2+4*2 && mouseX <= (204+36*2+4*2 + 36) &&
           mouseY >= 58 && mouseY <= 74){
            imgWidth += 10;
        }
        
        if(mouseX >= 204+36*3+4*3 && mouseX <= (204+36*3+4*3 + 36) &&
           mouseY >= 58 && mouseY <= 74){
            imgWidth -= 10;
        }
        
        if(mouseX >= 204+36*4+4*4 && mouseX <= (204+36*4+4*4 + 36) &&
           mouseY >= 58 && mouseY <= 74){
            imgWidth += 1;
        }
        
        if(mouseX >= 204+36*5+4*5 && mouseX <= (204+36*5+4*5 + 36) &&
           mouseY >= 58 && mouseY <= 74){
            imgWidth -= 1;
        }
        
        
        
        if(mouseX >= 204+36*0+4*0 && mouseX <= (204+36*0+4*0 + 36) &&
           mouseY >= 78 && mouseY <= 94){
            imgHeight += 100;
        }
        
        if(mouseX >= 204+36*1+4*1 && mouseX <= (204+36*1+4*1 + 36) &&
           mouseY >= 78 && mouseY <= 94){
            imgHeight -= 100;
        }
        
        if(mouseX >= 204+36*2+4*2 && mouseX <= (204+36*2+4*2 + 36) &&
           mouseY >= 78 && mouseY <= 94){
            imgHeight += 10;
        }
        
        if(mouseX >= 204+36*3+4*3 && mouseX <= (204+36*3+4*3 + 36) &&
           mouseY >= 78 && mouseY <= 94){
            imgHeight -= 10;
        }
        
        if(mouseX >= 204+36*4+4*4 && mouseX <= (204+36*4+4*4 + 36) &&
           mouseY >= 78 && mouseY <= 94){
            imgHeight += 1;
        }
        
        if(mouseX >= 204+36*5+4*5 && mouseX <= (204+36*5+4*5 + 36) &&
           mouseY >= 78 && mouseY <= 94){
            imgHeight -= 1;
        }
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
