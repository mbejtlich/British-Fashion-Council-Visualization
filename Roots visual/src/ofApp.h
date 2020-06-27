#pragma once

#include "ofMain.h"
#include "ofxCsv.h"
#include "ofxSandLine.h"
#include "ofxBlur.h"
#include "math/ofVec2f.h"
#include <math.h>
#include <vector>
#include <string>

class Roots{
    public:
    void setup();
    void draw(float step, int exponent);
    void update();
    int dayNum;
    int amountRoots;
    float centerX;
    float centerY;
    float endX;
    float endY;
    int rootFlag = 0;
    float startRandomX;
    float startRandomY;
    float currentX;
    float currentY;
    float previousX;
    float previousY;
    float distX;
    float distY;
    float percTraveled;
};

class Region{
    public:
    int regionNum;
    string regionName;
    string fashionWeekId;
    float startCurveX;
    float startCurveY;
    float endCurveX;
    float endCurveY;
    ofPolyline line;
    vector <float> reach;
    vector <float> reachDayGain;
    vector <int> numRoots;
    vector <vector <Roots>> dayRoots;
    void setup();
    void draw(int currentDay);
    void update();
    int exponent = 6; // determines shape of curve
    float step = 0.009;
    int mapUpper = 100;
    int mapLower = 2;
    int regionFlag = 0;
};

class ofApp : public ofBaseApp{

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
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        ofxCsv csv;
        ofPolyline line;
        int reachBaseline = 200;
        vector<Region> regions;
        int centerX = 2.75*ofGetWidth()/4+50;
        int centerY = ofGetHeight()/2;
        int circleRadiusOuter = 870;
        int circleRadiusInner = 100;
        int numRegions = 8;
        float angleSpace = 7.14285714286;
        int startAngle = 155;
        int currentDay = 1;
        int currentFashionWeek = 1;
        int days = 19;
        int dayFlag = 0;
};













