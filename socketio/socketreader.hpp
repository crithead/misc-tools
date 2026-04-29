/// @file socket.hpp
/// @brief Socket server functions.
#pragma once

#include "options.hpp"

/// @brief  Start a socket server that uses epoll(7) to wait.
/// @param opts Program options.
extern void SocketServerEpoll(const Options& opts);

/// @brief  Start a socket server that uses poll(2) to wait.
/// @param opts Program options.
extern void SocketServerPoll(const Options& opts);

/// @brief  Start a socket server that uses select(2) to wait.
/// @param opts Program options.
extern void SocketServerSelect(const Options& opts);
