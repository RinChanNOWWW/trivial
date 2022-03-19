#ifndef KV_H_
#define KV_H_

#include <string>

namespace trivial {

enum class KVStatus { OK, NOT_FOUND };

class KVStore {
   public:
    typedef std::string Key;
    typedef std::string Value;

   public:
    virtual KVStatus Get(const Key &key, Value *val) = 0;
    virtual void Set(const Key &key, const Value &val) = 0;
    virtual ~KVStore() = default;
};

}  // namespace trivial

#endif