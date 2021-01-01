#pragma once

#include <algorithm>
#include <string>
#include <tuple>
#include <vector>

class Fasta {
    private:
        std::string _header;
        std::string _sequence;
    public:
        std::tuple<std::string, std::size_t, std::pair<int, int>, int, std::string> SequenceMetadata();
        void SequenceMetadata(const std::string& newMetadata);
        const std::string& Sequence();
        void Sequence(const std::string& newSequence);

        const std::vector<std::pair<char, int>> PatchedSequence();

        Fasta();
        Fasta(const std::string& header, const std::string& sequence);
        ~Fasta();
};