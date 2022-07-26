#include "EarthEventHandler.h"

EarthEventHandler::EarthEventHandler()
{
    m_pEllipsoid = new osg::EllipsoidModel;
    //m_pMapNode = pMapNode;
    /*m_Terrain = pMapNode->getTerrain();
    m_Envelope = pMapNode->getMap()->getElevationPool()->createEnvelope(pMapNode->getMap()->getSRS(), 20u);*/

    //m_pEllipsoid = srs->getGeocentricSRS()->getEllipsoid();
}

EarthEventHandler::~EarthEventHandler()
{
}

bool EarthEventHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
    //将aa强制转换为viewer对象
    osgViewer::Viewer* viewer = dynamic_cast<osgViewer::Viewer*>(&aa);
    if (!viewer)//如果转换失败则直接退出
    {
        return false;
    }
    switch (ea.getEventType())//获取事件的类型，是键盘上的事件，还是鼠标上的事件以及鼠标单击，右击，双击等等。
    {
    case osgGA::GUIEventAdapter::KEYDOWN://键盘响应事件
        if (ea.getKey() == 0xFF51)
        {
            //首先获得场景中的数据，然后在获得Group，然后在获得Group的子节点，最后设置显示模式
            viewer->getSceneData()->asGroup()->getChild(0)->setNodeMask(1);//按向左的方向键
            viewer->getSceneData()->asGroup()->getChild(1)->setNodeMask(0);
        }
        if (ea.getKey() == 0xFF53)
        {
            viewer->getSceneData()->asGroup()->getChild(0)->setNodeMask(0);//按下向右的方向键
            viewer->getSceneData()->asGroup()->getChild(1)->setNodeMask(1);
        }
        break;
    case osgGA::GUIEventAdapter::PUSH:
        if (ea.getButton() == 4)//表示按鼠标右键
        {
            viewer->getSceneData()->asGroup()->getChild(0)->setNodeMask(0);
            viewer->getSceneData()->asGroup()->getChild(1)->setNodeMask(0);
        }
        break;
    case osgGA::GUIEventAdapter::DOUBLECLICK://表示双击类型
        if (ea.getButton() == 1)//表示按鼠标左键
        {
            viewer->getSceneData()->asGroup()->getChild(0)->setNodeMask(1);
            viewer->getSceneData()->asGroup()->getChild(1)->setNodeMask(1);
        }
        break;
    case osgGA::GUIEventAdapter::MOVE:
        if (true)
        {
            osg::Vec3d coord = GetCurCoord(ea, aa);
            emit EarthMouseMove(coord);
        }
        break;
    default:
        break;
    }
    return false;
}

osg::Vec3d EarthEventHandler::GetCurCoord(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
    osg::Vec3d coord = osg::Vec3d(0, 0, 0);
    osgViewer::Viewer* pViewer = dynamic_cast<osgViewer::Viewer*>(&aa);
    if (pViewer == NULL)
    {
        return osg::Vec3d(0, 0, 0);
    }
    // 获取当前点
    osgUtil::LineSegmentIntersector::Intersections intersection;
    double x = ea.getX();
    double y = ea.getY();
    pViewer->computeIntersections(ea.getX(), ea.getY(), intersection);
    osgUtil::LineSegmentIntersector::Intersections::iterator iter = intersection.begin();
    if (iter != intersection.end())
    {

        m_pEllipsoid->convertXYZToLatLongHeight(
            iter->getWorldIntersectPoint().x(), iter->getWorldIntersectPoint().y(), iter->getWorldIntersectPoint().z(),
            coord.y(), coord.x(), coord.z());
        coord.x() = osg::RadiansToDegrees(coord.x());
        coord.y() = osg::RadiansToDegrees(coord.y());

        /*double query_resolution = 0.00000001;
        double out_resolution = 0.0;
        osgEarth::ElevationQuery query(m_pMapNode->getMap());
        query.getElevation(osgEarth::GeoPoint::GeoPoint(m_pMapNode->getMapSRS(), 103.50, 31.50, 0.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE), query_resolution, &out_resolution);*/

        return coord;
    }
    return osg::Vec3d(0, 0, 0);
}
