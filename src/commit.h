#pragma once

#include "guitar.h"

/******************************************************************************/

class Commit: public CPPWrapperObjectTraits<Commit, git_commit>
{
public:
    explicit Commit(git_commit *commit);

    Rcpp::Reference id();
    std::string message_encoding();
    std::string message();
    SEXP time();
    SEXP committer();
    SEXP author();
    int type();

    unsigned int parent_count();

    // these load the commits from the db
    Rcpp::Reference parent(unsigned int n);
    Rcpp::List parent_list();

    // these don't
    Rcpp::Reference parent_id(unsigned int n);
    Rcpp::List parent_id_list();

    git_commit *unwrap() const { return commit.get(); }

protected:
    boost::shared_ptr<git_commit> commit;
};
