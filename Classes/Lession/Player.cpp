//
//  Player.cpp
//  MagicMario
//
//  Created by Nguyen Thanh Tai  on 4/1/19.
//

#include "Player.h"
#include "globals.h"

USING_NS_CC;

#define FRAMECACHE SpriteFrameCache::getInstance()

Player::Player(void)
{
    velocityX = 0;
    velocityY = 0;
    direction = 2; // by default: set facingRight for player
    
    facingLeft = 1;
    facingRight = 2;
    
    grounded = true;
    jumping = false;
    
    isDied = false;
    
    walk = nullptr;
    
    setupAnimation("walk");
}

Player::~Player(void)
{
    
}

Player * Player::create() {
    Player* pSprite = new Player();
    if (pSprite->initWithSpriteFrameName("idle")) {
        pSprite->setAnchorPoint(Point::ZERO);
        pSprite->playerSize = Size(pSprite->getBoundingBox().size.width, pSprite->getBoundingBox().size.height);

        return pSprite;
    }

    return NULL;
}

void Player::updateState(float delta) {
    log("update state");
    if (velocityX < 0) {
        if (walk == NULL || walk->isDone() || direction != facingLeft) {
            direction = facingLeft;
            walk->startWithTarget(this);
        }
    }
    
    if (velocityY < 0) {
        // @TODO
        // set state is falling
    }
    
    if (velocityX > 0) {
        if (walk == NULL || walk->isDone() || direction != facingRight) {
            direction = facingRight;
            walk->startWithTarget(this);
        }
    }
    
    if (velocityY > 0){
        // @TODO
        // set state is flying
    }
    
    if (velocityX != 0) {
        walk->step(delta); // repeat animation
    }
    
    if (direction == facingRight) {
        setFlippedX(false);
    } else {
        setFlippedX(true);
    }
    
    if (velocityX == 0 && velocityY == 0) {
        setSpriteFrame( FRAMECACHE->getSpriteFrameByName("idle"));
        if (direction == facingRight) {
            setFlippedX(false);
        } else {
            setFlippedX(true);
        }
    } else if (velocityY > 0 || velocityY < 0) {
        setSpriteFrame(FRAMECACHE->getSpriteFrameByName("jump"));
        if (direction == facingRight) {
            setFlippedX(false);
        } else {
            setFlippedX(true);
        }
    }
    
    log("direct = %d", direction);
    
    auto playerVelocity = Vec2(velocityX, velocityY);
    setPosition(getPosition() + playerVelocity * delta);
}

void Player::setupAnimation(const char* name) {
    if (walk != NULL) {
        walk->release();
    }
    
    FRAMECACHE->addSpriteFramesWithFile("character.plist", "character.png");
    Vector<SpriteFrame *> animFrames;
    
    for (int index = 1; index <= 9; index++) {
        std::string frameName = StringUtils::format("%s%d", name, index++);
        SpriteFrame* frame = FRAMECACHE->getSpriteFrameByName(frameName);
        
        if (frame == NULL) {
            break;
        }
        
        animFrames.pushBack(frame);
    }
    
    Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.12f);
    walk = Animate::create(animation);
    walk->startWithTarget(this);
    walk->retain();
}

void Player::setPlayerDied() {
    log("player is died!!!!");
    isDied = true;
}
