#include "DigitalEarthSDK.h"
#include <QDebug>

DigitalEarthSDK* DigitalEarthSDK::instance = NULL;

DigitalEarthSDK* DigitalEarthSDK::Instance()
{
    if (instance == NULL)
    {
        instance = new DigitalEarthSDK();
        atexit(Release);
    }
    return instance;
}

void DigitalEarthSDK::Release()
{
    if (instance)
    {
        delete instance;
        instance = NULL;
    }
}

DigitalEarthSDK::DigitalEarthSDK()
{
    _viewer = new osgViewer::Viewer;
    _root = new osg::Group;
    _camera = new osg::Camera;
    _map = new osgEarth::Map();
    _mapNode = new osgEarth::MapNode(_map);
    _earthManipulator = new osgEarth::Util::EarthManipulator;
    ellipsoidModel = new osg::EllipsoidModel;
}

QWidget* DigitalEarthSDK::LoadEarth()
{
    InitOSG();
    InitOSGEarth();
    osgQt::GraphicsWindowQt* gw = dynamic_cast<osgQt::GraphicsWindowQt*>(_camera->getGraphicsContext());
    QWidget* osg_widget = (QWidget*)(gw->getGLWidget());

    InitTimer();
    earthEventHandler = new EarthEventHandler();

    QObject::connect(earthEventHandler, &EarthEventHandler::EarthMouseMove, this, &DigitalEarthSDK::GetCurCoord);
    _viewer->addEventHandler(earthEventHandler);

    return osg_widget;
}

void DigitalEarthSDK::InitMaps(std::vector<MapObject> maps)
{
    osgEarth::ProfileOptions options;
    options.srsString() = "SRS string";
    osgEarth::Bounds bs(-180, -90, 180, 90);
    options.bounds() = bs;
    _map->setProfile(osgEarth::Profile::create(options));

    if(maps.size()>0)
    {
        size_t len = maps.size();
        for (size_t index=0;index<len ;index++ )
        {
            MapObject map = maps.at(index);
            if(map.mapType==MapType::Image)
            {
                AddImage(map);
            }
            else
            {
                AddElevation(map);
            }
        }
    }

    //    osgEarth::TMSImageLayer* tmsLayer = new osgEarth::TMSImageLayer();
    //    tmsLayer->setURL(osgEarth::URI("./config/tifs/tms.xml"));
    //    tmsLayer->setName("Image");
    //    _map->addLayer(tmsLayer);
}

void DigitalEarthSDK::AddImage(MapObject map)
{
    switch (map.driverType)
    {
    case MapDriverType::TMS:
    {
        osg::ref_ptr<osgEarth::TMSImageLayer> layer = new osgEarth::TMSImageLayer();
        layer->setURL(osgEarth::URI(map.url));
        qDebug()<<QString::fromStdString(map.url);
        layer->setName(map.name);
        layer->setVisible(map.isVisible);
        layer->setEnabled(map.enabled);
        _map->addLayer(layer);
        break;
    }
    case MapDriverType::XYZ:
    {
        osg::ref_ptr<osgEarth::XYZImageLayer> layer= new osgEarth::XYZImageLayer;
        layer->setURL(osgEarth::URI(map.url));
        layer->setName(map.name);
        layer->setVisible(map.isVisible);
        layer->setEnabled(map.enabled);
        _map->addLayer(layer);
        break;
    }
    case MapDriverType::ARCGIS:
    {
        break;
    }
    default:
        break;
    }
}

void DigitalEarthSDK::AddElevation(MapObject map)
{
    switch (map.driverType)
    {
    case MapDriverType::TMS:
    {
        osg::ref_ptr<osgEarth::TMSElevationLayer> layer = new osgEarth::TMSElevationLayer;
        layer->setURL(osgEarth::URI(map.url));
        layer->setName(map.name);
        layer->setVisible(map.isVisible);
        layer->setEnabled(map.enabled);
        _map->addLayer(layer);
        break;
    }
    case MapDriverType::XYZ:
    {
        osg::ref_ptr<osgEarth::XYZElevationLayer> layer= new osgEarth::XYZElevationLayer;
        layer->setURL(osgEarth::URI(map.url));
        layer->setName(map.name);
        layer->setVisible(map.isVisible);
        layer->setEnabled(map.enabled);
        _map->addLayer(layer);
        break;
    }
    case MapDriverType::ARCGIS:
    {
        break;
    }
    default:
        break;
    }
}

void DigitalEarthSDK::SetMapVisibility(std::string mapName, bool isVisible)
{
    osgEarth::Layer* layer = _map->getLayerByName(mapName);
    if(layer)
    {
        osgEarth::VisibleLayer* visibleLayer = dynamic_cast<osgEarth::VisibleLayer*>(layer);
        visibleLayer->setVisible(isVisible);
    }
}

