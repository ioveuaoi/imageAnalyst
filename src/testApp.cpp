#include "testApp.h"
#include <sstream>

bool compareHue( const ofColor& s1, const ofColor& s2 ) {
    return s1.getHue() < s2.getHue();
}

//--------------------------------------------------------------
void testApp::setup(){
    ofSetBackgroundColor(255,255,255);
    ofSetVerticalSync(true);
    ofSetBackgroundAuto(true);
    
    bLoad       = false;
    bPushLoad   = false;
    bAnal       = false;
    bPushAnal   = false;
    bCreate     = false;
    bPushCreate = false;
    bFileDone   = false;
    bStartRgb   = false;
    bImageMakePush  = false;
    bImageMakeStart = false;
  	pos         = 0;
    imageCnt    = 0;
    colorCnt    = 0;
    folderPath  = "";
    chgColorNumStr = "";
    
    imgWidth    = 64;
    imgHeight   = 48;
    wantColor   = ofColor(255,255,255);
    wr = 255;
    wg = 255;
    wb = 255;
}


//--------------------------------------------------------------
void testApp::update(){
    if(bLoad)
    {
        ImageLoad();
    }
    
    if(bAnal)
    {
        ColorTable();
        bAnal = false;
    }
    
    if(bCreate)
    {
        printColor();
        bCreate = false;
    }
    
    if(bFileDone){
        if(chgColorNumStr.size() > 0){
            stringCutter(chgColorNumStr,cutterInt,',');
        }
    }
    
    
    wr = wantColor.r;
    wg = wantColor.g;
    wb = wantColor.b;
    
    if(bImageMakeStart){
        for(int i=0; i<cutterInt.size(); i++)
            chgColorNum.push_back(cutterInt[i]);
        saveImage(chgColorNum,wantColor);
        bImageMakeStart = false;
    }
}

