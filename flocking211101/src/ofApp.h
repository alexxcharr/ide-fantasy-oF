#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOsc.h"
#include "boid.h"

#define PORT 12345

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
    ofxPanel gui;
    ofEasyCam cam;

    ofxOscReceiver osc;
    int freezeA, freezeB, freezeC, freezeD;
    float velDataAX, velDataAY, velDataBX, velDataBY, velDataCX, velDataCY, velDataDX, velDataDY;
    float datax, alignData, datay, cohesionData, dataz, separationData;
    float datax1, alignData1, datay1, cohesionData1, dataz1, separationData1;
    float datax2, alignData2, datay2, cohesionData2, dataz2, separationData2;
    float datax3, alignData3, datay3, cohesionData3, dataz3, separationData3;
    ofColor color;
    ofColor color1,  color2, color3;
    ofMesh mesh;

    ofVec2f velData, velData1, velData2, velData3;
    vector<boid> flock;
    vector<boid> flock1;
    vector<boid> flock2;
    vector<boid> flock3;

    vector<float> arrayA, arrayB, arrayC, arrayD;

    ofxFloatSlider alignSlider;
    ofxFloatSlider cohesionSlider;
    ofxFloatSlider separationSlider;
    ofxIntSlider radiusSlider;

    int graphicsBoo = 0;;
};
// extern vector<boid> flock;
