#include <iostream>
#include <fasta.h>
#include <fasta_parser.h>
#include <graph.h>

int main(int argc, char* argv[]) {
    FastaParser* parser = FastaParser::FastaParserInstance();
    std::vector<Fasta> sequences = parser->LoadFasta(argv[1]);
    for(std::size_t i = 0; i < sequences.size(); i++) {
        parser->DeleteNucleotidesBelowThreshold(sequences[i], argv[2], std::stoi(argv[3]));
        std::cout << "Sequence: " << sequences[i].Sequence() << std::endl;
    }

    Graph seqGraph = Graph(sequences, std::stoi(argv[4]));
    std::vector<Graph> cliques = seqGraph.FindClique();

    std::vector<std::string> usedTags = std::vector<std::string>();
    for(auto& graph : cliques) {
        if(std::find(usedTags.begin(), usedTags.end(), graph.Vertices().begin()->second.Tag()) != usedTags.end()) continue;

        std::cout << "Clique: " << std::endl;
        for(auto& [ key, vertex ] : graph.Vertices()) {
            std::cout << vertex.Header() << " : " << vertex.Position() << " - " << vertex.Tag() << std::endl;
        }
        std::cout << std::endl;
        usedTags.push_back(graph.Vertices().begin()->second.Tag());
    }

    // for(int i = 20; i < 33; i++) {
    //     std::cout << "Threshold: " << i << std::endl;
    //     std::vector<Fasta> sequences = parser->LoadFasta(argv[1]);
    //     for(auto& sequence : sequences) {
    //         parser->DeleteNucleotidesBelowThreshold(sequence, argv[2], i);
    //         std::cout << "Sequence " << std::get<0>(sequence.SequenceMetadata()) << ": " << sequence.Sequence() << std::endl;
    //     }

    //     for(int j = 4; j < 10; j++) {
    //         std::cout << "Tag length: " << j << std::endl;
    //         Graph seqGraph(sequences, j);
    //         std::vector<Graph> cliques = seqGraph.FindClique();

    //         std::vector<std::string> usedTags = std::vector<std::string>();
    //         for(auto& graph : cliques) {
    //             if(std::find(usedTags.begin(), usedTags.end(), graph.Vertices().begin()->second.Tag()) != usedTags.end()) continue;

    //             for(auto& [ key, vertex ] : graph.Vertices()) {
    //                 std::cout << vertex.Header() << " : " << vertex.Position() + 1 << " - " << vertex.Tag() << std::endl;
    //             }
    //             std::cout << std::endl;
    //             usedTags.push_back(graph.Vertices().begin()->second.Tag());
    //         }
    //         std::cout << std::endl;
    //     }
    //     std::cout << "============================================================" << std::endl;
    // }

    return 0;
}