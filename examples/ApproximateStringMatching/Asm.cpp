#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <cerrno>
#include "etl/unordered_map.h"
#include "etl/string.h"
#include "etl_profile.h"

// size of vector and map containers
const size_t MAX_SIZE_INPUT = 200000;
const size_t MAX_SIZE_NODES = 200000;
const size_t SIZE_ALPHABETH = 12;           // in case of pi greek constant ([0-9]|','|'\b')*

// input vector word
etl::vector<char, MAX_SIZE_INPUT> WORD;

// transistion hash suffix tree tables
etl::unordered_map<int, etl::unordered_map<char, int, SIZE_ALPHABETH>,  MAX_SIZE_INPUT, MAX_SIZE_INPUT / 2> TRANSITIONS;
etl::unordered_map<int, etl::array<int, 4>,  MAX_SIZE_INPUT, MAX_SIZE_INPUT / 2> NODES;

etl::vector <char, MAX_SIZE_INPUT> get_file_contents(const char *filename) {
    std::ifstream in(filename, std::ios::in | std::ios::binary);
    if (in)
    {
        etl::vector <char, MAX_SIZE_INPUT> contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return(contents);
    }
    throw(errno);
}

int split(int parent, int child, int k) {
    // number of new node
    int m = i + n;
    // update hash tables transition
    etl::unordered_map<char, int, SIZE_ALPHABETH> temp; // {{{WORD[NODES[child][0]+k], child}}};
    temp.insert({WORD[NODES[child][0]+k], child});
    // from new node m to child
    TRANSITIONS.insert({m, temp});
    // Logger
    // std::cout << "Fin qui tutto bene, siamo al ciclo: " << i << std::endl;
    // std::cout << "the WORD[ NODES[child] ][ 0 ] + k ] of temp           : " << temp[WORD[NODES[child][0]+k]] << std::endl;
    // std::cout << "the WORD[ NODES[child] ][ 0 ] + k ] of transitions    : " << TRANSITIONS[m][WORD[NODES[child][0]+k]] << std::endl;

    // from parent to the new node m
    TRANSITIONS[parent][WORD[NODES[child][0]]] = m;
    // insert new node in NODES table
    try {
        NODES.insert({m, {NODES[child][0], NODES[child][0]+k, NULL, parent}});
    }
    catch (int param) { std::cout << "int exception" << std::endl; }
    catch (char param) { std::cout << "char exception" << std::endl; }
    catch (...) { std::cout << "default exception" << std::endl; }
    // set new begin char of transition
    NODES[child][0] += k;
    // set new parent
    NODES[child][3] = m;
    return m;
}

int rescan(int locus, int begin, int endin) {
    int l = 0;
    int size_beta = endin - begin;
    while (l < size_beta) {
        if (TRANSITIONS[locus].count(WORD[begin+l])) {
            int locus_f = TRANSITIONS[locus][WORD[begin+l]];
            int omega_size = NODES[locus_f][1] - NODES[locus_f][0];
            if (l + omega_size > size_beta) {
                return split (locus, locus_f, size_beta - l);
            }
            l += omega_size;
            locus = locus_f;
        }
        else
            break;
    }
    return locus;
}

int scan(int locus) {
    int l = 0;
    while (TRANSITIONS[locus].count(WORD[tail + l])) {
        int k = 0;
        int locus_f = TRANSITIONS[locus][WORD[tail + l]];
        while (k < (NODES[locus_f][1] - NODES[locus_f][0]) && WORD[k + NODES[locus_f][0]] == WORD[tail + l]) {
            k += 1;
            l += 1;
        }
        if (k >= NODES[locus_f][1] - NODES[locus_f][0])
            locus = locus_f;
        else {
            if (k) {
                tail = tail + l;
                return split(locus, locus_f, k);
            }
        }
    }
    tail = tail + l;
    return locus;
}

