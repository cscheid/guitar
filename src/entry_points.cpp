#include "entry_points.h"
#include <dlfcn.h>
#include <cstdio>
#include <string>
#include <git2.h>

/******************************************************************************/
// entry point definitions

static void *dlsym_warn(void *dll, const char *entry_point)
{
    void *result = dlsym(dll, entry_point);
    if (!result) {
        fprintf(stderr, "Could not locate entry point %s\n", entry_point);
    }
    return result;
}

// repository

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

// reference

int (*_git_reference_lookup)(git_reference **out, git_repository *repo, const char *name);
int (*_git_reference_name_to_id)(
	git_oid *out, git_repository *repo, const char *name);
int (*_git_reference_symbolic_create)(git_reference **out, git_repository *repo, const char *name, const char *target, int force);
int (*_git_reference_create)(git_reference **out, git_repository *repo, const char *name, const git_oid *id, int force);
const git_oid * (*_git_reference_target)(const git_reference *ref);
const char * (*_git_reference_symbolic_target)(const git_reference *ref);
git_ref_t (*_git_reference_type)(const git_reference *ref);
const char * (*_git_reference_name)(const git_reference *ref);
int (*_git_reference_resolve)(git_reference **out, const git_reference *ref);
git_repository * (*_git_reference_owner)(const git_reference *ref);
int (*_git_reference_symbolic_set_target)(git_reference *ref, const char *target);
int (*_git_reference_set_target)(git_reference *ref, const git_oid *id);
int (*_git_reference_rename)(git_reference *ref, const char *name, int force);
int (*_git_reference_delete)(git_reference *ref);
int (*_git_reference_packall)(git_repository *repo);
int (*_git_reference_list)(git_strarray *array, git_repository *repo, unsigned int list_flags);int (*_git_reference_foreach)(
	git_repository *repo,
	unsigned int list_flags,
	git_reference_foreach_cb callback,
	void *payload);
int (*_git_reference_is_packed)(git_reference *ref);
int (*_git_reference_reload)(git_reference *ref);
void (*_git_reference_free)(git_reference *ref);
int (*_git_reference_cmp)(git_reference *ref1, git_reference *ref2);
int (*_git_reference_foreach_glob)(
	git_repository *repo,
	const char *glob,
	unsigned int list_flags,
	git_reference_foreach_cb callback,
	void *payload);
int (*_git_reference_has_log)(git_reference *ref);
int (*_git_reference_is_branch)(git_reference *ref);
int (*_git_reference_is_remote)(git_reference *ref);
int (*_git_reference_normalize_name)(
	char *buffer_out,
	size_t buffer_size,
	const char *name,
	unsigned int flags);
int (*_git_reference_peel)(
	git_object **out,
	git_reference *ref,
	git_otype type);
int (*_git_reference_is_valid_name)(const char *refname);

// index

int (*_git_index_open)(git_index **out, const char *index_path);
int (*_git_index_new)(git_index **out);
void (*_git_index_free)(git_index *index);
git_repository * (*_git_index_owner)(const git_index *index);
unsigned int (*_git_index_caps)(const git_index *index);
int (*_git_index_set_caps)(git_index *index, unsigned int caps);
int (*_git_index_read)(git_index *index);
int (*_git_index_write)(git_index *index);
int (*_git_index_read_tree)(git_index *index, const git_tree *tree);
int (*_git_index_write_tree)(git_oid *out, git_index *index);
int (*_git_index_write_tree_to)(git_oid *out, git_index *index, git_repository *repo);
size_t (*_git_index_entrycount)(const git_index *index);
void (*_git_index_clear)(git_index *index);
const git_index_entry * (*_git_index_get_byindex)(
	git_index *index, size_t n);
const git_index_entry * (*_git_index_get_bypath)(
	git_index *index, const char *path, int stage);
int (*_git_index_remove)(git_index *index, const char *path, int stage);
int (*_git_index_remove_directory)(
	git_index *index, const char *dir, int stage);
int (*_git_index_add)(git_index *index, const git_index_entry *source_entry);
int (*_git_index_entry_stage)(const git_index_entry *entry);
int (*_git_index_add_bypath)(git_index *index, const char *path);
int (*_git_index_remove_bypath)(git_index *index, const char *path);
int (*_git_index_find)(size_t *at_pos, git_index *index, const char *path);
int (*_git_index_conflict_add)(
   git_index *index,
	const git_index_entry *ancestor_entry,
	const git_index_entry *our_entry,
	const git_index_entry *their_entry);
int (*_git_index_conflict_get)(git_index_entry **ancestor_out, git_index_entry **our_out, git_index_entry **their_out, git_index *index, const char *path);
int (*_git_index_conflict_remove)(git_index *index, const char *path);
void (*_git_index_conflict_cleanup)(git_index *index);
int (*_git_index_has_conflicts)(const git_index *index);
unsigned int (*_git_index_reuc_entrycount)(git_index *index);
int (*_git_index_reuc_find)(size_t *at_pos, git_index *index, const char *path);
const git_index_reuc_entry * (*_git_index_reuc_get_bypath)(git_index *index, const char *path);
const git_index_reuc_entry * (*_git_index_reuc_get_byindex)(git_index *index, size_t n);
int (*_git_index_reuc_add)(git_index *index, const char *path,
	int ancestor_mode, git_oid *ancestor_id,
	int our_mode, git_oid *our_id,
	int their_mode, git_oid *their_id);
int (*_git_index_reuc_remove)(git_index *index, size_t n);

// oid

