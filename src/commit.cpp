#include "commit.h"
#include "oid.h"
#include "entry_points.h"
#include "time.h"

/******************************************************************************/

static void __git_commit_free(git_commit *commit)
{
    _git_object_free((git_object *)commit);
}

Commit::Commit(git_commit *_commit)
{
    commit = boost::shared_ptr<git_commit>(_commit, __git_commit_free);
}

Rcpp::Reference Commit::id()
{
    const git_oid *result = _git_object_id((const git_object *)commit.get());
    return OID::create(result);
}

std::string Commit::message_encoding()
{
    return std::string(_git_commit_message_encoding(commit.get()));
}

std::string Commit::message()
{
    return std::string(_git_commit_message(commit.get()));
}

SEXP Commit::time()
{
    git_time r;
    r.time = _git_commit_time(commit.get());
    r.offset = _git_commit_time_offset(commit.get());
    return Time::create(&r);
}

SEXP Commit::committer()
{
    const git_signature *result = _git_commit_committer(commit.get());
    return Rcpp::List::create(Rcpp::Named("name") = std::string(result->name),
                              Rcpp::Named("email") = std::string(result->email),
                              Rcpp::Named("time") = Time::create(&result->when));
}

SEXP Commit::author()
{
    const git_signature *result = _git_commit_author(commit.get());
    return Rcpp::List::create(Rcpp::Named("name") = std::string(result->name),
                              Rcpp::Named("email") = std::string(result->email),
                              Rcpp::Named("time") = Time::create(&result->when));
}

int Commit::type()
{
    return _git_object_type((git_object*)commit.get());
}

RCPP_MODULE(guitar_commit) {
    using namespace Rcpp;
    class_<Commit>("Commit")
        .method("id", &Commit::id)
        .method("message_encoding", &Commit::message_encoding)
        .method("message", &Commit::message)
        .method("time", &Commit::time)
        .method("type", &Commit::type)
        .method("committer", &Commit::committer)
        .method("author", &Commit::author)
        ;
}
