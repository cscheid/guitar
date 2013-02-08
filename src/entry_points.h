#pragma once

#include <RcppCommon.h>
#include <Rcpp.h>
#include <git2.h>

/******************************************************************************/
// entry point declarations

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

// reference

extern void (*_git_reference_free)(git_reference *ref);

// index

extern int (*_git_index_open)(git_index **out, const char *index_path);
extern int (*_git_index_new)(git_index **out);
extern void (*_git_index_free)(git_index *index);
extern git_repository * (*_git_index_owner)(const git_index *index);
extern unsigned int (*_git_index_caps)(const git_index *index);
extern int (*_git_index_set_caps)(git_index *index, unsigned int caps);
extern int (*_git_index_read)(git_index *index);
extern int (*_git_index_write)(git_index *index);
extern int (*_git_index_read_tree)(git_index *index, const git_tree *tree);
extern int (*_git_index_write_tree)(git_oid *out, git_index *index);
extern int (*_git_index_write_tree_to)(git_oid *out, git_index *index, git_repository *repo);
extern size_t (*_git_index_entrycount)(const git_index *index);
extern void (*_git_index_clear)(git_index *index);
extern const git_index_entry * (*_git_index_get_byindex)(
	git_index *index, size_t n);
extern const git_index_entry * (*_git_index_get_bypath)(
	git_index *index, const char *path, int stage);
extern int (*_git_index_remove)(git_index *index, const char *path, int stage);
extern int (*_git_index_remove_directory)(
	git_index *index, const char *dir, int stage);
extern int (*_git_index_add)(git_index *index, const git_index_entry *source_entry);
extern int (*_git_index_entry_stage)(const git_index_entry *entry);
extern int (*_git_index_add_bypath)(git_index *index, const char *path);
extern int (*_git_index_remove_bypath)(git_index *index, const char *path);
extern int (*_git_index_find)(size_t *at_pos, git_index *index, const char *path);
extern int (*_git_index_conflict_add)(
   git_index *index,
	const git_index_entry *ancestor_entry,
	const git_index_entry *our_entry,
	const git_index_entry *their_entry);
extern int (*_git_index_conflict_get)(git_index_entry **ancestor_out, git_index_entry **our_out, git_index_entry **their_out, git_index *index, const char *path);
extern int (*_git_index_conflict_remove)(git_index *index, const char *path);
extern void (*_git_index_conflict_cleanup)(git_index *index);
extern int (*_git_index_has_conflicts)(const git_index *index);
extern unsigned int (*_git_index_reuc_entrycount)(git_index *index);
extern int (*_git_index_reuc_find)(size_t *at_pos, git_index *index, const char *path);
extern const git_index_reuc_entry * (*_git_index_reuc_get_bypath)(git_index *index, const char *path);
extern const git_index_reuc_entry * (*_git_index_reuc_get_byindex)(git_index *index, size_t n);
extern int (*_git_index_reuc_add)(git_index *index, const char *path,
	int ancestor_mode, git_oid *ancestor_id,
	int our_mode, git_oid *our_id,
	int their_mode, git_oid *their_id);
extern int (*_git_index_reuc_remove)(git_index *index, size_t n);

RcppExport SEXP load_library();