int (*_git_oid_fromstr)(git_oid *out, const char *str);
int (*_git_oid_fromstrn)(git_oid *out, const char *str, size_t length);
void (*_git_oid_fromraw)(git_oid *out, const unsigned char *raw);
void (*_git_oid_fmt)(char *out, const git_oid *id);
void (*_git_oid_pathfmt)(char *out, const git_oid *id);
char * (*_git_oid_allocfmt)(const git_oid *id);
char * (*_git_oid_tostr)(char *out, size_t n, const git_oid *id);
void (*_git_oid_cpy)(git_oid *out, const git_oid *src);
int (*_git_oid_ncmp)(const git_oid *a, const git_oid *b, size_t len);
int (*_git_oid_streq)(const git_oid *id, const char *str);
int (*_git_oid_iszero)(const git_oid *id);
git_oid_shorten * (*_git_oid_shorten_new)(size_t min_length);
int (*_git_oid_shorten_add)(git_oid_shorten *os, const char *text_id);
void (*_git_oid_shorten_free)(git_oid_shorten *os);

// strarray

void (*_git_strarray_free)(git_strarray *array);
int (*_git_strarray_copy)(git_strarray *tgt, const git_strarray *src);

// odb

int (*_git_odb_new)(git_odb **out);
int (*_git_odb_open)(git_odb **out, const char *objects_dir);
int (*_git_odb_add_backend)(git_odb *odb, git_odb_backend *backend, int priority);
int (*_git_odb_add_alternate)(git_odb *odb, git_odb_backend *backend, int priority);
int (*_git_odb_add_disk_alternate)(git_odb *odb, const char *path);
void (*_git_odb_free)(git_odb *db);
int (*_git_odb_read)(git_odb_object **out, git_odb *db, const git_oid *id);
int (*_git_odb_read_prefix)(git_odb_object **out, git_odb *db, const git_oid *short_id, size_t len);
int (*_git_odb_read_header)(size_t *len_out, git_otype *type_out, git_odb *db, const git_oid *id);
int (*_git_odb_exists)(git_odb *db, const git_oid *id);
int (*_git_odb_refresh)(struct git_odb *db);
int (*_git_odb_foreach)(git_odb *db, git_odb_foreach_cb cb, void *payload);
int (*_git_odb_write)(git_oid *out, git_odb *odb, const void *data, size_t len, git_otype type);
int (*_git_odb_open_wstream)(git_odb_stream **out, git_odb *db, size_t size, git_otype type);
int (*_git_odb_open_rstream)(git_odb_stream **out, git_odb *db, const git_oid *oid);
int (*_git_odb_write_pack)(
 git_odb_writepack **out,
 git_odb *db,
 git_transfer_progress_callback progress_cb,
 void *progress_payload);
int (*_git_odb_hash)(git_oid *out, const void *data, size_t len, git_otype type);
int (*_git_odb_hashfile)(git_oid *out, const char *path, git_otype type);
void (*_git_odb_object_free)(git_odb_object *object);

// odb_object

const git_oid * (*_git_odb_object_id)(git_odb_object *object);
const void * (*_git_odb_object_data)(git_odb_object *object);
size_t (*_git_odb_object_size)(git_odb_object *object);
git_otype (*_git_odb_object_type)(git_odb_object *object);

// object

int (*_git_object_lookup)(
   git_object **object,
   git_repository *repo,
   const git_oid *id,
   git_otype type);
int (*_git_object_lookup_prefix)(
   git_object **object_out,
   git_repository *repo,
   const git_oid *id,
   size_t len,
   git_otype type);
const git_oid * (*_git_object_id)(const git_object *obj);
git_otype (*_git_object_type)(const git_object *obj);
git_repository * (*_git_object_owner)(const git_object *obj);
void (*_git_object_free)(git_object *object);
const char * (*_git_object_type2string)(git_otype type);
git_otype (*_git_object_string2type)(const char *str);
int (*_git_object_typeisloose)(git_otype type);
size_t (*_git_object__size)(git_otype type);
int (*_git_object_peel)(
	git_object **peeled,
	const git_object *object,
	git_otype target_type);

const char * (*_git_commit_message_encoding)(const git_commit *commit);
const char * (*_git_commit_message)(const git_commit *commit);
git_time_t (*_git_commit_time)(const git_commit *commit);
int (*_git_commit_time_offset)(const git_commit *commit);
const git_signature * (*_git_commit_committer)(const git_commit *commit);
const git_signature * (*_git_commit_author)(const git_commit *commit);
int (*_git_commit_tree)(git_tree **tree_out, const git_commit *commit);
const git_oid * (*_git_commit_tree_id)(const git_commit *commit);
unsigned int (*_git_commit_parentcount)(const git_commit *commit);
int (*_git_commit_parent)(git_commit **out, git_commit *commit, unsigned int n);
const git_oid * (*_git_commit_parent_id)(git_commit *commit, unsigned int n);
int (*_git_commit_nth_gen_ancestor)(git_commit **ancestor,
                                    const git_commit *commit,
                                    unsigned int n);
