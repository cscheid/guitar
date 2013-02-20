#pragma once

#include "guitar.h"

/******************************************************************************/

class Tree: public CPPWrapperObjectTraits<Tree, git_tree>
{
public:
    explicit Tree(git_tree *_tree);

    Rcpp::Reference id();
    size_t entry_count();
    int walk_pre(Rcpp::Function f);
    int walk_post(Rcpp::Function f);

    git_tree *unwrap() const { return tree.get(); }
    Rcpp::Reference entry_by_index(size_t idx);
    Rcpp::Reference entry_by_name(std::string filename);
    Rcpp::Reference entry_by_oid(SEXP oid);
    Rcpp::Reference entry_by_path(std::string path);

protected:
    boost::shared_ptr<git_tree> tree;
};

class TreeEntry: public CPPWrapperObjectTraits<TreeEntry, git_tree_entry>
{
public:
    TreeEntry(git_tree_entry *entry);
    int file_mode();
    Rcpp::Reference id();
    std::string name();
    SEXP object(SEXP _repo);
    int type();

protected:
    boost::shared_ptr<git_tree_entry> tree_entry;
};


