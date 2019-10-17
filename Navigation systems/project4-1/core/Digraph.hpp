// Digraph.hpp
//
// ICS 46 Winter 2019
// Project #4: Rock and Roll Stops the Traffic
//
// This header file declares a class template called Digraph, which is
// intended to implement a generic directed graph. The implementation
// uses the adjacency lists technique, so each vertex stores a linked
// list of its outgoing edges.
//
// Along with the Digraph class template is a class DigraphException
// and a couple of utility structs that aren't generally useful outside
// of this header file.
//
// In general, directed graphs are all the same, except in the sense
// that they store different kinds of information about each vertex and
// about each edge; these two types are the type parameters to the
// Digraph class template.

#ifndef DIGRAPH_HPP
#define DIGRAPH_HPP

#include <exception>
#include <functional>
#include <list>
#include <map>
#include <utility>
#include <vector>
#include <iterator>
#include <string>
#include <iostream>
#include <queue>



// DigraphExceptions are thrown from some of the member functions in the
// Digraph class template, so that exception is declared here, so it
// will be available to any code that includes this header file.

class DigraphException : public std::runtime_error
{
public:
    DigraphException(const std::string& reason);
};


inline DigraphException::DigraphException(const std::string& reason)
    : std::runtime_error{reason}
{
}



// A DigraphEdge lists a "from vertex" (the number of the vertex from which
// the edge points), a "to vertex" (the number of the vertex to which the
// edge points), and an EdgeInfo object.  Because different kinds of Digraphs
// store different kinds of edge information, DigraphEdge is a struct template.

template <typename EdgeInfo>
struct DigraphEdge
{
    int fromVertex;
    int toVertex;
    EdgeInfo einfo;
};



// A DigraphVertex includes two things: a VertexInfo object and a list of
// its outgoing edges.  Because different kinds of Digraphs store different
// kinds of vertex and edge information, DigraphVertex is a struct template.

template <typename VertexInfo, typename EdgeInfo>
struct DigraphVertex
{
    VertexInfo vinfo;
    std::list<DigraphEdge<EdgeInfo>> edges;
};



// Digraph is a class template that represents a directed graph implemented
// using adjacency lists.  It takes two type parameters:
//
// * VertexInfo, which specifies the kind of object stored for each vertex
// * EdgeInfo, which specifies the kind of object stored for each edge
//
// You'll need to implement the member functions declared here; each has a
// comment detailing how it is intended to work.
//
// Each vertex in a Digraph is identified uniquely by a "vertex number".
// Vertex numbers are not necessarily sequential and they are not necessarily
// zero- or one-based.

template <typename VertexInfo, typename EdgeInfo>
class Digraph
{
public:
    // The default constructor initializes a new, empty Digraph so that
    // contains no vertices and no edges.
    Digraph();

    // The copy constructor initializes a new Digraph to be a deep copy
    // of another one (i.e., any change to the copy will not affect the
    // original).
    Digraph(const Digraph& d);

    // The move constructor initializes a new Digraph from an expiring one.
    Digraph(Digraph&& d) noexcept;

    // The destructor deallocates any memory associated with the Digraph.
    ~Digraph() noexcept;

    // The assignment operator assigns the contents of the given Digraph
    // into "this" Digraph, with "this" Digraph becoming a separate, deep
    // copy of the contents of the given one (i.e., any change made to
    // "this" Digraph afterward will not affect the other).
    Digraph& operator=(const Digraph& d);

    // The move assignment operator assigns the contents of an expiring
    // Digraph into "this" Digraph.
    Digraph& operator=(Digraph&& d) noexcept;

    // vertices() returns a std::vector containing the vertex numbers of
    // every vertex in this Digraph.
    std::vector<int> vertices() const;

    // edges() returns a std::vector of std::pairs, in which each pair
    // contains the "from" and "to" vertex numbers of an edge in this
    // Digraph.  All edges are included in the std::vector.
    std::vector<std::pair<int, int>> edges() const;

    // This overload of edges() returns a std::vector of std::pairs, in
    // which each pair contains the "from" and "to" vertex numbers of an
    // edge in this Digraph.  Only edges outgoing from the given vertex
    // number are included in the std::vector.  If the given vertex does
    // not exist, a DigraphException is thrown instead.
    std::vector<std::pair<int, int>> edges(int vertex) const;

