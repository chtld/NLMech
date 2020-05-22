////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2019 Prashant K. Jha
//  Copyright (c) 2019 Patrick Diehl
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#include "vtkReader.h"

#include <vtkAbstractArray.h>
#include <vtkCellArray.h>
#include <vtkCellData.h>
#include <vtkDoubleArray.h>
#include <vtkFieldData.h>
#include <vtkIdList.h>
#include <vtkIntArray.h>
#include <vtkPointData.h>
#include <vtkPoints.h>
#include <vtkUnsignedCharArray.h>
#include <vtkUnsignedIntArray.h>

#include "util/feElementDefs.h"

size_t rw::reader::VtkReader::d_count = 0;

rw::reader::VtkReader::VtkReader(const std::string &filename) {
  d_count++;

  // Append the extension vtu to file_name
  d_reader_p = vtkSmartPointer<vtkXMLUnstructuredGridReader>::New();
  d_reader_p->SetFileName(const_cast<char *>(filename.c_str()));
  d_reader_p->Update();
}

<<<<<<< HEAD
bool rw::reader::VtkReader::vtuHasPointData(const std::string &data_tag) {

  // read point field data
  d_grid_p = d_reader_p->GetOutput();
  vtkPointData *p_field = d_grid_p->GetPointData();
  for (size_t i=0; i<p_field->GetNumberOfArrays(); i++) {
    auto tag = p_field->GetArrayName(i);

    if (tag == data_tag)
      return true;
  }

  return false;
}

bool rw::reader::VtkReader::vtuHasCellData(const std::string &data_tag) {

  // read point field data
  d_grid_p = d_reader_p->GetOutput();
  vtkCellData *c_field = d_grid_p->GetCellData();
  for (size_t i=0; i<c_field->GetNumberOfArrays(); i++) {
    auto tag = c_field->GetArrayName(i);
    if (tag == data_tag)
      return true;
  }

  return false;
}

