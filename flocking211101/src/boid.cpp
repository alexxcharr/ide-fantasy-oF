#include "ofApp.h"
#include "boid.h"


void boid::setup(float width, float height) {
    position.set(width, height);
    acceleration.set(0,0);
    float angle = ofRandom(TWO_PI);
    velocity.set(-1,1);//-ofRandom(cos(angle)),-ofRandom(sin(angle)));
    maxForce = 0.03 * 3;
    maxSpeed = 2;
    alignRadius = 1000;
    size = ofRandom(5);
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
        steer.limit(0.03*2);
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
        steer.limit(0.03);
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
            steering += diff;
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

void boid::flock(std::vector<boid> flock, float x, float y) {
    ofVec2f alignment = align(flock);
    ofVec2f coh = cohesion(flock);
    ofVec2f sep = separation(flock);
    ofVec2f dat = data(flock, x, y);
    alignment = alignment *  almult;// * accData;
    coh = coh * comult;
    sep = sep * almult;
    acceleration += alignment;
    acceleration += coh;
    acceleration += sep;
    acceleration += dat;
}


void boid::update() {
    velocity += acceleration;
    position += velocity;
    acceleration *= 0;
    this->log.push_front(this->position);
    while (this->log.size() > 120) {

        this->log.pop_back();
    }
}


void boid::draw(int boolean, ofColor color, std::vector<boid> flock) {
    ofSetColor(color);
    if (boolean == 0) {
        ofDrawCircle(position, size);
        for (int i = 0; i < flock.size(); i++) {

            float d = position.distance(flock[i].position);
            if (d>10 && d < 20) {
                ofDrawLine(position, flock[i].position);
            }
        }
    }
    if (boolean == 1) {
        for(int i = 0; i < this->log.size()-1; i++) {
            ofSetColor(color, ofMap(i, 0, this->log.size()-1, 255, 0));
            ofVec3f pos1 = this->log[i+1];
            ofVec3f pos2 = this->log[i];
            if(pos1.distance(pos2) < 100 && pos1.distance(pos2) > 0) {
                ofDrawLine(this->log[i], this->log[i+1]);
            }
        }
    }

}


void boid::drawLines(int boolean, ofColor color, std::vector<boid> flock) {
    ofSetColor(color);
    ofDrawCircle(position, 2);
    ofSetLineWidth(2);
    for(int i = 0; i < this->log.size()-1; i++) {
        ofSetColor(color, ofMap(i, 0, this->log.size()-1, 255, 0));
        ofVec3f pos1 = this->log[i+1];// - (this->log[i]);
        ofVec3f pos2 = this->log[i];
        if(pos1.distance(pos2) < 100 && pos1.distance(pos2) > 0) {
            ofDrawLine(this->log[i], this->log[i+1]);
        }
    }
}

void boid::edges() {
    if (position.x >= ofGetWidth()) {
        velocity.x = - velocity.x;
    }else if (position.x <= 0) {
        velocity.x = - velocity.x;
    }
    if (position.y >= ofGetHeight()) {
        velocity.y = - velocity.y;
    }else if (position.y <= 0) {
        velocity.y = - velocity.y;
    }
}


ofVec2f boid::data(std::vector<boid> flock, float x, float y) {
    ofVec2f steering(0, 0);
    ofVec2f dataVel(accData.x, accData.y);
    int total = 0;
    // for (int i = 0; i < flock.size(); i++) {
    //     ofVec2f diff = dataVel - flock[i].position;
    //     diff.normalize();
    // //     steering = dataVel;//diff;
    // //     // total++;
    //     steering = diff;// dataVel;
    // }
    // if (total > 0) {
        // steering /= (float(total));
    // }
    // if (steering.length() > 0) {
        // steering.normalize();
        // steering *= maxSpeed;
        // steering -= velocity;
    // }
    steering = dataVel - velocity;
    steering.normalize();
    steering *= 2;//maxSpeed;
    //cout<<x<<endl;
    steering.limit(0.03);
    return steering;
}
