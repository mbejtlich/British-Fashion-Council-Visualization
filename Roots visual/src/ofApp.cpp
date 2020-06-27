#include "ofApp.h"
#include <string>
#include <iostream>


//--------------------------------------------------------------
void ofApp::setup(){
    //Load roots CSV
    int num_rows;
    if(csv.load("vogue_reach_full.csv")){
        num_rows = csv.getNumRows();
        for(int i=1;i<num_rows;i=i+days){
            for(int j=2;j<10;j++){
                Region newRegion;
                newRegion.fashionWeekId = csv[i][0];
                newRegion.regionName = csv[0][j];
                newRegion.regionNum = j-1;
                //                std::cout << newRegion.id << endl;
                //                std::cout << newRegion.name << endl;
                for(int z=1;z<days+1;z++){
                    //                    std::cout <<"Value of i " << i << endl;
                    //                    std::cout <<"Value of j " << j << endl;
                    //                    std::cout << csv[i+z-1][j] << endl;
                    newRegion.reach.push_back(reachBaseline*std::stof(csv[i+z-1][j]));
                    newRegion.reachDayGain.push_back(std::stof(csv[i+z-1][j+8]));
                    //cout << csv[i+z-1][j+8] << endl;
                }
                //                cout << "Region # "<< newRegion.id << endl;
                //                cout << "Region # "<< newRegion.regionNum << endl;
                //                cout << "Region # "<< newRegion.name << endl;
                regions.push_back(newRegion);
            }
        }
    }
    
    // Set background color
    ofBackground(0,0,0);  // Clear the screen with a black color
    ofSetCircleResolution(100);
    ofSetVerticalSync(true);
    
    
    // calculate start and end points and store in region objects
    for (int m=0; m<numRegions;m++){
        float xOuter = centerX+ circleRadiusOuter * cos((startAngle+angleSpace*m)*PI/180);
        float yOuter = centerY+ circleRadiusOuter * -sin((startAngle+angleSpace*m)*PI/180);
        float xInner = centerX + circleRadiusInner * cos((startAngle+angleSpace*m)*PI/180);
        float yInner = centerY + circleRadiusInner * -sin((startAngle+angleSpace*m)*PI/180);
        for (Region& r : regions){
            if (r.regionNum == m+1){
                r.startCurveX = xOuter;
                r.startCurveY = yOuter;
                r.endCurveX = xInner;
                r.endCurveY = yInner;
//                std::cout << "X position " << xOuter << endl;
//                std::cout << "Y position " << yOuter<< endl;
//                std::cout << "X position " << r.startCurveX << endl;
//                std::cout << "Y position " << r.startCurveY<< endl;
                //                cout << regions[1].startCurveX << endl;
                //                cout << regions[1].startCurveY << endl;
            }
        }
        
    }
    
    for(int i = 0 ; i < regions.size();i++){
        regions[i].setup();
    }
//        cout << ofGetHeight()/2 << endl;
//        cout << ofGetWidth()/2 << endl;
//        cout << regions[1].startCurveX << endl;
//        cout << regions[1].startCurveY << endl;
    
//        float l = 1.733;
//        int q = (int)(l+0.5);
//        cout << q << endl;


}

//--------------------------------------------------------------

void ofApp::update(){

    // if day is over, reset all flags
    if (dayFlag == 1){
        dayFlag = 0; // reset dayFlag
        
        // reset all root and region flags
        
        for(int i = 0 ; i < numRegions ; i++){
            regions[i].regionFlag = 0;
            for (int j=0; j < regions[i].numRoots[currentDay-1];j++){
                regions[i].dayRoots[currentDay-1][j].rootFlag = 0;
                regions[i].dayRoots[currentDay-1][j].percTraveled = 0.0;
            }
        }
        
        currentDay = currentDay + 1;
    }
    
    // if day is equal to 19, loop fashion week continously
    if (currentDay == days+1){
        currentDay = 1;
    }
}

//--------------------------------------------------------------
void Region::setup(){
    ofSetLineWidth(3.0);

    for(int i = 0 ; i < 19; i++){
        float newSize = ofMap(reach[i],1.07436,1801.12764,mapLower,mapUpper);
        numRoots.push_back((int)(newSize + 0.5));
        vector<Roots> singleDay;
        for (int j = 0 ; j < numRoots[i]; j++){
            Roots newRoot;
            newRoot.dayNum = i+1;
            newRoot.centerX = startCurveX;
            newRoot.centerY = startCurveY;
            newRoot.endX = endCurveX;
            newRoot.endY = endCurveY;
            newRoot.amountRoots = (int)(newSize + 0.5);
            newRoot.setup();
            singleDay.push_back(newRoot);
        }
    dayRoots.push_back(singleDay);
    }
}

