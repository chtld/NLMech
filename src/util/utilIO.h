////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2019 Prashant K. Jha
//  Copyright (c) 2019 Patrick Diehl
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#ifndef UTILS_UTIL_IO_H
#define UTILS_UTIL_IO_H

#include "point.h"
#include <vector>
#include <iostream>

namespace util {

/*! @brief Provides geometrical methods such as point inside rectangle */
namespace io {

inline std::string getTabS(int nt) {
  std::string tabS = "";
  for (int i = 0; i < nt; i++)
    tabS += "\t";

  return tabS;
};

template <class T> inline std::string printStr(const std::vector<T> &list,
    int nt =
    0) {

  auto tabS = getTabS(nt);
  std::ostringstream oss;
  oss << tabS;
  size_t i = 0;
  for (auto l : list) {
    oss << l;
    i++;
    if (i != list.size())
      oss << ", ";
  }

  return oss.str();
};

template <> inline std::string printStr(const std::vector<util::Point3> &list,
                                               int nt) {

  auto tabS = getTabS(nt);
  std::ostringstream oss;
  oss << tabS;
  size_t i = 0;
  for (auto l : list) {
    oss << "(" << l[0] << ", " << l[1] << ", " << l[2] << ")";
    i++;
    if (i != list.size())
      oss << ", ";
  }

  return oss.str();
};

template <class T> inline void print(const std::vector<T> &list, int nt = 0) {

  std::cout << printStr(list, nt);
};

template <class T>
inline std::string printStr(const std::vector<std::vector<T>> &list,
                            int nt = 0) {

  auto tabS = getTabS(nt);
  std::ostringstream oss;
  oss << tabS;
  size_t i = 0;
  for (auto l : list) {
    oss << "(";
    for (size_t k = 0; k < l.size(); k++) {
      oss << l[k];
      if (k < l.size() - 1)
        oss << ", ";
    }
    oss << ")";

    i++;
    if (i != list.size())
      oss << ", ";
  }

  return oss.str();
}

template <class T> inline void print(const std::vector<std::vector<T>> &list, int nt = 0) {

  std::cout << printStr(list, nt);
};

/*!
 * @brief Prints box to std::cout
 */

inline std::string printBoxStr(const std::pair<util::Point3, util::Point3>
    &box, int nt =
0) {
  auto tabS = getTabS(nt);
  std::ostringstream oss;
  oss << tabS << "Corner point 1 = " << box.first.printStr(nt, 0) << std::endl;
  oss << tabS << "Corner point 2 = " << box.second.printStr(nt, 0) << std::endl;

  return oss.str();
};

inline void printBox(const std::pair<util::Point3, util::Point3> &box, int nt
= 0) {
  std::cout << printBoxStr(box, nt);
};

inline std::string printBoxStr(const std::pair<std::vector<double>, std::vector<double>>
                               &box, int nt =
0) {
  auto tabS = getTabS(nt);
  std::ostringstream oss;
  oss << tabS << "Corner point 1 = (" << printStr<double>(box.first, 0)
              << ")" << std::endl;
  oss << tabS << "Corner point 2 = (" << printStr<double>(box.second, 0)
              << ")" << std::endl;

  return oss.str();
};

inline void printBox(const std::pair<std::vector<double>, std::vector<double>> &box, int nt
= 0) {
  std::cout << printBoxStr(box, nt);
};
} // namespace io

} // namespace util

#endif // UTILS_UTIL_IO_H