#include "tag.h"
#include "entry_points.h"
#include "oid.h"

/******************************************************************************/

static void _git_tag_free(git_tag *tag)
{
    git_object_free((git_object*) tag);
}

Tag::Tag(git_tag *_tag)
{
    tag = boost::shared_ptr<git_tag>(_tag, _git_tag_free);
}

Rcpp::Reference Tag::id()
{
    return OID::create(git_tag_id(tag.get()));
}

Rcpp::Reference Tag::target_id()
{
    return OID::create(git_tag_target_id(tag.get()));
}

std::string Tag::message()
{
    return std::string(git_tag_message(tag.get()));
}

std::string Tag::name()
{
    return std::string(git_tag_name(tag.get()));
}

SEXP Tag::peel()
{
    BEGIN_RCPP
    git_object *result;
    int err = git_tag_peel(&result, tag.get());
    if (err)
        throw Rcpp::exception("object lookup failed");
    return object_to_sexp(result);
    END_RCPP
}

SEXP Tag::tagger()
{
    return Signature::create(git_tag_tagger(tag.get()));
}

SEXP Tag::target()
{
    BEGIN_RCPP
    git_object *result;
    int err = git_tag_target(&result, tag.get());
    if (err)
        throw Rcpp::exception("object lookup failed");
    return object_to_sexp(result);
    END_RCPP
}

int Tag::target_type()
{
    return git_tag_target_type(tag.get());
}

RCPP_MODULE(guitar_tag) {
    using namespace Rcpp;
    class_<Tag>("Tag")
        .method("id", &Tag::id)
        .method("message", &Tag::message)
        .method("name", &Tag::name)
        .method("peel", &Tag::peel)
        .method("tagger", &Tag::tagger)
        .method("target", &Tag::target)
        .method("target_id", &Tag::target_id)
        .method("target_type", &Tag::target_type)
        ;
}
