//
// Created by ortur on 29.04.22.
//

#ifndef MY_LITTLE_PROGRAMMING_LANGUAGE_HASH_SET_H
#define MY_LITTLE_PROGRAMMING_LANGUAGE_HASH_SET_H

#include <forward_list>
#include <vector>
#include <algorithm>

namespace bycicle {


    template<typename Type, typename Hasher>
    class HashSet {
    public:
        using BucketList = std::forward_list<Type>;
    public:
        explicit HashSet(
                size_t num_buckets,
                const Hasher &hasher = {}
        ) : buckets(num_buckets) , hasher(hasher){}

        void Add(const Type &value) {
            if (Has(value))
                return;
            auto& bucket = GetBucket(value);
            bucket.push_front(value);
        }

        bool Has(const Type &value) const {
            const auto& bucket = GetBucket(value);
            return std::find(bucket.begin(), bucket.end(), value) != bucket.end();
        }

        void Erase(const Type &value) {
            if (Has(value)) {
                auto& bucket = GetBucket(value);
                bucket.remove(value);
            }
        }

        const BucketList &GetBucket(const Type &value) const {
            size_t value_hash = hasher(value);
            return buckets[value_hash % buckets.size()];
        }

        BucketList &GetBucket(const Type &value) {
            size_t value_hash = hasher(value);
            return buckets[value_hash % buckets.size()];
        }
    private:
        Hasher hasher;
        std::vector<BucketList> buckets;
    };


};

#endif //MY_LITTLE_PROGRAMMING_LANGUAGE_HASH_SET_H
