#include "LED.h"

#include <limits>

void LED::Update(std::list<Blob> blobs)
{
    // Search for the closest blob to the predicted position
    double min_dist = std::numeric_limits<double>::max();
    std::list<Blob>::iterator index;

    for(std::list<Blob>::iterator it = blobs.begin(); it != blobs.end(); ++it)
    {
        double diff = pred.back() - *it;
        if (diff < min_dist)
        {
            index = it;
            min_dist = diff;
        }
    }
    
    // Add to list
    if (pos.size() >= LIST_SIZE)
    {
        pos.pop_front();
    }

    pos.push_back(*index);
    blobs.erase(index);

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

Blob LED::GetLastPosition()
{
    return pos.back();
}

Blob LED::GetLastPrediction()
{
    return pred.back();
}
