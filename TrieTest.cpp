#include <gtest/gtest.h>
#include "Trie.h"

TEST(Trietest, get_result) {

    shared_ptr<Trie> t = make_shared<Trie>();
    
    string i;
    t.get()->insert("asdwert");
    t.get()->insert("asds");
    
    ASSERT_TRUE(t.get()->searchWith("asds"));
}