void stamp() {
    // Iterate and print keys and values of transition table
    std::cout << "TRANSITION TABLE" << std::endl;
    for( auto& t : TRANSITIONS ) {
        for ( auto& u : t.second) {
            std::cout << "Key:[" << t.first << "] Values:[" << u.first << ", " << u.second << "]\n";
        }
    }

    // Iterate and print keys and values of NODES table
    std::cout << "NODES TABLE" << std::endl;
    for( auto& t : NODES ) {
        std::cout << "Key:[" << t.first << "] Values:[" << t.second[0] << ", " << t.second[1] << ", " << t.second[2] << ", " << t.second[3] << "]\n";
    }
}


void mcc() {
    for (i = 0; i < n; ++i) {

        //std::cout << "inizio al ciclo suffix_tree: i " << i << std::endl;
        //head = chi + alpha + beta
        //if head is empty then also chi is empty
        if (begin_head==endin_head) {
            chi = 0;
            locus_alpha = 0;
            begin_beta = begin_head;
            endin_beta = endin_head;
        }
        //otherwise chi is the first char of head
        else {
            chi = 1;
            //if the parent of head is root, alpha is root
            if (NODES[locus_head][3] == 0) {
                begin_beta = chi + NODES[locus_head][0];
                locus_alpha = 0; // it is the same of else statement: nodes[nodes[locus_head][3]][2]; left here for performance purpose 
            }
            //otherwise alpha is the suffixlink of chi_alpha (the parent of head)
            else {
                begin_beta = NODES[locus_head][0];
                locus_alpha = NODES[NODES[locus_head][3]][2];
            }
            endin_beta = NODES[locus_head][1];
        }
        //compute the new locus of alpha_beta
        locus_alpha_beta = rescan(locus_alpha, begin_beta, endin_beta);
        //update suffix link
        NODES[locus_head][2] = locus_alpha_beta;   //Da Verificare se inserire null o -1 in caso suf_link empty
        //temp tail
        tail = i + endin_head - begin_head - chi;
        //update of head and tail
        locus_head = scan(locus_alpha_beta);
        //update of transition table
        TRANSITIONS[locus_head].insert({WORD[tail], i + 1});
        //update of NODES table
        try {
            NODES.insert({i + 1, {tail, n, NULL, locus_head}});
        }
        catch (int param) { std::cout << "int exception" << std::endl; }
        catch (char param) { std::cout << "char exception" << std::endl; }
        catch (...) { std::cout << "default exception" << std::endl; }
        //update of the new head
        begin_head = i;
        endin_head = tail;
        // std::cout << "Fin qui tutto bene, dentro mcc suffix_tree: ciclo " << i << std::endl;
        // std::cout << "Fin qui tutto bene, dentro al ciclo suffix_tree: n " << n << std::endl;

    }
        //std::cout << "Fin qui tutto bene, fuori dal ciclo suffix_tree: n " << n << std::endl;

}

void build_suffix_tree() {
    locus_head = 0;
    WORD.push_back('\b');
    begin_head = 0;
    endin_head = 0;
    NODES[0] = {0, 0, 0, 0};
    n = WORD.size();
    mcc();

    //std::cout << "Fin qui tutto bene, dentro build suffix_tree: n " << n << std::endl;
}

int main(int ac, char ** av) {

    WORD = get_file_contents(av[1]);
    
    //std::cout << "Dove eravamo rimasti..." << std::endl;

    // etl::unordered_map<char, int,  MAX_SIZE_INPUT, MAX_SIZE_INPUT / 2> TRANSITIONS;

    // transitions.insert({'a', 1});

    etl::unordered_map<int, etl::unordered_map<char, int, 10>, 100, 100 / 2> temp;  // segmentation fault (core dumped) if more than this

    build_suffix_tree();

    stamp();

    std::cout << "Fin qui tutto bene" << std::endl;
    for (int j=0; j<10; j++) {
        std::cout << "char number " << j << " is " << WORD[j] << std::endl;
    }

}