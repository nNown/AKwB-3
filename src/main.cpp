#include <iostream>
#include <fasta.h>
#include <fasta_parser.h>
#include <graph.h>

Graph parseGraph(std::vector<Fasta> sequences, std::size_t maxLength);

int main(void) {
    FastaParser* parser = FastaParser::FastaParserInstance();
    std::vector<Fasta> test = parser->LoadFasta("./test.fasta");
    parser->DeleteNucleotidesBelowThreshold(test[0], "./testr.qual", 26);
    std::cout << test[0].Sequence() << std::endl;
    parser->DeleteNucleotidesBelowThreshold(test[1], "./testr.qual", 26);
    std::cout << test[1].Sequence() << std::endl;

    Graph seqGraph = parseGraph(test, 5);
    for(auto& vertex : seqGraph.Vertices()) {
        std::cout << vertex.Position() << " : " << vertex.Tag() << std::endl;
    }

    return 0;
}

Graph parseGraph(std::vector<Fasta> sequences, std::size_t maxLength) {
    Graph sequenceGraph = Graph();
    
    for(auto& sequence : sequences) {
        std::vector<std::pair<char, int>> patchedSequence = sequence.PatchedSequence();
        for(std::size_t i = 0; i < patchedSequence.size() - maxLength; i++) {
            std::string tag = [patchedSequence, i, maxLength]() {
                std::string tagContainer = "";
                for(std::size_t j = i; j < i + maxLength; j++) {
                    tagContainer += patchedSequence[j].first;
                }
                return tagContainer;
            }();

            sequenceGraph.AddVertex(Vertex(std::get<0>(sequence.SequenceMetadata()), tag, patchedSequence[i].second));
        }
    }

    return sequenceGraph;
}