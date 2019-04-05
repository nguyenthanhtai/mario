//
//  Level.h
//  MagicMario
//
//  Created by Nguyen Thanh Tai  on 4/2/19.
//

#ifndef Level_h
#define Level_h

#include "cocos2d.h"
#include <vector>

using namespace std;
USING_NS_CC;

class Level : public Ref
{
public:
    
    TMXTiledMap *map;
    
    void loadMap(const char* name);
    TMXTiledMap * getMap();
    
    Point tileCoordinateToPosition(Point point);
    Point positionToTileCoordinate(Point point);
    vector<Rect> getCollisionTilesY(Point point, int direction);
    vector<Rect> getCollisionTilesX(Point point, int direction);
    
    Level(void);
    virtual ~Level(void);
};

#endif /* Level_h */
