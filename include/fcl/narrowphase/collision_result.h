/*
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2011-2014, Willow Garage, Inc.
 *  Copyright (c) 2014-2016, Open Source Robotics Foundation
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of Open Source Robotics Foundation nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

/** @author Jia Pan */

#ifndef FCL_COLLISIONRESULT_H
#define FCL_COLLISIONRESULT_H

#include <set>
#include <vector>
#include "fcl/common/types.h"
#include "fcl/narrowphase/contact.h"
#include "fcl/narrowphase/cost_source.h"

namespace fcl
{

/// @brief collision result
template <typename S>
struct CollisionResult
{
private:
  /// @brief contact information
  std::vector<Contact<S>> contacts;

  /// @brief cost sources
  std::set<CostSource<S>> cost_sources;

public:
  Vector3<S> cached_gjk_guess;

public:
  CollisionResult();

  /// @brief add one contact into result structure
  void addContact(const Contact<S>& c);

  /// @brief add one cost source into result structure
  void addCostSource(const CostSource<S>& c, std::size_t num_max_cost_sources);

  /// @brief return binary collision result
  bool isCollision() const;

  /// @brief number of contacts found
  size_t numContacts() const;

  /// @brief number of cost sources found
  size_t numCostSources() const;

  /// @brief get the i-th contact calculated
  const Contact<S>& getContact(size_t i) const;

  /// @brief get all the contacts
  void getContacts(std::vector<Contact<S>>& contacts_);

  /// @brief get all the cost sources 
  void getCostSources(std::vector<CostSource<S>>& cost_sources_);

  /// @brief clear the results obtained
  void clear();
};

using CollisionResultf = CollisionResult<float>;
using CollisionResultd = CollisionResult<double>;

//============================================================================//
//                                                                            //
//                              Implementations                               //
//                                                                            //
//============================================================================//

//==============================================================================
template <typename S>
CollisionResult<S>::CollisionResult()
{
  // Do nothing
}

//==============================================================================
template <typename S>
void CollisionResult<S>::addContact(const Contact<S>& c)
{
  contacts.push_back(c);
}

//==============================================================================
template <typename S>
void CollisionResult<S>::addCostSource(
    const CostSource<S>& c, std::size_t num_max_cost_sources)
{
  cost_sources.insert(c);
  while (cost_sources.size() > num_max_cost_sources)
    cost_sources.erase(--cost_sources.end());
}

//==============================================================================
template <typename S>
bool CollisionResult<S>::isCollision() const
{
  return contacts.size() > 0;
}

//==============================================================================
template <typename S>
size_t CollisionResult<S>::numContacts() const
{
  return contacts.size();
}

//==============================================================================
template <typename S>
size_t CollisionResult<S>::numCostSources() const
{
  return cost_sources.size();
}

//==============================================================================
template <typename S>
const Contact<S>& CollisionResult<S>::getContact(size_t i) const
{
  if(i < contacts.size())
    return contacts[i];
  else
    return contacts.back();
}

//==============================================================================
template <typename S>
void CollisionResult<S>::getContacts(
    std::vector<Contact<S>>& contacts_)
{
  contacts_.resize(contacts.size());
  std::copy(contacts.begin(), contacts.end(), contacts_.begin());
}

//==============================================================================
template <typename S>
void CollisionResult<S>::getCostSources(
    std::vector<CostSource<S>>& cost_sources_)
{
  cost_sources_.resize(cost_sources.size());
  std::copy(cost_sources.begin(), cost_sources.end(), cost_sources_.begin());
}

//==============================================================================
template <typename S>
void CollisionResult<S>::clear()
{
  contacts.clear();
  cost_sources.clear();
}


} // namespace fcl

#endif
