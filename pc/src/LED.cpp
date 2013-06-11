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

    // std::cout << "[LED.cpp] pos: " << new_blob.pos << std::endl;
    Predict();
}

void LED::Predict()
{
    Blob predicted;
    Blob current = pos.back(); 
    auto last_it = pos.rbegin();
    ++last_it;
    Blob prev = *(last_it);
    
    // std::cout << "[LED.cpp] current: " << current.pos << std::endl;
    // std::cout << "[LED.cpp] prev: " << prev.pos << std::endl;

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

Blob LED::GetPenultimatePrediction() const
{
    if (pred.size() > 1) 
    { 
        auto last_it = pred.rbegin();
        ++last_it;
        return *last_it;
    }
    else { return GetLastPrediction(); }
}
