//
// Created by caspase on 7/24/2020.
//

#ifndef INC_3D_COLLISION_H
#define INC_3D_COLLISION_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <set>
#include <vector>
#include <map>
#include "Unit.h"
#include "vec3r.h"

class AABB;

class Collision {
public:
    Collision();

    int init(int x, int y, int z);

    int add(AABB* unit);

    int test(AABB* aabb);

    std::map<int64_t, AABB*> data;
};

extern Collision *worldCollision;


class AABB {

public:
    /**
     * Constructor.
     */
    AABB();

    /**
     * Constructor.
     */
    AABB(const vec3r &min, const vec3r &max);

    /**
     * Constructor.
     */
    AABB(const AABB &box);

    /**
     * Gets the center point of the bounding box.
     */
    vec3r getCenter();

    /* Near face, specified counter-clockwise looking towards the origin from the positive z-axis.
     * verts[0] : left top front
     * verts[1] : left bottom front
     * verts[2] : right bottom front
     * verts[3] : right top front
     *
     * Far face, specified counter-clockwise looking towards the origin from the negative z-axis.
     * verts[4] : right top back
     * verts[5] : right bottom back
     * verts[6] : left bottom back
     * verts[7] : left top back
     */
    void getCorners(vec3r *dst) const;

    /**
     * Tests whether this bounding box intersects the specified bounding object.
     */
    bool intersects(const AABB &aabb) const;

    /**
     * check whether the point is in.
     */
    bool containPoint(const vec3r &point) const;

    /**
     * Sets this bounding box to the smallest bounding box
     * that contains both this bounding object and the specified bounding box.
     */
    void merge(const AABB &box);

    /**
     * Sets this bounding box to the specified values.
     */
    void set(const vec3r &min, const vec3r &max);

    /**
     * reset min and max value.
     */
    void reset();

    bool isEmpty() const;

    /**
     * update the _min and _max from the given point.
     */
    void updateMinMax(const vec3r *point, ssize_t num);

    /**
     * Transforms the bounding box by the given transformation matrix.
     */
    void transform(const glm::mat4 &mat);

public:
    vec3r _min;
    vec3r _max;
};


#endif //INC_3D_COLLISION_H
