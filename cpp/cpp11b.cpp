// C++11 Experiment with thread, mutex, and condition_variable.
// GCC: Compile with "-std=c++11 -pthread"
/*
This program starts some threads that take an abstract action at random
(1 to 10) intervals.  Each thread waits on a condition variable for the 
turn count to update.  Each time it wakes up, it checks if it is time to
take its next action.  Each thread exits after taking N actions.

The main program starts the actor threads then begins incrementing the turn
count and signalling the condition variable until there are no more live
threads. Finally, it joins the treads and returns.

The threads don't wake up to check the current turn every turn.  They are
waking up after many, many turns, seemingly at random, to check the current
turn and take action or not.

*/

#include <unistd.h>

#include <atomic>
#include <condition_variable>
#include <cstdlib>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

const useconds_t DELAY_USEC = 5000;
const int NUM_ACTORS = 4;
const int NUM_ACTIONS = 4;

std::mutex io_lock;
std::mutex turn_lock;
std::condition_variable next_turn;
std::atomic<int> current_turn { 0 };
std::atomic<int> num_live_actors { 0 };

int next_rand( int max )
{
    int n = std::rand();
    n = n > 0 ? n : -n;
    n = 1 + ( n % max );
    return n;
}

void actor_body( int id )
{
    std::unique_lock<std::mutex> lock( turn_lock );

    for (int i = 1; i <= NUM_ACTIONS; i++) {
        int next_action = current_turn + ( next_rand( 10 ) );
        std::cout << "Actor #" << id << " waiting for turn " << next_action
                << std::endl;
        while ( next_action > current_turn ) {
            next_turn.wait( lock );
            std::cout << "Actor #" << id << " checking current turn at " 
                    << current_turn << std::endl;
        }
        std::cout << "Actor #" << id << " takes action #" << i << " on turn "
                << current_turn << std::endl;
    }
    std::cout << "Actor #" << id << " is done." << std::endl;
    num_live_actors--;
}

int main( int argc, char **argv )
{
    std::vector<std::thread> actors;

    std::cout << "--- Starting " << NUM_ACTORS << " actors" << std::endl;
    for ( int i = 1; i <= NUM_ACTORS; i++ ) {
        num_live_actors++;
        actors.push_back( std::thread( actor_body, i ) );
    }

    std::cout << "--- Starting turn count" << std::endl;
    while ( num_live_actors > 0 ) {
        std::unique_lock<std::mutex> lock( turn_lock ); // what does this do?
        usleep( DELAY_USEC );
        current_turn++;
        next_turn.notify_all();
        //std::this_thread::yield();
    }

    std::cout << "--- Synchronizing actors" << std::endl;
    for ( auto& t : actors )
        t.join();

    std::cout << "--- Done" << std::endl;
    return 0;
}

/* PROGRAM OUTPUT

--- Starting 4 actors
Actor #3 waiting for turn 4
Actor #2 waiting for turn 7
--- Starting turn count
Actor #2 takes action #1 on turn 18
Actor #2 waiting for turn 26
Actor #4 waiting for turn 24
Actor #3 takes action #1 on turn 18
Actor #3 waiting for turn 22
Actor #1 waiting for turn 24
Actor #2 takes action #2 on turn 130
Actor #2 waiting for turn 137
Actor #1 takes action #1 on turn 816
Actor #1 waiting for turn 819
Actor #2 takes action #3 on turn 7833
Actor #2 waiting for turn 7843
Actor #3 takes action #2 on turn 7833
Actor #3 waiting for turn 7835
Actor #1 takes action #2 on turn 7833
Actor #1 waiting for turn 7836
Actor #4 takes action #1 on turn 7833
Actor #4 waiting for turn 7841
Actor #4 takes action #2 on turn 13484
Actor #4 waiting for turn 13485
Actor #2 takes action #4 on turn 13484
Actor #2 is done.
Actor #3 takes action #3 on turn 13484
Actor #3 waiting for turn 13494
Actor #1 takes action #3 on turn 13484
Actor #1 waiting for turn 13488
Actor #1 takes action #4 on turn 14098
Actor #1 is done.
Actor #4 takes action #3 on turn 17090
Actor #4 waiting for turn 17097
Actor #3 takes action #4 on turn 17090
Actor #3 is done.
Actor #4 takes action #4 on turn 17270
Actor #4 is done.
--- Synchronizing actors
--- Done


*/
