#ifndef __ETL_PROFILE_H__
#define __ETL_PROFILE_H__

#define ETL_NO_STL

// input word
// etl::vector<char, MAX_SIZE_INPUT> word;
//etl::vector <char, MAX_SIZE> word;
//constructor
//SuffixTree(std::vector <char> &_word);
// char to int unordered sub map of transitions
// etl::unordered_map<char, int, MAX_SIZE, MAX_SIZE / 2> char_to_int; //number of backets over 2
//transition table with two info: char and child node
// etl::unordered_map<int, etl::unordered_map<char, int>, 10, 10, simple_hash> transitions;
// //node table with four int info: <begin_str, endin_str, suffix_link, parent_node>
// etl::unordered_map<int, etl::array<int, 4> > nodes;
//stamp function
void stamp();
//word length
int n;
    
//variables
//head string pointers
int begin_head;
int endin_head;
//chi length
int chi;
//beta string pointers
int begin_beta;
int endin_beta;
//tail string pointer
int tail;
//locus of head string
int locus_head;
//locus of alpha;
int locus_alpha;
//locus of alpha_beta
int locus_alpha_beta;
// iterator
int i;
//build functions
void build();
void mcc();
int scan(int locus);
int rescan(int locus, int begin, int endin);
int split(int parent, int child, int offset);


//etl::vector <char, MAX_SIZE_INPUT> get_file_contents(const char *filename)

#endif
