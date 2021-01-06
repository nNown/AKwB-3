#include <iostream>
#include <fasta.h>
#include <fasta_parser.h>
#include <graph.h>

int main(int argc, char* argv[]) {
    FastaParser* parser = FastaParser::FastaParserInstance();
    // std::vector<Fasta> sequences = parser->LoadFasta(argv[1]);
    // for(std::size_t i = 0; i < sequences.size(); i++) {
    //     parser->DeleteNucleotidesBelowThreshold(sequences[i], argv[2], std::stoi(argv[3]));
    // }

    // Graph seqGraph = Graph(sequences, std::stoi(argv[4]));
    // Graph clique = seqGraph.FindClique();
    // for(auto& [ key, vertex ] : clique.Vertices()) {
    //     std::cout << vertex.Header() << " : " << vertex.Position() << " - " << vertex.Tag() << std::endl;
    // }

    for(int i = 20; i < 33; i++) {
        std::vector<Fasta> sequences = parser->LoadFasta(argv[1]);
        for(auto& sequence : sequences) {
            parser->DeleteNucleotidesBelowThreshold(sequence, argv[2], i);
        }
        
        std::cout << "Threshold: " << i << std::endl;
        for(int j = 4; j < 10; j++) {
            std::cout << "Tag length: " << j << std::endl;
            Graph seqGraph(sequences, j);
            Graph clique = seqGraph.FindClique();
            for(auto& [ key, vertex ] : clique.Vertices()) {
                std::cout << vertex.Header() << " : " << vertex.Position() << " - " << vertex.Tag() << std::endl;
            }
            std::cout << std::endl;
        }
        std::cout << "============================================================" << std::endl;
    }

    return 0;
}