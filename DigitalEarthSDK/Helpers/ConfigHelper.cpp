#include "ConfigHelper.h"

QMap<std::string,QJsonValue>* ConfigHelper::_baseConfigCaches = 0;
QJsonValue ConfigHelper::GetBaseConfigByName(std::string dataName)
{
    if(dataName.empty())
    {
        return QJsonValue();
    }
    if(_baseConfigCaches&&_baseConfigCaches->contains(dataName))
    {
        return _baseConfigCaches->value(dataName);
    }
    return QJsonValue();
}

bool ConfigHelper::ReadBaseConfigs()
{
    if(!_baseConfigCaches)
    {
        _baseConfigCaches = new QMap<std::string,QJsonValue>;
    }
    QJsonDocument res = JsonTool::Read("./config/DataSourceConfig.json");
    if(res.isNull()||!res.isObject())
        return false;
    QJsonObject obj = res.object();
    QJsonObject::Iterator iterator;
    _baseConfigCaches->clear();
    for(iterator=obj.begin();iterator!=obj.end();iterator++)
    {
        _baseConfigCaches->insert(iterator.key().toStdString(),iterator.value());
    }
    return true;
}