int (*_git_commit_create)(
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

const git_oid * (*_git_tree_id)(const git_tree *tree);
git_repository * (*_git_tree_owner)(const git_tree *tree);
size_t (*_git_tree_entrycount)(const git_tree *tree);
const git_tree_entry * (*_git_tree_entry_byname)(
	git_tree *tree, const char *filename);
const git_tree_entry * (*_git_tree_entry_byindex)(
	git_tree *tree, size_t idx);
const git_tree_entry * (*_git_tree_entry_byoid)(
	const git_tree *tree, const git_oid *oid);
int (*_git_tree_entry_bypath)(
	git_tree_entry **out,
	git_tree *root,
	const char *path);
git_tree_entry * (*_git_tree_entry_dup)(const git_tree_entry *entry);
void (*_git_tree_entry_free)(git_tree_entry *entry);
const char * (*_git_tree_entry_name)(const git_tree_entry *entry);
const git_oid * (*_git_tree_entry_id)(const git_tree_entry *entry);
git_otype (*_git_tree_entry_type)(const git_tree_entry *entry);
git_filemode_t (*_git_tree_entry_filemode)(const git_tree_entry *entry);
int (*_git_tree_entry_cmp)(const git_tree_entry *e1, const git_tree_entry *e2);
int (*_git_tree_entry_to_object)(
	git_object **object_out,
	git_repository *repo,
	const git_tree_entry *entry);
int (*_git_treebuilder_create)(
	git_treebuilder **out, const git_tree *source);
void (*_git_treebuilder_clear)(git_treebuilder *bld);
unsigned int (*_git_treebuilder_entrycount)(git_treebuilder *bld);
void (*_git_treebuilder_free)(git_treebuilder *bld);
const git_tree_entry * (*_git_treebuilder_get)(
	git_treebuilder *bld, const char *filename);
int (*_git_treebuilder_insert)(
	const git_tree_entry **out,
	git_treebuilder *bld,
	const char *filename,
	const git_oid *id,
	git_filemode_t filemode);
int (*_git_treebuilder_remove)(
	git_treebuilder *bld, const char *filename);
void (*_git_treebuilder_filter)(
	git_treebuilder *bld,
	git_treebuilder_filter_cb filter,
	void *payload);
int (*_git_treebuilder_write)(
	git_oid *id, git_repository *repo, git_treebuilder *bld);
int (*_git_tree_walk)(
	const git_tree *tree,
	git_treewalk_mode mode,
	git_treewalk_cb callback,
	void *payload);

// blob

const void * (*_git_blob_rawcontent)(const git_blob *blob);
git_off_t (*_git_blob_rawsize)(const git_blob *blob);
int (*_git_blob_create_fromworkdir)(git_oid *id, git_repository *repo, const char *relative_path);
int (*_git_blob_create_fromdisk)(git_oid *id, git_repository *repo, const char *path);
int (*_git_blob_create_fromchunks)(
 git_oid *id,
 git_repository *repo,
 const char *hintpath,
 git_blob_chunk_cb callback,
 void *payload);
int (*_git_blob_create_frombuffer)(git_oid *oid, git_repository *repo, const void *buffer, size_t len);
int (*_git_blob_is_binary)(git_blob *blob);

// tag

const git_oid * (*_git_tag_id)(const git_tag *tag);
int (*_git_tag_target)(git_object **target_out, const git_tag *tag);
const git_oid * (*_git_tag_target_id)(const git_tag *tag);
git_otype (*_git_tag_target_type)(const git_tag *tag);
const char * (*_git_tag_name)(const git_tag *tag);
const git_signature * (*_git_tag_tagger)(const git_tag *tag);
const char * (*_git_tag_message)(const git_tag *tag);
int (*_git_tag_create)(
                       git_oid *oid,
                       git_repository *repo,
                       const char *tag_name,
                       const git_object *target,
                       const git_signature *tagger,
                       const char *message,
                       int force);
int (*_git_tag_create_frombuffer)(
                                  git_oid *oid,
                                  git_repository *repo,
                                  const char *buffer,
                                  int force);
int (*_git_tag_create_lightweight)(
                                   git_oid *oid,
                                   git_repository *repo,
                                   const char *tag_name,
                                   const git_object *target,
                                   int force);
int (*_git_tag_delete)(
                       git_repository *repo,
                       const char *tag_name);
int (*_git_tag_list)(
                     git_strarray *tag_names,
                     git_repository *repo);
int (*_git_tag_list_match)(
                           git_strarray *tag_names,
                           const char *pattern,
                           git_repository *repo);
int (*_git_tag_foreach)(
                        git_repository *repo,
                        git_tag_foreach_cb callback,
                        void *payload);
int (*_git_tag_peel)(
                     git_object **tag_target_out,
                     const git_tag *tag);

/******************************************************************************/
// function 
SEXP load_library()
{
    BEGIN_RCPP

    void *result;
    result = dlopen("libgit2.dylib", RTLD_LAZY);
    if (!result) {
        result = dlopen("libgit2.so", RTLD_LAZY);
    }

    _git_repository_open = (int (*)(git_repository**, const char*)) dlsym_warn(result, "git_repository_open");

    if (!_git_repository_open) {
        return Rcpp::LogicalVector::create(false);
    }

    /**************************************************************************/
    // now we load all entry points..

    _git_repository_free = (void (*)(git_repository*)) dlsym_warn(result, "git_repository_free");
    _git_repository_open = (int (*)(git_repository **out, const char *path)) dlsym_warn(result, "git_repository_open");
    _git_repository_wrap_odb = (int (*)(git_repository **out, git_odb *odb)) dlsym_warn(result, "git_repository_wrap_odb");
    _git_repository_open_ext = (int (*)(
                                        git_repository **out,
                                        const char *path,
                                        unsigned int flags,
                                        const char *ceiling_dirs)) dlsym_warn(result, "git_repository_open_ext");
    _git_repository_free = (void (*)(git_repository *repo)) dlsym_warn(result, "git_repository_free");
    _git_repository_init = (int (*)(
                                    git_repository **out,
                                    const char *path,
                                    unsigned is_bare)) dlsym_warn(result, "git_repository_init");
    _git_repository_init_ext = (int (*)(
                                        git_repository **out,
                                        const char *repo_path,
                                        git_repository_init_options *opts)) dlsym_warn(result, "git_repository_init_ext");
    _git_repository_head = (int (*)(git_reference **out, git_repository *repo)) dlsym_warn(result, "git_repository_head");
    _git_repository_head_detached = (int (*)(git_repository *repo)) dlsym_warn(result, "git_repository_head_detached");
    _git_repository_head_orphan = (int (*)(git_repository *repo)) dlsym_warn(result, "git_repository_head_orphan");
    _git_repository_is_empty = (int (*)(git_repository *repo)) dlsym_warn(result, "git_repository_is_empty");
    _git_repository_path = (const char * (*)(git_repository *repo)) dlsym_warn(result, "git_repository_path");
    _git_repository_workdir = (const char * (*)(git_repository *repo)) dlsym_warn(result, "git_repository_workdir");
    _git_repository_set_workdir = (int (*)(
                                           git_repository *repo, const char *workdir, int update_gitlink)) dlsym_warn(result, "git_repository_set_workdir");
    _git_repository_is_bare = (int (*)(git_repository *repo)) dlsym_warn(result, "git_repository_is_bare");
    _git_repository_config = (int (*)(git_config **out, git_repository *repo)) dlsym_warn(result, "git_repository_config");
    _git_repository_set_config = (void (*)(git_repository *repo, git_config *config)) dlsym_warn(result, "git_repository_set_config");
    _git_repository_odb = (int (*)(git_odb **out, git_repository *repo)) dlsym_warn(result, "git_repository_odb");
    _git_repository_set_odb = (void (*)(git_repository *repo, git_odb *odb)) dlsym_warn(result, "git_repository_set_odb");
    _git_repository_index = (int (*)(git_index **out, git_repository *repo)) dlsym_warn(result, "git_repository_index");
    _git_repository_set_index = (void (*)(git_repository *repo, git_index *index)) dlsym_warn(result, "git_repository_set_index");
    _git_repository_message = (int (*)(char *out, size_t len, git_repository *repo)) dlsym_warn(result, "git_repository_message");
    _git_repository_message_remove = (int (*)(git_repository *repo)) dlsym_warn(result, "git_repository_message_remove");
    _git_repository_merge_cleanup = (int (*)(git_repository *repo)) dlsym_warn(result, "git_repository_merge_cleanup");
    _git_repository_fetchhead_foreach = (int (*)(git_repository *repo,
                                                 git_repository_fetchhead_foreach_cb callback,
                                                 void *payload)) dlsym_warn(result, "git_repository_fetchhead_foreach");
    _git_repository_mergehead_foreach = (int (*)(git_repository *repo,
                                                 git_repository_mergehead_foreach_cb callback,
                                                 void *payload)) dlsym_warn(result, "git_repository_mergehead_foreach");
    _git_repository_hashfile = (int (*)(
                                        git_oid *out,
                                        git_repository *repo,
                                        const char *path,
                                        git_otype type,
                                        const char *as_path)) dlsym_warn(result, "git_repository_hashfile");
    _git_repository_set_head = (int (*)(
                                        git_repository* repo,
                                        const char* refname)) dlsym_warn(result, "git_repository_set_head");
    _git_repository_set_head_detached = (int (*)(
                                                 git_repository* repo,
                                                 const git_oid* commitish)) dlsym_warn(result, "git_repository_set_head_detached");
    _git_repository_detach_head = (int (*)(
                                           git_repository* repo)) dlsym_warn(result, "git_repository_detach_head");
    _git_repository_state = (int (*)(git_repository *repo)) dlsym_warn(result, "git_repository_state");

    _git_index_open = (int (*)(git_index **out, const char *index_path)) dlsym_warn(result, "git_index_open");
    _git_index_new = (int (*)(git_index **out)) dlsym_warn(result, "git_index_new");
    _git_index_free = (void (*)(git_index *index)) dlsym_warn(result, "git_index_free");
    _git_index_owner = (git_repository * (*)(const git_index *index)) dlsym_warn(result, "git_index_owner");
    _git_index_caps = (unsigned int (*)(const git_index *index)) dlsym_warn(result, "git_index_caps");
    _git_index_set_caps = (int (*)(git_index *index, unsigned int caps)) dlsym_warn(result, "git_index_set_caps");
    _git_index_read = (int (*)(git_index *index)) dlsym_warn(result, "git_index_read");
    _git_index_write = (int (*)(git_index *index)) dlsym_warn(result, "git_index_write");
    _git_index_read_tree = (int (*)(git_index *index, const git_tree *tree)) dlsym_warn(result, "git_index_read_tree");
    _git_index_write_tree = (int (*)(git_oid *out, git_index *index)) dlsym_warn(result, "git_index_write_tree");
    _git_index_write_tree_to = (int (*)(git_oid *out, git_index *index, git_repository *repo)) dlsym_warn(result, "git_index_write_tree_to");
    _git_index_entrycount = (size_t (*)(const git_index *index)) dlsym_warn(result, "git_index_entrycount");
    _git_index_clear = (void (*)(git_index *index)) dlsym_warn(result, "git_index_clear");
    _git_index_get_byindex = (const git_index_entry * (*)(
                                                          git_index *index, size_t n)) dlsym_warn(result, "git_index_get_byindex");
    _git_index_get_bypath = (const git_index_entry * (*)(
                                                         git_index *index, const char *path, int stage)) dlsym_warn(result, "git_index_get_bypath");
    _git_index_remove = (int (*)(git_index *index, const char *path, int stage)) dlsym_warn(result, "git_index_remove");
    _git_index_remove_directory = (int (*)(
                                           git_index *index, const char *dir, int stage)) dlsym_warn(result, "git_index_remove_directory");
    _git_index_add = (int (*)(git_index *index, const git_index_entry *source_entry)) dlsym_warn(result, "git_index_add");
    _git_index_entry_stage = (int (*)(const git_index_entry *entry)) dlsym_warn(result, "git_index_entry_stage");
    _git_index_add_bypath = (int (*)(git_index *index, const char *path)) dlsym_warn(result, "git_index_add_bypath");
    _git_index_remove_bypath = (int (*)(git_index *index, const char *path)) dlsym_warn(result, "git_index_remove_bypath");
    _git_index_find = (int (*)(size_t *at_pos, git_index *index, const char *path)) dlsym_warn(result, "git_index_find");
    _git_index_conflict_add = (int (*)(
                                       git_index *index,
                                       const git_index_entry *ancestor_entry,
                                       const git_index_entry *our_entry,
                                       const git_index_entry *their_entry)) dlsym_warn(result, "git_index_conflict_add");
    _git_index_conflict_get = (int (*)(git_index_entry **ancestor_out, git_index_entry **our_out, git_index_entry **their_out, git_index *index, const char *path)) dlsym_warn(result, "git_index_conflict_get");
    _git_index_conflict_remove = (int (*)(git_index *index, const char *path)) dlsym_warn(result, "git_index_conflict_remove");
    _git_index_conflict_cleanup = (void (*)(git_index *index)) dlsym_warn(result, "git_index_conflict_cleanup");
    _git_index_has_conflicts = (int (*)(const git_index *index)) dlsym_warn(result, "git_index_has_conflicts");
    _git_index_reuc_entrycount = (unsigned int (*)(git_index *index)) dlsym_warn(result, "git_index_reuc_entrycount");
    _git_index_reuc_find = (int (*)(size_t *at_pos, git_index *index, const char *path)) dlsym_warn(result, "git_index_reuc_find");
    _git_index_reuc_get_bypath = (const git_index_reuc_entry * (*)(git_index *index, const char *path)) dlsym_warn(result, "git_index_reuc_get_bypath");
    _git_index_reuc_get_byindex = (const git_index_reuc_entry * (*)(git_index *index, size_t n)) dlsym_warn(result, "git_index_reuc_get_byindex");
    _git_index_reuc_add = (int (*)(git_index *index, const char *path,
                                   int ancestor_mode, git_oid *ancestor_id,
                                   int our_mode, git_oid *our_id,
                                   int their_mode, git_oid *their_id)) dlsym_warn(result, "git_index_reuc_add");
    _git_index_reuc_remove = (int (*)(git_index *index, size_t n)) dlsym_warn(result, "git_index_reuc_remove");

    _git_reference_lookup = (int (*)(git_reference **out, git_repository *repo, const char *name)) dlsym_warn(result, "git_reference_lookup");
    _git_reference_name_to_id = (int (*)(
                                         git_oid *out, git_repository *repo, const char *name)) dlsym_warn(result, "git_reference_name_to_id");
    _git_reference_symbolic_create = (int (*)(git_reference **out, git_repository *repo, const char *name, const char *target, int force)) dlsym_warn(result, "git_reference_symbolic_create");
    _git_reference_create = (int (*)(git_reference **out, git_repository *repo, const char *name, const git_oid *id, int force)) dlsym_warn(result, "git_reference_create");
    _git_reference_target = (const git_oid * (*)(const git_reference *ref)) dlsym_warn(result, "git_reference_target");
    _git_reference_symbolic_target = (const char * (*)(const git_reference *ref)) dlsym_warn(result, "git_reference_symbolic_target");
    _git_reference_type = (git_ref_t (*)(const git_reference *ref)) dlsym_warn(result, "git_reference_type");
    _git_reference_name = (const char * (*)(const git_reference *ref)) dlsym_warn(result, "git_reference_name");
    _git_reference_resolve = (int (*)(git_reference **out, const git_reference *ref)) dlsym_warn(result, "git_reference_resolve");
    _git_reference_owner = (git_repository * (*)(const git_reference *ref)) dlsym_warn(result, "git_reference_owner");
    _git_reference_symbolic_set_target = (int (*)(git_reference *ref, const char *target)) dlsym_warn(result, "git_reference_symbolic_set_target");
    _git_reference_set_target = (int (*)(git_reference *ref, const git_oid *id)) dlsym_warn(result, "git_reference_set_target");
    _git_reference_rename = (int (*)(git_reference *ref, const char *name, int force)) dlsym_warn(result, "git_reference_rename");
    _git_reference_delete = (int (*)(git_reference *ref)) dlsym_warn(result, "git_reference_delete");
    _git_reference_packall = (int (*)(git_repository *repo)) dlsym_warn(result, "git_reference_packall");
    _git_reference_list = (int (*)(git_strarray *array, git_repository *repo, unsigned int list_flags)) dlsym_warn(result, "git_reference_list");
    _git_reference_foreach = (int (*)(
                                      git_repository *repo,
                                      unsigned int list_flags,
                                      git_reference_foreach_cb callback,
                                      void *payload)) dlsym_warn(result, "git_reference_foreach");
    _git_reference_is_packed = (int (*)(git_reference *ref)) dlsym_warn(result, "git_reference_is_packed");
    _git_reference_reload = (int (*)(git_reference *ref)) dlsym_warn(result, "git_reference_reload");
    _git_reference_free = (void (*)(git_reference *ref)) dlsym_warn(result, "git_reference_free");
    _git_reference_cmp = (int (*)(git_reference *ref1, git_reference *ref2)) dlsym_warn(result, "git_reference_cmp");
    _git_reference_foreach_glob = (int (*)(
                                           git_repository *repo,
                                           const char *glob,
                                           unsigned int list_flags,
                                           git_reference_foreach_cb callback,
                                           void *payload)) dlsym_warn(result, "git_reference_foreach_glob");
    _git_reference_has_log = (int (*)(git_reference *ref)) dlsym_warn(result, "git_reference_has_log");
    _git_reference_is_branch = (int (*)(git_reference *ref)) dlsym_warn(result, "git_reference_is_branch");
    _git_reference_is_remote = (int (*)(git_reference *ref)) dlsym_warn(result, "git_reference_is_remote");
    _git_reference_normalize_name = (int (*)(
                                             char *buffer_out,
                                             size_t buffer_size,
                                             const char *name,
                                             unsigned int flags)) dlsym_warn(result, "git_reference_normalize_name");
    _git_reference_peel = (int (*)(
                                   git_object **out,
                                   git_reference *ref,
                                   git_otype type)) dlsym_warn(result, "git_reference_peel");
    _git_reference_is_valid_name = (int (*)(const char *refname)) dlsym_warn(result, "git_reference_is_valid_name");
    
    _git_oid_fromstr = (int (*)(git_oid *out, const char *str)) dlsym_warn(result, "git_oid_fromstr");
    _git_oid_fromstrn = (int (*)(git_oid *out, const char *str, size_t length)) dlsym_warn(result, "git_oid_fromstrn");
    _git_oid_fromraw = (void (*)(git_oid *out, const unsigned char *raw)) dlsym_warn(result, "git_oid_fromraw");
    _git_oid_fmt = (void (*)(char *out, const git_oid *id)) dlsym_warn(result, "git_oid_fmt");
    _git_oid_pathfmt = (void (*)(char *out, const git_oid *id)) dlsym_warn(result, "git_oid_pathfmt");
    _git_oid_allocfmt = (char * (*)(const git_oid *id)) dlsym_warn(result, "git_oid_allocfmt");
    _git_oid_tostr = (char * (*)(char *out, size_t n, const git_oid *id)) dlsym_warn(result, "git_oid_tostr");
    _git_oid_cpy = (void (*)(git_oid *out, const git_oid *src)) dlsym_warn(result, "git_oid_cpy");
    _git_oid_ncmp = (int (*)(const git_oid *a, const git_oid *b, size_t len)) dlsym_warn(result, "git_oid_ncmp");
    _git_oid_streq = (int (*)(const git_oid *id, const char *str)) dlsym_warn(result, "git_oid_streq");
    _git_oid_iszero = (int (*)(const git_oid *id)) dlsym_warn(result, "git_oid_iszero");
    _git_oid_shorten_new = (git_oid_shorten * (*)(size_t min_length)) dlsym_warn(result, "git_oid_shorten_new");
    _git_oid_shorten_add = (int (*)(git_oid_shorten *os, const char *text_id)) dlsym_warn(result, "git_oid_shorten_add");
    _git_oid_shorten_free = (void (*)(git_oid_shorten *os)) dlsym_warn(result, "git_oid_shorten_free");

    _git_strarray_free = (void (*)(git_strarray *array)) dlsym_warn(result, "git_strarray_free");
    _git_strarray_copy = (int (*)(git_strarray *tgt, const git_strarray *src)) dlsym_warn(result, "git_strarray_copy");

    _git_odb_new = (int (*)(git_odb **out)) dlsym_warn(result, "git_odb_new");
    _git_odb_open = (int (*)(git_odb **out, const char *objects_dir)) dlsym_warn(result, "git_odb_open");
    _git_odb_add_backend = (int (*)(git_odb *odb, git_odb_backend *backend, int priority)) dlsym_warn(result, "git_odb_add_backend");
    _git_odb_add_alternate = (int (*)(git_odb *odb, git_odb_backend *backend, int priority)) dlsym_warn(result, "git_odb_add_alternate");
    _git_odb_add_disk_alternate = (int (*)(git_odb *odb, const char *path)) dlsym_warn(result, "git_odb_add_disk_alternate");
    _git_odb_free = (void (*)(git_odb *db)) dlsym_warn(result, "git_odb_free");
    _git_odb_read = (int (*)(git_odb_object **out, git_odb *db, const git_oid *id)) dlsym_warn(result, "git_odb_read");
    _git_odb_read_prefix = (int (*)(git_odb_object **out, git_odb *db, const git_oid *short_id, size_t len)) dlsym_warn(result, "git_odb_read_prefix");
    _git_odb_read_header = (int (*)(size_t *len_out, git_otype *type_out, git_odb *db, const git_oid *id)) dlsym_warn(result, "git_odb_read_header");
    _git_odb_exists = (int (*)(git_odb *db, const git_oid *id)) dlsym_warn(result, "git_odb_exists");
    _git_odb_refresh = (int (*)(struct git_odb *db)) dlsym_warn(result, "git_odb_refresh");
    _git_odb_foreach = (int (*)(git_odb *db, git_odb_foreach_cb cb, void *payload)) dlsym_warn(result, "git_odb_foreach");
    _git_odb_write = (int (*)(git_oid *out, git_odb *odb, const void *data, size_t len, git_otype type)) dlsym_warn(result, "git_odb_write");
    _git_odb_open_wstream = (int (*)(git_odb_stream **out, git_odb *db, size_t size, git_otype type)) dlsym_warn(result, "git_odb_open_wstream");
    _git_odb_open_rstream = (int (*)(git_odb_stream **out, git_odb *db, const git_oid *oid)) dlsym_warn(result, "git_odb_open_rstream");
    _git_odb_write_pack = (int (*)(
                                   git_odb_writepack **out,
                                   git_odb *db,
                                   git_transfer_progress_callback progress_cb,
                                   void *progress_payload)) dlsym_warn(result, "git_odb_write_pack");
    _git_odb_hash = (int (*)(git_oid *out, const void *data, size_t len, git_otype type)) dlsym_warn(result, "git_odb_hash");
    _git_odb_hashfile = (int (*)(git_oid *out, const char *path, git_otype type)) dlsym_warn(result, "git_odb_hashfile");

    _git_odb_object_free = (void (*)(git_odb_object *object)) dlsym_warn(result, "git_odb_object_free");
    _git_odb_object_id = (const git_oid * (*)(git_odb_object *object)) dlsym_warn(result, "git_odb_object_id");
    _git_odb_object_data = (const void * (*)(git_odb_object *object)) dlsym_warn(result, "git_odb_object_data");
    _git_odb_object_size = (size_t (*)(git_odb_object *object)) dlsym_warn(result, "git_odb_object_size");
    _git_odb_object_type = (git_otype (*)(git_odb_object *object)) dlsym_warn(result, "git_odb_object_type");

    _git_object_lookup = (int (*)(
                                  git_object **object,
                                  git_repository *repo,
                                  const git_oid *id,
                                  git_otype type)) dlsym_warn(result, "git_object_lookup");
    _git_object_lookup_prefix = (int (*)(
                                         git_object **object_out,
                                         git_repository *repo,
                                         const git_oid *id,
                                         size_t len,
                                         git_otype type)) dlsym_warn(result, "git_object_lookup_prefix");
    _git_object_id = (const git_oid * (*)(const git_object *obj)) dlsym_warn(result, "git_object_id");
    _git_object_type = (git_otype (*)(const git_object *obj)) dlsym_warn(result, "git_object_type");
    _git_object_owner = (git_repository * (*)(const git_object *obj)) dlsym_warn(result, "git_object_owner");
    _git_object_free = (void (*)(git_object *object)) dlsym_warn(result, "git_object_free");
    _git_object_type2string = (const char * (*)(git_otype type)) dlsym_warn(result, "git_object_type2string");
    _git_object_string2type = (git_otype (*)(const char *str)) dlsym_warn(result, "git_object_string2type");
    _git_object_typeisloose = (int (*)(git_otype type)) dlsym_warn(result, "git_object_typeisloose");
    _git_object__size = (size_t (*)(git_otype type)) dlsym_warn(result, "git_object__size");
    _git_object_peel = (int (*)(
                                git_object **peeled,
                                const git_object *object,
                                git_otype target_type)) dlsym_warn(result, "git_object_peel");

    _git_commit_message_encoding = (const char * (*)(const git_commit *commit)) dlsym_warn(result, "git_commit_message_encoding");
    _git_commit_message = (const char * (*)(const git_commit *commit)) dlsym_warn(result, "git_commit_message");
    _git_commit_time = (git_time_t (*)(const git_commit *commit)) dlsym_warn(result, "git_commit_time");
    _git_commit_time_offset = (int (*)(const git_commit *commit)) dlsym_warn(result, "git_commit_time_offset");
    _git_commit_committer = (const git_signature * (*)(const git_commit *commit)) dlsym_warn(result, "git_commit_committer");
    _git_commit_author = (const git_signature * (*)(const git_commit *commit)) dlsym_warn(result, "git_commit_author");
    _git_commit_tree = (int (*)(git_tree **tree_out, const git_commit *commit)) dlsym_warn(result, "git_commit_tree");
    _git_commit_tree_id = (const git_oid * (*)(const git_commit *commit)) dlsym_warn(result, "git_commit_tree_id");
    _git_commit_parentcount = (unsigned int (*)(const git_commit *commit)) dlsym_warn(result, "git_commit_parentcount");
    _git_commit_parent = (int (*)(git_commit **out, git_commit *commit, unsigned int n)) dlsym_warn(result, "git_commit_parent");
    _git_commit_parent_id = (const git_oid * (*)(git_commit *commit, unsigned int n)) dlsym_warn(result, "git_commit_parent_id");
    _git_commit_nth_gen_ancestor = (int (*)(git_commit **ancestor,
                                            const git_commit *commit,
                                            unsigned int n)) dlsym_warn(result, "git_commit_nth_gen_ancestor");
    _git_commit_create = (int (*)(
                                  git_oid *id,
                                  git_repository *repo,
                                  const char *update_ref,
                                  const git_signature *author,
                                  const git_signature *committer,
                                  const char *message_encoding,
                                  const char *message,
                                  const git_tree *tree,
                                  int parent_count,
                                  const git_commit *parents[])) dlsym_warn(result, "git_commit_create");

    _git_tree_id = (const git_oid * (*)(const git_tree *tree)) dlsym_warn(result, "git_tree_id");
    _git_tree_owner = (git_repository * (*)(const git_tree *tree)) dlsym_warn(result, "git_tree_owner");
    _git_tree_entrycount = (size_t (*)(const git_tree *tree)) dlsym_warn(result, "git_tree_entrycount");
    _git_tree_entry_byname = (const git_tree_entry * (*)(
                                                         git_tree *tree, const char *filename)) dlsym_warn(result, "git_tree_entry_byname");
    _git_tree_entry_byindex = (const git_tree_entry * (*)(
                                                          git_tree *tree, size_t idx)) dlsym_warn(result, "git_tree_entry_byindex");
    _git_tree_entry_byoid = (const git_tree_entry * (*)(
                                                        const git_tree *tree, const git_oid *oid)) dlsym_warn(result, "git_tree_entry_byoid");
    _git_tree_entry_bypath = (int (*)(
                                      git_tree_entry **out,
                                      git_tree *root,
                                      const char *path)) dlsym_warn(result, "git_tree_entry_bypath");
    _git_tree_entry_dup = (git_tree_entry * (*)(const git_tree_entry *entry)) dlsym_warn(result, "git_tree_entry_dup");
    _git_tree_entry_free = (void (*)(git_tree_entry *entry)) dlsym_warn(result, "git_tree_entry_free");
    _git_tree_entry_name = (const char * (*)(const git_tree_entry *entry)) dlsym_warn(result, "git_tree_entry_name");
    _git_tree_entry_id = (const git_oid * (*)(const git_tree_entry *entry)) dlsym_warn(result, "git_tree_entry_id");
    _git_tree_entry_type = (git_otype (*)(const git_tree_entry *entry)) dlsym_warn(result, "git_tree_entry_type");
    _git_tree_entry_filemode = (git_filemode_t (*)(const git_tree_entry *entry)) dlsym_warn(result, "git_tree_entry_filemode");
    _git_tree_entry_cmp = (int (*)(const git_tree_entry *e1, const git_tree_entry *e2)) dlsym_warn(result, "git_tree_entry_cmp");
    _git_tree_entry_to_object = (int (*)(
                                         git_object **object_out,
                                         git_repository *repo,
                                         const git_tree_entry *entry)) dlsym_warn(result, "git_tree_entry_to_object");
    _git_treebuilder_create = (int (*)(
                                       git_treebuilder **out, const git_tree *source)) dlsym_warn(result, "git_treebuilder_create");
    _git_treebuilder_clear = (void (*)(git_treebuilder *bld)) dlsym_warn(result, "git_treebuilder_clear");
    _git_treebuilder_entrycount = (unsigned int (*)(git_treebuilder *bld)) dlsym_warn(result, "git_treebuilder_entrycount");
    _git_treebuilder_free = (void (*)(git_treebuilder *bld)) dlsym_warn(result, "git_treebuilder_free");
    _git_treebuilder_get = (const git_tree_entry * (*)(
                                                       git_treebuilder *bld, const char *filename)) dlsym_warn(result, "git_treebuilder_get");
    _git_treebuilder_insert = (int (*)(
                                       const git_tree_entry **out,
                                       git_treebuilder *bld,
                                       const char *filename,
                                       const git_oid *id,
                                       git_filemode_t filemode)) dlsym_warn(result, "git_treebuilder_insert");
    _git_treebuilder_remove = (int (*)(
                                       git_treebuilder *bld, const char *filename)) dlsym_warn(result, "git_treebuilder_remove");
    _git_treebuilder_filter = (void (*)(
                                        git_treebuilder *bld,
                                        git_treebuilder_filter_cb filter,
                                        void *payload)) dlsym_warn(result, "git_treebuilder_filter");
    _git_treebuilder_write = (int (*)(
                                      git_oid *id, git_repository *repo, git_treebuilder *bld)) dlsym_warn(result, "git_treebuilder_write");
    _git_tree_walk = (int (*)(
                              const git_tree *tree,
                              git_treewalk_mode mode,
                              git_treewalk_cb callback,
                              void *payload)) dlsym_warn(result, "git_tree_walk");

    _git_blob_rawcontent = (const void * (*)(const git_blob *blob)) dlsym_warn(result, "git_blob_rawcontent");
    _git_blob_rawsize = (git_off_t (*)(const git_blob *blob)) dlsym_warn(result, "git_blob_rawsize");
    _git_blob_create_fromworkdir = (int (*)(git_oid *id, git_repository *repo, const char *relative_path)) dlsym_warn(result, "git_blob_create_fromworkdir");
    _git_blob_create_fromdisk = (int (*)(git_oid *id, git_repository *repo, const char *path)) dlsym_warn(result, "git_blob_create_fromdisk");
    _git_blob_create_fromchunks = (int (*)(
                                           git_oid *id,
                                           git_repository *repo,
                                           const char *hintpath,
                                           git_blob_chunk_cb callback,
                                           void *payload)) dlsym_warn(result, "git_blob_create_fromchunks");
    _git_blob_create_frombuffer = (int (*)(git_oid *oid, git_repository *repo, const void *buffer, size_t len)) dlsym_warn(result, "git_blob_create_frombuffer");
    _git_blob_is_binary = (int (*)(git_blob *blob)) dlsym_warn(result, "git_blob_is_binary");

    _git_tag_id = (const git_oid * (*)(const git_tag *tag)) dlsym_warn(result, "git_tag_id");
    _git_tag_target = (int (*)(git_object **target_out, const git_tag *tag)) dlsym_warn(result, "git_tag_target");
    _git_tag_target_id = (const git_oid * (*)(const git_tag *tag)) dlsym_warn(result, "git_tag_target_id");
    _git_tag_target_type = (git_otype (*)(const git_tag *tag)) dlsym_warn(result, "git_tag_target_type");
    _git_tag_name = (const char * (*)(const git_tag *tag)) dlsym_warn(result, "git_tag_name");
    _git_tag_tagger = (const git_signature * (*)(const git_tag *tag)) dlsym_warn(result, "git_tag_tagger");
    _git_tag_message = (const char * (*)(const git_tag *tag)) dlsym_warn(result, "git_tag_message");
    _git_tag_create = (int (*)(
                               git_oid *oid,
                               git_repository *repo,
                               const char *tag_name,
                               const git_object *target,
                               const git_signature *tagger,
                               const char *message,
                               int force)) dlsym_warn(result, "git_tag_create");
    _git_tag_create_frombuffer = (int (*)(
                                          git_oid *oid,
                                          git_repository *repo,
                                          const char *buffer,
                                          int force)) dlsym_warn(result, "git_tag_create_frombuffer");
    _git_tag_create_lightweight = (int (*)(
                                           git_oid *oid,
                                           git_repository *repo,
                                           const char *tag_name,
                                           const git_object *target,
                                           int force)) dlsym_warn(result, "git_tag_create_lightweight");
    _git_tag_delete = (int (*)(
                               git_repository *repo,
                               const char *tag_name)) dlsym_warn(result, "git_tag_delete");
    _git_tag_list = (int (*)(
                             git_strarray *tag_names,
                             git_repository *repo)) dlsym_warn(result, "git_tag_list");
    _git_tag_list_match = (int (*)(
                                   git_strarray *tag_names,
                                   const char *pattern,
                                   git_repository *repo)) dlsym_warn(result, "git_tag_list_match");
    _git_tag_foreach = (int (*)(
                                git_repository *repo,
                                git_tag_foreach_cb callback,
                                void *payload)) dlsym_warn(result, "git_tag_foreach");
    _git_tag_peel = (int (*)(
                             git_object **tag_target_out,
                             const git_tag *tag)) dlsym_warn(result, "git_tag_peel");

    return Rcpp::LogicalVector::create(true);
    END_RCPP
}
