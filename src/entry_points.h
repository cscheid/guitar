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

extern int (*_git_reference_lookup)(git_reference **out, git_repository *repo, const char *name);
extern int (*_git_reference_name_to_id)(
	git_oid *out, git_repository *repo, const char *name);
extern int (*_git_reference_symbolic_create)(git_reference **out, git_repository *repo, const char *name, const char *target, int force);
extern int (*_git_reference_create)(git_reference **out, git_repository *repo, const char *name, const git_oid *id, int force);
extern const git_oid * (*_git_reference_target)(const git_reference *ref);
extern const char * (*_git_reference_symbolic_target)(const git_reference *ref);
extern git_ref_t (*_git_reference_type)(const git_reference *ref);
extern const char * (*_git_reference_name)(const git_reference *ref);
extern int (*_git_reference_resolve)(git_reference **out, const git_reference *ref);
extern git_repository * (*_git_reference_owner)(const git_reference *ref);
extern int (*_git_reference_symbolic_set_target)(git_reference *ref, const char *target);
extern int (*_git_reference_set_target)(git_reference *ref, const git_oid *id);
extern int (*_git_reference_rename)(git_reference *ref, const char *name, int force);
extern int (*_git_reference_delete)(git_reference *ref);
extern int (*_git_reference_packall)(git_repository *repo);
extern int (*_git_reference_list)(git_strarray *array, git_repository *repo, unsigned int list_flags);
extern int (*_git_reference_foreach)(
	git_repository *repo,
	unsigned int list_flags,
	git_reference_foreach_cb callback,
	void *payload);
extern int (*_git_reference_is_packed)(git_reference *ref);
extern int (*_git_reference_reload)(git_reference *ref);
extern void (*_git_reference_free)(git_reference *ref);
extern int (*_git_reference_cmp)(git_reference *ref1, git_reference *ref2);
extern int (*_git_reference_foreach_glob)(
	git_repository *repo,
	const char *glob,
	unsigned int list_flags,
	git_reference_foreach_cb callback,
	void *payload);
extern int (*_git_reference_has_log)(git_reference *ref);
extern int (*_git_reference_is_branch)(git_reference *ref);
extern int (*_git_reference_is_remote)(git_reference *ref);
extern int (*_git_reference_normalize_name)(
	char *buffer_out,
	size_t buffer_size,
	const char *name,
	unsigned int flags);
extern int (*_git_reference_peel)(
	git_object **out,
	git_reference *ref,
	git_otype type);
extern int (*_git_reference_is_valid_name)(const char *refname);

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

// oid

extern int (*_git_oid_fromstr)(git_oid *out, const char *str);
extern int (*_git_oid_fromstrn)(git_oid *out, const char *str, size_t length);
extern void (*_git_oid_fromraw)(git_oid *out, const unsigned char *raw);
extern void (*_git_oid_fmt)(char *out, const git_oid *id);
extern void (*_git_oid_pathfmt)(char *out, const git_oid *id);
extern char * (*_git_oid_allocfmt)(const git_oid *id);
extern char * (*_git_oid_tostr)(char *out, size_t n, const git_oid *id);
extern void (*_git_oid_cpy)(git_oid *out, const git_oid *src);
extern int (*_git_oid_ncmp)(const git_oid *a, const git_oid *b, size_t len);
extern int (*_git_oid_streq)(const git_oid *id, const char *str);
extern int (*_git_oid_iszero)(const git_oid *id);
extern git_oid_shorten * (*_git_oid_shorten_new)(size_t min_length);
extern int (*_git_oid_shorten_add)(git_oid_shorten *os, const char *text_id);
extern void (*_git_oid_shorten_free)(git_oid_shorten *os);

// strarray

extern void (*_git_strarray_free)(git_strarray *array);
extern int (*_git_strarray_copy)(git_strarray *tgt, const git_strarray *src);

// odb

