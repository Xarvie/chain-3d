//
// Created by caspasex on 2020/7/8.
//

#include "Bomber.h"
#include "Data.h"

#include "Queue.h"
#include "Render.h"

Bomber* game = nullptr;

int Bomber::init()
{
    initMap();
    initUnit();

    return 0;
}

int Bomber::initMap()
{
    Map map;


    gd.maps.emplace_back(map);
    return 0;
}

int Bomber::initUnit()
{
    for(int i = 0; i < sizeof(sss) / sizeof(sss[0]); i++)
    {
        Unit unit;
        unit.posObj.pos = (vec3r(Real::FromInt( sss[i][0]), Real::FromInt(sss[i][1]),Real::FromInt(sss[i][2])));
        unit.modelObj.spiritModelId = sss[i][3];
        gd.maps[0].spiritSet.emplace_back(unit);
        Render* r = Render::get();
        static Render::Task t;
        t.type = Render::Task::TYPE::ADD_SPIRIT;
        t.u = unit;
        r->drawTask(t);
    }

    for(int i = 0; i < map1Unit.size(); i++)
    {
        Unit unit;
        unit.posObj.pos = map1Unit[i].first;
        unit.modelObj.spiritModelId =  map1Unit[i].second;
        unit.modelObj.anim = resType[unit.modelObj.spiritModelId].animAll>1;
        gd.maps[0].unitSet.emplace_back(unit);
        Render* r = Render::get();
        static Render::Task t;
        t.type = Render::Task::TYPE::ADD_UNIT;
        t.u = unit;
        r->drawTask(t);
    }

    return 0;
}



int Bomber::upEvent(bool press)
{
    real ang = Real::Div(Real::Pi, Real::FromInt(180));
    //worldData->unit1->moveObj.move(Real::Mul(ang, Real::FromInt(270)));
    return 0;
}

int Bomber::downEvent(bool press)
{
    real ang = Real::Div(Real::Pi, Real::FromInt(180));
    //worldData->unit1->moveObj.move(Real::Mul(ang, Real::FromInt(90)));
    return 0;
}

int Bomber::leftEvent(bool press)
{
    real ang = Real::Div(Real::Pi, Real::FromInt(180));
    //worldData->unit1->moveObj.move(Real::Mul(ang, Real::FromInt(180)));
    return 0;
}

int Bomber::rightEvent(bool press)
{
    real ang = Real::Div(Real::Pi, Real::FromInt(180));
    //worldData->unit1->moveObj.move(Real::Mul(ang, Real::FromInt(0)));
    return 0;
}

int Bomber::aEvent(bool press)
{
    return 0;
}

int Bomber::bEvent(bool press)
{
    return 0;
}

int Bomber::xEvent(bool press)
{
    return 0;
}

int Bomber::yEvent(bool press)
{
    return 0;
}

int Bomber::startEvent(bool press)
{
    return 0;
}

int Bomber::backEvent(bool press)
{
    return 0;
}
