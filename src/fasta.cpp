#include <fasta.h>

std::tuple<std::string, std::size_t, std::pair<int, int>, int, std::string> Fasta::SequenceMetadata() {
    if(this->_header.empty()) return std::make_tuple("", 0, std::make_pair(0, 0), 0, "");

    std::string word = "";
    std::vector<std::string> data = std::vector<std::string>();
    for(auto& letter : this->_header) {
        if(letter == ' ') {
            data.push_back(word);
            word = "";
        } else {
            word += letter;
        }

        if(letter == '=') {
            word = "";
        }
    }
    data.push_back(word);

    word = "";
    int x = 0, y = 0;
    for(auto& letter : data[2]) {
        if(letter == '_') {
            x = std::stoi(word);
            word = "";
        } else {
            word += letter;
        }
    }
    y = std::stoi(word);

    int length = std::stoi(data[1]);
    int region = std::stoi(data[3]);

    return std::make_tuple(data[0], length, std::make_pair(x, y), region, data[4]);
}

void Fasta::SequenceMetadata(const std::string& newMetadata) { this->_header = newMetadata; }

const std::string& Fasta::Sequence() { return this->_sequence; }
void Fasta::Sequence(const std::string& newSequence) { this->_sequence = newSequence; }

const std::vector<std::pair<char, int>> Fasta::PatchedSequence() {
    std::vector<std::pair<char, int>> patchedSequence = std::vector<std::pair<char, int>>();
    
    for(std::size_t i = 0; i < this->_sequence.length(); i++) {
        if(this->_sequence[i] == ' ') continue;

        patchedSequence.push_back(std::make_pair(this->_sequence[i], i));
    }

    return patchedSequence;
}

Fasta::Fasta() : _header(""), _sequence("") {}
Fasta::Fasta(const std::string& header, const std::string& sequence) : _header(header), _sequence(sequence) {}
Fasta::~Fasta() {}
