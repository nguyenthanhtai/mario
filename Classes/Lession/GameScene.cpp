//
//  GameScene.cpp
//  MagicMario
//
//  Created by Nguyen Thanh Tai  on 4/2/19.
//

#include "GameScene.h"
#include "globals.h"


Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = GameScene::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    level = new Level();
    level->loadMap("level1.tmx");
    level->retain();
    level->getMap()->setScale(SCALE_FACTOR);
    this->addChild(level->getMap());
    
    player = Player::create();
    player->retain();
    
    Point point = Point(10, 2);
    player->setPosition(level->tileCoordinateToPosition(point));
    
    Point origin = Director::getInstance()->getVisibleOrigin();
    Size size = Director::getInstance()->getVisibleSize();
    cameraTarget = Sprite::create();
    cameraTarget->setPositionX(player->getPositionX()); // set to players x
    cameraTarget->setPositionY(size.height/2 + origin.y); // center of height
    
    cameraTarget->retain();
    
    this->addChild(player);
    this->schedule(schedule_selector(GameScene::updateScene));
    
    this->addChild(cameraTarget);
    
    camera = Follow::create(cameraTarget, Rect::ZERO);
    camera->retain();
    
    loadEnemies();
    
    this->runAction(camera);
    return true;
}

void GameScene::loadEnemies(){
    
    Sprite *enemy1 = Sprite::create("CloseNormal.png");
    enemy1->setPosition(level->tileCoordinateToPosition( Point(33, 2)));
    enemy1->setAnchorPoint(Point::ZERO);
    enemy1->setScale(ENEMY_SCALE_FACTOR);
    enemy1->setFlippedX(true);
    enemy1->retain();
    
    enemyList.push_back(enemy1);
    this->addChild(enemy1);
    
    Sprite *enemy2 = Sprite::create("CloseNormal.png");
    enemy2->setPosition(level->tileCoordinateToPosition( Point(44, 2)));
    enemy2->setAnchorPoint(Point::ZERO);
    enemy2->setScale(ENEMY_SCALE_FACTOR);
    enemy2->setFlippedX(true);
    enemy2->retain();
    
    enemyList.push_back(enemy2);
    this->addChild(enemy2);
    
    
    Sprite *enemy3 = Sprite::create("CloseNormal.png");
    enemy3->setPosition(level->tileCoordinateToPosition( Point(55, 2)));
    enemy3->setAnchorPoint(Point::ZERO);
    enemy3->setScale(ENEMY_SCALE_FACTOR);
    enemy3->setFlippedX(true);
    enemy3->retain();
    
    enemyList.push_back(enemy3);
    this->addChild(enemy3);
    
    Sprite *enemy4 = Sprite::create("CloseNormal.png");
    enemy4->setPosition(level->tileCoordinateToPosition( Point(100, 2)));
    enemy4->setAnchorPoint(Point::ZERO);
    enemy4->setScale(ENEMY_SCALE_FACTOR);
    enemy4->setFlippedX(true);
    enemy4->retain();
    
    enemyList.push_back(enemy4);
    this->addChild(enemy4);
    
    Sprite *enemy5 = Sprite::create("CloseNormal.png");
    enemy5->setPosition(level->tileCoordinateToPosition( Point(100, 6)));
    enemy5->setAnchorPoint(Point::ZERO);
    enemy5->setScale(ENEMY_SCALE_FACTOR);
    enemy5->setFlippedX(true);
    enemy5->retain();
    
    enemyList.push_back(enemy5);
    this->addChild(enemy5);
    
}


void GameScene::updateScene(float delta) {
    cameraTarget->setPositionX(player->getPositionX());
    this->updatePlayer(delta);
}

