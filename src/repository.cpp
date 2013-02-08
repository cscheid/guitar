#include "repository.h"
#include "entry_points.h"
#include "index.h"

/******************************************************************************/

Repository::Repository(std::string path)
{
    git_repository *_repo;
    _git_repository_open(&_repo, path.c_str());
    repo = boost::shared_ptr<git_repository>(_repo, _git_repository_free);
}

Rcpp::Reference Repository::head() {
    git_reference *ref;
    _git_repository_head(&ref, repo.get());
    return Rcpp::internal::make_new_object(new GitReference(ref));
};

Rcpp::Reference Repository::index() {
    git_index *ix;
    _git_repository_index(&ix, repo.get());
    return Rcpp::internal::make_new_object(new Index(ix));
};

bool Repository::is_bare()
{
    return _git_repository_is_bare(repo.get());
};

std::string Repository::workdir()
{
    const char *r = _git_repository_workdir(repo.get());
    return r ? std::string(r) : std::string("");
};

RCPP_MODULE(guitar_repository) {
    using namespace Rcpp;
    class_<Repository>("Repository")
        .constructor<std::string>()
        .method("head", &Repository::head)
        .method("index", &Repository::index)
        .method("is_bare", &Repository::is_bare)
        .method("workdir", &Repository::workdir)
        ;
};
