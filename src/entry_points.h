#pragma once

#include <RcppCommon.h>
#include <Rcpp.h>
#include <git2.h>

/******************************************************************************/
// repository.h

extern int (*_git_repository_open)(git_repository **out, const char *path);
extern int (*_git_repository_wrap_odb)(git_repository **out, git_odb *odb);
extern int (*_git_repository_open_ext)(
	git_repository **out,
	const char *path,
	unsigned int flags,
	const char *ceiling_dirs);
extern void (*_git_repository_free)(git_repository *repo);
extern int (*_git_repository_init)(
	git_repository **out,
	const char *path,
	unsigned is_bare);
extern int (*_git_repository_init_ext)(
	git_repository **out,
	const char *repo_path,
	git_repository_init_options *opts);
extern int (*_git_repository_head)(git_reference **out, git_repository *repo);
extern int (*_git_repository_head_detached)(git_repository *repo);
extern int (*_git_repository_head_orphan)(git_repository *repo);
extern int (*_git_repository_is_empty)(git_repository *repo);
extern const char * (*_git_repository_path)(git_repository *repo);
extern const char * (*_git_repository_workdir)(git_repository *repo);
extern int (*_git_repository_set_workdir)(
	git_repository *repo, const char *workdir, int update_gitlink);
extern int (*_git_repository_is_bare)(git_repository *repo);
extern int (*_git_repository_config)(git_config **out, git_repository *repo);
extern void (*_git_repository_set_config)(git_repository *repo, git_config *config);
extern int (*_git_repository_odb)(git_odb **out, git_repository *repo);
extern void (*_git_repository_set_odb)(git_repository *repo, git_odb *odb);
extern int (*_git_repository_index)(git_index **out, git_repository *repo);
extern void (*_git_repository_set_index)(git_repository *repo, git_index *index);
extern int (*_git_repository_message)(char *out, size_t len, git_repository *repo);
extern int (*_git_repository_message_remove)(git_repository *repo);
extern int (*_git_repository_merge_cleanup)(git_repository *repo);
extern int (*_git_repository_fetchhead_foreach)(git_repository *repo,
	git_repository_fetchhead_foreach_cb callback,
	void *payload);
extern int (*_git_repository_mergehead_foreach)(git_repository *repo,
	git_repository_mergehead_foreach_cb callback,
	void *payload);
extern int (*_git_repository_hashfile)(
    git_oid *out,
    git_repository *repo,
    const char *path,
    git_otype type,
    const char *as_path);
extern int (*_git_repository_set_head)(
	git_repository* repo,
	const char* refname);
extern int (*_git_repository_set_head_detached)(
	git_repository* repo,
	const git_oid* commitish);
extern int (*_git_repository_detach_head)(
	git_repository* repo);
extern int (*_git_repository_state)(git_repository *repo);

/******************************************************************************/
// reference

extern void (*_git_reference_free)(git_reference *ref);

RcppExport SEXP load_library();
