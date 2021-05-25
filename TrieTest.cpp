#include "Trie.h"
#include <gtest/gtest.h>


TEST(Trietest, get_result)
{
    shared_ptr<Trie> t = make_shared<Trie>();

    string i;
    t->insert("asdwert");
    t->insert("asds");
    ASSERT_TRUE(t->searchWith("asd"));
    ASSERT_FALSE(t->searchWith("sw"));
    ASSERT_TRUE(t->search("asdwert"));
    ASSERT_FALSE(t->search("wer"));
}