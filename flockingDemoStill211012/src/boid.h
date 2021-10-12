#pragma once

// #include "ofMain.h"
// #include "ofApp.h"

class boid{

public:
    void setup(float width,  float height);
    ofVec2f align(std::vector<boid> flock);
    ofVec2f cohesion(std::vector<boid> flock);
    ofVec2f separation(std::vector<boid> flock);
    ofVec2f repulsion(std::vector<boid> flock, std::vector<boid> flock1);
    void flock(std::vector<boid> flock);
    void update();
    void draw(ofColor color, std::vector<boid> flock);
    void edges();

    ofVec2f position;
    ofVec2f velocity;
    ofVec2f acceleration;
    float maxForce;
    float maxSpeed;
    float semult, comult, almult, velx, vely;
    int alignRadius;
};

extern boid bo;
