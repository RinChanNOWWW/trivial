#ifndef KV_ITERATOR_H_
#define KV_ITERATOR_H_

#include "kv.h"

namespace trivial {

class KVIterator {
   public:
    using Key = KVStore::Key;
    using Value = KVStore::Value;

   public:
    /**
     * @brief Return if current position is valid.
     *
     * @return true if current position is valid
     * @return false if current position is not valid
     */
    virtual bool IsValid() const = 0;

    /**
     * @brief Change to the position whose key is equal to or greater than the
     * start_key.
     *
     * @param start_key the search key
     */

    virtual void Seek(const Key &start_key) = 0;
    /**
     * @brief Change to the position of the smallest key.
     *
     */
    virtual void SeekToFirst() = 0;

    /**
     * @brief Move to the smallest key which is greater than the current one.
     * REQUIRES: Valid()
     *
     */
    virtual void Next() = 0;

    /**
     * @brief Return the key at current position
     *
     * @return Key
     */
    virtual Key GetKey() const = 0;

    /**
     * @brief return the value at current position
     *
     * @return Value
     */
    virtual Value GetValue() const = 0;

    virtual ~KVIterator() = default;
};

}  // namespace trivial

#endif