    // vertexInfo() returns the VertexInfo object belonging to the vertex
    // with the given vertex number.  If that vertex does not exist, a
    // DigraphException is thrown instead.
    VertexInfo vertexInfo(int vertex) const;

    // edgeInfo() returns the EdgeInfo object belonging to the edge
    // with the given "from" and "to" vertex numbers.  If either of those
    // vertices does not exist *or* if the edge does not exist, a
    // DigraphException is thrown instead.
    EdgeInfo edgeInfo(int fromVertex, int toVertex) const;

    // addVertex() adds a vertex to the Digraph with the given vertex
    // number and VertexInfo object.  If there is already a vertex in
    // the graph with the given vertex number, a DigraphException is
    // thrown instead.
    void addVertex(int vertex, const VertexInfo& vinfo);

    // addEdge() adds an edge to the Digraph pointing from the given
    // "from" vertex number to the given "to" vertex number, and
    // associates with the given EdgeInfo object with it.  If one
    // of the vertices does not exist *or* if the same edge is already
    // present in the graph, a DigraphException is thrown instead.
    void addEdge(int fromVertex, int toVertex, const EdgeInfo& einfo);

    // removeVertex() removes the vertex (and all of its incoming
    // and outgoing edges) with the given vertex number from the
    // Digraph.  If the vertex does not exist already, a DigraphException
    // is thrown instead.
    void removeVertex(int vertex);

    // removeEdge() removes the edge pointing from the given "from"
    // vertex number to the given "to" vertex number from the Digraph.
    // If either of these vertices does not exist *or* if the edge
    // is not already present in the graph, a DigraphException is
    // thrown instead.
    void removeEdge(int fromVertex, int toVertex);

    // vertexCount() returns the number of vertices in the graph.
    int vertexCount() const noexcept;

    // edgeCount() returns the total number of edges in the graph,
    // counting edges outgoing from all vertices.
    int edgeCount() const noexcept;

    // This overload of edgeCount() returns the number of edges in
    // the graph that are outgoing from the given vertex number.
    // If the given vertex does not exist, a DigraphException is
    // thrown instead.
    int edgeCount(int vertex) const;

    // isStronglyConnected() returns true if the Digraph is strongly
    // connected (i.e., every vertex is reachable from every other),
    // false otherwise.
    bool isStronglyConnected() const;

    // findShortestPaths() takes a start vertex number and a function
    // that takes an EdgeInfo object and determines an edge weight.
    // It uses Dijkstra's Shortest Path Algorithm to determine the
    // shortest paths from the start vertex to every other vertex
    // in the graph.  The result is returned as a std::map<int, int>
    // where the keys are vertex numbers and the value associated
    // with each key k is the precedessor of that vertex chosen by
    // the algorithm.  For any vertex without a predecessor (e.g.,
    // a vertex that was never reached, or the start vertex itself),
    // the value is simply a copy of the key.
    std::map<int, int> findShortestPaths(
        int startVertex,
        std::function<double(const EdgeInfo&)> edgeWeightFunc) const;


private:
    // Add whatever member variables you think you need here.  One
    // possibility is a std::map where the keys are vertex numbers
    // and the values are DigraphVertex<VertexInfo, EdgeInfo> objects.
    std::map<int,DigraphVertex<VertexInfo,EdgeInfo>> data;
    // You can also feel free to add any additional member functions
    // you'd like (public or private), so long as you don't remove or
    // change the signatures of the ones that already exist.
};



// You'll need to implement the member functions below.  There's enough
// code in place to make them compile, but they'll all need to do the
// correct thing instead.