std::vector<std::string> rw::reader::VtkReader::readVtuFilePointTags() {

=======
std::vector<std::string> rw::reader::VtkReader::readVtuFilePointTags() {
>>>>>>> master
  // read point field data
  d_grid_p = d_reader_p->GetOutput();
  vtkPointData *p_field = d_grid_p->GetPointData();

  std::vector<std::string> tags;

<<<<<<< HEAD
  for (size_t i=0; i<p_field->GetNumberOfArrays(); i++) {
=======
  for (size_t i = 0; i < p_field->GetNumberOfArrays(); i++) {
>>>>>>> master
    auto tag = p_field->GetArrayName(i);
    tags.emplace_back(tag);
  }

  return tags;
}

std::vector<std::string> rw::reader::VtkReader::readVtuFileCellTags() {
<<<<<<< HEAD

=======
>>>>>>> master
  // read point field data
  d_grid_p = d_reader_p->GetOutput();
  vtkCellData *c_field = d_grid_p->GetCellData();

  std::vector<std::string> tags;

<<<<<<< HEAD
  for (size_t i=0; i<c_field->GetNumberOfArrays(); i++) {
=======
  for (size_t i = 0; i < c_field->GetNumberOfArrays(); i++) {
>>>>>>> master
    auto tag = c_field->GetArrayName(i);
    tags.emplace_back(tag);
  }

  return tags;
}

<<<<<<< HEAD

=======
>>>>>>> master
void rw::reader::VtkReader::readMesh(size_t dim,
                                     std::vector<util::Point3> *nodes,
                                     size_t &element_type, size_t &num_elem,
                                     std::vector<size_t> *enc,
                                     std::vector<std::vector<size_t>> *nec,
                                     std::vector<double> *volumes, bool is_fd) {
  //
  // For nodes, we read following data
  // 1. nodes initial configuration
  // 2. nodes volume (if provided)
  // 3. nodes element connectivity (if provided)
  //
  // For elements, we read following data
  // 1. element node connectivity
  // 2. element type
  //
  d_grid_p = d_reader_p->GetOutput();
  vtkIdType num_nodes = d_grid_p->GetNumberOfPoints();
  vtkIdType num_elems = d_grid_p->GetNumberOfCells();

  // read point field data
  vtkPointData *p_field = d_grid_p->GetPointData();

  // check if file contains nodal volumes
  bool has_volume = true;
  if (p_field->HasArray("Node_Volume") == 0 and
      p_field->HasArray("Volume") == 0)
    has_volume = false;
  vtkDataArray *vol_array;
  if (has_volume) {
    if (p_field->HasArray("Node_Volume"))
      vol_array = p_field->GetArray("Node_Volume");
    else if (p_field->HasArray("Volume"))
      vol_array = p_field->GetArray("Volume");
  }

  // resize data
  nodes->resize(num_nodes);
  if (has_volume) volumes->resize(num_nodes);

  // Below is not efficient and need improvement
  // declare another array data to hold the ux,uy,uz
  auto u_a = vtkSmartPointer<vtkDoubleArray>::New();
  u_a->SetNumberOfComponents(3);
  u_a->Allocate(3, 1);  // allocate memory

  auto fix_a = vtkSmartPointer<vtkUnsignedIntArray>::New();
  fix_a->SetNumberOfComponents(1);
  fix_a->Allocate(1, 1);  // allocate memory

  auto vol_a = vtkSmartPointer<vtkDoubleArray>::New();
  vol_a->SetNumberOfComponents(1);
  vol_a->Allocate(1, 1);  // allocate memory

  auto con_a = vtkSmartPointer<vtkIntArray>::New();
  con_a->SetNumberOfComponents(11);
  con_a->Allocate(11, 1);  // allocate memory

  for (size_t i = 0; i < num_nodes; i++) {
    vtkIdType id = i;

    double x[3];
    d_grid_p->GetPoint(id, x);

    util::Point3 i_node = util::Point3(x[0], x[1], x[2]);
    (*nodes)[i] = i_node;

    // read node volume
    if (has_volume) {
      vol_array->GetTuples(i, i, vol_a);
      (*volumes)[i] = vol_a->GetValue(0);
    }
  }

  // if mesh is for finite difference simulation and if we have read the
  // volume data then we do not need to go further
  if (is_fd and has_volume) return;

  // read elements
  // to resize element-node connectivity, we need to know the number of
  // vertex in the given element type
  num_elem = num_elems;

  // resize node-element connectivity
  nec->resize(num_nodes);

  // get cell types array
  vtkUnsignedCharArray *elem_types = d_grid_p->GetCellTypesArray();

  // read cell field data
  vtkCellData *c_field = d_grid_p->GetCellData();

  int nds_per_el = 0;
  for (size_t i = 0; i < num_elems; i++) {
    vtkIdType id = i;
    vtkIdType num_ids;
    vtkIdType *nodes_ids;

    d_grid_p->GetCellPoints(id, num_ids, nodes_ids);

    // resize element-node connectivity data in the beginning of the loop
    if (i == 0) {
      elem_types->GetTuples(i, i, fix_a);
      element_type = fix_a->GetValue(0);

      nds_per_el = util::vtk_map_element_to_num_nodes[element_type];

      //      std::cout << "nodes per element = " << nds_per_el << "\n";
      //      std::cout << "Num elements = " << num_elems << "\n";

      // resize the element-node connectivity
      enc->resize(nds_per_el * num_elems);
    }

    for (size_t j = 0; j < num_ids; j++) {
      // read element-node connectivity data
      (*enc)[nds_per_el * i + j] = nodes_ids[j];

      // update node-element connectivity data
      (*nec)[nodes_ids[j]].push_back(i);
    }
  }
}

void rw::reader::VtkReader::readNodes(std::vector<util::Point3> *nodes) {
  d_grid_p = d_reader_p->GetOutput();
  vtkIdType num_nodes = d_grid_p->GetNumberOfPoints();

  // resize data
  nodes->clear();
  nodes->resize(num_nodes);
  for (size_t i = 0; i < num_nodes; i++) {
    vtkIdType id = i;

    double x[3];
    d_grid_p->GetPoint(id, x);

    util::Point3 i_node = util::Point3(x[0], x[1], x[2]);
    (*nodes)[i] = i_node;
  }
}

void rw::reader::VtkReader::readCells(size_t dim, size_t &element_type,
                                      size_t &num_elem,
                                      std::vector<size_t> *enc,
                                      std::vector<std::vector<size_t>> *nec) {
  d_grid_p = d_reader_p->GetOutput();
  vtkIdType num_nodes = d_grid_p->GetNumberOfPoints();
  vtkIdType num_elems = d_grid_p->GetNumberOfCells();

  // set number of elements
  num_elem = num_elems;

  // resize data (we resize enc data inside loop, see below)
  nec->clear();
  nec->resize(num_nodes);

  // get cell types array
  vtkUnsignedCharArray *elem_types = d_grid_p->GetCellTypesArray();

  // read cell field data
  vtkCellData *c_field = d_grid_p->GetCellData();

  // to hold integer
  auto val = vtkSmartPointer<vtkUnsignedIntArray>::New();
  val->SetNumberOfComponents(1);
  val->Allocate(1, 1);  // allocate memory

  int nds_per_el = 0;
  for (size_t i = 0; i < num_elems; i++) {
    vtkIdType id = i;
    vtkIdType num_ids;
    vtkIdType *nodes_ids;

    d_grid_p->GetCellPoints(id, num_ids, nodes_ids);

    // resize element-node connectivity data in the beginning of the loop
    if (i == 0) {
      elem_types->GetTuples(i, i, val);
      element_type = val->GetValue(0);

      nds_per_el = util::vtk_map_element_to_num_nodes[element_type];

      //      std::cout << "nodes per element = " << nds_per_el << "\n";
      //      std::cout << "Num elements = " << num_elems << "\n";

      // resize the element-node connectivity
      enc->clear();
      enc->resize(nds_per_el * num_elems);
    }

    for (size_t j = 0; j < num_ids; j++) {
      // read element-node connectivity data
      (*enc)[nds_per_el * i + j] = nodes_ids[j];

      // update node-element connectivity data
      (*nec)[nodes_ids[j]].push_back(i);
    }
  }
}

bool rw::reader::VtkReader::readPointData(const std::string &name,
                                          std::vector<uint8_t> *data) {
  // read point field data
  d_grid_p = d_reader_p->GetOutput();
  vtkPointData *p_field = d_grid_p->GetPointData();

  // handle for displacement, fixity and node element connectivity
  if (p_field->HasArray(name.c_str()) == 0) return false;

  vtkDataArray *array = p_field->GetArray(name.c_str());

  // Below is not efficient. Later this can be improved.
  // declare another array data to hold the ux,uy,uz
  auto data_a = vtkSmartPointer<vtkDoubleArray>::New();
  data_a->SetNumberOfComponents(1);
  data_a->Allocate(1, 1);  // allocate memory

  (*data).resize(array->GetNumberOfTuples());
  for (size_t i = 0; i < array->GetNumberOfTuples(); i++) {
    array->GetTuples(i, i, data_a);
    (*data)[i] = data_a->GetValue(0);
  }

  return true;
}

bool rw::reader::VtkReader::readPointData(const std::string &name,
                                          std::vector<size_t> *data) {
  // read point field data
  d_grid_p = d_reader_p->GetOutput();
  vtkPointData *p_field = d_grid_p->GetPointData();

  // handle for displacement, fixity and node element connectivity
  if (p_field->HasArray(name.c_str()) == 0) return false;

  vtkDataArray *array = p_field->GetArray(name.c_str());

  // Below is not efficient. Later this can be improved.
  // declare another array data to hold the ux,uy,uz
  auto data_a = vtkSmartPointer<vtkDoubleArray>::New();
  data_a->SetNumberOfComponents(1);
  data_a->Allocate(1, 1);  // allocate memory
<<<<<<< HEAD

  (*data).resize(array->GetNumberOfTuples());
  for (size_t i = 0; i < array->GetNumberOfTuples(); i++) {
    array->GetTuples(i, i, data_a);
    (*data)[i] = data_a->GetValue(0);
  }

  return true;
}

bool rw::reader::VtkReader::readPointData(const std::string &name,
                                          std::vector<int> *data) {
=======

  (*data).resize(array->GetNumberOfTuples());
  for (size_t i = 0; i < array->GetNumberOfTuples(); i++) {
    array->GetTuples(i, i, data_a);
    (*data)[i] = data_a->GetValue(0);
  }

  return true;
}

bool rw::reader::VtkReader::readPointData(const std::string &name,
                                          std::vector<int> *data) {
  // read point field data
  d_grid_p = d_reader_p->GetOutput();
  vtkPointData *p_field = d_grid_p->GetPointData();

  // handle for displacement, fixity and node element connectivity
  if (p_field->HasArray(name.c_str()) == 0) return false;

  vtkDataArray *array = p_field->GetArray(name.c_str());

  // Below is not efficient. Later this can be improved.
  // declare another array data to hold the ux,uy,uz
  auto data_a = vtkSmartPointer<vtkDoubleArray>::New();
  data_a->SetNumberOfComponents(1);
  data_a->Allocate(1, 1);  // allocate memory

  (*data).resize(array->GetNumberOfTuples());
  for (size_t i = 0; i < array->GetNumberOfTuples(); i++) {
    array->GetTuples(i, i, data_a);
    (*data)[i] = data_a->GetValue(0);
  }

  return true;
}

bool rw::reader::VtkReader::readPointData(const std::string &name,
                                          std::vector<float> *data) {
  // read point field data
  d_grid_p = d_reader_p->GetOutput();
  vtkPointData *p_field = d_grid_p->GetPointData();

  // handle for displacement, fixity and node element connectivity
  if (p_field->HasArray(name.c_str()) == 0) return false;

  vtkDataArray *array = p_field->GetArray(name.c_str());

  // Below is not efficient. Later this can be improved.
  // declare another array data to hold the ux,uy,uz
  auto data_a = vtkSmartPointer<vtkDoubleArray>::New();
  data_a->SetNumberOfComponents(1);
  data_a->Allocate(1, 1);  // allocate memory

  (*data).resize(array->GetNumberOfTuples());
  for (size_t i = 0; i < array->GetNumberOfTuples(); i++) {
    array->GetTuples(i, i, data_a);
    (*data)[i] = data_a->GetValue(0);
  }

  return true;
}

bool rw::reader::VtkReader::readPointData(const std::string &name,
                                          std::vector<double> *data) {
>>>>>>> master
  // read point field data
  d_grid_p = d_reader_p->GetOutput();
  vtkPointData *p_field = d_grid_p->GetPointData();

  // handle for displacement, fixity and node element connectivity
  if (p_field->HasArray(name.c_str()) == 0) return false;

  vtkDataArray *array = p_field->GetArray(name.c_str());

  // Below is not efficient. Later this can be improved.
  // declare another array data to hold the ux,uy,uz
  auto data_a = vtkSmartPointer<vtkDoubleArray>::New();
  data_a->SetNumberOfComponents(1);
  data_a->Allocate(1, 1);  // allocate memory

  (*data).resize(array->GetNumberOfTuples());
  for (size_t i = 0; i < array->GetNumberOfTuples(); i++) {
    array->GetTuples(i, i, data_a);
    (*data)[i] = data_a->GetValue(0);
  }

  return true;
}

bool rw::reader::VtkReader::readPointData(const std::string &name,
                                          std::vector<util::Point3> *data) {
  // read point field data
  d_grid_p = d_reader_p->GetOutput();
  vtkPointData *p_field = d_grid_p->GetPointData();

  // handle for displacement, fixity and node element connectivity
  if (p_field->HasArray(name.c_str()) == 0) return false;

  vtkDataArray *array = p_field->GetArray(name.c_str());

  // Below is not efficient. Later this can be improved.
  // declare another array data to hold the ux,uy,uz
  auto data_a = vtkSmartPointer<vtkDoubleArray>::New();
  data_a->SetNumberOfComponents(3);
  data_a->Allocate(3, 1);  // allocate memory

  (*data).resize(array->GetNumberOfTuples());
  for (size_t i = 0; i < array->GetNumberOfTuples(); i++) {
    array->GetTuples(i, i, data_a);
    (*data)[i] = util::Point3(data_a->GetValue(0), data_a->GetValue(1),
                              data_a->GetValue(2));
  }

  return true;
}

bool rw::reader::VtkReader::readPointData(const std::string &name,
                                          std::vector<util::SymMatrix3> *data) {
  // read point field data
  d_grid_p = d_reader_p->GetOutput();
  vtkPointData *p_field = d_grid_p->GetPointData();

  // handle for displacement, fixity and node element connectivity
  if (p_field->HasArray(name.c_str()) == 0) return false;

  vtkDataArray *array = p_field->GetArray(name.c_str());

  // Below is not efficient. Later this can be improved.
  // declare another array data to hold the ux,uy,uz
  auto data_a = vtkSmartPointer<vtkDoubleArray>::New();
  data_a->SetNumberOfComponents(6);
  data_a->Allocate(6, 1);  // allocate memory

  (*data).resize(array->GetNumberOfTuples());
  for (size_t i = 0; i < array->GetNumberOfTuples(); i++) {
    array->GetTuples(i, i, data_a);
    (*data)[i] = util::SymMatrix3(data_a->GetValue(0), data_a->GetValue(1),
                                  data_a->GetValue(2), data_a->GetValue(3),
                                  data_a->GetValue(4), data_a->GetValue(5));
  }

  return true;
}

bool rw::reader::VtkReader::readPointData(const std::string &name,
                                          std::vector<util::Matrix33> *data) {
  // read point field data
  d_grid_p = d_reader_p->GetOutput();
  vtkPointData *p_field = d_grid_p->GetPointData();

  // handle for displacement, fixity and node element connectivity
  if (p_field->HasArray(name.c_str()) == 0) return false;

  vtkDataArray *array = p_field->GetArray(name.c_str());

  // Below is not efficient. Later this can be improved.
  // declare another array data to hold the ux,uy,uz
  auto data_a = vtkSmartPointer<vtkDoubleArray>::New();
  data_a->SetNumberOfComponents(6);
  data_a->Allocate(6, 1);  // allocate memory

  (*data).resize(array->GetNumberOfTuples());
  for (size_t i = 0; i < array->GetNumberOfTuples(); i++) {
    array->GetTuples(i, i, data_a);

    util::Matrix33 m;
    m(0, 0) = data_a->GetValue(0);
    m(1, 1) = data_a->GetValue(1);
    m(2, 2) = data_a->GetValue(2);
    m(0, 1) = data_a->GetValue(3);
    m(0, 2) = data_a->GetValue(4);
    m(1, 2) = data_a->GetValue(5);

    // symmetrize
    m(1, 0) = m(0, 1);
    m(2, 0) = m(0, 2);
    m(2, 1) = m(1, 2);

    // add to the data
    (*data)[i] = m;
  }

  return true;
}

bool rw::reader::VtkReader::readCellData(const std::string &name,
                                         std::vector<float> *data) {
  // read point field data
  d_grid_p = d_reader_p->GetOutput();
  vtkCellData *c_field = d_grid_p->GetCellData();

  // handle for displacement, fixity and node element connectivity
  if (c_field->HasArray(name.c_str()) == 0) return false;

  vtkDataArray *array = c_field->GetArray(name.c_str());

  // Below is not efficient. Later this can be improved.
  // declare another array data to hold the ux,uy,uz
  auto data_a = vtkSmartPointer<vtkDoubleArray>::New();
  data_a->SetNumberOfComponents(1);
  data_a->Allocate(1, 1);  // allocate memory

  (*data).resize(array->GetNumberOfTuples());
  for (size_t i = 0; i < array->GetNumberOfTuples(); i++) {
    array->GetTuples(i, i, data_a);
    (*data)[i] = data_a->GetValue(0);
  }

  return true;
}

bool rw::reader::VtkReader::readCellData(const std::string &name,
                                         std::vector<double> *data) {
  // read point field data
  d_grid_p = d_reader_p->GetOutput();
  vtkCellData *c_field = d_grid_p->GetCellData();

  // handle for displacement, fixity and node element connectivity
  if (c_field->HasArray(name.c_str()) == 0) return false;

  vtkDataArray *array = c_field->GetArray(name.c_str());

  // Below is not efficient. Later this can be improved.
  // declare another array data to hold the ux,uy,uz
  auto data_a = vtkSmartPointer<vtkDoubleArray>::New();
  data_a->SetNumberOfComponents(1);
  data_a->Allocate(1, 1);  // allocate memory

  (*data).resize(array->GetNumberOfTuples());
  for (size_t i = 0; i < array->GetNumberOfTuples(); i++) {
    array->GetTuples(i, i, data_a);
    (*data)[i] = data_a->GetValue(0);
  }

  return true;
}

bool rw::reader::VtkReader::readCellData(const std::string &name,
<<<<<<< HEAD
                                         std::vector<double> *data) {
  // read point field data
  d_grid_p = d_reader_p->GetOutput();
  vtkCellData *c_field = d_grid_p->GetCellData();

  // handle for displacement, fixity and node element connectivity
  if (c_field->HasArray(name.c_str()) == 0) return false;

  vtkDataArray *array = c_field->GetArray(name.c_str());

  // Below is not efficient. Later this can be improved.
  // declare another array data to hold the ux,uy,uz
  auto data_a = vtkSmartPointer<vtkDoubleArray>::New();
  data_a->SetNumberOfComponents(1);
  data_a->Allocate(1, 1);  // allocate memory

  (*data).resize(array->GetNumberOfTuples());
  for (size_t i = 0; i < array->GetNumberOfTuples(); i++) {
    array->GetTuples(i, i, data_a);
    (*data)[i] = data_a->GetValue(0);
  }

  return true;
}

bool rw::reader::VtkReader::readCellData(const std::string &name,
=======
>>>>>>> master
                                         std::vector<util::Point3> *data) {
  // read point field data
  d_grid_p = d_reader_p->GetOutput();
  vtkCellData *c_field = d_grid_p->GetCellData();

  // handle for displacement, fixity and node element connectivity
  if (c_field->HasArray(name.c_str()) == 0) return false;

  vtkDataArray *array = c_field->GetArray(name.c_str());

  // Below is not efficient. Later this can be improved.
  // declare another array data to hold the ux,uy,uz
  auto data_a = vtkSmartPointer<vtkDoubleArray>::New();
  data_a->SetNumberOfComponents(3);
  data_a->Allocate(3, 1);  // allocate memory

  (*data).resize(array->GetNumberOfTuples());
  for (size_t i = 0; i < array->GetNumberOfTuples(); i++) {
    array->GetTuples(i, i, data_a);
    (*data)[i] = util::Point3(data_a->GetValue(0), data_a->GetValue(1),
                              data_a->GetValue(2));
  }

  return true;
}

bool rw::reader::VtkReader::readCellData(const std::string &name,
                                         std::vector<util::SymMatrix3> *data) {
  // read point field data
  d_grid_p = d_reader_p->GetOutput();
  vtkCellData *c_field = d_grid_p->GetCellData();

  // handle for displacement, fixity and node element connectivity
  if (c_field->HasArray(name.c_str()) == 0) return false;

  vtkDataArray *array = c_field->GetArray(name.c_str());

  // Below is not efficient. Later this can be improved.
  // declare another array data to hold the ux,uy,uz
  auto data_a = vtkSmartPointer<vtkDoubleArray>::New();
  data_a->SetNumberOfComponents(6);
  data_a->Allocate(6, 1);  // allocate memory

  (*data).resize(array->GetNumberOfTuples());
  for (size_t i = 0; i < array->GetNumberOfTuples(); i++) {
    array->GetTuples(i, i, data_a);
    (*data)[i] = util::SymMatrix3({data_a->GetValue(0), data_a->GetValue(1),
                                   data_a->GetValue(2), data_a->GetValue(3),
                                   data_a->GetValue(4), data_a->GetValue(5)});
  }

  return true;
}

bool rw::reader::VtkReader::readCellData(const std::string &name,
                                         std::vector<util::Matrix33> *data) {
  // read point field data
  d_grid_p = d_reader_p->GetOutput();
  vtkCellData *c_field = d_grid_p->GetCellData();

  // handle for displacement, fixity and node element connectivity
  if (c_field->HasArray(name.c_str()) == 0) return false;

  vtkDataArray *array = c_field->GetArray(name.c_str());

  // Below is not efficient. Later this can be improved.
  // declare another array data to hold the ux,uy,uz
  auto data_a = vtkSmartPointer<vtkDoubleArray>::New();
  data_a->SetNumberOfComponents(6);
  data_a->Allocate(6, 1);  // allocate memory

  (*data).resize(array->GetNumberOfTuples());
  for (size_t i = 0; i < array->GetNumberOfTuples(); i++) {
    array->GetTuples(i, i, data_a);

    util::Matrix33 m;
    m(0, 0) = data_a->GetValue(0);
    m(1, 1) = data_a->GetValue(1);
    m(2, 2) = data_a->GetValue(2);
    m(0, 1) = data_a->GetValue(3);
    m(0, 2) = data_a->GetValue(4);
    m(1, 2) = data_a->GetValue(5);

    // symmetrize
    m(1, 0) = m(0, 1);
    m(2, 0) = m(0, 2);
    m(2, 1) = m(1, 2);

    // add to the data
    (*data)[i] = m;
  }

  return true;
}

void rw::reader::VtkReader::close() {
  // delete d_reader_p;
  // delete d_grid_p;
}
