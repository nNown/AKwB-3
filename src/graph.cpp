#include <graph.h>

const std::string& Vertex::Header() { return this->_header; }
void Vertex::Header(const std::string& newHeader) { this->_header = newHeader; }

const std::string& Vertex::Tag() { return this->_tag; }
void Vertex::Tag(const std::string& newTag) { this->_tag = newTag; }

const std::size_t& Vertex::Position() { return this->_position; }
void Vertex::Position(const std::size_t& newPosition) { this->_position = newPosition; }

std::vector<std::size_t>& Vertex::Edges() { return this->_edges; }
void Vertex::Edges(const std::vector<std::size_t>& newEdges) { this->_edges = newEdges; }

Vertex::Vertex() 
    : _header(""), _tag(""), _position(0) {}
Vertex::Vertex(const Vertex& vertex) 
    : _header(vertex._header), _tag(vertex._tag), _position(vertex._position), _edges(vertex._edges) {}
Vertex::Vertex(const std::string& header, const std::string& tag, const std::size_t& position) 
    : _header(header), _tag(tag), _position(position) {}
Vertex::~Vertex() {}

std::map<std::size_t, Vertex> Graph::Vertices() { return this->_vertices; }

void Graph::AddEdge(const std::size_t& i, const std::size_t& j) {
    this->_vertices[i].Edges().push_back(j);
}

bool Graph::HasEdge(const std::size_t& i, const std::size_t& j) { 
    for(size_t k = 0; k < this->_vertices[i].Edges().size(); k++) {
        if(this->_vertices[i].Edges()[k] == j) return true;
    }
    return false;
}

void Graph::AddVertex(const std::size_t& id, const Vertex& vertex) {
    this->_vertices.insert({id, vertex});
}

bool Graph::HasVertex(const std::size_t& i) {
    return this->_vertices.find(i) != this->_vertices.end() ? true : false;
}

std::vector<Graph> Graph::FindClique() {
    std::vector<Graph> cliques = std::vector<Graph>();
    
    for(auto& [ key, vertex ] : this->Vertices()) {
        Graph clique = Graph();
        clique.AddVertex(key, Vertex(vertex));

        for(auto& edge : vertex.Edges()) {
            if(clique.HasVertex(edge) || [this, &clique, edge]() {
                for(auto& [ checkedKey, checkedVertex ] : clique.Vertices()) {
                    if(!this->HasEdge(checkedKey, edge)) return true;
                }
                return false;
            }()) continue;

            clique.AddVertex(edge, Vertex(this->Vertices()[edge]));
        }

        if(clique.Vertices().size() > 4) cliques.push_back(clique);
    }

    return cliques;
}

Graph::Graph() 
    : _vertices(std::map<std::size_t, Vertex>()) {}

Graph::Graph(std::vector<Fasta>& sequences, const std::size_t& maxTagLength) {
    std::size_t vertexID = 0;

    for(auto& sequence : sequences) {
        std::vector<std::pair<char, int>> patchedSequence = sequence.PatchedSequence();
        if(patchedSequence.size() < maxTagLength) return;

        std::size_t i = 0; 
        do {
            std::string tag = [patchedSequence, maxTagLength, i]() {
                std::string tagContainer = "";
                for(std::size_t j = i; j < i + maxTagLength; j++) {
                    tagContainer += patchedSequence[j].first;
                }
                return tagContainer;
            }();

            this->AddVertex(vertexID, Vertex(std::get<0>(sequence.SequenceMetadata()), tag, patchedSequence[i].second));
            for(std::size_t i = 0; i < this->Vertices().size(); i++) {
                if(this->Vertices()[i].Tag() == this->Vertices()[vertexID].Tag() && this->Vertices()[i].Header() != this->Vertices()[vertexID].Header()) {
                    this->AddEdge(vertexID, i);
                    this->AddEdge(i, vertexID);
                }
            }
            
            i++;
            vertexID++;
        } while(i <= patchedSequence.size() - maxTagLength);
    }
}

Graph::~Graph() {}