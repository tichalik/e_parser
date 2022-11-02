# esperanto-constituency-parser

The project is an implementation of a constituency parser for the Esperanto language. 
While Esperanto is the main concern of this project, the software can be also used to
process other languages, both in the NLP understanding and in formal grammar approach.

The parser uses a predefined treebank of annotated sentences to analyze input files; 
the treebank can freely modified by adding/removing/changing files in the `trees` directory.
Additionally the grammar used to parse input sentences may also be provided as an XML file
placed in the `XML` directory. Switching between these two sources is done through code in 
`main.cpp` file, at the place marked with an appropriate comment. 

Sentences to be parsed are placed in text files in the `input` directory. The result is 
printed out in the console. 

Software provides concurrent processing, as well as ellaborate error handling in case 
of issues in provided input.
