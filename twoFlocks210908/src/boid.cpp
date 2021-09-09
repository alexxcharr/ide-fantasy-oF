#include "ofApp.h"
#include "boid.h"


void boid::setup() {
    position.set(ofRandomWidth()/2, ofRandomHeight());
    acceleration.set(0,0);
    float angle = ofRandom(TWO_PI);
    velocity.set(cos(angle), sin(angle));
    maxForce = 0.03;
    maxSpeed = 4;
    alignRadius = 1000;
}


ofVec2f boid::align(std::vector<boid> flock) {
    int perceptionRadius = 1000;
    ofVec2f sum(0, 0);
    int total = 0;
    for (int i = 0; i < flock.size(); i++) {
        float d = position.distance(flock[i].position);
        if (d > 0 && d < perceptionRadius) {
            sum += flock[i].velocity;
            total++;
        }
    }
    if (total>0) {
        sum /= (float(total));
        sum.normalize();
        sum *= maxSpeed;
        ofVec2f steer = sum - velocity;
        steer.limit(maxForce);
        return steer;
    } else {
        return ofVec2f(0, 0);
    }
}


ofVec2f boid::cohesion(std::vector<boid> flock) {
    int perceptionRadius = 1000;
    ofVec2f sum = ofVec2f(0,0);
    int total = 0;
    for (int i = 0; i < flock.size(); i++) {
        float d = position.distance(flock[i].position);
        if (d > 0 && d < perceptionRadius) {
            sum += flock[i].position;
            total++;
        }
    }
    if (total>0) {
        sum /= (float(total));
        ofVec2f desired = sum - position;
        desired.normalize();
        desired *= maxSpeed;
        ofVec2f steer = desired - velocity;
        steer.limit(0.09);
        return steer;
    }else {
        return ofVec2f(0,0);
    }
}


ofVec2f boid::separation(std::vector<boid> flock) {
    int perceptionRadius = 30;
    ofVec2f steering(0, 0);
    int total = 0;
    for (int i = 0; i < flock.size(); i++) {
        float d = position.distance(flock[i].position);
        if (d>0 && d < perceptionRadius) {
            ofVec2f diff = position - flock[i].position;
            diff.normalize();
            diff /= d;
            steering += diff;//flock[i].position;
            total++;
        }
    }
    if (total>0) {
        steering /= (float(total));
    }
    if (steering.length() > 0) {
        steering.normalize();
        steering *= maxSpeed;
        steering -= velocity;
        steering.limit(maxForce);
    }
    return steering;
}

void boid::flock(std::vector<boid> flock, std::vector<boid> flock1) {
    ofVec2f alignment = align(flock);
    ofVec2f coh = cohesion(flock);
    ofVec2f sep = separation(flock);
    ofVec2f rep = repulsion(flock, flock1);
    alignment = alignment * almult;
    coh = coh * comult;
    sep = sep * almult;
    acceleration += alignment;
    acceleration += coh;
    acceleration += sep;
    //  acceleration += rep;

}


void boid::update() {
    velocity += acceleration;
    velocity.limit(maxSpeed);
    position += velocity;
    acceleration *= 0;
}


void boid::draw(ofColor color, std::vector<boid> flock) {
    ofSetColor(color);
    ofDrawCircle(position, 2);
    //ofDrawSphere(this-> position, 5);
    for (int i = 0; i < flock.size(); i++) {

        float d = position.distance(flock[i].position);
        if (d>5 && d < 10) {
            ofDrawLine(position, flock[i].position);
        }
    }
}

void boid::edges() {
    if (position.x >= ofGetWidth()) {
        position.x = 0;
    }else if (position.x <= 0) {
        position.x = ofGetWidth();
    }
    if (position.y >= ofGetHeight()) {
        position.y = 0;
    }else if (position.y <= 0) {
        position.y = ofGetHeight();
    }
}



ofVec2f boid::repulsion(std::vector<boid> flock, std::vector<boid> flock1) {
    int perceptionRadius = 100;
    ofVec2f steering(0, 0);
    int total = 0;
    for (int i = 0; i < flock.size(); i++) {
        float d = flock1[i].position.distance(flock[i].position);
        if (d>0 && d < 30) {
            ofVec2f diff = flock1[i].position - flock[i].position;
            diff.normalize();
            diff /= d;
            steering += diff;//flock[i].position;
            total++;
            // cout<<total<<endl;
        }else if(d <=0) {
    }
    }
    if (total>0) {
        steering /= (float(total));
    }
    if (steering.length() > 0) {
        steering.normalize();
        steering *= maxSpeed;
        steering -= velocity;
        steering.limit(0.21);
    }
    return steering;
}
