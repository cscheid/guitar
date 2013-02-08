#include "repository.h"
#include "entry_points.h"

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
    // the Rcpp::internal::make_new_object technique comes from here:
    // http://lists.r-forge.r-project.org/pipermail/rcpp-devel/2012-September/004265.html
    return Rcpp::internal::make_new_object(new GitReference(ref));
};

bool Repository::is_bare()
{
    return _git_repository_is_bare(repo.get());
}

std::string Repository::workdir()
{
    const char *r = _git_repository_workdir(repo.get());
    return r ? std::string(r) : std::string("");
}

RCPP_MODULE(guitar_repository) {
    using namespace Rcpp;
    class_<Repository>("Repository")
        .constructor<std::string>()
        .method("head", &Repository::head)
        .method("is_bare", &Repository::is_bare)
        .method("workdir", &Repository::workdir)
        ;
};
