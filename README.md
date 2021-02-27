# Clique based sequence alignment
My implementation of multiple sequences alignment. Application creates graphs with edges between vertices with same sequence tag in different sequences and searches for cliques. Every clique is particular alignment.  

## Parameters
| Parameter | Data Type | Description |
|-----------|-----------|-------------|
| Path to fasta file (fasta) | String | 454 DNA sequencer output in fasta format |
| Path to qual file (qual) | String | 454 DNA sequencer reliability score output in qual format |
| Reliability score threshold (positionThreshold) | Integer greater than 0 | Score below which certain position in sequence will be deleted for further sequence processing |
| Tag length (tagLength) | Integer greater than 0 | Searched alignment length |

## Installation
```bash
make
```

## Usage
```bash
./main fasta qual positionThreshold tagLength
```