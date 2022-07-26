#pragma once

#include <QObject>
#include <osgGA/GUIEventHandler>
#include <osgViewer/Viewer>
#include <osgEarth/SpatialReference>
#include <osg/CoordinateSystemNode>
#include <osgEarth/MapNode>
#include <osgEarth/ElevationPool>
#include <osgEarth/ElevationQuery>

class EarthEventHandler : public QObject,public osgGA::GUIEventHandler
{
	Q_OBJECT

public:
	EarthEventHandler();
	~EarthEventHandler();

	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

private:
	osg::Vec3d GetCurCoord(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

signals:
	void EarthMouseMove(const osg::Vec3d&);

private:
	const osg::EllipsoidModel* m_pEllipsoid;
	//osgEarth::MapNode* m_pMapNode;
};