extern int (*_git_odb_new)(git_odb **out);
extern int (*_git_odb_open)(git_odb **out, const char *objects_dir);
extern int (*_git_odb_add_backend)(git_odb *odb, git_odb_backend *backend, int priority);
extern int (*_git_odb_add_alternate)(git_odb *odb, git_odb_backend *backend, int priority);
extern int (*_git_odb_add_disk_alternate)(git_odb *odb, const char *path);
extern void (*_git_odb_free)(git_odb *db);
extern int (*_git_odb_read)(git_odb_object **out, git_odb *db, const git_oid *id);
extern int (*_git_odb_read_prefix)(git_odb_object **out, git_odb *db, const git_oid *short_id, size_t len);
extern int (*_git_odb_read_header)(size_t *len_out, git_otype *type_out, git_odb *db, const git_oid *id);
extern int (*_git_odb_exists)(git_odb *db, const git_oid *id);
extern int (*_git_odb_refresh)(struct git_odb *db);
extern int (*_git_odb_foreach)(git_odb *db, git_odb_foreach_cb cb, void *payload);
extern int (*_git_odb_write)(git_oid *out, git_odb *odb, const void *data, size_t len, git_otype type);
extern int (*_git_odb_open_wstream)(git_odb_stream **out, git_odb *db, size_t size, git_otype type);
extern int (*_git_odb_open_rstream)(git_odb_stream **out, git_odb *db, const git_oid *oid);
extern int (*_git_odb_write_pack)(
	git_odb_writepack **out,
	git_odb *db,
	git_transfer_progress_callback progress_cb,
	void *progress_payload);
extern int (*_git_odb_hash)(git_oid *out, const void *data, size_t len, git_otype type);
extern int (*_git_odb_hashfile)(git_oid *out, const char *path, git_otype type);

// odb_object

extern void (*_git_odb_object_free)(git_odb_object *object);
extern const git_oid * (*_git_odb_object_id)(git_odb_object *object);
extern const void * (*_git_odb_object_data)(git_odb_object *object);
extern size_t (*_git_odb_object_size)(git_odb_object *object);
extern git_otype (*_git_odb_object_type)(git_odb_object *object);

// object

extern int (*_git_object_lookup)(
   git_object **object,
   git_repository *repo,
   const git_oid *id,
   git_otype type);
extern int (*_git_object_lookup_prefix)(
   git_object **object_out,
   git_repository *repo,
   const git_oid *id,
   size_t len,
   git_otype type);
extern const git_oid * (*_git_object_id)(const git_object *obj);
extern git_otype (*_git_object_type)(const git_object *obj);
extern git_repository * (*_git_object_owner)(const git_object *obj);
extern void (*_git_object_free)(git_object *object);
extern const char * (*_git_object_type2string)(git_otype type);
extern git_otype (*_git_object_string2type)(const char *str);
extern int (*_git_object_typeisloose)(git_otype type);
extern size_t (*_git_object__size)(git_otype type);
extern int (*_git_object_peel)(
	git_object **peeled,
	const git_object *object,
	git_otype target_type);

// commit

extern const char * (*_git_commit_message_encoding)(const git_commit *commit);
extern const char * (*_git_commit_message)(const git_commit *commit);
extern git_time_t (*_git_commit_time)(const git_commit *commit);
extern int (*_git_commit_time_offset)(const git_commit *commit);
extern const git_signature * (*_git_commit_committer)(const git_commit *commit);
extern const git_signature * (*_git_commit_author)(const git_commit *commit);
extern int (*_git_commit_tree)(git_tree **tree_out, const git_commit *commit);
extern const git_oid * (*_git_commit_tree_id)(const git_commit *commit);
extern unsigned int (*_git_commit_parentcount)(const git_commit *commit);
extern int (*_git_commit_parent)(git_commit **out, git_commit *commit, unsigned int n);
extern const git_oid * (*_git_commit_parent_id)(git_commit *commit, unsigned int n);
extern int (*_git_commit_nth_gen_ancestor)(
	git_commit **ancestor,
	const git_commit *commit,
	unsigned int n);
extern int (*_git_commit_create)(
		git_oid *id,
		git_repository *repo,
		const char *update_ref,
		const git_signature *author,
		const git_signature *committer,
		const char *message_encoding,
		const char *message,
		const git_tree *tree,
		int parent_count,
		const git_commit *parents[]);

// tree

extern const git_oid * (*_git_tree_id)(const git_tree *tree);
extern git_repository * (*_git_tree_owner)(const git_tree *tree);
extern size_t (*_git_tree_entrycount)(const git_tree *tree);
extern const git_tree_entry * (*_git_tree_entry_byname)(
	git_tree *tree, const char *filename);
extern const git_tree_entry * (*_git_tree_entry_byindex)(
	git_tree *tree, size_t idx);
extern const git_tree_entry * (*_git_tree_entry_byoid)(
	const git_tree *tree, const git_oid *oid);
extern int (*_git_tree_entry_bypath)(
	git_tree_entry **out,
	git_tree *root,
	const char *path);
