#pragma once 

#include <map>
#include <vector>

class Vertex {
    private: 
        std::string _header;
        std::string _tag;
        std::size_t _position;
        std::vector<int> _edges;
    public:
        const std::string& Header();
        void Header(const std::string& newHeader);
        const std::string& Tag();
        void Tag(const std::string& newTag);
        const std::size_t& Position();
        void Position(const std::size_t& newPosition);
        std::vector<int>& Edges();
        void Edges(const std::vector<int>& newEdges);

        Vertex();
        Vertex(const std::string& header, const std::string& tag, const std::size_t& position);
        ~Vertex();
};

class Graph {
    private: 
        // std::map<int, std::vector<int>> _vertices;
        std::vector<Vertex> _vertices;
    public:
        // std::map<int, std::vector<int>>& Vertices();
        std::vector<Vertex> Vertices();

        void AddEdge(const int& i, const int& j);
        bool HasEdge(const int& i, const int& j);

        // void AddVertex(const int& i);
        void AddVertex(const Vertex& vertex);
        // bool HasVertex(const int& i);

        Graph();
        ~Graph();
};