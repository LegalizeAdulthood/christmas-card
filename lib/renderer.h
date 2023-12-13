#pragma once

namespace card
{

class Renderer
{
public:
    virtual ~Renderer() = default;

    virtual int getFrameCount() const = 0;
    virtual void render(int frame, int subFrame) = 0;
};

} // namespace card
