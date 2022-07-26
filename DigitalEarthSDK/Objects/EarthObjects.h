#ifndef EARTHOBJECTS_H
#define EARTHOBJECTS_H
#include <iostream>
#include "Enums/EarthEnums.h"

struct MapObject{
    std::string name;
    MapType mapType;
    MapDriverType driverType;
    std::string url;
    bool enabled;
    bool isVisible;
    MapType MapType(std::string type)
    {
        if(!type.compare("Image"))
            return MapType::Image;
        else if(!type.compare("Elevation"))
            return MapType::Elevation;
        else if(!type.compare("Map"))
            return MapType::Map;
        else if(!type.compare("SeaMap"))
            return MapType::SeaMap;
        else
            return MapType::Other;
    }
    MapDriverType MapDriverType(std::string type)
    {
        if(!type.compare("TMS"))
            return MapDriverType::TMS;
        else if(!type.compare("XYZ"))
            return MapDriverType::XYZ;
        else if(!type.compare("ARCGIS"))
            return MapDriverType::ARCGIS;
    }
};

#endif // EARTHOBJECTS_H
