#ifndef COORDINATE_H
#define COORDINATE_H

#include <osg/Vec3d>

class Coordinate : public osg::Vec3d
{
public:
    Coordinate();

    Coordinate(double longitude = 0.0, double latitude = 0.0, double altitude = 0.0);

    double Longitude(){return _longitude;}

    void SetLongitude(double value){_longitude = value;}

    double Latitude(){return _latitude;}

    double SetLatitude(double value){_latitude = value;}

    double Altitude(){return _altitude;}

    double SetAltitude(double value){_altitude = value;}

private:
    double _longitude;
    double _latitude;
    double _altitude;
};

#endif // COORDINATE_H