//--------------------------------------------------------------
void testApp::draw(){
#pragma mark BUTTON
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
    
#pragma mark BUTTON TEXT
    ofSetColor(0, 0, 0);
    ofDrawBitmapString(" Open(O)", 10, 35);
    ofDrawBitmapString(" Load(L)", 120, 35);
    ofDrawBitmapString(" Analysts(A)", 230, 35);
    ofDrawBitmapString(" Create(C)", 340, 35);
    
#pragma mark IMAGE SCALE
    ofSetColor(150,0,0);
    ofDrawBitmapString("set Image Width  : " + ofToString(imgWidth), 10, 70);
    ofDrawBitmapString("set Image Height : " + ofToString(imgHeight), 10, 90);
    
#pragma mark SCALE CONTROL BUTTON
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
    
#pragma mark RESULT STRING
    ofSetColor(0);
    if(folderPath.length() >= 35)
    {
        tmpPath = folderPath;
        while (tmpPath.size() > 35)
        {
            tmpPath.erase(tmpPath.begin());
        }
        ofDrawBitmapString("Folder Path : ..." + tmpPath, 10, 120);
    }
    else
        ofDrawBitmapString("Folder Path : " + folderPath, 10, 120);
    
    ofDrawBitmapString("Loaded Image : " + ofToString(imageCnt), 10, 140);
    ofDrawBitmapString("Pixel : " + ofToString(colorCnt), 10, 160);
    
    if (colorTable.size() > 0)
    {
        ofDrawBitmapString("Used Color : " + ofToString(colorTable.size()), 10, 180);
    }else{
        ofDrawBitmapString("Used Color : 0", 10, 180);
    }
    
#pragma mark EXPANSION PANNEL
    if(bFileDone){
        ofSetWindowShape(450,330);
        ofDrawBitmapString("------------------------------------------------------", 10, 200);
        if(ofToInt(chgColorNumStr) >= 1 && ofToInt(chgColorNumStr) <= colorCnt+1){
            for(int i=0; i<cutterInt.size(); i++){
                ofSetColor(colorTable[cutterInt[i]-1]);
                ofRect(10+i*430/cutterInt.size(), 224, 430/cutterInt.size(), 20);
            }
        }else{
            ofSetColor(255,255,255);
            ofRect(10, 224, 430, 20);
        }
        ofSetColor(0);
        if(chgColorNumStr.length() >= 30){
            int tmp = chgColorNumStr.length();
            ofDrawBitmapString("                     "+ chgColorNumStr, 12+(30-tmp)*8, 218);
        }else{
            ofDrawBitmapString("                     "+ chgColorNumStr, 12, 218);
        }
        ofSetColor(200, 200, 200);
        ofRect(0,200, 173, 20);
        ofSetColor(0);
        ofDrawBitmapString("input color number : ",12, 218);
        
        
        ofSetColor(wantColor);
        ofRect(10, 244, 430, 20);
        
        ofSetColor(150,150,150);
        ofRect(10, 278, 60, 40);
        ofSetColor(0);
        ofDrawBitmapString("Change", 12, 302);
    }
    
#pragma mark SCALE CONTROL BUTTON2
    ofSetColor(150,0,0);
    ofDrawBitmapString("R : " + ofToString(wr),  110, 278);
    ofDrawBitmapString("G : " + ofToString(wg), 110, 298);
    ofDrawBitmapString("B : " + ofToString(wb), 110, 318);
    
    ofSetColor(150,150,150);
    ofRect(204+36*0+4*0, 266, 36, 16);
    ofRect(204+36*1+4*1, 266, 36, 16);
    ofRect(204+36*2+4*2, 266, 36, 16);
    ofRect(204+36*3+4*3, 266, 36, 16);
    ofRect(204+36*4+4*4, 266, 36, 16);
    ofRect(204+36*5+4*5, 266, 36, 16);
    
    ofRect(204+36*0+4*0, 286, 36, 16);
    ofRect(204+36*1+4*1, 286, 36, 16);
    ofRect(204+36*2+4*2, 286, 36, 16);
    ofRect(204+36*3+4*3, 286, 36, 16);
    ofRect(204+36*4+4*4, 286, 36, 16);
    ofRect(204+36*5+4*5, 286, 36, 16);
    
    ofRect(204+36*0+4*0, 306, 36, 16);
    ofRect(204+36*1+4*1, 306, 36, 16);
    ofRect(204+36*2+4*2, 306, 36, 16);
    ofRect(204+36*3+4*3, 306, 36, 16);
    ofRect(204+36*4+4*4, 306, 36, 16);
    ofRect(204+36*5+4*5, 306, 36, 16);
    
    ofSetColor(150,0,0);
    ofDrawBitmapString("+100 -100  +10  -10   +1   -1", 206, 278);
    ofDrawBitmapString("+100 -100  +10  -10   +1   -1", 206, 298);
    ofDrawBitmapString("+100 -100  +10  -10   +1   -1", 206, 318);
    
    
#pragma mark PROCESS MESSAGE
    if(bPushLoad)
    {
        ofSetColor(100, 100, 100);
        ofRect(0, 0, 450, 200);
        ofSetColor(255, 255, 255);
        ofDrawBitmapString("Load... ", 190, 100);
        bLoad = true;
    }
    
    if(bPushAnal)
    {
        ofSetColor(100, 100, 100);
        ofRect(0, 0, 450, 200);
        ofSetColor(255, 255, 255);
        ofDrawBitmapString("Analyst... ", 190, 100);
        bAnal = true;
    }
    
    if(bPushCreate)
    {
        ofSetColor(100, 100, 100);
        ofRect(0, 0, 450, 200);
        ofSetColor(255, 255, 255);
        ofDrawBitmapString("Create... ", 190, 100);
        bCreate = true;
    }
    
    if(bImageMakePush)
    {
        ofSetColor(100, 100, 100);
        ofRect(0, 0, 450, 270);
        ofSetColor(255, 255, 255);
        ofDrawBitmapString("Change... ", 190, 100);
        bImageMakeStart = true;
    }
}

