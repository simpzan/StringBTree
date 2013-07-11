
#include <gflags/gflags.h>
#include "strBTree/StringBTree.h"
#include "strBTree/SortStringsFile.h"
#include "utils.h"
#include "timer.h"

using namespace std;

uint64_t sortData(const vector<string> &tokens, const string &sortedFile) {
  FILE *sorted_file = fopen(sortedFile.c_str(), "wb");
  int count = tokens.size();
  for (int i = 0; i < count; ++i) {
    const string &token = tokens[i];
    StringBTree::writeString(sorted_file, token.c_str(), token.size());
  }
  fclose(sorted_file);
  
  StringBTree::SortStringsFile sort(sortedFile.c_str(), true, true);
  sort.start("/tmp", 2);
  uint64_t nbValue = sort.getNbValues();
  return nbValue;
}

void queryData(const vector<string> &tokens, StringBTree::StrBTree &bTree) {
  int nbValues = tokens.size();
  Timer t;
  for (int si = 0; si < nbValues; ++si) {
    const string &aString = tokens[si];
    uint64_t searchResult = bTree.getEntry(aString.c_str(), aString.size());
    if (searchResult == 0) {
      cout << aString << " search failed" << endl;
      assert(searchResult);
    }
    if (si % 10000 == 0) {
      cout << si << endl;
    }
  }
  t.Report(nbValues);
}

DEFINE_bool(build, false, "if the input file is used to build the idx, or to query");
int main(int argc, char *argv[])
{
  google::ParseCommandLineFlags(&argc, &argv, true);
  assert(argc == 3);
  string idxFile = argv[1];
  string inputFile = argv[2];
  vector<string> tokens;
  loadTokensFromFile(inputFile.c_str(), tokens);

  StringBTree::StrBTree btree;
  if (FLAGS_build) {
    string sortedFile = idxFile + ".lexicon";
    uint64_t count = sortData(tokens, sortedFile);
    btree.build(idxFile, sortedFile, count);
  } else {
    btree.load(idxFile);
  }
  
  queryData(tokens, btree);
  
  return 0;
}
