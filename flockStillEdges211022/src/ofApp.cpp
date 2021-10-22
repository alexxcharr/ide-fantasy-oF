#include "ofApp.h"
#include "boid.h"
//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    osc.setup(PORT);
    ofBackground(37);
    gui.setup();
    gui.add(radiusSlider.setup("radiusSlider", 50, 10, 1000));
    for (int i =0; i < 50; i++) {
        boid newB;
        newB.setup(200, 400);
        flock.push_back(newB);
        // cout<<newB.velocity<<endl;
    }
    for (int i = 0; i < 50; i++) {
        boid newC;
        newC.setup(400, 100);
        flock1.push_back(newC);
    }
    for (int i = 0; i < 50; i++) {
        boid newD;
        newD.setup(300, 600);
        flock2.push_back(newD);
    }
    for (int i = 0; i < 50; i++) {
        boid newE;
        newE.setup(100, 400);
        flock3.push_back(newE);
    }
    color.set(255, 255,  0);
    color1.set(255, 255, 255);
    color2.set(0, 0, 255);
    color3.set(255, 0, 0);
    graphicsBoo = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    while (osc.hasWaitingMessages()) {
        ofxOscMessage message;
        osc.getNextMessage(message);
        if (arrayA.size() > 2) {
            arrayA.erase(arrayA.begin());
        } if (arrayB.size() > 2) {
            arrayB.erase(arrayB.begin());
        } if (arrayC.size() > 2) {
            arrayC.erase(arrayC.begin());
        } if (arrayD.size() > 2) {
            arrayD.erase(arrayD.begin());
        }
        if (message.getAddress() == "/athens") {
            if (message.getArgAsFloat(0) == 1) {
                datax = message.getArgAsFloat(1);
                datay = message.getArgAsFloat(2);
                dataz = message.getArgAsFloat(3);
                velDataAX = ofMap(datax, 0.46, 0.54, -0.5, 0.5);
                velDataAY = ofMap(dataz, 0.46, 0.54, -0.5, 0.5);
                alignData = ofMap(datax, 0.45, 0.51, 0.1, 2);
                cohesionData = ofMap(datay, 0.45, 0.54, -0.35, 1.5);
                separationData = ofMap(dataz, 0.46, 0.51, 2, 8);
                arrayA.push_back(datax);
                 cout<<datax<<endl;
            }else if (message.getArgAsFloat(0) == 2) {
                datax1 = message.getArgAsFloat(1);
                datay1 = message.getArgAsFloat(2);
                dataz1 = message.getArgAsFloat(3);
                velDataBX = ofMap(datax1, 0.46, 0.54, -0.5, 0.5);
                velDataBY = ofMap(dataz1, 0.46, 0.54, -0.5, 0.5);
                alignData1 = ofMap(datax1, 0.46, 0.51, 0.1, 2);
                cohesionData1 = ofMap(datay1, 0.45, 0.54, -0.5, 1.5);
                separationData1 = ofMap(dataz1, 0.45, 0.51, 2, 8);
                arrayB.push_back(datax1);

            }
        }

        if (message.getAddress() == "/corfu") {
            if (message.getArgAsFloat(0) == 1) {
                datax2 = message.getArgAsFloat(1);
                datay2 = message.getArgAsFloat(2);
                dataz2 = message.getArgAsFloat(3);
                velDataCX = ofMap(datax2, 0.46, 0.54, -0.5, 0.5);
                velDataCY = ofMap(dataz2, 0.46, 0.54, -0.5, 0.5);
                alignData2 = ofMap(datax2, 0.46, 0.51, 0.1, 2);
                cohesionData2 = ofMap(datay2, 0.45, 0.51, -0.35, 1.5);
                separationData2 = ofMap(dataz2, 0.45, 0.51, 2, 8);
                arrayC.push_back(datax2);
                 cout<<datay<<endl;
            }else if (message.getArgAsFloat(0) == 2) {
                datax3 = message.getArgAsFloat(1);
                datay3 = message.getArgAsFloat(2);
                dataz3 = message.getArgAsFloat(3);
                velDataDX = ofMap(datax3, 0.46, 0.54, -0.5, 0.5);
                velDataDY = ofMap(dataz3, 0.46, 0.54, -0.5, 0.5);
                alignData3 = ofMap(datax3, 0.46, 0.51, 0.1, 2);
                cohesionData3 = ofMap(datay3, 0.45, 0.51, -0.35, 1.5);
                separationData3 = ofMap(dataz3, 0.45, 0.51, 2,  8);
                arrayD.push_back(datax3);
            }
        }
        if (message.getAddress() == "/change") {
            graphicsBoo = 1;
        }



        for (int i = 1; i < arrayA.size(); i++) {
            if ((arrayA[i] - arrayA[i-1]) < 0.01) {
                freezeA = 0;
            }else {
                freezeA = 1;
            }
        }
        for (int i = 1; i < arrayB.size(); i++) {
            if ((arrayB[i] - arrayB[i-1]) < 0.01) {
                freezeB = 0;
            }else {
                freezeB = 1;
            }
        }
        for (int i = 1; i < arrayC.size(); i++) {
            if ((arrayC[i] - arrayC[i-1]) < 0.01) {
                freezeC = 0;
            }else {
                freezeC = 1;
            }
        }
        for (int i = 1; i < arrayD.size(); i++) {
            if ((arrayD[i] - arrayD[i-1]) < 0.01) {
                freezeD = 0;
            }else {
                freezeD = 1;
            }
        }
        for (int i = 0; i < flock.size(); i++) {
            flock[i].velx = velDataAX * freezeA;
            flock[i].vely = velDataAY * freezeA;
            flock[i].almult = alignData * freezeA;
            flock[i].comult = cohesionData;// * freeze;//Slider;
            flock[i].semult = separationData;// * freezeA;
        }
        for (int i = 0; i < flock1.size(); i++) {
            flock1[i].velx = velDataBX * freezeB;
            flock1[i].vely = velDataBY * freezeB;
            flock1[i].almult = alignData1 * freezeB;
            flock1[i].comult = cohesionData1;//Slider;
            flock1[i].semult = separationData1;
        }
        for (int i = 0; i < flock2.size(); i++) {
            flock2[i].velx = velDataCX * freezeC;
            flock2[i].vely = velDataCY * freezeC;
            flock2[i].almult = alignData2 * freezeC;
            flock2[i].comult = cohesionData2;//Slider;
            flock2[i].semult = separationData2;
        }
        for (int i = 0; i < flock3.size(); i++) {
            flock3[i].velx = velDataDX * freezeD;
            flock3[i].vely = velDataDY * freezeD;
            flock3[i].almult = alignData3 * freezeD;
            flock3[i].comult = cohesionData3;//Slider;
            flock3[i].semult = separationData3;
        }
    }
}
//--------------------------------------------------------------
    void ofApp::draw(){
        // cam.begin();
        // ofTranslate(ofGetWidth()/2, ofGetHeight()/2, 0);
        // for (int i = 0; i < flock.size(); i++) {
        //     flock[i].update();
        //     flock[i].draw(graphicsBoo, color, flock);
        //     flock[i].flock(flock);
        //     flock[i].edges();
        //     // flock[i].repulsion(flock, flock1);

        // }
        // for (int i = 0; i < flock1.size(); i++) {
        //     flock1[i].update();
        //     flock1[i].draw(graphicsBoo, color1, flock1);
        //     flock1[i].flock(flock1);
        //     flock1[i].edges();
        //     // flock[i].repulsion(flock1, flock);
        // }
        for (int i = 0; i < flock2.size(); i++) {
            flock2[i].update();
            flock2[i].draw(graphicsBoo, color2, flock2);
            flock2[i].flock(flock2);
            flock2[i].edges();
        }
        for (int i = 0; i < flock3.size(); i++) {
            flock3[i].update();
            flock3[i].draw(graphicsBoo, color3, flock3);
            flock3[i].flock(flock3);
            flock3[i].edges();
        }
        // cam.end();
        // gui.draw();
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

//------+--------------------------------------------------------
    void ofApp::gotMessage(ofMessage msg){

    }

//--------------------------------------------------------------
    void ofApp::dragEvent(ofDragInfo dragInfo){

    }
