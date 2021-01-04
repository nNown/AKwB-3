#include <iostream>
#include <fasta.h>
#include <fasta_parser.h>
#include <graph.h>

int main(void) {
    FastaParser* parser = FastaParser::FastaParserInstance();
    std::vector<Fasta> test = parser->LoadFasta("./test.fasta");
    for(std::size_t i = 0; i < test.size(); i++) {
        parser->DeleteNucleotidesBelowThreshold(test[i], "./testr.qual", 26);
    }

    Graph seqGraph = Graph(test, 5);
    // for(std::size_t i = 0; i < seqGraph.Vertices().size(); i++) {
    //     for(std::size_t j = 0; j < seqGraph.Vertices().size(); j++) {
    //         if(seqGraph.HasEdge(i, j)) {
    //             std::cout << i << ":" << seqGraph.Vertices()[i].Position() << " : " << seqGraph.Vertices()[i].Tag() << " (" << seqGraph.Vertices()[i].Header() << ")" << " - " << j << ":" << seqGraph.Vertices()[j].Position() << " : " << seqGraph.Vertices()[j].Tag() << " (" << seqGraph.Vertices()[j].Header() << ")" << std::endl;
    //         }
    //     }
    //     // std::cout << i << ":" << seqGraph.Vertices()[i].Position() << " : " << seqGraph.Vertices()[i].Tag() << " (" << seqGraph.Vertices()[i].Header() << ")" << std::endl;
    // }

    Graph clique = seqGraph.FindClique();
    for(auto& [ key, vertex ] : clique.Vertices()) {
        // for(auto& [ comparedKey, comparedVertex ] : clique.Vertices()) {
        //     if(clique.HasEdge(key, comparedKey)) {
        //         std::cout << key << ":" << vertex.Position() << " : " << vertex.Tag() << " (" << vertex.Header() << ")" << " - " << comparedKey << ":" << comparedVertex.Position() << " : " << comparedVertex.Tag() << " (" << comparedVertex.Header() << ")" << std::endl;
        //     }
        // }
        std::cout << vertex.Header() << " : " << vertex.Position() << " - " << vertex.Tag() << std::endl;
    }

    return 0;
}