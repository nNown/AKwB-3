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

Graph Graph::FindClique() {
    Graph clique = Graph();
    
    for(std::size_t i = 0; i < this->Vertices().size(); i++) {
        for(std::size_t j = 0; j < this->Vertices().size(); j++) {

        }
    }
}

void Graph::AddVertex(const Vertex& vertex) {
    this->_vertices.push_back(vertex);
}

Graph::Graph() 
    : _vertices(std::vector<Vertex>()) {}

Graph::Graph(std::vector<Fasta>& sequences, const std::size_t& maxTagLength) {
    for(auto& sequence : sequences) {
        std::vector<std::pair<char, int>> patchedSequence = sequence.PatchedSequence();

        std::size_t i = 0; 
        do {
            std::string tag = [patchedSequence, maxTagLength, i]() {
                std::string tagContainer = "";
                for(std::size_t j = i; j < i + maxTagLength; j++) {
                    tagContainer += patchedSequence[j].first;
                }
                return tagContainer;
            }();
            std::cout << sequence.Sequence() << " " << i << " : " << tag << std::endl;
            this->AddVertex(Vertex(std::get<0>(sequence.SequenceMetadata()), tag, patchedSequence[i].second));
            i++;
        } while(i <= patchedSequence.size() - maxTagLength);
    }

    for(std::size_t i = 0; i < this->Vertices().size(); i++) {
        for(std::size_t j = 0; j < this->Vertices().size(); j++) {
            if(this->Vertices()[i].Tag() == this->Vertices()[j].Tag() && this->Vertices()[i].Header() != this->Vertices()[j].Header()) {
                this->AddEdge(i, j);
                this->AddEdge(j, i);
            }
        }
    }
}

Graph::~Graph() {}