#pragma once

#include "guitar.h"
#include <boost/shared_ptr.hpp>

class Index: public CPPWrapperObjectTraits<Index, git_index>
{
public:
    explicit Index(git_index *_ix); 

    SEXP read(); // git_index_read
    SEXP write(); // git_index_write

    void read_tree(SEXP tree);
    Rcpp::Reference write_tree(); // returns OID of the tree, not tree object itself

    size_t entrycount(); // git_index_entrycount
    void clear(); // git_index_clear;

    void add_by_path(std::string path);
    void remove_by_path(std::string path);
    void remove_directory(std::string path, int stage);

    Rcpp::List get_by_index(size_t n);
    Rcpp::List get_by_path(std::string path, int stage);

    // GIT_EXTERN(const git_index_entry *) git_index_get_byindex(git_index *index, size_t n);
    // GIT_EXTERN(const git_index_entry *) git_index_get_bypath(git_index *index, const char *path, int stage);

    // GIT_EXTERN(int) git_index_open(git_index **out, const char *index_path);
    // GIT_EXTERN(git_repository *) git_index_owner(const git_index *index);
    // GIT_EXTERN(unsigned int) git_index_caps(const git_index *index);
    // GIT_EXTERN(int) git_index_set_caps(git_index *index, unsigned int caps);
    // GIT_EXTERN(int) git_index_write_tree_to(git_oid *out, git_index *index, git_repository *repo);
    // GIT_EXTERN(int) git_index_remove(git_index *index, const char *path, int stage);
    // GIT_EXTERN(int) git_index_add(git_index *index, const git_index_entry *source_entry);
    // GIT_EXTERN(int) git_index_entry_stage(const git_index_entry *entry);
    // GIT_EXTERN(int) git_index_find(size_t *at_pos, git_index *index, const char *path);
    // GIT_EXTERN(int) git_index_conflict_add(git_index *index,
    //                                        const git_index_entry *ancestor_entry,
    //                                        const git_index_entry *our_entry,
    //                                        const git_index_entry *their_entry);
    // GIT_EXTERN(int) git_index_conflict_get(git_index_entry **ancestor_out, git_index_entry **our_out, git_index_entry **their_out, git_index *index, const char *path);
    // GIT_EXTERN(int) git_index_conflict_remove(git_index *index, const char *path);
    // GIT_EXTERN(void) git_index_conflict_cleanup(git_index *index);
    // GIT_EXTERN(int) git_index_has_conflicts(const git_index *index);
    // GIT_EXTERN(unsigned int) git_index_reuc_entrycount(git_index *index);
    // GIT_EXTERN(int) git_index_reuc_find(size_t *at_pos, git_index *index, const char *path);
    // GIT_EXTERN(const git_index_reuc_entry *) git_index_reuc_get_bypath(git_index *index, const char *path);
    // GIT_EXTERN(const git_index_reuc_entry *) git_index_reuc_get_byindex(git_index *index, size_t n);
    // GIT_EXTERN(int) git_index_reuc_add(git_index *index, const char *path,
    //                                    int ancestor_mode, git_oid *ancestor_id,
    //                                    int our_mode, git_oid *our_id,
    //                                    int their_mode, git_oid *their_id);
    // GIT_EXTERN(int) git_index_reuc_remove(git_index *index, size_t n);

    git_index *unwrap() { return ix.get(); }

protected:
    boost::shared_ptr<git_index> ix;
};
