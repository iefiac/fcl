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

#ifndef FCL_NARROWPHASE_DETAIL_HALFSPACE_H
#define FCL_NARROWPHASE_DETAIL_HALFSPACE_H


namespace fcl
{

namespace detail
{

template <typename S>
S halfspaceIntersectTolerance();

template <>
float halfspaceIntersectTolerance();

template <>
double halfspaceIntersectTolerance();

template <typename S>
bool sphereHalfspaceIntersect(const Sphere<S>& s1, const Transform3<S>& tf1,
                              const Halfspace<S>& s2, const Transform3<S>& tf2,
                              std::vector<ContactPoint<S>>* contacts);

template <typename S>
bool ellipsoidHalfspaceIntersect(const Ellipsoid<S>& s1, const Transform3<S>& tf1,
                                 const Halfspace<S>& s2, const Transform3<S>& tf2,
                                 std::vector<ContactPoint<S>>* contacts);

/// @brief box half space, a, b, c  = +/- edge size
/// n^T * (R(o + a v1 + b v2 + c v3) + T) <= d
/// so (R^T n) (a v1 + b v2 + c v3) + n * T <= d
/// check whether d - n * T - (R^T n) (a v1 + b v2 + c v3) >= 0 for some a, b, c
/// the max value of left side is d - n * T + |(R^T n) (a v1 + b v2 + c v3)|, check that is enough
template <typename S>
bool boxHalfspaceIntersect(const Box<S>& s1, const Transform3<S>& tf1,
                           const Halfspace<S>& s2, const Transform3<S>& tf2);

template <typename S>
bool boxHalfspaceIntersect(const Box<S>& s1, const Transform3<S>& tf1,
                           const Halfspace<S>& s2, const Transform3<S>& tf2,
                           std::vector<ContactPoint<S>>* contacts);

template <typename S>
bool capsuleHalfspaceIntersect(const Capsule<S>& s1, const Transform3<S>& tf1,
                               const Halfspace<S>& s2, const Transform3<S>& tf2,
                               std::vector<ContactPoint<S>>* contacts);

template <typename S>
bool cylinderHalfspaceIntersect(const Cylinder<S>& s1, const Transform3<S>& tf1,
                                const Halfspace<S>& s2, const Transform3<S>& tf2,
                                std::vector<ContactPoint<S>>* contacts);

template <typename S>
bool coneHalfspaceIntersect(const Cone<S>& s1, const Transform3<S>& tf1,
                            const Halfspace<S>& s2, const Transform3<S>& tf2,
                            std::vector<ContactPoint<S>>* contacts);

template <typename S>
bool convexHalfspaceIntersect(const Convex<S>& s1, const Transform3<S>& tf1,
                              const Halfspace<S>& s2, const Transform3<S>& tf2,
                              Vector3<S>* contact_points, S* penetration_depth, Vector3<S>* normal);

template <typename S>
bool halfspaceTriangleIntersect(const Halfspace<S>& s1, const Transform3<S>& tf1,
                                const Vector3<S>& P1, const Vector3<S>& P2, const Vector3<S>& P3, const Transform3<S>& tf2,
                                Vector3<S>* contact_points, S* penetration_depth, Vector3<S>* normal);

/// @brief return whether plane collides with halfspace
/// if the separation plane of the halfspace is parallel with the plane
///     return code 1, if the plane's normal is the same with halfspace's normal and plane is inside halfspace, also return plane in pl
///     return code 2, if the plane's normal is oppositie to the halfspace's normal and plane is inside halfspace, also return plane in pl
///     plane is outside halfspace, collision-free
/// if not parallel
///     return the intersection ray, return code 3. ray origin is p and direction is d
template <typename S>
bool planeHalfspaceIntersect(const Plane<S>& s1, const Transform3<S>& tf1,
                             const Halfspace<S>& s2, const Transform3<S>& tf2,
                             Plane<S>& pl,
                             Vector3<S>& p, Vector3<S>& d,
                             S& penetration_depth,
                             int& ret);

/// @brief return whether two halfspace intersect
/// if the separation planes of the two halfspaces are parallel
///    return code 1, if two halfspaces' normal are same and s1 is in s2, also return s1 in s;
///    return code 2, if two halfspaces' normal are same and s2 is in s1, also return s2 in s;
///    return code 3, if two halfspaces' normal are opposite and s1 and s2 are into each other;
///    collision free, if two halfspaces' are separate;
/// if the separation planes of the two halfspaces are not parallel, return intersection ray, return code 4. ray origin is p and direction is d
/// collision free return code 0
template <typename S>
bool halfspaceIntersect(const Halfspace<S>& s1, const Transform3<S>& tf1,
                        const Halfspace<S>& s2, const Transform3<S>& tf2,
                        Vector3<S>& p, Vector3<S>& d,
                        Halfspace<S>& s,
                        S& penetration_depth,
                        int& ret);

//============================================================================//
//                                                                            //
//                              Implementations                               //
//                                                                            //
//============================================================================//

//==============================================================================
template <typename S>
S halfspaceIntersectTolerance()
{
  return 0;
}

//==============================================================================
template <>
inline float halfspaceIntersectTolerance()
{
  return 0.0001f;
}

//==============================================================================
template <>
inline double halfspaceIntersectTolerance()
{
  return 0.0000001;
}

//==============================================================================
template <typename S>
bool sphereHalfspaceIntersect(const Sphere<S>& s1, const Transform3<S>& tf1,
                              const Halfspace<S>& s2, const Transform3<S>& tf2,
                              std::vector<ContactPoint<S>>* contacts)
{
  const Halfspace<S> new_s2 = transform(s2, tf2);
  const Vector3<S>& center = tf1.translation();
  const S depth = s1.radius - new_s2.signedDistance(center);

  if (depth >= 0)
  {
    if (contacts)
    {
      const Vector3<S> normal = -new_s2.n; // pointing from s1 to s2
      const Vector3<S> point = center - new_s2.n * s1.radius + new_s2.n * (depth * 0.5);
      const S penetration_depth = depth;

      contacts->emplace_back(normal, point, penetration_depth);
    }

    return true;
  }
  else
  {
    return false;
  }
}

//==============================================================================
template <typename S>
bool ellipsoidHalfspaceIntersect(const Ellipsoid<S>& s1, const Transform3<S>& tf1,
                                 const Halfspace<S>& s2, const Transform3<S>& tf2,
                                 std::vector<ContactPoint<S>>* contacts)
{
  // We first compute a single contact in the ellipsoid coordinates, tf1, then
  // will transform it to the world frame. So we use a new halfspace that is
  // expressed in the ellipsoid coordinates.
  const Halfspace<S>& new_s2 = transform(s2, tf1.inverse(Eigen::Isometry) * tf2);

  // Compute distance between the ellipsoid's center and a contact plane, whose
  // normal is equal to the halfspace's normal.
  const Vector3<S> normal2(std::pow(new_s2.n[0], 2), std::pow(new_s2.n[1], 2), std::pow(new_s2.n[2], 2));
  const Vector3<S> radii2(std::pow(s1.radii[0], 2), std::pow(s1.radii[1], 2), std::pow(s1.radii[2], 2));
  const S center_to_contact_plane = std::sqrt(normal2.dot(radii2));

  // Depth is the distance between the contact plane and the halfspace.
  const S depth = center_to_contact_plane + new_s2.d;

  if (depth >= 0)
  {
    if (contacts)
    {
      // Transform the results to the world coordinates.
      const Vector3<S> normal = tf1.linear() * -new_s2.n; // pointing from s1 to s2
      const Vector3<S> support_vector = (1.0/center_to_contact_plane) * Vector3<S>(radii2[0]*new_s2.n[0], radii2[1]*new_s2.n[1], radii2[2]*new_s2.n[2]);
      const Vector3<S> point_in_halfspace_coords = support_vector * (0.5 * depth / new_s2.n.dot(support_vector) - 1.0);
      const Vector3<S> point = tf1 * point_in_halfspace_coords; // roughly speaking, a middle point of the intersecting volume
      const S penetration_depth = depth;

      contacts->emplace_back(normal, point, penetration_depth);
    }

    return true;
  }
  else
  {
    return false;
  }
}

//==============================================================================
template <typename S>
bool boxHalfspaceIntersect(const Box<S>& s1, const Transform3<S>& tf1,
                           const Halfspace<S>& s2, const Transform3<S>& tf2)
{
  Halfspace<S> new_s2 = transform(s2, tf2);

  const Matrix3<S>& R = tf1.linear();
  const Vector3<S>& T = tf1.translation();

  Vector3<S> Q = R.transpose() * new_s2.n;
  Vector3<S> A(Q[0] * s1.side[0], Q[1] * s1.side[1], Q[2] * s1.side[2]);
  Vector3<S> B = A.cwiseAbs();

  S depth = 0.5 * (B[0] + B[1] + B[2]) - new_s2.signedDistance(T);
  return (depth >= 0);
}

//==============================================================================
template <typename S>
bool boxHalfspaceIntersect(const Box<S>& s1, const Transform3<S>& tf1,
                           const Halfspace<S>& s2, const Transform3<S>& tf2,
                           std::vector<ContactPoint<S>>* contacts)
{
  if(!contacts)
  {
    return boxHalfspaceIntersect(s1, tf1, s2, tf2);
  }
  else
  {
    const Halfspace<S> new_s2 = transform(s2, tf2);

    const Matrix3<S>& R = tf1.linear();
    const Vector3<S>& T = tf1.translation();

    Vector3<S> Q = R.transpose() * new_s2.n;
    Vector3<S> A(Q[0] * s1.side[0], Q[1] * s1.side[1], Q[2] * s1.side[2]);
    Vector3<S> B = A.cwiseAbs();

    S depth = 0.5 * (B[0] + B[1] + B[2]) - new_s2.signedDistance(T);
    if(depth < 0) return false;

    Vector3<S> axis[3];
    axis[0] = R.col(0);
    axis[1] = R.col(1);
    axis[2] = R.col(2);

    /// find deepest point
    Vector3<S> p(T);
    int sign = 0;

    if(std::abs(Q[0] - 1) < halfspaceIntersectTolerance<S>() || std::abs(Q[0] + 1) < halfspaceIntersectTolerance<S>())
    {
      sign = (A[0] > 0) ? -1 : 1;
      p += axis[0] * (0.5 * s1.side[0] * sign);
    }
    else if(std::abs(Q[1] - 1) < halfspaceIntersectTolerance<S>() || std::abs(Q[1] + 1) < halfspaceIntersectTolerance<S>())
    {
      sign = (A[1] > 0) ? -1 : 1;
      p += axis[1] * (0.5 * s1.side[1] * sign);
    }
    else if(std::abs(Q[2] - 1) < halfspaceIntersectTolerance<S>() || std::abs(Q[2] + 1) < halfspaceIntersectTolerance<S>())
    {
      sign = (A[2] > 0) ? -1 : 1;
      p += axis[2] * (0.5 * s1.side[2] * sign);
    }
    else
    {
      for(std::size_t i = 0; i < 3; ++i)
      {
        sign = (A[i] > 0) ? -1 : 1;
        p += axis[i] * (0.5 * s1.side[i] * sign);
      }
    }

    /// compute the contact point from the deepest point
    if (contacts)
    {
      const Vector3<S> normal = -new_s2.n;
      const Vector3<S> point = p + new_s2.n * (depth * 0.5);
      const S penetration_depth = depth;

      contacts->emplace_back(normal, point, penetration_depth);
    }

    return true;
  }
}

//==============================================================================
template <typename S>
bool capsuleHalfspaceIntersect(const Capsule<S>& s1, const Transform3<S>& tf1,
                               const Halfspace<S>& s2, const Transform3<S>& tf2,
                               std::vector<ContactPoint<S>>* contacts)
{
  Halfspace<S> new_s2 = transform(s2, tf2);

  const Matrix3<S>& R = tf1.linear();
  const Vector3<S>& T = tf1.translation();

  Vector3<S> dir_z = R.col(2);

  S cosa = dir_z.dot(new_s2.n);
  if(std::abs(cosa) < halfspaceIntersectTolerance<S>())
  {
    S signed_dist = new_s2.signedDistance(T);
    S depth = s1.radius - signed_dist;
    if(depth < 0) return false;

    if (contacts)
    {
      const Vector3<S> normal = -new_s2.n;
      const Vector3<S> point = T + new_s2.n * (0.5 * depth - s1.radius);
      const S penetration_depth = depth;

      contacts->emplace_back(normal, point, penetration_depth);
    }

    return true;
  }
  else
  {
    int sign = (cosa > 0) ? -1 : 1;
    Vector3<S> p = T + dir_z * (s1.lz * 0.5 * sign);

    S signed_dist = new_s2.signedDistance(p);
    S depth = s1.radius - signed_dist;
    if(depth < 0) return false;

    if (contacts)
    {
      const Vector3<S> normal = -new_s2.n;
      const Vector3<S> point = p - new_s2.n * s1.radius + new_s2.n * (0.5 * depth);  // deepest point
      const S penetration_depth = depth;

      contacts->emplace_back(normal, point, penetration_depth);
    }

    return true;
  }
}

//==============================================================================
template <typename S>
bool cylinderHalfspaceIntersect(const Cylinder<S>& s1, const Transform3<S>& tf1,
                                const Halfspace<S>& s2, const Transform3<S>& tf2,
                                std::vector<ContactPoint<S>>* contacts)
{
  Halfspace<S> new_s2 = transform(s2, tf2);

  const Matrix3<S>& R = tf1.linear();
  const Vector3<S>& T = tf1.translation();

  Vector3<S> dir_z = R.col(2);
  S cosa = dir_z.dot(new_s2.n);

  if(cosa < halfspaceIntersectTolerance<S>())
  {
    S signed_dist = new_s2.signedDistance(T);
    S depth = s1.radius - signed_dist;
    if(depth < 0) return false;

    if (contacts)
    {
      const Vector3<S> normal = -new_s2.n;
      const Vector3<S> point = T + new_s2.n * (0.5 * depth - s1.radius);
      const S penetration_depth = depth;

      contacts->emplace_back(normal, point, penetration_depth);
    }

    return true;
  }
  else
  {
    Vector3<S> C = dir_z * cosa - new_s2.n;
    if(std::abs(cosa + 1) < halfspaceIntersectTolerance<S>() || std::abs(cosa - 1) < halfspaceIntersectTolerance<S>())
      C = Vector3<S>(0, 0, 0);
    else
    {
      S s = C.norm();
      s = s1.radius / s;
      C *= s;
    }

    int sign = (cosa > 0) ? -1 : 1;
    // deepest point
    Vector3<S> p = T + dir_z * (s1.lz * 0.5 * sign) + C;
    S depth = -new_s2.signedDistance(p);
    if(depth < 0) return false;
    else
    {
      if (contacts)
      {
        const Vector3<S> normal = -new_s2.n;
        const Vector3<S> point = p + new_s2.n * (0.5 * depth);
        const S penetration_depth = depth;

        contacts->emplace_back(normal, point, penetration_depth);
      }

      return true;
    }
  }
}

//==============================================================================
template <typename S>
bool coneHalfspaceIntersect(const Cone<S>& s1, const Transform3<S>& tf1,
                            const Halfspace<S>& s2, const Transform3<S>& tf2,
                            std::vector<ContactPoint<S>>* contacts)
{
  Halfspace<S> new_s2 = transform(s2, tf2);

  const Matrix3<S>& R = tf1.linear();
  const Vector3<S>& T = tf1.translation();

  Vector3<S> dir_z = R.col(2);
  S cosa = dir_z.dot(new_s2.n);

  if(cosa < halfspaceIntersectTolerance<S>())
  {
    S signed_dist = new_s2.signedDistance(T);
    S depth = s1.radius - signed_dist;
    if(depth < 0) return false;
    else
    {
      if (contacts)
      {
        const Vector3<S> normal = -new_s2.n;
        const Vector3<S> point = T - dir_z * (s1.lz * 0.5) + new_s2.n * (0.5 * depth - s1.radius);
        const S penetration_depth = depth;

        contacts->emplace_back(normal, point, penetration_depth);
      }

      return true;
    }
  }
  else
  {
    Vector3<S> C = dir_z * cosa - new_s2.n;
    if(std::abs(cosa + 1) < halfspaceIntersectTolerance<S>() || std::abs(cosa - 1) < halfspaceIntersectTolerance<S>())
      C = Vector3<S>(0, 0, 0);
    else
    {
      S s = C.norm();
      s = s1.radius / s;
      C *= s;
    }

    Vector3<S> p1 = T + dir_z * (0.5 * s1.lz);
    Vector3<S> p2 = T - dir_z * (0.5 * s1.lz) + C;

    S d1 = new_s2.signedDistance(p1);
    S d2 = new_s2.signedDistance(p2);

    if(d1 > 0 && d2 > 0) return false;
    else
    {
      if (contacts)
      {
        const S penetration_depth = -std::min(d1, d2);
        const Vector3<S> normal = -new_s2.n;
        const Vector3<S> point = ((d1 < d2) ? p1 : p2) + new_s2.n * (0.5 * penetration_depth);

        contacts->emplace_back(normal, point, penetration_depth);
      }

      return true;
    }
  }
}

//==============================================================================
template <typename S>
bool convexHalfspaceIntersect(const Convex<S>& s1, const Transform3<S>& tf1,
                              const Halfspace<S>& s2, const Transform3<S>& tf2,
                              Vector3<S>* contact_points, S* penetration_depth, Vector3<S>* normal)
{
  Halfspace<S> new_s2 = transform(s2, tf2);

  Vector3<S> v;
  S depth = std::numeric_limits<S>::max();

  for(int i = 0; i < s1.num_points; ++i)
  {
    Vector3<S> p = tf1 * s1.points[i];

    S d = new_s2.signedDistance(p);
    if(d < depth)
    {
      depth = d;
      v = p;
    }
  }

  if(depth <= 0)
  {
    if(contact_points) *contact_points = v - new_s2.n * (0.5 * depth);
    if(penetration_depth) *penetration_depth = depth;
    if(normal) *normal = -new_s2.n;
    return true;
  }
  else
    return false;
}

//==============================================================================
template <typename S>
bool halfspaceTriangleIntersect(const Halfspace<S>& s1, const Transform3<S>& tf1,
                                const Vector3<S>& P1, const Vector3<S>& P2, const Vector3<S>& P3, const Transform3<S>& tf2,
                                Vector3<S>* contact_points, S* penetration_depth, Vector3<S>* normal)
{
  Halfspace<S> new_s1 = transform(s1, tf1);

  Vector3<S> v = tf2 * P1;
  S depth = new_s1.signedDistance(v);

  Vector3<S> p = tf2 * P2;
  S d = new_s1.signedDistance(p);
  if(d < depth)
  {
    depth = d;
    v = p;
  }

  p = tf2 * P3;
  d = new_s1.signedDistance(p);
  if(d < depth)
  {
    depth = d;
    v = p;
  }

  if(depth <= 0)
  {
    if(penetration_depth) *penetration_depth = -depth;
    if(normal) *normal = new_s1.n;
    if(contact_points) *contact_points = v - new_s1.n * (0.5 * depth);
    return true;
  }
  else
    return false;
}

//==============================================================================
template <typename S>
bool planeHalfspaceIntersect(const Plane<S>& s1, const Transform3<S>& tf1,
                             const Halfspace<S>& s2, const Transform3<S>& tf2,
                             Plane<S>& pl,
                             Vector3<S>& p, Vector3<S>& d,
                             S& penetration_depth,
                             int& ret)
{
  Plane<S> new_s1 = transform(s1, tf1);
  Halfspace<S> new_s2 = transform(s2, tf2);

  ret = 0;

  Vector3<S> dir = (new_s1.n).cross(new_s2.n);
  S dir_norm = dir.squaredNorm();
  if(dir_norm < std::numeric_limits<S>::epsilon()) // parallel
  {
    if((new_s1.n).dot(new_s2.n) > 0)
    {
      if(new_s1.d < new_s2.d)
      {
        penetration_depth = new_s2.d - new_s1.d;
        ret = 1;
        pl = new_s1;
        return true;
      }
      else
        return false;
    }
    else
    {
      if(new_s1.d + new_s2.d > 0)
        return false;
      else
      {
        penetration_depth = -(new_s1.d + new_s2.d);
        ret = 2;
        pl = new_s1;
        return true;
      }
    }
  }

  Vector3<S> n = new_s2.n * new_s1.d - new_s1.n * new_s2.d;
  Vector3<S> origin = n.cross(dir);
  origin *= (1.0 / dir_norm);

  p = origin;
  d = dir;
  ret = 3;
  penetration_depth = std::numeric_limits<S>::max();

  return true;
}

//==============================================================================
template <typename S>
bool halfspaceIntersect(const Halfspace<S>& s1, const Transform3<S>& tf1,
                        const Halfspace<S>& s2, const Transform3<S>& tf2,
                        Vector3<S>& p, Vector3<S>& d,
                        Halfspace<S>& s,
                        S& penetration_depth,
                        int& ret)
{
  Halfspace<S> new_s1 = transform(s1, tf1);
  Halfspace<S> new_s2 = transform(s2, tf2);

  ret = 0;

  Vector3<S> dir = (new_s1.n).cross(new_s2.n);
  S dir_norm = dir.squaredNorm();
  if(dir_norm < std::numeric_limits<S>::epsilon()) // parallel
  {
    if((new_s1.n).dot(new_s2.n) > 0)
    {
      if(new_s1.d < new_s2.d) // s1 is inside s2
      {
        ret = 1;
        penetration_depth = std::numeric_limits<S>::max();
        s = new_s1;
      }
      else // s2 is inside s1
      {
        ret = 2;
        penetration_depth = std::numeric_limits<S>::max();
        s = new_s2;
      }
      return true;
    }
    else
    {
      if(new_s1.d + new_s2.d > 0) // not collision
        return false;
      else // in each other
      {
        ret = 3;
        penetration_depth = -(new_s1.d + new_s2.d);
        return true;
      }
    }
  }

  Vector3<S> n = new_s2.n * new_s1.d - new_s1.n * new_s2.d;
  Vector3<S> origin = n.cross(dir);
  origin *= (1.0 / dir_norm);

  p = origin;
  d = dir;
  ret = 4;
  penetration_depth = std::numeric_limits<S>::max();

  return true;
}

} // namespace detail

} // namespace fcl

#endif
