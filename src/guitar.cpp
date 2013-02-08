#include "rcpp_hello_world.h"
#include <git2.h>
#include <dlfcn.h>
#include <cstdio>
#include <string>

/******************************************************************************/

using namespace Rcpp;

/******************************************************************************/
// repository.h

int (*_git_repository_open)(git_repository **out, const char *path);
int (*_git_repository_wrap_odb)(git_repository **out, git_odb *odb);
int (*_git_repository_open_ext)(
	git_repository **out,
	const char *path,
	unsigned int flags,
	const char *ceiling_dirs);
void (*_git_repository_free)(git_repository *repo);
int (*_git_repository_init)(
	git_repository **out,
	const char *path,
	unsigned is_bare);
int (*_git_repository_init_ext)(
	git_repository **out,
	const char *repo_path,
	git_repository_init_options *opts);
int (*_git_repository_head)(git_reference **out, git_repository *repo);
int (*_git_repository_head_detached)(git_repository *repo);
int (*_git_repository_head_orphan)(git_repository *repo);
int (*_git_repository_is_empty)(git_repository *repo);
const char * (*_git_repository_path)(git_repository *repo);
const char * (*_git_repository_workdir)(git_repository *repo);
int (*_git_repository_set_workdir)(
	git_repository *repo, const char *workdir, int update_gitlink);
int (*_git_repository_is_bare)(git_repository *repo);
int (*_git_repository_config)(git_config **out, git_repository *repo);
void (*_git_repository_set_config)(git_repository *repo, git_config *config);
int (*_git_repository_odb)(git_odb **out, git_repository *repo);
void (*_git_repository_set_odb)(git_repository *repo, git_odb *odb);
int (*_git_repository_index)(git_index **out, git_repository *repo);
void (*_git_repository_set_index)(git_repository *repo, git_index *index);
int (*_git_repository_message)(char *out, size_t len, git_repository *repo);
int (*_git_repository_message_remove)(git_repository *repo);
int (*_git_repository_merge_cleanup)(git_repository *repo);
int (*_git_repository_fetchhead_foreach)(git_repository *repo,
	git_repository_fetchhead_foreach_cb callback,
	void *payload);
int (*_git_repository_mergehead_foreach)(git_repository *repo,
	git_repository_mergehead_foreach_cb callback,
	void *payload);
int (*_git_repository_hashfile)(
    git_oid *out,
    git_repository *repo,
    const char *path,
    git_otype type,
    const char *as_path);
int (*_git_repository_set_head)(
	git_repository* repo,
	const char* refname);
int (*_git_repository_set_head_detached)(
	git_repository* repo,
	const git_oid* commitish);
int (*_git_repository_detach_head)(
	git_repository* repo);
int (*_git_repository_state)(git_repository *repo);

/******************************************************************************/

class Repository
{
public:
    explicit Repository(std::string path) {
        _git_repository_open(&repo, path.c_str());
    }
    ~Repository() {
        if (repo) {
            _git_repository_free(repo);
        }
    }

    // git_repository_config,
    // git_repository_detach_head,
    // git_repository_discover,
    // git_repository_fetchhead_foreach,
    // git_repository_free,
    // git_repository_hashfile,
    // git_repository_head,
    // git_repository_head_detached,
    // git_repository_head_orphan,
    // git_repository_index,
    // git_repository_init,
    // git_repository_init_ext,
    bool is_bare() {
        return _git_repository_is_bare(repo);
    };
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
    std::string workdir() {
        const char *r = _git_repository_workdir(repo);
        return r ? std::string(r) : std::string("");
    };
    // git_repository_wrap_odb,

protected:
    git_repository *repo;
};

RCPP_MODULE(guitar) {
    class_<Repository>("Repository")
        .constructor<std::string>()
        .method("is_bare", &Repository::is_bare)
        .method("workdir", &Repository::workdir)
    ;
};

