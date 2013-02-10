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

    git_commit *unwrap() const { return commit.get(); }

protected:
    boost::shared_ptr<git_commit> commit;
};
