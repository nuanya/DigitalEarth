#ifndef DIGITALEARTHSDK_H
#define DIGITALEARTHSDK_H

#include "DigitalEarthSDK_global.h"
#include "EarthEventHandler.h"
#include "GraphicsWindowQt.h"

#include <osg/Array>
#include <osg/Camera>
#include <osg/CoordinateSystemNode>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Group>
#include <osg/LineWidth>
#include <osg/Node>
#include <osg/PositionAttitudeTransform>
#include <osgDB/ReadFile>
#include <osgEarth/EarthManipulator>
#include <osgEarth/Ephemeris>
#include <osgEarth/GeoCommon>
#include <osgEarth/GeoData>
#include <osgEarth/GeoTransForm>
#include <osgEarth/GLUtils>
#include <osgEarth/ImageLayer>
#include <osgEarth/MapNode>
#include <osgEarth/Profile>
#include <osgEarth/Sky>
#include <osgEarth/SpatialReference>
#include <osgEarth/TMS>
#include <osgEarth/URI>
#include <osgEarth/XYZ>
#include <osgGA/TrackballManipulator>
#include <osgGA/StateSetManipulator>
#include <osgUtil/Tessellator>
#include <osgViewer/ViewerEventHandlers>
#include "Objects/EarthObjects.h"

#include <QCoreApplication>
#include <QDialog>
#include <QTimer>
#include <QVector3D>

#pragma comment(lib,"osg.lib")
#pragma comment(lib,"osgViewer.lib")
#pragma comment(lib,"osgDB.lib")
#pragma comment(lib,"osgGA.lib")
#pragma comment(lib,"osgEarth.lib")
#pragma comment(lib,"osgFX.lib")
#pragma comment(lib,"osgManipulator.lib")
#pragma comment(lib,"osgParticle.lib")
#pragma comment(lib,"osgShadow.lib")
#pragma comment(lib,"osgSim.lib")
#pragma comment(lib,"osgTerrain.lib")
#pragma comment(lib,"osgText.lib")
#pragma comment(lib,"osgUtil.lib")
#pragma comment(lib,"OpenThreads.lib")

class DIGITALEARTHSDK_EXPORT DigitalEarthSDK : public QDialog
{
    Q_OBJECT
public:
    static DigitalEarthSDK* Instance();
    static void Release();
    /**
     * @brief LoadEarth 加载数字地球
     * @return 返回数字地球Widget
     */
    QWidget* LoadEarth();
    /**
     * @brief GetSceneRoot 获取场景根节点
     * @return 返回根节点
     */
    osg::ref_ptr<osg::Group> GetSceneRoot(){return _root;}
    /**
     * @brief InitMaps 初始化地图
     * @param maps 地图数据
     */
    void InitMaps(std::vector<MapObject> maps);
    /**
     * @brief AddImage 添加影像数据
     * @param map 影像数据
     */
    void AddImage(MapObject map);
    /**
     * @brief AddElevation 添加高程数据
     * @param map 数据
     */
    void AddElevation(MapObject map);
    /**
     * @brief SetMapVisibility 设置地图显隐性
     * @param mapName 地图名称
     * @param isVisible 显隐性
     */
    void SetMapVisibility(std::string mapName,bool isVisible);
    /**
     * @brief GetMapVisibility 获取地图显隐性
     * @param mapName 地图名称
     * @return
     */
    bool GetMapVisibility(std::string mapName);

private:
    /**
     * @brief DigitalEarthSDK 构造函数
     */
    DigitalEarthSDK();
    /**
     * @brief InitOSG 初始化设置osg
     */
    void InitOSG();
    /**
     * @brief InitTimer 初始化定时器
     */
    void InitTimer();
    /**
     * @brief InitOSGEarth 初始化osgearth
     */
    void InitOSGEarth();
    /**
     * @brief InitSky 初始化天空
     */
    void InitSky();

public:
    QVector3D curCoord;

    osg::ref_ptr<osg::EllipsoidModel> ellipsoidModel;

private:
    static DigitalEarthSDK* instance;
    /**
     * @brief _timer 渲染定时器
     */
    QTimer* _timer;
    /**
     * @brief _viewer 主视图
     */
    osgViewer::Viewer* _viewer;
    /**
     * @brief _camera 主相机
     */
    osg::ref_ptr<osg::Camera> _camera;
    /**
     * @brief _earthNode 地球节点
     */
    osg::ref_ptr<osg::Node> _earthNode;
    /**
     * @brief _map 地图
     */
    osg::ref_ptr<osgEarth::Map> _map;
    /**
     * @brief _mapNode 地图节点
     */
    osg::ref_ptr<osgEarth::MapNode> _mapNode;
    /**
     * @brief _earthForm
     */
    osg::ref_ptr<osg::MatrixTransform> _earthForm;
    /**
     * @brief _earthManipulator
     */
    osg::ref_ptr<osgEarth::EarthManipulator> _earthManipulator;
    /**
     * @brief _skyNode 天空盒节点
     */
    osgEarth::SkyNode* _skyNode;
    /**
     * @brief _root Scene根节点
     */
    osg::ref_ptr<osg::Group> _root;

    tm* t_tm;

    time_t now_time;

    EarthEventHandler* earthEventHandler = NULL;

//signals:
//    void OnMouseMove(QVector3D);

private slots:
    // 定时更新帧的槽函数
    void updateFrame();

    void GetCurCoord(const osg::Vec3d&);
};

#endif // DIGITALEARTHSDK_H