bool DigitalEarthSDK::GetMapVisibility(std::string mapName)
{
    osgEarth::Layer* layer = _map->getLayerByName(mapName);
    if(layer)
    {
        osgEarth::VisibleLayer* visibleLayer = dynamic_cast<osgEarth::VisibleLayer*>(layer);
        return visibleLayer->getVisible();
    }
    return false;
}

void DigitalEarthSDK::InitOSG()// 初始化设置osg
{

    // 设置模型

    // 显示 .earth 文件中的地球模型
    //    _earthNode = new osg::Node;
    //    QString earthFilePath = QCoreApplication::applicationDirPath();
    //    earthFilePath += "/config/mymap.earth";
    QString earthFilePath = "./config/mymap.earth";
    //    _earthNode = osgDB::readNodeFile(earthFilePath.toLocal8Bit().data());

    //获取屏幕分辨率 长宽
    osg::GraphicsContext::WindowingSystemInterface* wsi = osg::GraphicsContext::getWindowingSystemInterface();
    if (!wsi)
        return;
    unsigned int width, height;
    wsi->getScreenResolution(osg::GraphicsContext::ScreenIdentifier(0), width, height);
    //设置图形环境特性
    osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
    traits->windowDecoration = false;//声明是否显示窗口的描述
    traits->x = 0;
    traits->y = 0;
    traits->width = width;
    traits->height = height;
    traits->doubleBuffer = true;//创建图形窗口是否使用双缓存

    //设置照相机

    _camera->setGraphicsContext(new osgQt::GraphicsWindowQt(traits.get()));
    _camera->setClearColor(osg::Vec4(0.2, 0.2, 0.6, 1.0));
    _camera->setViewport(new osg::Viewport(0, 0, width, height));
    _camera->setProjectionMatrixAsPerspective(30.0f, (double(traits->width)) / (double(traits->height)), 1.0f, 10000.0f);

    //设置渲染器
    _viewer->setCamera(_camera);
    _viewer->setSceneData(_root);
    _viewer->setThreadingModel(osgViewer::Viewer::SingleThreaded);//创建为单线程
    _viewer->addEventHandler(new osgGA::StateSetManipulator(_viewer->getCamera()->getOrCreateStateSet()));
    _viewer->addEventHandler(new osgViewer::StatsHandler);//快捷键S-查看帧率、CPU占用等状态
}

void DigitalEarthSDK::InitOSGEarth()
{
    //mapnode初始化



    _earthForm = new osg::MatrixTransform;
    //osgearth操作器

    if (_mapNode.valid())
    {
        _earthManipulator->setNode(_mapNode);
    }

    _earthManipulator->getSettings()->setArcViewpointTransitions(true);
    _viewer->setCameraManipulator(_earthManipulator);

    //获取地球半径 设置视点
    double earth_R = _mapNode->getMap()->getSRS()->getEllipsoid().getRadiusEquator();
    const char* viewPointName = QString::fromLocal8Bit("北京").toStdString().c_str();
    _earthManipulator->setViewpoint(osgEarth::Viewpoint(viewPointName, 112.44, 33.75, 0.0, 0.0, -90.0, 5 * earth_R), 5);
    //初始化天空
    InitSky();
}

void DigitalEarthSDK::InitSky()
{
    //获取当前时间 初始化天空
    now_time = time(0);
    t_tm = localtime(&now_time);;
    osgEarth::DateTime cur_date_time(now_time);
    osgEarth::Util::Ephemeris* ephemeris = new osgEarth::Util::Ephemeris;

    //设置黑夜明暗程度
    osgEarth::Util::SkyOptions skyOptions;
    skyOptions.ambient() = 0.1;

    _skyNode = osgEarth::SkyNode::create(skyOptions);
    _skyNode->setName("SkyNode");
    _skyNode->setAtmosphereVisible(0.6f);
    _skyNode->setEphemeris(ephemeris);
    _skyNode->setDateTime(cur_date_time);
    _viewer->setLightingMode(osg::View::SKY_LIGHT);
    _skyNode->attach(_viewer, 0);
    _skyNode->setLighting(false);

    _skyNode->addChild(_mapNode);
    _root->addChild(_skyNode);

}

void DigitalEarthSDK::InitTimer()//屏幕刷新初始化
{
    _timer = new QTimer;
    QObject::connect(_timer, &QTimer::timeout, this, &DigitalEarthSDK::updateFrame);
    _timer->start(10);
}

void DigitalEarthSDK::updateFrame()
{
    _viewer->frame();
}

void DigitalEarthSDK::GetCurCoord(const osg::Vec3d& coord)
{
    curCoord.setX(coord.x());
    curCoord.setY(coord.y());
    curCoord.setZ(coord.z());
    //    emit OnMouseMove(curCoord);
}
