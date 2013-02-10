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

unsigned int Commit::parent_count()
{
    return _git_commit_parentcount(commit.get());
}

Rcpp::Reference Commit::parent(unsigned int n)
{
    BEGIN_RCPP
    git_commit *result;
    int err = _git_commit_parent(&result, commit.get(), n);
    if (err)
        throw Rcpp::exception("bad parent number");
    return Commit::create(result);
    END_RCPP
}

Rcpp::List Commit::parent_list()
{
    BEGIN_RCPP
    Rcpp::List v;
    unsigned int c = parent_count();
    for (int i=0; i<c; ++i) {
        v.push_back(parent(i));
    }
    return v;
    END_RCPP
}

Rcpp::Reference Commit::parent_id(unsigned int n)
{
    BEGIN_RCPP
    const git_oid *result = _git_commit_parent_id(commit.get(), n);
    return OID::create(result);
    END_RCPP
}

Rcpp::List Commit::parent_id_list()
{
    BEGIN_RCPP
    Rcpp::List v;
    unsigned int c = parent_count();
    for (int i=0; i<c; ++i) {
        v.push_back(parent_id(i));
    }
    return v;
    END_RCPP
}

RCPP_MODULE(guitar_commit) {
    using namespace Rcpp;
    class_<Commit>("Commit")
        .method("id", &Commit::id)
        .method("message_encoding", &Commit::message_encoding)
        .method("message", &Commit::message)
        .method("time", &Commit::time)
        .method("committer", &Commit::committer)
        .method("author", &Commit::author)
        .method("type", &Commit::type)
        .method("parent_count", &Commit::parent_count)
        .method("parent", &Commit::parent)
        .method("parent_list", &Commit::parent_list)
        .method("parent_id", &Commit::parent_id)
        .method("parent_id_list", &Commit::parent_id_list)
        ;
}
