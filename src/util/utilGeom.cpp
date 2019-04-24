// Copyright (c) 2019    Prashant K. Jha
//
// Distributed under the GNU GENERAL PUBLIC LICENSE, Version 3.0.
// (See accompanying file LICENSE.txt)

#include "utilGeom.h"
#include "compare.h"
#include "transfomation.h"
#include <cmath>                      // definition of sin, cosine etc

bool util::geometry::isPointInsideRectangle(util::Point3 x, double x_min,
                                            double x_max, double y_min,
                                            double y_max) {

  return !(util::compare::definitelyLessThan(x.d_x, x_min - 1.0E-12) or
           util::compare::definitelyLessThan(x.d_y, y_min - 1.0E-12) or
           util::compare::definitelyGreaterThan(x.d_x, x_max + 1.0E-12) or
           util::compare::definitelyGreaterThan(x.d_y, y_max + 1.0E-12));
}

bool util::geometry::isPointInsideAngledRectangle(util::Point3 x, double x1,
                                                  double x2, double y1,
                                                  double y2, double theta) {
  // we assume that the rectangle has passed the test

  //
  //                             (x2,y2)
  //                            o
  //
  //
  //
  //
  //
  //        o
  //      (x1,y1)

  // get divisors
  util::Point3 lam = util::transformation::rotateCW2D(
      util::Point3(x2 - x1, y2 - y1, 0.0), theta);

  // double lam1 = (x2-x1) * std::cos(theta) + (y2-y1) * std::sin(theta);
  // double lam2 = -(x2-x1) * std::sin(theta) + (y2-y1) * std::cos(theta);

  // get mapped coordinate of x
  util::Point3 xmap = util::transformation::rotateCW2D(
      util::Point3(x[0] - x1, x[1] - y1, 0.0), theta);

  // double xmap = (x[0]-x1) * std::cos(theta) + (x[1]-y1) * std::sin(theta);
  // double ymap = -(x[0]-x1) * std::sin(theta) + (x[1]-y1) * std::cos(theta);

  // check if mapped coordinate are out of range [0, lam1] and [0, lam2]
  return !(util::compare::definitelyLessThan(xmap[0], -1.0E-12) or
           util::compare::definitelyLessThan(xmap[1], -1.0E-12) or
           util::compare::definitelyGreaterThan(xmap[0], lam[0] + 1.0E-12) or
           util::compare::definitelyGreaterThan(xmap[1], lam[1] + 1.0E-12));
}