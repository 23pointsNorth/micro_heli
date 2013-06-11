#include "LED.h"

#include <limits>

void LED::Update(const Blob& new_blob)
{
    // Add to list
    if (pos.size() >= LIST_SIZE)
    {
        pos.pop_front();
    }

    pos.push_back(new_blob);

    Predict();
}

void LED::Predict()
{
    Blob predicted;
    Blob current = pos.back();
    Blob prev = *(--pos.end());
    
    predicted.pos = current.pos + (current.pos - prev.pos);
    predicted.area = current.area + (current.area - prev.area);   
    
    if (pred.size() >= LIST_SIZE)
    {
        pred.pop_front();
    }

    pred.push_back(predicted);
}

Blob LED::GetLastPosition() const
{
    return pos.back();
}

Blob LED::GetLastPrediction() const
{
    return pred.back();
}
