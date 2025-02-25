#pragma once

namespace flexor::base
{

/**
 * In order to make templated operators work only for vectors, we give them all an empty base class.
 */
struct vector
{
};

/**
 * In order to make templated operators work only for matrices, we give them all an empty base
 * class.
 */
struct matrix
{
};

} // namespace flexor::base