#ifndef GRAPH_ALGS
#define GRAPH_ALGS

#include <map>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <deque>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <utility>
#include <algorithm>
#include "weighted_graph.hpp"
#include "easy_weighted_graph_algorithms.cpp"


//Returns true if the graph is connected, false otherwise.
template < typename vertex >
    bool is_connected(const weighted_graph < vertex > & g) {
    //check empty graph
        if (g.num_vertices() == 0) {
            return true;
        } //check graph with vertices and edges
    else if (!g.num_vertices() == 0 && !g.num_edges() == 0) {
            std::vector < vertex > vertices1 = depth_first(g, *(g.begin()));


            if (vertices1.size() == g.num_vertices()) {
                return true;
            }

        }

        return false;

    }

//Returns a vector of weighted graphs, where each weighted graph is a connected
//component of the input graph.
template < typename vertex >
    std::vector < weighted_graph < vertex >> connected_components(const weighted_graph < vertex > & g) {

        std::vector < weighted_graph < vertex >> graphList;
        std::vector < vertex > vertices_all(g.begin(), g.end());//all the vertives in the graph
        int y = 0;//inatialise the boolean counter
        bool visited[g.num_vertices()];
        
        //mark all the vertices as not visited
        for (unsigned i = 0; i < g.num_vertices(); i++) {
            visited[i] = false;
        }



        for (auto itr = g.begin(); itr != g.end(); ++itr) {
            weighted_graph < vertex > subGraph;
            auto traversalVertex = depth_first(g, * itr);

            //if the vertex we are pointing at is not visited then add it to the subgraph, add edge and mark it as visited
            if (visited[ * itr] == false) {
                for (vertex v: traversalVertex) {
                    subGraph.add_vertex(v);
                    visited[v] = true;
                    y++;
                }
                for (auto z: vertices_all) {
                    for (auto u: vertices_all) {
                        if (g.are_adjacent(u, z)) {
                            subGraph.add_edge(u, z, g.get_edge_weight(u, z));
                        }
                    }
                }
                graphList.push_back(subGraph);


            }
        }


        return graphList;

    }



//Returns a map of the vertices of the weighted graph g and their distances from
//the given starting vertex v.
template < typename vertex >
    std::map < vertex, int > dijkstras(const weighted_graph < vertex > & g,
        const vertex & v) {

        std::map < vertex, int > distance;
        std::set < vertex > unprocessed; //vertices we need to compute
        std::set < int > ::iterator itr;

        //test for empty graph
        if (g.num_vertices() == 0) {
            return distance;
        } else {
            for (auto j: g) {
                //set distance of all the vertices to maximum number 
                distance[j] = std::numeric_limits < int > ::max();
            }
            distance[v] = 0;//start vertex
            for (auto i: g) {
                if (i != v) {
                    unprocessed.insert(i);//inserting everything but the start in the unprocessed vector 
                }
            }
           //getting edge weight of all vertices 
            for (itr = unprocessed.begin(); itr != unprocessed.end(); ++itr) {
                if (g.are_adjacent( * itr, v)) {
                    distance[ * itr] = g.get_edge_weight(v, * itr);
                }
            }
            while (!unprocessed.empty()) {
                int min_distance = std::numeric_limits < int > ::max();
                vertex u;
                for (itr = unprocessed.begin(); itr != unprocessed.end(); ++itr) {
                    if (distance[ * itr] < min_distance) {
                        min_distance = distance[ * itr];//changes distance form max tp minimum distance between them 
                        u = * itr;  // change what *itr is pointing at 
                    }
                }
                unprocessed.erase(u);
                for (itr = unprocessed.begin(); itr != unprocessed.end(); ++itr) {
                    if (g.are_adjacent(u, * itr)) {
                        int weight = g.get_edge_weight(u, * itr);
                        if (distance[u] + weight < distance[ * itr]) {
                            distance[ * itr] = distance[u] + weight;//adjusting the distance for rest of the vertices 
                        }
                    }
                }
            }
        }
        return distance;
    }

//Returns a vector containing all the articulation points of the
//input weighted graph g.
template < typename vertex >
    std::vector < vertex > articulation_points(const weighted_graph < vertex > & g) {

        std::vector < vertex > articulation_points;
        for (auto i: g) {
            weighted_graph < vertex > temp_graph = g;// make a new temp graph
            temp_graph.remove_vertex(i);
            
            //check if graph is still connected , if not the vertex is an articualtion point
            if (!is_connected(temp_graph)) {
                articulation_points.push_back(i);
            }
        }



        return articulation_points;
    }

#endif