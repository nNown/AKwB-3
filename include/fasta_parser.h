#pragma once

#include <fstream>
#include <stdexcept>
#include <fasta.h>
#include <iostream>
#include <vector>
#include <cstring>

class FastaParser {
    private:
        static FastaParser* _parserInstance;
        FastaParser();
        
        
    public:
        std::vector<Fasta> LoadFasta(const std::string& path);
        void DeleteNucleotidesBelowThreshold(Fasta& fasta, const std::string& pathToReliablityScoreFile, int threshold);
        static FastaParser* FastaParserInstance();
        ~FastaParser();
};