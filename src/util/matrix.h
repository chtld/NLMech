// Copyright (c) 2019    Prashant K. Jha
//
// Distributed under the GNU GENERAL PUBLIC LICENSE, Version 3.0.
// (See accompanying file LICENSE.txt)

#ifndef UTIL_MATRIX_H
#define UTIL_MATRIX_H

namespace util {

/*! @brief A structure to represent 3d matrices */
struct Matrix3 {

  /**
   * \defgroup Data members
   */
  /**@{*/

  /**< @brief the xx component */
  float d_xx;

  /**< @brief the xy component */
  float d_xy;

  /**< @brief the xz component */
  float d_xz;

  /**< @brief the yx component */
  float d_yx;

  /**< @brief the yy component */
  float d_yy;

  /**< @brief the yz component */
  float d_yz;

  /**< @brief the zx component */
  float d_zx;

  /**< @brief the zy component */
  float d_zy;

  /**< @brief the zz component */
  float d_zz;

  /** @}*/

  /*!
   * @brief Constructor
   */
  Matrix3()
      : d_xx(0.), d_xy(0.), d_xz(0.), d_yx(0.), d_yy(0.), d_yz(0.), d_zx(0.),
        d_zy(0.), d_zz(0.){};
};

/*! @brief A structure to represent 3d symmetric matrices */
struct SymMatrix3 {

  /**
   * \defgroup Data members
   */
  /**@{*/

  /**< @brief the xx component */
  float d_xx;

  /**< @brief the yy component */
  float d_yy;

  /**< @brief the zz component */
  float d_zz;

  /**< @brief the xy (yx) component */
  float d_xy;

  /**< @brief the xz (zx) component */
  float d_xz;

  /**< @brief the yz (zy) component */
  float d_yz;

  /** @}*/

  /*!
   * @brief Constructor
   */
  SymMatrix3() : d_xx(0.), d_yy(0.), d_zz(0.), d_xy(0.), d_xz(0.), d_yz(0.){};
};

} // namespace util

#endif
