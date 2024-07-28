#include "time_manager.h"
#include <algorithm>

namespace ChessEngine
{

    TimeManager::TimeManager() : allocated_time_ms(0), time_left_ms(0), increment_ms(0), moves_to_go(0), complexity_factor(1.0) {}

    void TimeManager::set_time_control(int time_left_ms, int increment_ms, int moves_to_go)
    {
        this->time_left_ms = time_left_ms;
        this->increment_ms = increment_ms;
        this->moves_to_go = moves_to_go;
        this->allocated_time_ms = calculate_move_time();
    }

    void TimeManager::start_turn()
    {
        start_time = std::chrono::steady_clock::now();
    }

    bool TimeManager::should_stop()
    {
        auto current_time = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time).count();
        return elapsed >= allocated_time_ms;
    }

    void TimeManager::adjust_for_position_complexity(double complexity_factor)
    {
        this->complexity_factor = std::clamp(complexity_factor, 0.5, 2.0);
        allocated_time_ms = static_cast<int>(allocated_time_ms * complexity_factor);
    }

    int TimeManager::calculate_move_time()
    {
        int base_time;
        if (moves_to_go > 0)
        {
            base_time = time_left_ms / moves_to_go;
        }
        else
        {
            base_time = time_left_ms / 30; // Assume 30 more moves in the game
        }

        // Add a portion of the increment, but ensure we don't use more than 80% of available time
        int move_time = std::min(base_time + increment_ms / 2, static_cast<int>(time_left_ms * 0.8));

        return move_time;
    }

} // namespace ChessEngine