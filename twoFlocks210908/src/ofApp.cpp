#include "ofApp.h"
#include "boid.h"
//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    osc.setup(PORT);
    ofBackground(237);
    gui.setup();
    //gui.add(alignSlider.setup("alignSlider", 1, -5, 5));
    // gui.add(cohesionSlider.setup("cohesionSlider", 1, -5, 5));
    // gui.add(separationSlider.setup("separationSlider", 1, -5, 5));
    gui.add(radiusSlider.setup("radiusSlider", 50, 10, 1000));
    for (int i =0; i < 500; i++) {
        boid newB;
        newB.setup();
        flock.push_back(newB);
        // cout<<newB.velocity<<endl;
    }
    for (int i = 0; i < 500; i++) {
        boid newC;
        newC.setup();
        flock1.push_back(newC);
    }
    for (int i = 0; i < 500; i++) {
        boid newD;
        newD.setup();
        flock2.push_back(newD);
    }
    for (int i = 0; i < 500; i++) {
        boid newE;
        newE.setup();
        flock3.push_back(newE);
    }
    color.set(39);
    color1.set(250, 0, 5);
}

//--------------------------------------------------------------
void ofApp::update(){
    while (osc.hasWaitingMessages()) {
        ofxOscMessage message;
        osc.getNextMessage(message);
        if (message.getAddress() == "/sapporo") {
            if (message.getArgAsFloat(0) == 1) {
                datax = message.getArgAsFloat(1);
                datay = message.getArgAsFloat(2);
                dataz = message.getArgAsFloat(3);
                alignData = ofMap(datax, 0.46, 0.56, 0, 2);
                cohesionData = ofMap(datay, 0.45, 0.55, 0, 2);
                separationData = ofMap(dataz, 0.45, 0.55, 1, 2);
                // cout<<datay<<endl;
            }else if (message.getArgAsFloat(0) == 2) {
                datax1 = message.getArgAsFloat(1);
                datay1 = message.getArgAsFloat(2);
                dataz1 = message.getArgAsFloat(3);
                alignData1 = ofMap(datax, 0.46, 0.56, 0, 1.5);
                cohesionData1 = ofMap(datay, 0.45, 0.55, 0, 1.5);
                separationData1 = ofMap(dataz, 0.45, 0.55, 1, 1.5);
            }

        } if (message.getAddress() == "/corfu") {
            if (message.getArgAsFloat(0) == 1) {
                datax2 = message.getArgAsFloat(1);
                datay2 = message.getArgAsFloat(2);
                dataz2 = message.getArgAsFloat(3);
                alignData2 = ofMap(datax, 0.46, 0.56, 0, 2);
                cohesionData2 = ofMap(datay, 0.45, 0.55, 0, 2);
                separationData2 = ofMap(dataz, 0.45, 0.55, 1, 2);
                // cout<<datay<<endl;
            }else if (message.getArgAsFloat(0) == 2) {
                datax3 = message.getArgAsFloat(1);
                datay3 = message.getArgAsFloat(2);
                dataz3 = message.getArgAsFloat(3);
                alignData3 = ofMap(datax, 0.46, 0.56, 0, 1.5);
                cohesionData3 = ofMap(datay, 0.45, 0.55, 0, 1.5);
                separationData3 = ofMap(dataz, 0.45, 0.55, 1, 1.5);
            }

        }
    }
    for (int i = 0; i < flock.size(); i++) {
        flock[i].almult = alignData;
        flock[i].comult = cohesionData;//Slider;
        flock[i].semult = separationData;
        flock[i].alignRadius = radiusSlider;
    }
    for (int i = 0; i < flock1.size(); i++) {
        flock1[i].almult = alignData1;
        flock1[i].comult = cohesionData1;//Slider;
        flock1[i].semult = separationData1;
        flock1[i].alignRadius = radiusSlider;
    }
    for (int i = 0; i < flock1.size(); i++) {
        flock2[i].almult = alignData2;
        flock2[i].comult = cohesionData2;//Slider;
        flock2[i].semult = separationData2;
        flock2[i].alignRadius = radiusSlider;
    }
    for (int i = 0; i < flock1.size(); i++) {
        flock3[i].almult = alignData3;
        flock3[i].comult = cohesionData3;//Slider;
        flock3[i].semult = separationData3;
        flock3[i].alignRadius = radiusSlider;
    }
}
//--------------------------------------------------------------
void ofApp::draw(){
    // cam.begin();
    // ofTranslate(ofGetWidth()/2, ofGetHeight()/2, 0);
    for (int i = 0; i < flock.size(); i++) {
        flock[i].update();
        flock[i].draw(color, flock);
        flock[i].flock(flock, flock1);
        flock[i].edges();
        // flock[i].repulsion(flock, flock1);

    }
    for (int i = 0; i < flock1.size(); i++) {
        flock1[i].update();
        flock1[i].draw(color, flock);
        flock1[i].flock(flock, flock1);
        flock1[i].edges();
    }
    for (int i = 0; i < flock1.size(); i++) {
        flock2[i].update();
        flock2[i].draw(color1, flock1);
        flock2[i].flock(flock1, flock);
        flock2[i].edges();
    }
    for (int i = 0; i < flock1.size(); i++) {
        flock3[i].update();
        flock3[i].draw(color1, flock1);
        flock3[i].flock(flock1, flock);
        flock3[i].edges();
    }
    // cam.end();
    gui.draw();
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
