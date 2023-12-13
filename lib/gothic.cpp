#include "gothic.h"

#include "options.h"
#include "sprite.h"

#include <curses.h>

#include <algorithm>
#include <chrono>
#include <string_view>

namespace card
{

namespace
{

const char *const sprite[] = {
    // clang-format off
    R"sprite(            /\\,/\\,)sprite",
    R"sprite(           /| || ||)sprite",
    R"sprite(           || || ||   _-_  ,._-_ ,._-_ '\\/\\)sprite",
    R"sprite(           ||=|= ||  || \\  ||    ||    || ;')sprite",
    R"sprite(          ~|| || ||  ||/    ||    ||    ||/)sprite",
    R"sprite(           |, \\,\\, \\,/   \\,   \\,   |/)sprite",
    R"sprite(          _-                           ()sprite",
    R"sprite(                                        -_-)sprite",
    R"sprite()sprite",
    R"sprite(  ,- _~. ,,                     ,)sprite",
    R"sprite( (' /|   ||           '        ||             _)sprite",
    R"sprite(((  ||   ||/\\ ,._-_ \\  _-_, =||= \\/\\/\\  < \,  _-_,)sprite",
    R"sprite(((  ||   || ||  ||   || ||_.   ||  || || ||  /-|| ||_.)sprite",
    R"sprite( ( / |   || ||  ||   ||  ~ ||  ||  || || || (( ||  ~ ||)sprite",
    R"sprite(  -____- \\ |/  \\,  \\ ,-_-   \\, \\ \\ \\  \/\\ ,-_-)sprite",
    R"sprite(           _/)sprite"
    // clang-format on
};

const int spriteWidth = getSpriteWidth(sprite);
const int spriteHeight = getSpriteHeight(sprite);

bool shouldRenderGothicMerryChristmas(int frame)
{
    return frame < (LINES + spriteHeight) * 3;
}

void renderRedraw(int frame, int phase)
{
    int beginSpriteLine{};
    int endSpriteLine{spriteHeight};
    int startRow{0};
    // phase 1: sprite scrolling in from top
    if (phase < spriteHeight)
    {
        beginSpriteLine = spriteHeight - phase - 1;
    }
    // phase 2: sprite wholly on screen
    else if (phase < LINES)
    {
        startRow = phase - (spriteHeight - 1);
    }
    // phase 3: sprite scrolling off bottom
    else
    {
        endSpriteLine = phase - (LINES - spriteHeight) - 2;
        startRow = phase - (spriteHeight - 1);
    }
    if (getOptions().debug)
    {
        mvprintw(0, 0, "Phase: %d\nbegin %d, end %d\nstart %d", phase, beginSpriteLine, endSpriteLine, startRow);
        clrtoeol();
    }

    const int x{(COLS - spriteWidth) / 2 - 1};
    int       y{startRow};
    if (startRow > 0)
    {
        move(startRow - 1, x);
        clrtoeol();
    }
    for (int i = beginSpriteLine; i < endSpriteLine; ++i)
    {
        if (has_colors() && frame >= (LINES + spriteHeight))
        {
            if (i < 8)
            {
                attrset(COLOR_PAIR(1));
            }
            else
            {
                attrset(COLOR_PAIR(2));
            }
        }
        mvaddstr(y, x, sprite[i]);
        if (has_colors() && frame >= LINES)
        {
            attrset(A_NORMAL);
        }
        clrtoeol();
        ++y;
    }
}

void renderScroll(int frame, int phase)
{
    static int lastFrame{-1};
    if (lastFrame == frame)
        return;

    lastFrame = frame;
    scrl(-1);
    if (getOptions().debug)
    {
        mvaddstr(1, 0, "                ");
        mvprintw(0, 0, "Phase: %d", phase);
        clrtoeol();
    }
    if (phase < spriteHeight)
    {
        int       spriteLine = spriteHeight - 1 - phase;
        const int x{(COLS - spriteWidth) / 2 - 1};
        if (has_colors() && frame >= LINES + spriteHeight)
        {
            if (phase < 8)
            {
                attrset(COLOR_PAIR(1));
            }
            else
            {
                attrset(COLOR_PAIR(2));
            }
        }
        mvaddstr(0, x, sprite[spriteLine]);
        if (has_colors() && frame >= LINES)
        {
            attrset(A_NORMAL);
        }
        clrtoeol();
    }
}

class GothicRenderer : public Renderer
{
public:
    int  getFrameCount() const override { return (LINES + spriteHeight) * 3; }
    void render(int frame, int subFrame) override;
};

// Three phases of the animation
// 1. scroll partial sprite down from top
// 2. scroll sprite through window to bottom
// 3. scroll sprite off bottom
void GothicRenderer::render(int frame, int /*subFrame*/)
{
    enum class Strategy
    {
        Redraw = 1,
        Scroll = 2
    };
    static Strategy strategy{Strategy::Scroll};

    const int phase = frame % (LINES + spriteHeight);
    if (strategy == Strategy::Redraw)
    {
        renderRedraw(frame, phase);
    }
    else
    {
        renderScroll(frame, phase);
    }
}

} // namespace

std::shared_ptr<Renderer> createGothicMerryChristmas()
{
    return std::make_shared<GothicRenderer>();
}

} // namespace card
