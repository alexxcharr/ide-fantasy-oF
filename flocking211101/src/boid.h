#pragma once

// #include "ofMain.h"
// #include "ofApp.h"

class boid{

public:
    void setup(float width,  float height);
    ofVec2f align(std::vector<boid> flock);
    ofVec2f cohesion(std::vector<boid> flock);
    ofVec2f separation(std::vector<boid> flock);
    ofVec2f data(std::vector<boid> flock, float x, float y);
    ofVec2f repulsion(std::vector<boid> flock, std::vector<boid> flock1);
    void flock(std::vector<boid> flock, float x, float y);
    void update();
    void draw(int boolean, ofColor color, std::vector<boid> flock);
    void drawLines(int boolean, ofColor color, std::vector<boid> flock);
    void edges();

    ofVec2f position;
    ofVec2f velocity;
    ofVec2f acceleration;
    ofVec2f direction;
    ofVec2f accData;
    ofVec2f vell;
    float maxForce;
    float maxSpeed;
    float semult =1.0, comult =1.0, almult=1.0, velx = 0, vely =0;

    int alignRadius;
    int size;
    deque<glm::vec2> log;

};
extern boid bo;
