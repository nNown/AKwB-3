#pragma once 

#include <map>
#include <vector>
#include <fasta.h>
#include <iostream>

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
        std::vector<Vertex> _vertices;
    public:
        std::vector<Vertex> Vertices();

        void AddEdge(const int& i, const int& j);
        bool HasEdge(const int& i, const int& j);

        void AddVertex(const Vertex& vertex);
        Graph FindClique();

        Graph();
        Graph(std::vector<Fasta>& sequences, const std::size_t& maxTagLength);
        ~Graph();
};