extern git_tree_entry * (*_git_tree_entry_dup)(const git_tree_entry *entry);
extern void (*_git_tree_entry_free)(git_tree_entry *entry);
extern const char * (*_git_tree_entry_name)(const git_tree_entry *entry);
extern const git_oid * (*_git_tree_entry_id)(const git_tree_entry *entry);
extern git_otype (*_git_tree_entry_type)(const git_tree_entry *entry);
extern git_filemode_t (*_git_tree_entry_filemode)(const git_tree_entry *entry);
extern int (*_git_tree_entry_cmp)(const git_tree_entry *e1, const git_tree_entry *e2);
extern int (*_git_tree_entry_to_object)(
	git_object **object_out,
	git_repository *repo,
	const git_tree_entry *entry);
extern int (*_git_treebuilder_create)(
	git_treebuilder **out, const git_tree *source);
extern void (*_git_treebuilder_clear)(git_treebuilder *bld);
extern unsigned int (*_git_treebuilder_entrycount)(git_treebuilder *bld);
extern void (*_git_treebuilder_free)(git_treebuilder *bld);
extern const git_tree_entry * (*_git_treebuilder_get)(
	git_treebuilder *bld, const char *filename);
extern int (*_git_treebuilder_insert)(
	const git_tree_entry **out,
	git_treebuilder *bld,
	const char *filename,
	const git_oid *id,
	git_filemode_t filemode);
extern int (*_git_treebuilder_remove)(
	git_treebuilder *bld, const char *filename);
extern void (*_git_treebuilder_filter)(
	git_treebuilder *bld,
	git_treebuilder_filter_cb filter,
	void *payload);
extern int (*_git_treebuilder_write)(
	git_oid *id, git_repository *repo, git_treebuilder *bld);
extern int (*_git_tree_walk)(
	const git_tree *tree,
	git_treewalk_mode mode,
	git_treewalk_cb callback,
	void *payload);

// blob

extern const void * (*_git_blob_rawcontent)(const git_blob *blob);
extern git_off_t (*_git_blob_rawsize)(const git_blob *blob);
extern int (*_git_blob_create_fromworkdir)(git_oid *id, git_repository *repo, const char *relative_path);
extern int (*_git_blob_create_fromdisk)(git_oid *id, git_repository *repo, const char *path);
extern int (*_git_blob_create_fromchunks)(
	git_oid *id,
	git_repository *repo,
	const char *hintpath,
	git_blob_chunk_cb callback,
	void *payload);
extern int (*_git_blob_create_frombuffer)(git_oid *oid, git_repository *repo, const void *buffer, size_t len);
extern int (*_git_blob_is_binary)(git_blob *blob);

// tag

extern const git_oid * (*_git_tag_id)(const git_tag *tag);
extern int (*_git_tag_target)(git_object **target_out, const git_tag *tag);
extern const git_oid * (*_git_tag_target_id)(const git_tag *tag);
extern git_otype (*_git_tag_target_type)(const git_tag *tag);
extern const char * (*_git_tag_name)(const git_tag *tag);
extern const git_signature * (*_git_tag_tagger)(const git_tag *tag);
extern const char * (*_git_tag_message)(const git_tag *tag);
extern int (*_git_tag_create)(
	git_oid *oid,
	git_repository *repo,
	const char *tag_name,
	const git_object *target,
	const git_signature *tagger,
	const char *message,
	int force);
extern int (*_git_tag_create_frombuffer)(
	git_oid *oid,
	git_repository *repo,
	const char *buffer,
	int force);
extern int (*_git_tag_create_lightweight)(
	git_oid *oid,
	git_repository *repo,
	const char *tag_name,
	const git_object *target,
	int force);
extern int (*_git_tag_delete)(
	git_repository *repo,
	const char *tag_name);
extern int (*_git_tag_list)(
	git_strarray *tag_names,
	git_repository *repo);
extern int (*_git_tag_list_match)(
	git_strarray *tag_names,
	const char *pattern,
	git_repository *repo);
extern int (*_git_tag_foreach)(
	git_repository *repo,
	git_tag_foreach_cb callback,
	void *payload);
extern int (*_git_tag_peel)(
	git_object **tag_target_out,
	const git_tag *tag);

// signature

extern int (*_git_signature_new)(git_signature **out, const char *name, const char *email, git_time_t time, int offset);
extern int (*_git_signature_now)(git_signature **out, const char *name, const char *email);
extern git_signature * (*_git_signature_dup)(const git_signature *sig);
extern void (*_git_signature_free)(git_signature *sig);

/******************************************************************************/

RcppExport SEXP load_library();
