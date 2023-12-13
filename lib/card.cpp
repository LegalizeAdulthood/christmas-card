#include <card.h>

#include "gothicMerryChristmas.h"
#include "options.h"
#include "wideMerryChristmas.h"

#include <curses.h>

#include <algorithm>
#include <cctype>
#include <chrono>
#include <string_view>

namespace card
{

using namespace std::chrono_literals;

using clock_t = std::chrono::high_resolution_clock;
using time_point_t = std::chrono::time_point<clock_t>;
using duration_t = clock_t::duration;

enum class AnimationControl
{
    Continue = 0,
    Pause = 1,
    SingleStep = 2,
    Quit = 3
};

void renderFrame(int frame, AnimationControl control)
{
    const time_point_t start{clock_t::now()};

    if (shouldRenderGothicMerryChristmas(frame))
        renderGothicMerryChristmas(frame);
    else if (shouldRenderWideMerryChristmas(frame))
        renderWideMerryChristmas(frame - LINES * 3);

    if (getOptions().debug)
    {
        mvprintw(LINES - 1, 0, "Frame %d, LINES=%d, COLS=%d, ", frame, LINES, COLS);
        if (has_colors())
        {
            printw("color (%d colors, %d pairs)", COLORS, COLOR_PAIRS);
        }
        else
        {
            printw("B&W");
        }
        if (control == AnimationControl::Pause)
        {
            printw(" (paused)");
        }
        else if (control == AnimationControl::SingleStep)
        {
            printw(" (single step)");
        }
        clrtoeol();
    }

    refresh();

    const duration_t duration = clock_t::now() - start;
    const int        ms = static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(duration).count());
    const int        FRAME_TIME_MS{100};
    if (ms < FRAME_TIME_MS)
    {
        napms(FRAME_TIME_MS - static_cast<int>(ms));
    }
}

int main(const std::vector<std::string_view> &args)
{
    parseOptions(args);
    initscr();
    if (has_colors())
    {
        start_color();
        init_pair(1, COLOR_RED, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
    }
    curs_set(getOptions().cursor);
    nodelay(stdscr, TRUE);
    scrollok(stdscr, TRUE);

    bool             singleStep{getOptions().singleStep};
    AnimationControl control{singleStep ? AnimationControl::SingleStep : AnimationControl::Continue};
    int              frame{};
    while (control != AnimationControl::Quit)
    {
        renderFrame(frame, control);

        const int ch = std::tolower(getch());
        // toggle pause/continue
        if (ch == ' ')
        {
            control = (control == AnimationControl::Pause) || singleStep ? AnimationControl::Continue
                                                                         : AnimationControl::Pause;
        }
        // toggle single step/continue
        else if (ch == 's')
        {
            singleStep = !singleStep;
            control = singleStep ? AnimationControl::SingleStep : AnimationControl::Continue;
        }
        // quit
        else if (ch == 'q')
        {
            control = AnimationControl::Quit;
        }

        if (control == AnimationControl::Continue)
        {
            ++frame;
            // if single step, only advance one frame
            if (singleStep)
            {
                control = AnimationControl::SingleStep;
            }
        }
    }

    endwin();
    return 0;
}

} // namespace card
