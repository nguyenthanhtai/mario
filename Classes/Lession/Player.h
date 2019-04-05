//
//  Player.h
//  MagicMario
//
//  Created by Nguyen Thanh Tai  on 4/1/19.
//

#ifndef Player_h
#define Player_h

#include "cocos2d.h"

USING_NS_CC;

class Player : public Sprite
{
public:
    
    float velocityX;
    float velocityY;
    
    int direction;
    int facingLeft;
    int facingRight;
    bool grounded;
    bool jumping;
    bool isDied;
    bool isWin;
    
    Animate *walk;
    Size playerSize;
    
    static Player* create();
    
    void updateState(float delta);
    void setupAnimation(const char* name);
    void setPlayerDied();
    
    Player(void);
    virtual ~Player(void);
};

#endif /* Player_h */
