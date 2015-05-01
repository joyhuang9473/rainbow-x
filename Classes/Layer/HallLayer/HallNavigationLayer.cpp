#include "HallNavigationLayer.h"

USING_NS_CC;


bool HallNavigationLayer::init() {
    if ( !Layer::init() ) {
        return false;
    }

    // Map
    std::vector<std::string> searchPaths;
    searchPaths.push_back("Map");
    FileUtils::getInstance()->setSearchPaths(searchPaths);
    this->m_map = TMXTiledMap::create("hall_navigation.tmx");
    this->addChild(this->m_map);
    
    return true;
}

