//
// Created by caspase on 9/6/2020.
//

#ifndef INC_3D_MOVESYSTEM_H
#define INC_3D_MOVESYSTEM_H

#include <vector>
class BomberSystem {
public:






    /*
int MoveObj::move(real degree){
        real distance = moveSpeed;
        real x = Real::Mul(distance, Real::Cos(degree));
        real y = Real::Mul(distance, Real::Sin(degree));
        //std::cout << "ox,oy:" << Real::FloorToInt(aabb->_min.x) << "," << Real::FloorToInt(aabb->_min.y) << std::endl;
        real newMinx = Real::Add(aabb->_min.x, x);
        real newMiny = Real::Add(aabb->_min.y, y);
        real newMaxx = Real::Add(aabb->_max.x, x);
        real newMaxy = Real::Add(aabb->_max.y, y);
        AABB old = *aabb;
        aabb->_min.x = newMinx;
        aabb->_min.y = newMiny;
        aabb->_max.x = newMaxx;
        aabb->_max.y = newMaxy;

        //std::cout << "mx,my:" << Real::FloorToInt(newMinx) << "," << Real::FloorToInt(newMiny) << std::endl;
        if(worldData->worldCollision.test(aabb))
        {
            *aabb = old;
            return 0;
        }
        this->pos->x = Real::Add(this->pos->x, x);
        this->pos->y = Real::Add(this->pos->y, y);
        this->aabb->_min.x = newMinx;
        this->aabb->_min.y = newMiny;
        this->aabb->_max.x = newMaxx;
        this->aabb->_max.y = newMaxy;
        return 0;
    }
 * */

};


#endif //INC_3D_MOVESYSTEM_H
