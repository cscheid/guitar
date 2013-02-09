#pragma once

#include <boost/shared_ptr.hpp>

#include "guitar.h"
#include "reference.h"

/******************************************************************************/

class Repository: public CPPWrapperObjectTraits<Repository, git_repository>
{
public:
    explicit Repository(std::string path);

    // git_repository_config,
    // git_repository_detach_head,
    // git_repository_discover,
    // git_repository_fetchhead_foreach,
    // git_repository_free,
    // git_repository_hashfile,
    Rcpp::Reference head();
    // git_repository_head_detached,
    // git_repository_head_orphan,
    Rcpp::Reference index();
    // git_repository_init,
    // git_repository_init_ext,
    bool is_bare();
    // git_repository_is_empty,
    // git_repository_merge_cleanup,
    // git_repository_mergehead_foreach,
    // git_repository_message,
    // git_repository_message_remove,
    Rcpp::Reference odb();
    // git_repository_open,
    // git_repository_open_ext,
    // git_repository_path,
    // git_repository_set_config,
    // git_repository_set_head,
    // git_repository_set_head_detached,
    // git_repository_set_index,
    // git_repository_set_odb,
    // git_repository_set_workdir,
    // git_repository_state,
    std::string workdir();
    // git_repository_wrap_odb,

    Rcpp::Reference reference_lookup(std::string name); // returns a GitReference object
    Rcpp::Reference name_to_id(std::string name); // returns a OID object
    SEXP reference_list(unsigned int flags); // returns a list of characters

    git_repository *unwrap() { return repo.get(); }

protected:
    boost::shared_ptr<git_repository> repo;
};
