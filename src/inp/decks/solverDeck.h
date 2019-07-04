////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2019 Prashant K. Jha
//  Copyright (c) 2019 Patrick Diehl
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#ifndef INP_SOLVERDECK_H
#define INP_SOLVERDECK_H

#include <iostream> // error handling
#include <vector>

namespace inp {

/**
 * \ingroup Input
 */
/**@{*/

/*! @brief Structure to read and store solver related input data */
struct SolverDeck {

  /**
   * @name Data members
   */
  /**@{*/

  /*! @brief Solver type */
  std::string d_solverType;

  /*! @brief Maximum iterations */
  int d_maxIters;

  /*! @brief Tolerance */
  double d_tol;

  /** @}*/

  /*!
   * @brief Constructor
   */
  SolverDeck() : d_maxIters(0), d_tol(0.){};
};

/** @}*/

} // namespace inp

#endif // INP_SOLVERDECK_H
