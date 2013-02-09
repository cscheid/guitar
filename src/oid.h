#pragma once

#include "guitar.h"

/******************************************************************************/

class OID: public CPPWrapperObjectTraits<OID, git_oid>
{
public:
    OID();
    explicit OID(std::string str);
    explicit OID(const git_oid *other_oid);

    std::string fmt();

    operator git_oid *() { return &oid; }
    operator const git_oid *() const { return unwrap(); }
    const git_oid *unwrap() const { return &oid; }

protected:
    git_oid oid;
};