//--------------------------------------------------------------
bool testApp::License(int year, int month, int day, int hour, int minute){
    if(ofGetYear()  <= year     &&
       ofGetMonth() <= month    &&
       ofGetDay()   <= day)
        return true;
    else
        return false;
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
               dir[i].getExtension() == "GIF"  ||
               dir[i].getExtension() == "tga"  ||
               dir[i].getExtension() == "TGA")
            {
                img.loadImage(tmpstr);
                if(img.width    == imgWidth &&
                   img.height   == imgHeight)
                {
                    imageCnt++;
                    for(int i=0; i < img.width; i++)
                    {
                        for(int j=0; j<img.height; j++)
                        {
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
                else
                {
                    continue;
                }
                
            }
        }
        bPushLoad = false;
    }
    catch(exception e)
    {
        
    }
    bLoad = false;
}

//--------------------------------------------------------------
void testApp::printColor(){
    if(License(YEAR,MON,DAY,HOUR,MINUTE))
    {
        try {
            
            //for TEXT
            if(colorInfomationArray.size()>0)
            {
                ofstream file;
                file.open ("result.txt", ios::out);
                for (int i=0; i< colorInfomationArray.size() ; i++)
                {
                    file << colorInfomationArray[i] << colorNumber[i]+1 << "/" << endl;
                }
                file.close();
                bFileDone = true;
            }
            
            //for HTML
            if(colorInfomationHTML.size()>0)
            {
                ofstream file;
                file.open ("result.html", ios::out);
                file << "<html><head><title>Result</title></head><body><table border =\"1\"><tr align =\"center\"><td>Pixel</td><td>Image</td><td>X</td><td>Y</td><td>Color</td><td>Match</td></tr>" << endl;
                for (int i=0; i< colorInfomationHTML.size() ; i++)
                {
                    file << colorInfomationHTML[i] << "<td align =\"right\">" << colorNumber[i]+1 << "</td></tr>" << endl;
                }
                file << "</td></tr></table></body></html>" << endl;
                file.close();
                bFileDone = true;
            }
            
            //for HTML
            if(colorTable.size()>0)
            {
                ofstream file;
                file.open ("colorTable.html", ios::out);
                file << "<html><head><title>Color Table</title></head><body><table border =\"1\"><tr align =\"center\"><td>Number</td><td>Color</td><td>RGB</td></tr>" << endl;
                for (int i=0; i< colorTable.size() ; i++)
                {
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
            ofSort(colorTable,compareHue);
        }
        return colorTable.size();
    }
}

//--------------------------------------------------------------
void testApp::ColorTable(){
    if(License(YEAR,MON,DAY,HOUR,MINUTE))
    {
        if(colorArray.size() > 0)
        {
            for (int i=0; i<colorArray.size(); i++)
            {
                palette(colorArray[i]);
            }
            //ofSort(colorTable,compareHue);
            //ofSort(colorTable,compareHue);
            for (int i=0; i<colorArray.size(); i++)
            {
                for (int j=0; j< colorTable.size(); j++)
                {
                    if(colorArray[i] == colorTable[j])
                    {
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
void testApp::stringCutter(string str, vector<int> &ch, char knife){
    std::stringstream tmpstr;
    ch.clear();
    for(int i=0; i<str.length(); i++){
        if(str[i] == knife){
            int tmpi = ofToInt(tmpstr.str());
            ch.push_back(tmpi);
            tmpstr.str("");
            continue;
        }else{
            tmpstr << str[i];
        }
    }
}

//--------------------------------------------------------------
void testApp::saveImage(vector<int> selectNum, ofColor color){
    int imgCnt = dir.size();
    ofImage tmp;
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
           dir[i].getExtension() == "GIF"  ||
           dir[i].getExtension() == "tga"  ||
           dir[i].getExtension() == "TGA")
        {
            tmp.loadImage(tmpstr);
            if(tmp.width    == imgWidth &&
               tmp.height   == imgHeight)
            {
                for(int i=0; i < tmp.width; i++)
                {
                    for(int j=0; j<tmp.height; j++)
                    {
                        for(int k=0; k<selectNum.size(); k++)
                        {
                            if(tmp.getColor(i,j) == colorTable[selectNum[k]-1])
                            {
                                tmp.setColor(i,j, ofColor(color));
                            }
                        }
                    }
                    
                }
            }
            else
            {
                continue;
            }
        }
        tmp.setImageType(OF_IMAGE_COLOR);
        tmp.saveImage("convert/"+dir[i].getFileName());
    }
    bImageMakePush  = false;
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if(key == 13)
        chgColorNumStr ="";
    if(key == 8 || key == 127){
        if( pos != 0 ){
            pos--;
            chgColorNumStr = chgColorNumStr.substr(0,pos);
        }else
            chgColorNumStr = "";
    }else if((key >= 48 && key <= 57) || (key == 44) || (key == 46) || (key == 47)){
        chgColorNumStr.append(1, (char) key);
        pos++;
    }
    
    
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
            break;
            
        case 'C':
        case 'c':
            bPushCreate = true;
            break;
            
        case ' ':
            bImageMakePush = true;
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
    if(License(YEAR,MON,DAY,HOUR,MINUTE))
    {
        if(mouseX >= 10 && mouseX <= (10 + 100) &&
           mouseY >= 10 && mouseY <= 50)
        {
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
           mouseY >= 10 && mouseY <= 50)
        {
            bPushLoad = true;
        }
        
        if(mouseX >= 230 && mouseX <= (230 + 100) &&
           mouseY >= 10 && mouseY <= 50)
        {
            bPushAnal = true;
        }
        
        
        if(mouseX >= 340 && mouseX <= (340 + 100) &&
           mouseY >= 10 && mouseY <= 50)
        {
            bPushCreate = true;
        }
        
        if(mouseX >= 10 && mouseX <= (10 + 60) &&
           mouseY >= 278 && mouseY <= (278+40))
        {
            bImageMakePush = true;
        }
        
        
        
        if(mouseX >= 204+36*0+4*0 && mouseX <= (204+36*0+4*0 + 36) &&
           mouseY >= 58 && mouseY <= 74)
        {
            imgWidth += 100;
        }
        
        if(mouseX >= 204+36*1+4*1 && mouseX <= (204+36*1+4*1 + 36) &&
           mouseY >= 58 && mouseY <= 74)
        {
            imgWidth -= 100;
        }
        
        if(mouseX >= 204+36*2+4*2 && mouseX <= (204+36*2+4*2 + 36) &&
           mouseY >= 58 && mouseY <= 74)
        {
            imgWidth += 10;
        }
        
        if(mouseX >= 204+36*3+4*3 && mouseX <= (204+36*3+4*3 + 36) &&
           mouseY >= 58 && mouseY <= 74)
        {
            imgWidth -= 10;
        }
        
        if(mouseX >= 204+36*4+4*4 && mouseX <= (204+36*4+4*4 + 36) &&
           mouseY >= 58 && mouseY <= 74)
        {
            imgWidth += 1;
        }
        
        if(mouseX >= 204+36*5+4*5 && mouseX <= (204+36*5+4*5 + 36) &&
           mouseY >= 58 && mouseY <= 74)
        {
            imgWidth -= 1;
        }
        
        
        if(mouseX >= 204+36*0+4*0 && mouseX <= (204+36*0+4*0 + 36) &&
           mouseY >= 78 && mouseY <= 94)
        {
            imgHeight += 100;
        }
        
        if(mouseX >= 204+36*1+4*1 && mouseX <= (204+36*1+4*1 + 36) &&
           mouseY >= 78 && mouseY <= 94)
        {
            imgHeight -= 100;
        }
        
        if(mouseX >= 204+36*2+4*2 && mouseX <= (204+36*2+4*2 + 36) &&
           mouseY >= 78 && mouseY <= 94)
        {
            imgHeight += 10;
        }
        
        if(mouseX >= 204+36*3+4*3 && mouseX <= (204+36*3+4*3 + 36) &&
           mouseY >= 78 && mouseY <= 94)
        {
            imgHeight -= 10;
        }
        
        if(mouseX >= 204+36*4+4*4 && mouseX <= (204+36*4+4*4 + 36) &&
           mouseY >= 78 && mouseY <= 94)
        {
            imgHeight += 1;
        }
        
        if(mouseX >= 204+36*5+4*5 && mouseX <= (204+36*5+4*5 + 36) &&
           mouseY >= 78 && mouseY <= 94)
        {
            imgHeight -= 1;
        }
        
        
        
        
        if(mouseX >= 204+36*0+4*0 && mouseX <= (204+36*0+4*0 + 36) &&
           mouseY >= 266 && mouseY <= 282)
        {
            wantColor.r += 100;
        }
        
        if(mouseX >= 204+36*1+4*1 && mouseX <= (204+36*1+4*1 + 36) &&
           mouseY >= 266 && mouseY <= 282)
        {
            wantColor.r -= 100;
        }
        
        if(mouseX >= 204+36*2+4*2 && mouseX <= (204+36*2+4*2 + 36) &&
           mouseY >= 266 && mouseY <= 282)
        {
            wantColor.r += 10;
        }
        
        if(mouseX >= 204+36*3+4*3 && mouseX <= (204+36*3+4*3 + 36) &&
           mouseY >= 266 && mouseY <= 282)
        {
            wantColor.r -= 10;
        }
        
        if(mouseX >= 204+36*4+4*4 && mouseX <= (204+36*4+4*4 + 36) &&
           mouseY >= 266 && mouseY <= 282)
        {
            wantColor.r += 1;
        }
        
        if(mouseX >= 204+36*5+4*5 && mouseX <= (204+36*5+4*5 + 36) &&
           mouseY >= 266 && mouseY <= 282)
        {
            wantColor.r -= 1;
        }
        
        
        if(mouseX >= 204+36*0+4*0 && mouseX <= (204+36*0+4*0 + 36) &&
           mouseY >= 286 && mouseY <= 302)
        {
            wantColor.g += 100;
        }
        
        if(mouseX >= 204+36*1+4*1 && mouseX <= (204+36*1+4*1 + 36) &&
           mouseY >= 286 && mouseY <= 302)
        {
            wantColor.g -= 100;
        }
        
        if(mouseX >= 204+36*2+4*2 && mouseX <= (204+36*2+4*2 + 36) &&
           mouseY >= 286 && mouseY <= 302)
        {
            wantColor.g += 10;
        }
        
        if(mouseX >= 204+36*3+4*3 && mouseX <= (204+36*3+4*3 + 36) &&
           mouseY >= 286 && mouseY <= 302)
        {
            wantColor.g -= 10;
        }
        
        if(mouseX >= 204+36*4+4*4 && mouseX <= (204+36*4+4*4 + 36) &&
           mouseY >= 286 && mouseY <= 302)
        {
            wantColor.g += 1;
        }
        
        if(mouseX >= 204+36*5+4*5 && mouseX <= (204+36*5+4*5 + 36) &&
           mouseY >= 286 && mouseY <= 302)
        {
            wantColor.g -= 1;
        }
        
        if(mouseX >= 204+36*0+4*0 && mouseX <= (204+36*0+4*0 + 36) &&
           mouseY >= 306 && mouseY <= 322)
        {
            wantColor.b += 100;
        }
        
        if(mouseX >= 204+36*1+4*1 && mouseX <= (204+36*1+4*1 + 36) &&
           mouseY >= 306 && mouseY <= 322)
        {
            wantColor.b -= 100;
        }
        
        if(mouseX >= 204+36*2+4*2 && mouseX <= (204+36*2+4*2 + 36) &&
           mouseY >= 306 && mouseY <= 322)
        {
            wantColor.b += 10;
        }
        
        if(mouseX >= 204+36*3+4*3 && mouseX <= (204+36*3+4*3 + 36) &&
           mouseY >= 306 && mouseY <= 322)
        {
            wantColor.b -= 10;
        }
        
        if(mouseX >= 204+36*4+4*4 && mouseX <= (204+36*4+4*4 + 36) &&
           mouseY >= 306 && mouseY <= 322)
        {
            wantColor.b += 1;
        }
        
        if(mouseX >= 204+36*5+4*5 && mouseX <= (204+36*5+4*5 + 36) &&
           mouseY >= 306 && mouseY <= 322)
        {
            wantColor.b -= 1;
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
