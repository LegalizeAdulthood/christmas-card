#include "wide.h"

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
    R"sprite(88b           d88                                                   ,ad8888ba,  88                     88)sprite",
    R"sprite(888b         d888                                                  d8"'    `"8b 88                     ""             ,d)sprite",
    R"sprite(88`8b       d8'88                                                 d8'           88                                    88)sprite",
    R"sprite(88 `8b     d8' 88  ,adPPYba, 8b,dPPYba, 8b,dPPYba, 8b       d8    88            88,dPPYba,  8b,dPPYba, 88 ,adPPYba, MM88MMM 88,dPYba,,adPYba,  ,adPPYYba, ,adPPYba,)sprite",
    R"sprite(88  `8b   d8'  88 a8P_____88 88P'   "Y8 88P'   "Y8 `8b     d8'    88            88P'    "8a 88P'   "Y8 88 I8[    ""   88    88P'   "88"    "8a ""     `Y8 I8[    "")sprite",
    R"sprite(88   `8b d8'   88 8PP""""""" 88         88          `8b   d8'     Y8,           88       88 88         88  `"Y8ba,    88    88      88      88 ,adPPPPP88  `"Y8ba,)sprite",
    R"sprite(88    `888'    88 "8b,   ,aa 88         88           `8b,d8'       Y8a.    .a8P 88       88 88         88 aa    ]8I   88,   88      88      88 88,    ,88 aa    ]8I)sprite",
    R"sprite(88     `8'     88  `"Ybbd8"' 88         88             Y88'         `"Y8888Y"'  88       88 88         88 `"YbbdP"'   "Y888 88      88      88 `"8bbdP"Y8 `"YbbdP"')sprite",
    R"sprite(                                                       d8')sprite",
    R"sprite(                                                      d8')sprite"
    // clang-format on
};

const int spriteWidth = getSpriteWidth(sprite);
const int spriteHeight = getSpriteHeight(sprite);

enum class Strategy
{
    Redraw = 1,
    Pad = 2
};

class WideRenderer : public Renderer
{
public:
    WideRenderer();
    ~WideRenderer() override;

    int getFrameCount() const override
    {
        return (COLS + spriteWidth) * 3;
    }
    void render(int frame, int subFrame) override;

private:
    void renderRedraw(int frame, int subFrame);
    void renderPad(int frame, int subFrame);

    Strategy m_strategy{Strategy::Redraw};
    WINDOW  *m_pad{};
    int      m_lastStart{};
};

WideRenderer::WideRenderer()
{
    if (m_strategy == Strategy::Pad)
    {
        m_pad = newpad(spriteHeight, spriteWidth);
    }
}

WideRenderer::~WideRenderer()
{
    if (m_pad != nullptr)
    {
        delwin(m_pad);
        m_pad = nullptr;
    }
}

void WideRenderer::renderRedraw(int frame, int subFrame)
{
    const int phase{subFrame % spriteWidth};
    if (has_colors())
    {
        attrset(COLOR_PAIR(1));
    }

    if (frame > 0)
    {
        move(m_lastStart, 0);
        clrtoeol();
    }
    const int x = phase;
    int       y{(LINES - spriteHeight) / 2 - 1};
    m_lastStart = y;
    for (int i = 0; i < spriteHeight; ++i)
    {
        std::string_view line{sprite[i]};
        if (x > static_cast<int>(line.length()))
        {
            move(y, 0);
        }
        else
        {
            mvaddstr(y, 0, line.substr(x).data());
        }
        clrtoeol();
        ++y;
    }

    if (has_colors())
    {
        attrset(A_NORMAL);
    }
}

void WideRenderer::renderPad(int frame, int subFrame)
{
    const int phase{subFrame % spriteWidth};
    if (has_colors())
    {
        attrset(COLOR_PAIR(1));
    }

    static int lastStart{};
    if (frame > 0)
    {
        move(lastStart, 0);
        clrtoeol();
    }
    const int x = phase;
    int       y{(LINES - spriteHeight) / 2 - 1};
    lastStart = y;
    for (int i = 0; i < spriteHeight; ++i)
    {
        std::string_view line{sprite[i]};
        if (x > static_cast<int>(line.length()))
        {
            move(y, 0);
        }
        else
        {
            mvaddstr(y, 0, line.substr(x).data());
        }
        clrtoeol();
        ++y;
    }

    if (has_colors())
    {
        attrset(A_NORMAL);
    }
}

void WideRenderer::render(int frame, int subFrame)
{
    if (m_strategy == Strategy::Redraw)
    {
        renderRedraw(frame, subFrame);
    }
    else
    {
        renderPad(frame, subFrame);
    }
}

} // namespace

std::shared_ptr<Renderer> createWideMerryChristmas()
{
    return std::make_shared<WideRenderer>();
}

} // namespace card
