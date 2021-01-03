#include <iostream>
#include <fasta.h>
#include <fasta_parser.h>
#include <graph.h>

int main(void) {
    FastaParser* parser = FastaParser::FastaParserInstance();
    std::vector<Fasta> test = parser->LoadFasta("./test.fasta");
    parser->DeleteNucleotidesBelowThreshold(test[0], "./testr.qual", 26);
    std::cout << test[0].Sequence() << std::endl;
    parser->DeleteNucleotidesBelowThreshold(test[1], "./testr.qual", 26);
    std::cout << test[1].Sequence() << std::endl;
    parser->DeleteNucleotidesBelowThreshold(test[2], "./testr.qual", 26);
    std::cout << test[2].Sequence() << std::endl;

    Graph seqGraph = Graph(test, 5);
    for(std::size_t i = 0; i < seqGraph.Vertices().size(); i++) {
        for(std::size_t j = 0; j < seqGraph.Vertices().size(); j++) {
            if(seqGraph.HasEdge(i, j)) {
                std::cout << seqGraph.Vertices()[i].Position() << " : " << seqGraph.Vertices()[i].Tag() << " (" << seqGraph.Vertices()[i].Header() << ")" << " - " << seqGraph.Vertices()[j].Position() << " : " << seqGraph.Vertices()[j].Tag() << " (" << seqGraph.Vertices()[j].Header() << ")" << std::endl;
            }
        }
    }

    return 0;
}