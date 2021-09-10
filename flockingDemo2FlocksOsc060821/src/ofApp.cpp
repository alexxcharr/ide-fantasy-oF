#include "ofApp.h"
#include "boid.h"
//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    osc.setup(PORT);
    ofBackground(37);
    gui.setup();
    //gui.add(alignSlider.setup("alignSlider", 1, -5, 5));
    // gui.add(cohesionSlider.setup("cohesionSlider", 1, -5, 5));
    // gui.add(separationSlider.setup("separationSlider", 1, -5, 5));
    gui.add(radiusSlider.setup("radiusSlider", 50, 10, 1000));
    for (int i =0; i < 250; i++) {
        boid newB;
        newB.setup(200, 400);
        flock.push_back(newB);
        // cout<<newB.velocity<<endl;
    }
    for (int i = 0; i < 250; i++) {
        boid newC;
        newC.setup(400, 100);
        flock1.push_back(newC);
    }
    for (int i = 0; i < 250; i++) {
        boid newD;
        newD.setup(300, 600);
        flock2.push_back(newD);
    }
    for (int i = 0; i < 250; i++) {
        boid newE;
        newE.setup(100, 400);
        flock3.push_back(newE);
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
        if (message.getAddress() == "/corfu") {
            if (message.getArgAsFloat(0) == 1) {
                datax = message.getArgAsFloat(1);
                datay = message.getArgAsFloat(2);
                dataz = message.getArgAsFloat(3);
                alignData = ofMap(datax, 0.46, 0.51, 0, 2);
                cohesionData = ofMap(datay, 0.45, 0.51, 0, 2);
                separationData = ofMap(dataz, 0.45, 0.51, 2, 10);
                // cout<<datay<<endl;
            }else if (message.getArgAsFloat(0) == 2) {
                datax1 = message.getArgAsFloat(1);
                datay1 = message.getArgAsFloat(2);
                dataz1 = message.getArgAsFloat(3);
                alignData1 = ofMap(datax1, 0.46, 0.51, 0, 2);
                cohesionData1 = ofMap(datay1, 0.45, 0.51, 0, 2);
                separationData1 = ofMap(dataz1, 0.45, 0.51, 2, 10);
            }

        } if (message.getAddress() == "/sapporo") {
            if (message.getArgAsFloat(0) == 1) {
                datax2 = message.getArgAsFloat(1);
                datay2 = message.getArgAsFloat(2);
                dataz2 = message.getArgAsFloat(3);
                alignData2 = ofMap(datax2, 0.46, 0.51, 0, 2);
                cohesionData2 = ofMap(datay2, 0.45, 0.51, 0, 2);
                separationData2 = ofMap(dataz2, 0.45, 0.51, 2, 10);
                // cout<<datay<<endl;
            }else if (message.getArgAsFloat(0) == 2) {
                datax3 = message.getArgAsFloat(1);
                datay3 = message.getArgAsFloat(2);
                dataz3 = message.getArgAsFloat(3);
                alignData3 = ofMap(datax3, 0.46, 0.51, 0, 2);
                cohesionData3 = ofMap(datay3, 0.45, 0.51, 0, 2);
                separationData3 = ofMap(dataz3, 0.45, 0.51, 2,  10);
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
        flock[i].repulsion(flock, flock1);

    }
    for (int i = 0; i < flock1.size(); i++) {
        flock1[i].update();
        flock1[i].draw(color1, flock);
        flock1[i].flock(flock1, flock);
        flock1[i].edges();
        flock[i].repulsion(flock1, flock);
    }
    for (int i = 0; i < flock1.size(); i++) {
        flock2[i].update();
        flock2[i].draw(color2, flock1);
        flock2[i].flock(flock2, flock3);
        flock2[i].edges();
        flock[i].repulsion(flock2, flock3);

    }
    for (int i = 0; i < flock1.size(); i++) {
        flock3[i].update();
        flock3[i].draw(color3, flock1);
        flock3[i].flock(flock3, flock2);
        flock3[i].edges();
        flock[i].repulsion(flock3, flock2);

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

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
