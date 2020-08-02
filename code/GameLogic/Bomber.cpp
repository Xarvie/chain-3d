//
// Created by caspasex on 2020/7/8.
//

#include "Bomber.h"
#include "Data.h"

int Bomber::upEvent(bool press)
{
    real ang = Real::Div(Real::Pi, Real::FromInt(180));
    worldData->unit1->moveObj.move(Real::Mul(ang, Real::FromInt(270)));
    return 0;
}

int Bomber::downEvent(bool press)
{
    real ang = Real::Div(Real::Pi, Real::FromInt(180));
    worldData->unit1->moveObj.move(Real::Mul(ang, Real::FromInt(90)));
    return 0;
}

int Bomber::leftEvent(bool press)
{
    real ang = Real::Div(Real::Pi, Real::FromInt(180));
    worldData->unit1->moveObj.move(Real::Mul(ang, Real::FromInt(180)));
    return 0;
}

int Bomber::rightEvent(bool press)
{
    real ang = Real::Div(Real::Pi, Real::FromInt(180));
    worldData->unit1->moveObj.move(Real::Mul(ang, Real::FromInt(0)));
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
