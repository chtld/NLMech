////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2019 Prashant K. Jha
//  Copyright (c) 2019 Patrick Diehl
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////
#ifndef MODEL_UTIL_H
#define MODEL_UTIL_H

#include <iostream>
#include <string>
#include <cstddef>
#include "inp/input.h"
#include "inp/decks/modelDeck.h"
#include "inp/decks/outputDeck.h"
#include "inp/decks/policyDeck.h"
#include "rw/writer.h"
#include "data/DataManager.h"
#include "fe/mesh.h"
#include "util/point.h"
#include "inp/policy.h"
#include "geometry/neighbor.h"


namespace inp {
struct ModelDeck;
struct OutputDeck;
struct MeshDeck;
struct PolicyDeck;
class Policy;
} // namespace inp

namespace fe {
class Mesh;
// class Quadrature;
}// namespace fe

namespace model {

class Output{

public:  

Output(inp::Input *d_input_p,data::DataManager *d_dataManager_p, size_t d_n, double d_time);

};

}

#endif