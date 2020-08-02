//
// Created by caspase on 7/24/2020.
//

#include "Collision.h"

#include <iostream>

#include <set>
#include "Unit.h"

Collision::Collision() {

}

int Collision::init(int x, int y, int z){

    return 0;
}

int Collision::add(AABB* unit)
{
    glm::int64_t id = (int64_t)unit;
    data[id] = unit;
    return 0;
}

int Collision::test(AABB* aabb){
    for(auto & E : this->data)
    {
        if(aabb == E.second)
            continue;
        if(aabb->intersects(*E.second))
        {
            return 1;
        }
    }
    return 0;
}

AABB::AABB()
{
    reset();
}

AABB::AABB(const vec3r& min, const vec3r& max)
{
    set(min, max);
}

AABB::AABB(const AABB& box)
{
    set(box._min,box._max);
}

//获取包围盒中心点坐标
vec3r AABB::getCenter()
{
    vec3r center;
    center.x = Real::Half*(Real::Add(_min.x, _max.x));
    center.y = Real::Half*(Real::Add(_min.y, _max.y));
    center.z = Real::Half*(Real::Add(_min.z, _max.z));

    return center;
}
//获取包围盒八个顶点信息
void AABB::getCorners(vec3r *dst) const
{
    assert(dst);

    // Near face, specified counter-clockwise looking towards the origin from the positive z-axis.
    // 朝着Z轴正方向的面

    // 左上顶点坐标
    dst[0] = vec3r(_min.x, _max.y, _max.z);
    // 左下顶点坐标
    dst[1] = vec3r(_min.x, _min.y, _max.z);
    // 右下顶点坐标
    dst[2] = vec3r(_max.x, _min.y, _max.z);
    // 右上顶点坐标
    dst[3] = vec3r(_max.x, _max.y, _max.z);

    // Far face, specified counter-clockwise looking towards the origin from the negative z-axis.
    // 朝着Z轴负方向的面

    // 右上顶点坐标
    dst[4] = vec3r(_max.x, _max.y, _min.z);
    // 右下顶点坐标.
    dst[5] = vec3r(_max.x, _min.y, _min.z);
    // 左下顶点坐标.
    dst[6] = vec3r(_min.x, _min.y, _min.z);
    // 左上顶点坐标.
    dst[7] = vec3r(_min.x, _max.y, _min.z);
}
//判断两个包围盒是否碰撞
bool AABB::intersects(const AABB& aabb) const
{
    bool x1 = _min.x >= aabb._min.x && _min.x <= aabb._max.x;
    bool x2 = aabb._min.x >= _min.x && aabb._min.x <= _max.x;
    bool y1 = _min.y >= aabb._min.y && _min.y <= aabb._max.y;
    bool y2 = aabb._min.y >= _min.y && aabb._min.y <= _max.y;
    bool z1 = _min.z >= aabb._min.z && _min.z <= aabb._max.z;
    bool z2 = aabb._min.z >= _min.z && aabb._min.z <= _max.z;
    return ((x1) || (x2)) &&
           ((y1) || (y2)) &&
           ((z1) || (z2));
}

//判断点和包围盒是否碰撞
bool AABB::containPoint(const vec3r& point) const
{
    if (point.x < _min.x) return false;
    if (point.y < _min.y) return false;
    if (point.z < _min.z) return false;
    if (point.x > _max.x) return false;
    if (point.y > _max.y) return false;
    if (point.z > _max.z) return false;
    return true;
}

//生成一个新的包围盒 同时容纳两个包围盒， 新的包围盒 的_min 各轴要是其他两个最小的那个，_max各轴要是其他两个最大的那个
void AABB::merge(const AABB& box)
{
    // Calculate the new minimum point.计算新的最小点坐标
    _min.x = std::min(_min.x, box._min.x);
    _min.y = std::min(_min.y, box._min.y);
    _min.z = std::min(_min.z, box._min.z);

    // Calculate the new maximum point.计算新的最大点坐标
    _max.x = std::max(_max.x, box._max.x);
    _max.y = std::max(_max.y, box._max.y);
    _max.z = std::max(_max.z, box._max.z);
}
//设置最大顶点与最小顶点
void AABB::set(const vec3r& min, const vec3r& max)
{
    this->_min = min;
    this->_max = max;
}
//顶点复位 初始化信息
void AABB::reset()
{
    _min = vec3r(99999.0f, 99999.0f, 99999.0f);
    _max= vec3r(-99999.0f, -99999.0f, -99999.0f);
}
//检测坐标信息是否有误
bool AABB::isEmpty() const
{
    return _min.x > _max.x || _min.y > _max.y || _min.z > _max.z;
}
//由给定点坐标点重新确定最大最小的坐标向量
void AABB::updateMinMax(const vec3r* point, ssize_t num)
{
    for (ssize_t i = 0; i < num; i++)
    {
        // Leftmost point.
        if (point[i].x < _min.x)
            _min.x = point[i].x;

        // Lowest point.
        if (point[i].y < _min.y)
            _min.y = point[i].y;

        // Farthest point.
        if (point[i].z < _min.z)
            _min.z = point[i].z;

        // Rightmost point.
        if (point[i].x > _max.x)
            _max.x = point[i].x;

        // Highest point.
        if (point[i].y > _max.y)
            _max.y = point[i].y;

        // Nearest point.
        if (point[i].z > _max.z)
            _max.z = point[i].z;
    }
}
//通过给定的变换矩阵对包围盒进行变换
void AABB::transform(const glm::mat4& mat)
{
    vec3r corners[8];//保存包围盒八个顶点

//
//    // Near face, specified counter-clockwise //朝向z轴正方向的面
//
//    // Left-top-front.
//    corners[0].set(_min.x, _max.y, _max.z);
//    // Left-bottom-front.
//    corners[1].set(_min.x, _min.y, _max.z);
//    // Right-bottom-front.
//    corners[2].set(_max.x, _min.y, _max.z);
//    // Right-top-front.
//    corners[3].set(_max.x, _max.y, _max.z);
//
//
//
//    // Far face, specified clockwise //朝向z轴负方向的面
//
//    // Right-top-back.
//    corners[4].set(_max.x, _max.y, _min.z);
//    // Right-bottom-back.
//    corners[5].set(_max.x, _min.y, _min.z);
//    // Left-bottom-back.
//    corners[6].set(_min.x, _min.y, _min.z);
//    // Left-top-back.
//    corners[7].set(_min.x, _max.y, _min.z);
//
//
//
//    //顶点变换
//    // Transform the corners, recalculate the min and max points along the way.
//    for (int i = 0; i < 8; i++)
//        mat.transformPoint(&corners[i]);   //mat 是变换矩阵，变换 &corners[i] 向量。
//    //复位最大顶点最小顶点
    reset();
    //重新计算最大最小点信息
    updateMinMax(corners, 8);
}
