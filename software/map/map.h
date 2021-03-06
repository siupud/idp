#include <vector>

namespace idp {

class Point {
public:
  char name[2];
  double coord_x;
  double coord_y;
}; // class Point

class Line {
public:
  char point1[2];
  char point2[2];

  bool is_straight;  // true for a straight line, false for circular arc
  int orientation;
  /*  0 if the straight line is vertical, or the circular arc from point1 to point2 is vertical
      1 if horizontal
      2 if at 45 degrees anticlockwise from horizontal
      3 if at 45 degrees clockwise from horizontal
  */
}; // class Line

class Map {
public:
  Map();
  int populate();

private:
  char map_filename[256];
  std::vector<Point> _points;
  std::vector<Line> _lines;
}; // class Map

} // namespace idp