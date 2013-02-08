#pragma once

#include <RcppCommon.h>
#include <Rcpp.h>
#include "reference.h"

class Repository
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
    // git_repository_index,
    // git_repository_init,
    // git_repository_init_ext,
    bool is_bare();
    // git_repository_is_empty,
    // git_repository_merge_cleanup,
    // git_repository_mergehead_foreach,
    // git_repository_message,
    // git_repository_message_remove,
    // git_repository_odb,
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

protected:
    boost::shared_ptr<git_repository> repo;
};
