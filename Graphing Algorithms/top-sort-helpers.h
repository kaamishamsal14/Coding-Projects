#pragma once

#include <unordered_map>

#include "weighted-graph.hpp"
#include "graph-types.h"

template <typename T>
void computeIndegrees(const WeightedGraph<T>& graph, std::unordered_map<value_type<T>, int>& indegrees) {
    // TODO store the indegree for each vertex in the graph in the indegrees map
    for(auto i = graph.begin(); i != graph.end(); i++){
        indegrees[i->first] = 0;
    }
    for(auto i = graph.begin(); i != graph.end(); i++){
        for(auto k = graph.begin(i->first); k != graph.end(i->first); k++){
            indegrees[k->first] += 1;
        }
    }
}
