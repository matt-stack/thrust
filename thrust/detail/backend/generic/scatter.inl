/*
 *  Copyright 2008-2011 NVIDIA Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include <thrust/detail/config.h>
#include <thrust/detail/backend/generic/scatter.h>
#include <thrust/iterator/iterator_traits.h>
#include <thrust/functional.h>
#include <thrust/transform.h>
#include <thrust/iterator/permutation_iterator.h>

namespace thrust
{
namespace detail
{
namespace backend
{
namespace generic
{


template<typename InputIterator1,
         typename InputIterator2,
         typename RandomAccessIterator>
  void scatter(tag,
               InputIterator1 first,
               InputIterator1 last,
               InputIterator2 map,
               RandomAccessIterator output)
{
  thrust::transform(first,
                    last,
                    thrust::make_permutation_iterator(output, map),
                    thrust::identity<typename thrust::iterator_value<InputIterator1>::type>());
} // end scatter()


template<typename InputIterator1,
         typename InputIterator2,
         typename InputIterator3,
         typename RandomAccessIterator>
  void scatter_if(tag,
                  InputIterator1 first,
                  InputIterator1 last,
                  InputIterator2 map,
                  InputIterator3 stencil,
                  RandomAccessIterator output)
{
  // default predicate is identity
  typedef typename thrust::iterator_value<InputIterator3>::type StencilType;
  thrust::scatter_if(first, last, map, stencil, output, thrust::identity<StencilType>());
} // end scatter_if()


template<typename InputIterator1,
         typename InputIterator2,
         typename InputIterator3,
         typename RandomAccessIterator,
         typename Predicate>
  void scatter_if(tag,
                  InputIterator1 first,
                  InputIterator1 last,
                  InputIterator2 map,
                  InputIterator3 stencil,
                  RandomAccessIterator output,
                  Predicate pred)
{
  typedef typename thrust::iterator_value<InputIterator1>::type InputType;
  thrust::transform_if(first, last, stencil, thrust::make_permutation_iterator(output, map), thrust::identity<InputType>(), pred);
} // end scatter_if()


} // end namespace generic
} // end namespace backend
} // end namespace detail
} // end namespace thrust