void GameScene::updatePlayer(float delta) {
    if (std::find(heldKeys.begin(), heldKeys.end(), SPACEBAR) != heldKeys.end()) {
        if(player->grounded && player->velocityY <= 0){
            player->velocityY = PLAYER_JUMP_VELOCITY;
            player->jumping = true;
            player->grounded = false;
        }
        
    }
    
    if(std::find(heldKeys.begin(), heldKeys.end(), RIGHT_ARROW) != heldKeys.end()){
        player->velocityX = PLAYER_MAX_VELOCITY;
        player->facingRight = true;
    }
    
    if(std::find(heldKeys.begin(), heldKeys.end(), LEFT_ARROW) != heldKeys.end()){
        player->velocityX = -PLAYER_MAX_VELOCITY;
        player->facingRight = false;
    }
    
    player->velocityY -= GRAVITY;
    
    Rect playerRect = player->getBoundingBox();
    
    Point tmp;
    vector<Rect> tiles;
    tiles.clear();
    
    // center of player's sprite
    tmp = level->positionToTileCoordinate(Point(player->getPositionX() + player->playerSize.width * 0.5f ,
                                                player->getPositionY() + player->playerSize.height * 0.5f));
    
    log("log tmp:%f, %f", tmp.x, tmp.y);
    if (tmp.x >= 210) {
        // is win
        // @TODO optimize later
        log("player is win!!!");
        Point p = level->tileCoordinateToPosition(Point(10, 2));
        player->setPosition(p);
    }
    if (tmp.x < 10 || tmp.y < 2) {
        // player is died and back the beginning point
        // @TODO optimize later
        player->setPlayerDied();
        Point p = level->tileCoordinateToPosition(Point(10, 2));
        player->setPosition(p);
    }
    
    if (player->velocityX > 0) {
        tiles = level->getCollisionTilesX(tmp, 1);
    } else {
        tiles = level->getCollisionTilesX(tmp, -1);
    }
    
    playerRect.setRect(
                        player->getBoundingBox().getMinX() + player->velocityX * delta,
                        player->getBoundingBox().getMinY() + 1.0f,
                        player->playerSize.width,
                        player->playerSize.height
                        );
    
    for (Rect tile : tiles) {
        // for debug
//        DrawNode *drawRectTile = DrawNode::create();
//        drawRectTile->drawRect(Vec2(tile.getMinX(), tile.getMinY()),
//                               Vec2(tile.getMaxX(), tile.getMaxY()),
//                               Color4F::RED);
//        this->addChild(drawRectTile);
        
        if (playerRect.intersectsRect(tile)) {
            player->velocityX = 0;
            break;
        }
    }
    
    tiles.clear();
    
    if (player->velocityY > 0) {
        tiles = level->getCollisionTilesY(tmp, 1);
    } else if (player->velocityY < 0) {
        tiles = level->getCollisionTilesY(tmp, -1);
    }
    
    playerRect.setRect(
                        player->getBoundingBox().getMinX(),
                        player->getBoundingBox().getMinY(),
                        player->playerSize.width,
                        player->playerSize.height
                        );
    
    for (Rect tile : tiles) {
        if (tile.intersectsRect(playerRect)) {
            log("hit");
            if (player->velocityY > 0) {
                player->velocityY = player->velocityY * 0.5;
            } else {
                player->setPositionY(tile.getMaxY());
                // if we hit the ground, mark us as grounded so we can jump
                player->grounded = true;
                player->jumping = false;
                log("hit grounded");
            }
            player->velocityY = 0;
            break;
            
        }
        player->grounded = false;
    }
    
    // check for enemy collisions
    for (Sprite *tile : enemyList) {
        if (tile->getBoundingBox().intersectsRect(playerRect)) {
            player->setPlayerDied();
            Point p = level->tileCoordinateToPosition(Point(10, 2));
            player->setPosition(p);
        }
    }
    
    player->updateState(delta);
    player->velocityX = 0;
    
    log("player Position: X=%f, Y=%f", player->getPositionX(), player->getPositionY());
}


void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
    if(std::find(heldKeys.begin(), heldKeys.end(), keyCode) == heldKeys.end()){
        heldKeys.push_back(keyCode);
    }
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
    heldKeys.erase(std::remove(heldKeys.begin(), heldKeys.end(), keyCode), heldKeys.end());
}

void GameScene::menuCloseCallback(Ref* pSender) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    return;
#endif
    
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

GameScene::GameScene(void) {
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

GameScene::~GameScene(void) {
    level->release();
}
