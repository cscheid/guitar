#include "entry_points.h"
#include <dlfcn.h>
#include <cstdio>
#include <string>
#include <git2.h>

/******************************************************************************/
// entry point definitions

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

    _git_repository_open = (int (*)(git_repository**, const char*)) dlsym(result, "git_repository_open");

    if (!_git_repository_open) {
        return Rcpp::LogicalVector::create(false);
    }

    /**************************************************************************/
    // now we load all entry points..

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

    _git_index_open = (int (*)(git_index **out, const char *index_path)) dlsym(result, "git_index_open");
    _git_index_new = (int (*)(git_index **out)) dlsym(result, "git_index_new");
    _git_index_free = (void (*)(git_index *index)) dlsym(result, "git_index_free");
    _git_index_owner = (git_repository * (*)(const git_index *index)) dlsym(result, "git_index_owner");
    _git_index_caps = (unsigned int (*)(const git_index *index)) dlsym(result, "git_index_caps");
    _git_index_set_caps = (int (*)(git_index *index, unsigned int caps)) dlsym(result, "git_index_set_caps");
    _git_index_read = (int (*)(git_index *index)) dlsym(result, "git_index_read");
    _git_index_write = (int (*)(git_index *index)) dlsym(result, "git_index_write");
    _git_index_read_tree = (int (*)(git_index *index, const git_tree *tree)) dlsym(result, "git_index_read_tree");
    _git_index_write_tree = (int (*)(git_oid *out, git_index *index)) dlsym(result, "git_index_write_tree");
    _git_index_write_tree_to = (int (*)(git_oid *out, git_index *index, git_repository *repo)) dlsym(result, "git_index_write_tree_to");
    _git_index_entrycount = (size_t (*)(const git_index *index)) dlsym(result, "git_index_entrycount");
    _git_index_clear = (void (*)(git_index *index)) dlsym(result, "git_index_clear");
    _git_index_get_byindex = (const git_index_entry * (*)(
                                                          git_index *index, size_t n)) dlsym(result, "git_index_get_byindex");
    _git_index_get_bypath = (const git_index_entry * (*)(
                                                         git_index *index, const char *path, int stage)) dlsym(result, "git_index_get_bypath");
    _git_index_remove = (int (*)(git_index *index, const char *path, int stage)) dlsym(result, "git_index_remove");
    _git_index_remove_directory = (int (*)(
                                           git_index *index, const char *dir, int stage)) dlsym(result, "git_index_remove_directory");
    _git_index_add = (int (*)(git_index *index, const git_index_entry *source_entry)) dlsym(result, "git_index_add");
    _git_index_entry_stage = (int (*)(const git_index_entry *entry)) dlsym(result, "git_index_entry_stage");
    _git_index_add_bypath = (int (*)(git_index *index, const char *path)) dlsym(result, "git_index_add_bypath");
    _git_index_remove_bypath = (int (*)(git_index *index, const char *path)) dlsym(result, "git_index_remove_bypath");
    _git_index_find = (int (*)(size_t *at_pos, git_index *index, const char *path)) dlsym(result, "git_index_find");
    _git_index_conflict_add = (int (*)(
   git_index *index,
	const git_index_entry *ancestor_entry,
	const git_index_entry *our_entry,
   const git_index_entry *their_entry)) dlsym(result, "git_index_conflict_add");
    _git_index_conflict_get = (int (*)(git_index_entry **ancestor_out, git_index_entry **our_out, git_index_entry **their_out, git_index *index, const char *path)) dlsym(result, "git_index_conflict_get");
    _git_index_conflict_remove = (int (*)(git_index *index, const char *path)) dlsym(result, "git_index_conflict_remove");
    _git_index_conflict_cleanup = (void (*)(git_index *index)) dlsym(result, "git_index_conflict_cleanup");
    _git_index_has_conflicts = (int (*)(const git_index *index)) dlsym(result, "git_index_has_conflicts");
    _git_index_reuc_entrycount = (unsigned int (*)(git_index *index)) dlsym(result, "git_index_reuc_entrycount");
    _git_index_reuc_find = (int (*)(size_t *at_pos, git_index *index, const char *path)) dlsym(result, "git_index_reuc_find");
    _git_index_reuc_get_bypath = (const git_index_reuc_entry * (*)(git_index *index, const char *path)) dlsym(result, "git_index_reuc_get_bypath");
    _git_index_reuc_get_byindex = (const git_index_reuc_entry * (*)(git_index *index, size_t n)) dlsym(result, "git_index_reuc_get_byindex");
    _git_index_reuc_add = (int (*)(git_index *index, const char *path,
	int ancestor_mode, git_oid *ancestor_id,
	int our_mode, git_oid *our_id,
                                   int their_mode, git_oid *their_id)) dlsym(result, "git_index_reuc_add");
    _git_index_reuc_remove = (int (*)(git_index *index, size_t n)) dlsym(result, "git_index_reuc_remove");

    _git_reference_lookup = (int (*)(git_reference **out, git_repository *repo, const char *name)) dlsym(result, "git_reference_lookup");
    _git_reference_name_to_id = (int (*)(
                                         git_oid *out, git_repository *repo, const char *name)) dlsym(result, "git_reference_name_to_id");
    _git_reference_symbolic_create = (int (*)(git_reference **out, git_repository *repo, const char *name, const char *target, int force)) dlsym(result, "git_reference_symbolic_create");
    _git_reference_create = (int (*)(git_reference **out, git_repository *repo, const char *name, const git_oid *id, int force)) dlsym(result, "git_reference_create");
    _git_reference_target = (const git_oid * (*)(const git_reference *ref)) dlsym(result, "git_reference_target");
    _git_reference_symbolic_target = (const char * (*)(const git_reference *ref)) dlsym(result, "git_reference_symbolic_target");
    _git_reference_type = (git_ref_t (*)(const git_reference *ref)) dlsym(result, "git_reference_type");
    _git_reference_name = (const char * (*)(const git_reference *ref)) dlsym(result, "git_reference_name");
    _git_reference_resolve = (int (*)(git_reference **out, const git_reference *ref)) dlsym(result, "git_reference_resolve");
    _git_reference_owner = (git_repository * (*)(const git_reference *ref)) dlsym(result, "git_reference_owner");
    _git_reference_symbolic_set_target = (int (*)(git_reference *ref, const char *target)) dlsym(result, "git_reference_symbolic_set_target");
    _git_reference_set_target = (int (*)(git_reference *ref, const git_oid *id)) dlsym(result, "git_reference_set_target");
    _git_reference_rename = (int (*)(git_reference *ref, const char *name, int force)) dlsym(result, "git_reference_rename");
    _git_reference_delete = (int (*)(git_reference *ref)) dlsym(result, "git_reference_delete");
    _git_reference_packall = (int (*)(git_repository *repo)) dlsym(result, "git_reference_packall");
    _git_reference_list = (int (*)(git_strarray *array, git_repository *repo, unsigned int list_flags)) dlsym(result, "git_reference_list");
    _git_reference_foreach = (int (*)(
	git_repository *repo,
	unsigned int list_flags,
	git_reference_foreach_cb callback,
	void *payload)) dlsym(result, "git_reference_foreach");
    _git_reference_is_packed = (int (*)(git_reference *ref)) dlsym(result, "git_reference_is_packed");
    _git_reference_reload = (int (*)(git_reference *ref)) dlsym(result, "git_reference_reload");
    _git_reference_free = (void (*)(git_reference *ref)) dlsym(result, "git_reference_free");
    _git_reference_cmp = (int (*)(git_reference *ref1, git_reference *ref2)) dlsym(result, "git_reference_cmp");
    _git_reference_foreach_glob = (int (*)(
	git_repository *repo,
	const char *glob,
	unsigned int list_flags,
	git_reference_foreach_cb callback,
	void *payload)) dlsym(result, "git_reference_foreach_glob");
    _git_reference_has_log = (int (*)(git_reference *ref)) dlsym(result, "git_reference_has_log");
    _git_reference_is_branch = (int (*)(git_reference *ref)) dlsym(result, "git_reference_is_branch");
    _git_reference_is_remote = (int (*)(git_reference *ref)) dlsym(result, "git_reference_is_remote");
    _git_reference_normalize_name = (int (*)(
	char *buffer_out,
	size_t buffer_size,
	const char *name,
	unsigned int flags)) dlsym(result, "git_reference_normalize_name");
    _git_reference_peel = (int (*)(
	git_object **out,
	git_reference *ref,
	git_otype type)) dlsym(result, "git_reference_peel");
    _git_reference_is_valid_name = (int (*)(const char *refname)) dlsym(result, "git_reference_is_valid_name");
    
    _git_oid_fromstr = (int (*)(git_oid *out, const char *str)) dlsym(result, "git_oid_fromstr");
    _git_oid_fromstrn = (int (*)(git_oid *out, const char *str, size_t length)) dlsym(result, "git_oid_fromstrn");
    _git_oid_fromraw = (void (*)(git_oid *out, const unsigned char *raw)) dlsym(result, "git_oid_fromraw");
    _git_oid_fmt = (void (*)(char *out, const git_oid *id)) dlsym(result, "git_oid_fmt");
    _git_oid_pathfmt = (void (*)(char *out, const git_oid *id)) dlsym(result, "git_oid_pathfmt");
    _git_oid_allocfmt = (char * (*)(const git_oid *id)) dlsym(result, "git_oid_allocfmt");
    _git_oid_tostr = (char * (*)(char *out, size_t n, const git_oid *id)) dlsym(result, "git_oid_tostr");
    _git_oid_cpy = (void (*)(git_oid *out, const git_oid *src)) dlsym(result, "git_oid_cpy");
    _git_oid_ncmp = (int (*)(const git_oid *a, const git_oid *b, size_t len)) dlsym(result, "git_oid_ncmp");
    _git_oid_streq = (int (*)(const git_oid *id, const char *str)) dlsym(result, "git_oid_streq");
    _git_oid_iszero = (int (*)(const git_oid *id)) dlsym(result, "git_oid_iszero");
    _git_oid_shorten_new = (git_oid_shorten * (*)(size_t min_length)) dlsym(result, "git_oid_shorten_new");
    _git_oid_shorten_add = (int (*)(git_oid_shorten *os, const char *text_id)) dlsym(result, "git_oid_shorten_add");
    _git_oid_shorten_free = (void (*)(git_oid_shorten *os)) dlsym(result, "git_oid_shorten_free");

    _git_strarray_free = (void (*)(git_strarray *array)) dlsym(result, "git_strarray_free");
    _git_strarray_copy = (int (*)(git_strarray *tgt, const git_strarray *src)) dlsym(result, "git_strarray_copy");

    return Rcpp::LogicalVector::create(true);
    END_RCPP
}
