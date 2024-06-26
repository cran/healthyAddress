#ifndef healthyAddress_H
#define healthyAddress_H

#if _OPENMP
#include <omp.h>
#endif

#include <R.h>
#define USE_RINTERNALS
#include <Rinternals.h>
#include <stdint.h> // for uint64_t rather than unsigned long long
#include <stdbool.h>
#include <math.h>
#include "streetcodes.h"
#include <ctype.h>

#if defined _OPENMP && _OPENMP >= 201511
#define FORLOOP(content)                                                \
int nThread = as_nThread(nthreads);                                     \
_Pragma("omp parallel for num_threads(nThread)")                        \
  for (R_xlen_t i = 0; i < N; ++i) {                                    \
    content                                                             \
  }
#else
#define FORLOOP(content)                                       \
for (R_xlen_t i = 0; i < N; ++i) {                             \
  content                                                      \
}
#endif


// Empirical data / known features of Australian postcodes
#define N_POSTCODES 2642
#define SUP_POSTCODES 8192
#define SUP_POSTCODE_ 8191
#define MAX_NUMBER_STREET_TYPES_ANY_POSTCODE 64
#define N_STREET_TYPES 224
#define MAX_POSTCODE 7470
#define N_UNIQUE_STREET_CODES 224
#define MAX_STREET_CODE 224

// This is true, but not necessarily the longest
// word one might find in an address string
#define MAX_STREET_NAME_LEN 42

typedef struct {
  unsigned int THE_code : 2;
  unsigned int n_saints : 2;
} Postcode;

extern Postcode M_POSTCODE[SUP_POSTCODES];
bool isnt_vale_postcode(uint16_t poa);

// the_xxx_trie
#define ALPHABET_SIZE 27  // Assuming only uppercase letters plus space
typedef struct TrieNode {
  struct TrieNode *children[ALPHABET_SIZE];
  bool isEndOfWord;
  int code;
} TrieNode;

// Parameters or assumptions (often about stacks)
// // Number of words per string to be considered
#define WORD_DATUMS 32
#define COMMA_DATUMS 8
typedef struct {
  int n_words; // the actual number of words
  int lhs[WORD_DATUMS];
  int rhs[WORD_DATUMS];
  int comma_pos[COMMA_DATUMS];
  int flat_pos;
  int no1st; // position of first digit
  int postcode;
  int postcode_pos; // x[j + 0:3] is the postcode
  const char * x; // the original string
  int n; // the original string's length
} WordData;

WordData word_data(const char * x, int n);

// C_max_nchar.c
int max_nchar(SEXP x);
void err_if_nchar_geq(SEXP x, int max_nchar, const char * vx);

int isnt_sorted_asc(SEXP x);
int find_common_street(const char * x, int n, int i);

bool isUPPER(char x);
int next_numeral(int j, const char * x, int n);


bool has_STREET(const char * x, int n);
bool has_ROAD(const char * x, int n);
bool has_AVENUE(const char * x, int n);
bool has_DRIVE(const char * x, int n);
bool has_COURT(const char * x, int n);
bool has_CRESCENT(const char * x, int n);
bool has_WAY(const char * x, int n);
bool has_CLOSE(const char * x, int n);
bool has_PLACE(const char * x, int n);
bool has_LANE(const char * x, int n);
bool has_GROVE(const char * x, int n);

bool poa_has_ROAD(int poa);

bool poa_has_street_type(int poa, int type);
void prep_postcode2tinrnl(void);
unsigned int postcode2intrnl(unsigned int poa);
unsigned int intrnl2postcode(unsigned int ipoa);
bool is_postcode(unsigned int poa);


// followed_by_STE_POSTCODE
bool followed_by_STE_POSTCODE(int w_i, WordData * wd);

int isnt_sorted_asc(SEXP x);

// omp_diagnose.c
int as_nThread(SEXP nthreads);

// trie
#define N_THE_XXXS 703
extern const char * THE_XXXs[N_THE_XXXS];
extern const int H_THE_XXX[N_THE_XXXS];
TrieNode *getNode(void);
void freeTrie(TrieNode *root);
void insert(TrieNode *root, const char *key, int code);
int search(TrieNode *root, const char *key);
void insert_all(TrieNode *root);
void memoize_trie_postcodes(void);
int THE_xxx3(TrieNode *root, WordData * wd, unsigned char p_postcode);
SEXP C_do_the_xxx(SEXP x, SEXP Postcode, SEXP Hash);
void prepend_THE(char SN[MAX_STREET_NAME_LEN], const char * suffix);

// verifyEquiStr.c
void errIfNotStr(SEXP x, const char * xx);
void errIfNotLen(SEXP x, const char * xx, R_xlen_t N);
void verifyEquiStr2(SEXP x, const char * xx,
                    SEXP y, const char * yy);
void verifyEquiOrLen1Str2(SEXP x, const char * xx,
                          SEXP y, const char * yy);
void verifyEquiStr4(SEXP x, const char * xx,
                    SEXP y, const char * yy,
                    SEXP z, const char * zz,
                    SEXP w, const char * ww);
void errifNotTF(SEXP x, const char * v);
void verifyEquiDouble(SEXP x, const char * xx, SEXP y, const char * yy);

// xnumbers
int n_numbers(const char * x, int n);



#endif
