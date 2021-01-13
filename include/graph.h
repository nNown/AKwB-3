#pragma once 

#include <map>
#include <vector>
#include <fasta.h>
#include <iostream>
#include <functional>

class Vertex {
    private: 
        std::string _header;
        std::string _tag;
        std::size_t _position;
        std::vector<std::size_t> _edges;
    public:
        const std::string& Header();
        void Header(const std::string& newHeader);
        const std::string& Tag();
        void Tag(const std::string& newTag);
        const std::size_t& Position();
        void Position(const std::size_t& newPosition);
        std::vector<std::size_t>& Edges();
        void Edges(const std::vector<std::size_t>& newEdges);

        Vertex();
        Vertex(const Vertex& vertex);
        Vertex(const std::string& header, const std::string& tag, const std::size_t& position);
        ~Vertex();
};

class Graph {
    private: 
        std::map<std::size_t, Vertex> _vertices;
    public:
        std::map<std::size_t, Vertex> Vertices();

        void AddEdge(const std::size_t& i, const std::size_t& j);
        bool HasEdge(const std::size_t& i, const std::size_t& j);

        void AddVertex(const std::size_t& id, const Vertex& vertex);
        bool HasVertex(const std::size_t& i);

        std::vector<Graph> FindClique();

        Graph();
        Graph(std::vector<Fasta>& sequences, const std::size_t& maxTagLength);
        ~Graph();
};