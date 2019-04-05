//
//  GameScene.h
//  MagicMario
//
//  Created by Nguyen Thanh Tai  on 4/2/19.
//

#ifndef GameScene_h
#define GameScene_h

#include "cocos2d.h"
#include "Level.h"
#include "Player.h"
#include <algorithm>
#include <string>
#include <vector>

using namespace std;
USING_NS_CC;

class GameScene : public cocos2d::Layer
{
public:
    
    //FIELDS
    Level * level;
    Player *player;
    Sprite *cameraTarget;
    
    vector<Sprite*> enemyList;
    
    Follow *camera;
    
    DrawNode *rectWithBorder;
    
    vector<EventKeyboard::KeyCode> heldKeys;
    
    //CONSTRUCTOR & METHODS
    
    virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    
    void updateScene(float interval);
    
    void updatePlayer(float interval);
    
    void loadEnemies();
    
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    CREATE_FUNC(GameScene);
    
    GameScene(void);
    virtual ~GameScene(void);
};

#endif /* GameScene_h */
