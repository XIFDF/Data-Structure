#include "Trie.h"
#include <gtest/gtest.h>


TEST(Trietest, get_result)
{
    shared_ptr<Trie> t = make_shared<Trie>();

    string i;
    t->insert("asdwert", t);
    t->insert("asds", t);
    ASSERT_TRUE(t->searchWith("asd", t));
    ASSERT_FALSE(t->searchWith("sw", t));
    ASSERT_TRUE(t->search("asdwert", t));
    ASSERT_FALSE(t->search("wer", t));
}