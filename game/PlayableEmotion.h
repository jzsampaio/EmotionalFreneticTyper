//
// Created by jasf on 5/22/16.
//

#ifndef IDJ201601T1_PLAYBLEEMOTION_H
#define IDJ201601T1_PLAYBLEEMOTION_H


#include "GameObject.h"
#include "Sprite.h"
#include "Timer.h"

class PlayableEmotion : public GameObject{
public:
    enum PlayableState{IDLE, WALKING, JUMPING, FALLING, RUNNING, GRABBING, DASHING};
    enum PlayableFacing{LEFT, RIGHT};

private:

    Sprite sp;
    PlayableState currentState;
    PlayableFacing currentlyFacing;
    Vec2 speed, acceleration;
    float speedAngle, speedMagnitude;
    float accelerationAngle, accelerationMagnitude;

    int lifePoints;

    Timer dashTimer;

public:

    PlayableEmotion();


    virtual void update(float dt);

    virtual bool isDead();

    virtual void notifyCollision(GameObject &other);

    virtual bool is(std::string type);

    void render(bool forceDraw=false);
};


#endif //IDJ201601T1_PLAYBLEEMOTION_H