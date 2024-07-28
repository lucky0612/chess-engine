#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

#include <chrono>
#include "../core/types.h"

namespace ChessEngine
{

    class TimeManager
    {
    public:
        TimeManager();

        void set_time_control(int time_left_ms, int increment_ms, int moves_to_go = 0);
        void start_turn();
        bool should_stop();
        void adjust_for_position_complexity(double complexity_factor);

    private:
        std::chrono::steady_clock::time_point start_time;
        int allocated_time_ms;
        int time_left_ms;
        int increment_ms;
        int moves_to_go;
        double complexity_factor;

        int calculate_move_time();
    };

} // namespace ChessEngine

#endif // TIME_MANAGER_H