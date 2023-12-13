#pragma once

namespace card
{

struct Renderer
{
    int numFrames;
    void (*renderer)(int frame, int subFrame);
};

} // namespace card
