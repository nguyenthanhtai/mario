#include "Level.h"
#include "globals.h"

void Level::loadMap(const char* mapName) {
    map = TMXTiledMap::create(mapName);
    map->retain();
}

TMXTiledMap * Level::getMap() {
    return map;
}

Point Level::tileCoordinateToPosition(Point point) {
    float x = floor(point.x * map->getTileSize().width * SCALE_FACTOR);
    float y = floor(point.y * map->getTileSize().height * SCALE_FACTOR);
    
    return Point(x, y);
}

Point Level::positionToTileCoordinate(Point point) {
    float x = floor(point.x / (map->getTileSize().width * SCALE_FACTOR));
    float y = floor(point.y / (map->getTileSize().height * SCALE_FACTOR));
    
    return Point((int)x, (int)y);
}

vector<Rect> Level::getCollisionTilesY(Point point, int direction) {
    vector<Rect> list;
    TMXLayer *walls = map->getLayer("walls");
    
    int mapHeight = (int) map->getMapSize().height - 1;
    
    for (int b = -1; b < 2; b++) {
        Sprite *tile = walls->getTileAt(Point((int)point.x + b, mapHeight - ((int)point.y + direction)));
        
        if (tile != nullptr) {
            Rect tileRect = Rect();
            auto tmpPoint = Point((int) point.x + b, mapHeight - ((int) point.y + direction));
            Point tmp = walls->getPositionAt(tmpPoint);
            tileRect.setRect(tmp.x * SCALE_FACTOR, tmp.y * SCALE_FACTOR, map->getTileSize().width * SCALE_FACTOR, map->getTileSize().height * SCALE_FACTOR);
            list.push_back(tileRect);
        }
    }
    
    return list;
}

vector<Rect> Level::getCollisionTilesX(Point point, int direction) {
    vector<Rect> list;
    TMXLayer *walls = map->getLayer("walls");
    int mapHeight = (int) map->getMapSize().height - 1;
    
    for (int b = -1; b < 2; b++) {
        auto tmpPoint = Point((int)point.x + direction, mapHeight - ((int)point.y + b));
        Sprite *tile = walls->getTileAt(tmpPoint);
        if (tile != nullptr) {
            Rect tileRect = Rect();
            Point tmp = walls->getPositionAt(Point((int)point.x + direction, mapHeight - ((int)point.y + b)));
            tileRect.setRect(tmp.x * SCALE_FACTOR, tmp.y * SCALE_FACTOR,
                             map->getTileSize().width * SCALE_FACTOR,
                             map->getTileSize().height * SCALE_FACTOR);
            
            list.push_back(tileRect);
        }
    }
    
    return list;
}

Level::Level(void) {
}

Level::~Level(void) {
    map->release();
}
