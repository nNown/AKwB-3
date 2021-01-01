#include<fasta_parser.h>

FastaParser* FastaParser::_parserInstance = nullptr;
FastaParser::FastaParser() {}

std::vector<Fasta> FastaParser::LoadFasta(const std::string& path) {
    std::ifstream fastaFile = std::ifstream(path, std::ios::in);
    if(!fastaFile.is_open()) throw std::runtime_error("Failed to open file");

    std::vector<Fasta> sequences = std::vector<Fasta>();

    std::string line;

    std::string header, sequence = "";
    std::getline(fastaFile, header);

    while(std::getline(fastaFile, line)) {
        if(line.find(">") != std::string::npos) {
            sequences.push_back(Fasta(header, sequence));
            header = line;
            sequence = "";
        } else sequence += line;
    }
    sequences.push_back(Fasta(header, sequence));

    fastaFile.close();
    return sequences;
}

void FastaParser::DeleteNucleotidesBelowThreshold(Fasta& fasta, const std::string& pathToReliablityScoreFile, int threshold) {
    std::ifstream reliabilityFile = std::ifstream(pathToReliablityScoreFile, std::ios::in);
    if(!reliabilityFile.is_open()) throw std::runtime_error("Failed to open file");

    std::string header;
    while(std::getline(reliabilityFile, header)) {
        if(header.find(std::get<0>(fasta.SequenceMetadata())) != std::string::npos) {
            break;
        }
    }

    if(!header.compare(std::get<0>(fasta.SequenceMetadata()))) throw std::runtime_error("Wrong reliability table");

    std::string word, sequence = fasta.Sequence();
    int i = 0, score;
    while(reliabilityFile >> word) {
        if(word.find(">") != std::string::npos) break;

        score = std::stoi(word);

        if(score < threshold) {
            sequence.replace(i, 1, " ");
        }

        i++;
    }
    fasta.Sequence(sequence);
}

FastaParser* FastaParser::FastaParserInstance() {
    if(_parserInstance == nullptr) {
        _parserInstance = new FastaParser();
    }

    return _parserInstance;
}

FastaParser::~FastaParser() {}