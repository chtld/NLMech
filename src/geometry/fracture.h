////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2019 Prashant K. Jha
//  Copyright (c) 2019 Patrick Diehl
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#ifndef GEOM_FRACTURE_H
#define GEOM_FRACTURE_H

#include "util/point.h" // definition of Point3
#include <inp/decks/fractureDeck.h>
#include <stdint.h> // uint8_t type
#include <string.h> // size_t type
#include <vector>

// forward declaration of fracture deck
namespace inp {
struct EdgeCrack;
struct FractureDeck;
} // namespace inp

/*! @brief Collection of methods and data related to geometry */
namespace geometry {

/*! @brief A class for fracture state of bonds
 *
 * This class provides method to read and modify fracture state of bonds
 */
class Fracture {

public:
  /*!
   * @brief Constructor
   * @param deck Input deck which contains user-specified information
   * @param nodes Pointer to nodal coordinates
   * @param neighbor_list Pointer to neighbor list
   */
  Fracture(inp::FractureDeck *deck, const std::vector<util::Point3> *nodes,
           const std::vector<std::vector<size_t>> *neighbor_list);

  /*!
   * @brief Constructor
   * @param deck Input deck which contains user-specified information
   */
  explicit Fracture(inp::FractureDeck *deck);

  /*!
   * @brief Sets fracture state according to the crack data
   * @param time Actual simulation time
   * @param nodes Pointer to nodal coordinates
   * @param neighbor_list Pointer to neighbor list
   * @return True if one of the crack is applied at given time
   */
  bool addCrack(const double &time, const std::vector<util::Point3> *nodes,
            const std::vector<std::vector<size_t>> *neighbor_list);

  /*!
   * @brief Sets the bond state
   *
   * @param i Nodal id
   * @param j Local id of bond in neighbor list of i
   * @param state State which is applied to the bond
   */
  void setBondState(const size_t &i, const size_t &j, const bool &state);

  /*!
   * @brief Read bond state
   *
   * @param i Nodal id
   * @param j Local id of bond in neighbor list of i
   * @return bool True if bond is fractured otherwise false
   */
  bool getBondState(const size_t &i, const size_t &j) const;

  /*!
   * @brief Returns the list of bonds of node i
   *
   * @param i Nodal id
   * @return list Bonds of node i
   */
  std::vector<uint8_t> getBonds(const size_t &i) const;

  /*!
   * @brief Returns the string containing information about the instance of
   * the object
   *
   * @param nt Number of tabs to append before each line of string
   * @param lvl Level of information sought (higher level means more
   * information)
   * @return string String containing information about this object
   * */
  std::string printStr(int nt = 0, int lvl = 0) const;

  /*!
   * @brief Prints the information about the instance of the object
   *
   * @param nt Number of tabs to append before each line of string
   * @param lvl Level of information sought (higher level means more
   * information)
   * */
  void print(int nt = 0, int lvl = 0) const { std::cout << printStr(nt, lvl); };

private:
  /*!
   * @brief Sets state of bond which intersect the pre-crack line as fractured
   *
   * @param i Nodal id
   * @param crack Pointer to the pre-crack
   * @param nodes Pointer to nodal coordinates
   * @param neighbors Pointer to neighbors of node i
   */
  void computeFracturedBondFd(const size_t &i, inp::EdgeCrack *crack,
                              const std::vector<util::Point3> *nodes,
                              const std::vector<size_t> *neighbors);

  /*! @brief Interior flags deck */
  inp::FractureDeck *d_fractureDeck_p;

  /*! @brief Vector which stores the state of bonds
   *
   * Given node i, vector d_fracture[i] is the list of state of bonds of node
   * i.
   *
   * We only use 1 bit per bond of node to store the state.
   */
  std::vector<std::vector<uint8_t>> d_fracture;
};

} // namespace geometry

#endif // GEOM_FRACTURE_H
