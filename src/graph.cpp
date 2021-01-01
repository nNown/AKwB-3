#include <graph.h>

const std::string& Vertex::Header() { return this->_header; }
void Vertex::Header(const std::string& newHeader) { this->_header = newHeader; }

const std::string& Vertex::Tag() { return this->_tag; }
void Vertex::Tag(const std::string& newTag) { this->_tag = newTag; }

const std::size_t& Vertex::Position() { return this->_position; }
void Vertex::Position(const std::size_t& newPosition) { this->_position = newPosition; }

std::vector<int>& Vertex::Edges() { return this->_edges; }
void Vertex::Edges(const std::vector<int>& newEdges) { this->_edges = newEdges; }

Vertex::Vertex() 
    : _header(""), _position(0) {}
Vertex::Vertex(const std::string& header, const std::string& tag, const std::size_t& position) 
    : _header(header), _tag(tag), _position(position) {}
Vertex::~Vertex() {}

// std::map<int, std::vector<int>>& Graph::Vertices() { return this->_vertices; }
std::vector<Vertex> Graph::Vertices() { return this->_vertices; }

void Graph::AddEdge(const int& i, const int& j) {
    this->_vertices[i].Edges().push_back(j);
}

bool Graph::HasEdge(const int& i, const int& j) { 
    for(size_t k = 0; k < this->_vertices[i].Edges().size(); k++) {
        if(this->_vertices[i].Edges()[k] == j) return true;
    }
    return false;
}

// void Graph::AddVertex(const int& i) {
//     this->_vertices.insert({i, std::vector<int>()});
// }

void Graph::AddVertex(const Vertex& vertex) {
    this->_vertices.push_back(vertex);
}

// bool Graph::HasVertex(const int& i) {
//     return this->_vertices.find(i) != this->_vertices.end() ? true : false;
// }

Graph::Graph() 
    : _vertices(std::vector<Vertex>()) {}

Graph::~Graph() {}