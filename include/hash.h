#ifndef DIFFERENTIATOR_HASH_H
#define DIFFERENTIATOR_HASH_H

#include <cstddef>

typedef size_t hash_t;

hash_t qhash(const void *const buffer, const size_t buffer_bytes);

#endif // DIFFERENTIATOR_HASH_H