template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::Digraph()
{
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::Digraph(const Digraph& d)
{
    data = d.data;
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::Digraph(Digraph&& d) noexcept
{
    std::swap(data,d.data);
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::~Digraph() noexcept
{
    for(typename std::map<int,DigraphVertex<VertexInfo,EdgeInfo>>::iterator i = data.begin(); i != data.end(); i++){
        i->second.edges.clear();
    }
    data.clear();
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>& Digraph<VertexInfo, EdgeInfo>::operator=(const Digraph& d)
{
    data = d.data;
    return *this;
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>& Digraph<VertexInfo, EdgeInfo>::operator=(Digraph&& d) noexcept
{
    std::swap(data,d.data);
    return *this;
}


template <typename VertexInfo, typename EdgeInfo>
std::vector<int> Digraph<VertexInfo, EdgeInfo>::vertices() const
{
    std::vector<int> verticeList;
    for(typename std::map<int,DigraphVertex<VertexInfo,EdgeInfo>>::const_iterator i = data.begin(); i != data.end(); i++){
        verticeList.push_back(i->first);
    }
    return verticeList;
}


template <typename VertexInfo, typename EdgeInfo>
std::vector<std::pair<int, int>> Digraph<VertexInfo, EdgeInfo>::edges() const
{
    std::vector<std::pair<int, int>> edgeList;
    for(typename std::map<int,DigraphVertex<VertexInfo,EdgeInfo>>::const_iterator i = data.begin(); i != data.end(); i++){
        for(typename std::list<DigraphEdge<EdgeInfo>>::const_iterator j = i->second.edges.begin(); j != i->second.edges.end(); j++){
            std::pair<int,int> edge;
            edge.first = j->fromVertex;
            edge.second = j->toVertex;
            edgeList.push_back(edge);
        }
    }
    return edgeList;
}


template <typename VertexInfo, typename EdgeInfo>
std::vector<std::pair<int, int>> Digraph<VertexInfo, EdgeInfo>::edges(int vertex) const
{   
    std::vector<int> v = vertices();
    if(std::count(v.begin(), v.end(), vertex)){
        std::vector<std::pair<int, int>> edgeList;
        std::list<DigraphEdge<EdgeInfo>> findEdges = data.find(vertex)->second.edges;
        for(typename std::list<DigraphEdge<EdgeInfo>>::const_iterator i = findEdges.begin(); i != findEdges.end(); i++){
            std::pair<int,int> edge;
            edge.first = i->fromVertex;
            edge.second = i->toVertex;
            edgeList.push_back(edge);
        }
        return edgeList;
    }else{
        throw DigraphException("The given vertex does not exist.");
    }
}


template <typename VertexInfo, typename EdgeInfo>
VertexInfo Digraph<VertexInfo, EdgeInfo>::vertexInfo(int vertex) const
{
    std::vector<int> v = vertices();
    if(std::count(v.begin(), v.end(), vertex)){
        VertexInfo findVertex;
        findVertex = data.find(vertex)->second.vinfo;
        return findVertex;
    }else{
        throw DigraphException("The given vertex does not exist.");
    }
}


template <typename VertexInfo, typename EdgeInfo>
EdgeInfo Digraph<VertexInfo, EdgeInfo>::edgeInfo(int fromVertex, int toVertex) const
{
    std::vector<int> v = vertices();
    if(std::count(v.begin(), v.end(), fromVertex) == 0){
        throw DigraphException("The given fromVertex does not exist.");
    }
    if(std::count(v.begin(), v.end(), toVertex) == 0){
        throw DigraphException("The given toVertex does not exist.");
    }
    std::pair<int,int> edge;
    edge.first = fromVertex;
    edge.second = toVertex;
    std::vector<std::pair<int, int>> e = edges(fromVertex);
    if(std::count(e.begin(), e.end(), edge)){
        std::list<DigraphEdge<EdgeInfo>> findEdges = data.find(fromVertex)->second.edges;
        for(typename std::list<DigraphEdge<EdgeInfo>>::const_iterator i = findEdges.begin(); i != findEdges.end(); i++){
            if(i->toVertex == toVertex){
                return i->einfo;
            }
        }
    }else{
        throw DigraphException("The given edge does not exist.");
    }
}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::addVertex(int vertex, const VertexInfo& vinfo)
{
    std::vector<int> v = vertices();
    if(std::count(v.begin(), v.end(), vertex)){
        throw DigraphException("The given vertex already exist.");
    }else{
        DigraphVertex<VertexInfo,EdgeInfo> newVertex;
        newVertex.vinfo = vinfo;
        data.insert({vertex,newVertex});
    }
}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::addEdge(int fromVertex, int toVertex, const EdgeInfo& einfo)
{
    std::vector<int> v = vertices();
    if(std::count(v.begin(), v.end(), fromVertex) == 0){
        throw DigraphException("The given fromVertex does not exist.");
    }
    if(std::count(v.begin(), v.end(), toVertex) == 0){
        throw DigraphException("The given toVertex does not exist.");
    }
    std::vector<std::pair<int, int>> e = edges(fromVertex);
    std::pair<int,int> edge;
    edge.first = fromVertex;
    edge.second = toVertex;
    if(std::count(e.begin(), e.end(), edge)){
        throw DigraphException("The given edge already exist.");
    }else{
        DigraphEdge<EdgeInfo> newEdge;
        newEdge.fromVertex = fromVertex;
        newEdge.toVertex = toVertex;
        newEdge.einfo = einfo;
        data.at(fromVertex).edges.push_back(newEdge);
    }

}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::removeVertex(int vertex)
{
    std::vector<int> v = vertices();
    if(std::count(v.begin(), v.end(), vertex)){
            for(typename std::map<int,DigraphVertex<VertexInfo,EdgeInfo>>::const_iterator i = data.begin(); i != data.end(); i++){
                for(typename std::list<DigraphEdge<EdgeInfo>>::const_iterator j = i->second.edges.begin(); j != i->second.edges.end(); j++){
                    if(j->fromVertex == vertex||j->toVertex == vertex){
                        removeEdge(j->fromVertex, j->toVertex);
                    }
            }
        }
        data.at(vertex).edges.clear();
        data.erase(vertex);
    }else{
        throw DigraphException("The given vertex does not exist.");
    }
}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::removeEdge(int fromVertex, int toVertex)
{
    std::vector<int> v = vertices();
    if(std::count(v.begin(), v.end(), fromVertex) == 0){
        throw DigraphException("The given fromVertex does not exist.");
    }
    if(std::count(v.begin(), v.end(), toVertex) == 0){
        throw DigraphException("The given toVertex does not exist.");
    }
    std::pair<int,int> edge;
    edge.first = fromVertex;
    edge.second = toVertex;
    std::vector<std::pair<int, int>> e = edges(fromVertex);
    if(std::count(e.begin(), e.end(), edge)){
        for(typename std::list<DigraphEdge<EdgeInfo>>::const_iterator i = data.at(fromVertex).edges.begin(); i != data.at(fromVertex).edges.end(); i++){
            if(i->toVertex == toVertex){
                data.at(fromVertex).edges.erase(i);
            }
        }
    }else{
        throw DigraphException("The given edge does not exist.");
    }
}


template <typename VertexInfo, typename EdgeInfo>
int Digraph<VertexInfo, EdgeInfo>::vertexCount() const noexcept
{
    std::vector<int> v = vertices();
    return v.size();   
}


template <typename VertexInfo, typename EdgeInfo>
int Digraph<VertexInfo, EdgeInfo>::edgeCount() const noexcept
{
    std::vector<std::pair<int, int>> e = edges();
    return e.size();
}


template <typename VertexInfo, typename EdgeInfo>
int Digraph<VertexInfo, EdgeInfo>::edgeCount(int vertex) const
{
    std::vector<std::pair<int, int>> e = edges(vertex);
    return e.size();
}


template <typename VertexInfo, typename EdgeInfo>
bool Digraph<VertexInfo, EdgeInfo>::isStronglyConnected() const
{
    std::vector<int> v = vertices();
    for(int &i : v){
        std::map<int,int> findpath = findShortestPaths(i,[](double edgeInfo){return edgeInfo;});
        if(findpath.size() != v.size()){
            return false;
        }
    }
    return true;
}

template <typename VertexInfo, typename EdgeInfo>
std::map<int, int> Digraph<VertexInfo, EdgeInfo>::findShortestPaths(
    int startVertex,
    std::function<double(const EdgeInfo&)> edgeWeightFunc) const
{
    std::map<int, bool> visited;
    std::map<int, int> predecessor;
    std::map<int, double>shortestpath;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    std::vector<int> v = vertices();
    for(int &i : v){
        visited.insert({i,false});
        predecessor.insert({i,-1});
        shortestpath.insert({i,99999999999999999});
    }
    pq.push(std::make_pair(0,startVertex));
    shortestpath.at(startVertex) = 0;
    predecessor.at(startVertex) = startVertex;
    while(pq.empty() == false){
        int current = pq.top().second;
        pq.pop();
        if(visited.at(current) == false){
            visited.at(current) = true;
            std::vector<std::pair<int, int>> e = edges(current);
            for(std::pair<int, int> &p : e){
                int w = p.second;
                EdgeInfo einfo = edgeInfo(current, w);
                if(shortestpath.at(w) > shortestpath.at(current) + edgeWeightFunc(einfo)){
                    shortestpath.at(w) = shortestpath.at(current) + edgeWeightFunc(einfo);
                    predecessor.at(w) = current;
                    pq.push(std::make_pair(shortestpath.at(w),w));
                }
            }
        }
    }
    return predecessor;
}



#endif // DIGRAPH_HPP

