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
    /**
     * @brief Get the value of a key.
     *
     * @param key
     * @param value value address
     * @return The status of current operation.
     */
    virtual KVStatus Get(const Key &key, Value *val) = 0;
    /**
     * @brief Set the value of a key.
     *
     * @param key
     * @param val the value to be set.
     */
    virtual void Set(const Key &key, const Value &val) = 0;
    virtual ~KVStore() = default;
};

}  // namespace trivial

#endif