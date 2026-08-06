#ifndef VEC3_HPP
#define VEC3_HPP
class Vec3
{
  public:
    Vec3();
    Vec3(double, double, double);
    double getX() {return x;}
    double getY() {return y;}
    double getZ() {return z;}

    void Set(double _x, double _y, double _z)
    {
      this->x = _x;
      this->y = _y;
      this->z = _z;
    }
  private:
    double x;
    double y;
    double z;
};
#endif