#pragma once
#include <string>
#include "Baner.h"

class DynamicBaner: public Baner
{
    protected:
    float *pnum = nullptr;
    int digits;

    public:
    DynamicBaner(std::string msg, char frame_ch, float *fp, int digits=5): 
        Baner(msg, frame_ch, 5+digits), digits(digits) {this->pnum = fp;};
    ~DynamicBaner() override {};

    void draw(Canvas &c, int x, int y) override;
};