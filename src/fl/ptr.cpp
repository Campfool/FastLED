#include "fl/ptr.h"

#include "fl/namespace.h"

namespace fl {

Referent::Referent() : mRefCount(0) {}
Referent::~Referent() = default;
void Referent::ref() const { mRefCount++; }

int Referent::ref_count() const { return mRefCount; }

void Referent::unref() const {
    if (--mRefCount == 0) {
        if (mWeakPtr) {
            mWeakPtr->setReferent(nullptr);
            mWeakPtr.reset();
        }
        destroy();
    }
}

void Referent::destroy() const { delete this; }

Referent::Referent(const Referent &) = default;
Referent &Referent::operator=(const Referent &) = default;
Referent::Referent(Referent &&) = default;
Referent &Referent::operator=(Referent &&) = default;

} // namespace fl
