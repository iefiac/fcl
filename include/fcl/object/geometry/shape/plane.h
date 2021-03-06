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

#ifndef FCL_SHAPE_PLANE_H
#define FCL_SHAPE_PLANE_H

#include "fcl/object/geometry/shape/shape_base.h"
#include "fcl/object/geometry/shape/compute_bv.h"
#include "fcl/math/bv/OBB.h"
#include "fcl/math/bv/RSS.h"
#include "fcl/math/bv/OBBRSS.h"
#include "fcl/math/bv/kDOP.h"
#include "fcl/math/bv/kIOS.h"

namespace fcl
{

/// @brief Infinite plane 
template <typename S_>
class Plane : public ShapeBase<S_>
{
public:

  using S = S_;

  /// @brief Construct a plane with normal direction and offset 
  Plane(const Vector3<S>& n, S d);
  
  /// @brief Construct a plane with normal direction and offset 
  Plane(S a, S b, S c, S d);

  Plane();

  S signedDistance(const Vector3<S>& p) const;

  S distance(const Vector3<S>& p) const;

  /// @brief Compute AABB
  void computeLocalAABB() override;

  /// @brief Get node type: a plane 
  NODE_TYPE getNodeType() const override;

  /// @brief Plane normal 
  Vector3<S> n;

  /// @brief Plane offset 
  S d;

protected:
  
  /// @brief Turn non-unit normal into unit 
  void unitNormalTest();
};

using Planef = Plane<float>;
using Planed = Plane<double>;

template <typename S>
Plane<S> transform(const Plane<S>& a, const Transform3<S>& tf)
{
  /// suppose the initial halfspace is n * x <= d
  /// after transform (R, T), x --> x' = R x + T
  /// and the new half space becomes n' * x' <= d'
  /// where n' = R * n
  ///   and d' = d + n' * T

  Vector3<S> n = tf.linear() * a.n;
  S d = a.d + n.dot(tf.translation());

  return Plane<S>(n, d);
}

//============================================================================//
//                                                                            //
//                              Implementations                               //
//                                                                            //
//============================================================================//

//==============================================================================
template <typename S>
Plane<S>::Plane(const Vector3<S>& n, S d)
  : ShapeBase<S>(), n(n), d(d)
{
  unitNormalTest();
}

//==============================================================================
template <typename S>
Plane<S>::Plane(S a, S b, S c, S d)
  : ShapeBase<S>(), n(a, b, c), d(d)
{
  unitNormalTest();
}

//==============================================================================
template <typename S>
Plane<S>::Plane() : ShapeBase<S>(), n(1, 0, 0), d(0)
{
  // Do nothing
}

//==============================================================================
template <typename S>
S Plane<S>::signedDistance(const Vector3<S>& p) const
{
  return n.dot(p) - d;
}

//==============================================================================
template <typename S>
S Plane<S>::distance(const Vector3<S>& p) const
{
  return std::abs(n.dot(p) - d);
}

//==============================================================================
template <typename S>
void Plane<S>::computeLocalAABB()
{
  computeBV(*this, Transform3<S>::Identity(), this->aabb_local);
  this->aabb_center = this->aabb_local.center();
  this->aabb_radius = (this->aabb_local.min_ - this->aabb_center).norm();
}

//==============================================================================
template <typename S>
NODE_TYPE Plane<S>::getNodeType() const
{
  return GEOM_PLANE;
}

//==============================================================================
template <typename S>
void Plane<S>::unitNormalTest()
{
  S l = n.norm();
  if(l > 0)
  {
    S inv_l = 1.0 / l;
    n *= inv_l;
    d *= inv_l;
  }
  else
  {
    n << 1, 0, 0;
    d = 0;
  }
}

} // namespace fcl

#include "fcl/object/geometry/shape/detail/bv_computer_plane.h"

#endif
