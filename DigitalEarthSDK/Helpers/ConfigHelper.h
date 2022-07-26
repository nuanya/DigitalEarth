#ifndef CONFIGHELPER_H
#define CONFIGHELPER_H
#include <QMap>
#include <iostream>
#include "DigitalEarthSDK_global.h"
#include "Tools/JsonTool.h"

class DIGITALEARTHSDK_EXPORT ConfigHelper
{
public:
    static bool ReadBaseConfigs();
    static QJsonValue GetBaseConfigByName(std::string dataName);

private:
    static QMap<std::string,QJsonValue>* _baseConfigCaches;
};

#endif // CONFIGHELPER_H
