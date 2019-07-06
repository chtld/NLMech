// Copyright (c) 2019    Prashant K. Jha
//
// Distributed under the GNU GENERAL PUBLIC LICENSE, Version 3.0.
// (See accompanying file LICENSE.txt)

#ifndef RW_VTKREADER_H
#define RW_VTKREADER_H

#include <vtkSmartPointer.h>
#include <vtkUnstructuredGrid.h>
#include <vtkXMLUnstructuredGridReader.h>

#include "util/point.h"           // definition of Point3

namespace rw {

namespace reader {

/*!
 * @brief A class to read VTK (.vtu) mesh files
 *
 * @note Depends on VTK library.
 */
class VtkReader {

public:
  /*!
   * @brief Constructor
   * @param filename Name of mesh file
   *
   * @note filename is expected to have .vtu extension
   */
  explicit VtkReader(const std::string &filename);

  /*!
   * @brief Reads mesh data into node file and element file
   * @param dim Dimension
   * @param nodes Vector of nodes data
   * @param element_type Type of element
   * @param num_elem Number of elements
   * @param enc Vector holding element-node connectivity
   * @param nec Vector holding node-element connectivity
   * @param volumes Vector holding volume of the nodes
   * @param is_fd Flag indicating if this mesh is for finite_difference
   * simulation
   */
  void readMesh(size_t dim, std::vector<util::Point3> *nodes,
                size_t &element_type, size_t &num_elem,
                std::vector<size_t> *enc, std::vector<std::vector<size_t>> *nec,
                std::vector<double> *volumes, bool is_fd = false);

  /*!
   * @brief Reads nodal position
   *
   * @param nodes Vector of nodal coordinates
   */
  void readNodes(std::vector<util::Point3> *nodes);

  /*!
   * @brief reads point data from .vtu file
   * @param name Name of data
   * @param data Pointer to the vector of data
   * @return status True if data is found otherwise false
   */
  bool readPointData(const std::string &name, std::vector<util::Point3> *data);

  /*!
   * @brief reads point data from .vtu file
   * @param name Name of data
   * @param data Pointer to the vector of data
   * @return status True if data is found otherwise false
   */
  bool readPointData(const std::string &name, std::vector<double> *data);

  /*! @brief Close the file */
  void close();

private:

  /*! @brief Counter */
  static size_t d_count;

  /*! @brief XML unstructured grid writer */
  vtkSmartPointer<vtkXMLUnstructuredGridReader> d_reader_p;

  /*! @brief Unstructured grid */
  vtkSmartPointer<vtkUnstructuredGrid> d_grid_p;
};

} // namespace reader

} // namespace rw

#endif // RW_VTKREADER_H