//--------------------------------------------------------------
void Roots::setup(){
    // generate N random points (amountRoots) within a circle of radius r
    float r = amountRoots*ofRandom(0,1);
    float theta = ofRandom(0,1)*2*PI;
    float x = r*cos(theta);
    float y = r*sin(theta);
    startRandomX = centerX + x;
    startRandomY = centerY + y;
    distX = endX - startRandomX;
    distY = endY - startRandomY;
    percTraveled = 0.0;
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //    ofSetColor(255);  // Set the drawing color to white
    //    ofSetLineWidth(3.0);
    ofSetLineWidth(2);
    ofColor yellow(255, 255, 255, 80);
    ofSetColor(yellow);
    ofNoFill();
    ofDrawCircle(centerX, centerY, circleRadiusOuter);
    ofDrawCircle(centerX, centerY, circleRadiusInner);
    
    //    for (int m=0; m<numRegions;m++){
    //        float xOuter = centerX + circleRadiusOuter * cos((startAngle+angleSpace*m)*PI/180);
    //        float yOuter = centerY + circleRadiusOuter * -sin((startAngle+angleSpace*m)*PI/180);
    //        float xInner = centerX + circleRadiusInner * cos((startAngle+angleSpace*m)*PI/180);
    //        float yInner = centerY + circleRadiusInner * -sin((startAngle+angleSpace*m)*PI/180);
    //        std::cout << "X position " << xOuter << endl;
    //        std::cout << "Y position " << yOuter<< endl;
    //        ofDrawLine(xOuter, yOuter, xInner, yInner);
    //        ofNoFill();
    //        ofDrawCircle(xOuter,yOuter,13);
    //        }
    //
    //    std::vector<Region> region_subset(regions.begin(), regions.begin()+8);
    //    for (Region r : region_subset){
    //            ofDrawLine(r.startCurveX, r.startCurveY, r.endCurveX, r.endCurveY);
    //            ofNoFill();
    //            ofDrawCircle(r.startCurveX,r.startCurveY,18);
    //            r.draw();
    //        }
    
    for(int i = 0 ; i < numRegions ; i++){
//        cout << "Current Day: " << currentDay << endl;
        regions[i].draw(currentDay);
    }
    
     // check region status flags
    
    int regionFlagCount = 0;
    int regionFlagStatus = 0;
    for (int i=0; i < numRegions;i++){
        regionFlagStatus = regions[i].regionFlag;
        regionFlagCount = regionFlagCount + regionFlagStatus;
    }
    
    if (regionFlagCount == numRegions){
        dayFlag = 1;
    }

    //    for(int i = 0 ; i < numRegions ; i++){
    //        regions[i].draw(currentDay);
    //        cout << currentDay << endl;
    //        if (regions[i].dayFinished == true && i < numRegions - 1){
    //            regions[i].percTraveled = 0.0;
    //            regions[i].dayFinished = false;
    //            }
    //        if (regions[i].dayFinished == true && i == numRegions - 1){
    //            regions[i].percTraveled = 0.0;
    //            regions[i].dayFinished = false;
    //            currentDay += 1;
    //        }
    //    }
    
    cout << "Current Day: " << currentDay << endl;
}

//--------------------------------------------------------------
void Region::update(){
    
}

//--------------------------------------------------------------
void Region::draw(int currentDay){

    for (int i=0; i < numRoots[currentDay-1];i++){
//        cout << "Region: " << regionNum << endl;
//        cout << "Region Num Roots: " << numRoots[currentDay-1] << endl;
        dayRoots[currentDay-1][i].draw(step,exponent);
    }
    
    // check root status flags
    int rootFlagCount = 0;
    int rootFlagStatus;
    for (int i=0; i < numRoots[currentDay-1];i++){
        rootFlagStatus = dayRoots[currentDay-1][i].rootFlag;
        rootFlagCount = rootFlagCount + rootFlagStatus;
    }
    
    if (rootFlagCount== numRoots[currentDay-1]){
        regionFlag = 1;
    }
    
//    percTraveled += step;
//    if (percTraveled < 1.0) {
//        currentX = startCurveX + percTraveled * distX;
//        currentY = startCurveY + pow(percTraveled, exponent) * distY;
//        ofSetColor(41,120,255); // draw small circle
//        ofFill();
//        ofDrawCircle(currentX, currentY, numRoots[currentDay-1]);
//    }
//    else{
//        dayFinished = true;
//    }
    
}

//--------------------------------------------------------------
void Roots::update(){
    
}

//--------------------------------------------------------------
void Roots::draw(float step, int exponent){
    
    // draw region circle for each day
    ofSetLineWidth(1.8);
    ofColor blue(134, 195, 255);
    ofSetColor(blue);
    ofDrawCircle(centerX,centerY,amountRoots);
    
    // set color of emitted line particles
    ofSetLineWidth(1.8);
    ofColor green(11, 245, 128);
    ofSetColor(green,120);
    ofSetLineWidth(3);
    
    percTraveled += step;
//    cout << "Percent Traveled: " << step << endl;

    if (percTraveled < 1.0) {
        currentX = startRandomX + percTraveled * distX;
        currentY = startRandomY + pow(percTraveled, exponent) * distY;
        if (percTraveled == step){
            ofDrawLine(startRandomX, startRandomY, currentX, currentY);
            previousX = currentX;
            previousY = currentY;
        }
        else{
            ofDrawLine(previousX, previousY, currentX, currentY);
            previousX = currentX;
            previousY = currentY;
        }
    }
    else{
        rootFlag = 1;
    }
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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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

