#pragma once

#include <boost/shared_ptr.hpp>

#include "guitar.h"
#include "reference.h"

/******************************************************************************/

class Repository: public CPPWrapperObjectTraits<Repository, git_repository>
{
public:
    explicit Repository(std::string path);
    explicit Repository(git_repository *_repo);

    // git_repository_config,
    // git_repository_detach_head,
    // git_repository_discover,
    // git_repository_fetchhead_foreach,
    Rcpp::Reference hash_file(std::string path, int type); // git_repository_hashfile,
    Rcpp::Reference head();
    bool head_detached();
    bool head_orphan();
    Rcpp::Reference index();
    // git_repository_init_ext,
    bool is_bare();
    bool is_empty();
    // git_repository_merge_cleanup,
    // git_repository_mergehead_foreach,
    // git_repository_message,
    // git_repository_message_remove,
    Rcpp::Reference odb();
    // git_repository_open_ext,
    std::string path();
    // git_repository_set_config,
    void set_head(std::string refname);
    void set_head_detached(SEXP oid);
    // git_repository_set_index,
    // git_repository_set_odb,
    // git_repository_set_workdir,
    int state();
    // git_repository_state,
    std::string workdir();
    // git_repository_wrap_odb,

    Rcpp::Reference reference_lookup(std::string name); // returns a GitReference object
    Rcpp::Reference name_to_id(std::string name); // returns a OID object
    SEXP reference_list(unsigned int flags); // returns a list of characters

    // returns a Commit, Tree, Blog, Tar, OffsetDelta or ReferenceDelta objects
    // (that is, one of the subclasses of git_object)
    SEXP object_lookup(SEXP oid, int otype);

    void create_commit(std::string update_ref,
                       SEXP author,
                       SEXP committer,
                       std::string message_encoding,
                       std::string message,
                       SEXP tree,
                       SEXP parents);

    git_repository *unwrap() { return repo.get(); }

protected:
    boost::shared_ptr<git_repository> repo;
};
