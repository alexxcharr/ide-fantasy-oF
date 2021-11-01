#include "ofApp.h"
#include "boid.h"
//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    osc.setup(PORT);
    ofBackground(15);
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
    for (int i =0; i < 50; i++) {
        boid newA;
        newA.setup(700, 500);
        flock2.push_back(newA);
        // cout<<newB.velocity<<endl;
    }
    for (int i = 0; i < 50; i++) {
        boid newD;
        newD.setup(300, 100);
        flock3.push_back(newD);
    }
    color.set(255, 255,  0);
    color1.set(255, 255, 255);
    color2.set(0, 0, 255);
    color3.set(255, 0, 0);
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
        }
        if (message.getAddress() == "/corfu") {
            if (message.getArgAsFloat(0) == 1) {
                datax = message.getArgAsFloat(1);
                datay = message.getArgAsFloat(2);
                dataz = message.getArgAsFloat(3);
                alignData = ofMap(datax, 0.45, 0.51, 0.1, 2);
                cohesionData = ofMap(datay, 0.45, 0.54, -0.35, 1.5);
                separationData = ofMap(dataz, 0.46, 0.51, 2, 8);
                arrayA.push_back(datax);
                if (datax > 0.50 && datax < 0.501) {
                    velData.x = 0;
                    // cout<<datax<<endl;
                }else if (datax < 0.49) {
                    velData.x = -1;
                }else if (datax > 0.50)  {
                    velData.x = 1;
                }
                if (datay > 0.49 && datay < 0.501) {
                    velData.y = 0;
                }else if (datay < 0.49) {
                    velData.y = -1;
                }else if (datay > 0.50) {
                    velData.y = 1;
                }
            }
            else if (message.getArgAsFloat(0) == 2) {
                datax1 = message.getArgAsFloat(1);
                datay1 = message.getArgAsFloat(2);
                dataz1 = message.getArgAsFloat(3);
                alignData1 = ofMap(datax1, 0.46, 0.51, 0.1, 2);
                cohesionData1 = ofMap(datay1, 0.45, 0.54, -0.5, 1.5);
                separationData1 = ofMap(dataz1, 0.45, 0.51, 2, 8);
                arrayB.push_back(datax1);
                if (datax1 > 0.50 && datax1 < 0.501) {
                    velData1.x = 0;
                    // cout<<datax<<endl;
                }else if (datax1 < 0.49) {
                    velData1.x = -1;
                }else if (datax1 > 0.50)  {
                    velData1.x = 1;
                }
                if (datay1 > 0.49 && datay1 < 0.501) {
                    velData1.y = 0;
                }else if (datay1 < 0.49) {
                    velData1.y = -1;
                }else if (datay1 > 0.50) {
                    velData1.y = 1;
                }
            }

        }
        if (message.getAddress() == "/athens") {
            if (message.getArgAsFloat(0) == 2) {
                datax2 = message.getArgAsFloat(1);
                datay2 = message.getArgAsFloat(2);
                dataz2 = message.getArgAsFloat(3);
                alignData2 = ofMap(datax2, 0.45, 0.51, 0.1, 2);
                cohesionData2 = ofMap(datay2, 0.45, 0.54, -0.35, 1.5);
                separationData2 = ofMap(dataz2, 0.46, 0.51, 2, 8);
                arrayC.push_back(datax2);
                if (datax2 > 0.50 && datax2 < 0.501) {
                    velData2.x = 0;
                    // cout<<datax<<endl;
                }else if (datax2 < 0.49) {
                    velData2.x = -1;
                }else if (datax2 > 0.50)  {
                    velData2.x = 1;
                }
                if (datay2 > 0.49 && datay2 < 0.501) {
                    velData2.y = 0;
                }else if (datay2 < 0.49) {
                    velData2.y = -1;
                }else if (datay2 > 0.50) {
                    velData2.y = 1;
                }
            }
            else if (message.getArgAsFloat(0) == 1) {
                datax3 = message.getArgAsFloat(1);
                datay3 = message.getArgAsFloat(2);
                dataz3 = message.getArgAsFloat(3);
                alignData3 = ofMap(datax3, 0.45, 0.51, 0.1, 2);
                cohesionData3 = ofMap(datay3, 0.45, 0.54, -0.35, 1.5);
                separationData3 = ofMap(dataz3, 0.46, 0.51, 2, 8);
                arrayD.push_back(datax3);
                cout<<datax2<<endl;
                ///////
                if (datax3 > 0.50 && datax3 < 0.501) {
                    velData3.x = 0;
                    // cout<<datax<<endl;
                }else if (datax3 < 0.49) {
                    velData3.x = -1;
                }else if (datax3 > 0.50)  {
                    velData3.x = 1;
                }
                if (datay3 > 0.49 && datay3 < 0.501) {
                    velData3.y = 0;
                }else if (datay3 < 0.49) {
                    velData3.y = -1;
                }else if (datay3 > 0.50) {
                    velData3.y = 1;
                }
            }

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
            flock[i].vell.x = velData.x;// * freezeA;
            flock[i].vell.y = velData.y;// * freezeA;
            flock[i].almult = alignData * freezeA;
            flock[i].comult = cohesionData;
            flock[i].semult = separationData;
            flock[i].accData.x = ofMap(datax, 0.45, 0.55, -1, 1);
            flock[i].accData.y = ofMap(datay, 0.45, 0.55, -1, 1);
        }
        for (int i = 0; i < flock1.size(); i++) {
            flock1[i].vell.x = velData1.x;// * freezeA;
            flock1[i].vell.y = velData1.y;// * freezeA;
            flock1[i].almult = alignData1 * freezeB;
            flock1[i].comult = cohesionData1;//Slider;
            flock1[i].semult = separationData1;
            flock1[i].accData.x = ofMap(datax1, 0.45, 0.55, -1, 1);
            flock1[i].accData.y = ofMap(datay1, 0.45, 0.55, -1, 1);
        }
        for (int i = 0; i < flock2.size(); i++) {
            flock2[i].vell.x = velData2.x;// * freezeA;
            flock2[i].vell.y = velData2.y;// * freezeA;
            flock2[i].almult = alignData2 * freezeC;
            flock2[i].comult = cohesionData2;
            flock2[i].semult = separationData2;
            flock2[i].accData.x = ofMap(datax2, 0.45, 0.55, -1, 1);
            flock2[i].accData.y = ofMap(datay2, 0.45, 0.55, -1, 1);
        }
        for (int i = 0; i < flock3.size(); i++) {
            flock3[i].vell.x = velData3.x;// * freezeA;
            flock3[i].vell.y = velData3.y;// * freezeA;
            flock3[i].almult = alignData3 * freezeD;
            flock3[i].comult = cohesionData3;//Slider;
            flock3[i].semult = separationData3;
            flock3[i].accData.x = ofMap(datax3, 0.45, 0.55, -1, 1);
            flock3[i].accData.y = ofMap(datay3, 0.45, 0.55, -1, 1);
        }
    }
}
//--------------------------------------------------------------
void ofApp::draw(){
    for (int i = 0; i < flock.size(); i++) {
        flock[i].update();
        flock[i].drawLines(graphicsBoo, color, flock);
        //cout<<velData.x<<endl;
        flock[i].flock(flock, velData.x, velData.y);
        flock[i].edges();
    }
    for (int i = 0; i < flock1.size(); i++) {
        flock1[i].update();
        flock1[i].drawLines(graphicsBoo, color1, flock1);
        flock1[i].flock(flock1, velData1.x, velData1.y);
        flock1[i].edges();
    }
    for (int i = 0; i < flock2.size(); i++) {
        flock2[i].update();
        flock2[i].draw(graphicsBoo, color2, flock2);
        flock2[i].flock(flock2, velData2.x, velData2.y);
        flock2[i].edges();
    }
    for (int i = 0; i < flock3.size(); i++) {
        flock3[i].update();
        flock3[i].draw(graphicsBoo, color3, flock3);
        flock3[i].flock(flock3, velData3.x, velData3.y);
        flock3[i].edges();
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

//------+--------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