SEXP load_library()
{
    BEGIN_RCPP

    void *result = dlopen("libgit2.dylib", RTLD_LAZY);
    _git_repository_open = (int (*)(git_repository**, const char*)) dlsym(result, "git_repository_open");

    if (!_git_repository_open) {
        return Rcpp::LogicalVector::create(false);
    }

    _git_repository_free = (void (*)(git_repository*)) dlsym(result, "git_repository_free");
    _git_repository_open = (int (*)(git_repository **out, const char *path)) dlsym(result, "git_repository_open");
    _git_repository_wrap_odb = (int (*)(git_repository **out, git_odb *odb)) dlsym(result, "git_repository_wrap_odb");
    _git_repository_open_ext = (int (*)(
	git_repository **out,
	const char *path,
	unsigned int flags,
	const char *ceiling_dirs)) dlsym(result, "git_repository_open_ext");
    _git_repository_free = (void (*)(git_repository *repo)) dlsym(result, "git_repository_free");
    _git_repository_init = (int (*)(
	git_repository **out,
	const char *path,
	unsigned is_bare)) dlsym(result, "git_repository_init");
    _git_repository_init_ext = (int (*)(
	git_repository **out,
	const char *repo_path,
	git_repository_init_options *opts)) dlsym(result, "git_repository_init_ext");
    _git_repository_head = (int (*)(git_reference **out, git_repository *repo)) dlsym(result, "git_repository_head");
    _git_repository_head_detached = (int (*)(git_repository *repo)) dlsym(result, "git_repository_head_detached");
    _git_repository_head_orphan = (int (*)(git_repository *repo)) dlsym(result, "git_repository_head_orphan");
    _git_repository_is_empty = (int (*)(git_repository *repo)) dlsym(result, "git_repository_is_empty");
    _git_repository_path = (const char * (*)(git_repository *repo)) dlsym(result, "git_repository_path");
    _git_repository_workdir = (const char * (*)(git_repository *repo)) dlsym(result, "git_repository_workdir");
    _git_repository_set_workdir = (int (*)(
                                           git_repository *repo, const char *workdir, int update_gitlink)) dlsym(result, "git_repository_set_workdir");
    _git_repository_is_bare = (int (*)(git_repository *repo)) dlsym(result, "git_repository_is_bare");
    _git_repository_config = (int (*)(git_config **out, git_repository *repo)) dlsym(result, "git_repository_config");
    _git_repository_set_config = (void (*)(git_repository *repo, git_config *config)) dlsym(result, "git_repository_set_config");
    _git_repository_odb = (int (*)(git_odb **out, git_repository *repo)) dlsym(result, "git_repository_odb");
    _git_repository_set_odb = (void (*)(git_repository *repo, git_odb *odb)) dlsym(result, "git_repository_set_odb");
    _git_repository_index = (int (*)(git_index **out, git_repository *repo)) dlsym(result, "git_repository_index");
    _git_repository_set_index = (void (*)(git_repository *repo, git_index *index)) dlsym(result, "git_repository_set_index");
    _git_repository_message = (int (*)(char *out, size_t len, git_repository *repo)) dlsym(result, "git_repository_message");
    _git_repository_message_remove = (int (*)(git_repository *repo)) dlsym(result, "git_repository_message_remove");
    _git_repository_merge_cleanup = (int (*)(git_repository *repo)) dlsym(result, "git_repository_merge_cleanup");
    _git_repository_fetchhead_foreach = (int (*)(git_repository *repo,
	git_repository_fetchhead_foreach_cb callback,
                                                 void *payload)) dlsym(result, "git_repository_fetchhead_foreach");
    _git_repository_mergehead_foreach = (int (*)(git_repository *repo,
	git_repository_mergehead_foreach_cb callback,
                                                 void *payload)) dlsym(result, "git_repository_mergehead_foreach");
    _git_repository_hashfile = (int (*)(
    git_oid *out,
    git_repository *repo,
    const char *path,
    git_otype type,
    const char *as_path)) dlsym(result, "git_repository_hashfile");
    _git_repository_set_head = (int (*)(
	git_repository* repo,
	const char* refname)) dlsym(result, "git_repository_set_head");
    _git_repository_set_head_detached = (int (*)(
	git_repository* repo,
	const git_oid* commitish)) dlsym(result, "git_repository_set_head_detached");
    _git_repository_detach_head = (int (*)(
                                           git_repository* repo)) dlsym(result, "git_repository_detach_head");
    _git_repository_state = (int (*)(git_repository *repo)) dlsym(result, "git_repository_state");


    return Rcpp::LogicalVector::create(true);
    END_RCPP
}
